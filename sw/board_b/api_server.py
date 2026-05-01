#!/usr/bin/env python3
"""
api_server.py — HTTP / SSE dashboard server for Board B.

Polls the AXI-Lite register window in a background thread, maintains a
live snapshot + ring buffer of recent samples, and serves both a JSON
REST API and an embedded "Robinhood-style" HTML dashboard.

Endpoints
---------
GET  /                           Embedded dashboard (HTML + JS)
GET  /api/portfolio              Cash, position value, total account, total P&L, return %
GET  /api/snapshot               Full current state (counters, per-symbol arrays, latency)
GET  /api/history?seconds=120    Time-series arrays (ts, account_cash, position_value,
                                 total_account, total_pnl) for plotting
GET  /api/config                 Read writable config registers
POST /api/config  {json body}    Update writable config (any subset of keys)
POST /api/control/start          Pulse CTRL[0] (start the trader FSM)
POST /api/control/reset          Pulse CTRL[1] (reset the trader FSM + counters)
GET  /api/stream                 Server-Sent Events stream (1 Hz push of /api/portfolio)

Run on Board B PYNQ
-------------------
  sudo python3 api_server.py --initial-cash 1000000 --port 8080

The dashboard will be available at http://<board_b_ip>:8080/.

Run on a laptop (no PYNQ board) for development
------------------------------------------------
  python3 api_server.py --mock --port 8080

Mock mode generates a plausible synthetic feed so the dashboard / API
behaviour can be exercised without hardware.

Key concept — initial cash
--------------------------
The RTL `cash` register starts at 0 and tracks **cash flow** (negative
for buys, positive for sells). To present a familiar "starting balance"
view, this server adds a Python-side `INITIAL_CASH` constant:

    account_cash    = INITIAL_CASH + cash_register_value
    position_value  = Σ position[i] * mid[i]
    total_account   = account_cash + position_value
    total_pnl       = total_account - INITIAL_CASH
                    = cash_register_value + position_value
    return_pct      = total_pnl / INITIAL_CASH * 100
"""
from __future__ import annotations

import argparse
import json
import math
import random
import threading
import time
from collections import deque
from typing import Any, Dict, List, Optional

from flask import Flask, Response, jsonify, request


# ── Try to import PYNQ + register helpers; fall back gracefully for --mock
try:
    from pynq import Overlay, MMIO  # type: ignore
    _PYNQ_AVAILABLE = True
except Exception:  # pragma: no cover
    Overlay = None  # type: ignore
    MMIO = None  # type: ignore
    _PYNQ_AVAILABLE = False

try:
    from register_map import (
        CTRL, STRATEGY_SEL, THRESHOLD, EMA_ALPHA, BASE_QTY,
        MAX_POSITION, MAX_ORDER_RATE, MAX_LOSS,
        STATUS, QUOTES_RCVD, ORDERS_SENT, FILLS_RCVD, RISK_REJECTS, LINK_ERRORS,
        CASH_LO, CASH_HI,
        HIST_BASE, LAT_MIN, LAT_MAX, LAT_SUM, LAT_COUNT, LAST_LATENCY,
        NUM_SYMBOLS, NUM_HIST_BINS,
        q16_16, cash_q32_16,
    )
    from telemetry_server import decode_status, read_per_symbol, STRATEGY_NAMES
    _REGMAP_AVAILABLE = True
except Exception:
    _REGMAP_AVAILABLE = False
    NUM_SYMBOLS = 16
    NUM_HIST_BINS = 16
    STRATEGY_NAMES = {0: "MEAN_REV", 1: "MOMENTUM", 2: "NN", 3: "AUTO"}


