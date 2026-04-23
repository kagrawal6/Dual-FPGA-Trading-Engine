# FPGA Board Bring-Up Guide

Step-by-step instructions for building bitstreams and deploying them to the AUP-ZU3 PYNQ boards.

---

## Part 1: Building Bitstreams in Vivado

### Prerequisites
- Vivado 2023.1+ installed
- Project root: the `Dual-FPGA-Trading-Engine` directory

### Board A

1. Open Vivado
2. In the Tcl Console, `cd` to the project root:
   ```tcl
   cd {C:/Users/Kushal Agrawal/UW-madison school work/Dual-FPGA-Trading-Engine}
   ```
3. Create the Board A project and block design:
   ```tcl
   source vivado/create_board_a.tcl
   ```
   This creates `vivado/hft_board_a/`, adds all RTL sources, sets up the Zynq PS at 50 MHz PL clock, wires AXI/clocks/resets, and generates the block design.

4. Build (synthesize + implement + generate bitstream):
   ```tcl
   source vivado/build.tcl
   ```
   Wait for completion (~15-30 min). Check for:
   - `Synthesis status: synth_design Complete!`
   - `Implementation status: write_bitstream Complete!`
   - Timing summary: WNS should be positive (timing met)

5. The output files are:
   - **Bitstream:** `vivado/hft_board_a/hft_board_a.runs/impl_1/system_wrapper.bit`
   - **Hardware handoff:** `vivado/hft_board_a/hft_board_a.gen/sources_1/bd/system/hw_handoff/system.hwh`

### Board B

Same process, different script:

1. In Vivado Tcl Console (still in the project root):
   ```tcl
   source vivado/create_board_b.tcl
   ```
2. Build:
   ```tcl
   source vivado/build.tcl
   ```
3. Output files are under `vivado/hft_board_b/` at the same relative paths.

### Packaging for PYNQ

After building both boards, run:
```tcl
source vivado/package_pynq.tcl
```
This copies the `.bit` and `.hwh` files into `pynq/overlays/` with matching names:
- `pynq/overlays/board_a.bit` + `board_a.hwh`
- `pynq/overlays/board_b.bit` + `board_b.hwh`

---

## Part 2: Deploying to PYNQ Boards

### Flashing the SD Card

