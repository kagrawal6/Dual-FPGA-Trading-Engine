# Plan — G4 Adaptive regime detection

**Goal:** Implement `regime_detector.sv` to drive **`STRAT_AUTO`** when the operator selects auto mode (via G3).  
**Spec:** `docs/updated_design_specification.md` §8.4.  
**Depends on:** **G1** (trend input), **G2** (NN path), **G3** (selector mux to `active_strategy`), **G5** (`vol_hat`).

---

## Phase 0 — Prerequisite check

- [ ] G5 `vol_hat[s]` available per quote, Q16.16.  
- [ ] G1 exposes `trend[s] = ema_short - ema_long` (or equivalent) to classifier.  
- [ ] G3 can set `active_strategy` from logic, not only from SW/AXI manual values.

## Phase 1 — Rules and hysteresis

1. **Implement** threshold compares from spec: `V_LOW`, `V_HIGH`, `V_CRISIS`, `S_LOW`, `S_WIDE`, `T_THRESH` (all Q16.16 or consistent types).
2. **State machine** or counter: `detected_mode` must persist **N** consecutive quotes (`HYSTERESIS_N`, default 64) before **committing** strategy change.
3. **Output:** `active_strategy` to mux when mode = AUTO; optional `detected_regime` status for dashboard.

## Phase 2 — RTL

1. **`regime_detector.sv`:** Inputs: `vol_hat`, `spread`, `trend` (per symbol or aggregated — **decide**: max vol across symbols vs per-symbol auto).
2. **Clock:** Same as pipeline (single domain unless MMCM stretch).
3. **Reset:** Clear hysteresis counters on global reset or FSM HALTED.

## Phase 3 — Registers

1. **AXI** for all thresholds + `HYSTERESIS_N` (table in §8.4).  
2. **Read-only** status: last classification, quotes until switch.

## Phase 4 — Integration

1. **Wire** detector output to **`strategy_selector`** when `STRATEGY_SEL == AUTO`.  
2. **Override safety:** if link down or quotes stopped, hold strategy or revert to MR (document).

## Phase 5 — Verification

1. **Directed sim:** sweep vol/spread/trend; check classification and hysteresis.  
2. **HW:** force VOLATILE + trend → momentum; force crisis → NN path.

## Exit criteria

- [ ] Auto mode selects strategies per rules without rapid oscillation.  
- [ ] Dashboard shows **detected** mode vs **manual** mode distinction.
