// ============================================================================
// File List: Board A — all RTL + testbenches in compile order
// Usage:  vlog -sv -f filelist_board_a.f
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

// ── 4. Board A RTL ─────────────────────────────────────────────────────────
../rtl/board_a/market_sim.sv
../rtl/board_a/market_noise_gen.sv
../rtl/board_a/exchange_lite.sv
../rtl/board_a/tx_arbiter.sv
../rtl/board_a/board_a_ctrl.sv
../rtl/board_a/board_a_axi_regs.sv
../rtl/board_a/board_a_top.sv

// ── 5. Board A testbenches ─────────────────────────────────────────────────
../tb/board_a/tb_market_sim.sv
../tb/board_a/tb_board_a_axi_regs.sv
../tb/board_a/tb_market_noise_gen.sv
../tb/board_a/tb_exchange_lite.sv
../tb/board_a/tb_tx_arbiter.sv
../tb/board_a/tb_board_a_ctrl.sv
../tb/board_a/tb_board_a_top.sv
