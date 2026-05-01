# =============================================================================
# ModelSim script — Compile full design + run ALL testbenches
#
# Usage (from sim/ directory):
#   do run_all.do
#
# This is the single entry point: compiles everything, runs every TB,
# and prints a full regression summary at the end.
# =============================================================================

# ── Compile everything ───────────────────────────────────────────────────────
do compile_all.do

# ── Run each group ───────────────────────────────────────────────────────────
# We track results across all groups for a combined summary.

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

        # NOTE: do NOT use `onbreak` as a failure indicator — ModelSim Intel
        # FPGA Edition fires onbreak on every $finish (clean test exit prints
        # "Break in Module ... line N"), so it would mark every TB as FAIL.
        # We rely solely on transcript scanning for explicit PASS/FAIL markers
        # printed by the testbenches themselves.
        onbreak {resume}

        set fsize 0
        if {[file exists transcript]} {
            set fsize [file size transcript]
        }

        # -voptargs="+acc" — required on ModelSim ASE 2020 (-novopt is
        # deprecated and produces "Error loading design"). vopt cost is
        # mostly paid once the NN is in the work library; consider using
        # the per-group runners (run_all_board_b_lite.do etc) for fast
        # iteration on individual leaf modules.
        if {[catch {
            vsim -voptargs="+acc" work.$tb -quiet -onfinish stop
            run -all
            quit -sim
        } err]} {
            puts ">>> FAIL: $tb (Tcl error: $err)"
            lappend all_fail $tb
            catch {quit -sim}
            continue
        }

        # Scan the new transcript region produced by THIS testbench only.
        set had_fatal 0
        set saw_pass  0
        if {[file exists transcript]} {
            after 200
            set fp [open transcript r]
            seek $fp $fsize
            set new_content [read $fp]
            close $fp

            # Hard-failure markers (genuine ModelSim or testbench errors).
            # We deliberately do NOT match "FAIL" alone or "Errors: N" because
            # ModelSim's "Errors: 0" line and Tcl's own ">>> FAIL:" output
            # would otherwise give false positives.
            foreach pat {"** Fatal:" "TESTBENCH FAILED" "Assertion error"} {
                if {[string first $pat $new_content] >= 0} {
                    set had_fatal 1
                    break
                }
            }

            # If we did not see a hard fail, check for a positive PASS marker.
            # Each TB ends with one of:
            #   "<tb>: PASS (N checks passed)"          ← simple TBs
            #   "ALL TESTS PASSED"                       ← legacy TBs
            #   "PASSED: N\n#   FAILED: 0"               ← group-style TBs
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

# ── Shared + Link ────────────────────────────────────────────────────────────
run_group "Shared + Link" {
    tb_debounce
    tb_sync_fifo
    tb_lfsr32
    tb_link_tx
    tb_link_rx
    tb_link_loopback
}

# ── Board A ──────────────────────────────────────────────────────────────────
run_group "Board A" {
    tb_market_sim
    tb_market_noise_gen
    tb_exchange_lite
    tb_tx_arbiter
    tb_board_a_ctrl
    tb_board_a_top
}

# ── Board B ──────────────────────────────────────────────────────────────────
run_group "Board B" {
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

# ── System Top ───────────────────────────────────────────────────────────────
run_group "System" {
    tb_system_top
}

# ── Final Summary ────────────────────────────────────────────────────────────
set total_run [expr {[llength $all_pass] + [llength $all_fail]}]

puts "\n\n###############################################"
puts " FULL REGRESSION SUMMARY"
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
