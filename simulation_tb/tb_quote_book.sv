`timescale 1ns / 1ps

module tb_quote_book();
    import hft_pkg::*;

    logic               clk, rst_n;
    logic [FRAME_W-1:0] quote_frame;
    logic               quote_valid;
    price_t             bid_price, ask_price;
    qty_t               bid_size, ask_size;
    symbol_t            symbol_id;
    regime_e            regime;
    logic               book_valid;

    integer err_cnt = 0;

    always #5 clk = ~clk;

    quote_book dut (
        .clk(clk), .rst_n(rst_n),
        .quote_frame(quote_frame), .quote_valid(quote_valid),
        .bid_price(bid_price), .ask_price(ask_price),
        .bid_size(bid_size), .ask_size(ask_size),
        .symbol_id(symbol_id), .regime(regime),
        .book_valid(book_valid)
    );

    initial begin
        clk = 0; rst_n = 0;
        quote_frame = '0; quote_valid = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // Frame layout: [127:124]=msg_type, [123:116]=symbol, [115:114]=regime,
        //   [113:112]=unused, [111:80]=bid, [79:48]=ask, [47:32]=bid_sz, [31:16]=ask_sz

        // Test 1: Write symbol 0, bid=100, ask=200
        $display("TEST 1: Write symbol 0 bid=100 ask=200");
        quote_frame = {MSG_QUOTE, 8'd0, 2'b00, 2'b0,
                        32'd100, 32'd200, 16'd10, 16'd20};
        quote_valid = 1;
        @(posedge clk);
        quote_valid = 0;
        @(posedge clk); #1;

        if (book_valid !== 1'b1) begin
            $display("FAIL: book_valid not asserted"); err_cnt = err_cnt + 1;
        end else $display("PASS: book_valid asserted");

        if (bid_price !== 32'd100) begin
            $display("FAIL: bid_price=%0d, exp 100", bid_price); err_cnt = err_cnt + 1;
        end else $display("PASS: bid_price=100");

        if (ask_price !== 32'd200) begin
            $display("FAIL: ask_price=%0d, exp 200", ask_price); err_cnt = err_cnt + 1;
        end else $display("PASS: ask_price=200");

        if (symbol_id !== 8'd0) begin
            $display("FAIL: symbol_id=%0d, exp 0", symbol_id); err_cnt = err_cnt + 1;
        end else $display("PASS: symbol_id=0");

        @(posedge clk); #1;

        // Test 2: Write symbol 1 (independent storage)
        $display("TEST 2: Write symbol 1 bid=300 ask=400");
        quote_frame = {MSG_QUOTE, 8'd1, 2'b01, 2'b0,
                        32'd300, 32'd400, 16'd5, 16'd8};
        quote_valid = 1;
        @(posedge clk);
        quote_valid = 0;
        @(posedge clk); #1;

        if (bid_price !== 32'd300) begin
            $display("FAIL: bid_price=%0d, exp 300", bid_price); err_cnt = err_cnt + 1;
        end else $display("PASS: bid_price=300");

        if (ask_price !== 32'd400) begin
            $display("FAIL: ask_price=%0d, exp 400", ask_price); err_cnt = err_cnt + 1;
        end else $display("PASS: ask_price=400");

        if (symbol_id !== 8'd1) begin
            $display("FAIL: symbol_id=%0d, exp 1", symbol_id); err_cnt = err_cnt + 1;
        end else $display("PASS: symbol_id=1");

        if (regime !== REGIME_VOLATILE) begin
            $display("FAIL: regime mismatch"); err_cnt = err_cnt + 1;
        end else $display("PASS: regime=VOLATILE");

        @(posedge clk); #1;

        // Test 3: Overwrite symbol 0, verify new values
        $display("TEST 3: Overwrite symbol 0 bid=500 ask=600");
        quote_frame = {MSG_QUOTE, 8'd0, 2'b00, 2'b0,
                        32'd500, 32'd600, 16'd15, 16'd25};
        quote_valid = 1;
        @(posedge clk);
        quote_valid = 0;
        @(posedge clk); #1;

        if (bid_price !== 32'd500) begin
            $display("FAIL: bid_price=%0d, exp 500", bid_price); err_cnt = err_cnt + 1;
        end else $display("PASS: bid_price=500 after overwrite");

        if (ask_price !== 32'd600) begin
            $display("FAIL: ask_price=%0d, exp 600", ask_price); err_cnt = err_cnt + 1;
        end else $display("PASS: ask_price=600 after overwrite");

        if (bid_size !== 16'd15) begin
            $display("FAIL: bid_size=%0d, exp 15", bid_size); err_cnt = err_cnt + 1;
        end else $display("PASS: bid_size=15");

        if (ask_size !== 16'd25) begin
            $display("FAIL: ask_size=%0d, exp 25", ask_size); err_cnt = err_cnt + 1;
        end else $display("PASS: ask_size=25");

        // Summary
        $display("=================================");
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $display("=================================");
        $stop;
    end

endmodule
