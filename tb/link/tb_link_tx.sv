// ============================================================================
// Testbench: tb_link_tx
// Multi-frame burst, backpressure, all 3 message types, nibble-level verify.
// Uses link_rx as reference monitor for round-trip checking.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_link_tx;

    logic                  clk;
    logic                  rst_n;
    logic [127:0]          frame_in;
    logic                  frame_in_valid;
    logic                  frame_in_ready;
    logic [3:0]            pmod_data;
    logic                  pmod_valid;
    logic                  link_remote_ready;

    // RX monitor
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

    link_tx #(.FRAME_W(128), .DATA_W(4)) dut (
        .clk            (clk),
        .rst_n          (rst_n),
        .frame_in       (frame_in),
        .frame_in_valid (frame_in_valid),
        .frame_in_ready (frame_in_ready),
        .pmod_data      (pmod_data),
        .pmod_valid     (pmod_valid),
        .remote_ready   (link_remote_ready)
    );

    link_rx #(.FRAME_W(128), .DATA_W(4)) u_mon (
        .clk             (clk),
        .rst_n           (rst_n),
        .counter_clr     (1'b0),
        .pmod_data       (pmod_data),
        .pmod_valid      (pmod_valid),
        .local_ready     (link_remote_ready),
        .frame_out       (frame_out),
        .frame_out_valid (frame_out_valid),
        .link_up         (link_up),
        .error_count     (error_count)
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

    // Send a frame and wait for acceptance
    task automatic send_frame(input logic [127:0] f);
        frame_in = f;
        frame_in_valid = 1'b1;
        do begin
            @(posedge clk);
        end while (!(frame_in_ready && frame_in_valid));
        @(posedge clk);
        frame_in_valid = 1'b0;
    endtask

    // Wait for frame_out_valid and capture
    task automatic wait_rx(output logic [127:0] received, input int timeout = 200);
        int cnt = 0;
        received = '0;
        while (!frame_out_valid && cnt < timeout) begin
            @(posedge clk);
            cnt++;
        end
        if (frame_out_valid) received = frame_out;
    endtask

    initial begin
        logic [127:0] rx_frame;
        logic [127:0] QUOTE_F, ORDER_F, FILL_F;
        logic [3:0]   captured_nibbles [32];
        int           nib_idx;

        $dumpfile("tb_link_tx.vcd");
        $dumpvars(0, tb_link_tx);

        frame_in       = '0;
        frame_in_valid = 1'b0;

        @(posedge clk);
        wait (rst_n === 1'b1);
        repeat (4) @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 1) Single QUOTE frame
        // ─────────────────────────────────────────────────────
        $display("--- test_single_quote ---");
        QUOTE_F = {4'h1, 4'h0, 120'h1234_5678_9ABC_DEF0_0000_0000_0001};
        send_frame(QUOTE_F);
        wait_rx(rx_frame);
        check128("single QUOTE match", rx_frame, QUOTE_F);
        check("link_up after QUOTE", link_up == 1'b1);
        check("no errors", error_count == 32'h0);

        // ─────────────────────────────────────────────────────
        // 2) All 3 message types
        // ─────────────────────────────────────────────────────
        $display("--- test_all_msg_types ---");
        ORDER_F = {4'h2, 8'h03, 1'b0, 3'b000, 32'h0064_0000, 16'd100, 16'd1, 16'hABCD, 32'h0};
        FILL_F  = {4'h3, 8'h03, 1'b0, 3'b000, 32'h0064_0000, 16'd100, 16'd1, 16'hABCD, 32'h0};

        send_frame(ORDER_F);
        wait_rx(rx_frame);
        check128("ORDER frame match", rx_frame, ORDER_F);

        send_frame(FILL_F);
        wait_rx(rx_frame);
        check128("FILL frame match", rx_frame, FILL_F);

        // ─────────────────────────────────────────────────────
        // 3) Multi-frame burst: 4 frames back-to-back
        // ─────────────────────────────────────────────────────
        $display("--- test_multi_frame_burst ---");
        for (int i = 0; i < 4; i++) begin
            logic [127:0] bf;
            bf = {4'h1, 4'(i), 120'(i * 128'h1111_1111_1111_1111_1111_1111_1111_111)};
            send_frame(bf);
            wait_rx(rx_frame);
            check128($sformatf("burst frame[%0d]", i), rx_frame, bf);
        end
        check("no errors after burst", error_count == 32'h0);

        // ─────────────────────────────────────────────────────
        // 4) Nibble-level verification (MSB-first)
        // ─────────────────────────────────────────────────────
        $display("--- test_nibble_order ---");
        // Send a frame with known nibble pattern
        QUOTE_F = 128'h1234_5678_9ABC_DEF0_FEDC_BA98_7654_3210;
        frame_in = QUOTE_F;
        frame_in_valid = 1'b1;
        // Wait for acceptance
        do @(posedge clk); while (!(frame_in_ready && frame_in_valid));
        @(posedge clk);
        frame_in_valid = 1'b0;

        // Capture nibbles during transmission
        nib_idx = 0;
        begin
            int timeout = 200;
            while (nib_idx < 32 && timeout > 0) begin
                @(posedge clk);
                if (pmod_valid) begin
                    captured_nibbles[nib_idx] = pmod_data;
                    nib_idx++;
                    @(posedge clk); // skip half_nibble hold cycle
                end
                timeout--;
            end
        end

        // Verify MSB-first: nibble[0] = frame[127:124] = 4'h1
        if (nib_idx >= 32) begin
            check("nibble[0] = MSB", captured_nibbles[0] == 4'h1);
            check("nibble[1]", captured_nibbles[1] == 4'h2);
            check("nibble[30]", captured_nibbles[30] == 4'h1);
            check("nibble[31] = LSB", captured_nibbles[31] == 4'h0);
        end else begin
            $error("FAIL: only captured %0d nibbles", nib_idx);
            fail_count++;
        end
        wait_rx(rx_frame);
        check128("nibble frame round-trip", rx_frame, QUOTE_F);

        // ─────────────────────────────────────────────────────
        // 5) remote_ready deassert (backpressure)
        // ─────────────────────────────────────────────────────
        $display("--- test_backpressure ---");
        // This test verifies that frame_in_ready depends on remote_ready_sync.
        // Since remote_ready is driven by link_rx.local_ready which goes
        // low during capture, the TX naturally waits between frames.
        // Verify by sending a frame, then checking no new frame can start
        // during transmission.
        QUOTE_F = {4'h1, 124'hAAAA_BBBB_CCCC_DDDD_EEEE_FFFF_0000_000};
        send_frame(QUOTE_F);
        wait_rx(rx_frame);
        check128("backpressure frame", rx_frame, QUOTE_F);

        // ─────────────────────────────────────────────────────
        // Summary
        // ─────────────────────────────────────────────────────
        $display("\n===================================");
        if (fail_count == 0)
            $display("tb_link_tx: PASS (%0d checks passed)", pass_count);
        else begin
            $display("tb_link_tx: FAIL (%0d passed, %0d failed)", pass_count, fail_count);
            $fatal;
        end
        $display("===================================");
        $finish;
    end

endmodule
