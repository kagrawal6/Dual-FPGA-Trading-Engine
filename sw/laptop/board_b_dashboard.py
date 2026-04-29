#!/usr/bin/env python3
"""
Board B — laptop telemetry dashboard (Plotly Dash)
====================================================
Reads newline-delimited JSON from Board B UART (telemetry_server.py on PYNQ).

Dependencies:
    pip install dash plotly pyserial

This script **is** a small web server: after you start it in the terminal, open a
browser to the printed URL (default http://127.0.0.1:8050/). Use ``--browser`` to
open that URL automatically. Serial device is ``--port``; HTTP listen port is
``--dash-port``. Use ``--host 0.0.0.0`` only if you need another machine on your
LAN to reach the dashboard (less private).

Usage:
    python board_b_dashboard.py --port /dev/ttyUSB0
    python board_b_dashboard.py --port COM5 --baud 115200 --dash-port 8050 --browser
"""

from __future__ import annotations

import argparse
import csv
import io
import json
import threading
import time
import webbrowser
from collections import deque
from pathlib import Path
from typing import Any, Deque, Dict, List, Optional, Tuple

import dash
from dash import Dash, Input, Output, State, callback, dcc, html, no_update
import plotly.graph_objects as go

try:
    import serial
except ImportError as e:  # pragma: no cover
    raise SystemExit("Install pyserial: pip install pyserial") from e

NUM_SYMBOLS = 16
NUM_HIST_BINS = 16
HIST_BIN_CYCLES = 32
NS_PER_CYCLE = 10
BIN_WIDTH_NS = HIST_BIN_CYCLES * NS_PER_CYCLE
STALE_MS = 500.0
DEFAULT_HISTORY_SEC = 120.0

SYMBOL_NAMES = [
    "AAPL", "MSFT", "GOOG", "META", "NVDA", "AMD", "INTC", "AVGO",
    "AMZN", "TSLA", "JPM", "GS", "JNJ", "PFE", "XOM", "CVX",
]

# Board A market regimes (set on Board A; label here so the audience sees what demo you run)
REGIME_LABELS = ("CALM", "VOLATILE", "BURST", "ADVERSARIAL")
REGIME_INFO: Dict[str, Tuple[str, str]] = {
    "CALM": (
        "#238636",
        "Quiet synthetic market — smaller moves. Use this when explaining the basics.",
    ),
    "VOLATILE": (
        "#9e6a03",
        "Larger random swings — good for showing risk limits and wider spreads.",
    ),
    "BURST": (
        "#0969da",
        "Bursty activity — highlights throughput and how the trader keeps up.",
    ),
    "ADVERSARIAL": (
        "#cf222e",
        "Stress-style conditions — use when discussing halts, rejects, or worst case.",
    ),
}


def _hex_to_rgb(h: str) -> Tuple[int, int, int]:
    h = h.lstrip("#")
    return int(h[0:2], 16), int(h[2:4], 16), int(h[4:6], 16)


def regime_chart_tint(regime_name: str, dark: bool) -> Tuple[str, str]:
    """Plotly paper_bg / plot_bg tint from Board A regime (truthful: same data, visual skin)."""
    name = regime_name.upper() if regime_name else "CALM"
    if name not in REGIME_INFO:
        name = "CALM"
    r, g, b = _hex_to_rgb(REGIME_INFO[name][0])
    a = 0.14 if dark else 0.20
    tint = f"rgba({r},{g},{b},{a})"
    base = theme_colors(dark)
    return base["card"], tint


def latency_regime_caption(regime_name: str) -> str:
    name = (regime_name or "CALM").upper()
    tips = {
        "CALM": "Expect tighter latency clusters — fewer tail events.",
        "VOLATILE": "Tails often widen — compare p99 to CALM when you switch.",
        "BURST": "Bursts stress sustained throughput; watch reject rate in parallel.",
        "ADVERSARIAL": "Worst-case stress: halts and rejects are part of the story.",
    }
    return tips.get(name, tips["CALM"])


def cash_to_dollars(cash_lo: int, cash_hi: int) -> float:
    cash_lo &= 0xFFFFFFFF
    cash_hi &= 0xFFFFFFFF
    raw = (cash_hi << 32) | cash_lo
    if cash_hi & 0x8000:
        raw -= 1 << 48
    return raw / 65536.0


def compute_percentiles(hist_bins: List[int], bin_width_ns: float = BIN_WIDTH_NS) -> Tuple[float, float]:
    total = sum(hist_bins)
    if total == 0:
        return 0.0, 0.0
    cumulative = 0
    p50 = p99 = 0.0
    for i, count in enumerate(hist_bins):
        cumulative += count
        if cumulative >= total * 0.50 and p50 == 0.0:
            p50 = (i + 0.5) * bin_width_ns
        if cumulative >= total * 0.99:
            p99 = (i + 0.5) * bin_width_ns
            break
    return p50, p99


def theme_colors(dark: bool) -> Dict[str, str]:
    if dark:
        return {
            "bg": "#0d1117",
            "card": "#161b22",
            "text": "#e6edf3",
            "muted": "#8b949e",
            "accent": "#58a6ff",
            "good": "#3fb950",
            "bad": "#f85149",
            "warn": "#d29922",
            "grid": "#30363d",
        }
    return {
        "bg": "#f6f8fa",
        "card": "#ffffff",
        "text": "#1f2328",
        "muted": "#656d76",
        "accent": "#0969da",
        "good": "#1a7f37",
        "bad": "#cf222e",
        "warn": "#9a6700",
        "grid": "#d0d7de",
    }


def fig_blank(message: str, c: Dict[str, str]) -> go.Figure:
    fig = go.Figure()
    fig.add_annotation(
        text=message,
        xref="paper",
        yref="paper",
        x=0.5,
        y=0.5,
        showarrow=False,
        font=dict(size=14, color=c["muted"]),
    )
    fig.update_xaxes(visible=False)
    fig.update_yaxes(visible=False)
    fig.update_layout(
        paper_bgcolor=c["card"],
        plot_bgcolor=c["card"],
        margin=dict(l=20, r=20, t=30, b=20),
    )
    return fig


