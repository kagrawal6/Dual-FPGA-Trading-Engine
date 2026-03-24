// ============================================================================
// Testbench: tb_system_top
// End-to-end system test. Instantiates both board_a_top and board_b_top,
// connects their PMOD ports together (Board A pmod_ja → Board B pmod_ja,
// Board A pmod_jb ← Board B pmod_jb, with ready signals crossed). Each board
// has its own AXI-Lite interface for independent configuration.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_system_top;

    localparam LINK_W_A            = LINK_DATA_W;
    localparam LINK_W_B            = LINK_DATA_W;
    localparam C_S_AXI_ADDR_WIDTH_A = 8;
    localparam C_S_AXI_ADDR_WIDTH_B = 9;
    localparam C_S_AXI_DATA_WIDTH  = 32;

    logic                     clk;
    logic                     rst_n;

    // Board A physical I/O
    logic [3:0]               btn_a;
    logic [7:0]               sw_a;
    logic [7:0]               led_a;
    logic [2:0]               rgb0_a;
    logic [2:0]               rgb1_a;

    // Board B physical I/O
    logic [3:0]               btn_b;
    logic [7:0]               sw_b;
    logic [7:0]               led_b;
    logic [2:0]               rgb0_b;
    logic [2:0]               rgb1_b;

    // PMOD interconnect: Board A TX (pmod_ja) → Board B RX (pmod_ja)
    logic [LINK_W_A-1:0]      pmod_ja_data;      // shared wire
    logic                     pmod_ja_valid_a2b;  // A drives, B receives
    logic                     pmod_ja_ready_b2a; // B drives, A receives

    // PMOD interconnect: Board B TX (pmod_jb) → Board A RX (pmod_jb)
    logic [LINK_W_B-1:0]      pmod_jb_data;      // shared wire
    logic                     pmod_jb_valid_b2a;  // B drives, A receives
    logic                     pmod_jb_ready_a2b; // A drives, B receives

    // Board A AXI-Lite
    logic [C_S_AXI_ADDR_WIDTH_A-1:0] s_axi_awaddr_a;
    logic [2:0]                       s_axi_awprot_a;
    logic                               s_axi_awvalid_a;
    logic                               s_axi_awready_a;
    logic [C_S_AXI_DATA_WIDTH-1:0]     s_axi_wdata_a;
    logic [3:0]                         s_axi_wstrb_a;
    logic                               s_axi_wvalid_a;
    logic                               s_axi_wready_a;
    logic [1:0]                         s_axi_bresp_a;
    logic                               s_axi_bvalid_a;
    logic                               s_axi_bready_a;
    logic [C_S_AXI_ADDR_WIDTH_A-1:0] s_axi_araddr_a;
    logic [2:0]                       s_axi_arprot_a;
    logic                               s_axi_arvalid_a;
    logic                               s_axi_arready_a;
    logic [C_S_AXI_DATA_WIDTH-1:0]     s_axi_rdata_a;
    logic [1:0]                         s_axi_rresp_a;
    logic                               s_axi_rvalid_a;
    logic                               s_axi_rready_a;

    // Board B AXI-Lite
    logic [C_S_AXI_ADDR_WIDTH_B-1:0] s_axi_awaddr_b;
    logic [2:0]                       s_axi_awprot_b;
    logic                               s_axi_awvalid_b;
    logic                               s_axi_awready_b;
    logic [C_S_AXI_DATA_WIDTH-1:0]     s_axi_wdata_b;
    logic [3:0]                         s_axi_wstrb_b;
    logic                               s_axi_wvalid_b;
    logic                               s_axi_wready_b;
    logic [1:0]                         s_axi_bresp_b;
    logic                               s_axi_bvalid_b;
    logic                               s_axi_bready_b;
    logic [C_S_AXI_ADDR_WIDTH_B-1:0] s_axi_araddr_b;
    logic [2:0]                       s_axi_arprot_b;
    logic                               s_axi_arvalid_b;
    logic                               s_axi_arready_b;
    logic [C_S_AXI_DATA_WIDTH-1:0]     s_axi_rdata_b;
    logic [1:0]                         s_axi_rresp_b;
    logic                               s_axi_rvalid_b;
    logic                               s_axi_rready_b;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low rst_n, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    // Board A: Exchange + Market Simulator
    // pmod_ja = TX (A → B), pmod_jb = RX (B → A)
    board_a_top u_board_a (
        .clk            (clk),
        .rst_n          (rst_n),
        .btn            (btn_a),
        .sw             (sw_a),
        .led            (led_a),
        .rgb0           (rgb0_a),
        .rgb1           (rgb1_a),
        .pmod_ja        (pmod_ja_data),
        .pmod_ja_valid  (pmod_ja_valid_a2b),
        .pmod_ja_ready  (pmod_ja_ready_b2a),
        .pmod_jb        (pmod_jb_data),
        .pmod_jb_valid  (pmod_jb_valid_b2a),
        .pmod_jb_ready  (pmod_jb_ready_a2b),
        .s_axi_awaddr   (s_axi_awaddr_a),
        .s_axi_awprot   (s_axi_awprot_a),
        .s_axi_awvalid  (s_axi_awvalid_a),
        .s_axi_awready  (s_axi_awready_a),
        .s_axi_wdata    (s_axi_wdata_a),
        .s_axi_wstrb    (s_axi_wstrb_a),
        .s_axi_wvalid   (s_axi_wvalid_a),
        .s_axi_wready   (s_axi_wready_a),
        .s_axi_bresp    (s_axi_bresp_a),
        .s_axi_bvalid   (s_axi_bvalid_a),
        .s_axi_bready   (s_axi_bready_a),
        .s_axi_araddr   (s_axi_araddr_a),
        .s_axi_arprot   (s_axi_arprot_a),
        .s_axi_arvalid  (s_axi_arvalid_a),
        .s_axi_arready  (s_axi_arready_a),
        .s_axi_rdata    (s_axi_rdata_a),
        .s_axi_rresp    (s_axi_rresp_a),
        .s_axi_rvalid   (s_axi_rvalid_a),
        .s_axi_rready   (s_axi_rready_a)
    );

    // Board B: use stub until board_b_top is fully wired (see tb/stubs/)
    board_b_top_stub u_board_b (
        .clk            (clk),
        .rst_n          (rst_n),
        .btn            (btn_b),
        .sw             (sw_b),
        .led            (led_b),
        .rgb0           (rgb0_b),
        .rgb1           (rgb1_b),
        .pmod_ja        (pmod_ja_data),
        .pmod_ja_valid  (pmod_ja_valid_a2b),
        .pmod_ja_ready  (pmod_ja_ready_b2a),
        .pmod_jb        (pmod_jb_data),
        .pmod_jb_valid  (pmod_jb_valid_b2a),
        .pmod_jb_ready  (pmod_jb_ready_a2b),
        .s_axi_awaddr   (s_axi_awaddr_b),
        .s_axi_awprot   (s_axi_awprot_b),
        .s_axi_awvalid  (s_axi_awvalid_b),
        .s_axi_awready  (s_axi_awready_b),
        .s_axi_wdata    (s_axi_wdata_b),
        .s_axi_wstrb    (s_axi_wstrb_b),
        .s_axi_wvalid   (s_axi_wvalid_b),
        .s_axi_wready   (s_axi_wready_b),
        .s_axi_bresp    (s_axi_bresp_b),
        .s_axi_bvalid   (s_axi_bvalid_b),
        .s_axi_bready   (s_axi_bready_b),
        .s_axi_araddr   (s_axi_araddr_b),
        .s_axi_arprot   (s_axi_arprot_b),
        .s_axi_arvalid  (s_axi_arvalid_b),
        .s_axi_arready  (s_axi_arready_b),
        .s_axi_rdata    (s_axi_rdata_b),
        .s_axi_rresp    (s_axi_rresp_b),
        .s_axi_rvalid   (s_axi_rvalid_b),
        .s_axi_rready   (s_axi_rready_b)
    );

    initial begin
        btn_a = 4'b0;
        sw_a  = 8'h0;
        btn_b = 4'b0;
        sw_b  = 8'h0;

        s_axi_awvalid_a = 1'b0;
        s_axi_wvalid_a  = 1'b0;
        s_axi_bready_a  = 1'b0;
        s_axi_arvalid_a = 1'b0;
        s_axi_rready_a  = 1'b0;
        s_axi_awaddr_a  = '0;
        s_axi_wdata_a   = '0;
        s_axi_wstrb_a   = 4'h0;
        s_axi_araddr_a  = '0;

        s_axi_awvalid_b = 1'b0;
        s_axi_wvalid_b  = 1'b0;
        s_axi_bready_b  = 1'b0;
        s_axi_arvalid_b = 1'b0;
        s_axi_rready_b  = 1'b0;
        s_axi_awaddr_b  = '0;
        s_axi_wdata_b   = '0;
        s_axi_wstrb_b   = 4'h0;
        s_axi_araddr_b  = '0;

        #50_000;
        $display("tb_system_top: PASS (smoke: Board A + stub B, 50 us idle)");
        $finish;
    end

endmodule
