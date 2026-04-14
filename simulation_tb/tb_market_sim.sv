`timescale 1ns / 1ps

module tb_market_sim();
    import hft_pkg::*;

    localparam NUM_SYM = 4;

    logic                    clk, rst_n, enable, counter_clr, lfsr_load;
    logic [31:0]             lfsr_seed;
    regime_e                 active_regime;
    logic [31:0]             quote_interval;
    logic [7:0]              active_sym_count;
    logic [SECTOR_ID_W-1:0]  sector_id [NUM_SYM];
    price_t                  init_mid    [NUM_SYM];
    price_t                  init_spread [NUM_SYM];
    logic [FRAME_W-1:0]     quote_frame;
    logic                    quote_valid, quote_ready;
    price_t                  best_bid [NUM_SYM];
    price_t                  best_ask [NUM_SYM];
    logic [COUNTER_W-1:0]   quotes_generated;

    integer err_cnt = 0;
    integer i;

    // Variables for new tests
    price_t calm_spread, vol_spread;
    logic [COUNTER_W-1:0] cnt_before;

    always #5 clk = ~clk;

    market_sim #(.NUM_SYM(NUM_SYM), .NUM_SECTORS(2)) dut (
        .clk(clk), .rst_n(rst_n), .enable(enable),
        .counter_clr(counter_clr), .lfsr_load(lfsr_load),
        .lfsr_seed(lfsr_seed), .active_regime(active_regime),
        .quote_interval(quote_interval), .active_sym_count(active_sym_count),
        .sector_id(sector_id), .init_mid(init_mid), .init_spread(init_spread),
        .quote_frame(quote_frame), .quote_valid(quote_valid),
        .quote_ready(quote_ready), .best_bid(best_bid), .best_ask(best_ask),
        .quotes_generated(quotes_generated)
    );

    initial begin
        clk = 0; rst_n = 0; enable = 0; counter_clr = 0;
        lfsr_load = 0; quote_ready = 1;
        lfsr_seed       = 32'hDEAD_BEEF;
        active_regime   = REGIME_CALM;
        quote_interval  = 32'd0;
        active_sym_count = 8'd4;

        sector_id[0] = 3'd0; sector_id[1] = 3'd0;
        sector_id[2] = 3'd1; sector_id[3] = 3'd1;
        init_mid[0] = 32'h00B4_0000;   // $180 Q16.16
        init_mid[1] = 32'h01A4_0000;   // $420
        init_mid[2] = 32'h0384_0000;   // $900
        init_mid[3] = 32'h0073_0000;   // $115
        for (i = 0; i < NUM_SYM; i++) init_spread[i] = 32'h0000_1000;

        #20; rst_n = 1; @(posedge clk);

        // Pulse lfsr_load, then enable
        lfsr_load = 1; @(posedge clk);
        lfsr_load = 0; enable = 1;

        // Test 1: first quote msg_type = QUOTE (0x1)
        @(posedge quote_valid); #1;
        if (quote_frame[127:124] !== MSG_QUOTE) begin
            $display("FAIL: msg_type=%h, expected %h", quote_frame[127:124], MSG_QUOTE);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: msg_type = QUOTE");

        // Test 2: first quote symbol == 0
        if (quote_frame[123:116] !== 8'd0) begin
            $display("FAIL: symbol=%0d, expected 0", quote_frame[123:116]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: first symbol = 0");

        // Test 3: bid < ask
        if (quote_frame[111:80] >= quote_frame[79:48]) begin
            $display("FAIL: bid=%h >= ask=%h", quote_frame[111:80], quote_frame[79:48]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: bid < ask (bid=%h, ask=%h)", quote_frame[111:80], quote_frame[79:48]);

        // Test 4: symbols rotate 1, 2, 3
        for (i = 1; i < 4; i++) begin
            begin : wait_sym
                automatic int guard;
                guard = 0;
                while (1) begin
                    @(posedge clk);
                    #1;
                    guard = guard + 1;
                    if (guard > 500) begin
                        $display("FAIL: timeout waiting for symbol %0d", i);
                        err_cnt = err_cnt + 1;
                        disable wait_sym;
                    end
                    if (quote_frame[123:116] === i[7:0])
                        disable wait_sym;
                end
            end
            #1;
            if (quote_frame[123:116] !== i[7:0]) begin
                $display("FAIL: symbol=%0d, expected %0d", quote_frame[123:116], i);
                err_cnt = err_cnt + 1;
            end else
                $display("PASS: symbol %0d rotated correctly", i);
        end

        // Test 5: quotes_generated counter
        @(posedge clk); #1;
        if (quotes_generated < 32'd4) begin
            $display("FAIL: quotes_generated=%0d, expected >= 4", quotes_generated);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: quotes_generated=%0d", quotes_generated);

        // ----------------------------------------------------------------
        // Test 6: regime change to VOLATILE widens spread
        // CALM base_spread = 0x1000, VOLATILE base_spread = 0x4000 (4x wider)
        // ----------------------------------------------------------------
        calm_spread = best_ask[0] - best_bid[0];
        active_regime = REGIME_VOLATILE;
        // Let all 4 symbols cycle through twice under the new regime
        repeat(10) @(posedge clk); #1;
        vol_spread = best_ask[0] - best_bid[0];

        if (vol_spread <= calm_spread) begin
            $display("FAIL: VOLATILE spread=%h not wider than CALM spread=%h",
                     vol_spread, calm_spread);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: VOLATILE spread=%h > CALM spread=%h",
                     vol_spread, calm_spread);

        // Restore CALM regime for remaining tests
        active_regime = REGIME_CALM;
        repeat(5) @(posedge clk);

        // ----------------------------------------------------------------
        // Test 7: counter_clr resets quotes_generated to 0
        // ----------------------------------------------------------------
        enable = 0;
        quote_ready = 0;
        repeat(3) @(posedge clk);
        counter_clr = 1;
        @(posedge clk);
        counter_clr = 0;
        @(posedge clk); #1;

        if (quotes_generated !== 32'd0) begin
            $display("FAIL: quotes_generated=%0d after counter_clr, expected 0",
                     quotes_generated);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: counter_clr reset quotes_generated to 0");

        quote_ready = 1;
        enable = 1;

        // Let a few quotes flow to get a non-zero baseline for Test 8
        repeat(6) @(posedge clk); #1;

        // ----------------------------------------------------------------
        // Test 8: backpressure — quote_ready=0 suppresses emission
        // market_sim uses pulse-valid semantics: quote_valid only fires when
        // quote_ready is high, so backpressure stalls the producer entirely.
        // ----------------------------------------------------------------
        cnt_before = quotes_generated;
        quote_ready = 0;
        repeat(10) @(posedge clk); #1;

        if (quote_valid !== 1'b0) begin
            $display("FAIL: quote_valid=%b under backpressure, expected 0 (pulse-valid)",
                     quote_valid);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: quote_valid=0 under backpressure (pulse-valid semantics)");

        if (quotes_generated !== cnt_before) begin
            $display("FAIL: quotes_generated advanced under backpressure (%0d -> %0d)",
                     cnt_before, quotes_generated);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: quotes_generated stalled under backpressure (%0d)", cnt_before);

        quote_ready = 1;

        // Summary
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
