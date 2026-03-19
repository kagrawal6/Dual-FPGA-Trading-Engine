// ============================================================================
// Testbench: tb_exchange_lite
// Tests the exchange_lite module: simplified exchange matching engine that
// receives ORDER frames, compares limit_price against live bid/ask from
// market_sim, and generates FILL frames (FILLED or REJECTED).
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_exchange_lite;

    logic                     clk;
    logic                     rst_n;
    logic                     enable;
    price_t                   best_bid    [4];
    price_t                   best_ask    [4];
    logic [FRAME_W-1:0]       order_frame;
    logic                     order_valid;
    logic [FRAME_W-1:0]       fill_frame;
    logic                     fill_valid;
    logic                     fill_ready;
    logic [COUNTER_W-1:0]     orders_rcvd;
    logic [COUNTER_W-1:0]     fills_sent;
    logic [COUNTER_W-1:0]     rejects_sent;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    exchange_lite dut (
        .clk         (clk),
        .rst_n       (rst_n),
        .enable      (enable),
        .best_bid    (best_bid),
        .best_ask    (best_ask),
        .order_frame (order_frame),
        .order_valid (order_valid),
        .fill_frame  (fill_frame),
        .fill_valid  (fill_valid),
        .fill_ready  (fill_ready),
        .orders_rcvd (orders_rcvd),
        .fills_sent  (fills_sent),
        .rejects_sent(rejects_sent)
    );

    initial begin
        // TODO: Add test stimulus
        #1000;
        $finish;
    end

endmodule
