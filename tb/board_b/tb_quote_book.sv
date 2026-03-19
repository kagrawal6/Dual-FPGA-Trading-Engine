// ============================================================================
// Testbench: tb_quote_book
// Tests the quote_book module: QUOTE frame decoding, per-symbol register
// updates, and output timing (1 cycle after quote_valid).
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_quote_book;

    logic                     clk;
    logic                     rst_n;
    logic [FRAME_W-1:0]       quote_frame;
    logic                     quote_valid;
    price_t                   bid_price;
    price_t                   ask_price;
    qty_t                     bid_size;
    qty_t                     ask_size;
    symbol_t                  symbol_id;
    regime_e                  regime;
    logic                     book_valid;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    quote_book dut (
        .clk         (clk),
        .rst_n       (rst_n),
        .quote_frame (quote_frame),
        .quote_valid (quote_valid),
        .bid_price   (bid_price),
        .ask_price   (ask_price),
        .bid_size    (bid_size),
        .ask_size    (ask_size),
        .symbol_id   (symbol_id),
        .regime      (regime),
        .book_valid  (book_valid)
    );

    initial begin
        // TODO: Add test stimulus
        $finish;
    end

endmodule
