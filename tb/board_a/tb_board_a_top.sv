// ============================================================================
// Testbench: tb_board_a_top
// Full integration test shell for board_a_top: top-level Board A wrapper with
// 4-state FSM, AXI-Lite slave interface, PMOD link signals (JA/JB), and
// physical I/O (buttons, switches, LEDs).
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_a_top;

    localparam C_S_AXI_ADDR_WIDTH = 8;
    localparam C_S_AXI_DATA_WIDTH = 32;
    localparam LINK_W             = LINK_DATA_W;

    logic        clk;
    logic        rst_n;
    logic [3:0]  btn;
    logic [7:0]  sw;
    logic [7:0]  led;
    logic [2:0]  rgb0;
    logic [2:0]  rgb1;
    logic [LINK_W-1:0] pmod_ja;
    logic              pmod_ja_valid;
    logic              pmod_ja_ready;
    logic [LINK_W-1:0] pmod_jb;
    logic              pmod_jb_valid;
    logic              pmod_jb_ready;
    logic [C_S_AXI_ADDR_WIDTH-1:0] s_axi_awaddr;
    logic [2:0]                     s_axi_awprot;
    logic                           s_axi_awvalid;
    logic                           s_axi_awready;
    logic [C_S_AXI_DATA_WIDTH-1:0] s_axi_wdata;
    logic [3:0]                     s_axi_wstrb;
    logic                           s_axi_wvalid;
    logic                           s_axi_wready;
    logic [1:0]                     s_axi_bresp;
    logic                           s_axi_bvalid;
    logic                           s_axi_bready;
    logic [C_S_AXI_ADDR_WIDTH-1:0] s_axi_araddr;
    logic [2:0]                     s_axi_arprot;
    logic                           s_axi_arvalid;
    logic                           s_axi_arready;
    logic [C_S_AXI_DATA_WIDTH-1:0] s_axi_rdata;
    logic [1:0]                     s_axi_rresp;
    logic                           s_axi_rvalid;
    logic                           s_axi_rready;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    board_a_top dut (
        .clk           (clk),
        .rst_n         (rst_n),
        .btn           (btn),
        .sw            (sw),
        .led           (led),
        .rgb0          (rgb0),
        .rgb1          (rgb1),
        .pmod_ja       (pmod_ja),
        .pmod_ja_valid (pmod_ja_valid),
        .pmod_ja_ready (pmod_ja_ready),
        .pmod_jb       (pmod_jb),
        .pmod_jb_valid (pmod_jb_valid),
        .pmod_jb_ready (pmod_jb_ready),
        .s_axi_awaddr  (s_axi_awaddr),
        .s_axi_awprot  (s_axi_awprot),
        .s_axi_awvalid (s_axi_awvalid),
        .s_axi_awready (s_axi_awready),
        .s_axi_wdata   (s_axi_wdata),
        .s_axi_wstrb   (s_axi_wstrb),
        .s_axi_wvalid  (s_axi_wvalid),
        .s_axi_wready  (s_axi_wready),
        .s_axi_bresp   (s_axi_bresp),
        .s_axi_bvalid  (s_axi_bvalid),
        .s_axi_bready  (s_axi_bready),
        .s_axi_araddr  (s_axi_araddr),
        .s_axi_arprot  (s_axi_arprot),
        .s_axi_arvalid (s_axi_arvalid),
        .s_axi_arready (s_axi_arready),
        .s_axi_rdata   (s_axi_rdata),
        .s_axi_rresp   (s_axi_rresp),
        .s_axi_rvalid  (s_axi_rvalid),
        .s_axi_rready  (s_axi_rready)
    );

    initial begin
        // TODO: Add test stimulus
        #1000;
        $finish;
    end

endmodule
