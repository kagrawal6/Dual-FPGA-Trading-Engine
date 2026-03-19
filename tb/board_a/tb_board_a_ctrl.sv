// ============================================================================
// Testbench: tb_board_a_ctrl
// Tests the board_a_ctrl module: Board A physical I/O manager with debounce
// for buttons, edge-detected pulses for start/stop/reset, switch sampling
// for regime selection, and LED/RGB driving for system state.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_a_ctrl;

    logic        clk;
    logic        rst_n;
    logic [3:0]  btn;
    logic [7:0]  sw;
    logic        ctrl_start_pulse;
    logic        ctrl_stop_pulse;
    logic        ctrl_reset_pulse;
    regime_e     regime_sw;
    logic        sw_override;
    a_state_e    fsm_state;
    logic        running;
    regime_e     active_regime;
    logic        link_up;
    logic        link_error;
    logic [7:0]  led;
    logic [2:0]  rgb0;
    logic [2:0]  rgb1;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    board_a_ctrl dut (
        .clk              (clk),
        .rst_n            (rst_n),
        .btn              (btn),
        .sw               (sw),
        .ctrl_start_pulse (ctrl_start_pulse),
        .ctrl_stop_pulse  (ctrl_stop_pulse),
        .ctrl_reset_pulse (ctrl_reset_pulse),
        .regime_sw        (regime_sw),
        .sw_override      (sw_override),
        .fsm_state        (fsm_state),
        .running          (running),
        .active_regime    (active_regime),
        .link_up          (link_up),
        .link_error       (link_error),
        .led              (led),
        .rgb0             (rgb0),
        .rgb1             (rgb1)
    );

    initial begin
        // TODO: Add test stimulus
        #1000;
        $finish;
    end

endmodule
