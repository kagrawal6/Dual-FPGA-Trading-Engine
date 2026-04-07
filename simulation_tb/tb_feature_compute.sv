`timescale 1ns / 1ps

module tb_feature_compute();
    import hft_pkg::*;

    logic        clk, rst_n, clear;
    price_t      bid_price, ask_price;
    symbol_t     symbol_id;
    logic        book_valid;
    logic [ALPHA_W-1:0] ema_alpha;
    price_t      mid, spread, ema;
    sprice_t     deviation;
    price_t      bid_out, ask_out;
    symbol_t     symbol_out;
    logic        feature_valid;

    integer err_cnt = 0;

    always #5 clk = ~clk;

    feature_compute dut (
        .clk(clk), .rst_n(rst_n), .clear(clear),
        .bid_price(bid_price), .ask_price(ask_price),
        .symbol_id(symbol_id), .book_valid(book_valid),
        .ema_alpha(ema_alpha),
        .mid(mid), .spread(spread), .ema(ema), .deviation(deviation),
        .bid_out(bid_out), .ask_out(ask_out),
        .symbol_out(symbol_out), .feature_valid(feature_valid)
    );

    initial begin
        clk = 0; rst_n = 0; clear = 0;
        bid_price = 0; ask_price = 0; symbol_id = 0; book_valid = 0;
        ema_alpha = 16'd32768; // 0.5 in Q0.16
        #20; rst_n = 1;
        @(posedge clk);

        // Test 1: First quote -> EMA seeds to mid
        $display("TEST 1: First quote, EMA init to mid");
        bid_price = 32'd100; ask_price = 32'd200; symbol_id = 8'd0;
        book_valid = 1;
        @(posedge clk); book_valid = 0;
        @(posedge clk); @(posedge clk); @(posedge clk); #1;

        if (feature_valid !== 1'b1) begin
            $display("FAIL: feature_valid not asserted"); err_cnt = err_cnt + 1;
        end else $display("PASS: feature_valid asserted");
        if (mid !== 32'd150) begin
            $display("FAIL: mid=%0d, exp 150", mid); err_cnt = err_cnt + 1;
        end else $display("PASS: mid=150");
        if (spread !== 32'd100) begin
            $display("FAIL: spread=%0d, exp 100", spread); err_cnt = err_cnt + 1;
        end else $display("PASS: spread=100");
        if (ema !== 32'd150) begin
            $display("FAIL: ema=%0d, exp 150", ema); err_cnt = err_cnt + 1;
        end else $display("PASS: ema=150 (first sample init)");
        if (deviation !== 0) begin
            $display("FAIL: deviation=%0d, exp 0", $signed(deviation)); err_cnt = err_cnt + 1;
        end else $display("PASS: deviation=0");
        @(posedge clk); #1;

        // Test 2: Second quote -> EMA = 0.5*200 + 0.5*150 = 175
        $display("TEST 2: Second quote, EMA update");
        bid_price = 32'd180; ask_price = 32'd220; symbol_id = 8'd0;
        book_valid = 1;
        @(posedge clk); book_valid = 0;
        @(posedge clk); @(posedge clk); @(posedge clk); #1;

        if (mid !== 32'd200) begin
            $display("FAIL: mid=%0d, exp 200", mid); err_cnt = err_cnt + 1;
        end else $display("PASS: mid=200");
        if (spread !== 32'd40) begin
            $display("FAIL: spread=%0d, exp 40", spread); err_cnt = err_cnt + 1;
        end else $display("PASS: spread=40");
        if (ema !== 32'd175) begin
            $display("FAIL: ema=%0d, exp 175", ema); err_cnt = err_cnt + 1;
        end else $display("PASS: ema=175");
        if ($signed(deviation) !== 32'sd25) begin
            $display("FAIL: deviation=%0d, exp 25", $signed(deviation)); err_cnt = err_cnt + 1;
        end else $display("PASS: deviation=25");
        @(posedge clk); #1;

        // Test 3: Third quote -> EMA = 0.5*170 + 0.5*175 = 172
        $display("TEST 3: Third quote, continued EMA");
        bid_price = 32'd160; ask_price = 32'd180; symbol_id = 8'd0;
        book_valid = 1;
        @(posedge clk); book_valid = 0;
        @(posedge clk); @(posedge clk); @(posedge clk); #1;

        if (mid !== 32'd170) begin
            $display("FAIL: mid=%0d, exp 170", mid); err_cnt = err_cnt + 1;
        end else $display("PASS: mid=170");
        if (ema !== 32'd172) begin
            $display("FAIL: ema=%0d, exp 172", ema); err_cnt = err_cnt + 1;
        end else $display("PASS: ema=172");
        @(posedge clk); #1;

        // Test 4: New symbol gets fresh EMA init
        $display("TEST 4: New symbol -> fresh EMA init");
        bid_price = 32'd500; ask_price = 32'd600; symbol_id = 8'd3;
        book_valid = 1;
        @(posedge clk); book_valid = 0;
        @(posedge clk); @(posedge clk); @(posedge clk); #1;

        if (ema !== 32'd550) begin
            $display("FAIL: ema=%0d, exp 550", ema); err_cnt = err_cnt + 1;
        end else $display("PASS: ema=550 (new symbol init)");
        if (symbol_out !== 8'd3) begin
            $display("FAIL: symbol_out=%0d, exp 3", symbol_out); err_cnt = err_cnt + 1;
        end else $display("PASS: symbol_out=3");

        $display("=================================");
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $display("=================================");
        $stop;
    end

endmodule
