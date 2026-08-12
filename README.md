# TradeMark — Dual-FPGA Trading Engine

Closed-loop trading system on **two AMD AUP-ZU3** boards (Zynq UltraScale+ **XCZU3EG-2SFVC784E**). Board A is the market simulator + exchange-lite. Board B is a pipelined trader. They talk over a custom full-duplex **4-bit PMOD** framed link with valid/ready backpressure.

This is the ECE 554 capstone repo (Rev B2). The full hardware/software contract is [`design_specification.md`](design_specification.md).

| Board | Role | FSM | Key RTL |
|-------|------|-----|---------|
| **A** | Market sim + exchange-lite | `RESET → IDLE → RUNNING ↔ STOPPED` | `market_sim`, `market_noise_gen`, `exchange_lite`, `tx_arbiter` |
| **B** | Trader (strategy + risk + telemetry) | `RESET → IDLE → ARMED → TRADING ↔ HALTED` | `quote_book`, `feature_compute`, `strategy_engine`, `risk_manager`, `order_manager`, `position_tracker` |

**Clock.** PS `FCLK0` at **100 MHz** clocks the PL on each board. The only CDC is the mesochronous 2-FF synchronizer on the PMOD RX path.

**Link.** 128-bit frames, 4-bit nibble + valid/ready, ~**1.47 M msg/s** theoretical capacity per direction, ~**2.07 μs** quote-to-fill RTT.

**Trader pipeline.** Mean-reversion + pending-order risk, Q16.16 / Q32.16 fixed point, **8 cycles (~80 ns)** tick-to-trade (quote in → order out) at 100 MHz.

**Universe.** 16 symbols, 4 regimes (`CALM` / `VOLATILE` / `BURST` / `ADVERSARIAL`), OU price model + 3-tier LFSR noise (global / sector / company).

**Host software.** PYNQ Overlay + AXI-Lite MMIO on each PS, UART JSON telemetry from Board B, Plotly Dash dashboard on the laptop.

---

## Table of contents

