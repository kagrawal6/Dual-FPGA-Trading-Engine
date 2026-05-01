#!/usr/bin/env python3
"""
Laptop Dashboard — dashboard.py
Robinhood-style real-time portfolio monitor for the Dual-FPGA Trading Engine.

IMPORTANT: This is NOT the Board B TradeMark terminal dashboard. That UI is
``board_b_dashboard.py`` (same default HTTP port 8050 — only one can run at a time).
For Book / Events / Diagnostics tabs and terminal-style charts, run:
``python board_b_dashboard.py --demo --browser``

Reads JSON telemetry from Board B's USB-UART (one JSON object per line emitted
by sw/board_b/telemetry_server.py) and renders a Plotly Dash web app with:

  • Header bar:
      - Portfolio value (cash + Σ position·mid)
      - Total P&L $ + % (color-coded green/red)
      - Cash, link status, risk-halt indicator, FSM state
  • Per-symbol cards (Robinhood tile style):
      - Ticker + sector color chip
      - Current mid price + % change vs init_mid
      - Position quantity + position value
      - Mark-to-market P&L $ (green/red)
      - Mini sparkline of recent mid price
      - Last fill price marker, trade count
  • Sector filter pills
  • Latency widget (histogram + min/avg/max in ns)
  • Recent activity (orders/fills/rejects per second + cumulative)
  • System health (link errors, risk halt banner)

Usage:
  # Live serial mode (default):
  python dashboard.py --port COM5 --baud 115200

  # Replay/file mode (read newline-delimited JSON from stdin):
  python sw/board_b/telemetry_server.py ... | python dashboard.py --stdin

  # Demo mode with synthetic data (no Board B required):
  python dashboard.py --demo

  # Custom symbols/sectors from JSON config (else uses default 16-stock map):
  python dashboard.py --port COM5 --symbols-config sw/laptop/symbols_default.json
"""

from __future__ import annotations

import argparse
import json
import math
import random
import sys
import threading
import time
from collections import deque
from typing import Any, Dict, List, Optional

import dash
from dash import dcc, html, Input, Output, State, no_update
import plotly.graph_objects as go


# ═══════════════════════════════════════════════════════════════════════════
# Defaults — must match sw/board_a/symbol_universe.py default loadout.
# Sector colors are picked to be high-contrast on a dark background.
# ═══════════════════════════════════════════════════════════════════════════
NUM_SYMBOLS = 16

DEFAULT_TICKERS = [
    "AAPL", "MSFT", "NVDA", "GOOGL",   # Tech (sector_id=0)
    "AMZN", "TSLA",                     # Cons.Disc (3)
    "JPM",  "GS",                       # Financials (4)
    "JNJ",  "UNH",                      # Health (2)
    "XOM",  "CVX",                      # Energy (1)
    "CAT",  "HON",                      # Industrials (5)
    "PG",   "KO",                       # Staples (6)
]

DEFAULT_SECTOR_IDS = [0, 0, 0, 0, 3, 3, 4, 4, 2, 2, 1, 1, 5, 5, 6, 6]

DEFAULT_INIT_MID = [
    180.00, 420.00, 900.00, 175.00,
    185.00, 250.00,
    200.00, 480.00,
    155.00, 520.00,
    115.00, 160.00,
    360.00, 200.00,
    165.00,  60.00,
]

SECTOR_NAMES = {
    0: "Tech", 1: "Energy", 2: "Health", 3: "Cons.Disc",
    4: "Financials", 5: "Industrials", 6: "Staples", 7: "Comms",
}

SECTOR_COLORS = {
    0: "#5B8DEF",   # Tech       — blue
    1: "#F5A524",   # Energy     — amber
    2: "#22C55E",   # Health     — green
    3: "#EC4899",   # Cons.Disc  — pink
    4: "#A855F7",   # Financials — purple
    5: "#EF4444",   # Industrial — red
    6: "#14B8A6",   # Staples    — teal
    7: "#06B6D4",   # Comms      — cyan
}

GAIN  = "#22C55E"
LOSS  = "#EF4444"
NEUT  = "#6B7280"
BG    = "#0B0F19"
PANEL = "#111827"
TEXT  = "#F3F4F6"
DIM   = "#9CA3AF"

POLL_HZ_DEFAULT = 5.0
SPARK_LEN = 60   # 60 samples ≈ 12s at 5 Hz