class SerialTelemetryReader(threading.Thread):
    def __init__(self, port: str, baud: int):
        super().__init__(daemon=True)
        self._port = port
        self._baud = baud
        self._lock = threading.Lock()
        self._ser: Optional[serial.Serial] = None
        self._stop = threading.Event()

        self.connected = False
        self.parse_errors = 0
        self.last_mono: float = 0.0
        self.latest: Dict[str, Any] = {}
        self.rates = {"q": 0.0, "o": 0.0, "f": 0.0, "rej": 0.0}

        self._prev_mono: float = 0.0
        self._prev: Dict[str, int] = {}

        self.history_t: Deque[float] = deque(maxlen=8000)
        self.history_cash: Deque[float] = deque(maxlen=8000)
        self.history_rej: Deque[float] = deque(maxlen=8000)

        self._last_regime_name: str = ""
        self._last_regime_id: int = -1
        self._regime_edge_pending: bool = False

        self._session_cash_start: Optional[float] = None
        self._session_cash_min: Optional[float] = None
        self._session_cash_max: Optional[float] = None

    def stop(self) -> None:
        self._stop.set()
        if self._ser and self._ser.is_open:
            try:
                self._ser.close()
            except Exception:
                pass

    def open_serial(self) -> bool:
        with self._lock:
            if self._ser and self._ser.is_open:
                try:
                    self._ser.close()
                except Exception:
                    pass
            self._ser = None
            self.connected = False
        try:
            ser = serial.Serial(self._port, self._baud, timeout=0.5)
            with self._lock:
                self._ser = ser
                self.connected = True
            return True
        except Exception:
            with self._lock:
                self._ser = None
                self.connected = False
            return False

    def run(self) -> None:
        buf = ""
        while not self._stop.is_set():
            with self._lock:
                ser = self._ser
            if not ser or not ser.is_open:
                time.sleep(0.2)
                continue
            try:
                n = ser.in_waiting
                chunk = ser.read(n if n else 1).decode("utf-8", errors="replace")
                buf += chunk
                while "\n" in buf:
                    line, buf = buf.split("\n", 1)
                    line = line.strip()
                    if not line:
                        continue
                    try:
                        data = json.loads(line)
                    except json.JSONDecodeError:
                        with self._lock:
                            self.parse_errors = min(self.parse_errors + 1, 99999)
                        continue
                    self._ingest(data)
            except Exception:
                with self._lock:
                    self.connected = False
                try:
                    ser.close()
                except Exception:
                    pass
                time.sleep(0.3)

    def _ingest(self, data: Dict[str, Any]) -> None:
        now = time.monotonic()
        with self._lock:
            if self._prev_mono > 0:
                dt = now - self._prev_mono
                if dt > 1e-6:
                    self.rates["q"] = max(
                        0.0, (int(data.get("qps", 0)) - self._prev.get("qps", 0)) / dt
                    )
                    self.rates["o"] = max(
                        0.0, (int(data.get("ops", 0)) - self._prev.get("ops", 0)) / dt
                    )
                    self.rates["f"] = max(
                        0.0, (int(data.get("fps", 0)) - self._prev.get("fps", 0)) / dt
                    )
                    self.rates["rej"] = max(
                        0.0, (int(data.get("rej", 0)) - self._prev.get("rej", 0)) / dt
                    )
            self._prev_mono = now
            self._prev = {
                "qps": int(data.get("qps", 0)),
                "ops": int(data.get("ops", 0)),
                "fps": int(data.get("fps", 0)),
                "rej": int(data.get("rej", 0)),
            }
            cash = cash_to_dollars(
                int(data.get("cash_lo", 0)), int(data.get("cash_hi", 0))
            )
            self.history_t.append(now)
            self.history_cash.append(cash)
            self.history_rej.append(float(self.rates["rej"]))
            if self._session_cash_start is None:
                self._session_cash_start = cash
            self._session_cash_min = (
                cash
                if self._session_cash_min is None
                else min(self._session_cash_min, cash)
            )
            self._session_cash_max = (
                cash
                if self._session_cash_max is None
                else max(self._session_cash_max, cash)
            )
            self.latest = data
            self.last_mono = now

            nm = str(data.get("regime_name") or "").strip().upper()
            rid_raw = data.get("regime")
            try:
                rid_i = int(rid_raw) & 3 if rid_raw is not None else -1
            except (TypeError, ValueError):
                rid_i = -1
            if self._last_regime_id >= 0 and rid_i >= 0 and rid_i != self._last_regime_id:
                self._regime_edge_pending = True
            elif self._last_regime_name and nm and nm != self._last_regime_name:
                self._regime_edge_pending = True
            if nm:
                self._last_regime_name = nm
            if rid_i >= 0:
                self._last_regime_id = rid_i

    def pop_regime_edge(self) -> bool:
        with self._lock:
            e = self._regime_edge_pending
            self._regime_edge_pending = False
            return e

    def snapshot(self) -> Tuple[Dict[str, Any], Dict[str, float], float, bool]:
        with self._lock:
            age_ms = (
                (time.monotonic() - self.last_mono) * 1000 if self.last_mono else 1e9
            )
            return dict(self.latest), dict(self.rates), age_ms, self.connected

    def history_arrays(
        self, window_sec: float
    ) -> Tuple[List[float], List[float], List[float]]:
        cutoff = time.monotonic() - window_sec
        t_list: List[float] = []
        c_list: List[float] = []
        r_list: List[float] = []
        with self._lock:
            for t, c, rr in zip(self.history_t, self.history_cash, self.history_rej):
                if t >= cutoff:
                    t_list.append(t)
                    c_list.append(c)
                    r_list.append(rr)
        if t_list:
            t0 = t_list[0]
            t_rel = [x - t0 for x in t_list]
        else:
            t_rel = []
        return t_rel, c_list, r_list

    def session_cash_stats(self) -> Optional[Dict[str, float]]:
        """Session min/max/start since first telemetry sample (this dashboard run)."""
        with self._lock:
            if self._session_cash_start is None:
                return None
            return {
                "start": float(self._session_cash_start),
                "min": float(self._session_cash_min or self._session_cash_start),
                "max": float(self._session_cash_max or self._session_cash_start),
            }


READER: Optional[SerialTelemetryReader] = None


