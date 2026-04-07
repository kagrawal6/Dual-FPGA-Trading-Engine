`timescale 1ns / 1ps

module tb_order_manager();
    import hft_pkg::*;

    logic        clk, rst_n, clear;
    logic        approved_valid, approved_side;
    price_t      approved_price;
    qty_t        approved_qty;
    symbol_t     approved_symbol;
    timestamp_t  cycle_counter;
    logic [FRAME_W-1:0]  order_frame;
    logic                 order_valid, order_ready;
    logic [COUNTER_W-1:0] orders_sent;

    integer err_cnt = 0;

    always #5 clk = ~clk;

    order_manager dut (
        .clk(clk), .rst_n(rst_n), .clear(clear),
        .approved_valid(approved_valid), .approved_side(approved_side),
        .approved_price(approved_price), .approved_qty(approved_qty),
        .approved_symbol(approved_symbol), .cycle_counter(cycle_counter),
        .order_frame(order_frame), .order_valid(order_valid),
        .order_ready(order_ready), .orders_sent(orders_sent)
    );

    initial begin
        clk = 0; rst_n = 0; clear = 0;
        approved_valid = 0; approved_side = 0;
        approved_price = 0; approved_qty = 0; approved_symbol = 0;
        cycle_counter = 16'd100; order_ready = 1;
        #20; rst_n = 1;
        @(posedge clk);

        // Test 1: BUY order -> correct ORDER frame fields
        $display("TEST 1: BUY order -> ORDER frame");
        approved_valid = 1; approved_side = 0;
        approved_price = 32'd5000; approved_qty = 16'd25;
        approved_symbol = 8'd7; cycle_counter = 16'd42;
        @(posedge clk);
        approved_valid = 0;
        @(posedge clk); #1;

        if (order_valid !== 1'b1) begin
            $display("FAIL: order_valid should be 1"); err_cnt = err_cnt + 1;
        end else $display("PASS: order_valid=1");
        if (order_frame[127:124] !== MSG_ORDER) begin
            $display("FAIL: msg_type=%h, exp 2", order_frame[127:124]); err_cnt = err_cnt + 1;
        end else $display("PASS: msg_type=ORDER");
        if (order_frame[123:116] !== 8'd7) begin
            $display("FAIL: symbol=%0d, exp 7", order_frame[123:116]); err_cnt = err_cnt + 1;
        end else $display("PASS: symbol=7");
        if (order_frame[115] !== 1'b0) begin
            $display("FAIL: side=%b, exp 0 (BUY)", order_frame[115]); err_cnt = err_cnt + 1;
        end else $display("PASS: side=BUY");
        if (order_frame[111:80] !== 32'd5000) begin
            $display("FAIL: price=%0d, exp 5000", order_frame[111:80]); err_cnt = err_cnt + 1;
        end else $display("PASS: price=5000");
        if (order_frame[79:64] !== 16'd25) begin
            $display("FAIL: qty=%0d, exp 25", order_frame[79:64]); err_cnt = err_cnt + 1;
        end else $display("PASS: qty=25");
        if (order_frame[63:48] !== 16'd0) begin
            $display("FAIL: order_id=%0d, exp 0", order_frame[63:48]); err_cnt = err_cnt + 1;
        end else $display("PASS: order_id=0");
        @(posedge clk); #1;

        // Test 2: SELL order -> side=1, incremented order_id
        $display("TEST 2: SELL order -> correct frame");
        approved_valid = 1; approved_side = 1;
        approved_price = 32'd8000; approved_qty = 16'd50;
        approved_symbol = 8'd3; cycle_counter = 16'd55;
        @(posedge clk);
        approved_valid = 0;
        @(posedge clk); #1;

        if (order_frame[115] !== 1'b1) begin
            $display("FAIL: side=%b, exp 1 (SELL)", order_frame[115]); err_cnt = err_cnt + 1;
        end else $display("PASS: side=SELL");
        if (order_frame[63:48] !== 16'd1) begin
            $display("FAIL: order_id=%0d, exp 1", order_frame[63:48]); err_cnt = err_cnt + 1;
        end else $display("PASS: order_id=1 (incremented)");
        @(posedge clk); #1;

        // Test 3: Backpressure: order_ready=0 holds output
        $display("TEST 3: Backpressure holds output");
        order_ready = 0;
        approved_valid = 1; approved_side = 0;
        approved_price = 32'd1234; approved_qty = 16'd1;
        approved_symbol = 8'd0; cycle_counter = 16'd99;
        @(posedge clk);
        approved_valid = 0;
        @(posedge clk); #1;

        if (order_valid !== 1'b1) begin
            $display("FAIL: order_valid should be 1"); err_cnt = err_cnt + 1;
        end else $display("PASS: order_valid=1 during backpressure");
        @(posedge clk); #1;
        if (order_valid !== 1'b1) begin
            $display("FAIL: order_valid should hold"); err_cnt = err_cnt + 1;
        end else $display("PASS: order_valid holds while ready=0");

        order_ready = 1;
        @(posedge clk); @(posedge clk); #1;
        if (order_valid !== 1'b0) begin
            $display("FAIL: order_valid should clear"); err_cnt = err_cnt + 1;
        end else $display("PASS: order_valid cleared after consume");
        if (orders_sent !== 32'd3) begin
            $display("FAIL: orders_sent=%0d, exp 3", orders_sent); err_cnt = err_cnt + 1;
        end else $display("PASS: orders_sent=3");

        $display("=================================");
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $display("=================================");
        $stop;
    end

endmodule
