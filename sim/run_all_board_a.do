# =============================================================================
# ModelSim script — Run ALL Board A testbenches sequentially
#
# Usage (from sim/ directory):
#   do compile_board_a.do
#   do run_all_board_a.do
# =============================================================================

set tb_list {
    tb_market_sim
    tb_market_noise_gen
    tb_exchange_lite
    tb_tx_arbiter
    tb_board_a_ctrl
    tb_board_a_top
}

set results {}

foreach tb $tb_list {
    puts "\n==========================================="
    puts " Running: $tb"
    puts "==========================================="

    vsim -voptargs=+acc work.$tb -quiet
    run -all
    quit -sim

    lappend results "  $tb"
}

puts "\n==========================================="
puts " Board A Testbench Results"
puts "==========================================="
puts " Ran [llength $tb_list] testbenches"
foreach r $results {
    puts $r
}
puts "==========================================="
