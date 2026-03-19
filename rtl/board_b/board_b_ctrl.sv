// ============================================================================
// Module: board_b_ctrl
// Board B physical I/O manager. Instantiates 4x debounce for buttons,
// generates edge-detected pulses for start/stop/reset. Samples switches
// for trading_enable and strategy selection. Drives LEDs for order/fill
// activity and RGB LEDs for PnL and risk status.
// Does NOT contain the FSM — that lives in board_b_top.
// ============================================================================

`timescale 1ns / 1ps

module board_b_ctrl
    import hft_pkg::*;
(
    input  logic        clk,
    input  logic        rst_n,

    // ── Raw physical inputs ─────────────────────────────────────────────────
    input  logic [3:0]  btn,                // BTN[3:0] active-high
    input  logic [7:0]  sw,                 // SW[7:0] active-high

    // ── Debounced button pulses (single-cycle) ──────────────────────────────
    output logic        ctrl_start_pulse,   // BTN[0] rising edge
    output logic        ctrl_stop_pulse,    // BTN[1] rising edge
    output logic        ctrl_reset_pulse,   // BTN[2] rising edge

    // ── Switch-derived config ───────────────────────────────────────────────
    output logic        trading_enable,     // SW[0] — gate ARMED→TRADING
    output strategy_e   strategy_sw,        // SW[2:1] — strategy when override active
    output logic        sw_strategy_override, // SW[3] — use strategy_sw instead of PS

    // ── Status inputs (for LED/RGB driving) ─────────────────────────────────
    input  b_state_e    fsm_state,
    input  logic        order_enable,
    input  logic        risk_halt,
    input  logic        link_up,
    input  sprice_t     total_pnl,

    // ── LED/RGB outputs ─────────────────────────────────────────────────────
    output logic [7:0]  led,
    output logic [2:0]  rgb0,               // PnL indicator (green/red/off)
    output logic [2:0]  rgb1                // risk status (green/yellow/red)
);

    // TODO: Implementation
    // Instantiate debounce x4 for btn[3:0].
    // SW[0] = trading_enable (registered).
    // SW[2:1] = strategy_sw (registered).
    // SW[3] = sw_strategy_override (registered).
    // LED[3:0] = order activity flash, LED[7:4] = fill activity flash.
    // RGB0: total_pnl > 0 → green, total_pnl < 0 → red, == 0 → off.
    // RGB1: !risk_halt & link_up → green, !risk_halt & !link_up → yellow, risk_halt → red.

endmodule
