// ============================================================================
// Testbench: tb_msg_demux
// Tests the msg_demux module: frame routing by msg_type (QUOTE vs FILL),
// counter behavior (quotes_rcvd, demux_errors), and clear functionality.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_msg_demux;

    logic                     clk;
    logic                     rst_n;
    logic                     clear;
    logic [FRAME_W-1:0]       frame_in;
    logic                     frame_in_valid;
    logic [FRAME_W-1:0]       quote_frame;
    logic                     quote_valid;
    logic [FRAME_W-1:0]       fill_frame;
    logic                     fill_valid;
    logic [COUNTER_W-1:0]     quotes_rcvd;
    logic [COUNTER_W-1:0]     demux_errors;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    msg_demux dut (
        .clk           (clk),
        .rst_n         (rst_n),
        .clear         (clear),
        .frame_in      (frame_in),
        .frame_in_valid(frame_in_valid),
        .quote_frame   (quote_frame),
        .quote_valid   (quote_valid),
        .fill_frame    (fill_frame),
        .fill_valid    (fill_valid),
        .quotes_rcvd   (quotes_rcvd),
        .demux_errors  (demux_errors)
    );

    initial begin
        // TODO: Add test stimulus
        $finish;
    end

endmodule
