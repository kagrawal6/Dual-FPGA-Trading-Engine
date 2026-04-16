# ==============================================================================
# package_pynq.tcl — Copy .bit + .hwh into pynq/ with matching base names
# ==============================================================================
# Usage (Vivado Tcl console, after build.tcl completes for BOTH boards):
#   cd {C:/Users/Kushal Agrawal/UW-madison school work/Dual-FPGA-Trading-Engine}
#   source vivado/package_pynq.tcl
# ==============================================================================

set proj_root [file dirname [file dirname [file normalize [info script]]]]
set pynq_dir  [file join $proj_root pynq overlays]
file mkdir $pynq_dir

foreach board {board_a board_b} {
    set proj_name "hft_${board}"
    set proj_dir  [file join $proj_root vivado $proj_name]

    set bit_src [file normalize [file join $proj_dir ${proj_name}.runs impl_1 system_wrapper.bit]]
    set hwh_src [file normalize [file join $proj_dir ${proj_name}.gen sources_1 bd system hw_handoff system.hwh]]

    if {![file exists $bit_src] || ![file exists $hwh_src]} {
        puts "WARNING: Skipping $board — bitstream or hwh not found."
        puts "         Run create_${board}.tcl + build.tcl first."
        continue
    }

    file copy -force $bit_src [file join $pynq_dir ${board}.bit]
    file copy -force $hwh_src [file join $pynq_dir ${board}.hwh]
    puts "Packaged $board overlay -> $pynq_dir/${board}.bit + ${board}.hwh"
}

puts "\nDone. Upload the pynq/ folder to each PYNQ board."
