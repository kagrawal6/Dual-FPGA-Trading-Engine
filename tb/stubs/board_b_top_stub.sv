// ============================================================================
// board_b_top_stub — simulation-only stand-in for board_b_top until Board B
// wiring is complete. Same ports as board_b_top; accepts link from Board A,
// holds TX to Board A idle, ties AXI slave idle-safe.
// ============================================================================

`timescale 1ns / 1ps

module board_b_top_stub
    import hft_pkg::*;
#(
    parameter NUM_SYM            = NUM_SYMBOLS,
    parameter LINK_W             = LINK_DATA_W,
    parameter C_S_AXI_ADDR_WIDTH = 9,
    parameter C_S_AXI_DATA_WIDTH = 32
)(
    input  logic        clk,
    input  logic        rst_n,

    input  logic [3:0]  btn,
    input  logic [7:0]  sw,
    output logic [7:0]  led,
    output logic [2:0]  rgb0,
    output logic [2:0]  rgb1,

    input  logic [LINK_W-1:0] pmod_ja,
    input  logic              pmod_ja_valid,
    output logic              pmod_ja_ready,

    output logic [LINK_W-1:0] pmod_jb,
    output logic              pmod_jb_valid,
    input  logic              pmod_jb_ready,

    input  logic [C_S_AXI_ADDR_WIDTH-1:0] s_axi_awaddr,
    input  logic [2:0]                     s_axi_awprot,
    input  logic                           s_axi_awvalid,
    output logic                           s_axi_awready,
    input  logic [C_S_AXI_DATA_WIDTH-1:0] s_axi_wdata,
    input  logic [3:0]                     s_axi_wstrb,
    input  logic                           s_axi_wvalid,
    output logic                           s_axi_wready,
    output logic [1:0]                     s_axi_bresp,
    output logic                           s_axi_bvalid,
    input  logic                           s_axi_bready,
    input  logic [C_S_AXI_ADDR_WIDTH-1:0] s_axi_araddr,
    input  logic [2:0]                     s_axi_arprot,
    input  logic                           s_axi_arvalid,
    output logic                           s_axi_arready,
    output logic [C_S_AXI_DATA_WIDTH-1:0] s_axi_rdata,
    output logic [1:0]                     s_axi_rresp,
    output logic                           s_axi_rvalid,
    input  logic                           s_axi_rready
);

    assign pmod_ja_ready = 1'b1;
    assign pmod_jb       = '0;
    assign pmod_jb_valid = 1'b0;

    assign led  = '0;
    assign rgb0 = '0;
    assign rgb1 = '0;

    assign s_axi_awready = 1'b1;
    assign s_axi_wready  = 1'b1;
    assign s_axi_bresp   = 2'b00;
    assign s_axi_bvalid  = 1'b0;

    assign s_axi_arready = 1'b1;
    assign s_axi_rdata   = '0;
    assign s_axi_rresp   = 2'b00;
    assign s_axi_rvalid  = 1'b0;

endmodule
