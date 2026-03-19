// ============================================================================
// Module: link_tx
// PMOD link transmitter. Serializes a 128-bit frame into DATA_W-bit nibbles
// at 50 MHz effective rate (clock-enable toggle at 100 MHz). Asserts
// pmod_valid for the duration of frame transmission. Respects remote_ready
// backpressure before starting a new frame.
// ============================================================================

`timescale 1ns / 1ps

module link_tx #(
    parameter FRAME_W = 128,
    parameter DATA_W  = 4
)(
    input  logic                  clk,
    input  logic                  rst_n,

    // Frame input (valid/ready handshake)
    input  logic [FRAME_W-1:0]   frame_in,
    input  logic                  frame_in_valid,
    output logic                  frame_in_ready,

    // PMOD output pins
    output logic [DATA_W-1:0]    pmod_data,
    output logic                  pmod_valid,

    // Backpressure from remote link_rx
    input  logic                  remote_ready
);

    localparam BEATS = FRAME_W / DATA_W;   // 32 for 4-bit, 16 for 8-bit

    // TODO: Implementation
    // 50 MHz tick toggle, shift register, beat counter.
    // Hold each nibble for 2 core_clk cycles (20 ns).
    // pmod_valid high during all BEATS data beats.
    // frame_in_ready asserted when idle and remote_ready is high.

endmodule
