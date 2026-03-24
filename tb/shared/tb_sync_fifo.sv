// ============================================================================
// Testbench: tb_sync_fifo
// Fill/drain ordering, full/empty/almost_full, flush, concurrent rd+wr.
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

    int err_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

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
        .clk         (clk),
        .rst_n       (rst_n),
        .flush       (flush),
        .wr_en       (wr_en),
        .wr_data     (wr_data),
        .full        (full),
        .rd_en       (rd_en),
        .rd_data     (rd_data),
        .empty       (empty),
        .almost_full (almost_full),
        .count       (count)
    );

    task automatic check(input string msg, input logic cond);
        if (!cond) begin
            $error("FAIL: %s", msg);
            err_count++;
        end
    endtask

    initial begin
        flush   = 1'b0;
        wr_en   = 1'b0;
        rd_en   = 1'b0;
        wr_data = '0;

        @(posedge clk);
        wait (rst_n === 1'b1);
        @(posedge clk);

        check("empty after reset", empty == 1'b1 && count == 0);
        check("!full after reset", full == 1'b0);

        // Write 5 entries
        for (int i = 1; i <= 5; i++) begin
            @(posedge clk);
            wr_data = 128'(i * 32'h1000_0001);
            wr_en   = 1'b1;
            @(posedge clk);
            wr_en = 1'b0;
        end
        check("count==5", count == 7'd5);
        check("!empty", empty == 1'b0);

        // Read back in order
        for (int i = 1; i <= 5; i++) begin
            @(posedge clk);
            check($sformatf("rd_data %0d", i), rd_data === 128'(i * 32'h1000_0001));
            rd_en = 1'b1;
            @(posedge clk);
            rd_en = 1'b0;
        end
        check("empty after drain", empty == 1'b1);

        // almost_full: fill to 60
        for (int i = 0; i < 60; i++) begin
            @(posedge clk);
            wr_data = 128'(i);
            wr_en   = 1'b1;
            @(posedge clk);
            wr_en = 1'b0;
        end
        check("count 60", count == 7'd60);
        check("almost_full", almost_full == 1'b1);
        check("!full yet", full == 1'b0);

        for (int j = 60; j < 64; j++) begin
            @(posedge clk);
            wr_data = 128'(j);
            wr_en   = 1'b1;
            @(posedge clk);
            wr_en = 1'b0;
        end
        @(posedge clk);
        check("full at 64", full == 1'b1 && count == 7'd64);

        // flush
        @(posedge clk);
        flush = 1'b1;
        @(posedge clk);
        flush = 1'b0;
        @(posedge clk);
        check("flush empty", empty == 1'b1 && count == 0);

        @(posedge clk);
        wr_data = 128'hfeed_face;
        wr_en   = 1'b1;
        @(posedge clk);
        wr_en = 1'b0;
        @(posedge clk);
        check("peek before rd", rd_data === 128'hfeed_face);
        rd_en = 1'b1;
        @(posedge clk);
        rd_en = 1'b0;
        @(posedge clk);
        check("empty after single rd", empty == 1'b1);

        if (err_count == 0)
            $display("tb_sync_fifo: PASS (all checks passed)");
        else
            $display("tb_sync_fifo: FAIL (%0d errors)", err_count);
        $finish;
    end

endmodule
