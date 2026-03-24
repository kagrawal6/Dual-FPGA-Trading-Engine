// ============================================================================
// Testbench: tb_market_sim
// Phased tests for market_sim + market_noise_gen integration:
//   1) Main: round-robin, regime switch, frame checks, quotes_generated
//   2) Backpressure: quote_ready low — no quote_valid; quotes_generated frozen; resume order
//   3) active_sym_count=2: only symbols 0,1 alternating
//   4) Mid-run lfsr_load: counters/state reload
//   5) quote_interval==0: fastest tick path
// Price path is not golden-modeled; see tb_market_noise_gen.sv for noise checks.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_market_sim;
    localparam int TB_NUM_SYM = 4;

    logic                     clk;
    logic                     rst_n;
    logic                     enable;
    logic                     lfsr_load;
    logic [31:0]              lfsr_seed;
    regime_e                  active_regime;
    logic [31:0]              quote_interval;
    logic [7:0]               active_sym_count;
    logic [SECTOR_ID_W-1:0]   sector_id [TB_NUM_SYM];
    price_t                   init_mid    [TB_NUM_SYM];
    price_t                   init_spread [TB_NUM_SYM];
    logic [FRAME_W-1:0]       quote_frame;
    logic                     quote_valid;
    logic                     quote_ready;
    price_t                   best_bid    [TB_NUM_SYM];
    price_t                   best_ask    [TB_NUM_SYM];
    logic [COUNTER_W-1:0]     quotes_generated;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    market_sim #(.NUM_SYM(TB_NUM_SYM)) dut (
        .clk              (clk),
        .rst_n            (rst_n),
        .enable           (enable),
        .lfsr_load        (lfsr_load),
        .lfsr_seed        (lfsr_seed),
        .active_regime    (active_regime),
        .quote_interval   (quote_interval),
        .active_sym_count (active_sym_count),
        .sector_id        (sector_id),
        .init_mid         (init_mid),
        .init_spread      (init_spread),
        .quote_frame      (quote_frame),
        .quote_valid      (quote_valid),
        .quote_ready      (quote_ready),
        .best_bid         (best_bid),
        .best_ask         (best_ask),
        .quotes_generated (quotes_generated)
    );

    int err_count = 0;

    task automatic check(input string msg, input logic cond);
        if (!cond) begin
            $error("FAIL: %s", msg);
            err_count++;
        end
    endtask

    initial begin
        $dumpfile("tb_market_sim.vcd");
        $dumpvars(0, tb_market_sim);
    end

    localparam sprice_t MIN_PRICE_Q16_16 = sprice_t'(32'h0001_0000);
    localparam sprice_t MAX_PRICE_Q16_16 = sprice_t'(32'h2710_0000);

    function automatic price_t base_spread_for(input regime_e r);
        unique case (r)
            REGIME_CALM:       base_spread_for = 32'h0000_2000;
            REGIME_VOLATILE:   base_spread_for = 32'h0000_8000;
            REGIME_BURST:      base_spread_for = 32'h0000_2000;
            default:           base_spread_for = 32'h0001_0000;
        endcase
    endfunction

    // Expected seq per symbol; round-robin wrap at sym_wrap (inclusive), e.g. 3 for 4 symbols, 1 for 2.
    logic [15:0] seq_expect [TB_NUM_SYM];
    logic [7:0]   sym_id_u8;
    regime_e      regime_in_frame;
    logic [15:0]  seq_in_frame;
    logic [31:0]  bid_u, ask_u;
    price_t       spread_b;
    logic [31:0]  spread_meas;

    function automatic int next_sym(input int cur, input int sym_wrap);
        next_sym = (cur == sym_wrap) ? 0 : (cur + 1);
    endfunction

    // Wait until quote_valid is high (sampled after posedge in loop).
    task automatic wait_quote;
        do begin
            @(posedge clk);
        end while (!quote_valid);
    endtask

    // One-cycle pulse lfsr_load (assumes enable controlled by test).
    task automatic pulse_lfsr_load;
        lfsr_load = 1'b1;
        @(posedge clk);
        lfsr_load = 1'b0;
        @(posedge clk);
    endtask

    // Verify one QUOTE frame; exp_sym must match [123:116]; seq_expect[exp_sym] is checked then incremented.
    task automatic check_one_quote(
        input string    tag,
        input int       exp_sym,
        input int       sym_wrap
    );
        wait_quote;
        check($sformatf("%s: msg_type QUOTE", tag), quote_frame[127:124] == 4'h1);
        sym_id_u8 = quote_frame[123:116];
        check($sformatf("%s: symbol_id==%0d", tag, exp_sym), sym_id_u8 == exp_sym[7:0]);
        check($sformatf("%s: symbol in active range", tag), sym_id_u8 <= sym_wrap[7:0]);

        regime_in_frame = regime_e'(quote_frame[115:114]);
        seq_in_frame    = quote_frame[15:0];
        check($sformatf("%s: seq for sym %0d", tag, exp_sym), seq_in_frame == seq_expect[exp_sym]);

        bid_u = quote_frame[111:80];
        ask_u = quote_frame[79:48];
        check($sformatf("%s: ask>=bid", tag), $signed(ask_u) >= $signed(bid_u));
        check($sformatf("%s: bid range", tag),
              bid_u >= price_t'(MIN_PRICE_Q16_16) && bid_u <= price_t'(MAX_PRICE_Q16_16));
        check($sformatf("%s: ask range", tag),
              ask_u >= price_t'(MIN_PRICE_Q16_16) && ask_u <= price_t'(MAX_PRICE_Q16_16));

        spread_b = base_spread_for(regime_in_frame);
        spread_meas = ask_u - bid_u;
        check($sformatf("%s: spread==regime base", tag),
              spread_meas === (spread_b == '0 ? 32'h0000_0001 : spread_b));

        seq_expect[exp_sym] = seq_expect[exp_sym] + 16'd1;
    endtask

    task automatic init_defaults;
        enable           = 1'b0;
        lfsr_load        = 1'b0;
        lfsr_seed        = 32'hACE1_CAFE;
        quote_ready      = 1'b1;
        quote_interval   = 32'd1;
        active_regime    = REGIME_CALM;
        active_sym_count = TB_NUM_SYM[7:0];
        for (int s = 0; s < TB_NUM_SYM; s++) begin
            init_mid[s]    = price_t'(32'h0064_0000 + (s * 32'h0010_0000));
            init_spread[s] = base_spread_for(REGIME_CALM);
            sector_id[s]   = SECTOR_ID_W'(s);
            seq_expect[s]  = 16'd0;
        end
    endtask

    // -------------------------------------------------------------------------
    // Main phased test
    // -------------------------------------------------------------------------
    initial begin
        int exp_sym;
        int sym_wrap;
        int q;
        bit seen_volatile;
        logic [COUNTER_W-1:0] qg_before_block;

        wait (rst_n === 1'b1);
        @(posedge clk);

        init_defaults();

        // ---------------- Phase 1: main run (60 quotes, regime switch) ----------------
        pulse_lfsr_load();
        enable = 1'b1;
        sym_wrap = TB_NUM_SYM - 1;
        exp_sym  = 0;
        seen_volatile = 1'b0;

        for (q = 0; q < 60; q++) begin
            check_one_quote($sformatf("P1 q%0d", q), exp_sym, sym_wrap);
            if (regime_in_frame == REGIME_VOLATILE) seen_volatile = 1'b1;
            exp_sym = next_sym(exp_sym, sym_wrap);
            if (q == 29) active_regime = REGIME_VOLATILE;
        end
        check("P1: quotes_generated==60", quotes_generated == 60);
        check("P1: saw VOLATILE", seen_volatile);

        // ---------------- Phase 2: backpressure (quote_interval>1 so threshold can stall) ----------------
        enable = 1'b0;
        @(posedge clk);
        init_defaults();
        active_sym_count = TB_NUM_SYM[7:0];
        quote_interval   = 32'd5;
        pulse_lfsr_load();
        enable = 1'b1;
        quote_ready = 1'b1;
        sym_wrap = TB_NUM_SYM - 1;
        exp_sym  = 0;
        for (int s = 0; s < TB_NUM_SYM; s++) seq_expect[s] = 16'd0;

        // One quote to advance FSM (sym 0). quote_interval>1 so the next cycle does not commit:
        // quote_valid must be a single-cycle pulse (not held across idle cycles).
        check_one_quote("P2 pre-block", exp_sym, sym_wrap);
        check("P2 quote_valid pulse width: high on emission cycle", quote_valid === 1'b1);
        @(posedge clk);
        check("P2 quote_valid pulse width: low next cycle (no back-to-back tick)", quote_valid === 1'b0);
        exp_sym = next_sym(exp_sym, sym_wrap);

        qg_before_block = quotes_generated;
        // Block downstream: no commits while not ready; counter must not advance
        quote_ready = 1'b0;
        repeat (40) begin
            @(posedge clk);
            check("P2: no quote_valid while blocked", quote_valid === 1'b0);
            check("P2: quotes_generated stable while blocked", quotes_generated == qg_before_block);
        end
        quote_ready = 1'b1;

        // Next quote must continue round-robin (sym 1)
        check_one_quote("P2 post-block", exp_sym, sym_wrap);
        exp_sym = next_sym(exp_sym, sym_wrap);
        check_one_quote("P2 post-block b", exp_sym, sym_wrap);

        // ---------------- Phase 3: active_sym_count == 2 ----------------
        enable = 1'b0;
        @(posedge clk);
        init_defaults();
        active_sym_count = 8'd2;
        quote_interval   = 32'd1;
        pulse_lfsr_load();
        enable = 1'b1;
        sym_wrap = 1; // symbols 0..1 only
        exp_sym  = 0;
        for (int s = 0; s < TB_NUM_SYM; s++) seq_expect[s] = 16'd0;

        repeat (8) begin
            check_one_quote("P3 active2", exp_sym, sym_wrap);
            exp_sym = next_sym(exp_sym, sym_wrap);
        end

        // ---------------- Phase 4: mid-run lfsr_load reload ----------------
        enable = 1'b0;
        @(posedge clk);
        init_defaults();
        active_sym_count = TB_NUM_SYM[7:0];
        quote_interval   = 32'd1;
        pulse_lfsr_load();
        enable = 1'b1;
        sym_wrap = TB_NUM_SYM - 1;
        exp_sym  = 0;
        for (int s = 0; s < TB_NUM_SYM; s++) seq_expect[s] = 16'd0;

        repeat (5) begin
            check_one_quote("P4 pre-reload", exp_sym, sym_wrap);
            exp_sym = next_sym(exp_sym, sym_wrap);
        end
        check("P4: quotes before reload", quotes_generated == 5);

        // Hold enable low across reload so the post-pulse cycle cannot emit a quote
        // before we sample quotes_generated (RTL clears counter on lfsr_load edge).
        enable = 1'b0;
        @(posedge clk);
        pulse_lfsr_load();
        check("P4: quotes_generated cleared on lfsr_load", quotes_generated == 0);
        enable = 1'b1;
        for (int s = 0; s < TB_NUM_SYM; s++) seq_expect[s] = 16'd0;
        exp_sym = 0;

        // sym_ptr resets to 0 on lfsr_load (RTL); first post-reload quote must be symbol 0 — that is the behavioral check.
        // After reload, first quote seq for sym0 should be 0 again; prices match init_mid band
        check_one_quote("P4 after reload", 0, sym_wrap);
        check("P4: best_bid[0] sane after reload",
              best_bid[0] >= price_t'(MIN_PRICE_Q16_16));

        // ---------------- Phase 5: quote_interval == 0 (every enabled cycle) ----------------
        enable = 1'b0;
        @(posedge clk);
        init_defaults();
        quote_interval   = 32'd0;
        active_sym_count = TB_NUM_SYM[7:0];
        pulse_lfsr_load();
        enable = 1'b1;
        sym_wrap = TB_NUM_SYM - 1;
        exp_sym  = 0;
        for (int s = 0; s < TB_NUM_SYM; s++) seq_expect[s] = 16'd0;

        repeat (10) begin
            check_one_quote("P5 interval0", exp_sym, sym_wrap);
            exp_sym = next_sym(exp_sym, sym_wrap);
        end
        check("P5: quotes_generated==10", quotes_generated == 10);

        if (err_count == 0)
            $display("tb_market_sim: PASS (all checks passed)");
        else
            $display("tb_market_sim: FAIL (%0d errors)", err_count);

        $finish;
    end

endmodule
