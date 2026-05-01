# Laptop — TradeMark dashboard (`board_b_dashboard.py`)

Python **Dash + Plotly** UI that reads **newline-delimited JSON** from Board B (USB‑UART) or runs in **demo** mode with no hardware.

## Requirements

- Python 3.10+ recommended  
- Dependencies listed in **`requirements.txt`** (`dash`, `plotly`, `pyserial`)

## Install (venv recommended)

```bash
cd sw/laptop
python3 -m venv .venv
source .venv/bin/activate          # Windows: .venv\Scripts\activate
pip install -r requirements.txt
```

## Run — demo (no board, good for UI checkout)

```bash
source .venv/bin/activate
python3 board_b_dashboard.py --demo --browser
```

Open **http://127.0.0.1:8050/** (default). Hard-refresh after CSS changes: **Ctrl+Shift+R** / **Cmd+Shift+R**.

## Run — React UI (same Python telemetry, new front end)

The **FastAPI** server in **`react_boardb_server.py`** reuses **`SerialTelemetryReader` / `DemoTelemetryReader`** from `board_b_dashboard.py` (same JSON ingest and history buffers). You still need the same Python venv (`dash` is imported with that module even though the React UI does not use Dash).

**For demos / “everything fits” mode:** set your browser zoom to **50%** (Chrome/Edge: View → Zoom → 50%, or `Cmd+-` / `Ctrl+-`). The UI is intentionally dense and is tuned to show the whole terminal at once at reduced zoom.

**Terminal A — API (default port 8765, not 8050):**

```bash
cd sw/laptop
source .venv/bin/activate
pip install -r requirements.txt   # includes fastapi, uvicorn, websockets
python3 react_boardb_server.py --demo --api-port 8765
```

**Terminal B — React dev (Vite proxies `/api` and `/ws` to 8765):**

```bash
cd sw/laptop/frontend
npm install
npm run dev
```

Open **http://127.0.0.1:5173/**.

**Production (API also serves the built static bundle):**

```bash
cd sw/laptop/frontend && npm install && npm run build && cd ..
python3 react_boardb_server.py --demo --api-port 8765 --browser
```

Then open **http://127.0.0.1:8765/** (same port as the API).

UART mode matches Dash: omit **`--demo`**, pass **`--port`** / **`--baud`**, or use **`POST /api/connect`** from the React toolbar when the server was started with an empty port.

## Verify real data flow (Boards → WebSocket → UI)

The React UI is driven by the WebSocket stream:

- Board B UART emits **one JSON object per line**
- `react_boardb_server.py` reads UART (or `--demo`) and publishes JSON packets on **`ws://127.0.0.1:8765/ws/stream`**
- The React UI connects to that websocket (Vite dev proxy or production static on the same port)

### Jupyter notebook (optional but recommended)

If you want to “see the packets” independent of the UI, create a notebook using:

- `sw/laptop/notebooks/boardb_ws_smoke.ipynb`

It connects to `/ws/stream`, prints a few packets, and shows which fields are live/stale. This is the quickest way to validate the boards are actually driving the laptop.

### About “random companies” prompts from Board A

- The UI will always update for whatever **telemetry fields Board B is streaming** (prices, spreads, features, signal, regime, etc.).
- **Symbol names** are currently the fixed 16-ticker list unless your telemetry includes a symbol list field.
- If your upstream (Board A → Board B) pipeline sends `symbol_names` (or `symbols`) as a list of 16 names in the UART JSON, the laptop will **auto-update** the UI’s symbol labels live (no restart).

## Run — live UART

1. Connect Board B USB‑UART; find the port (macOS: `ls /dev/cu.*`, Linux: `ls /dev/ttyUSB*`, Windows: Device Manager → COM port).
2. On the PYNQ, run `telemetry_server.py` so one JSON object prints per line (see **`../board_b/README.md`**).
3. On the laptop:

```bash
source .venv/bin/activate
python3 board_b_dashboard.py --port /dev/cu.YOUR_DEVICE --baud 115200 --browser
```

Use **`--host 0.0.0.0`** only if other machines on the LAN must reach the Dash server (less private). **`--dash-port`** changes the HTTP port if 8050 is busy.

## Do not confuse with `dashboard.py`

| Script | Purpose |
|--------|---------|
| **`board_b_dashboard.py`** | TradeMark terminal (tabs, dense charts, this README). |
| **`react_boardb_server.py`** | FastAPI + WebSocket for the **React** UI; same telemetry readers (default HTTP **8765**). |
| **`dashboard.py`** | Different Robinhood-style cards; **same default port 8050** — only one can bind at a time. |

## Optional

- `python3 board_b_dashboard.py -h` — all CLI flags.  
- `symbols_default.json` — symbol names for the 16-ticker table when not overridden.
