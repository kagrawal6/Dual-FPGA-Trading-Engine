// ============================================================================
// Module: board_b_axi_regs
// AXI-Lite slave register interface for Board B. Provides config registers
// (CTRL, STRATEGY_SEL, THRESHOLD, EMA_ALPHA, BASE_QTY, MAX_POSITION,
// MAX_ORDER_RATE, MAX_LOSS) and extensive read-only status registers
// (FSM state, counters, per-symbol positions, cash, histogram, latency stats).
// See Appendix D.2 of the design spec for the full register map.
// ============================================================================

`timescale 1ns / 1ps

module board_b_axi_regs
    import hft_pkg::*;
#(
    parameter NUM_SYM            = NUM_SYMBOLS,
    parameter C_S_AXI_ADDR_WIDTH = 9,
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

    // ── Config Outputs ──────────────────────────────────────────────────────
    output logic                  axi_start_pulse,   // 1-cycle pulse
    output logic                  axi_reset_pulse,   // 1-cycle pulse
    output strategy_e             strategy_sel,
    output price_t                threshold,          // Q16.16
    output logic [ALPHA_W-1:0]    ema_alpha,          // Q0.16
    output qty_t                  base_qty,
    output logic [POSITION_W-1:0] max_position,
    output logic [COUNTER_W-1:0]  max_order_rate,
    output price_t                max_loss,           // Q16.16

    // ── Status Inputs ───────────────────────────────────────────────────────
    input  b_state_e              fsm_state,
    input  logic                  link_up,
    input  logic                  risk_halt,
    input  strategy_e             active_strategy,
    input  logic [COUNTER_W-1:0]  quotes_rcvd,
    input  logic [COUNTER_W-1:0]  orders_sent,
    input  logic [COUNTER_W-1:0]  fills_rcvd,
    input  logic [COUNTER_W-1:0]  risk_rejects,
    input  logic [COUNTER_W-1:0]  link_errors,
    input  position_t             position     [NUM_SYM],
    input  cash_t                 cash,
    input  logic [HIST_BIN_W-1:0] hist_bins    [HIST_BINS],
    input  logic [COUNTER_W-1:0]  lat_min,
    input  logic [COUNTER_W-1:0]  lat_max,
    input  logic [COUNTER_W-1:0]  lat_sum,
    input  logic [COUNTER_W-1:0]  lat_count
);

    // TODO: Implementation
    // Standard AXI-Lite write/read state machine.
    // Register map per Appendix D.2:
    //   Config: 0x00 CTRL, 0x04 STRATEGY_SEL, 0x08 THRESHOLD, 0x0C EMA_ALPHA,
    //           0x10 BASE_QTY, 0x14 MAX_POSITION, 0x18 MAX_ORDER_RATE, 0x1C MAX_LOSS
    //   Status: 0x40 STATUS, 0x44 QUOTES_RCVD, 0x48 ORDERS_SENT, 0x4C FILLS_RCVD,
    //           0x50 RISK_REJECTS, 0x54 LINK_ERRORS, 0x58-0x64 POS_SYMx,
    //           0x68 CASH_LO, 0x6C CASH_HI, 0x80-0xBC HIST_BINx,
    //           0xC0 LAT_MIN, 0xC4 LAT_MAX, 0xC8 LAT_SUM, 0xCC LAT_COUNT

endmodule
