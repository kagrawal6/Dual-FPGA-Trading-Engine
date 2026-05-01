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

# ── Robust PASS/FAIL detection (matches run_all.do) ──────────────────────────
set pass_list {}
set fail_list {}
set total [llength $tb_list]
set idx 0

foreach tb $tb_list {
    incr idx
    puts "\n==========================================="
    puts " \[$idx/$total\] Board B — $tb"
    puts "==========================================="

    onbreak {resume}

    set fsize 0
    if {[file exists transcript]} {
        set fsize [file size transcript]
    }

    # NOTE on flags:
    #   -voptargs="+acc" — required on ModelSim ASE 2020 (it refuses
    #     to load a design without `vopt` running; -novopt is deprecated
    #     in this version and produces "Error loading design").
    #   This means each `vsim` runs `vopt` on the work library. With
    #   the NN modules (~26k unrolled MACs) in the library, that
    #   adds 30-60s of startup PER TB on ASE Starter Edition.
    #   For fast iteration on a single leaf module, prefer
    #   `run_all_board_b_lite.do`, which uses a NN-free work library.
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
