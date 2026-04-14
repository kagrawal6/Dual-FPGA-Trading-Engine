`timescale 1ns / 1ps

module tb_lfsr32();

    import hft_pkg::*;

    logic        clk, rst_n, enable, load;
    logic [31:0] seed_in, rand_out;
    integer err_cnt;

    always #5 clk = ~clk;

    lfsr32 dut (
        .clk     (clk),
        .rst_n   (rst_n),
        .enable  (enable),
        .load    (load),
        .seed_in (seed_in),
        .rand_out(rand_out)
    );

    // Golden model: Galois LFSR with TAPS=0x00400007
    //   if lsb==1: next = (reg >> 1) ^ 0x00400007
    //   if lsb==0: next = (reg >> 1)

    initial begin
        clk = 0; rst_n = 0; enable = 0; load = 0; seed_in = '0;
        err_cnt = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // ----------------------------------------------------------------
        // Test 1: Reset — LFSR must not stick at 0; expect rand_out = 1.
        // ----------------------------------------------------------------
        @(posedge clk); #1;
        if (rand_out !== 32'h0000_0001) begin
            $display("FAIL: rand_out=%h after reset (expected 0x00000001)", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: reset state = 0x00000001");

        // ----------------------------------------------------------------
        // Test 2: Synchronous load — seed 0xDEADBEEF appears next cycle.
        // ----------------------------------------------------------------
        load = 1; seed_in = 32'hDEAD_BEEF;
        @(posedge clk);
        load = 0;
        #1;
        if (rand_out !== 32'hDEAD_BEEF) begin
            $display("FAIL: after load rand_out=%h (expected DEADBEEF)", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: loaded seed 0xDEADBEEF");

        // ----------------------------------------------------------------
        // Test 3: One enabled clock — Galois step (odd seed).
        //         0xDEADBEEF >> 1 = 0x6F56DF77, ^ TAPS = 0x6F16DF70
        // ----------------------------------------------------------------
        enable = 1;
        @(posedge clk);
        enable = 0;
        #1;
        if (rand_out !== 32'h6F16_DF70) begin
            $display("FAIL: after first step rand_out=%h (expected 6F16DF70)", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: first step = 0x6F16DF70");

        // ----------------------------------------------------------------
        // Test 4: Second enabled step (even state) — right shift only.
        //         0x6F16DF70 >> 1 = 0x378B6FB8
        // ----------------------------------------------------------------
        enable = 1;
        @(posedge clk);
        enable = 0;
        #1;
        if (rand_out !== 32'h378B_6FB8) begin
            $display("FAIL: after second step rand_out=%h (expected 378B6FB8)", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: second step = 0x378B6FB8");

        // ----------------------------------------------------------------
        // Test 5: Zero seed remap — loading 0 should remap to 1.
        // ----------------------------------------------------------------
        load = 1; seed_in = 32'h0;
        @(posedge clk);
        load = 0;
        #1;
        if (rand_out !== 32'h0000_0001) begin
            $display("FAIL: zero-seed load rand_out=%h (expected 1)", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: zero seed remapped to 1");

        // ----------------------------------------------------------------
        // Test 6: Enable-gating — with enable=0, rand_out must not change
        //         over 5 cycles.
        // ----------------------------------------------------------------
        load = 1; seed_in = 32'hCAFE_BABE;
        @(posedge clk);
        load = 0;
        #1;
        begin : enable_gate_blk
            logic [31:0] frozen_val;
            integer i;
            integer gate_ok;
            frozen_val = rand_out;
            gate_ok = 1;
            enable = 0;
            for (i = 0; i < 5; i = i + 1) begin
                @(posedge clk); #1;
                if (rand_out !== frozen_val) begin
                    gate_ok = 0;
                end
            end
            if (!gate_ok) begin
                $display("FAIL: rand_out changed with enable=0");
                err_cnt = err_cnt + 1;
            end else $display("PASS: enable-gating holds value for 5 cycles");
        end

        // ----------------------------------------------------------------
        // Test 7: Determinism — load same seed, run 10 steps, reload,
        //         run 10 steps; sequences must match.
        // ----------------------------------------------------------------
        begin : determinism_blk
            logic [31:0] seq1 [0:9];
            logic [31:0] seq2 [0:9];
            integer i;
            integer match;

            load = 1; seed_in = 32'h1234_5678;
            @(posedge clk);
            load = 0;
            enable = 1;
            for (i = 0; i < 10; i = i + 1) begin
                @(posedge clk); #1;
                seq1[i] = rand_out;
            end
            enable = 0;

            load = 1; seed_in = 32'h1234_5678;
            @(posedge clk);
            load = 0;
            enable = 1;
            for (i = 0; i < 10; i = i + 1) begin
                @(posedge clk); #1;
                seq2[i] = rand_out;
            end
            enable = 0;

            match = 1;
            for (i = 0; i < 10; i = i + 1) begin
                if (seq1[i] !== seq2[i]) match = 0;
            end
            if (!match) begin
                $display("FAIL: determinism — sequences differ on reload");
                err_cnt = err_cnt + 1;
            end else $display("PASS: determinism — identical sequences from same seed");
        end

        // ----------------------------------------------------------------
        // Test 8: All-ones seed (0xFFFFFFFF).
        //         First step: (0xFFFFFFFF >> 1) ^ TAPS
        //                   = 0x7FFFFFFF ^ 0x00400007 = 0x7FBFFFF8 (odd, xor)
        //         Wait — 0xFFFFFFFF is odd so XOR applies.
        // ----------------------------------------------------------------
        load = 1; seed_in = 32'hFFFF_FFFF;
        @(posedge clk);
        load = 0;
        enable = 1;
        @(posedge clk);
        enable = 0;
        #1;
        if (rand_out !== 32'h7FBF_FFF8) begin
            $display("FAIL: all-ones seed step rand_out=%h (expected 7FBFFFF8)", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: all-ones seed first step = 0x7FBFFFF8");

        // ----------------------------------------------------------------
        // Test 9: Never-zero — run 100 enabled cycles from seed 0xDEADBEEF
        //         and verify rand_out never equals 0.
        // ----------------------------------------------------------------
        load = 1; seed_in = 32'hDEAD_BEEF;
        @(posedge clk);
        load = 0;
        enable = 1;
        begin : never_zero_blk
            integer i;
            integer saw_zero;
            saw_zero = 0;
            for (i = 0; i < 100; i = i + 1) begin
                @(posedge clk); #1;
                if (rand_out === 32'h0) saw_zero = 1;
            end
            if (saw_zero) begin
                $display("FAIL: rand_out hit zero during 100-cycle run");
                err_cnt = err_cnt + 1;
            end else $display("PASS: never-zero — no zero output in 100 cycles");
        end
        enable = 0;

        // ----------------------------------------------------------------
        // Summary
        // ----------------------------------------------------------------
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
