// ============================================================================
// Module: order_manager
// Builds 128-bit ORDER frames from approved trade signals. Assigns a
// monotonically incrementing order_id (16-bit wrapping counter) and captures
// the current cycle_counter as the timestamp for round-trip latency
// measurement. Pipeline stage 7 (1 cycle).
// ============================================================================

`timescale 1ns / 1ps

module order_manager
    import hft_pkg::*;
(
    input  logic        clk,
    input  logic        rst_n,
    input  logic        clear,              // reset order_id counter

    // Approved signal from risk_manager (stage 6 output)
    input  logic        approved_valid,
    input  logic        approved_side,      // 0=BUY, 1=SELL
    input  price_t      approved_price,
    input  qty_t        approved_qty,
    input  symbol_t     approved_symbol,

    // Cycle counter for timestamping (free-running in board_b_top)
    input  timestamp_t  cycle_counter,

    // ORDER frame output (to link_tx)
    output logic [FRAME_W-1:0]  order_frame,
    output logic                 order_valid,
    input  logic                 order_ready,

    // Status
    output logic [COUNTER_W-1:0] orders_sent
);

    // TODO: Implementation
    // Pack ORDER frame per §4.5.3:
    //   [127:124] = MSG_ORDER (4'h2)
    //   [123:116] = approved_symbol
    //   [115]     = approved_side
    //   [114:112] = 3'b0 (reserved)
    //   [111:80]  = approved_price (limit_price)
    //   [79:64]   = approved_qty
    //   [63:48]   = order_id (auto-increment)
    //   [47:32]   = 16'b0 (reserved)
    //   [31:16]   = cycle_counter (timestamp)
    //   [15:0]    = seq_num (auto-increment)

endmodule
