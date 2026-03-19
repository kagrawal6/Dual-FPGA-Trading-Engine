// ============================================================================
// Testbench: tb_sync_fifo
// Tests the parameterized synchronous FIFO: write/read operations, full/empty
// flags, almost_full backpressure, count, and flush.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_sync_fifo;

    logic                       clk;
    logic                       rst_n;
    logic                       flush;
    logic                       wr_en;
    logic [127:0]               wr_data;
    logic                       full;
    logic                       rd_en;
    logic [127:0]               rd_data;
    logic                       empty;
    logic                       almost_full;
    logic [$clog2(64):0]        count;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    sync_fifo #(
        .DATA_W             (128),
        .DEPTH              (64),
        .ALMOST_FULL_THRESH (60)
    ) dut (
        .clk             (clk),
        .rst_n           (rst_n),
        .flush           (flush),
        .wr_en           (wr_en),
        .wr_data         (wr_data),
        .full            (full),
        .rd_en           (rd_en),
        .rd_data         (rd_data),
        .empty           (empty),
        .almost_full     (almost_full),
        .count           (count)
    );

    initial begin
        // TODO: Add test stimulus
        $finish;
    end

endmodule
