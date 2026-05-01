# =============================================================================
# ModelSim script — Run the two recently fixed TBs + all "top" integration TBs
#
# Usage (from sim/ directory):
#   do run_focused.do
#
# Targets:
#   - tb_market_sim        (off-by-one fix in test_interval_0)
#   - tb_board_a_top       (AXI handshake hang fix)
#   - tb_board_b_top
#   - tb_system_top
#
# Reuses compile_all.do so the full design is freshly compiled before running.
# Pass/fail detection is identical to run_all.do (transcript scan).
# =============================================================================

# ── Compile everything (same as full regression) ────────────────────────────
do compile_all.do

do _run_lib.do

set all_pass {}
set all_fail {}

proc run_group {group_name tb_list} {
    upvar all_pass all_pass
    upvar all_fail all_fail

    set total [llength $tb_list]
    set idx 0

    puts "\n\n###############################################"
    puts " $group_name  ($total testbenches)"
    puts "###############################################"

    foreach tb $tb_list {
        incr idx
        puts "\n==========================================="
        puts " \[$idx/$total\] $group_name -- $tb"
        puts "==========================================="
        set result [run_one_test $tb]
        if {$result eq "PASS"} {
            lappend all_pass $tb
        } else {
            lappend all_fail $tb
        }
    }
}

# ── Recently fixed Board A unit TBs ─────────────────────────────────────────
run_group "Board A — recently fixed" {
    tb_market_sim
    tb_board_a_top
}

# ── Top-level integration TBs ───────────────────────────────────────────────
# (tb_board_a_top is already covered above; included here in spirit but not
# re-run.)
run_group "Top-level integration" {
    tb_board_b_top
    tb_system_top
}

# ── Final Summary ───────────────────────────────────────────────────────────
set total_run [expr {[llength $all_pass] + [llength $all_fail]}]

puts "\n\n###############################################"
puts " FOCUSED REGRESSION SUMMARY"
puts "###############################################"
puts " Total : $total_run"
puts " Pass  : [llength $all_pass]"
puts " Fail  : [llength $all_fail]"
puts "-----------------------------------------------"

if {[llength $all_fail] > 0} {
    puts " FAILED:"
    foreach tb $all_fail {
        puts "   - $tb"
    }
} else {
    puts " ALL $total_run TESTBENCHES PASSED"
}
puts "###############################################"
