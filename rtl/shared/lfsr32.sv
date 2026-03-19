// ============================================================================
// Module: lfsr32
// 32-bit Galois LFSR with maximal-length polynomial (x^32+x^22+x^2+x+1).
// Produces one pseudo-random 32-bit value per enabled clock cycle.
// Seed is loaded via the load/seed_in interface on the IDLE→RUNNING transition.
// ============================================================================

`timescale 1ns / 1ps

module lfsr32
    import hft_pkg::*;
(
    input  logic        clk,
    input  logic        rst_n,
    input  logic        enable,      // advance LFSR one step per cycle
    input  logic        load,        // synchronous seed load (1-cycle pulse)
    input  logic [31:0] seed_in,     // must be non-zero
    output logic [31:0] rand_out     // current LFSR state = pseudo-random value
);

    // TODO: Implementation
    // Galois LFSR with tap mask LFSR_TAPS = 32'h00400007
    // if (load)        lfsr <= seed_in;
    // else if (enable) lfsr <= lfsr[0] ? (lfsr >> 1) ^ LFSR_TAPS : (lfsr >> 1);

endmodule
