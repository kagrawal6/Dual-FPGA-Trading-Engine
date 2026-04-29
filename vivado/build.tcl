# ============================================================================
# build.tcl — Synthesize, Implement, and Generate Bitstream
# ============================================================================
# Usage (from Vivado Tcl console, with a project already open):
#   source vivado/build.tcl
#
# Or in batch mode:
#   vivado -mode batch -source vivado/build.tcl -tclargs <project_xpr_path>
# ============================================================================

# If a project path was passed as argument, open it
if {[llength $argv] > 0} {
    set xpr [lindex $argv 0]
    if {[file exists $xpr]} {
        open_project $xpr
    } else {
        puts "ERROR: Project file not found: $xpr"
        return
    }
}

# Verify a project is open
if {[catch {current_project} msg]} {
    puts "ERROR: No project open. Open a project first or pass its .xpr path."
    return
}

set proj [get_property NAME [current_project]]
puts "============================================================"
puts " Building project: $proj"
puts "============================================================"

# ── Synthesis ──────────────────────────────────────────────────────────────
# NOTE: -jobs reduced from 4 → 2 to keep peak memory under ~5 GB. With 4
# parallel OOC IP synth subruns (Zynq PS + SmartConnect + reset + hft_core),
# Vivado peaks at ~6–8 GB, which OOMs on a 16 GB Windows host where Chrome
# / Cursor / etc. are also resident. Two parallel jobs is the sweet spot.
puts "\n>>> Running Synthesis ..."
reset_run synth_1
launch_runs synth_1 -jobs 2
wait_on_run synth_1

set synth_status [get_property STATUS [get_runs synth_1]]
puts "    Synthesis status: $synth_status"
if {$synth_status ne "synth_design Complete!"} {
    puts "ERROR: Synthesis failed — check messages for details."
    return
}

# ── Implementation + Bitstream ─────────────────────────────────────────────
# NOTE: -jobs reduced from 4 → 2 (see synth note above). Place + Route +
# write_bitstream is even more memory-hungry per job than synth.
puts "\n>>> Running Implementation + write_bitstream ..."
launch_runs impl_1 -to_step write_bitstream -jobs 2
wait_on_run impl_1

set impl_status [get_property STATUS [get_runs impl_1]]
puts "    Implementation status: $impl_status"
if {$impl_status ne "write_bitstream Complete!"} {
    puts "ERROR: Implementation/bitstream failed — check messages."
    return
}

# Locate the bitstream
set impl_dir [get_property DIRECTORY [get_runs impl_1]]
set bit_file [glob -nocomplain ${impl_dir}/*.bit]

puts ""
puts "============================================================"
puts " Build complete!"
puts " Bitstream : $bit_file"
puts ""
puts " Next: Export hardware (.xsa) for Vitis:"
puts "   write_hw_platform -fixed -include_bit \\   "
puts "       -file ${proj}.xsa"
puts "============================================================"

# ── Timing summary ────────────────────────────────────────────────────────
puts "\n--- Post-implementation timing summary ---"
open_run impl_1
report_timing_summary -max_paths 10
