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
        // With quote_interval==0, quote_valid stays high every cycle (do_quote every
        // clk); there is no second posedge on quote_valid. Step on clk until the
        // frame's symbol field matches.
        for (i = 1; i < 4; i++) begin
            begin : wait_sym
                automatic int guard = 0;
                // Sample after posedge + delay so quote_frame_hold NBA has settled (avoid
                // reading stale symbol_id on the same tick as the clock edge).
                while (1) begin
                    @(posedge clk);
                    #1;
                    guard++;
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

        // Summary
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
