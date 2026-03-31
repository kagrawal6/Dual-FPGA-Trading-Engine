// ============================================================================
// Testbench: tb_market_noise_gen
// Golden vectors (8 ticks from gen_board_a_vectors.py), enable=0 gating,
// active_sym_count=1/full, decomposition checks, sector population scaling,
// drift saturation bounds, determinism.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_market_noise_gen;
    localparam int TB_NUM_SYM = 4;
    localparam int NT = 24;

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

    int pass_count = 0;
    int fail_count = 0;

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

    task automatic check(string msg, logic cond);
        if (cond) pass_count++;
        else begin
            $error("FAIL: %s", msg);
            fail_count++;
        end
    endtask

    task automatic check32(string msg, logic [31:0] actual, logic [31:0] expected);
        if (actual === expected) pass_count++;
        else begin
            $error("FAIL: %s — got %08h, exp %08h", msg, actual, expected);
            fail_count++;
        end
    endtask

    task automatic do_tick;
        tick = 1'b1;
        @(posedge clk);
        tick = 1'b0;
        @(posedge clk); #1;
    endtask

    task automatic pulse_lfsr_load;
        lfsr_load = 1'b1;
        @(posedge clk);
        lfsr_load = 1'b0;
        @(posedge clk); #1;
    endtask

    task automatic check_decomp(string tag, int n_act);
        for (int s = 0; s < TB_NUM_SYM; s++) begin
            if (s < n_act) begin
                logic signed [31:0] exp_step;
                exp_step = global_noise_q16_16
                         + sector_noise_q16_16[sector_id[s]]
                         + company_noise_q16_16[s];
                check32($sformatf("%s decomp sym%0d", tag, s), step_out_q16_16[s], exp_step);
            end
        end
    endtask

    // Golden vectors: seed=0xDEADBEEF, sector_ids=[0,0,1,1], 8 ticks
    localparam logic [31:0] GOLDEN_STEP [8][4] = '{
        '{32'h00000780, 32'h00000780, 32'h00000780, 32'h00000780},
        '{32'h000007B0, 32'h00000878, 32'h00000780, 32'h00000808},
        '{32'h000004E0, 32'h00000610, 32'h00000598, 32'h00000668},
        '{32'h00000458, 32'h000005B8, 32'h00000680, 32'h00000778},
        '{32'h00000510, 32'h00000688, 32'h000007F0, 32'h00000900},
        '{32'hFFFFFD68, 32'hFFFFFDF0, 32'h000000A0, 32'h000000C0},
        '{32'hFFFFFEB0, 32'hFFFFFFC0, 32'h00000418, 32'h000002C0},
        '{32'h00000230, 32'h00000380, 32'h000007B0, 32'h00000498}
    };

    function automatic longint abs32(input logic signed [31:0] v);
        if (v < 0) return -longint'($signed(v));
        return longint'($signed(v));
    endfunction

    initial begin
        $dumpfile("tb_market_noise_gen.vcd");
        $dumpvars(0, tb_market_noise_gen);

        enable           = 1'b0;
        lfsr_load        = 1'b0;
        tick             = 1'b0;
        base_seed        = 32'hDEAD_BEEF;
        active_sym_count = TB_NUM_SYM[7:0];
        sector_id[0] = SECTOR_ID_W'(0);
        sector_id[1] = SECTOR_ID_W'(0);
        sector_id[2] = SECTOR_ID_W'(1);
        sector_id[3] = SECTOR_ID_W'(1);

        wait (rst_n === 1'b1);
        @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 1) Post-reset: drift outputs zero
        // ─────────────────────────────────────────────────────
        $display("--- test_reset ---");
        for (int ks = 0; ks < NUM_SECTORS; ks++)
            check($sformatf("reset sec_noise[%0d]=0", ks), sector_noise_q16_16[ks] === 32'sd0);
        for (int isy = 0; isy < TB_NUM_SYM; isy++)
            check($sformatf("reset company[%0d]=0", isy), company_noise_q16_16[isy] === 32'sd0);

        enable = 1'b1;

        // ─────────────────────────────────────────────────────
        // 2) Golden vectors: 8 ticks with decomposition check
        // ─────────────────────────────────────────────────────
        $display("--- test_golden_vectors ---");
        pulse_lfsr_load();
        for (int t = 0; t < 8; t++) begin
            check_decomp($sformatf("golden t%0d", t), TB_NUM_SYM);
            for (int s = 0; s < 4; s++) begin
                check32($sformatf("golden t%0d s%0d", t, s), step_out_q16_16[s], GOLDEN_STEP[t][s]);
            end
            do_tick();
        end

        // ─────────────────────────────────────────────────────
        // 3) enable=0 mid-stream: outputs frozen
        // ─────────────────────────────────────────────────────
        $display("--- test_enable_gating ---");
        pulse_lfsr_load();
        // Run 4 ticks
        for (int t = 0; t < 4; t++) do_tick();
        begin
            logic signed [31:0] frozen [TB_NUM_SYM];
            for (int s = 0; s < TB_NUM_SYM; s++) frozen[s] = step_out_q16_16[s];
            enable = 1'b0;
            for (int i = 0; i < 4; i++) begin
                do_tick();
                for (int s = 0; s < TB_NUM_SYM; s++)
                    check32($sformatf("enable=0 frozen[%0d] at %0d", s, i), step_out_q16_16[s], frozen[s]);
            end
            enable = 1'b1;
        end

        // ─────────────────────────────────────────────────────
        // 4) active_sym_count=1: only sym0 gets output
        // ─────────────────────────────────────────────────────
        $display("--- test_active_1 ---");
        pulse_lfsr_load();
        active_sym_count = 8'd1;
        for (int t = 0; t < 8; t++) begin
            do_tick();
            check($sformatf("active1 sym1 zero t%0d", t), step_out_q16_16[1] == 32'sd0);
            check($sformatf("active1 sym2 zero t%0d", t), step_out_q16_16[2] == 32'sd0);
            check($sformatf("active1 sym3 zero t%0d", t), step_out_q16_16[3] == 32'sd0);
        end
        active_sym_count = TB_NUM_SYM[7:0];

        // ─────────────────────────────────────────────────────
        // 5) Determinism: same seed → same sequence
        // ─────────────────────────────────────────────────────
        $display("--- test_determinism ---");
        begin
            logic signed [31:0] run_a [TB_NUM_SYM][NT];
            logic signed [31:0] run_b [TB_NUM_SYM][NT];
            pulse_lfsr_load();
            for (int t = 0; t < NT; t++) begin
                do_tick();
                for (int s = 0; s < TB_NUM_SYM; s++) run_a[s][t] = step_out_q16_16[s];
            end
            // Reset and replay
            rst_n = 1'b0;
            #40;
            rst_n = 1'b1;
            @(posedge clk);
            enable = 1'b1;
            pulse_lfsr_load();
            for (int t = 0; t < NT; t++) begin
                do_tick();
                for (int s = 0; s < TB_NUM_SYM; s++) run_b[s][t] = step_out_q16_16[s];
            end
            for (int t = 0; t < NT; t++)
                for (int s = 0; s < TB_NUM_SYM; s++)
                    check32($sformatf("det sym%0d t%0d", s, t), run_b[s][t], run_a[s][t]);
        end

        // ─────────────────────────────────────────────────────
        // 6) Population-weighted sector motion
        // ─────────────────────────────────────────────────────
        $display("--- test_pop_scaling ---");
        // 3 syms in sector 0, 1 in sector 1
        sector_id[0] = SECTOR_ID_W'(0);
        sector_id[1] = SECTOR_ID_W'(0);
        sector_id[2] = SECTOR_ID_W'(0);
        sector_id[3] = SECTOR_ID_W'(1);
        pulse_lfsr_load();
        begin
            longint cum0 = 0, cum1 = 0;
            for (int t = 0; t < 160; t++) begin
                do_tick();
                cum0 += abs32(sector_noise_q16_16[0]);
                cum1 += abs32(sector_noise_q16_16[1]);
            end
            check("pop: |sec0| > |sec1|", cum0 > cum1);
        end
        // Restore
        sector_id[0] = SECTOR_ID_W'(0);
        sector_id[1] = SECTOR_ID_W'(0);
        sector_id[2] = SECTOR_ID_W'(1);
        sector_id[3] = SECTOR_ID_W'(1);

        // ─────────────────────────────────────────────────────
        // 7) Drift saturation bounds
        // ─────────────────────────────────────────────────────
        $display("--- test_drift_saturation ---");
        pulse_lfsr_load();
        repeat (4000) do_tick();
        for (int ks = 0; ks < NUM_SECTORS; ks++) begin
            check($sformatf("sat sec[%0d] bound", ks),
                  sector_noise_q16_16[ks] <= MARKET_NOISE_DRIFT_SAT_Q16
                  && sector_noise_q16_16[ks] >= -MARKET_NOISE_DRIFT_SAT_Q16);
        end
        for (int isy = 0; isy < TB_NUM_SYM; isy++) begin
            check($sformatf("sat company[%0d] bound", isy),
                  company_noise_q16_16[isy] <= MARKET_NOISE_DRIFT_SAT_Q16
                  && company_noise_q16_16[isy] >= -MARKET_NOISE_DRIFT_SAT_Q16);
        end

        // ─────────────────────────────────────────────────────
        // 8) lfsr_load resets drift accumulators
        // ─────────────────────────────────────────────────────
        $display("--- test_lfsr_load_clears_drift ---");
        // After 4000 ticks, drift should be nonzero
        begin
            logic some_nonzero = 1'b0;
            for (int isy = 0; isy < TB_NUM_SYM; isy++)
                if (company_noise_q16_16[isy] != 32'sd0) some_nonzero = 1'b1;
            check("pre-reload: some drift nonzero", some_nonzero);
        end
        pulse_lfsr_load();
        for (int ks = 0; ks < NUM_SECTORS; ks++)
            check($sformatf("reload sec[%0d]=0", ks), sector_noise_q16_16[ks] === 32'sd0);
        for (int isy = 0; isy < TB_NUM_SYM; isy++)
            check($sformatf("reload company[%0d]=0", isy), company_noise_q16_16[isy] === 32'sd0);

        // ─────────────────────────────────────────────────────
        // Summary
        // ─────────────────────────────────────────────────────
        $display("\n===================================");
        if (fail_count == 0)
            $display("tb_market_noise_gen: PASS (%0d checks passed)", pass_count);
        else begin
            $display("tb_market_noise_gen: FAIL (%0d passed, %0d failed)", pass_count, fail_count);
            $fatal;
        end
        $display("===================================");
        $finish;
    end

endmodule
