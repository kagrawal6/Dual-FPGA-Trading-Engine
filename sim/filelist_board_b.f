// ============================================================================
// File List: Board B — all RTL + testbenches in compile order
// Usage:  vlog -sv -f filelist_board_b.f
// Run from: sim/ directory
// ============================================================================

// ── 1. Package (must be first) ──────────────────────────────────────────────
../rtl/shared/hft_pkg.sv

// ── 2. Shared modules ──────────────────────────────────────────────────────
../rtl/shared/debounce.sv
../rtl/shared/sync_fifo.sv
../rtl/shared/lfsr32.sv

// ── 3. Link layer ──────────────────────────────────────────────────────────
../rtl/link/link_tx.sv
../rtl/link/link_rx.sv

// ── 4. Board B RTL (order doesn't matter after package) ────────────────────
../rtl/board_b/msg_demux.sv
../rtl/board_b/quote_book.sv
../rtl/board_b/feature_compute.sv
../rtl/board_b/strategy_engine.sv
../rtl/board_b/risk_manager.sv
../rtl/board_b/order_manager.sv
../rtl/board_b/position_tracker.sv
../rtl/board_b/latency_histogram.sv
../rtl/board_b/board_b_ctrl.sv
../rtl/board_b/board_b_axi_regs.sv
../rtl/board_b/board_b_top.sv

// ── 5. Board B testbenches ─────────────────────────────────────────────────
../tb/board_b/tb_msg_demux.sv
../tb/board_b/tb_quote_book.sv
../tb/board_b/tb_feature_compute.sv
../tb/board_b/tb_strategy_engine.sv
../tb/board_b/tb_risk_manager.sv
../tb/board_b/tb_order_manager.sv
../tb/board_b/tb_position_tracker.sv
../tb/board_b/tb_latency_histogram.sv
../tb/board_b/tb_board_b_ctrl.sv
../tb/board_b/tb_board_b_axi_regs.sv
../tb/board_b/tb_board_b_top.sv
../tb/board_b/tb_board_b_pipeline.sv
