# Dual-FPGA integration — stretch clock goals

When you change **PL reference clocks**, **MMCM-derived core clocks**, or **CDC** on one or both boards, the **link between boards** and **host software** must stay consistent.

---

## 1. Reference clock alignment (50 → 100 MHz)

**Recommendation:** After validation, set **both** `create_board_a.tcl` and `create_board_b.tcl` to the **same** `PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ` (e.g. **100**).

**Why:** The design spec assumes **mesochronous** operation: each board has its own crystal-derived PS clock; they are **not** phase-locked, but **nominal** frequency should match so the **link layer** timing assumptions (oversampling, clock enables in `link_tx` / `link_rx`) remain as documented.

**Scripts:**  
`stretch_goals/scripts/apply_pl0_100mhz_board_a.tcl`  
`stretch_goals/scripts/apply_pl0_100mhz_board_b.tcl`

**Integration check:** Rebuild **both** bitstreams, then refresh overlays (section 4).

---

## 2. PMOD link vs core frequency

- The **logical** link rate is often described as **~50 MHz effective** (nibble timing via **clock enable** at **100 MHz core** in the spec).
- If you only change **50 → 100 MHz** on `pl_clk0` **without** changing link RTL, **re-verify** `link_tx` / `link_rx` timing: beat widths, gaps, and **debounce** intervals (cycle counts) change in **wall-clock** time unless you compensate in RTL or registers.

**Action:** After any PL frequency change, run **hardware loopback** or **A↔B cable** tests and compare to golden vectors / `golden_model/` if you rely on them.

---

## 3. MMCM (150 / 200 MHz) on one or both boards

**Asymmetric clocks (A fast, B slow or vice versa)** are possible but **risky** for the **PMOD link** unless:

- The **link I/O** remains in a **single clock domain** that both sides can sample reliably, or  
- You **document** new sampling behavior and re-validate **setup/hold** across the cable.

**Safer pattern:** Keep **link_tx / link_rx** on the **same** domain as today (often **`pl_clk0`** or a divided enable from it), and run only **internal pipeline** on MMCM clocks **behind** registered PMOD I/O. That implies **explicit RTL partitioning**, not only BD edits.

**Symmetric pattern:** Same MMCM ratio on Board A and Board B → similar internal latency; still re-validate **CDC** at each AXI boundary.

---

## 4. PYNQ overlays and software

Hardware handoff for notebooks/scripts lives under **`pynq/overlays/`** (`board_a.bit`, `board_a.hwh`, `board_b.bit`, `board_b.hwh`).

After bitstream changes:

1. Run **`source vivado/package_pynq.tcl`** from the Vivado Tcl console (with both projects built and bitstreams present).  
   See `vivado/package_pynq.tcl` for paths.
2. Copy updated **`pynq/`** to each board (or sync your repo).
3. Reload overlays in PYNQ (`Overlay('...')`) so **`hwh`** matches **addresses and clock topology**.

**Register maps:** `sw/board_a/` and `sw/board_b/register_map.py` are **logical** addresses; they change only if the **BD address map** or **peripheral** structure changes. A **frequency-only** PS tweak usually keeps addresses the same—still confirm in the **Address Editor** after BD edits.

---

## 5. Order of operations (suggested)

1. Move **both** boards to **100 MHz** `pl_clk0` using the stretch scripts; close timing; run link tests.  
2. Commit updated **`create_board_*.tcl`** when stable.  
3. Optionally add **MMCM + CDC** on **one** board in a branch; validate; repeat for the second board.  
4. **`package_pynq.tcl`** → deploy overlays → system test **A + B + laptop dashboard**.

---

## 6. What does *not* require dual-board coordination

- **Vitis / `export_hw.tcl`** per project: independent per board.  
- **Laptop `sw/laptop/dashboard.py`**: only depends on **telemetry** and **register** contracts; update if register semantics or scaling change.

---

## 7. Related repo files

| Topic | Location |
|-------|----------|
| Package bit + hwh | `vivado/package_pynq.tcl` |
| Export `.xsa` | `vivado/export_hw.tcl` |
| Board A stretch detail | `stretch_goals/board_a_pl_clock_and_mmcm.md` |
| Board B stretch detail | `stretch_goals/board_b_pl_clock_and_mmcm.md` |
| PL 100 MHz scripts | `stretch_goals/scripts/` |
