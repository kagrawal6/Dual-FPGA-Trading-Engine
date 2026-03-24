// ============================================================================
// Testbench: tb_link_tx
// Uses link_rx as reference monitor: remote_ready/backpressure + frame check.
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

    logic [127:0]          frame_out;
    logic                  frame_out_valid;
    logic                  link_up;
    logic [31:0]           error_count;

    int err_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    link_tx #(
        .FRAME_W (128),
        .DATA_W  (4)
    ) dut (
        .clk            (clk),
        .rst_n          (rst_n),
        .frame_in       (frame_in),
        .frame_in_valid (frame_in_valid),
        .frame_in_ready (frame_in_ready),
        .pmod_data      (pmod_data),
        .pmod_valid     (pmod_valid),
        .remote_ready   (link_remote_ready)
    );

    link_rx #(
        .FRAME_W (128),
        .DATA_W  (4)
    ) u_mon (
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

    task automatic check(input string msg, input logic cond);
        if (!cond) begin
            $error("FAIL: %s", msg);
            err_count++;
        end
    endtask

    initial begin
        logic [127:0] exp_frame;
        frame_in       = '0;
        frame_in_valid = 1'b0;

        @(posedge clk);
        wait (rst_n === 1'b1);
        @(posedge clk);

        exp_frame = {4'h2, 4'h3, 120'h5_dead_beef_cafe_0000_0000_0000};
        @(posedge clk);
        frame_in       = exp_frame;
        frame_in_valid = 1'b1;
        do begin
            @(posedge clk);
        end while (!(frame_in_ready && frame_in_valid));
        @(posedge clk);
        frame_in_valid = 1'b0;

        wait (frame_out_valid === 1'b1);
        @(posedge clk);
        check("assembled frame", frame_out === exp_frame);
        check("link_up", link_up == 1'b1);
        check("rx errors", error_count == 32'h0);

        if (err_count == 0)
            $display("tb_link_tx: PASS (all checks passed)");
        else
            $display("tb_link_tx: FAIL (%0d errors)", err_count);
        $finish;
    end

endmodule
