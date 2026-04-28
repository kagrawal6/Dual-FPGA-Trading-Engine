// ============================================================================
// Module: position_tracker_nn
// Identical to position_tracker with two additional output ports:
//   entry_mid     [NUM_SYM] — mid price when position was opened, Q16.16
//   holding_time  [NUM_SYM] — quotes received since position opened (saturates at 255)
// These are needed by nn_inference for features 8 and 9.
// All other logic is unchanged.
// ============================================================================

`timescale 1ns / 1ps

module position_tracker_nn
    import hft_pkg::*;
#(
    parameter NUM_SYM = NUM_SYMBOLS
)(
    input  logic        clk,
    input  logic        rst_n,
    input  logic        clear,

    input  logic [FRAME_W-1:0] fill_frame,
    input  logic                fill_valid,

    // ── NEW: current mid per symbol (from feature_compute_nn) ───
    // Used to seed entry_mid when a position opens.
    input  price_t      current_mid [NUM_SYM],

    // ── NEW: feature_valid pulse — increments holding_time ──────
    input  logic        feature_valid_in,
    input  symbol_t     feature_symbol_in,

    output position_t           position [NUM_SYM],
    output cash_t               cash,
    output sprice_t             total_pnl,

    output timestamp_t          ts_echo,
    output logic                fill_processed,

    output symbol_t             fill_symbol_out,
    output logic                fill_side_out,
    output qty_t                fill_qty_out,
    output logic                fill_notify,

    output logic [COUNTER_W-1:0] fills_rcvd,

    // ── NEW outputs for nn_inference ────────────────────────────
    output price_t      entry_mid    [NUM_SYM],  // mid at position open
    output logic [7:0]  holding_time [NUM_SYM]   // quotes since entry (sat 255)
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

    logic [47:0] product;
    assign product = {16'b0, frame_price} * {32'b0, frame_qty};

    assign total_pnl = cash[47:16];

    // ── Registered update ───────────────────────────────────────
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cash           <= '0;
            ts_echo        <= '0;
            fill_processed <= 1'b0;
            fill_notify    <= 1'b0;
            fill_symbol_out <= '0;
            fill_side_out  <= 1'b0;
            fill_qty_out   <= '0;
            fills_rcvd     <= '0;
            for (int i = 0; i < NUM_SYM; i++) begin
                position[i]     <= '0;
                entry_mid[i]    <= '0;    // NEW
                holding_time[i] <= '0;   // NEW
            end
        end else if (clear) begin
            cash           <= '0;
            fill_processed <= 1'b0;
            fill_notify    <= 1'b0;
            fills_rcvd     <= '0;
            for (int i = 0; i < NUM_SYM; i++) begin
                position[i]     <= '0;
                entry_mid[i]    <= '0;    // NEW
                holding_time[i] <= '0;   // NEW
            end
        end else begin
            fill_processed <= 1'b0;
            fill_notify    <= 1'b0;

            // NEW: increment holding_time for the symbol that just got a quote
            if (feature_valid_in && feature_symbol_in < NUM_SYM[7:0]) begin
                if (position[feature_symbol_in] != '0) begin
                    // saturate at 255
                    if (holding_time[feature_symbol_in] != 8'hFF)
                        holding_time[feature_symbol_in] <= holding_time[feature_symbol_in] + 1'b1;
                end else begin
                    holding_time[feature_symbol_in] <= '0;
                end
            end

            if (fill_valid) begin
                fill_symbol_out <= frame_symbol;
                fill_side_out   <= frame_side;
                fill_notify     <= 1'b1;

                if (is_filled && frame_symbol < NUM_SYM[7:0]) begin
                    automatic position_t prev_pos;
                    automatic position_t new_pos;
                    prev_pos = position[frame_symbol];

                    if (frame_side == 1'b0) begin
                        // BUY
                        new_pos = prev_pos + $signed({{(POSITION_W-QTY_W){1'b0}}, frame_qty});
                        position[frame_symbol] <= new_pos;
                        cash <= cash - $signed(product);
                    end else begin
                        // SELL
                        new_pos = prev_pos - $signed({{(POSITION_W-QTY_W){1'b0}}, frame_qty});
                        position[frame_symbol] <= new_pos;
                        cash <= cash + $signed(product);
                    end

                    // NEW: update entry_mid and holding_time on position change
                    if (prev_pos == '0 && new_pos != '0) begin
                        // position just opened — record entry mid and reset timer
                        entry_mid[frame_symbol]    <= current_mid[frame_symbol];
                        holding_time[frame_symbol] <= '0;
                    end else if (new_pos == '0) begin
                        // position just closed — clear entry tracking
                        entry_mid[frame_symbol]    <= '0;
                        holding_time[frame_symbol] <= '0;
                    end

                    ts_echo        <= frame_ts_echo;
                    fill_processed <= 1'b1;
                    fills_rcvd     <= fills_rcvd + 1'b1;
                    fill_qty_out   <= frame_qty;
                end else begin
                    fill_qty_out <= frame_qty;
                end
            end
        end
    end

endmodule