# =============================================================================
# ModelSim compile script — Board B (all RTL + testbenches)
#
# Usage (from sim/ directory):
#   do compile_board_b.do
#
# After compiling, run any testbench with:
#   vsim -voptargs=+acc work.tb_msg_demux -do "run -all"
#   vsim -voptargs=+acc work.tb_quote_book -do "run -all"
#   vsim -voptargs=+acc work.tb_board_b_top -do "run -all"
#   ... etc
# =============================================================================

# Recreate work library
if {[file exists work]} { vdel -all -lib work }
vlib work
vmap work work

puts "========================================="
puts " Compiling Board B design..."
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

# 4. Board B RTL
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

# 5. Testbenches
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
vlog -sv -work work ../tb/board_b/tb_board_b_top.sv
vlog -sv -work work ../tb/board_b/tb_board_b_pipeline.sv

puts "========================================="
puts " Board B compilation complete!"
puts " Run a testbench with:"
puts "   vsim work.tb_msg_demux -do \"run -all\""
puts "========================================="
