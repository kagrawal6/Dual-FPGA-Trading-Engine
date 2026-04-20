# Plan — G5 Volatility estimator

**Goal:** Per-symbol `vol_hat[s]` — EMA of **absolute mid price change** — for G4 and telemetry.  
**Spec:** `docs/updated_design_specification.md` §8.5.  
**Depends on:** None (feeds **G4**). Can ship before G4 as **telemetry-only**.

---

## Phase 1 — Math lock-in

1. **Inputs:** `mid_new`, `mid_old` per symbol (Q16.16).  
2. **Compute:** `delta_mid = abs(mid_new - mid_old)` (unsigned path; watch signed subtraction).  
3. **EMA:** `vol_hat = (vol_alpha * delta_mid + (65536 - vol_alpha) * vol_hat_old) >> 16`.  
4. **Parameter:** `vol_alpha` Q0.16 (~0.05 default).

## Phase 2 — RTL module

1. **Create** `volatility_estimator.sv` (or fold into `feature_compute` if you prefer locality — spec suggests separate block for clarity).  
2. **State:** `mid_old[NUM_SYM]`, `vol_hat[NUM_SYM]`.  
3. **DSP:** ~2 MACs if time-multiplexed per symbol; or parallel for timing.

## Phase 3 — Wiring

1. **Consume** `mid` from quote path when quotes update (same tick as `feature_compute` uses).  
2. **Export** `vol_hat` to:
   - **G4** `regime_detector` (when present).  
   - **AXI read** registers for dashboard.  
   - Optional **telemetry JSON** fields.

## Phase 4 — Registers + SW

1. **AXI:** `VOL_ALPHA` + optional per-symbol read of `vol_hat` (may be heavy — consider **windowed read** or **UART-only** telemetry).  
2. **`register_map.py`:** offsets and Q format.

## Phase 5 — Verification

1. **TB:** step mid price; assert `vol_hat` rises after large jumps and decays in flat periods.  
2. **Cross-check** vs Python one-liner EMA on same vectors.

## Exit criteria

- [ ] Stable `vol_hat` on hardware under CALM vs VOLATILE.  
- [ ] G4 can consume `vol_hat` without glue hacks.
