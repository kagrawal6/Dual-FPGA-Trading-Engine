# =============================================================================
# ModelSim script — Compile full design + run ALL simulation_tb testbenches
#
# Usage (from sim_run/ directory):
#   do run_all.do
#
# These are the showcase testbenches (simulation_tb/) — simpler, readable
# versions designed for demonstration and professor review.
# =============================================================================

# ── Create / map work library ─────────────────────────────────────────────────
vlib work
vmap work work

puts "========================================="
puts " Compiling RTL..."
puts "========================================="

# -- Package (must be first) --
vlog -reportprogress 300 -sv -work work ../rtl/shared/hft_pkg.sv

# -- Shared --
vlog -reportprogress 300 -sv -work work ../rtl/shared/debounce.sv
vlog -reportprogress 300 -sv -work work ../rtl/shared/sync_fifo.sv
vlog -reportprogress 300 -sv -work work ../rtl/shared/lfsr32.sv

# -- Link --
vlog -reportprogress 300 -sv -work work ../rtl/link/link_tx.sv
vlog -reportprogress 300 -sv -work work ../rtl/link/link_rx.sv

# -- Board A --
vlog -reportprogress 300 -sv -work work ../rtl/board_a/market_sim.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_a/market_noise_gen.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_a/exchange_lite.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_a/exchange_plus.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_a/tx_arbiter.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_a/board_a_ctrl.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_a/board_a_axi_regs.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_a/board_a_top.sv

# -- Board B --
vlog -reportprogress 300 -sv -work work ../rtl/board_b/msg_demux.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_b/quote_book.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_b/feature_compute.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_b/strategy_engine.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_b/risk_manager.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_b/order_manager.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_b/position_tracker.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_b/latency_histogram.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_b/board_b_ctrl.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_b/board_b_axi_regs.sv
vlog -reportprogress 300 -sv -work work ../rtl/board_b/board_b_top.sv

puts "========================================="
puts " Compiling Testbenches (simulation_tb)..."
puts "========================================="

# -- Shared --
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_debounce.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_sync_fifo.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_lfsr32.sv

# -- Link --
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_link_tx.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_link_rx.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_link_loopback.sv

# -- Board A --
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_market_sim.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_market_noise_gen.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_exchange_lite.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_tx_arbiter.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_board_a_ctrl.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_board_a_top.sv

# -- Board B --
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_msg_demux.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_quote_book.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_feature_compute.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_strategy_engine.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_risk_manager.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_order_manager.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_position_tracker.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_latency_histogram.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_board_b_ctrl.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_board_b_axi_regs.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_board_b_top.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_board_b_pipeline.sv
vlog -reportprogress 300 -sv -work work ../simulation_tb/tb_system_top.sv

puts "========================================="
puts " Compilation done. Running testbenches..."
puts "========================================="

# ── Testbench list ─────────────────────────────────────────────────────────────
set tb_list {
    tb_debounce
    tb_sync_fifo
    tb_lfsr32
    tb_link_tx
    tb_link_rx
    tb_link_loopback
    tb_market_sim
    tb_market_noise_gen
    tb_exchange_lite
    tb_tx_arbiter
    tb_board_a_ctrl
    tb_board_a_top
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
    tb_system_top
}

set pass_list {}
set fail_list {}
set total [llength $tb_list]
set idx 0

foreach tb $tb_list {
    incr idx
    puts "\n==========================================="
    puts " \[$idx/$total\] Running: $tb"
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
        lappend fail_list $tb
        catch {quit -sim}
        continue
    }

    # simulation_tb tests end with $stop and print either
    #   "ALL TESTS PASSED" or "FAILED: N errors"
    set had_error 0
    if {[file exists transcript]} {
        after 200
        set fp [open transcript r]
        seek $fp $fsize
        set new_content [read $fp]
        close $fp
        if {[string first "ALL TESTS PASSED" $new_content] >= 0} {
            set had_error 0
        } elseif {[string first "FAILED:" $new_content] >= 0 ||
                  [string first "FAIL:"  $new_content] >= 0 ||
                  [string first "** Fatal:" $new_content] >= 0} {
            set had_error 1
        } else {
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

# ── Summary ────────────────────────────────────────────────────────────────────
puts "\n###############################################"
puts " REGRESSION SUMMARY (simulation_tb)"
puts "###############################################"
puts " Total : $total"
puts " Pass  : [llength $pass_list]"
puts " Fail  : [llength $fail_list]"
puts "-----------------------------------------------"
if {[llength $fail_list] > 0} {
    puts " FAILED:"
    foreach tb $fail_list { puts "   - $tb" }
} else {
    puts " ALL $total TESTBENCHES PASSED"
}
puts "###############################################"
