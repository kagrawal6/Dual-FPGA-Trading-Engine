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

    // Trade signal output -> risk_manager
    output logic        signal_valid,
    output logic        signal_side,        // 0 = BUY, 1 = SELL
    output price_t      signal_price,       // limit price (ask for BUY, bid for SELL)
    output qty_t        signal_qty,
    output symbol_t     signal_symbol
);

    sprice_t pos_threshold;
    sprice_t neg_threshold;

    assign pos_threshold =  $signed({1'b0, threshold});
    assign neg_threshold = -$signed({1'b0, threshold});

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
                    // Price above average -> SELL at bid (expect reversion down)
                    signal_valid  <= 1'b1;
                    signal_side   <= 1'b1;  // SELL
                    signal_price  <= bid_price;
                    signal_qty    <= base_qty;
                    signal_symbol <= symbol_id;
                end else if (deviation < neg_threshold) begin
                    // Price below average -> BUY at ask (expect reversion up)
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