# ═══════════════════════════════════════════════════════════════════════════
# Telemetry source: serial / stdin / demo
# ═══════════════════════════════════════════════════════════════════════════
class TelemetrySource:
    """Background reader that produces the latest snapshot dict.

    The snapshot contains the JSON telemetry from Board B plus a
    deque of (ts, mid_per_symbol) tuples for sparklines.
    """

    def __init__(self, num_symbols: int = NUM_SYMBOLS):
        self.num_symbols = num_symbols
        self.lock = threading.Lock()
        self.latest: Optional[Dict[str, Any]] = None
        self.history: deque = deque(maxlen=SPARK_LEN)
        self.fills_history: deque = deque(maxlen=20)
        self._stop = threading.Event()
        self._thread: Optional[threading.Thread] = None

    def start(self, target):
        self._thread = threading.Thread(target=target, args=(self,), daemon=True)
        self._thread.start()

    def stop(self):
        self._stop.set()

    def _ingest(self, data: Dict[str, Any]) -> None:
        with self.lock:
            prev = self.latest
            self.latest = data
            self.history.append((data.get("ts", time.time()),
                                 list(data.get("mid", [0.0] * self.num_symbols))))
            if prev is not None:
                df = data.get("fps", 0) - prev.get("fps", 0)
                if df > 0:
                    self.fills_history.append({
                        "ts": data.get("ts", time.time()),
                        "delta_fps": df,
                    })

    def snapshot(self) -> Optional[Dict[str, Any]]:
        with self.lock:
            if self.latest is None:
                return None
            snap = dict(self.latest)
            snap["_history"] = list(self.history)
            snap["_fills_recent"] = list(self.fills_history)
            return snap


def serial_reader(src: TelemetrySource, port: str, baud: int) -> None:
    import serial  # imported lazily so demo mode works without pyserial
    ser = serial.Serial(port, baud, timeout=1)
    print(f"Serial reader listening on {port} @ {baud}", flush=True)
    buf = b""
    while not src._stop.is_set():
        try:
            chunk = ser.read(4096)
            if not chunk:
                continue
            buf += chunk
            while b"\n" in buf:
                line, buf = buf.split(b"\n", 1)
                line = line.strip()
                if not line:
                    continue
                try:
                    data = json.loads(line.decode(errors="replace"))
                except json.JSONDecodeError:
                    continue
                src._ingest(data)
        except Exception as e:
            print(f"Serial reader error: {e}", flush=True)
            time.sleep(0.5)


def stdin_reader(src: TelemetrySource) -> None:
    print("Stdin reader active (one JSON line per snapshot)", flush=True)
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        try:
            data = json.loads(line)
        except json.JSONDecodeError:
            continue
        src._ingest(data)


def demo_reader(src: TelemetrySource) -> None:
    """Synthetic telemetry generator for offline demos."""
    print("Demo reader active — generating synthetic Board B telemetry", flush=True)
    rng = random.Random(0xC0FFEE)
    mids = list(DEFAULT_INIT_MID)
    pos  = [0] * NUM_SYMBOLS
    pnl_cash = [0.0] * NUM_SYMBOLS
    last_fill = [0.0] * NUM_SYMBOLS
    trades = [0] * NUM_SYMBOLS
    qps = ops = fps = rej = 0
    cash = 0.0
    t0 = time.time()
    while not src._stop.is_set():
        for i in range(NUM_SYMBOLS):
            mids[i] *= (1.0 + rng.gauss(0, 0.0008))
            mids[i] = max(0.5, mids[i])
            if rng.random() < 0.07:
                qty = 25 if rng.random() < 0.5 else 50
                side = rng.choice([-1, 1])
                price = mids[i]
                pos[i] += side * qty
                pnl_cash[i] += -side * qty * price
                cash += -side * qty * price
                last_fill[i] = price
                trades[i] += 1
                fps += 1
                ops += 1
        qps += rng.randint(8, 20)
        if rng.random() < 0.02:
            rej += 1
            ops += 1

        bid = [m * (1 - 0.0006) for m in mids]
        ask = [m * (1 + 0.0006) for m in mids]
        mid = [(b + a) * 0.5 for b, a in zip(bid, ask)]
        spread = [a - b for b, a in zip(bid, ask)]
        pos_value = [p * m for p, m in zip(pos, mid)]
        pnl_mtm = [pc + p * m for pc, p, m in zip(pnl_cash, pos, mid)]
        inventory_mtm = sum(pos_value)
        port_value = cash + inventory_mtm
        elapsed = time.time() - t0
        # Synthetic latency histogram peaked around bin 1-2 (32-95 cy)
        hist = [0] * 16
        for _ in range(min(fps, 200)):
            b = max(0, min(15, int(rng.gauss(2.0, 1.2))))
            hist[b] += 1

        data = {
            "ts": round(time.time(), 3),
            "state": "B_TRADING",
            "link_up": True,
            "risk_halt": False,
            "strategy": "MEAN_REV",
            "qps": qps, "ops": ops, "fps": fps, "rej": rej, "link_err": 0,
            "cash": round(cash, 2),
            "total_pnl": round(sum(pnl_mtm), 2),
            "port_value": round(port_value, 2),
            "inventory_mtm": round(inventory_mtm, 2),
            "pos": pos, "bid": bid, "ask": ask, "mid": mid, "spread": spread,
            "pnl_cash": pnl_cash, "pnl_mtm": pnl_mtm, "pos_value": pos_value,
            "last_fill": last_fill, "trades": trades,
            "hist": hist,
            "lat_min": 12, "lat_max": 480, "lat_sum": int(elapsed * 50000), "lat_cnt": max(1, fps),
        }
        src._ingest(data)
        time.sleep(0.2)


