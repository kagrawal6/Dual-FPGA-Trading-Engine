# Board B — PL reference 100 MHz, optional MMCM, CDC

Applies to `vivado/hft_board_b`, RTL under `rtl/board_b/`, wrapper `rtl/board_b/board_b_top_bd.v`.

Board B’s block design mirrors Board A: **Zynq UltraScale+** `zynq_ps`, **SmartConnect**, **`proc_sys_reset`**, **`board_b_top_bd`** as `hft_core`. The **50 → 100 MHz** upgrade uses the **same PS property** as Board A.

---

## Part 1 — Raise `pl_clk0` from 50 MHz to 100 MHz

### Steps

1. **Automated**

   ```tcl
   source /path/to/Dual-FPGA-Trading-Engine/stretch_goals/scripts/apply_pl0_100mhz_board_b.tcl
   ```

2. **Manual**

   ```tcl
   set_property -dict [list CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {100}] [get_bd_cells zynq_ps]
   validate_bd_design
   save_bd_design
   generate_target all [get_files system.bd]
   ```

3. **Rebuild**  
   `vivado/build.tcl` for Board B project.

4. **Baseline**  
   Update `vivado/create_board_b.tcl` (`PL0_REF_CTRL__FREQMHZ` `{50}` → `{100}`) once verified.

### Board B specifics

- **AXI address width** is **9** bits on `board_b_top` / `board_b_top_bd` (vs 8 on Board A). Dual-clock work must keep **register map** and **AXI** timing on **`clk_axi`**; pipeline blocks (`feature_compute`, `strategy_engine`, `risk_manager`, `order_manager`, link, etc.) belong on **`clk_core`** if you split domains.
- Software under `sw/board_b/` (`register_map.py`, telemetry) does not need changes for **reference clock only**; it **does** need refreshed **`.hwh`** if addresses or PS configuration change.

---

## Part 2 — Optional MMCM (150 / 200 MHz)

Same methodology as Board A:

1. Instantiate **`clk_wiz`** + second **`proc_sys_reset`** (`rst_fast`).
2. **`pl_clk0`** → MMCM `clk_in1`; **`clk_out1`** → `rst_fast/slowest_sync_clk` and **`hft_core/clk_core`** (after RTL adds that port).
3. **`MMCM_CLKIN1_PERIOD`**: **10.000 ns** if `pl_clk0` is **100 MHz**; **20.000 ns** if still **50 MHz**.

See **`board_a_pl_clock_and_mmcm.md` Part 2** for the same Tcl pattern and locked-reset note.

---

## Part 3 — CDC

Identical **categories** as Board A:

- **Pulses** from AXI or control logic → core: pulse synchronizer / XPM.
- **Status / counters** core → AXI: synchronizers, Gray counters, or snapshot registers in the AXI clock domain.
- **FIFOs** between stages: single-clock vs **async FIFO** if domains differ.

Board B has **more pipeline depth** in the trading path; latency numbers in documentation (e.g. “8 cycles”) scale with **`clk_core`** period after you move logic to the fast clock.

---

## Part 4 — Constraints

Same as Board A: **`set_clock_groups`** between `pl_clk0` and MMCM output once both exist; refine with post-route clock names.

---

## Part 5 — Validation checklist

- [ ] Timing closed at **100 MHz** reference (and at MMCM output if used).  
- [ ] CDC review on **AXI ↔ pipeline** boundaries.  
- [ ] Regenerate overlay: `source vivado/package_pynq.tcl` (includes `board_b`).  
- [ ] Re-test **telemetry** and **register** reads against `register_map.py`.

---

## File reference

| Artifact | Path |
|----------|------|
| BD generator | `vivado/create_board_b.tcl` |
| SV top | `rtl/board_b/board_b_top.sv` |
| BD Verilog wrapper | `rtl/board_b/board_b_top_bd.v` |
