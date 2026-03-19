// ============================================================================
// Testbench: tb_position_tracker
// Tests the position_tracker module: FILL frame processing, per-symbol position
// updates (BUY adds, SELL subtracts), cash accumulator (Q32.16), total_pnl
// extraction, and ts_echo output for latency measurement.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_position_tracker;

    logic                     clk;
    logic                     rst_n;
    logic                     clear;
    logic [FRAME_W-1:0]       fill_frame;
    logic                     fill_valid;
    position_t                position [NUM_SYMBOLS];
    cash_t                   cash;
    sprice_t                  total_pnl;
    timestamp_t               ts_echo;
    logic                     fill_processed;
    logic [COUNTER_W-1:0]     fills_rcvd;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low rst_n, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    position_tracker dut (
        .clk            (clk),
        .rst_n          (rst_n),
        .clear          (clear),
        .fill_frame     (fill_frame),
        .fill_valid     (fill_valid),
        .position       (position),
        .cash           (cash),
        .total_pnl      (total_pnl),
        .ts_echo        (ts_echo),
        .fill_processed (fill_processed),
        .fills_rcvd     (fills_rcvd)
    );

    initial begin
        // TODO: Add test stimulus
        #1000;
        $finish;
    end

endmodule