# ═══════════════════════════════════════════════════════════════════════════
# Symbol metadata loader
# ═══════════════════════════════════════════════════════════════════════════
def load_symbols_config(path: Optional[str]) -> Dict[str, list]:
    if path:
        with open(path, "r") as f:
            cfg = json.load(f)
        tickers = cfg.get("tickers", DEFAULT_TICKERS)
        sector_ids = cfg.get("sector_ids", DEFAULT_SECTOR_IDS)
        init_mid = cfg.get("init_mid", DEFAULT_INIT_MID)
        return {"tickers": tickers, "sector_ids": sector_ids, "init_mid": init_mid}
    return {
        "tickers": DEFAULT_TICKERS,
        "sector_ids": DEFAULT_SECTOR_IDS,
        "init_mid": DEFAULT_INIT_MID,
    }


# ═══════════════════════════════════════════════════════════════════════════
# Dash app — layout
# ═══════════════════════════════════════════════════════════════════════════
def build_app(src: TelemetrySource, sym_cfg: Dict[str, list],
              poll_hz: float = POLL_HZ_DEFAULT) -> dash.Dash:
    app = dash.Dash(__name__)
    app.title = "Dual-FPGA Trading Engine — Live Portfolio"

    sectors_present = sorted(set(sym_cfg["sector_ids"]))

    sector_pills = [
        html.Button(
            "All",
            id={"type": "sector-pill", "sid": -1},
            n_clicks=0,
            style=_pill_style(NEUT, selected=True),
        ),
    ] + [
        html.Button(
            SECTOR_NAMES.get(sid, f"S{sid}"),
            id={"type": "sector-pill", "sid": sid},
            n_clicks=0,
            style=_pill_style(SECTOR_COLORS.get(sid, NEUT), selected=False),
        )
        for sid in sectors_present
    ]

    app.layout = html.Div(
        style={"backgroundColor": BG, "color": TEXT, "minHeight": "100vh",
               "fontFamily": "Inter, -apple-system, system-ui, sans-serif",
               "padding": "20px"},
        children=[
            dcc.Store(id="sector-filter", data=-1),
            dcc.Store(id="sym-meta", data=sym_cfg),
            dcc.Interval(id="tick", interval=int(1000 / poll_hz), n_intervals=0),

            # ── Header ─────────────────────────────────────────────
            html.Div(id="header", style={"marginBottom": "20px"}),
            html.Div(id="risk-banner"),

            # ── Sector pills ───────────────────────────────────────
            html.Div(sector_pills,
                     id="sector-pills",
                     style={"display": "flex", "gap": "8px", "flexWrap": "wrap",
                            "marginBottom": "16px"}),

            # ── Top row: portfolio + activity + latency ────────────
            html.Div(
                style={"display": "grid",
                       "gridTemplateColumns": "2fr 1fr 1fr",
                       "gap": "16px", "marginBottom": "20px"},
                children=[
                    html.Div(id="portfolio-chart", style=_panel_style()),
                    html.Div(id="activity-panel", style=_panel_style()),
                    html.Div(id="latency-panel", style=_panel_style()),
                ],
            ),

            # ── Symbol grid ────────────────────────────────────────
            html.Div(id="symbol-grid",
                     style={"display": "grid",
                            "gridTemplateColumns": "repeat(auto-fill, minmax(260px, 1fr))",
                            "gap": "12px"}),

            # ── Footer ─────────────────────────────────────────────
            html.Div(id="footer",
                     style={"marginTop": "24px", "color": DIM, "fontSize": "12px",
                            "textAlign": "center"}),
        ],
    )

    _register_callbacks(app, src, sym_cfg)
    return app


