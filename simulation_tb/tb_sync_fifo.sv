`timescale 1ns / 1ps

module tb_sync_fifo();

    import hft_pkg::*;

    localparam DATA_W = 8;
    localparam DEPTH  = 4;

    logic                    clk, rst_n, flush;
    logic                    wr_en, rd_en;
    logic [DATA_W-1:0]       wr_data, rd_data;
    logic                    full, empty, almost_full;
    logic [$clog2(DEPTH):0]  count;
    integer err_cnt = 0;

    always #5 clk = ~clk;

    sync_fifo #(.DATA_W(DATA_W), .DEPTH(DEPTH)) dut (
        .clk(clk), .rst_n(rst_n), .flush(flush),
        .wr_en(wr_en), .wr_data(wr_data), .full(full),
        .rd_en(rd_en), .rd_data(rd_data), .empty(empty),
        .almost_full(almost_full), .count(count)
    );

    initial begin
        clk = 0; rst_n = 0; flush = 0;
        wr_en = 0; rd_en = 0; wr_data = '0;
        #20; rst_n = 1;
        @(posedge clk);

        // After reset: empty should be 1 and count 0 (DEPTH=4 FIFO).
        @(posedge clk); #1;
        if (!empty || count !== 0) begin
            $display("FAIL: after reset empty=%0b count=%0d (want empty=1 count=0)", empty, count);
            err_cnt = err_cnt + 1;
        end else $display("PASS: empty and count OK after reset");

        // Write four bytes; full flag should set and count==4.
        wr_en = 1;
        wr_data = 8'hAA; @(posedge clk);
        wr_data = 8'hBB; @(posedge clk);
        wr_data = 8'hCC; @(posedge clk);
        wr_data = 8'hDD; @(posedge clk);
        wr_en = 0;
        @(posedge clk); #1;
        if (!full || count !== 4) begin
            $display("FAIL: not full after 4 writes", full, count);
            err_cnt = err_cnt + 1;
        end else $display("PASS: full after four writes");

        // Pop in order: expect AA, BB, CC, DD (combinational rd_data before each rd_en).
        #1;
        if (rd_data !== 8'hAA) begin
            $display("FAIL: first rd_data=%h expected AA", rd_data);
            err_cnt = err_cnt + 1;
        end else $display("ok: first byte AA");

        rd_en = 1;
        @(posedge clk); #1;
        if (rd_data !== 8'hBB) begin
            $display("FAIL: second pop %h want BB", rd_data);
            err_cnt = err_cnt + 1;
        end

        @(posedge clk); #1;
        if (rd_data !== 8'hCC) begin
            $display("FAIL: third pop %h want CC", rd_data);
            err_cnt = err_cnt + 1;
        end

        @(posedge clk); #1;
        if (rd_data !== 8'hDD) begin
            $display("FAIL: fourth pop %h want DD", rd_data);
            err_cnt = err_cnt + 1;
        end
        @(posedge clk);
        rd_en = 0;
        if (err_cnt == 0) $display("PASS: FIFO order AA BB CC DD");

        // All reads done: empty again, count 0.
        @(posedge clk); #1;
        if (!empty || count !== 0) begin
            $display("FAIL: after drain empty=%0b count=%0d", empty, count);
            err_cnt = err_cnt + 1;
        end else $display("PASS: empty after full drain");

        // Flush: write two entries then assert flush; FIFO should clear.
        wr_en = 1;
        wr_data = 8'hEE; @(posedge clk);
        wr_data = 8'hFF; @(posedge clk);
        wr_en = 0;
        @(posedge clk); #1;
        if (count !== 2) begin
            $display("FAIL: count before flush=%0d expected 2", count);
            err_cnt = err_cnt + 1;
        end

        flush = 1;
        @(posedge clk);
        flush = 0;
        @(posedge clk); #1;
        if (!empty || count !== 0) begin
            $display("FAIL: after flush empty=%0b count=%0d", empty, count);
            err_cnt = err_cnt + 1;
        end else $display("PASS: flush cleared FIFO");

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
