# =============================================================================
# ModelSim script — Compile full design + run TOP-LEVEL testbenches only
#
# Usage (from sim/ directory):
#   do run_top_tests.do
#
# Runs: tb_board_a_top, tb_board_b_top, tb_system_top
# =============================================================================

# ── Compile everything ───────────────────────────────────────────────────────
do compile_all.do

# ── Track results ────────────────────────────────────────────────────────────
set pass_list {}
set fail_list {}

set tb_list {
    tb_board_a_top
    tb_board_b_top
    tb_system_top
}

set total [llength $tb_list]
set idx 0

foreach tb $tb_list {
    incr idx
    puts "\n==========================================="
    puts " \[$idx/$total\] Running: $tb"
    puts "==========================================="

    set ::_tb_break 0
    onbreak {set ::_tb_break 1; resume}

    set fsize 0
    if {[file exists transcript]} {
        set fsize [file size transcript]
    }

    if {[catch {
        vsim -voptargs=+acc work.$tb -quiet
        run -all
        quit -sim
    } err]} {
        puts ">>> FAIL: $tb (Tcl error: $err)"
        lappend fail_list $tb
        catch {quit -sim}
        continue
    }

    set had_error $::_tb_break

    if {!$had_error && [file exists transcript]} {
        after 200
        set fp [open transcript r]
        seek $fp $fsize
        set new_content [read $fp]
        close $fp
        foreach pat {"** Fatal:" "** Error: FAIL:" "FAIL (" "TESTBENCH FAILED"} {
            if {[string first $pat $new_content] >= 0} {
                set had_error 1
                break
            }
        }
    }

    if {$had_error} {
        puts ">>> FAIL: $tb"
        lappend fail_list $tb
    } else {
        puts ">>> PASS: $tb"
        lappend pass_list $tb
    }
}

# ── Summary ──────────────────────────────────────────────────────────────────
puts "\n==========================================="
puts " TOP-LEVEL TEST SUMMARY"
puts "==========================================="
puts " Total : $total"
puts " Pass  : [llength $pass_list]"
puts " Fail  : [llength $fail_list]"
if {[llength $fail_list] > 0} {
    puts "-----------------------------------------"
    foreach tb $fail_list { puts "   FAIL: $tb" }
} else {
    puts " ALL $total TOP-LEVEL TESTBENCHES PASSED"
}
puts "==========================================="
