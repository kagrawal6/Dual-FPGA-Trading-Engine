# =============================================================================
# ModelSim script — Run ALL Board A testbenches
#
# Prerequisites:
#   do compile_board_a.do           ;# or do compile_all.do
#
# Usage (from sim/ directory):
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

set pass_list {}
set fail_list {}
set total [llength $tb_list]
set idx 0

foreach tb $tb_list {
    incr idx
    puts "\n==========================================="
    puts " \[$idx/$total\] Running: $tb"
    puts "==========================================="

    if {[catch {
        vsim -voptargs=+acc work.$tb -quiet
        run -all
        quit -sim
    } err]} {
        puts "*** FAIL: $tb ($err)"
        lappend fail_list $tb
    } else {
        lappend pass_list $tb
    }
}

puts "\n==========================================="
puts " Board A Results"
puts "==========================================="
puts " Total : $total"
puts " Pass  : [llength $pass_list]"
puts " Fail  : [llength $fail_list]"
if {[llength $fail_list] > 0} {
    puts "-------------------------------------------"
    foreach tb $fail_list { puts "   FAIL: $tb" }
}
puts "==========================================="
