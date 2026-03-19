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

    // TODO: Implementation
    // Instantiates lfsr32. Round-robin symbol counter.
    // Price evolution: signed_step = lfsr[4:0] - 16, scaled by regime step_size.
    // mid_price[sym] += price_delta, clamped to [MIN_PRICE, MAX_PRICE].
    // bid = mid - (spread >> 1), ask = mid + (spread >> 1).
    // Pack QUOTE frame per §4.5.3 format.

endmodule
