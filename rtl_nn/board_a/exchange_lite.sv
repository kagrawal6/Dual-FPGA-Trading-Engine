// ============================================================================
// Module: exchange_lite
// Simplified exchange matching engine. Receives ORDER frames from Board B,
// compares limit_price against live bid/ask from market_sim, and generates
// FILL frames (FILLED or REJECTED). Echoes order_id and timestamp for
// round-trip latency measurement.
//
// counter_clr: synchronous clear from Board A FSM RESET (counters + pipeline);
//              must match instantiation in board_a_top (and TB tie-off).
// ============================================================================

`timescale 1ns / 1ps

module exchange_lite
    import hft_pkg::*;
#(
    parameter NUM_SYM = NUM_SYMBOLS
)(
    input  logic                 clk,
    input  logic                 rst_n,
    input  logic                 enable,
    input  logic                 counter_clr,         // FSM RESET: clear counters + pipeline

    // Current market prices (from market_sim)
    input  price_t               best_bid [NUM_SYM],
    input  price_t               best_ask [NUM_SYM],

    // Order input (from link_rx via Board A internal routing)
    input  logic [FRAME_W-1:0]  order_frame,
    input  logic                 order_valid,

    // Fill output (to tx_arbiter)
    output logic [FRAME_W-1:0]  fill_frame,
    output logic                 fill_valid,
    input  logic                 fill_ready,

    // Status counters
    output logic [COUNTER_W-1:0] orders_rcvd,
    output logic [COUNTER_W-1:0] fills_sent,
    output logic [COUNTER_W-1:0] rejects_sent
);

    // Fill status encoding per spec:
    //   3'b000 = FILLED, 3'b001 = REJECTED
    localparam logic [2:0] STATUS_FILLED   = 3'b000;
    localparam logic [2:0] STATUS_REJECTED = 3'b001;

    // Side encoding from ORDER frame:
    //   1'b0 = BUY, 1'b1 = SELL
    localparam logic SIDE_BUY  = 1'b0;
    localparam int SYM_IDX_W = (NUM_SYM > 1) ? $clog2(NUM_SYM) : 1;

    // Stage-1 decode / lookup registers (single outstanding order)
    logic        p1_valid;
    logic        p1_sym_in_range;
    logic [7:0]  p1_symbol;
    logic        p1_side;
    logic [31:0] p1_limit_price;
    logic [15:0] p1_qty;
    logic [15:0] p1_order_id;
    logic [15:0] p1_timestamp;
    logic [31:0] p1_cur_bid, p1_cur_ask;

    // Stage-2 match results (from stage-1 registers)
    logic        is_filled;
    logic [31:0] fill_price_val;
    logic [15:0] fill_qty_val;

    // ---------------------------------------------------------------------
    // Stage 2: matching
    // BUY  fills at ask if limit >= ask
    // SELL fills at bid if limit <= bid
    // ---------------------------------------------------------------------
    always_comb begin
        if (!p1_sym_in_range) begin
            is_filled = 1'b0;
        end else if (p1_side == SIDE_BUY) begin
            is_filled = (p1_limit_price >= p1_cur_ask);
        end else begin
            is_filled = (p1_limit_price <= p1_cur_bid);
        end

        fill_price_val = is_filled ? ((p1_side == SIDE_BUY) ? p1_cur_ask : p1_cur_bid) : 32'h0;
        fill_qty_val   = is_filled ? p1_qty : 16'h0;
    end

    // ---------------------------------------------------------------------
    // Stage 1 + Stage 2 output register / counters
    // Behavior choices:
    // - One outstanding order/response at a time (minimal demo-safe).
    // - Every valid ORDER frame gets exactly one response frame.
    // - Out-of-range symbol IDs generate REJECT responses (not silent drops).
    // - fill_valid is held until fill_ready; no response is dropped on stall.
    // ---------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            p1_valid      <= 1'b0;
            p1_sym_in_range <= 1'b0;
            p1_symbol     <= '0;
            p1_side       <= 1'b0;
            p1_limit_price <= '0;
            p1_qty        <= '0;
            p1_order_id   <= '0;
            p1_timestamp  <= '0;
            p1_cur_bid    <= '0;
            p1_cur_ask    <= '0;
            orders_rcvd   <= '0;
            fill_frame   <= '0;
            fill_valid   <= 1'b0;
            fills_sent   <= '0;
            rejects_sent <= '0;
        end else if (counter_clr) begin
            p1_valid        <= 1'b0;
            p1_sym_in_range <= 1'b0;
            p1_symbol       <= '0;
            p1_side         <= 1'b0;
            p1_limit_price  <= '0;
            p1_qty          <= '0;
            p1_order_id     <= '0;
            p1_timestamp    <= '0;
            p1_cur_bid      <= '0;
            p1_cur_ask      <= '0;
            orders_rcvd     <= '0;
            fill_frame      <= '0;
            fill_valid      <= 1'b0;
            fills_sent      <= '0;
            rejects_sent    <= '0;
        end else begin
            // Consume response when downstream accepts it.
            if (fill_valid && fill_ready) begin
                fill_valid <= 1'b0;
            end

            // Stage 2: produce one response whenever stage-1 has an order and output slot is empty.
            if (enable && p1_valid && !fill_valid) begin
                fill_frame <= {
                    MSG_FILL,                                      // [127:124]
                    p1_symbol,                                     // [123:116]
                    p1_side,                                       // [115]
                    (is_filled ? STATUS_FILLED : STATUS_REJECTED), // [114:112]
                    fill_price_val,                                // [111:80]
                    fill_qty_val,                                  // [79:64]
                    p1_order_id,                                   // [63:48]
                    p1_timestamp,                                  // [47:32] ts_echo
                    32'h0                                          // [31:0] reserved
                };
                fill_valid <= 1'b1;
                p1_valid   <= 1'b0;

                if (is_filled) fills_sent <= fills_sent + 1'b1;
                else           rejects_sent <= rejects_sent + 1'b1;
            end

            // Stage 1: accept one new ORDER when stage-1 slot is free and no response is queued.
            if (enable && !p1_valid && !fill_valid && order_valid && (order_frame[127:124] == MSG_ORDER)) begin
                p1_symbol       <= order_frame[123:116];
                p1_side         <= order_frame[115];
                p1_limit_price  <= order_frame[111:80];
                p1_qty          <= order_frame[79:64];
                p1_order_id     <= order_frame[63:48];
                p1_timestamp    <= order_frame[47:32];
                p1_sym_in_range <= (order_frame[123:116] < NUM_SYM[7:0]);

                if (order_frame[123:116] < NUM_SYM[7:0]) begin
                    p1_cur_bid <= best_bid[SYM_IDX_W'(order_frame[123:116])];
                    p1_cur_ask <= best_ask[SYM_IDX_W'(order_frame[123:116])];
                end else begin
                    p1_cur_bid <= 32'h0;
                    p1_cur_ask <= 32'h0;
                end

                p1_valid    <= 1'b1;
                orders_rcvd <= orders_rcvd + 1'b1;
            end
        end
    end

endmodule
