// ============================================================================
// Module: market_noise_gen
// Executable sector-aware noise generator with:
// - one independent LFSR random source per symbol
// - symbol-local drift state in parallel
// - clean symbol separation via per-symbol outputs
//
// Integrates runtime active symbol count (`active_sym_count`) so logic scales
// behavior to however many symbols are currently enabled (up to NUM_SYM).
// ============================================================================

`timescale 1ns / 1ps

module market_noise_gen
    import hft_pkg::*;
#(
    parameter int NUM_SYM     = NUM_SYMBOLS,
    parameter int NUM_SECTORS = 8
)(
    input  logic                             clk,
    input  logic                             rst_n,
    input  logic                             enable,
    input  logic                             tick,              // one update pulse per quote-step
    input  logic [31:0]                      base_seed,         // deterministic root seed
    input  logic [7:0]                       active_sym_count,  // runtime active symbol count
    input  logic [2:0]                       sector_id [NUM_SYM],

    output logic signed [31:0]               global_noise_q16_16,
    output logic signed [31:0]               sector_noise_q16_16 [NUM_SECTORS],
    output logic signed [31:0]               company_noise_q16_16 [NUM_SYM],
    output logic signed [31:0]               step_out_q16_16 [NUM_SYM]
);

    localparam logic [31:0] GOLDEN = 32'h9E37_79B9;

    logic [31:0] sym_rand [NUM_SYM];
    logic [31:0] sym_seed [NUM_SYM];
    logic signed [31:0] sym_drift_q16_16 [NUM_SYM];
    logic signed [31:0] sec_drift_q16_16 [NUM_SECTORS];

    integer i;
    integer k;

    genvar g;
    generate
        // ADDITION: one independent RNG instance per symbol.
        for (g = 0; g < NUM_SYM; g++) begin : g_sym_rng
            assign sym_seed[g] = base_seed ^ (GOLDEN * (g + 1));

            lfsr32 u_sym_lfsr (
                .clk     (clk),
                .rst_n   (rst_n),
                .enable  (enable && tick && (g < active_sym_count)),
                .load    (!rst_n),
                .seed_in (sym_seed[g]),
                .rand_out(sym_rand[g])
            );
        end
    endgenerate

    // ADDITION: shared global movement term (deterministic).
    always_comb begin
        global_noise_q16_16 = (($signed({1'b0, sym_rand[0][5:0]}) - 32'sd32) <<< 6);
    end

    // ADDITION: parallel sector drift + symbol-local drift updates.
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (k = 0; k < NUM_SECTORS; k++) begin
                sec_drift_q16_16[k] <= '0;
            end
            for (i = 0; i < NUM_SYM; i++) begin
                sym_drift_q16_16[i] <= '0;
            end
        end else if (enable && tick) begin
            for (i = 0; i < NUM_SYM; i++) begin
                if (i < active_sym_count) begin
                    // Local per-symbol drift from each symbol's own RNG source.
                    sym_drift_q16_16[i] <= sym_drift_q16_16[i]
                        + (($signed({1'b0, sym_rand[i][11:6]}) - 32'sd32) <<< 3);

                    // Sector drift update fed by that symbol's RNG, keyed by sector.
                    sec_drift_q16_16[sector_id[i]] <= sec_drift_q16_16[sector_id[i]]
                        + (($signed({1'b0, sym_rand[i][17:12]}) - 32'sd32) <<< 2);
                end
            end
        end
    end

    // ADDITION: output decomposition:
    // price_step[s] = global + sector + company
    always_comb begin
        for (k = 0; k < NUM_SECTORS; k++) begin
            sector_noise_q16_16[k] = sec_drift_q16_16[k];
        end

        for (i = 0; i < NUM_SYM; i++) begin
            if (i < active_sym_count) begin
                company_noise_q16_16[i] = sym_drift_q16_16[i];
                step_out_q16_16[i] = global_noise_q16_16
                                   + sec_drift_q16_16[sector_id[i]]
                                   + sym_drift_q16_16[i];
            end else begin
                company_noise_q16_16[i] = '0;
                step_out_q16_16[i]      = '0;
            end
        end
    end

endmodule
