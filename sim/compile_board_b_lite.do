# =============================================================================
# ModelSim compile script — Board B WITHOUT the NN (lean)
#
# Compiles only the legacy Board B pipeline: msg_demux → quote_book →
# feature_compute → strategy_engine → risk_manager → order_manager →
# position_tracker → latency_histogram, plus their AXI/control wrappers.
#
# OMITS:
#   - rtl/board_b/policy_weights_4bit.sv (~3,300 lines of 4-bit weight ROMs)
#   - rtl/board_b/nn_inference.sv        (time-multiplexed 9->128->128->64->3 MLP)
#   - tb/board_b/tb_nn_inference.sv     (depends on nn_inference)
#   - tb/board_b/tb_board_b_top.sv      (instantiates nn_inference)
#   - tb/board_b/tb_board_b_pipeline.sv (instantiates feature_compute_nn)
#
# Use this when iterating on a single leaf module (msg_demux, quote_book,
# strategy_engine, risk_manager, etc.) where the NN is irrelevant. Pair
# with run_all_board_b_lite.do.
#
# For full Board B coverage (including the NN), use compile_board_b.do.
# =============================================================================

if {[file exists work]} { vdel -all -lib work }
vlib work
vmap work work

puts "========================================="
puts " Compiling Board B (LEAN — no NN)..."
puts "========================================="

# 1. Package — MUST be first
vlog -sv -work work ../rtl/shared/hft_pkg.sv

# 2. Shared modules
vlog -sv -work work ../rtl/shared/debounce.sv
vlog -sv -work work ../rtl/shared/sync_fifo.sv
vlog -sv -work work ../rtl/shared/lfsr32.sv

# 3. Link layer
vlog -sv -work work ../rtl/link/link_tx.sv
vlog -sv -work work ../rtl/link/link_rx.sv

# 4. Board B RTL — NO policy_weights, NO nn_inference. board_b_top is also
#    omitted because it instantiates nn_inference; the lean group only
#    exercises leaf modules.
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

# 5. Leaf-module testbenches only
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

puts "========================================="
puts " Board B LEAN compilation complete!"
puts "========================================="
