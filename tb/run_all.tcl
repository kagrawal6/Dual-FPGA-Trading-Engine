# ============================================================================
# tb/run_all.tcl — Vivado xsim runner for all SystemVerilog testbenches.
#
# Runs (or filters) the full suite of unit + integration testbenches against
# the current RTL.  Picks up the B2 changes:
#
#   • board_a_axi_regs / board_a_top    — 9-bit AXI address space
#   • board_b_axi_regs / board_b_top    — 10-bit AXI address space
#   • quote_book                         — best_bid_arr / best_ask_arr outputs
#   • position_tracker                   — pnl_cash_per_sym / last_fill_price /
#                                          trades_per_sym outputs
#
# Usage from the repo root:
#   vivado -mode batch -source tb/run_all.tcl
#
# Optional argument selects a subset:
#   vivado -mode batch -source tb/run_all.tcl -tclargs <tb_name|"b2">
#       <tb_name>  – run a single TB (e.g. tb_quote_book)
#       "b2"       – run only the testbenches touched by the B2 changes
# ============================================================================

set repo_root [file normalize [file dirname [file dirname [file normalize [info script]]]]]
set rtl_dir   $repo_root/rtl
set tb_dir    $repo_root/tb
set work_dir  $repo_root/sim_work
file mkdir $work_dir

# --- RTL file list (compile order: shared → link → board_a → board_b) ----
set rtl_files [list \
    $rtl_dir/shared/hft_pkg.sv          \
    $rtl_dir/shared/debounce.sv         \
    $rtl_dir/shared/lfsr32.sv           \
    $rtl_dir/shared/sync_fifo.sv        \
    $rtl_dir/link/link_tx.sv            \
    $rtl_dir/link/link_rx.sv            \
    $rtl_dir/board_a/market_noise_gen.sv \
    $rtl_dir/board_a/market_sim.sv      \
    $rtl_dir/board_a/exchange_lite.sv   \
    $rtl_dir/board_a/tx_arbiter.sv      \
    $rtl_dir/board_a/board_a_axi_regs.sv \
    $rtl_dir/board_a/board_a_ctrl.sv    \
    $rtl_dir/board_a/board_a_top.sv     \
    $rtl_dir/board_b/msg_demux.sv       \
    $rtl_dir/board_b/quote_book.sv      \
    $rtl_dir/board_b/feature_compute.sv \
    $rtl_dir/board_b/strategy_engine.sv \
    $rtl_dir/board_b/risk_manager.sv    \
    $rtl_dir/board_b/order_manager.sv   \
    $rtl_dir/board_b/position_tracker.sv \
    $rtl_dir/board_b/latency_histogram.sv \
    $rtl_dir/board_b/board_b_axi_regs.sv \
    $rtl_dir/board_b/board_b_ctrl.sv    \
    $rtl_dir/board_b/board_b_top.sv     \
]

# --- Testbench catalog ----------------------------------------------------
# Each entry: { tb_module_name tb_source_file  [b2?] }
set tb_list [list \
    {tb_lfsr32             $tb_dir/shared/tb_lfsr32.sv             0} \
    {tb_debounce           $tb_dir/shared/tb_debounce.sv           0} \
    {tb_sync_fifo          $tb_dir/shared/tb_sync_fifo.sv          0} \
    {tb_link_tx            $tb_dir/link/tb_link_tx.sv              0} \
    {tb_link_rx            $tb_dir/link/tb_link_rx.sv              0} \
    {tb_link_loopback      $tb_dir/link/tb_link_loopback.sv        0} \
    {tb_market_noise_gen   $tb_dir/board_a/tb_market_noise_gen.sv  0} \
    {tb_market_sim         $tb_dir/board_a/tb_market_sim.sv        0} \
    {tb_exchange_lite      $tb_dir/board_a/tb_exchange_lite.sv     0} \
    {tb_tx_arbiter         $tb_dir/board_a/tb_tx_arbiter.sv        0} \
    {tb_board_a_ctrl       $tb_dir/board_a/tb_board_a_ctrl.sv      0} \
    {tb_board_a_top        $tb_dir/board_a/tb_board_a_top.sv       1} \
    {tb_msg_demux          $tb_dir/board_b/tb_msg_demux.sv         0} \
    {tb_quote_book         $tb_dir/board_b/tb_quote_book.sv        1} \
    {tb_feature_compute    $tb_dir/board_b/tb_feature_compute.sv   0} \
    {tb_strategy_engine    $tb_dir/board_b/tb_strategy_engine.sv   0} \
    {tb_risk_manager       $tb_dir/board_b/tb_risk_manager.sv      0} \
    {tb_order_manager      $tb_dir/board_b/tb_order_manager.sv     0} \
    {tb_position_tracker   $tb_dir/board_b/tb_position_tracker.sv  1} \
    {tb_latency_histogram  $tb_dir/board_b/tb_latency_histogram.sv 0} \
    {tb_board_b_axi_regs   $tb_dir/board_b/tb_board_b_axi_regs.sv  1} \
    {tb_board_b_ctrl       $tb_dir/board_b/tb_board_b_ctrl.sv      0} \
    {tb_board_b_pipeline   $tb_dir/board_b/tb_board_b_pipeline.sv  1} \
    {tb_board_b_top        $tb_dir/board_b/tb_board_b_top.sv       1} \
    {tb_system_top         $tb_dir/tb_system_top.sv                1} \
]

