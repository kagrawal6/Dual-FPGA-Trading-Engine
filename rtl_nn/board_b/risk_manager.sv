// ============================================================================
// Module: risk_manager
// Three parallel limit checks in 1 cycle (pipeline stage 6):
//   1) Position limit: worst-case position (including in-flight pending)
//      must not exceed max_position
//   2) Order rate: order_count < max_order_rate
//   3) Max loss: total_pnl > -max_loss
// Final gate: approved = pass_1 & pass_2 & pass_3 & order_enable & !risk_halt.
// Latches risk_halt when check 3 fails (cleared only by clear).
//
// In-flight tracking: pending_buy[sym] and pending_sell[sym] track orders
// that have been sent but not yet filled/rejected. on_fill clears them.
// ============================================================================

`timescale 1ns / 1ps

module risk_manager
    import hft_pkg::*;
#(
    parameter NUM_SYM = NUM_SYMBOLS
)(
    input  logic        clk,
    input  logic        rst_n,
    input  logic        clear,

    input  logic        order_enable,

    // Trade signal from strategy_engine
    input  logic        signal_valid,
    input  logic        signal_side,        // 0=BUY, 1=SELL
    input  price_t      signal_price,
    input  qty_t        signal_qty,
    input  symbol_t     signal_symbol,

    // Position feedback from position_tracker
    input  position_t   position [NUM_SYM],
    input  sprice_t     total_pnl,

    // Configuration
    input  logic [POSITION_W-1:0]  max_position,
    input  logic [COUNTER_W-1:0]   max_order_rate,
    input  price_t                 max_loss,

    // Approved output → order_manager
    output logic        approved_valid,
    output logic        approved_side,
    output price_t      approved_price,
    output qty_t        approved_qty,
    output symbol_t     approved_symbol,

    // Fill feedback (from position_tracker) — clears pending
    input  logic        fill_valid,
    input  symbol_t     fill_symbol,
    input  logic        fill_side,
    input  qty_t        fill_qty,

    // Status
    output logic                  risk_halt,
    output logic [COUNTER_W-1:0] risk_rejects
);

    // ── In-flight pending tracking ──────────────────────────────
    logic [QTY_W-1:0] pending_buy  [NUM_SYM];
    logic [QTY_W-1:0] pending_sell [NUM_SYM];

    // ── Order rate counter ──────────────────────────────────────
    logic [COUNTER_W-1:0] order_count;

    // ── Combinational check signals ─────────────────────────────
    logic pass_pos, pass_rate, pass_loss;
    logic approved_comb;

    always_comb begin
        // Default
        pass_pos  = 1'b1;
        pass_rate = 1'b1;
        pass_loss = 1'b1;

        // Check 1: worst-case position after all pending orders fill
        if (signal_valid && signal_symbol < NUM_SYM[7:0]) begin
            automatic logic signed [POSITION_W:0] cur_pos;
            automatic logic signed [POSITION_W:0] worst;
            cur_pos = $signed(position[signal_symbol]);

            if (signal_side == 1'b0) begin
                // BUY: worst case = current + pending_buy + qty
                worst = cur_pos + $signed({1'b0, pending_buy[signal_symbol]})
                                + $signed({1'b0, signal_qty});
            end else begin
                // SELL: worst case = current - pending_sell - qty
                worst = cur_pos - $signed({1'b0, pending_sell[signal_symbol]})
                                - $signed({1'b0, signal_qty});
            end

            // abs(worst) <= max_position
            if (worst < 0)
                pass_pos = (-worst) <= $signed({1'b0, max_position});
            else
                pass_pos = worst <= $signed({1'b0, max_position});
        end

        // Check 2: order rate
        pass_rate = (order_count < max_order_rate);

        // Check 3: max loss (total_pnl > -max_loss)
        pass_loss = (total_pnl > -$signed({1'b0, max_loss[PRICE_W-2:0]}));

        approved_comb = signal_valid & order_enable & !risk_halt
                        & pass_pos & pass_rate & pass_loss;
    end

    // ── Registered output + state update ────────────────────────
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            approved_valid  <= 1'b0;
            approved_side   <= 1'b0;
            approved_price  <= '0;
            approved_qty    <= '0;
            approved_symbol <= '0;
            risk_halt       <= 1'b0;
            risk_rejects    <= '0;
            order_count     <= '0;
            for (int i = 0; i < NUM_SYM; i++) begin
                pending_buy[i]  <= '0;
                pending_sell[i] <= '0;
            end
        end else if (clear) begin
            approved_valid  <= 1'b0;
            risk_halt       <= 1'b0;
            risk_rejects    <= '0;
            order_count     <= '0;
            for (int i = 0; i < NUM_SYM; i++) begin
                pending_buy[i]  <= '0;
                pending_sell[i] <= '0;
            end
        end else begin
            approved_valid <= 1'b0;

            if (signal_valid) begin
                if (!order_enable || risk_halt) begin
                    risk_rejects <= risk_rejects + 1'b1;
                end else if (approved_comb) begin
                    approved_valid  <= 1'b1;
                    approved_side   <= signal_side;
                    approved_price  <= signal_price;
                    approved_qty    <= signal_qty;
                    approved_symbol <= signal_symbol;
                    order_count     <= order_count + 1'b1;

                    if (signal_symbol < NUM_SYM[7:0]) begin
                        // Skip standalone pending increment when the fill
                        // block below handles the merged update.
                        logic fill_merges_buy, fill_merges_sell;
                        fill_merges_buy  = fill_valid && (fill_symbol == signal_symbol)
                                           && (fill_symbol < NUM_SYM[7:0])
                                           && (signal_side == 1'b0) && (fill_side == 1'b0);
                        fill_merges_sell = fill_valid && (fill_symbol == signal_symbol)
                                           && (fill_symbol < NUM_SYM[7:0])
                                           && (signal_side == 1'b1) && (fill_side == 1'b1);

                        if (signal_side == 1'b0 && !fill_merges_buy)
                            pending_buy[signal_symbol] <= pending_buy[signal_symbol] + signal_qty;
                        else if (signal_side == 1'b1 && !fill_merges_sell)
                            pending_sell[signal_symbol] <= pending_sell[signal_symbol] + signal_qty;
                    end
                end else begin
                    risk_rejects <= risk_rejects + 1'b1;
                    if (!pass_loss)
                        risk_halt <= 1'b1;
                end
            end

            // Fill feedback — clear pending.
            // Guard: if signal and fill target the same pending entry on the
            // same cycle, merge both deltas to avoid last-NBA-wins data loss.
            if (fill_valid && fill_symbol < NUM_SYM[7:0]) begin
                logic sig_same_buy, sig_same_sell;
                sig_same_buy  = approved_comb && (signal_symbol == fill_symbol)
                                && (signal_side == 1'b0) && (fill_side == 1'b0);
                sig_same_sell = approved_comb && (signal_symbol == fill_symbol)
                                && (signal_side == 1'b1) && (fill_side == 1'b1);

                if (fill_side == 1'b0) begin
                    if (sig_same_buy) begin
                        // Merge: +signal_qty from approval, -fill_qty from fill
                        if (pending_buy[fill_symbol] + signal_qty >= fill_qty)
                            pending_buy[fill_symbol] <= pending_buy[fill_symbol] + signal_qty - fill_qty;
                        else
                            pending_buy[fill_symbol] <= '0;
                    end else if (pending_buy[fill_symbol] >= fill_qty)
                        pending_buy[fill_symbol] <= pending_buy[fill_symbol] - fill_qty;
                    else
                        pending_buy[fill_symbol] <= '0;
                end else begin
                    if (sig_same_sell) begin
                        if (pending_sell[fill_symbol] + signal_qty >= fill_qty)
                            pending_sell[fill_symbol] <= pending_sell[fill_symbol] + signal_qty - fill_qty;
                        else
                            pending_sell[fill_symbol] <= '0;
                    end else if (pending_sell[fill_symbol] >= fill_qty)
                        pending_sell[fill_symbol] <= pending_sell[fill_symbol] - fill_qty;
                    else
                        pending_sell[fill_symbol] <= '0;
                end
            end
        end
    end

endmodule
