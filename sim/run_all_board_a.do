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
    tb_board_a_top
}

# ── Robust PASS/FAIL detection (matches run_all.do) ──────────────────────────
set pass_list {}
set fail_list {}
set total [llength $tb_list]
set idx 0

foreach tb $tb_list {
    incr idx
    puts "\n==========================================="
    puts " \[$idx/$total\] Board A — $tb"
    puts "==========================================="

    onbreak {resume}

    set fsize 0
    if {[file exists transcript]} {
        set fsize [file size transcript]
    }

    # -voptargs="+acc" — required on ModelSim ASE 2020 (-novopt is
    # deprecated and produces "Error loading design"). Board A modules
    # are small so vopt time is negligible here.
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
