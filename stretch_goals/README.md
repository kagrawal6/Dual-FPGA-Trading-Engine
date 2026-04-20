# Stretch goals — higher PL clocks, MMCM, CDC, integration

This folder holds **optional** upgrades beyond the baseline bitstreams. The main Vivado flows (`vivado/create_board_a.tcl`, `vivado/create_board_b.tcl`) currently configure **PS PL fabric clock 0 (`pl_clk0`) at 50 MHz** via `PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ`, while the product README and design spec often describe **100 MHz** as the architectural intent.

## Master index (all stretch plans)

**[`INDEX.md`](INDEX.md)** lists every stretch item, **implementation status**, and links to **step-by-step plan files** (`plan_*.md`), including spec goals **G1–G8**, PL/MMCM, Board A telemetry, and infrastructure extras. **G7 (8-bit link)** is recorded as **complete** in [`completed_g7_8bit_link.md`](completed_g7_8bit_link.md).

**Laptop ↔ Board A (dev setup, SSH, prompts, demo polish):** [`board_a_laptop_setup_and_prompt_demo.md`](board_a_laptop_setup_and_prompt_demo.md) — **§0** step-by-step from Vivado build through overlay deploy and iteration loops; why Board A does not need its own telemetry stream; `config_symbols.py --interactive`; terminal UI (§3) and `ssh -t` (§4).

## Contents (reference docs + scripts)

| Path | Purpose |
|------|---------|
| `scripts/` | Tcl to raise `pl_clk0` from **50 MHz → 100 MHz** on an **existing** block design (`scripts/README.md` lists files) |
| [`board_a_pl_clock_and_mmcm.md`](board_a_pl_clock_and_mmcm.md) | Board A: reference clock, optional MMCM (150/200 MHz), CDC, XDC, validation |
| [`board_b_pl_clock_and_mmcm.md`](board_b_pl_clock_and_mmcm.md) | Board B: same pattern, board-specific notes |
| [`integration_dual_fpga.md`](integration_dual_fpga.md) | Dual-board: link timing, overlays, software, suggested order of work |
| [`plan_pl_reference_100mhz_and_mmcm.md`](plan_pl_reference_100mhz_and_mmcm.md) | Concise **plan** tying scripts + MMCM docs together |

## Quick start (reference clock only)

1. Open Vivado.
2. In the Tcl Console (adjust the path to your clone):

   ```tcl
   cd {/path/to/Dual-FPGA-Trading-Engine}
   source /path/to/Dual-FPGA-Trading-Engine/stretch_goals/scripts/apply_pl0_100mhz_board_a.tcl
   source /path/to/Dual-FPGA-Trading-Engine/stretch_goals/scripts/apply_pl0_100mhz_board_b.tcl
   ```

   Each script opens its own `.xpr`, so you can run **only Board A** or **only Board B** if you prefer—comment out or omit one `source` line.

3. If you already `cd` into the repo, relative paths also work: `source stretch_goals/scripts/apply_pl0_100mhz_board_a.tcl` (and `_board_b`).

4. Re-run synthesis and implementation, export bitstream / hardware, refresh PYNQ overlays if you use them.

## Relationship to the main repo

- **Baseline `create_board_*.tcl`**: Unchanged unless you merge these settings in (see each script’s header comment).
- **Stretch documentation** does not modify RTL; implementing **dual-clock + CDC** requires RTL and constraint changes described in the Board A/B guides.

## Conventions

- **Reference clock**: Frequency programmed in the Zynq UltraScale+ PS block for **`pl_clk0`** (MHz).
- **Link data rate**: PMOD signaling is still often **~50 MHz effective** via clock enables in `link_tx` / `link_rx`; raising **core** frequency changes internal timing and latency numbers, not necessarily the wire bit rate unless you change the link RTL.