def _panel_style() -> dict:
    return {
        "backgroundColor": PANEL, "borderRadius": "12px",
        "padding": "16px", "boxShadow": "0 2px 8px rgba(0,0,0,0.3)",
    }


def _pill_style(color: str, selected: bool) -> dict:
    return {
        "padding": "6px 14px", "borderRadius": "999px",
        "border": f"2px solid {color}",
        "backgroundColor": color if selected else "transparent",
        "color": TEXT if selected else color,
        "fontWeight": "600", "cursor": "pointer", "fontSize": "13px",
    }


# ═══════════════════════════════════════════════════════════════════════════
# Callbacks
# ═══════════════════════════════════════════════════════════════════════════
def _register_callbacks(app: dash.Dash, src: TelemetrySource,
                        sym_cfg: Dict[str, list]) -> None:

    tickers   = sym_cfg["tickers"]
    sector_id = sym_cfg["sector_ids"]
    init_mid  = sym_cfg["init_mid"]

    @app.callback(
        Output("sector-filter", "data"),
        Output("sector-pills", "children"),
        Input({"type": "sector-pill", "sid": dash.ALL}, "n_clicks"),
        State("sector-pills", "children"),
        State("sector-filter", "data"),
        prevent_initial_call=True,
    )
    def _on_pill_click(n_clicks_list, pills, current):
        ctx = dash.callback_context
        if not ctx.triggered:
            return no_update, no_update
        triggered = json.loads(ctx.triggered[0]["prop_id"].split(".")[0])
        sid = triggered["sid"]
        # Re-render all pills with the new selected one
        new_pills = []
        for p in pills:
            pid = p["props"]["id"]
            psid = pid["sid"]
            color = NEUT if psid == -1 else SECTOR_COLORS.get(psid, NEUT)
            new_pills.append(
                html.Button(
                    p["props"]["children"],
                    id=pid, n_clicks=0,
                    style=_pill_style(color, selected=(psid == sid)),
                )
            )
        return sid, new_pills

    @app.callback(
        Output("header", "children"),
        Output("risk-banner", "children"),
        Output("portfolio-chart", "children"),
        Output("activity-panel", "children"),
        Output("latency-panel", "children"),
        Output("symbol-grid", "children"),
        Output("footer", "children"),
        Input("tick", "n_intervals"),
        State("sector-filter", "data"),
    )
    def _on_tick(_n, filter_sid):
        snap = src.snapshot()
        if snap is None:
            placeholder = html.Div("Waiting for telemetry…",
                                   style={"color": DIM, "fontSize": "16px",
                                          "padding": "20px"})
            return (placeholder, html.Div(), placeholder, placeholder,
                    placeholder, html.Div(), "")

        return (
            _render_header(snap),
            _render_risk_banner(snap),
            _render_portfolio_chart(snap, tickers),
            _render_activity_panel(snap),
            _render_latency_panel(snap),
            _render_symbol_grid(snap, tickers, sector_id, init_mid, filter_sid),
            _render_footer(snap),
        )


# ═══════════════════════════════════════════════════════════════════════════
# Renderers
# ═══════════════════════════════════════════════════════════════════════════
def _color_for_pnl(v: float) -> str:
    if v > 0.005:  return GAIN
    if v < -0.005: return LOSS
    return NEUT


