# Board B — PYNQ PS instructions

Run this on the **Board B** PYNQ host (Zynq PS), after the Board B bitstream is loaded. These scripts use **PYNQ** (`Overlay`, `MMIO`) to read/write the `hft_core` AXI slave and stream **one JSON object per line** on **stdout**. That stream is what the laptop **TradeMark** dashboard consumes over **USB‑UART** (FTDI), so stdout must reach the UART that the PC sees as e.g. `/dev/cu.usbserial-*` (macOS) or `COM*` (Windows).

---

## 1. Get the repo on the PYNQ

```bash
# Example: adjust URL and path to your fork/layout
cd ~
git clone https://github.com/<org>/Dual-FPGA-Trading-Engine.git
cd Dual-FPGA-Trading-Engine
git checkout my-work-stretch-goals   # or whichever branch you test
```

You need **`telemetry_server.py`** and **`register_map.py`** in the same directory (as in `sw/board_b/` in this repo). Either work from `sw/board_b/` or copy both files to a folder on the board.

---

## 2. Dependencies (Board B PYNQ)

Use the system Python that has **PYNQ** installed (the image that shipped with the board). If you use a venv, install PYNQ into it only if you know that workflow; the default is **global PYNQ** from the PYNQ image.

```bash
cd ~/Dual-FPGA-Trading-Engine/sw/board_b   # or your copy path
python3 -c "from pynq import Overlay, MMIO; print('PYNQ OK')"
```

---

## 3. Overlay path

`telemetry_server.py` defaults to:

```text
--overlay overlays/board_b.bit
```

Place your built **`board_b.bit`** (and `.hwh` if your flow uses it) where that path resolves, **or** pass an absolute path:

```bash
python3 telemetry_server.py --overlay /home/xilinx/bitstreams/board_b.bit
```

The AXI IP name defaults to **`hft_core`**; override with `--ip-block <name>` if your overlay differs.

---

## 4. Quick health check (no telemetry loop)

Prints registers once and exits:

```bash
cd ~/Dual-FPGA-Trading-Engine/sw/board_b
python3 telemetry_server.py --overlay /path/to/board_b.bit --status
```

---

## 5. Configure, start FSM, and run the telemetry loop

This writes strategy / risk limits to MMIO, pulses **start** (unless disabled), then prints JSON lines at `--poll-hz` (default 20 Hz):

```bash
python3 telemetry_server.py \
  --overlay /path/to/board_b.bit \
  --strategy 0 \
  --threshold 1.0 \
  --ema-alpha 6554 \
  --base-qty 100 \
  --max-position 500 \
  --max-order-rate 1000 \
  --max-loss 100.0 \
  --poll-hz 20
```

**Strategy codes:** `0` MEAN_REV, `1` MOMENTUM, `2` NN, `3` AUTO (see `STRATEGY_NAMES` in `telemetry_server.py`).

Useful variants:

| Goal | Flags |
|------|--------|
| Write config only, do not start | `--no-start` |
| Write config + start, no JSON loop | `--no-telemetry` |
| Pulse reset before configure | `--reset` |

Stop the loop with **Ctrl+C**.

---

## 6. Link to the laptop TradeMark dashboard

1. Connect **Board B** USB‑UART to the laptop.
2. On the laptop (see top-level `README.md` or `python3 board_b_dashboard.py -h`):

```bash
cd ~/Dual-FPGA-Trading-Engine/sw/laptop
source .venv/bin/activate   # if you use the project venv
python3 board_b_dashboard.py --port /dev/cu.YOUR_DEVICE --baud 115200 --browser
```

3. In the UI, **Connect** if you did not pass `--port`, then confirm JSON is updating (status strip / heartbeat).

**Note:** The laptop dashboard **ingests** UART JSON only. Changing risk/strategy on **real hardware** is done here on the PYNQ via **`telemetry_server.py` flags** (or your own MMIO tool), then restart or re-run as needed. The TradeMark UI **Apply** for risk limits only mutates the **demo** synthetic stream unless you add a separate command channel.

---

## 7. System bring-up checklist (minimal)

1. Board A running with link up (quotes) if you expect traffic.
2. PMOD / link wiring as in your lab setup.
3. Board B bitstream loaded; `telemetry_server.py --status` looks sane.
4. `telemetry_server.py` running; UART shows one JSON line per sample.
5. Laptop `board_b_dashboard.py` on the correct serial port, same baud (default **115200** unless you changed both sides).

---

## 8. Related files

| File | Role |
|------|------|
| `telemetry_server.py` | MMIO read/write + JSON telemetry loop |
| `register_map.py` | AXI offsets shared with docs / RTL naming |
| `../laptop/board_b_dashboard.py` | TradeMark UI over serial |
| `../laptop/dashboard.py` | Different Robinhood-style UI (same default HTTP port if both run) |