# --- Argument parsing ----------------------------------------------------
set selector "all"
if {[llength $argv] > 0} { set selector [lindex $argv 0] }

set selected {}
foreach entry $tb_list {
    set tb_name [lindex $entry 0]
    set tb_file [subst [lindex $entry 1]]
    set is_b2   [lindex $entry 2]
    set keep 0
    switch -exact -- $selector {
        "all" { set keep 1 }
        "b2"  { if {$is_b2} { set keep 1 } }
        default { if {$tb_name eq $selector} { set keep 1 } }
    }
    if {$keep} { lappend selected [list $tb_name $tb_file] }
}

if {[llength $selected] == 0} {
    puts "ERROR: no testbenches matched selector '$selector'"
    exit 1
}

# --- Run each testbench --------------------------------------------------
set pass_list {}
set fail_list {}

foreach entry $selected {
    set tb_name [lindex $entry 0]
    set tb_file [lindex $entry 1]
    set log     $work_dir/$tb_name.log

    # Per-TB work subdirectory keeps xsim.dir/ locks isolated so that a hang
    # in one TB cannot prevent the next TB's xvlog from acquiring its work
    # library.
    set tb_work_dir $work_dir/$tb_name.work
    file mkdir $tb_work_dir

    puts "============================================================"
    puts " RUN $tb_name"
    puts "============================================================"
    cd $tb_work_dir

    # Drop a local copy of the xsim runner script with a space-free path.
    # xsim's -tclbatch handling can mis-parse paths containing spaces (it
    # splits on whitespace and tries to `source` each token), so we use a
    # plain filename relative to the current working directory.
    #
    # NOTE: When the testbench calls $finish, xsim's `run` returns control to
    # this batch script — it does NOT auto-exit. So we deliberately keep this
    # script silent: we detect a real timeout below by looking for the
    # absence of a "$finish called" line in the log.
    set runner_fp [open "_runner.tcl" w]
    puts $runner_fp "run 50ms"
    puts $runner_fp "quit"
    close $runner_fp

    # 1) xvlog: compile RTL + this TB
    set xvlog_cmd "xvlog -sv"
    foreach rf $rtl_files { append xvlog_cmd " \"$rf\"" }
    append xvlog_cmd " \"$tb_file\""

    # 2) xelab → 3) xsim (with hard 5-ms sim-time cap via tclbatch runner)
    set xelab_cmd "xelab --debug typical -L unisims_ver -L secureip $tb_name -s ${tb_name}_sim"
    set xsim_cmd  "xsim ${tb_name}_sim -tclbatch _runner.tcl"

    set rc 0
    if {[catch {exec {*}$xvlog_cmd >& $log} msg]} { set rc 1 }
    if {$rc == 0 && [catch {exec {*}$xelab_cmd >>& $log} msg]} { set rc 1 }
    if {$rc == 0 && [catch {exec {*}$xsim_cmd >>& $log} msg]} { set rc 1 }

    # Examine log for FAIL markers
    set log_fp [open $log r]
    set log_text [read $log_fp]
    close $log_fp
    set has_fail    [regexp {(?i)\[FAIL\]|TESTBENCH FAILED|Fatal:} $log_text]
    set has_passed  [regexp {(?i)PASS \(|testbench complete|tb_\w+ complete} $log_text]
    set has_finish  [regexp {\$finish called} $log_text]
    # Timeout = simulation never reached $finish before the 5-ms tclbatch cap
    set has_timeout [expr {!$has_finish}]

    if {$rc == 0 && !$has_fail && $has_finish && $has_passed} {
        lappend pass_list $tb_name
        puts " PASS — see $log"
    } elseif {$has_timeout} {
        lappend fail_list $tb_name
        puts " FAIL (timeout) — see $log"
    } else {
        lappend fail_list $tb_name
        puts " FAIL — see $log"
    }
    cd $repo_root
}

# --- Summary -------------------------------------------------------------
puts "\n============================================================"
puts " run_all.tcl summary  (selector: $selector)"
puts "============================================================"
puts "  PASSED: [llength $pass_list]"
foreach n $pass_list { puts "    + $n" }
puts "  FAILED: [llength $fail_list]"
foreach n $fail_list { puts "    - $n" }

# Do NOT call `exit` — that would kill an interactive Vivado shell.
# In batch mode (`vivado -mode batch -source ...`) Vivado exits naturally
# when the script ends. Return the failure count for programmatic use.
return [llength $fail_list]
