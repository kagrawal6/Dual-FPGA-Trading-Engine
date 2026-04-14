`timescale 1ns / 1ps

module tb_market_noise_gen();
    import hft_pkg::*;

    localparam NUM_SYM = 4;
    localparam NUM_SEC = 2;

    logic                    clk, rst_n, enable, lfsr_load, tick;
    logic [31:0]             base_seed;
    logic [7:0]              active_sym_count;
    logic [SECTOR_ID_W-1:0]  sector_id [NUM_SYM];
    logic signed [31:0]      global_noise;
    logic signed [31:0]      sector_noise [NUM_SEC];
    logic signed [31:0]      company_noise [NUM_SYM];
    logic signed [31:0]      step_out [NUM_SYM];

    integer err_cnt = 0;
    integer i;
    logic signed [31:0] saved_step [NUM_SYM];
    logic signed [31:0] replay_step [NUM_SYM];

    // Sector correlation temporaries
    logic signed [31:0] base_sym0, base_sym1, base_sym2;

    always #5 clk = ~clk;

    market_noise_gen #(.NUM_SYM(NUM_SYM), .NUM_SECTORS(NUM_SEC)) dut (
        .clk(clk), .rst_n(rst_n), .enable(enable),
        .lfsr_load(lfsr_load), .tick(tick),
        .base_seed(base_seed), .active_sym_count(active_sym_count),
        .sector_id(sector_id),
        .global_noise_q16_16(global_noise),
        .sector_noise_q16_16(sector_noise),
        .company_noise_q16_16(company_noise),
        .step_out_q16_16(step_out)
    );

    initial begin
        clk = 0; rst_n = 0; enable = 0;
        lfsr_load = 0; tick = 0;
        base_seed = 32'hDEAD_BEEF;
        active_sym_count = 8'd4;
        sector_id[0] = 3'd0; sector_id[1] = 3'd0;
        sector_id[2] = 3'd1; sector_id[3] = 3'd1;

        #20; rst_n = 1; @(posedge clk);

        // Load LFSRs with seeds
        lfsr_load = 1; @(posedge clk);
        lfsr_load = 0; @(posedge clk); #1;

        // Test 1: pre-tick, all step_out equal global_noise (drifts=0)
        for (i = 0; i < NUM_SYM; i++) begin
            if (step_out[i] !== global_noise) begin
                $display("FAIL: step_out[%0d]=%0d != global_noise=%0d", i, step_out[i], global_noise);
                err_cnt = err_cnt + 1;
            end else
                $display("PASS: step_out[%0d] == global_noise (%0d)", i, global_noise);
        end

        // Test 2: tick once with enable, step_out non-zero and bounded
        enable = 1;
        tick = 1; @(posedge clk);
        tick = 0; @(posedge clk); #1;

        for (i = 0; i < NUM_SYM; i++) begin
            if (step_out[i] > 32'sh0001_0000 || step_out[i] < -32'sh0001_0000) begin
                $display("FAIL: step_out[%0d]=%h out of bounds", i, step_out[i]);
                err_cnt = err_cnt + 1;
            end else
                $display("PASS: step_out[%0d]=%0d bounded", i, step_out[i]);
        end

        // Save step_out for gating test and determinism replay
        for (i = 0; i < NUM_SYM; i++) saved_step[i] = step_out[i];

        // Test 3: enable=0, tick does not change step_out
        enable = 0;
        tick = 1; @(posedge clk);
        tick = 0; @(posedge clk); #1;

        for (i = 0; i < NUM_SYM; i++) begin
            if (step_out[i] !== saved_step[i]) begin
                $display("FAIL: step_out[%0d] changed when disabled (%0d -> %0d)",
                         i, saved_step[i], step_out[i]);
                err_cnt = err_cnt + 1;
            end else
                $display("PASS: step_out[%0d] unchanged when disabled", i);
        end

        // ----------------------------------------------------------------
        // Test 4: determinism — reset, reload same seed, tick once;
        //         step_out must exactly match saved_step from Test 2.
        // ----------------------------------------------------------------
        rst_n = 0;
        repeat(2) @(posedge clk);
        rst_n = 1; @(posedge clk);

        lfsr_load = 1; @(posedge clk);
        lfsr_load = 0; @(posedge clk); #1;

        enable = 1;
        tick = 1; @(posedge clk);
        tick = 0; @(posedge clk); #1;

        for (i = 0; i < NUM_SYM; i++) replay_step[i] = step_out[i];

        for (i = 0; i < NUM_SYM; i++) begin
            if (replay_step[i] !== saved_step[i]) begin
                $display("FAIL: determinism step_out[%0d]: replay=%0d, original=%0d",
                         i, replay_step[i], saved_step[i]);
                err_cnt = err_cnt + 1;
            end else
                $display("PASS: determinism step_out[%0d] matches (%0d)", i, saved_step[i]);
        end

        // ----------------------------------------------------------------
        // Test 5: sector correlation — symbols in the same sector share
        //         sector_noise; different sectors produce different noise.
        //         sym 0,1 → sector 0; sym 2,3 → sector 1.
        // ----------------------------------------------------------------

        // 5a: same-sector symbols share the sector contribution
        //     base = step_out - company_noise = global + sector_noise[sector]
        base_sym0 = step_out[0] - company_noise[0];
        base_sym1 = step_out[1] - company_noise[1];

        if (base_sym0 !== base_sym1) begin
            $display("FAIL: sector sharing — base[0]=%0d != base[1]=%0d", base_sym0, base_sym1);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: symbols 0,1 share sector 0 contribution (%0d)", base_sym0);

        // 5b: different sectors produce different noise
        base_sym2 = step_out[2] - company_noise[2];
        if (base_sym0 === base_sym2) begin
            $display("FAIL: sector_noise[0] == sector_noise[1] (both %0d), expected differ",
                     base_sym0);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: sector 0 (%0d) != sector 1 (%0d) noise", base_sym0, base_sym2);

        // Summary
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
