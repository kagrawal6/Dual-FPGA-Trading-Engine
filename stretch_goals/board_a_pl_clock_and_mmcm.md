# Board A — PL reference 100 MHz, optional MMCM, CDC

Applies to `vivado/hft_board_a`, RTL under `rtl/board_a/`, wrapper `rtl/board_a/board_a_top_bd.v`.

---

## Part 1 — Raise `pl_clk0` from 50 MHz to 100 MHz (reference clock)

### Why

`create_board_a.tcl` sets `CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {50}`. The project README describes a **100 MHz** single clock domain for PL logic.

### Steps

1. **Automated (recommended)**  
   In Vivado Tcl Console:

   ```tcl
   source /path/to/Dual-FPGA-Trading-Engine/stretch_goals/scripts/apply_pl0_100mhz_board_a.tcl
   ```

2. **Manual (same effect)**  
   Open `system.bd` → Zynq PS → **Clocking** → set **PL Fabric Clocks** → **FCLK_CLK0** to **100 MHz**, or run:

   ```tcl
   set_property -dict [list CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {100}] [get_bd_cells zynq_ps]
   validate_bd_design
   save_bd_design
   generate_target all [get_files system.bd]
   ```

3. **Rebuild**  
   Run `vivado/build.tcl` (or your flow) for **synth + impl + bitstream**.

4. **Optional — baseline script**  
   For new clones, change `vivado/create_board_a.tcl` line with `PL0_REF_CTRL__FREQMHZ` from `{50}` to `{100}`.

### Verification

- **Timing report**: `pl_clk0` period should be **10 ns** (100 MHz).  
- **Simulation / golden model**: Cycle-based delays in testbenches (if tied to “100 MHz”) stay consistent with RTL intent.

---

## Part 2 — Optional: MMCM in PL for 150 MHz or 200 MHz core clock

Keep **PS → PL** reference at **100 MHz** on `pl_clk0`. Add **Clocking Wizard** (`clk_wiz`) in the block design to multiply to a **faster local clock** for the datapath only.

### Block design (Tcl outline)

After opening `system.bd`:

```tcl
create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz clk_wiz_fast
# Set MMCM_CLKIN1_PERIOD to match pl_clk0: 10.000 ns @ 100 MHz (20.000 ns @ 50 MHz)
# Set CLKOUT1_REQUESTED_OUT_FREQ to 150.0 or 200.0
create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset rst_fast
connect_bd_net [get_bd_pins zynq_ps/pl_clk0] [get_bd_pins clk_wiz_fast/clk_in1]
connect_bd_net [get_bd_pins zynq_ps/pl_resetn0] [get_bd_pins clk_wiz_fast/resetn]
connect_bd_net [get_bd_pins clk_wiz_fast/clk_out1] [get_bd_pins rst_fast/slowest_sync_clk]
connect_bd_net [get_bd_pins zynq_ps/pl_resetn0] [get_bd_pins rst_fast/ext_reset_in]
```

Use **`report_property [get_bd_cells clk_wiz_fast]`** if your Vivado version uses different `CONFIG.*` names.

### RTL changes (required for dual clock)

Today `board_a_top` and `board_a_top_bd` use a **single** `clk` / `rst_n` for **AXI** and **datapath**.

1. Add ports: `clk_axi`, `rst_n_axi`, `clk_core`, `rst_n_core` (or equivalent names).
2. Clock **`board_a_axi_regs`** and the **AXI-Lite** side on **`clk_axi`** / **`rst_n_axi`**.
3. Clock **FSM, market_sim, FIFOs, exchange, arbiter, link_tx/rx, ctrl** on **`clk_core`** / **`rst_n_core`**.
4. Implement **CDC** on every signal that crosses between domains (see Part 3).

### Resets

- **`rst_sys`** (existing): tie to **`clk_axi`** domain.  
- **`rst_fast`**: tie to **`clk_core`** domain.  
- Optionally gate **`rst_fast/ext_reset_in`** with MMCM **`locked`** before trusting the fast clock.

---

## Part 3 — CDC (clock domain crossing)

### AXI (slow) → core (fast)

- **Single-cycle pulses** (`axi_start_pulse`, `axi_reset_pulse`, control pulses): use a **pulse synchronizer** or **XPM CDC** (`xpm_cdc_pulse`, toggle/edge scheme). Do not sample a 1-cycle AXI pulse directly on `clk_core`.
- **Wide configuration buses** (registers, arrays): treat as **quasi-static** (software only changes when idle), or use **handshake** (request/ack) or **double-buffering** after a known-safe point.

### Core (fast) → AXI (slow)

- **Status bits** (`running`, `link_up`): `xpm_cdc_single` or 2-FF synchronizer into `clk_axi`.
- **Multi-bit counters** (quotes, orders, errors): **Gray code** synchronizers, **snapshot/latch** triggered by an AXI-readable strobe, or counters maintained in the AXI domain from synchronized events.

### FIFOs

- **`sync_fifo`** in `board_a_top` is **single-clock**. If producer and consumer stay on **`clk_core`**, no change. If the FIFO straddles domains, replace with **`xpm_fifo_async`** or **FIFO Generator** (asynchronous).

---

## Part 4 — Constraints (XDC)

After implementation, use **Report → Clock Networks** to name clocks, then declare asynchronous groups, for example:

```tcl
set_clock_groups -asynchronous \
  -group [get_clocks -of_objects [get_pins zynq_ps/pl_clk0]] \
  -group [get_clocks -of_objects [get_pins clk_wiz_fast/clk_out1]]
```

Replace pin paths with those from your routed design. Add **false path** / **max_delay** only where your CDC IP (XPM/FIFO) requires it.

---

## Part 5 — Validation checklist

- [ ] `pl_clk0` at **100 MHz** (or chosen reference) meets **timing** on AXI + SmartConnect.  
- [ ] If MMCM used: **locked** behavior and **reset** sequencing tested in sim or ILA.  
- [ ] All cross-domain paths use a **documented CDC** mechanism.  
- [ ] Re-run **`vivado/package_pynq.tcl`** after bitstream so `pynq/overlays/board_a.*` match hardware.

---

## File reference

| Artifact | Path |
|----------|------|
| BD generator | `vivado/create_board_a.tcl` |
| SV top | `rtl/board_a/board_a_top.sv` |
| BD Verilog wrapper | `rtl/board_a/board_a_top_bd.v` |
| Pin constraints | `constraints/hft_top.xdc` |
