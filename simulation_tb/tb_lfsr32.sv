`timescale 1ns / 1ps

module tb_lfsr32();

    import hft_pkg::*;

    logic        clk, rst_n, enable, load;
    logic [31:0] seed_in, rand_out;
    integer err_cnt = 0;

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
        #20; rst_n = 1;
        @(posedge clk);

        // ---- T1: Reset state = 1 ----
        @(posedge clk); #1;
        if (rand_out !== 32'h0000_0001) begin
            $display("FAIL: T1 rand_out=%h after reset, expected 1", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T1 reset state = 0x00000001");

        // ---- T2: Load seed 0xDEADBEEF ----
        load = 1; seed_in = 32'hDEAD_BEEF;
        @(posedge clk);
        load = 0;
        #1;
        if (rand_out !== 32'hDEAD_BEEF) begin
            $display("FAIL: T2 rand_out=%h, expected DEADBEEF", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T2 loaded seed 0xDEADBEEF");

        // ---- T3: Enable 1 cycle → expect 0x6F16DF70 ----
        // 0xDEADBEEF is odd → (>>1) ^ TAPS = 0x6F56DF77 ^ 0x00400007 = 0x6F16DF70
        enable = 1;
        @(posedge clk);
        enable = 0;
        #1;
        if (rand_out !== 32'h6F16_DF70) begin
            $display("FAIL: T3 rand_out=%h, expected 6F16DF70", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T3 step1 = 0x6F16DF70");

        // ---- T4: Enable 1 more → expect 0x378B6FB8 ----
        // 0x6F16DF70 is even → >>1 = 0x378B6FB8
        enable = 1;
        @(posedge clk);
        enable = 0;
        #1;
        if (rand_out !== 32'h378B_6FB8) begin
            $display("FAIL: T4 rand_out=%h, expected 378B6FB8", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T4 step2 = 0x378B6FB8");

        // ---- T5: Load zero → remaps to 1 ----
        load = 1; seed_in = 32'h0;
        @(posedge clk);
        load = 0;
        #1;
        if (rand_out !== 32'h0000_0001) begin
            $display("FAIL: T5 rand_out=%h, expected 1 (zero remap)", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T5 zero seed remapped to 1");

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
