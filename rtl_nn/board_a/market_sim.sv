// ============================================================================
// Module: market_sim
// Sector-aware market simulator. Maintains per-symbol mid price and spread.
//
// Price step: market_noise_gen.step_out_q16_16[s] is a signed Q16.16-style
// increment (global + sector drift + per-symbol drift, see market_noise_gen).
// market_sim scales it by regime step_size_q16_16 (also Q16.16):
//   delta_price_Q16_16 = (step_out * step_size) >>> 16
// so the product is Q32.32-aligned then brought back to Q16.16 for mid_price.
//
// Quote scheduling: quote_interval==0 means tick every enabled cycle (fastest).
// Otherwise one quote attempt when quote_ctr reaches quote_interval-1.
//
// quote_valid / quote_ready: do_quote = tick_raw && quote_ready, so a quote is
// only emitted when the consumer is already ready — quote_valid is a 1-cycle
// pulse (not a held-valid skid). Intentional for this FIFO-style sink.
//
// Mean-reversion pull-back (Ornstein-Uhlenbeck restoring force):
//   displacement = init_mid[s] - mid_price[s]
//   pullback     = displacement >>> PULLBACK_SHIFT
//   new_mid      = old_mid + noise_delta + pullback
// This creates bounded price oscillations around init_mid, ensuring the
// market simulator produces mean-reverting price dynamics suitable for the
// Board B mean-reversion trading strategy.
//
// Spread model: each update sets spread from base_spread_q16_16 (regime only).
// init_spread[] applies on async reset or lfsr_load only (no sector/company
// spread dynamics).
// ============================================================================

