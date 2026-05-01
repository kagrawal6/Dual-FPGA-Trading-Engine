# =============================================================================
# ModelSim script — Compile + run LEAN Board B testbenches (no NN)
#
# Usage (from sim/ directory):
#   do run_all_board_b_lite.do
#
# Faster path for iterating on a single Board-B leaf module. Skips the
# NN-related compilation entirely (saves ~30 sec of vlog + avoids ASE
# Starter Edition's vopt throttle). Use the full `run_all_board_b.do`
# when you need to validate tb_nn_inference, tb_board_b_top, or
# tb_board_b_pipeline.
# =============================================================================

# ── Compile lean (no NN) ─────────────────────────────────────────────────────
do compile_board_b_lite.do

# ── Testbench list — leaf modules only ───────────────────────────────────────
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
}

# ── Robust PASS/FAIL detection (matches run_all.do) ──────────────────────────
set pass_list {}
set fail_list {}
set total [llength $tb_list]
set idx 0

foreach tb $tb_list {
    incr idx
    puts "\n==========================================="
    puts " \[$idx/$total\] Board B (lean) — $tb"
    puts "==========================================="

    onbreak {resume}

    set fsize 0
    if {[file exists transcript]} {
        set fsize [file size transcript]
    }

    # -voptargs="+acc" — required on ModelSim ASE 2020. The lean
    # work library (no NN) means vopt finishes quickly here.
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
puts " BOARD B LEAN SUMMARY"
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
