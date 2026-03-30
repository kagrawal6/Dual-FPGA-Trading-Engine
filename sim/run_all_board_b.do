# =============================================================================
# ModelSim script — Run ALL Board B testbenches sequentially
#
# Usage (from sim/ directory):
#   do compile_board_b.do         ;# compile first
#   do run_all_board_b.do         ;# then run all TBs
#
# Or to run a SINGLE testbench:
#   vsim -voptargs=+acc work.tb_msg_demux -do "run -all; quit -f"
# =============================================================================

set tb_list {
    tb_msg_demux
    tb_quote_book
    tb_feature_compute
    tb_strategy_engine
    tb_risk_manager
    tb_order_manager
    tb_position_tracker
    tb_latency_histogram
    tb_board_b_ctrl
    tb_board_b_axi_regs
    tb_board_b_top
}

set pass_count 0
set fail_count 0
set results {}

foreach tb $tb_list {
    puts "\n==========================================="
    puts " Running: $tb"
    puts "==========================================="

    vsim -voptargs=+acc work.$tb -quiet
    run -all
    quit -sim

    lappend results "  $tb"
    incr pass_count
}

puts "\n==========================================="
puts " Board B Testbench Results"
puts "==========================================="
puts " Ran [llength $tb_list] testbenches"
foreach r $results {
    puts $r
}
puts "==========================================="
