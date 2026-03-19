// ============================================================================
// Testbench: tb_market_sim
// Tests the market_sim module:
//   - instantiates lfsr32 to produce deterministic pseudo-random price steps
//   - updates one symbol per quote_interval (round-robin)
//   - generates QUOTE frames with the expected bit layout
//   - regime switching changes spread/step parameters on subsequent quotes
//   - outputs stay within range and satisfy ask>=bid
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_market_sim;
    // ---------------------------------------------------------------------
    // DUT signals
    // ---------------------------------------------------------------------
    logic                     clk;
    logic                     rst_n;
    logic                     enable;
    logic                     lfsr_load;
    logic [31:0]              lfsr_seed;
    regime_e                  active_regime;
    logic [31:0]              quote_interval;
    price_t                   init_mid    [4];
    price_t                   init_spread [4];
    logic [FRAME_W-1:0]       quote_frame;
    logic                     quote_valid;
    logic                     quote_ready;
    price_t                   best_bid    [4];
    price_t                   best_ask    [4];
    logic [COUNTER_W-1:0]     quotes_generated;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    market_sim dut (
        .clk             (clk),
        .rst_n           (rst_n),
        .enable          (enable),
        .lfsr_load       (lfsr_load),
        .lfsr_seed       (lfsr_seed),
        .active_regime   (active_regime),
        .quote_interval  (quote_interval),
        .init_mid        (init_mid),
        .init_spread     (init_spread),
        .quote_frame     (quote_frame),
        .quote_valid     (quote_valid),
        .quote_ready     (quote_ready),
        .best_bid        (best_bid),
        .best_ask        (best_ask),
        .quotes_generated(quotes_generated)
    );

    // ---------------------------------------------------------------------
    // Checks / bookkeeping
    // ---------------------------------------------------------------------
    int err_count = 0;

    task automatic check(input string msg, input logic cond);
        if (!cond) begin
            $error("FAIL: %s", msg);
            err_count++;
        end
    endtask

    // ---------------------------------------------------------------------
    // VCD dump
    // ---------------------------------------------------------------------
    initial begin
        $dumpfile("tb_market_sim.vcd");
        $dumpvars(0, tb_market_sim);
    end

    // ---------------------------------------------------------------------
    // Golden helpers (match RTL math)
    // ---------------------------------------------------------------------
    localparam sprice_t MIN_PRICE_Q16_16 = sprice_t'(32'h0001_0000);
    localparam sprice_t MAX_PRICE_Q16_16 = sprice_t'(32'h2710_0000);
    localparam logic [31:0] LFSR_TAPS   = 32'h0040_0007;

    function automatic sprice_t clamp_price(input sprice_t v);
        if (v < MIN_PRICE_Q16_16) clamp_price = MIN_PRICE_Q16_16;
        else if (v > MAX_PRICE_Q16_16) clamp_price = MAX_PRICE_Q16_16;
        else clamp_price = v;
    endfunction

    function automatic logic [31:0] lfsr_step(input logic [31:0] state);
        if (state[0]) lfsr_step = (state >> 1) ^ LFSR_TAPS;
        else           lfsr_step = (state >> 1);
    endfunction

    function automatic price_t step_size_for(input regime_e r);
        unique case (r)
            REGIME_CALM:        step_size_for = 32'h0000_0100;
            REGIME_VOLATILE:   step_size_for = 32'h0000_1000;
            REGIME_BURST:      step_size_for = 32'h0000_0100;
            default:           step_size_for = 32'h0000_4000; // adversarial
        endcase
    endfunction

    function automatic price_t base_spread_for(input regime_e r);
        unique case (r)
            REGIME_CALM:        base_spread_for = 32'h0000_2000;
            REGIME_VOLATILE:   base_spread_for = 32'h0000_8000;
            REGIME_BURST:      base_spread_for = 32'h0000_2000;
            default:           base_spread_for = 32'h0001_0000; // adversarial
        endcase
    endfunction

    // ---------------------------------------------------------------------
    // Golden model state (declared at module scope for Verilator)
    // ---------------------------------------------------------------------
    logic [31:0] lfsr_state;
    sprice_t golden_mid    [4];
    sprice_t golden_spread [4];
    logic [15:0] seq_expect [4];

    int  expected_sym;
    int  total_quotes;
    bit  seen_volatile;

    // Per-quote temporaries
    logic [7:0]   sym_id_u8;
    regime_e       regime_in_frame;
    logic [15:0]  seq_in_frame;
    logic [31:0]  bid_u, ask_u;
    price_t        step_sz;
    price_t        spread_b;
    logic signed [31:0] signed_step_s;
    logic signed [63:0] delta64;
    logic signed [31:0] delta_s;
    sprice_t       new_mid_s;
    sprice_t       spr_h;
    sprice_t       bid_s;
    sprice_t       ask_s;
    logic [31:0]  spread_meas;

    // ---------------------------------------------------------------------
    // Main test
    // ---------------------------------------------------------------------
    initial begin
        // Defaults
        enable          = 1'b0;
        lfsr_load       = 1'b0;
        lfsr_seed       = 32'hACE1_CAFE;
        quote_ready     = 1'b1;
        quote_interval  = 32'd1; // easiest alignment for golden checks
        active_regime   = REGIME_CALM;

        for (int s = 0; s < 4; s++) begin
            init_mid[s]    = price_t'(32'h0064_0000 + (s * 32'h0010_0000)); // 100.0 + s*16.0
            init_spread[s] = base_spread_for(REGIME_CALM); // overwritten per-tick in RTL anyway
        end

        // Wait for reset release
        @(posedge clk);
        wait (rst_n === 1'b1);
        @(posedge clk);

        // Load initial seed (while enable=0)
        lfsr_load = 1'b1;
        @(posedge clk);
        lfsr_load = 1'b0;
        @(posedge clk);

        enable = 1'b1;

        // Golden initial state (seed remap handled like lfsr32)
        lfsr_state = lfsr_seed;
        if (lfsr_state == 32'h0) lfsr_state = 32'h1;

        for (int s = 0; s < 4; s++) begin
            golden_mid[s]    = sprice_t'(init_mid[s]);
            golden_spread[s] = sprice_t'(base_spread_for(REGIME_CALM));
            seq_expect[s]    = '0;
        end

        expected_sym = 0;
        total_quotes = 60;
        seen_volatile = 1'b0;

        for (int qi = 0; qi < total_quotes; qi++) begin
            // Wait until a quote is emitted (quote_valid is a 1-cycle pulse)
            @(posedge clk);
            while (!quote_valid) @(posedge clk);

            // Basic frame checks
            check($sformatf("Quote %0d: msg_type==QUOTE", qi),
                  quote_frame[127:124] == 4'h1);

            sym_id_u8 = quote_frame[123:116];
            check($sformatf("Quote %0d: symbol_id within range", qi),
                  sym_id_u8 < 4);

            check($sformatf("Quote %0d: round-robin symbol order", qi),
                  sym_id_u8 == expected_sym[7:0]);

            regime_in_frame = regime_e'(quote_frame[115:114]);
            if (regime_in_frame == REGIME_VOLATILE) seen_volatile = 1'b1;

            seq_in_frame = quote_frame[15:0];
            check($sformatf("Quote %0d: seq_num matches per-symbol counter", qi),
                  seq_in_frame == seq_expect[expected_sym]);

            bid_u = quote_frame[111:80];
            ask_u = quote_frame[79:48];
            check($sformatf("Quote %0d: ask>=bid", qi),
                  $signed(ask_u) >= $signed(bid_u));

            // Golden expected update for this symbol, using current LFSR state
            step_sz = step_size_for(regime_in_frame);
            spread_b = base_spread_for(regime_in_frame);

            signed_step_s = $signed({1'b0, lfsr_state[4:0]}) - 32'sd16;
            delta64 = $signed(signed_step_s) * $signed(step_sz); // Q16.16
            delta_s = delta64[31:0];

            new_mid_s = golden_mid[expected_sym] + delta_s;
            new_mid_s = clamp_price(new_mid_s);

            golden_mid[expected_sym] = new_mid_s;
            golden_spread[expected_sym] =
                sprice_t'(spread_b == '0 ? 32'h0000_0001 : spread_b);

            spr_h  = golden_spread[expected_sym] >>> 1;
            bid_s  = golden_mid[expected_sym] - spr_h;
            ask_s  = golden_mid[expected_sym] + spr_h;
            bid_s  = clamp_price(bid_s);
            ask_s  = clamp_price(ask_s);

            // Compare with emitted prices
            check($sformatf("Quote %0d: bid_price golden match", qi),
                  bid_u === price_t'(bid_s));
            check($sformatf("Quote %0d: ask_price golden match", qi),
                  ask_u === price_t'(ask_s));

            // Spread should match base_spread exactly for these Q16.16 constants
            spread_meas = ask_u - bid_u;
            check($sformatf("Quote %0d: spread matches regime base", qi),
                  spread_meas === (spread_b == '0 ? 32'h0000_0001 : spread_b));

            // Update expected sequence counters + round-robin
            seq_expect[expected_sym] = seq_expect[expected_sym] + 16'd1;
            expected_sym = (expected_sym == 3) ? 0 : (expected_sym + 1);

            // Advance software LFSR model after consuming current state
            lfsr_state = lfsr_step(lfsr_state);

            // Regime switch mid-run: switch after 30 quotes.
            if (qi == 29) begin
                active_regime = REGIME_VOLATILE;
            end
        end

        check("Saw at least one VOLATILE frame after regime switch", seen_volatile == 1'b1);

        if (err_count == 0)
            $display("tb_market_sim: PASS (all checks passed)");
        else
            $display("tb_market_sim: FAIL (%0d errors)", err_count);

        $finish;
    end

endmodule
