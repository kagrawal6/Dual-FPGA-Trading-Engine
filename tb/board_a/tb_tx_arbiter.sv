// ============================================================================
// Testbench: tb_tx_arbiter
// Simultaneous fill+quote (fill wins), fill while quote buffered, quote
// starvation, rapid consume+refill, reset, back-to-back quotes, tx_ready
// toggling.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_tx_arbiter;
    logic               clk;
    logic               rst_n;
    logic [FRAME_W-1:0] fill_frame;
    logic               fill_valid;
    logic               fill_ready;
    logic [FRAME_W-1:0] quote_frame;
    logic               quote_valid;
    logic               quote_ready;
    logic [FRAME_W-1:0] tx_frame;
    logic               tx_valid;
    logic               tx_ready;

    int pass_count = 0;
    int fail_count = 0;

    initial clk = 1'b0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 1'b0;
        #100;
        rst_n = 1'b1;
    end

    tx_arbiter dut (
        .clk        (clk),
        .rst_n      (rst_n),
        .fill_frame (fill_frame),
        .fill_valid (fill_valid),
        .fill_ready (fill_ready),
        .quote_frame(quote_frame),
        .quote_valid(quote_valid),
        .quote_ready(quote_ready),
        .tx_frame   (tx_frame),
        .tx_valid   (tx_valid),
        .tx_ready   (tx_ready)
    );

    task automatic check(string msg, logic cond);
        if (cond) pass_count++;
        else begin
            $error("FAIL: %s", msg);
            fail_count++;
        end
    endtask

    task automatic check128(string msg, logic [127:0] actual, logic [127:0] expected);
        if (actual === expected) pass_count++;
        else begin
            $error("FAIL: %s — got %032h, exp %032h", msg, actual, expected);
            fail_count++;
        end
    endtask

    // Consume the current buffered frame
    task automatic consume();
        tx_ready = 1'b1;
        @(posedge clk); #1;
        tx_ready = 1'b0;
    endtask

    initial begin
        logic [FRAME_W-1:0] F1, F2, F3, Q1, Q2, Q3, Q4, Q5;

        $dumpfile("tb_tx_arbiter.vcd");
        $dumpvars(0, tb_tx_arbiter);

        fill_frame  = '0;
        fill_valid  = 1'b0;
        quote_frame = '0;
        quote_valid = 1'b0;
        tx_ready    = 1'b0;

        F1 = {MSG_FILL, 124'h0000_0000_0000_0000_0000_0000_0001};
        F2 = {MSG_FILL, 124'h0000_0000_0000_0000_0000_0000_0002};
        F3 = {MSG_FILL, 124'h0000_0000_0000_0000_0000_0000_0003};
        Q1 = {MSG_QUOTE, 124'h0000_0000_0000_0000_0000_0000_0011};
        Q2 = {MSG_QUOTE, 124'h0000_0000_0000_0000_0000_0000_0022};
        Q3 = {MSG_QUOTE, 124'h0000_0000_0000_0000_0000_0000_0033};
        Q4 = {MSG_QUOTE, 124'h0000_0000_0000_0000_0000_0000_0044};
        Q5 = {MSG_QUOTE, 124'h0000_0000_0000_0000_0000_0000_0055};

        wait (rst_n === 1'b1);
        @(posedge clk); #1;

        // ─────────────────────────────────────────────────────
        // 1) Reset: tx_valid=0
        // ─────────────────────────────────────────────────────
        $display("--- test_reset ---");
        check("reset: tx_valid=0", tx_valid == 1'b0);

        // ─────────────────────────────────────────────────────
        // 2) Simultaneous fill+quote: fill wins
        // ─────────────────────────────────────────────────────
        $display("--- test_fill_priority ---");
        fill_frame  = F1;
        quote_frame = Q1;
        fill_valid  = 1'b1;
        quote_valid = 1'b1;
        tx_ready    = 1'b0;
        #1;
        check("both valid: quote_ready=0", quote_ready == 1'b0);
        check("both valid: not both ready", !(fill_ready && quote_ready));
        @(posedge clk); #1;
        check("fill wins: tx_valid", tx_valid == 1'b1);
        check128("fill wins: frame=F1", tx_frame, F1);

        // While stalled, no new accepts
        fill_frame = F2;
        @(posedge clk); #1;
        check("stalled: fill_ready=0", fill_ready == 1'b0);
        check("stalled: quote_ready=0", quote_ready == 1'b0);
        check128("stalled: frame stable", tx_frame, F1);

        // Consume F1
        consume();
        check("consumed F1: tx_valid=0", tx_valid == 1'b0);

        // Now fill F2 should be accepted (still both valid)
        @(posedge clk); #1;
        check("F2 accepted", tx_valid == 1'b1);
        check128("F2 frame", tx_frame, F2);
        fill_valid = 1'b0;
        consume();

        // Now Q1 should be accepted
        @(posedge clk); #1;
        check("Q1 accepted after fills", tx_valid == 1'b1);
        check128("Q1 frame", tx_frame, Q1);
        quote_valid = 1'b0;
        consume();

        // ─────────────────────────────────────────────────────
        // 3) Quote only path
        // ─────────────────────────────────────────────────────
        $display("--- test_quote_only ---");
        fill_valid  = 1'b0;
        quote_valid = 1'b1;
        quote_frame = Q2;
        tx_ready    = 1'b1;
        @(posedge clk); #1;
        check("quote only: accepted", tx_valid == 1'b1);
        check128("quote only: Q2", tx_frame, Q2);
        @(posedge clk); #1;
        check("quote consumed", tx_valid == 1'b0);
        quote_valid = 1'b0;
        tx_ready = 1'b0;

        // ─────────────────────────────────────────────────────
        // 4) Fill while quote buffered: no preemption
        // ─────────────────────────────────────────────────────
        $display("--- test_no_preempt ---");
        tx_ready    = 1'b0;
        quote_valid = 1'b1;
        quote_frame = Q3;
        fill_valid  = 1'b0;
        @(posedge clk); #1;
        check("Q3 buffered", tx_valid && tx_frame == Q3);

        // Now present fill while Q3 is buffered
        fill_valid = 1'b1;
        fill_frame = F3;
        repeat (3) begin
            @(posedge clk); #1;
            check128("no preempt: still Q3", tx_frame, Q3);
            check("no preempt: no dual ready", !(fill_ready && quote_ready));
        end
        // Consume Q3
        tx_ready = 1'b1;
        @(posedge clk); #1;
        check("Q3 consumed", tx_valid == 1'b0);
        // F3 should be next
        quote_valid = 1'b0;
        @(posedge clk); #1;
        check("F3 accepted", tx_valid == 1'b1);
        check128("F3 frame", tx_frame, F3);
        fill_valid = 1'b0;
        @(posedge clk); #1;
        tx_ready = 1'b0;

        // ─────────────────────────────────────────────────────
        // 5) Quote starvation: 10 continuous fills
        // ─────────────────────────────────────────────────────
        $display("--- test_starvation ---");
        tx_ready = 1'b1;
        quote_valid = 1'b1;
        quote_frame = Q4;
        begin
            int quote_accepted = 0;
            for (int i = 0; i < 10; i++) begin
                fill_frame = {MSG_FILL, 124'(i + 100)};
                fill_valid = 1'b1;
                @(posedge clk); #1;
                if (tx_valid && tx_frame[127:124] == MSG_QUOTE) quote_accepted++;
                @(posedge clk); #1; // consume cycle
            end
            fill_valid = 1'b0;
            check("starvation: quotes starved during fills", quote_accepted == 0);
        end
        // After fills stop, quote should get through
        @(posedge clk); #1;
        @(posedge clk); #1;
        if (tx_valid) begin
            check("starvation: quote gets through after fills", tx_frame[127:124] == MSG_QUOTE);
        end
        quote_valid = 1'b0;
        tx_ready = 1'b0;
        repeat (3) @(posedge clk); #1;

        // ─────────────────────────────────────────────────────
        // 6) Back-to-back quotes
        // ─────────────────────────────────────────────────────
        $display("--- test_back_to_back_quotes ---");
        tx_ready = 1'b1;
        fill_valid = 1'b0;
        for (int i = 0; i < 5; i++) begin
            quote_frame = {MSG_QUOTE, 124'(i + 500)};
            quote_valid = 1'b1;
            @(posedge clk); #1;
            if (tx_valid) begin
                check($sformatf("b2b quote[%0d]: msg_type", i), tx_frame[127:124] == MSG_QUOTE);
            end
            @(posedge clk); #1; // allow bubble
        end
        quote_valid = 1'b0;
        tx_ready = 1'b0;
        repeat (3) @(posedge clk); #1;

        // ─────────────────────────────────────────────────────
        // 7) tx_ready toggling: no data corruption
        // ─────────────────────────────────────────────────────
        $display("--- test_ready_toggling ---");
        quote_frame = Q5;
        quote_valid = 1'b1;
        fill_valid  = 1'b0;
        for (int i = 0; i < 10; i++) begin
            tx_ready = (i % 2 == 0) ? 1'b1 : 1'b0;
            @(posedge clk); #1;
            if (tx_valid)
                check($sformatf("toggle[%0d]: frame ok", i), tx_frame[127:124] == MSG_QUOTE);
        end
        quote_valid = 1'b0;
        tx_ready = 1'b0;

        // ─────────────────────────────────────────────────────
        // 8) Reset: tx_valid deasserts
        // ─────────────────────────────────────────────────────
        $display("--- test_mid_reset ---");
        quote_frame = Q1;
        quote_valid = 1'b1;
        @(posedge clk); #1;
        rst_n = 1'b0;
        repeat (4) @(posedge clk); #1;
        check("mid-reset: tx_valid=0", tx_valid == 1'b0);
        rst_n = 1'b1;
        quote_valid = 1'b0;
        repeat (4) @(posedge clk); #1;

        // ─────────────────────────────────────────────────────
        // Summary
        // ─────────────────────────────────────────────────────
        $display("\n===================================");
        if (fail_count == 0)
            $display("tb_tx_arbiter: PASS (%0d checks passed)", pass_count);
        else begin
            $display("tb_tx_arbiter: FAIL (%0d passed, %0d failed)", pass_count, fail_count);
            $fatal;
        end
        $display("===================================");
        $finish;
    end

endmodule
