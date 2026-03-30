// ============================================================================
// Testbench: tb_lfsr32
// Multi-seed golden vectors, adversarial load/enable, zero-seed remap,
// all-ones seed, rapid load toggling, determinism replay.
// Golden vectors from golden_model/gen_board_a_vectors.py.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_lfsr32;

    logic        clk;
    logic        rst_n;
    logic        enable;
    logic        load;
    logic [31:0] seed_in;
    logic [31:0] rand_out;

    int pass_count = 0;
    int fail_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

    lfsr32 dut (
        .clk      (clk),
        .rst_n    (rst_n),
        .enable   (enable),
        .load     (load),
        .seed_in  (seed_in),
        .rand_out (rand_out)
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
            $error("FAIL: %s — got %08h, exp %08h", msg, actual, expected);
            fail_count++;
        end
    endtask

    initial begin
        $dumpfile("tb_lfsr32.vcd");
        $dumpvars(0, tb_lfsr32);
    end

    task automatic wait_reset();
        rst_n   = 1'b0;
        enable  = 1'b0;
        load    = 1'b0;
        seed_in = 32'h0;
        repeat (4) @(posedge clk);
        rst_n = 1'b1;
        @(posedge clk);
    endtask

    // ── Golden vectors: seed 0xDEADBEEF, 16 steps ──
    localparam int GVLEN = 16;
    localparam logic [31:0] GV_DEADBEEF [GVLEN] = '{
        32'h6F16DF70, 32'h378B6FB8, 32'h1BC5B7DC, 32'h0DE2DBEE,
        32'h06F16DF7, 32'h0338B6FC, 32'h019C5B7E, 32'h00CE2DBF,
        32'h002716D8, 32'h00138B6C, 32'h0009C5B6, 32'h0004E2DB,
        32'h0042716A, 32'h002138B5, 32'h00509C5D, 32'h00684E29
    };

    // ── Golden vectors: seed 0x00000001, 16 steps ──
    localparam logic [31:0] GV_SEED1 [GVLEN] = '{
        32'h00400007, 32'h00600004, 32'h00300002, 32'h00180001,
        32'h004C0007, 32'h00660004, 32'h00330002, 32'h00198001,
        32'h004CC007, 32'h00666004, 32'h00333002, 32'h00199801,
        32'h004CCC07, 32'h00666604, 32'h00333302, 32'h00199981
    };

    // ── Test: reset state ──
    task automatic test_reset();
        $display("--- test_reset ---");
        check32("After reset, rand_out == 1", rand_out, 32'h0000_0001);
    endtask

    // ── Test: load + hold ──
    task automatic test_load_hold();
        $display("--- test_load_hold ---");
        seed_in = 32'hCAFE_BABE;
        load = 1'b1;
        @(posedge clk);
        load = 1'b0;
        @(posedge clk);
        check32("After load, seed latched", rand_out, 32'hCAFE_BABE);
        repeat (5) @(posedge clk);
        check32("enable=0: state holds", rand_out, 32'hCAFE_BABE);
    endtask

    // ── Test: golden vectors for seed 0xDEADBEEF ──
    task automatic test_golden_deadbeef();
        $display("--- test_golden_deadbeef ---");
        seed_in = 32'hDEAD_BEEF;
        load = 1'b1;
        @(posedge clk);
        load = 1'b0;
        @(posedge clk);
        check32("seed DEADBEEF loaded", rand_out, 32'hDEAD_BEEF);
        enable = 1'b1;
        for (int i = 0; i < GVLEN; i++) begin
            @(posedge clk);
            check32($sformatf("DEADBEEF step[%0d]", i), rand_out, GV_DEADBEEF[i]);
        end
        enable = 1'b0;
    endtask

    // ── Test: golden vectors for seed 1 ──
    task automatic test_golden_seed1();
        $display("--- test_golden_seed1 ---");
        seed_in = 32'h0000_0001;
        load = 1'b1;
        @(posedge clk);
        load = 1'b0;
        @(posedge clk);
        enable = 1'b1;
        for (int i = 0; i < GVLEN; i++) begin
            @(posedge clk);
            check32($sformatf("SEED1 step[%0d]", i), rand_out, GV_SEED1[i]);
        end
        enable = 1'b0;
    endtask

    // ── Test: zero-seed remap ──
    task automatic test_zero_seed_remap();
        $display("--- test_zero_seed_remap ---");
        seed_in = 32'h0;
        load = 1'b1;
        @(posedge clk);
        load = 1'b0;
        @(posedge clk);
        check32("Zero seed remapped to 1", rand_out, 32'h0000_0001);
        // Should produce same sequence as seed 1
        enable = 1'b1;
        for (int i = 0; i < 8; i++) begin
            @(posedge clk);
            check32($sformatf("Zero remap step[%0d]", i), rand_out, GV_SEED1[i]);
        end
        enable = 1'b0;
    endtask

    // ── Test: all-ones seed ──
    task automatic test_all_ones_seed();
        $display("--- test_all_ones_seed ---");
        seed_in = 32'hFFFF_FFFF;
        load = 1'b1;
        @(posedge clk);
        load = 1'b0;
        @(posedge clk);
        check32("All-ones seed loaded", rand_out, 32'hFFFF_FFFF);
        enable = 1'b1;
        for (int i = 0; i < 100; i++) begin
            @(posedge clk);
            check($sformatf("All-ones step[%0d] non-zero", i), rand_out != 32'h0);
        end
        enable = 1'b0;
    endtask

    // ── Test: load during enable (load takes priority) ──
    task automatic test_load_during_enable();
        $display("--- test_load_during_enable ---");
        seed_in = 32'hDEAD_BEEF;
        load = 1'b1;
        @(posedge clk);
        load = 1'b0;
        enable = 1'b1;
        repeat (5) @(posedge clk);
        // Now load a new seed while enable is high
        seed_in = 32'h0000_0001;
        load = 1'b1;
        @(posedge clk);
        load = 1'b0;
        @(posedge clk);
        // Should have clean cut to new sequence
        check32("Load during enable: seed 1 loaded", rand_out, 32'h0000_0001);
        @(posedge clk);
        check32("Load during enable: first step matches seed1", rand_out, GV_SEED1[0]);
        enable = 1'b0;
    endtask

    // ── Test: simultaneous load + enable (load should win) ──
    task automatic test_simultaneous_load_enable();
        $display("--- test_simultaneous_load_enable ---");
        seed_in = 32'hA5A5_5A5A;
        load = 1'b1;
        enable = 1'b1;
        @(posedge clk);
        load = 1'b0;
        @(posedge clk);
        check32("Simultaneous load+enable: load wins", rand_out, 32'hA5A5_5A5A);
        enable = 1'b0;
    endtask

    // ── Test: rapid load/unload toggling ──
    task automatic test_rapid_toggle();
        $display("--- test_rapid_toggle ---");
        enable = 1'b0;
        for (int i = 0; i < 10; i++) begin
            seed_in = 32'h1000_0000 + i;
            load = 1'b1;
            @(posedge clk);
            load = 1'b0;
            @(posedge clk);
            check($sformatf("Rapid toggle[%0d]: non-zero", i), rand_out != 32'h0);
        end
        // Verify last seed stuck
        check32("Rapid toggle: last seed", rand_out, 32'h1000_0009);
    endtask

    // ── Test: determinism replay ──
    task automatic test_determinism();
        logic [31:0] seq_a [20];
        $display("--- test_determinism ---");
        seed_in = 32'hBAAD_F00D;
        load = 1'b1;
        @(posedge clk);
        load = 1'b0;
        enable = 1'b1;
        for (int i = 0; i < 20; i++) begin
            @(posedge clk);
            seq_a[i] = rand_out;
        end
        enable = 1'b0;
        // Replay
        seed_in = 32'hBAAD_F00D;
        load = 1'b1;
        @(posedge clk);
        load = 1'b0;
        enable = 1'b1;
        for (int i = 0; i < 20; i++) begin
            @(posedge clk);
            check32($sformatf("Determinism[%0d]", i), rand_out, seq_a[i]);
        end
        enable = 1'b0;
    endtask

    // ── Test: never-zero stress ──
    task automatic test_never_zero();
        $display("--- test_never_zero ---");
        seed_in = 32'hDEAD_BEEF;
        load = 1'b1;
        @(posedge clk);
        load = 1'b0;
        enable = 1'b1;
        for (int i = 0; i < 1000; i++) begin
            @(posedge clk);
            check($sformatf("Stress[%0d] non-zero", i), rand_out != 32'h0);
        end
        enable = 1'b0;
    endtask

    initial begin
        wait_reset();
        test_reset();
        test_load_hold();
        test_golden_deadbeef();
        test_golden_seed1();
        test_zero_seed_remap();
        test_all_ones_seed();
        test_load_during_enable();
        test_simultaneous_load_enable();
        test_rapid_toggle();
        test_determinism();
        test_never_zero();

        $display("\n===================================");
        if (fail_count == 0)
            $display("tb_lfsr32: PASS (%0d checks passed)", pass_count);
        else begin
            $display("tb_lfsr32: FAIL (%0d passed, %0d failed)", pass_count, fail_count);
            $fatal;
        end
        $display("===================================");
        $finish;
    end

endmodule
