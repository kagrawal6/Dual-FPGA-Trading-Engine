// ============================================================================
// Module: quote_book
// Per-symbol register file storing the latest bid/ask prices and sizes.
// Updated by incoming QUOTE frames (1 cycle latency). Outputs the current
// symbol's data for downstream pipeline processing (feature_compute).
// Pipeline stage 2 in the Board B data plane.
//
// Out-of-range symbols (>= NUM_SYM) are silently ignored.
// ============================================================================

`timescale 1ns / 1ps

module quote_book
    import hft_pkg::*;
#(
    parameter NUM_SYM = NUM_SYMBOLS
)(
    input  logic                clk,
    input  logic                rst_n,

    // QUOTE frame input (from msg_demux)
    input  logic [FRAME_W-1:0] quote_frame,
    input  logic                quote_valid,

    // Output: current symbol data for pipeline (1 cycle after quote_valid)
    output price_t              bid_price,
    output price_t              ask_price,
    output qty_t                bid_size,
    output qty_t                ask_size,
    output symbol_t             symbol_id,
    output regime_e             regime,
    output logic                book_valid
);

    // ── Register file ───────────────────────────────────────────
    price_t  best_bid [NUM_SYM];
    price_t  best_ask [NUM_SYM];
    qty_t    best_bid_sz [NUM_SYM];
    qty_t    best_ask_sz [NUM_SYM];

    // ── Combinational frame decode ──────────────────────────────
    logic [7:0]  frame_symbol;
    logic [1:0]  frame_regime;
    price_t      frame_bid;
    price_t      frame_ask;
    qty_t        frame_bid_sz;
    qty_t        frame_ask_sz;

    assign frame_symbol = quote_frame[123:116];
    assign frame_regime = quote_frame[115:114];
    assign frame_bid    = quote_frame[111:80];
    assign frame_ask    = quote_frame[79:48];
    assign frame_bid_sz = quote_frame[47:32];
    assign frame_ask_sz = quote_frame[31:16];

    // ── Registered update + output ──────────────────────────────
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            book_valid <= 1'b0;
            bid_price  <= '0;
            ask_price  <= '0;
            bid_size   <= '0;
            ask_size   <= '0;
            symbol_id  <= '0;
            regime     <= REGIME_CALM;
            for (int i = 0; i < NUM_SYM; i++) begin
                best_bid[i]    <= '0;
                best_ask[i]    <= '0;
                best_bid_sz[i] <= '0;
                best_ask_sz[i] <= '0;
            end
        end else begin
            book_valid <= 1'b0;

            if (quote_valid && frame_symbol < NUM_SYM[7:0]) begin
                best_bid[frame_symbol]    <= frame_bid;
                best_ask[frame_symbol]    <= frame_ask;
                best_bid_sz[frame_symbol] <= frame_bid_sz;
                best_ask_sz[frame_symbol] <= frame_ask_sz;

                bid_price  <= frame_bid;
                ask_price  <= frame_ask;
                bid_size   <= frame_bid_sz;
                ask_size   <= frame_ask_sz;
                symbol_id  <= frame_symbol;
                regime     <= regime_e'(frame_regime);
                book_valid <= 1'b1;
            end
        end
    end

endmodule
