// ============================================================================
// Module: order_manager
// Builds 128-bit ORDER frames from approved trade signals. Assigns a
// monotonically incrementing order_id (16-bit wrapping counter) and captures
// the current cycle_counter as the timestamp for round-trip latency
// measurement. Pipeline stage 7 (1 cycle).
//
// ORDER frame format (Appendix C):
//   [127:124] = MSG_ORDER (4'h2)
//   [123:116] = symbol_id
//   [115]     = side (0=BUY, 1=SELL)
//   [114:112] = 3'b0 (reserved)
//   [111:80]  = limit_price (Q16.16)
//   [79:64]   = quantity
//   [63:48]   = order_id
//   [47:32]   = timestamp (cycle_counter)
//   [31:0]    = 32'h0 (reserved)
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

    order_id_t  next_order_id;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            order_frame   <= '0;
            order_valid   <= 1'b0;
            next_order_id <= '0;
            orders_sent   <= '0;
        end else if (clear) begin
            order_valid   <= 1'b0;
            next_order_id <= '0;
            orders_sent   <= '0;
        end else begin
            // Deassert valid once downstream accepts
            if (order_valid && order_ready) begin
                order_valid <= 1'b0;
            end

            if (approved_valid && (!order_valid || order_ready)) begin
                order_frame <= {
                    MSG_ORDER,                  // [127:124] msg_type
                    approved_symbol,            // [123:116] symbol_id
                    approved_side,              // [115]     side
                    3'b000,                     // [114:112] reserved
                    approved_price,             // [111:80]  limit_price
                    approved_qty,               // [79:64]   quantity
                    next_order_id,              // [63:48]   order_id
                    cycle_counter,              // [47:32]   timestamp
                    32'h0                       // [31:0]    reserved
                };
                order_valid   <= 1'b1;
                next_order_id <= next_order_id + 1;
                orders_sent   <= orders_sent + 1;
            end
        end
    end

endmodule
