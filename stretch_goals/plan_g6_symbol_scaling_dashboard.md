# Plan — G6 Symbol scaling (parameter + software alignment)

**Goal:** Ensure **parameterized symbol count** is consistent across RTL, PS scripts, and laptop dashboard.  
**Spec:** `docs/updated_design_specification.md` §8.6 (written when default was smaller; **repo may already use 16**).

---

## Current repo note

- `hft_pkg.sv` typically sets **`NUM_SYMBOLS = 16`** and Board A uses windowed AXI for per-symbol config.  
- **G6** is therefore mostly **verification and UX**, not “turn 4 into 8” unless someone lowers the parameter for a **reduced demo**.

---

## Step 1 — Single source of truth

1. **Confirm** `NUM_SYMBOLS` in `rtl/shared/hft_pkg.sv`.  
2. **Grep** Python for hardcoded `4` or `8` symbol assumptions (`register_map.py`, `config_symbols.py`, `telemetry_server.py`, `dashboard.py`).  
3. **Align** loops and register addresses with **16-symbol** map (see `todo.md` if any addresses were stale).

## Step 2 — Board B positions

1. **Per-symbol** position registers scale with `NUM_SYMBOLS`; verify AXI address map **fits** in allocated range.  
2. **Telemetry JSON:** export `positions[]` length = `NUM_SYMBOLS`.

## Step 3 — Dashboard

1. **Plotly** bars / tables: build from JSON array length, not hardcoded 4.  
2. **Labels:** symbol ids `0 .. NUM_SYMBOLS-1`.

## Step 4 — Reduce symbols (optional lab mode)

1. If you set `NUM_SYMBOLS = 8` for a **smaller build**, re-run **full register map diff** and update **both** boards’ address constants.

## Exit criteria

- [ ] No Python **IndexError** or wrong cash/hist addresses when `NUM_SYMBOLS` is 16.  
- [ ] Dashboard matches RTL symbol count on first connect.
