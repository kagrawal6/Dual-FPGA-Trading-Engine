// ============================================================================
// Module: board_b_top
// Top-level wrapper for Board B (Trader: Strategy + Risk + Telemetry).
// Contains the 5-state FSM (RESET/IDLE/ARMED/TRADING/HALTED), a free-running
// 16-bit cycle counter for timestamps, and instantiates all Board B
// sub-modules with structural wiring. Packaged as a Vivado custom IP.
// ============================================================================

`timescale 1ns / 1ps

module board_b_top
    import hft_pkg::*;
#(
    parameter NUM_SYM            = NUM_SYMBOLS,
    parameter LINK_W             = LINK_DATA_W,
    parameter C_S_AXI_ADDR_WIDTH = 9,
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

    // ── PMOD JA — RX direction (Board A → Board B) ─────────────────────────
    input  logic [LINK_W-1:0] pmod_ja,           // JA[3:0] data
    input  logic              pmod_ja_valid,      // JA[4]
    output logic              pmod_ja_ready,      // JA[5] (to Board A)

    // ── PMOD JB — TX direction (Board B → Board A) ─────────────────────────
    output logic [LINK_W-1:0] pmod_jb,           // JB[3:0] data
    output logic              pmod_jb_valid,      // JB[4]
    input  logic              pmod_jb_ready,      // JB[5] (from Board A)

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

    // ── Free-running cycle counter (for timestamping) ───────────────────────
    timestamp_t cycle_counter;
    always_ff @(posedge clk or negedge rst_n)
        if (!rst_n) cycle_counter <= '0;
        else        cycle_counter <= cycle_counter + 1'b1;

    // ── Internal wires ──────────────────────────────────────────────────────
    // FSM
    b_state_e fsm_state, fsm_next;
    logic order_enable, counter_clr, position_clr;

    // AXI config
    logic        axi_start_pulse, axi_reset_pulse;
    strategy_e   strategy_sel;
    price_t      threshold;
    logic [ALPHA_W-1:0] ema_alpha;
    qty_t        base_qty;
    logic [POSITION_W-1:0] max_position;
    logic [COUNTER_W-1:0]  max_order_rate;
    price_t      max_loss;

    // Ctrl
    logic   ctrl_start_pulse, ctrl_stop_pulse, ctrl_reset_pulse;
    logic   trading_enable;
    strategy_e strategy_sw;
    logic   sw_strategy_override;

    // Combined triggers
    logic start_combined, stop_combined, reset_combined;
    assign start_combined = axi_start_pulse | ctrl_start_pulse;
    assign stop_combined  = ctrl_stop_pulse;
    assign reset_combined = axi_reset_pulse | ctrl_reset_pulse;

    // Active strategy: switch override or PS register
    strategy_e active_strategy;
    assign active_strategy = sw_strategy_override ? strategy_sw : strategy_sel;

    // Link
    logic [FRAME_W-1:0] rx_frame;
    logic               rx_frame_valid;
    logic               link_up;
    logic [31:0]        link_errors;

    // Demux
    logic [FRAME_W-1:0] quote_frame_demux, fill_frame_demux;
    logic               quote_valid_demux,  fill_valid_demux;
    logic [COUNTER_W-1:0] quotes_rcvd, demux_errors;

    // Quote book
    price_t  qb_bid, qb_ask;
    qty_t    qb_bid_size, qb_ask_size;
    symbol_t qb_symbol;
    regime_e qb_regime;
    logic    qb_valid;

    // Feature compute
    price_t  fc_mid, fc_spread, fc_ema;
    sprice_t fc_deviation;
    price_t  fc_bid_out, fc_ask_out;
    symbol_t fc_symbol_out;
    logic    fc_valid;

    // Strategy engine
    logic    se_valid, se_side;
    price_t  se_price;
    qty_t    se_qty;
    symbol_t se_symbol;

    // Risk manager
    logic    rm_valid, rm_side;
    price_t  rm_price;
    qty_t    rm_qty;
    symbol_t rm_symbol;
    logic    risk_halt;
    logic [COUNTER_W-1:0] risk_rejects;

    // Order manager
    logic [FRAME_W-1:0] order_frame;
    logic               order_valid, order_ready;
    logic [COUNTER_W-1:0] orders_sent;

    // Position tracker
    position_t   position [NUM_SYM];
    cash_t       cash;
    sprice_t     total_pnl;
    timestamp_t  ts_echo;
    logic        fill_processed;
    logic [COUNTER_W-1:0] fills_rcvd;

    // Latency histogram
    logic [HIST_BIN_W-1:0] hist_bins [HIST_BINS];
    logic [COUNTER_W-1:0]  lat_min, lat_max, lat_sum, lat_count;

    // TODO: Implementation
    // 1. 5-state FSM (B_RESET → B_IDLE → B_ARMED → B_TRADING ↔ B_HALTED)
    //    Transitions per §4.4.5:
    //      RESET → IDLE: automatic after 1 cycle
    //      IDLE  → ARMED: start_combined & link_up
    //      ARMED → TRADING: start_combined & trading_enable (SW[0])
    //      TRADING → HALTED: risk_halt
    //      TRADING → ARMED: stop_combined | !trading_enable
    //      HALTED → RESET: reset_combined only
    //      Any → RESET: reset_combined
    //    Outputs:
    //      order_enable = (fsm_state == B_TRADING)
    //      counter_clr  = (fsm_state == B_RESET)
    //      position_clr = (fsm_state == B_RESET)
    //
    // 2. Instantiate all modules:
    //    board_b_axi_regs, board_b_ctrl,
    //    link_rx, msg_demux, quote_book, feature_compute,
    //    strategy_engine, risk_manager, order_manager,
    //    position_tracker, latency_histogram, link_tx
    //
    // 3. Wire per §4.6.7 interconnection diagram
    //    Pipeline: link_rx → msg_demux → quote_book → feature_compute →
    //              strategy_engine → risk_manager → order_manager → link_tx

endmodule
