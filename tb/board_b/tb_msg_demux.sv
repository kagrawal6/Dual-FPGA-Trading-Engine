// ============================================================================
// Testbench: tb_msg_demux
// Tests the msg_demux module: frame routing by msg_type field [127:124].
// Verifies QUOTE routing, FILL routing, unknown type rejection, counter
// accuracy, clear functionality, and back-to-back frame handling.
//
// Golden model reference: board_b.py BoardB.step() performs the same
// msg_type dispatch — QUOTE frames go to _handle_quote, FILL frames to
// _handle_fill, unknown frames are silently discarded.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_msg_demux;

    logic                 clk;
    logic                 rst_n;
    logic                 clear;
    logic [FRAME_W-1:0]   frame_in;
    logic                 frame_in_valid;
    logic [FRAME_W-1:0]   quote_frame;
    logic                 quote_valid;
    logic [FRAME_W-1:0]   fill_frame;
    logic                 fill_valid;
    logic [COUNTER_W-1:0] quotes_rcvd;
    logic [COUNTER_W-1:0] demux_errors;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    msg_demux dut (
        .clk            (clk),
        .rst_n          (rst_n),
        .clear          (clear),
        .frame_in       (frame_in),
        .frame_in_valid (frame_in_valid),
        .quote_frame    (quote_frame),
        .quote_valid    (quote_valid),
        .fill_frame     (fill_frame),
        .fill_valid     (fill_valid),
        .quotes_rcvd    (quotes_rcvd),
        .demux_errors   (demux_errors)
    );

    // ── Helper: build a QUOTE frame ─────────────────────────────────────────
    function automatic logic [FRAME_W-1:0] make_quote(
        input logic [7:0]  symbol,
        input logic [1:0]  regime,
        input logic [31:0] bid,
        input logic [31:0] ask,
        input logic [15:0] bid_sz,
        input logic [15:0] ask_sz,
        input logic [15:0] seq
    );
        make_quote = {MSG_QUOTE, symbol, regime, 2'b00, bid, ask, bid_sz, ask_sz, seq};
    endfunction

    // ── Helper: build a FILL frame ──────────────────────────────────────────
    function automatic logic [FRAME_W-1:0] make_fill(
        input logic [7:0]  symbol,
        input logic        side,
        input logic [2:0]  status,
        input logic [31:0] price,
        input logic [15:0] qty,
        input logic [15:0] order_id,
        input logic [15:0] ts_echo
    );
        make_fill = {MSG_FILL, symbol, side, status, price, qty, order_id, ts_echo, 32'h0};
    endfunction

    // ── Helper: build a frame with arbitrary msg_type ───────────────────────
    function automatic logic [FRAME_W-1:0] make_raw(input logic [3:0] mtype);
        make_raw = {mtype, 124'hDEAD_BEEF_CAFE_1234_5678_9ABC_DEF0_1};
    endfunction

    // ── Check task ──────────────────────────────────────────────────────────
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

    // ── Test sequence ───────────────────────────────────────────────────────
    logic [FRAME_W-1:0] expected_quote;
    logic [FRAME_W-1:0] expected_fill;

    initial begin
        frame_in       = '0;
        frame_in_valid = 1'b0;
        clear          = 1'b0;

        @(posedge rst_n);
        repeat (2) @(posedge clk);

        // ────────────────────────────────────────────────────────────────
        // TEST 1: Single QUOTE frame routing
        // ────────────────────────────────────────────────────────────────
        $display("\n=== TEST 1: Single QUOTE frame ===");
        expected_quote = make_quote(8'd5, REGIME_CALM, 32'h00B4_0000, 32'h00B4_8000,
                                    16'd1000, 16'd1000, 16'd0);
        frame_in       = expected_quote;
        frame_in_valid = 1'b1;
        @(posedge clk);
        frame_in_valid = 1'b0;
        @(posedge clk);

        check("T1: quote_valid asserted",   quote_valid == 1'b1);
        check("T1: fill_valid deasserted",   fill_valid == 1'b0);
        check("T1: quote_frame matches",     quote_frame == expected_quote);
        check("T1: quotes_rcvd == 1",        quotes_rcvd == 32'd1);
        check("T1: demux_errors == 0",       demux_errors == 32'd0);

        @(posedge clk);
        check("T1: quote_valid deasserts",   quote_valid == 1'b0);

        // ────────────────────────────────────────────────────────────────
        // TEST 2: Single FILL frame routing
        // ────────────────────────────────────────────────────────────────
        $display("\n=== TEST 2: Single FILL frame ===");
        expected_fill = make_fill(8'd3, 1'b0, 3'b000, 32'h00B4_0000,
                                  16'd100, 16'd1, 16'hA5A5);
        frame_in       = expected_fill;
        frame_in_valid = 1'b1;
        @(posedge clk);
        frame_in_valid = 1'b0;
        @(posedge clk);

        check("T2: fill_valid asserted",     fill_valid == 1'b1);
        check("T2: quote_valid deasserted",  quote_valid == 1'b0);
        check("T2: fill_frame matches",      fill_frame == expected_fill);
        check("T2: quotes_rcvd unchanged",   quotes_rcvd == 32'd1);
        check("T2: demux_errors == 0",       demux_errors == 32'd0);

        @(posedge clk);
        check("T2: fill_valid deasserts",    fill_valid == 1'b0);

        // ────────────────────────────────────────────────────────────────
        // TEST 3: Unknown msg_type → error counter
        // ────────────────────────────────────────────────────────────────
        $display("\n=== TEST 3: Unknown msg_type ===");
        frame_in       = make_raw(4'h0);
        frame_in_valid = 1'b1;
        @(posedge clk);
        frame_in_valid = 1'b0;
        @(posedge clk);

        check("T3: quote_valid == 0",        quote_valid == 1'b0);
        check("T3: fill_valid == 0",         fill_valid == 1'b0);
        check("T3: demux_errors == 1",       demux_errors == 32'd1);

        // Try another unknown type (MSG_ORDER = 4'h2 should NOT be routed on Board B)
        frame_in       = make_raw(4'h2);
        frame_in_valid = 1'b1;
        @(posedge clk);
        frame_in_valid = 1'b0;
        @(posedge clk);

        check("T3b: ORDER on Board B → error", demux_errors == 32'd2);
        check("T3b: quote_valid == 0",       quote_valid == 1'b0);
        check("T3b: fill_valid == 0",        fill_valid == 1'b0);

        // More invalid types: 4'h4..4'hF
        for (int mt = 4; mt < 16; mt++) begin
            frame_in       = make_raw(4'(mt));
            frame_in_valid = 1'b1;
            @(posedge clk);
            frame_in_valid = 1'b0;
            @(posedge clk);
        end
        check("T3c: all invalid types counted", demux_errors == 32'd14);

        // ────────────────────────────────────────────────────────────────
        // TEST 4: Back-to-back QUOTE frames (no idle gap)
        // ────────────────────────────────────────────────────────────────
        $display("\n=== TEST 4: Back-to-back QUOTEs ===");
        begin
            logic [FRAME_W-1:0] q0, q1, q2;
            q0 = make_quote(8'd0, REGIME_CALM,     32'h0064_0000, 32'h0064_8000, 16'd500, 16'd500, 16'd10);
            q1 = make_quote(8'd1, REGIME_VOLATILE,  32'h00C8_0000, 32'h00C8_4000, 16'd200, 16'd200, 16'd11);
            q2 = make_quote(8'd2, REGIME_BURST,     32'h012C_0000, 32'h012C_2000, 16'd300, 16'd300, 16'd12);

            // Send 3 consecutive frames with no gap
            frame_in       = q0;
            frame_in_valid = 1'b1;
            @(posedge clk);

            frame_in = q1;
            @(posedge clk);
            check("T4: q0 routed",           quote_valid == 1'b1);
            check("T4: q0 frame",            quote_frame == q0);

            frame_in = q2;
            @(posedge clk);
            check("T4: q1 routed",           quote_valid == 1'b1);
            check("T4: q1 frame",            quote_frame == q1);

            frame_in_valid = 1'b0;
            @(posedge clk);
            check("T4: q2 routed",           quote_valid == 1'b1);
            check("T4: q2 frame",            quote_frame == q2);

            @(posedge clk);
            check("T4: valid deasserts",     quote_valid == 1'b0);
            // 1 (T1) + 3 (T4) = 4 total quotes
            check("T4: quotes_rcvd == 4",    quotes_rcvd == 32'd4);
        end

        // ────────────────────────────────────────────────────────────────
        // TEST 5: Interleaved QUOTE and FILL
        // ────────────────────────────────────────────────────────────────
        $display("\n=== TEST 5: Interleaved QUOTE/FILL ===");
        begin
            logic [FRAME_W-1:0] q, f;
            q = make_quote(8'd7, REGIME_ADVERSARIAL, 32'h01F4_0000, 32'h01F4_C000,
                           16'd100, 16'd100, 16'd20);
            f = make_fill(8'd7, 1'b1, 3'b000, 32'h01F4_0000, 16'd100, 16'd5, 16'h1234);

            frame_in       = q;
            frame_in_valid = 1'b1;
            @(posedge clk);

            frame_in = f;
            @(posedge clk);
            check("T5: quote routed",        quote_valid == 1'b1);
            check("T5: fill not yet",        fill_valid == 1'b0);
            check("T5: quote_frame",         quote_frame == q);

            frame_in_valid = 1'b0;
            @(posedge clk);
            check("T5: fill routed",         fill_valid == 1'b1);
            check("T5: quote deasserted",    quote_valid == 1'b0);
            check("T5: fill_frame",          fill_frame == f);
        end

        // ────────────────────────────────────────────────────────────────
        // TEST 6: Clear resets counters but not outputs
        // ────────────────────────────────────────────────────────────────
        $display("\n=== TEST 6: Counter clear ===");
        @(posedge clk);
        check("T6: pre-clear quotes_rcvd > 0", quotes_rcvd > 0);
        check("T6: pre-clear errors > 0",      demux_errors > 0);

        clear = 1'b1;
        @(posedge clk);
        clear = 1'b0;
        @(posedge clk);

        check("T6: quotes_rcvd cleared",    quotes_rcvd == 32'd0);
        check("T6: demux_errors cleared",   demux_errors == 32'd0);
        check("T6: quote_valid == 0",       quote_valid == 1'b0);
        check("T6: fill_valid == 0",        fill_valid == 1'b0);

        // ────────────────────────────────────────────────────────────────
        // TEST 7: No valid input → no output
        // ────────────────────────────────────────────────────────────────
        $display("\n=== TEST 7: Idle (no valid) ===");
        frame_in       = make_quote(8'd0, REGIME_CALM, 32'h1000_0000, 32'h1000_8000,
                                    16'd100, 16'd100, 16'd99);
        frame_in_valid = 1'b0;
        @(posedge clk);
        @(posedge clk);
        check("T7: no quote_valid",         quote_valid == 1'b0);
        check("T7: no fill_valid",          fill_valid == 1'b0);
        check("T7: quotes_rcvd == 0",       quotes_rcvd == 32'd0);

        // ────────────────────────────────────────────────────────────────
        // TEST 8: FILL with REJECTED status (still routes to fill path)
        // ────────────────────────────────────────────────────────────────
        $display("\n=== TEST 8: Rejected FILL routing ===");
        expected_fill = make_fill(8'd2, 1'b0, 3'b001, 32'h0, 16'd0, 16'd42, 16'hBEEF);
        frame_in       = expected_fill;
        frame_in_valid = 1'b1;
        @(posedge clk);
        frame_in_valid = 1'b0;
        @(posedge clk);

        check("T8: fill_valid asserted",    fill_valid == 1'b1);
        check("T8: fill_frame matches",     fill_frame == expected_fill);
        check("T8: quote_valid == 0",       quote_valid == 1'b0);

        // ────────────────────────────────────────────────────────────────
        // TEST 9: Golden model cross-reference frames
        // ────────────────────────────────────────────────────────────────
        $display("\n=== TEST 9: Golden model reference frames ===");
        begin
            logic [FRAME_W-1:0] gm_quote, gm_fill;

            gm_quote = 128'h100000B3F81E00B4081E03E803E80000;
            frame_in       = gm_quote;
            frame_in_valid = 1'b1;
            @(posedge clk);
            frame_in_valid = 1'b0;
            @(posedge clk);
            check("T9a: GM quote routed",    quote_valid == 1'b1);
            check("T9a: GM quote frame",     quote_frame == gm_quote);
            check("T9a: GM symbol==0",       quote_frame[123:116] == 8'd0);
            check("T9a: GM regime==CALM",    quote_frame[115:114] == 2'b00);

            gm_quote = 128'h101001A3F82101A4082103E803E80000;
            frame_in       = gm_quote;
            frame_in_valid = 1'b1;
            @(posedge clk);
            frame_in_valid = 1'b0;
            @(posedge clk);
            check("T9b: GM sym1 routed",     quote_valid == 1'b1);
            check("T9b: GM sym1 frame",      quote_frame == gm_quote);

            gm_quote = 128'h10200383F8160384081603E803E80000;
            frame_in       = gm_quote;
            frame_in_valid = 1'b1;
            @(posedge clk);
            frame_in_valid = 1'b0;
            @(posedge clk);
            check("T9c: GM sym2 routed",     quote_valid == 1'b1);
            check("T9c: GM sym2 frame",      quote_frame == gm_quote);

            gm_fill = 128'h300000B4081500640001002A00000000;
            frame_in       = gm_fill;
            frame_in_valid = 1'b1;
            @(posedge clk);
            frame_in_valid = 1'b0;
            @(posedge clk);
            check("T9d: GM fill routed",     fill_valid == 1'b1);
            check("T9d: GM fill frame",      fill_frame == gm_fill);
            check("T9d: GM fill sym==0",     fill_frame[123:116] == 8'd0);
            check("T9d: GM fill side==BUY",  fill_frame[115] == 1'b0);
            check("T9d: GM fill FILLED",     fill_frame[114:112] == 3'b000);

            frame_in       = 128'h00000000DEADBEEFCAFE1234567890AB;
            frame_in_valid = 1'b1;
            @(posedge clk);
            frame_in_valid = 1'b0;
            @(posedge clk);
            check("T9e: GM invalid→error",   quote_valid == 1'b0 && fill_valid == 1'b0);
        end

        // ────────────────────────────────────────────────────────────────
        // TEST 10: 10-frame back-to-back QUOTE stress
        // ────────────────────────────────────────────────────────────────
        $display("\n=== TEST 10: 10-frame back-to-back stress ===");
        begin
            clear = 1'b1;
            @(posedge clk);
            clear = 1'b0;
            @(posedge clk);

            for (int i = 0; i < 10; i++) begin
                frame_in = make_quote(8'(i % 4), REGIME_CALM,
                    32'h00640000 + 32'(i * 32'h1000),
                    32'h00648000 + 32'(i * 32'h1000),
                    16'd100, 16'd100, 16'(i));
                frame_in_valid = 1'b1;
                @(posedge clk);
            end
            frame_in_valid = 1'b0;

            // Wait for pipeline to drain
            repeat (2) @(posedge clk);
            check("T10: quotes_rcvd==10", quotes_rcvd == 32'd10);
            check("T10: no errors",       demux_errors == 32'd0);
        end

        // ────────────────────────────────────────────────────────────────
        // TEST 11: Clear pulse resets counters, no stale output
        // ────────────────────────────────────────────────────────────────
        $display("\n=== TEST 11: Clear mid-stream ===");
        begin
            // Send a quote first
            frame_in = make_quote(8'd0, REGIME_CALM, 32'h00640000, 32'h00648000,
                                  16'd100, 16'd100, 16'd99);
            frame_in_valid = 1'b1;
            @(posedge clk);
            frame_in_valid = 1'b0;
            @(posedge clk);

            check("T11a: quotes > 0",    quotes_rcvd > 0);

            clear = 1'b1;
            @(posedge clk);
            clear = 1'b0;
            @(posedge clk);

            check("T11b: counters reset", quotes_rcvd == 32'd0);
            check("T11b: errors reset",   demux_errors == 32'd0);
            check("T11b: no stale quote", quote_valid == 1'b0);
            check("T11b: no stale fill",  fill_valid == 1'b0);
        end

        // ────────────────────────────────────────────────────────────────
        // TEST 12: Alternating QUOTE-FILL-QUOTE-FILL back-to-back
        // ────────────────────────────────────────────────────────────────
        $display("\n=== TEST 12: Alternating QUOTE/FILL burst ===");
        begin
            logic [FRAME_W-1:0] qf [0:3];
            qf[0] = make_quote(8'd0, REGIME_CALM, 32'h00640000, 32'h00648000, 16'd100, 16'd100, 16'd30);
            qf[1] = make_fill(8'd0, 1'b0, 3'b000, 32'h00640000, 16'd50, 16'd1, 16'h0010);
            qf[2] = make_quote(8'd1, REGIME_VOLATILE, 32'h00C80000, 32'h00C88000, 16'd200, 16'd200, 16'd31);
            qf[3] = make_fill(8'd1, 1'b1, 3'b000, 32'h00C80000, 16'd100, 16'd2, 16'h0020);

            frame_in = qf[0];
            frame_in_valid = 1'b1;
            @(posedge clk);
            #1;
            frame_in = qf[1];
            check("T12a: quote first",    quote_valid == 1'b1);
            @(posedge clk);
            #1;
            frame_in = qf[2];
            check("T12b: fill second",    fill_valid == 1'b1);
            @(posedge clk);
            #1;
            frame_in = qf[3];
            check("T12c: quote third",    quote_valid == 1'b1);
            @(posedge clk);
            #1;
            frame_in_valid = 1'b0;
            check("T12d: fill fourth",    fill_valid == 1'b1);
        end

        // ────────────────────────────────────────────────────────────────
        // SUMMARY
        // ────────────────────────────────────────────────────────────────
        repeat (3) @(posedge clk);
        $display("\n══════════════════════════════════════════");
        $display("  msg_demux testbench complete");
        $display("  PASSED: %0d", pass_count);
        $display("  FAILED: %0d", fail_count);
        $display("══════════════════════════════════════════\n");

        if (fail_count > 0) $fatal(1, "TESTBENCH FAILED");
        $finish;
    end

endmodule
