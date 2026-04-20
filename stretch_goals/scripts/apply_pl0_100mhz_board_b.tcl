# ============================================================================
# apply_pl0_100mhz_board_b.tcl — Set PS PL0 fabric clock to 100 MHz (Board B)
# ============================================================================
# Baseline create_board_b.tcl uses 50 MHz for PL0. This script updates an
# existing block design to 100 MHz to match README / spec intent.
#
# Usage (Vivado Tcl Console):
#   source /path/to/repo/stretch_goals/scripts/apply_pl0_100mhz_board_b.tcl
# ============================================================================

set script_dir [file dirname [file normalize [info script]]]
set repo_root  [file normalize [file join $script_dir .. ..]]
set proj_path  [file join $repo_root vivado hft_board_b hft_board_b.xpr]

if {![file exists $proj_path]} {
    puts "ERROR: Project not found: $proj_path"
    puts "       Create it first: source vivado/create_board_b.tcl"
    return
}

puts "Opening: $proj_path"
open_project $proj_path

set bd_file [get_files -quiet system.bd]
if {$bd_file eq ""} {
    puts "ERROR: system.bd not found in project."
    return
}

open_bd_design $bd_file

if {[catch {get_bd_cells zynq_ps} ps_cell]} {
    puts "ERROR: zynq_ps not found in block design."
    return
}

set_property -dict [list CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {100}] $ps_cell

puts "INFO: PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ set to 100 MHz for Board B."
puts "      Re-run synth/impl; if you add MMCM, use MMCM_CLKIN1_PERIOD 10.000 ns."

validate_bd_design
save_bd_design
generate_target all [get_files system.bd]

puts "DONE: Block design saved and generation targets updated."
