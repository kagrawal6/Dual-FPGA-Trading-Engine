//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2025.2 (win64) Build 6299465 Fri Nov 14 19:35:11 GMT 2025
//Date        : Thu Apr 16 07:38:33 2026
//Host        : Kushal2009 running 64-bit major release  (build 9200)
//Command     : generate_target system_wrapper.bd
//Design      : system_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module system_wrapper
   (btn,
    led,
    pmod_ja,
    pmod_ja_ready,
    pmod_ja_valid,
    pmod_jb,
    pmod_jb_ready,
    pmod_jb_valid,
    rgb0,
    rgb1,
    sw);
  input [3:0]btn;
  output [7:0]led;
  input [3:0]pmod_ja;
  output pmod_ja_ready;
  input pmod_ja_valid;
  output [3:0]pmod_jb;
  input pmod_jb_ready;
  output pmod_jb_valid;
  output [2:0]rgb0;
  output [2:0]rgb1;
  input [7:0]sw;

  wire [3:0]btn;
  wire [7:0]led;
  wire [3:0]pmod_ja;
  wire pmod_ja_ready;
  wire pmod_ja_valid;
  wire [3:0]pmod_jb;
  wire pmod_jb_ready;
  wire pmod_jb_valid;
  wire [2:0]rgb0;
  wire [2:0]rgb1;
  wire [7:0]sw;

  system system_i
       (.btn(btn),
        .led(led),
        .pmod_ja(pmod_ja),
        .pmod_ja_ready(pmod_ja_ready),
        .pmod_ja_valid(pmod_ja_valid),
        .pmod_jb(pmod_jb),
        .pmod_jb_ready(pmod_jb_ready),
        .pmod_jb_valid(pmod_jb_valid),
        .rgb0(rgb0),
        .rgb1(rgb1),
        .sw(sw));
endmodule
