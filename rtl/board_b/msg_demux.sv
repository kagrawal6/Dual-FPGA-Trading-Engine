// ============================================================================
// Module: msg_demux
// Frame router for Board B. Reads msg_type field [127:124] from incoming
// link_rx frames and routes QUOTE (4'h1) to the quote path and FILL (4'h3)
// to the fill path. Unknown types are discarded and counted as errors.
// Also counts total quotes received for AXI status readback.
// ============================================================================

`timescale 1ns / 1ps

module msg_demux
    import hft_pkg::*;
(
    input  logic                clk,
    input  logic                rst_n,
    input  logic                clear,          // reset counters

    // Frame input (from link_rx)
    input  logic [FRAME_W-1:0] frame_in,
    input  logic                frame_in_valid,

    // QUOTE output → quote_book
    output logic [FRAME_W-1:0] quote_frame,
    output logic                quote_valid,

    // FILL output → position_tracker
    output logic [FRAME_W-1:0] fill_frame,
    output logic                fill_valid,

    // Status
    output logic [COUNTER_W-1:0] quotes_rcvd,
    output logic [COUNTER_W-1:0] demux_errors
);

    // TODO: Implementation
    // Combinational decode of frame_in[127:124]:
    //   MSG_QUOTE → quote_frame/quote_valid
    //   MSG_FILL  → fill_frame/fill_valid
    //   other     → discard, increment demux_errors

endmodule
