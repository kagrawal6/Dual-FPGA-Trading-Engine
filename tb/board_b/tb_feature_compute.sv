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

    initial clk = 0;
    always #5 clk = ~clk;

    int err_count = 0;

    task automatic check(input string name, input logic [31:0] got, input logic [31:0] exp);
        if (got !== exp) begin
            $display("FAIL [%0t] %s: got 0x%08h, expected 0x%08h", $time, name, got, exp);
            err_count++;
        end
    endtask

    task automatic check_tolerance(input string name, input logic [31:0] got,
                                   input logic [31:0] exp, input int tol);
        logic signed [31:0] diff;
        diff = $signed(got) - $signed(exp);
        if (diff < -tol || diff > tol) begin
            $display("FAIL [%0t] %s: got 0x%08h, expected 0x%08h (tol=%0d)", $time, name, got, exp, tol);
            err_count++;
        end
    endtask

    feature_compute dut (.*);

    // Golden EMA model
    logic [63:0] golden_ema;
    logic [31:0] golden_mid;

    initial begin
        rst_n = 0; clear = 0; bid_price = 0; ask_price = 0;
        symbol_id = 0; book_valid = 0;
        ema_alpha = 16'd6554;  // ~0.1 in Q0.16
        golden_ema = 0;
        #100; rst_n = 1;
        @(posedge clk); #1;

        // ── Test 1: Single quote, check mid & spread (3-cycle latency) ──
        bid_price  = 32'h0096_0000;  // $150.00
        ask_price  = 32'h0096_8000;  // $150.50
        symbol_id  = 8'd0;
        book_valid = 1;
        @(posedge clk); #1;
        book_valid = 0;

        // Wait 3 cycles for output
        @(posedge clk); #1;
        @(posedge clk); #1;
        @(posedge clk); #1;
        check("T1 feature_valid", feature_valid, 1);
        check("T1 mid",    mid,    32'h0096_4000);  // (150.00 + 150.50) / 2 = 150.25
        check("T1 spread", spread, 32'h0000_8000);  // 150.50 - 150.00 = 0.50
        check("T1 bid_out", bid_out, 32'h0096_0000);
        check("T1 ask_out", ask_out, 32'h0096_8000);
        check("T1 symbol_out", symbol_out, 8'd0);

        // First EMA: alpha*mid + (1-alpha)*0 >> 16 = alpha*mid >> 16
        golden_mid = 32'h0096_4000;
        golden_ema = ({32'b0, ema_alpha} * {32'b0, golden_mid}
                    + {32'b0, (32'd65536 - {16'b0, ema_alpha})} * 64'd0) >> 16;
        check_tolerance("T1 ema", ema, golden_ema[31:0], 2);

        @(posedge clk); #1;
        check("T1b feature_valid deasserts", feature_valid, 0);

        // ── Test 2: Feed same quote 20 times, EMA should converge ──
        for (int i = 0; i < 20; i++) begin
            bid_price  = 32'h00C8_0000;  // $200.00
            ask_price  = 32'h00C9_0000;  // $201.00
            symbol_id  = 8'd1;
            book_valid = 1;
            @(posedge clk); #1;
            book_valid = 0;
            repeat (3) @(posedge clk); #1;
        end
        // After 20 iterations with constant input, EMA should be close to mid = $200.50
        golden_mid = 32'h00C8_8000;  // (200 + 201) / 2 = 200.50
        check_tolerance("T2 ema converge", ema, golden_mid, 32'h0002_0000);
        check("T2 spread", spread, 32'h0001_0000);  // 201 - 200 = 1.0

        // ── Test 3: Check deviation sign ──
        // After convergence, EMA ~= mid, so deviation should be near zero
        check_tolerance("T3 deviation near zero", deviation, 32'h0, 32'h0002_0000);

        // ── Test 4: Clear resets EMA state ──
        clear = 1;
        @(posedge clk); #1;
        clear = 0;
        @(posedge clk); #1;

        // Feed a new quote; EMA should start from 0 again
        bid_price  = 32'h0064_0000;  // $100.00
        ask_price  = 32'h0064_8000;  // $100.50
        symbol_id  = 8'd1;
        book_valid = 1;
        @(posedge clk); #1;
        book_valid = 0;
        repeat (3) @(posedge clk); #1;
        golden_mid = 32'h0064_4000;  // $100.25
        golden_ema = ({32'b0, ema_alpha} * {32'b0, golden_mid}) >> 16;
        check_tolerance("T4 ema after clear", ema, golden_ema[31:0], 2);

        // ── Test 5: Different symbols maintain independent EMA ──
        // Symbol 0 was set in T1, symbol 1 cleared in T4; send to symbol 0
        bid_price  = 32'h0096_0000;
        ask_price  = 32'h0096_8000;
        symbol_id  = 8'd0;
        book_valid = 1;
        @(posedge clk); #1;
        book_valid = 0;
        repeat (3) @(posedge clk); #1;
        // Symbol 0 was also cleared, so EMA starts fresh from 0
        golden_mid = 32'h0096_4000;
        golden_ema = ({32'b0, ema_alpha} * {32'b0, golden_mid}) >> 16;
        check_tolerance("T5 sym0 ema independent", ema, golden_ema[31:0], 2);

        // ── Test 6: Pipeline pass-through alignment ──
        bid_price  = 32'h00FF_0000;
        ask_price  = 32'h0100_0000;
        symbol_id  = 8'd2;
        book_valid = 1;
        @(posedge clk); #1;
        book_valid = 0;
        repeat (3) @(posedge clk); #1;
        check("T6 bid_out passthrough", bid_out, 32'h00FF_0000);
        check("T6 ask_out passthrough", ask_out, 32'h0100_0000);
        check("T6 symbol_out passthrough", symbol_out, 8'd2);

        repeat (5) @(posedge clk);

        if (err_count == 0)
            $display("tb_feature_compute: PASS");
        else
            $display("tb_feature_compute: FAIL (%0d errors)", err_count);
        $finish;
    end

endmodule
