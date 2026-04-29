// ============================================================================
// Testbench: tb_strategy_engine
// Tests mean-reversion strategy: deviation vs threshold comparison, BUY/SELL
// signal generation, all 9 golden vectors from strategy_vectors.json,
// boundary conditions at exactly ±threshold, back-to-back feature_valid,
// and different threshold/qty configurations.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_strategy_engine;

    logic        clk;
    logic        rst_n;
    sprice_t     deviation;
    price_t      bid_price;
    price_t      ask_price;
    symbol_t     symbol_id;
    logic        feature_valid;
    price_t      threshold;
    qty_t        base_qty;
    logic        signal_valid;
    logic        signal_side;
    price_t      signal_price;
    qty_t        signal_qty;
    symbol_t     signal_symbol;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    strategy_engine dut (
        .clk            (clk),
        .rst_n          (rst_n),
        .deviation      (deviation),
        .bid_price      (bid_price),
        .ask_price      (ask_price),
        .symbol_id      (symbol_id),
        .feature_valid  (feature_valid),
        .threshold      (threshold),
        .base_qty       (base_qty),
        .signal_valid   (signal_valid),
        .signal_side    (signal_side),
        .signal_price   (signal_price),
        .signal_qty     (signal_qty),
        .signal_symbol  (signal_symbol)
    );

    integer pass_count = 0;
    integer fail_count = 0;

    task automatic check(input string name, input logic condition);
        if (condition) begin
            pass_count++;
        end else begin
            fail_count++;
            $display("[FAIL] %0s at time %0t", name, $time);
        end
    endtask

    task automatic check32(input string name, input logic [31:0] actual, input logic [31:0] expected);
        if (actual == expected) begin
            pass_count++;
        end else begin
            fail_count++;
            $display("[FAIL] %0s: got 0x%08X, expected 0x%08X at time %0t",
                     name, actual, expected, $time);
        end
    endtask

    task automatic send_and_wait(
        input sprice_t dev,
        input price_t  bid,
        input price_t  ask,
        input symbol_t sym
    );
        deviation     = dev;
        bid_price     = bid;
        ask_price     = ask;
        symbol_id     = sym;
        feature_valid = 1'b1;
        @(posedge clk); #1;
        feature_valid = 1'b0;
        @(posedge clk); #1;
    endtask

    // Golden model vectors from strategy_vectors.json
    // All use bid=0x00B40000, ask=0x00B41999, threshold=0x00008000, qty=100
    localparam logic [31:0] GM_DEV [0:8] = '{
        32'h00000000,  // no trade
        32'h00004CCC,  // small pos → no trade
        32'h0000828F,  // above threshold → SELL
        32'h00010000,  // large pos → SELL
        32'hFFFFB334,  // small neg → no trade
        32'hFFFF7D71,  // below -threshold → BUY
        32'hFFFE0000,  // large neg → BUY
        32'h00008000,  // exactly +threshold → NO trade
        32'hFFFF8000   // exactly -threshold → NO trade
    };
    localparam logic GM_VALID [0:8] = '{
        1'b0, 1'b0, 1'b1, 1'b1, 1'b0, 1'b1, 1'b1, 1'b0, 1'b0
    };
    localparam logic GM_SIDE [0:8] = '{
        1'b0, 1'b0, 1'b1, 1'b1, 1'b0, 1'b0, 1'b0, 1'b0, 1'b0
    };
    localparam logic [31:0] GM_PRICE [0:8] = '{
        32'h00000000, 32'h00000000,
        32'h00B40000, 32'h00B40000,   // SELL at bid
        32'h00000000,
        32'h00B41999, 32'h00B41999,   // BUY at ask
        32'h00000000, 32'h00000000
    };

    initial begin
        deviation     = '0;
        bid_price     = '0;
        ask_price     = '0;
        symbol_id     = '0;
        feature_valid = 1'b0;
        threshold     = 32'h00008000;
        base_qty      = 16'd100;

        @(posedge rst_n);
        repeat (2) @(posedge clk); #1;

        // ──────────────────────────────────────────────────────
        // TEST 1-9: All 9 golden model vectors
        // ──────────────────────────────────────────────────────
        $display("\n=== Golden model vectors (9 cases) ===");
        for (int i = 0; i < 9; i++) begin
            send_and_wait(GM_DEV[i], 32'h00B40000, 32'h00B41999, 8'(i));
            check($sformatf("GM%0d: signal_valid", i),
                  signal_valid == GM_VALID[i]);
            if (GM_VALID[i]) begin
                check($sformatf("GM%0d: side", i),
                      signal_side == GM_SIDE[i]);
                check32($sformatf("GM%0d: price", i),
                        signal_price, GM_PRICE[i]);
                check($sformatf("GM%0d: qty", i),
                      signal_qty == 16'd100);
                check($sformatf("GM%0d: symbol", i),
                      signal_symbol == 8'(i));
            end
        end

        // ──────────────────────────────────────────────────────
        // TEST 10: One tick above +threshold → SELL
        // ──────────────────────────────────────────────────────
        $display("\n=== T10: One tick above +threshold ===");
        send_and_wait(32'h00008001, 32'h00B40000, 32'h00B41999, 8'd0);
        check("T10: valid SELL",        signal_valid == 1'b1);
        check("T10: side==SELL",        signal_side == 1'b1);
        check32("T10: price==bid",      signal_price, 32'h00B40000);

        // ──────────────────────────────────────────────────────
        // TEST 11: One tick below -threshold → BUY
        // ──────────────────────────────────────────────────────
        $display("\n=== T11: One tick below -threshold ===");
        send_and_wait(32'hFFFF7FFF, 32'h00B40000, 32'h00B41999, 8'd0);
        check("T11: valid BUY",         signal_valid == 1'b1);
        check("T11: side==BUY",         signal_side == 1'b0);
        check32("T11: price==ask",      signal_price, 32'h00B41999);

        // ──────────────────────────────────────────────────────
        // TEST 12: Back-to-back feature_valid pulses
        // ──────────────────────────────────────────────────────
        $display("\n=== T12: Back-to-back feature_valid ===");
        // Two consecutive valid inputs: first should SELL, second should not trade
        deviation     = 32'h00010000;  // big positive → SELL
        bid_price     = 32'h00B40000;
        ask_price     = 32'h00B41999;
        symbol_id     = 8'd0;
        feature_valid = 1'b1;
        @(posedge clk); #1;

        // Immediately next: zero deviation → no trade
        deviation     = 32'h00000000;
        symbol_id     = 8'd1;
        @(posedge clk); #1;
        feature_valid = 1'b0;

        // Check first output: SELL sym=0
        check("T12a: valid SELL",       signal_valid == 1'b1);
        check("T12a: side==SELL",       signal_side == 1'b1);
        check("T12a: sym==0",           signal_symbol == 8'd0);

        @(posedge clk); #1;
        // Check second output: no trade sym=1
        check("T12b: no trade",         signal_valid == 1'b0);

        // ──────────────────────────────────────────────────────
        // TEST 13: Different threshold value
        // ──────────────────────────────────────────────────────
        $display("\n=== T13: Different threshold ===");
        threshold = 32'h00010000;  // $1.00
        base_qty  = 16'd200;

        // deviation = $0.50 (below new threshold) → no trade
        send_and_wait(32'h00008000, 32'h00B40000, 32'h00B41999, 8'd0);
        check("T13a: below new threshold", signal_valid == 1'b0);

        // deviation = $1.01 (above threshold) → SELL
        send_and_wait(32'h00010100, 32'h00B40000, 32'h00B41999, 8'd0);
        check("T13b: above → SELL",     signal_valid == 1'b1);
        check("T13b: qty==200",         signal_qty == 16'd200);

        threshold = 32'h00008000;
        base_qty  = 16'd100;

        // ──────────────────────────────────────────────────────
        // TEST 14: No valid input → no output
        // ──────────────────────────────────────────────────────
        $display("\n=== T14: Idle ===");
        deviation     = 32'h00010000;
        feature_valid = 1'b0;
        @(posedge clk); #1;
        @(posedge clk); #1;
        check("T14: no spurious valid",  signal_valid == 1'b0);

        // ── Summary ───────────────────────────────────────────
        repeat (3) @(posedge clk); #1;
        $display("\n══════════════════════════════════════════");
        $display("  strategy_engine testbench complete");
        $display("  PASSED: %0d", pass_count);
        $display("  FAILED: %0d", fail_count);
        $display("══════════════════════════════════════════\n");

        if (fail_count > 0) $fatal(1, "TESTBENCH FAILED");
        $finish;
    end

endmodule