def build_app(reader: SerialTelemetryReader) -> Dash:
    here = Path(__file__).resolve().parent
    app = Dash(
        __name__,
        suppress_callback_exceptions=True,
        assets_folder=str(here / "assets"),
        external_stylesheets=[
            "https://fonts.googleapis.com/css2?family=IBM+Plex+Mono:wght@400;600&family=IBM+Plex+Sans:wght@400;600;700&display=swap",
        ],
    )
    app.title = "Board B — Trading Engine"

    app.layout = html.Div(
        [
            html.Link(rel="stylesheet", href=app.get_asset_url("boardb_theme.css")),
            dcc.Store(id="telemetry-store", data={}),
            dcc.Store(id="freeze-store", data={"active": False, "payload": None}),
            dcc.Store(id="hotkey-store", data={}),
            dcc.Store(id="regime-modal", data={"open": False, "topic": 0}),
            dcc.Store(
                id="prefs-store",
                data={
                    "dark": True,
                    "history_sec": 120.0,
                    "symbols": list(range(NUM_SYMBOLS)),
                    "show_quotes_bar": True,
                    "enable_sound": False,
                    "enable_confetti": False,
                    "reduced_motion": False,
                },
            ),
            dcc.Interval(id="tick", interval=250, n_intervals=0),
            html.Div(id="confetti-root", className="bb-confetti-root"),
            html.Div(id="clientside-fx-tick", style={"display": "none"}),
            html.Div(id="header-bar"),
            html.Div(
                [
                    dcc.Input(
                        id="port-input",
                        type="text",
                        placeholder="/dev/ttyUSB0 or COM5",
                        style={"width": "220px", "marginRight": "8px"},
                    ),
                    dcc.Input(
                        id="baud-input",
                        type="number",
                        value=115200,
                        style={"width": "100px", "marginRight": "8px"},
                    ),
                    html.Button("Connect", id="btn-connect", n_clicks=0),
                    html.Button("Pause display", id="btn-freeze", n_clicks=0),
                    html.Button("Resume", id="btn-unfreeze", n_clicks=0),
                    dcc.Download(id="download-csv"),
                    html.Button(
                        "Export CSV",
                        id="btn-export",
                        n_clicks=0,
                        style={"marginLeft": "12px"},
                    ),
                ],
                style={
                    "padding": "8px 16px",
                    "display": "flex",
                    "alignItems": "center",
                    "flexWrap": "wrap",
                    "gap": "6px",
                },
            ),
            dcc.Tabs(
                id="main-tabs",
                value="tab-overview",
                persistence=True,
                children=[
                    dcc.Tab(
                        label="Overview",
                        value="tab-overview",
                        children=html.Div(
                            [
                                html.Div(
                                    [
                                        html.Div(
                                            [
                                                html.Span(
                                                    "Market regime (from Board A quotes, decoded on Board B)",
                                                    className="bb-headline",
                                                ),
                                                html.Button(
                                                    "Regime guide · keys 1–4",
                                                    id="btn-regime-learn",
                                                    n_clicks=0,
                                                    className="bb-btn-secondary",
                                                    title="Open read-only guide (keyboard 1–4 highlights rows)",
                                                ),
                                            ],
                                            style={
                                                "display": "flex",
                                                "flexWrap": "wrap",
                                                "alignItems": "center",
                                                "gap": "12px",
                                                "marginBottom": "6px",
                                            },
                                        ),
                                        html.Div(
                                            "Updates automatically when Board A changes REGIME — each QUOTE carries the regime field.",
                                            style={"fontSize": "13px", "opacity": 0.85, "marginBottom": "4px"},
                                        ),
                                        html.Div(id="regime-blurb"),
                                    ],
                                    id="regime-strip",
                                ),
                                html.Div(id="flow-strip"),
                                html.H2(
                                    "Profit & loss (what viewers usually ask first)",
                                    id="pnl-section-title",
                                    style={"marginTop": "8px", "marginBottom": "10px"},
                                ),
                                html.Div(id="pnl-hero"),
                                dcc.Graph(id="fig-pnl"),
                                html.H3(
                                    "Position exposure (shares per symbol)",
                                    id="pos-section-title",
                                    style={"marginTop": "28px", "marginBottom": "8px"},
                                ),
                                dcc.Graph(
                                    id="fig-positions",
                                    style={"height": "520px", "maxWidth": "1100px"},
                                ),
                                html.H3(
                                    "Activity & throughput",
                                    style={
                                        "marginTop": "24px",
                                        "marginBottom": "8px",
                                        "fontSize": "18px",
                                        "fontWeight": "700",
                                        "borderLeft": "5px solid #8b949e",
                                        "paddingLeft": "12px",
                                    },
                                ),
                                dcc.Graph(id="fig-thr", style={"maxWidth": "900px"}),
                                html.H3(
                                    "Latency snapshot",
                                    style={
                                        "marginTop": "20px",
                                        "marginBottom": "8px",
                                        "fontSize": "18px",
                                        "fontWeight": "700",
                                        "borderLeft": "5px solid #8b949e",
                                        "paddingLeft": "12px",
                                    },
                                ),
                                html.Div(
                                    [
                                        html.Div(
                                            dcc.Graph(id="fig-mini-hist"),
                                            style={
                                                "width": "58%",
                                                "minWidth": "300px",
                                                "display": "inline-block",
                                            },
                                        ),
                                        html.Div(
                                            id="scalar-table",
                                            style={
                                                "width": "38%",
                                                "minWidth": "240px",
                                                "display": "inline-block",
                                                "verticalAlign": "top",
                                            },
                                        ),
                                    ],
                                    style={"marginTop": "4px"},
                                ),
                            ],
                            style={"padding": "12px 16px"},
                        ),
                    ),
                    dcc.Tab(
                        label="Latency",
                        value="tab-latency",
                        children=html.Div(
                            dcc.Graph(id="fig-latency", style={"height": "520px"}),
                            style={"padding": "12px 16px"},
                        ),
                    ),
                    dcc.Tab(
                        label="Settings",
                        value="tab-settings",
                        children=html.Div(
                            [
                                html.H3("Settings", style={"marginTop": 0}),
                                html.Label("Theme"),
                                dcc.Checklist(
                                    id="set-dark",
                                    options=[
                                        {
                                            "label": " Dark mode (better on projectors)",
                                            "value": "dark",
                                        }
                                    ],
                                    value=["dark"],
                                ),
                                html.Br(),
                                html.Label("P&L / sparkline history window"),
                                dcc.Dropdown(
                                    id="set-history",
                                    options=[
                                        {"label": "30 s", "value": 30},
                                        {"label": "2 min", "value": 120},
                                        {"label": "10 min", "value": 600},
                                    ],
                                    value=120,
                                    clearable=False,
                                    style={"maxWidth": "280px"},
                                ),
                                html.Br(),
                                html.Label("Symbols shown in position exposure (Overview)"),
                                dcc.Dropdown(
                                    id="set-symbols",
                                    options=[
                                        {"label": SYMBOL_NAMES[i], "value": i}
                                        for i in range(NUM_SYMBOLS)
                                    ],
                                    value=list(range(NUM_SYMBOLS)),
                                    multi=True,
                                    style={"maxWidth": "560px"},
                                ),
                                html.Br(),
                                html.Label("Throughput strip"),
                                dcc.Checklist(
                                    id="set-show-quotes",
                                    options=[
                                        {"label": " Include quote rate", "value": "q"}
                                    ],
                                    value=["q"],
                                ),
                                html.Hr(),
                                html.H4("Regime change effects (optional)"),
                                html.Label("Subtle sound on regime edge (off by default)"),
                                dcc.Checklist(
                                    id="set-sound",
                                    options=[
                                        {
                                            "label": " Enable short chime when Board A regime changes",
                                            "value": "s",
                                        }
                                    ],
                                    value=[],
                                ),
                                html.Br(),
                                html.Label("Confetti burst (consumer energy)"),
                                dcc.Checklist(
                                    id="set-confetti",
                                    options=[
                                        {
                                            "label": " One-shot particles on regime change",
                                            "value": "c",
                                        }
                                    ],
                                    value=[],
                                ),
                                html.Br(),
                                html.Label("Accessibility"),
                                dcc.Checklist(
                                    id="set-reduced",
                                    options=[
                                        {
                                            "label": " Reduced motion (no pulse / confetti / sound)",
                                            "value": "r",
                                        }
                                    ],
                                    value=[],
                                ),
                                html.P(
                                    "Port and baud are set in the bar above (Connect). "
                                    "Regime comes from Board B telemetry (QUOTE field). "
                                    "This dashboard does not write FPGA parameters.",
                                    style={"maxWidth": "640px", "opacity": 0.85},
                                ),
                            ],
                            style={"padding": "16px"},
                        ),
                    ),
                ],
            ),
            html.Div(
                [
                    html.Div(
                        [
                            html.Button(
                                "× Close",
                                id="btn-regime-close",
                                n_clicks=0,
                                className="bb-btn-close",
                            ),
                            html.Div(id="regime-modal-body"),
                        ],
                        className="bb-modal-panel",
                    )
                ],
                id="regime-modal-overlay",
                style={"display": "none"},
            ),
        ],
        id="root",
        style={"minHeight": "100vh"},
    )

    @callback(
        Output("freeze-store", "data"),
        Input("btn-freeze", "n_clicks"),
        Input("btn-unfreeze", "n_clicks"),
        State("freeze-store", "data"),
        State("telemetry-store", "data"),
        prevent_initial_call=True,
    )
    def on_freeze(n_f, n_u, fstore, telem):
        ctx = dash.callback_context
        if not ctx.triggered:
            return no_update
        tid = ctx.triggered[0]["prop_id"].split(".")[0]
        if tid == "btn-freeze":
            pl = dict(telem) if telem else {}
            pl["session_snapshot"] = reader.session_cash_stats()
            pl["regime_edge"] = False
            return {"active": True, "payload": pl}
        if tid == "btn-unfreeze":
            return {"active": False, "payload": None}
        return no_update

    @callback(
        Output("prefs-store", "data"),
        Input("set-dark", "value"),
        Input("set-history", "value"),
        Input("set-symbols", "value"),
        Input("set-show-quotes", "value"),
        Input("set-sound", "value"),
        Input("set-confetti", "value"),
        Input("set-reduced", "value"),
        State("prefs-store", "data"),
    )
    def on_prefs(dark, hist_sec, syms, show_q, sound, confetti, reduced, cur):
        cur = cur or {}
        out = {**cur}
        if dark is not None:
            out["dark"] = bool("dark" in dark)
        if hist_sec is not None:
            out["history_sec"] = float(hist_sec)
        if syms is not None:
            out["symbols"] = [int(x) for x in syms] if syms else list(range(NUM_SYMBOLS))
        if show_q is not None:
            out["show_quotes_bar"] = bool("q" in show_q)
        if sound is not None:
            out["enable_sound"] = bool("s" in sound)
        if confetti is not None:
            out["enable_confetti"] = bool("c" in confetti)
        if reduced is not None:
            out["reduced_motion"] = bool("r" in reduced)
        return out

    @callback(
        Output("regime-blurb", "children"),
        Output("regime-strip", "style"),
        Input("prefs-store", "data"),
        Input("telemetry-store", "data"),
    )
    def render_regime_blurb(prefs, telem):
        prefs = prefs or {}
        telem = telem or {}
        dark = prefs.get("dark", True)
        reduced = prefs.get("reduced_motion", False)
        c = theme_colors(dark)
        latest = telem.get("latest") or {}
        name = str(latest.get("regime_name") or "").strip().upper()
        if not name or name == "?":
            rid = int(latest.get("regime", 0)) & 3
            name = REGIME_LABELS[rid] if rid < len(REGIME_LABELS) else "CALM"
        if name not in REGIME_INFO:
            name = "CALM"
        bg, blurb = REGIME_INFO[name]
        edge = bool(telem.get("regime_edge"))
        pulse_cls = "" if reduced else (" bb-regime-pulse" if edge else "")

        inner = [
            html.Div(
                [
                    html.Span(
                        name.replace("_", " "),
                        className="bb-regime-title",
                    ),
                    html.Span(
                        f" · id={int(latest.get('regime', 0)) & 3}",
                        className="bb-mono bb-regime-id",
                    ),
                ],
                style={"display": "flex", "alignItems": "baseline", "flexWrap": "wrap", "gap": "8px"},
            ),
            html.Div(
                blurb,
                style={
                    "fontSize": "17px",
                    "marginTop": "10px",
                    "lineHeight": "1.5",
                    "maxWidth": "920px",
                    "fontWeight": "500",
                },
            ),
            html.Div(
                "Source: when telemetry includes regime / regime_name (from your Board B PL "
                "register map), this banner tracks Board A’s QUOTE regime field. "
                "Wire those fields in telemetry_server.py to match your friend’s AXI layout.",
                style={
                    "marginTop": "12px",
                    "fontSize": "12px",
                    "opacity": 0.88,
                    "fontFamily": "'IBM Plex Mono', ui-monospace, monospace",
                },
            ),
        ]
        children = html.Div(
            inner,
            className="bb-regime-inner" + pulse_cls,
            style={
                "marginTop": "14px",
                "padding": "20px 22px",
                "borderRadius": "10px",
                "backgroundColor": bg,
                "color": "#fff",
                "boxShadow": "0 2px 12px rgba(0,0,0,0.25)",
            },
        )
        strip_style = {
            "padding": "16px 18px",
            "marginBottom": "16px",
            "borderRadius": "12px",
            "border": f"2px solid {c['grid']}",
            "backgroundColor": c["card"],
            "color": c["text"],
        }
        return children, strip_style

    @callback(
        Output("port-input", "value"),
        Output("baud-input", "value"),
        Input("btn-connect", "n_clicks"),
        State("port-input", "value"),
        State("baud-input", "value"),
        prevent_initial_call=True,
    )
    def on_connect(_n, port, baud):
        if not port:
            return no_update, no_update
        try:
            b = int(baud) if baud is not None else 115200
        except (TypeError, ValueError):
            b = 115200
        reader._port = str(port).strip()
        reader._baud = b
        reader.open_serial()
        return port, b

    @callback(
        Output("download-csv", "data"),
        Input("btn-export", "n_clicks"),
        State("prefs-store", "data"),
        prevent_initial_call=True,
    )
    def on_export(_n, prefs):
        prefs = prefs or {}
        w = float(prefs.get("history_sec", DEFAULT_HISTORY_SEC))
        t_rel, cash_h, rej_h = reader.history_arrays(w)
        out = io.StringIO()
        wtr = csv.writer(out)
        wtr.writerow(["t_rel_s", "cash_usd", "reject_rate_per_s"])
        for i in range(len(t_rel)):
            wtr.writerow([f"{t_rel[i]:.3f}", f"{cash_h[i]:.4f}", f"{rej_h[i]:.4f}"])
        return dict(
            content=out.getvalue(),
            filename="board_b_export.csv",
            type="text/csv",
        )

    @callback(
        Output("telemetry-store", "data"),
        Input("tick", "n_intervals"),
        Input("freeze-store", "data"),
        State("freeze-store", "data"),
    )
    def poll_telemetry(_n, _freeze_trigger, freeze):
        if freeze and freeze.get("active") and freeze.get("payload") is not None:
            return freeze["payload"]
        regime_edge = reader.pop_regime_edge()
        latest, rates, age_ms, connected = reader.snapshot()
        return {
            "latest": latest,
            "rates": rates,
            "age_ms": age_ms,
            "connected": connected,
            "parse_errors": reader.parse_errors,
            "regime_edge": regime_edge,
            "ts": time.time(),
        }

    def _active_data(telem: Dict[str, Any], freeze: Dict[str, Any]) -> Dict[str, Any]:
        if freeze and freeze.get("active") and freeze.get("payload"):
            return freeze["payload"]
        return telem

    @callback(
        Output("header-bar", "children"),
        Output("root", "style"),
        Input("telemetry-store", "data"),
        Input("prefs-store", "data"),
        State("freeze-store", "data"),
    )
    def render_header(telem, prefs, freeze):
        freeze = freeze or {}
        paused = bool(freeze.get("active"))
        telem = _active_data(telem or {}, freeze)
        prefs = prefs or {}
        dark = prefs.get("dark", True)
        c = theme_colors(dark)
        latest = telem.get("latest") or {}
        age_ms = float(telem.get("age_ms", 1e9))
        connected = telem.get("connected", False)
        stale = (age_ms > STALE_MS) and not paused

        rn = str(latest.get("regime_name") or "").strip().upper()
        if not rn or rn == "?":
            rn = REGIME_LABELS[int(latest.get("regime", 0)) & 3]
        regime_show = rn

        state = latest.get("state", "—")
        strat = latest.get("strategy", "—")
        link_up = latest.get("link_up", False)
        risk_halt = latest.get("risk_halt", False)
        link_err = int(latest.get("link_err", 0))
        pe = int(telem.get("parse_errors", 0))

        root_style = {
            "minHeight": "100vh",
            "backgroundColor": c["bg"],
            "color": c["text"],
            "fontFamily": "'IBM Plex Sans', 'Segoe UI', system-ui, sans-serif",
        }

        if paused:
            banner = html.Div(
                "DISPLAY PAUSED — charts frozen; serial may still run in background",
                style={
                    "backgroundColor": c["accent"],
                    "color": "#fff",
                    "padding": "10px 16px",
                    "fontWeight": "600",
                },
            )
        elif not connected:
            banner = html.Div(
                "DISCONNECTED — enter port above and click Connect",
                style={
                    "backgroundColor": c["bad"],
                    "color": "#fff",
                    "padding": "10px 16px",
                    "fontWeight": "600",
                },
            )
        elif stale:
            banner = html.Div(
                f"STALE DATA ({age_ms:.0f} ms since last JSON line)",
                style={
                    "backgroundColor": c["warn"],
                    "color": "#111",
                    "padding": "10px 16px",
                    "fontWeight": "600",
                },
            )
        else:
            ok = link_up and not risk_halt and link_err == 0
            banner = html.Div(
                f"Live · Board A regime (from quotes): {regime_show} · {state} · {strat} · "
                f"{'LINK UP' if link_up else 'LINK DOWN'} · "
                f"{'RISK HALT' if risk_halt else 'Risk OK'} · "
                f"link_err={link_err} · json_parse_err={pe}",
                style={
                    "backgroundColor": c["good"] if ok else c["warn"],
                    "color": "#111" if ok else "#fff",
                    "padding": "10px 16px",
                    "fontWeight": "600",
                },
            )
        return banner, root_style

    @callback(
        Output("flow-strip", "children"),
        Output("pnl-section-title", "style"),
        Output("pnl-hero", "children"),
        Output("fig-pnl", "figure"),
        Output("pos-section-title", "style"),
        Output("fig-positions", "figure"),
        Output("fig-thr", "figure"),
        Output("fig-mini-hist", "figure"),
        Output("scalar-table", "children"),
        Output("fig-latency", "figure"),
        Input("telemetry-store", "data"),
        Input("prefs-store", "data"),
        State("freeze-store", "data"),
    )
    def render_figures(telem, prefs, freeze):
        telem = _active_data(telem or {}, freeze or {})
        prefs = prefs or {}
        dark = prefs.get("dark", True)
        hist_sec = float(prefs.get("history_sec", DEFAULT_HISTORY_SEC))
        sym_filter = prefs.get("symbols", list(range(NUM_SYMBOLS)))
        show_quotes = prefs.get("show_quotes_bar", True)
        c = theme_colors(dark)

        latest = telem.get("latest") or {}
        rates = telem.get("rates") or {}

        rname = str(latest.get("regime_name") or "").strip().upper()
        if not rname or rname == "?":
            rname = REGIME_LABELS[int(latest.get("regime", 0)) & 3]
        chart_paper, chart_plot = regime_chart_tint(rname, dark)
        lat_cap = latency_regime_caption(rname)

        state = latest.get("state", "—")
        risk_halt = latest.get("risk_halt", False)
        fsm_order = ["B_RESET", "B_IDLE", "B_ARMED", "B_TRADING", "B_HALTED"]
        fsm_cells = []
        for s in fsm_order:
            active = state == s
            fsm_cells.append(
                html.Div(
                    s.replace("B_", ""),
                    style={
                        "padding": "8px 14px",
                        "marginRight": "6px",
                        "borderRadius": "6px",
                        "fontWeight": "700",
                        "fontSize": "12px",
                        "backgroundColor": c["accent"] if active else c["grid"],
                        "color": "#fff" if active else c["text"],
                        "border": (
                            f"2px solid {c['accent']}" if active else f"1px solid {c['grid']}"
                        ),
                    },
                )
            )
        pnl_title_style = {
            "marginTop": "8px",
            "marginBottom": "10px",
            "fontSize": "22px",
            "fontWeight": "800",
            "borderLeft": f"6px solid {c['good']}",
            "paddingLeft": "14px",
            "color": c["text"],
        }
        pos_title_style = {
            "marginTop": "28px",
            "marginBottom": "10px",
            "fontSize": "20px",
            "fontWeight": "800",
            "borderLeft": f"6px solid {c['accent']}",
            "paddingLeft": "14px",
            "color": c["text"],
        }

        flow = html.Div(
            [
                html.Div(
                    "Board B pipeline",
                    style={
                        "fontWeight": "700",
                        "marginBottom": "2px",
                        "fontSize": "15px",
                        "color": c["text"],
                    },
                ),
                html.Div(
                    "Logical flow (for narration) — profit is above, not here",
                    style={
                        "fontWeight": "500",
                        "marginBottom": "8px",
                        "fontSize": "12px",
                        "color": c["muted"],
                    },
                ),
                html.Div(
                    [
                        html.Span("Quotes", style=_pill_style(c["muted"], c)),
                        html.Span("→", style={"margin": "0 6px", "color": c["muted"]}),
                        html.Span(
                            "Features + strategy", style=_pill_style(c["muted"], c)
                        ),
                        html.Span("→", style={"margin": "0 6px", "color": c["muted"]}),
                        html.Span(
                            "Risk",
                            style=_pill_style(
                                c["warn"] if risk_halt else c["muted"], c
                            ),
                        ),
                        html.Span("→", style={"margin": "0 6px", "color": c["muted"]}),
                        html.Span(
                            "Orders → Board A", style=_pill_style(c["accent"], c)
                        ),
                        html.Span("→", style={"margin": "0 6px", "color": c["muted"]}),
                        html.Span("Fills", style=_pill_style(c["good"], c)),
                    ],
                    style={"display": "flex", "alignItems": "center", "flexWrap": "wrap"},
                ),
                html.Div(
                    ["FSM: "] + fsm_cells,
                    style={
                        "display": "flex",
                        "alignItems": "center",
                        "marginTop": "10px",
                        "flexWrap": "wrap",
                    },
                ),
            ],
            style={
                "backgroundColor": c["card"],
                "padding": "14px 18px",
                "borderRadius": "8px",
                "marginBottom": "12px",
            },
        )

        cash = cash_to_dollars(
            int(latest.get("cash_lo", 0)), int(latest.get("cash_hi", 0))
        )
        sess_snap = telem.get("session_snapshot") if isinstance(telem, dict) else None
        sess = sess_snap if isinstance(sess_snap, dict) else reader.session_cash_stats()
        if sess:
            sess_delta = cash - sess["start"]
            sess_min = sess["min"]
            sess_max = sess["max"]
        else:
            sess_delta = 0.0
            sess_min = cash
            sess_max = cash
        delta_color = c["good"] if sess_delta >= 0 else c["bad"]
        cash_color = c["good"] if cash >= 0 else c["bad"]

        pnl_hero = html.Div(
            [
                html.Div(
                    [
                        html.Div(
                            [
                                html.Div(
                                    "Realized cash (from Board B hardware)",
                                    style={
                                        "fontSize": "13px",
                                        "fontWeight": "600",
                                        "color": c["muted"],
                                        "textTransform": "uppercase",
                                        "letterSpacing": "0.05em",
                                    },
                                ),
                                html.Div(
                                    f"${cash:,.2f}",
                                    className="bb-mono",
                                    style={
                                        "fontSize": "52px",
                                        "fontWeight": "900",
                                        "lineHeight": "1.1",
                                        "color": cash_color,
                                        "marginTop": "4px",
                                    },
                                ),
                            ],
                            style={"flex": "1.2", "minWidth": "240px"},
                        ),
                        html.Div(
                            [
                                html.Div(
                                    "Session gain / loss",
                                    style={
                                        "fontSize": "13px",
                                        "fontWeight": "600",
                                        "color": c["muted"],
                                        "textTransform": "uppercase",
                                        "letterSpacing": "0.05em",
                                    },
                                ),
                                html.Div(
                                    f"{'+' if sess_delta >= 0 else ''}${sess_delta:,.2f}",
                                    className="bb-mono",
                                    style={
                                        "fontSize": "36px",
                                        "fontWeight": "800",
                                        "color": delta_color,
                                        "marginTop": "6px",
                                    },
                                ),
                                html.Div(
                                    "Since this dashboard first saw telemetry",
                                    style={
                                        "fontSize": "12px",
                                        "color": c["muted"],
                                        "marginTop": "6px",
                                    },
                                ),
                            ],
                            style={
                                "flex": "1",
                                "minWidth": "200px",
                                "borderLeft": f"1px solid {c['grid']}",
                                "paddingLeft": "22px",
                            },
                        ),
                        html.Div(
                            [
                                html.Div(
                                    "Session range (cash)",
                                    style={
                                        "fontSize": "13px",
                                        "fontWeight": "600",
                                        "color": c["muted"],
                                        "textTransform": "uppercase",
                                        "letterSpacing": "0.05em",
                                    },
                                ),
                                html.Div(
                                    f"High ${sess_max:,.2f}",
                                    style={
                                        "fontSize": "18px",
                                        "fontWeight": "700",
                                        "color": c["good"],
                                        "marginTop": "8px",
                                    },
                                ),
                                html.Div(
                                    f"Low ${sess_min:,.2f}",
                                    style={
                                        "fontSize": "18px",
                                        "fontWeight": "700",
                                        "color": c["bad"],
                                        "marginTop": "4px",
                                    },
                                ),
                            ],
                            style={
                                "flex": "0.9",
                                "minWidth": "180px",
                                "borderLeft": f"1px solid {c['grid']}",
                                "paddingLeft": "22px",
                            },
                        ),
                    ],
                    style={
                        "display": "flex",
                        "flexWrap": "wrap",
                        "gap": "18px",
                        "alignItems": "flex-start",
                        "padding": "22px 24px",
                        "borderRadius": "12px",
                        "backgroundColor": c["card"],
                        "border": f"2px solid {c['grid']}",
                    },
                ),
                html.Div(
                    "This is realized P&L from fills (Q32.16), not full mark-to-market unless you add price feeds. "
                    "Positions below show how many shares the engine holds per symbol.",
                    style={
                        "marginTop": "12px",
                        "fontSize": "14px",
                        "lineHeight": "1.45",
                        "color": c["muted"],
                        "maxWidth": "960px",
                    },
                ),
            ]
        )

        t_rel, cash_h, _rej = reader.history_arrays(hist_sec)
        if freeze and freeze.get("active"):
            t_rel = [0.0]
            cash_h = [cash]

        fig_pnl = go.Figure()
        if len(cash_h) > 1:
            fig_pnl.add_trace(
                go.Scatter(
                    x=t_rel,
                    y=cash_h,
                    mode="lines",
                    line=dict(color=c["accent"], width=2),
                    name="Realized cash",
                    hovertemplate="t=%{x:.2f}s<br>$%{y:.2f}<extra></extra>",
                )
            )
        elif len(cash_h) == 1:
            fig_pnl.add_trace(
                go.Scatter(
                    x=[0],
                    y=cash_h,
                    mode="markers",
                    marker=dict(size=10, color=c["accent"]),
                    hovertemplate="$%{y:.2f}<extra></extra>",
                )
            )
        else:
            fig_pnl = fig_blank("Waiting for telemetry…", c)
        fig_pnl.update_layout(
            title="Cash over time (same numbers as the cards above)",
            paper_bgcolor=chart_paper,
            plot_bgcolor=chart_plot,
            font=dict(color=c["text"]),
            height=280,
            margin=dict(l=50, r=20, t=48, b=44),
            xaxis=dict(showgrid=True, gridcolor=c["grid"], title="window (s)"),
            yaxis=dict(showgrid=True, gridcolor=c["grid"], title="USD"),
        )

        bars_x: List[float] = []
        bars_y: List[str] = []
        colors: List[str] = []
        if show_quotes:
            bars_x.append(float(rates.get("q", 0.0)))
            bars_y.append("Quotes/s")
            colors.append(c["muted"])
        bars_x.extend(
            [
                float(rates.get("o", 0.0)),
                float(rates.get("f", 0.0)),
                float(rates.get("rej", 0.0)),
            ]
        )
        bars_y.extend(["Orders/s", "Fills/s", "Risk rej/s"])
        colors.extend([c["accent"], c["good"], c["bad"]])
        fig_thr = go.Figure(
            go.Bar(
                x=bars_x,
                y=bars_y,
                orientation="h",
                marker_color=colors,
                hovertemplate="%{y}: %{x:.1f}<extra></extra>",
            )
        )
        fig_thr.update_layout(
            title="Throughput (Δcounters / Δtime on laptop)",
            paper_bgcolor=chart_paper,
            plot_bgcolor=chart_plot,
            font=dict(color=c["text"]),
            height=220,
            margin=dict(l=100, r=20, t=44, b=30),
            xaxis=dict(showgrid=True, gridcolor=c["grid"]),
            yaxis=dict(showgrid=False),
        )

        hist = [int(x) for x in latest.get("hist", [0] * NUM_HIST_BINS)]
        x_idx = [i * HIST_BIN_CYCLES for i in range(NUM_HIST_BINS)]
        fig_mini = go.Figure(
            go.Bar(
                x=[str(x) for x in x_idx],
                y=hist,
                marker_color=c["accent"],
                hovertemplate="start %{x} cyc<br>count=%{y}<extra></extra>",
            )
        )
        fig_mini.update_layout(
            title="Latency histogram (compact)",
            paper_bgcolor=chart_paper,
            plot_bgcolor=chart_plot,
            font=dict(color=c["text"], size=11),
            height=220,
            margin=dict(l=50, r=12, t=40, b=40),
            xaxis=dict(title="bin start (cycles)"),
            yaxis=dict(title="fills"),
        )

        lat_cnt = int(latest.get("lat_cnt", 0))
        lat_mean_cy = int(latest.get("lat_sum", 0)) / lat_cnt if lat_cnt else 0.0
        p50, p99 = compute_percentiles(hist)

        scalar = html.Table(
            [
                html.Tr([html.Th("Metric"), html.Th("Value")]),
                html.Tr([html.Td("quotes_rcvd"), html.Td(f"{int(latest.get('qps', 0)):,}")]),
                html.Tr([html.Td("orders_sent"), html.Td(f"{int(latest.get('ops', 0)):,}")]),
                html.Tr([html.Td("fills_rcvd"), html.Td(f"{int(latest.get('fps', 0)):,}")]),
                html.Tr([html.Td("risk_rejects"), html.Td(f"{int(latest.get('rej', 0)):,}")]),
                html.Tr(
                    [
                        html.Td("mean latency"),
                        html.Td(f"{lat_mean_cy * NS_PER_CYCLE:.1f} ns"),
                    ]
                ),
                html.Tr(
                    [
                        html.Td("p50 / p99 (from hist)"),
                        html.Td(f"{p50:.0f} / {p99:.0f} ns"),
                    ]
                ),
            ],
            style={
                "width": "100%",
                "borderCollapse": "collapse",
                "fontSize": "13px",
                "backgroundColor": c["card"],
                "color": c["text"],
            },
        )
        for row in scalar.children[1:]:  # type: ignore[attr-defined]
            for cell in row.children:
                cell.style = {  # type: ignore[attr-defined]
                    "padding": "6px",
                    "borderBottom": f"1px solid {c['grid']}",
                }

        bin_centers_ns = [(i + 0.5) * BIN_WIDTH_NS for i in range(NUM_HIST_BINS)]
        fig_lat = go.Figure(
            go.Bar(
                x=bin_centers_ns,
                y=hist,
                marker_color=c["accent"],
                hovertemplate="~%{x:.0f} ns<br>count=%{y}<extra></extra>",
            )
        )
        fig_lat.update_layout(
            title="Round-trip latency (PL histogram, 32 cycles / bin, 10 ns/cycle)",
            paper_bgcolor=chart_paper,
            plot_bgcolor=chart_plot,
            font=dict(color=c["text"]),
            xaxis=dict(
                title="bin center (ns)",
                showgrid=True,
                gridcolor=c["grid"],
            ),
            yaxis=dict(title="fill count", showgrid=True, gridcolor=c["grid"]),
            margin=dict(l=55, r=25, t=50, b=55),
            annotations=[
                dict(
                    xref="paper",
                    yref="paper",
                    x=0.02,
                    y=0.98,
                    xanchor="left",
                    yanchor="top",
                    showarrow=False,
                    align="left",
                    text=(
                        f"p50 ≈ {p50:.0f} ns · p99 ≈ {p99:.0f} ns<br>"
                        f"min {int(latest.get('lat_min', 0)) * NS_PER_CYCLE} ns · "
                        f"max {int(latest.get('lat_max', 0)) * NS_PER_CYCLE} ns · "
                        f"n={lat_cnt}\n{lat_cap}"
                    ),
                    font=dict(color=c["text"], size=12),
                )
            ],
        )

        pos = latest.get("pos", [0] * NUM_SYMBOLS)
        if not isinstance(pos, list):
            pos = [0] * NUM_SYMBOLS
        while len(pos) < NUM_SYMBOLS:
            pos.append(0)
        names: List[str] = []
        vals: List[int] = []
        for i in sym_filter:
            if 0 <= i < NUM_SYMBOLS:
                names.append(SYMBOL_NAMES[i])
                vals.append(int(pos[i]))
        fig_pos = go.Figure(
            go.Bar(
                y=names,
                x=vals,
                orientation="h",
                marker_color=[c["good"] if v >= 0 else c["bad"] for v in vals],
                hovertemplate="%{y}: %{x} shares<extra></extra>",
            )
        )
        fig_pos.update_layout(
            title="Long = right (green) · Short = left (red) · flat at center",
            paper_bgcolor=chart_paper,
            plot_bgcolor=chart_plot,
            font=dict(color=c["text"], size=12),
            xaxis=dict(
                title="shares (signed)",
                showgrid=True,
                gridcolor=c["grid"],
                zeroline=True,
                zerolinewidth=2,
                zerolinecolor=c["muted"],
            ),
            yaxis=dict(autorange="reversed"),
            margin=dict(l=72, r=24, t=56, b=48),
            height=500,
        )

        return (
            flow,
            pnl_title_style,
            pnl_hero,
            fig_pnl,
            pos_title_style,
            fig_pos,
            fig_thr,
            fig_mini,
            scalar,
            fig_lat,
        )

    @callback(
        Output("regime-modal", "data"),
        Input("btn-regime-learn", "n_clicks"),
        Input("btn-regime-close", "n_clicks"),
        Input("hotkey-store", "data"),
        State("regime-modal", "data"),
    )
    def regime_modal_ctrl(n_learn, n_close, hk, cur):
        cur = cur or {"open": False, "topic": 0}
        ctx = dash.callback_context
        if not ctx.triggered:
            return cur
        tid = ctx.triggered[0]["prop_id"].split(".")[0]
        if tid == "btn-regime-close" and n_close:
            return {"open": False, "topic": int(cur.get("topic", 0))}
        if tid == "btn-regime-learn" and n_learn:
            return {"open": True, "topic": int(cur.get("topic", 0))}
        if tid == "hotkey-store" and isinstance(hk, dict):
            k = hk.get("key")
            if k == "esc":
                return {"open": False, "topic": int(cur.get("topic", 0))}
            if k in ("1", "2", "3", "4"):
                return {"open": True, "topic": int(k) - 1}
        return cur

    @callback(
        Output("regime-modal-overlay", "style"),
        Output("regime-modal-body", "children"),
        Input("regime-modal", "data"),
        Input("prefs-store", "data"),
    )
    def render_regime_modal(m, prefs):
        prefs = prefs or {}
        dark = prefs.get("dark", True)
        c = theme_colors(dark)
        m = m or {"open": False, "topic": 0}
        if not m.get("open"):
            return {"display": "none"}, []
        topic = int(m.get("topic", 0)) % 4
        names = list(REGIME_LABELS)
        rows = []
        for i, nm in enumerate(names):
            bg, blurb = REGIME_INFO[nm]
            hi = i == topic
            rows.append(
                html.Div(
                    [
                        html.Div(
                            nm,
                            className="bb-mono",
                            style={
                                "fontSize": "18px",
                                "fontWeight": "800",
                                "color": bg,
                                "marginBottom": "6px",
                            },
                        ),
                        html.P(
                            blurb,
                            style={
                                "margin": "0",
                                "lineHeight": "1.45",
                                "fontSize": "14px",
                                "color": c["text"],
                            },
                        ),
                    ],
                    style={
                        "padding": "12px 14px",
                        "marginBottom": "10px",
                        "borderRadius": "8px",
                        "border": (
                            f"3px solid {bg}" if hi else f"1px solid {c['grid']}"
                        ),
                        "backgroundColor": c["card"] if not hi else c["bg"],
                    },
                )
            )
        overlay_style = {
            "display": "flex",
            "position": "fixed",
            "top": "0",
            "left": "0",
            "right": "0",
            "bottom": "0",
            "backgroundColor": "rgba(0,0,0,0.55)",
            "zIndex": "9999",
            "justifyContent": "center",
            "alignItems": "flex-start",
            "paddingTop": "8vh",
            "overflowY": "auto",
        }
        body = [
            html.H3(
                "Market regimes (read-only guide)",
                style={"marginTop": "0", "color": c["text"]},
            ),
            html.P(
                "Keys 1–4 highlight a row; Esc closes. Regime on the wire comes from Board A QUOTE frames.",
                style={"fontSize": "13px", "color": c["muted"], "marginBottom": "14px"},
            ),
            *rows,
        ]
        return overlay_style, body

    app.clientside_callback(
        """
        function(n) {
            if (!window.__bb_key_hook) {
                window.__bb_key_hook = 1;
                document.addEventListener('keydown', function(ev) {
                    var t = ev.target && ev.target.tagName;
                    if (t === 'INPUT' || t === 'TEXTAREA' || t === 'SELECT') return;
                    if (ev.key === '1' || ev.key === '2' || ev.key === '3' || ev.key === '4')
                        window.__BOARDB_HOTKEY__ = ev.key;
                    if (ev.key === 'Escape') window.__BOARDB_HOTKEY__ = 'esc';
                });
            }
            var k = window.__BOARDB_HOTKEY__;
            window.__BOARDB_HOTKEY__ = null;
            if (!k) return window.dash_clientside.no_update;
            return {key: k, t: n};
        }
        """,
        Output("hotkey-store", "data"),
        Input("tick", "n_intervals"),
    )

    app.clientside_callback(
        """
        function(n, te, prefs) {
            if (!te || !te.regime_edge) return window.dash_clientside.no_update;
            prefs = prefs || {};
            if (prefs.reduced_motion) return '';
            if (prefs.enable_sound) {
                try {
                    var C = window.AudioContext || window.webkitAudioContext;
                    if (C) {
                        var ctx = new C();
                        var o = ctx.createOscillator();
                        var g = ctx.createGain();
                        o.type = 'triangle';
                        o.frequency.value = 880;
                        g.gain.setValueAtTime(0.032, ctx.currentTime);
                        g.gain.exponentialRampToValueAtTime(0.0001, ctx.currentTime + 0.1);
                        o.connect(g);
                        g.connect(ctx.destination);
                        o.start();
                        o.stop(ctx.currentTime + 0.11);
                    }
                } catch (e) {}
            }
            if (prefs.enable_confetti) {
                var root = document.getElementById('confetti-root');
                if (root) {
                    var colors = ['#238636', '#d29922', '#58a6ff', '#f85149'];
                    for (var i = 0; i < 48; i++) {
                        var p = document.createElement('div');
                        p.className = 'bb-confetti-piece';
                        p.style.left = (Math.random() * 100) + 'vw';
                        p.style.background = colors[i % colors.length];
                        p.style.animationDelay = (Math.random() * 0.12) + 's';
                        root.appendChild(p);
                        (function(node) {
                            setTimeout(function() {
                                try { root.removeChild(node); } catch (e) {}
                            }, 2400);
                        })(p);
                    }
                }
            }
            return '';
        }
        """,
        Output("clientside-fx-tick", "children"),
        Input("tick", "n_intervals"),
        State("telemetry-store", "data"),
        State("prefs-store", "data"),
    )

    return app