# ─────────────────────────────────────────────────────────────────────────────
# Snapshot polling — produces the canonical dict consumed by every endpoint.
# ─────────────────────────────────────────────────────────────────────────────
class Poller:
    """Background thread that snapshots Board B at `poll_hz` and stores
    the latest state plus a ring buffer of recent samples."""

    def __init__(
        self,
        mmio: Optional[Any],
        initial_cash: float,
        poll_hz: float = 5.0,
        history_seconds: float = 600.0,
        mock: bool = False,
    ) -> None:
        self.mmio = mmio
        self.initial_cash = initial_cash
        self.interval = 1.0 / max(poll_hz, 0.1)
        self.mock = mock

        max_samples = max(60, int(history_seconds * poll_hz))
        self.history: deque = deque(maxlen=max_samples)
        self.snapshot: Dict[str, Any] = {}
        self._lock = threading.Lock()
        self._stop = threading.Event()
        self._thread = threading.Thread(target=self._run, daemon=True)

        # Mock state — used when --mock is set
        self._mock_state = {
            "t0": time.time(),
            "pos": [0] * NUM_SYMBOLS,
            "cash_raw": 0.0,                 # cash flow only
            "trades": [0] * NUM_SYMBOLS,
            "mid_base": [50.0 + 12.0 * i for i in range(NUM_SYMBOLS)],
            "ema": [50.0 + 12.0 * i for i in range(NUM_SYMBOLS)],
            "last_fill": [0.0] * NUM_SYMBOLS,
            "last_signal": [0] * NUM_SYMBOLS,
            "qrcvd": 0, "osent": 0, "frcvd": 0, "rej": 0, "lerr": 0,
            "lat_min": 47, "lat_max": 89, "lat_sum": 0, "lat_cnt": 0, "lat_last": 0,
            "hist": [0] * NUM_HIST_BINS,
        }

    def start(self) -> None:
        self._thread.start()

    def stop(self) -> None:
        self._stop.set()

    # ── Polling loop ────────────────────────────────────────────────────────
    def _run(self) -> None:
        next_t = time.time()
        while not self._stop.is_set():
            try:
                snap = self._mock_snapshot() if self.mock else self._real_snapshot()
                with self._lock:
                    self.snapshot = snap
                    self.history.append(snap)
            except Exception as e:  # never let a transient AXI hiccup kill the poller
                with self._lock:
                    self.snapshot = {**self.snapshot, "error": str(e), "ts": time.time()}
            next_t += self.interval
            sleep = next_t - time.time()
            if sleep > 0:
                time.sleep(sleep)
            else:
                next_t = time.time()  # we fell behind, resync

    # ── Hardware path ───────────────────────────────────────────────────────
    def _real_snapshot(self) -> Dict[str, Any]:
        mm = self.mmio
        st = decode_status(mm.read(STATUS))
        cash_raw = cash_q32_16(mm.read(CASH_LO), mm.read(CASH_HI))
        psd = read_per_symbol(mm)

        position_value = sum(psd["pos_value"])
        account_cash   = self.initial_cash + cash_raw
        total_account  = account_cash + position_value
        total_pnl      = cash_raw + position_value     # = total_account - initial_cash
        return_pct     = (total_pnl / self.initial_cash * 100.0) if self.initial_cash else 0.0

        return {
            "ts":              round(time.time(), 3),
            # Status
            "state":           st["fsm_state"],
            "link_up":         st["link_up"],
            "risk_halt":       st["risk_halt"],
            "strategy":        st["strategy"],
            # Counters
            "quotes_rcvd":     mm.read(QUOTES_RCVD),
            "orders_sent":     mm.read(ORDERS_SENT),
            "fills_rcvd":      mm.read(FILLS_RCVD),
            "risk_rejects":    mm.read(RISK_REJECTS),
            "link_errors":     mm.read(LINK_ERRORS),
            # Money — the headline numbers
            "initial_cash":    self.initial_cash,
            "cash_raw":        round(cash_raw, 4),
            "account_cash":    round(account_cash, 4),
            "position_value":  round(position_value, 4),
            "total_account":   round(total_account, 4),
            "total_pnl":       round(total_pnl, 4),
            "return_pct":      round(return_pct, 4),
            # Per-symbol
            "pos":             psd["pos"],
            "bid":             [round(v, 4) for v in psd["bid"]],
            "ask":             [round(v, 4) for v in psd["ask"]],
            "mid":             [round(v, 4) for v in psd["mid"]],
            "spread":          [round(v, 4) for v in psd["spread"]],
            "ema":             [round(v, 4) for v in psd["ema"]],
            "pnl_cash":        [round(v, 4) for v in psd["pnl_cash"]],
            "pnl_mtm":         [round(v, 4) for v in psd["pnl_mtm"]],
            "pos_value":       [round(v, 4) for v in psd["pos_value"]],
            "last_fill":       [round(v, 4) for v in psd["last_fill"]],
            "trades":          psd["trades"],
            "last_signal":     psd["last_signal"],
            "last_signal_label": psd["last_signal_label"],
            # Latency
            "hist":            [mm.read(HIST_BASE + i * 4) for i in range(NUM_HIST_BINS)],
            "lat_min":         mm.read(LAT_MIN),
            "lat_max":         mm.read(LAT_MAX),
            "lat_sum":         mm.read(LAT_SUM),
            "lat_count":       mm.read(LAT_COUNT),
            "lat_last":        mm.read(LAST_LATENCY),
        }

    # ── Mock path ───────────────────────────────────────────────────────────
    def _mock_snapshot(self) -> Dict[str, Any]:
        m = self._mock_state
        t = time.time() - m["t0"]

        # Diffuse mid prices with a tiny mean-reverting walk
        mid: List[float] = []
        ema: List[float] = []
        bid: List[float] = []
        ask: List[float] = []
        for i in range(NUM_SYMBOLS):
            base = m["mid_base"][i]
            walk = (random.random() - 0.5) * 0.04 * base
            new_mid = max(0.01, base + 0.5 * math.sin(t * 0.3 + i) + walk)
            m["mid_base"][i] = m["mid_base"][i] * 0.95 + new_mid * 0.05  # leak toward fresh
            mid.append(round(new_mid, 4))
            m["ema"][i] = m["ema"][i] * 0.98 + new_mid * 0.02
            ema.append(round(m["ema"][i], 4))
            spr = max(0.02, 0.01 * new_mid)
            bid.append(round(new_mid - spr / 2, 4))
            ask.append(round(new_mid + spr / 2, 4))

        # Occasionally execute fake trades
        signals = [0] * NUM_SYMBOLS
        for _ in range(random.randint(0, 2)):
            i = random.randrange(NUM_SYMBOLS)
            side = random.choice([+1, -1])  # +1 = BUY, -1 = SELL
            qty = 100
            px = ask[i] if side > 0 else bid[i]
            m["pos"][i] += side * qty
            m["cash_raw"] -= side * qty * px
            m["trades"][i] += 1
            m["last_fill"][i] = px
            m["frcvd"] += 1
            m["osent"] += 1
            signals[i] = 1 if side > 0 else 2
        m["qrcvd"] += random.randint(40, 60)

        pos_value = sum(p * mi for p, mi in zip(m["pos"], mid))
        cash_raw = m["cash_raw"]
        account_cash = self.initial_cash + cash_raw
        total_account = account_cash + pos_value
        total_pnl = cash_raw + pos_value
        return_pct = total_pnl / self.initial_cash * 100.0 if self.initial_cash else 0.0

        last_sig_labels = ["NONE", "BUY", "SELL", "RISK_BLOCKED"]
        return {
            "ts": round(time.time(), 3),
            "state": "B_TRADING", "link_up": True, "risk_halt": False, "strategy": "MEAN_REV",
            "quotes_rcvd": m["qrcvd"], "orders_sent": m["osent"], "fills_rcvd": m["frcvd"],
            "risk_rejects": m["rej"], "link_errors": m["lerr"],
            "initial_cash": self.initial_cash,
            "cash_raw": round(cash_raw, 4),
            "account_cash": round(account_cash, 4),
            "position_value": round(pos_value, 4),
            "total_account": round(total_account, 4),
            "total_pnl": round(total_pnl, 4),
            "return_pct": round(return_pct, 4),
            "pos": list(m["pos"]),
            "bid": bid, "ask": ask, "mid": mid, "ema": ema,
            "spread": [round(a - b, 4) for a, b in zip(ask, bid)],
            "pnl_cash": [0.0] * NUM_SYMBOLS,
            "pnl_mtm": [round(p * mi, 4) for p, mi in zip(m["pos"], mid)],
            "pos_value": [round(p * mi, 4) for p, mi in zip(m["pos"], mid)],
            "last_fill": list(m["last_fill"]),
            "trades": list(m["trades"]),
            "last_signal": signals,
            "last_signal_label": [last_sig_labels[s] for s in signals],
            "hist": [random.randint(0, 50) for _ in range(NUM_HIST_BINS)],
            "lat_min": 47, "lat_max": 89, "lat_sum": m["lat_sum"], "lat_count": m["lat_cnt"],
            "lat_last": random.randint(40, 95),
        }

    # ── API helpers ─────────────────────────────────────────────────────────
    def get_snapshot(self) -> Dict[str, Any]:
        with self._lock:
            return dict(self.snapshot)

    def get_history(self, seconds: float) -> Dict[str, List[float]]:
        cutoff = time.time() - seconds
        with self._lock:
            samples = [s for s in self.history if s.get("ts", 0) >= cutoff]
        return {
            "ts":              [s["ts"]            for s in samples],
            "account_cash":    [s["account_cash"]  for s in samples],
            "position_value":  [s["position_value"] for s in samples],
            "total_account":   [s["total_account"] for s in samples],
            "total_pnl":       [s["total_pnl"]     for s in samples],
            "cash_raw":        [s["cash_raw"]      for s in samples],
        }


