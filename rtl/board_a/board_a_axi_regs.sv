// ============================================================================
// Module: board_a_axi_regs
// AXI-Lite slave register interface for Board A. Provides config registers
// (CTRL, QUOTE_INTERVAL, LFSR_SEED, REGIME, per-symbol init prices) and
// read-only status registers (STATUS, counters). Generates single-cycle
// pulses on CTRL write for start/reset triggers.
// See Appendix D.1 of the design spec for the full register map.
// ============================================================================

`timescale 1ns / 1ps

module board_a_axi_regs
    import hft_pkg::*;
#(
    parameter NUM_SYM            = NUM_SYMBOLS,
    parameter C_S_AXI_ADDR_WIDTH = 8,
    parameter C_S_AXI_DATA_WIDTH = 32
)(
    input  logic        clk,
    input  logic        rst_n,

    // ── AXI-Lite Slave Interface ────────────────────────────────────────────
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
    input  logic                           s_axi_rready,

    // ── Config Outputs (directly drive Board A data plane) ──────────────────
    output logic                           axi_start_pulse,    // 1-cycle pulse on CTRL[0] write
    output logic                           axi_reset_pulse,    // 1-cycle pulse on CTRL[1] write
    output regime_e                        regime_from_ps,      // REGIME register [1:0]
    output logic [31:0]                    quote_interval,      // cycles between quotes
    output logic [31:0]                    lfsr_seed,
    output price_t                         sym_init_mid    [NUM_SYM],
    output price_t                         sym_init_spread [NUM_SYM],

    // ── Status Inputs (from Board A data plane + link) ──────────────────────
    input  logic                           running,
    input  logic                           link_up,
    input  regime_e                        active_regime,
    input  logic [COUNTER_W-1:0]           quotes_sent,
    input  logic [COUNTER_W-1:0]           orders_rcvd,
    input  logic [COUNTER_W-1:0]           fills_sent,
    input  logic [COUNTER_W-1:0]           rejects_sent,
    input  logic [COUNTER_W-1:0]           link_errors,
    input  logic [6:0]                     fifo_fill
);

    // TODO: Implementation
    // Standard AXI-Lite write/read state machine.
    // Register map per Appendix D.1:
    //   0x00 CTRL (W, pulse), 0x04 QUOTE_INTERVAL, 0x08 LFSR_SEED,
    //   0x0C REGIME, 0x10-0x2C SYMx init values,
    //   0x40 STATUS (R), 0x44 QUOTES_SENT, 0x48 ORDERS_RCVD, ...

endmodule
