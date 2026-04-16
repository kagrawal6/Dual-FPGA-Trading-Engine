# ============================================================================
# create_board_b.tcl — Vivado project + block design for HFT Board B
# ============================================================================
# Usage:  Open Vivado ▸ Tcl Console ▸
#         cd <project_root>
#         source vivado/create_board_b.tcl
# ============================================================================

set script_dir [file dirname [file normalize [info script]]]
set proj_root  [file dirname $script_dir]
set proj_name  "hft_board_b"
set proj_dir   [file join $proj_root vivado $proj_name]
set part       "xczu3eg-sfvc784-2-e"
set bd_name    "system"

puts "============================================================"
puts " Creating Vivado project : $proj_name"
puts " Part                    : $part"
puts " Project directory       : $proj_dir"
puts " RTL root                : $proj_root/rtl"
puts "============================================================"

# ── 1. Create project ─────────────────────────────────────────────────────
create_project $proj_name "$proj_dir" -part $part -force

# ── 2. Add RTL sources ────────────────────────────────────────────────────
# Board B needs shared modules, link layer, and all board_b modules.
add_files -norecurse [glob "[file join $proj_root rtl shared]/*.sv"]
add_files -norecurse [glob "[file join $proj_root rtl link]/*.sv"]
add_files -norecurse [glob "[file join $proj_root rtl board_b]/*.sv"]
add_files -norecurse [list [file normalize [file join $proj_root rtl board_b board_b_top_bd.v]]]
set_property file_type SystemVerilog [get_files -of_objects [get_filesets sources_1] *.sv]
update_compile_order -fileset sources_1

# ── 3. Add constraints ────────────────────────────────────────────────────
set xdc_path [file normalize [file join $proj_root constraints hft_top.xdc]]
add_files -fileset constrs_1 -norecurse [list $xdc_path]

# ── 4. Create block design ────────────────────────────────────────────────
create_bd_design $bd_name

# ── 5. Add Zynq UltraScale+ PS ────────────────────────────────────────────
set ps_cell [create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e zynq_ps]

# NOTE: If you have board files installed for the AUP-ZU3, uncomment the
# next line to auto-configure DDR, UART, etc. for your specific board.
# apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e \
#     -config {apply_board_preset "1"} [get_bd_cells zynq_ps]

set_property -dict [list \
    CONFIG.PSU__USE__M_AXI_GP0          {1}   \
    CONFIG.PSU__MAXIGP0__DATA_WIDTH     {32}  \
    CONFIG.PSU__USE__M_AXI_GP1          {0}   \
    CONFIG.PSU__USE__M_AXI_GP2          {0}   \
    CONFIG.PSU__FPGA_PL0_ENABLE         {1}   \
    CONFIG.PSU__CRL_APB__PL0_REF_CTRL__FREQMHZ {50} \
    CONFIG.PSU__USE__FABRIC__RST        {1}   \
    CONFIG.PSU__NUM_FABRIC_RESETS       {1}   \
] $ps_cell

# ── 6. Add RTL module to block design ─────────────────────────────────────
# Use the Verilog wrapper (Vivado BD does not support SV module references).
create_bd_cell -type module -reference board_b_top_bd hft_core

# ── 7. Add infrastructure IPs ─────────────────────────────────────────────
set sc_cell [create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect axi_sc]
set_property -dict [list CONFIG.NUM_SI {1} CONFIG.NUM_MI {1}] $sc_cell

create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset rst_sys

# ── 8. Connect clocks ─────────────────────────────────────────────────────
connect_bd_net [get_bd_pins zynq_ps/pl_clk0] \
    [get_bd_pins hft_core/clk]               \
    [get_bd_pins axi_sc/aclk]                \
    [get_bd_pins rst_sys/slowest_sync_clk]   \
    [get_bd_pins zynq_ps/maxihpm0_fpd_aclk]

# ── 9. Connect resets ─────────────────────────────────────────────────────
connect_bd_net [get_bd_pins zynq_ps/pl_resetn0] \
    [get_bd_pins rst_sys/ext_reset_in]

