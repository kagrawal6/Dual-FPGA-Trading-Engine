// ============================================================================
// Testbench: tb_sync_fifo
// Concurrent rd+wr, overflow guard, underflow guard, flush during write,
// almost_full threshold, small DEPTH=4 corner cases.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_sync_fifo;

    // ── Default-size FIFO (DEPTH=64) ──
    logic               clk;
    logic               rst_n;
    logic               flush;
    logic               wr_en;
    logic [127:0]       wr_data;
    logic               full;
    logic               rd_en;
    logic [127:0]       rd_data;
    logic               empty;
    logic               almost_full;
    logic [$clog2(64):0] count;

    int pass_count = 0;
    int fail_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

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

    // ── Small FIFO (DEPTH=4) for corner cases ──
    logic               sm_flush, sm_wr_en, sm_full, sm_rd_en, sm_empty, sm_af;
    logic [127:0]       sm_wr_data, sm_rd_data;
    logic [$clog2(4):0] sm_count;

    sync_fifo #(
        .DATA_W             (128),
        .DEPTH              (4),
        .ALMOST_FULL_THRESH (3)
    ) dut_small (
        .clk         (clk),
        .rst_n       (rst_n),
        .flush       (sm_flush),
        .wr_en       (sm_wr_en),
        .wr_data     (sm_wr_data),
        .full        (sm_full),
        .rd_en       (sm_rd_en),
        .rd_data     (sm_rd_data),
        .empty       (sm_empty),
        .almost_full (sm_af),
        .count       (sm_count)
    );

    task automatic check(string msg, logic cond);
        if (cond) pass_count++;
        else begin
            $error("FAIL: %s", msg);
            fail_count++;
        end
    endtask

    task automatic check32(string msg, logic [31:0] actual, logic [31:0] expected);
        if (actual === expected) pass_count++;
        else begin
            $error("FAIL: %s — got %0d, exp %0d", msg, actual, expected);
            fail_count++;
        end
    endtask

    initial begin
        $dumpfile("tb_sync_fifo.vcd");
        $dumpvars(0, tb_sync_fifo);
    end

    initial begin
        rst_n = 0; flush = 0; wr_en = 0; rd_en = 0; wr_data = '0;
        sm_flush = 0; sm_wr_en = 0; sm_rd_en = 0; sm_wr_data = '0;
        #100;
        rst_n = 1;
        @(posedge clk); #1;

        // ─────────────────────────────────────────────────────
        // 1) Post-reset state
        // ─────────────────────────────────────────────────────
        $display("--- test_reset ---");
        check("empty after reset", empty == 1'b1);
        check32("count==0 after reset", count, 0);
        check("!full after reset", full == 1'b0);

        // ─────────────────────────────────────────────────────
        // 2) Fill/drain ordering
        // ─────────────────────────────────────────────────────
        $display("--- test_fill_drain ---");
        for (int i = 1; i <= 10; i++) begin
            wr_data = 128'(i);
            wr_en = 1'b1;
            @(posedge clk); #1;
        end
        wr_en = 1'b0;
        @(posedge clk); #1;
        check32("count after 10 writes", count, 10);
        check("!empty after writes", empty == 1'b0);

        for (int i = 1; i <= 10; i++) begin
            check($sformatf("rd_data[%0d]", i), rd_data === 128'(i));
            rd_en = 1'b1;
            @(posedge clk); #1;
        end
        rd_en = 1'b0;
        @(posedge clk); #1;
        check("empty after drain", empty == 1'b1);

        // ─────────────────────────────────────────────────────
        // 3) Concurrent rd+wr at steady state
        // ─────────────────────────────────────────────────────
        $display("--- test_concurrent_rdwr ---");
        // Fill to 32
        for (int i = 0; i < 32; i++) begin
            wr_data = 128'(i + 100);
            wr_en = 1'b1;
            @(posedge clk); #1;
        end
        wr_en = 1'b0;
        @(posedge clk); #1;
        check32("count==32 before concurrent", count, 32);

        // Simultaneous rd+wr for 20 cycles
        for (int i = 0; i < 20; i++) begin
            wr_data = 128'(i + 200);
            wr_en = 1'b1;
            rd_en = 1'b1;
            @(posedge clk); #1;
            check32($sformatf("concurrent[%0d] count stable", i), count, 32);
        end
        wr_en = 1'b0;
        rd_en = 1'b0;
        @(posedge clk); #1;
        check32("count still 32 after concurrent", count, 32);
        // Drain and verify ordering: first 12 should be [112..131], then [200..219]
        rd_en = 1'b1;
        for (int i = 0; i < 32; i++) begin
            @(posedge clk); #1;
        end
        rd_en = 1'b0;
        @(posedge clk); #1;
        check("empty after full drain", empty == 1'b1);

        // ─────────────────────────────────────────────────────
        // 4) Overflow guard
        // ─────────────────────────────────────────────────────
        $display("--- test_overflow ---");
        for (int i = 0; i < 64; i++) begin
            wr_data = 128'(i);
            wr_en = 1'b1;
            @(posedge clk); #1;
        end
        wr_en = 1'b0;
        @(posedge clk); #1;
        check("full at 64", full == 1'b1);
        check32("count==64", count, 64);

        // Write while full — should not corrupt
        wr_data = 128'hDEAD;
        wr_en = 1'b1;
        @(posedge clk); #1;
        @(posedge clk); #1;
        wr_en = 1'b0;
        @(posedge clk); #1;
        check32("count still 64 after overflow attempt", count, 64);
        check("still full", full == 1'b1);
        // First element should still be 0 (not DEAD)
        check("rd_data not corrupted by overflow", rd_data === 128'h0);

        // Flush for next test
        flush = 1'b1;
        @(posedge clk); #1;
        flush = 1'b0;
        @(posedge clk); #1;
        check("flush empties FIFO", empty == 1'b1);

        // ─────────────────────────────────────────────────────
        // 5) Underflow guard
        // ─────────────────────────────────────────────────────
        $display("--- test_underflow ---");
        check("empty before underflow test", empty == 1'b1);
        rd_en = 1'b1;
        @(posedge clk); #1;
        @(posedge clk); #1;
        rd_en = 1'b0;
        @(posedge clk); #1;
        check32("count still 0 after underflow", count, 0);
        check("still empty after underflow", empty == 1'b1);
        // Verify FIFO still works after underflow
        wr_data = 128'hBEEF;
        wr_en = 1'b1;
        @(posedge clk); #1;
        wr_en = 1'b0;
        @(posedge clk); #1;
        check("FIFO works after underflow", rd_data === 128'hBEEF);
        rd_en = 1'b1;
        @(posedge clk); #1;
        rd_en = 1'b0;
        @(posedge clk); #1;

        // ─────────────────────────────────────────────────────
        // 6) Flush during write
        // ─────────────────────────────────────────────────────
        $display("--- test_flush_during_write ---");
        wr_data = 128'hAAAA;
        wr_en = 1'b1;
        flush = 1'b1;
        @(posedge clk); #1;
        wr_en = 1'b0;
        flush = 1'b0;
        @(posedge clk); #1;
        check("flush during write: empty", empty == 1'b1);
        check32("flush during write: count==0", count, 0);

        // ─────────────────────────────────────────────────────
        // 7) Almost_full threshold (transition at count=60)
        // ─────────────────────────────────────────────────────
        $display("--- test_almost_full ---");
        for (int i = 0; i < 59; i++) begin
            wr_data = 128'(i);
            wr_en = 1'b1;
            @(posedge clk); #1;
        end
        wr_en = 1'b0;
        @(posedge clk); #1;
        check32("count==59", count, 59);
        check("almost_full=0 at 59", almost_full == 1'b0);

        wr_data = 128'd59;
        wr_en = 1'b1;
        @(posedge clk); #1;
        wr_en = 1'b0;
        @(posedge clk); #1;
        check32("count==60", count, 60);
        check("almost_full=1 at 60", almost_full == 1'b1);
        check("not full at 60", full == 1'b0);

        flush = 1'b1;
        @(posedge clk); #1;
        flush = 1'b0;
        @(posedge clk); #1;

        // ─────────────────────────────────────────────────────
        // 8) Small FIFO (DEPTH=4) corner cases
        // ─────────────────────────────────────────────────────
        $display("--- test_small_fifo ---");
        check("small: empty after reset", sm_empty == 1'b1);

        // Fill to 4
        for (int i = 0; i < 4; i++) begin
            sm_wr_data = 128'(i + 1000);
            sm_wr_en = 1'b1;
            @(posedge clk); #1;
        end
        sm_wr_en = 1'b0;
        @(posedge clk); #1;
        check("small: full at 4", sm_full == 1'b1);
        check32("small: count==4", sm_count, 4);
        check("small: almost_full at 4", sm_af == 1'b1);

        // Drain and verify order
        for (int i = 0; i < 4; i++) begin
            check($sformatf("small: rd[%0d]", i), sm_rd_data === 128'(i + 1000));
            sm_rd_en = 1'b1;
            @(posedge clk); #1;
        end
        sm_rd_en = 1'b0;
        @(posedge clk); #1;
        check("small: empty after drain", sm_empty == 1'b1);

        // Concurrent rd+wr on small FIFO
        sm_wr_data = 128'h5555;
        sm_wr_en = 1'b1;
        @(posedge clk); #1;
        sm_wr_en = 1'b0;
        @(posedge clk); #1;
        // Now simultaneous rd+wr
        sm_wr_data = 128'h6666;
        sm_wr_en = 1'b1;
        sm_rd_en = 1'b1;
        @(posedge clk); #1;
        sm_wr_en = 1'b0;
        sm_rd_en = 1'b0;
        @(posedge clk); #1;
        check32("small: concurrent count==1", sm_count, 1);
        check("small: concurrent rd_data", sm_rd_data === 128'h6666);
        sm_rd_en = 1'b1;
        @(posedge clk); #1;
        sm_rd_en = 1'b0;
        @(posedge clk); #1;

        // ─────────────────────────────────────────────────────
        // Summary
        // ─────────────────────────────────────────────────────
        $display("\n===================================");
        if (fail_count == 0)
            $display("tb_sync_fifo: PASS (%0d checks passed)", pass_count);
        else begin
            $display("tb_sync_fifo: FAIL (%0d passed, %0d failed)", pass_count, fail_count);
            $fatal;
        end
        $display("===================================");
        $finish;
    end

endmodule
