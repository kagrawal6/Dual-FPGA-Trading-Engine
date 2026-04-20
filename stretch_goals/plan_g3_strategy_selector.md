# Plan — G3 Strategy selector mux

**Goal:** Let the operator (or software) choose **mean-reversion**, **momentum**, or **NN** without resynthesizing.  
**Spec:** `docs/updated_design_specification.md` §8.1 (summary row G3), §4.4.5 modularity.  
**Depends on:** At least **two** of: baseline MR, **G1** momentum, **G2** NN.

---

## Phase 1 — Control encoding

1. **Confirm** `hft_pkg` enums: `STRAT_MEAN_REV`, `STRAT_MOMENTUM`, `STRAT_NN`, `STRAT_AUTO` (if reserved for G4).
2. **Map** hardware `SW[1:0]` or `STRATEGY_SEL` register to `active_strategy` per spec tables (see §4.4.2 / strategy switching sections).
3. **Default:** MR only if stretch blocks absent (safe fallback).

## Phase 2 — Datapath mux in `board_b_top` / `strategy_engine`

1. **Instantiate** `strategy_selector` **or** inline mux:
   - Inputs: per-strategy `signal_valid`, direction, price, qty (aligned formats).
   - Select: `active_strategy`.
2. **Latency:** Either all paths **same pipeline depth** or mux after registered outputs (avoid combinational long paths).
3. **ARMED / TRADING:** FSM must not glitch orders on strategy change mid-burst — optional **blanking** for 1 cycle on switch.

## Phase 3 — Status / telemetry

1. **Mirror** `active_strategy` to AXI **STATUS** bits (already partially defined — verify width vs `board_b_axi_regs`).
2. **JSON** telemetry: export strategy name string or numeric code for dashboard.

## Phase 4 — Verification

1. **Sim:** Toggle `active_strategy` in TB; ensure only selected path drives `risk_manager`.
2. **HW:** Flip switches during IDLE vs TRADING; document **allowed** vs **undefined** behavior.

## Phase 5 — Demo script

1. Rehearse: **MR** in CALM → switch to **momentum** in VOLATILE → (optional) **NN** in ADVERSARIAL.

## Exit criteria

- [ ] Live switch between implemented strategies without FPGA reflash.  
- [ ] Dashboard shows current strategy.  
- [ ] No duplicate orders on hot-switch (or behavior is defined and tested).
