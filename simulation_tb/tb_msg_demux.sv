`timescale 1ns / 1ps

module tb_msg_demux();
    import hft_pkg::*;

    logic               clk, rst_n, clear;
    logic [FRAME_W-1:0] frame_in;
    logic               frame_in_valid;
    logic [FRAME_W-1:0] quote_frame, fill_frame;
    logic               quote_valid, fill_valid;
    logic [COUNTER_W-1:0] quotes_rcvd, demux_errors;

    integer err_cnt = 0;

    always #5 clk = ~clk;

    msg_demux dut (
        .clk(clk), .rst_n(rst_n), .clear(clear),
        .frame_in(frame_in), .frame_in_valid(frame_in_valid),
        .quote_frame(quote_frame), .quote_valid(quote_valid),
        .fill_frame(fill_frame), .fill_valid(fill_valid),
        .quotes_rcvd(quotes_rcvd), .demux_errors(demux_errors)
    );

    initial begin
        clk = 0; rst_n = 0; clear = 0;
        frame_in = '0; frame_in_valid = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // Test 1: QUOTE frame (msg_type=4'h1 in [127:124])
        $display("TEST 1: Send QUOTE frame");
        frame_in = {MSG_QUOTE, 8'd5, 2'b00, 2'b0, 32'd100, 32'd200, 16'd10, 16'd20};
        frame_in_valid = 1;
        @(posedge clk);
        frame_in_valid = 0;
        @(posedge clk); #1;

        if (quote_valid !== 1'b1) begin
            $display("FAIL: quote_valid should be 1"); err_cnt = err_cnt + 1;
        end else $display("PASS: quote_valid is 1");

        if (quote_frame[127:124] !== MSG_QUOTE) begin
            $display("FAIL: quote_frame msg_type mismatch"); err_cnt = err_cnt + 1;
        end else $display("PASS: quote_frame msg_type correct");

        if (fill_valid !== 1'b0) begin
            $display("FAIL: fill_valid should be 0"); err_cnt = err_cnt + 1;
        end else $display("PASS: fill_valid is 0");

        @(posedge clk); #1;

        // Test 2: FILL frame (msg_type=4'h3)
        $display("TEST 2: Send FILL frame");
        frame_in = {MSG_FILL, 124'hABCDEF};
        frame_in_valid = 1;
        @(posedge clk);
        frame_in_valid = 0;
        @(posedge clk); #1;

        if (fill_valid !== 1'b1) begin
            $display("FAIL: fill_valid should be 1"); err_cnt = err_cnt + 1;
        end else $display("PASS: fill_valid is 1");

        if (fill_frame[127:124] !== MSG_FILL) begin
            $display("FAIL: fill_frame msg_type mismatch"); err_cnt = err_cnt + 1;
        end else $display("PASS: fill_frame msg_type correct");

        if (quote_valid !== 1'b0) begin
            $display("FAIL: quote_valid should be 0 during fill"); err_cnt = err_cnt + 1;
        end else $display("PASS: quote_valid is 0 during fill");

        @(posedge clk); #1;

        // Test 3: Unknown msg_type -> no valid, error counter
        $display("TEST 3: Unknown msg_type");
        frame_in = {4'hF, 124'd0};
        frame_in_valid = 1;
        @(posedge clk);
        frame_in_valid = 0;
        @(posedge clk); #1;

        if (quote_valid !== 1'b0) begin
            $display("FAIL: quote_valid should be 0"); err_cnt = err_cnt + 1;
        end else $display("PASS: quote_valid is 0 for unknown type");

        if (fill_valid !== 1'b0) begin
            $display("FAIL: fill_valid should be 0"); err_cnt = err_cnt + 1;
        end else $display("PASS: fill_valid is 0 for unknown type");

        if (demux_errors !== 32'd1) begin
            $display("FAIL: demux_errors expected 1, got %0d", demux_errors);
            err_cnt = err_cnt + 1;
        end else $display("PASS: demux_errors = 1");

        // Test 4: Verify quotes_rcvd counter
        $display("TEST 4: Check quotes_rcvd counter");
        if (quotes_rcvd !== 32'd1) begin
            $display("FAIL: quotes_rcvd expected 1, got %0d", quotes_rcvd);
            err_cnt = err_cnt + 1;
        end else $display("PASS: quotes_rcvd = 1");

        // Send another quote to verify counter increments
        frame_in = {MSG_QUOTE, 124'd999};
        frame_in_valid = 1;
        @(posedge clk);
        frame_in_valid = 0;
        @(posedge clk); #1;

        if (quotes_rcvd !== 32'd2) begin
            $display("FAIL: quotes_rcvd expected 2, got %0d", quotes_rcvd);
            err_cnt = err_cnt + 1;
        end else $display("PASS: quotes_rcvd = 2 after second quote");

        // Summary
        $display("=================================");
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $display("=================================");
        $stop;
    end

endmodule
