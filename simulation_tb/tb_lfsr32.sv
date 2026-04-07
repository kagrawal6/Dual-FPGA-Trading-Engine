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

        // Reset: LFSR must not stick at 0 (illegal state); expect rand_out = 1.
        @(posedge clk); #1;
        if (rand_out !== 32'h0000_0001) begin
            $display("FAIL: rand_out=%h after reset (expected 0x00000001)", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: reset state = 0x00000001");

        // Synchronous load: seed_in = 0xDEADBEEF should appear on rand_out next cycle.
        load = 1; seed_in = 32'hDEAD_BEEF;
        @(posedge clk);
        load = 0;
        #1;
        if (rand_out !== 32'hDEAD_BEEF) begin
            $display("FAIL: after load rand_out=%h (expected DEADBEEF)", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: loaded seed 0xDEADBEEF");

        // One enabled clock: Galois step (odd seed) -> golden value 0x6F16DF70.
        // 0xDEADBEEF is odd -> (>>1) ^ TAPS = 0x6F56DF77 ^ 0x00400007 = 0x6F16DF70
        enable = 1;
        @(posedge clk);
        enable = 0;
        #1;
        if (rand_out !== 32'h6F16_DF70) begin
            $display("FAIL: after first step rand_out=%h (expected 6F16DF70)", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: first step = 0x6F16DF70");

        // Second enabled step (even state): right shift only -> 0x378B6FB8 (matches golden script).
        // 0x6F16DF70 is even -> >>1 = 0x378B6FB8
        enable = 1;
        @(posedge clk);
        enable = 0;
        #1;
        if (rand_out !== 32'h378B_6FB8) begin
            $display("FAIL: after second step rand_out=%h (expected 378B6FB8)", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: second step = 0x378B6FB8");

        // load with seed 0: RTL remaps to 1 so the register never locks at zero.
        load = 1; seed_in = 32'h0;
        @(posedge clk);
        load = 0;
        #1;
        if (rand_out !== 32'h0000_0001) begin
            $display("FAIL: zero-seed load rand_out=%h (expected 1)", rand_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: zero seed remapped to 1");

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
