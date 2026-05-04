# TradeMark React UI + PYNQ notebook bridge — runbook

This guide explains how to run the **React TradeMark UI** on a laptop while **Board B PYNQ Jupyter** pushes live AXI telemetry over HTTP (no UART).

You will run **two laptop processes** (API + React dev server) and **one PYNQ notebook flow** (configure/arm + monitor/push).

---

## What runs where

| Machine | What you run | Purpose |
|---|---|---|
| Laptop | `react_boardb_server.py --ingest-http --host 0.0.0.0 --api-port 8765` | FastAPI + WebSocket ingest (`POST /api/ingest`) |
| Laptop | `npm run dev` in `sw/laptop/frontend` | React UI (Vite) |
| Board B PYNQ | Jupyter cells (`live_monitor.py` + `live_monitor_simple.py`) | Read MMIO + POST snapshots to laptop |

---

## Prerequisites

### Laptop (Windows)

- Python **3.10+** recommended
- Node.js **LTS** (includes `npm`) — required for the React UI
- This repo checked out on disk

### Board B (PYNQ)

- Board B overlay available at `overlays/board_b.bit` (as used by the monitor scripts)
- `requests` available in the PYNQ Python environment (install instructions below)

---

## Part A — Laptop setup (one-time)

### A1) Create the Python venv + install dependencies

PowerShell:

```powershell
cd C:\ECE554\Dual-FPGA-Trading-Engine\sw\laptop
py -m venv .venv
.\.venv\Scripts\Activate.ps1
pip install -r requirements.txt
```

If PowerShell blocks activation:

```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
.\.venv\Scripts\Activate.ps1
```

### A2) Install Node deps for the React UI

PowerShell:

```powershell
cd C:\ECE554\Dual-FPGA-Trading-Engine\sw\laptop\frontend
$env:Path = "C:\Program Files\nodejs;" + $env:Path
npm install
```

---

## Part B — Laptop “every time you demo”

You need **two terminals** open.

### B1) Terminal 1 — start the ingest API (must listen on all interfaces)

PowerShell:

```powershell
cd C:\ECE554\Dual-FPGA-Trading-Engine\sw\laptop
.\.venv\Scripts\Activate.ps1
python react_boardb_server.py --ingest-http --host 0.0.0.0 --api-port 8765
```

Sanity checks:

- Local health: `http://127.0.0.1:8765/api/health` should return JSON including `"demo":"false"`

### B1b) Windows firewall (only if PYNQ can’t reach the laptop)

If the PYNQ can ping/curl fails intermittently, allow inbound TCP **8765** (Admin PowerShell example):

```powershell
New-NetFirewallRule -DisplayName "TradeMark ingest 8765" -Direction Inbound -Action Allow -Protocol TCP -LocalPort 8765 -Profile Any
```

### B2) Terminal 2 — start the React dev server

PowerShell:

```powershell
cd C:\ECE554\Dual-FPGA-Trading-Engine\sw\laptop\frontend
$env:Path = "C:\Program Files\nodejs;" + $env:Path
npm run dev
```

Open:

- `http://localhost:5173/`

---

## Part C — Figure out the laptop IP the PYNQ should use

Your PYNQ may reach the laptop via:

- **USB gadget / RNDIS style link**: commonly laptop is `192.168.4.2` and PYNQ `usb0` is `192.168.4.1`
- **Wi‑Fi / campus LAN**: laptop will be something like `10.x.x.x`

### C1) On Windows, confirm the address

PowerShell:

```powershell
ipconfig
```

Pick the IPv4 on the interface that actually connects to the PYNQ for this demo.

### C2) On PYNQ Jupyter, verify HTTP connectivity

Replace the IP below with your laptop IP from `ipconfig`:

```python
!curl -m 2 -sS http://<LAPTOP_IP>:8765/api/health
```

Expected:

- HTTP 200
- JSON includes `"demo":"false"`

---

## Part D — PYNQ Jupyter notebook flow

The repo contains:

- `sw/board_b/live_monitor.py` — includes `configure_and_arm()` (writes config + start pulses)
- `sw/board_b/live_monitor_simple.py` — reads AXI + optional `monitor(push_http=True)` to POST to the laptop

### D0) Install `requests` on PYNQ (one-time per image)

```python
import sys, subprocess
subprocess.check_call([sys.executable, "-m", "pip", "install", "-q", "requests"])
```

### D1) Set `API_BASE` in `live_monitor_simple.py`

Edit this line to match **your** laptop IP:

- `API_BASE = "http://<LAPTOP_IP>:8765"`

Or override in-notebook after loading the script:

```python
API_BASE = "http://<LAPTOP_IP>:8765"
```

### D2) Notebook cells (recommended order)

**Cell 1 — load trading helper + MMIO**

Paste/run `sw/board_b/live_monitor.py` (or `%run` it from the repo root).

**Cell 2 — arm/configure/start**

```python
configure_and_arm()
# Optional tuning example:
# configure_and_arm(threshold=0x00004000, max_position=2000)
```

**Cell 3 — load simple monitor + website bridge**

Paste/run `sw/board_b/live_monitor_simple.py` (or `%run` it from the repo root).

**Cell 4 — stream to website**

```python
monitor(push_http=True)
```

Stop with **Interrupt kernel** / notebook stop.

---

## Common failure modes (quick)

### “React UI loads but data looks dummy”

- You started the API with `--demo` (demo mode). Ingest mode must show `"demo":"false"` at `/api/health`.

### “PYNQ can’t reach laptop”

- Wrong laptop IP for the link you’re using (USB `192.168.4.x` vs Wi‑Fi `10.x.x.x`)
- API not started with `--host 0.0.0.0`
- Windows firewall blocking inbound TCP 8765

### “No trades, but registers update”

That’s trading/risk/strategy gating — not the website pipeline. Use `configure_and_arm(...)` parameters and verify:

- FSM is `B_TRADING`
- `link_up` is true
- `risk_halt` is false
- counters `orders_sent` / `fills_rcvd` move

---

## Optional: production-ish mode (single laptop port)

Build static files and let FastAPI serve them:

```powershell
cd C:\ECE554\Dual-FPGA-Trading-Engine\sw\laptop\frontend
npm run build
cd ..
python react_boardb_server.py --ingest-http --host 0.0.0.0 --api-port 8765 --browser
```

Then open `http://127.0.0.1:8765/` on the laptop.

---

## Files involved

- `sw/laptop/react_boardb_server.py` — FastAPI server (`--ingest-http`, `/api/ingest`, `/ws/stream`)
- `sw/laptop/frontend/` — React UI (Vite)
- `sw/board_b/live_monitor.py` — `configure_and_arm()`
- `sw/board_b/live_monitor_simple.py` — AXI snapshot + `monitor(push_http=True)`
