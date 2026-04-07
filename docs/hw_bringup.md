# Hardware bring-up guide — AUP-ZU3 (Dual-FPGA trading engine)

This document is a **step-by-step** path from **no bitstream** to **Python on the Zynq PS talking to your PL** and running the class scripts. Follow sections in order unless you already completed an earlier milestone.

**Target board:** AMD / Xilinx **AUP-ZU3** — Zynq UltraScale+ **XCZU3EG-2SFVC784** (speed grade **-2**).

**Repo paths** (adjust if your clone lives elsewhere):

- RTL: `rtl/`
- Pin constraints: `constraints/hft_top.xdc`
- Board A PS scripts: `sw/board_a/`
- Board B PS scripts: `sw/board_b/`
- Laptop dashboard: `sw/laptop/`
- Full design narrative: `docs/updated_design_specification.md` (especially §5.6 demo, §6 Vivado, §7.4 bring-up phases)

---

## Table of contents

1. [What you are building](#1-what-you-are-building)
2. [Prerequisites checklist](#2-prerequisites-checklist)
3. [Physical setup: power, USB, PMOD](#3-physical-setup-power-usb-pmod)
4. [Vivado: first-time project (Board A)](#4-vivado-first-time-project-board-a)
5. [Vivado: block design and PS configuration](#5-vivado-block-design-and-ps-configuration)
6. [Vivado: custom IP from your RTL](#6-vivado-custom-ip-from-your-rtl)
7. [Vivado: constraints and clock](#7-vivado-constraints-and-clock)
8. [Vivado: synthesis, implementation, bitstream](#8-vivado-synthesis-implementation-bitstream)
9. [Getting `.bit` and `.hwh` onto disk](#9-getting-bit-and-hwh-onto-disk)
10. [Repeat for Board B](#10-repeat-for-board-b)
11. [Copy overlays to each board](#11-copy-overlays-to-each-board)
12. [Install / sync Python on the boards](#12-install--sync-python-on-the-boards)
13. [Run Python on Board A](#13-run-python-on-board-a)
14. [Run Python on Board B](#14-run-python-on-board-b)
15. [Laptop dashboard (optional)](#15-laptop-dashboard-optional)
16. [Expected demo sequence](#16-expected-demo-sequence)
17. [Troubleshooting](#17-troubleshooting)
18. [Incremental bring-up (recommended)](#18-incremental-bring-up-recommended)

---

## 1. What you are building

You need **two independent FPGA images** (same PCB, different logic):

| Artifact | Board A (exchange + market sim) | Board B (trader pipeline) |
|----------|----------------------------------|---------------------------|
| Top-level RTL module | `board_a_top` | `board_b_top` |
| Bitstream (example name) | `board_a.bit` | `board_b.bit` |
| Handoff file for PYNQ | `board_a.hwh` | `board_b.hwh` |
| Default overlay path in repo scripts | `overlays/board_a.bit` | `overlays/board_b.bit` |

**PYNQ overlay rule:** The `.bit` and `.hwh` must live in the **same directory** and use the **same base name** (e.g. `board_a.bit` + `board_a.hwh`). PYNQ loads the bitstream and reads the `.hwh` to discover **AXI base addresses** and IP blocks.

**Processor system (PS):** Linux runs on the Arm cores. Your Python scripts use **`pynq.Overlay`** and **`pynq.MMIO`** to read/write **AXI-Lite** registers in the PL.

---

## 2. Prerequisites checklist

### 2.1 Workstation

- [ ] **Vivado** installed with a license that supports **Zynq UltraScale+** (not every “WebPACK” install includes US+; confirm with your university).
- [ ] Enough disk space for Vivado projects (tens of GB).
- [ ] Optional: **ModelSim / Questa** for simulation (not required for hardware bring-up).

### 2.2 Boards (×2)

- [ ] **AUP-ZU3** boards, each with SD card flashed with a **Linux image that boots** (typically **PYNQ**-based for this class flow).
- [ ] USB cables from each board to the PC (program / JTAG / serial as provided by the board).
- [ ] **Two PMOD flywires or ribbon assemblies** for the inter-board link (JA and JB, see [§3](#3-physical-setup-power-usb-pmod)).

### 2.3 Accounts and access

- [ ] You can **SSH** into each board (hostname/IP, user `xilinx` or per your image).
- [ ] You know the **password** for that user (often documented with the SD image).

### 2.4 Knowledge anchors

- [ ] You can open **Vivado** and create a project (if not, do Xilinx “Zynq US+ embedded” tutorial first).
- [ ] You understand: **bitstream** configures PL; **`.hwh`** describes the **address map** for PYNQ.

---

## 3. Physical setup: power, USB, PMOD

### 3.1 Power

- Power **one board at a time** while learning; power **both** for full system tests.
- Wait until Linux finishes booting (often **30–60 s** after power-on).

### 3.2 USB

Typical setup (matches design spec §5.6):

- **Board A:** USB to PC for **SSH** (and file copy). You run `config_symbols.py` here.
- **Board B:** USB to PC for **SSH** *and* **UART serial** for telemetry (dashboard reads this COM port).

Document which **COM port** is Board B UART in Windows Device Manager.

### 3.3 PMOD wiring (critical)

Use **`constraints/hft_top.xdc`** as the source of truth. Summary:

**PMOD JA — cable 1 (A → B path)**

| Signal role | Board A (`board_a_top`) | Board B (`board_b_top`) |
|-------------|-------------------------|-------------------------|
| Data nibble | **TX** `pmod_ja[3:0]` | **RX** `pmod_ja[3:0]` |
| Valid       | **TX** `pmod_ja_valid`  | **RX** `pmod_ja_valid` |
| Ready       | **RX** `pmod_ja_ready`  | **TX** `pmod_ja_ready` |

**PMOD JB — cable 2 (B → A path)**

| Signal role | Board A | Board B |
|-------------|---------|---------|
| Data nibble | **RX** `pmod_jb[3:0]` | **TX** `pmod_jb[3:0]` |
| Valid       | **RX** `pmod_jb_valid`  | **TX** `pmod_jb_valid` |
| Ready       | **TX** `pmod_jb_ready`  | **RX** `pmod_jb_ready` |

**Practical rule:** Connect **JA on A** to **JA on B** with a **straight** cable (pin 1 to pin 1, same orientation on both boards). Same for **JB**. If the link does not come up, **first suspect** is a flipped connector or wrong header.

**Voltage:** PMOD link uses **3.3 V** (`LVCMOS33`) per XDC.

---

## 4. Vivado: first-time project (Board A)

You will create **at least one Vivado project** for Board A. Many teams use **two projects** (`trading_a`, `trading_b`) to avoid re-synthesizing when only one side changes.

1. **Vivado** → **Create Project** → **RTL Project** (do not add sources yet if you prefer; you can add them when creating the IP).
2. **Default part:** `xczu3eg-sfvc784-2-e` (family **Zynq UltraScale+**, package **sfvc784**, speed **-2**).
3. Finish the wizard.

---

## 5. Vivado: block design and PS configuration

### 5.1 Create the block design

1. **Create Block Design** (name e.g. `design_1`).
2. Add **Zynq UltraScale+ MPSoC** (`zynq_ultra_ps_e`).
3. **Run Block Automation** when prompted (connects DDR, etc., depending on preset).

### 5.2 PS settings you must verify

Open the **Zynq IP** customization GUI. Exact tab names vary by Vivado version; find equivalents for:

| Setting | Purpose |
|---------|---------|
| **PL clocks** | Enable **FCLK_CLK0** at **100 MHz** (this clocks all your PL logic). |
| **AXI master to PL** | Enable a path so the PS can issue **AXI** transactions to the PL. Common choice in docs: **Master AXI HPM0 LPD** (`M_AXI_HPM0_LPD`) or the master your lab handout specifies. |
| **UART0** | Enabled and **MIO** pinned per **AUP-ZU3** (for Linux console / telemetry). |
| **USB** | If your PYNQ image expects USB gadget, leave as preset. |

Apply, **OK**, return to the canvas.

### 5.3 Clock and reset fabric for PL

1. Add **Processor System Reset** (`proc_sys_reset`).
2. Connect:
   - **slowest_sync_clk** (or `ext_reset_in` clock input — follow Vivado connection assistant) to **FCLK_CLK0**.
   - **ext_reset_in** to the **PS’s peripheral reset** output that Block Automation created (often `pl_resetn0` or similar — use **Connection Automation** if offered).

You need a **low-active reset** (`peripheral_aresetn`) going to your custom IP.

### 5.4 AXI interconnect

1. Add **AXI Interconnect** (or **SmartConnect** if your flow uses it).
2. Configure **one master, one slave** (1× PS master → 1× your AXI-Lite slave).
3. Connect:
   - PS **AXI master** → interconnect **S00_AXI** (or automated equivalent).
   - Interconnect **M00_AXI** → your custom IP’s **slave** (after you add the IP in [§6](#6-vivado-custom-ip-from-your-rtl)).

**Address assignment:** After the slave exists, **Run Connection Automation** and then **Validate Design**. Open **Address Editor** and confirm the slave has an assigned range (e.g. 4 KB or 512 B — must cover your register file).

---

## 6. Vivado: custom IP from your RTL

Your top modules are **`board_a_top`** and **`board_b_top`**. They already expose **AXI-Lite** (`s_axi_*`) and **GPIO-style** ports (`pmod_*`, `sw`, `btn`, `led`, `rgb*`).

### 6.1 Recommended approach (matches course spec)

1. **Tools → Create and Package New IP**.
2. **Create a new AXI4 peripheral** (AXI4-Lite, 32-bit data).
3. Vivado creates a **manage IP** or **IP packager** project with a stub top.
4. **Replace** the stub with your real design:
   - Add all **SystemVerilog** sources from the repo (`hft_pkg.sv`, shared, link, board_a **or** board_b tree).
   - Set **top** to `board_a_top` (or `board_b_top`).
5. **Port matching:** The packaged IP’s **wrapper** must expose the **exact** top-level ports your XDC expects (`pmod_ja`, `pmod_ja_valid`, `pmod_ja_ready`, `pmod_jb`, …). If the wizard generated different names, **edit the wrapper** or **edit the XDC** — they must match **exactly** (case-sensitive).

**AXI address width note (do not ignore):**

- `board_a_top` uses **`C_S_AXI_ADDR_WIDTH = 8`**.
- `board_b_top` uses **`C_S_AXI_ADDR_WIDTH = 9`**.

Your interconnect / address map must allow the full span your RTL decodes.

### 6.2 Add packaged IP to the block design

1. **Settings → IP → Repository** → add your packaged IP directory if needed.
2. **Add IP** → your **Board A** (or B) core.
3. **Run Connection Automation:**
   - Connect **AXI slave** to the interconnect master.
   - Connect **clock** to `FCLK_CLK0`.
   - Connect **reset** to `peripheral_aresetn` (or the correct active-low reset net).
4. **Right-click** the IP → **Make External** on: `pmod_*`, `sw`, `btn`, `led`, `rgb0`, `rgb1` (all FPGA pins).

### 6.3 Create HDL wrapper

1. **Generate Block Design** (sources tab → design → Generate Output Products).
2. **Create HDL Wrapper** for the block design → **Let Vivado manage** (recommended).
3. Set the **wrapper** as **top** for synthesis.

### 6.4 PYNQ `ip_dict` name (must match Python)

After you implement and export, PYNQ will show keys like `board_a_top_0`. Your repo expects:

- Board A: `ol.ip_dict["board_a_top_0"]` in `config_symbols.py`.
- Board B: default `ol.ip_dict["board_b_top_0"]` in `telemetry_server.py` (`--ip-block` overrides).

**Rule:** In the block design, the instance name of your IP should be **`board_a_top_0`** / **`board_b_top_0`**, or you must **change the Python** to match whatever appears in `ol.ip_dict.keys()`.

---

## 7. Vivado: constraints and clock

1. Add `constraints/hft_top.xdc` to the project (Add Sources → Constraints).

### 7.1 Fix the PS clock pin name in the XDC

The repo XDC contains:

```tcl
create_clock -period 10.000 -name clk_pl [get_pins zynq_ps/FCLK_CLK0]
```

Your Zynq block might not be named `zynq_ps`. **After synthesis** (or using the netlist browser), find the cell/pin path to **FCLK_CLK0** and **edit this line** to match, or rename the BD cell to `zynq_ps`.

If this line is wrong, **timing analysis is meaningless** and you can get bogus slack or errors.

### 7.2 IO standards

The XDC sets **LVCMOS33** for PMOD and **LVCMOS18** for switches/LEDs/RGB per the Real Digital reference. If your board revision differs, follow the **vendor master XDC** and merge only the **signal names** that match your RTL.

---

## 8. Vivado: synthesis, implementation, bitstream

1. **Run Synthesis** → fix **errors** (missing files, wrong top, port mismatches).
2. **Run Implementation** → open **Timing Summary**.
   - **WNS ≥ 0** at **100 MHz** before you treat the build as “good.”
3. **Generate Bitstream**.

Common issues at this stage:

- **DRC / pin** errors: top-level port name ≠ XDC `get_ports`.
- **Unconnected** outputs on the IP wrapper.
- **Clock not defined** (bad `create_clock`).

---

## 9. Getting `.bit` and `.hwh` onto disk

You need two files per board with the **same base name**:

- `board_a.bit` + `board_a.hwh`
- `board_b.bit` + `board_b.hwh`

### 9.1 Bitstream

Typical path:

`/<project>/<project>.runs/impl_1/<top_wrapper>.bit`

Copy/rename to `board_a.bit` (or `board_b.bit`).

### 9.2 `.hwh` (hardware handshake)

Vivado version and flow differ; try in order:

1. After **Generate Block Design**, look under the project’s **gen** tree, e.g.  
   `/<project>/<project>.gen/sources_1/bd/<bd_name>/hw_handoff/<bd_name>.hwh`
2. If your class uses a **Tcl script** or **PYNQ** notebook to package overlays, use that (some courses ship a `makefile`).

**Rename** the `.hwh` to match the bitstream base name (`board_a.hwh`).

**Sanity check:** Open the `.hwh` in a text editor; you should see XML describing blocks and **REGISTERS** / **ADDRESS_OFFSET** for your AXI slave.

---

## 10. Repeat for Board B

1. New project (or new run) with **`board_b_top`** as the packaged IP top.
2. Same PS + interconnect template.
3. Same XDC (pin names identical; directions differ by RTL, not by XDC).
4. Produce `board_b.bit` + `board_b.hwh`.

---

## 11. Copy overlays to each board

On **each** board, under the Linux user that runs Python (usually `xilinx`):

```bash
mkdir -p /home/xilinx/overlays
```

**Board A SD:** place:

- `/home/xilinx/overlays/board_a.bit`
- `/home/xilinx/overlays/board_a.hwh`

**Board B SD:** place:

- `/home/xilinx/overlays/board_b.bit`
- `/home/xilinx/overlays/board_b.hwh`

**From laptop (example using `scp`):**

```bash
scp board_a.bit board_a.hwh xilinx@<BOARD_A_IP>:/home/xilinx/overlays/
scp board_b.bit board_b.hwh xilinx@<BOARD_B_IP>:/home/xilinx/overlays/
```

---

## 12. Install / sync Python on the boards

### 12.1 Copy the `sw/` tree

Copy at least:

- **Board A:** entire `sw/board_a/` including `config_symbols.py`, `symbol_universe.py`, and any modules they import.
- **Board B:** entire `sw/board_b/` including `telemetry_server.py`, `register_map.py`.

Example:

```bash
scp -r sw/board_a xilinx@<BOARD_A_IP>:/home/xilinx/trading_sw/
scp -r sw/board_b xilinx@<BOARD_B_IP>:/home/xilinx/trading_sw/
```

### 12.2 PYNQ

Standard PYNQ images already include **`pynq`**. Verify:

```bash
python3 -c "from pynq import Overlay, MMIO; print('ok')"
```

### 12.3 Working directory

Run Board A scripts from the folder that contains `config_symbols.py` so imports resolve, **or** set `PYTHONPATH`:

```bash
export PYTHONPATH=/home/xilinx/trading_sw/board_a
cd /home/xilinx/trading_sw/board_a
```

---

## 13. Run Python on Board A

### 13.1 Inspect overlay keys (first time only)

```bash
cd /home/xilinx/trading_sw/board_a
python3 - << 'PY'
from pynq import Overlay
ol = Overlay("/home/xilinx/overlays/board_a.bit")
print(list(ol.ip_dict.keys()))
PY
```

You must see a key matching **`board_a_top_0`** (or edit `config_symbols.py` line with `ol.ip_dict["..."]`).

### 13.2 Status-only smoke test

```bash
python3 config_symbols.py --status
```

This loads the overlay and reads **STATUS / QUOTES_SENT / ORDERS_RCVD** style registers.

### 13.3 Full configure + start

Examples (see `python3 config_symbols.py --help` for your team’s real flags):

```bash
python3 config_symbols.py --start --tokens AAPL MSFT
```

or interactive / file-based flows per script help.

**Expected:** FSM moves toward **RUNNING**, quotes begin (Board B not required for some counters, but **link_up** on A may need B receiving).

---

## 14. Run Python on Board B

### 14.1 Default command

From `sw/board_b` on **Board B**:

```bash
python3 telemetry_server.py --overlay /home/xilinx/overlays/board_b.bit
```

Default **`--ip-block`** is `board_b_top_0`. If `ip_dict` differs:

```bash
python3 telemetry_server.py --overlay /home/xilinx/overlays/board_b.bit --ip-block <exact_key>
```

### 14.2 Status-only

```bash
python3 telemetry_server.py --status
```

### 14.3 Telemetry on UART

`telemetry_server.py` prints **one JSON object per line** to **stdout**. On PYNQ, stdout on the UART-connected session is what the laptop reads.

Typical workflow:

1. SSH to Board B and run `telemetry_server.py` **in that session**, **or**
2. Use `screen` / `minicom` on the UART COM port from the laptop (course-specific).

---

## 15. Laptop dashboard (optional)

The design spec describes **`sw/laptop/dashboard.py`** driven by **serial JSON** from Board B.

1. On Windows, find the **COM port** for Board B UART.
2. Install Python deps your dashboard needs (if the repo adds `requirements.txt`, use it; otherwise install `pyserial`, `dash`, `plotly` as in the design spec §5.5.3).
3. Run (example):

```bash
python dashboard.py --port COM5 --baud 115200
```

Adjust **baud** to match the image / design (115200 is the spec default).

---

## 16. Expected demo sequence

This mirrors `docs/updated_design_specification.md` §5.6 at a high level:

1. Power both boards; connect USB; confirm PMOD **JA** and **JB** between A and B.
2. **Board A:** run `config_symbols.py` with `--start` (or equivalent).
3. **Board B:** run `telemetry_server.py`.
4. **Laptop:** open dashboard on Board B’s serial stream.
5. On **Board B**, set **trading enable** (design uses **SW[0]** per spec) to leave **ARMED** and enter **TRADING**.
6. Use **Board A switches** for regime / behavior per spec.
7. **Stop** / **reset** using buttons per `board_b` FSM spec.

---

## 17. Troubleshooting

| Symptom | Likely cause | What to do |
|--------|----------------|------------|
| `Overlay()` fails | Missing `.hwh` or wrong path | Same directory as `.bit`, same basename; use absolute path. |
| `KeyError` in `ip_dict` | IP instance name ≠ Python | Print `ol.ip_dict.keys()`; fix BD instance name or `--ip-block` / `config_symbols.py`. |
| `MMIO` writes seem ignored | Wrong base, or PL not clocked | Confirm `.hwh` matches this bitstream; PS→PL clock enabled; reset released. |
| `link_up` never 1 | PMOD wiring, wrong bitstream on wrong board, or other side not running | Swap-check cables; confirm A has **A** bitstream and B has **B**; start A quotes first. |
| Timing **WNS < 0** | Real timing failure or bad `create_clock` | Fix clock constraint pin; pipeline RTL; check false paths only where architecturally valid. |
| UART garbage | Wrong baud / wrong COM port | Match UART0 settings; try PuTTY/minicom settings. |

---

## 18. Incremental bring-up (recommended)

Do **not** skip straight to full trading. Use gated steps from design spec §7.4:

1. **Minimal PL** (LED blink) + `Overlay()` on each board.
2. **AXI smoke:** one R/W register, Python readback.
3. **Board A only:** `config_symbols.py --status`, counters move.
4. **Board B only:** `--status`, FSM fields sane.
5. **PMOD loopback** or **link smoke** (counter frames), then full quotes + trading.

---

## Quick reference — script defaults

| Script | Overlay path | MMIO key |
|--------|--------------|----------|
| `sw/board_a/config_symbols.py` | `overlays/board_a.bit` (relative to **cwd**) | `board_a_top_0` |
| `sw/board_b/telemetry_server.py` | `overlays/board_b.bit` (default `--overlay`) | `board_b_top_0` (`--ip-block`) |

**Tip:** On the board, prefer **absolute paths** for overlays until you are sure of cwd:

```bash
python3 telemetry_server.py --overlay /home/xilinx/overlays/board_b.bit
```

---

*Document generated for the ECE 554 capstone repo. Update Vivado menu names and PS tabs to match your installed version.*
