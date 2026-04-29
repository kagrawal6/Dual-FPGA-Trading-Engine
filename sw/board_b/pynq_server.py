#!/usr/bin/env python3
"""
Board B PYNQ HTTP server — runs ON the Board B PYNQ (same idea as repo-root pynq_server.py for Board A).

Reads **real** Board B AXI registers (no simulated prices / no random telemetry) and:
  - Serves JSON at GET /api/telemetry  (same shape as telemetry_server.py UART lines + cash_lo/cash_hi)
  - Serves a ring buffer at GET /api/history  for simple charts
  - Serves a minimal browser UI at GET /  (profit, cash, counters, live charts)

Upload the whole ``sw/board_b/`` directory (needs ``register_map.py``, ``telemetry_server.py``) then:

    cd ~/Dual-FPGA-Trading-Engine/sw/board_b   # your path on the board
    python3 pynq_server.py

Or without configuring the trader (already running):

    python3 pynq_server.py --no-configure

Then open in a browser:  http://<board-b-ip>:8090/
"""

from __future__ import annotations

import argparse
import json
import threading
import time
from collections import deque
from http.server import BaseHTTPRequestHandler, HTTPServer
from typing import Any, Deque, Dict

# PYNQ / telemetry imports are deferred so `python3 pynq_server.py --help` works on a laptop.

SYMBOL_NAMES = [
    "AAPL", "MSFT", "GOOG", "META", "NVDA", "AMD", "INTC", "AVGO",
    "AMZN", "TSLA", "JPM", "GS", "JNJ", "PFE", "XOM", "CVX",
]

_lock = threading.Lock()
_latest: Dict[str, Any] = {}
_history: Deque[Dict[str, Any]] = deque(maxlen=600)  # ~30 s @ 20 Hz


def _poll_loop(mmio: Any, hz: float) -> None:
    from telemetry_server import read_telemetry_snapshot

    global _latest
    interval = 1.0 / max(hz, 0.25)
    while True:
        try:
            snap = read_telemetry_snapshot(mmio)
            pt = {
                "t": snap["ts"],
                "cash": snap["cash"],
                "total_pnl": snap["total_pnl"],
                "port_value": snap["port_value"],
                "qps": snap["qps"],
                "ops": snap["ops"],
                "fps": snap["fps"],
                "rej": snap["rej"],
            }
            with _lock:
                _latest = snap
                _history.append(pt)
        except Exception as ex:  # pragma: no cover
            with _lock:
                _latest = {"error": str(ex), "ts": time.time()}
        time.sleep(interval)


def _configure(mmio: Any, args: argparse.Namespace) -> None:
    from register_map import (
        CTRL,
        STRATEGY_SEL,
        THRESHOLD,
        EMA_ALPHA,
        BASE_QTY,
        MAX_POSITION,
        MAX_ORDER_RATE,
        MAX_LOSS,
        q16_16,
    )

    if args.reset:
        mmio.write(CTRL, 0x02)
    mmio.write(STRATEGY_SEL, args.strategy)
    mmio.write(THRESHOLD, q16_16(args.threshold))
    mmio.write(EMA_ALPHA, args.ema_alpha)
    mmio.write(BASE_QTY, args.base_qty)
    mmio.write(MAX_POSITION, args.max_position)
    mmio.write(MAX_ORDER_RATE, args.max_order_rate)
    mmio.write(MAX_LOSS, args.max_loss)
    if not args.no_start:
        mmio.write(CTRL, 0x01)


