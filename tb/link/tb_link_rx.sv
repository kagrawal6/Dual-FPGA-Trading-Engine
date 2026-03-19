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

    initial begin
        // TODO: Add test stimulus
        $finish;
    end

endmodule
