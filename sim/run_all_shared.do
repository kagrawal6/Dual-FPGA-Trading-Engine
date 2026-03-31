# =============================================================================
# ModelSim script — Run ALL Shared + Link testbenches
#
# Prerequisites:
#   do compile_shared.do            ;# or do compile_all.do
#
# Usage (from sim/ directory):
#   do run_all_shared.do
# =============================================================================

set tb_list {
    tb_debounce
    tb_sync_fifo
    tb_lfsr32
    tb_link_tx
    tb_link_rx
    tb_link_loopback
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
puts " Shared + Link Results"
puts "==========================================="
puts " Total : $total"
puts " Pass  : [llength $pass_list]"
puts " Fail  : [llength $fail_list]"
if {[llength $fail_list] > 0} {
    puts "-------------------------------------------"
    foreach tb $fail_list { puts "   FAIL: $tb" }
}
puts "==========================================="
