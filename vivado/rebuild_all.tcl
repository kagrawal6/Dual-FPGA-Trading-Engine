# ============================================================================
# rebuild_all.tcl — One-shot rebuild for BOTH boards from a clean state
# ============================================================================
# Wipes vivado/hft_board_a/ and vivado/hft_board_b/ (the existing project
# directories), then recreates project + BD + bitstream + pynq overlay copy
# for each board sequentially.
#
# Use this AFTER any of:
#   - rtl/board_a/board_a_top_bd.v or rtl/board_b/board_b_top_bd.v changed
#     (i.e. AXI address width / port list changed)
#   - SystemVerilog source set added/removed under rtl/{shared,link,board_*}/
#   - constraints/hft_top.xdc changed
#
# Usage (from repo root, batch mode):
#   vivado -mode batch -source vivado/rebuild_all.tcl
#
# Or interactive:
#   vivado -mode tcl -source vivado/rebuild_all.tcl
#
# Or inside an open Vivado:
#   cd <repo_root>
#   source vivado/rebuild_all.tcl
#
# Total runtime ≈ 25–40 minutes (both boards, 8 jobs, modern workstation).
# ============================================================================

set script_dir [file dirname [file normalize [info script]]]
set proj_root  [file dirname $script_dir]

puts ""
puts "============================================================"
puts " REBUILD ALL — Dual-FPGA Trading Engine"
puts " Repo root: $proj_root"
puts "============================================================"

set t_start [clock seconds]

foreach board {a b} {
    set proj_name "hft_board_${board}"
    set proj_dir  [file join $proj_root vivado $proj_name]

    puts ""
    puts "============================================================"
    puts " >>> Board ${board}: starting fresh build"
    puts "============================================================"

    # Close anything currently open
    if {![catch {current_project} cur]} {
        close_project -quiet
    }

    # 1. Recreate project from scratch (the create_board_*.tcl uses -force)
    source [file join $script_dir "create_board_${board}.tcl"]

    # 2. Synth + impl + bitstream
    source [file join $script_dir "build.tcl"]

    # 3. Close before moving to next board
    close_project
}

# 4. Package both bitstreams into pynq/overlays/
puts ""
puts "============================================================"
puts " >>> Packaging bitstreams for PYNQ"
puts "============================================================"
source [file join $script_dir "package_pynq.tcl"]

set elapsed [expr {[clock seconds] - $t_start}]
set mins    [expr {$elapsed / 60}]
set secs    [expr {$elapsed % 60}]

puts ""
puts "============================================================"
puts " ALL DONE  (elapsed: ${mins}m ${secs}s)"
puts ""
puts " Bitstreams + .hwh files are in:"
puts "   ${proj_root}/pynq/overlays/board_a.bit + board_a.hwh"
puts "   ${proj_root}/pynq/overlays/board_b.bit + board_b.hwh"
puts ""
puts " Copy both files for each board to its PYNQ:"
puts "   scp pynq/overlays/board_a.bit  xilinx@<board_a_ip>:/home/xilinx/overlays/"
puts "   scp pynq/overlays/board_a.hwh  xilinx@<board_a_ip>:/home/xilinx/overlays/"
puts "   scp pynq/overlays/board_b.bit  xilinx@<board_b_ip>:/home/xilinx/overlays/"
puts "   scp pynq/overlays/board_b.hwh  xilinx@<board_b_ip>:/home/xilinx/overlays/"
puts "============================================================"
