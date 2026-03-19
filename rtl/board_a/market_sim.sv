// ============================================================================
// Module: market_sim
// LFSR-driven market simulator. Maintains per-symbol mid_price and spread.
// Each quote_interval cycles, updates one symbol's prices using a scaled
// pseudo-random step, builds a 128-bit QUOTE frame, and round-robins
// through all symbols. Exports live bid/ask arrays for exchange_lite.
// ============================================================================

`timescale 1ns / 1ps

module market_sim
    import hft_pkg::*;
#(
    parameter NUM_SYM = NUM_SYMBOLS
)(
    input  logic                 clk,
    input  logic                 rst_n,
    input  logic                 enable,              // high when FSM is RUNNING

    // LFSR control
    input  logic                 lfsr_load,            // pulse: load seed (IDLE→RUNNING)
    input  logic [31:0]          lfsr_seed,            // from AXI register

    // Configuration
    input  regime_e              active_regime,
    input  logic [31:0]          quote_interval,       // cycles between quote rounds
    input  price_t               init_mid    [NUM_SYM], // per-symbol initial mid prices
    input  price_t               init_spread [NUM_SYM], // per-symbol initial spreads

    // Quote frame output (to quote FIFO / tx_arbiter)
    output logic [FRAME_W-1:0]  quote_frame,
    output logic                 quote_valid,
    input  logic                 quote_ready,          // backpressure

    // Live prices (for exchange_lite order matching)
    output price_t               best_bid [NUM_SYM],
    output price_t               best_ask [NUM_SYM],

    // Status
    output logic [COUNTER_W-1:0] quotes_generated
);

    // ---------------------------------------------------------------------
    // Constants (Q16.16)
    // ---------------------------------------------------------------------
    localparam sprice_t MIN_PRICE_Q16_16 = sprice_t'(32'h0001_0000); // $1.00
    localparam sprice_t MAX_PRICE_Q16_16 = sprice_t'(32'h2710_0000); // $10,000.00

    // ---------------------------------------------------------------------
    // LFSR instance (one pseudo-random step per quote generation)
    // ---------------------------------------------------------------------
    logic [31:0] lfsr_rand;
    logic        lfsr_enable;

    lfsr32 u_lfsr32 (
        .clk     (clk),
        .rst_n   (rst_n),
        .enable  (lfsr_enable),
        .load    (lfsr_load),
        .seed_in (lfsr_seed),
        .rand_out(lfsr_rand)
    );

    // ---------------------------------------------------------------------
    // Per-symbol state
    // ---------------------------------------------------------------------
    price_t mid_price [NUM_SYM];
    price_t spread    [NUM_SYM];
    logic   [15:0] seq_num [NUM_SYM];

    // Round-robin pointer and quote interval counter
    localparam int SYM_PTR_W = (NUM_SYM > 1) ? $clog2(NUM_SYM) : 1;
    logic [SYM_PTR_W-1:0] sym_ptr;
    logic [31:0]          quote_ctr;

    // ---------------------------------------------------------------------
    // Regime parameter mapping (Q16.16)
    // ---------------------------------------------------------------------
    price_t step_size_q16_16;
    price_t base_spread_q16_16;

    always_comb begin
        unique case (active_regime)
            REGIME_CALM: begin
                step_size_q16_16   = 32'h0000_0100;
                base_spread_q16_16 = 32'h0000_2000;
            end
            REGIME_VOLATILE: begin
                step_size_q16_16   = 32'h0000_1000;
                base_spread_q16_16 = 32'h0000_8000;
            end
            REGIME_BURST: begin
                step_size_q16_16   = 32'h0000_0100;
                base_spread_q16_16 = 32'h0000_2000;
            end
            default: begin // REGIME_ADVERSARIAL
                step_size_q16_16   = 32'h0000_4000;
                base_spread_q16_16 = 32'h0001_0000;
            end
        endcase
    end

    // ---------------------------------------------------------------------
    // Quote scheduling: generate exactly one QUOTE per quote_interval cycles,
    // but only when quote_ready is asserted.
    // ---------------------------------------------------------------------
    logic tick_raw;
    logic do_quote;

    assign tick_raw = enable && (
        (quote_interval == 32'd0) ? 1'b1 : (quote_ctr == (quote_interval - 1))
    );
    assign do_quote = tick_raw && quote_ready;

    // Advance LFSR only when generating a quote.
    assign lfsr_enable = do_quote;

    // ---------------------------------------------------------------------
    // Frame registers
    // ---------------------------------------------------------------------
    logic [FRAME_W-1:0] quote_frame_next;
    logic [FRAME_W-1:0] quote_frame_hold;

    integer s;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            sym_ptr          <= '0;
            quote_ctr        <= 32'd0;
            quote_valid      <= 1'b0;
            quote_frame_hold <= '0;
            quotes_generated <= '0;

            for (s = 0; s < NUM_SYM; s++) begin
                mid_price[s] <= init_mid[s];
                spread[s]    <= (init_spread[s] == '0) ? 32'h0000_0001 : init_spread[s];
                seq_num[s]   <= '0;

                // Initialize best bid/ask from init_* values.
                begin
                    sprice_t mid_s = sprice_t'(init_mid[s]);
                    sprice_t spr_s = sprice_t'((init_spread[s] == '0) ? 32'h0000_0001 : init_spread[s]);
                    sprice_t spr_h = spr_s >>> 1;
                    sprice_t bid_s = mid_s - spr_h;
                    sprice_t ask_s = mid_s + spr_h;

                    if (bid_s < MIN_PRICE_Q16_16) best_bid[s] <= price_t'(MIN_PRICE_Q16_16);
                    else if (bid_s > MAX_PRICE_Q16_16) best_bid[s] <= price_t'(MAX_PRICE_Q16_16);
                    else best_bid[s] <= price_t'(bid_s);

                    if (ask_s < MIN_PRICE_Q16_16) best_ask[s] <= price_t'(MIN_PRICE_Q16_16);
                    else if (ask_s > MAX_PRICE_Q16_16) best_ask[s] <= price_t'(MAX_PRICE_Q16_16);
                    else best_ask[s] <= price_t'(ask_s);
                end
            end
        end else begin
            // Default: one-cycle pulse on quote_valid
            quote_valid <= 1'b0;

            // When not enabled, stall counters.
            if (!enable) begin
                quote_ctr <= 32'd0;
                sym_ptr   <= sym_ptr;
            end else begin
                if (tick_raw) begin
                    if (!quote_ready) begin
                        // Hold at the threshold until downstream accepts.
                        quote_ctr <= quote_ctr;
                    end else begin
                        quote_ctr <= 32'd0;
                    end
                end else begin
                    quote_ctr <= quote_ctr + 32'd1;
                end

                if (do_quote) begin
                    // ----------------------------
                    // Price evolution step
                    // ----------------------------
                    logic [4:0] raw_step;
                    logic signed [31:0] signed_step_s;
                    logic signed [63:0] delta64;
                    logic signed [31:0] delta_s;

                    logic signed [31:0] mid_s;
                    logic signed [31:0] new_mid_s;
                    logic [31:0]        new_mid_u;

                    // Declare all temps up-front (Verilator is picky about
                    // declarations after statements).
                    price_t  new_spread_q;
                    sprice_t spr_h_s;
                    sprice_t bid_s2, ask_s2;
                    price_t  bid_calc, ask_calc;
                    logic [15:0] bid_size_calc, ask_size_calc;

                    raw_step = lfsr_rand[4:0]; // 0..31
                    signed_step_s = $signed({1'b0, raw_step}) - 32'sd16; // -16..+15
                    delta64 = $signed(signed_step_s) * $signed(step_size_q16_16); // still Q16.16
                    delta_s = delta64[31:0];

                    mid_s     = $signed(mid_price[sym_ptr]);
                    new_mid_s = mid_s + delta_s;

                    if (new_mid_s < MIN_PRICE_Q16_16) new_mid_u = price_t'(MIN_PRICE_Q16_16);
                    else if (new_mid_s > MAX_PRICE_Q16_16) new_mid_u = price_t'(MAX_PRICE_Q16_16);
                    else new_mid_u = price_t'(new_mid_s);

                    // Spread is kept as regime base_spread.
                    new_spread_q = base_spread_q16_16;
                    if (new_spread_q == '0) new_spread_q = 32'h0000_0001;

                    // Bid/ask from mid +/- (spread>>1), with saturation.
                    spr_h_s = sprice_t'(new_spread_q) >>> 1;
                    bid_s2  = sprice_t'(new_mid_u) - spr_h_s;
                    ask_s2  = sprice_t'(new_mid_u) + spr_h_s;

                    if (bid_s2 < MIN_PRICE_Q16_16) bid_calc = price_t'(MIN_PRICE_Q16_16);
                    else if (bid_s2 > MAX_PRICE_Q16_16) bid_calc = price_t'(MAX_PRICE_Q16_16);
                    else bid_calc = price_t'(bid_s2);

                    if (ask_s2 < MIN_PRICE_Q16_16) ask_calc = price_t'(MIN_PRICE_Q16_16);
                    else if (ask_s2 > MAX_PRICE_Q16_16) ask_calc = price_t'(MAX_PRICE_Q16_16);
                    else ask_calc = price_t'(ask_s2);

                    // ----------------------------
                    // Commit state + outputs
                    // ----------------------------
                    mid_price[sym_ptr] <= price_t'(new_mid_u);
                    spread[sym_ptr]    <= new_spread_q;
                    best_bid[sym_ptr]  <= bid_calc;
                    best_ask[sym_ptr]  <= ask_calc;

                    // Sizes kept constant but non-zero.
                    bid_size_calc = 16'd1000;
                    ask_size_calc = 16'd1000;

                    quote_frame_next = '0;
                    quote_frame_next[127:124] = MSG_QUOTE;
                    quote_frame_next[123:116] = price_t'(sym_ptr); // zero-extend
                    quote_frame_next[115:114] = active_regime;
                    quote_frame_next[113:112] = 2'b00;
                    quote_frame_next[111:80]  = bid_calc;
                    quote_frame_next[79:48]   = ask_calc;
                    quote_frame_next[47:32]  = bid_size_calc;
                    quote_frame_next[31:16]  = ask_size_calc;
                    quote_frame_next[15:0]    = seq_num[sym_ptr];

                    quote_frame_hold <= quote_frame_next;
                    quote_valid      <= 1'b1;
                    quotes_generated <= quotes_generated + 1'b1;

                    // Increment sequence + round-robin pointer.
                    seq_num[sym_ptr] <= seq_num[sym_ptr] + 16'd1;
                    if (sym_ptr == (NUM_SYM-1)) sym_ptr <= '0;
                    else sym_ptr <= sym_ptr + 1'b1;
                end
            end
        end
    end

    assign quote_frame = quote_frame_hold;

endmodule
