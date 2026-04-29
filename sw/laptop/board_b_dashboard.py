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
# Regime banner colors — Robinhood-adjacent (green / amber / blue / red)
REGIME_INFO: Dict[str, Tuple[str, str]] = {
    "CALM": (
        "#00C805",
        "Quiet synthetic market — smaller moves. Use this when explaining the basics.",
    ),
    "VOLATILE": (
        "#FFB020",
        "Larger random swings — good for showing risk limits and wider spreads.",
    ),
    "BURST": (
        "#5AC8FA",
        "Bursty activity — highlights throughput and how the trader keeps up.",
    ),
    "ADVERSARIAL": (
        "#FF331F",
        "Stress-style conditions — use when discussing halts, rejects, or worst case.",
    ),
}


def _hex_to_rgb(h: str) -> Tuple[int, int, int]:
    h = h.lstrip("#")
    return int(h[0:2], 16), int(h[2:4], 16), int(h[4:6], 16)


def regime_chart_tint(regime_name: str, dark: bool) -> Tuple[str, str]:
    """Plotly paper_bg / plot_bg tint from Board A regime (truthful: same data, visual skin)."""
    name = regime_name.upper() if regime_name else "CALM"
    base = theme_colors(dark)
    if name not in REGIME_INFO:
        # Neutral tint when regime is unavailable (avoid pretending CALM).
        r, g, b = _hex_to_rgb(base["muted"])
        a = 0.10 if dark else 0.16
        tint = f"rgba({r},{g},{b},{a})"
        return base["card"], tint
    r, g, b = _hex_to_rgb(REGIME_INFO[name][0])
    a = 0.14 if dark else 0.20
    tint = f"rgba({r},{g},{b},{a})"
    base = theme_colors(dark)
    return base["card"], tint


def latency_regime_caption(regime_name: str) -> str:
    name = (regime_name or "CALM").upper()
    if name == "UNKNOWN":
        return "Latency regime info unavailable (regime fields missing from telemetry)."
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
    """Robinhood-inspired surfaces (dark-first) + their green/red accent language."""
    if dark:
        return {
            "bg": "#000000",
            "card": "#1c1c1e",
            "text": "#ffffff",
            "muted": "#a1a1a6",
            "accent": "#5ac8fa",
            "good": "#00c805",
            "bad": "#ff331f",
            "warn": "#ffb020",
            "grid": "#2c2c2e",
        }
    return {
        "bg": "#ffffff",
        "card": "#f9f9f9",
        "text": "#000000",
        "muted": "#6b6b6b",
        "accent": "#0066ff",
        "good": "#00c805",
        "bad": "#ff331f",
        "warn": "#ffb020",
        "grid": "#e5e5e5",
    }


FONT_UI = "'DM Sans', 'Segoe UI', system-ui, sans-serif"
FONT_PLOT = "DM Sans, sans-serif"


def _plot_font(c: Dict[str, str], size: Optional[int] = None) -> Dict[str, Any]:
    d: Dict[str, Any] = {"color": c["text"], "family": FONT_PLOT}
    if size is not None:
        d["size"] = size
    return d


