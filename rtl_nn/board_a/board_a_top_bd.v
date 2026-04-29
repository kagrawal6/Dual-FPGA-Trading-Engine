// Verilog wrapper for board_a_top — required because Vivado block design
// does not support SystemVerilog modules as module references.
// All ports mirror board_a_top.sv with hardcoded parameter defaults.

module board_a_top_bd (
    input  wire        clk,
    input  wire        rst_n,

    input  wire [3:0]  btn,
    input  wire [7:0]  sw,
    output wire [7:0]  led,
    output wire [2:0]  rgb0,
    output wire [2:0]  rgb1,

    output wire [3:0]  pmod_ja,
    output wire        pmod_ja_valid,
    input  wire        pmod_ja_ready,

    input  wire [3:0]  pmod_jb,
    input  wire        pmod_jb_valid,
    output wire        pmod_jb_ready,

    input  wire [7:0]  s_axi_awaddr,
    input  wire [2:0]  s_axi_awprot,
    input  wire        s_axi_awvalid,
    output wire        s_axi_awready,
    input  wire [31:0] s_axi_wdata,
    input  wire [3:0]  s_axi_wstrb,
    input  wire        s_axi_wvalid,
    output wire        s_axi_wready,
    output wire [1:0]  s_axi_bresp,
    output wire        s_axi_bvalid,
    input  wire        s_axi_bready,
    input  wire [7:0]  s_axi_araddr,
    input  wire [2:0]  s_axi_arprot,
    input  wire        s_axi_arvalid,
    output wire        s_axi_arready,
    output wire [31:0] s_axi_rdata,
    output wire [1:0]  s_axi_rresp,
    output wire        s_axi_rvalid,
    input  wire        s_axi_rready
);

    board_a_top #(
        .NUM_SYM            (16),
        .LINK_W             (4),
        .C_S_AXI_ADDR_WIDTH (8),
        .C_S_AXI_DATA_WIDTH (32)
    ) u_core (
        .clk            (clk),
        .rst_n          (rst_n),
        .btn            (btn),
        .sw             (sw),
        .led            (led),
        .rgb0           (rgb0),
        .rgb1           (rgb1),
        .pmod_ja        (pmod_ja),
        .pmod_ja_valid  (pmod_ja_valid),
        .pmod_ja_ready  (pmod_ja_ready),
        .pmod_jb        (pmod_jb),
        .pmod_jb_valid  (pmod_jb_valid),
        .pmod_jb_ready  (pmod_jb_ready),
        .s_axi_awaddr   (s_axi_awaddr),
        .s_axi_awprot   (s_axi_awprot),
        .s_axi_awvalid  (s_axi_awvalid),
        .s_axi_awready  (s_axi_awready),
        .s_axi_wdata    (s_axi_wdata),
        .s_axi_wstrb    (s_axi_wstrb),
        .s_axi_wvalid   (s_axi_wvalid),
        .s_axi_wready   (s_axi_wready),
        .s_axi_bresp    (s_axi_bresp),
        .s_axi_bvalid   (s_axi_bvalid),
        .s_axi_bready   (s_axi_bready),
        .s_axi_araddr   (s_axi_araddr),
        .s_axi_arprot   (s_axi_arprot),
        .s_axi_arvalid  (s_axi_arvalid),
        .s_axi_arready  (s_axi_arready),
        .s_axi_rdata    (s_axi_rdata),
        .s_axi_rresp    (s_axi_rresp),
        .s_axi_rvalid   (s_axi_rvalid),
        .s_axi_rready   (s_axi_rready)
    );

endmodule
