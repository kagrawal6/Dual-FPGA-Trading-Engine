// ============================================================================
// Testbench: tb_link_tx
// Tests the PMOD link transmitter: frame serialization, valid/ready handshake,
// pmod_data/pmod_valid output timing, and remote_ready backpressure.
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
    logic                  remote_ready;

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
    ) dut (
        .clk            (clk),
        .rst_n          (rst_n),
        .frame_in       (frame_in),
        .frame_in_valid (frame_in_valid),
        .frame_in_ready (frame_in_ready),
        .pmod_data      (pmod_data),
        .pmod_valid     (pmod_valid),
        .remote_ready   (remote_ready)
    );

    initial begin
        // TODO: Add test stimulus
        $finish;
    end

endmodule
