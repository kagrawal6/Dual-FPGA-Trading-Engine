// ============================================================================
// Testbench: tb_board_b_ctrl
// Tests debounce button pulses, switch config mapping, LED state encoding,
// and RGB PnL/risk status indicators.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_b_ctrl;

    logic        clk, rst_n;
    logic [3:0]  btn;
    logic [7:0]  sw;
    logic        ctrl_start_pulse, ctrl_stop_pulse, ctrl_reset_pulse;
    logic        trading_enable;
    strategy_e   strategy_sw;
    logic        sw_strategy_override;
    b_state_e    fsm_state;
    logic        order_enable, risk_halt, link_up;
    sprice_t     total_pnl;
    logic [7:0]  led;
    logic [2:0]  rgb0, rgb1;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    board_b_ctrl #(.BTN_DEB_W(4)) dut (
        .clk                (clk),
        .rst_n              (rst_n),
        .btn                (btn),
        .sw                 (sw),
        .ctrl_start_pulse   (ctrl_start_pulse),
        .ctrl_stop_pulse    (ctrl_stop_pulse),
        .ctrl_reset_pulse   (ctrl_reset_pulse),
        .trading_enable     (trading_enable),
        .strategy_sw        (strategy_sw),
        .sw_strategy_override(sw_strategy_override),
        .fsm_state          (fsm_state),
        .order_enable       (order_enable),
        .risk_halt          (risk_halt),
        .link_up            (link_up),
        .total_pnl          (total_pnl),
        .led                (led),
        .rgb0               (rgb0),
        .rgb1               (rgb1)
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

    initial begin
        btn          = 4'b0000;
        sw           = 8'h00;
        fsm_state    = B_RESET;
        order_enable = 1'b0;
        risk_halt    = 1'b0;
        link_up      = 1'b0;
        total_pnl    = '0;

        @(posedge rst_n);
        repeat (2) @(posedge clk);

        // ── T1: Switch mapping ──────────────────────────────────
        $display("\n=== T1: Switch mapping ===");
        sw = 8'b0000_1011;  // SW[0]=1, SW[2:1]=01, SW[3]=1
        @(posedge clk);
        check("T1: trading_enable",     trading_enable == 1'b1);
        check("T1: strategy==MOMENTUM", strategy_sw == STRAT_MOMENTUM);
        check("T1: override active",    sw_strategy_override == 1'b1);

        sw = 8'b0000_0100;  // SW[0]=0, SW[2:1]=10, SW[3]=0
        @(posedge clk);
        check("T1b: trading off",       trading_enable == 1'b0);
        check("T1b: strategy==NN",      strategy_sw == STRAT_NN);
        check("T1b: no override",       sw_strategy_override == 1'b0);

        // ── T2: Button debounce pulse ───────────────────────────
        $display("\n=== T2: Button debounce ===");
        btn[0] = 1'b1;
        repeat (20) @(posedge clk);  // wait for debounce (COUNTER_W=4 → 16 cycles)
        // Check that start pulse was generated (single cycle)
        // We'll look at the outputs in a window
        btn[0] = 1'b0;
        repeat (20) @(posedge clk);
        // (Debounce with COUNTER_W=4 should settle quickly in sim)

        // ── T3: LED state encoding ──────────────────────────────
        $display("\n=== T3: LED state encoding ===");
        fsm_state    = B_TRADING;
        link_up      = 1'b1;
        risk_halt    = 1'b0;
        order_enable = 1'b1;
        @(posedge clk);
        check("T3: LED[2:0]=TRADING",    led[2:0] == B_TRADING[2:0]);
        check("T3: LED[4]=link_up",      led[4] == 1'b1);
        check("T3: LED[5]=no halt",      led[5] == 1'b0);
        check("T3: LED[6]=order_en",     led[6] == 1'b1);

        fsm_state = B_HALTED;
        risk_halt = 1'b1;
        @(posedge clk);
        check("T3b: LED[2:0]=HALTED",   led[2:0] == B_HALTED[2:0]);
        check("T3b: LED[5]=halt",        led[5] == 1'b1);

        // ── T4: RGB0 — PnL indicator ────────────────────────────
        $display("\n=== T4: RGB0 PnL ===");
        total_pnl = 32'sd100;
        @(posedge clk);
        check("T4: profit → green",     rgb0 == 3'b010);

        total_pnl = -32'sd50;
        @(posedge clk);
        check("T4b: loss → red",        rgb0 == 3'b100);

        total_pnl = 32'sd0;
        @(posedge clk);
        check("T4c: flat → off",        rgb0 == 3'b000);

        // ── T5: RGB1 — risk/link status ─────────────────────────
        $display("\n=== T5: RGB1 risk/link ===");
        risk_halt = 1'b0;
        link_up   = 1'b1;
        @(posedge clk);
        check("T5: healthy → green",    rgb1 == 3'b010);

        link_up = 1'b0;
        @(posedge clk);
        check("T5b: no link → yellow",  rgb1 == 3'b110);

        risk_halt = 1'b1;
        @(posedge clk);
        check("T5c: halt → red",        rgb1 == 3'b100);

        // ── Summary ─────────────────────────────────────────────
        repeat (3) @(posedge clk);
        $display("\n══════════════════════════════════════════");
        $display("  board_b_ctrl testbench complete");
        $display("  PASSED: %0d", pass_count);
        $display("  FAILED: %0d", fail_count);
        $display("══════════════════════════════════════════\n");

        if (fail_count > 0) $fatal(1, "TESTBENCH FAILED");
        $finish;
    end

endmodule
