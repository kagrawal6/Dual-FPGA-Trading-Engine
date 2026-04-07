

# Create work library
vlib work
vmap work work

puts "========================================="
puts " Compiling RTL..."
puts "========================================="

# -- Package (must be first) --
vlog -sv -work work ../rtl/shared/hft_pkg.sv

# -- Shared --
vlog -sv -work work ../rtl/shared/debounce.sv
vlog -sv -work work ../rtl/shared/sync_fifo.sv
vlog -sv -work work ../rtl/shared/lfsr32.sv

# -- Link --
vlog -sv -work work ../rtl/link/link_tx.sv
vlog -sv -work work ../rtl/link/link_rx.sv

# -- Board A --
vlog -sv -work work ../rtl/board_a/market_sim.sv
vlog -sv -work work ../rtl/board_a/market_noise_gen.sv
vlog -sv -work work ../rtl/board_a/exchange_lite.sv
vlog -sv -work work ../rtl/board_a/exchange_plus.sv
vlog -sv -work work ../rtl/board_a/tx_arbiter.sv
vlog -sv -work work ../rtl/board_a/board_a_ctrl.sv
vlog -sv -work work ../rtl/board_a/board_a_axi_regs.sv
vlog -sv -work work ../rtl/board_a/board_a_top.sv

# -- Board B --
vlog -sv -work work ../rtl/board_b/msg_demux.sv
vlog -sv -work work ../rtl/board_b/quote_book.sv
vlog -sv -work work ../rtl/board_b/feature_compute.sv
vlog -sv -work work ../rtl/board_b/strategy_engine.sv
vlog -sv -work work ../rtl/board_b/risk_manager.sv
vlog -sv -work work ../rtl/board_b/order_manager.sv
vlog -sv -work work ../rtl/board_b/position_tracker.sv
vlog -sv -work work ../rtl/board_b/latency_histogram.sv
vlog -sv -work work ../rtl/board_b/board_b_ctrl.sv
vlog -sv -work work ../rtl/board_b/board_b_axi_regs.sv
vlog -sv -work work ../rtl/board_b/board_b_top.sv

puts "========================================="
puts " Compiling Testbenches..."
puts "========================================="

# -- All testbenches --
vlog -sv -work work ../simulation_tb/tb_debounce.sv
vlog -sv -work work ../simulation_tb/tb_sync_fifo.sv
vlog -sv -work work ../simulation_tb/tb_lfsr32.sv
vlog -sv -work work ../simulation_tb/tb_link_tx.sv
vlog -sv -work work ../simulation_tb/tb_link_rx.sv
vlog -sv -work work ../simulation_tb/tb_link_loopback.sv
vlog -sv -work work ../simulation_tb/tb_market_sim.sv
vlog -sv -work work ../simulation_tb/tb_market_noise_gen.sv
vlog -sv -work work ../simulation_tb/tb_exchange_lite.sv
vlog -sv -work work ../simulation_tb/tb_tx_arbiter.sv
vlog -sv -work work ../simulation_tb/tb_board_a_ctrl.sv
vlog -sv -work work ../simulation_tb/tb_board_a_top.sv
vlog -sv -work work ../simulation_tb/tb_msg_demux.sv
vlog -sv -work work ../simulation_tb/tb_quote_book.sv
vlog -sv -work work ../simulation_tb/tb_feature_compute.sv
vlog -sv -work work ../simulation_tb/tb_strategy_engine.sv
vlog -sv -work work ../simulation_tb/tb_risk_manager.sv
vlog -sv -work work ../simulation_tb/tb_order_manager.sv
vlog -sv -work work ../simulation_tb/tb_position_tracker.sv
vlog -sv -work work ../simulation_tb/tb_latency_histogram.sv
vlog -sv -work work ../simulation_tb/tb_board_b_ctrl.sv
vlog -sv -work work ../simulation_tb/tb_board_b_axi_regs.sv
vlog -sv -work work ../simulation_tb/tb_board_b_top.sv
vlog -sv -work work ../simulation_tb/tb_board_b_pipeline.sv
vlog -sv -work work ../simulation_tb/tb_system_top.sv

puts "========================================="
puts " Compilation done. Running testbenches..."
puts "========================================="

# ---------- Run each testbench ----------

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
    puts "\n--- \[$idx/$total\] Running: $tb ---"

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
        lappend fail_list $tb
        continue
    }

    set had_error 0
    if {[file exists transcript]} {
        set fp [open transcript r]
        seek $fp $fsize
        set new_content [read $fp]
        close $fp
        if {[string first "** Fatal:" $new_content] >= 0 ||
            [string first "** Error:" $new_content] >= 0} {
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

# ---------- Summary ----------
puts "\n========================================="
puts " REGRESSION SUMMARY"
puts "========================================="
puts " Total : $total"
puts " Pass  : [llength $pass_list]"
puts " Fail  : [llength $fail_list]"
if {[llength $fail_list] > 0} {
    puts "-----------------------------------------"
    foreach tb $fail_list { puts "   FAIL: $tb" }
} else {
    puts " ALL $total TESTBENCHES PASSED"
}
puts "========================================="
