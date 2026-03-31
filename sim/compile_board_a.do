# =============================================================================
# ModelSim compile script — Board A (all RTL + testbenches)
#
# Usage (from sim/ directory):
#   do compile_board_a.do
#
# After compiling, run any testbench with:
#   vsim -voptargs=+acc work.tb_market_sim -do "run -all"
#   vsim -voptargs=+acc work.tb_board_a_top -do "run -all"
#   ... etc
# =============================================================================

if {[file exists work]} { vdel -all -lib work }
vlib work
vmap work work

puts "========================================="
puts " Compiling Board A design..."
puts "========================================="

# 1. Package
vlog -sv -work work ../rtl/shared/hft_pkg.sv

# 2. Shared modules
vlog -sv -work work ../rtl/shared/debounce.sv
vlog -sv -work work ../rtl/shared/sync_fifo.sv
vlog -sv -work work ../rtl/shared/lfsr32.sv

# 3. Link layer
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

# 5. Testbenches
vlog -sv -work work ../tb/board_a/tb_market_sim.sv
vlog -sv -work work ../tb/board_a/tb_market_noise_gen.sv
vlog -sv -work work ../tb/board_a/tb_exchange_lite.sv
vlog -sv -work work ../tb/board_a/tb_tx_arbiter.sv
vlog -sv -work work ../tb/board_a/tb_board_a_ctrl.sv
vlog -sv -work work ../tb/board_a/tb_board_a_top.sv

puts "========================================="
puts " Board A compilation complete!"
puts " Run a testbench with:"
puts "   vsim work.tb_market_sim -do \"run -all\""
puts "========================================="
