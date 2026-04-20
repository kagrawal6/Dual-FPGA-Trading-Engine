# Plan — PL reference 100 MHz + optional MMCM fast core

**Goal:** Align PS **PL fabric clock 0** with the **100 MHz** architecture described in the README/spec, and optionally add **MMCM** for 150/200 MHz **core** logic with CDC.  
**Status:** **Partially prepared** — Tcl + narrative docs exist; **not** the default in `create_board_*.tcl` (still **50 MHz**).

---

## A. Reference clock only (50 MHz → 100 MHz)

### Steps

1. Run (per board):

   ```tcl
   source /path/to/repo/stretch_goals/scripts/apply_pl0_100mhz_board_a.tcl
   source /path/to/repo/stretch_goals/scripts/apply_pl0_100mhz_board_b.tcl
   ```

2. **Synthesize / implement** both projects; fix **timing** at 10 ns period on `pl_clk0`.  
3. **Regression:** link loopback, trading demo, latency histogram (expect **shorter** absolute time per cycle if logic was cycle-identical).  
4. **Commit** change into `vivado/create_board_a.tcl` and `create_board_b.tcl` when stable (`PL0_REF_CTRL__FREQMHZ {100}`).  
5. **`vivado/package_pynq.tcl`** → refresh `pynq/overlays/`.

### References

- `stretch_goals/scripts/README.md`  
- `stretch_goals/board_a_pl_clock_and_mmcm.md` / `board_b_pl_clock_and_mmcm.md`  
- `stretch_goals/integration_dual_fpga.md`

---

## B. MMCM + dual clock + CDC (optional stretch)

### Steps

1. **RTL:** Add `clk_axi` / `clk_core` (and matching resets) to `board_*_top` + `*_top_bd.v`.  
2. **BD:** Instantiate `clk_wiz`, second `proc_sys_reset`; wire per `board_*_pl_clock_and_mmcm.md`.  
3. **CDC:** Pulse synchronizers, `xpm_fifo_async` where needed, **never** ad-hoc multi-bit sampling.  
4. **XDC:** `set_clock_groups` between `pl_clk0` and MMCM output.  
5. **Re-verify** PMOD timing if link logic moves domains.

### Exit criteria

- [ ] WNS > 0 on both domains.  
- [ ] No CDC tool warnings; formal CDC checklist signed off for class.

---

## Integration reminder

Both boards should use the **same** nominal `pl_clk0` unless you intentionally document asymmetry. See **`integration_dual_fpga.md`**.
