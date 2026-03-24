// ============================================================================
// Testbench: tb_board_a_top
// AXI start + short quote interval; Board B side idle; expect quotes_sent > 0.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_a_top;

    localparam logic [7:0] ADDR_CTRL          = 8'h00;
    localparam logic [7:0] ADDR_QUOTE_INT     = 8'h04;
    localparam logic [7:0] ADDR_QUOTES_SENT   = 8'hF8;

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

    int err_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

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

    task automatic check(input string msg, input logic cond);
        if (!cond) begin
            $error("FAIL: %s", msg);
            err_count++;
        end
    endtask

    task automatic axi_write(input logic [7:0] addr, input logic [31:0] data);
        @(posedge clk);
        s_axi_awaddr  = addr;
        s_axi_awvalid = 1'b1;
        s_axi_wdata   = data;
        s_axi_wstrb   = 4'hF;
        s_axi_wvalid  = 1'b1;
        wait (s_axi_awready && s_axi_wready);
        @(posedge clk);
        s_axi_awvalid = 1'b0;
        s_axi_wvalid  = 1'b0;
        s_axi_bready  = 1'b1;
        wait (s_axi_bvalid);
        @(posedge clk);
        s_axi_bready  = 1'b0;
    endtask

    task automatic axi_read(input logic [7:0] addr, output logic [31:0] data);
        @(posedge clk);
        s_axi_araddr  = addr;
        s_axi_arvalid = 1'b1;
        wait (s_axi_arready);
        @(posedge clk);
        s_axi_arvalid = 1'b0;
        s_axi_rready  = 1'b1;
        wait (s_axi_rvalid);
        data = s_axi_rdata;
        @(posedge clk);
        s_axi_rready  = 1'b0;
    endtask

    initial begin
        logic [31:0] q;
        btn              = 4'b0;
        sw               = 8'h0;
        pmod_ja_ready    = 1'b1;
        pmod_jb          = '0;
        pmod_jb_valid    = 1'b0;
        s_axi_awaddr     = '0;
        s_axi_awprot     = 3'b0;
        s_axi_awvalid    = 1'b0;
        s_axi_wdata      = '0;
        s_axi_wstrb      = 4'h0;
        s_axi_wvalid     = 1'b0;
        s_axi_bready     = 1'b0;
        s_axi_araddr     = '0;
        s_axi_arprot     = 3'b0;
        s_axi_arvalid    = 1'b0;
        s_axi_rready     = 1'b0;

        @(posedge clk);
        wait (rst_n === 1'b1);
        repeat (20) @(posedge clk);

        axi_write(ADDR_QUOTE_INT, 32'd0);
        axi_write(ADDR_CTRL, 32'd1);

        repeat (80_000) @(posedge clk);

        axi_read(ADDR_QUOTES_SENT, q);
        check("quotes_sent non-zero", q > 32'd0);
        check("running LED", led[2] == 1'b1);

        if (err_count == 0)
            $display("tb_board_a_top: PASS (quotes_sent=%0d)", q);
        else
            $display("tb_board_a_top: FAIL (%0d errors)", err_count);
        $finish;
    end

endmodule