_HTML_TEMPLATE = """<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8"/>
  <meta name="viewport" content="width=device-width, initial-scale=1"/>
  <title>Board B — Live</title>
  <script src="https://cdn.jsdelivr.net/npm/chart.js@4.4.1/dist/chart.umd.min.js"></script>
  <style>
    :root { --bg:#000; --card:#1c1c1e; --txt:#fff; --muted:#a1a1a6; --up:#00c805; --down:#ff331f; --line:#5ac8fa; }
    body { font-family: system-ui, -apple-system, sans-serif; background: var(--bg); color: var(--txt); margin:0; padding:16px; }
    h1 { font-size: 1.25rem; font-weight: 700; margin: 0 0 16px; }
    .grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(140px,1fr)); gap: 12px; margin-bottom: 20px; }
    .card { background: var(--card); border-radius: 16px; padding: 14px 16px; border: 1px solid #2c2c2e; }
    .card label { display:block; font-size: 11px; color: var(--muted); text-transform: uppercase; letter-spacing: .06em; margin-bottom: 4px; }
    .card .v { font-size: 1.35rem; font-weight: 700; font-variant-numeric: tabular-nums; }
    .pos { color: var(--up); } .neg { color: var(--down); }
    .row { display: flex; flex-wrap: wrap; gap: 16px; align-items: flex-start; }
    .chart-box { flex: 1 1 360px; min-height: 280px; background: var(--card); border-radius: 16px; padding: 12px; border: 1px solid #2c2c2e; }
    table { width: 100%; border-collapse: collapse; font-size: 13px; }
    th, td { text-align: left; padding: 6px 8px; border-bottom: 1px solid #2c2c2e; }
    th { color: var(--muted); font-weight: 600; font-size: 11px; text-transform: uppercase; }
    .pill { display:inline-block; padding: 4px 10px; border-radius: 999px; font-size: 12px; font-weight: 600; background:#2c2c2e; }
  </style>
</head>
<body>
  <h1>Board B — hardware telemetry</h1>
  <div class="grid" id="cards"></div>
  <div class="row">
    <div class="chart-box"><canvas id="chMain"></canvas></div>
    <div class="chart-box" style="flex:0 1 320px"><canvas id="chRates"></canvas></div>
  </div>
  <h2 style="font-size:14px; color:var(--muted); margin:24px 0 8px;">Per-symbol (from Board B book)</h2>
  <div class="card" style="max-width:920px"><table id="sym"><thead><tr>
    <th>Sym</th><th>Mid</th><th>Pos</th><th>PnL MTM</th><th>Trades</th>
  </tr></thead><tbody></tbody></table></div>
  <p style="color:var(--muted); font-size:12px; margin-top:20px;">
    Data source: <code>/api/telemetry</code> — same AXI reads as <code>telemetry_server.py</code>. No random generation.
  </p>
<script>
const fmt = (n, d=2) => (n==null||isNaN(n)) ? "—" : Number(n).toLocaleString(undefined,{maximumFractionDigits:d});
const money = (n) => {
  if (n==null||isNaN(n)) return "—";
  const s = (n>=0?"+":"") + "$" + Math.abs(n).toFixed(2);
  return s;
};
let chartMain, chartRates;
function initCharts() {
  const common = { responsive:true, maintainAspectRatio:false,
    plugins:{ legend:{ labels:{ color:"#a1a1a6" } } },
    scales: {
      x: { ticks:{ color:"#a1a1a6", maxTicksLimit:8 }, grid:{ color:"#2c2c2e" } },
      y: { ticks:{ color:"#a1a1a6" }, grid:{ color:"#2c2c2e" } }
    } };
  chartMain = new Chart(document.getElementById("chMain"), {
    type: "line",
    data: { labels: [], datasets: [
      { label: "Cash (USD)", data: [], borderColor:"#00c805", tension:0.15, pointRadius:0 },
      { label: "Total PnL MTM", data: [], borderColor:"#5ac8fa", tension:0.15, pointRadius:0 },
      { label: "Port value", data: [], borderColor:"#ffb020", tension:0.15, pointRadius:0 }
    ]},
    options: { ...common, plugins:{ title:{ display:true, text:"Profit & portfolio (live)", color:"#fff" } } }
  });
  chartRates = new Chart(document.getElementById("chRates"), {
    type: "bar",
    data: { labels:["Quotes","Orders","Fills","Rej"], datasets:[{ data:[0,0,0,0],
      backgroundColor:["#6b6b6b","#5ac8fa","#00c805","#ff331f"] }]},
    options: { ...common, plugins:{ title:{ display:true, text:"Cumulative counters", color:"#fff" } } }
  });
}
function setCards(j) {
  const g = document.getElementById("cards");
  const risk = j.risk_halt ? "HALT" : "OK";
  const link = j.link_up ? "UP" : "DOWN";
  const haltCls = j.risk_halt ? "neg" : "pos";
  g.innerHTML = `
    <div class="card"><label>Cash</label><div class="v ${j.cash>=0?"pos":"neg"}">${money(j.cash)}</div></div>
    <div class="card"><label>Total PnL (MTM)</label><div class="v ${j.total_pnl>=0?"pos":"neg"}">${money(j.total_pnl)}</div></div>
    <div class="card"><label>Port value</label><div class="v">${money(j.port_value)}</div></div>
    <div class="card"><label>FSM</label><div class="v" style="font-size:1rem">${j.state}</div></div>
    <div class="card"><label>Strategy</label><div class="v" style="font-size:1rem">${j.strategy}</div></div>
    <div class="card"><label>Link / Risk</label><div class="v" style="font-size:1rem"><span class="pill">${link}</span> <span class="pill ${haltCls}">${risk}</span></div></div>
    <div class="card"><label>Quotes rcvd</label><div class="v">${fmt(j.qps,0)}</div></div>
    <div class="card"><label>Orders sent</label><div class="v">${fmt(j.ops,0)}</div></div>
    <div class="card"><label>Fills rcvd</label><div class="v">${fmt(j.fps,0)}</div></div>
    <div class="card"><label>Risk rejects</label><div class="v">${fmt(j.rej,0)}</div></div>
  `;
}
function setTable(j) {
  const tb = document.querySelector("#sym tbody");
  tb.innerHTML = "";
  const names = __SYMBOLS_JSON__;
  for (let i = 0; i < names.length; i++) {
    const tr = document.createElement("tr");
    const mid = (j.mid && j.mid[i] != null) ? j.mid[i] : 0;
    const pos = (j.pos && j.pos[i] != null) ? j.pos[i] : 0;
    const pnl = (j.pnl_mtm && j.pnl_mtm[i] != null) ? j.pnl_mtm[i] : 0;
    const trd = (j.trades && j.trades[i] != null) ? j.trades[i] : 0;
    tr.innerHTML = `<td>${names[i]}</td><td>$${fmt(mid,2)}</td><td>${pos}</td><td class="${pnl>=0?"pos":"neg"}">${money(pnl)}</td><td>${trd}</td>`;
    tb.appendChild(tr);
  }
}
function pushHistory(h) {
  const pts = h.points || [];
  const lab = pts.map(p => "");
  chartMain.data.labels = pts.map((p,i)=> i);
  chartMain.data.datasets[0].data = pts.map(p => p.cash);
  chartMain.data.datasets[1].data = pts.map(p => p.total_pnl);
  chartMain.data.datasets[2].data = pts.map(p => p.port_value);
  chartMain.update("none");
}
async function tick() {
  try {
    const [rJ, hJ] = await Promise.all([
      fetch("/api/telemetry").then(r=>r.json()),
      fetch("/api/history").then(r=>r.json())
    ]);
    if (rJ.error) { document.getElementById("cards").innerHTML = `<div class="card neg">Error: ${rJ.error}</div>`; return; }
    setCards(rJ);
    setTable(rJ);
    pushHistory(hJ);
    chartRates.data.datasets[0].data = [rJ.qps, rJ.ops, rJ.fps, rJ.rej];
    chartRates.update("none");
  } catch(e) { console.warn(e); }
}
initCharts();
setInterval(tick, 400);
tick();
</script>
</body>
</html>"""


