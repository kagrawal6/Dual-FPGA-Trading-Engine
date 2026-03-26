// ============================================================================
// Module: feature_compute
// Computes mid price, spread, EMA, and deviation for each symbol.
// Pipeline stages 3-4 (3 cycles total):
//   Cycle 1: mid = (bid+ask) >> 1, spread = ask - bid
//   Cycle 2-3: EMA MAC via DSP48E2: ema_new = (alpha*mid + (65536-alpha)*ema_old) >> 16
// Maintains per-symbol EMA state. Passes through bid/ask (delayed 3 cycles)
// for use by strategy_engine.
// ============================================================================

`timescale 1ns / 1ps

module feature_compute
    import hft_pkg::*;
#(
    parameter NUM_SYM = NUM_SYMBOLS
)(
    input  logic        clk,
    input  logic        rst_n,
    input  logic        clear,              // reset EMA state to zero

    // Input from quote_book (stage 2 output)
    input  price_t      bid_price,
    input  price_t      ask_price,
    input  symbol_t     symbol_id,
    input  logic        book_valid,

    // Configuration
    input  logic [ALPHA_W-1:0] ema_alpha,   // Q0.16 smoothing factor

    // Feature outputs (available 3 cycles after book_valid)
    output price_t      mid,
    output price_t      spread,
    output price_t      ema,
    output sprice_t     deviation,          // signed: mid - ema

    // Pipeline pass-through (delayed 3 cycles to align with features)
    output price_t      bid_out,
    output price_t      ask_out,
    output symbol_t     symbol_out,
    output logic        feature_valid
);

    // Per-symbol EMA state
    price_t ema_state [NUM_SYM];

    // Pipeline stage 1 registers (cycle 1)
    logic        s1_valid;
    price_t      s1_mid;
    price_t      s1_spread;
    price_t      s1_bid;
    price_t      s1_ask;
    symbol_t     s1_sym;
    price_t      s1_ema_old;

    // Pipeline stage 2 registers (cycle 2) - multiply
    logic        s2_valid;
    logic [47:0] s2_prod_alpha;     // alpha * mid
    logic [47:0] s2_prod_beta;      // (65536 - alpha) * ema_old
    price_t      s2_mid;
    price_t      s2_spread;
    price_t      s2_bid;
    price_t      s2_ask;
    symbol_t     s2_sym;

    // Pipeline stage 3 registers (cycle 3) - accumulate + output
    logic        s3_valid;
    price_t      s3_mid;
    price_t      s3_spread;
    price_t      s3_ema_new;
    sprice_t     s3_deviation;
    price_t      s3_bid;
    price_t      s3_ask;
    symbol_t     s3_sym;

    // Complementary alpha: 65536 - alpha
    logic [16:0] alpha_comp;
    assign alpha_comp = 17'd65536 - {1'b0, ema_alpha};

    integer i;

    // Stage 1: mid & spread computation
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s1_valid   <= 1'b0;
            s1_mid     <= '0;
            s1_spread  <= '0;
            s1_bid     <= '0;
            s1_ask     <= '0;
            s1_sym     <= '0;
            s1_ema_old <= '0;
        end else if (clear) begin
            s1_valid <= 1'b0;
        end else begin
            s1_valid <= book_valid;
            if (book_valid) begin
                s1_mid    <= (bid_price + ask_price) >> 1;
                s1_spread <= ask_price - bid_price;
                s1_bid    <= bid_price;
                s1_ask    <= ask_price;
                s1_sym    <= symbol_id;
                s1_ema_old <= ema_state[symbol_id];
            end
        end
    end

    // Stage 2: multiply (DSP48E2-friendly)
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s2_valid      <= 1'b0;
            s2_prod_alpha <= '0;
            s2_prod_beta  <= '0;
            s2_mid        <= '0;
            s2_spread     <= '0;
            s2_bid        <= '0;
            s2_ask        <= '0;
            s2_sym        <= '0;
        end else if (clear) begin
            s2_valid <= 1'b0;
        end else begin
            s2_valid <= s1_valid;
            if (s1_valid) begin
                s2_prod_alpha <= {16'b0, ema_alpha} * {16'b0, s1_mid};
                s2_prod_beta  <= {15'b0, alpha_comp} * {16'b0, s1_ema_old};
                s2_mid        <= s1_mid;
                s2_spread     <= s1_spread;
                s2_bid        <= s1_bid;
                s2_ask        <= s1_ask;
                s2_sym        <= s1_sym;
            end
        end
    end

    // Stage 3: accumulate, truncate, compute deviation, writeback EMA
    logic [47:0] ema_sum;
    price_t      ema_new;
    assign ema_sum = s2_prod_alpha + s2_prod_beta;
    assign ema_new = ema_sum[47:16];   // >> 16 truncation back to Q16.16

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s3_valid     <= 1'b0;
            s3_mid       <= '0;
            s3_spread    <= '0;
            s3_ema_new   <= '0;
            s3_deviation <= '0;
            s3_bid       <= '0;
            s3_ask       <= '0;
            s3_sym       <= '0;
            for (i = 0; i < NUM_SYM; i++)
                ema_state[i] <= '0;
        end else if (clear) begin
            s3_valid <= 1'b0;
            for (i = 0; i < NUM_SYM; i++)
                ema_state[i] <= '0;
        end else begin
            s3_valid <= s2_valid;
            if (s2_valid) begin
                s3_mid       <= s2_mid;
                s3_spread    <= s2_spread;
                s3_ema_new   <= ema_new;
                s3_deviation <= $signed({1'b0, s2_mid}) - $signed({1'b0, ema_new});
                s3_bid       <= s2_bid;
                s3_ask       <= s2_ask;
                s3_sym       <= s2_sym;
                ema_state[s2_sym] <= ema_new;
            end
        end
    end

    // Output assignments
    assign mid           = s3_mid;
    assign spread        = s3_spread;
    assign ema           = s3_ema_new;
    assign deviation     = s3_deviation;
    assign bid_out       = s3_bid;
    assign ask_out       = s3_ask;
    assign symbol_out    = s3_sym;
    assign feature_valid = s3_valid;

endmodule
