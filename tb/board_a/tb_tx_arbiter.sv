// ============================================================================
// Testbench: tb_tx_arbiter
// Verifies minimal Board A arbiter contract:
// - strict priority: fill > quote
// - deterministic one-frame output behavior
// - no dual-ready assertion
// - downstream backpressure does not corrupt or drop selected frame
// ============================================================================

// -----------------------------------------------------------------------------
// Future complexity / upgrade ideas for tx_arbiter
//
// Current version is intentionally minimal:
//   - strict priority: fill > quote
//   - one-entry output buffer
//   - no dropped frame under backpressure
//   - no fairness logic
//   - one-cycle bubble between consume and next accept is acceptable
//
// Ways this file could become more complex in the future:
//
// 1) Quote starvation prevention
//    - Right now, continuous fill traffic can starve quotes forever.
//    - Future version could add fairness or weighted scheduling so quotes
//      still get occasional service under heavy fill load.
//
// 2) Same-cycle consume + refill
//    - Current arbiter inserts a bubble after tx_ready consumes a frame.
//    - Future version could support refill in the same cycle for higher
//      throughput, but logic becomes trickier.
//
// 3) More message classes
//    - Right now there are only two inputs: fill and quote.
//    - Future versions could arbitrate among fills, rejects, quotes,
//      control/status frames, telemetry, etc.
//
// 4) Weighted / policy-based scheduling
//    - Instead of fixed priority, future logic could support round-robin,
//      weighted priority, or configurable QoS rules.
//
// 5) Input-side buffering
//    - Current design assumes producers hold valid correctly until accepted.
//    - Future version could add FIFOs on fill/quote inputs for burst absorption.
//
// 6) Burst-aware arbitration
//    - Could choose to drain several fills before returning to quotes, or vice
//      versa, depending on system goals.
//
// 7) Runtime-configurable arbitration policy
//    - Priority mode could later become software-configurable via AXI-Lite
//      registers instead of hardcoded fill > quote.
//
// Keep current version simple for the original demo. Only add these if needed
// after the baseline system is fully stable.
// -----------------------------------------------------------------------------

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

    int err_count = 0;

    task automatic check(input string msg, input logic cond);
        if (!cond) begin
            $error("FAIL: %s", msg);
            err_count++;
        end
    endtask

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

    initial begin
        $dumpfile("tb_tx_arbiter.vcd");
        $dumpvars(0, tb_tx_arbiter);
    end

    initial begin
        logic [FRAME_W-1:0] F1, F2, Q1, Q2;

        fill_frame  = '0;
        fill_valid  = 1'b0;
        quote_frame = '0;
        quote_valid = 1'b0;
        tx_ready    = 1'b0;

        F1 = {MSG_FILL, 124'h0000_0000_0000_0000_0000_0000_0001};
        F2 = {MSG_FILL, 124'h0000_0000_0000_0000_0000_0000_0002};
        Q1 = {MSG_QUOTE,124'h0000_0000_0000_0000_0000_0000_0011};
        Q2 = {MSG_QUOTE,124'h0000_0000_0000_0000_0000_0000_0022};

        wait (rst_n === 1'b1);
        @(posedge clk);

        // 1) Strict priority and no-dual-ready when both request.
        fill_frame  = F1;
        quote_frame = Q1;
        fill_valid  = 1'b1;
        quote_valid = 1'b1;
        tx_ready    = 1'b0;
        #1;
        check("both valid -> quote_ready low (strict priority)", quote_ready === 1'b0);
        check("both valid -> not both ready high", !(fill_ready && quote_ready));
        @(posedge clk);
        check("selected frame is fill", tx_valid && tx_frame == F1);

        // Once buffered, no new accepts while stalled.
        fill_frame = F2;
        @(posedge clk);
        check("while stalled, fill_ready low", fill_ready === 1'b0);
        check("while stalled, quote_ready low", quote_ready === 1'b0);
        check("stalled output remains stable", tx_valid && tx_frame == F1);

        // 2) Consume first frame; one-cycle bubble is acceptable in this minimal arbiter.
        tx_ready = 1'b1;
        @(posedge clk);
        check("consumed frame deasserts tx_valid", tx_valid === 1'b0);

        // 3) Quote only path.
        fill_valid  = 1'b0;
        quote_valid = 1'b1;
        quote_frame = Q2;
        tx_ready    = 1'b1;
        @(posedge clk);
        check("quote accepted when no fill", tx_valid && tx_frame == Q2);
        @(posedge clk);
        check("quote consumed", tx_valid === 1'b0);

        // 4) No corruption under backpressure:
        // buffer quote while tx_ready=0, then keep stable even when fill appears.
        tx_ready    = 1'b0;
        quote_valid = 1'b1;
        quote_frame = Q1;
        fill_valid  = 1'b0;
        @(posedge clk);
        check("quote buffered with tx stall", tx_valid && tx_frame == Q1);

        fill_valid = 1'b1;
        fill_frame = F2;
        repeat (3) begin
            @(posedge clk);
            check("held frame remains quote (no preempt mid-hold)", tx_valid && tx_frame == Q1);
            check("no dual ready while full", !(fill_ready && quote_ready));
        end
        tx_ready = 1'b1;
        @(posedge clk);
        check("held quote consumed first", tx_valid === 1'b0);

        // Fill can be accepted afterward.
        @(posedge clk);
        check("fill accepted after buffer frees", tx_valid && tx_frame == F2);

        if (err_count == 0)
            $display("tb_tx_arbiter: PASS (all checks passed)");
        else
            $display("tb_tx_arbiter: FAIL (%0d errors)", err_count);

        $finish;
    end
endmodule
