# =============================================================================
# ModelSim script — Compile + run ALL Board B testbenches
#
# Usage (from sim/ directory):
#   do run_all_board_b.do
#
# Self-contained: compiles the shared/link/Board-B RTL (including the NN
# package + module) and all Board-B testbenches, then runs them in order.
# Use this when iterating on Board B without burning time on Board A.
# =============================================================================

# ── Compile only what this group needs ───────────────────────────────────────
do compile_board_b.do

# ── Testbench list ───────────────────────────────────────────────────────────
# Order is: smallest leaf modules first → integration tests last.
# tb_nn_inference is grouped with the other strategy / pipeline unit tests.
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
    tb_nn_inference
    tb_board_b_top
    tb_board_b_pipeline
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
    puts " \[$idx/$total\] Board B -- $tb"
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
puts " BOARD B SUMMARY"
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
