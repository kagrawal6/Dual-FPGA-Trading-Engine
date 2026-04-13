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

    onbreak {resume}

    # Capture transcript size before sim so we can read only new content
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

    # Read new transcript content and check for failures
    set had_error 0
    if {[file exists transcript]} {
        set fp [open transcript r]
        seek $fp $fsize
        set new_content [read $fp]
        close $fp

        # Check for Fatal or Error messages from the simulation
        if {[string first "** Fatal:" $new_content] >= 0} {
            set had_error 1
        }
        # Check for our testbench FAIL marker (from $error calls)
        if {[string first "** Error: FAIL:" $new_content] >= 0} {
            set had_error 1
        }
        # Check for testbench-level FAIL summary printed by our TB
        if {[string first "FAIL (" $new_content] >= 0} {
            set had_error 1
        }
        # Check for TESTBENCH FAILED from $fatal(1, ...)
        if {[string first "TESTBENCH FAILED" $new_content] >= 0} {
            set had_error 1
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