1. [Repository layout](#repository-layout)
2. [Prerequisites](#prerequisites)
3. [Golden model (run + extract values)](#golden-model)
4. [RTL simulation](#rtl-simulation)
5. [Vivado bitstreams](#vivado-bitstreams)
6. [PYNQ image and Jupyter](#pynq-image-and-jupyter)
7. [Hardware demo](#hardware-demo)
8. [AXI register maps](#axi-register-maps)
9. [Further reading](#further-reading)

---

## Repository layout

```
Dual-FPGA-Trading-Engine/
├── design_specification.md   Full Rev B2 spec (architecture, AXI maps, demo, testing)
├── README.md                 This file
├── requirements.txt          Laptop / mock-mode Python deps (Flask)
│
├── rtl/                      Production SystemVerilog (Board A + B + link)
├── rtl_nn/                   Experimental NN-strategy RTL variant
├── tb/                       SystemVerilog testbenches (mirrors rtl/) + xsim runner
├── sim/                      Questa / ModelSim `.do` compile + regression scripts
├── sim_tb_nn/                Extra NN top-level TB (`tb_board_b_top_nn.sv`)
├── constraints/              Pin / clock XDC for AUP-ZU3
├── vivado/                   Tcl BD scripts + generated Vivado projects
├── pynq/                     Packaged overlays + SD-card boot files
│
├── golden_model/             Bit-accurate Python golden model + vector dump
├── golden_model_nn/          PyTorch training / weight export for the NN stretch path
│
├── sw/                       PS scripts on each board + laptop dashboard
├── docs/                     Bring-up notes, stretch goals, progress reports
├── poster/                   36×48 conference poster (LaTeX)
├── progress_reports/         Dated LaTeX progress reports
├── images/                   Simulation waveform screenshots
│
├── web_server_a_updated.py   Board A browser UI (runs on PYNQ)
├── register_map_a_updated.py Board A AXI offsets used by the Board A UI
├── symbol_config.py          Interactive ticker picker (runs on PYNQ before start)
├── pynq_server.py            Board A HTTP price server (pairs with live_prices.py)
└── live_prices.py            Laptop terminal UI that talks to pynq_server.py
```

Generated / large trees you normally do **not** edit by hand:

| Path | What it is |
|------|------------|
| `vivado/hft_board_a/`, `vivado/hft_board_b/` | Current Vivado projects (BD, IP cache, runs) |
| `vivado/old_implementations/` | Snapshot bitstreams / projects from 04/28 and 05/01 |
| `pynq/overlays/` | Current `.bit` + `.hwh` plus dated overlay snapshots |
| `build/` | Local Verilator / xvlog work products |
| `sim/run_logs/` | Per-TB Questa transcripts |

### `rtl/` — production hardware

| Path | Contents |
|------|----------|
| `rtl/shared/hft_pkg.sv` | Types, enums (`MsgType`, regimes, strategies), Q-format helpers |
| `rtl/shared/lfsr32.sv` | 32-bit LFSR (market noise + deterministic seeds) |
| `rtl/shared/sync_fifo.sv` | Elastic buffer used on the link / pipeline |
| `rtl/shared/debounce.sv` | Button / switch debounce + edge pulse |
| `rtl/link/link_tx.sv` | 128-bit frame → 4-bit PMOD serializer + backpressure |
| `rtl/link/link_rx.sv` | 4-bit PMOD → 128-bit frame, 2-FF CDC, `link_up` |
| `rtl/board_a/` | Market sim, 3-tier noise, exchange-lite, TX arbiter, AXI-Lite (9-bit), FSM/LEDs, `board_a_top` + BD wrapper |
| `rtl/board_b/` | Quote book, EMA/features, mean-reversion strategy, risk, order mgr, position/P&L, latency histogram, AXI-Lite (10-bit), FSM, optional `nn_inference` + `policy_weights_4bit`, `board_b_top` + BD wrapper |

Compile order is always **package → shared → link → board_a → board_b**.

### `rtl_nn/`

Parallel tree used for the neural-strategy stretch path (`board_b_top_nn.sv`, `feature_compute_nn.sv`, `nn_interface.sv`, `position_tracker_nn.sv`). Same Board A / link layout. Do not mix this tree with `rtl/` in one Vivado project unless you intend to.

### `tb/`

Mirrors `rtl/`: `tb/shared/`, `tb/link/`, `tb/board_a/`, `tb/board_b/`, plus `tb/tb_system_top.sv` (A↔B over the mesochronous link).

| Script | Simulator | Usage |
|--------|-----------|--------|
| `tb/run_all.tcl` | Vivado **xsim** | `vivado -mode batch -source tb/run_all.tcl` from repo root |
| `tb/_xsim_runner.tcl` | xsim helper | Invoked by `run_all.tcl`; do not run alone |

Selector examples:

```bash
vivado -mode batch -source tb/run_all.tcl                 # full suite
vivado -mode batch -source tb/run_all.tcl -tclargs b2     # B2-touched TBs only
vivado -mode batch -source tb/run_all.tcl -tclargs tb_quote_book
```

Logs land in `sim_work/<tb>.log`.

### `sim/` — Questa / ModelSim `.do` files

All `.do` scripts assume the cwd is **`sim/`**.

| Script | Purpose |
|--------|---------|
| `compile_all.do` | Compile full RTL + all TBs into `work` |
| `compile_shared.do` / `compile_board_a.do` / `compile_board_b.do` / `compile_board_b_lite.do` | Subset compiles |
| `run_all.do` | Full regression (shared + A + B + system) |
| `run_all_shared.do` | Debounce, FIFO, LFSR, link TX/RX/loopback |
| `run_all_board_a.do` | Board A unit + `tb_board_a_top` |
| `run_all_board_b.do` / `run_all_board_b_lite.do` | Board B (full / without NN) |
| `run_all_top.do` | `tb_board_a_top`, `tb_board_b_top`, `tb_system_top` |
| `run_top_tests.do` | Alias for `run_all_top.do` |
| `run_focused.do` | Recently fixed + top integration TBs |
| `run_nn_only.do` | Just `tb_nn_inference` |
| `_run_lib.do` | Shared `run_one_test` helper (sourced by the others) |

### `constraints/`

`hft_top.xdc` — AUP-ZU3 PMOD JA/JB, switches, buttons, LEDs/RGB, `create_clock` on PS `FCLK_CLK0`. Pin names must match `board_*_top` ports exactly.

### `vivado/`

| File | Role |
|------|------|
| `create_board_a.tcl` / `create_board_b.tcl` | Create project, package `hft_core` IP, build BD, wrapper |
| `build.tcl` | Synth + impl + bitstream for the **currently open** project |
| `package_pynq.tcl` | Copy `.bit` + `.hwh` → `pynq/overlays/board_{a,b}.*` |
| `rebuild_all.tcl` | Wipe both project dirs and rebuild A then B (~25–40 min) |
| `export_hw.tcl` | Hardware handoff helper |

IP instance name expected by Python is **`hft_core`**. AXI windows: Board A **9-bit** (4 KiB allocated), Board B **10-bit** (4 KiB allocated). See spec Appendix D.

### `pynq/`

| Path | Role |
|------|------|
| `pynq/overlays/board_a.bit` + `board_a.hwh` | Overlay for Board A (same basename required) |
| `pynq/overlays/board_b.bit` + `board_b.hwh` | Overlay for Board B |
| `pynq/overlays/old_implementation/` | Dated overlay snapshots |
| `pynq/build_files/` | SD image pieces (`BOOT.BIN`, `image.ub`, `boot.py`, wheels) |

### `golden_model/`

Bit-accurate Python twin of the RTL algorithms and 128-bit frame packing.

| File | Role |
|------|------|
| `common.py` | Q-format, frame structs, LFSR, link delay model, 16-ticker universe |
| `board_a.py` | OU market + 3-tier noise + exchange-lite |
| `board_b.py` | EMA / strategy / risk / orders / positions |
| `run.py` | Interactive closed-loop dashboard |
| `gen_test_vectors.py` | Dump hex/JSON vectors for RTL `$readmemh` |
| `gen_board_a_vectors.py` | Print LFSR / noise / price hex constants to stdout |
| `vectors/` | Last dumped vector files |

### `golden_model_nn/`

Same golden-model core plus PyTorch:

| File | Role |
|------|------|
| `train_nn.py` | Imitation net (HOLD/BUY/SELL) labeled by mean-reversion |
| `train_profit_nn.py` | Profit-oriented policy training |
| `export_weights.py` | Checkpoint → SystemVerilog `localparam` arrays |
| `verify_weights.py` | Quantized vs float sanity check |
| `policy_weights*.sv` | Exported weight packages consumed by `rtl/` / `rtl_nn/` |
| `profit_nn_*/`, `nn_out/` | Training runs / checkpoints |

### `sw/`

| Path | Where it runs | Role |
|------|---------------|------|
| `sw/board_a/config_symbols.py` | Board A PYNQ | Load tickers/sectors/mids, optional `--start` / `--status` / `--reset` |
| `sw/board_a/symbol_universe.py` | Board A | S&P catalog used by the config script |
| `sw/board_a/symbol_config_panel.py` | Board A | Jupyter-friendly picker UI |
| `sw/board_a/board_a_ps_test*.py` | Board A | AXI smoke / extensive register tests |
| `sw/board_b/telemetry_server.py` | Board B PYNQ | Configure trader + emit JSON lines on UART |
| `sw/board_b/register_map.py` | Board B | AXI offsets for Board B |
| `sw/board_b/api_server.py` | Board B | HTTP / SSE Robinhood-style dashboard on the board |
| `sw/board_b/live_monitor*.py`, `monitor.sh` | Board B | Terminal monitors |
| `sw/laptop/dashboard.py` | Laptop | Plotly Dash UI from UART JSON |
| `sw/laptop/symbols_default.json` | Laptop | Default 16-symbol display map |
| `sw/laptop/requirements.txt` | Laptop | `dash`, `plotly`, `pyserial` |
| `sw/dual_board_test_a.py` / `_b.py` | Each board | Paired Jupyter end-to-end test |

### Root Python (Board A demo path)

These sit at the repo root because they are uploaded next to the overlay on Board A:

| File | Role |
|------|------|
| `web_server_a_updated.py` | Combined AXI poller + browser UI (`--bitfile overlays/board_a.bit`) |
| `register_map_a_updated.py` | Board A offsets including B2/B3 live bid/ask/mid arrays |
| `symbol_config.py` | Interactive sector/ticker fill of 16 slots |
| `pynq_server.py` | Lightweight HTTP price API on the board |
| `live_prices.py` | Laptop Rich TUI: `python live_prices.py --ip 192.168.3.1` |

### `docs/`

| File | Role |
|------|------|
| `bringup.md` | Tcl bitstream build + Jupyter Overlay/MMIO smoke test |
| `hw_bringup.md` | Longer A→B hardware path (PMOD wiring, PS scripts, dashboard) |
| `adding_complexity.md` | Symbol-universe / UX design notes |
| `stretch_goals.md` | Unshipped ideas (proportional spread, etc.) |
| `updated_design_specification.md` | Stub → root [`design_specification.md`](design_specification.md) |
| `progress_report_2026-04-09.tex` | In-repo progress report source |

### `poster/`, `progress_reports/`, `images/`

- `poster/poster.tex` — 36×48 TradeMark poster (metrics, block diagram, results).
- `progress_reports/04_09/`, `04_16/` — dated report snapshots.
- `images/` — TB waveform PNGs (debounce, exchange, LFSR, link RX, market sim).

---

## Prerequisites

**Workstation**

- Vivado **2023.1+** with a Zynq UltraScale+ license
- Optional: **Questa / ModelSim** for `.do` regression (xsim works without it)
- Python 3.10+ on the laptop (`pip install -r requirements.txt` and `pip install -r sw/laptop/requirements.txt`)

**Boards (×2 AUP-ZU3)**

- microSD cards flashed with the **PYNQ ZU3EG** image ([pynq.io](http://www.pynq.io/boards.html))
- USB to PC (gadget / Jupyter / SSH / UART)
- Two straight PMOD cables: **JA↔JA** and **JB↔JB** (pin 1 to pin 1, 3.3 V LVCMOS)

Default Jupyter URL after USB boot: **`http://192.168.3.1:9090`**, password **`xilinx`**.

---

## Golden model

Use this before RTL or hardware. It is cycle-stepped and frame-accurate, so hex dumps can go straight into testbenches.

### Interactive closed loop

```bash
cd golden_model
python run.py
```

Optional flags:

```bash
python run.py --regime 1 --threshold 0.30 --sym 16
```

| Flag | Meaning |
|------|---------|
| `--regime` | `0` CALM, `1` VOLATILE (default), `2` BURST, `3` ADVERSARIAL |
| `--threshold` | Mean-reversion threshold in dollars |
| `--sym` | Active symbol count (first N of the 16-ticker universe) |

Keys while running: `c/v/b/a` regimes, `+/-` threshold ±$0.10, `s` start/stop trading, `r` reset, `q` quit.

### Dump vectors for RTL

```bash
cd golden_model
python gen_test_vectors.py
```

Writes `golden_model/vectors/`:

| File | Typical use |
|------|-------------|
| `lfsr_vectors.json` | `tb_lfsr32` |
| `noise_vectors.json` | `tb_market_noise_gen` |
| `quote_frames.hex`, `quote_vectors.json` | `tb_market_sim`, `$readmemh` |
| `exchange_vectors.json` | `tb_exchange_lite` fill/reject |
| `demux_vectors.json` | `tb_msg_demux` |
| `quote_book_vectors.json` | `tb_quote_book` |
| `feature_compute_vectors.json` | `tb_feature_compute` |
| `strategy_vectors.json` | `tb_strategy_engine` |
| `position_tracker_vectors.json` | `tb_position_tracker` |
| `latency_histogram_vectors.json` | `tb_latency_histogram` |
| `pipeline_vectors.json` | `tb_board_b_pipeline` / `tb_system_top` |

Stdout hex dump (copy into `localparam` arrays):

```bash
python gen_board_a_vectors.py
```

### Extract a single expected value in Python

```python
from common import (
    QuoteFrame, LFSR32, from_q16,
    default_init_mids, default_init_spreads, default_sector_ids,
)
from board_a import BoardA
from board_b import FeatureEngine

# LFSR sequence for a known seed
lfsr = LFSR32(0xDEADBEEF)
print([f"32'h{lfsr.step():08X}" for _ in range(8)])

# EMA / deviation (alpha = 6554 ≈ 0.1 in Q0.16).
# First call seeds EMA to mid and returns 0; second call is the real step.
fe = FeatureEngine(num_sym=16)
mid = default_init_mids()[0]          # AAPL init mid, Q16.16
fe.compute(symbol=0, mid=mid, alpha=6554)
dev = fe.compute(symbol=0, mid=mid + 1000, alpha=6554)
print(f"deviation Q16.16 = 32'h{dev & 0xFFFFFFFF:08X}  (${from_q16(dev):.4f})")

# Quote frame bits from a live Board A step
a = BoardA(num_sym=16, num_sectors=8)
a.configure(
    regime=0, quote_interval=0, seed=0xDEADBEEF,
    init_mid=default_init_mids(),
    init_spread=default_init_spreads(),
    sector_ids=default_sector_ids(),
    active_count=16,
)
a.start()
bits = a.step(0)
if bits is not None:
    qf = QuoteFrame.from_bits(bits)
    print(f"frame = 128'h{bits:032X}")
    print(f"sym={qf.symbol} bid=${from_q16(qf.bid):.2f} ask=${from_q16(qf.ask):.2f}")
```

Assert in SystemVerilog:

```systemverilog
assert (dut.deviation === 32'h<value_from_python>);
```

Q16.16 reminder: dollar value `x` → `int(x * 65536)`. Inverse: `reg / 65536.0`.

### NN golden path (optional)

```bash
cd golden_model_nn
python train_nn.py --cycles-per-regime 2000 --epochs 20 --output-dir nn_out
python export_weights.py --checkpoint profit_nn_out/model_best_v1_profitable.pth.tar
```

`export_weights.py` prints a `.sv` weight package. Copy into `rtl/board_b/` or `rtl_nn/board_b/` only after verifying with `verify_weights.py`.

---

## RTL simulation

### Questa / ModelSim (`.do` files)

From a GUI or `vsim -do`:

```tcl
cd sim
do run_all.do
```

Subset runs (still from `sim/`):

```tcl
do run_all_shared.do
do run_all_board_a.do
do run_all_board_b.do
do run_all_top.do
do run_nn_only.do
```

Compile only:

```tcl
do compile_all.do
```

Then run one TB by hand:

```tcl
do _run_lib.do
run_one_test tb_market_sim
```

Per-test transcripts: `sim/run_logs/<tb>.log`. The runner looks for `: PASS (`, `ALL TESTS PASSED`, or `PASSED:` + `FAILED: 0`, and fails on `** Fatal:` / `TESTBENCH FAILED`.

Batch-style from a shell (tool-dependent):

```bash
cd sim
vsim -c -do "do run_all.do; quit -f"
```

### Vivado xsim

```bash
# repo root
vivado -mode batch -source tb/run_all.tcl
```

See [tb/](#tb) for selectors. Work directory: `sim_work/`.

---

## Vivado bitstreams

From the **Vivado Tcl console**, cwd = **repo root**.

### One board at a time

```tcl
source vivado/create_board_a.tcl
source vivado/build.tcl
```

Then Board B (new project):

```tcl
source vivado/create_board_b.tcl
source vivado/build.tcl
```

Check: `synth_design Complete!`, `write_bitstream Complete!`, **WNS ≥ 0**.

Outputs:

- `vivado/hft_board_a/hft_board_a.runs/impl_1/system_wrapper.bit`
- `vivado/hft_board_a/hft_board_a.gen/sources_1/bd/system/hw_handoff/system.hwh`
- same relative paths under `vivado/hft_board_b/`

### Both boards, clean rebuild

```bash
vivado -mode batch -source vivado/rebuild_all.tcl
```

### Package overlays

```tcl
source vivado/package_pynq.tcl
```

Produces:

- `pynq/overlays/board_a.bit` + `board_a.hwh`
- `pynq/overlays/board_b.bit` + `board_b.hwh`

`.bit` and `.hwh` **must** share a basename and live in the same directory. PYNQ uses the `.hwh` to discover `hft_core` and its AXI base.

Manual packaging path (if you skip the Tcl helper) is documented in [`docs/hw_bringup.md`](docs/hw_bringup.md) §9–11.

---

## PYNQ image and Jupyter

### Flash and boot

1. Download the **ZU3EG PYNQ** `.img` from [pynq.io](http://www.pynq.io/boards.html).
2. Flash the microSD with **balenaEtcher** (or equivalent).
3. Insert the card, power the AUP-ZU3, wait ~30–60 s.
4. Connect USB (gadget mode). Jupyter: **`http://192.168.3.1:9090`**, password **`xilinx`**. Home directory is `/home/xilinx/`.

SSH (if enabled on your image): `ssh xilinx@192.168.3.1`.

### Upload overlays and scripts

On **each** board, create `overlays/` in Jupyter (New → Folder) or:

```bash
mkdir -p /home/xilinx/overlays
scp pynq/overlays/board_a.bit pynq/overlays/board_a.hwh xilinx@<BOARD_A_IP>:/home/xilinx/overlays/
scp pynq/overlays/board_b.bit pynq/overlays/board_b.hwh xilinx@<BOARD_B_IP>:/home/xilinx/overlays/
```

**Board A** also needs (upload to `/home/xilinx/` or `jupyter_notebooks/`):

- `sw/board_a/config_symbols.py`, `symbol_universe.py`, `symbol_config_panel.py`, `board_a_ps_test.py`
- and/or root `web_server_a_updated.py`, `register_map_a_updated.py`, `symbol_config.py`

**Board B:**

- `sw/board_b/telemetry_server.py`, `register_map.py` (and optionally `api_server.py`)

### Load the overlay in a new notebook

Do **not** reuse an old lab notebook. New notebook, first cell:

```python
from pynq import Overlay, MMIO

ol = Overlay('overlays/board_a.bit')   # or overlays/board_b.bit
print(list(ol.ip_dict.keys()))         # expect 'hft_core'

base = ol.ip_dict['hft_core']['phys_addr']
span = ol.ip_dict['hft_core']['addr_range']
mmio = MMIO(base, span)
```

If the key is not `hft_core`, print `ol.ip_dict.keys()` and pass `--ip-block <exact_key>` to the PS scripts.

### Board A AXI smoke test (notebook)

```python
print(f"STATUS:          0x{mmio.read(0xF4):08X}")   # running=0 before start
print(f"QUOTE_INTERVAL:  {mmio.read(0x04)}")         # default 1000
mmio.write(0x04, 500)
print(f"After write:     {mmio.read(0x04)}")
```

### Board B AXI smoke test (notebook)

```python
status = mmio.read(0x40)
print(f"STATUS:        0x{status:08X}")
print(f"  strategy:    {status & 0x3}")
print(f"  fsm_state:   {(status >> 2) & 0x7}")   # 1 = IDLE
print(f"  link_up:     {bool((status >> 5) & 1)}")
print(f"  risk_halt:   {bool((status >> 6) & 1)}")
print(f"STRATEGY_SEL:  {mmio.read(0x04)}")
print(f"THRESHOLD:     0x{mmio.read(0x08):08X}")
print(f"QUOTES_RCVD:   {mmio.read(0x44)}")
print(f"ORDERS_SENT:   {mmio.read(0x48)}")
```

### Board A browser UI (common demo path)

On Board A (Jupyter terminal or SSH), from the directory that contains the uploaded scripts and can see `overlays/`:

```bash
python web_server_a_updated.py --bitfile overlays/board_a.bit
```

Then in a notebook, reset + load 16 symbols + start:

```python
import time

mmio.write(0x00, 0x02)   # CTRL reset pulse
time.sleep(0.1)

symbols_config = [
    (180.00, 0.10), (420.00, 0.15), (175.00, 0.12), (510.00, 0.20),
    (900.00, 0.25), (160.00, 0.08), ( 31.00, 0.05), (170.00, 0.18),
    (185.00, 0.10), (250.00, 0.30), (200.00, 0.08), (470.00, 0.22),
    (155.00, 0.06), ( 27.00, 0.04), (105.00, 0.07), (155.00, 0.09),
]

for i, (mid, spr) in enumerate(symbols_config):
    mmio.write(0x10 + 4*i, int(mid * 65536) & 0xFFFFFFFF)   # INIT_MID
    mmio.write(0x50 + 4*i, int(spr * 65536) & 0xFFFFFFFF)   # INIT_SPREAD

mmio.write(0xF0, 16)       # ACTIVE_SYM_COUNT
mmio.write(0x04, 1000)     # QUOTE_INTERVAL
mmio.write(0x08, 0xDEADBEEF)
mmio.write(0x0C, 0)        # CALM
mmio.write(0x00, 0x01)     # CTRL start pulse
```

Laptop terminal UI against `pynq_server.py`:

```bash
# on Board A
python pynq_server.py --bitfile-a overlays/board_a.bit

# on laptop
python live_prices.py --ip 192.168.3.1
```

---

## Hardware demo

Wire **PMOD JA A↔B** and **JB A↔B** (straight, same orientation). Power both boards. USB both to the PC.

### Board A — configure + start

```bash
cd /home/xilinx/trading_sw/board_a   # or wherever you copied sw/board_a
python3 config_symbols.py --status
python3 config_symbols.py --start --tokens AAPL MSFT NVDA XOM
# or
python3 config_symbols.py --interactive --start
python3 config_symbols.py --reset   # pulse CTRL[1] before a reconfig
```

Useful flags: `--quote-interval`, `--lfsr-seed`, `--regime`, `--hw-slots`, `--write-sector-id` (default on).

### Board B — trader + telemetry

```bash
cd /home/xilinx/trading_sw/board_b
python3 telemetry_server.py --overlay /home/xilinx/overlays/board_b.bit
python3 telemetry_server.py --status
python3 telemetry_server.py --reset
```

Defaults: `--ip-block hft_core`, `--strategy 0` (mean-reversion), `--threshold 1.00`, `--poll-hz 20`. Stdout is **one JSON object per line** (UART → laptop).

Optional on-board HTTP UI:

```bash
sudo python3 api_server.py --initial-cash 1000000 --port 8080
```

### Laptop dashboard

```bash
pip install -r sw/laptop/requirements.txt
python sw/laptop/dashboard.py --port COM5 --baud 115200
python sw/laptop/dashboard.py --demo
python sw/laptop/dashboard.py --stdin   # pipe telemetry JSON
```

macOS/Linux serial device instead of `COM5`, e.g. `--port /dev/ttyUSB0`.

### Bring-up order

1. Both boards booted, PMOD seated, overlays loaded.
2. Start **Board A** quotes (`config_symbols.py --start` or notebook CTRL start).
3. Confirm Board A `STATUS.link_up` / `QUOTES_SENT` increment.
4. Start **Board B** (`telemetry_server.py`). Confirm `QUOTES_RCVD`, then `ORDERS_SENT` / `FILLS_RCVD`.
5. Open the laptop dashboard. Use Board A switches for regime; Board B SW[0] to leave ARMED → TRADING (see spec §4.4 / §5.6).

Troubleshooting table: [`docs/hw_bringup.md`](docs/hw_bringup.md) §17. Incremental 10-phase plan: spec §7.4.

---

## AXI register maps

Authoritative tables: [`design_specification.md`](design_specification.md) Appendix D. Quick smoke-test subset (B2):

### Board A (9-bit slave, 4 KiB window)

| Addr | Name | R/W |
|------|------|-----|
| `0x00` | CTRL `[0]=start [1]=reset` | W |
| `0x04` | QUOTE_INTERVAL | R/W |
| `0x08` | LFSR_SEED | R/W |
| `0x0C` | REGIME `[1:0]` | R/W |
| `0x10+4*i` | INIT_MID\[i\] Q16.16 | R/W |
| `0x50+4*i` | INIT_SPREAD\[i\] | R/W |
| `0x90+4*i` | SECTOR_ID\[i\] | R/W |
| `0xD0+4*j` | TOKEN\[j\] (two 16-bit tokens) | R/W |
| `0xF0` | ACTIVE_SYM_COUNT | R/W |
| `0xF4` | STATUS | R |
| `0xF8` / `0xFC` | QUOTES_SENT / ORDERS_RCVD | R |
| `0x100` / `0x104` / `0x108` | FILLS_SENT / REJECTS_SENT / LINK_ERRORS | R |
| `0x110+4*i` / `0x150+4*i` / `0x190+4*i` | LIVE_BID / ASK / MID | R |

### Board B (10-bit slave, 4 KiB window)

| Addr | Name | R/W |
|------|------|-----|
| `0x00` | CTRL `[0]=start [1]=reset` | W |
| `0x04` | STRATEGY_SEL | R/W |
| `0x08` | THRESHOLD Q16.16 | R/W |
| `0x0C` | EMA_ALPHA Q0.16 | R/W |
| `0x10` / `0x14` / `0x18` / `0x1C` | BASE_QTY / MAX_POSITION / MAX_ORDER_RATE / MAX_LOSS | R/W |
| `0x40` | STATUS `{risk_halt, link_up, fsm[2:0], strategy[1:0]}` | R |
| `0x44` … `0x54` | QUOTES_RCVD / ORDERS_SENT / FILLS_RCVD / RISK_REJECTS / LINK_ERRORS | R |
| `0x58+4*i` | POSITION\[i\] signed | R |
| `0x98` / `0x9C` | CASH_LO / CASH_HI | R |
| `0xA0+4*i` | HIST_BIN\[i\] latency histogram | R |
| `0xE0` … `0xEC` | LAT_MIN / MAX / SUM / COUNT | R |
| `0x100+4*i` / `0x140+4*i` | BID\[i\] / ASK\[i\] (B2 dashboard) | R |
| `0x180+4*i` / `0x1C0+4*i` | PNL_CASH_LO/HI\[i\] | R |
| `0x200+4*i` / `0x240+4*j` | LAST_FILL_PRICE\[i\] / TRADES_PACK | R |

Python mirrors: `register_map_a_updated.py`, `sw/board_b/register_map.py`.

---

## Further reading

| Doc | Use when |
|-----|----------|
| [`design_specification.md`](design_specification.md) | Architecture, clocks, frames, FSMs, AXI, PS software, test plan |
| [`docs/bringup.md`](docs/bringup.md) | Vivado Tcl + Jupyter Overlay/MMIO first light |
| [`docs/hw_bringup.md`](docs/hw_bringup.md) | PMOD wiring, scp, `config_symbols.py` / `telemetry_server.py` / dashboard |
| [`golden_model/README.md`](golden_model/README.md) | Golden-model keys and universe table |
| [`poster/poster.tex`](poster/poster.tex) | Public metrics and block diagram |
| [`docs/stretch_goals.md`](docs/stretch_goals.md) | Ideas not in the B2 baseline |
