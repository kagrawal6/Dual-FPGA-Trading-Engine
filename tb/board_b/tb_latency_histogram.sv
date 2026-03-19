// ============================================================================
// Testbench: tb_latency_histogram
// Tests the latency_histogram module: round-trip latency computation from
// fill_processed and ts_echo, bin mapping, and scalar stats (lat_min, lat_max,
// lat_sum, lat_count).
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_latency_histogram;

    logic                     clk;
    logic                     rst_n;
    logic                     clear;
    logic                     fill_processed;
    timestamp_t               ts_echo;
    timestamp_t               cycle_counter;
    logic [HIST_BIN_W-1:0]    hist_bins [HIST_BINS];
    logic [COUNTER_W-1:0]     lat_min;
    logic [COUNTER_W-1:0]     lat_max;
    logic [COUNTER_W-1:0]     lat_sum;
    logic [COUNTER_W-1:0]     lat_count;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low rst_n, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    latency_histogram dut (
        .clk            (clk),
        .rst_n          (rst_n),
        .clear          (clear),
        .fill_processed (fill_processed),
        .ts_echo        (ts_echo),
        .cycle_counter  (cycle_counter),
        .hist_bins      (hist_bins),
        .lat_min        (lat_min),
        .lat_max        (lat_max),
        .lat_sum        (lat_sum),
        .lat_count      (lat_count)
    );

    initial begin
        // TODO: Add test stimulus
        #1000;
        $finish;
    end

endmodule