connect_bd_net [get_bd_pins rst_sys/peripheral_aresetn] \
    [get_bd_pins hft_core/rst_n]                        \
    [get_bd_pins axi_sc/aresetn]

# ── 10. Connect AXI ───────────────────────────────────────────────────────
connect_bd_intf_net \
    [get_bd_intf_pins zynq_ps/M_AXI_HPM0_FPD] \
    [get_bd_intf_pins axi_sc/S00_AXI]

connect_bd_intf_net \
    [get_bd_intf_pins axi_sc/M00_AXI] \
    [get_bd_intf_pins hft_core/s_axi]

# ── 11. Create external I/O ports ─────────────────────────────────────────
# Board B PMOD directions are REVERSED vs Board A:
#   JA = RX (input from Board A)
#   JB = TX (output to Board A)

# Inputs
create_bd_port -dir I -from 3 -to 0 btn
create_bd_port -dir I -from 7 -to 0 sw
create_bd_port -dir I -from 3 -to 0 pmod_ja
create_bd_port -dir I              pmod_ja_valid
create_bd_port -dir I              pmod_jb_ready

# Outputs
create_bd_port -dir O -from 7 -to 0 led
create_bd_port -dir O -from 2 -to 0 rgb0
create_bd_port -dir O -from 2 -to 0 rgb1
create_bd_port -dir O              pmod_ja_ready
create_bd_port -dir O -from 3 -to 0 pmod_jb
create_bd_port -dir O              pmod_jb_valid

# Wire external ports ↔ RTL module
connect_bd_net [get_bd_ports btn]           [get_bd_pins hft_core/btn]
connect_bd_net [get_bd_ports sw]            [get_bd_pins hft_core/sw]
connect_bd_net [get_bd_ports pmod_ja]       [get_bd_pins hft_core/pmod_ja]
connect_bd_net [get_bd_ports pmod_ja_valid] [get_bd_pins hft_core/pmod_ja_valid]
connect_bd_net [get_bd_ports pmod_jb_ready] [get_bd_pins hft_core/pmod_jb_ready]

connect_bd_net [get_bd_pins hft_core/led]           [get_bd_ports led]
connect_bd_net [get_bd_pins hft_core/rgb0]          [get_bd_ports rgb0]
connect_bd_net [get_bd_pins hft_core/rgb1]          [get_bd_ports rgb1]
connect_bd_net [get_bd_pins hft_core/pmod_ja_ready] [get_bd_ports pmod_ja_ready]
connect_bd_net [get_bd_pins hft_core/pmod_jb]       [get_bd_ports pmod_jb]
connect_bd_net [get_bd_pins hft_core/pmod_jb_valid] [get_bd_ports pmod_jb_valid]

# ── 12. Assign AXI address ────────────────────────────────────────────────
assign_bd_address

# ── 13. Validate block design ─────────────────────────────────────────────
regenerate_bd_layout
validate_bd_design
save_bd_design

# ── 14. Generate output products ──────────────────────────────────────────
generate_target all [get_files ${bd_name}.bd]

# ── 15. Create HDL wrapper (Vivado-managed) ────────────────────────────────
make_wrapper -files [get_files ${bd_name}.bd] -top
set gen_hdl_dir [file normalize [file join $proj_dir ${proj_name}.gen sources_1 bd $bd_name hdl]]
set src_hdl_dir [file normalize [file join $proj_dir ${proj_name}.srcs sources_1 bd $bd_name hdl]]
set wrapper_file [glob -nocomplain [file join $gen_hdl_dir ${bd_name}_wrapper*]]
if {$wrapper_file eq ""} {
    set wrapper_file [glob [file join $src_hdl_dir ${bd_name}_wrapper*]]
}
add_files -norecurse $wrapper_file
update_compile_order -fileset sources_1
set_property top ${bd_name}_wrapper [current_fileset]

puts ""
puts "============================================================"
puts " Board B project created successfully!"
puts ""
puts " Next steps:"
puts "   1. Open the Address Editor and note the AXI base address"
puts "   2. source vivado/build.tcl   (to synthesise + bitstream)"
puts "============================================================"
