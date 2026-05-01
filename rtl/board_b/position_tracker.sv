// ============================================================================
// Module: position_tracker
// Processes FILL frames from the exchange. Updates per-symbol signed position
// (BUY adds, SELL subtracts) and a 48-bit signed cash accumulator (Q32.16):
// SELL adds price*qty, BUY subtracts price*qty.
//
// Only FILLED frames (status == 3'b000) update position/cash.
// REJECTED frames are silently ignored (but still notify risk for pending clear).
// Also extracts ts_echo for latency measurement.
//
// Per-symbol P&L extension (added):
//   - pnl_cash_per_sym[i]    : 48-bit signed Q32.16 cash flow per symbol.
//                              Buy decrements, sell increments. Used by the
//                              laptop dashboard to compute mark-to-market PnL
//                              as: pnl_cash_per_sym[i] + position[i] * mid[i].
//   - last_fill_price[i]     : 32-bit Q16.16 last execution price per symbol.
//   - trades_per_sym[i]      : 16-bit count of FILLED executions per symbol.
// ============================================================================

`timescale 1ns / 1ps

module position_tracker
    import hft_pkg::*;
#(
    parameter NUM_SYM = NUM_SYMBOLS
)(
    input  logic        clk,
    input  logic        rst_n,
    input  logic        clear,

    input  logic [FRAME_W-1:0] fill_frame,
    input  logic                fill_valid,

    // NN: per-symbol current mid (combinational) — used to seed entry_mid
    // when a new position is opened. Wired from board_b_top from a register
    // that latches fc_mid each time feature_valid pulses.
    input  price_t              current_mid       [NUM_SYM],
    // NN: per-quote pulse + symbol — used to advance the holding-time counter
    // for the symbol that just received a fresh feature. Defaults to 0 in
    // legacy testbenches that do not connect them (then holding_time stays 0).
    input  logic                feature_valid_in,
    input  symbol_t             feature_symbol_in,

    output position_t           position [NUM_SYM],
    output cash_t               cash,
    output sprice_t             total_pnl,

    output timestamp_t          ts_echo,
    output logic                fill_processed,

    // Fill info forwarded to risk_manager for pending clear
    output symbol_t             fill_symbol_out,
    output logic                fill_side_out,
    output qty_t                fill_qty_out,
    output logic                fill_notify,

    output logic [COUNTER_W-1:0] fills_rcvd,

    // Per-symbol P&L accounting (exposed for laptop dashboard via AXI)
    output cash_t               pnl_cash_per_sym [NUM_SYM],
    output price_t              last_fill_price  [NUM_SYM],
    output logic [15:0]         trades_per_sym   [NUM_SYM],

    // NN: per-symbol entry_mid (price at position open, Q16.16) and
    // holding_time (quotes seen since position opened, saturating 8-bit).
    output price_t              entry_mid        [NUM_SYM],
    output logic [7:0]          holding_time     [NUM_SYM]
);

    // ── Combinational frame decode ──────────────────────────────
    logic [7:0]  frame_symbol;
    logic        frame_side;
    logic [2:0]  frame_status;
    price_t      frame_price;
    qty_t        frame_qty;
    logic [15:0] frame_order_id;
    timestamp_t  frame_ts_echo;

    assign frame_symbol   = fill_frame[123:116];
    assign frame_side     = fill_frame[115];
    assign frame_status   = fill_frame[114:112];
    assign frame_price    = fill_frame[111:80];
    assign frame_qty      = fill_frame[79:64];
    assign frame_order_id = fill_frame[63:48];
    assign frame_ts_echo  = fill_frame[47:32];

    logic is_filled;
    assign is_filled = (frame_status == 3'b000);

    // price * qty product (32 × 16 = 48 bits, Q16.16 result)
    logic [47:0] product;
    assign product = {16'b0, frame_price} * {32'b0, frame_qty};

    // ── total_pnl: integer part of cash ─────────────────────────
    assign total_pnl = cash[47:16];

    // ── Registered update ───────────────────────────────────────
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cash           <= '0;
            ts_echo        <= '0;
            fill_processed <= 1'b0;
            fill_notify    <= 1'b0;
            fill_symbol_out<= '0;
            fill_side_out  <= 1'b0;
            fill_qty_out   <= '0;
            fills_rcvd     <= '0;
            for (int i = 0; i < NUM_SYM; i++) begin
                position[i]          <= '0;
                pnl_cash_per_sym[i]  <= '0;
                last_fill_price[i]   <= '0;
                trades_per_sym[i]    <= '0;
                entry_mid[i]         <= '0;
                holding_time[i]      <= '0;
            end
        end else if (clear) begin
            cash           <= '0;
            fill_processed <= 1'b0;
            fill_notify    <= 1'b0;
            fills_rcvd     <= '0;
            for (int i = 0; i < NUM_SYM; i++) begin
                position[i]          <= '0;
                pnl_cash_per_sym[i]  <= '0;
                last_fill_price[i]   <= '0;
                trades_per_sym[i]    <= '0;
                entry_mid[i]         <= '0;
                holding_time[i]      <= '0;
            end
        end else begin
            fill_processed <= 1'b0;
            fill_notify    <= 1'b0;

            // NN: advance holding-time counter on each new feature for the
            // matching symbol. Saturate at 0xFF so the NN's 8-bit feature
            // stays well-defined even on long holds.
            if (feature_valid_in && feature_symbol_in < NUM_SYM[7:0]) begin
                if (position[feature_symbol_in] != '0) begin
                    if (holding_time[feature_symbol_in] != 8'hFF)
                        holding_time[feature_symbol_in] <=
                            holding_time[feature_symbol_in] + 8'd1;
                end else begin
                    holding_time[feature_symbol_in] <= '0;
                end
            end

            if (fill_valid) begin
                // Always forward fill info to risk_manager for pending clear
                fill_symbol_out <= frame_symbol;
                fill_side_out   <= frame_side;
                fill_notify     <= 1'b1;

                if (is_filled && frame_symbol < NUM_SYM[7:0]) begin
                    // Use locals (declared with automatic for ModelSim) so we
                    // can see prev_pos / new_pos to detect position open/close
                    // without re-reading the non-blocking-assigned position[].
                    automatic position_t prev_pos;
                    automatic position_t new_pos;
                    prev_pos = position[frame_symbol];

                    // ── Position + global cash + per-symbol P&L update ──
                    if (frame_side == 1'b0) begin
                        // BUY: position goes up, cash goes down
                        new_pos = prev_pos
                                + $signed({{(POSITION_W-QTY_W){1'b0}}, frame_qty});
                        position[frame_symbol] <= new_pos;
                        cash <= cash - $signed(product);
                        pnl_cash_per_sym[frame_symbol] <=
                            pnl_cash_per_sym[frame_symbol] - $signed(product);
                    end else begin
                        // SELL: position goes down, cash goes up
                        new_pos = prev_pos
                                - $signed({{(POSITION_W-QTY_W){1'b0}}, frame_qty});
                        position[frame_symbol] <= new_pos;
                        cash <= cash + $signed(product);
                        pnl_cash_per_sym[frame_symbol] <=
                            pnl_cash_per_sym[frame_symbol] + $signed(product);
                    end

                    // NN: maintain entry_mid and holding_time around opens/closes.
                    //   - Position just opened (was flat)  → seed entry_mid, reset timer.
                    //   - Position just closed (now flat)  → clear both.
                    //   - Add-to / partial-out / flip kept simple: leave entry_mid at
                    //     original open price (matches reference NN training behavior).
                    if (prev_pos == '0 && new_pos != '0) begin
                        entry_mid[frame_symbol]    <= current_mid[frame_symbol];
                        holding_time[frame_symbol] <= '0;
                    end else if (new_pos == '0) begin
                        entry_mid[frame_symbol]    <= '0;
                        holding_time[frame_symbol] <= '0;
                    end

                    last_fill_price[frame_symbol] <= frame_price;
                    trades_per_sym[frame_symbol]  <= trades_per_sym[frame_symbol] + 16'd1;

                    ts_echo        <= frame_ts_echo;
                    fill_processed <= 1'b1;
                    fills_rcvd     <= fills_rcvd + 1'b1;
                    fill_qty_out   <= frame_qty;
                end else begin
                    // Rejected or out-of-range: still notify risk with base_qty
                    fill_qty_out <= frame_qty;
                end
            end
        end
    end

endmodule
