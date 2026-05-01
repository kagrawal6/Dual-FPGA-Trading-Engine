# =============================================================================
# ModelSim script — Compile + run ALL top-level / system testbenches
#
# Usage (from sim/ directory):
#   do run_all_top.do
#
# Runs the three "big" integration testbenches:
#   tb_board_a_top   — Board A as a custom IP (16-symbol pipeline + AXI)
#   tb_board_b_top   — Board B as a custom IP (NN strategy + AXI dashboard)
#   tb_system_top    — Both boards wired together via the mesochronous link
#
# These tests take longest in the regression because they exercise full
# AXI-Lite paths, the link layer, and (in tb_system_top) an 80k-cycle NN
# trading window. Splitting them out lets you iterate on the smaller
# unit TBs without paying that cost every time.
# =============================================================================

# ── Compile EVERYTHING (system_top crosses both boards) ──────────────────────
do compile_all.do

# ── Testbench list ───────────────────────────────────────────────────────────
set tb_list {
    tb_board_a_top
    tb_board_b_top
    tb_system_top
}

# ── Robust PASS/FAIL detection (shared with run_all.do) ──────────────────────
do _run_lib.do

set pass_list {}
set fail_list {}
set total [llength $tb_list]
set idx 0

foreach tb $tb_list {
    incr idx
    puts "\n==========================================="
    puts " \[$idx/$total\] System / Top -- $tb"
    puts "==========================================="
    set result [run_one_test $tb]
    if {$result eq "PASS"} {
        lappend pass_list $tb
    } else {
        lappend fail_list $tb
    }
}

# ── Summary ──────────────────────────────────────────────────────────────────
puts "\n==========================================="
puts " TOP / SYSTEM SUMMARY"
puts "==========================================="
puts " Total : $total"
puts " Pass  : [llength $pass_list]"
puts " Fail  : [llength $fail_list]"
if {[llength $fail_list] > 0} {
    puts "-------------------------------------------"
    foreach tb $fail_list { puts "   FAIL: $tb" }
} else {
    puts " ALL $total TESTBENCHES PASSED"
}
puts "==========================================="
