// ============================================================================
// Module: risk_manager
// Three parallel limit checks in 1 cycle (pipeline stage 6):
//   1) Position limit: |position[symbol] + delta| <= max_position
//   2) Order rate:     orders_this_window < max_order_rate
//   3) Max loss:       total_pnl > -max_loss
// Final gate: approved = pass_1 & pass_2 & pass_3 & order_enable & !risk_halt.
// Latches risk_halt when check 3 fails (cleared only by clear).
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
    input  sprice_t     total_pnl,          // signed Q16.16 PnL

    // Configuration (from AXI registers)
    input  logic [POSITION_W-1:0]  max_position,
    input  logic [COUNTER_W-1:0]   max_order_rate,
    input  price_t                 max_loss,        // Q16.16 positive threshold

    // Approved output -> order_manager
    output logic        approved_valid,
    output logic        approved_side,
    output price_t      approved_price,
    output qty_t        approved_qty,
    output symbol_t     approved_symbol,

    // Status
    output logic                  risk_halt,
    output logic [COUNTER_W-1:0] risk_rejects
);

    // Sliding-window order rate counter
    logic [COUNTER_W-1:0] order_count;
    logic [COUNTER_W-1:0] window_timer;
    localparam WINDOW_CYCLES = 32'd100_000; // 1 ms at 100 MHz

    // Combinational risk checks
    logic pass_pos, pass_rate, pass_loss;
    logic approved_comb;

    position_t cur_pos;
    position_t new_pos;
    position_t abs_new_pos;

    always_comb begin
        cur_pos = (signal_symbol < NUM_SYM[SYMBOL_W-1:0])
                  ? position[signal_symbol] : '0;

        new_pos = signal_side
                  ? (cur_pos - $signed({{(POSITION_W - QTY_W){1'b0}}, signal_qty}))
                  : (cur_pos + $signed({{(POSITION_W - QTY_W){1'b0}}, signal_qty}));

        abs_new_pos = (new_pos < 0) ? -new_pos : new_pos;

        pass_pos  = (abs_new_pos <= $signed(max_position));
        pass_rate = (order_count < max_order_rate);
        pass_loss = (total_pnl > -$signed({1'b0, max_loss}));

        approved_comb = signal_valid & pass_pos & pass_rate & pass_loss
                      & order_enable & !risk_halt;
    end

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
            window_timer    <= '0;
        end else if (clear) begin
            approved_valid  <= 1'b0;
            risk_halt       <= 1'b0;
            risk_rejects    <= '0;
            order_count     <= '0;
            window_timer    <= '0;
        end else begin
            approved_valid <= 1'b0;

            // Sliding window reset
            if (window_timer >= WINDOW_CYCLES) begin
                window_timer <= '0;
                order_count  <= '0;
            end else begin
                window_timer <= window_timer + 1;
            end

            // Loss halt latch
            if (signal_valid && !pass_loss) begin
                risk_halt <= 1'b1;
            end

            if (signal_valid) begin
                if (approved_comb) begin
                    approved_valid  <= 1'b1;
                    approved_side   <= signal_side;
                    approved_price  <= signal_price;
                    approved_qty    <= signal_qty;
                    approved_symbol <= signal_symbol;
                    order_count     <= order_count + 1;
                end else begin
                    risk_rejects <= risk_rejects + 1;
                end
            end
        end
    end

endmodule
