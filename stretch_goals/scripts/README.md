# Stretch-goal Vivado scripts

## Prerequisites

- AMD Vivado with a **project already created** from `vivado/create_board_a.tcl` or `create_board_b.tcl`, **or** run the scripts below: they **open** the project by path relative to this file.

## Scripts

| File | Action |
|------|--------|
| `apply_pl0_100mhz_board_a.tcl` | Sets `PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ` to **100** on `zynq_ps` in `hft_board_a` |
| `apply_pl0_100mhz_board_b.tcl` | Same for `hft_board_b` |

Each script:

1. Resolves the repository root from `info script`.
2. Opens the `.xpr` and `system.bd`.
3. Applies the PS property, `validate_bd_design`, `save_bd_design`, `generate_target all`.

## Usage (Tcl Console)

From any working directory:

```tcl
source /path/to/Dual-FPGA-Trading-Engine/stretch_goals/scripts/apply_pl0_100mhz_board_a.tcl
```

If you **already** have the project open, you can instead run only the core command:

```tcl
set_property -dict [list CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {100}] [get_bd_cells zynq_ps]
validate_bd_design
save_bd_design
generate_target all [get_files system.bd]
```

## Keeping new projects aligned

After verifying timing at 100 MHz, update the baseline generators so fresh clones match:

- `vivado/create_board_a.tcl` — change `CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {50}` to `{100}`.
- `vivado/create_board_b.tcl` — same line.

Optional: add a Clocking Wizard with `MMCM_CLKIN1_PERIOD {10.000}` (10 ns = 100 MHz input) when you follow `board_*_pl_clock_and_mmcm.md`.
