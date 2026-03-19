// ============================================================================
// Module: link_rx
// PMOD link receiver. 2-FF synchronizes incoming data/valid into the local
// clock domain, detects frame start via rising edge of valid, then captures
// BEATS_PER_FRAME nibbles into a shift register. Outputs assembled 128-bit
// frames. Tracks framing errors and link-up status.
// ============================================================================

`timescale 1ns / 1ps

module link_rx #(
    parameter FRAME_W = 128,
    parameter DATA_W  = 4
)(
    input  logic                  clk,
    input  logic                  rst_n,

    // PMOD input pins (directly from external — synchronized internally)
    input  logic [DATA_W-1:0]    pmod_data,
    input  logic                  pmod_valid,

    // Backpressure to remote link_tx
    output logic                  local_ready,

    // Frame output (valid pulse when complete frame assembled)
    output logic [FRAME_W-1:0]   frame_out,
    output logic                  frame_out_valid,

    // Status
    output logic                  link_up,
    output logic [31:0]           error_count
);

    localparam BEATS = FRAME_W / DATA_W;

    // TODO: Implementation
    // 2-FF synchronizers for pmod_data and pmod_valid.
    // Rising-edge detect on synced valid → start capture.
    // Internal 50 MHz tick (phase-aligned to detected edge).
    // Shift register assembles FRAME_W bits over BEATS samples.
    // Framing error if new valid arrives mid-frame.
    // link_up set after first successful frame, cleared on reset.
    // local_ready driven by internal FIFO almost_full (if buffered).

endmodule