1. Download the PYNQ image for ZU3EG from [pynq.io](http://www.pynq.io/boards.html)
2. Flash the `.img` file to a microSD card using **balenaEtcher**
3. Insert the SD card into the AUP-ZU3 board and power on
4. Connect the board to your PC via the **USB cable** (USB gadget mode)
5. Wait ~60 seconds for Linux to boot

### Connecting to Jupyter Lab

1. Open a browser and go to: `http://192.168.3.1:9090`
   - Default password: `xilinx`
2. You should see the Jupyter Lab file browser at `/home/xilinx/`

### Uploading Files

#### Board A

Upload these files to `/home/xilinx/` on the Board A PYNQ:

1. Create an `overlays/` folder in Jupyter (New > Folder)
2. Upload into `overlays/`:
   - `board_a.bit`
   - `board_a.hwh`
3. Upload to `/home/xilinx/` (root of Jupyter):
   - `sw/board_a/config_symbols.py`
   - `sw/board_a/symbol_config_panel.py`
   - `sw/board_a/symbol_universe.py`
   - `sw/board_a/board_a_ps_test.py`

#### Board B

Upload these files to `/home/xilinx/` on the Board B PYNQ:

1. Create an `overlays/` folder in Jupyter
2. Upload into `overlays/`:
   - `board_b.bit`
   - `board_b.hwh`
3. Upload to `/home/xilinx/`:
   - `sw/board_b/telemetry_server.py`
   - `sw/board_b/register_map.py`

### Loading the Overlay

Create a **new notebook** in Jupyter (not an existing one like minilab0.ipynb). In the first cell:

```python
from pynq import Overlay
ol = Overlay('overlays/board_a.bit')   # or board_b.bit for Board B
print(ol.ip_dict.keys())
```

You should see `dict_keys(['hft_core', 'zynq_ps'])`.

### Getting the MMIO Handle

```python
from pynq import MMIO
base = ol.ip_dict['hft_core']['phys_addr']
span = ol.ip_dict['hft_core']['addr_range']
mmio = MMIO(base, span)
```

### Board A: Quick Smoke Test

```python
# Read STATUS register — should show running=False
status = mmio.read(0xF4)
print(f"STATUS: 0x{status:08X}")

# Read default QUOTE_INTERVAL — should be 1000
qi = mmio.read(0x04)
print(f"QUOTE_INTERVAL: {qi}")

# Write and readback
mmio.write(0x04, 500)
print(f"After write: {mmio.read(0x04)}")
```

### Board B: Quick Smoke Test

```python
# Read STATUS register (0x40)
status = mmio.read(0x40)
fsm_state = (status >> 2) & 0x07
link_up = bool((status >> 5) & 1)
print(f"STATUS: 0x{status:08X}")
print(f"  fsm_state: {fsm_state} (1=IDLE)")
print(f"  link_up:   {link_up}")

# Read default config registers
print(f"STRATEGY_SEL:   {mmio.read(0x04)}")
print(f"THRESHOLD:      0x{mmio.read(0x08):08X}")
print(f"EMA_ALPHA:      0x{mmio.read(0x0C):08X}")
print(f"BASE_QTY:       {mmio.read(0x10)}")
print(f"MAX_POSITION:   {mmio.read(0x14)}")
print(f"QUOTES_RCVD:    {mmio.read(0x44)}")
print(f"ORDERS_SENT:    {mmio.read(0x48)}")
```

---

## Part 3: Connecting Both Boards

1. Connect Board A PMOD JA to Board B PMOD JA with a PMOD cable
2. Connect Board A PMOD JB to Board B PMOD JB with a PMOD cable
3. Start Board A market sim (CTRL[0] pulse via `mmio.write(0x00, 0x01)`)
4. On Board B, check `link_up` in STATUS register and `QUOTES_RCVD` counter
5. Start Board B trading (CTRL[0] pulse via `mmio.write(0x00, 0x01)`)
6. Monitor `ORDERS_SENT`, `FILLS_RCVD`, and position registers from Board B

---

## Register Map Quick Reference

### Board A (8-bit address space)

| Address | Register | R/W | Description |
|---------|----------|-----|-------------|
| 0x00 | CTRL | W | bit[0]=start, bit[1]=reset |
| 0x04 | QUOTE_INTERVAL | R/W | Cycles between quotes |
| 0x08 | LFSR_SEED | R/W | PRNG seed |
| 0x0C | REGIME | R/W | [1:0] market regime |
| 0x10+4*i | INIT_MID[i] | R/W | Q16.16 initial mid price |
| 0x50+4*i | INIT_SPREAD[i] | R/W | Q16.16 initial spread |
| 0x90+4*i | SECTOR_ID[i] | R/W | Sector assignment |
| 0xD0+4*j | TOKEN[j] | R/W | Two 16-bit tokens packed |
| 0xF0 | ACTIVE_SYM_COUNT | R/W | 1-16 (clamped) |
| 0xF4 | STATUS | R | {fifo_fill, regime, link_up, running} |
| 0xF8 | QUOTES_SENT | R | Counter |
| 0xFC | ORDERS_RCVD | R | Counter |

### Board B (9-bit address space)

| Address | Register | R/W | Description |
|---------|----------|-----|-------------|
| 0x00 | CTRL | W | bit[0]=start, bit[1]=reset |
| 0x04 | STRATEGY_SEL | R/W | [1:0] strategy enum |
| 0x08 | THRESHOLD | R/W | Q16.16 deviation threshold |
| 0x0C | EMA_ALPHA | R/W | Q0.16 smoothing factor |
| 0x10 | BASE_QTY | R/W | Order quantity |
| 0x14 | MAX_POSITION | R/W | Position limit |
| 0x18 | MAX_ORDER_RATE | R/W | Orders per session |
| 0x1C | MAX_LOSS | R/W | Q16.16 loss threshold |
| 0x40 | STATUS | R | {risk_halt, link_up, fsm[2:0], strategy[1:0]} |
| 0x44 | QUOTES_RCVD | R | Counter |
| 0x48 | ORDERS_SENT | R | Counter |
| 0x4C | FILLS_RCVD | R | Counter |
| 0x50 | RISK_REJECTS | R | Counter |
| 0x54 | LINK_ERRORS | R | Counter |
| 0x58+4*i | POSITION[i] | R | Signed per-symbol position |
| 0x98 | CASH_LO | R | cash[31:0] |
| 0x9C | CASH_HI | R | cash[47:32] sign-extended |
| 0xA0+4*i | HIST_BIN[i] | R | Latency histogram (16 bins) |
| 0xE0 | LAT_MIN | R | Min latency |
| 0xE4 | LAT_MAX | R | Max latency |
| 0xE8 | LAT_SUM | R | Sum of latencies |
| 0xEC | LAT_COUNT | R | Number of latency samples |
