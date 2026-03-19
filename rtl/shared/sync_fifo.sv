// ============================================================================
// Module: sync_fifo
// Parameterized synchronous FIFO (single clock domain). Provides almost_full
// for link-layer backpressure and count for AXI status readback.
// ============================================================================

`timescale 1ns / 1ps

module sync_fifo #(
    parameter DATA_W             = 128,
    parameter DEPTH              = 64,
    parameter ALMOST_FULL_THRESH = DEPTH - 4
)(
    input  logic                       clk,
    input  logic                       rst_n,
    input  logic                       flush,        // synchronous clear

    // Write interface
    input  logic                       wr_en,
    input  logic [DATA_W-1:0]          wr_data,
    output logic                       full,

    // Read interface
    input  logic                       rd_en,
    output logic [DATA_W-1:0]          rd_data,
    output logic                       empty,

    // Status
    output logic                       almost_full,
    output logic [$clog2(DEPTH):0]     count         // current occupancy
);

    // TODO: Implementation
    // Circular buffer with wr_ptr / rd_ptr.
    // count tracks occupancy; almost_full = (count >= ALMOST_FULL_THRESH).

endmodule
