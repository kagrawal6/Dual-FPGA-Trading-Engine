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

        // Save step_out for gating test
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

        // Summary
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
