# =============================================================================
# ModelSim script — Compile + run ALL Board A testbenches
#
# Usage (from sim/ directory):
#   do run_all_board_a.do
#
# Self-contained: compiles the shared/link/Board-A RTL + testbenches, then
# runs each TB and prints a regression summary. Use this when you want to
# validate just Board A without running Board B's heavy NN / system tests.
# =============================================================================

# ── Compile only what this group needs ───────────────────────────────────────
do compile_board_a.do

# ── Testbench list ───────────────────────────────────────────────────────────
set tb_list {
    tb_market_sim
    tb_market_noise_gen
    tb_exchange_lite
    tb_tx_arbiter
    tb_board_a_ctrl
    tb_board_a_axi_regs
    tb_board_a_top
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
    puts " \[$idx/$total\] Board A -- $tb"
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
puts " BOARD A SUMMARY"
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
