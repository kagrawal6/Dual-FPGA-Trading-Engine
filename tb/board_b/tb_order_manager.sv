// ============================================================================
// Testbench: tb_order_manager
// Tests the order_manager module: ORDER frame packing, order_id and timestamp
// assignment, order_ready handshake, and clear functionality.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_order_manager;

    logic                     clk;
    logic                     rst_n;
    logic                     clear;
    logic                     approved_valid;
    logic                     approved_side;
    price_t                   approved_price;
    qty_t                     approved_qty;
    symbol_t                  approved_symbol;
    timestamp_t               cycle_counter;
    logic [FRAME_W-1:0]       order_frame;
    logic                     order_valid;
    logic                     order_ready;
    logic [COUNTER_W-1:0]     orders_sent;

    initial clk = 0;
    always #5 clk = ~clk;

    int err_count = 0;

    // Free-running cycle counter
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) cycle_counter <= '0;
        else        cycle_counter <= cycle_counter + 1;
    end

    task automatic check(input string name, input logic [31:0] got, input logic [31:0] exp);
        if (got !== exp) begin
            $display("FAIL [%0t] %s: got 0x%08h, expected 0x%08h", $time, name, got, exp);
            err_count++;
        end
    endtask

    order_manager dut (.*);

    initial begin
        rst_n = 0; clear = 0; approved_valid = 0; approved_side = 0;
        approved_price = 0; approved_qty = 0; approved_symbol = 0;
        order_ready = 1;
        #100; rst_n = 1;
        @(posedge clk); #1;

        // ── Test 1: Basic ORDER frame generation ──
        approved_valid  = 1;
        approved_side   = 1'b0;       // BUY
        approved_price  = 32'h0096_8000;  // $150.50
        approved_qty    = 16'd100;
        approved_symbol = 8'd0;
        @(posedge clk); #1;
        approved_valid = 0;
        @(posedge clk); #1;

        check("T1 order_valid", order_valid, 1);
        check("T1 msg_type", order_frame[127:124], MSG_ORDER);
        check("T1 symbol",   order_frame[123:116], 8'd0);
        check("T1 side",     order_frame[115],     1'b0);
        check("T1 reserved", order_frame[114:112], 3'b000);
        check("T1 price",    order_frame[111:80],  32'h0096_8000);
        check("T1 qty",      order_frame[79:64],   16'd100);
        check("T1 order_id", order_frame[63:48],   16'd0);  // first order
        check("T1 reserved_lo", order_frame[31:0], 32'h0);
        check("T1 orders_sent", orders_sent, 1);

        // Accept the frame
        @(posedge clk); #1;

        // ── Test 2: Second order -> order_id increments ──
        approved_valid  = 1;
        approved_side   = 1'b1;       // SELL
        approved_price  = 32'h0096_0000;  // $150.00
        approved_qty    = 16'd50;
        approved_symbol = 8'd1;
        @(posedge clk); #1;
        approved_valid = 0;
        @(posedge clk); #1;

        check("T2 order_valid", order_valid, 1);
        check("T2 side",     order_frame[115],    1'b1);
        check("T2 symbol",   order_frame[123:116], 8'd1);
        check("T2 order_id", order_frame[63:48],   16'd1);  // second order
        check("T2 orders_sent", orders_sent, 2);

        @(posedge clk); #1;

        // ── Test 3: Timestamp is captured from cycle_counter ──
        begin
            timestamp_t ts_before;
            ts_before = cycle_counter;  // capture before asserting
            approved_valid  = 1;
            approved_side   = 1'b0;
            approved_price  = 32'h0064_0000;
            approved_qty    = 16'd200;
            approved_symbol = 8'd2;
            @(posedge clk); #1;
            approved_valid = 0;
            @(posedge clk); #1;
            // timestamp should be ts_before (captured on the clock edge when approved_valid was high)
            check("T3 timestamp", order_frame[47:32], ts_before);
        end

        @(posedge clk); #1;

        // ── Test 4: order_ready=0 -> frame held ──
        order_ready = 0;
        approved_valid  = 1;
        approved_side   = 1'b0;
        approved_price  = 32'h00C8_0000;
        approved_qty    = 16'd75;
        approved_symbol = 8'd3;
        @(posedge clk); #1;
        approved_valid = 0;
        @(posedge clk); #1;
        check("T4 order_valid (held)", order_valid, 1);

        // Frame stays valid
        repeat (3) @(posedge clk); #1;
        check("T4 still valid", order_valid, 1);

        // Now accept
        order_ready = 1;
        @(posedge clk); #1;
        check("T4 clears after accept", order_valid, 0);

        // ── Test 5: Clear resets order_id and counter ──
        clear = 1;
        @(posedge clk); #1;
        clear = 0;
        @(posedge clk); #1;
        check("T5 orders_sent after clear", orders_sent, 0);

        // Next order should get ID 0 again
        approved_valid  = 1;
        approved_side   = 1'b0;
        approved_price  = 32'h0032_0000;
        approved_qty    = 16'd10;
        approved_symbol = 8'd0;
        @(posedge clk); #1;
        approved_valid = 0;
        @(posedge clk); #1;
        check("T5 order_id reset", order_frame[63:48], 16'd0);
        check("T5 orders_sent", orders_sent, 1);

        // ── Test 6: Rapid back-to-back orders ──
        for (int i = 0; i < 5; i++) begin
            approved_valid  = 1;
            approved_side   = i[0];
            approved_price  = 32'h0050_0000 + i[31:0] * 32'h10000;
            approved_qty    = 16'd10 + i[15:0];
            approved_symbol = i[7:0];
            @(posedge clk); #1;
        end
        approved_valid = 0;
        @(posedge clk); #1;
        check("T6 orders_sent", orders_sent, 6);  // 1 from T5 + 5 here

        repeat (5) @(posedge clk);

        if (err_count == 0)
            $display("tb_order_manager: PASS");
        else
            $display("tb_order_manager: FAIL (%0d errors)", err_count);
        $finish;
    end

endmodule
