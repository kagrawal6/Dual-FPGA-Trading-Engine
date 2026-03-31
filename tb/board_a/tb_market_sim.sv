// ============================================================================
// Testbench: tb_market_sim
// Golden quote frames (128-bit), all 4 regimes, counter_clr, quote_interval=0,
// price clamping, mean reversion, active_sym_count transitions, backpressure,
// lfsr_load while enable=1.
// Golden vectors from gen_board_a_vectors.py (seed=0xDEADBEEF, 4 syms, CALM).
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_market_sim;
    localparam int TB_NUM_SYM = 4;

    logic                     clk;
    logic                     rst_n;
    logic                     enable;
    logic                     lfsr_load;
    logic                     counter_clr_sig;
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

    int pass_count = 0;
    int fail_count = 0;

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
        .counter_clr      (counter_clr_sig),
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

    task automatic check128(string msg, logic [127:0] actual, logic [127:0] expected);
        if (actual === expected) pass_count++;
        else begin
            $error("FAIL: %s", msg);
            $error("  got: %032h", actual);
            $error("  exp: %032h", expected);
            fail_count++;
        end
    endtask

    // Wait for next quote_valid pulse
    task automatic wait_quote(input int timeout = 500);
        int cnt = 0;
        while (!quote_valid && cnt < timeout) begin
            @(posedge clk); #1;
            cnt++;
        end
    endtask

    task automatic pulse_lfsr_load;
        lfsr_load = 1'b1;
        @(posedge clk);
        lfsr_load = 1'b0;
        @(posedge clk);
    endtask

    // Golden 128-bit quote frames (first 16 quotes, CALM, seed=0xDEADBEEF)
    localparam logic [127:0] GQ [16] = '{
        128'h100000B3F81E00B4081E03E803E80000,
        128'h101001A3F82101A4082103E803E80000,
        128'h10200383F8160384081603E803E80000,
        128'h10300072F81D0073081D03E803E80000,
        128'h100000B3F83100B4083103E803E80001,
        128'h101001A3F81601A4081603E803E80001,
        128'h10200383F8250384082503E803E80001,
        128'h10300072F82E0073082E03E803E80001,
        128'h100000B3F81A00B4081A03E803E80002,
        128'h101001A3F81801A4081803E803E80002,
        128'h10200383F81B0384081B03E803E80002,
        128'h10300072F80D0073080D03E803E80002,
        128'h100000B3F80B00B4080B03E803E80003,
        128'h101001A3F7F401A407F403E803E80003,
        128'h10200383F7FE038407FE03E803E80003,
        128'h10300072F80F0073080F03E803E80003
    };

    localparam sprice_t MIN_P = sprice_t'(32'h0001_0000);
    localparam sprice_t MAX_P = sprice_t'(32'h2710_0000);

    task automatic init_defaults;
        enable           = 1'b0;
        lfsr_load        = 1'b0;
        counter_clr_sig  = 1'b0;
        lfsr_seed        = 32'hDEAD_BEEF;
        quote_ready      = 1'b1;
        quote_interval   = 32'd0;
        active_regime    = REGIME_CALM;
        active_sym_count = TB_NUM_SYM[7:0];
        init_mid[0]    = 32'h00B4_0000; // $180.00
        init_mid[1]    = 32'h01A4_0000; // $420.00
        init_mid[2]    = 32'h0384_0000; // $900.00
        init_mid[3]    = 32'h0073_0000; // $115.00
        init_spread[0] = 32'h0000_199A; // $0.10
        init_spread[1] = 32'h0000_2666; // $0.15
        init_spread[2] = 32'h0000_4000; // $0.25
        init_spread[3] = 32'h0000_147B; // $0.08
        sector_id[0] = SECTOR_ID_W'(0);
        sector_id[1] = SECTOR_ID_W'(0);
        sector_id[2] = SECTOR_ID_W'(1);
        sector_id[3] = SECTOR_ID_W'(1);
    endtask

    initial begin
        $dumpfile("tb_market_sim.vcd");
        $dumpvars(0, tb_market_sim);

        wait (rst_n === 1'b1);
        @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 1) Golden quote frames (128-bit comparison)
        // ─────────────────────────────────────────────────────
        $display("--- test_golden_quotes ---");
        init_defaults();
        pulse_lfsr_load();
        enable = 1'b1;

        for (int q = 0; q < 16; q++) begin
            wait_quote(); #1;
            check128($sformatf("golden quote[%0d]", q), quote_frame, GQ[q]);
            check($sformatf("gq[%0d] msg_type", q), quote_frame[127:124] == 4'h1);
            check($sformatf("gq[%0d] symbol=%0d", q, q%4), quote_frame[123:116] == 8'(q%4));
            check($sformatf("gq[%0d] bid_size", q), quote_frame[47:32] == 16'd1000);
            check($sformatf("gq[%0d] ask_size", q), quote_frame[31:16] == 16'd1000);
            check($sformatf("gq[%0d] seq_num=%0d", q, q/4), quote_frame[15:0] == 16'(q/4));
            @(posedge clk);
        end
        enable = 1'b0;
        @(posedge clk); #1;
        check32("quotes_generated=16", quotes_generated, 16);
        @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 2) All 4 regimes: verify spread matches
        // ─────────────────────────────────────────────────────
        $display("--- test_all_regimes ---");
        begin
            regime_e regimes [4] = '{REGIME_CALM, REGIME_VOLATILE, REGIME_BURST, REGIME_ADVERSARIAL};
            logic [31:0] expected_spreads [4] = '{32'h0000_1000, 32'h0000_4000, 32'h0000_1000, 32'h0000_8000};
            for (int r = 0; r < 4; r++) begin
                init_defaults();
                active_regime = regimes[r];
                pulse_lfsr_load();
                enable = 1'b1;
                for (int q = 0; q < 4; q++) begin
                    wait_quote(); #1;
                    begin
                        logic [31:0] bid_u, ask_u, spread;
                        bid_u = quote_frame[111:80];
                        ask_u = quote_frame[79:48];
                        spread = ask_u - bid_u;
                        check32($sformatf("regime%0d q%0d spread", r, q), spread, expected_spreads[r]);
                    end
                    @(posedge clk);
                end
                enable = 1'b0;
                @(posedge clk);
            end
        end

        // ─────────────────────────────────────────────────────
        // 3) counter_clr: quotes_generated resets
        // ─────────────────────────────────────────────────────
        $display("--- test_counter_clr ---");
        init_defaults();
        pulse_lfsr_load();
        enable = 1'b1;
        repeat (4) begin wait_quote(); @(posedge clk); end
        #1;
        check("pre-clr count>0", quotes_generated > 0);
        counter_clr_sig = 1'b1;
        @(posedge clk);
        counter_clr_sig = 1'b0;
        @(posedge clk); #1;
        check32("counter_clr: count=0", quotes_generated, 0);
        enable = 1'b0;
        @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 4) quote_interval=0: quote every enabled cycle
        // ─────────────────────────────────────────────────────
        $display("--- test_interval_0 ---");
        init_defaults();
        quote_interval = 32'd0;
        pulse_lfsr_load();
        enable = 1'b1;
        repeat (10) begin wait_quote(); @(posedge clk); end
        check32("interval0: 10 quotes", quotes_generated, 10);
        enable = 1'b0;
        @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 5) Backpressure: quote_ready=0 freezes generation
        // ─────────────────────────────────────────────────────
        $display("--- test_backpressure ---");
        init_defaults();
        pulse_lfsr_load();
        enable = 1'b1;
        repeat (2) begin wait_quote(); @(posedge clk); end
        begin
            logic [COUNTER_W-1:0] cnt_before;
            quote_ready = 1'b0;
            repeat (2) @(posedge clk);
            #1;
            cnt_before = quotes_generated;
            repeat (100) begin
                @(posedge clk); #1;
                check("bp: no quote_valid", quote_valid == 1'b0);
                check("bp: count stable", quotes_generated == cnt_before);
            end
            quote_ready = 1'b1;
            wait_quote();
            check("bp: resumed quote_valid", quote_valid == 1'b1);
            #1;
            check("bp: count advanced", quotes_generated == cnt_before + 1);
        end
        enable = 1'b0;
        @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 6) active_sym_count transitions: 4→2
        // ─────────────────────────────────────────────────────
        $display("--- test_active_transition ---");
        init_defaults();
        pulse_lfsr_load();
        enable = 1'b1;
        repeat (4) begin wait_quote(); @(posedge clk); end
        active_sym_count = 8'd2;
        repeat (4) @(posedge clk);
        for (int q = 0; q < 8; q++) begin
            wait_quote(); #1;
            check($sformatf("active2 q%0d sym<2", q), quote_frame[123:116] < 8'd2);
            @(posedge clk);
        end
        active_sym_count = TB_NUM_SYM[7:0];
        enable = 1'b0;
        @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 7) Price clamping: init near MAX_PRICE
        // ─────────────────────────────────────────────────────
        $display("--- test_price_clamp ---");
        init_defaults();
        init_mid[0] = 32'h2710_0000; // exactly MAX_PRICE ($10000)
        init_spread[0] = 32'h0000_1000;
        active_sym_count = 8'd1;
        pulse_lfsr_load();
        enable = 1'b1;
        for (int q = 0; q < 8; q++) begin
            wait_quote(); #1;
            begin
                logic [31:0] bid_u, ask_u;
                bid_u = quote_frame[111:80];
                ask_u = quote_frame[79:48];
                check($sformatf("clamp q%0d bid<=MAX", q), bid_u <= 32'h2710_0000);
                check($sformatf("clamp q%0d ask<=MAX", q), ask_u <= 32'h2710_0000);
                check($sformatf("clamp q%0d bid>=MIN", q), bid_u >= 32'h0001_0000);
            end
            @(posedge clk);
        end
        enable = 1'b0;
        @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 8) Mean reversion: prices stay near init_mid
        // ─────────────────────────────────────────────────────
        $display("--- test_mean_reversion ---");
        init_defaults();
        active_sym_count = 8'd1;
        pulse_lfsr_load();
        enable = 1'b1;
        begin
            logic [31:0] last_mid;
            longint total_disp = 0;
            for (int q = 0; q < 200; q++) begin
                wait_quote(); #1;
                last_mid = (quote_frame[111:80] + quote_frame[79:48]) >> 1;
                begin
                    longint disp;
                    disp = $signed(last_mid) - $signed(init_mid[0]);
                    if (disp < 0) disp = -disp;
                    total_disp += disp;
                end
                @(posedge clk);
            end
            // Average displacement should be modest (< $50 in Q16.16 = 0x320000)
            check("mean_rev: avg displacement bounded", (total_disp / 200) < 64'sh0032_0000);
        end
        enable = 1'b0;
        @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 9) lfsr_load reloads state (sym_ptr=0, seq_num=0)
        // ─────────────────────────────────────────────────────
        $display("--- test_lfsr_load_reload ---");
        init_defaults();
        active_sym_count = TB_NUM_SYM[7:0];
        pulse_lfsr_load();
        enable = 1'b1;
        repeat (5) begin wait_quote(); @(posedge clk); end
        #1;
        check("pre-reload count>0", quotes_generated > 0);
        enable = 1'b0;
        @(posedge clk);
        pulse_lfsr_load();
        #1;
        check32("lfsr_load: count=0", quotes_generated, 0);
        enable = 1'b1;
        wait_quote(); #1;
        check("reload: first quote sym=0", quote_frame[123:116] == 8'd0);
        check("reload: seq_num=0", quote_frame[15:0] == 16'd0);
        check128("reload: matches GQ[0]", quote_frame, GQ[0]);
        enable = 1'b0;
        @(posedge clk);

        // ─────────────────────────────────────────────────────
        // Summary
        // ─────────────────────────────────────────────────────
        $display("\n===================================");
        if (fail_count == 0)
            $display("tb_market_sim: PASS (%0d checks passed)", pass_count);
        else begin
            $display("tb_market_sim: FAIL (%0d passed, %0d failed)", pass_count, fail_count);
            $fatal;
        end
        $display("===================================");
        $finish;
    end

endmodule
