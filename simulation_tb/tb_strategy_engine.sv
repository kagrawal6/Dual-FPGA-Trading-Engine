`timescale 1ns / 1ps

module tb_strategy_engine();
    import hft_pkg::*;

    logic        clk, rst_n;
    sprice_t     deviation;
    price_t      bid_price, ask_price, threshold;
    symbol_t     symbol_id;
    qty_t        base_qty;
    logic        feature_valid;

    logic        signal_valid, signal_side;
    price_t      signal_price;
    qty_t        signal_qty;
    symbol_t     signal_symbol;

    integer err_cnt = 0;

    always #5 clk = ~clk;

    strategy_engine dut (
        .clk(clk), .rst_n(rst_n),
        .deviation(deviation), .bid_price(bid_price), .ask_price(ask_price),
        .symbol_id(symbol_id), .feature_valid(feature_valid),
        .threshold(threshold), .base_qty(base_qty),
        .signal_valid(signal_valid), .signal_side(signal_side),
        .signal_price(signal_price), .signal_qty(signal_qty),
        .signal_symbol(signal_symbol)
    );

    initial begin
        clk = 0; rst_n = 0;
        deviation = 0; bid_price = 0; ask_price = 0;
        symbol_id = 0; feature_valid = 0;
        threshold = 32'd10;
        base_qty = 16'd5;
        #20; rst_n = 1;
        @(posedge clk);

        // Test 1: deviation > +threshold -> SELL at bid
        // Mean-rev: price above average -> sell (expect revert down)
        $display("TEST 1: deviation=+20 > threshold=10 -> SELL");
        deviation = 32'sd20;
        bid_price = 32'd1000; ask_price = 32'd1010;
        symbol_id = 8'd2; feature_valid = 1;
        @(posedge clk);
        feature_valid = 0;
        @(posedge clk); #1;

        if (signal_valid !== 1'b1) begin
            $display("FAIL: signal_valid should be 1"); err_cnt = err_cnt + 1;
        end else $display("PASS: signal_valid=1");

        if (signal_side !== 1'b1) begin
            $display("FAIL: signal_side should be 1 (SELL)"); err_cnt = err_cnt + 1;
        end else $display("PASS: signal_side=SELL");

        if (signal_price !== 32'd1000) begin
            $display("FAIL: signal_price=%0d, exp 1000 (bid)", signal_price);
            err_cnt = err_cnt + 1;
        end else $display("PASS: signal_price=bid=1000");

        if (signal_qty !== 16'd5) begin
            $display("FAIL: signal_qty=%0d, exp 5", signal_qty); err_cnt = err_cnt + 1;
        end else $display("PASS: signal_qty=5");

        @(posedge clk); #1;

        // Test 2: deviation < -threshold -> BUY at ask
        $display("TEST 2: deviation=-15 < -threshold=-10 -> BUY");
        deviation = -32'sd15;
        bid_price = 32'd900; ask_price = 32'd910;
        symbol_id = 8'd4; feature_valid = 1;
        @(posedge clk);
        feature_valid = 0;
        @(posedge clk); #1;

        if (signal_valid !== 1'b1) begin
            $display("FAIL: signal_valid should be 1"); err_cnt = err_cnt + 1;
        end else $display("PASS: signal_valid=1");

        if (signal_side !== 1'b0) begin
            $display("FAIL: signal_side should be 0 (BUY)"); err_cnt = err_cnt + 1;
        end else $display("PASS: signal_side=BUY");

        if (signal_price !== 32'd910) begin
            $display("FAIL: signal_price=%0d, exp 910 (ask)", signal_price);
            err_cnt = err_cnt + 1;
        end else $display("PASS: signal_price=ask=910");

        if (signal_symbol !== 8'd4) begin
            $display("FAIL: signal_symbol=%0d, exp 4", signal_symbol);
            err_cnt = err_cnt + 1;
        end else $display("PASS: signal_symbol=4");

        @(posedge clk); #1;

        // Test 3: deviation within threshold -> no trade
        $display("TEST 3: deviation=+5, within threshold -> HOLD");
        deviation = 32'sd5;
        bid_price = 32'd950; ask_price = 32'd960;
        symbol_id = 8'd0; feature_valid = 1;
        @(posedge clk);
        feature_valid = 0;
        @(posedge clk); #1;

        if (signal_valid !== 1'b0) begin
            $display("FAIL: signal_valid should be 0 (no trade)");
            err_cnt = err_cnt + 1;
        end else $display("PASS: signal_valid=0 (HOLD)");

        @(posedge clk); #1;

        // Test 4: Exactly at threshold -> no trade (strict inequality)
        $display("TEST 4: deviation=+10 exactly at threshold -> no trade");
        deviation = 32'sd10;
        bid_price = 32'd950; ask_price = 32'd960;
        symbol_id = 8'd0; feature_valid = 1;
        @(posedge clk);
        feature_valid = 0;
        @(posedge clk); #1;

        if (signal_valid !== 1'b0) begin
            $display("FAIL: signal_valid should be 0 at exact threshold");
            err_cnt = err_cnt + 1;
        end else $display("PASS: signal_valid=0 at exact threshold");

        @(posedge clk); #1;

        // Test 5: feature_valid=0 -> no output
        $display("TEST 5: feature_valid=0 -> no output");
        deviation = 32'sd100; feature_valid = 0;
        @(posedge clk); @(posedge clk); #1;
        if (signal_valid !== 1'b0) begin
            $display("FAIL: signal_valid should be 0"); err_cnt = err_cnt + 1;
        end else $display("PASS: no signal when feature_valid=0");

        $display("=================================");
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $display("=================================");
        $stop;
    end

endmodule
