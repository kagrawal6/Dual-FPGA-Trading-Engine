// ============================================================================
// Module: market_noise_gen
// - Global LFSR + per-symbol company LFSRs + per-sector sector LFSRs
// - sector_pop[k] = count of active symbols in sector k; each tick:
//     sec_drift[k] += sat( sector_base_delta(sector_rand[k]) * sector_pop[k] )
//   so crowded sectors move faster (predictable, tunable).
// - Company drift: per-symbol, saturated (unchanged recipe).
// - lfsr_load: reseeds all LFSRs and clears sym/sec drift (aligned with
//   market_sim "fresh run" on the same pulse).
//
// step_out_q16_16[s] = global_noise + sec_drift[sector_id[s]] + sym_drift[s]
// market_sim: delta_mid = (step_out * step_size_q16_16) >>> 16
// ============================================================================

`timescale 1ns / 1ps

module market_noise_gen
    import hft_pkg::*;
#(
    parameter int NUM_SYM     = NUM_SYMBOLS,
    parameter int NUM_SECTORS = hft_pkg::NUM_SECTORS
)(
    input  logic                             clk,
    input  logic                             rst_n,
    input  logic                             enable,
    input  logic                             lfsr_load,
    input  logic                             tick,
    input  logic [31:0]                      base_seed,
    input  logic [7:0]                       active_sym_count,
    input  logic [SECTOR_ID_W-1:0]           sector_id [NUM_SYM],

    output logic signed [31:0]               global_noise_q16_16,
    output logic signed [31:0]               sector_noise_q16_16 [NUM_SECTORS],
    output logic signed [31:0]               company_noise_q16_16 [NUM_SYM],
    output logic signed [31:0]               step_out_q16_16 [NUM_SYM]
);

    localparam logic [31:0] GOLDEN          = 32'h9E37_79B9;
    localparam logic [31:0] GLOBAL_SEED_XOR = 32'hA11F_E511;
    localparam logic [31:0] SECTOR_SEED_XOR = 32'hC13F_A9A9;
    localparam logic signed [31:0] DRIFT_SAT_Q16 = MARKET_NOISE_DRIFT_SAT_Q16;

    logic [31:0] sym_rand [NUM_SYM];
    logic [31:0] sym_seed [NUM_SYM];
    logic [31:0] global_rand;
    logic [31:0] sector_rand [NUM_SECTORS];
    logic [31:0] sector_seed [NUM_SECTORS];
    logic [7:0]  active_count_eff;

    logic [7:0] sector_pop [NUM_SECTORS];

    logic signed [31:0] sym_drift_q16_16 [NUM_SYM];
    logic signed [31:0] sec_drift_q16_16 [NUM_SECTORS];

    function automatic logic signed [31:0] add_sat32(
        input logic signed [31:0] acc,
        input logic signed [31:0] delta,
        input logic signed [31:0] lim_neg,
        input logic signed [31:0] lim_pos
    );
        logic signed [63:0] s;
        s = 64'sd0 + $signed(acc) + $signed(delta);
        if (s > $signed(lim_pos)) return lim_pos;
        if (s < $signed(lim_neg)) return lim_neg;
        return s[31:0];
    endfunction

    function automatic logic signed [31:0] sector_base_delta(input logic [31:0] r);
        logic signed [31:0] raw;
        raw = $signed({1'b0, r[17:12]}) - 32'sd32;
        if (raw == -32'sd32) raw = 32'sd0;  // clamp to symmetric range [-31..+31], mean=0
        return (raw <<< 2);
    endfunction

    function automatic logic signed [31:0] sector_scaled_delta(
        input logic [31:0] r,
        input logic [7:0]  pop
    );
        logic signed [31:0] base;
        logic signed [63:0] prod;
        base = sector_base_delta(r);
        prod = $signed(base) * $signed({24'd0, pop});
        if (prod > 64'sh7FFF_FFFF) return 32'sh7FFF_FFFF;
        if (prod < -64'sh8000_0000) return -32'sh8000_0000;
        return prod[31:0];
    endfunction

    function automatic logic signed [31:0] company_tick_delta(input logic [31:0] r);
        logic signed [31:0] raw;
        raw = $signed({1'b0, r[11:6]}) - 32'sd32;
        if (raw == -32'sd32) raw = 32'sd0;  // clamp to symmetric range [-31..+31], mean=0
        return (raw <<< 3);
    endfunction

    // Defensive clamp for standalone use (integration already clamps upstream).
    always_comb begin
        if (active_sym_count > NUM_SYM[7:0]) active_count_eff = NUM_SYM[7:0];
        else active_count_eff = active_sym_count;
    end

    always_comb begin
        for (int pc = 0; pc < NUM_SECTORS; pc++) begin
            sector_pop[pc] = 8'd0;
        end
        for (int pi = 0; pi < NUM_SYM; pi++) begin
            if (pi < active_count_eff) begin
                sector_pop[sector_id[pi]] = sector_pop[sector_id[pi]] + 8'd1;
            end
        end
    end

    genvar g;
    generate
        for (g = 0; g < NUM_SYM; g++) begin : g_sym_rng
            assign sym_seed[g] = base_seed ^ (GOLDEN * (g + 1));

            lfsr32 u_sym_lfsr (
                .clk     (clk),
                .rst_n   (rst_n),
                .enable  (enable && tick && (g < active_count_eff)),
                .load    (lfsr_load),
                .seed_in (sym_seed[g]),
                .rand_out(sym_rand[g])
            );
        end
    endgenerate

    genvar gs;
    generate
        for (gs = 0; gs < NUM_SECTORS; gs++) begin : g_sec_rng
            assign sector_seed[gs] = base_seed ^ (SECTOR_SEED_XOR + (gs * GOLDEN));

            lfsr32 u_sec_lfsr (
                .clk     (clk),
                .rst_n   (rst_n),
                .enable  (enable && tick),
                .load    (lfsr_load),
                .seed_in (sector_seed[gs]),
                .rand_out(sector_rand[gs])
            );
        end
    endgenerate

    lfsr32 u_global_lfsr (
        .clk     (clk),
        .rst_n   (rst_n),
        .enable  (enable && tick),
        .load    (lfsr_load),
        .seed_in (base_seed ^ GLOBAL_SEED_XOR),
        .rand_out(global_rand)
    );

    always_comb begin
        logic signed [31:0] g_raw;
        g_raw = $signed({1'b0, global_rand[5:0]}) - 32'sd32;
        if (g_raw == -32'sd32) g_raw = 32'sd0;  // clamp to symmetric range [-31..+31], mean=0
        global_noise_q16_16 = (g_raw <<< 6);
    end

    integer kk;
    integer ii;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (kk = 0; kk < NUM_SECTORS; kk++) begin
                sec_drift_q16_16[kk] <= '0;
            end
            for (ii = 0; ii < NUM_SYM; ii++) begin
                sym_drift_q16_16[ii] <= '0;
            end
        end else if (lfsr_load) begin
            // Fresh run together with market_sim symbol table / quote state reload.
            for (kk = 0; kk < NUM_SECTORS; kk++) begin
                sec_drift_q16_16[kk] <= '0;
            end
            for (ii = 0; ii < NUM_SYM; ii++) begin
                sym_drift_q16_16[ii] <= '0;
            end
        end else if (enable && tick) begin
            for (ii = 0; ii < NUM_SYM; ii++) begin
                if (ii < active_count_eff) begin
                    sym_drift_q16_16[ii] <= add_sat32(
                        sym_drift_q16_16[ii],
                        company_tick_delta(sym_rand[ii]),
                        -DRIFT_SAT_Q16,
                        DRIFT_SAT_Q16
                    );
                end
            end
            for (kk = 0; kk < NUM_SECTORS; kk++) begin
                sec_drift_q16_16[kk] <= add_sat32(
                    sec_drift_q16_16[kk],
                    sector_scaled_delta(sector_rand[kk], sector_pop[kk]),
                    -DRIFT_SAT_Q16,
                    DRIFT_SAT_Q16
                );
            end
        end
    end

    always_comb begin
        for (int ks = 0; ks < NUM_SECTORS; ks++) begin
            sector_noise_q16_16[ks] = sec_drift_q16_16[ks];
        end

        for (int isy = 0; isy < NUM_SYM; isy++) begin
            if (isy < active_count_eff) begin
                company_noise_q16_16[isy] = sym_drift_q16_16[isy];
                step_out_q16_16[isy] = global_noise_q16_16
                                     + sec_drift_q16_16[sector_id[isy]]
                                     + sym_drift_q16_16[isy];
            end else begin
                company_noise_q16_16[isy] = '0;
                step_out_q16_16[isy]      = '0;
            end
        end
    end

endmodule
