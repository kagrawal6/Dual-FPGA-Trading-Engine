# =============================================================================
# ModelSim compile script — Shared + Link modules
#
# Usage (from sim/ directory):
#   do compile_shared.do
# =============================================================================

if {[file exists work]} { vdel -all -lib work }
vlib work
vmap work work

puts "========================================="
puts " Compiling Shared + Link modules..."
puts "========================================="

vlog -sv -work work ../rtl/shared/hft_pkg.sv
vlog -sv -work work ../rtl/shared/debounce.sv
vlog -sv -work work ../rtl/shared/sync_fifo.sv
vlog -sv -work work ../rtl/shared/lfsr32.sv
vlog -sv -work work ../rtl/link/link_tx.sv
vlog -sv -work work ../rtl/link/link_rx.sv

vlog -sv -work work ../tb/shared/tb_debounce.sv
vlog -sv -work work ../tb/shared/tb_sync_fifo.sv
vlog -sv -work work ../tb/shared/tb_lfsr32.sv
vlog -sv -work work ../tb/link/tb_link_tx.sv
vlog -sv -work work ../tb/link/tb_link_rx.sv
vlog -sv -work work ../tb/link/tb_link_loopback.sv

puts "========================================="
puts " Shared/Link compilation complete!"
puts "========================================="
