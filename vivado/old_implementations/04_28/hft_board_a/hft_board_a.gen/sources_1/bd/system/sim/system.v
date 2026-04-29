//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2025.2 (win64) Build 6299465 Fri Nov 14 19:35:11 GMT 2025
//Date        : Thu Apr 16 07:20:21 2026
//Host        : Kushal2009 running 64-bit major release  (build 9200)
//Command     : generate_target system.bd
//Design      : system
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "system,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=system,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=4,numReposBlks=4,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=1,numPkgbdBlks=0,bdsource=USER,synth_mode=Hierarchical}" *) (* HW_HANDOFF = "system.hwdef" *) 
module system
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
  output [3:0]pmod_ja;
  input pmod_ja_ready;
  output pmod_ja_valid;
  input [3:0]pmod_jb;
  output pmod_jb_ready;
  input pmod_jb_valid;
  output [2:0]rgb0;
  output [2:0]rgb1;
  input [7:0]sw;

  wire [7:0]axi_sc_M00_AXI_ARADDR;
  wire [2:0]axi_sc_M00_AXI_ARPROT;
  wire axi_sc_M00_AXI_ARREADY;
  wire axi_sc_M00_AXI_ARVALID;
  wire [7:0]axi_sc_M00_AXI_AWADDR;
  wire [2:0]axi_sc_M00_AXI_AWPROT;
  wire axi_sc_M00_AXI_AWREADY;
  wire axi_sc_M00_AXI_AWVALID;
  wire axi_sc_M00_AXI_BREADY;
  wire [1:0]axi_sc_M00_AXI_BRESP;
  wire axi_sc_M00_AXI_BVALID;
  wire [31:0]axi_sc_M00_AXI_RDATA;
  wire axi_sc_M00_AXI_RREADY;
  wire [1:0]axi_sc_M00_AXI_RRESP;
  wire axi_sc_M00_AXI_RVALID;
  wire [31:0]axi_sc_M00_AXI_WDATA;
  wire axi_sc_M00_AXI_WREADY;
  wire [3:0]axi_sc_M00_AXI_WSTRB;
  wire axi_sc_M00_AXI_WVALID;
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
  wire [0:0]rst_sys_peripheral_aresetn;
  wire [7:0]sw;
  wire [39:0]zynq_ps_M_AXI_HPM0_FPD_ARADDR;
  wire [1:0]zynq_ps_M_AXI_HPM0_FPD_ARBURST;
  wire [3:0]zynq_ps_M_AXI_HPM0_FPD_ARCACHE;
  wire [15:0]zynq_ps_M_AXI_HPM0_FPD_ARID;
  wire [7:0]zynq_ps_M_AXI_HPM0_FPD_ARLEN;
  wire zynq_ps_M_AXI_HPM0_FPD_ARLOCK;
  wire [2:0]zynq_ps_M_AXI_HPM0_FPD_ARPROT;
  wire [3:0]zynq_ps_M_AXI_HPM0_FPD_ARQOS;
  wire zynq_ps_M_AXI_HPM0_FPD_ARREADY;
  wire [2:0]zynq_ps_M_AXI_HPM0_FPD_ARSIZE;
  wire [15:0]zynq_ps_M_AXI_HPM0_FPD_ARUSER;
  wire zynq_ps_M_AXI_HPM0_FPD_ARVALID;
  wire [39:0]zynq_ps_M_AXI_HPM0_FPD_AWADDR;
  wire [1:0]zynq_ps_M_AXI_HPM0_FPD_AWBURST;
  wire [3:0]zynq_ps_M_AXI_HPM0_FPD_AWCACHE;
  wire [15:0]zynq_ps_M_AXI_HPM0_FPD_AWID;
  wire [7:0]zynq_ps_M_AXI_HPM0_FPD_AWLEN;
  wire zynq_ps_M_AXI_HPM0_FPD_AWLOCK;
  wire [2:0]zynq_ps_M_AXI_HPM0_FPD_AWPROT;
  wire [3:0]zynq_ps_M_AXI_HPM0_FPD_AWQOS;
  wire zynq_ps_M_AXI_HPM0_FPD_AWREADY;
  wire [2:0]zynq_ps_M_AXI_HPM0_FPD_AWSIZE;
  wire [15:0]zynq_ps_M_AXI_HPM0_FPD_AWUSER;
  wire zynq_ps_M_AXI_HPM0_FPD_AWVALID;
  wire [15:0]zynq_ps_M_AXI_HPM0_FPD_BID;
  wire zynq_ps_M_AXI_HPM0_FPD_BREADY;
  wire [1:0]zynq_ps_M_AXI_HPM0_FPD_BRESP;
  wire zynq_ps_M_AXI_HPM0_FPD_BVALID;
  wire [31:0]zynq_ps_M_AXI_HPM0_FPD_RDATA;
  wire [15:0]zynq_ps_M_AXI_HPM0_FPD_RID;
  wire zynq_ps_M_AXI_HPM0_FPD_RLAST;
  wire zynq_ps_M_AXI_HPM0_FPD_RREADY;
  wire [1:0]zynq_ps_M_AXI_HPM0_FPD_RRESP;
  wire zynq_ps_M_AXI_HPM0_FPD_RVALID;
  wire [31:0]zynq_ps_M_AXI_HPM0_FPD_WDATA;
  wire zynq_ps_M_AXI_HPM0_FPD_WLAST;
  wire zynq_ps_M_AXI_HPM0_FPD_WREADY;
  wire [3:0]zynq_ps_M_AXI_HPM0_FPD_WSTRB;
  wire zynq_ps_M_AXI_HPM0_FPD_WVALID;
  wire zynq_ps_pl_clk0;
  wire zynq_ps_pl_resetn0;

  system_axi_sc_0 axi_sc
       (.M00_AXI_araddr(axi_sc_M00_AXI_ARADDR),
        .M00_AXI_arprot(axi_sc_M00_AXI_ARPROT),
        .M00_AXI_arready(axi_sc_M00_AXI_ARREADY),
        .M00_AXI_arvalid(axi_sc_M00_AXI_ARVALID),
        .M00_AXI_awaddr(axi_sc_M00_AXI_AWADDR),
        .M00_AXI_awprot(axi_sc_M00_AXI_AWPROT),
        .M00_AXI_awready(axi_sc_M00_AXI_AWREADY),
        .M00_AXI_awvalid(axi_sc_M00_AXI_AWVALID),
        .M00_AXI_bready(axi_sc_M00_AXI_BREADY),
        .M00_AXI_bresp(axi_sc_M00_AXI_BRESP),
        .M00_AXI_bvalid(axi_sc_M00_AXI_BVALID),
        .M00_AXI_rdata(axi_sc_M00_AXI_RDATA),
        .M00_AXI_rready(axi_sc_M00_AXI_RREADY),
        .M00_AXI_rresp(axi_sc_M00_AXI_RRESP),
        .M00_AXI_rvalid(axi_sc_M00_AXI_RVALID),
        .M00_AXI_wdata(axi_sc_M00_AXI_WDATA),
        .M00_AXI_wready(axi_sc_M00_AXI_WREADY),
        .M00_AXI_wstrb(axi_sc_M00_AXI_WSTRB),
        .M00_AXI_wvalid(axi_sc_M00_AXI_WVALID),
        .S00_AXI_araddr(zynq_ps_M_AXI_HPM0_FPD_ARADDR),
        .S00_AXI_arburst(zynq_ps_M_AXI_HPM0_FPD_ARBURST),
        .S00_AXI_arcache(zynq_ps_M_AXI_HPM0_FPD_ARCACHE),
        .S00_AXI_arid(zynq_ps_M_AXI_HPM0_FPD_ARID),
        .S00_AXI_arlen(zynq_ps_M_AXI_HPM0_FPD_ARLEN),
        .S00_AXI_arlock(zynq_ps_M_AXI_HPM0_FPD_ARLOCK),
        .S00_AXI_arprot(zynq_ps_M_AXI_HPM0_FPD_ARPROT),
        .S00_AXI_arqos(zynq_ps_M_AXI_HPM0_FPD_ARQOS),
        .S00_AXI_arready(zynq_ps_M_AXI_HPM0_FPD_ARREADY),
        .S00_AXI_arsize(zynq_ps_M_AXI_HPM0_FPD_ARSIZE),
        .S00_AXI_aruser(zynq_ps_M_AXI_HPM0_FPD_ARUSER),
        .S00_AXI_arvalid(zynq_ps_M_AXI_HPM0_FPD_ARVALID),
        .S00_AXI_awaddr(zynq_ps_M_AXI_HPM0_FPD_AWADDR),
        .S00_AXI_awburst(zynq_ps_M_AXI_HPM0_FPD_AWBURST),
        .S00_AXI_awcache(zynq_ps_M_AXI_HPM0_FPD_AWCACHE),
        .S00_AXI_awid(zynq_ps_M_AXI_HPM0_FPD_AWID),
        .S00_AXI_awlen(zynq_ps_M_AXI_HPM0_FPD_AWLEN),
        .S00_AXI_awlock(zynq_ps_M_AXI_HPM0_FPD_AWLOCK),
        .S00_AXI_awprot(zynq_ps_M_AXI_HPM0_FPD_AWPROT),
        .S00_AXI_awqos(zynq_ps_M_AXI_HPM0_FPD_AWQOS),
        .S00_AXI_awready(zynq_ps_M_AXI_HPM0_FPD_AWREADY),
        .S00_AXI_awsize(zynq_ps_M_AXI_HPM0_FPD_AWSIZE),
        .S00_AXI_awuser(zynq_ps_M_AXI_HPM0_FPD_AWUSER),
        .S00_AXI_awvalid(zynq_ps_M_AXI_HPM0_FPD_AWVALID),
        .S00_AXI_bid(zynq_ps_M_AXI_HPM0_FPD_BID),
        .S00_AXI_bready(zynq_ps_M_AXI_HPM0_FPD_BREADY),
        .S00_AXI_bresp(zynq_ps_M_AXI_HPM0_FPD_BRESP),
        .S00_AXI_bvalid(zynq_ps_M_AXI_HPM0_FPD_BVALID),
        .S00_AXI_rdata(zynq_ps_M_AXI_HPM0_FPD_RDATA),
        .S00_AXI_rid(zynq_ps_M_AXI_HPM0_FPD_RID),
        .S00_AXI_rlast(zynq_ps_M_AXI_HPM0_FPD_RLAST),
        .S00_AXI_rready(zynq_ps_M_AXI_HPM0_FPD_RREADY),
        .S00_AXI_rresp(zynq_ps_M_AXI_HPM0_FPD_RRESP),
        .S00_AXI_rvalid(zynq_ps_M_AXI_HPM0_FPD_RVALID),
        .S00_AXI_wdata(zynq_ps_M_AXI_HPM0_FPD_WDATA),
        .S00_AXI_wlast(zynq_ps_M_AXI_HPM0_FPD_WLAST),
        .S00_AXI_wready(zynq_ps_M_AXI_HPM0_FPD_WREADY),
        .S00_AXI_wstrb(zynq_ps_M_AXI_HPM0_FPD_WSTRB),
        .S00_AXI_wvalid(zynq_ps_M_AXI_HPM0_FPD_WVALID),
        .aclk(zynq_ps_pl_clk0),
        .aresetn(rst_sys_peripheral_aresetn));
  system_hft_core_0 hft_core
       (.btn(btn),
        .clk(zynq_ps_pl_clk0),
        .led(led),
        .pmod_ja(pmod_ja),
        .pmod_ja_ready(pmod_ja_ready),
        .pmod_ja_valid(pmod_ja_valid),
        .pmod_jb(pmod_jb),
        .pmod_jb_ready(pmod_jb_ready),
        .pmod_jb_valid(pmod_jb_valid),
        .rgb0(rgb0),
        .rgb1(rgb1),
        .rst_n(rst_sys_peripheral_aresetn),
        .s_axi_araddr(axi_sc_M00_AXI_ARADDR),
        .s_axi_arprot(axi_sc_M00_AXI_ARPROT),
        .s_axi_arready(axi_sc_M00_AXI_ARREADY),
        .s_axi_arvalid(axi_sc_M00_AXI_ARVALID),
        .s_axi_awaddr(axi_sc_M00_AXI_AWADDR),
        .s_axi_awprot(axi_sc_M00_AXI_AWPROT),
        .s_axi_awready(axi_sc_M00_AXI_AWREADY),
        .s_axi_awvalid(axi_sc_M00_AXI_AWVALID),
        .s_axi_bready(axi_sc_M00_AXI_BREADY),
        .s_axi_bresp(axi_sc_M00_AXI_BRESP),
        .s_axi_bvalid(axi_sc_M00_AXI_BVALID),
        .s_axi_rdata(axi_sc_M00_AXI_RDATA),
        .s_axi_rready(axi_sc_M00_AXI_RREADY),
        .s_axi_rresp(axi_sc_M00_AXI_RRESP),
        .s_axi_rvalid(axi_sc_M00_AXI_RVALID),
        .s_axi_wdata(axi_sc_M00_AXI_WDATA),
        .s_axi_wready(axi_sc_M00_AXI_WREADY),
        .s_axi_wstrb(axi_sc_M00_AXI_WSTRB),
        .s_axi_wvalid(axi_sc_M00_AXI_WVALID),
        .sw(sw));
  system_rst_sys_0 rst_sys
       (.aux_reset_in(1'b1),
        .dcm_locked(1'b1),
        .ext_reset_in(zynq_ps_pl_resetn0),
        .mb_debug_sys_rst(1'b0),
        .peripheral_aresetn(rst_sys_peripheral_aresetn),
        .slowest_sync_clk(zynq_ps_pl_clk0));
  system_zynq_ps_0 zynq_ps
       (.maxigp0_araddr(zynq_ps_M_AXI_HPM0_FPD_ARADDR),
        .maxigp0_arburst(zynq_ps_M_AXI_HPM0_FPD_ARBURST),
        .maxigp0_arcache(zynq_ps_M_AXI_HPM0_FPD_ARCACHE),
        .maxigp0_arid(zynq_ps_M_AXI_HPM0_FPD_ARID),
        .maxigp0_arlen(zynq_ps_M_AXI_HPM0_FPD_ARLEN),
        .maxigp0_arlock(zynq_ps_M_AXI_HPM0_FPD_ARLOCK),
        .maxigp0_arprot(zynq_ps_M_AXI_HPM0_FPD_ARPROT),
        .maxigp0_arqos(zynq_ps_M_AXI_HPM0_FPD_ARQOS),
        .maxigp0_arready(zynq_ps_M_AXI_HPM0_FPD_ARREADY),
        .maxigp0_arsize(zynq_ps_M_AXI_HPM0_FPD_ARSIZE),
        .maxigp0_aruser(zynq_ps_M_AXI_HPM0_FPD_ARUSER),
        .maxigp0_arvalid(zynq_ps_M_AXI_HPM0_FPD_ARVALID),
        .maxigp0_awaddr(zynq_ps_M_AXI_HPM0_FPD_AWADDR),
        .maxigp0_awburst(zynq_ps_M_AXI_HPM0_FPD_AWBURST),
        .maxigp0_awcache(zynq_ps_M_AXI_HPM0_FPD_AWCACHE),
        .maxigp0_awid(zynq_ps_M_AXI_HPM0_FPD_AWID),
        .maxigp0_awlen(zynq_ps_M_AXI_HPM0_FPD_AWLEN),
        .maxigp0_awlock(zynq_ps_M_AXI_HPM0_FPD_AWLOCK),
        .maxigp0_awprot(zynq_ps_M_AXI_HPM0_FPD_AWPROT),
        .maxigp0_awqos(zynq_ps_M_AXI_HPM0_FPD_AWQOS),
        .maxigp0_awready(zynq_ps_M_AXI_HPM0_FPD_AWREADY),
        .maxigp0_awsize(zynq_ps_M_AXI_HPM0_FPD_AWSIZE),
        .maxigp0_awuser(zynq_ps_M_AXI_HPM0_FPD_AWUSER),
        .maxigp0_awvalid(zynq_ps_M_AXI_HPM0_FPD_AWVALID),
        .maxigp0_bid(zynq_ps_M_AXI_HPM0_FPD_BID),
        .maxigp0_bready(zynq_ps_M_AXI_HPM0_FPD_BREADY),
        .maxigp0_bresp(zynq_ps_M_AXI_HPM0_FPD_BRESP),
        .maxigp0_bvalid(zynq_ps_M_AXI_HPM0_FPD_BVALID),
        .maxigp0_rdata(zynq_ps_M_AXI_HPM0_FPD_RDATA),
        .maxigp0_rid(zynq_ps_M_AXI_HPM0_FPD_RID),
        .maxigp0_rlast(zynq_ps_M_AXI_HPM0_FPD_RLAST),
        .maxigp0_rready(zynq_ps_M_AXI_HPM0_FPD_RREADY),
        .maxigp0_rresp(zynq_ps_M_AXI_HPM0_FPD_RRESP),
        .maxigp0_rvalid(zynq_ps_M_AXI_HPM0_FPD_RVALID),
        .maxigp0_wdata(zynq_ps_M_AXI_HPM0_FPD_WDATA),
        .maxigp0_wlast(zynq_ps_M_AXI_HPM0_FPD_WLAST),
        .maxigp0_wready(zynq_ps_M_AXI_HPM0_FPD_WREADY),
        .maxigp0_wstrb(zynq_ps_M_AXI_HPM0_FPD_WSTRB),
        .maxigp0_wvalid(zynq_ps_M_AXI_HPM0_FPD_WVALID),
        .maxihpm0_fpd_aclk(zynq_ps_pl_clk0),
        .pl_clk0(zynq_ps_pl_clk0),
        .pl_resetn0(zynq_ps_pl_resetn0));
endmodule
