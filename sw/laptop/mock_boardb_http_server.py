#!/usr/bin/env python3
"""
Mock Board B HTTP telemetry server (laptop-only).

Why:
  - Lets you iterate on the Board B web UI without a PYNQ board / MMIO.
  - Serves the same endpoints as sw/board_b/pynq_server.py:
      GET /              minimal HTML (optional)
      GET /api/telemetry JSON snapshot (fake but schema-shaped)
      GET /api/history   ring buffer of {t,cash,total_pnl,port_value,qps,ops,fps,rej}

Defaults are **slow / light** (low poll rate, scaled sim time, infrequent browser
refresh, smaller history ring) so you can leave the mock running for a long session.
Speed up with e.g. ``--poll-hz 5 --sim-time-scale 0.25 --ui-poll-ms 800``.

Run (PowerShell):
  cd C:\\ECE554\\Dual-FPGA-Trading-Engine\\sw\\laptop
  python .\\mock_boardb_http_server.py --http-port 8099

Then open:
  http://127.0.0.1:8099/
  http://127.0.0.1:8099/api/telemetry

When you are done with UI work, switch back to the real board server; the JSON shape
is intentionally close to telemetry_server.read_telemetry_snapshot().
"""

from __future__ import annotations

import argparse
import json
import math
import random
import threading
import time
from collections import deque
from http.server import BaseHTTPRequestHandler, HTTPServer
from typing import Any, Deque, Dict, List, Tuple

NUM_SYMBOLS = 16
NUM_HIST_BINS = 16

SYMBOL_NAMES = [
    "AAPL", "MSFT", "GOOG", "META", "NVDA", "AMD", "INTC", "AVGO",
    "AMZN", "TSLA", "JPM", "GS", "JNJ", "PFE", "XOM", "CVX",
]


def _clamp(x: float, lo: float, hi: float) -> float:
    return max(lo, min(hi, x))


