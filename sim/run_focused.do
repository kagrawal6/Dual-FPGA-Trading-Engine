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
        puts " \[$idx/$total\] $group_name — $tb"
        puts "==========================================="

        onbreak {resume}

        set fsize 0
        if {[file exists transcript]} {
            set fsize [file size transcript]
        }

        if {[catch {
            vsim -voptargs=+acc work.$tb -quiet -onfinish stop
            run -all
            quit -sim
        } err]} {
            puts ">>> FAIL: $tb (Tcl error: $err)"
            lappend all_fail $tb
            catch {quit -sim}
            continue
        }

        set had_fatal 0
        set saw_pass  0
        if {[file exists transcript]} {
            after 200
            set fp [open transcript r]
            seek $fp $fsize
            set new_content [read $fp]
            close $fp

            foreach pat {"** Fatal:" "TESTBENCH FAILED" "Assertion error"} {
                if {[string first $pat $new_content] >= 0} {
                    set had_fatal 1
                    break
                }
            }

            if {!$had_fatal} {
                if {[string first ": PASS ("        $new_content] >= 0 ||
                    [string first "ALL TESTS PASSED" $new_content] >= 0 ||
                    ([string first "FAILED: 0" $new_content] >= 0 &&
                     [string first "PASSED:"   $new_content] >= 0)} {
                    set saw_pass 1
                }
            }
        }

        if {$had_fatal || !$saw_pass} {
            puts ">>> FAIL: $tb"
            lappend all_fail $tb
        } else {
            puts ">>> PASS: $tb"
            lappend all_pass $tb
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
