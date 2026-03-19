// ============================================================================
// Testbench: tb_board_b_ctrl
// Tests the board_b_ctrl module: button debounce, switch sampling (trading_enable,
// strategy_sw, sw_strategy_override), and LED/RGB outputs driven by FSM state,
// order_enable, risk_halt, link_up, and total_pnl.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_b_ctrl;

    logic                     clk;
    logic                     rst_n;
    logic [3:0]               btn;
    logic [7:0]               sw;
    logic                     ctrl_start_pulse;
    logic                     ctrl_stop_pulse;
    logic                     ctrl_reset_pulse;
    logic                     trading_enable;
    strategy_e                strategy_sw;
    logic                     sw_strategy_override;
    b_state_e                 fsm_state;
    logic                     order_enable;
    logic                     risk_halt;
    logic                     link_up;
    sprice_t                  total_pnl;
    logic [7:0]               led;
    logic [2:0]               rgb0;
    logic [2:0]               rgb1;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low rst_n, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    board_b_ctrl dut (
        .clk                  (clk),
        .rst_n                (rst_n),
        .btn                  (btn),
        .sw                   (sw),
        .ctrl_start_pulse     (ctrl_start_pulse),
        .ctrl_stop_pulse      (ctrl_stop_pulse),
        .ctrl_reset_pulse     (ctrl_reset_pulse),
        .trading_enable       (trading_enable),
        .strategy_sw          (strategy_sw),
        .sw_strategy_override (sw_strategy_override),
        .fsm_state            (fsm_state),
        .order_enable         (order_enable),
        .risk_halt            (risk_halt),
        .link_up              (link_up),
        .total_pnl            (total_pnl),
        .led                  (led),
        .rgb0                 (rgb0),
        .rgb1                 (rgb1)
    );

    initial begin
        // TODO: Add test stimulus
        #1000;
        $finish;
    end

endmodule
