// ============================================================================
// Module: board_a_top
// Top-level wrapper for Board A (Exchange + Market Simulator).
// Contains the 4-state FSM (RESET/IDLE/RUNNING/STOPPED), instantiates all
// Board A sub-modules, and performs structural wiring. This is the module
// packaged as a Vivado custom IP with an AXI-Lite slave interface.
// ============================================================================

`timescale 1ns / 1ps

module board_a_top
    import hft_pkg::*;
#(
    parameter NUM_SYM            = NUM_SYMBOLS,
    parameter LINK_W             = LINK_DATA_W,
    parameter C_S_AXI_ADDR_WIDTH = 8,
    parameter C_S_AXI_DATA_WIDTH = 32
)(
    input  logic        clk,
    input  logic        rst_n,

    // ── Physical I/O ────────────────────────────────────────────────────────
    input  logic [3:0]  btn,
    input  logic [7:0]  sw,
    output logic [7:0]  led,
    output logic [2:0]  rgb0,
    output logic [2:0]  rgb1,

    // ── PMOD JA — TX direction (Board A → Board B) ─────────────────────────
    output logic [LINK_W-1:0] pmod_ja,           // JA[3:0] data
    output logic              pmod_ja_valid,      // JA[4]
    input  logic              pmod_ja_ready,      // JA[5] (from Board B)

    // ── PMOD JB — RX direction (Board B → Board A) ─────────────────────────
    input  logic [LINK_W-1:0] pmod_jb,           // JB[3:0] data
    input  logic              pmod_jb_valid,      // JB[4]
    output logic              pmod_jb_ready,      // JB[5] (to Board B)

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
    input  logic                           s_axi_rready
);

    // ── Internal wires ──────────────────────────────────────────────────────
    // FSM
    a_state_e fsm_state, fsm_next;
    logic running, lfsr_load, counter_clr, fifo_flush;

    // AXI config outputs
    logic        axi_start_pulse, axi_reset_pulse;
    regime_e     regime_from_ps;
    logic [31:0] quote_interval, lfsr_seed;
    price_t      sym_init_mid    [NUM_SYM];
    price_t      sym_init_spread [NUM_SYM];

    // Ctrl outputs
    logic   ctrl_start_pulse, ctrl_stop_pulse, ctrl_reset_pulse;
    regime_e regime_sw;
    logic   sw_override;

    // Combined triggers
    logic start_combined, stop_combined, reset_combined;
    assign start_combined = axi_start_pulse | ctrl_start_pulse;
    assign stop_combined  = ctrl_stop_pulse;
    assign reset_combined = axi_reset_pulse | ctrl_reset_pulse;

    // Active regime: switch override or PS register
    regime_e active_regime;
    assign active_regime = sw_override ? regime_sw : regime_from_ps;

    // Data plane wires
    logic [FRAME_W-1:0] quote_frame, fill_frame, order_frame_rx;
    logic               quote_valid_ms, quote_ready_fifo;
    logic [FRAME_W-1:0] quote_frame_fifo;
    logic               quote_valid_fifo, quote_ready_arb;
    logic               fill_valid, fill_ready;
    logic               order_valid_rx;
    logic [FRAME_W-1:0] tx_frame;
    logic               tx_valid, tx_ready;

    // Status
    logic [COUNTER_W-1:0] quotes_generated, orders_rcvd, fills_sent, rejects_sent;
    logic [COUNTER_W-1:0] link_errors;
    logic                 link_up;
    logic [$clog2(64):0]  fifo_fill_level;
    price_t               best_bid [NUM_SYM];
    price_t               best_ask [NUM_SYM];

    // TODO: Implementation
    // 1. 4-state FSM (A_RESET → A_IDLE → A_RUNNING ↔ A_STOPPED)
    //    - lfsr_load pulsed on IDLE→RUNNING only (not STOPPED→RUNNING)
    //    - running = (fsm_state == A_RUNNING)
    // 2. Instantiate: board_a_axi_regs, board_a_ctrl, market_sim,
    //    sync_fifo (quote_fifo), exchange_lite, tx_arbiter,
    //    link_tx, link_rx
    // 3. Wire all signals per §4.6.7 interconnection diagram

endmodule
