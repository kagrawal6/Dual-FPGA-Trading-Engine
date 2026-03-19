// ============================================================================
// Testbench: tb_feature_compute
// Tests the feature_compute module: mid price, spread, EMA, deviation
// computation, pipeline timing (3 cycles), and clear functionality.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_feature_compute;

    logic                     clk;
    logic                     rst_n;
    logic                     clear;
    price_t                   bid_price;
    price_t                   ask_price;
    symbol_t                  symbol_id;
    logic                     book_valid;
    logic [ALPHA_W-1:0]       ema_alpha;
    price_t                   mid;
    price_t                   spread;
    price_t                   ema;
    sprice_t                  deviation;
    price_t                   bid_out;
    price_t                   ask_out;
    symbol_t                  symbol_out;
    logic                     feature_valid;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    feature_compute dut (
        .clk          (clk),
        .rst_n        (rst_n),
        .clear        (clear),
        .bid_price    (bid_price),
        .ask_price    (ask_price),
        .symbol_id    (symbol_id),
        .book_valid   (book_valid),
        .ema_alpha    (ema_alpha),
        .mid          (mid),
        .spread       (spread),
        .ema          (ema),
        .deviation    (deviation),
        .bid_out      (bid_out),
        .ask_out      (ask_out),
        .symbol_out   (symbol_out),
        .feature_valid(feature_valid)
    );

    initial begin
        // TODO: Add test stimulus
        $finish;
    end

endmodule