def _fake_snapshot(t: float, seed: int) -> Dict[str, Any]:
    rng = random.Random(int(t * 1000) ^ seed)

    # Slowly drifting base prices per symbol.
    mids: List[float] = []
    bids: List[float] = []
    asks: List[float] = []
    spreads: List[float] = []
    emas: List[float] = []
    for i in range(NUM_SYMBOLS):
        base = 30.0 + i * 35.0 + 8.0 * math.sin(t / 12.0 + i)
        spr = 0.04 + 0.02 * (1.0 + math.sin(t / 7.0 + 2 * i))
        mid = base + 0.35 * math.sin(t / 2.2 + i * 0.7) + rng.uniform(-0.08, 0.08)
        bid = mid - spr * 0.5
        ask = mid + spr * 0.5
        ema = mid + 0.25 * math.sin(t / 3.0 + i * 0.35) + rng.uniform(-0.05, 0.05)
        mids.append(round(mid, 4))
        bids.append(round(bid, 4))
        asks.append(round(ask, 4))
        spreads.append(round(ask - bid, 4))
        emas.append(round(ema, 4))

    pos = [int(200 * math.sin(t / 5.0 + i)) + rng.randint(-40, 40) for i in range(NUM_SYMBOLS)]
    pos = [int(_clamp(p, -500, 500)) for p in pos]

    pnl_cash = [round(rng.uniform(-2500.0, 2500.0), 4) for _ in range(NUM_SYMBOLS)]
    pos_value = [round(p * m, 4) for p, m in zip(pos, mids)]
    pnl_mtm = [round(pc + pv, 4) for pc, pv in zip(pnl_cash, pos_value)]

    cash = round(sum(pnl_cash) * -0.02 + 5000 * math.sin(t / 30.0), 4)
    total_pnl = round(sum(pnl_mtm), 4)
    inventory_mtm = round(sum(pos_value), 4)
    port_value = round(cash + inventory_mtm, 4)

    # Fake cumulative counters (monotonic-ish).
    qps = int(1_000_000 + t * 1200.0)
    ops = int(250_000 + t * 18.0 + 10 * math.sin(t))
    fps = int(180_000 + t * 12.0 + 8 * math.cos(t))
    rej = int(50_000 + t * 3.0 + 40 * abs(math.sin(t / 1.5)))

    # last_signal-ish classification (dashboard uses strings)
    signal: List[str] = []
    for i in range(NUM_SYMBOLS):
        dev = mids[i] - emas[i]
        if abs(dev) < 0.02:
            signal.append("NONE")
        elif dev > 0.12:
            signal.append("BUY" if rng.random() < 0.55 else "RISK_BLOCKED")
        elif dev < -0.12:
            signal.append("SELL" if rng.random() < 0.55 else "RISK_BLOCKED")
        else:
            signal.append("RISK_BLOCKED" if rng.random() < 0.25 else "NONE")

    signal_code = []
    for s in signal:
        if s == "BUY":
            signal_code.append(1)
        elif s == "SELL":
            signal_code.append(2)
        elif s == "RISK_BLOCKED":
            signal_code.append(3)
        else:
            signal_code.append(0)

    trades = [max(0, int(abs(p) * 2 + rng.randint(0, 200))) for p in pos]
    last_fill = [round(m + rng.uniform(-0.25, 0.25), 4) for m in mids]

    hist = [max(0, int(2000 * (0.6 ** i)) + rng.randint(0, 25)) for i in range(NUM_HIST_BINS)]

    cash_scaled = int(cash * 65536)
    cash_lo = cash_scaled & 0xFFFFFFFF
    cash_hi = int(((cash_scaled >> 32) & 0xFFFF) | 0xFFFF0000)  # nonsense-but-present field

    return {
        "ts": round(t, 3),
        "state": "B_TRADING",
        "link_up": True,
        "risk_halt": False,
        "strategy": "MEAN_REV",
        "qps": qps,
        "ops": ops,
        "fps": fps,
        "rej": rej,
        "link_err": 0,
        "cash_lo": cash_lo,
        "cash_hi": cash_hi,
        "cash": cash,
        "total_pnl": total_pnl,
        "port_value": port_value,
        "inventory_mtm": inventory_mtm,
        "pos": pos,
        "bid": bids,
        "ask": asks,
        "mid": mids,
        "spread": spreads,
        "ema": emas,
        "signal": signal,
        "signal_code": signal_code,
        "pnl_cash": pnl_cash,
        "pnl_mtm": pnl_mtm,
        "pos_value": pos_value,
        "last_fill": last_fill,
        "trades": trades,
        "hist": hist,
        "lat_min": 2,
        "lat_max": 120,
        "lat_sum": int(55 * fps),
        "lat_cnt": max(1, fps),
        "last_latency": int(10 + 6 * abs(math.sin(t))),
        # Config echo fields (dashboard uses these when present)
        "threshold": 0.25,
        "ema_alpha": 6554,
        "base_qty": 100,
        "max_position": 5000,
        "max_order_rate": 1_000_000,
        "max_loss": 100000.0,
    }


_lock = threading.Lock()
_latest: Dict[str, Any] = {}
_history: Deque[Dict[str, Any]] = deque(maxlen=200)


def _poll_loop(hz: float, seed: int, sim_time_scale: float) -> None:
    interval = 1.0 / max(hz, 0.05)
    t0 = time.time()
    scale = max(0.0, float(sim_time_scale))
    while True:
        t = (time.time() - t0) * scale
        snap = _fake_snapshot(t, seed)
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
            global _latest
            _latest = snap
            _history.append(pt)
        time.sleep(interval)


