// ============================================================================
// Module: quote_book
// Per-symbol register file storing the latest bid/ask prices and sizes.
// Updated by incoming QUOTE frames (1 cycle latency). Outputs the current
// symbol's data for downstream pipeline processing (feature_compute).
// Pipeline stage 2 in the Board B data plane.
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

    // TODO: Implementation
    // Decode QUOTE frame fields per §4.5.3:
    //   [127:124]=msg_type, [123:116]=symbol_id, [115:114]=regime,
    //   [111:80]=bid_price, [79:48]=ask_price, [47:32]=bid_size, [31:16]=ask_size
    // Store in register array: best_bid[NUM_SYM], best_ask[NUM_SYM], etc.
    // On quote_valid: update registers, output that symbol's data with book_valid=1.

endmodule
