// ============================================================================
// Module: lfsr32
// 32-bit Galois LFSR with maximal-length polynomial (x^32+x^22+x^2+x+1).
// Produces one pseudo-random 32-bit value per enabled clock cycle.
// Seed is loaded via the load/seed_in interface on the IDLE→RUNNING transition.
// ============================================================================

`timescale 1ns / 1ps

module lfsr32
(
    input  logic        clk,
    input  logic        rst_n,
    input  logic        enable,      // advance LFSR one step per cycle
    input  logic        load,        // synchronous seed load (1-cycle pulse)
    input  logic [31:0] seed_in,     // must be non-zero (0 is remapped to 1)
    output logic [31:0] rand_out     // current LFSR state = pseudo-random value
);

    // -------------------------------------------------------------------------
    // Internal state
    // -------------------------------------------------------------------------
    // Local copy of the LFSR taps (same as hft_pkg::LFSR_TAPS = 32'h00400007).
    localparam logic [31:0] LFSR_TAPS = 32'h0040_0007;

    // The visible pseudo-random word is the full register (same as market_sim
    // raw_step = rand_out[4:0]).  Kept in one always_ff block so ModelSim
    // waveforms show a single clean state vector advancing in lockstep with clk.
    logic [31:0] lfsr_reg;

    // -------------------------------------------------------------------------
    // Galois LFSR update (Appendix E.1, updated_design_specification.md)
    // -------------------------------------------------------------------------
    // Right-shift configuration: if the bit shifting out (LSB) is 1, XOR the
    // fixed tap mask into the shifted word.  This is equivalent to XOR-at-taps
    // in parallel and matches LFSR_TAPS = 32'h00400007 in hft_pkg.
    //
    // next = lfsr[0] ? (lfsr >> 1) ^ LFSR_TAPS : (lfsr >> 1);
    //
    // Priority: asynchronous reset > synchronous load > enable advance > hold.
    // load wins over enable on the same cycle so a seed pulse is not corrupted
    // by an accidental simultaneous advance.
    // -------------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // Known non-zero power-on default.  Board A overwrites via load on
            // IDLE→RUNNING; zero state is illegal (stuck forever).
            lfsr_reg <= 32'h1;
        end
        else if (load) begin
            // Software may write 0 to MMIO by mistake; remap to 1 per spec.
            lfsr_reg <= (seed_in == 32'h0) ? 32'h1 : seed_in;
        end
        else if (enable) begin
            lfsr_reg <= lfsr_reg[0] ? ((lfsr_reg >> 1) ^ LFSR_TAPS)
                                    : (lfsr_reg >> 1);
        end
        // else: hold last value (e.g. market paused, or LFSR clock-gated)
    end

    // Registered output — probe `rand_out` in waves; it equals lfsr_reg.
    assign rand_out = lfsr_reg;

endmodule
