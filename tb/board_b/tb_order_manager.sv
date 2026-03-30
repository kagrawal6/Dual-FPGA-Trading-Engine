// ============================================================================
// Testbench: tb_order_manager
// Tests the order_manager module: ORDER frame packing per Appendix C,
// auto-incrementing order_id, timestamp capture, backpressure handling,
// and counter clearing.
//
// Golden model reference: board_b.py BoardB._handle_quote() packs
// ORDER frames with the same field layout and auto-incrementing ID.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_order_manager;

    logic        clk, rst_n, clear;
    logic        approved_valid, approved_side;
    price_t      approved_price;
    qty_t        approved_qty;
    symbol_t     approved_symbol;
    timestamp_t  cycle_counter;
    logic [FRAME_W-1:0] order_frame;
    logic        order_valid, order_ready;
    logic [COUNTER_W-1:0] orders_sent;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    order_manager dut (
        .clk             (clk),
        .rst_n           (rst_n),
        .clear           (clear),
        .approved_valid  (approved_valid),
        .approved_side   (approved_side),
        .approved_price  (approved_price),
        .approved_qty    (approved_qty),
        .approved_symbol (approved_symbol),
        .cycle_counter   (cycle_counter),
        .order_frame     (order_frame),
        .order_valid     (order_valid),
        .order_ready     (order_ready),
        .orders_sent     (orders_sent)
    );

    integer pass_count = 0;
    integer fail_count = 0;

    task automatic check(input string name, input logic condition);
        if (condition) begin
            pass_count++;
        end else begin
            fail_count++;
            $display("[FAIL] %0s at time %0t", name, $time);
        end
    endtask

    task automatic check32(input string name, input logic [31:0] actual, input logic [31:0] expected);
        if (actual == expected) begin
            pass_count++;
        end else begin
            fail_count++;
            $display("[FAIL] %0s: got 0x%08X, expected 0x%08X at time %0t",
                     name, actual, expected, $time);
        end
    endtask

    initial begin
        approved_valid  = 1'b0;
        approved_side   = 1'b0;
        approved_price  = '0;
        approved_qty    = '0;
        approved_symbol = '0;
        cycle_counter   = '0;
        clear           = 1'b0;
        order_ready     = 1'b1;

        @(posedge rst_n);
        repeat (2) @(posedge clk);

        // ── T1: Basic BUY order packing ─────────────────────────
        $display("\n=== T1: BUY order frame packing ===");
        cycle_counter   = 16'h002A;
        approved_valid  = 1'b1;
        approved_side   = 1'b0;  // BUY
        approved_price  = 32'h00B4_1999;  // ask price
        approved_qty    = 16'd100;
        approved_symbol = 8'd0;
        @(posedge clk);
        approved_valid = 1'b0;
        @(posedge clk);

        check("T1: order_valid",         order_valid == 1'b1);
        check("T1: msg_type==ORDER",     order_frame[127:124] == MSG_ORDER);
        check("T1: symbol==0",           order_frame[123:116] == 8'd0);
        check("T1: side==BUY",           order_frame[115] == 1'b0);
        check("T1: reserved==000",       order_frame[114:112] == 3'b000);
        check32("T1: price",              order_frame[111:80], 32'h00B4_1999);
        check("T1: qty==100",            order_frame[79:64] == 16'd100);
        check("T1: order_id==0",         order_frame[63:48] == 16'd0);
        check("T1: timestamp==0x002A",   order_frame[47:32] == 16'h002A);
        check32("T1: reserved_lo",        order_frame[31:0], 32'h0);
        check("T1: orders_sent==1",      orders_sent == 32'd1);

        // ── T2: SELL order with auto-incremented ID ─────────────
        $display("\n=== T2: SELL order, order_id=1 ===");
        order_ready = 1'b1;
        @(posedge clk);  // let T1 frame be consumed

        cycle_counter   = 16'h0050;
        approved_valid  = 1'b1;
        approved_side   = 1'b1;  // SELL
        approved_price  = 32'h00B4_0000;  // bid price
        approved_qty    = 16'd50;
        approved_symbol = 8'd3;
        @(posedge clk);
        approved_valid = 1'b0;
        order_ready = 1'b0;  // prevent T2 frame from being consumed
        @(posedge clk);

        check("T2: order_valid",         order_valid == 1'b1);
        check("T2: side==SELL",          order_frame[115] == 1'b1);
        check("T2: symbol==3",           order_frame[123:116] == 8'd3);
        check("T2: order_id==1",         order_frame[63:48] == 16'd1);
        check("T2: timestamp==0x0050",   order_frame[47:32] == 16'h0050);
        check("T2: orders_sent==2",      orders_sent == 32'd2);

        // ── T3: Backpressure — order_ready low ──────────────────
        $display("\n=== T3: Backpressure ===");
        // order_ready is already 0; T2 frame occupies the output

        cycle_counter   = 16'h0060;
        approved_valid  = 1'b1;
        approved_side   = 1'b0;
        approved_price  = 32'h01A4_0000;
        approved_qty    = 16'd200;
        approved_symbol = 8'd1;
        @(posedge clk);
        approved_valid = 1'b0;
        @(posedge clk);

        check("T3: order_valid still high", order_valid == 1'b1);
        check("T3: orders_sent==3",      orders_sent == 32'd3);

        // Release backpressure — held frame should appear
        order_ready = 1'b1;
        @(posedge clk);
        @(posedge clk);
        check("T3b: held frame out",    order_valid == 1'b1);
        check("T3b: symbol==1",         order_frame[123:116] == 8'd1);
        check("T3b: order_id==2",       order_frame[63:48] == 16'd2);

        // ── T4: Clear resets ID and counter ─────────────────────
        $display("\n=== T4: Clear ===");
        order_ready = 1'b1;
        @(posedge clk);

        clear = 1'b1;
        @(posedge clk);
        clear = 1'b0;
        @(posedge clk);

        check("T4: order_valid==0",      order_valid == 1'b0);
        check("T4: orders_sent==0",      orders_sent == 32'd0);

        // Next order should get id=0
        cycle_counter   = 16'h0100;
        approved_valid  = 1'b1;
        approved_side   = 1'b0;
        approved_price  = 32'h00C8_0000;
        approved_qty    = 16'd10;
        approved_symbol = 8'd2;
        @(posedge clk);
        approved_valid = 1'b0;
        @(posedge clk);

        check("T4b: order_id reset to 0", order_frame[63:48] == 16'd0);
        check("T4b: orders_sent==1",      orders_sent == 32'd1);

        // ── T5: No valid → no output ────────────────────────────
        $display("\n=== T5: Idle ===");
        order_ready = 1'b1;
        @(posedge clk);
        @(posedge clk);
        approved_valid = 1'b0;
        repeat (3) @(posedge clk);
        check("T5: no output",            order_valid == 1'b0);

        // ── Summary ─────────────────────────────────────────────
        repeat (3) @(posedge clk);
        $display("\n══════════════════════════════════════════");
        $display("  order_manager testbench complete");
        $display("  PASSED: %0d", pass_count);
        $display("  FAILED: %0d", fail_count);
        $display("══════════════════════════════════════════\n");

        if (fail_count > 0) $fatal(1, "TESTBENCH FAILED");
        $finish;
    end

endmodule