def _render_header(snap: dict) -> html.Div:
    port_value = snap.get("port_value", 0.0)
    cash       = snap.get("cash", 0.0)
    total_pnl  = snap.get("total_pnl", 0.0)
    cost_basis = port_value - total_pnl
    pnl_pct    = (total_pnl / cost_basis * 100.0) if abs(cost_basis) > 1e-3 else 0.0
    state      = snap.get("state", "?")
    strategy   = snap.get("strategy", "?")
    link_up    = snap.get("link_up", False)
    risk_halt  = snap.get("risk_halt", False)

    pnl_color = _color_for_pnl(total_pnl)

    pills = [
        html.Span(state, style={
            "padding": "4px 10px", "borderRadius": "6px", "fontSize": "12px",
            "backgroundColor": GAIN if state == "B_TRADING" else NEUT, "color": TEXT,
            "fontWeight": "700",
        }),
        html.Span(f"strategy: {strategy}", style={"color": DIM, "fontSize": "13px"}),
        html.Span("LINK UP" if link_up else "LINK DOWN", style={
            "padding": "4px 10px", "borderRadius": "6px", "fontSize": "12px",
            "backgroundColor": GAIN if link_up else LOSS, "color": TEXT, "fontWeight": "700",
        }),
    ]
    if risk_halt:
        pills.append(html.Span("RISK HALT", style={
            "padding": "4px 10px", "borderRadius": "6px", "fontSize": "12px",
            "backgroundColor": LOSS, "color": TEXT, "fontWeight": "700",
        }))

    return html.Div(
        style={"display": "flex", "alignItems": "center",
               "gap": "20px", "justifyContent": "space-between",
               "backgroundColor": PANEL, "padding": "16px 20px",
               "borderRadius": "12px"},
        children=[
            html.Div([
                html.Div("Portfolio Value", style={"color": DIM, "fontSize": "12px",
                                                    "textTransform": "uppercase",
                                                    "letterSpacing": "0.05em"}),
                html.Div(f"${port_value:,.2f}",
                         style={"fontSize": "32px", "fontWeight": "800",
                                "marginTop": "2px"}),
                html.Div([
                    html.Span(f"{'+' if total_pnl >= 0 else ''}${total_pnl:,.2f}",
                              style={"color": pnl_color, "fontWeight": "700",
                                     "fontSize": "16px"}),
                    html.Span(f"  ({pnl_pct:+.2f}%)",
                              style={"color": pnl_color, "marginLeft": "6px",
                                     "fontSize": "14px"}),
                ], style={"marginTop": "4px"}),
            ]),
            html.Div([
                html.Div("Cash", style={"color": DIM, "fontSize": "12px",
                                        "textTransform": "uppercase"}),
                html.Div(f"${cash:,.2f}",
                         style={"fontSize": "20px", "fontWeight": "700",
                                "color": _color_for_pnl(cash)}),
            ]),
            html.Div(pills, style={"display": "flex", "gap": "10px",
                                    "alignItems": "center"}),
        ],
    )


def _render_risk_banner(snap: dict) -> html.Div:
    if not snap.get("risk_halt"):
        return html.Div()
    return html.Div(
        "⚠ RISK HALT — Maximum loss threshold breached. Trading frozen until reset.",
        style={"backgroundColor": LOSS, "color": TEXT, "padding": "12px",
               "borderRadius": "8px", "fontWeight": "700", "marginBottom": "12px",
               "textAlign": "center"},
    )


def _render_portfolio_chart(snap: dict, tickers: List[str]) -> html.Div:
    history = snap.get("_history", [])
    pos = snap.get("pos", [0] * NUM_SYMBOLS)
    cash = snap.get("cash", 0.0)
    if len(history) < 2:
        return html.Div([
            html.Div("Portfolio Value Over Time",
                     style={"color": DIM, "fontSize": "12px", "marginBottom": "8px"}),
            html.Div("(collecting data…)",
                     style={"color": DIM, "padding": "60px 0", "textAlign": "center"}),
        ])

    ts = [t for t, _ in history]
    t0 = ts[0]
    rel_t = [t - t0 for t in ts]
    port_series = []
    for _, mids in history:
        v = cash + sum(p * m for p, m in zip(pos, mids))
        port_series.append(v)

    fig = go.Figure()
    line_color = GAIN if (port_series[-1] >= port_series[0]) else LOSS
    fig.add_trace(go.Scatter(
        x=rel_t, y=port_series, mode="lines",
        line=dict(color=line_color, width=2),
        fill="tozeroy", fillcolor=f"{line_color}22",
        hovertemplate="t=%{x:.1f}s<br>$%{y:,.2f}<extra></extra>",
    ))
    fig.update_layout(
        margin=dict(l=10, r=10, t=10, b=10), height=180,
        paper_bgcolor=PANEL, plot_bgcolor=PANEL,
        xaxis=dict(title="seconds", color=DIM, gridcolor="#1F2937", showgrid=True),
        yaxis=dict(title="$", color=DIM, gridcolor="#1F2937", showgrid=True,
                   tickformat=",.0f"),
        showlegend=False,
    )
    return html.Div([
        html.Div("Portfolio Value Over Time",
                 style={"color": DIM, "fontSize": "12px", "marginBottom": "4px",
                        "textTransform": "uppercase", "letterSpacing": "0.05em"}),
        dcc.Graph(figure=fig, config={"displayModeBar": False}),
    ])


