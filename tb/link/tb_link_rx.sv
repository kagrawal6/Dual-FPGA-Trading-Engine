// ============================================================================
// Testbench: tb_link_rx
// Tests the PMOD link receiver: data/valid synchronization, frame assembly,
// frame_out_valid pulse, link_up status, and error_count tracking.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_link_rx;

    logic                  clk;
    logic                  rst_n;
    logic [3:0]            pmod_data;
    logic                  pmod_valid;
    logic                  local_ready;
    logic [127:0]          frame_out;
    logic                  frame_out_valid;
    logic                  link_up;
    logic [31:0]           error_count;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    link_rx #(
        .FRAME_W (128),
        .DATA_W  (4)
    ) dut (
        .clk             (clk),
        .rst_n            (rst_n),
        .pmod_data        (pmod_data),
        .pmod_valid       (pmod_valid),
        .local_ready      (local_ready),
        .frame_out        (frame_out),
        .frame_out_valid  (frame_out_valid),
        .link_up          (link_up),
        .error_count      (error_count)
    );

    // ---------------------------------------------------------------------
    // Test utilities
    // ---------------------------------------------------------------------
    int err_count_scratch = 0;
    int frames_seen       = 0;
    logic [127:0] last_frame = '0;

    always_ff @(posedge clk) begin
        if (frame_out_valid) begin
            frames_seen <= frames_seen + 1;
            last_frame   <= frame_out;
        end
    end

    task automatic check(input string msg, input logic cond);
        if (!cond) begin
            $error("FAIL: %s", msg);
            err_count_scratch++;
        end
    endtask

    localparam int FRAME_W = 128;
    localparam int DATA_W  = 4;
    localparam int BEATS   = FRAME_W / DATA_W; // 32

    function automatic logic [DATA_W-1:0] nibble_at(input logic [FRAME_W-1:0] frame, input int i);
        // MSB-first: beat 0 = frame[127:124], beat 1 = frame[123:120], ...
        nibble_at = frame[FRAME_W-1 - (i*DATA_W) -: DATA_W];
    endfunction

    // Drive a frame with 2 core_clk cycles per beat.
    task automatic send_frame(
        input logic [FRAME_W-1:0] frame,
        input int beats_to_send,
        input int pad_cycles_after_last_beat
    );
        int i;
        begin
            // Start from an idle valid low so the receiver sees a clean rising edge.
            pmod_valid = 1'b0;
            pmod_data  = '0;
            @(posedge clk);

            for (i = 0; i < beats_to_send; i++) begin
                pmod_data  = nibble_at(frame, i);
                pmod_valid = 1'b1;
                @(posedge clk);
                @(posedge clk); // hold for 2 cycles
            end

            // Keep valid high a little longer so the receiver (with 2-FF sync and
            // phase-aligned sampling) still sees valid asserted during its final
            // sampling beat.
            if (pad_cycles_after_last_beat > 0) begin
                repeat (pad_cycles_after_last_beat) @(posedge clk);
            end

            // Deassert valid after the last beat + padding.
            pmod_valid = 1'b0;
            pmod_data  = '0;
            @(posedge clk);
        end
    endtask

    // A helper to wait and ensure frame_out_valid doesn't pulse unexpectedly.
    task automatic wait_cycles_no_frame(input int cycles);
        begin
            for (int k = 0; k < cycles; k++) begin
                @(posedge clk);
                check($sformatf("Unexpected frame_out_valid pulse at cycle %0d", k),
                      frame_out_valid == 1'b0);
            end
        end
    endtask

    // ---------------------------------------------------------------------
    // Waveform dump
    // ---------------------------------------------------------------------
    initial begin
        $dumpfile("tb_link_rx.vcd");
        $dumpvars(0, tb_link_rx);
    end

    // ---------------------------------------------------------------------
    // Test sequence
    // ---------------------------------------------------------------------
    initial begin
        int err0;
        int err1;
        int wait_p;
        logic [127:0] good_frame;
        logic [127:0] bad_msg_frame;

        // Defaults
        pmod_data       = '0;
        pmod_valid      = 1'b0;
        frames_seen     = 0;
        last_frame      = '0;
        err_count_scratch = 0;

        // Wait for reset release
        @(posedge clk);
        wait (rst_n === 1'b1);
        @(posedge clk);

        // -------------------------------------------------------------
        // 1) valid staying low indefinitely → no frames, link_up stays 0
        // -------------------------------------------------------------
        wait_cycles_no_frame(30);
        check("No frames should be seen in idle period", frames_seen == 0);
        check("link_up should remain 0 before first valid frame", link_up == 1'b0);

        err0 = error_count;

        // -------------------------------------------------------------
        // 2) Glitch/truncated valid: should not assert frame_out_valid,
        //    but should increment error_count.
        // -------------------------------------------------------------
        send_frame(128'hDEAD_BEEF_F00D_1234_5678_9ABC_DEF0_0001, 5, 0);
        // Allow time for receiver to complete/abort and update error_count
        wait_cycles_no_frame(80);
        check("Truncated frame must not produce frame_out_valid", frames_seen == 0);
        check("error_count should increment after truncation", error_count > err0);
        err1 = error_count;

        // -------------------------------------------------------------
        // 3) Full valid frame (msg_type=QUOTE=4'h1) → frame assembles,
        //    frame_out_valid pulses once, link_up asserts.
        // -------------------------------------------------------------
        good_frame = {4'h1, 124'h1234_5678_9ABC_DEF0_0FED_CBA9_8765_432};

        // Reset counters for this scenario
        frames_seen = 0;
        last_frame  = '0;

        send_frame(good_frame, BEATS, 10);

        // Wait for one successful pulse.
        wait_p = 0;
        while (frames_seen == 0 && wait_p < 120) begin
            @(posedge clk);
            wait_p++;
        end
        check("Full valid frame must produce at least one frame_out_valid pulse", frames_seen == 1);
        check("Assembled frame_out must match the transmitted frame", last_frame === good_frame);
        check("link_up must assert after first successful frame", link_up == 1'b1);
        check("No new errors expected for a valid complete frame", error_count == err1);

        // -------------------------------------------------------------
        // 4) Full frame with invalid msg_type → frame_out_valid must stay low,
        //    error_count increments; link_up should remain 1.
        // -------------------------------------------------------------
        bad_msg_frame = {4'hF, 124'h0};
        frames_seen = 0;
        last_frame  = '0;

        send_frame(bad_msg_frame, BEATS, 10);
        wait_cycles_no_frame(90);
        check("Invalid msg_type must not output frame_out_valid", frames_seen == 0);
        check("error_count should increment on invalid msg_type", error_count > err1);
        check("link_up should remain asserted once link is up", link_up == 1'b1);

        // -------------------------------------------------------------
        // Summary
        // -------------------------------------------------------------
        if (err_count_scratch == 0)
            $display("tb_link_rx: PASS (all tests passed)");
        else
            $display("tb_link_rx: FAIL (%0d errors)", err_count_scratch);

        $finish;
    end

endmodule