def _html_dashboard() -> bytes:
    return _HTML_TEMPLATE.replace("__SYMBOLS_JSON__", json.dumps(SYMBOL_NAMES)).encode(
        "utf-8"
    )


class BoardBHandler(BaseHTTPRequestHandler):
    def _cors(self) -> None:
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Cache-Control", "no-store")

    def do_GET(self) -> None:  # pragma: no cover
        path = self.path.split("?", 1)[0].rstrip("/") or "/"
        if path == "/api/telemetry":
            with _lock:
                body = json.dumps(_latest).encode("utf-8")
            self.send_response(200)
            self.send_header("Content-Type", "application/json; charset=utf-8")
            self.send_header("Content-Length", str(len(body)))
            self._cors()
            self.end_headers()
            self.wfile.write(body)
            return
        if path == "/api/history":
            with _lock:
                body = json.dumps({"points": list(_history)}).encode("utf-8")
            self.send_response(200)
            self.send_header("Content-Type", "application/json; charset=utf-8")
            self.send_header("Content-Length", str(len(body)))
            self._cors()
            self.end_headers()
            self.wfile.write(body)
            return
        if path in ("/", "/index.html"):
            body = _html_dashboard()
            self.send_response(200)
            self.send_header("Content-Type", "text/html; charset=utf-8")
            self.send_header("Content-Length", str(len(body)))
            self._cors()
            self.end_headers()
            self.wfile.write(body)
            return
        self.send_response(404)
        self.end_headers()

    def log_message(self, fmt: str, *args: Any) -> None:
        pass


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Board B HTTP telemetry + charts (PYNQ)")
    p.add_argument("--http-port", type=int, default=8090, help="HTTP listen port (default 8090)")
    p.add_argument("--host", default="0.0.0.0", help="Bind address (default all interfaces)")
    p.add_argument("--poll-hz", type=float, default=20.0, help="MMIO poll rate for /api/telemetry")
    p.add_argument("--overlay", type=str, default="overlays/board_b.bit")
    p.add_argument("--ip-block", type=str, default="hft_core")
    p.add_argument("--no-configure", action="store_true", help="Do not write strategy/config or start pulse (read only)")
    p.add_argument("--reset", action="store_true", help="Pulse CTRL reset before configure")
    p.add_argument("--no-start", action="store_true", help="With configure: do not pulse CTRL start")
    p.add_argument("--strategy", type=int, default=0, choices=[0, 1, 2, 3])
    p.add_argument("--threshold", type=float, default=1.0)
    p.add_argument("--ema-alpha", type=int, default=6554)
    p.add_argument("--base-qty", type=int, default=100)
    p.add_argument("--max-position", type=int, default=500)
    p.add_argument("--max-order-rate", type=int, default=1000)
    p.add_argument("--max-loss", type=int, default=100)
    return p.parse_args()


