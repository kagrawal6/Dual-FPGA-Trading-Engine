// ============================================================================
// Testbench: tb_msg_demux
// Tests the msg_demux module: frame routing by msg_type (QUOTE vs FILL),
// counter behavior (quotes_rcvd, demux_errors), and clear functionality.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_msg_demux;

    logic                     clk;
    logic                     rst_n;
    logic                     clear;
    logic [FRAME_W-1:0]       frame_in;
    logic                     frame_in_valid;
    logic [FRAME_W-1:0]       quote_frame;
    logic                     quote_valid;
    logic [FRAME_W-1:0]       fill_frame;
    logic                     fill_valid;
    logic [COUNTER_W-1:0]     quotes_rcvd;
    logic [COUNTER_W-1:0]     demux_errors;

    initial clk = 0;
    always #5 clk = ~clk;

    int err_count = 0;

    task automatic check(input string name, input logic [31:0] got, input logic [31:0] exp);
        if (got !== exp) begin
            $display("FAIL [%0t] %s: got 0x%08h, expected 0x%08h", $time, name, got, exp);
            err_count++;
        end
    endtask

    // Build a QUOTE frame
    function automatic logic [FRAME_W-1:0] make_quote(
        input symbol_t sym, input price_t bid, input price_t ask,
        input qty_t bsz, input qty_t asz, input logic [15:0] seq
    );
        return {MSG_QUOTE, sym, REGIME_CALM, 2'b00, bid, ask, bsz, asz, seq};
    endfunction

    // Build a FILL frame
    function automatic logic [FRAME_W-1:0] make_fill(
        input symbol_t sym, input logic side, input logic [2:0] status,
        input price_t fill_price, input qty_t fill_qty,
        input order_id_t oid, input timestamp_t ts
    );
        return {MSG_FILL, sym, side, status, fill_price, fill_qty, oid, ts, 32'h0};
    endfunction

    msg_demux dut (.*);

    initial begin
        rst_n = 0; clear = 0; frame_in = '0; frame_in_valid = 0;
        #100; rst_n = 1;
        @(posedge clk); #1;

        // ── Test 1: Send a QUOTE frame ──
        frame_in = make_quote(8'd0, 32'h0096_0000, 32'h0096_8000, 16'd100, 16'd100, 16'd1);
        frame_in_valid = 1;
        @(posedge clk); #1;
        frame_in_valid = 0;
        @(posedge clk); #1;
        check("T1 quote_valid", quote_valid, 1);
        check("T1 fill_valid",  fill_valid,  0);
        check("T1 quotes_rcvd", quotes_rcvd, 1);
        check("T1 demux_errors", demux_errors, 0);
        check("T1 quote_frame[127:124]", quote_frame[127:124], MSG_QUOTE);

        @(posedge clk); #1;

        // ── Test 2: Send a FILL frame ──
        frame_in = make_fill(8'd0, 1'b0, FILL_OK, 32'h0096_8000, 16'd50, 16'd1, 16'hABCD);
        frame_in_valid = 1;
        @(posedge clk); #1;
        frame_in_valid = 0;
        @(posedge clk); #1;
        check("T2 fill_valid",  fill_valid,  1);
        check("T2 quote_valid", quote_valid, 0);
        check("T2 quotes_rcvd", quotes_rcvd, 1);  // unchanged
        check("T2 fill_frame[127:124]", fill_frame[127:124], MSG_FILL);

        @(posedge clk); #1;

        // ── Test 3: Send an invalid frame (msg_type = 4'hF) ──
        frame_in = {4'hF, 124'h0};
        frame_in_valid = 1;
        @(posedge clk); #1;
        frame_in_valid = 0;
        @(posedge clk); #1;
        check("T3 quote_valid", quote_valid, 0);
        check("T3 fill_valid",  fill_valid,  0);
        check("T3 demux_errors", demux_errors, 1);

        @(posedge clk); #1;

        // ── Test 4: Send ORDER frame (msg_type=4'h2) — should be an error on Board B ──
        frame_in = {MSG_ORDER, 124'h0};
        frame_in_valid = 1;
        @(posedge clk); #1;
        frame_in_valid = 0;
        @(posedge clk); #1;
        check("T4 demux_errors", demux_errors, 2);

        @(posedge clk); #1;

        // ── Test 5: Multiple QUOTEs back-to-back ──
        for (int i = 0; i < 5; i++) begin
            frame_in = make_quote(i[7:0], 32'h0064_0000 + i * 32'h10000,
                                  32'h0064_8000 + i * 32'h10000, 16'd200, 16'd200, i[15:0]);
            frame_in_valid = 1;
            @(posedge clk); #1;
        end
        frame_in_valid = 0;
        @(posedge clk); #1;
        check("T5 quotes_rcvd", quotes_rcvd, 6); // 1 from T1 + 5 here

        // ── Test 6: Clear resets counters ──
        clear = 1;
        @(posedge clk); #1;
        clear = 0;
        @(posedge clk); #1;
        check("T6 quotes_rcvd", quotes_rcvd, 0);
        check("T6 demux_errors", demux_errors, 0);

        // ── Test 7: Frames after clear ──
        frame_in = make_quote(8'd2, 32'h00C8_0000, 32'h00C8_4000, 16'd50, 16'd50, 16'd0);
        frame_in_valid = 1;
        @(posedge clk); #1;
        frame_in_valid = 0;
        @(posedge clk); #1;
        check("T7 quotes_rcvd", quotes_rcvd, 1);

        repeat (5) @(posedge clk);

        if (err_count == 0)
            $display("tb_msg_demux: PASS");
        else
            $display("tb_msg_demux: FAIL (%0d errors)", err_count);
        $finish;
    end

endmodule
