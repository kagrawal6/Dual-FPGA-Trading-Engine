// ============================================================================
// Testbench: tb_market_sim
// Tests the market_sim module: LFSR-driven market simulator that maintains
// per-symbol mid_price and spread, generates QUOTE frames, and exports
// live bid/ask arrays for exchange_lite.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_market_sim;

    logic                     clk;
    logic                     rst_n;
    logic                     enable;
    logic                     lfsr_load;
    logic [31:0]              lfsr_seed;
    regime_e                  active_regime;
    logic [31:0]              quote_interval;
    price_t                   init_mid    [4];
    price_t                   init_spread [4];
    logic [FRAME_W-1:0]       quote_frame;
    logic                     quote_valid;
    logic                     quote_ready;
    price_t                   best_bid    [4];
    price_t                   best_ask    [4];
    logic [COUNTER_W-1:0]     quotes_generated;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    market_sim dut (
        .clk             (clk),
        .rst_n           (rst_n),
        .enable          (enable),
        .lfsr_load       (lfsr_load),
        .lfsr_seed       (lfsr_seed),
        .active_regime   (active_regime),
        .quote_interval  (quote_interval),
        .init_mid        (init_mid),
        .init_spread     (init_spread),
        .quote_frame     (quote_frame),
        .quote_valid     (quote_valid),
        .quote_ready     (quote_ready),
        .best_bid        (best_bid),
        .best_ask        (best_ask),
        .quotes_generated(quotes_generated)
    );

    initial begin
        // TODO: Add test stimulus
        #1000;
        $finish;
    end

endmodule
