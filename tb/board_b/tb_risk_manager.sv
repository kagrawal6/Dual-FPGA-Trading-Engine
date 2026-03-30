// ============================================================================
// Testbench: tb_risk_manager
// Tests the risk_manager module: position limit, order rate, max loss,
// order_enable gating, risk_halt latch, in-flight pending tracking,
// fill feedback, and clear behavior.
//
// Golden model reference: board_b.py RiskManager class. Test values are
// constructed to match golden model logic (worst-case position including
// pending, strict rate limit, signed PnL comparison).
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_risk_manager;

    localparam int TB_NUM_SYM = 4;

    logic        clk, rst_n, clear, order_enable;
    logic        signal_valid, signal_side;
    price_t      signal_price;
    qty_t        signal_qty;
    symbol_t     signal_symbol;
    position_t   position [TB_NUM_SYM];
    sprice_t     total_pnl;
    logic [POSITION_W-1:0] max_position;
    logic [COUNTER_W-1:0]  max_order_rate;
    price_t      max_loss;

    logic        approved_valid, approved_side;
    price_t      approved_price;
    qty_t        approved_qty;
    symbol_t     approved_symbol;

    logic        fill_valid, fill_side;
    symbol_t     fill_symbol;
    qty_t        fill_qty;

    logic        risk_halt;
    logic [COUNTER_W-1:0] risk_rejects;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    risk_manager #(.NUM_SYM(TB_NUM_SYM)) dut (
        .clk             (clk),
        .rst_n           (rst_n),
        .clear           (clear),
        .order_enable    (order_enable),
        .signal_valid    (signal_valid),
        .signal_side     (signal_side),
        .signal_price    (signal_price),
        .signal_qty      (signal_qty),
        .signal_symbol   (signal_symbol),
        .position        (position),
        .total_pnl       (total_pnl),
        .max_position    (max_position),
        .max_order_rate  (max_order_rate),
        .max_loss        (max_loss),
        .approved_valid  (approved_valid),
        .approved_side   (approved_side),
        .approved_price  (approved_price),
        .approved_qty    (approved_qty),
        .approved_symbol (approved_symbol),
        .fill_valid      (fill_valid),
        .fill_symbol     (fill_symbol),
        .fill_side       (fill_side),
        .fill_qty        (fill_qty),
        .risk_halt       (risk_halt),
        .risk_rejects    (risk_rejects)
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

    task automatic send_signal(
        input logic        side,
        input price_t      price,
        input qty_t        qty,
        input symbol_t     sym
    );
        signal_valid  = 1'b1;
        signal_side   = side;
        signal_price  = price;
        signal_qty    = qty;
        signal_symbol = sym;
        @(posedge clk);
        signal_valid = 1'b0;
        @(posedge clk);
    endtask

    task automatic send_fill(
        input symbol_t sym,
        input logic    side,
        input qty_t    qty
    );
        fill_valid  = 1'b1;
        fill_symbol = sym;
        fill_side   = side;
        fill_qty    = qty;
        @(posedge clk);
        fill_valid = 1'b0;
    endtask

    initial begin
        signal_valid  = 1'b0;
        signal_side   = 1'b0;
        signal_price  = '0;
        signal_qty    = '0;
        signal_symbol = '0;
        fill_valid    = 1'b0;
        fill_symbol   = '0;
        fill_side     = 1'b0;
        fill_qty      = '0;
        clear         = 1'b0;
        order_enable  = 1'b1;
        total_pnl     = '0;
        max_position  = 32'd500;
        max_order_rate = 32'd10000;
        max_loss      = 32'd100;  // $100 integer (matching total_pnl units)

        for (int i = 0; i < TB_NUM_SYM; i++) position[i] = '0;

        @(posedge rst_n);
        repeat (2) @(posedge clk);

        // ── T1: Basic approval (all checks pass) ────────────────
        $display("\n=== T1: Basic approval ===");
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T1: approved",       approved_valid == 1'b1);
        check("T1: side==BUY",      approved_side == 1'b0);
        check("T1: price",          approved_price == 32'h00B4_0000);
        check("T1: qty==100",       approved_qty == 16'd100);
        check("T1: symbol==0",      approved_symbol == 8'd0);
        check("T1: no halt",        risk_halt == 1'b0);

        // ── T2: order_enable = 0 → rejected ────────────────────
        $display("\n=== T2: order_enable off ===");
        order_enable = 1'b0;
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T2: rejected",       approved_valid == 1'b0);
        check("T2: risk_rejects++", risk_rejects == 32'd1);
        order_enable = 1'b1;

        // ── T3: Position limit exceeded ─────────────────────────
        $display("\n=== T3: Position limit ===");
        // Position[0] = 450, max_position = 500
        // BUY qty=100 → worst = 450 + 100 (pending_buy from T1) + 100 = 650 > 500
        position[0] = 32'd450;
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T3: rejected (pos)",  approved_valid == 1'b0);
        check("T3: risk_rejects",    risk_rejects == 32'd2);

        // Clear pending by sending a fill for the T1 pending buy
        send_fill(8'd0, 1'b0, 16'd100);

        // Now with pending cleared: worst = 450 + 0 + 100 = 550 > 500
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T3b: still rejected", approved_valid == 1'b0);

        // Reduce position
        position[0] = 32'd300;
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T3c: approved (300+100<=500)", approved_valid == 1'b1);

        position[0] = '0;

        // ── T4: Order rate limit ────────────────────────────────
        $display("\n=== T4: Rate limit ===");
        max_order_rate = 32'd3;
        clear = 1'b1;
        @(posedge clk);
        clear = 1'b0;
        @(posedge clk);

        // Send 3 orders → should all pass
        send_signal(1'b0, 32'h00B4_0000, 16'd10, 8'd0);
        check("T4a: order 1 ok",   approved_valid == 1'b1);
        send_signal(1'b0, 32'h00B4_0000, 16'd10, 8'd1);
        check("T4b: order 2 ok",   approved_valid == 1'b1);
        send_signal(1'b0, 32'h00B4_0000, 16'd10, 8'd2);
        check("T4c: order 3 ok",   approved_valid == 1'b1);

        // 4th order should fail rate check
        send_signal(1'b0, 32'h00B4_0000, 16'd10, 8'd3);
        check("T4d: rate limited", approved_valid == 1'b0);

        max_order_rate = 32'd10000;

        // ── T5: Max loss → risk_halt ────────────────────────────
        $display("\n=== T5: Max loss halt ===");
        clear = 1'b1;
        @(posedge clk);
        clear = 1'b0;
        @(posedge clk);

        // total_pnl = -$101 → below -max_loss(-$100) → halt
        // In Q16.16 signed: -101 = 0xFFFFFF9B as integer dollars in sprice_t
        total_pnl = -32'sd101;
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T5: rejected",      approved_valid == 1'b0);
        check("T5: risk_halt set", risk_halt == 1'b1);

        // Subsequent orders fail even with good PnL (halt is latched)
        total_pnl = 32'sd100;
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T5b: still halted", approved_valid == 1'b0);

        // Clear unlatches
        clear = 1'b1;
        @(posedge clk);
        clear = 1'b0;
        @(posedge clk);
        check("T5c: halt cleared", risk_halt == 1'b0);

        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T5d: approved again", approved_valid == 1'b1);
        total_pnl = '0;

        // ── T6: SELL order position check ───────────────────────
        $display("\n=== T6: SELL position check ===");
        clear = 1'b1;
        @(posedge clk);
        clear = 1'b0;
        @(posedge clk);

        position[1] = -32'sd400;
        send_signal(1'b1, 32'h01A4_0000, 16'd100, 8'd1);
        // worst = -400 - 0 - 100 = -500, abs = 500 <= 500 → pass
        check("T6a: SELL at boundary", approved_valid == 1'b1);

        // Now pending_sell[1] = 100, worst = -400 - 100 - 100 = -600 > 500
        send_signal(1'b1, 32'h01A4_0000, 16'd100, 8'd1);
        check("T6b: SELL rejected", approved_valid == 1'b0);

        position[1] = '0;

        // ── T7: No valid → no output ────────────────────────────
        $display("\n=== T7: Idle ===");
        signal_valid = 1'b0;
        @(posedge clk);
        @(posedge clk);
        check("T7: no output", approved_valid == 1'b0);

        // ── Summary ─────────────────────────────────────────────
        repeat (3) @(posedge clk);
        $display("\n══════════════════════════════════════════");
        $display("  risk_manager testbench complete");
        $display("  PASSED: %0d", pass_count);
        $display("  FAILED: %0d", fail_count);
        $display("══════════════════════════════════════════\n");

        if (fail_count > 0) $fatal(1, "TESTBENCH FAILED");
        $finish;
    end

endmodule