def main(args: argparse.Namespace) -> None:
    try:
        from pynq import MMIO, Overlay
    except ImportError as e:  # pragma: no cover
        raise SystemExit(
            "The 'pynq' package is not available on this machine.\n"
            "  • On your Mac: you can still run  python3 pynq_server.py --help\n"
            "  • To serve telemetry: copy sw/board_b/ onto Board B PYNQ and run this script there."
        ) from e

    ol = Overlay(args.overlay)
    mmio = MMIO(ol.ip_dict[args.ip_block]["phys_addr"], ol.ip_dict[args.ip_block]["addr_range"])
    if not args.no_configure:
        _configure(mmio, args)
        print("Board B configured / started (unless --no-start).")
    else:
        print("Read-only mode (--no-configure): not writing CTRL or config registers.")

    threading.Thread(target=_poll_loop, args=(mmio, args.poll_hz), daemon=True).start()
    time.sleep(0.05)  # one sample before first HTTP hit

    httpd = HTTPServer((args.host, args.http_port), BoardBHandler)
    print(f"Board B HTTP UI:  http://<this-board-ip>:{args.http_port}/")
    print(f"JSON telemetry:   http://<this-board-ip>:{args.http_port}/api/telemetry")
    print("Ctrl+C to stop.")
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\nStopped.")


if __name__ == "__main__":
    main(parse_args())
