// ============================================================================
// Module: debounce
// Button debouncer using a counter-based approach. Input must be stable for
// 2^COUNTER_W clock cycles (~10.5 ms at 100 MHz with COUNTER_W=20) before
// the output changes. Also produces a single-cycle rising-edge pulse.
// ============================================================================

`timescale 1ns / 1ps

module debounce #(
    parameter COUNTER_W = 20           // 2^20 ≈ 10.5 ms at 100 MHz
)(
    input  logic clk,
    input  logic rst_n,
    input  logic btn_in,               // raw mechanical button input
    output logic btn_out,              // debounced level
    output logic btn_pulse             // single-cycle pulse on rising edge
);

    // TODO: Implementation
    // Counter-based: increment counter while btn_in != btn_out,
    // reset counter when btn_in == btn_out.
    // Toggle btn_out when counter saturates.
    // btn_pulse = btn_out & ~btn_out_prev (edge detect).

endmodule
