// ============================================================================
// Module: feature_compute
// Computes mid price, spread, EMA, and deviation for each symbol.
// Pipeline: 3 cycles total:
//   Cycle 1: mid = (bid+ask) >> 1, spread = ask - bid
//   Cycle 2: EMA multiply — product_a = alpha * mid, product_b = beta * ema_old
//   Cycle 3: EMA accumulate — ema_new = (product_a + product_b) >> 16
//            deviation = mid_delayed - ema_new (signed)
//
// First-sample initialization: on the first quote for a symbol, EMA is
// seeded directly to mid (no multiply needed). deviation = 0.
//
// Passes bid/ask/symbol through a 3-stage shift register to align with
// feature output timing.
// ============================================================================

`timescale 1ns / 1ps

module feature_compute
    import hft_pkg::*;
#(
    parameter NUM_SYM = NUM_SYMBOLS
)(
    input  logic        clk,
    input  logic        rst_n,
    input  logic        clear,

    input  price_t      bid_price,
    input  price_t      ask_price,
    input  symbol_t     symbol_id,
    input  logic        book_valid,

    input  logic [ALPHA_W-1:0] ema_alpha,

    output price_t      mid,
    output price_t      spread,
    output price_t      ema,
    output sprice_t     deviation,

    output price_t      bid_out,
    output price_t      ask_out,
    output symbol_t     symbol_out,
    output logic        feature_valid
);

    // ── Per-symbol EMA state ────────────────────────────────────
    price_t  ema_state [NUM_SYM];
    logic    ema_init  [NUM_SYM];   // has this symbol seen its first quote?

    // ── Pipeline stage 1 registers ──────────────────────────────
    price_t  s1_mid;
    price_t  s1_spread;
    price_t  s1_bid, s1_ask;
    symbol_t s1_sym;
    logic    s1_valid;

    // ── Pipeline stage 2 registers ──────────────────────────────
    logic [47:0] s2_prod_a;      // alpha * mid  (16 × 32 = 48 bits)
    logic [47:0] s2_prod_b;      // beta  * ema_old
    price_t      s2_mid;
    price_t      s2_bid, s2_ask;
    symbol_t     s2_sym;
    logic        s2_valid;
    logic        s2_first;       // first sample for this symbol

    // ── Pipeline stage 3 (output) registers ─────────────────────
    // (declared as outputs)

    // ── beta = 65536 - alpha ────────────────────────────────────
    logic [16:0] beta;
    assign beta = 17'h10000 - {1'b0, ema_alpha};

    // ── Stage 1: mid & spread computation ───────────────────────
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s1_mid    <= '0;
            s1_spread <= '0;
            s1_bid    <= '0;
            s1_ask    <= '0;
            s1_sym    <= '0;
            s1_valid  <= 1'b0;
        end else begin
            s1_valid <= book_valid;
            if (book_valid) begin
                s1_mid    <= (bid_price + ask_price) >> 1;
                s1_spread <= ask_price - bid_price;
                s1_bid    <= bid_price;
                s1_ask    <= ask_price;
                s1_sym    <= symbol_id;
            end
        end
    end

    // ── Stage 2: EMA multiply ───────────────────────────────────
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s2_prod_a <= '0;
            s2_prod_b <= '0;
            s2_mid    <= '0;
            s2_bid    <= '0;
            s2_ask    <= '0;
            s2_sym    <= '0;
            s2_valid  <= 1'b0;
            s2_first  <= 1'b0;
        end else begin
            s2_valid <= s1_valid;
            if (s1_valid) begin
                s2_mid <= s1_mid;
                s2_bid <= s1_bid;
                s2_ask <= s1_ask;
                s2_sym <= s1_sym;

                if (!ema_init[s1_sym]) begin
                    s2_first  <= 1'b1;
                    s2_prod_a <= '0;
                    s2_prod_b <= '0;
                end else begin
                    s2_first  <= 1'b0;
                    s2_prod_a <= {16'b0, ema_alpha} * {16'b0, s1_mid};
                    s2_prod_b <= {15'b0, beta} * {16'b0, ema_state[s1_sym]};
                end
            end
        end
    end

    // ── Spread delay pipeline (stage 1 → stage 3 alignment) ────
    price_t spread_s2;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            spread_s2 <= '0;
        else
            spread_s2 <= s1_spread;
    end

    // ── Stage 3: EMA accumulate + deviation + state writeback ───
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            mid           <= '0;
            spread        <= '0;
            ema           <= '0;
            deviation     <= '0;
            bid_out       <= '0;
            ask_out       <= '0;
            symbol_out    <= '0;
            feature_valid <= 1'b0;
            for (int i = 0; i < NUM_SYM; i++) begin
                ema_state[i] <= '0;
                ema_init[i]  <= 1'b0;
            end
        end else if (clear) begin
            feature_valid <= 1'b0;
            for (int i = 0; i < NUM_SYM; i++) begin
                ema_state[i] <= '0;
                ema_init[i]  <= 1'b0;
            end
        end else begin
            feature_valid <= s2_valid;

            if (s2_valid) begin
                mid        <= s2_mid;
                spread     <= spread_s2;
                bid_out    <= s2_bid;
                ask_out    <= s2_ask;
                symbol_out <= s2_sym;

                if (s2_first) begin
                    ema           <= s2_mid;
                    deviation     <= '0;
                    ema_state[s2_sym] <= s2_mid;
                    ema_init[s2_sym]  <= 1'b1;
                end else begin
                    logic [47:0] sum48;
                    price_t      ema_new;
                    sum48   = s2_prod_a + s2_prod_b;
                    ema_new = sum48[47:16];
                    ema           <= ema_new;
                    deviation     <= $signed({1'b0, s2_mid}) - $signed({1'b0, ema_new});
                    ema_state[s2_sym] <= ema_new;
                end
            end
        end
    end

endmodule
