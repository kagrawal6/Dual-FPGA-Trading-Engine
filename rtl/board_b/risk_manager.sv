// ============================================================================
// Module: risk_manager
// Three parallel limit checks in 1 cycle (pipeline stage 6):
//   1) Position limit: |position[symbol]| < max_position
//   2) Order rate:     orders_this_window < max_order_rate
//   3) Max loss:       total_pnl > -max_loss
// Final gate: approved = pass_1 & pass_2 & pass_3 & order_enable.
// Latches risk_halt when check 3 fails (cleared only by counter_clr).
// ============================================================================

`timescale 1ns / 1ps

module risk_manager
    import hft_pkg::*;
#(
    parameter NUM_SYM = NUM_SYMBOLS
)(
    input  logic        clk,
    input  logic        rst_n,
    input  logic        clear,              // reset halt latch + rate counter

    // FSM control
    input  logic        order_enable,       // high only in TRADING state

    // Trade signal from strategy_engine (stage 5 output)
    input  logic        signal_valid,
    input  logic        signal_side,        // 0=BUY, 1=SELL
    input  price_t      signal_price,
    input  qty_t        signal_qty,
    input  symbol_t     signal_symbol,

    // Position feedback (from position_tracker, combinational read)
    input  position_t   position [NUM_SYM],
    input  sprice_t     total_pnl,          // cash[47:16] — integer dollar PnL

    // Configuration (from AXI registers)
    input  logic [POSITION_W-1:0]  max_position,
    input  logic [COUNTER_W-1:0]   max_order_rate,
    input  price_t                 max_loss,        // Q16.16 positive threshold

    // Approved output → order_manager
    output logic        approved_valid,
    output logic        approved_side,
    output price_t      approved_price,
    output qty_t        approved_qty,
    output symbol_t     approved_symbol,

    // Status
    output logic                  risk_halt,
    output logic [COUNTER_W-1:0] risk_rejects
);

    // TODO: Implementation
    // Parallel checks (combinational):
    //   pass_pos  = (position[signal_symbol] >= 0)
    //              ? (position[signal_symbol] + signal_qty <= max_position)
    //              : (-position[signal_symbol] + signal_qty <= max_position);
    //   pass_rate = (order_count < max_order_rate);
    //   pass_loss = (total_pnl > -$signed(max_loss));
    //   approved  = signal_valid & pass_pos & pass_rate & pass_loss & order_enable & !risk_halt;
    // Registered output (1 cycle).
    // risk_halt latches on !pass_loss, cleared by clear.
    // Sliding window counter for order rate.

endmodule