_HTML_TEMPLATE = """<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8"/>
  <meta name="viewport" content="width=device-width, initial-scale=1"/>
  <title>Board B — MOCK</title>
  <script src="https://cdn.jsdelivr.net/npm/chart.js@4.4.1/dist/chart.umd.min.js"></script>
  <style>
    :root { --bg:#000; --card:#1c1c1e; --txt:#fff; --muted:#a1a1a6; --up:#00c805; --down:#ff331f; }
    body { font-family: system-ui, -apple-system, sans-serif; background: var(--bg); color: var(--txt); margin:0; padding:16px; }
    h1 { font-size: 1.25rem; font-weight: 700; margin: 0 0 16px; }
    .pill { display:inline-block; padding: 4px 10px; border-radius: 999px; font-size: 12px; font-weight: 600; background:#2c2c2e; }
    .hint { color: var(--muted); font-size: 12px; margin: 10px 0 18px; max-width: 980px; line-height: 1.45; }
    .grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(140px,1fr)); gap: 12px; margin-bottom: 20px; }
    .card { background: var(--card); border-radius: 16px; padding: 14px 16px; border: 1px solid #2c2c2e; }
    .card label { display:block; font-size: 11px; color: var(--muted); text-transform: uppercase; letter-spacing: .06em; margin-bottom: 4px; }
    .card .v { font-size: 1.35rem; font-weight: 700; font-variant-numeric: tabular-nums; }
    .pos { color: var(--up); } .neg { color: var(--down); }
    .row { display: flex; flex-wrap: wrap; gap: 16px; align-items: flex-start; }
    .chart-box { flex: 1 1 360px; min-height: 280px; background: var(--card); border-radius: 16px; padding: 12px; border: 1px solid #2c2c2e; }
  </style>
</head>
<body>
  <h1>Board B — MOCK telemetry server</h1>
  <div class="hint"><b>Note:</b> This is fake data for UI development. Defaults use a <b>slow</b> sim clock and infrequent UI refresh to stay light for long sessions. Switch back to the real PYNQ server when hardware is connected.</div>
  <div class="grid" id="cards"></div>
  <div class="row">
    <div class="chart-box"><canvas id="chMain"></canvas></div>
    <div class="chart-box" style="flex:0 1 320px"><canvas id="chRates"></canvas></div>
  </div>
  <p style="color:var(--muted); font-size:12px; margin-top:20px;">
    JSON: <code>/api/telemetry</code> · History: <code>/api/history</code>
  </p>
<script>
const fmt = (n, d=2) => (n==null||isNaN(n)) ? "—" : Number(n).toLocaleString(undefined,{maximumFractionDigits:d});
const money = (n) => {
  if (n==null||isNaN(n)) return "—";
  const s = (n>=0?"+":"") + "$" + Math.abs(n).toFixed(2);
  return s;
};
function inventoryAtMid(j) {
  if (j.inventory_mtm != null && Number.isFinite(Number(j.inventory_mtm))) return Number(j.inventory_mtm);
  if (!Array.isArray(j.pos) || !Array.isArray(j.mid)) return null;
  let s = 0;
  const n = Math.min(j.pos.length, j.mid.length);
  for (let i = 0; i < n; i++) s += Number(j.pos[i]||0) * Number(j.mid[i]||0);
  return Number.isFinite(s) ? s : null;
}
let chartMain, chartRates;
function initCharts() {
  const common = { responsive:true, maintainAspectRatio:false, animation:false,
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
    options: { ...common, plugins:{ title:{ display:true, text:"Profit & portfolio (MOCK)", color:"#fff" } } }
  });
  chartRates = new Chart(document.getElementById("chRates"), {
    type: "bar",
    data: { labels:["Quotes","Orders","Fills","Rej"], datasets:[{ data:[0,0,0,0],
      backgroundColor:["#6b6b6b","#5ac8fa","#00c805","#ff331f"] }]},
    options: { ...common, plugins:{ title:{ display:true, text:"Cumulative counters (MOCK)", color:"#fff" } } }
  });
}
function setCards(j) {
  const g = document.getElementById("cards");
  const risk = j.risk_halt ? "HALT" : "OK";
  const link = j.link_up ? "UP" : "DOWN";
  const haltCls = j.risk_halt ? "neg" : "pos";
  const inv = inventoryAtMid(j);
  const invCls = (inv!=null && inv>=0) ? "pos" : "neg";
  g.innerHTML = `
    <div class="card"><label>Cash</label><div class="v ${j.cash>=0?"pos":"neg"}">${money(j.cash)}</div></div>
    <div class="card"><label>Inventory @ mid (Σ pos·mid)</label><div class="v ${inv!=null?invCls:""}">${inv!=null?money(inv):"—"}</div></div>
    <div class="card"><label>Total PnL (MTM)</label><div class="v ${j.total_pnl>=0?"pos":"neg"}">${money(j.total_pnl)}</div></div>
    <div class="card"><label>Port value (cash + inv.)</label><div class="v ${j.port_value>=0?"pos":"neg"}">${money(j.port_value)}</div></div>
    <div class="card"><label>FSM</label><div class="v" style="font-size:1rem">${j.state}</div></div>
    <div class="card"><label>Strategy</label><div class="v" style="font-size:1rem">${j.strategy}</div></div>
    <div class="card"><label>Link / Risk</label><div class="v" style="font-size:1rem"><span class="pill">${link}</span> <span class="pill ${haltCls}">${risk}</span></div></div>
    <div class="card"><label>Quotes rcvd</label><div class="v">${fmt(j.qps,0)}</div></div>
    <div class="card"><label>Orders sent</label><div class="v">${fmt(j.ops,0)}</div></div>
    <div class="card"><label>Fills rcvd</label><div class="v">${fmt(j.fps,0)}</div></div>
    <div class="card"><label>Risk rejects</label><div class="v">${fmt(j.rej,0)}</div></div>
  `;
}
function pushHistory(h) {
  const pts = h.points || [];
  chartMain.data.labels = pts.map((p,i)=> i);
  chartMain.data.datasets[0].data = pts.map(p => p.cash);
  chartMain.data.datasets[1].data = pts.map(p => p.total_pnl);
  chartMain.data.datasets[2].data = pts.map(p => p.port_value);
  chartMain.update("none");
}
async function tick() {
  const [rJ, hJ] = await Promise.all([
    fetch("/api/telemetry").then(r=>r.json()),
    fetch("/api/history").then(r=>r.json())
  ]);
  setCards(rJ);
  pushHistory(hJ);
  chartRates.data.datasets[0].data = [rJ.qps, rJ.ops, rJ.fps, rJ.rej];
  chartRates.update("none");
}
initCharts();
setInterval(tick, __UI_POLL_MS__);
tick();
</script>
</body>
</html>"""


