// ============================================================================
// Testbench: tb_link_loopback
// All 3 message types, 10-frame stress, pattern tests (all-0, all-1, alt).
// link_tx → link_rx wire loopback.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_link_loopback;

    logic                  clk;
    logic                  rst_n;

    logic [127:0]          frame_in;
    logic                  frame_in_valid;
    logic                  frame_in_ready;

    logic [127:0]          frame_out;
    logic                  frame_out_valid;
    logic                  link_up;
    logic [31:0]           error_count;

    logic [3:0]            pmod_data;
    logic                  pmod_valid;
    logic                  link_remote_ready;

    int pass_count = 0;
    int fail_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    link_tx #(.FRAME_W(128), .DATA_W(4)) u_link_tx (
        .clk            (clk),
        .rst_n          (rst_n),
        .frame_in       (frame_in),
        .frame_in_valid (frame_in_valid),
        .frame_in_ready (frame_in_ready),
        .pmod_data      (pmod_data),
        .pmod_valid     (pmod_valid),
        .remote_ready   (link_remote_ready)
    );

    link_rx #(.FRAME_W(128), .DATA_W(4)) u_link_rx (
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

    task automatic send_and_verify(input logic [127:0] f, input string tag);
        logic [127:0] rx;
        frame_in = f;
        frame_in_valid = 1'b1;
        do @(posedge clk); while (!(frame_in_ready && frame_in_valid));
        @(posedge clk);
        frame_in_valid = 1'b0;

        begin
            int timeout = 200;
            while (!frame_out_valid && timeout > 0) begin
                @(posedge clk);
                timeout--;
            end
        end
        check($sformatf("%s: received", tag), frame_out_valid);
        check128($sformatf("%s: match", tag), frame_out, f);
    endtask

    initial begin
        $dumpfile("tb_link_loopback.vcd");
        $dumpvars(0, tb_link_loopback);

        frame_in       = '0;
        frame_in_valid = 1'b0;

        @(posedge clk);
        wait (rst_n === 1'b1);
        repeat (4) @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 1) All 3 message types
        // ─────────────────────────────────────────────────────
        $display("--- test_all_msg_types ---");
        send_and_verify(
            {4'h1, 8'h00, 2'b00, 2'b00, 32'h00B4_0000, 32'h00B5_0000, 16'd1000, 16'd1000, 16'd0},
            "QUOTE"
        );
        send_and_verify(
            {4'h2, 8'h03, 1'b0, 3'b000, 32'h0064_0000, 16'd100, 16'd1, 16'hABCD, 32'h0},
            "ORDER"
        );
        send_and_verify(
            {4'h3, 8'h03, 1'b0, 3'b000, 32'h0064_0000, 16'd100, 16'd1, 16'hABCD, 32'h0},
            "FILL"
        );
        check("3 types: link_up", link_up == 1'b1);
        check("3 types: no errors", error_count == 32'h0);

        // ─────────────────────────────────────────────────────
        // 2) 10-frame stress test
        // ─────────────────────────────────────────────────────
        $display("--- test_10_frame_stress ---");
        for (int i = 0; i < 10; i++) begin
            logic [127:0] f;
            // Alternate message types for variety
            case (i % 3)
                0: f = {4'h1, 8'(i), 116'(i + 1)};
                1: f = {4'h2, 8'(i), 1'b0, 115'(i + 1)};
                2: f = {4'h3, 8'(i), 1'b0, 3'b000, 112'(i + 1)};
            endcase
            send_and_verify(f, $sformatf("stress[%0d]", i));
        end
        check("stress: no errors", error_count == 32'h0);

        // ─────────────────────────────────────────────────────
        // 3) Pattern tests
        // ─────────────────────────────────────────────────────
        $display("--- test_patterns ---");

        // All-zeros payload (msg_type=QUOTE to pass validation)
        send_and_verify(
            {4'h1, 124'h0},
            "all-zero payload"
        );

        // All-ones payload
        send_and_verify(
            {4'h1, 124'hFFFFFFF_FFFFFFFF_FFFFFFFF_FFFFFFF},
            "all-ones payload"
        );

        // Alternating 0xA/0x5 nibbles (msg_type=1 first nibble)
        send_and_verify(
            128'h1A5A_5A5A_5A5A_5A5A_5A5A_5A5A_5A5A_5A5A,
            "alternating A/5"
        );

        // Alternating 0x5/0xA nibbles
        send_and_verify(
            128'h15A5_A5A5_A5A5_A5A5_A5A5_A5A5_A5A5_A5A5,
            "alternating 5/A"
        );

        // Walking-ones in each 32-bit word
        send_and_verify(
            128'h1000_0001_8000_0000_4000_0000_2000_0000,
            "walking ones"
        );

        check("patterns: no errors", error_count == 32'h0);

        // ─────────────────────────────────────────────────────
        // Summary
        // ─────────────────────────────────────────────────────
        $display("\n===================================");
        if (fail_count == 0)
            $display("tb_link_loopback: PASS (%0d checks passed)", pass_count);
        else begin
            $display("tb_link_loopback: FAIL (%0d passed, %0d failed)", pass_count, fail_count);
            $fatal;
        end
        $display("===================================");
        $finish;
    end

endmodule
