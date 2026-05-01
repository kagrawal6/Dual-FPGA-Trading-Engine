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
| **`dashboard.py`** | Different Robinhood-style cards; **same default port 8050** — only one can bind at a time. |

## Optional

- `python3 board_b_dashboard.py -h` — all CLI flags.  
- `symbols_default.json` — symbol names for the 16-ticker table when not overridden.