def _build_index_html(ui_poll_ms: int) -> bytes:
    ms = int(max(250, min(ui_poll_ms, 120_000)))
    return _HTML_TEMPLATE.replace("__UI_POLL_MS__", str(ms)).encode("utf-8")


INDEX_HTML: bytes = _build_index_html(2800)


class Handler(BaseHTTPRequestHandler):
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
            body = INDEX_HTML
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
        return


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Mock Board B HTTP telemetry server (laptop-only).")
    p.add_argument("--http-port", type=int, default=8099)
    p.add_argument("--host", default="127.0.0.1")
    p.add_argument(
        "--poll-hz",
        type=float,
        default=1.0,
        help="Telemetry snapshot rate (Hz). Default 1.0 is easy on CPU for long runs.",
    )
    p.add_argument(
        "--sim-time-scale",
        type=float,
        default=0.05,
        help="Fake market clock vs wall time (0..1). 0.05 ≈ 20× slower drift. Default 0.05.",
    )
    p.add_argument(
        "--ui-poll-ms",
        type=int,
        default=2800,
        help="Browser refresh interval (ms). Default 2800.",
    )
    p.add_argument(
        "--history-max",
        type=int,
        default=180,
        help="Ring buffer size for /api/history. Default 180.",
    )
    p.add_argument("--seed", type=int, default=1)
    return p.parse_args()


def main() -> None:
    args = parse_args()
    global _history, INDEX_HTML
    _history = deque(maxlen=max(20, min(int(args.history_max), 5000)))
    INDEX_HTML = _build_index_html(args.ui_poll_ms)
    # Publish one sample immediately so /api/telemetry is never "{}" on first fetch.
    with _lock:
        global _latest
        _latest = _fake_snapshot(0.0, args.seed)
        _history.append(
            {
                "t": _latest["ts"],
                "cash": _latest["cash"],
                "total_pnl": _latest["total_pnl"],
                "port_value": _latest["port_value"],
                "qps": _latest["qps"],
                "ops": _latest["ops"],
                "fps": _latest["fps"],
                "rej": _latest["rej"],
            }
        )
    threading.Thread(
        target=_poll_loop,
        args=(args.poll_hz, args.seed, args.sim_time_scale),
        daemon=True,
    ).start()
    time.sleep(0.05)
    httpd = HTTPServer((args.host, args.http_port), Handler)
    print(f"MOCK Board B HTTP UI:  http://{args.host}:{args.http_port}/")
    print(f"MOCK JSON telemetry:  http://{args.host}:{args.http_port}/api/telemetry")
    print(
        f"Light profile: poll={args.poll_hz} Hz | sim_time_scale={args.sim_time_scale} | "
        f"UI every {args.ui_poll_ms} ms | history≤{args.history_max}"
    )
    print("Ctrl+C to stop.")
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\nStopped.")


if __name__ == "__main__":
    main()
