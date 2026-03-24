// ============================================================================
// Module: exchange_plus
// Upgraded exchange block for future growth, while keeping deterministic,
// demo-friendly behavior.
//
// Features:
//   - one active decoded order + one-entry input queue
//   - held response under backpressure (no dropped responses)
//   - partial fills (optional)
//   - visible liquidity depletion (optional)
//   - one resting-order slot per symbol (optional)
//
// Still intentionally lightweight:
//   - no multi-level order book
//   - no price-time queue
//   - no multiple participants
//   - one response held at a time until fill_ready
// ============================================================================

`timescale 1ns / 1ps

module exchange_plus
    import hft_pkg::*;
#(
    parameter int NUM_SYM                  = NUM_SYMBOLS,
    parameter bit ENABLE_INPUT_QUEUE       = 1'b1,
    parameter bit ENABLE_PARTIAL_FILL      = 1'b1,
    parameter bit ENABLE_SIZE_DEPLETION    = 1'b1,
    parameter bit ENABLE_RESTING_ORDER     = 1'b1,
    parameter logic [15:0] DEFAULT_LIQ_QTY = 16'd1000
)(
    input  logic                 clk,
    input  logic                 rst_n,
    input  logic                 enable,

    // Current market prices (from market_sim)
    input  price_t               best_bid [NUM_SYM],
    input  price_t               best_ask [NUM_SYM],

    // Visible liquidity per symbol
    input  logic [15:0]          best_bid_qty [NUM_SYM],
    input  logic [15:0]          best_ask_qty [NUM_SYM],

    // Pulse meaning quote state refreshed externally
    input  logic                 market_refresh,

    // Order input
    input  logic [FRAME_W-1:0]   order_frame,
    input  logic                 order_valid,

    // Fill / reject output
    output logic [FRAME_W-1:0]   fill_frame,
    output logic                 fill_valid,
    input  logic                 fill_ready,

    // Status counters
    output logic [COUNTER_W-1:0] orders_rcvd,
    output logic [COUNTER_W-1:0] fills_sent,
    output logic [COUNTER_W-1:0] partials_sent,
    output logic [COUNTER_W-1:0] rejects_sent,
    output logic [COUNTER_W-1:0] resting_accepted
);

    localparam logic SIDE_BUY  = 1'b0;
    localparam logic SIDE_SELL = 1'b1;
    localparam int   SYM_IDX_W = (NUM_SYM > 1) ? $clog2(NUM_SYM) : 1;

    // FILL status field [114:112]
    localparam logic [2:0] STATUS_FILLED           = 3'b000;
    localparam logic [2:0] STATUS_REJECTED         = 3'b001;
    localparam logic [2:0] STATUS_PARTIAL          = 3'b010;
    localparam logic [2:0] STATUS_RESTING_ACCEPTED = 3'b011;

    // ------------------------------------------------------------------------
    // Available visible liquidity
    // ------------------------------------------------------------------------
    logic [15:0] avail_bid_qty [NUM_SYM];
    logic [15:0] avail_ask_qty [NUM_SYM];

    // ------------------------------------------------------------------------
    // One resting order slot per symbol
    // ------------------------------------------------------------------------
    logic        rest_valid       [NUM_SYM];
    logic        rest_side        [NUM_SYM];
    logic [31:0] rest_limit_price [NUM_SYM];
    logic [15:0] rest_qty         [NUM_SYM];
    logic [15:0] rest_order_id    [NUM_SYM];
    logic [15:0] rest_timestamp   [NUM_SYM];

    // ------------------------------------------------------------------------
    // Stage 1: active decoded order
    // ------------------------------------------------------------------------
    logic        p1_valid;
    logic        p1_sym_in_range;
    logic [7:0]  p1_symbol;
    logic        p1_side;
    logic [31:0] p1_limit_price;
    logic [15:0] p1_qty;
    logic [15:0] p1_order_id;
    logic [15:0] p1_timestamp;
    logic [31:0] p1_cur_bid, p1_cur_ask;
    logic [15:0] p1_cur_bid_qty, p1_cur_ask_qty;

    // ------------------------------------------------------------------------
    // Optional one-entry input queue
    // ------------------------------------------------------------------------
    logic        q_valid;
    logic [7:0]  q_symbol;
    logic        q_side;
    logic [31:0] q_limit_price;
    logic [15:0] q_qty;
    logic [15:0] q_order_id;
    logic [15:0] q_timestamp;

    // ------------------------------------------------------------------------
    // Held output response
    // ------------------------------------------------------------------------
    logic [FRAME_W-1:0] resp_frame_hold;
    logic               resp_valid_hold;

    assign fill_frame = resp_frame_hold;
    assign fill_valid = resp_valid_hold;

    // ------------------------------------------------------------------------
    // Active-order combinational decision
    // ------------------------------------------------------------------------
    logic        act_is_marketable;
    logic [2:0]  act_status;
    logic [31:0] act_fill_price;
    logic [15:0] act_fill_qty;
    logic [15:0] act_remain_qty;

    always_comb begin
        act_is_marketable = 1'b0;
        act_status        = STATUS_REJECTED;
        act_fill_price    = 32'h0;
        act_fill_qty      = 16'h0;
        act_remain_qty    = p1_qty;

        if (!enable) begin
            act_status = STATUS_REJECTED;
        end
        else if (!p1_sym_in_range) begin
            act_status = STATUS_REJECTED;
        end
        else begin
            if (p1_side == SIDE_BUY) begin
                act_is_marketable = (p1_limit_price >= p1_cur_ask);
                act_fill_price    = p1_cur_ask;

                if (!act_is_marketable) begin
                    if (ENABLE_RESTING_ORDER) act_status = STATUS_RESTING_ACCEPTED;
                    else                      act_status = STATUS_REJECTED;
                end
                else if (!ENABLE_SIZE_DEPLETION) begin
                    act_status     = STATUS_FILLED;
                    act_fill_qty   = p1_qty;
                    act_remain_qty = 16'd0;
                end
                else if (p1_cur_ask_qty == 16'd0) begin
                    act_status = STATUS_REJECTED;
                end
                else if (p1_qty <= p1_cur_ask_qty) begin
                    act_status     = STATUS_FILLED;
                    act_fill_qty   = p1_qty;
                    act_remain_qty = 16'd0;
                end
                else if (ENABLE_PARTIAL_FILL) begin
                    act_status     = STATUS_PARTIAL;
                    act_fill_qty   = p1_cur_ask_qty;
                    act_remain_qty = p1_qty - p1_cur_ask_qty;
                end
                else begin
                    act_status = STATUS_REJECTED;
                end
            end
            else begin
                act_is_marketable = (p1_limit_price <= p1_cur_bid);
                act_fill_price    = p1_cur_bid;

                if (!act_is_marketable) begin
                    if (ENABLE_RESTING_ORDER) act_status = STATUS_RESTING_ACCEPTED;
                    else                      act_status = STATUS_REJECTED;
                end
                else if (!ENABLE_SIZE_DEPLETION) begin
                    act_status     = STATUS_FILLED;
                    act_fill_qty   = p1_qty;
                    act_remain_qty = 16'd0;
                end
                else if (p1_cur_bid_qty == 16'd0) begin
                    act_status = STATUS_REJECTED;
                end
                else if (p1_qty <= p1_cur_bid_qty) begin
                    act_status     = STATUS_FILLED;
                    act_fill_qty   = p1_qty;
                    act_remain_qty = 16'd0;
                end
                else if (ENABLE_PARTIAL_FILL) begin
                    act_status     = STATUS_PARTIAL;
                    act_fill_qty   = p1_cur_bid_qty;
                    act_remain_qty = p1_qty - p1_cur_bid_qty;
                end
                else begin
                    act_status = STATUS_REJECTED;
                end
            end
        end
    end

    // ------------------------------------------------------------------------
    // Resting-order match scan (one hit max)
    // ------------------------------------------------------------------------
    logic                     rest_hit_valid;
    logic [SYM_IDX_W-1:0]     rest_hit_sym;
    logic [2:0]               rest_hit_status;
    logic [31:0]              rest_hit_price;
    logic [15:0]              rest_hit_qty;
    logic                     rest_hit_is_fill;

    integer rs;
    always_comb begin
        rest_hit_valid   = 1'b0;
        rest_hit_sym     = '0;
        rest_hit_status  = STATUS_REJECTED;
        rest_hit_price   = 32'h0;
        rest_hit_qty     = 16'h0;
        rest_hit_is_fill = 1'b0;

        for (rs = 0; rs < NUM_SYM; rs++) begin
            if (!rest_hit_valid && rest_valid[rs]) begin
                if (rest_side[rs] == SIDE_BUY) begin
                    if (rest_limit_price[rs] >= best_ask[rs]) begin
                        rest_hit_valid = 1'b1;
                        rest_hit_sym   = SYM_IDX_W'(rs);
                        rest_hit_price = best_ask[rs];

                        if (!ENABLE_SIZE_DEPLETION) begin
                            rest_hit_status  = STATUS_FILLED;
                            rest_hit_qty     = rest_qty[rs];
                            rest_hit_is_fill = 1'b1;
                        end
                        else if (best_ask_qty[rs] == 16'd0) begin
                            rest_hit_status  = STATUS_REJECTED;
                            rest_hit_qty     = 16'd0;
                            rest_hit_is_fill = 1'b0;
                        end
                        else if (rest_qty[rs] <= best_ask_qty[rs]) begin
                            rest_hit_status  = STATUS_FILLED;
                            rest_hit_qty     = rest_qty[rs];
                            rest_hit_is_fill = 1'b1;
                        end
                        else if (ENABLE_PARTIAL_FILL) begin
                            rest_hit_status  = STATUS_PARTIAL;
                            rest_hit_qty     = best_ask_qty[rs];
                            rest_hit_is_fill = 1'b1;
                        end
                        else begin
                            rest_hit_status  = STATUS_REJECTED;
                            rest_hit_qty     = 16'd0;
                            rest_hit_is_fill = 1'b0;
                        end
                    end
                end
                else begin
                    if (rest_limit_price[rs] <= best_bid[rs]) begin
                        rest_hit_valid = 1'b1;
                        rest_hit_sym   = SYM_IDX_W'(rs);
                        rest_hit_price = best_bid[rs];

                        if (!ENABLE_SIZE_DEPLETION) begin
                            rest_hit_status  = STATUS_FILLED;
                            rest_hit_qty     = rest_qty[rs];
                            rest_hit_is_fill = 1'b1;
                        end
                        else if (best_bid_qty[rs] == 16'd0) begin
                            rest_hit_status  = STATUS_REJECTED;
                            rest_hit_qty     = 16'd0;
                            rest_hit_is_fill = 1'b0;
                        end
                        else if (rest_qty[rs] <= best_bid_qty[rs]) begin
                            rest_hit_status  = STATUS_FILLED;
                            rest_hit_qty     = rest_qty[rs];
                            rest_hit_is_fill = 1'b1;
                        end
                        else if (ENABLE_PARTIAL_FILL) begin
                            rest_hit_status  = STATUS_PARTIAL;
                            rest_hit_qty     = best_bid_qty[rs];
                            rest_hit_is_fill = 1'b1;
                        end
                        else begin
                            rest_hit_status  = STATUS_REJECTED;
                            rest_hit_qty     = 16'd0;
                            rest_hit_is_fill = 1'b0;
                        end
                    end
                end
            end
        end
    end

    // ------------------------------------------------------------------------
    // Main sequential logic
    // ------------------------------------------------------------------------
    integer i;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            p1_valid         <= 1'b0;
            p1_sym_in_range  <= 1'b0;
            p1_symbol        <= '0;
            p1_side          <= 1'b0;
            p1_limit_price   <= '0;
            p1_qty           <= '0;
            p1_order_id      <= '0;
            p1_timestamp     <= '0;
            p1_cur_bid       <= '0;
            p1_cur_ask       <= '0;
            p1_cur_bid_qty   <= '0;
            p1_cur_ask_qty   <= '0;

            q_valid          <= 1'b0;
            q_symbol         <= '0;
            q_side           <= 1'b0;
            q_limit_price    <= '0;
            q_qty            <= '0;
            q_order_id       <= '0;
            q_timestamp      <= '0;

            resp_frame_hold  <= '0;
            resp_valid_hold  <= 1'b0;

            orders_rcvd      <= '0;
            fills_sent       <= '0;
            partials_sent    <= '0;
            rejects_sent     <= '0;
            resting_accepted <= '0;

            for (i = 0; i < NUM_SYM; i++) begin
                avail_bid_qty[i] <= DEFAULT_LIQ_QTY;
                avail_ask_qty[i] <= DEFAULT_LIQ_QTY;

                rest_valid[i]       <= 1'b0;
                rest_side[i]        <= 1'b0;
                rest_limit_price[i] <= '0;
                rest_qty[i]         <= '0;
                rest_order_id[i]    <= '0;
                rest_timestamp[i]   <= '0;
            end
        end
        else begin
            if (market_refresh) begin
                for (i = 0; i < NUM_SYM; i++) begin
                    avail_bid_qty[i] <= best_bid_qty[i];
                    avail_ask_qty[i] <= best_ask_qty[i];
                end
            end

            if (resp_valid_hold && fill_ready) begin
                resp_valid_hold <= 1'b0;
            end

            // Resting-order execution path
            if (enable && !resp_valid_hold && !p1_valid && rest_hit_valid) begin
                resp_frame_hold <= {
                    MSG_FILL,
                    8'(rest_hit_sym),
                    rest_side[rest_hit_sym],
                    rest_hit_status,
                    (rest_hit_is_fill ? rest_hit_price : 32'h0),
                    (rest_hit_is_fill ? rest_hit_qty   : 16'h0),
                    rest_order_id[rest_hit_sym],
                    rest_timestamp[rest_hit_sym],
                    32'h0
                };
                resp_valid_hold <= 1'b1;

                if (rest_hit_status == STATUS_FILLED) fills_sent <= fills_sent + 1'b1;
                else if (rest_hit_status == STATUS_PARTIAL) partials_sent <= partials_sent + 1'b1;
                else rejects_sent <= rejects_sent + 1'b1;

                if (rest_hit_is_fill) begin
                    if (ENABLE_SIZE_DEPLETION) begin
                        if (rest_side[rest_hit_sym] == SIDE_BUY)
                            avail_ask_qty[rest_hit_sym] <= avail_ask_qty[rest_hit_sym] - rest_hit_qty;
                        else
                            avail_bid_qty[rest_hit_sym] <= avail_bid_qty[rest_hit_sym] - rest_hit_qty;
                    end

                    if (rest_hit_status == STATUS_PARTIAL)
                        rest_qty[rest_hit_sym] <= rest_qty[rest_hit_sym] - rest_hit_qty;
                    else
                        rest_valid[rest_hit_sym] <= 1'b0;
                end
                else begin
                    rest_valid[rest_hit_sym] <= 1'b0;
                end
            end

            // Active order -> held response
            if (enable && p1_valid && !resp_valid_hold) begin
                resp_frame_hold <= {
                    MSG_FILL,
                    p1_symbol,
                    p1_side,
                    act_status,
                    ((act_status == STATUS_FILLED || act_status == STATUS_PARTIAL) ? act_fill_price : 32'h0),
                    ((act_status == STATUS_FILLED || act_status == STATUS_PARTIAL) ? act_fill_qty   : 16'h0),
                    p1_order_id,
                    p1_timestamp,
                    32'h0
                };
                resp_valid_hold <= 1'b1;
                p1_valid        <= 1'b0;

                if (act_status == STATUS_FILLED) begin
                    fills_sent <= fills_sent + 1'b1;
                    if (ENABLE_SIZE_DEPLETION && p1_sym_in_range) begin
                        if (p1_side == SIDE_BUY)
                            avail_ask_qty[SYM_IDX_W'(p1_symbol)] <= avail_ask_qty[SYM_IDX_W'(p1_symbol)] - act_fill_qty;
                        else
                            avail_bid_qty[SYM_IDX_W'(p1_symbol)] <= avail_bid_qty[SYM_IDX_W'(p1_symbol)] - act_fill_qty;
                    end
                end
                else if (act_status == STATUS_PARTIAL) begin
                    partials_sent <= partials_sent + 1'b1;
                    if (ENABLE_SIZE_DEPLETION && p1_sym_in_range) begin
                        if (p1_side == SIDE_BUY) avail_ask_qty[SYM_IDX_W'(p1_symbol)] <= 16'd0;
                        else                     avail_bid_qty[SYM_IDX_W'(p1_symbol)] <= 16'd0;
                    end

                    if (ENABLE_RESTING_ORDER && p1_sym_in_range) begin
                        rest_valid[SYM_IDX_W'(p1_symbol)]       <= 1'b1;
                        rest_side[SYM_IDX_W'(p1_symbol)]        <= p1_side;
                        rest_limit_price[SYM_IDX_W'(p1_symbol)] <= p1_limit_price;
                        rest_qty[SYM_IDX_W'(p1_symbol)]         <= act_remain_qty;
                        rest_order_id[SYM_IDX_W'(p1_symbol)]    <= p1_order_id;
                        rest_timestamp[SYM_IDX_W'(p1_symbol)]   <= p1_timestamp;
                    end
                end
                else if (act_status == STATUS_RESTING_ACCEPTED) begin
                    resting_accepted <= resting_accepted + 1'b1;

                    if (ENABLE_RESTING_ORDER && p1_sym_in_range) begin
                        rest_valid[SYM_IDX_W'(p1_symbol)]       <= 1'b1;
                        rest_side[SYM_IDX_W'(p1_symbol)]        <= p1_side;
                        rest_limit_price[SYM_IDX_W'(p1_symbol)] <= p1_limit_price;
                        rest_qty[SYM_IDX_W'(p1_symbol)]         <= p1_qty;
                        rest_order_id[SYM_IDX_W'(p1_symbol)]    <= p1_order_id;
                        rest_timestamp[SYM_IDX_W'(p1_symbol)]   <= p1_timestamp;
                    end
                end
                else begin
                    rejects_sent <= rejects_sent + 1'b1;
                end
            end

            // Move queued order into stage 1
            if (enable && !p1_valid && !resp_valid_hold && q_valid) begin
                p1_symbol       <= q_symbol;
                p1_side         <= q_side;
                p1_limit_price  <= q_limit_price;
                p1_qty          <= q_qty;
                p1_order_id     <= q_order_id;
                p1_timestamp    <= q_timestamp;
                p1_sym_in_range <= (q_symbol < NUM_SYM[7:0]);

                if (q_symbol < NUM_SYM[7:0]) begin
                    p1_cur_bid     <= best_bid[SYM_IDX_W'(q_symbol)];
                    p1_cur_ask     <= best_ask[SYM_IDX_W'(q_symbol)];
                    p1_cur_bid_qty <= avail_bid_qty[SYM_IDX_W'(q_symbol)];
                    p1_cur_ask_qty <= avail_ask_qty[SYM_IDX_W'(q_symbol)];
                end
                else begin
                    p1_cur_bid     <= 32'h0;
                    p1_cur_ask     <= 32'h0;
                    p1_cur_bid_qty <= 16'h0;
                    p1_cur_ask_qty <= 16'h0;
                end

                p1_valid <= 1'b1;
                q_valid  <= 1'b0;
            end

            // Capture new order
            if (enable && order_valid && (order_frame[127:124] == MSG_ORDER)) begin
                if (!p1_valid && !resp_valid_hold) begin
                    p1_symbol       <= order_frame[123:116];
                    p1_side         <= order_frame[115];
                    p1_limit_price  <= order_frame[111:80];
                    p1_qty          <= order_frame[79:64];
                    p1_order_id     <= order_frame[63:48];
                    p1_timestamp    <= order_frame[47:32];
                    p1_sym_in_range <= (order_frame[123:116] < NUM_SYM[7:0]);

                    if (order_frame[123:116] < NUM_SYM[7:0]) begin
                        p1_cur_bid     <= best_bid[SYM_IDX_W'(order_frame[123:116])];
                        p1_cur_ask     <= best_ask[SYM_IDX_W'(order_frame[123:116])];
                        p1_cur_bid_qty <= avail_bid_qty[SYM_IDX_W'(order_frame[123:116])];
                        p1_cur_ask_qty <= avail_ask_qty[SYM_IDX_W'(order_frame[123:116])];
                    end
                    else begin
                        p1_cur_bid     <= 32'h0;
                        p1_cur_ask     <= 32'h0;
                        p1_cur_bid_qty <= 16'h0;
                        p1_cur_ask_qty <= 16'h0;
                    end

                    p1_valid    <= 1'b1;
                    orders_rcvd <= orders_rcvd + 1'b1;
                end
                else if (ENABLE_INPUT_QUEUE && !q_valid) begin
                    q_symbol      <= order_frame[123:116];
                    q_side        <= order_frame[115];
                    q_limit_price <= order_frame[111:80];
                    q_qty         <= order_frame[79:64];
                    q_order_id    <= order_frame[63:48];
                    q_timestamp   <= order_frame[47:32];
                    q_valid       <= 1'b1;
                    orders_rcvd   <= orders_rcvd + 1'b1;
                end
                // else: intentionally drop if both stage1 and queue are full
            end
        end
    end

endmodule