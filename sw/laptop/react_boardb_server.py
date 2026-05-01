#!/usr/bin/env python3
"""
TradeMark Board B — FastAPI backend for the React UI
=====================================================
Reuses ``SerialTelemetryReader`` / ``DemoTelemetryReader`` from ``board_b_dashboard.py``
(no duplicate ingest logic). Serves:

- ``GET /api/meta`` — symbol names, defaults
- ``GET /api/snapshot`` — one-shot same shape as WebSocket payload
- ``WebSocket /ws/stream`` — JSON telemetry ~4 Hz + optional client prefs
- ``POST /api/connect`` — UART connect (ignored in ``--demo``)
- ``POST /api/demo-risk`` — demo-only risk overrides
- ``GET /api/export/csv`` — cash / reject history CSV
- Static ``frontend/dist`` when built (``npm run build``), else CORS for Vite dev on :5173

Run (dev: API + use Vite for UI):

    pip install fastapi uvicorn websockets
    python3 react_boardb_server.py --demo --api-port 8765

Then in ``frontend/``: ``npm install && npm run dev`` and open http://127.0.0.1:5173/

Run (prod: API serves built React):

    cd frontend && npm install && npm run build && cd ..
    python3 react_boardb_server.py --demo --api-port 8765
    open http://127.0.0.1:8765/
"""

from __future__ import annotations

import argparse
import asyncio
import csv
import io
import json
import sys
import threading
import time
import webbrowser
from pathlib import Path
from typing import Any, Dict, List, Optional

# Telemetry readers without Dash dependency.
import board_b_telemetry as bbd

from fastapi import FastAPI, WebSocket, WebSocketDisconnect
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import FileResponse, HTMLResponse, StreamingResponse
from fastapi.staticfiles import StaticFiles

READER: Optional[bbd.SerialTelemetryReader] = None
DEMO_MODE: bool = False
HERE = Path(__file__).resolve().parent
FRONTEND_DIST = HERE / "frontend" / "dist"


def _build_payload(history_sec: float, ema_idx: int) -> Dict[str, Any]:
    assert READER is not None
    latest, rates, age_ms, connected, heartbeat = READER.snapshot()
    regime_edge = READER.pop_regime_edge()
    events = READER.events_snapshot()
    t_rel, cash_h, pnl_h, port_h = READER.history_profit_arrays(history_sec)
    t_act, q_h, o_h, f_h, r_h = READER.history_activity_arrays(history_sec)
    try:
        ei = int(ema_idx) % bbd.NUM_SYMBOLS
    except (TypeError, ValueError):
        ei = 0
    t_sym, mid_h, ema_h = READER.symbol_series(ei)
    return {
        "ts": time.time(),
        "meta": {
            "symbols": list(bbd.SYMBOL_NAMES),
        },
        "latest": latest,
        "rates": rates,
        "age_ms": age_ms,
        "connected": connected,
        "heartbeat": heartbeat,
        "hardware_stalled": READER.hardware_stalled,
        "parse_errors": READER.parse_errors,
        "events": events[-120:],
        "regime_edge": regime_edge,
        "series": {
            "history_sec": history_sec,
            "ema_symbol": ei,
            "t_cash": t_rel,
            "cash": cash_h,
            "pnl": pnl_h,
            "port": port_h,
            "t_act": t_act,
            "quotes": q_h,
            "orders": o_h,
            "fills": f_h,
            "rejects": r_h,
            "t_sym": t_sym,
            "mid": mid_h,
            "ema": ema_h,
        },
    }


