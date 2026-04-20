# Plan — G1 Momentum / trend-following strategy

**Goal:** Add `strategy_momentum.sv` and wire it as a selectable strategy on Board B.  
**Spec:** `docs/updated_design_specification.md` §8.2.  
**Depends on:** None (standalone module). **Unlocks:** G3 (strategy selector).

---

## Phase 1 — Algorithm and interfaces

1. **Read** current `strategy_engine.sv` and `feature_compute.sv` to see how mean-reversion outputs `signal_valid`, side, price, qty per symbol.
2. **Define** momentum outputs to match the same **downstream contract** as mean-reversion (so `risk_manager` does not need a second API).
3. **Implement** per spec:
   - Per-symbol `ema_long` state (Q16.16), α from new register `EMA_LONG_ALPHA`.
   - `trend = ema_short - ema_long` using **`ema_short` from `feature_compute`** (no duplicate short EMA).
   - Compare `trend` to signed `MOMENTUM_THRESHOLD` (Q16.16).

## Phase 2 — RTL

1. **Create** `rtl/board_b/strategy_momentum.sv` (or name matching repo conventions).
2. **Instantiate** inside `strategy_engine` behind a mux, **or** parallel compute with mux selecting MR vs momentum outputs (match existing `active_strategy` plumbing in `hft_pkg`).
3. **Resource plan:** ~2 DSP48 for long-EMA MAC; pipeline to meet timing.

## Phase 3 — Registers

1. **Extend** `board_b_axi_regs.sv` with:
   - `EMA_LONG_ALPHA` (16-bit, Q0.16 default ~0.02).
   - `MOMENTUM_THRESHOLD` (32-bit Q16.16 per spec).
2. **Update** `sw/board_b/register_map.py` and any `telemetry_server.py` write paths.
3. **Reserve** or align addresses so the map stays contiguous (watch 16-symbol layout).

## Phase 4 — Verification

1. **Unit TB:** feed synthetic `mid`, `ema_short` sequences; check `ema_long`, `trend`, BUY/SELL/no-trade.
2. **Integration:** with `active_strategy` forced to momentum, run `tb_board_b_pipeline.sv` (or minimal cosim) when available.
3. **Hardware:** CALM vs VOLATILE quotes — dashboard should show **trend-following** behavior vs mean-reversion.

## Phase 5 — Demo

1. Document **when** momentum beats MR (trending markets) for the poster / oral.
2. If G3 not ready, temporarily **tie** `active_strategy` in RTL to momentum for a branch demo.

## Exit criteria

- [ ] Momentum path synthesizes and meets timing with core clock.  
- [ ] PS can tune α and threshold live.  
- [ ] Observable difference vs mean-reversion on trending synthetic data.