`timescale 1ns / 1ps

module market_sim
    import hft_pkg::*;
#(
    parameter int NUM_SYM     = NUM_SYMBOLS,
    parameter int NUM_SECTORS = hft_pkg::NUM_SECTORS
)(
    input  logic                 clk,
    input  logic                 rst_n,
    input  logic                 enable,              // high when FSM is RUNNING
    input  logic                 counter_clr,         // FSM RESET: clear quote counter only

    // LFSR / config reload (pulse on IDLE→RUNNING): reload symbol state + noise seeds
    input  logic                 lfsr_load,
    input  logic [31:0]          lfsr_seed,            // from AXI register

    // Configuration
    input  regime_e              active_regime,
    input  logic [31:0]          quote_interval,       // 0 = every cycle; else cycles between quote ticks
    input  logic [7:0]           active_sym_count,
    input  logic [SECTOR_ID_W-1:0] sector_id [NUM_SYM],
    input  price_t               init_mid    [NUM_SYM],
    input  price_t               init_spread [NUM_SYM],

    // Quote frame output (to quote FIFO / tx_arbiter)
    output logic [FRAME_W-1:0]  quote_frame,
    output logic                 quote_valid,          // 1-cycle pulse when do_quote (requires quote_ready)
    input  logic                 quote_ready,

    // Live prices (for exchange_lite order matching)
    output price_t               best_bid [NUM_SYM],
    output price_t               best_ask [NUM_SYM],

    // Status
    output logic [COUNTER_W-1:0] quotes_generated
);

    localparam sprice_t MIN_PRICE_Q16_16 = sprice_t'(32'h0001_0000);
    localparam sprice_t MAX_PRICE_Q16_16 = sprice_t'(32'h2710_0000);
    localparam logic [7:0] NUM_SYM_U8 = 8'(NUM_SYM);

    // Signed 32b price delta (Q16.16) after scaling; typedef cast is tool-clear vs plain 32'().
    typedef logic signed [31:0] price_delta_s32_t;

    price_t step_size_q16_16;
    price_t base_spread_q16_16;

    always_comb begin
        unique case (active_regime)
            REGIME_CALM: begin
                step_size_q16_16   = 32'h0000_0400;
                base_spread_q16_16 = 32'h0000_1000;
            end
            REGIME_VOLATILE: begin
                step_size_q16_16   = 32'h0000_8000;
                base_spread_q16_16 = 32'h0000_4000;
            end
            REGIME_BURST: begin
                step_size_q16_16   = 32'h0000_0400;
                base_spread_q16_16 = 32'h0000_1000;
            end
            default: begin // REGIME_ADVERSARIAL
                step_size_q16_16   = 32'h0001_0000;
                base_spread_q16_16 = 32'h0000_8000;
            end
        endcase
    end

    logic [7:0] active_count_eff;
    assign active_count_eff = (active_sym_count == 8'd0) ? 8'd1 :
                              (active_sym_count > NUM_SYM_U8) ? NUM_SYM_U8 :
                              active_sym_count;

    // Per-symbol state (before combinational quote step that reads mid_price[sym_ptr])
    price_t mid_price [NUM_SYM];
    price_t spread    [NUM_SYM];
    logic   [15:0] seq_num [NUM_SYM];

    localparam int SYM_PTR_W = (NUM_SYM > 1) ? $clog2(NUM_SYM) : 1;
    logic [SYM_PTR_W-1:0] sym_ptr;
    logic [31:0]          quote_ctr;

    logic tick_raw;
    logic do_quote;
    // quote_interval==0: quote opportunity every enabled cycle (fastest path).
    assign tick_raw = enable && (
        (quote_interval == 32'd0) ? 1'b1 : (quote_ctr == (quote_interval - 1))
    );
    // Producer only fires when sink is ready (pulse valid, not held-valid AXI-style).
    assign do_quote = tick_raw && quote_ready;

    logic signed [31:0] n_global;
    logic signed [31:0] n_sector [NUM_SECTORS];
    logic signed [31:0] n_company [NUM_SYM];
    logic signed [31:0] n_step_out [NUM_SYM];

    market_noise_gen #(
        .NUM_SYM(NUM_SYM),
        .NUM_SECTORS(NUM_SECTORS)
    ) u_market_noise_gen (
        .clk                  (clk),
        .rst_n                (rst_n),
        .enable               (enable),
        .lfsr_load            (lfsr_load),
        .tick                 (do_quote),
        .base_seed            (lfsr_seed),
        .active_sym_count     (active_count_eff),
        .sector_id            (sector_id),
        .global_noise_q16_16  (n_global),
        .sector_noise_q16_16  (n_sector),
        .company_noise_q16_16 (n_company),
        .step_out_q16_16      (n_step_out)
    );

    logic [FRAME_W-1:0] quote_frame_hold;

    // Combinational quote-step math (when do_quote):
    // step_out_q16_16 and step_size_q16_16 are both Q16.16; product >>> 16 => Q16.16 delta.
    logic signed [63:0] delta_mul_c;
    logic signed [31:0] delta_scaled_c;
    logic signed [31:0] mid_s_c;
    logic signed [31:0] new_mid_s_c;
    logic [31:0]        new_mid_u_c;
    sprice_t            displacement_c;  // init_mid - current mid (signed)
    sprice_t            pullback_c;      // restoring force toward init_mid
    price_t             new_spread_q_c;
    sprice_t            spr_h_s_c;
    sprice_t            bid_s2_c, ask_s2_c;
    price_t             bid_calc_c, ask_calc_c;
    logic [15:0]        bid_size_calc_c, ask_size_calc_c;
    logic [FRAME_W-1:0] quote_frame_next_c;

    always_comb begin
        delta_mul_c    = 64'sd0;
        delta_scaled_c = 32'sd0;
        mid_s_c        = 32'sd0;
        new_mid_s_c    = 32'sd0;
        new_mid_u_c    = 32'd0;
        displacement_c = 32'sd0;
        pullback_c     = 32'sd0;
        new_spread_q_c = 32'd0;
        spr_h_s_c      = 32'sd0;
        bid_s2_c       = 32'sd0;
        ask_s2_c       = 32'sd0;
        bid_calc_c     = 32'd0;
        ask_calc_c     = 32'd0;
        bid_size_calc_c = 16'd0;
        ask_size_calc_c = 16'd0;
        quote_frame_next_c = '0;

        if (do_quote) begin
            // step_size_q16_16 is nonnegative Q16.16; $signed is stylistic width/sign alignment.
            delta_mul_c = $signed(n_step_out[sym_ptr]) * $signed(step_size_q16_16);
            // Arithmetic shift then cast to signed 32b Q16.16 delta (see header for unit contract).
            delta_scaled_c = price_delta_s32_t'(delta_mul_c >>> 16);

            mid_s_c         = $signed(mid_price[sym_ptr]);

            // Ornstein-Uhlenbeck pull-back: restoring force toward initial price
            displacement_c = $signed(init_mid[sym_ptr]) - $signed(mid_price[sym_ptr]);
            pullback_c     = displacement_c >>> PULLBACK_SHIFT;

            new_mid_s_c     = mid_s_c + delta_scaled_c + pullback_c;

            if (new_mid_s_c < MIN_PRICE_Q16_16) new_mid_u_c = price_t'(MIN_PRICE_Q16_16);
            else if (new_mid_s_c > MAX_PRICE_Q16_16) new_mid_u_c = price_t'(MAX_PRICE_Q16_16);
            else new_mid_u_c = price_t'(new_mid_s_c);

            // Static per-regime spread each tick (no sector/company spread evolution).
            new_spread_q_c = base_spread_q16_16;
            if (new_spread_q_c == '0) new_spread_q_c = 32'h0000_0001;

            spr_h_s_c = sprice_t'(new_spread_q_c) >>> 1;
            bid_s2_c  = sprice_t'(new_mid_u_c) - spr_h_s_c;
            ask_s2_c  = sprice_t'(new_mid_u_c) + spr_h_s_c;

            if (bid_s2_c < MIN_PRICE_Q16_16) bid_calc_c = price_t'(MIN_PRICE_Q16_16);
            else if (bid_s2_c > MAX_PRICE_Q16_16) bid_calc_c = price_t'(MAX_PRICE_Q16_16);
            else bid_calc_c = price_t'(bid_s2_c);

            if (ask_s2_c < MIN_PRICE_Q16_16) ask_calc_c = price_t'(MIN_PRICE_Q16_16);
            else if (ask_s2_c > MAX_PRICE_Q16_16) ask_calc_c = price_t'(MAX_PRICE_Q16_16);
            else ask_calc_c = price_t'(ask_s2_c);

            bid_size_calc_c = 16'd1000;
            ask_size_calc_c = 16'd1000;

            quote_frame_next_c[127:124] = MSG_QUOTE;
            quote_frame_next_c[123:116] = symbol_t'(sym_ptr);
            quote_frame_next_c[115:114] = active_regime;
            quote_frame_next_c[113:112] = 2'b00;
            quote_frame_next_c[111:80]  = bid_calc_c;
            quote_frame_next_c[79:48]   = ask_calc_c;
            quote_frame_next_c[47:32]   = bid_size_calc_c;
            quote_frame_next_c[31:16]   = ask_size_calc_c;
            // Convention: frame carries seq for this emission; register increments after commit (first quote = 0).
            quote_frame_next_c[15:0]    = seq_num[sym_ptr];
        end
    end

    // Pre-compute initial bid/ask from init_mid/init_spread (combinational)
    price_t init_bid_c [NUM_SYM];
    price_t init_ask_c [NUM_SYM];

    always_comb begin
        for (int ci = 0; ci < NUM_SYM; ci++) begin
            sprice_t c_mid = sprice_t'(init_mid[ci]);
            sprice_t c_spr = sprice_t'((init_spread[ci] == '0) ? 32'h0000_0001 : init_spread[ci]);
            sprice_t c_hsp = c_spr >>> 1;
            sprice_t c_bid = c_mid - c_hsp;
            sprice_t c_ask = c_mid + c_hsp;

            if (c_bid < MIN_PRICE_Q16_16)      init_bid_c[ci] = price_t'(MIN_PRICE_Q16_16);
            else if (c_bid > MAX_PRICE_Q16_16) init_bid_c[ci] = price_t'(MAX_PRICE_Q16_16);
            else                               init_bid_c[ci] = price_t'(c_bid);

            if (c_ask < MIN_PRICE_Q16_16)      init_ask_c[ci] = price_t'(MIN_PRICE_Q16_16);
            else if (c_ask > MAX_PRICE_Q16_16) init_ask_c[ci] = price_t'(MAX_PRICE_Q16_16);
            else                               init_ask_c[ci] = price_t'(c_ask);
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            sym_ptr          <= '0;
            quote_ctr        <= 32'd0;
            quote_valid      <= 1'b0;
            quote_frame_hold <= '0;
            quotes_generated <= '0;
            for (int ri = 0; ri < NUM_SYM; ri++) begin
                mid_price[ri] <= '0;
                spread[ri]    <= 32'h0000_0001;
                seq_num[ri]   <= 16'd0;
                best_bid[ri]  <= '0;
                best_ask[ri]  <= '0;
            end
        end else if (counter_clr) begin
            quotes_generated <= '0;
        end else if (lfsr_load) begin
            sym_ptr          <= '0;
            quote_ctr        <= 32'd0;
            quote_valid      <= 1'b0;
            quote_frame_hold <= '0;
            quotes_generated <= '0;
            for (int li = 0; li < NUM_SYM; li++) begin
                mid_price[li] <= init_mid[li];
                spread[li]    <= (init_spread[li] == '0) ? 32'h0000_0001 : init_spread[li];
                seq_num[li]   <= 16'd0;
                best_bid[li]  <= init_bid_c[li];
                best_ask[li]  <= init_ask_c[li];
            end
        end else begin
            // Default: pulse semantics — deassert unless this cycle commits a quote.
            quote_valid <= 1'b0;

            if (!enable) begin
                quote_ctr <= 32'd0;
            end else begin
                if (tick_raw) begin
                    if (!quote_ready) quote_ctr <= quote_ctr;
                    else              quote_ctr <= 32'd0;
                end else begin
                    quote_ctr <= quote_ctr + 32'd1;
                end

                if (do_quote) begin
                    mid_price[sym_ptr] <= price_t'(new_mid_u_c);
                    spread[sym_ptr]    <= new_spread_q_c;
                    best_bid[sym_ptr]  <= bid_calc_c;
                    best_ask[sym_ptr]  <= ask_calc_c;

                    quote_frame_hold <= quote_frame_next_c;
                    quote_valid      <= 1'b1;
                    quotes_generated <= quotes_generated + 1'b1;

                    seq_num[sym_ptr] <= seq_num[sym_ptr] + 16'd1;
                    if (sym_ptr == SYM_PTR_W'(active_count_eff - 8'd1)) sym_ptr <= '0;
                    else sym_ptr <= sym_ptr + 1'b1;
                end
            end
        end
    end

    assign quote_frame = quote_frame_hold;

endmodule
