// ============================================================================
// Testbench: tb_risk_manager
// Tests the risk_manager module: position limit, order rate, max loss,
// order_enable gating, risk_halt latch, in-flight pending tracking,
// fill feedback, simultaneous signal+fill (same and different symbols),
// position boundary conditions, and clear behavior.
//
// Critical regression: simultaneous signal_valid + fill_valid on same
// symbol/side — verifies the merged NBA delta fix (no last-wins race).
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

    task automatic do_clear();
        clear = 1'b1;
        @(posedge clk);
        clear = 1'b0;
        @(posedge clk);
    endtask

    initial begin
        signal_valid   = 1'b0;
        signal_side    = 1'b0;
        signal_price   = '0;
        signal_qty     = '0;
        signal_symbol  = '0;
        fill_valid     = 1'b0;
        fill_symbol    = '0;
        fill_side      = 1'b0;
        fill_qty       = '0;
        clear          = 1'b0;
        order_enable   = 1'b1;
        total_pnl      = '0;
        max_position   = 32'd500;
        max_order_rate = 32'd10000;
        max_loss       = 32'd100;

        for (int i = 0; i < TB_NUM_SYM; i++) position[i] = '0;

        @(posedge rst_n);
        repeat (2) @(posedge clk);

        // ── T1: Basic approval (all checks pass) ─────────────
        $display("\n=== T1: Basic approval ===");
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T1: approved",        approved_valid == 1'b1);
        check("T1: side==BUY",       approved_side == 1'b0);
        check("T1: price",           approved_price == 32'h00B4_0000);
        check("T1: qty==100",        approved_qty == 16'd100);
        check("T1: symbol==0",       approved_symbol == 8'd0);
        check("T1: no halt",         risk_halt == 1'b0);

        // ── T2: order_enable = 0 → rejected ──────────────────
        $display("\n=== T2: order_enable off ===");
        order_enable = 1'b0;
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T2: rejected",        approved_valid == 1'b0);
        check("T2: risk_rejects++",  risk_rejects == 32'd1);
        order_enable = 1'b1;

        // ── T3: Position limit exceeded ───────────────────────
        $display("\n=== T3: Position limit ===");
        position[0] = 32'd450;
        // worst = 450 + pending_buy[0](100 from T1) + 100 = 650 > 500
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T3: rejected (pos)", approved_valid == 1'b0);

        // Clear pending
        send_fill(8'd0, 1'b0, 16'd100);
        // Now pending_buy[0]=0, worst = 450 + 0 + 100 = 550 > 500
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T3b: still rejected", approved_valid == 1'b0);

        // Reduce position to boundary
        position[0] = 32'd400;
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T3c: approved (400+100<=500)", approved_valid == 1'b1);

        // ── T3d: Position boundary: exactly at limit ──────────
        $display("\n=== T3d: Position boundary exactly ===");
        do_clear();
        position[0] = 32'd499;
        max_position = 32'd500;
        send_signal(1'b0, 32'h00B4_0000, 16'd1, 8'd0);
        check("T3d: qty=1 at 499 → 500 ok", approved_valid == 1'b1);

        send_signal(1'b0, 32'h00B4_0000, 16'd2, 8'd0);
        // worst = 499 + pending(1 from T3d) + 2 = 502 > 500
        check("T3e: qty=2 → 502 rejected", approved_valid == 1'b0);

        position[0] = '0;

        // ── T4: Order rate limit ──────────────────────────────
        $display("\n=== T4: Rate limit ===");
        do_clear();
        max_order_rate = 32'd3;

        send_signal(1'b0, 32'h00B4_0000, 16'd10, 8'd0);
        check("T4a: order 1 ok",   approved_valid == 1'b1);
        send_signal(1'b0, 32'h00B4_0000, 16'd10, 8'd1);
        check("T4b: order 2 ok",   approved_valid == 1'b1);
        send_signal(1'b0, 32'h00B4_0000, 16'd10, 8'd2);
        check("T4c: order 3 ok",   approved_valid == 1'b1);

        send_signal(1'b0, 32'h00B4_0000, 16'd10, 8'd3);
        check("T4d: rate limited", approved_valid == 1'b0);

        max_order_rate = 32'd10000;

        // ── T5: Max loss → risk_halt ──────────────────────────
        $display("\n=== T5: Max loss halt ===");
        do_clear();
        total_pnl = -32'sd101;
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T5: rejected",       approved_valid == 1'b0);
        check("T5: risk_halt set",  risk_halt == 1'b1);

        // Latched — even good PnL gets rejected
        total_pnl = 32'sd100;
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T5b: still halted",  approved_valid == 1'b0);

        // Clear unlatches
        do_clear();
        check("T5c: halt cleared",  risk_halt == 1'b0);

        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T5d: approved again", approved_valid == 1'b1);
        total_pnl = '0;

        // ── T6: SELL order position check ─────────────────────
        $display("\n=== T6: SELL position check ===");
        do_clear();
        position[1] = -32'sd400;
        send_signal(1'b1, 32'h01A4_0000, 16'd100, 8'd1);
        // worst = -400 - 0 - 100 = -500, abs=500 <= 500 → pass
        check("T6a: SELL at boundary", approved_valid == 1'b1);

        // pending_sell[1] = 100, worst = -400 - 100 - 100 = -600 > 500
        send_signal(1'b1, 32'h01A4_0000, 16'd100, 8'd1);
        check("T6b: SELL rejected", approved_valid == 1'b0);
        position[1] = '0;

        // ──────────────────────────────────────────────────────
        // T7: CRITICAL REGRESSION — Simultaneous signal+fill
        // same symbol, same side. Must verify merged NBA delta.
        // ──────────────────────────────────────────────────────
        $display("\n=== T7: Simultaneous signal+fill (same sym/side) ===");
        do_clear();
        // First, build up a pending_buy[0] = 100
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T7-setup: approved", approved_valid == 1'b1);
        // Now pending_buy[0] = 100

        // On the same cycle: approve BUY sym=0 qty=50 AND fill BUY sym=0 qty=100
        signal_valid  = 1'b1;
        signal_side   = 1'b0;  // BUY
        signal_price  = 32'h00B4_0000;
        signal_qty    = 16'd50;
        signal_symbol = 8'd0;
        fill_valid    = 1'b1;
        fill_symbol   = 8'd0;
        fill_side     = 1'b0;  // BUY
        fill_qty      = 16'd100;
        @(posedge clk);
        signal_valid = 1'b0;
        fill_valid   = 1'b0;
        @(posedge clk);

        check("T7: simultaneous approved", approved_valid == 1'b1);
        // pending_buy[0] should be: 100 (old) + 50 (new signal) - 100 (fill) = 50
        // With the bug (no merge), it would be either 50 or 0 (last NBA wins)
        // With the fix, the merge handles both in one update
        check("T7: pending merged",
              dut.pending_buy[0] == 16'd50);

        // ──────────────────────────────────────────────────────
        // T8: Simultaneous signal+fill DIFFERENT symbols
        // ──────────────────────────────────────────────────────
        $display("\n=== T8: Simultaneous signal+fill (different syms) ===");
        do_clear();
        // Build pending_sell[1] = 200
        send_signal(1'b1, 32'h01A4_0000, 16'd200, 8'd1);
        check("T8-setup: approved", approved_valid == 1'b1);

        // Simultaneously: approve BUY sym=0 qty=100 AND fill SELL sym=1 qty=200
        signal_valid  = 1'b1;
        signal_side   = 1'b0;  // BUY sym=0
        signal_price  = 32'h00B4_0000;
        signal_qty    = 16'd100;
        signal_symbol = 8'd0;
        fill_valid    = 1'b1;
        fill_symbol   = 8'd1;
        fill_side     = 1'b1;  // SELL sym=1
        fill_qty      = 16'd200;
        @(posedge clk);
        signal_valid = 1'b0;
        fill_valid   = 1'b0;
        @(posedge clk);

        check("T8: approved",              approved_valid == 1'b1);
        check("T8: pending_buy[0]=100",    dut.pending_buy[0] == 16'd100);
        check("T8: pending_sell[1]=0",     dut.pending_sell[1] == 16'd0);

        // ──────────────────────────────────────────────────────
        // T9: Fill clears pending (no underflow)
        // ──────────────────────────────────────────────────────
        $display("\n=== T9: Fill overshoot (no underflow) ===");
        do_clear();
        send_signal(1'b0, 32'h00B4_0000, 16'd50, 8'd2);
        check("T9-setup: approved", approved_valid == 1'b1);
        // pending_buy[2] = 50

        // Fill with qty=100 (more than pending) — should clamp to 0
        send_fill(8'd2, 1'b0, 16'd100);
        @(posedge clk);
        check("T9: pending clamped to 0", dut.pending_buy[2] == 16'd0);

        // ──────────────────────────────────────────────────────
        // T10: Clear resets everything
        // ──────────────────────────────────────────────────────
        $display("\n=== T10: Clear resets all ===");
        total_pnl = -32'sd200;
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T10a: halt triggered", risk_halt == 1'b1);

        do_clear();
        check("T10b: halt cleared",       risk_halt == 1'b0);
        check("T10b: rejects cleared",    risk_rejects == 32'd0);
        check("T10b: pending_buy[0]==0",  dut.pending_buy[0] == 16'd0);
        check("T10b: pending_sell[0]==0", dut.pending_sell[0] == 16'd0);

        total_pnl = '0;
        send_signal(1'b0, 32'h00B4_0000, 16'd100, 8'd0);
        check("T10c: can approve after clear", approved_valid == 1'b1);

        // ── T11: No valid → no output ─────────────────────────
        $display("\n=== T11: Idle ===");
        signal_valid = 1'b0;
        @(posedge clk);
        @(posedge clk);
        check("T11: no output", approved_valid == 1'b0);

        // ── Summary ───────────────────────────────────────────
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
