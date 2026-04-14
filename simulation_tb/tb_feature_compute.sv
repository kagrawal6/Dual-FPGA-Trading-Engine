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
        @(posedge clk); @(posedge clk); #1;

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
        @(posedge clk); @(posedge clk); #1;

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
        @(posedge clk); @(posedge clk); #1;

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
        @(posedge clk); @(posedge clk); #1;

        if (ema !== 32'd550) begin
            $display("FAIL: ema=%0d, exp 550", ema); err_cnt = err_cnt + 1;
        end else $display("PASS: ema=550 (new symbol init)");
        if (symbol_out !== 8'd3) begin
            $display("FAIL: symbol_out=%0d, exp 3", symbol_out); err_cnt = err_cnt + 1;
        end else $display("PASS: symbol_out=3");
        @(posedge clk); #1;

        // ── Test 5: Clear resets EMA state ───────────────────────────
        // After clear, ema_init[] is zeroed for all symbols. The next
        // quote for symbol 0 must re-seed EMA to mid (fresh start).
        $display("TEST 5: Clear resets EMA state");
        clear = 1;
        @(posedge clk);
        clear = 0;
        @(posedge clk); @(posedge clk); #1; // flush pipeline

        bid_price = 32'd400; ask_price = 32'd600; symbol_id = 8'd0;
        book_valid = 1;
        @(posedge clk); book_valid = 0;
        @(posedge clk); @(posedge clk); #1;

        if (ema !== 32'd500) begin
            $display("FAIL: ema=%0d, exp 500 (re-seeded after clear)", ema);
            err_cnt = err_cnt + 1;
        end else $display("PASS: ema=500 (re-seeded after clear)");

        if (deviation !== 0) begin
            $display("FAIL: deviation=%0d, exp 0 after re-seed", $signed(deviation));
            err_cnt = err_cnt + 1;
        end else $display("PASS: deviation=0 after re-seed");
        @(posedge clk); #1;

        // ── Test 6: Spread computation ───────────────────────────────
        // bid=100, ask=300 → spread = ask-bid = 200, mid = 200
        $display("TEST 6: Spread computation bid=100 ask=300");
        bid_price = 32'd100; ask_price = 32'd300; symbol_id = 8'd10;
        book_valid = 1;
        @(posedge clk); book_valid = 0;
        @(posedge clk); @(posedge clk); #1;

        if (spread !== 32'd200) begin
            $display("FAIL: spread=%0d, exp 200", spread); err_cnt = err_cnt + 1;
        end else $display("PASS: spread=200");

        if (mid !== 32'd200) begin
            $display("FAIL: mid=%0d, exp 200", mid); err_cnt = err_cnt + 1;
        end else $display("PASS: mid=200");
        @(posedge clk); #1;

        // ── Test 7: ema_alpha=0 → EMA frozen at initial value ───────
        // With alpha=0, beta=65536. EMA_new = (0*mid + 65536*ema_old)>>16
        // = ema_old. After seeding, EMA must never change.
        $display("TEST 7: ema_alpha=0 -> EMA frozen");
        ema_alpha = 16'd0;

        // First quote for symbol 8: seeds EMA to mid=1500
        bid_price = 32'd1000; ask_price = 32'd2000; symbol_id = 8'd8;
        book_valid = 1;
        @(posedge clk); book_valid = 0;
        @(posedge clk); @(posedge clk); #1;

        if (ema !== 32'd1500) begin
            $display("FAIL: ema=%0d, exp 1500 (seed)", ema); err_cnt = err_cnt + 1;
        end else $display("PASS: ema=1500 (seed with alpha=0)");

        // Second quote for same symbol: mid=3000, EMA should stay 1500
        bid_price = 32'd2000; ask_price = 32'd4000; symbol_id = 8'd8;
        book_valid = 1;
        @(posedge clk); book_valid = 0;
        @(posedge clk); @(posedge clk); #1;

        if (ema !== 32'd1500) begin
            $display("FAIL: ema=%0d, exp 1500 (frozen)", ema); err_cnt = err_cnt + 1;
        end else $display("PASS: ema=1500 (frozen, alpha=0)");

        if (mid !== 32'd3000) begin
            $display("FAIL: mid=%0d, exp 3000", mid); err_cnt = err_cnt + 1;
        end else $display("PASS: mid=3000 while EMA frozen");

        $display("=================================");
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $display("=================================");
        $stop;
    end

endmodule
