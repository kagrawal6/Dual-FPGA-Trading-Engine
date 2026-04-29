// ============================================================================
// Testbench: tb_order_manager
// Tests the order_manager module: ORDER frame packing, auto-incrementing
// order_id, timestamp capture, backpressure handling (held frame + new order
// simultaneous arrival), rapid burst, order ID wrap-around, and clear.
//
// Critical regression: simultaneous held-release + new order — verifies the
// 3-branch priority fix that prevents silent order drops.
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

    task automatic approve_order(
        input logic       side,
        input price_t     price,
        input qty_t       qty,
        input symbol_t    sym,
        input timestamp_t ts
    );
        cycle_counter   = ts;
        approved_valid  = 1'b1;
        approved_side   = side;
        approved_price  = price;
        approved_qty    = qty;
        approved_symbol = sym;
        @(posedge clk); #1;
        approved_valid = 1'b0;
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
        repeat (2) @(posedge clk); #1;

        // ── T1: Basic BUY order packing ───────────────────────
        $display("\n=== T1: BUY order frame packing ===");
        approve_order(1'b0, 32'h00B4_1999, 16'd100, 8'd0, 16'h002A);
        // FIX: order_manager is 1-cycle registered. After approve_order's
        // edge, order_valid is high. With order_ready=1 (default), the next
        // clock edge would CONSUME it (order_valid<=0). Check immediately.

        check("T1: order_valid",         order_valid == 1'b1);
        check("T1: msg_type==ORDER",     order_frame[127:124] == MSG_ORDER);
        check("T1: symbol==0",           order_frame[123:116] == 8'd0);
        check("T1: side==BUY",           order_frame[115] == 1'b0);
        check("T1: reserved==000",       order_frame[114:112] == 3'b000);
        check32("T1: price",             order_frame[111:80], 32'h00B4_1999);
        check("T1: qty==100",            order_frame[79:64] == 16'd100);
        check("T1: order_id==0",         order_frame[63:48] == 16'd0);
        check("T1: timestamp==0x002A",   order_frame[47:32] == 16'h002A);
        check32("T1: reserved_lo",       order_frame[31:0], 32'h0);
        check("T1: orders_sent==1",      orders_sent == 32'd1);

        // ── T2: SELL order with auto-incremented ID ───────────
        $display("\n=== T2: SELL order, order_id=1 ===");
        order_ready = 1'b1;
        @(posedge clk); #1;

        approve_order(1'b1, 32'h00B4_0000, 16'd50, 8'd3, 16'h0050);
        order_ready = 1'b0;
        @(posedge clk); #1;

        check("T2: order_valid",         order_valid == 1'b1);
        check("T2: side==SELL",          order_frame[115] == 1'b1);
        check("T2: symbol==3",           order_frame[123:116] == 8'd3);
        check("T2: order_id==1",         order_frame[63:48] == 16'd1);
        check("T2: orders_sent==2",      orders_sent == 32'd2);

        // ── T3: Backpressure — new order goes to holding ──────
        $display("\n=== T3: Backpressure ===");
        approve_order(1'b0, 32'h01A4_0000, 16'd200, 8'd1, 16'h0060);
        @(posedge clk); #1;

        check("T3: order_valid still",   order_valid == 1'b1);
        check("T3: orders_sent==3",      orders_sent == 32'd3);
        check("T3: holding==1",          dut.holding == 1'b1);

        // Release backpressure → held frame appears
        // FIX: one edge moves held → output. A second edge would consume the
        // freshly placed frame (order_ready stays 1), so check after one edge.
        order_ready = 1'b1;
        @(posedge clk); #1;
        check("T3b: held frame out",     order_valid == 1'b1);
        check("T3b: symbol==1",          order_frame[123:116] == 8'd1);
        check("T3b: order_id==2",        order_frame[63:48] == 16'd2);

        // ──────────────────────────────────────────────────────
        // T4: CRITICAL REGRESSION — Simultaneous held-release + new order
        // When output is occupied, held is occupied, and order_ready goes
        // high same cycle as a new approved_valid:
        //   - held frame should move to output
        //   - new order should go to holding register
        // ──────────────────────────────────────────────────────
        $display("\n=== T4: Simultaneous held-release + new order ===");
        order_ready = 1'b1;
        @(posedge clk); #1;
        @(posedge clk); #1;

        // Fill output with order A
        approve_order(1'b0, 32'h00640000, 16'd10, 8'd0, 16'h0100);
        order_ready = 1'b0;
        @(posedge clk); #1;
        check("T4-setup-A: valid",       order_valid == 1'b1);

        // Send order B → goes to holding
        approve_order(1'b1, 32'h00C80000, 16'd20, 8'd1, 16'h0110);
        @(posedge clk); #1;
        check("T4-setup-B: holding",     dut.holding == 1'b1);
        check("T4-setup-B: orders==5",   orders_sent == 32'd5);

        // Now: output=A, held=B. Release backpressure AND send new order C simultaneously
        order_ready    = 1'b1;
        approved_valid = 1'b1;
        approved_side  = 1'b0;
        approved_price = 32'h012C0000;
        approved_qty   = 16'd30;
        approved_symbol = 8'd2;
        cycle_counter  = 16'h0120;
        @(posedge clk); #1;
        approved_valid = 1'b0;

        // FIX: After this single edge: held B has been promoted to output and
        // new C has been latched into holding. A second edge with order_ready
        // still high would already consume B and pull C out, so check NOW.
        check("T4: B now in output",     order_valid == 1'b1);
        check("T4: B symbol==1",         order_frame[123:116] == 8'd1);
        check("T4: C in holding",        dut.holding == 1'b1);
        check("T4: orders_sent==6",      orders_sent == 32'd6);

        // Consume B → C should appear
        @(posedge clk); #1;
        check("T4b: C now out",          order_valid == 1'b1);
        check("T4b: C symbol==2",        order_frame[123:116] == 8'd2);
        check("T4b: holding cleared",    dut.holding == 1'b0);

        // ──────────────────────────────────────────────────────
        // T5: Rapid 3-order burst with backpressure
        // ──────────────────────────────────────────────────────
        $display("\n=== T5: Rapid 3-order burst ===");
        order_ready = 1'b1;
        @(posedge clk); #1;
        @(posedge clk); #1;

        // Ensure clean state
        order_ready = 1'b0;

        // Send 3 orders on consecutive cycles
        approve_order(1'b0, 32'h00640000, 16'd10, 8'd0, 16'h0200);
        approve_order(1'b1, 32'h00C80000, 16'd20, 8'd1, 16'h0201);
        approve_order(1'b0, 32'h012C0000, 16'd30, 8'd2, 16'h0202);
        @(posedge clk); #1;

        // First 2 should be captured (output + held), third may be dropped
        check("T5: output occupied",     order_valid == 1'b1);

        // Release and drain
        order_ready = 1'b1;
        repeat (4) @(posedge clk); #1;

        // ──────────────────────────────────────────────────────
        // T6: Clear resets ID and counter
        // ──────────────────────────────────────────────────────
        $display("\n=== T6: Clear ===");
        order_ready = 1'b1;
        repeat (3) @(posedge clk); #1;

        clear = 1'b1;
        @(posedge clk); #1;
        clear = 1'b0;
        @(posedge clk); #1;

        check("T6: order_valid==0",      order_valid == 1'b0);
        check("T6: orders_sent==0",      orders_sent == 32'd0);
        check("T6: holding==0",          dut.holding == 1'b0);

        // Next order should get id=0
        approve_order(1'b0, 32'h00C8_0000, 16'd10, 8'd2, 16'h0300);
        @(posedge clk); #1;
        check("T6b: order_id reset",     order_frame[63:48] == 16'd0);
        check("T6b: orders_sent==1",     orders_sent == 32'd1);

        // ──────────────────────────────────────────────────────
        // T7: Order ID wrap-around (16-bit)
        // ──────────────────────────────────────────────────────
        $display("\n=== T7: Order ID wrap-around ===");
        clear = 1'b1;
        @(posedge clk); #1;
        clear = 1'b0;
        @(posedge clk); #1;

        // Force next_order_id near the wrap point
        force dut.next_order_id = 16'hFFFE;
        @(posedge clk); #1;
        release dut.next_order_id;

        approve_order(1'b0, 32'h00640000, 16'd10, 8'd0, 16'h0400);
        @(posedge clk); #1;
        check("T7a: id=0xFFFE",          order_frame[63:48] == 16'hFFFE);

        approve_order(1'b0, 32'h00640000, 16'd10, 8'd0, 16'h0401);
        @(posedge clk); #1;
        check("T7b: id=0xFFFF",          order_frame[63:48] == 16'hFFFF);

        approve_order(1'b0, 32'h00640000, 16'd10, 8'd0, 16'h0402);
        @(posedge clk); #1;
        check("T7c: id wraps to 0",      order_frame[63:48] == 16'h0000);

        // ── T8: No valid → no output ──────────────────────────
        $display("\n=== T8: Idle ===");
        order_ready = 1'b1;
        @(posedge clk); #1;
        @(posedge clk); #1;
        approved_valid = 1'b0;
        repeat (3) @(posedge clk); #1;
        check("T8: no output",           order_valid == 1'b0);

        // ── Summary ───────────────────────────────────────────
        repeat (3) @(posedge clk); #1;
        $display("\n══════════════════════════════════════════");
        $display("  order_manager testbench complete");
        $display("  PASSED: %0d", pass_count);
        $display("  FAILED: %0d", fail_count);
        $display("══════════════════════════════════════════\n");

        if (fail_count > 0) $fatal(1, "TESTBENCH FAILED");
        $finish;
    end

endmodule
