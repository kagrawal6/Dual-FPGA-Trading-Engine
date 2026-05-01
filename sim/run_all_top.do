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

# ── Robust PASS/FAIL detection (matches run_all.do) ──────────────────────────
set pass_list {}
set fail_list {}
set total [llength $tb_list]
set idx 0

foreach tb $tb_list {
    incr idx
    puts "\n==========================================="
    puts " \[$idx/$total\] System / Top — $tb"
    puts "==========================================="

    onbreak {resume}

    set fsize 0
    if {[file exists transcript]} {
        set fsize [file size transcript]
    }

    # -voptargs="+acc" — required on ModelSim ASE 2020 (-novopt is
    # deprecated and produces "Error loading design"). Note these top
    # TBs DO instantiate the NN, so vopt cost is unavoidable here.
    if {[catch {
        vsim -voptargs="+acc" work.$tb -quiet -onfinish stop
        run -all
        quit -sim
    } err]} {
        puts ">>> FAIL: $tb (Tcl error: $err)"
        lappend fail_list $tb
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
        lappend fail_list $tb
    } else {
        puts ">>> PASS: $tb"
        lappend pass_list $tb
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
