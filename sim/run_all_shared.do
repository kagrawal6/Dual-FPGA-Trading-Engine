# =============================================================================
# ModelSim script — Compile + run ALL Shared + Link testbenches
#
# Usage (from sim/ directory):
#   do run_all_shared.do
#
# Self-contained: compiles the shared/link RTL + testbenches, then runs each
# TB and prints a regression summary. Use this when you want to validate just
# the shared/link layer without touching Board A / Board B.
# =============================================================================

# ── Compile only what this group needs ───────────────────────────────────────
do compile_shared.do

# ── Testbench list ───────────────────────────────────────────────────────────
set tb_list {
    tb_debounce
    tb_sync_fifo
    tb_lfsr32
    tb_link_tx
    tb_link_rx
    tb_link_loopback
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
    puts " \[$idx/$total\] Shared + Link -- $tb"
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
puts " SHARED + LINK SUMMARY"
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
