// ============================================================================
// Module: tx_arbiter
// Strict-priority 2:1 frame multiplexer. Fill frames (high priority) always
// win over quote frames (low priority). Once a frame starts serialization
// it completes without preemption. Outputs one frame at a time to link_tx.
// ============================================================================

`timescale 1ns / 1ps

module tx_arbiter
    import hft_pkg::*;
(
    input  logic                clk,
    input  logic                rst_n,

    // Fill frame input (high priority)
    input  logic [FRAME_W-1:0] fill_frame,
    input  logic                fill_valid,
    output logic                fill_ready,

    // Quote frame input (low priority)
    input  logic [FRAME_W-1:0] quote_frame,
    input  logic                quote_valid,
    output logic                quote_ready,

    // Arbitrated output (to link_tx)
    output logic [FRAME_W-1:0] tx_frame,
    output logic                tx_valid,
    input  logic                tx_ready
);

    // TODO: Implementation
    // When tx_ready: if fill_valid → forward fill; else if quote_valid → forward quote.
    // No preemption once tx_valid is asserted and tx_ready acknowledged.

endmodule
