# ============================================================================
# export_hw.tcl — Export hardware platform (.xsa) for Vitis
# ============================================================================
# Usage (Vivado Tcl console, with a project open and bitstream generated):
#   source vivado/export_hw.tcl
# ============================================================================

if {[catch {current_project} msg]} {
    puts "ERROR: No project open."
    return
}

set proj_name [get_property NAME [current_project]]
set proj_dir  [get_property DIRECTORY [current_project]]
set xsa_path  "${proj_dir}/${proj_name}.xsa"

# Ensure bitstream is ready
set impl_status [get_property STATUS [get_runs impl_1]]
if {$impl_status ne "write_bitstream Complete!"} {
    puts "ERROR: Bitstream not generated. Run  source vivado/build.tcl  first."
    return
}

puts "Exporting hardware platform to: $xsa_path"

write_hw_platform -fixed -include_bit -force -file $xsa_path

puts ""
puts "============================================================"
puts " Hardware platform exported: $xsa_path"
puts ""
puts " Open Vitis IDE and create a platform project from this .xsa"
puts "============================================================"
