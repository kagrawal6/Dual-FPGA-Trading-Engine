// ============================================================================
// Module: strategy_engine
// Mean-reversion trading strategy (core build). Compares deviation against
// a configurable threshold. If deviation > +threshold: SELL at bid (price
// expected to revert down). If deviation < -threshold: BUY at ask (price
// expected to revert up). Otherwise: no trade. Pipeline stage 5 (1 cycle).
// ============================================================================

`timescale 1ns / 1ps

module strategy_engine
    import hft_pkg::*;
(
    input  logic        clk,
    input  logic        rst_n,

    // Input from feature_compute (stage 4 output)
    input  sprice_t     deviation,          // signed: mid - ema
    input  price_t      bid_price,          // pipeline-delayed bid
    input  price_t      ask_price,          // pipeline-delayed ask
    input  symbol_t     symbol_id,          // pipeline-delayed symbol
    input  logic        feature_valid,

    // Configuration (from AXI registers)
    input  price_t      threshold,          // deviation threshold (Q16.16)
    input  qty_t        base_qty,           // shares per order

    // Trade signal output → risk_manager
    output logic        signal_valid,
    output logic        signal_side,        // 0 = BUY, 1 = SELL
    output price_t      signal_price,       // limit price (ask for BUY, bid for SELL)
    output qty_t        signal_qty,
    output symbol_t     signal_symbol
);

    // TODO: Implementation
    // Registered comparison (1 cycle):
    //   if (deviation > +threshold)  → SELL at bid_price
    //   if (deviation < -threshold)  → BUY  at ask_price
    //   else                         → signal_valid = 0 (no trade)

endmodule