def fig_blank(message: str, c: Dict[str, str]) -> go.Figure:
    fig = go.Figure()
    fig.add_annotation(
        text=message,
        xref="paper",
        yref="paper",
        x=0.5,
        y=0.5,
        showarrow=False,
        font=_plot_font(c, 14) | {"color": c["muted"]},
    )
    fig.update_xaxes(visible=False)
    fig.update_yaxes(visible=False)
    fig.update_layout(
        paper_bgcolor=c["card"],
        plot_bgcolor=c["card"],
        font=_plot_font(c),
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
        # "Heartbeat" is a dashboard-side liveness counter (telemetry samples ingested).
        # This is not a PL-internal counter, but it is useful to detect stalls on the link.
        self.heartbeat: int = 0

        # Events are derived in software from telemetry counter deltas and transitions.
        # This avoids requiring any RTL changes.
        self._events: Deque[Dict[str, Any]] = deque(maxlen=100)
        self._last_link_up: Optional[bool] = None
        self._last_risk_halt: Optional[bool] = None
        self._last_state: Optional[str] = None
        self._last_strategy: Optional[str] = None
        self._last_regime_name_evt: Optional[str] = None
        self._last_mmio_err_mono: float = 0.0

        # Heartbeat stall detection (dashboard-side): if reader ingests stop
        # advancing heartbeat across consecutive snapshots, we flag a stall.
        self._last_snapshot_hb: int = 0
        self._stall_snapshot_count: int = 0
        self.hardware_stalled: bool = False

        self._prev_mono: float = 0.0
        self._prev: Dict[str, int] = {}

        self.history_t: Deque[float] = deque(maxlen=8000)
        self.history_cash: Deque[float] = deque(maxlen=8000)
        self.history_pnl: Deque[float] = deque(maxlen=8000)
        self.history_port: Deque[float] = deque(maxlen=8000)
        self.history_rej: Deque[float] = deque(maxlen=8000)
        # Activity over time (derived rates, not cumulative counters).
        self.history_rate_q: Deque[float] = deque(maxlen=8000)
        self.history_rate_o: Deque[float] = deque(maxlen=8000)
        self.history_rate_f: Deque[float] = deque(maxlen=8000)
        self.history_rate_rej: Deque[float] = deque(maxlen=8000)

        self._last_regime_name: str = ""
        self._last_regime_id: int = -1
        self._last_regime_changes: Optional[int] = None
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
                            now_mono = time.monotonic()
                            # Throttle MMIO/parse error events so the log doesn't explode.
                            if now_mono - self._last_mmio_err_mono > 2.0:
                                self._last_mmio_err_mono = now_mono
                                self._events.append(
                                    {
                                        "ts": time.time(),
                                        "type": "MMIO ERROR",
                                        "msg": "Unable to parse telemetry JSON line",
                                    }
                                )
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
            cur_qps = int(data.get("qps", 0) or 0)
            cur_ops = int(data.get("ops", 0) or 0)
            cur_fps = int(data.get("fps", 0) or 0)
            cur_rej = int(data.get("rej", 0) or 0)

            prev_qps = int(self._prev.get("qps", 0) or 0)
            prev_ops = int(self._prev.get("ops", 0) or 0)
            prev_fps = int(self._prev.get("fps", 0) or 0)
            prev_rej = int(self._prev.get("rej", 0) or 0)

            if self._prev_mono > 0:
                dt = now - self._prev_mono
                if dt > 1e-6:
                    # Emit events derived from counter deltas.
                    dq = max(0, cur_qps - prev_qps)
                    do = max(0, cur_ops - prev_ops)
                    df = max(0, cur_fps - prev_fps)
                    dr = max(0, cur_rej - prev_rej)
                    if dq > 0:
                        self._events.append(
                            {"ts": time.time(), "type": "QUOTE RX", "msg": f"+{dq} quotes"}
                        )
                    if do > 0:
                        self._events.append(
                            {"ts": time.time(), "type": "ORDER TX", "msg": f"+{do} orders"}
                        )
                    if df > 0:
                        self._events.append(
                            {"ts": time.time(), "type": "FILL RX", "msg": f"+{df} fills"}
                        )
                    if dr > 0:
                        self._events.append(
                            {"ts": time.time(), "type": "RISK REJECT", "msg": f"+{dr} rejects"}
                        )

                    self.rates["q"] = max(
                        0.0, (cur_qps - prev_qps) / dt
                    )
                    self.rates["o"] = max(
                        0.0, (cur_ops - prev_ops) / dt
                    )
                    self.rates["f"] = max(
                        0.0, (cur_fps - prev_fps) / dt
                    )
                    self.rates["rej"] = max(
                        0.0, (cur_rej - prev_rej) / dt
                    )
            self._prev_mono = now
            self._prev = {
                "qps": cur_qps,
                "ops": cur_ops,
                "fps": cur_fps,
                "rej": cur_rej,
            }
            cash = cash_to_dollars(
                int(data.get("cash_lo", 0)), int(data.get("cash_hi", 0))
            )
            self.history_t.append(now)
            self.history_cash.append(cash)
            # Profit chart inputs.
            self.history_pnl.append(float(data.get("total_pnl", cash) or cash))
            self.history_port.append(float(data.get("port_value", cash) or cash))
            self.history_rej.append(float(self.rates["rej"]))
            # Activity chart inputs (rates, already derived in previous block).
            self.history_rate_q.append(float(self.rates.get("q", 0.0) or 0.0))
            self.history_rate_o.append(float(self.rates.get("o", 0.0) or 0.0))
            self.history_rate_f.append(float(self.rates.get("f", 0.0) or 0.0))
            self.history_rate_rej.append(float(self.rates.get("rej", 0.0) or 0.0))
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
            self.heartbeat += 1

            # Transition events: link/risk/state/strategy/regime.
            link_up_now = bool(data.get("link_up", False))
            risk_halt_now = bool(data.get("risk_halt", False))
            if self._last_link_up is not None and link_up_now != self._last_link_up:
                self._events.append(
                    {
                        "ts": time.time(),
                        "type": "LINK UP" if link_up_now else "LINK DOWN",
                        "msg": "Link state changed",
                    }
                )
            if self._last_risk_halt is not None and risk_halt_now != self._last_risk_halt:
                if risk_halt_now:
                    self._events.append(
                        {"ts": time.time(), "type": "RISK HALT", "msg": "Risk gate halted"}
                    )
            self._last_link_up = link_up_now
            self._last_risk_halt = risk_halt_now

            st_now = data.get("state", None)
            st_str = str(st_now).strip() if st_now is not None else ""
            if self._last_state is not None and st_str and st_str != self._last_state:
                self._events.append(
                    {"ts": time.time(), "type": "FSM CHANGE", "msg": st_str}
                )
            self._last_state = st_str or self._last_state

            strat_now = data.get("strategy", None)
            strat_str = str(strat_now).strip() if strat_now is not None else ""
            if self._last_strategy is not None and strat_str and strat_str != self._last_strategy:
                self._events.append(
                    {"ts": time.time(), "type": "STRATEGY CHANGE", "msg": strat_str}
                )
            self._last_strategy = strat_str or self._last_strategy

            reg_now = data.get("regime_name", None)
            reg_str = str(reg_now).strip().upper() if reg_now is not None else ""
            if self._last_regime_name_evt is not None and reg_str and reg_str != self._last_regime_name_evt:
                self._events.append(
                    {"ts": time.time(), "type": "MARKET REGIME", "msg": reg_str}
                )
            self._last_regime_name_evt = reg_str or self._last_regime_name_evt

            nm = str(data.get("regime_name") or "").strip().upper()
            rid_raw = data.get("regime")
            try:
                rid_i = int(rid_raw) & 3 if rid_raw is not None else -1
            except (TypeError, ValueError):
                rid_i = -1

            # Regime UX edge: prefer optional monotonic regime_changes from JSON (any
            # upstream); else infer from successive regime / regime_name (no FPGA change).
            rc_raw = data.get("regime_changes")
            use_rc = "regime_changes" in data and rc_raw is not None
            if use_rc:
                try:
                    rc = int(rc_raw)
                    if self._last_regime_changes is not None and rc != self._last_regime_changes:
                        self._regime_edge_pending = True
                    self._last_regime_changes = rc
                except (TypeError, ValueError):
                    use_rc = False
            if not use_rc:
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

    def snapshot(
        self,
    ) -> Tuple[Dict[str, Any], Dict[str, float], float, bool, int]:
        with self._lock:
            age_ms = (
                (time.monotonic() - self.last_mono) * 1000 if self.last_mono else 1e9
            )
            # Update stall detection based on whether heartbeat is changing.
            if self.connected and self.last_mono:
                if self.heartbeat == self._last_snapshot_hb and self.heartbeat != 0:
                    self._stall_snapshot_count += 1
                else:
                    self._stall_snapshot_count = 0
                self._last_snapshot_hb = self.heartbeat
                # ~250ms poll interval → 3 snapshots ≈ 0.75s without heartbeat change.
                self.hardware_stalled = self._stall_snapshot_count >= 3
            else:
                self.hardware_stalled = False

            return (
                dict(self.latest),
                dict(self.rates),
                age_ms,
                self.connected,
                self.heartbeat,
            )

    def events_snapshot(self) -> List[Dict[str, Any]]:
        with self._lock:
            return list(self._events)

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

    def history_profit_arrays(
        self, window_sec: float
    ) -> Tuple[List[float], List[float], List[float], List[float]]:
        """Cash + PnL(MTM) + Port value time-series for the profit chart."""
        cutoff = time.monotonic() - window_sec
        t_list: List[float] = []
        cash_list: List[float] = []
        pnl_list: List[float] = []
        port_list: List[float] = []
        with self._lock:
            for t, cash, pnl, port in zip(
                self.history_t, self.history_cash, self.history_pnl, self.history_port
            ):
                if t >= cutoff:
                    t_list.append(t)
                    cash_list.append(cash)
                    pnl_list.append(pnl)
                    port_list.append(port)
        if t_list:
            t0 = t_list[0]
            t_rel = [x - t0 for x in t_list]
        else:
            t_rel = []
        return t_rel, cash_list, pnl_list, port_list

    def history_activity_arrays(
        self, window_sec: float
    ) -> Tuple[List[float], List[float], List[float], List[float], List[float]]:
        """Activity line series (rates) over the last window_sec."""
        cutoff = time.monotonic() - window_sec
        t_list: List[float] = []
        q_list: List[float] = []
        o_list: List[float] = []
        f_list: List[float] = []
        r_list: List[float] = []
        with self._lock:
            for t, q, o, f, r in zip(
                self.history_t,
                self.history_rate_q,
                self.history_rate_o,
                self.history_rate_f,
                self.history_rate_rej,
            ):
                if t >= cutoff:
                    t_list.append(t)
                    q_list.append(q)
                    o_list.append(o)
                    f_list.append(f)
                    r_list.append(r)
        if t_list:
            t0 = t_list[0]
            t_rel = [x - t0 for x in t_list]
        else:
            t_rel = []
        return t_rel, q_list, o_list, f_list, r_list

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
            "https://fonts.googleapis.com/css2?family=DM+Sans:ital,opsz,wght@0,9..40,400;0,9..40,500;0,9..40,600;0,9..40,700;0,9..40,800;1,9..40,400&display=swap",
        ],
    )
    app.title = "Board B"

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
                    "presenter_mode": True,
                    "debug_mode": False,
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
                        placeholder="Serial port (e.g. /dev/cu.usbserial-*)",
                        className="bb-toolbar-input",
                        style={"width": "240px"},
                    ),
                    dcc.Input(
                        id="baud-input",
                        type="number",
                        value=115200,
                        className="bb-toolbar-input bb-toolbar-input--narrow",
                        style={"width": "100px"},
                    ),
                    html.Button("Connect", id="btn-connect", n_clicks=0, className="bb-btn-primary"),
                    html.Button("Pause", id="btn-freeze", n_clicks=0, className="bb-btn-ghost"),
                    html.Button("Resume", id="btn-unfreeze", n_clicks=0, className="bb-btn-ghost"),
                    dcc.Download(id="download-csv"),
                    html.Button(
                        "Export CSV",
                        id="btn-export",
                        n_clicks=0,
                        className="bb-btn-ghost",
                    ),
                ],
                className="bb-toolbar",
            ),
            dcc.Tabs(
                id="main-tabs",
                className="bb-main-tabs",
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
                                                    "Market regime (from telemetry)",
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
                                            "Updates from telemetry fields regime / regime_name. "
                                            "Pulse, sound, and confetti use a one-shot edge when those values "
                                            "change between JSON lines (or when optional regime_changes changes).",
                                            style={"fontSize": "13px", "opacity": 0.85, "marginBottom": "4px"},
                                        ),
                                        html.Div(id="regime-blurb"),
                                    ],
                                    id="regime-strip",
                                ),
                                html.Div(id="flow-strip"),
                                dcc.Tabs(
                                    id="view-tabs",
                                    value="demo",
                                    persistence=True,
                                    children=[
                                        dcc.Tab(
                                            label="Demo View",
                                            value="demo",
                                        ),
                                        dcc.Tab(
                                            label="Debug View",
                                            value="debug",
                                        ),
                                    ],
                                    className="bb-main-tabs",
                                    style={"marginBottom": "6px"},
                                ),
                                html.Div(id="kpi-strip"),
                                html.Div(id="sys-diagram"),
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
                                    "Per-symbol book (quotes + exposure)",
                                    className="bb-section-heading",
                                    style={"marginTop": "18px", "marginBottom": "10px"},
                                ),
                                html.Div(id="symbol-table", style={"width": "100%", "overflowX": "hidden"}),
                                html.H3(
                                    "Activity & throughput",
                                    className="bb-section-heading",
                                    style={
                                        "marginTop": "28px",
                                        "marginBottom": "10px",
                                    },
                                ),
                                dcc.Graph(id="fig-thr", style={"maxWidth": "900px"}),
                                html.H3(
                                    "Latency snapshot",
                                    className="bb-section-heading",
                                    style={
                                        "marginTop": "24px",
                                        "marginBottom": "10px",
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
                                html.Div(
                                    [
                                        html.Div(
                                            [
                                                html.H3(
                                                    "Recent Events",
                                                    className="bb-section-heading",
                                                    style={"marginTop": 0, "marginBottom": "10px"},
                                                ),
                                                html.Div(id="events-panel"),
                                            ],
                                            style={"minWidth": 0},
                                        ),
                                        html.Div(
                                            [
                                                html.H3(
                                                    "Strategy / Risk Diagnostics",
                                                    className="bb-section-heading",
                                                    style={"marginTop": 0, "marginBottom": "10px"},
                                                ),
                                                html.Div(id="diag-panel"),
                                            ],
                                            style={"minWidth": 0},
                                        ),
                                    ],
                                    style={
                                        "display": "grid",
                                        "gridTemplateColumns": "minmax(0, 1fr) minmax(360px, 0.9fr)",
                                        "gap": "16px",
                                        "marginTop": "18px",
                                    },
                                ),
                            ],
                            className="bb-tab-page",
                            style={"padding": "8px 16px 40px", "maxWidth": "1120px", "margin": "0 auto"},
                        ),
                    ),
                    dcc.Tab(
                        label="Latency",
                        value="tab-latency",
                        children=html.Div(
                            dcc.Graph(id="fig-latency", style={"height": "520px"}),
                            className="bb-tab-page",
                            style={"padding": "16px 20px 40px", "maxWidth": "1120px", "margin": "0 auto"},
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
                                            "label": " Enable short chime on regime edge (telemetry)",
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
                                html.Br(),
                                html.Label("Presenter mode (recommended for demos)"),
                                dcc.Checklist(
                                    id="set-presenter",
                                    options=[
                                        {
                                            "label": " Large headline metrics + less debug text",
                                            "value": "p",
                                        }
                                    ],
                                    value=["p"],
                                ),
                                html.Br(),
                                html.Hr(),
                                html.Label("View mode"),
                                dcc.Checklist(
                                    id="set-debug",
                                    options=[
                                        {
                                            "label": " Show raw telemetry diagnostics (Debug View)",
                                            "value": "d",
                                        }
                                    ],
                                    value=[],
                                ),
                                html.P(
                                    "Port and baud are set in the bar above (Connect). "
                                    "Regime display and regime-change effects follow regime / regime_name "
                                    "in each telemetry JSON line (no RTL changes required here). "
                                    "This dashboard does not write FPGA parameters.",
                                    style={"maxWidth": "640px", "opacity": 0.85},
                                ),
                            ],
                            className="bb-tab-page",
                            style={"padding": "16px 20px 48px", "maxWidth": "720px", "margin": "0 auto"},
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
        className="bb-root bb-root--dark",
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
        Input("set-presenter", "value"),
        Input("set-debug", "value"),
        State("prefs-store", "data"),
    )
    def on_prefs(dark, hist_sec, syms, show_q, sound, confetti, reduced, presenter, debug, cur):
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
        if presenter is not None:
            out["presenter_mode"] = bool("p" in presenter)
        if debug is not None:
            out["debug_mode"] = bool("d" in debug)
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
        presenter = prefs.get("presenter_mode", True)
        reduced = prefs.get("reduced_motion", False)
        c = theme_colors(dark)
        latest = telem.get("latest") or {}
        regime_name_raw = latest.get("regime_name", None)
        name = "UNKNOWN"
        if regime_name_raw is not None:
            rn = str(regime_name_raw).strip().upper()
            if rn and rn != "?" and rn in REGIME_INFO:
                name = rn
        if name == "UNKNOWN" and latest.get("regime", None) is not None:
            try:
                rid = int(latest.get("regime", 0)) & 3
                if 0 <= rid < len(REGIME_LABELS):
                    name = REGIME_LABELS[rid]
            except (TypeError, ValueError):
                name = "UNKNOWN"
        if name in REGIME_INFO:
            bg, blurb = REGIME_INFO[name]
        else:
            bg = c["grid"]
            blurb = "Market regime diagnostics unavailable — regime_name/regime fields missing from telemetry."
        edge = bool(telem.get("regime_edge"))
        pulse_cls = "" if reduced else (" bb-regime-pulse" if edge else "")

        inner: List[Any] = [
            html.Div(
                [
                    html.Span(
                        name.replace("_", " "),
                        className="bb-regime-title",
                    ),
                    html.Span(
                        " · id=UNKNOWN" if latest.get("regime", None) is None else f" · id={int(latest.get('regime', 0)) & 3}",
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
        ]
        if not presenter:
            inner.append(
                html.Div(
                    "Source: JSON lines may include regime and regime_name (however your pipeline "
                    "fills them). Edges for motion and optional chime/confetti come from successive "
                    "samples, or from regime_changes if your publisher adds that counter.",
                    style={
                        "marginTop": "12px",
                        "fontSize": "12px",
                        "opacity": 0.88,
                        "fontFamily": FONT_UI,
                        "fontVariantNumeric": "tabular-nums",
                    },
                )
            )
        children = html.Div(
            inner,
            className="bb-regime-inner" + pulse_cls,
            style={
                "marginTop": "14px",
                "padding": "24px 26px",
                "borderRadius": "20px",
                "backgroundColor": bg,
                "color": "#fff",
                "boxShadow": "0 8px 32px rgba(0,0,0,0.35)",
            },
        )
        strip_style = {
            "padding": "8px 4px 0",
            "marginBottom": "12px",
            "borderRadius": "0",
            "border": "none",
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
        latest, rates, age_ms, connected, heartbeat = reader.snapshot()
        return {
            "latest": latest,
            "rates": rates,
            "age_ms": age_ms,
            "connected": connected,
            "heartbeat": heartbeat,
            "hardware_stalled": reader.hardware_stalled,
            "parse_errors": reader.parse_errors,
            "regime_edge": regime_edge,
            "events": reader.events_snapshot(),
            "ts": time.time(),
        }

    def _active_data(telem: Dict[str, Any], freeze: Dict[str, Any]) -> Dict[str, Any]:
        if freeze and freeze.get("active") and freeze.get("payload"):
            return freeze["payload"]
        return telem

    @callback(
        Output("header-bar", "children"),
        Output("root", "style"),
        Output("root", "className"),
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
        presenter = prefs.get("presenter_mode", True)
        c = theme_colors(dark)
        latest = telem.get("latest") or {}
        age_ms = float(telem.get("age_ms", 1e9))
        heartbeat = telem.get("heartbeat", 0)
        connected = telem.get("connected", False)
        hardware_stalled = bool(telem.get("hardware_stalled", False))
        stale = (age_ms > STALE_MS) and not paused

        rates = telem.get("rates") or {}

        def _clean(v: Any, fallback: str = "UNKNOWN") -> str:
            s = "" if v is None else str(v).strip()
            if not s or s in ("?", "—", "-", "null", "None"):
                return fallback
            return s

        raw_link_up = bool(latest.get("link_up", False))
        raw_risk_halt = bool(latest.get("risk_halt", False))
        raw_state = latest.get("state", None)
        raw_strategy = latest.get("strategy", None)

        # FSM STATE label (explicit fallback; no '?')
        fsm_state = _clean(raw_state)
        if fsm_state.startswith("B_"):
            fsm_short = fsm_state[2:]
            if fsm_short in ("RESET", "IDLE", "ARMED"):
                fsm_state = "RESET" if fsm_short == "RESET" else "IDLE" if fsm_short == "IDLE" else "RUNNING"
            elif fsm_short == "TRADING":
                fsm_state = "RUNNING"
            elif fsm_short == "HALTED":
                fsm_state = "STOPPED"
        if fsm_state in ("UNKNOWN", "—", "?"):
            fsm_state = "UNKNOWN"

        # STRATEGY label (explicit fallback; no '?')
        strat_raw = _clean(raw_strategy)
        if fsm_state != "RUNNING":
            strat = "IDLE"
        else:
            strat_map = {
                "MEAN_REV": "MEAN REVERSION",
                "MOMENTUM": "MOMENTUM",
                "NN": "ML",
                "AUTO": "SAFE",
            }
            strat = strat_map.get(strat_raw, "UNKNOWN")

        # MARKET REGIME label (explicit fallback; do not assume CALM when missing)
        regime_name_raw = latest.get("regime_name", None)
        regime_show = "UNKNOWN"
        rn = str(regime_name_raw).strip().upper() if regime_name_raw is not None else ""
        if rn and rn != "?" and rn in REGIME_INFO:
            regime_show = rn
        else:
            if "regime" in latest and latest.get("regime", None) is not None:
                try:
                    rid = int(latest.get("regime", 0)) & 3
                    regime_show = REGIME_LABELS[rid]
                except (TypeError, ValueError):
                    regime_show = "UNKNOWN"

        # RISK STATE label
        risk_halt = raw_risk_halt
        rej_rate = float(rates.get("rej", 0.0) or 0.0)
        if risk_halt:
            risk_state = "HALTED"
            risk_tone = c["bad"]
        elif rej_rate > 0:
            risk_state = "REJECTING"
            risk_tone = c["warn"]
        else:
            risk_state = "OK"
            risk_tone = c["good"]

        link_up = raw_link_up
        link_err = int(latest.get("link_err", 0) or 0)
        pe = int(telem.get("parse_errors", 0) or 0)

        qps = int(latest.get("qps", 0) or 0)
        ops = int(latest.get("ops", 0) or 0)
        fps = int(latest.get("fps", 0) or 0)
        has_quotes = (qps > 0) or (float(rates.get("q", 0.0) or 0.0) > 0.0)
        has_orders = (ops > 0) or (float(rates.get("o", 0.0) or 0.0) > 0.0)
        has_fills = (fps > 0) or (float(rates.get("f", 0.0) or 0.0) > 0.0)

        axi_ok = connected and (not stale) and pe == 0
        telemetry_mode = "LIVE" if (connected and not stale) else ("STALE" if connected else "DISCONNECTED")

        root_style = {
            "minHeight": "100vh",
            "backgroundColor": c["bg"],
            "color": c["text"],
            "fontFamily": FONT_UI,
        }

        _banner_base = {
            "padding": "12px 20px",
            "fontWeight": "600",
            "fontSize": "14px",
            "letterSpacing": "0.01em",
            "borderRadius": "12px",
            "margin": "12px 16px 0",
            "maxWidth": "1200px",
        }

        if paused:
            status_text = "BOARD B STATUS: PAUSED — charts frozen"
            status_tone = c["muted"]
            hint = "Serial may still run in the background."
        elif not connected:
            status_text = "BOARD B STATUS: MMIO ERROR — Unable to read telemetry registers"
            status_tone = c["bad"]
            hint = "No telemetry is arriving. Check serial link and board-side server."
        elif hardware_stalled:
            status_text = "BOARD B STATUS: HARDWARE STALLED — Telemetry heartbeat not incrementing"
            status_tone = c["bad"]
            hint = "Telemetry ingest heartbeat stopped changing while link state is not stale."
        elif stale:
            status_text = "BOARD B STATUS: HARDWARE STALLED — Telemetry updates are stale"
            status_tone = c["bad"]
            hint = f"Last telemetry update was {age_ms:.0f} ms ago."
        else:
            if not link_up:
                status_text = "BOARD B STATUS: LINK DOWN — No quotes received from Board A"
                status_tone = c["bad"]
                hint = "Board B is alive, but the RX link is not delivering quotes."
            elif not has_quotes:
                status_text = "BOARD B STATUS: WAITING — Hardware alive, links OK, but no quotes yet"
                status_tone = c["warn"]
                hint = "Try starting Board A and verify link mapping/PMOD wiring."
            elif risk_halt:
                status_text = "BOARD B STATUS: RISK HALTED — Orders blocked"
                status_tone = c["bad"]
                hint = f"Risk rejects: {int(latest.get('rej', 0) or 0):,}."
            elif has_quotes and has_orders:
                status_text = "BOARD B STATUS: LIVE — Receiving quotes and sending orders"
                status_tone = c["good"]
                hint = "Traffic is flowing through the pipeline."
            elif has_quotes and not has_orders:
                status_text = "BOARD B STATUS: WAITING — Quotes flowing, but no orders sent"
                status_tone = c["warn"]
                hint = "Check strategy activation and risk thresholds."
            else:
                status_text = "BOARD B STATUS: UNKNOWN"
                status_tone = c["warn"]
                hint = "Telemetry is present but state is ambiguous."

        # Meta strip (right-aligned on the same header row)
        meta_strip = html.Div(
            [
                html.Span(f"Last telemetry update: {age_ms:.0f} ms ago", style={"color": c["muted"]}),
                html.Span(" · ", style={"color": c["muted"]}),
                html.Span(f"Telemetry heartbeat: {int(heartbeat):08d}", style={"color": c["text"]}),
                html.Span(" · ", style={"color": c["muted"]}),
                html.Span(f"AXI/MMIO: {'OK' if axi_ok else 'ERROR'}", style={"color": c["good"] if axi_ok else c["bad"]}),
                html.Span(" · ", style={"color": c["muted"]}),
                html.Span(f"Telemetry: {telemetry_mode}", style={"color": c["warn"] if telemetry_mode != 'LIVE' else c["good"]}),
            ],
            style={
                "fontSize": "12px",
                "fontWeight": "600",
                "letterSpacing": "0.01em",
                "whiteSpace": "nowrap",
            },
        )

        banner = html.Div(
            [
                html.Div(
                    [
                        html.Span(
                            status_text,
                            style={
                                "color": status_tone,
                                "fontWeight": "900",
                                "fontSize": "16px",
                                "letterSpacing": "0.01em",
                            },
                        ),
                        html.Div(
                            hint,
                            style={
                                "color": c["muted"],
                                "fontSize": "12px",
                                "marginTop": "6px",
                                "fontWeight": "500",
                                "lineHeight": "1.4",
                            },
                        ),
                    ],
                    style={"flex": "1 1 auto", "minWidth": 0},
                ),
                html.Div(meta_strip, style={"flex": "0 0 auto", "marginLeft": "18px"}),
            ],
            style={
                **_banner_base,
                "backgroundColor": c["card"],
                "border": f"1px solid {c['grid']}",
                "display": "flex",
                "alignItems": "flex-start",
                "justifyContent": "space-between",
                "gap": "14px",
                "maxWidth": "1200px",
                "marginLeft": "auto",
                "marginRight": "auto",
            },
        )

        title = html.Div(
            "Board B — Trader Telemetry",
            style={
                "fontSize": "22px",
                "fontWeight": "900",
                "letterSpacing": "-0.01em",
                "margin": "14px 0 6px",
                "maxWidth": "1200px",
                "marginLeft": "auto",
                "marginRight": "auto",
            },
        )
        root_cls = "bb-root bb-root--dark" if dark else "bb-root bb-root--light"
        if presenter:
            root_cls += " bb-presenter"
        return html.Div([title, banner]), root_style, root_cls

    @callback(
        Output("flow-strip", "children"),
        Output("kpi-strip", "children"),
        Output("pnl-section-title", "style"),
        Output("pnl-hero", "children"),
        Output("fig-pnl", "figure"),
        Output("pos-section-title", "style"),
        Output("fig-positions", "figure"),
        Output("fig-thr", "figure"),
        Output("fig-mini-hist", "figure"),
        Output("scalar-table", "children"),
        Output("fig-latency", "figure"),
        Output("events-panel", "children"),
        Output("diag-panel", "children"),
        Output("symbol-table", "children"),
        Output("sys-diagram", "children"),
        Input("telemetry-store", "data"),
        Input("prefs-store", "data"),
        Input("view-tabs", "value"),
        State("freeze-store", "data"),
    )
    def render_figures(telem, prefs, view_tab, freeze):
        telem = _active_data(telem or {}, freeze or {})
        prefs = prefs or {}
        dark = prefs.get("dark", True)
        presenter = prefs.get("presenter_mode", True)
        debug_mode = prefs.get("debug_mode", False)
        effective_debug = bool(debug_mode) or (view_tab == "debug")
        hist_sec = float(prefs.get("history_sec", DEFAULT_HISTORY_SEC))
        sym_filter = prefs.get("symbols", list(range(NUM_SYMBOLS)))
        show_quotes = prefs.get("show_quotes_bar", True)
        c = theme_colors(dark)

        latest = telem.get("latest") or {}
        rates = telem.get("rates") or {}

        regime_name_raw = latest.get("regime_name", None)
        regime_lbl_for_charts = "UNKNOWN"
        if regime_name_raw is not None:
            rn = str(regime_name_raw).strip().upper()
            if rn and rn != "?" and rn in REGIME_INFO:
                regime_lbl_for_charts = rn
        if regime_lbl_for_charts == "UNKNOWN" and latest.get("regime", None) is not None:
            try:
                rid = int(latest.get("regime", 0)) & 3
                regime_lbl_for_charts = REGIME_LABELS[rid]
            except (TypeError, ValueError, IndexError):
                regime_lbl_for_charts = "UNKNOWN"

        chart_paper, chart_plot = regime_chart_tint(regime_lbl_for_charts, dark)
        lat_cap = latency_regime_caption(regime_lbl_for_charts)

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
            "marginTop": "20px",
            "marginBottom": "6px",
            "fontSize": "13px",
            "fontWeight": "600",
            "letterSpacing": "0.06em",
            "textTransform": "uppercase",
            "color": c["muted"],
        }
        pos_title_style = {
            "marginTop": "32px",
            "marginBottom": "6px",
            "fontSize": "13px",
            "fontWeight": "600",
            "letterSpacing": "0.06em",
            "textTransform": "uppercase",
            "color": c["muted"],
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
                    "Narrative flow — market data to risk-checked execution",
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
                "padding": "18px 20px",
                "borderRadius": "16px",
                "marginBottom": "16px",
                "border": f"1px solid {c['grid']}",
            },
        )

        def _kpi_card(
            label: str,
            value: str,
            tone: str,
            sub: str = "",
            tooltip: str = "",
            clickable: bool = False,
        ) -> html.Div:
            return html.Div(
                [
                    html.Div(
                        label,
                        style={
                            "fontSize": "11px",
                            "fontWeight": "700",
                            "letterSpacing": "0.08em",
                            "textTransform": "uppercase",
                            "color": c["muted"],
                        },
                    ),
                    html.Div(
                        value,
                        className="bb-mono",
                        style={
                            "fontSize": "26px",
                            "fontWeight": "800",
                            "lineHeight": "1.15",
                            "marginTop": "4px",
                            "color": tone,
                        },
                    ),
                    html.Div(
                        sub,
                        style={
                            "fontSize": "12px",
                            "marginTop": "6px",
                            "color": c["muted"],
                            "minHeight": "18px",
                        },
                    ),
                ],
                style={
                    "flex": "1 1 180px",
                    "minWidth": "170px",
                    "padding": "14px 16px",
                    "borderRadius": "14px",
                    "backgroundColor": c["card"],
                    "border": f"1px solid {c['grid']}",
                    "cursor": "pointer" if clickable else "default",
                    "transition": "box-shadow 0.15s ease, border-color 0.15s ease",
                },
                title=tooltip or None,
                className="bb-kpi-card" if clickable else None,
            )

        def _label_unknown(v: Any) -> str:
            s = "" if v is None else str(v).strip()
            if not s or s in ("?", "—", "-", "null", "None"):
                return "UNKNOWN"
            return s

        def _fsm_label(raw_state: Any) -> str:
            s = _label_unknown(raw_state)
            m = {
                "B_RESET": "RESET",
                "B_IDLE": "IDLE",
                "B_ARMED": "RUNNING",
                "B_TRADING": "RUNNING",
                "B_HALTED": "STOPPED",
            }
            return m.get(s, "UNKNOWN" if s == "UNKNOWN" else s.replace("B_", ""))  # never returns '?'

        def _strategy_label(raw_strategy: Any, fsm_lbl: str) -> str:
            if fsm_lbl not in ("RUNNING",):
                return "IDLE"
            s = _label_unknown(raw_strategy)
            return {
                "MEAN_REV": "MEAN REVERSION",
                "MOMENTUM": "MOMENTUM",
                "NN": "ML",
                "AUTO": "SAFE",
                "MEAN_REVERSION": "MEAN REVERSION",
                "ML": "ML",
                "SAFE": "SAFE",
            }.get(s, "UNKNOWN")

        def _regime_label(latest_obj: Dict[str, Any]) -> str:
            rn_raw = latest_obj.get("regime_name", None)
            if rn_raw is not None:
                rn = _label_unknown(rn_raw).upper()
                if rn in REGIME_INFO:
                    return rn
            if latest_obj.get("regime", None) is not None:
                try:
                    rid = int(latest_obj.get("regime", 0)) & 3
                    if 0 <= rid < len(REGIME_LABELS):
                        return REGIME_LABELS[rid]
                except (TypeError, ValueError):
                    pass
            return "UNKNOWN"

        def _risk_label(risk_halt_flag: bool, rej_rate_value: float) -> str:
            if risk_halt_flag:
                return "HALTED"
            # If risk gate is not halted but we are rejecting, call it REJECTING.
            if rej_rate_value > 0.0:
                return "REJECTING"
            return "OK"

        raw_state = latest.get("state", None)
        fsm_lbl = _fsm_label(raw_state)
        strat_lbl = _strategy_label(latest.get("strategy", None), fsm_lbl)

        link_up = bool(latest.get("link_up", False))
        risk_halt = bool(latest.get("risk_halt", False))
        rej_rate = float(rates.get("rej", 0.0) or 0.0)

        regime_lbl = _regime_label(latest)
        risk_lbl = _risk_label(risk_halt, rej_rate)

        parse_err = int(telem.get("parse_errors", 0) or 0)
        qps = int(latest.get("qps", 0) or 0)
        ops = int(latest.get("ops", 0) or 0)
        fps = int(latest.get("fps", 0) or 0)
        rej = int(latest.get("rej", 0) or 0)

        total_pnl = float(latest.get("total_pnl", 0.0) or 0.0)
        port_value = float(latest.get("port_value", 0.0) or 0.0)
        cash_val = float(latest.get("cash", 0.0) or 0.0)

        system_row = html.Div(
            [
                _kpi_card(
                    "LINK STATUS",
                    "UP" if link_up else "DOWN",
                    c["good"] if link_up else c["bad"],
                    "Board-to-board RX",
                    tooltip=(
                        "Board B is receiving quotes from Board A."
                        if link_up
                        else "Board B is alive, but no quotes are arriving from Board A."
                    ),
                    clickable=True,
                ),
                _kpi_card(
                    "FSM STATE",
                    fsm_lbl,
                    c["accent"] if fsm_lbl in ("RUNNING", "RESET") else c["muted"],
                    "Board B control flow",
                ),
                _kpi_card(
                    "STRATEGY",
                    strat_lbl,
                    c["accent"] if strat_lbl not in ("IDLE", "UNKNOWN") else c["muted"],
                    "ML / rules layer",
                ),
                _kpi_card(
                    "MARKET REGIME",
                    regime_lbl,
                    c["accent"] if regime_lbl != "UNKNOWN" else c["muted"],
                    "Telemetry-derived",
                ),
                _kpi_card(
                    "RISK STATE",
                    risk_lbl,
                    c["bad"] if risk_lbl in ("HALTED", "REJECTING") else c["good"],
                    ("" if presenter else f"Rej counter: {rej:,}"),
                    tooltip=(
                        "Orders may be blocked because risk limits are being enforced."
                        if risk_halt or risk_lbl in ("REJECTING", "HALTED")
                        else "Risk limits are OK; orders are allowed to flow."
                    ),
                    clickable=True,
                ),
            ],
            style={"display": "flex", "flexWrap": "wrap", "gap": "10px", "marginBottom": "10px"},
        )

        perf_row = html.Div(
            [
                _kpi_card("CASH", f"${cash_val:,.2f}", c["good"] if cash_val >= 0 else c["bad"], "Board B realized"),
                _kpi_card(
                    "TOTAL PNL",
                    f"${total_pnl:+,.2f}",
                    c["good"] if total_pnl >= 0 else c["bad"],
                    "MTM aggregate",
                ),
                _kpi_card("PORT VALUE", f"${port_value:,.2f}", c["accent"], "Cash + Σ pos·mid"),
                _kpi_card("QUOTES RX", f"{qps:,}", c["muted"], "Board A → B"),
                _kpi_card("ORDERS TX", f"{ops:,}", c["muted"], "B → Board A"),
                _kpi_card("FILLS RX", f"{fps:,}", c["muted"], "Execution results"),
                _kpi_card("RISK REJECTS", f"{rej:,}", c["bad"] if rej > 0 else c["muted"], "Gate pressure"),
            ],
            style={"display": "flex", "flexWrap": "wrap", "gap": "10px"},
        )

        kpis = html.Div([system_row, perf_row], style={"marginBottom": "18px"})

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
                                        "fontSize": "64px" if presenter else "52px",
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
                                        "fontSize": "42px" if presenter else "36px",
                                        "fontWeight": "800",
                                        "color": delta_color,
                                        "marginTop": "6px",
                                    },
                                ),
                                html.Div(
                                    "Session delta since dashboard start",
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
                        "padding": "28px 28px",
                        "borderRadius": "20px",
                        "backgroundColor": c["card"],
                        "border": f"1px solid {c['grid']}",
                    },
                ),
                html.Div(
                    (
                        "Realized P&L from hardware fills. Exposure below shows current inventory by symbol."
                        if presenter
                        else "This is realized P&L from fills (Q32.16), not full mark-to-market unless you add price feeds. "
                        "Positions below show how many shares the engine holds per symbol."
                    ),
                    style={
                        "marginTop": "12px",
                        "fontSize": "16px" if presenter else "14px",
                        "lineHeight": "1.45",
                        "color": c["muted"],
                        "maxWidth": "960px",
                    },
                ),
            ]
        )

        t_rel, cash_h, pnl_h, port_h = reader.history_profit_arrays(hist_sec)
        if freeze and freeze.get("active"):
            t_rel = [0.0]
            cash_h = [cash]
            pnl_h = [float(latest.get("total_pnl", 0.0) or 0.0)]
            port_h = [float(latest.get("port_value", 0.0) or 0.0)]

        fig_pnl = go.Figure()
        if len(t_rel) > 0:
            if len(cash_h) == 0:
                cash_h = [0.0]
            if len(pnl_h) == 0:
                pnl_h = [0.0]
            if len(port_h) == 0:
                port_h = [0.0]

            any_movement = (
                (max(abs(float(x) or 0.0) for x in cash_h) > 1e-6)
                or (max(abs(float(x) or 0.0) for x in pnl_h) > 1e-6)
                or (max(abs(float(x) or 0.0) for x in port_h) > 1e-6)
            )

            if not any_movement:
                fig_pnl = fig_blank(
                    "Waiting for trading data...<br>No cash, P&L, or portfolio movement has been observed yet.",
                    c,
                )
            else:
                line_mode = "lines" if len(t_rel) > 1 else "markers"
                fig_pnl.add_trace(
                    go.Scatter(
                        x=t_rel,
                        y=cash_h,
                        mode=line_mode,
                        line=dict(color=c["good"], width=2.5),
                        marker=dict(size=10, color=c["good"]),
                        name="Cash",
                        hovertemplate="t=%{x:.2f}s<br>Cash=$%{y:.2f}<extra></extra>",
                    )
                )
                fig_pnl.add_trace(
                    go.Scatter(
                        x=t_rel,
                        y=pnl_h,
                        mode=line_mode,
                        line=dict(color=c["accent"], width=2.2),
                        marker=dict(size=10, color=c["accent"]),
                        name="Total PnL MTM",
                        hovertemplate="t=%{x:.2f}s<br>Total PnL=$%{y:.2f}<extra></extra>",
                    )
                )
                fig_pnl.add_trace(
                    go.Scatter(
                        x=t_rel,
                        y=port_h,
                        mode=line_mode,
                        line=dict(color=c["warn"], width=2.2),
                        marker=dict(size=10, color=c["warn"]),
                        name="Port Value",
                        hovertemplate="t=%{x:.2f}s<br>Port=$%{y:.2f}<extra></extra>",
                    )
                )
        else:
            fig_pnl = fig_blank(
                "Waiting for trading data...<br>No cash, P&L, or portfolio movement has been observed yet.",
                c,
            )
        fig_pnl.update_layout(
            title=dict(
                text="Profit & Portfolio",
                font=_plot_font(c, 13),
            ),
            paper_bgcolor=chart_paper,
            plot_bgcolor=chart_plot,
            font=_plot_font(c),
            height=300,
            margin=dict(l=50, r=20, t=44, b=44),
            xaxis=dict(
                showgrid=True,
                gridcolor=c["grid"],
                title="window (s)",
                zeroline=False,
            ),
            yaxis=dict(showgrid=True, gridcolor=c["grid"], title="USD", zeroline=False),
        )

        # Activity over time: derived rates (quotes/orders/fills/rejects).
        qps_i = int(latest.get("qps", 0) or 0)
        ops_i = int(latest.get("ops", 0) or 0)
        fps_i = int(latest.get("fps", 0) or 0)
        has_any_traffic_now = (qps_i > 0) or (ops_i > 0) or (fps_i > 0)

        t_act, q_h, o_h, f_h, r_h = reader.history_activity_arrays(hist_sec)
        if (not t_act) or (not has_any_traffic_now) or (
            max(q_h + o_h + f_h + r_h) if (q_h or o_h or f_h or r_h) else 0.0
        ) <= 1e-12:
            fig_thr = fig_blank("No traffic yet.<br>Check Board A is running, PMOD cables are connected, and link status is UP.", c)
        else:
            fig_thr = go.Figure()
            if show_quotes:
                fig_thr.add_trace(
                    go.Scatter(
                        x=t_act,
                        y=q_h,
                        mode="lines",
                        line=dict(color=c["muted"], width=2.2),
                        name="quotes/sec",
                        hovertemplate="t=%{x:.2f}s<br>quotes/sec=%{y:.1f}<extra></extra>",
                    )
                )
            fig_thr.add_trace(
                go.Scatter(
                    x=t_act,
                    y=o_h,
                    mode="lines",
                    line=dict(color=c["accent"], width=2.2),
                    name="orders/sec",
                    hovertemplate="t=%{x:.2f}s<br>orders/sec=%{y:.1f}<extra></extra>",
                )
            )
            fig_thr.add_trace(
                go.Scatter(
                    x=t_act,
                    y=f_h,
                    mode="lines",
                    line=dict(color=c["good"], width=2.2),
                    name="fills/sec",
                    hovertemplate="t=%{x:.2f}s<br>fills/sec=%{y:.1f}<extra></extra>",
                )
            )
            fig_thr.add_trace(
                go.Scatter(
                    x=t_act,
                    y=r_h,
                    mode="lines",
                    line=dict(color=c["bad"], width=2.2),
                    name="risk rejects/sec",
                    hovertemplate="t=%{x:.2f}s<br>risk rejects/sec=%{y:.1f}<extra></extra>",
                )
            )
            fig_thr.update_layout(
                title=dict(text="Traffic Activity", font=_plot_font(c, 13)),
                paper_bgcolor=chart_paper,
                plot_bgcolor=chart_plot,
                font=_plot_font(c),
                height=240,
                margin=dict(l=55, r=20, t=40, b=40),
                xaxis=dict(showgrid=True, gridcolor=c["grid"], title="window (s)"),
                yaxis=dict(showgrid=True, gridcolor=c["grid"], title="rate per second"),
                legend=dict(orientation="h", yanchor="bottom", y=1.02, xanchor="left", x=0),
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
            title=dict(text="Latency histogram", font=_plot_font(c, 13)),
            paper_bgcolor=chart_paper,
            plot_bgcolor=chart_plot,
            font=_plot_font(c, 11),
            height=240,
            margin=dict(l=50, r=12, t=40, b=40),
            xaxis=dict(title="bin start (cycles)"),
            yaxis=dict(title="fills"),
        )

        lat_cnt = int(latest.get("lat_cnt", 0) or 0)
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
            title=dict(
                text="Round-trip latency",
                font=_plot_font(c, 13),
            ),
            paper_bgcolor=chart_paper,
            plot_bgcolor=chart_plot,
            font=_plot_font(c),
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
                    font=_plot_font(c, 12),
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
        # Empty-state behavior: if we have no quotes yet, show a clear message.
        qps_i = int(latest.get("qps", 0) or 0)
        ops_i = int(latest.get("ops", 0) or 0)
        fps_i = int(latest.get("fps", 0) or 0)
        has_any_traffic = (qps_i > 0) or (ops_i > 0) or (fps_i > 0)

        if not has_any_traffic:
            fig_pos = fig_blank("Waiting for quotes from Board A…", c)
        else:
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
                title=dict(text="Positions", font=_plot_font(c, 13)),
                paper_bgcolor=chart_paper,
                plot_bgcolor=chart_plot,
                font=_plot_font(c, 12),
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

        # Empty-state overlays for throughput and latency
        if not has_any_traffic:
            fig_thr = fig_blank("No traffic yet.<br>Check that Board A is running.", c)
            fig_mini = fig_blank("No fills received yet…", c)
            fig_lat = fig_blank("No fills received yet…", c)
        else:
            # Quotes/orders can exist without fills; explain the specific reason latency is empty.
            if fps_i <= 0:
                fig_mini = fig_blank("No fills received yet…", c)
                fig_lat = fig_blank(
                    "No fills received yet.<br>Latency data will appear after orders are filled.",
                    c,
                )

        # ── Events + diagnostics (Priority 2) ─────────────────────────────
        events = telem.get("events") or []

        def _fmt_time_ms(t: Any) -> str:
            try:
                tf = float(t)
            except (TypeError, ValueError):
                return "--:--:--.---"
            lt = time.localtime(tf)
            ms = int((tf - int(tf)) * 1000.0)
            return f"{lt.tm_hour:02d}:{lt.tm_min:02d}:{lt.tm_sec:02d}.{ms:03d}"

        def _event_color(ev_type: str) -> str:
            if ev_type in ("FILL RX", "LINK UP"):
                return c["good"]
            if ev_type in ("QUOTE RX", "ORDER TX", "FSM CHANGE", "STRATEGY CHANGE", "MARKET REGIME"):
                return c["accent"]
            if ev_type in ("RISK HALT", "LINK DOWN", "MMIO ERROR"):
                return c["bad"]
            if ev_type in ("RISK REJECT",):
                return c["warn"]
            return c["muted"]

        if not events:
            events_panel = html.Div(
                "No events yet. Waiting for hardware activity.",
                style={"color": c["muted"], "fontSize": "13px", "lineHeight": "1.5"},
            )
        else:
            # Newest first.
            evs = list(events)[::-1][:60]
            rows = []
            for ev in evs:
                ev_type = str(ev.get("type") or "UNKNOWN")
                msg = str(ev.get("msg") or "")
                rows.append(
                    html.Div(
                        [
                            html.Span(
                                _fmt_time_ms(ev.get("ts")),
                                className="bb-mono",
                                style={"color": c["muted"], "fontSize": "12px", "minWidth": "108px"},
                            ),
                            html.Span(
                                ev_type,
                                style={
                                    "color": _event_color(ev_type),
                                    "fontWeight": "900",
                                    "fontSize": "12px",
                                    "letterSpacing": "0.01em",
                                },
                            ),
                            html.Span(msg, style={"color": c["text"], "fontSize": "12px", "opacity": 0.95}),
                        ],
                        style={"display": "flex", "gap": "10px", "flexWrap": "wrap", "padding": "6px 0"},
                    )
                )
            events_panel = html.Div(
                rows,
                style={
                    "borderRadius": "14px",
                    "padding": "12px 14px",
                    "border": f"1px solid {c['grid']}",
                    "backgroundColor": c["card"],
                    "maxHeight": "320px",
                    "overflowY": "auto",
                },
            )

        # Strategy / Risk diagnostics (derived, not raw buy/sell)
        pos = latest.get("pos", [0] * NUM_SYMBOLS)
        if not isinstance(pos, list):
            pos = [0] * NUM_SYMBOLS
        exposure = sum(abs(int(x) if x is not None else 0) for x in pos[:NUM_SYMBOLS])
        symbol_idx = None
        for i in range(min(NUM_SYMBOLS, len(pos))):
            try:
                if int(pos[i]) != 0:
                    symbol_idx = i
                    break
            except (TypeError, ValueError):
                continue
        selected_symbol = SYMBOL_NAMES[symbol_idx] if symbol_idx is not None else "UNKNOWN"

        decision = "UNKNOWN"
        reason = "Telemetry is present but decision logic cannot be derived."
        conf = 0.2
        qps_i = int(latest.get("qps", 0) or 0)
        ops_i = int(latest.get("ops", 0) or 0)
        fps_i = int(latest.get("fps", 0) or 0)
        has_quotes = qps_i > 0
        has_orders = ops_i > 0
        has_fills = fps_i > 0

        if risk_halt:
            decision = "HOLD (risk halted)"
            reason = f"Risk gate is HALTED; rejecting/halting order generation (rej={rej:,})."
            conf = 0.95
        elif not has_quotes:
            decision = "WAITING_FOR_QUOTES"
            reason = "No quotes received yet from Board A (RX link may be down or Board A not running)."
            conf = 0.45
        elif has_quotes and not has_orders:
            decision = "HOLD"
            reason = "Quotes are flowing, but orders are not being generated yet (strategy trigger/threshold not met)."
            conf = 0.6
        elif has_orders:
            decision = "SENDING_ORDERS"
            reason = "Strategy is generating orders; monitor for fills and risk rejects."
            conf = 0.8

        ml_diag = (
            "ML diagnostics unavailable (telemetry provides only strategy name)."
            if strat_lbl == "ML"
            else "ML diagnostics unavailable."
        )

        risk_section = html.Div(
            [
                html.Div("Risk State", style={"color": c["muted"], "fontSize": "11px", "textTransform": "uppercase", "letterSpacing": "0.08em"}),
                html.Div(risk_lbl, style={"fontWeight": "900", "fontSize": "18px", "color": c["bad"] if risk_lbl in ("HALTED","REJECTING") else c["good"], "marginTop": "4px"}),
                html.Div(f"Exposure (Σ|pos|): {exposure:,}", style={"color": c["text"], "fontSize": "13px", "marginTop": "8px"}),
                html.Div("Position limit: UNKNOWN (not exposed in current telemetry).", style={"color": c["muted"], "fontSize": "13px", "marginTop": "4px"}),
                html.Div(f"Reject count: {rej:,}", style={"color": c["muted"], "fontSize": "13px", "marginTop": "4px"}),
                html.Div("Last reject reason: UNKNOWN (not provided).", style={"color": c["muted"], "fontSize": "13px", "marginTop": "4px"}),
            ]
        )

        strategy_section = html.Div(
            [
                html.Div("Strategy", style={"color": c["muted"], "fontSize": "11px", "textTransform": "uppercase", "letterSpacing": "0.08em"}),
                html.Div(strat_lbl, style={"fontWeight": "900", "fontSize": "18px", "color": c["accent"], "marginTop": "4px"}),
                html.Div(f"Current decision: {decision}", style={"color": c["text"], "fontSize": "13px", "marginTop": "8px"}),
                html.Div(f"Reason: {reason}", style={"color": c["muted"], "fontSize": "13px", "marginTop": "4px", "lineHeight": "1.45"}),
                html.Div(f"Confidence: {int(conf * 100)}%", style={"color": c["muted"], "fontSize": "13px", "marginTop": "8px"}),
                html.Div(f"Regime: {regime_lbl}", style={"color": c["muted"], "fontSize": "13px", "marginTop": "4px"}),
                html.Div(f"Selected symbol: {selected_symbol}", style={"color": c["muted"], "fontSize": "13px", "marginTop": "4px"}),
                html.Div(ml_diag, style={"color": c["muted"], "fontSize": "13px", "marginTop": "8px", "lineHeight": "1.45"}),
            ]
        )

        diag_panel = html.Div(
            [
                strategy_section,
                html.Div(style={"height": "1px", "backgroundColor": c["grid"], "margin": "14px 0"}),
                risk_section,
                (
                    html.Div(
                        [
                            html.Div(
                                "Debug View (raw telemetry)",
                                style={
                                    "color": c["muted"],
                                    "fontSize": "11px",
                                    "textTransform": "uppercase",
                                    "letterSpacing": "0.08em",
                                    "marginBottom": "8px",
                                    "fontWeight": "700",
                                },
                            ),
                            html.Div(
                                f"Raw state: {latest.get('state', 'UNKNOWN')}",
                                style={"color": c["text"], "fontSize": "13px"},
                            ),
                            html.Div(
                                f"Raw strategy: {latest.get('strategy', 'UNKNOWN')}",
                                style={"color": c["text"], "fontSize": "13px", "marginTop": "4px"},
                            ),
                            html.Div(
                                f"Raw regime: regime={latest.get('regime', 'UNKNOWN')} regime_name={latest.get('regime_name', 'UNKNOWN')}",
                                style={"color": c["text"], "fontSize": "13px", "marginTop": "4px"},
                            ),
                            html.Div(
                                f"Link errors: {int(latest.get('link_err', 0) or 0)} | Parse errors: {int(telem.get('parse_errors', 0) or 0)}",
                                style={"color": c["text"], "fontSize": "13px", "marginTop": "4px"},
                            ),
                            html.Div(
                                f"Counters: qps={int(latest.get('qps', 0) or 0)} ops={int(latest.get('ops', 0) or 0)} fps={int(latest.get('fps', 0) or 0)} rej={int(latest.get('rej', 0) or 0)}",
                                style={"color": c["text"], "fontSize": "13px", "marginTop": "4px"},
                            ),
                            html.Div(
                                f"Telemetry heartbeat (ingest count): {int(telem.get('heartbeat', 0) or 0)}",
                                style={"color": c["text"], "fontSize": "13px", "marginTop": "4px"},
                            ),
                            html.Div(
                                "Raw telemetry snapshot (truncated):",
                                style={
                                    "color": c["muted"],
                                    "fontSize": "13px",
                                    "marginTop": "10px",
                                    "fontWeight": "700",
                                },
                            ),
                            html.Pre(
                                (
                                    __import__("json").dumps(latest, indent=2, sort_keys=True)[:900]
                                    + ("…" if len(__import__("json").dumps(latest, indent=2, sort_keys=True)) > 900 else "")
                                ),
                                style={
                                    "color": c["text"],
                                    "fontSize": "11px",
                                    "whiteSpace": "pre-wrap",
                                    "wordBreak": "break-word",
                                    "marginTop": "6px",
                                    "backgroundColor": "#0f172a",
                                    "padding": "10px",
                                    "borderRadius": "12px",
                                    "border": f"1px solid {c['grid']}",
                                    "maxHeight": "220px",
                                    "overflowY": "auto",
                                },
                            ),
                        ],
                        style={"marginTop": "14px", "paddingTop": "14px", "borderTop": f"1px solid {c['grid']}"},
                    )
                    if effective_debug
                    else None
                ),
            ],
            style={
                "borderRadius": "14px",
                "padding": "12px 14px",
                "border": f"1px solid {c['grid']}",
                "backgroundColor": c["card"],
            },
        )

        # Per-symbol book table (derived from existing telemetry fields).
        if not has_any_traffic:
            symbol_table = html.Div(
                "Waiting for quotes from Board A…",
                style={"color": c["muted"], "fontSize": "13px", "lineHeight": "1.5"},
            )
        else:
            import math

            def _fmt_money_signed(v: Any) -> str:
                try:
                    fv = float(v)
                    if math.isnan(fv):
                        return "—"
                except (TypeError, ValueError):
                    return "—"
                if fv >= 0:
                    return f"+${fv:,.2f}"
                return f"-${abs(fv):,.2f}"

            def _fmt_money(v: Any) -> str:
                try:
                    fv = float(v)
                    if math.isnan(fv):
                        return "—"
                except (TypeError, ValueError):
                    return "—"
                return f"${fv:,.2f}"

            def _fmt_count(v: Any) -> str:
                try:
                    return f"{int(v):,}"
                except (TypeError, ValueError):
                    return "—"

            bid = latest.get("bid", [0.0] * NUM_SYMBOLS)
            ask = latest.get("ask", [0.0] * NUM_SYMBOLS)
            mid = latest.get("mid", [0.0] * NUM_SYMBOLS)
            spread = latest.get("spread", [0.0] * NUM_SYMBOLS)
            pos = latest.get("pos", [0] * NUM_SYMBOLS)
            pnl_mtm = latest.get("pnl_mtm", [0.0] * NUM_SYMBOLS)
            trades = latest.get("trades", [0] * NUM_SYMBOLS)
            last_fill = latest.get("last_fill", [0.0] * NUM_SYMBOLS)

            for arr_name, arr, default in (
                ("bid", bid, [0.0] * NUM_SYMBOLS),
                ("ask", ask, [0.0] * NUM_SYMBOLS),
                ("mid", mid, [0.0] * NUM_SYMBOLS),
                ("spread", spread, [0.0] * NUM_SYMBOLS),
                ("pos", pos, [0] * NUM_SYMBOLS),
                ("pnl_mtm", pnl_mtm, [0.0] * NUM_SYMBOLS),
                ("trades", trades, [0] * NUM_SYMBOLS),
                ("last_fill", last_fill, [0.0] * NUM_SYMBOLS),
            ):
                if not isinstance(arr, list):
                    locals()[arr_name] = default

            # Ensure all arrays are long enough.
            def _pad_list(v: Any, n: int, fill: Any) -> List[Any]:
                if not isinstance(v, list):
                    v = []
                out = list(v)
                while len(out) < n:
                    out.append(fill)
                return out[:n]

            bid = _pad_list(bid, NUM_SYMBOLS, 0.0)
            ask = _pad_list(ask, NUM_SYMBOLS, 0.0)
            mid = _pad_list(mid, NUM_SYMBOLS, 0.0)
            spread = _pad_list(spread, NUM_SYMBOLS, 0.0)
            pos = _pad_list(pos, NUM_SYMBOLS, 0)
            pnl_mtm = _pad_list(pnl_mtm, NUM_SYMBOLS, 0.0)
            trades = _pad_list(trades, NUM_SYMBOLS, 0)
            last_fill = _pad_list(last_fill, NUM_SYMBOLS, 0.0)

            headers = ["SYM", "BID", "ASK", "MID", "SPREAD", "POS", "PNL", "TRADES", "LAST ACTION"]
            th_style = {
                "textAlign": "left",
                "padding": "6px 6px",
                "borderBottom": f"1px solid {c['grid']}",
                "color": c["muted"],
                "fontSize": "11px",
                "letterSpacing": "0.06em",
                "textTransform": "uppercase",
                "fontWeight": "700",
                "whiteSpace": "nowrap",
                "overflow": "hidden",
                "textOverflow": "ellipsis",
            }
            td_style = {
                "padding": "6px 6px",
                "borderBottom": f"1px solid {c['grid']}",
                "fontSize": "12px",
                "whiteSpace": "nowrap",
                "overflow": "hidden",
                "textOverflow": "ellipsis",
            }

            body_rows: List[html.Tr] = []
            for i in sym_filter:
                if not (0 <= i < NUM_SYMBOLS):
                    continue
                ticker = SYMBOL_NAMES[i]
                b = bid[i]
                a = ask[i]
                m = mid[i]
                spr = spread[i]
                p = pos[i]
                pnl = pnl_mtm[i]
                tr = trades[i]
                lf = last_fill[i]

                quote_missing = (b == 0.0 and a == 0.0 and m == 0.0 and spr == 0.0)
                pos_s = "0" if int(p) == 0 else (f"+{int(p)}" if int(p) > 0 else f"{int(p)}")

                last_action = "—"
                if int(tr) > 0:
                    last_action = "FILL"

                if quote_missing:
                    bid_s = ask_s = mid_s = spread_s = pnl_s = "—"
                else:
                    bid_s = _fmt_money(b)
                    ask_s = _fmt_money(a)
                    mid_s = _fmt_money(m)
                    spread_s = f"{float(spr):.3f}"
                    pnl_s = _fmt_money_signed(pnl)

                # Value color semantics.
                pnl_color = c["muted"]
                try:
                    if not quote_missing:
                        pnl_color = c["good"] if float(pnl) >= 0 else c["bad"]
                except (TypeError, ValueError):
                    pnl_color = c["muted"]

                body_rows.append(
                    html.Tr(
                        [
                            html.Td(ticker, style=td_style),
                            html.Td(bid_s, style=td_style),
                            html.Td(ask_s, style=td_style),
                            html.Td(mid_s, style=td_style),
                            html.Td(spread_s, style=td_style),
                            html.Td(pos_s, style=td_style),
                            html.Td(pnl_s, style={**td_style, "color": pnl_color, "fontWeight": "700"}),
                            html.Td(_fmt_count(tr), style={**td_style}),
                            html.Td(last_action, style=td_style),
                        ]
                    )
                )

            symbol_table = html.Table(
                [
                    html.Thead(html.Tr([html.Th(h, style=th_style) for h in headers])),
                    html.Tbody(body_rows),
                ],
                style={
                    "width": "100%",
                    "borderCollapse": "collapse",
                    "tableLayout": "fixed",
                    "overflowX": "hidden",
                },
            )

        # Mini system diagram (demo-friendly, no RTL dependence).
        def _pill(text: str, color: str) -> html.Span:
            return html.Span(
                text,
                style={
                    "display": "inline-block",
                    "padding": "4px 10px",
                    "borderRadius": "999px",
                    "fontSize": "12px",
                    "fontWeight": "900",
                    "letterSpacing": "0.01em",
                    "color": "#000000" if color in (c["accent"], c["good"]) else "#ffffff",
                    "backgroundColor": color,
                },
            )

        qps_i = int(latest.get("qps", 0) or 0)
        ops_i = int(latest.get("ops", 0) or 0)
        board_a_status = "QUOTES RX" if qps_i > 0 else "WAITING"
        link_status = "UP" if link_up else "DOWN"
        link_color = c["good"] if link_up else c["bad"]
        board_a_color = c["good"] if qps_i > 0 else c["warn"]
        board_b_color = c["accent"] if fsm_lbl in ("RUNNING", "RESET") else c["muted"]
        orders_status = "BLOCKED" if risk_halt else ("SENDING" if ops_i > 0 else "IDLE")
        orders_color = c["bad"] if risk_halt else (c["good"] if ops_i > 0 else c["warn"])
        exchange_status = "RISK HALTED" if risk_halt else "ENABLED"
        exchange_color = c["bad"] if risk_halt else c["good"]

        sys_diagram = html.Div(
            [
                html.Div(
                    "Mini System Diagram",
                    style={"fontSize": "11px", "color": c["muted"], "textTransform": "uppercase", "letterSpacing": "0.08em", "fontWeight": "800", "marginBottom": "10px"},
                ),
                html.Div(
                    [
                        html.Div(
                            [
                                html.Div("Board A", style={"fontWeight": "900", "fontSize": "12px", "color": c["muted"]}),
                                html.Div("Market Sim", style={"fontWeight": "900", "fontSize": "14px", "color": c["text"], "marginTop": "2px"}),
                                _pill(board_a_status, board_a_color),
                            ],
                            style={"padding": "12px 12px", "borderRadius": "14px", "border": f"1px solid {c['grid']}", "backgroundColor": c["card"]},
                        ),
                        html.Div("→", style={"fontWeight": "900", "fontSize": "22px", "color": c["muted"]}),
                        html.Div(
                            [
                                html.Div("PMOD Link", style={"fontWeight": "900", "fontSize": "12px", "color": c["muted"]}),
                                _pill(link_status, link_color),
                            ],
                            style={"padding": "12px 12px", "borderRadius": "14px", "border": f"1px solid {c['grid']}", "backgroundColor": c["card"]},
                        ),
                        html.Div("→", style={"fontWeight": "900", "fontSize": "22px", "color": c["muted"]}),
                        html.Div(
                            [
                                html.Div("Board B", style={"fontWeight": "900", "fontSize": "12px", "color": c["muted"]}),
                                html.Div("Trader", style={"fontWeight": "900", "fontSize": "14px", "color": c["text"], "marginTop": "2px"}),
                                _pill(fsm_lbl if fsm_lbl != "UNKNOWN" else "UNKNOWN", board_b_color),
                            ],
                            style={"padding": "12px 12px", "borderRadius": "14px", "border": f"1px solid {c['grid']}", "backgroundColor": c["card"]},
                        ),
                        html.Div("→", style={"fontWeight": "900", "fontSize": "22px", "color": c["muted"]}),
                        html.Div(
                            [
                                html.Div("Orders TX", style={"fontWeight": "900", "fontSize": "12px", "color": c["muted"]}),
                                _pill(orders_status, orders_color),
                            ],
                            style={"padding": "12px 12px", "borderRadius": "14px", "border": f"1px solid {c['grid']}", "backgroundColor": c["card"]},
                        ),
                        html.Div("→", style={"fontWeight": "900", "fontSize": "22px", "color": c["muted"]}),
                        html.Div(
                            [
                                html.Div("Board A", style={"fontWeight": "900", "fontSize": "12px", "color": c["muted"]}),
                                html.Div("Exchange", style={"fontWeight": "900", "fontSize": "14px", "color": c["text"], "marginTop": "2px"}),
                                _pill(exchange_status, exchange_color),
                            ],
                            style={"padding": "12px 12px", "borderRadius": "14px", "border": f"1px solid {c['grid']}", "backgroundColor": c["card"]},
                        ),
                    ],
                    style={"display": "flex", "flexWrap": "wrap", "alignItems": "center", "gap": "12px"},
                ),
            ],
            style={"marginTop": "10px"},
        )

        return (
            flow,
            kpis,
            pnl_title_style,
            pnl_hero,
            fig_pnl,
            pos_title_style,
            fig_pos,
            fig_thr,
            fig_mini,
            scalar,
            fig_lat,
            events_panel,
            diag_panel,
            symbol_table,
            sys_diagram,
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
                "Keys 1–4 highlight a row; Esc closes. Regime labels follow regime / regime_name in telemetry.",
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
                    var colors = ['#00C805', '#FFB020', '#5AC8FA', '#FF331F'];
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
    if args.port:
        port = args.port
    elif sys.platform == "win32":
        port = "COM5"
    elif sys.platform == "darwin":
        port = ""  # Mac: use --port /dev/cu.* or set device in the UI bar
    else:
        port = "/dev/ttyUSB0"
    reader = SerialTelemetryReader(port, args.baud)
    READER = reader
    if not args.no_open and port:
        reader.open_serial()
    reader.start()

    app = build_app(reader)
    display_host = "127.0.0.1" if args.host in ("0.0.0.0", "::") else args.host
    url = f"http://{display_host}:{args.dash_port}/"
    print(f"Dashboard web UI (open in a browser): {url}")
    if args.host == "0.0.0.0":
        print("  (bound on all interfaces — use this machine's LAN IP from other devices)")
    print(
        f"UART serial device: {port or '(none — enter /dev/cu.* in UI and Connect)'} "
        f"@ {args.baud} baud"
    )
    print("Press Ctrl+C in this terminal to stop the server.")

    if args.browser:

        def _open_later() -> None:
            time.sleep(1.25)
            webbrowser.open(url)

        threading.Thread(target=_open_later, daemon=True).start()

    app.run(debug=False, host=args.host, port=args.dash_port)


if __name__ == "__main__":
    main()
