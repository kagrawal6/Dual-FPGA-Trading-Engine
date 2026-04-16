# ==============================================================================
# HFT Capstone — XDC Constraints for AMD AUP-ZU3
# Shared between Board A and Board B (same physical hardware, pin directions
# determined by RTL port declarations).
# Source: AUP-ZU3 board master XDC from Real Digital
# ==============================================================================

# --- Clock (PS FCLK0) ---
# The Zynq PS block design auto-constrains pl_clk0; no manual create_clock
# needed.  Uncomment below ONLY for a non-block-design flow where the PS
# instance is named "zynq_ps":
# create_clock -period 10.000 -name clk_pl [get_pins zynq_ps/FCLK_CLK0]

# ==============================================================================
# PMOD JA — Cable 1 (A→B data path)
#   Board A: JA[3:0]=TX data, JA[4]=TX valid, JA[5]=RX ready
#   Board B: JA[3:0]=RX data, JA[4]=RX valid, JA[5]=TX ready
# ==============================================================================
set_property PACKAGE_PIN J12  [get_ports {pmod_ja[0]}]
set_property PACKAGE_PIN H12  [get_ports {pmod_ja[1]}]
set_property PACKAGE_PIN H11  [get_ports {pmod_ja[2]}]
set_property PACKAGE_PIN G10  [get_ports {pmod_ja[3]}]
set_property PACKAGE_PIN K13  [get_ports {pmod_ja_valid}]
set_property PACKAGE_PIN K12  [get_ports {pmod_ja_ready}]
# JA[6]=J11, JA[7]=J10 — reserved for 8-bit stretch
set_property IOSTANDARD LVCMOS33 [get_ports {pmod_ja[*]}]
set_property IOSTANDARD LVCMOS33 [get_ports {pmod_ja_valid}]
set_property IOSTANDARD LVCMOS33 [get_ports {pmod_ja_ready}]

# ==============================================================================
# PMOD JB — Cable 2 (B→A data path)
#   Board A: JB[3:0]=RX data, JB[4]=RX valid, JB[5]=TX ready
#   Board B: JB[3:0]=TX data, JB[4]=TX valid, JB[5]=RX ready
# ==============================================================================
set_property PACKAGE_PIN E12  [get_ports {pmod_jb[0]}]
set_property PACKAGE_PIN D11  [get_ports {pmod_jb[1]}]
set_property PACKAGE_PIN B11  [get_ports {pmod_jb[2]}]
set_property PACKAGE_PIN A10  [get_ports {pmod_jb[3]}]
set_property PACKAGE_PIN C11  [get_ports {pmod_jb_valid}]
set_property PACKAGE_PIN B10  [get_ports {pmod_jb_ready}]
# JB[6]=A12, JB[7]=A11 — reserved for 8-bit stretch
set_property IOSTANDARD LVCMOS33 [get_ports {pmod_jb[*]}]
set_property IOSTANDARD LVCMOS33 [get_ports {pmod_jb_valid}]
set_property IOSTANDARD LVCMOS33 [get_ports {pmod_jb_ready}]

# ==============================================================================
# PMOD JAB Extension (stretch goal: 8-bit link valid/ready)
# ==============================================================================
# set_property PACKAGE_PIN F12  [get_ports {pmod_jab[0]}]
# set_property PACKAGE_PIN G11  [get_ports {pmod_jab[1]}]
# set_property PACKAGE_PIN E10  [get_ports {pmod_jab[2]}]
# set_property PACKAGE_PIN F10  [get_ports {pmod_jab[3]}]
# set_property IOSTANDARD LVCMOS33 [get_ports {pmod_jab[*]}]

# ==============================================================================
# Switches (active-high)
# ==============================================================================
set_property PACKAGE_PIN AB1  [get_ports {sw[0]}]
set_property PACKAGE_PIN AF1  [get_ports {sw[1]}]
set_property PACKAGE_PIN AE3  [get_ports {sw[2]}]
set_property PACKAGE_PIN AC2  [get_ports {sw[3]}]
set_property PACKAGE_PIN AC1  [get_ports {sw[4]}]
set_property PACKAGE_PIN AD6  [get_ports {sw[5]}]
set_property PACKAGE_PIN AD1  [get_ports {sw[6]}]
set_property PACKAGE_PIN AD2  [get_ports {sw[7]}]
set_property IOSTANDARD LVCMOS18 [get_ports {sw[*]}]

# ==============================================================================
# Pushbuttons (active-high, active-low active depends on board rev)
# ==============================================================================
set_property PACKAGE_PIN AB6  [get_ports {btn[0]}]
set_property PACKAGE_PIN AB7  [get_ports {btn[1]}]
set_property PACKAGE_PIN AB2  [get_ports {btn[2]}]
set_property PACKAGE_PIN AC6  [get_ports {btn[3]}]
set_property IOSTANDARD LVCMOS18 [get_ports {btn[*]}]

# ==============================================================================
# LEDs (active-high)
# ==============================================================================
set_property PACKAGE_PIN AF5  [get_ports {led[0]}]
set_property PACKAGE_PIN AE7  [get_ports {led[1]}]
set_property PACKAGE_PIN AH2  [get_ports {led[2]}]
set_property PACKAGE_PIN AE5  [get_ports {led[3]}]
set_property PACKAGE_PIN AH1  [get_ports {led[4]}]
set_property PACKAGE_PIN AE4  [get_ports {led[5]}]
set_property PACKAGE_PIN AG1  [get_ports {led[6]}]
set_property PACKAGE_PIN AF2  [get_ports {led[7]}]
set_property IOSTANDARD LVCMOS18 [get_ports {led[*]}]

# ==============================================================================
# RGB LEDs (active-high, accent colors)
# ==============================================================================
set_property PACKAGE_PIN AD7  [get_ports {rgb0[0]}]
set_property PACKAGE_PIN AD9  [get_ports {rgb0[1]}]
set_property PACKAGE_PIN AE9  [get_ports {rgb0[2]}]
set_property IOSTANDARD LVCMOS18 [get_ports {rgb0[*]}]

set_property PACKAGE_PIN AG9  [get_ports {rgb1[0]}]
set_property PACKAGE_PIN AE8  [get_ports {rgb1[1]}]
set_property PACKAGE_PIN AF8  [get_ports {rgb1[2]}]
set_property IOSTANDARD LVCMOS18 [get_ports {rgb1[*]}]
