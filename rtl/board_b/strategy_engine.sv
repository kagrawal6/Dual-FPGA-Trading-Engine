// ============================================================================
// Module: strategy_engine
// Mean-reversion trading strategy (core build). Compares deviation against
// a configurable threshold. If deviation > +threshold: SELL at bid (price
// expected to revert down). If deviation < -threshold: BUY at ask (price
// expected to revert up). Otherwise: no trade. Pipeline stage 5 (1 cycle).
//
// Uses strict inequality: exactly at ±threshold → no trade.
// ============================================================================

`timescale 1ns / 1ps

module strategy_engine
    import hft_pkg::*;
(
    input  logic        clk,
    input  logic        rst_n,

    input  sprice_t     deviation,
    input  price_t      bid_price,
    input  price_t      ask_price,
    input  symbol_t     symbol_id,
    input  logic        feature_valid,

    input  price_t      threshold,
    input  qty_t        base_qty,

    output logic        signal_valid,
    output logic        signal_side,        // 0 = BUY, 1 = SELL
    output price_t      signal_price,
    output qty_t        signal_qty,
    output symbol_t     signal_symbol
);

    // Signed comparison operands
    sprice_t pos_threshold;
    sprice_t neg_threshold;

    assign pos_threshold = $signed({1'b0, threshold[30:0]});
    assign neg_threshold = -pos_threshold;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            signal_valid  <= 1'b0;
            signal_side   <= 1'b0;
            signal_price  <= '0;
            signal_qty    <= '0;
            signal_symbol <= '0;
        end else begin
            signal_valid <= 1'b0;

            if (feature_valid) begin
                if (deviation > pos_threshold) begin
                    // Price above average → SELL at bid
                    signal_valid  <= 1'b1;
                    signal_side   <= 1'b1;  // SELL
                    signal_price  <= bid_price;
                    signal_qty    <= base_qty;
                    signal_symbol <= symbol_id;
                end else if (deviation < neg_threshold) begin
                    // Price below average → BUY at ask
                    signal_valid  <= 1'b1;
                    signal_side   <= 1'b0;  // BUY
                    signal_price  <= ask_price;
                    signal_qty    <= base_qty;
                    signal_symbol <= symbol_id;
                end
            end
        end
    end

endmodule
