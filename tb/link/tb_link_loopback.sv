// ============================================================================
// Testbench: tb_link_loopback
// Tests link_tx connected to link_rx in a loopback configuration. Verifies
// end-to-end frame transmission: frame_in → link_tx → pmod → link_rx → frame_out.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_link_loopback;

    logic                  clk;
    logic                  rst_n;

    // link_tx inputs
    logic [127:0]          frame_in;
    logic                  frame_in_valid;
    logic                  frame_in_ready;

    // link_rx outputs
    logic [127:0]          frame_out;
    logic                  frame_out_valid;
    logic                  link_up;
    logic [31:0]           error_count;

    // Loopback connection: link_tx → link_rx
    logic [3:0]            pmod_data;
    logic                  pmod_valid;
    logic                  remote_ready;   // link_rx local_ready → link_tx remote_ready

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    link_tx #(
        .FRAME_W (128),
        .DATA_W  (4)
    ) u_link_tx (
        .clk            (clk),
        .rst_n          (rst_n),
        .frame_in       (frame_in),
        .frame_in_valid (frame_in_valid),
        .frame_in_ready (frame_in_ready),
        .pmod_data      (pmod_data),
        .pmod_valid     (pmod_valid),
        .remote_ready   (remote_ready)
    );

    link_rx #(
        .FRAME_W (128),
        .DATA_W  (4)
    ) u_link_rx (
        .clk             (clk),
        .rst_n            (rst_n),
        .pmod_data        (pmod_data),
        .pmod_valid       (pmod_valid),
        .local_ready      (remote_ready),
        .frame_out        (frame_out),
        .frame_out_valid  (frame_out_valid),
        .link_up          (link_up),
        .error_count      (error_count)
    );

    initial begin
        // TODO: Add test stimulus
        $finish;
    end

endmodule
