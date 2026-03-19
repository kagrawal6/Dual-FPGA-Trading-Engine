// ============================================================================
// Module: feature_compute
// Computes mid price, spread, EMA, and deviation for each symbol.
// Pipeline stages 3-4 (3 cycles total):
//   Cycle 1: mid = (bid+ask) >> 1, spread = ask - bid
//   Cycle 2-3: EMA MAC via DSP48E2: ema_new = (α*mid + (65536-α)*ema_old) >> 16
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

    // TODO: Implementation
    // Cycle 1: mid = (bid + ask) >> 1; spread = ask - bid;
    // Cycle 2: product_alpha = ema_alpha * mid; product_beta = (16'hFFFF - ema_alpha + 1) * ema_old;
    // Cycle 3: ema_new = (product_alpha + product_beta) >> 16; deviation = mid - ema_new;
    // Pipeline registers for bid/ask/symbol pass-through (3-stage shift register).
    // Per-symbol EMA state: ema_state[NUM_SYM] array.

endmodule