def _render_activity_panel(snap: dict) -> html.Div:
    qps = snap.get("qps", 0)
    ops = snap.get("ops", 0)
    fps = snap.get("fps", 0)
    rej = snap.get("rej", 0)
    link_err = snap.get("link_err", 0)
    fill_rate   = (fps / ops * 100) if ops else 0.0
    reject_rate = (rej / max(ops + rej, 1) * 100)

    rows = [
        ("Quotes received", f"{qps:,}",  TEXT),
        ("Orders sent",     f"{ops:,}",  TEXT),
        ("Fills received",  f"{fps:,}",  GAIN),
        ("Risk rejects",    f"{rej:,}",  LOSS if rej else DIM),
        ("Link errors",     f"{link_err:,}", LOSS if link_err else DIM),
        ("Fill rate",       f"{fill_rate:.1f}%", TEXT),
        ("Reject rate",     f"{reject_rate:.1f}%", LOSS if reject_rate > 5 else TEXT),
    ]
    return html.Div([
        html.Div("Activity",
                 style={"color": DIM, "fontSize": "12px", "marginBottom": "10px",
                        "textTransform": "uppercase", "letterSpacing": "0.05em"}),
        html.Div([
            html.Div([
                html.Span(label, style={"color": DIM, "fontSize": "13px"}),
                html.Span(value, style={"float": "right", "color": color,
                                         "fontWeight": "600"}),
            ], style={"padding": "5px 0",
                      "borderBottom": "1px solid #1F2937"})
            for label, value, color in rows
        ]),
    ])


def _render_latency_panel(snap: dict) -> html.Div:
    lat_min = snap.get("lat_min", 0)
    lat_max = snap.get("lat_max", 0)
    lat_sum = snap.get("lat_sum", 0)
    lat_cnt = snap.get("lat_cnt", 0)
    avg_cy = (lat_sum / lat_cnt) if lat_cnt else 0.0
    NS = 10  # 100 MHz core clock

    hist = snap.get("hist", [0] * 16)
    fig = go.Figure()
    bin_labels = [f"{i*32}-{i*32+31}" if i < 15 else "≥480"
                  for i in range(16)]
    bar_colors = [
        GAIN if i <= 1 else "#06B6D4" if i <= 4
        else "#F59E0B" if i <= 9 else LOSS
        for i in range(16)
    ]
    fig.add_trace(go.Bar(
        x=bin_labels, y=hist, marker_color=bar_colors,
        hovertemplate="%{x} cy<br>%{y:,} fills<extra></extra>",
    ))
    fig.update_layout(
        margin=dict(l=10, r=10, t=10, b=30), height=130,
        paper_bgcolor=PANEL, plot_bgcolor=PANEL,
        xaxis=dict(color=DIM, tickangle=-45, tickfont=dict(size=8)),
        yaxis=dict(color=DIM, gridcolor="#1F2937", showgrid=True),
        showlegend=False, bargap=0.05,
    )

    return html.Div([
        html.Div("Latency (quote → fill)",
                 style={"color": DIM, "fontSize": "12px", "marginBottom": "8px",
                        "textTransform": "uppercase", "letterSpacing": "0.05em"}),
        html.Div([
            html.Div([
                html.Div("min", style={"color": DIM, "fontSize": "11px"}),
                html.Div(f"{lat_min*NS} ns", style={"color": GAIN, "fontWeight": "700"}),
            ]),
            html.Div([
                html.Div("avg", style={"color": DIM, "fontSize": "11px"}),
                html.Div(f"{avg_cy*NS:.0f} ns", style={"color": TEXT, "fontWeight": "700"}),
            ]),
            html.Div([
                html.Div("max", style={"color": DIM, "fontSize": "11px"}),
                html.Div(f"{lat_max*NS} ns", style={"color": LOSS, "fontWeight": "700"}),
            ]),
            html.Div([
                html.Div("samples", style={"color": DIM, "fontSize": "11px"}),
                html.Div(f"{lat_cnt:,}", style={"color": TEXT, "fontWeight": "700"}),
            ]),
        ], style={"display": "flex", "justifyContent": "space-between",
                  "marginBottom": "10px"}),
        dcc.Graph(figure=fig, config={"displayModeBar": False}),
    ])


