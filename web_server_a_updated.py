#!/usr/bin/env python3
"""
web_server_a_updated.py — Board A combined HTTP server + browser UI.

Runs ON the PYNQ board. Reads Board A AXI registers and serves:
  GET  /                  → full browser trading dashboard
  GET  /api/prices        → live prices JSON
  GET  /api/status        → board status JSON
  POST /api/set_regime    → {"regime": 0-3}
  POST /api/set_symbols   → {"symbols": [...]}
  POST /api/start         → start Board A
  POST /api/reset         → reset Board A

Usage:
    python web_server_a_updated.py --bitfile overlays/board_a.bit
    python web_server_a_updated.py --demo   # no hardware needed
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
from typing import Any, Dict, Deque

try:
    from register_map_a_updated import (
        CTRL, REGIME, INIT_MID_BASE, INIT_SPREAD_BASE,
        ACTIVE_SYM_COUNT, STATUS, QUOTES_SENT, ORDERS_RCVD,
        FILLS_SENT, REJECTS_SENT, LINK_ERRORS,
        LIVE_BID_BASE, LIVE_ASK_BASE, LIVE_MID_BASE,
        REGIME_NAMES, NUM_SYMBOLS, Q16,
        q16_16, from_q16_16, decode_status,
    )
except ImportError:
    # fallback constants if register_map not found
    CTRL=0; REGIME=0x0C; INIT_MID_BASE=0x10; INIT_SPREAD_BASE=0x50
    ACTIVE_SYM_COUNT=0xF0; STATUS=0xF4; QUOTES_SENT=0xF8; ORDERS_RCVD=0xFC
    FILLS_SENT=0x100; REJECTS_SENT=0x104; LINK_ERRORS=0x108
    LIVE_BID_BASE=0x110; LIVE_ASK_BASE=0x150; LIVE_MID_BASE=0x190
    REGIME_NAMES={0:"CALM",1:"VOLATILE",2:"BURST",3:"ADVERSARIAL"}
    NUM_SYMBOLS=16; Q16=65536
    def q16_16(v): return int(v*Q16)&0xFFFFFFFF
    def from_q16_16(r): return r/Q16
    def decode_status(r): return {"running":bool(r&1),"link_up":bool((r>>1)&1),"active_regime":(r>>2)&3,"fifo_fill":(r>>9)&0x7F}

# ── Default symbol universe ──────────────────────────────────────
DEFAULT_SYMBOLS = [
    {"ticker":"AAPL","mid":180.00,"spread":0.10},
    {"ticker":"MSFT","mid":420.00,"spread":0.15},
    {"ticker":"GOOG","mid":175.00,"spread":0.12},
    {"ticker":"META","mid":510.00,"spread":0.20},
    {"ticker":"NVDA","mid":900.00,"spread":0.25},
    {"ticker":"AMD", "mid":160.00,"spread":0.08},
    {"ticker":"INTC","mid": 31.00,"spread":0.05},
    {"ticker":"AVGO","mid":170.00,"spread":0.18},
    {"ticker":"AMZN","mid":185.00,"spread":0.10},
    {"ticker":"TSLA","mid":250.00,"spread":0.30},
    {"ticker":"JPM", "mid":200.00,"spread":0.08},
    {"ticker":"GS",  "mid":470.00,"spread":0.22},
    {"ticker":"JNJ", "mid":155.00,"spread":0.06},
    {"ticker":"PFE", "mid": 27.00,"spread":0.04},
    {"ticker":"XOM", "mid":105.00,"spread":0.07},
    {"ticker":"CVX", "mid":155.00,"spread":0.09},
]

UNIVERSE = {
    "Tech":["AAPL","MSFT","GOOG","META","ORCL","CRM","ADBE","SNOW"],
    "Semiconductor":["NVDA","AMD","INTC","AVGO","QCOM","MU","AMAT","LRCX"],
    "Consumer":["AMZN","TSLA","HD","NKE","MCD","SBUX","TGT","COST"],
    "Finance":["JPM","GS","BAC","WFC","MS","BLK","C","AXP"],
    "Health":["JNJ","PFE","UNH","ABBV","MRK","LLY","BMY","GILD"],
    "Energy":["XOM","CVX","COP","SLB","EOG","PXD","MPC","VLO"],
    "Industrial":["CAT","HON","GE","BA","MMM","LMT","RTX","DE"],
    "Staples":["PG","KO","PEP","WMT","CL","GIS","K","SYY"],
    "Comms":["NFLX","DIS","CMCSA","T","VZ","TMUS","PARA","WBD"],
    "Real Estate":["AMT","PLD","CCI","EQIX","PSA","DLR","O","SPG"],
}

STOCK_DATA = {
    "AAPL":(180.00,0.10),"MSFT":(420.00,0.15),"GOOG":(175.00,0.12),"META":(510.00,0.20),
    "NVDA":(900.00,0.25),"AMD":(160.00,0.08),"INTC":(31.00,0.05),"AVGO":(170.00,0.18),
    "AMZN":(185.00,0.10),"TSLA":(250.00,0.30),"JPM":(200.00,0.08),"GS":(470.00,0.22),
    "JNJ":(155.00,0.06),"PFE":(27.00,0.04),"XOM":(105.00,0.07),"CVX":(155.00,0.09),
    "ORCL":(115.00,0.08),"CRM":(270.00,0.18),"ADBE":(520.00,0.22),"SNOW":(165.00,0.14),
    "QCOM":(170.00,0.12),"MU":(85.00,0.07),"AMAT":(190.00,0.14),"LRCX":(850.00,0.30),
    "HD":(350.00,0.15),"NKE":(90.00,0.08),"MCD":(290.00,0.12),"SBUX":(90.00,0.07),
    "TGT":(145.00,0.10),"COST":(730.00,0.25),"BAC":(35.00,0.04),"WFC":(55.00,0.05),
    "MS":(95.00,0.07),"BLK":(820.00,0.35),"C":(60.00,0.05),"AXP":(230.00,0.12),
    "UNH":(520.00,0.22),"ABBV":(175.00,0.10),"MRK":(125.00,0.08),"LLY":(780.00,0.30),
    "BMY":(50.00,0.05),"GILD":(75.00,0.06),"COP":(115.00,0.08),"SLB":(45.00,0.05),
    "EOG":(115.00,0.08),"PXD":(225.00,0.14),"MPC":(170.00,0.10),"VLO":(145.00,0.09),
    "CAT":(360.00,0.15),"HON":(200.00,0.10),"GE":(150.00,0.08),"BA":(190.00,0.14),
    "MMM":(95.00,0.07),"LMT":(450.00,0.20),"RTX":(95.00,0.07),"DE":(375.00,0.16),
    "PG":(165.00,0.08),"KO":(60.00,0.04),"PEP":(170.00,0.09),"WMT":(170.00,0.09),
    "CL":(90.00,0.06),"GIS":(65.00,0.05),"K":(65.00,0.05),"SYY":(80.00,0.06),
    "NFLX":(630.00,0.28),"DIS":(90.00,0.07),"CMCSA":(40.00,0.04),"T":(17.00,0.03),
    "VZ":(40.00,0.04),"TMUS":(160.00,0.10),"PARA":(15.00,0.03),"WBD":(10.00,0.02),
    "AMT":(195.00,0.12),"PLD":(120.00,0.08),"CCI":(105.00,0.08),"EQIX":(780.00,0.32),
    "PSA":(285.00,0.14),"DLR":(140.00,0.09),"O":(55.00,0.05),"SPG":(150.00,0.10),
}

# ── Shared state ─────────────────────────────────────────────────
_lock    = threading.Lock()
_latest: Dict[str, Any] = {}
_history: Deque[Dict] = deque(maxlen=300)
_symbols = list(DEFAULT_SYMBOLS)
_mmio    = None
_demo    = False

def _write_symbols_to_hw(symbols):
    if _mmio is None:
        return
    _mmio.write(CTRL, 0x02)
    time.sleep(0.05)
    for i, s in enumerate(symbols):
        _mmio.write(INIT_MID_BASE    + 4*i, q16_16(s["mid"]))
        _mmio.write(INIT_SPREAD_BASE + 4*i, q16_16(s["spread"]))
    _mmio.write(ACTIVE_SYM_COUNT, len(symbols))
    _mmio.write(0x04, 1000)
    _mmio.write(0x08, 0xDEADBEEF)
    _mmio.write(REGIME, 0)
    _mmio.write(CTRL, 0x01)

def _poll_loop(hz: float):
    global _latest
    interval = 1.0 / max(hz, 1.0)
    tick = 0
    while True:
        tick += 1
        try:
            with _lock:
                syms = list(_symbols)
            if _demo or _mmio is None:
                regime_val = _latest.get("regime", 0)
                noise_scale = {0:0.0005, 1:0.003, 2:0.010, 3:0.004}
                spread_mult = {0:1.0,    1:2.5,   2:5.0,   3:3.0}
                amp  = noise_scale.get(regime_val, 0.001)
                mult = spread_mult.get(regime_val, 1.0)
                prices = []
                t = time.time()
                for i, s in enumerate(syms):
                    init_p  = s["mid"]
                    init_sp = s["spread"]
                    drift   = math.sin(t * 0.3 + i * 0.7) * init_p * amp * 3
                    noise   = random.gauss(0, init_p * amp)
                    mid     = init_p + drift + noise
                    spr     = init_sp * mult
                    prices.append({
                        "ticker": s["ticker"],
                        "bid":    round(mid - spr/2, 4),
                        "ask":    round(mid + spr/2, 4),
                        "mid":    round(mid, 4),
                        "spread": round(spr, 4),
                    })
                snap = {
                    "regime":      regime_val,
                    "regime_name": REGIME_NAMES.get(regime_val, "?"),
                    "running":     True,
                    "link_up":     True,
                    "quotes_sent": tick * NUM_SYMBOLS * 100,
                    "orders_rcvd": tick // 10,
                    "fills_sent":  tick // 12,
                    "prices":      prices,
                    "ts":          round(t, 3),
                }
            else:
                raw_status  = _mmio.read(STATUS)
                st          = decode_status(raw_status)
                regime_val  = st["active_regime"]
                quotes_sent = _mmio.read(QUOTES_SENT)
                prices = []
                for i, s in enumerate(syms):
                    bid_q16 = _mmio.read(LIVE_BID_BASE + 4*i)
                    ask_q16 = _mmio.read(LIVE_ASK_BASE + 4*i)
                    if bid_q16 == 0 or ask_q16 == 0:
                        mid_q16 = _mmio.read(INIT_MID_BASE    + 4*i)
                        spr_q16 = _mmio.read(INIT_SPREAD_BASE + 4*i)
                        bid_q16 = max(0, mid_q16 - spr_q16//2)
                        ask_q16 = mid_q16 + spr_q16//2
                    bid = from_q16_16(bid_q16)
                    ask = from_q16_16(ask_q16)
                    prices.append({
                        "ticker": s["ticker"],
                        "bid":    round(bid, 4),
                        "ask":    round(ask, 4),
                        "mid":    round((bid+ask)/2, 4),
                        "spread": round(ask-bid, 4),
                    })
                snap = {
                    "regime":      regime_val,
                    "regime_name": REGIME_NAMES.get(regime_val, "?"),
                    "running":     st["running"],
                    "link_up":     st["link_up"],
                    "quotes_sent": _mmio.read(QUOTES_SENT),
                    "orders_rcvd": _mmio.read(ORDERS_RCVD),
                    "fills_sent":  _mmio.read(FILLS_SENT),
                    "prices":      prices,
                    "ts":          round(time.time(), 3),
                }
            pt = {"t": snap["ts"], "quotes": snap["quotes_sent"]}
            for p in snap["prices"]:
                pt[p["ticker"]] = p["mid"]
            with _lock:
                _latest = snap
                _history.append(pt)
        except Exception as e:
            print(f"Poll error: {e}")
        time.sleep(interval)

# ── HTML dashboard ────────────────────────────────────────────────
_HTML = r"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8"/>
<meta name="viewport" content="width=device-width,initial-scale=1"/>
<title>FPGA Trading Engine</title>
<script src="https://cdn.jsdelivr.net/npm/chart.js@4.4.1/dist/chart.umd.min.js"></script>
<link rel="preconnect" href="https://fonts.googleapis.com">
<link href="https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@400;600;700&family=Space+Grotesk:wght@400;600;700&display=swap" rel="stylesheet">
<style>
:root {
  --bg:#030712; --card:#0f1729; --border:#1e3a5f;
  --txt:#e2e8f0; --muted:#64748b; --accent:#38bdf8;
  --up:#22c55e; --down:#ef4444; --warn:#f59e0b;
  --calm:#22c55e; --volatile:#f59e0b; --burst:#ef4444; --adv:#a855f7;
}
* { box-sizing:border-box; margin:0; padding:0; }
body { font-family:'Space Grotesk',sans-serif; background:var(--bg); color:var(--txt); min-height:100vh; }
.mono { font-family:'JetBrains Mono',monospace; }

/* Header */
header { display:flex; align-items:center; justify-content:space-between;
  padding:16px 24px; border-bottom:1px solid var(--border);
  background:rgba(15,23,41,0.8); backdrop-filter:blur(10px);
  position:sticky; top:0; z-index:100; }
header h1 { font-size:1.1rem; font-weight:700; letter-spacing:.05em;
  color:var(--accent); display:flex; align-items:center; gap:8px; }
.dot { width:8px; height:8px; border-radius:50%; background:var(--up);
  box-shadow:0 0 8px var(--up); animation:pulse 2s infinite; }
@keyframes pulse { 0%,100%{opacity:1} 50%{opacity:.4} }

/* Regime bar */
.regime-bar { display:flex; gap:8px; align-items:center; padding:12px 24px;
  border-bottom:1px solid var(--border); background:var(--card); }
.regime-bar label { font-size:11px; color:var(--muted); text-transform:uppercase;
  letter-spacing:.08em; margin-right:4px; }
.regime-btn { padding:6px 16px; border-radius:6px; border:1px solid var(--border);
  background:transparent; color:var(--muted); font-family:inherit; font-size:12px;
  font-weight:600; cursor:pointer; transition:all .15s; letter-spacing:.04em; }
.regime-btn:hover { border-color:var(--accent); color:var(--accent); }
.regime-btn.active-calm    { background:var(--calm);    border-color:var(--calm);    color:#000; }
.regime-btn.active-volatile{ background:var(--volatile); border-color:var(--volatile);color:#000; }
.regime-btn.active-burst   { background:var(--burst);   border-color:var(--burst);   color:#fff; }
.regime-btn.active-adv     { background:var(--adv);     border-color:var(--adv);     color:#fff; }
.status-pill { margin-left:auto; display:flex; gap:8px; align-items:center; }
.pill { padding:4px 10px; border-radius:4px; font-size:11px; font-weight:600;
  font-family:'JetBrains Mono',monospace; }
.pill-up   { background:rgba(34,197,94,.15);  color:var(--up);   border:1px solid rgba(34,197,94,.3); }
.pill-down { background:rgba(239,68,68,.15);  color:var(--down); border:1px solid rgba(239,68,68,.3); }
.pill-muted{ background:rgba(100,116,139,.15);color:var(--muted);border:1px solid rgba(100,116,139,.3); }

/* Layout */
.main { display:grid; grid-template-columns:1fr 380px; gap:0; height:calc(100vh - 97px); }
.left  { overflow-y:auto; border-right:1px solid var(--border); }
.right { overflow-y:auto; display:flex; flex-direction:column; }

/* Price table */
.price-table { width:100%; border-collapse:collapse; }
.price-table thead th { padding:10px 16px; text-align:left; font-size:11px;
  color:var(--muted); text-transform:uppercase; letter-spacing:.06em;
  border-bottom:1px solid var(--border); position:sticky; top:0;
  background:var(--bg); font-weight:600; }
.price-table tbody tr { border-bottom:1px solid rgba(30,58,95,.4); cursor:pointer;
  transition:background .1s; }
.price-table tbody tr:hover { background:rgba(56,189,248,.05); }
.price-table tbody tr.selected { background:rgba(56,189,248,.08);
  border-left:2px solid var(--accent); }
.price-table td { padding:10px 16px; font-size:13px; }
.ticker { font-weight:700; font-size:14px; color:var(--txt); }
.sector-tag { font-size:10px; color:var(--muted); font-weight:400; margin-left:4px; }
.price-val { font-family:'JetBrains Mono',monospace; font-size:13px; }
.chg-up   { color:var(--up);   font-weight:600; font-family:'JetBrains Mono',monospace; }
.chg-down { color:var(--down); font-weight:600; font-family:'JetBrains Mono',monospace; }
.chg-flat { color:var(--muted); font-family:'JetBrains Mono',monospace; }
.win-btn { padding:3px 8px; border-radius:4px; border:none; background:transparent;
  color:var(--muted); font-family:inherit; font-size:11px; cursor:pointer;
  transition:all .15s; font-weight:600; }
.win-btn:hover { color:var(--txt); }
.active-win { background:var(--accent) !important; color:#000 !important; }
.active-smooth { background:var(--warn) !important; color:#000 !important; border-color:var(--warn) !important; }
.spark { width:80px; height:24px; }

/* Chart panel */
.chart-panel { flex:1; padding:16px; border-bottom:1px solid var(--border); min-height:280px; }
.chart-panel h3 { font-size:12px; color:var(--muted); text-transform:uppercase;
  letter-spacing:.06em; margin-bottom:12px; display:flex; justify-content:space-between; }
.chart-panel h3 span { color:var(--txt); font-size:14px; text-transform:none;
  letter-spacing:0; font-weight:700; }
#mainChart { width:100% !important; }

/* Stats panel */
.stats-panel { padding:16px; }
.stats-grid { display:grid; grid-template-columns:1fr 1fr; gap:8px; }
.stat-card { background:var(--card); border:1px solid var(--border);
  border-radius:8px; padding:10px 12px; }
.stat-card label { display:block; font-size:10px; color:var(--muted);
  text-transform:uppercase; letter-spacing:.06em; margin-bottom:4px; }
.stat-card .val { font-family:'JetBrains Mono',monospace; font-size:15px;
  font-weight:700; color:var(--txt); }

/* Symbol picker modal */
.modal-overlay { display:none; position:fixed; inset:0; background:rgba(0,0,0,.7);
  z-index:200; backdrop-filter:blur(4px); align-items:center; justify-content:center; }
.modal-overlay.open { display:flex; }
.modal { background:var(--card); border:1px solid var(--border); border-radius:12px;
  width:min(640px,95vw); max-height:80vh; overflow-y:auto; }
.modal-header { padding:20px 24px; border-bottom:1px solid var(--border);
  display:flex; align-items:center; justify-content:space-between; }
.modal-header h2 { font-size:16px; font-weight:700; }
.modal-close { background:none; border:none; color:var(--muted); font-size:20px;
  cursor:pointer; padding:4px 8px; border-radius:4px; }
.modal-close:hover { color:var(--txt); background:rgba(255,255,255,.05); }
.modal-body { padding:20px 24px; }
.sector-grid { display:grid; grid-template-columns:repeat(2,1fr); gap:8px; margin-bottom:16px; }
.sector-btn { padding:10px 14px; border-radius:8px; border:1px solid var(--border);
  background:var(--bg); color:var(--txt); font-family:inherit; font-size:13px;
  cursor:pointer; text-align:left; transition:all .15s; }
.sector-btn:hover { border-color:var(--accent); }
.sector-btn.active { border-color:var(--accent); background:rgba(56,189,248,.1); }
.stock-list { display:grid; grid-template-columns:repeat(2,1fr); gap:6px; margin-bottom:16px; }
.stock-item { display:flex; align-items:center; gap:8px; padding:8px 10px;
  border-radius:6px; border:1px solid var(--border); cursor:pointer;
  transition:all .15s; font-size:13px; }
.stock-item:hover { border-color:var(--accent); }
.stock-item.picked { border-color:var(--up); background:rgba(34,197,94,.08); }
.stock-item input[type=checkbox] { accent-color:var(--up); }
.slot-progress { display:flex; gap:4px; margin-bottom:16px; flex-wrap:wrap; }
.slot { width:28px; height:8px; border-radius:4px; background:var(--border); }
.slot.filled-locked { background:var(--accent); }
.slot.filled-free   { background:var(--up); }
.modal-footer { padding:16px 24px; border-top:1px solid var(--border);
  display:flex; justify-content:flex-end; gap:8px; }
.btn { padding:8px 20px; border-radius:6px; font-family:inherit; font-size:13px;
  font-weight:600; cursor:pointer; border:none; transition:all .15s; }
.btn-primary { background:var(--accent); color:#000; }
.btn-primary:hover { opacity:.9; }
.btn-secondary { background:transparent; color:var(--muted);
  border:1px solid var(--border); }
.btn-secondary:hover { color:var(--txt); border-color:var(--txt); }
.note { font-size:11px; color:var(--muted); margin-bottom:12px; line-height:1.5; }
.note b { color:var(--txt); }
.slot-label { font-size:11px; color:var(--muted); margin-bottom:6px; }

/* Scrollbar */
::-webkit-scrollbar { width:4px; }
::-webkit-scrollbar-track { background:transparent; }
::-webkit-scrollbar-thumb { background:var(--border); border-radius:4px; }
</style>
</head>
<body>

<header>
  <h1>TradeMark Stock Exchange</h1>
  <div style="display:flex;gap:8px;align-items:center">
    <button class="btn btn-secondary" onclick="shuffleDisplay(prices.length);renderTable({prices});" style="font-size:11px;padding:5px 12px">
      ⇌ Shuffle
    </button>
    <button class="btn btn-secondary" onclick="openModal()" style="font-size:11px;padding:5px 12px">
      ⚙ Configure Symbols
    </button>
    <span class="mono" style="font-size:11px;color:var(--muted)" id="clock">--:--:--</span>
  </div>
</header>

<div class="regime-bar">
  <label>Market Regime:</label>
  <button class="regime-btn" id="btn0" onclick="setRegime(0)">CALM</button>
  <button class="regime-btn" id="btn1" onclick="setRegime(1)">VOLATILE</button>
  <button class="regime-btn" id="btn2" onclick="setRegime(2)">BURST</button>
  <button class="regime-btn" id="btn3" onclick="setRegime(3)">ADVERSARIAL</button>
  <div class="status-pill">
    <span class="pill pill-muted" id="pillRunning">STOPPED</span>
    <span class="pill pill-muted" id="pillLink">LINK DOWN</span>
    <span class="pill pill-muted mono" id="pillQuotes">0 quotes</span>
  </div>
</div>

<div class="main">
  <!-- Left: price table -->
  <div class="left">
    <table class="price-table">
      <thead><tr>
        <th>#</th><th>Symbol</th><th>Bid</th><th>Ask</th>
        <th>Mid</th><th>Spread</th><th>Chg</th><th>Trend</th>
      </tr></thead>
      <tbody id="priceBody"></tbody>
    </table>
  </div>

  <!-- Right: chart + stats -->
  <div class="right">
    <div class="chart-panel">
      <div style="display:flex;align-items:center;justify-content:space-between;margin-bottom:10px;">
        <div style="font-size:11px;color:var(--muted);text-transform:uppercase;letter-spacing:.06em;">
          Price Chart <span id="chartTicker" style="color:var(--txt);font-size:14px;font-weight:700;text-transform:none;letter-spacing:0;margin-left:6px;">—</span>
        </div>
        <div style="display:flex;gap:4px;align-items:center;flex-wrap:nowrap;">
          <div style="display:flex;gap:1px;background:var(--bg);border:1px solid var(--border);border-radius:6px;padding:2px;">
            <button onclick="setWindow(30)"  id="w30"  class="win-btn active-win">30s</button>
            <button onclick="setWindow(60)"  id="w60"  class="win-btn">1m</button>
            <button onclick="setWindow(120)" id="w120" class="win-btn">2m</button>
            <button onclick="setWindow(240)" id="w240" class="win-btn">All</button>
          </div>
          <button onclick="toggleSmooth()"     id="smoothBtn"   class="win-btn" style="border:1px solid var(--border);border-radius:6px;padding:3px 7px;">〜</button>
          <button onclick="toggleChartMode()"  id="chartModeBtn" class="win-btn" style="border:1px solid var(--border);border-radius:6px;padding:3px 7px;">🕯</button>
        </div>
      </div>
      <canvas id="mainChart" height="220"></canvas>
    </div>
    <div class="stats-panel">
      <div class="stats-grid">
        <div class="stat-card">
          <label>Quotes Sent</label>
          <div class="val" id="statQuotes">0</div>
        </div>
        <div class="stat-card">
          <label>Orders Rcvd</label>
          <div class="val" id="statOrders">0</div>
        </div>
        <div class="stat-card">
          <label>Regime</label>
          <div class="val" id="statRegime">CALM</div>
        </div>
        <div class="stat-card">
          <label>Link Status</label>
          <div class="val" id="statLink">DOWN</div>
        </div>
      </div>
    </div>
  </div>
</div>

<!-- Symbol picker modal -->
<div class="modal-overlay" id="modal">
  <div class="modal">
    <div class="modal-header">
      <h2>Configure Market Symbols</h2>
      <button class="modal-close" onclick="closeModal()">✕</button>
    </div>
    <div class="modal-body">
      <p class="note">
        <b>Slots 0–7</b> use locked prices from the NN training set — only the company name changes.<br>
        <b>Slots 8–15</b> are free — choose any sector and stock.
      </p>
      <div class="slot-label">Slots filled:</div>
      <div class="slot-progress" id="slotProgress"></div>

      <!-- Phase indicator -->
      <div id="phaseLabel" style="font-size:12px;color:var(--accent);margin-bottom:12px;font-weight:600;"></div>

      <!-- Sector picker -->
      <div id="sectorSection">
        <div style="font-size:12px;color:var(--muted);margin-bottom:8px;">Choose a sector:</div>
        <div class="sector-grid" id="sectorGrid"></div>
      </div>

      <!-- Stock picker (shown after sector selected) -->
      <div id="stockSection" style="display:none">
        <div style="display:flex;align-items:center;justify-content:space-between;margin-bottom:8px;">
          <span style="font-size:12px;color:var(--muted)" id="stockSectorLabel"></span>
          <button class="btn btn-secondary" style="font-size:11px;padding:4px 10px" onclick="backToSectors()">← Back</button>
        </div>
        <div class="stock-list" id="stockList"></div>
        <button class="btn btn-primary" style="width:100%;margin-top:8px" onclick="confirmStocks()">
          Add Selected →
        </button>
      </div>
    </div>
    <div class="modal-footer">
      <button class="btn btn-secondary" onclick="resetPicker()">Reset</button>
      <button class="btn btn-secondary" onclick="useDefault()">Use Default</button>
      <button class="btn btn-primary" id="applyBtn" onclick="applySymbols()" disabled>
        Apply to Hardware
      </button>
    </div>
  </div>
</div>

<script>
// ── State ────────────────────────────────────────────────────────
const LOCKED_PRICES = [
  {mid:180.00,spread:0.10},{mid:420.00,spread:0.15},
  {mid:175.00,spread:0.12},{mid:510.00,spread:0.20},
  {mid:900.00,spread:0.25},{mid:160.00,spread:0.08},
  {mid: 31.00,spread:0.05},{mid:170.00,spread:0.18},
];
const UNIVERSE = __UNIVERSE_JSON__;
const STOCK_DATA = __STOCK_DATA_JSON__;
const SECTORS = Object.keys(UNIVERSE);

let prices     = [];
let prevPrices = {};
let history    = {};   // ticker → [mid, ...]
let selected   = 0;    // selected display row index
let chart      = null;
let pickerSyms = [];
let pickerSector = null;
let pickerStockSel = new Set();
let displayOrder = [];  // maps display row → hardware slot index

function shuffleDisplay(n) {
  displayOrder = Array.from({length: n}, (_, i) => i);
  // Fisher-Yates shuffle
  for (let i = displayOrder.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [displayOrder[i], displayOrder[j]] = [displayOrder[j], displayOrder[i]];
  }
}

// ── Chart setup ──────────────────────────────────────────────────
function initChart() {
  const ctx = document.getElementById("mainChart").getContext("2d");
  chart = new Chart(ctx, {
    type: "line",
    data: { labels:[], datasets:[{
      label:"Mid Price", data:[], borderColor:"#38bdf8",
      backgroundColor:"rgba(56,189,248,.08)", fill:true,
      tension:0.3, pointRadius:0, borderWidth:2,
    }]},
    options: {
      responsive:true, maintainAspectRatio:false, animation:false,
      plugins:{ legend:{display:false} },
      scales:{
        x:{ display:false },
        y:{ ticks:{color:"#64748b", font:{family:"JetBrains Mono",size:11}},
            grid:{color:"rgba(30,58,95,.5)"} }
      }
    }
  });
}

// ── Price table ──────────────────────────────────────────────────
const SECTORS_MAP = {
  AAPL:"Tech",MSFT:"Tech",GOOG:"Tech",META:"Tech",NVDA:"Semi",
  AMD:"Semi",INTC:"Semi",AVGO:"Semi",AMZN:"Cons",TSLA:"Cons",
  JPM:"Fin",GS:"Fin",JNJ:"Health",PFE:"Health",XOM:"Energy",CVX:"Energy",
  ORCL:"Tech",CRM:"Tech",ADBE:"Tech",SNOW:"Tech",QCOM:"Semi",MU:"Semi",
  AMAT:"Semi",LRCX:"Semi",HD:"Cons",NKE:"Cons",MCD:"Cons",SBUX:"Cons",
  TGT:"Cons",COST:"Cons",BAC:"Fin",WFC:"Fin",MS:"Fin",BLK:"Fin",
  C:"Fin",AXP:"Fin",UNH:"Health",ABBV:"Health",MRK:"Health",LLY:"Health",
  BMY:"Health",GILD:"Health",COP:"Energy",SLB:"Energy",EOG:"Energy",
  PXD:"Energy",MPC:"Energy",VLO:"Energy",CAT:"Ind",HON:"Ind",GE:"Ind",
  BA:"Ind",MMM:"Ind",LMT:"Ind",RTX:"Ind",DE:"Ind",PG:"Staples",
  KO:"Staples",PEP:"Staples",WMT:"Staples",CL:"Staples",GIS:"Staples",
  K:"Staples",SYY:"Staples",NFLX:"Comms",DIS:"Comms",CMCSA:"Comms",
  T:"Comms",VZ:"Comms",TMUS:"Comms",PARA:"Comms",WBD:"Comms",
  AMT:"RE",PLD:"RE",CCI:"RE",EQIX:"RE",PSA:"RE",DLR:"RE",O:"RE",SPG:"RE",
};

function drawSparkline(canvas, data) {
  const ctx = canvas.getContext("2d");
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  if (!data || data.length < 2) return;
  const mn = Math.min(...data), mx = Math.max(...data);
  const rng = mx - mn || 0.001;
  const w = canvas.width, h = canvas.height;
  const rising = data[data.length-1] >= data[0];
  ctx.strokeStyle = rising ? "#22c55e" : "#ef4444";
  ctx.lineWidth = 1.5;
  ctx.beginPath();
  data.forEach((v,i) => {
    const x = (i / (data.length-1)) * w;
    const y = h - ((v - mn) / rng) * h;
    i === 0 ? ctx.moveTo(x,y) : ctx.lineTo(x,y);
  });
  ctx.stroke();
}

function renderTable(data) {
  prices = data.prices || [];
  // Init or resize displayOrder
  if (displayOrder.length !== prices.length) shuffleDisplay(prices.length);
  const body = document.getElementById("priceBody");
  body.innerHTML = "";
  displayOrder.forEach((hwSlot, displayRow) => {
    const p = prices[hwSlot];
    if (!p) return;
    const prev = prevPrices[p.ticker];
    const chg = prev != null ? p.mid - prev : 0;
    const chgStr = chg === 0 ? "─" : (chg > 0 ? `▲${chg.toFixed(3)}` : `▼${Math.abs(chg).toFixed(3)}`);
    const chgCls = chg > 0.001 ? "chg-up" : chg < -0.001 ? "chg-down" : "chg-flat";
    if (!history[p.ticker]) history[p.ticker] = [];
    history[p.ticker].push(p.mid);
    if (history[p.ticker].length > 240) history[p.ticker].shift();

    const tr = document.createElement("tr");
    if (displayRow === selected) tr.classList.add("selected");
    tr.onclick = () => { selected = displayRow; renderTable({prices}); updateChart(); };
    tr.innerHTML = `
      <td class="mono" style="color:var(--muted);font-size:11px">${displayRow}</td>
      <td><span class="ticker">${p.ticker}</span><span class="sector-tag">${SECTORS_MAP[p.ticker]||""}</span></td>
      <td class="price-val">$${p.bid.toFixed(3)}</td>
      <td class="price-val">$${p.ask.toFixed(3)}</td>
      <td class="price-val" style="font-weight:600">$${p.mid.toFixed(3)}</td>
      <td class="price-val" style="color:var(--muted)">$${p.spread.toFixed(4)}</td>
      <td class="${chgCls}">${chgStr}</td>
      <td><canvas class="spark" width="80" height="24"></canvas></td>
    `;
    body.appendChild(tr);
    drawSparkline(tr.querySelector("canvas"), history[p.ticker]);
    prevPrices[p.ticker] = p.mid;
  });
}

// ── Chart mode toggle ────────────────────────────────────────────
let chartMode   = "line";
let chartWindow = 30;   // number of data points to show
let chartSmooth = false;

function setWindow(n) {
  chartWindow = n;
  ["30","60","120","240"].forEach(v => {
    document.getElementById("w"+v).classList.toggle("active-win", parseInt(v)===n);
  });
  updateChart();
}

function toggleSmooth() {
  chartSmooth = !chartSmooth;
  document.getElementById("smoothBtn").classList.toggle("active-smooth", chartSmooth);
  updateChart();
}

function smoothData(data, k=5) {
  if (!chartSmooth || data.length < k) return data;
  return data.map((v, i) => {
    const start = Math.max(0, i - Math.floor(k/2));
    const end   = Math.min(data.length, start + k);
    const slice = data.slice(start, end);
    return slice.reduce((a,b) => a+b, 0) / slice.length;
  });
}

function toggleChartMode() {
  chartMode = chartMode === "line" ? "candle" : "line";
  document.getElementById("chartModeBtn").style.color =
    chartMode === "candle" ? "var(--accent)" : "var(--muted)";
  updateChart();
}

function buildCandles(data, candleSize=5) {
  const candles = [];
  for (let i = 0; i + candleSize <= data.length; i += candleSize) {
    const w = data.slice(i, i + candleSize);
    candles.push({ o:w[0], h:Math.max(...w), l:Math.min(...w), c:w[w.length-1] });
  }
  return candles;
}

function updateChart() {
  const hwSlot = displayOrder[selected] ?? selected;
  if (!prices[hwSlot]) return;
  const p    = prices[hwSlot];
  const full = history[p.ticker] || [];
  document.getElementById("chartTicker").textContent = p.ticker;

  if (chartMode === "line") {
    const hist    = chartWindow >= 240 ? full : full.slice(-chartWindow);
    const smoothed = smoothData(hist);
    chart.config.type = "line";
    chart.data.labels   = smoothed.map((_,i) => i);
    chart.data.datasets = [{
      label:"Mid Price", data:smoothed,
      borderColor: smoothed.length>1 && smoothed[smoothed.length-1]>=smoothed[0] ? "#22c55e":"#ef4444",
      backgroundColor: smoothed.length>1 && smoothed[smoothed.length-1]>=smoothed[0]
        ? "rgba(34,197,94,.08)":"rgba(239,68,68,.08)",
      fill:true, tension: chartSmooth ? 0.5 : 0.3, pointRadius:0, borderWidth:2,
    }];
  } else {
    const candles = buildCandles(full);  // use all history for more candles
    if (candles.length === 0) { chart.update("none"); return; }
    chart.config.type = "bar";
    chart.data.labels = candles.map((_,i) => i);
    chart.data.datasets = [
      {
        label:"Body",
        data: candles.map(c => [Math.min(c.o,c.c), Math.max(c.o,c.c)]),
        backgroundColor: candles.map(c => c.c>=c.o ? "rgba(34,197,94,.9)":"rgba(239,68,68,.9)"),
        borderColor:     candles.map(c => c.c>=c.o ? "#22c55e":"#ef4444"),
        borderWidth:1, barPercentage:0.6, categoryPercentage:0.7,
        order:2,
      },
      {
        label:"Wick",
        data: candles.map(c => [c.l, c.h]),
        backgroundColor: candles.map(c => c.c>=c.o ? "rgba(34,197,94,.7)":"rgba(239,68,68,.7)"),
        borderColor:     candles.map(c => c.c>=c.o ? "#22c55e":"#ef4444"),
        borderWidth:1, barPercentage:0.06, categoryPercentage:0.7,
        order:1,
      }
    ];
  }
  chart.update("none");
}

// ── Status / regime ──────────────────────────────────────────────
const REGIME_CLASSES = ["active-calm","active-volatile","active-burst","active-adv"];
function updateRegimeUI(regime) {
  [0,1,2,3].forEach(i => {
    const b = document.getElementById(`btn${i}`);
    b.className = "regime-btn" + (i===regime ? " "+REGIME_CLASSES[i] : "");
  });
  const names = ["CALM","VOLATILE","BURST","ADVERSARIAL"];
  document.getElementById("statRegime").textContent = names[regime]||"?";
}

async function setRegime(val) {
  await fetch("/api/set_regime", {method:"POST",
    headers:{"Content-Type":"application/json"},
    body:JSON.stringify({regime:val})});
}

function updateStatus(data) {
  const pRun = document.getElementById("pillRunning");
  const pLnk = document.getElementById("pillLink");
  const pQ   = document.getElementById("pillQuotes");
  pRun.textContent = data.running ? "RUNNING" : "STOPPED";
  pRun.className   = "pill " + (data.running ? "pill-up" : "pill-down");
  pLnk.textContent = data.link_up ? "LINK UP" : "LINK DOWN";
  pLnk.className   = "pill " + (data.link_up ? "pill-up" : "pill-muted");
  pQ.textContent   = (data.quotes_sent||0).toLocaleString() + " quotes";
  document.getElementById("statQuotes").textContent = (data.quotes_sent||0).toLocaleString();
  document.getElementById("statOrders").textContent = (data.orders_rcvd||0).toLocaleString();
  document.getElementById("statLink").textContent   = data.link_up ? "UP" : "DOWN";
  document.getElementById("clock").textContent      = new Date().toLocaleTimeString();
  updateRegimeUI(data.regime||0);
}

// ── Poll loop ────────────────────────────────────────────────────
async function tick() {
  try {
    const r = await fetch("/api/prices");
    const d = await r.json();
    renderTable(d);
    updateStatus(d);
    updateChart();
  } catch(e) { console.warn(e); }
}
setInterval(tick, 250);
tick();

// ── Symbol picker modal ──────────────────────────────────────────
function openModal() {
  document.getElementById("modal").classList.add("open");
  renderPicker();
}
function closeModal() {
  document.getElementById("modal").classList.remove("open");
}

function renderPicker() {
  renderSlots();
  const phase = pickerSyms.length < 8 ? 1 : 2;
  const label = phase===1
    ? `Phase 1 of 2 — Choose names for slots 0–7 (${pickerSyms.length}/8 filled)`
    : `Phase 2 of 2 — Choose stocks for slots 8–15 (${pickerSyms.length}/16 filled)`;
  document.getElementById("phaseLabel").textContent = label;
  document.getElementById("applyBtn").disabled = pickerSyms.length < 16;
  showSectors();
}

function renderSlots() {
  const el = document.getElementById("slotProgress");
  el.innerHTML = "";
  for (let i=0; i<16; i++) {
    const d = document.createElement("div");
    d.className = "slot" + (i < pickerSyms.length ? (i<8?" filled-locked":" filled-free") : "");
    d.title = pickerSyms[i] ? pickerSyms[i].ticker : `Slot ${i}`;
    el.appendChild(d);
  }
}

function showSectors() {
  document.getElementById("sectorSection").style.display = "";
  document.getElementById("stockSection").style.display  = "none";
  const grid = document.getElementById("sectorGrid");
  grid.innerHTML = "";
  SECTORS.forEach(s => {
    const avail = UNIVERSE[s].filter(t => !pickerSyms.find(x=>x.ticker===t)).length;
    if (avail === 0) return;
    const b = document.createElement("button");
    b.className = "sector-btn";
    b.innerHTML = `<b>${s}</b> <span style="float:right;color:var(--muted);font-size:11px">${avail} stocks</span>`;
    b.onclick = () => selectSector(s);
    grid.appendChild(b);
  });
}

function selectSector(sector) {
  pickerSector = sector;
  pickerStockSel.clear();
  document.getElementById("sectorSection").style.display = "none";
  document.getElementById("stockSection").style.display  = "";
  document.getElementById("stockSectorLabel").textContent = sector;
  const list = document.getElementById("stockList");
  list.innerHTML = "";
  const available = UNIVERSE[sector].filter(t => !pickerSyms.find(x=>x.ticker===t));
  const remaining = 16 - pickerSyms.length;

  // Random add bar
  const randomBar = document.createElement("div");
  randomBar.style = "display:flex;align-items:center;gap:8px;margin-bottom:12px;padding:8px 10px;background:rgba(56,189,248,.06);border-radius:8px;border:1px solid var(--border);";
  randomBar.innerHTML = `
    <span style="font-size:12px;color:var(--muted);">Randomly add</span>
    <input id="randomCount" type="number" min="1" max="${Math.min(available.length,remaining)}"
      value="1" style="width:52px;padding:4px 8px;border-radius:6px;border:1px solid var(--border);
      background:var(--bg);color:var(--txt);font-family:'JetBrains Mono',monospace;font-size:13px;">
    <span style="font-size:12px;color:var(--muted);">from ${sector}</span>
    <button onclick="randomAdd('${sector}')" style="padding:4px 12px;border-radius:6px;border:none;
      background:var(--accent);color:#000;font-size:12px;font-weight:600;cursor:pointer;">Add Random</button>
  `;
  list.appendChild(randomBar);

  available.forEach(ticker => {
    const data = STOCK_DATA[ticker] || {mid:0,spread:0};
    const div  = document.createElement("div");
    div.className = "stock-item";
    div.innerHTML = `<input type="checkbox" id="chk_${ticker}">
      <label for="chk_${ticker}" style="cursor:pointer;flex:1">
        <b>${ticker}</b>
        <span style="float:right;color:var(--muted);font-size:11px">$${data.mid.toFixed(0)}</span>
      </label>`;
    div.querySelector("input").onchange = (e) => {
      if (e.target.checked) pickerStockSel.add(ticker);
      else pickerStockSel.delete(ticker);
      div.classList.toggle("picked", e.target.checked);
    };
    list.appendChild(div);
  });
}

function randomAdd(sector) {
  const count = parseInt(document.getElementById("randomCount").value) || 1;
  const available = UNIVERSE[sector].filter(t => !pickerSyms.find(x=>x.ticker===t));
  const remaining = 16 - pickerSyms.length;
  const n = Math.min(count, available.length, remaining);
  if (n === 0) { alert("No slots remaining or no stocks available."); return; }
  // Shuffle and pick n
  const shuffled = [...available].sort(() => Math.random() - 0.5).slice(0, n);
  shuffled.forEach(ticker => {
    const phase = pickerSyms.length < 8 ? 1 : 2;
    if (phase === 1) {
      const locked = LOCKED_PRICES[pickerSyms.length];
      pickerSyms.push({ticker, mid:locked.mid, spread:locked.spread});
    } else {
      const data = STOCK_DATA[ticker] || {mid:100, spread:0.10};
      pickerSyms.push({ticker, mid:data.mid, spread:data.spread});
    }
  });
  renderPicker();
}

function backToSectors() {
  pickerStockSel.clear();
  showSectors();
}

function confirmStocks() {
  if (pickerStockSel.size === 0) { alert("Select at least one stock."); return; }
  const remaining = 16 - pickerSyms.length;
  if (pickerStockSel.size > remaining) {
    alert(`Only ${remaining} slots left. Deselect ${pickerStockSel.size-remaining} stocks.`);
    return;
  }
  pickerStockSel.forEach(ticker => {
    const phase = pickerSyms.length < 8 ? 1 : 2;
    if (phase === 1) {
      // locked price slot
      const locked = LOCKED_PRICES[pickerSyms.length];
      pickerSyms.push({ticker, mid:locked.mid, spread:locked.spread});
    } else {
      const data = STOCK_DATA[ticker] || {mid:100, spread:0.10};
      pickerSyms.push({ticker, mid:data.mid, spread:data.spread});
    }
  });
  renderPicker();
}

function resetPicker() {
  pickerSyms = [];
  renderPicker();
}

function useDefault() {
  pickerSyms = [
    {ticker:"AAPL",mid:180,spread:0.10},{ticker:"MSFT",mid:420,spread:0.15},
    {ticker:"GOOG",mid:175,spread:0.12},{ticker:"META",mid:510,spread:0.20},
    {ticker:"NVDA",mid:900,spread:0.25},{ticker:"AMD", mid:160,spread:0.08},
    {ticker:"INTC",mid: 31,spread:0.05},{ticker:"AVGO",mid:170,spread:0.18},
    {ticker:"AMZN",mid:185,spread:0.10},{ticker:"TSLA",mid:250,spread:0.30},
    {ticker:"JPM", mid:200,spread:0.08},{ticker:"GS",  mid:470,spread:0.22},
    {ticker:"JNJ", mid:155,spread:0.06},{ticker:"PFE", mid: 27,spread:0.04},
    {ticker:"XOM", mid:105,spread:0.07},{ticker:"CVX", mid:155,spread:0.09},
  ];
  renderPicker();
}

async function applySymbols() {
  if (pickerSyms.length !== 16) { alert("Need exactly 16 symbols."); return; }
  const btn = document.getElementById("applyBtn");
  btn.textContent = "Applying...";
  btn.disabled = true;
  try {
    const r = await fetch("/api/set_symbols", {
      method:"POST",
      headers:{"Content-Type":"application/json"},
      body:JSON.stringify({symbols:pickerSyms})
    });
    const d = await r.json();
    if (d.ok) { closeModal(); history = {}; prevPrices = {}; }
    else alert("Failed: " + (d.error||"unknown error"));
  } catch(e) { alert("Network error: " + e); }
  btn.textContent = "Apply to Hardware";
  btn.disabled = false;
}

// Init
initChart();
</script>
</body>
</html>"""

