// ============================================================================
// Testbench: tb_link_rx
// link_up deassertion on error/counter_clr, recovery, invalid msg_type,
// back-to-back frames, local_ready behavior.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_link_rx;

    logic                  clk;
    logic                  rst_n;
    logic                  counter_clr;
    logic [3:0]            pmod_data;
    logic                  pmod_valid;
    logic                  local_ready;
    logic [127:0]          frame_out;
    logic                  frame_out_valid;
    logic                  link_up;
    logic [31:0]           error_count;

    int pass_count = 0;
    int fail_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    link_rx #(.FRAME_W(128), .DATA_W(4)) dut (
        .clk             (clk),
        .rst_n           (rst_n),
        .counter_clr     (counter_clr),
        .pmod_data       (pmod_data),
        .pmod_valid      (pmod_valid),
        .local_ready     (local_ready),
        .frame_out       (frame_out),
        .frame_out_valid (frame_out_valid),
        .link_up         (link_up),
        .error_count     (error_count)
    );

    localparam int FRAME_W = 128;
    localparam int DATA_W  = 4;
    localparam int BEATS   = FRAME_W / DATA_W;

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

    function automatic logic [DATA_W-1:0] nibble_at(input logic [FRAME_W-1:0] frame, input int i);
        nibble_at = frame[FRAME_W-1 - (i*DATA_W) -: DATA_W];
    endfunction

    // Drive a complete frame (2 clk per nibble), with optional truncation
    task automatic send_frame(
        input logic [FRAME_W-1:0] frame,
        input int beats_to_send,
        input int pad_after
    );
        pmod_valid = 1'b0;
        pmod_data  = '0;
        @(posedge clk);

        for (int i = 0; i < beats_to_send; i++) begin
            pmod_data  = nibble_at(frame, i);
            pmod_valid = 1'b1;
            @(posedge clk);
            @(posedge clk);
        end

        if (pad_after > 0)
            repeat (pad_after) @(posedge clk);

        pmod_valid = 1'b0;
        pmod_data  = '0;
        @(posedge clk);
    endtask

    // Wait for frame_out_valid or timeout
    task automatic wait_frame(output logic got_frame, output logic [127:0] captured, input int timeout = 120);
        int cnt = 0;
        got_frame = 1'b0;
        captured = '0;
        while (!frame_out_valid && cnt < timeout) begin
            @(posedge clk); #1;
            cnt++;
        end
        if (frame_out_valid) begin
            got_frame = 1'b1;
            captured = frame_out;
        end
    endtask

    // Verify no frame arrives for N cycles
    task automatic no_frame_for(input int cycles, input string tag);
        for (int i = 0; i < cycles; i++) begin
            @(posedge clk); #1;
            check($sformatf("%s: no frame at cycle %0d", tag, i), frame_out_valid == 1'b0);
        end
    endtask

    initial begin
        logic [127:0] good_frame, bad_frame, rx_frame;
        logic got;

        $dumpfile("tb_link_rx.vcd");
        $dumpvars(0, tb_link_rx);

        pmod_data   = '0;
        pmod_valid  = 1'b0;
        counter_clr = 1'b0;

        @(posedge clk);
        wait (rst_n === 1'b1);
        repeat (4) @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 1) Idle state: no frames, link_up=0
        // ─────────────────────────────────────────────────────
        $display("--- test_idle ---");
        no_frame_for(30, "idle");
        check("idle: link_up=0", link_up == 1'b0);

        // ─────────────────────────────────────────────────────
        // 2) Truncated frame → error, no frame_out_valid
        // ─────────────────────────────────────────────────────
        $display("--- test_truncated ---");
        begin
            int err_before = error_count;
            send_frame(128'hDEAD_BEEF_F00D_1234_5678_9ABC_DEF0_0001, 5, 0);
            no_frame_for(80, "truncated");
            check("truncated: error_count incremented", error_count > err_before);
        end

        // ─────────────────────────────────────────────────────
        // 3) Valid QUOTE frame → assembles, link_up=1
        // ─────────────────────────────────────────────────────
        $display("--- test_valid_quote ---");
        good_frame = {4'h1, 124'h1234_5678_9ABC_DEF0_0FED_CBA9_8765_432};
        begin
            int err_before = error_count;
            fork
                send_frame(good_frame, BEATS, 10);
                wait_frame(got, rx_frame);
            join
            check("valid: frame received", got);
            check128("valid: frame matches", rx_frame, good_frame);
            @(posedge clk); #1;
            check("valid: link_up=1", link_up == 1'b1);
            check("valid: no new errors", error_count == err_before);
        end

        // ─────────────────────────────────────────────────────
        // 4) Invalid msg_type → error++, link_up drops
        // ─────────────────────────────────────────────────────
        $display("--- test_invalid_msg_type ---");
        bad_frame = {4'hF, 124'h0};
        begin
            int err_before = error_count;
            send_frame(bad_frame, BEATS, 10);
            no_frame_for(90, "invalid msg");
            check("invalid: error_count++", error_count > err_before);
            check("invalid: link_up dropped", link_up == 1'b0);
        end

        // ─────────────────────────────────────────────────────
        // 5) link_up recovery after error
        // ─────────────────────────────────────────────────────
        $display("--- test_link_up_recovery ---");
        good_frame = {4'h2, 8'h01, 1'b0, 3'b000, 32'h0064_0000, 16'd50, 16'd1, 16'h1234, 32'h0};
        fork
            send_frame(good_frame, BEATS, 10);
            wait_frame(got, rx_frame);
        join
        check("recovery: frame received", got);
        check128("recovery: frame matches", rx_frame, good_frame);
        @(posedge clk); #1;
        check("recovery: link_up=1 again", link_up == 1'b1);

        // ─────────────────────────────────────────────────────
        // 6) counter_clr → link_up drops, error_count=0
        // ─────────────────────────────────────────────────────
        $display("--- test_counter_clr ---");
        @(posedge clk); #1;
        check("pre-clr: link_up=1", link_up == 1'b1);
        counter_clr = 1'b1;
        @(posedge clk);
        counter_clr = 1'b0;
        @(posedge clk); #1;
        check("counter_clr: link_up=0", link_up == 1'b0);
        check("counter_clr: error_count=0", error_count == 32'h0);

        // ─────────────────────────────────────────────────────
        // 7) Back-to-back frames (3 frames, minimal gap)
        // ─────────────────────────────────────────────────────
        $display("--- test_back_to_back ---");
        for (int i = 0; i < 3; i++) begin
            logic [127:0] bf;
            bf = {4'h1, 8'(i), 116'(i + 1)};
            fork
                send_frame(bf, BEATS, 4);
                wait_frame(got, rx_frame);
            join
            check($sformatf("b2b[%0d]: received", i), got);
            check128($sformatf("b2b[%0d]: match", i), rx_frame, bf);
        end
        @(posedge clk); #1;
        check("b2b: link_up=1", link_up == 1'b1);

        // ─────────────────────────────────────────────────────
        // 8) Invalid msg_type 0x0 → error
        // ─────────────────────────────────────────────────────
        $display("--- test_msg_type_0 ---");
        begin
            int err_before = error_count;
            bad_frame = {4'h0, 124'hAAAA_BBBB_CCCC_DDDD_EEEE_FFFF_0000_000};
            send_frame(bad_frame, BEATS, 10);
            no_frame_for(90, "msg_type_0");
            check("msg_type_0: error_count++", error_count > err_before);
            check("msg_type_0: link_up dropped", link_up == 1'b0);
        end

        // ─────────────────────────────────────────────────────
        // Summary
        // ─────────────────────────────────────────────────────
        $display("\n===================================");
        if (fail_count == 0)
            $display("tb_link_rx: PASS (%0d checks passed)", pass_count);
        else begin
            $display("tb_link_rx: FAIL (%0d passed, %0d failed)", pass_count, fail_count);
            $fatal;
        end
        $display("===================================");
        $finish;
    end

endmodule