def _render_symbol_grid(snap: dict, tickers: List[str], sector_ids: List[int],
                         init_mids: List[float], filter_sid: int) -> List[html.Div]:
    history = snap.get("_history", [])
    pos       = snap.get("pos", [0] * NUM_SYMBOLS)
    bid       = snap.get("bid", [0.0] * NUM_SYMBOLS)
    ask       = snap.get("ask", [0.0] * NUM_SYMBOLS)
    mid       = snap.get("mid", [0.0] * NUM_SYMBOLS)
    spread    = snap.get("spread", [0.0] * NUM_SYMBOLS)
    pnl_mtm   = snap.get("pnl_mtm", [0.0] * NUM_SYMBOLS)
    pos_value = snap.get("pos_value", [0.0] * NUM_SYMBOLS)
    last_fill = snap.get("last_fill", [0.0] * NUM_SYMBOLS)
    trades    = snap.get("trades", [0] * NUM_SYMBOLS)

    cards = []
    for i in range(min(NUM_SYMBOLS, len(tickers))):
        sid = sector_ids[i] if i < len(sector_ids) else 0
        if filter_sid != -1 and sid != filter_sid:
            continue

        ticker = tickers[i]
        sname  = SECTOR_NAMES.get(sid, f"S{sid}")
        scolor = SECTOR_COLORS.get(sid, NEUT)
        cur    = mid[i]
        init   = init_mids[i] if i < len(init_mids) else 0.0
        pct    = ((cur - init) / init * 100.0) if init > 0 else 0.0
        pct_color = _color_for_pnl(pct)
        pnl_color = _color_for_pnl(pnl_mtm[i])

        # Sparkline
        spark_y = [snap_mids[i] for _, snap_mids in history if i < len(snap_mids)]
        if len(spark_y) >= 2:
            spark = go.Figure()
            line_c = GAIN if spark_y[-1] >= spark_y[0] else LOSS
            spark.add_trace(go.Scatter(
                y=spark_y, mode="lines",
                line=dict(color=line_c, width=1.5),
                fill="tozeroy", fillcolor=f"{line_c}33",
                hoverinfo="skip",
            ))
            spark.update_layout(
                margin=dict(l=0, r=0, t=0, b=0), height=44,
                paper_bgcolor=PANEL, plot_bgcolor=PANEL,
                xaxis=dict(visible=False), yaxis=dict(visible=False, range=[
                    min(spark_y) * 0.998, max(spark_y) * 1.002
                ]),
                showlegend=False,
            )
            spark_div = dcc.Graph(figure=spark, config={"displayModeBar": False})
        else:
            spark_div = html.Div(style={"height": "44px"})

        # Position chip
        if pos[i] > 0:
            pos_chip = html.Span(f"LONG {pos[i]}", style={
                "color": GAIN, "fontWeight": "700", "fontSize": "11px",
                "padding": "2px 6px", "borderRadius": "4px",
                "border": f"1px solid {GAIN}",
            })
        elif pos[i] < 0:
            pos_chip = html.Span(f"SHORT {abs(pos[i])}", style={
                "color": LOSS, "fontWeight": "700", "fontSize": "11px",
                "padding": "2px 6px", "borderRadius": "4px",
                "border": f"1px solid {LOSS}",
            })
        else:
            pos_chip = html.Span("FLAT", style={
                "color": DIM, "fontSize": "11px",
                "padding": "2px 6px", "borderRadius": "4px",
                "border": f"1px solid {DIM}",
            })

        cards.append(html.Div(
            style={"backgroundColor": PANEL, "borderRadius": "10px",
                   "padding": "12px", "boxShadow": "0 1px 4px rgba(0,0,0,0.3)",
                   "borderTop": f"3px solid {scolor}"},
            children=[
                # Top row: ticker + sector
                html.Div([
                    html.Span(ticker, style={"fontWeight": "800", "fontSize": "16px"}),
                    html.Span(sname, style={
                        "float": "right", "color": scolor,
                        "fontSize": "10px", "fontWeight": "600",
                        "textTransform": "uppercase", "letterSpacing": "0.05em",
                    }),
                ]),
                # Price + % change
                html.Div([
                    html.Span(f"${cur:,.2f}", style={"fontSize": "20px",
                                                     "fontWeight": "700"}),
                    html.Span(f"{pct:+.2f}%", style={
                        "float": "right", "color": pct_color,
                        "fontWeight": "700", "fontSize": "13px",
                        "marginTop": "5px",
                    }),
                ], style={"marginTop": "4px"}),
                # Sparkline
                html.Div(spark_div, style={"marginTop": "4px"}),
                # Position + chip
                html.Div([
                    pos_chip,
                    html.Span(f"${pos_value[i]:+,.2f}", style={
                        "float": "right", "color": _color_for_pnl(pos_value[i]),
                        "fontSize": "12px", "fontWeight": "600",
                    }),
                ], style={"marginTop": "6px"}),
                # P&L
                html.Div([
                    html.Span("P&L", style={"color": DIM, "fontSize": "11px"}),
                    html.Span(f"{'+' if pnl_mtm[i] >= 0 else ''}${pnl_mtm[i]:,.2f}",
                              style={"float": "right", "color": pnl_color,
                                     "fontWeight": "700", "fontSize": "13px"}),
                ], style={"marginTop": "4px",
                          "borderTop": "1px solid #1F2937", "paddingTop": "4px"}),
                # Bid/Ask + spread
                html.Div([
                    html.Span(f"bid ${bid[i]:.2f}", style={"color": LOSS,
                                                            "fontSize": "10px"}),
                    html.Span(f" · ", style={"color": DIM, "fontSize": "10px"}),
                    html.Span(f"ask ${ask[i]:.2f}", style={"color": GAIN,
                                                            "fontSize": "10px"}),
                    html.Span(f"spread ${spread[i]:.3f}", style={
                        "float": "right", "color": DIM, "fontSize": "10px",
                    }),
                ], style={"marginTop": "4px"}),
                # Last fill + trades
                html.Div([
                    html.Span(f"last ${last_fill[i]:.2f}" if last_fill[i] > 0 else "no fills yet",
                              style={"color": DIM, "fontSize": "10px"}),
                    html.Span(f"{trades[i]} trades", style={
                        "float": "right", "color": DIM, "fontSize": "10px",
                    }),
                ], style={"marginTop": "2px"}),
            ],
        ))

    return cards


