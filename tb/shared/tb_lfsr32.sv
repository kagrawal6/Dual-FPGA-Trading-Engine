// ============================================================================
// Testbench: tb_lfsr32
// Tests the 32-bit Galois LFSR (lfsr32) module: seed loading, enable/advance,
// zero-seed remap, and golden-vector sequence (matches Python / spec).
//
// ModelSim waveform tips:
//   - Add to wave: clk, rst_n, enable, load, seed_in, dut.lfsr_reg, rand_out
//   - Optional: vsim -voptargs=+acc work.tb_lfsr32:dut for full internal visibility
//   - VCD is written to tb_lfsr32.vcd in the simulation working directory
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

    int err_count = 0;

    // Clock generation (100 MHz)
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

    // Golden vectors: Galois step (lfsr[0] ? (lfsr>>1)^LFSR_TAPS : lfsr>>1),
    // starting from seed 32'h1, first eight *states seen after each advancing
    // clock edge* when load then repeated enable — see task run_golden_check.
    localparam int GOLDEN_LEN = 8;
    localparam logic [31:0] GOLDEN_AFTER_SEED1 [GOLDEN_LEN] = '{
        32'h0000_0001,  // after load cycle (hold)
        32'h0040_0007,  // after 1st enable
        32'h0060_0004,  // after 2nd enable
        32'h0030_0002,  // after 3rd enable
        32'h0018_0001,  // after 4th enable
        32'h004c_0007,  // after 5th enable
        32'h0066_0004,  // after 6th enable
        32'h0033_0002   // after 7th enable
    };

    task automatic check(string msg, logic pass);
        if (!pass) begin
            $error("FAIL: %s", msg);
            err_count++;
        end
    endtask

    // Waveform dump (ModelSim, Icarus, Verilator-compatible subset)
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

    // After reset, DUT holds lfsr_reg == 1 until load or enable changes it.
    task automatic run_reset_check();
        check("After async reset, state must be 1", rand_out == 32'h1);
    endtask

    task automatic run_load_hold_check();
        seed_in = 32'hCAFE_BABE;
        load    = 1'b1;
        @(posedge clk);
        load = 1'b0;
        @(posedge clk);
        check("After load, rand_out must match seed", rand_out == 32'hCAFE_BABE);
        // Hold with enable low
        repeat (3) @(posedge clk);
        check("With enable low, state must hold", rand_out == 32'hCAFE_BABE);
    endtask

    task automatic run_golden_check();
        int k;
        enable  = 1'b0;
        seed_in = 32'h1;
        load    = 1'b1;
        @(posedge clk);
        load = 1'b0;
        @(posedge clk);
        for (k = 0; k < GOLDEN_LEN; k++) begin
            check(
                $sformatf("Golden vector %0d: exp %08h got %08h", k, GOLDEN_AFTER_SEED1[k], rand_out),
                rand_out == GOLDEN_AFTER_SEED1[k]
            );
            if (k != GOLDEN_LEN - 1) begin
                enable = 1'b1;
                @(posedge clk);
            end
        end
        enable = 1'b0;
    endtask

    task automatic run_never_zero_stress();
        int i;
        seed_in = 32'hDEAD_BEEF;
        load    = 1'b1;
        @(posedge clk);
        load   = 1'b0;
        enable = 1'b1;
        for (i = 0; i < 500; i++) begin
            @(posedge clk);
            check($sformatf("Stress cycle %0d: output non-zero", i), rand_out != 32'h0);
        end
        enable = 1'b0;
    endtask

    task automatic run_zero_seed_remap();
        seed_in = 32'h0;
        load    = 1'b1;
        @(posedge clk);
        load = 1'b0;
        @(posedge clk);
        check("Zero seed remapped to 1", rand_out == 32'h1);
    endtask

    task automatic run_determinism_check();
        logic [31:0] seq [10];
        int i;
        seed_in = 32'hA5A5_5A5A;
        load    = 1'b1;
        @(posedge clk);
        load   = 1'b0;
        enable = 1'b1;
        for (i = 0; i < 10; i++) begin
            @(posedge clk);
            seq[i] = rand_out;
        end
        enable = 1'b0;
        // Reload same seed and replay
        seed_in = 32'hA5A5_5A5A;
        load    = 1'b1;
        @(posedge clk);
        load   = 1'b0;
        enable = 1'b1;
        for (i = 0; i < 10; i++) begin
            @(posedge clk);
            check($sformatf("Determinism idx %0d", i), rand_out == seq[i]);
        end
        enable = 1'b0;
    endtask

    initial begin
        wait_reset();
        run_reset_check();

        run_load_hold_check();
        run_golden_check();
        run_never_zero_stress();
        run_zero_seed_remap();
        run_determinism_check();

        if (err_count == 0)
            $display("tb_lfsr32: PASS (all checks passed, VCD: tb_lfsr32.vcd)");
        else
            $display("tb_lfsr32: FAIL (%0d errors)", err_count);

        $finish;
    end

endmodule
