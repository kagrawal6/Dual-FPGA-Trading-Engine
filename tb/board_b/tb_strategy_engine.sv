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

    initial clk = 0;
    always #5 clk = ~clk;

    int err_count = 0;

    task automatic check(input string name, input logic [31:0] got, input logic [31:0] exp);
        if (got !== exp) begin
            $display("FAIL [%0t] %s: got 0x%08h, expected 0x%08h", $time, name, got, exp);
            err_count++;
        end
    endtask

    strategy_engine dut (.*);

    initial begin
        rst_n = 0;
        deviation = 0; bid_price = 0; ask_price = 0; symbol_id = 0;
        feature_valid = 0;
        threshold = 32'h0001_0000;  // $1.00
        base_qty = 16'd100;
        #100; rst_n = 1;
        @(posedge clk); #1;

        // ── Test 1: Deviation > +threshold -> SELL at bid ──
        deviation     = 32'sh0001_8000;  // +$1.50 (above $1.00 threshold)
        bid_price     = 32'h0096_0000;   // $150.00
        ask_price     = 32'h0096_8000;   // $150.50
        symbol_id     = 8'd0;
        feature_valid = 1;
        @(posedge clk); #1;
        feature_valid = 0;
        @(posedge clk); #1;
        check("T1 signal_valid", signal_valid, 1);
        check("T1 signal_side",  signal_side,  1);  // SELL
        check("T1 signal_price", signal_price, 32'h0096_0000);  // bid
        check("T1 signal_qty",   signal_qty,   16'd100);
        check("T1 signal_symbol",signal_symbol, 8'd0);

        @(posedge clk); #1;
        check("T1b valid deasserts", signal_valid, 0);

        // ── Test 2: Deviation < -threshold -> BUY at ask ──
        deviation     = -32'sh0001_8000;  // -$1.50
        bid_price     = 32'h0096_0000;
        ask_price     = 32'h0096_8000;
        symbol_id     = 8'd1;
        feature_valid = 1;
        @(posedge clk); #1;
        feature_valid = 0;
        @(posedge clk); #1;
        check("T2 signal_valid", signal_valid, 1);
        check("T2 signal_side",  signal_side,  0);  // BUY
        check("T2 signal_price", signal_price, 32'h0096_8000);  // ask
        check("T2 signal_symbol",signal_symbol, 8'd1);

        // ── Test 3: Deviation within threshold -> no trade ──
        @(posedge clk); #1;
        deviation     = 32'sh0000_8000;  // +$0.50 (less than $1.00)
        feature_valid = 1;
        @(posedge clk); #1;
        feature_valid = 0;
        @(posedge clk); #1;
        check("T3 signal_valid", signal_valid, 0);

        // ── Test 4: Deviation exactly at threshold -> no trade ──
        deviation     = 32'sh0001_0000;  // +$1.00 exactly
        feature_valid = 1;
        @(posedge clk); #1;
        feature_valid = 0;
        @(posedge clk); #1;
        check("T4 signal_valid (at threshold)", signal_valid, 0);

        // ── Test 5: Deviation exactly at -threshold -> no trade ──
        deviation     = -32'sh0001_0000;  // -$1.00 exactly
        feature_valid = 1;
        @(posedge clk); #1;
        feature_valid = 0;
        @(posedge clk); #1;
        check("T5 signal_valid (at -threshold)", signal_valid, 0);

        // ── Test 6: Zero deviation -> no trade ──
        deviation     = 32'sh0;
        feature_valid = 1;
        @(posedge clk); #1;
        feature_valid = 0;
        @(posedge clk); #1;
        check("T6 signal_valid (zero)", signal_valid, 0);

        // ── Test 7: Very large deviation -> SELL ──
        deviation     = 32'sh7FFF_FFFF;  // max positive
        bid_price     = 32'h00C8_0000;
        ask_price     = 32'h00C8_8000;
        symbol_id     = 8'd3;
        feature_valid = 1;
        @(posedge clk); #1;
        feature_valid = 0;
        @(posedge clk); #1;
        check("T7 signal_valid", signal_valid, 1);
        check("T7 signal_side",  signal_side,  1);  // SELL
        check("T7 signal_price", signal_price, 32'h00C8_0000);  // bid
        check("T7 signal_symbol",signal_symbol, 8'd3);

        // ── Test 8: Different threshold ──
        threshold = 32'h0000_8000;  // $0.50
        deviation = 32'sh0000_C000;  // +$0.75 (now > threshold)
        bid_price = 32'h0032_0000;   // $50
        ask_price = 32'h0032_8000;   // $50.50
        symbol_id = 8'd2;
        feature_valid = 1;
        @(posedge clk); #1;
        feature_valid = 0;
        @(posedge clk); #1;
        check("T8 signal_valid", signal_valid, 1);
        check("T8 signal_side",  signal_side,  1);  // SELL
        check("T8 signal_price", signal_price, 32'h0032_0000);  // bid

        // ── Test 9: Different base_qty ──
        base_qty  = 16'd50;
        deviation = -32'sh0000_C000;  // -$0.75
        feature_valid = 1;
        @(posedge clk); #1;
        feature_valid = 0;
        @(posedge clk); #1;
        check("T9 signal_qty", signal_qty, 16'd50);

        // ── Test 10: No feature_valid -> no output ──
        repeat (5) @(posedge clk); #1;
        check("T10 signal_valid (idle)", signal_valid, 0);

        repeat (5) @(posedge clk);

        if (err_count == 0)
            $display("tb_strategy_engine: PASS");
        else
            $display("tb_strategy_engine: FAIL (%0d errors)", err_count);
        $finish;
    end

endmodule
