// ============================================================================
// Testbench: tb_risk_manager
// Tests the risk_manager module: position limit, order rate, max loss checks,
// approved output gating, risk_halt latch, and clear functionality.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_risk_manager;

    logic                     clk;
    logic                     rst_n;
    logic                     clear;
    logic                     order_enable;
    logic                     signal_valid;
    logic                     signal_side;
    price_t                   signal_price;
    qty_t                     signal_qty;
    symbol_t                  signal_symbol;
    position_t                position [NUM_SYMBOLS];
    sprice_t                  total_pnl;
    logic [POSITION_W-1:0]    max_position;
    logic [COUNTER_W-1:0]     max_order_rate;
    price_t                   max_loss;
    logic                     approved_valid;
    logic                     approved_side;
    price_t                   approved_price;
    qty_t                     approved_qty;
    symbol_t                  approved_symbol;
    logic                     risk_halt;
    logic [COUNTER_W-1:0]     risk_rejects;

    initial clk = 0;
    always #5 clk = ~clk;

    int err_count = 0;

    task automatic check(input string name, input logic [31:0] got, input logic [31:0] exp);
        if (got !== exp) begin
            $display("FAIL [%0t] %s: got 0x%08h, expected 0x%08h", $time, name, got, exp);
            err_count++;
        end
    endtask

    task automatic send_signal(input logic side, input price_t price,
                               input qty_t qty, input symbol_t sym);
        signal_valid  = 1;
        signal_side   = side;
        signal_price  = price;
        signal_qty    = qty;
        signal_symbol = sym;
        @(posedge clk); #1;
        signal_valid = 0;
        @(posedge clk); #1;
    endtask

    risk_manager dut (.*);

    initial begin
        rst_n = 0; clear = 0; order_enable = 0;
        signal_valid = 0; signal_side = 0; signal_price = 0;
        signal_qty = 0; signal_symbol = 0;
        for (int i = 0; i < NUM_SYMBOLS; i++) position[i] = 0;
        total_pnl = 0;
        max_position = 500;
        max_order_rate = 1000;
        max_loss = 32'h0064_0000;  // $100.00
        #100; rst_n = 1;
        @(posedge clk); #1;

        // ── Test 1: order_enable=0 -> all rejected ──
        order_enable = 0;
        send_signal(1'b0, 32'h0096_0000, 16'd100, 8'd0);
        check("T1 approved_valid (disabled)", approved_valid, 0);
        check("T1 risk_rejects", risk_rejects, 1);

        // ── Test 2: All checks pass -> approved ──
        order_enable = 1;
        position[0] = 32'sd0;
        total_pnl = 32'sh0001_0000;  // positive PnL
        send_signal(1'b0, 32'h0096_0000, 16'd100, 8'd0);  // BUY 100
        check("T2 approved_valid", approved_valid, 1);
        check("T2 approved_side", approved_side, 0);
        check("T2 approved_price", approved_price, 32'h0096_0000);
        check("T2 approved_qty", approved_qty, 16'd100);
        check("T2 approved_symbol", approved_symbol, 8'd0);

        // ── Test 3: Position limit check - at boundary ──
        position[0] = 32'sd450;
        send_signal(1'b0, 32'h0096_0000, 16'd50, 8'd0);  // BUY 50 -> pos=500 (ok, = limit)
        check("T3 approved_valid (at limit)", approved_valid, 1);

        // ── Test 4: Position limit check - exceeds ──
        position[0] = 32'sd450;
        send_signal(1'b0, 32'h0096_0000, 16'd51, 8'd0);  // BUY 51 -> pos=501 (over limit)
        check("T4 approved_valid (over limit)", approved_valid, 0);

        // ── Test 5: Negative position, SELL increases magnitude ──
        position[1] = -32'sd400;
        send_signal(1'b1, 32'h0096_0000, 16'd101, 8'd1);  // SELL 101 -> pos=-501 (over)
        check("T5 approved_valid (neg over)", approved_valid, 0);

        // ── Test 6: Max loss check -> risk_halt latches ──
        position[0] = 32'sd0;
        total_pnl = -32'sh0064_0001;  // slightly worse than -$100.00
        send_signal(1'b0, 32'h0096_0000, 16'd10, 8'd0);
        check("T6 approved_valid (loss)", approved_valid, 0);
        check("T6 risk_halt", risk_halt, 1);

        // ── Test 7: risk_halt persists even with good PnL ──
        total_pnl = 32'sh0001_0000;  // positive PnL now
        position[0] = 32'sd0;
        send_signal(1'b0, 32'h0096_0000, 16'd10, 8'd0);
        check("T7 risk_halt persists", risk_halt, 1);
        check("T7 approved_valid (halted)", approved_valid, 0);

        // ── Test 8: Clear resets risk_halt ──
        clear = 1;
        @(posedge clk); #1;
        clear = 0;
        @(posedge clk); #1;
        check("T8 risk_halt after clear", risk_halt, 0);
        check("T8 risk_rejects after clear", risk_rejects, 0);

        // ── Test 9: After clear, normal operation resumes ──
        total_pnl = 32'sh0001_0000;
        position[0] = 32'sd0;
        send_signal(1'b0, 32'h0096_0000, 16'd100, 8'd0);
        check("T9 approved_valid (after clear)", approved_valid, 1);

        // ── Test 10: PnL exactly at -max_loss -> rejected (loss check fails) ──
        total_pnl = -32'sh0064_0000;  // exactly -$100.00 = -(max_loss)
        position[0] = 32'sd0;
        send_signal(1'b0, 32'h0096_0000, 16'd10, 8'd0);
        check("T10 approved_valid (exact limit)", approved_valid, 0);

        // ── Test 11: SELL side passes ──
        clear = 1; @(posedge clk); #1; clear = 0; @(posedge clk); #1;
        total_pnl = 32'sh0010_0000;
        position[2] = 32'sd100;
        send_signal(1'b1, 32'h0096_0000, 16'd50, 8'd2);  // SELL 50 from pos=100
        check("T11 approved_valid (sell)", approved_valid, 1);
        check("T11 approved_side", approved_side, 1);

        repeat (5) @(posedge clk);

        if (err_count == 0)
            $display("tb_risk_manager: PASS");
        else
            $display("tb_risk_manager: FAIL (%0d errors)", err_count);
        $finish;
    end

endmodule