def _pill_style(bg: str, c: Dict[str, str]) -> Dict[str, Any]:
    light_text = bg in (c["accent"], c["good"], c["bad"], c["warn"])
    return {
        "backgroundColor": bg,
        "color": "#fff" if light_text else c["text"],
        "padding": "6px 12px",
        "borderRadius": "999px",
        "fontSize": "12px",
        "fontWeight": "600",
    }


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Board B telemetry dashboard")
    p.add_argument(
        "--port",
        default="",
        help="Serial device (e.g. /dev/ttyUSB0, COM5)",
    )
    p.add_argument("--baud", type=int, default=115200)
    p.add_argument(
        "--host",
        default="127.0.0.1",
        help="HTTP bind address (127.0.0.1 = this machine only; 0.0.0.0 = all interfaces).",
    )
    p.add_argument(
        "--dash-port",
        type=int,
        default=8050,
        dest="dash_port",
        help="HTTP port for the dashboard web UI (not the UART serial port).",
    )
    p.add_argument(
        "--browser",
        action="store_true",
        help="Open the dashboard URL in your default web browser after the server starts.",
    )
    p.add_argument(
        "--no-open",
        action="store_true",
        help="Do not open UART serial until you click Connect in the UI.",
    )
    return p.parse_args()


def main() -> None:
    global READER
    import sys

    args = parse_args()
    port = args.port or ("/dev/ttyUSB0" if sys.platform != "win32" else "COM5")
    reader = SerialTelemetryReader(port, args.baud)
    READER = reader
    if not args.no_open:
        reader.open_serial()
    reader.start()

    app = build_app(reader)
    display_host = "127.0.0.1" if args.host in ("0.0.0.0", "::") else args.host
    url = f"http://{display_host}:{args.dash_port}/"
    print(f"Dashboard web UI (open in a browser): {url}")
    if args.host == "0.0.0.0":
        print("  (bound on all interfaces — use this machine's LAN IP from other devices)")
    print(f"UART serial device: {port} @ {args.baud} baud")
    print("Press Ctrl+C in this terminal to stop the server.")

    if args.browser:

        def _open_later() -> None:
            time.sleep(1.25)
            webbrowser.open(url)

        threading.Thread(target=_open_later, daemon=True).start()

    app.run(debug=False, host=args.host, port=args.dash_port)


if __name__ == "__main__":
    main()
