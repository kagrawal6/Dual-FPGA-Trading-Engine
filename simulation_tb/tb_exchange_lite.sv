`timescale 1ns / 1ps

module tb_exchange_lite();
    import hft_pkg::*;

    localparam NUM_SYM = 4;

    logic                  clk, rst_n, enable, counter_clr;
    price_t                best_bid [NUM_SYM];
    price_t                best_ask [NUM_SYM];
    logic [FRAME_W-1:0]   order_frame;
    logic                  order_valid;
    logic [FRAME_W-1:0]   fill_frame;
    logic                  fill_valid, fill_ready;
    logic [COUNTER_W-1:0] orders_rcvd, fills_sent, rejects_sent;

    integer err_cnt = 0;
    integer i;

    always #5 clk = ~clk;

    exchange_lite #(.NUM_SYM(NUM_SYM)) dut (
        .clk(clk), .rst_n(rst_n), .enable(enable),
        .counter_clr(counter_clr),
        .best_bid(best_bid), .best_ask(best_ask),
        .order_frame(order_frame), .order_valid(order_valid),
        .fill_frame(fill_frame), .fill_valid(fill_valid),
        .fill_ready(fill_ready),
        .orders_rcvd(orders_rcvd), .fills_sent(fills_sent),
        .rejects_sent(rejects_sent)
    );

    initial begin
        clk = 0; rst_n = 0; enable = 0; counter_clr = 0;
        order_valid = 0; fill_ready = 1; order_frame = '0;
        for (i = 0; i < NUM_SYM; i++) begin
            best_bid[i] = 32'h0064_0000;   // $100 Q16.16
            best_ask[i] = 32'h0065_0000;   // $101 Q16.16
        end

        #20; rst_n = 1; @(posedge clk);
        enable = 1;

        // Test 1: BUY limit=$102 >= ask=$101 -> FILL at ask
        //               {MSG_ORDER, sym=0, side=BUY, 3'b0, price, qty, oid, ts, 32'b0}
        order_frame = {MSG_ORDER, 8'd0, 1'b0, 3'b000,
                       32'h0066_0000, 16'd100, 16'd1, 16'd10, 32'h0};
        order_valid = 1;
        @(posedge clk); order_valid = 0;
        @(posedge clk); #1;

        if (fill_frame[127:124] !== MSG_FILL) begin
            $display("FAIL: msg_type=%h, expected FILL", fill_frame[127:124]);
            err_cnt = err_cnt + 1;
        end else if (fill_frame[114:112] !== 3'b000) begin
            $display("FAIL: status=%b, expected FILLED(000)", fill_frame[114:112]);
            err_cnt = err_cnt + 1;
        end else if (fill_frame[111:80] !== 32'h0065_0000) begin
            $display("FAIL: fill_price=%h, expected ask=0065_0000", fill_frame[111:80]);
            err_cnt = err_cnt + 1;
        end else if (fill_frame[79:64] !== 16'd100) begin
            $display("FAIL: fill_qty=%0d, expected 100", fill_frame[79:64]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: BUY filled at ask price, qty=100");

        // Wait for pipeline to drain
        repeat(3) @(posedge clk);

        // Test 2: BUY limit=$99 < ask=$101 -> REJECT
        order_frame = {MSG_ORDER, 8'd0, 1'b0, 3'b000,
                       32'h0063_0000, 16'd50, 16'd2, 16'd20, 32'h0};
        order_valid = 1;
        @(posedge clk); order_valid = 0;
        @(posedge clk); #1;

        if (fill_frame[114:112] !== 3'b001) begin
            $display("FAIL: status=%b, expected REJECTED(001)", fill_frame[114:112]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: BUY below ask rejected");

        repeat(3) @(posedge clk);

        // Test 3: SELL limit=$99 <= bid=$100 -> FILL at bid
        order_frame = {MSG_ORDER, 8'd0, 1'b1, 3'b000,
                       32'h0063_0000, 16'd75, 16'd3, 16'd30, 32'h0};
        order_valid = 1;
        @(posedge clk); order_valid = 0;
        @(posedge clk); #1;

        if (fill_frame[114:112] !== 3'b000) begin
            $display("FAIL: status=%b, expected FILLED", fill_frame[114:112]);
            err_cnt = err_cnt + 1;
        end else if (fill_frame[115] !== 1'b1) begin
            $display("FAIL: side=%b, expected SELL(1)", fill_frame[115]);
            err_cnt = err_cnt + 1;
        end else if (fill_frame[111:80] !== 32'h0064_0000) begin
            $display("FAIL: fill_price=%h, expected bid=0064_0000", fill_frame[111:80]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: SELL filled at bid price");

        repeat(3) @(posedge clk);

        // Test 4: order_id and timestamp echoed back
        order_frame = {MSG_ORDER, 8'd1, 1'b0, 3'b000,
                       32'h0066_0000, 16'd10, 16'hABCD, 16'h1234, 32'h0};
        order_valid = 1;
        @(posedge clk); order_valid = 0;
        @(posedge clk); #1;

        if (fill_frame[63:48] !== 16'hABCD) begin
            $display("FAIL: order_id=%h, expected ABCD", fill_frame[63:48]);
            err_cnt = err_cnt + 1;
        end else if (fill_frame[47:32] !== 16'h1234) begin
            $display("FAIL: timestamp=%h, expected 1234", fill_frame[47:32]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: order_id and timestamp echoed correctly");

        repeat(3) @(posedge clk);

        // Test 5: counters
        @(posedge clk); #1;
        if (orders_rcvd !== 32'd4) begin
            $display("FAIL: orders_rcvd=%0d, expected 4", orders_rcvd);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: orders_rcvd=4");

        if (fills_sent !== 32'd3) begin
            $display("FAIL: fills_sent=%0d, expected 3", fills_sent);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: fills_sent=3");

        if (rejects_sent !== 32'd1) begin
            $display("FAIL: rejects_sent=%0d, expected 1", rejects_sent);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: rejects_sent=1");

        // Summary
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
