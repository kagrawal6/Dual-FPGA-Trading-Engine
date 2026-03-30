// ============================================================================
// Module: order_manager
// Builds 128-bit ORDER frames from approved trade signals. Assigns a
// monotonically incrementing order_id (16-bit wrapping counter) and captures
// the current cycle_counter as the timestamp for round-trip latency
// measurement. Pipeline stage 7 (1 cycle).
//
// Respects downstream backpressure via order_ready. If order_ready is low
// when an approved signal arrives, the frame is held until ready.
// ============================================================================

`timescale 1ns / 1ps

module order_manager
    import hft_pkg::*;
(
    input  logic        clk,
    input  logic        rst_n,
    input  logic        clear,

    input  logic        approved_valid,
    input  logic        approved_side,
    input  price_t      approved_price,
    input  qty_t        approved_qty,
    input  symbol_t     approved_symbol,

    input  timestamp_t  cycle_counter,

    output logic [FRAME_W-1:0]  order_frame,
    output logic                 order_valid,
    input  logic                 order_ready,

    output logic [COUNTER_W-1:0] orders_sent
);

    // ── Order ID counter ────────────────────────────────────────
    logic [15:0] next_order_id;

    // ── Holding register for backpressure ───────────────────────
    logic        holding;
    logic [FRAME_W-1:0] held_frame;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            order_frame   <= '0;
            order_valid   <= 1'b0;
            orders_sent   <= '0;
            next_order_id <= '0;
            holding       <= 1'b0;
            held_frame    <= '0;
        end else if (clear) begin
            order_valid   <= 1'b0;
            orders_sent   <= '0;
            next_order_id <= '0;
            holding       <= 1'b0;
        end else begin
            // If currently outputting and downstream consumed it
            if (order_valid && order_ready) begin
                order_valid <= 1'b0;
            end

            // If we have a held frame and output is free
            if (holding && (!order_valid || order_ready)) begin
                order_frame <= held_frame;
                order_valid <= 1'b1;
                holding     <= 1'b0;
            end

            // New approved signal
            if (approved_valid) begin
                logic [FRAME_W-1:0] new_frame;
                new_frame = {MSG_ORDER,             // [127:124]
                             approved_symbol,       // [123:116]
                             approved_side,         // [115]
                             3'b000,                // [114:112]
                             approved_price,        // [111:80]
                             approved_qty,          // [79:64]
                             next_order_id,         // [63:48]
                             cycle_counter,         // [47:32]
                             32'h0};                // [31:0]

                if (!holding && (!order_valid || order_ready)) begin
                    order_frame <= new_frame;
                    order_valid <= 1'b1;
                    next_order_id <= next_order_id + 1'b1;
                    orders_sent   <= orders_sent + 1'b1;
                end else if (!holding) begin
                    held_frame <= new_frame;
                    holding    <= 1'b1;
                    next_order_id <= next_order_id + 1'b1;
                    orders_sent   <= orders_sent + 1'b1;
                end else if (!order_valid || order_ready) begin
                    // holding=1 but output is freeing up this cycle (block 2
                    // releases held→output), so the holding slot is available
                    // for the new order.
                    held_frame <= new_frame;
                    holding    <= 1'b1;
                    next_order_id <= next_order_id + 1'b1;
                    orders_sent   <= orders_sent + 1'b1;
                end
                // else: output and holding truly occupied — order dropped
                // (cannot occur at normal quote rates)
            end
        end
    end

endmodule