# ─────────────────────────────────────────────────────────────────────────────
# Flask app
# ─────────────────────────────────────────────────────────────────────────────
def make_app(poller: Poller, mmio: Optional[Any], mock: bool) -> Flask:
    app = Flask(__name__)

    @app.after_request
    def _cors(resp):  # allow Jupyter / laptop dashboards from any origin
        resp.headers["Access-Control-Allow-Origin"] = "*"
        resp.headers["Access-Control-Allow-Methods"] = "GET, POST, OPTIONS"
        resp.headers["Access-Control-Allow-Headers"] = "Content-Type"
        return resp

    @app.route("/")
    def index():
        return Response(_DASHBOARD_HTML, mimetype="text/html")

    @app.route("/api/snapshot")
    def snapshot():
        return jsonify(poller.get_snapshot())

    @app.route("/api/portfolio")
    def portfolio():
        s = poller.get_snapshot()
        if not s:
            return jsonify({"error": "no snapshot yet"}), 503
        # Top-N symbols by absolute position
        per_sym = []
        for i in range(NUM_SYMBOLS):
            if s["pos"][i] == 0 and s["trades"][i] == 0:
                continue
            per_sym.append({
                "i": i,
                "pos":         s["pos"][i],
                "mid":         s["mid"][i],
                "last_fill":   s["last_fill"][i],
                "pnl_mtm":     s["pnl_mtm"][i],
                "pos_value":   s["pos_value"][i],
                "trades":      s["trades"][i],
                "last_signal": s["last_signal_label"][i],
            })
        return jsonify({
            "ts":              s["ts"],
            "initial_cash":    s["initial_cash"],
            "account_cash":    s["account_cash"],
            "position_value":  s["position_value"],
            "total_account":   s["total_account"],
            "total_pnl":       s["total_pnl"],
            "return_pct":      s["return_pct"],
            "fills_rcvd":      s["fills_rcvd"],
            "orders_sent":     s["orders_sent"],
            "risk_rejects":    s["risk_rejects"],
            "state":           s["state"],
            "link_up":         s["link_up"],
            "risk_halt":       s["risk_halt"],
            "strategy":        s["strategy"],
            "per_symbol":      per_sym,
        })

    @app.route("/api/history")
    def history():
        seconds = float(request.args.get("seconds", "120"))
        return jsonify(poller.get_history(seconds))

    @app.route("/api/config", methods=["GET"])
    def get_config():
        if mock or not _REGMAP_AVAILABLE or mmio is None:
            return jsonify({"mock": True, "msg": "config endpoint disabled in mock mode"})
        return jsonify({
            "strategy":       mmio.read(STRATEGY_SEL),
            "threshold":      mmio.read(THRESHOLD) / 65536.0,
            "ema_alpha":      mmio.read(EMA_ALPHA),
            "base_qty":       mmio.read(BASE_QTY),
            "max_position":   mmio.read(MAX_POSITION),
            "max_order_rate": mmio.read(MAX_ORDER_RATE),
            "max_loss":       mmio.read(MAX_LOSS),
        })

    @app.route("/api/config", methods=["POST"])
    def set_config():
        if mock or not _REGMAP_AVAILABLE or mmio is None:
            return jsonify({"error": "mock mode — write disabled"}), 400
        body = request.get_json(force=True) or {}
        wrote = {}
        # Whitelist of keys → (axi addr, value transform)
        whitelist = {
            "strategy":       (STRATEGY_SEL,   lambda v: int(v) & 0x3),
            "threshold":      (THRESHOLD,      lambda v: q16_16(float(v))),
            "ema_alpha":      (EMA_ALPHA,      lambda v: int(v) & 0xFFFF),
            "base_qty":       (BASE_QTY,       lambda v: int(v) & 0xFFFF),
            "max_position":   (MAX_POSITION,   lambda v: int(v)),
            "max_order_rate": (MAX_ORDER_RATE, lambda v: int(v)),
            "max_loss":       (MAX_LOSS,       lambda v: int(v)),
        }
        for k, v in body.items():
            if k not in whitelist:
                continue
            addr, xform = whitelist[k]
            try:
                raw = xform(v)
                mmio.write(addr, raw)
                wrote[k] = raw
            except Exception as e:
                return jsonify({"error": f"bad value for {k}: {e}"}), 400
        return jsonify({"ok": True, "wrote": wrote})

    @app.route("/api/control/start", methods=["POST"])
    def ctrl_start():
        if mock or not _REGMAP_AVAILABLE or mmio is None:
            return jsonify({"mock": True})
        mmio.write(CTRL, 0x01)
        return jsonify({"ok": True})

    @app.route("/api/control/reset", methods=["POST"])
    def ctrl_reset():
        if mock or not _REGMAP_AVAILABLE or mmio is None:
            return jsonify({"mock": True})
        mmio.write(CTRL, 0x02)
        return jsonify({"ok": True})

    @app.route("/api/stream")
    def stream():
        """Server-Sent Events: 1 Hz portfolio push for live UI."""
        def gen():
            last_ts = 0.0
            while True:
                snap = poller.get_snapshot()
                ts = snap.get("ts", 0)
                if ts != last_ts:
                    payload = {
                        "ts":             ts,
                        "account_cash":   snap.get("account_cash"),
                        "position_value": snap.get("position_value"),
                        "total_account":  snap.get("total_account"),
                        "total_pnl":      snap.get("total_pnl"),
                        "return_pct":     snap.get("return_pct"),
                        "state":          snap.get("state"),
                        "link_up":        snap.get("link_up"),
                        "risk_halt":      snap.get("risk_halt"),
                    }
                    yield f"data: {json.dumps(payload)}\n\n"
                    last_ts = ts
                time.sleep(1.0)
        return Response(gen(), mimetype="text/event-stream")

    return app