def _make_html() -> bytes:
    with _lock:
        syms = list(_symbols)
    html = _HTML
    html = html.replace("__UNIVERSE_JSON__", json.dumps(UNIVERSE))
    html = html.replace("__STOCK_DATA_JSON__", json.dumps({
        k: {"mid": v[0], "spread": v[1]} for k, v in STOCK_DATA.items()
    }))
    return html.encode("utf-8")

# ── HTTP handler ──────────────────────────────────────────────────
class Handler(BaseHTTPRequestHandler):
    def _send_json(self, data, status=200):
        body = json.dumps(data).encode()
        self.send_response(status)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", len(body))
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()
        self.wfile.write(body)

    def do_GET(self):
        path = self.path.split("?")[0]
        if path in ("/", "/index.html"):
            body = _make_html()
            self.send_response(200)
            self.send_header("Content-Type", "text/html; charset=utf-8")
            self.send_header("Content-Length", len(body))
            self.end_headers()
            self.wfile.write(body)
        elif path == "/api/prices":
            with _lock:
                data = dict(_latest)
            self._send_json(data)
        elif path == "/api/status":
            with _lock:
                data = {k:v for k,v in _latest.items() if k != "prices"}
            self._send_json(data)
        else:
            self.send_response(404); self.end_headers()

    def do_POST(self):
        global _symbols
        length = int(self.headers.get("Content-Length", 0))
        body   = json.loads(self.rfile.read(length) or b"{}")
        path   = self.path.split("?")[0]

        if path == "/api/set_regime":
            val = int(body.get("regime", 0)) & 0x3
            if _mmio:
                _mmio.write(REGIME, val)
            with _lock:
                if _latest:
                    _latest["regime"] = val
                    _latest["regime_name"] = REGIME_NAMES.get(val, "?")
            self._send_json({"ok": True, "regime": val})

        elif path == "/api/set_symbols":
            syms = body.get("symbols", [])
            if len(syms) != 16:
                self._send_json({"ok": False, "error": "Need exactly 16 symbols"}, 400)
                return
            with _lock:
                _symbols = syms
            if _mmio:
                try:
                    _mmio.write(CTRL, 0x02); time.sleep(0.05)
                    for i, s in enumerate(syms):
                        _mmio.write(INIT_MID_BASE    + 4*i, q16_16(s["mid"]))
                        _mmio.write(INIT_SPREAD_BASE + 4*i, q16_16(s["spread"]))
                    _mmio.write(ACTIVE_SYM_COUNT, 16)
                    _mmio.write(0x04, 1000)
                    _mmio.write(0x08, 0xDEADBEEF)
                    _mmio.write(REGIME, 0)
                    _mmio.write(CTRL, 0x01)
                    self._send_json({"ok": True})
                except Exception as e:
                    self._send_json({"ok": False, "error": str(e)}, 500)
            else:
                self._send_json({"ok": True})  # demo mode

        elif path == "/api/start":
            if _mmio: _mmio.write(CTRL, 0x01)
            self._send_json({"ok": True})

        elif path == "/api/reset":
            if _mmio: _mmio.write(CTRL, 0x02)
            self._send_json({"ok": True})

        else:
            self.send_response(404); self.end_headers()

    def log_message(self, fmt, *args):
        pass