def _render_footer(snap: dict) -> str:
    ts = snap.get("ts", time.time())
    age_ms = (time.time() - ts) * 1000
    return (f"Last update: {time.strftime('%H:%M:%S', time.localtime(ts))}  "
            f"·  age {age_ms:.0f} ms  ·  "
            f"Dual-FPGA Trading Engine — Live Hardware Telemetry")


# ═══════════════════════════════════════════════════════════════════════════
# Entry point
# ═══════════════════════════════════════════════════════════════════════════
def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Dual-FPGA Trading Engine — Live Dashboard")
    p.add_argument("--port", default=None,
                   help="Serial port for Board B UART (e.g. COM5, /dev/ttyUSB0)")
    p.add_argument("--baud", type=int, default=115200, help="Baud rate (default: 115200)")
    p.add_argument("--stdin", action="store_true",
                   help="Read JSON telemetry from stdin instead of serial")
    p.add_argument("--demo", action="store_true",
                   help="Generate synthetic data — no Board B required")
    p.add_argument("--symbols-config", default=None,
                   help="JSON file with tickers/sector_ids/init_mid arrays")
    p.add_argument("--poll-hz", type=float, default=POLL_HZ_DEFAULT,
                   help=f"Dashboard refresh rate (default: {POLL_HZ_DEFAULT})")
    p.add_argument("--host", default="127.0.0.1", help="Dash host (default: 127.0.0.1)")
    p.add_argument("--http-port", type=int, default=8050, help="Dash port (default: 8050)")
    return p.parse_args()


def main():
    args = parse_args()
    sym_cfg = load_symbols_config(args.symbols_config)
    src = TelemetrySource()

    if args.demo:
        src.start(demo_reader)
    elif args.stdin:
        src.start(stdin_reader)
    elif args.port:
        src.start(lambda s: serial_reader(s, args.port, args.baud))
    else:
        sys.exit("error: must pass one of --port, --stdin, or --demo")

    app = build_app(src, sym_cfg, poll_hz=args.poll_hz)
    print(f"\n  Dashboard URL:  http://{args.host}:{args.http_port}/", flush=True)
    print(
        "  (Robinhood-style card grid from dashboard.py — not board_b_dashboard.py)\n",
        flush=True,
    )
    app.run(host=args.host, port=args.http_port, debug=False)


if __name__ == "__main__":
    main()
