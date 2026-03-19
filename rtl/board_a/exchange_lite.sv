// ============================================================================
// Module: exchange_lite
// Simplified exchange matching engine. Receives ORDER frames from Board B,
// compares limit_price against live bid/ask from market_sim, and generates
// FILL frames (FILLED or REJECTED). Echoes order_id and timestamp for
// round-trip latency measurement.
// ============================================================================

`timescale 1ns / 1ps

module exchange_lite
    import hft_pkg::*;
#(
    parameter NUM_SYM = NUM_SYMBOLS
)(
    input  logic                 clk,
    input  logic                 rst_n,
    input  logic                 enable,

    // Current market prices (from market_sim)
    input  price_t               best_bid [NUM_SYM],
    input  price_t               best_ask [NUM_SYM],

    // Order input (from link_rx via Board A internal routing)
    input  logic [FRAME_W-1:0]  order_frame,
    input  logic                 order_valid,

    // Fill output (to tx_arbiter)
    output logic [FRAME_W-1:0]  fill_frame,
    output logic                 fill_valid,
    input  logic                 fill_ready,

    // Status counters
    output logic [COUNTER_W-1:0] orders_rcvd,
    output logic [COUNTER_W-1:0] fills_sent,
    output logic [COUNTER_W-1:0] rejects_sent
);

    // TODO: Implementation
    // Decode ORDER frame: symbol_id, side, limit_price, qty, order_id, timestamp.
    // BUY:  limit_price >= best_ask[symbol] → FILLED at ask; else REJECTED.
    // SELL: limit_price <= best_bid[symbol] → FILLED at bid; else REJECTED.
    // Pack FILL frame per §4.5.3, echo order_id and timestamp as ts_echo.

endmodule