# ── Main ──────────────────────────────────────────────────────────
def main():
    global _mmio, _demo, _symbols

    parser = argparse.ArgumentParser()
    parser.add_argument("--bitfile", default="overlays/board_a.bit")
    parser.add_argument("--port",    default=8090, type=int)
    parser.add_argument("--hz",      default=20.0, type=float)
    parser.add_argument("--demo",    action="store_true")
    parser.add_argument("--config",  default="symbols.json")
    args = parser.parse_args()

    # Load symbol config
    try:
        with open(args.config) as f:
            _symbols = json.load(f)
        print(f"Loaded {len(_symbols)} symbols from {args.config}")
    except Exception:
        print("Using default symbols")

    _demo = args.demo or not _try_import_pynq()

    if not _demo:
        try:
            from pynq import Overlay, MMIO
            ol    = Overlay(args.bitfile)
            base  = ol.ip_dict["hft_core"]["phys_addr"]
            rng   = ol.ip_dict["hft_core"]["addr_range"]
            _mmio = MMIO(base, rng)
            print(f"Board A loaded: {args.bitfile}")
        except Exception as e:
            print(f"Board A load failed: {e} — running in demo mode")
            _demo = True
    else:
        print("Demo mode — simulated prices")

    threading.Thread(target=_poll_loop, args=(args.hz,), daemon=True).start()
    time.sleep(0.1)

    print(f"\nDual-FPGA Trading Dashboard: http://<pynq-ip>:{args.port}/")
    print(f"On your laptop: open http://192.168.3.1:{args.port}/ in your browser")
    print("Ctrl+C to stop.\n")
    try:
        HTTPServer(("0.0.0.0", args.port), Handler).serve_forever()
    except KeyboardInterrupt:
        print("Stopped.")


def _try_import_pynq():
    try:
        import pynq
        return True
    except ImportError:
        return False


if __name__ == "__main__":
    main()