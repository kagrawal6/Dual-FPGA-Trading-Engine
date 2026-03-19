// ============================================================================
// Testbench: tb_strategy_engine
// Tests the strategy_engine module: mean-reversion logic (deviation vs
// threshold), BUY/SELL signal generation, and configuration (threshold,
// base_qty).
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_strategy_engine;

    logic                     clk;
    logic                     rst_n;
    sprice_t                  deviation;
    price_t                   bid_price;
    price_t                   ask_price;
    symbol_t                  symbol_id;
    logic                     feature_valid;
    price_t                   threshold;
    qty_t                     base_qty;
    logic                     signal_valid;
    logic                     signal_side;
    price_t                   signal_price;
    qty_t                     signal_qty;
    symbol_t                  signal_symbol;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    strategy_engine dut (
        .clk           (clk),
        .rst_n         (rst_n),
        .deviation     (deviation),
        .bid_price     (bid_price),
        .ask_price     (ask_price),
        .symbol_id     (symbol_id),
        .feature_valid (feature_valid),
        .threshold     (threshold),
        .base_qty      (base_qty),
        .signal_valid  (signal_valid),
        .signal_side   (signal_side),
        .signal_price  (signal_price),
        .signal_qty    (signal_qty),
        .signal_symbol (signal_symbol)
    );

    initial begin
        // TODO: Add test stimulus
        $finish;
    end

endmodule
