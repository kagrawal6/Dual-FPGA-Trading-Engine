`timescale 1ns / 1ps
import hft_pkg::*;

module tb_latency_histogram();

    logic       clk = 0;
    logic       rst_n;
    logic       clear;
    logic       fill_processed;
    timestamp_t ts_echo;
    timestamp_t cycle_counter;

    logic [HIST_BIN_W-1:0] hist_bins [HIST_BINS];
    logic [COUNTER_W-1:0]  lat_min, lat_max, lat_sum, lat_count;

    integer err_cnt = 0;

    always #5 clk = ~clk;

    latency_histogram dut (
        .clk(clk), .rst_n(rst_n), .clear(clear),
        .fill_processed(fill_processed), .ts_echo(ts_echo),
        .cycle_counter(cycle_counter),
        .hist_bins(hist_bins),
        .lat_min(lat_min), .lat_max(lat_max),
        .lat_sum(lat_sum), .lat_count(lat_count)
    );

    initial begin
        $display("=== tb_latency_histogram ===");
        rst_n = 0; clear = 0; fill_processed = 0;
        ts_echo = 0; cycle_counter = 0;
        #20; rst_n = 1; @(posedge clk);

        // Test 1: latency = 140 - 100 = 40, bin = 40 >> 5 = 1
        $display("Test 1: latency=40, bin=1");
        cycle_counter = 16'd140; ts_echo = 16'd100;
        fill_processed = 1;
        @(posedge clk); fill_processed = 0;
        @(posedge clk); #1;
        if (hist_bins[1] == 32'd1)
            $display("  PASS: hist_bins[1] = 1");
        else begin
            $display("  FAIL: hist_bins[1] = %0d, expected 1", hist_bins[1]);
            err_cnt = err_cnt + 1;
        end
        if (lat_min == 32'd40 && lat_max == 32'd40)
            $display("  PASS: min=40, max=40");
        else begin
            $display("  FAIL: min=%0d max=%0d", lat_min, lat_max);
            err_cnt = err_cnt + 1;
        end

        // Test 2: latency = 200 - 100 = 100, bin = 100 >> 5 = 3
        $display("Test 2: latency=100, bin=3");
        cycle_counter = 16'd200; ts_echo = 16'd100;
        fill_processed = 1;
        @(posedge clk); fill_processed = 0;
        @(posedge clk); #1;
        if (hist_bins[3] == 32'd1)
            $display("  PASS: hist_bins[3] = 1");
        else begin
            $display("  FAIL: hist_bins[3] = %0d, expected 1", hist_bins[3]);
            err_cnt = err_cnt + 1;
        end

        // Test 3: Aggregate stats after 2 fills
        $display("Test 3: Aggregate stats");
        if (lat_min == 32'd40 && lat_max == 32'd100 &&
            lat_sum == 32'd140 && lat_count == 32'd2)
            $display("  PASS: min=40 max=100 sum=140 count=2");
        else begin
            $display("  FAIL: min=%0d max=%0d sum=%0d count=%0d",
                     lat_min, lat_max, lat_sum, lat_count);
            err_cnt = err_cnt + 1;
        end

        // Test 4: Same bin increments
        $display("Test 4: bin 1 increments again");
        cycle_counter = 16'd150; ts_echo = 16'd110;
        fill_processed = 1;
        @(posedge clk); fill_processed = 0;
        @(posedge clk); #1;
        if (hist_bins[1] == 32'd2)
            $display("  PASS: hist_bins[1] = 2");
        else begin
            $display("  FAIL: hist_bins[1] = %0d, expected 2", hist_bins[1]);
            err_cnt = err_cnt + 1;
        end

        // Test 5: Clear resets all bins and stats
        $display("Test 5: Clear resets");
        clear = 1; @(posedge clk); clear = 0;
        @(posedge clk); #1;
        if (hist_bins[1] == 0 && hist_bins[3] == 0 &&
            lat_count == 0 && lat_min == 32'hFFFF_FFFF)
            $display("  PASS: all bins and stats cleared");
        else begin
            $display("  FAIL: bins/stats not cleared");
            err_cnt = err_cnt + 1;
        end

        // Test 6: Zero latency (cycle_counter == ts_echo) -> bin 0
        $display("Test 6: Zero latency -> bin 0");
        cycle_counter = 16'd500; ts_echo = 16'd500;
        fill_processed = 1;
        @(posedge clk); fill_processed = 0;
        @(posedge clk); #1;
        if (hist_bins[0] == 32'd1)
            $display("  PASS: hist_bins[0] = 1");
        else begin
            $display("  FAIL: hist_bins[0] = %0d, expected 1", hist_bins[0]);
            err_cnt = err_cnt + 1;
        end
        if (lat_min == 32'd0)
            $display("  PASS: lat_min = 0");
        else begin
            $display("  FAIL: lat_min = %0d, expected 0", lat_min);
            err_cnt = err_cnt + 1;
        end

        // Test 7: Large latency exceeding bin range -> clamped to bin 15
        // latency = 600, bin = 600>>5 = 18, clamped to HIST_BINS-1 = 15
        $display("Test 7: Large latency -> bin 15 (clamped)");
        cycle_counter = 16'd600; ts_echo = 16'd0;
        fill_processed = 1;
        @(posedge clk); fill_processed = 0;
        @(posedge clk); #1;
        if (hist_bins[15] == 32'd1)
            $display("  PASS: hist_bins[15] = 1 (clamped)");
        else begin
            $display("  FAIL: hist_bins[15] = %0d, expected 1", hist_bins[15]);
            err_cnt = err_cnt + 1;
        end
        if (lat_max == 32'd600)
            $display("  PASS: lat_max = 600");
        else begin
            $display("  FAIL: lat_max = %0d, expected 600", lat_max);
            err_cnt = err_cnt + 1;
        end

        // Test 8: 16-bit timestamp wrap — latency computed correctly
        // cycle_counter wrapped past 0xFFFF: 0x000A - 0xFFF0 = 26
        $display("Test 8: 16-bit timestamp wrap");
        clear = 1; @(posedge clk); clear = 0;
        @(posedge clk); #1;
        cycle_counter = 16'h000A; ts_echo = 16'hFFF0;
        fill_processed = 1;
        @(posedge clk); fill_processed = 0;
        @(posedge clk); #1;
        if (lat_min == 32'd26 && lat_max == 32'd26)
            $display("  PASS: wrapped latency = 26");
        else begin
            $display("  FAIL: min=%0d max=%0d, expected 26", lat_min, lat_max);
            err_cnt = err_cnt + 1;
        end
        if (hist_bins[0] == 32'd1)
            $display("  PASS: bin 0 correct (26>>5=0)");
        else begin
            $display("  FAIL: hist_bins[0] = %0d, expected 1", hist_bins[0]);
            err_cnt = err_cnt + 1;
        end

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
