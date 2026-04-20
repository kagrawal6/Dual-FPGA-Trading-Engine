# Stretch goals — implementation index

Use this table to find **step-by-step plans** for work that is **not yet implemented** in the main branch (or is only partially documented). The design specification’s stretch list is in `docs/updated_design_specification.md` §8.

| ID | Topic | Status | Plan file |
|----|--------|--------|-----------|
| **G7** | 8-bit PMOD link (`LINK_DATA_W = 8`, JAB wiring) | **Done** (team; not tracked in this chat) | [`completed_g7_8bit_link.md`](completed_g7_8bit_link.md) |
| **G1** | Momentum / dual-EMA strategy (`strategy_momentum.sv`) | Not implemented | [`plan_g1_momentum_strategy.md`](plan_g1_momentum_strategy.md) |
| **G2** | Neural network inference (`strategy_nn.sv`) | In progress — see plan for scope tiers | [`plan_g2_neural_network_strategy.md`](plan_g2_neural_network_strategy.md) |
| **G3** | Strategy selector mux + SW mapping | Not implemented (needs G1 and/or G2) | [`plan_g3_strategy_selector.md`](plan_g3_strategy_selector.md) |
| **G4** | Adaptive regime detector (`regime_detector.sv`) | Not implemented | [`plan_g4_adaptive_regime_detector.md`](plan_g4_adaptive_regime_detector.md) |
| **G5** | Volatility estimator | Not implemented | [`plan_g5_volatility_estimator.md`](plan_g5_volatility_estimator.md) |
| **G6** | Symbol scaling (parameter + SW/dashboard) | Partially satisfied (`NUM_SYMBOLS = 16` in RTL); verify end-to-end | [`plan_g6_symbol_scaling_dashboard.md`](plan_g6_symbol_scaling_dashboard.md) |
| **G8** | High-speed UART telemetry (921600 baud) | Not implemented | [`plan_g8_telemetry_high_baud.md`](plan_g8_telemetry_high_baud.md) |
| **PL** | PS `pl_clk0` 50→100 MHz + optional MMCM fast core | Scripts + reference docs exist; not default in `create_board_*.tcl` | [`plan_pl_reference_100mhz_and_mmcm.md`](plan_pl_reference_100mhz_and_mmcm.md) |
| **A-tele** | Board A telemetry to laptop (spec §5.5.3) — **optional**; core demo does not need it | Not implemented | [`plan_board_a_ps_telemetry.md`](plan_board_a_ps_telemetry.md) |
| **A-demo** | **§0** full dev setup (Vivado → overlays → `scp` → verify); SSH, prompts, terminal polish, full system checklist | How-to | [`board_a_laptop_setup_and_prompt_demo.md`](board_a_laptop_setup_and_prompt_demo.md) |
| **Extras** | RX→exchange FIFO, AXI widen/stop, link CRC, `exchange_plus` | Open items from `todo.md` | [`plan_board_a_and_link_extras.md`](plan_board_a_and_link_extras.md) |

**Suggested order** (from spec §8.1, adjusted for your progress): G1 → G3 → G6 (verification) → G2 → G5 → G4 → G8 → PL hardening. G7 is already complete.
