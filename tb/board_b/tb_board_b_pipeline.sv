// ============================================================================
// Testbench: tb_board_b_pipeline
// Integration test for the Board B pipeline. Instantiates quote_book →
// feature_compute → strategy_engine → risk_manager → order_manager, with
// position_tracker providing position/cash feedback to risk_manager. Drives
// synthetic QUOTE frames at the input and monitors ORDER frames at the output.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_b_pipeline;

    logic                     clk;
    logic                     rst_n;
    logic                     clear;
    logic                     order_enable;

    // Synthetic QUOTE frame input
    logic [FRAME_W-1:0]       quote_frame;
    logic                     quote_valid;

    // Pipeline interconnect
    price_t                   qb_bid;
    price_t                   qb_ask;
    qty_t                     qb_bid_size;
    qty_t                     qb_ask_size;
    symbol_t                  qb_symbol;
    regime_e                  qb_regime;
    logic                     qb_valid;

    price_t                   fc_mid;
    price_t                   fc_spread;
    price_t                   fc_ema;
    sprice_t                  fc_deviation;
    price_t                   fc_bid_out;
    price_t                   fc_ask_out;
    symbol_t                  fc_symbol_out;
    logic                     fc_valid;

    logic                     se_valid;
    logic                     se_side;
    price_t                   se_price;
    qty_t                     se_qty;
    symbol_t                  se_symbol;

    logic                     rm_valid;
    logic                     rm_side;
    price_t                   rm_price;
    qty_t                     rm_qty;
    symbol_t                  rm_symbol;
    logic                     risk_halt;
    logic [COUNTER_W-1:0]     risk_rejects;

    logic [FRAME_W-1:0]       order_frame;
    logic                     order_valid;
    logic                     order_ready;
    logic [COUNTER_W-1:0]     orders_sent;

    // Position tracker (for risk_manager feedback)
    logic [FRAME_W-1:0]       fill_frame;
    logic                     fill_valid;
    position_t                position [NUM_SYMBOLS];
    cash_t                    cash;
    sprice_t                  total_pnl;
    timestamp_t               ts_echo;
    logic                     fill_processed;
    logic [COUNTER_W-1:0]     fills_rcvd;

    // Config
    logic [ALPHA_W-1:0]       ema_alpha;
    price_t                   threshold;
    qty_t                     base_qty;
    logic [POSITION_W-1:0]    max_position;
    logic [COUNTER_W-1:0]     max_order_rate;
    price_t                   max_loss;

    // Cycle counter for order_manager
    timestamp_t               cycle_counter;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low rst_n, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    // Free-running cycle counter
    always_ff @(posedge clk or negedge rst_n)
        if (!rst_n) cycle_counter <= '0;
        else        cycle_counter <= cycle_counter + 1'b1;

    quote_book u_quote_book (
        .clk         (clk),
        .rst_n       (rst_n),
        .quote_frame (quote_frame),
        .quote_valid (quote_valid),
        .bid_price   (qb_bid),
        .ask_price   (qb_ask),
        .bid_size    (qb_bid_size),
        .ask_size    (qb_ask_size),
        .symbol_id   (qb_symbol),
        .regime      (qb_regime),
        .book_valid  (qb_valid)
    );

    feature_compute u_feature_compute (
        .clk         (clk),
        .rst_n       (rst_n),
        .clear       (clear),
        .bid_price   (qb_bid),
        .ask_price   (qb_ask),
        .symbol_id   (qb_symbol),
        .book_valid  (qb_valid),
        .ema_alpha   (ema_alpha),
        .mid         (fc_mid),
        .spread      (fc_spread),
        .ema         (fc_ema),
        .deviation   (fc_deviation),
        .bid_out     (fc_bid_out),
        .ask_out     (fc_ask_out),
        .symbol_out  (fc_symbol_out),
        .feature_valid (fc_valid)
    );

    strategy_engine u_strategy_engine (
        .clk          (clk),
        .rst_n        (rst_n),
        .deviation    (fc_deviation),
        .bid_price    (fc_bid_out),
        .ask_price    (fc_ask_out),
        .symbol_id    (fc_symbol_out),
        .feature_valid (fc_valid),
        .threshold    (threshold),
        .base_qty     (base_qty),
        .signal_valid (se_valid),
        .signal_side  (se_side),
        .signal_price (se_price),
        .signal_qty   (se_qty),
        .signal_symbol (se_symbol)
    );

    risk_manager u_risk_manager (
        .clk            (clk),
        .rst_n          (rst_n),
        .clear          (clear),
        .order_enable   (order_enable),
        .signal_valid   (se_valid),
        .signal_side    (se_side),
        .signal_price   (se_price),
        .signal_qty     (se_qty),
        .signal_symbol  (se_symbol),
        .position       (position),
        .total_pnl      (total_pnl),
        .max_position   (max_position),
        .max_order_rate (max_order_rate),
        .max_loss       (max_loss),
        .approved_valid (rm_valid),
        .approved_side  (rm_side),
        .approved_price (rm_price),
        .approved_qty   (rm_qty),
        .approved_symbol (rm_symbol),
        .risk_halt      (risk_halt),
        .risk_rejects   (risk_rejects)
    );

    order_manager u_order_manager (
        .clk            (clk),
        .rst_n          (rst_n),
        .clear          (clear),
        .approved_valid (rm_valid),
        .approved_side  (rm_side),
        .approved_price (rm_price),
        .approved_qty   (rm_qty),
        .approved_symbol (rm_symbol),
        .cycle_counter  (cycle_counter),
        .order_frame    (order_frame),
        .order_valid    (order_valid),
        .order_ready    (order_ready),
        .orders_sent    (orders_sent)
    );

    position_tracker u_position_tracker (
        .clk            (clk),
        .rst_n          (rst_n),
        .clear          (clear),
        .fill_frame     (fill_frame),
        .fill_valid     (fill_valid),
        .position       (position),
        .cash           (cash),
        .total_pnl      (total_pnl),
        .ts_echo        (ts_echo),
        .fill_processed (fill_processed),
        .fills_rcvd     (fills_rcvd)
    );

    initial begin
        // TODO: Add test stimulus — drive synthetic QUOTE frames, monitor ORDER frames
        #1000;
        $finish;
    end

endmodule