def create_app() -> FastAPI:
    app = FastAPI(title="TradeMark Board B API", version="1.0")

    app.add_middleware(
        CORSMiddleware,
        allow_origins=[
            "http://127.0.0.1:5173",
            "http://localhost:5173",
            "http://127.0.0.1:4173",
            "http://localhost:4173",
        ],
        allow_credentials=True,
        allow_methods=["*"],
        allow_headers=["*"],
    )

    @app.get("/api/health")
    def health() -> Dict[str, str]:
        return {"ok": "true", "demo": str(DEMO_MODE).lower()}

    @app.get("/api/meta")
    def meta() -> Dict[str, Any]:
        return {
            "symbols": list(bbd.SYMBOL_NAMES),
            "num_symbols": bbd.NUM_SYMBOLS,
            "default_history_sec": bbd.DEFAULT_HISTORY_SEC,
            "regime_labels": list(bbd.REGIME_LABELS),
            "demo_mode": DEMO_MODE,
            "num_hist_bins": bbd.NUM_HIST_BINS,
            "hist_bin_cycles": bbd.HIST_BIN_CYCLES,
            "ns_per_cycle": bbd.NS_PER_CYCLE,
        }

    @app.get("/api/snapshot")
    def snapshot(
        history_sec: float = bbd.DEFAULT_HISTORY_SEC,
        ema_symbol: int = 0,
    ) -> Dict[str, Any]:
        return _build_payload(float(history_sec), int(ema_symbol))

    @app.post("/api/connect")
    def connect(body: Dict[str, Any]) -> Dict[str, Any]:
        if DEMO_MODE or READER is None:
            return {"ok": False, "msg": "Connect is only for UART mode (omit --demo)."}
        port = str(body.get("port") or "").strip()
        baud = int(body.get("baud") or 115200)
        if not port:
            return {"ok": False, "msg": "port required"}
        READER._port = port
        READER._baud = baud
        ok = READER.open_serial()
        return {"ok": ok, "msg": "opened" if ok else "open failed"}

    @app.post("/api/demo-risk")
    def demo_risk(body: Dict[str, Any]) -> Dict[str, str]:
        if not DEMO_MODE or READER is None:
            return {"msg": "demo-risk only works in --demo mode."}
        msg = READER.apply_demo_risk_overrides(body)
        return {"msg": msg}

    @app.get("/api/export/csv")
    def export_csv(history_sec: float = bbd.DEFAULT_HISTORY_SEC) -> StreamingResponse:
        assert READER is not None
        t_rel, cash_h, rej_h = READER.history_arrays(float(history_sec))
        buf = io.StringIO()
        w = csv.writer(buf)
        w.writerow(["t_rel_s", "cash_usd", "reject_rate_per_s"])
        for i in range(len(t_rel)):
            w.writerow([f"{t_rel[i]:.3f}", f"{cash_h[i]:.4f}", f"{rej_h[i]:.4f}"])
        data = buf.getvalue()
        return StreamingResponse(
            iter([data]),
            media_type="text/csv",
            headers={"Content-Disposition": "attachment; filename=board_b_export.csv"},
        )

    @app.websocket("/ws/stream")
    async def ws_stream(websocket: WebSocket) -> None:
        await websocket.accept()
        history_sec = float(bbd.DEFAULT_HISTORY_SEC)
        ema_idx = 0
        try:
            while True:
                try:
                    raw = await asyncio.wait_for(websocket.receive_text(), timeout=0.05)
                    msg = json.loads(raw)
                    if isinstance(msg, dict):
                        if "history_sec" in msg:
                            history_sec = max(5.0, min(3600.0, float(msg["history_sec"])))
                        if "ema_symbol" in msg:
                            ema_idx = int(msg["ema_symbol"]) % bbd.NUM_SYMBOLS
                except asyncio.TimeoutError:
                    pass
                except json.JSONDecodeError:
                    pass
                payload = _build_payload(history_sec, ema_idx)
                await websocket.send_text(json.dumps(payload))
                await asyncio.sleep(0.22)
        except WebSocketDisconnect:
            return

    @app.get("/api")
    def api_root() -> Dict[str, Any]:
        return {
            "service": "TradeMark Board B API",
            "docs": "/docs",
            "websocket": "/ws/stream",
            "ui": "Build frontend (npm run build) or run Vite dev on :5173",
        }

    assets_dir = FRONTEND_DIST / "assets"
    if assets_dir.is_dir():
        app.mount("/assets", StaticFiles(directory=str(assets_dir)), name="vite_assets")

    @app.get("/")
    def index_html() -> Any:
        idx = FRONTEND_DIST / "index.html"
        if idx.is_file():
            return FileResponse(idx)
        return HTMLResponse(
            "<html><body style='font-family:system-ui;padding:24px'>"
            "<h1>TradeMark Board B API</h1>"
            "<p><a href='/docs'>OpenAPI docs</a></p>"
            "<p>React UI: <code>cd frontend && npm install && npm run dev</code> "
            "then open <code>http://127.0.0.1:5173</code></p>"
            "<p>Production: <code>cd frontend && npm run build</code> then reload this page.</p>"
            "</body></html>"
        )

    return app


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="FastAPI server for TradeMark React UI")
    p.add_argument("--demo", action="store_true", help="Synthetic telemetry (same as Dash demo)")
    p.add_argument("--port", default="", help="UART device when not using --demo")
    p.add_argument("--baud", type=int, default=115200)
    p.add_argument("--host", default="127.0.0.1")
    p.add_argument(
        "--api-port",
        type=int,
        default=8765,
        help="HTTP port for API + static (avoid 8050 used by Dash)",
    )
    p.add_argument("--browser", action="store_true", help="Open API/static URL after start")
    p.add_argument(
        "--no-open",
        action="store_true",
        help="Do not open UART until POST /api/connect (non-demo only)",
    )
    return p.parse_args()


def main() -> None:
    global READER, DEMO_MODE
    args = parse_args()
    DEMO_MODE = bool(args.demo)

    if args.demo:
        READER = bbd.DemoTelemetryReader()
        READER.open_serial()
        READER.start()
        print("Demo mode — synthetic telemetry (no UART).")
    else:
        port = str(args.port or "").strip()
        if not port and sys.platform == "darwin":
            port = ""
        elif not port and sys.platform != "win32":
            port = "/dev/ttyUSB0"
        elif not port and sys.platform == "win32":
            port = "COM5"
        READER = bbd.SerialTelemetryReader(port, args.baud)
        if not args.no_open and port:
            READER.open_serial()
        READER.start()
        print(f"UART: {port or '(none — use POST /api/connect)'} @ {args.baud}")

    app = create_app()

    import uvicorn

    display_host = "127.0.0.1" if args.host in ("0.0.0.0", "::") else args.host
    url = f"http://{display_host}:{args.api_port}/"
    print(f"API + UI: {url}")
    print("  React dev: cd frontend && npm run dev  →  http://127.0.0.1:5173")
    print("  React prod: cd frontend && npm run build  →  served from this port")
    print("  OpenAPI: ", f"http://{display_host}:{args.api_port}/docs")

    if args.browser:

        def _open() -> None:
            time.sleep(0.8)
            webbrowser.open(url)

        threading.Thread(target=_open, daemon=True).start()

    uvicorn.run(app, host=args.host, port=args.api_port, log_level="info")


if __name__ == "__main__":
    main()
