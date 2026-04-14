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
    integer err_cnt;

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
        err_cnt = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // ----------------------------------------------------------------
        // Test 1: After reset — empty=1, count=0 (DEPTH=4 FIFO).
        // ----------------------------------------------------------------
        @(posedge clk); #1;
        if (!empty || count !== 0) begin
            $display("FAIL: after reset empty=%0b count=%0d (want empty=1 count=0)", empty, count);
            err_cnt = err_cnt + 1;
        end else $display("PASS: empty and count OK after reset");

        // ----------------------------------------------------------------
        // Test 2: Write four bytes; full flag should set and count==4.
        // ----------------------------------------------------------------
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

        // ----------------------------------------------------------------
        // Test 3: Pop in order — expect AA, BB, CC, DD (FIFO ordering).
        // ----------------------------------------------------------------
        #1;
        if (rd_data !== 8'hAA) begin
            $display("FAIL: first rd_data=%h expected AA", rd_data);
            err_cnt = err_cnt + 1;
        end else $display("PASS: first byte AA");

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

        // ----------------------------------------------------------------
        // Test 4: All reads done — empty again, count 0.
        // ----------------------------------------------------------------
        @(posedge clk); #1;
        if (!empty || count !== 0) begin
            $display("FAIL: after drain empty=%0b count=%0d", empty, count);
            err_cnt = err_cnt + 1;
        end else $display("PASS: empty after full drain");

        // ----------------------------------------------------------------
        // Test 5: Flush — write two entries then assert flush; FIFO clears.
        // ----------------------------------------------------------------
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

        // ----------------------------------------------------------------
        // Test 6: Concurrent read+write — flush then write one entry so
        //         ordering is unambiguous. Concurrent wr+rd swaps the
        //         single entry; count stays 1 and 0x33 must appear.
        // ----------------------------------------------------------------
        flush = 1; @(posedge clk); flush = 0; @(posedge clk);

        wr_en = 1; rd_en = 0;
        wr_data = 8'h11; @(posedge clk);
        wr_en = 0;
        @(posedge clk); #1;
        if (count !== 1) begin
            $display("FAIL: setup for concurrent r/w, count=%0d expected 1", count);
            err_cnt = err_cnt + 1;
        end

        wr_en = 1; rd_en = 1;
        wr_data = 8'h33;
        @(posedge clk);
        wr_en = 0; rd_en = 0;
        @(posedge clk); #1;
        if (count !== 1) begin
            $display("FAIL: concurrent r/w count=%0d expected 1", count);
            err_cnt = err_cnt + 1;
        end else $display("PASS: concurrent read+write keeps count stable");

        rd_en = 1;
        @(posedge clk); #1;
        rd_en = 0;
        if (rd_data !== 8'h33) begin
            $display("FAIL: concurrent write data missing, rd_data=%h expected 33", rd_data);
            err_cnt = err_cnt + 1;
        end else $display("PASS: concurrent write data 0x33 present");
        @(posedge clk);

        // ----------------------------------------------------------------
        // Test 7: Overflow protection — write when full; full stays 1,
        //         count stays at DEPTH=4, no corruption.
        // ----------------------------------------------------------------
        flush = 1; @(posedge clk); flush = 0; @(posedge clk);

        wr_en = 1;
        wr_data = 8'hA1; @(posedge clk);
        wr_data = 8'hA2; @(posedge clk);
        wr_data = 8'hA3; @(posedge clk);
        wr_data = 8'hA4; @(posedge clk);
        wr_en = 0;
        @(posedge clk); #1;
        if (!full) begin
            $display("FAIL: FIFO not full before overflow test");
            err_cnt = err_cnt + 1;
        end

        // Attempt one extra write while full
        wr_en = 1;
        wr_data = 8'hFF;
        @(posedge clk);
        wr_en = 0;
        @(posedge clk); #1;
        if (!full || count !== 4) begin
            $display("FAIL: overflow broke FIFO, full=%0b count=%0d", full, count);
            err_cnt = err_cnt + 1;
        end else $display("PASS: overflow protection — full & count unchanged");

        // Verify no corruption: first element should still be A1
        #1;
        if (rd_data !== 8'hA1) begin
            $display("FAIL: overflow corrupted head, rd_data=%h expected A1", rd_data);
            err_cnt = err_cnt + 1;
        end else $display("PASS: overflow did not corrupt data");

        // ----------------------------------------------------------------
        // Test 8: Underflow protection — read when empty; empty stays 1,
        //         count stays 0.
        // ----------------------------------------------------------------
        flush = 1; @(posedge clk); flush = 0; @(posedge clk); #1;
        if (!empty) begin
            $display("FAIL: FIFO not empty before underflow test");
            err_cnt = err_cnt + 1;
        end

        rd_en = 1;
        @(posedge clk);
        rd_en = 0;
        @(posedge clk); #1;
        if (!empty || count !== 0) begin
            $display("FAIL: underflow broke FIFO, empty=%0b count=%0d", empty, count);
            err_cnt = err_cnt + 1;
        end else $display("PASS: underflow protection — empty & count unchanged");

        // ----------------------------------------------------------------
        // Test 9: almost_full flag — write 3 entries into DEPTH=4 FIFO,
        //         almost_full should assert (DEPTH-1 threshold).
        // ----------------------------------------------------------------
        flush = 1; @(posedge clk); flush = 0; @(posedge clk);

        wr_en = 1;
        wr_data = 8'hB1; @(posedge clk);
        wr_data = 8'hB2; @(posedge clk);
        wr_data = 8'hB3; @(posedge clk);
        wr_en = 0;
        @(posedge clk); #1;
        if (count !== 3) begin
            $display("FAIL: almost_full setup count=%0d expected 3", count);
            err_cnt = err_cnt + 1;
        end
        if (!almost_full) begin
            $display("FAIL: almost_full=%0b with 3 of 4 entries (expected 1)", almost_full);
            err_cnt = err_cnt + 1;
        end else $display("PASS: almost_full asserted at count=3");

        // ----------------------------------------------------------------
        // Summary
        // ----------------------------------------------------------------
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
