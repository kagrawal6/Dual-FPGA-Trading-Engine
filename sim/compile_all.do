# =============================================================================
# ModelSim compile script — EVERYTHING (shared + Board A + Board B + system)
#
# Usage (from sim/ directory):
#   do compile_all.do
# =============================================================================

if {[file exists work]} { vdel -all -lib work }
vlib work
vmap work work

puts "========================================="
puts " Compiling full design..."
puts "========================================="

# 1. Package
vlog -sv -work work ../rtl/shared/hft_pkg.sv

# 2. Shared
vlog -sv -work work ../rtl/shared/debounce.sv
vlog -sv -work work ../rtl/shared/sync_fifo.sv
vlog -sv -work work ../rtl/shared/lfsr32.sv

# 3. Link
vlog -sv -work work ../rtl/link/link_tx.sv
vlog -sv -work work ../rtl/link/link_rx.sv

# 4. Board A RTL
vlog -sv -work work ../rtl/board_a/market_sim.sv
vlog -sv -work work ../rtl/board_a/market_noise_gen.sv
vlog -sv -work work ../rtl/board_a/exchange_lite.sv
vlog -sv -work work ../rtl/board_a/exchange_plus.sv
vlog -sv -work work ../rtl/board_a/tx_arbiter.sv
vlog -sv -work work ../rtl/board_a/board_a_ctrl.sv
vlog -sv -work work ../rtl/board_a/board_a_axi_regs.sv
vlog -sv -work work ../rtl/board_a/board_a_top.sv

# 5. Board B RTL
#    NN package + module compiled BEFORE board_b_top so the import resolves.
vlog -sv -work work ../rtl/board_b/policy_weights.sv
vlog -sv -work work ../rtl/board_b/nn_inference.sv
vlog -sv -work work ../rtl/board_b/msg_demux.sv
vlog -sv -work work ../rtl/board_b/quote_book.sv
vlog -sv -work work ../rtl/board_b/feature_compute.sv
vlog -sv -work work ../rtl/board_b/strategy_engine.sv
vlog -sv -work work ../rtl/board_b/risk_manager.sv
vlog -sv -work work ../rtl/board_b/order_manager.sv
vlog -sv -work work ../rtl/board_b/position_tracker.sv
vlog -sv -work work ../rtl/board_b/latency_histogram.sv
vlog -sv -work work ../rtl/board_b/board_b_ctrl.sv
vlog -sv -work work ../rtl/board_b/board_b_axi_regs.sv
vlog -sv -work work ../rtl/board_b/board_b_top.sv

# 6. Shared testbenches
vlog -sv -work work ../tb/shared/tb_debounce.sv
vlog -sv -work work ../tb/shared/tb_sync_fifo.sv
vlog -sv -work work ../tb/shared/tb_lfsr32.sv

# 7. Link testbenches
vlog -sv -work work ../tb/link/tb_link_tx.sv
vlog -sv -work work ../tb/link/tb_link_rx.sv
vlog -sv -work work ../tb/link/tb_link_loopback.sv

# 8. Board A testbenches
vlog -sv -work work ../tb/board_a/tb_market_sim.sv
vlog -sv -work work ../tb/board_a/tb_market_noise_gen.sv
vlog -sv -work work ../tb/board_a/tb_exchange_lite.sv
vlog -sv -work work ../tb/board_a/tb_tx_arbiter.sv
vlog -sv -work work ../tb/board_a/tb_board_a_ctrl.sv
vlog -sv -work work ../tb/board_a/tb_board_a_top.sv

# 9. Board B testbenches
vlog -sv -work work ../tb/board_b/tb_msg_demux.sv
vlog -sv -work work ../tb/board_b/tb_quote_book.sv
vlog -sv -work work ../tb/board_b/tb_feature_compute.sv
vlog -sv -work work ../tb/board_b/tb_strategy_engine.sv
vlog -sv -work work ../tb/board_b/tb_risk_manager.sv
vlog -sv -work work ../tb/board_b/tb_order_manager.sv
vlog -sv -work work ../tb/board_b/tb_position_tracker.sv
vlog -sv -work work ../tb/board_b/tb_latency_histogram.sv
vlog -sv -work work ../tb/board_b/tb_board_b_ctrl.sv
vlog -sv -work work ../tb/board_b/tb_board_b_axi_regs.sv
vlog -sv -work work ../tb/board_b/tb_nn_inference.sv
vlog -sv -work work ../tb/board_b/tb_board_b_top.sv
vlog -sv -work work ../tb/board_b/tb_board_b_pipeline.sv

# 10. System-level testbench
vlog -sv -work work ../tb/tb_system_top.sv

puts "========================================="
puts " Full compilation complete!"
puts "========================================="
