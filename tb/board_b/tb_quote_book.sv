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

    initial clk = 0;
    always #5 clk = ~clk;

    int err_count = 0;

    task automatic check(input string name, input logic [31:0] got, input logic [31:0] exp);
        if (got !== exp) begin
            $display("FAIL [%0t] %s: got 0x%08h, expected 0x%08h", $time, name, got, exp);
            err_count++;
        end
    endtask

    function automatic logic [FRAME_W-1:0] make_quote(
        input symbol_t sym, input regime_e reg_val,
        input price_t bid, input price_t ask,
        input qty_t bsz, input qty_t asz, input logic [15:0] seq
    );
        return {MSG_QUOTE, sym, reg_val, 2'b00, bid, ask, bsz, asz, seq};
    endfunction

    quote_book dut (.*);

    initial begin
        rst_n = 0; quote_frame = '0; quote_valid = 0;
        #100; rst_n = 1;
        @(posedge clk); #1;

        // ── Test 1: Single quote for symbol 0 ──
        quote_frame = make_quote(8'd0, REGIME_CALM,
            32'h0096_0000, 32'h0096_8000, 16'd100, 16'd150, 16'd1);
        quote_valid = 1;
        @(posedge clk); #1;
        quote_valid = 0;
        @(posedge clk); #1;  // output appears 1 cycle later
        check("T1 book_valid", book_valid, 1);
        check("T1 symbol_id",  symbol_id,  8'd0);
        check("T1 bid_price",  bid_price,  32'h0096_0000);
        check("T1 ask_price",  ask_price,  32'h0096_8000);
        check("T1 bid_size",   bid_size,   16'd100);
        check("T1 ask_size",   ask_size,   16'd150);
        check("T1 regime",     regime,     REGIME_CALM);

        @(posedge clk); #1;
        check("T1b book_valid deasserts", book_valid, 0);

        // ── Test 2: Quote for symbol 1 with different regime ──
        quote_frame = make_quote(8'd1, REGIME_VOLATILE,
            32'h00C8_0000, 32'h00C8_4000, 16'd200, 16'd250, 16'd1);
        quote_valid = 1;
        @(posedge clk); #1;
        quote_valid = 0;
        @(posedge clk); #1;
        check("T2 symbol_id",  symbol_id,  8'd1);
        check("T2 bid_price",  bid_price,  32'h00C8_0000);
        check("T2 ask_price",  ask_price,  32'h00C8_4000);
        check("T2 regime",     regime,     REGIME_VOLATILE);

        // ── Test 3: Update symbol 0 again, verify overwrite ──
        quote_frame = make_quote(8'd0, REGIME_BURST,
            32'h0097_0000, 32'h0097_8000, 16'd300, 16'd350, 16'd2);
        quote_valid = 1;
        @(posedge clk); #1;
        quote_valid = 0;
        @(posedge clk); #1;
        check("T3 bid_price",  bid_price,  32'h0097_0000);
        check("T3 ask_price",  ask_price,  32'h0097_8000);
        check("T3 bid_size",   bid_size,   16'd300);
        check("T3 regime",     regime,     REGIME_BURST);

        // ── Test 4: Out-of-range symbol (>= NUM_SYMBOLS) is ignored ──
        quote_frame = make_quote(8'd255, REGIME_CALM,
            32'hFFFF_FFFF, 32'hFFFF_FFFF, 16'hFFFF, 16'hFFFF, 16'd0);
        quote_valid = 1;
        @(posedge clk); #1;
        quote_valid = 0;
        @(posedge clk); #1;
        check("T4 book_valid (out of range)", book_valid, 0);

        // ── Test 5: Spaced-out quotes for all 4 symbols ──
        for (int s = 0; s < 4; s++) begin
            quote_frame = make_quote(s[7:0], REGIME_ADVERSARIAL,
                32'h0050_0000 + s[31:0] * 32'h0010_0000,
                32'h0050_8000 + s[31:0] * 32'h0010_0000,
                (s[15:0] + 1) * 16'd100,
                (s[15:0] + 1) * 16'd100,
                s[15:0]);
            quote_valid = 1;
            @(posedge clk); #1;
            quote_valid = 0;
            @(posedge clk); #1;
            check($sformatf("T5 sym%0d symbol_id", s), symbol_id, s[7:0]);
            check($sformatf("T5 sym%0d book_valid", s), book_valid, 1);
            @(posedge clk); #1;
        end

        repeat (5) @(posedge clk);

        if (err_count == 0)
            $display("tb_quote_book: PASS");
        else
            $display("tb_quote_book: FAIL (%0d errors)", err_count);
        $finish;
    end

endmodule
