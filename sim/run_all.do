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

        onbreak {resume}

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
            lappend all_fail $tb
            continue
        }

        set had_fatal 0
        if {[file exists transcript]} {
            set fp [open transcript r]
            seek $fp $fsize
            set new_content [read $fp]
            close $fp
            if {[string first "** Fatal:" $new_content] >= 0 ||
                [string first "** Error:" $new_content] >= 0} {
                set had_fatal 1
            }
        }

        if {$had_fatal} {
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