# ─────────────────────────────────────────────────────────────────────────────
# Embedded dashboard (Robinhood-style)
# ─────────────────────────────────────────────────────────────────────────────
_DASHBOARD_HTML = r"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8" />
<title>Board B — Dual-FPGA Trading Engine</title>
<meta name="viewport" content="width=device-width,initial-scale=1" />
<style>
  :root {
    --bg: #0a0e0a; --panel: #131a13; --border: #233323;
    --text: #e8f0e8; --muted: #8aa08a;
    --green: #00c805; --red: #ff5000; --yellow: #ffcc00; --blue: #59b9ff;
    --mono: ui-monospace, "JetBrains Mono", Menlo, Consolas, monospace;
  }
  * { box-sizing: border-box; }
  body { background: var(--bg); color: var(--text); font-family: system-ui, sans-serif;
         margin: 0; padding: 24px; }
  h1 { font-size: 14px; letter-spacing: 2px; color: var(--muted); font-weight: 600;
       text-transform: uppercase; margin: 0 0 24px; }
  .pnl-banner { padding: 28px; border: 1px solid var(--border); border-radius: 12px;
                background: var(--panel); margin-bottom: 24px; }
  .pnl-banner .total { font-size: 56px; font-weight: 700; font-family: var(--mono);
                       letter-spacing: -1px; }
  .pnl-banner .pl { font-size: 22px; margin-top: 8px; font-family: var(--mono); }
  .green { color: var(--green); }
  .red { color: var(--red); }
  .grid { display: grid; grid-template-columns: 1fr 1fr; gap: 16px; }
  .panel { padding: 18px; border: 1px solid var(--border); border-radius: 10px;
           background: var(--panel); }
  .panel h2 { margin: 0 0 12px; font-size: 12px; letter-spacing: 1.5px;
              color: var(--muted); text-transform: uppercase; }
  .kv { display: flex; justify-content: space-between; margin: 6px 0;
        font-family: var(--mono); font-size: 14px; }
  .kv .k { color: var(--muted); }
  table { width: 100%; border-collapse: collapse; font-family: var(--mono); font-size: 13px; }
  th, td { padding: 8px 6px; text-align: right; }
  th { color: var(--muted); font-weight: 500; border-bottom: 1px solid var(--border);
       font-size: 11px; letter-spacing: 1px; text-transform: uppercase; }
  td { border-bottom: 1px solid #1c281c; }
  tr:hover td { background: #1a221a; }
  td.sym { text-align: left; color: var(--muted); }
  .pill { display: inline-block; padding: 2px 8px; border-radius: 999px;
          font-size: 11px; font-weight: 600; letter-spacing: 0.5px; }
  .pill.green { background: rgba(0,200,5,0.15);   color: var(--green); }
  .pill.red   { background: rgba(255,80,0,0.15);  color: var(--red); }
  .pill.gray  { background: rgba(138,160,138,0.15); color: var(--muted); }
  .pill.yellow{ background: rgba(255,204,0,0.15); color: var(--yellow); }
  #spark { width: 100%; height: 80px; }
  .row { display: flex; gap: 24px; align-items: baseline; }
  .badge { font-size: 11px; padding: 3px 8px; border-radius: 4px;
           background: #1c281c; color: var(--muted); font-family: var(--mono); }
  .badge.live { color: var(--green); border: 1px solid rgba(0,200,5,0.3); }
</style>
</head>
<body>
  <h1>Board B · Dual-FPGA Trading Engine
      <span class="badge live" id="liveTag">● LIVE</span>
      <span class="badge" id="state">—</span>
      <span class="badge" id="strat">—</span>
  </h1>

  <div class="pnl-banner">
    <div style="color:var(--muted);font-size:11px;letter-spacing:1px;text-transform:uppercase">
      Total Account Value
    </div>
    <div class="total" id="totalAccount">$—</div>
    <div class="pl" id="totalPnl">—</div>
    <canvas id="spark"></canvas>
  </div>

  <div class="grid">
    <div class="panel">
      <h2>Cash & Holdings</h2>
      <div class="kv"><span class="k">Initial cash</span>     <span id="initCash">—</span></div>
      <div class="kv"><span class="k">Account cash</span>     <span id="acctCash">—</span></div>
      <div class="kv"><span class="k">Position value (MTM)</span> <span id="posVal">—</span></div>
      <div class="kv"><span class="k">Total account</span>    <span id="totAcct">—</span></div>
      <div class="kv"><span class="k">Return</span>           <span id="retPct">—</span></div>
    </div>

    <div class="panel">
      <h2>Activity</h2>
      <div class="kv"><span class="k">Quotes received</span> <span id="qrcvd">—</span></div>
      <div class="kv"><span class="k">Orders sent</span>     <span id="osent">—</span></div>
      <div class="kv"><span class="k">Fills received</span>  <span id="frcvd">—</span></div>
      <div class="kv"><span class="k">Risk rejects</span>    <span id="rrej">—</span></div>
      <div class="kv"><span class="k">Link errors</span>     <span id="lerr">—</span></div>
      <div class="kv"><span class="k">Latency (last)</span>  <span id="latLast">—</span></div>
    </div>
  </div>

  <div class="panel" style="margin-top:16px">
    <h2>Positions</h2>
    <table id="posTable">
      <thead><tr>
        <th class="sym" style="text-align:left">Symbol</th>
        <th>Position</th><th>Mid</th><th>Last fill</th>
        <th>Pos value</th><th>P&amp;L (MTM)</th><th>Trades</th><th>Last signal</th>
      </tr></thead>
      <tbody></tbody>
    </table>
  </div>

<script>
const $  = (id) => document.getElementById(id);
const fmt$ = (v) => (v == null) ? '—' :
  (v < 0 ? '-$' : '$') + Math.abs(v).toLocaleString(undefined,
    {minimumFractionDigits:2, maximumFractionDigits:2});
const fmtPct = (v) => (v == null) ? '—' : (v >= 0 ? '+' : '') + v.toFixed(2) + '%';
const sign = (v) => (v == null) ? '' : (v >= 0 ? 'green' : 'red');
const sigPillClass = (s) => ({BUY:'green', SELL:'red', RISK_BLOCKED:'yellow'})[s] || 'gray';

const sparkData = [];

async function refresh() {
  let p, snap;
  try {
    [p, snap] = await Promise.all([
      fetch('/api/portfolio').then(r => r.json()),
      fetch('/api/snapshot').then(r => r.json()),
    ]);
  } catch (e) { console.error(e); return; }

  // Banner
  $('totalAccount').textContent = fmt$(p.total_account);
  $('totalPnl').textContent = fmt$(p.total_pnl) + '   ' + fmtPct(p.return_pct);
  $('totalPnl').className = 'pl ' + sign(p.total_pnl);
  $('state').textContent = p.state || '—';
  $('strat').textContent = p.strategy || '—';
  $('liveTag').className = 'badge live' + (p.link_up ? '' : ' red');

  // Cash & Holdings
  $('initCash').textContent = fmt$(p.initial_cash);
  $('acctCash').textContent = fmt$(p.account_cash);
  $('posVal').textContent   = fmt$(p.position_value);
  $('totAcct').textContent  = fmt$(p.total_account);
  $('retPct').textContent   = fmtPct(p.return_pct);
  $('retPct').className     = sign(p.total_pnl);

  // Activity
  $('qrcvd').textContent = p.fills_rcvd != null ? snap.quotes_rcvd : '—';
  $('osent').textContent = p.orders_sent;
  $('frcvd').textContent = p.fills_rcvd;
  $('rrej').textContent  = p.risk_rejects;
  $('lerr').textContent  = snap.link_errors;
  $('latLast').textContent = snap.lat_last != null ? snap.lat_last + ' cyc (' +
                              (snap.lat_last * 20).toLocaleString() + ' ns)' : '—';

  // Positions table
  const tbody = $('posTable').getElementsByTagName('tbody')[0];
  tbody.innerHTML = '';
  for (const r of (p.per_symbol || [])) {
    const tr = document.createElement('tr');
    tr.innerHTML = `
      <td class="sym">SYM_${String(r.i).padStart(2,'0')}</td>
      <td class="${r.pos>=0?'green':'red'}">${r.pos>=0?'+':''}${r.pos}</td>
      <td>${fmt$(r.mid)}</td>
      <td>${fmt$(r.last_fill)}</td>
      <td>${fmt$(r.pos_value)}</td>
      <td class="${sign(r.pnl_mtm)}">${fmt$(r.pnl_mtm)}</td>
      <td>${r.trades}</td>
      <td><span class="pill ${sigPillClass(r.last_signal)}">${r.last_signal}</span></td>`;
    tbody.appendChild(tr);
  }

  // Spark line
  sparkData.push(p.total_account);
  if (sparkData.length > 240) sparkData.shift();
  drawSpark();
}

function drawSpark() {
  const c = $('spark'); const ctx = c.getContext('2d');
  const w = c.width = c.clientWidth, h = c.height = c.clientHeight;
  ctx.clearRect(0,0,w,h);
  if (sparkData.length < 2) return;
  const lo = Math.min(...sparkData), hi = Math.max(...sparkData);
  const span = (hi - lo) || 1;
  ctx.beginPath();
  sparkData.forEach((v, i) => {
    const x = (i / (sparkData.length - 1)) * w;
    const y = h - ((v - lo) / span) * (h - 8) - 4;
    i === 0 ? ctx.moveTo(x, y) : ctx.lineTo(x, y);
  });
  const last = sparkData[sparkData.length-1], first = sparkData[0];
  ctx.strokeStyle = (last >= first) ? '#00c805' : '#ff5000';
  ctx.lineWidth = 2;
  ctx.stroke();
}

refresh();
setInterval(refresh, 1000);
</script>
</body></html>
"""


# ─────────────────────────────────────────────────────────────────────────────
# CLI
# ─────────────────────────────────────────────────────────────────────────────
def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Board B HTTP/SSE dashboard server")
    p.add_argument("--initial-cash", type=float, default=1_000_000.0,
                   help="Synthetic starting cash (USD). Default: $1,000,000.")
    p.add_argument("--port", type=int, default=8080)
    p.add_argument("--host", type=str, default="0.0.0.0")
    p.add_argument("--poll-hz", type=float, default=5.0,
                   help="AXI snapshot rate. Default: 5 Hz.")
    p.add_argument("--history-seconds", type=float, default=600.0,
                   help="In-memory time-series window. Default: 600 s.")
    p.add_argument("--overlay", type=str, default="overlays/board_b.bit",
                   help="Path to the Board B overlay bitstream.")
    p.add_argument("--ip-block", type=str, default="hft_core",
                   help="IP block name in the overlay for MMIO.")
    p.add_argument("--mock", action="store_true",
                   help="Generate synthetic data (no PYNQ board needed).")
    return p.parse_args()


def main() -> None:
    args = parse_args()
    mmio = None

    if args.mock:
        print("[api_server] MOCK MODE — generating synthetic feed")
    else:
        if not (_PYNQ_AVAILABLE and _REGMAP_AVAILABLE):
            raise SystemExit(
                "pynq / register_map import failed. Run with --mock for laptop dev "
                "or run on a PYNQ board with the Board B overlay installed."
            )
        ol = Overlay(args.overlay)
        mmio = MMIO(ol.ip_dict[args.ip_block]['phys_addr'],
                    ol.ip_dict[args.ip_block]['addr_range'])
        print(f"[api_server] Loaded overlay {args.overlay}, MMIO at "
              f"0x{ol.ip_dict[args.ip_block]['phys_addr']:08X}")

    poller = Poller(
        mmio=mmio,
        initial_cash=args.initial_cash,
        poll_hz=args.poll_hz,
        history_seconds=args.history_seconds,
        mock=args.mock,
    )
    poller.start()

    app = make_app(poller, mmio, args.mock)
    print(f"[api_server] Listening on http://{args.host}:{args.port}/  "
          f"(initial_cash=${args.initial_cash:,.2f})")
    # threaded=True is essential — the SSE stream holds a request indefinitely.
    app.run(host=args.host, port=args.port, threaded=True, use_reloader=False)


if __name__ == "__main__":
    main()
