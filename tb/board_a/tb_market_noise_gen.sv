// ============================================================================
// Testbench: tb_market_noise_gen
// Determinism, lfsr_load tail alignment (drifts clear on lfsr_load — matches
// market_sim), active_sym_count gating, decomposition, population-weighted
// sector motion (cum |sector0| > |sector1| when pop 3 vs 1), drift saturation
// bounds, and coarse step_out diversity.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_market_noise_gen;
    localparam int TB_NUM_SYM = 4;
    localparam int NT         = 24;

    logic                     clk;
    logic                     rst_n;
    logic                     enable;
    logic                     lfsr_load;
    logic                     tick;
    logic [31:0]              base_seed;
    logic [7:0]               active_sym_count;
    logic [SECTOR_ID_W-1:0]   sector_id [TB_NUM_SYM];

    logic signed [31:0]       global_noise_q16_16;
    logic signed [31:0]       sector_noise_q16_16 [NUM_SECTORS];
    logic signed [31:0]       company_noise_q16_16 [TB_NUM_SYM];
    logic signed [31:0]       step_out_q16_16 [TB_NUM_SYM];

    int err_count = 0;

    function automatic longint abs32(input logic signed [31:0] v);
        if (v < 0) return -longint'($signed(v));
        return longint'($signed(v));
    endfunction

    task automatic check(input string msg, input logic cond);
        if (!cond) begin
            $error("FAIL: %s", msg);
            err_count++;
        end
    endtask

    task automatic check_decomp(input string tag, input int n_act);
        logic signed [31:0] exp_step;
        for (int s = 0; s < TB_NUM_SYM; s++) begin
            if (s < n_act) begin
                exp_step = global_noise_q16_16
                         + sector_noise_q16_16[sector_id[s]]
                         + company_noise_q16_16[s];
                check($sformatf("%s decomp sym%0d", tag, s), step_out_q16_16[s] === exp_step);
            end
        end
    endtask

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    market_noise_gen #(
        .NUM_SYM(TB_NUM_SYM),
        .NUM_SECTORS(NUM_SECTORS)
    ) dut (
        .clk                  (clk),
        .rst_n                (rst_n),
        .enable               (enable),
        .lfsr_load            (lfsr_load),
        .tick                 (tick),
        .base_seed            (base_seed),
        .active_sym_count     (active_sym_count),
        .sector_id            (sector_id),
        .global_noise_q16_16  (global_noise_q16_16),
        .sector_noise_q16_16  (sector_noise_q16_16),
        .company_noise_q16_16 (company_noise_q16_16),
        .step_out_q16_16      (step_out_q16_16)
    );

    task automatic do_tick;
        tick = 1'b1;
        @(posedge clk);
        tick = 1'b0;
        @(posedge clk);
    endtask

    task automatic do_tick_decomp(input string tag, input int n_act);
        do_tick();
        check_decomp(tag, n_act);
    endtask

    task automatic pulse_lfsr_load;
        lfsr_load = 1'b1;
        @(posedge clk);
        lfsr_load = 1'b0;
        @(posedge clk);
    endtask

    task automatic capture_stream(
        ref logic signed [31:0] cap [TB_NUM_SYM][NT],
        input int n
    );
        for (int t = 0; t < n; t++) begin
            do_tick_decomp($sformatf("cap t%0d", t), TB_NUM_SYM);
            for (int s = 0; s < TB_NUM_SYM; s++) cap[s][t] = step_out_q16_16[s];
        end
    endtask

    // Three symbols in sector 0, one in sector 1 — sector_pop 3 vs 1 when all active.
    task automatic init_sector_ids;
        sector_id[0] = SECTOR_ID_W'(0);
        sector_id[1] = SECTOR_ID_W'(0);
        sector_id[2] = SECTOR_ID_W'(0);
        sector_id[3] = SECTOR_ID_W'(1);
    endtask

    initial begin
        logic signed [31:0] run_a [TB_NUM_SYM][NT];
        logic signed [31:0] run_b [TB_NUM_SYM][NT];
        int t;
        bit diff01;
        longint cum_abs_sec0, cum_abs_sec1;

        wait (rst_n === 1'b1);
        @(posedge clk);

        base_seed        = 32'hA5A5_5A5A;
        enable           = 1'b0;
        lfsr_load        = 1'b0;
        tick             = 1'b0;
        active_sym_count = TB_NUM_SYM[7:0];
        init_sector_ids();

        // ---------- Reset: drift-backed outputs zero before any tick ----------
        for (int ks = 0; ks < NUM_SECTORS; ks++) begin
            check($sformatf("post-rst sector_noise[%0d] zero", ks),
                  sector_noise_q16_16[ks] === 32'sd0);
        end
        for (int isy = 0; isy < TB_NUM_SYM; isy++) begin
            check($sformatf("post-rst company[%0d] zero", isy),
                  company_noise_q16_16[isy] === 32'sd0);
        end

        enable = 1'b1;

        // ---------- Determinism: full reset, same seed, identical streams ----------
        pulse_lfsr_load();
        capture_stream(run_a, NT);

        rst_n = 1'b0;
        #40;
        rst_n = 1'b1;
        @(posedge clk);
        enable = 1'b1;
        pulse_lfsr_load();
        capture_stream(run_b, NT);

        for (t = 0; t < NT; t++) begin
            check($sformatf("det step_out[0][%0d]", t), run_a[0][t] === run_b[0][t]);
            check($sformatf("det step_out[1][%0d]", t), run_a[1][t] === run_b[1][t]);
            check($sformatf("det step_out[2][%0d]", t), run_a[2][t] === run_b[2][t]);
            check($sformatf("det step_out[3][%0d]", t), run_a[3][t] === run_b[3][t]);
        end

        // ---------- lfsr_load: same prefix + reload → same tail (drifts zeroed on load) ----------
        begin
            logic signed [31:0] tail_x [TB_NUM_SYM][3];
            logic signed [31:0] tail_y [TB_NUM_SYM][3];
            rst_n = 1'b0;
            #40;
            rst_n = 1'b1;
            @(posedge clk);
            enable = 1'b1;
            pulse_lfsr_load();
            repeat (10) do_tick_decomp("warm", TB_NUM_SYM);
            pulse_lfsr_load();
            for (int k = 0; k < 3; k++) begin
                do_tick_decomp($sformatf("tail_x k%0d", k), TB_NUM_SYM);
                for (int s = 0; s < TB_NUM_SYM; s++) tail_x[s][k] = step_out_q16_16[s];
            end

            rst_n = 1'b0;
            #40;
            rst_n = 1'b1;
            @(posedge clk);
            enable = 1'b1;
            pulse_lfsr_load();
            repeat (10) do_tick_decomp("warm2", TB_NUM_SYM);
            pulse_lfsr_load();
            for (int k = 0; k < 3; k++) begin
                do_tick_decomp($sformatf("tail_y k%0d", k), TB_NUM_SYM);
                for (int s = 0; s < TB_NUM_SYM; s++) tail_y[s][k] = step_out_q16_16[s];
            end

            for (int k = 0; k < 3; k++) begin
                for (int s = 0; s < TB_NUM_SYM; s++) begin
                    check($sformatf("lfsr_load tail sym%0d t%0d", s, k),
                          tail_x[s][k] === tail_y[s][k]);
                end
            end
        end

        // ---------- active_sym_count: inactive outputs tied to zero + decomp for active ----------
        pulse_lfsr_load();
        active_sym_count = 8'd2;
        repeat (8) begin
            do_tick_decomp("active2", 2);
            check("active2 sym2 zero", step_out_q16_16[2] == 32'sd0);
            check("active2 sym3 zero", step_out_q16_16[3] == 32'sd0);
        end
        active_sym_count = TB_NUM_SYM[7:0];

        // ---------- Population-weighted sector motion (trend sanity, not a formal identity) ----------
        // Expect sector 0 (pop 3) to accumulate larger sum(|sector_noise|) than sector 1 (pop 1)
        // over many ticks. Seeding/scaling changes could theoretically flip this; if that happens,
        // extend ticks or switch to a structural check (e.g. compare per-tick deltas when pops differ).
        pulse_lfsr_load();
        init_sector_ids();
        active_sym_count = TB_NUM_SYM[7:0];
        cum_abs_sec0 = 0;
        cum_abs_sec1 = 0;
        repeat (160) begin
            do_tick_decomp("popscale", TB_NUM_SYM);
            cum_abs_sec0 += abs32(sector_noise_q16_16[0]);
            cum_abs_sec1 += abs32(sector_noise_q16_16[1]);
        end
        check("popscale cumulative |sector0| > |sector1|", cum_abs_sec0 > cum_abs_sec1);

        // ---------- Drift saturates within ±MARKET_NOISE_DRIFT_SAT_Q16 (outputs) ----------
        pulse_lfsr_load();
        init_sector_ids();
        active_sym_count = TB_NUM_SYM[7:0];
        repeat (4000) do_tick_decomp("sat", TB_NUM_SYM);
        for (int ks = 0; ks < NUM_SECTORS; ks++) begin
            check($sformatf("sat |sector_noise[%0d]| bound", ks),
                  sector_noise_q16_16[ks] <= MARKET_NOISE_DRIFT_SAT_Q16
                  && sector_noise_q16_16[ks] >= -MARKET_NOISE_DRIFT_SAT_Q16);
        end
        for (int isy = 0; isy < TB_NUM_SYM; isy++) begin
            if (isy < active_sym_count) begin
                check($sformatf("sat |company[%0d]| bound", isy),
                      company_noise_q16_16[isy] <= MARKET_NOISE_DRIFT_SAT_Q16
                      && company_noise_q16_16[isy] >= -MARKET_NOISE_DRIFT_SAT_Q16);
            end
        end

        // ---------- Same-sector pair vs different sector (smoke) ----------
        pulse_lfsr_load();
        diff01 = 1'b0;
        repeat (NT) begin
            do_tick_decomp("diff", TB_NUM_SYM);
            if (step_out_q16_16[0] != step_out_q16_16[2]) diff01 = 1'b1;
        end
        check("sym0 vs sym2 differ at least once", diff01);

        if (err_count == 0)
            $display("tb_market_noise_gen: PASS (all checks passed)");
        else
            $display("tb_market_noise_gen: FAIL (%0d errors)", err_count);

        $finish;
    end

endmodule
