// ============================================================================
// Module: board_a_ctrl
// Board A physical I/O manager. Instantiates 4x debounce for buttons,
// generates edge-detected pulses for start/stop/reset. Samples switches
// for regime selection and override. Drives LEDs and RGB LEDs to reflect
// system state (regime, running, link health).
// Does NOT contain the FSM — that lives in board_a_top.
// ============================================================================

`timescale 1ns / 1ps

module board_a_ctrl
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
    output regime_e     regime_sw,          // SW[1:0] → regime when override active
    output logic        sw_override,        // SW[2]   → use regime_sw instead of PS

    // ── Status inputs (for LED/RGB driving) ─────────────────────────────────
    input  a_state_e    fsm_state,
    input  logic        running,
    input  regime_e     active_regime,
    input  logic        link_up,
    input  logic        link_error,         // any link errors detected

    // ── LED/RGB outputs ─────────────────────────────────────────────────────
    output logic [7:0]  led,
    output logic [2:0]  rgb0,               // regime indicator color
    output logic [2:0]  rgb1                // link health indicator
);

    // TODO: Implementation
    // Instantiate debounce x4 for btn[3:0].
    // LED mapping: [1:0]=regime, [2]=running, [3]=blink, [4]=link_up, etc.
    // RGB0: CALM=green, VOLATILE=yellow, BURST=red, ADVERSARIAL=purple.
    // RGB1: link_up & !error=green, link_up & error=yellow, !link_up=red.

endmodule
