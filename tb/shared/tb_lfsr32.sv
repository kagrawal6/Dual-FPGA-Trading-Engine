// ============================================================================
// Testbench: tb_lfsr32
// Tests the 32-bit Galois LFSR (lfsr32) module: seed loading, enable/advance,
// and pseudo-random output sequence.
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

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    lfsr32 dut (
        .clk      (clk),
        .rst_n    (rst_n),
        .enable   (enable),
        .load     (load),
        .seed_in  (seed_in),
        .rand_out (rand_out)
    );

    initial begin
        // TODO: Add test stimulus
        $finish;
    end

endmodule
