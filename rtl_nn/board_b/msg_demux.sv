// ============================================================================
// Module: msg_demux
// Frame router for Board B. Reads msg_type field [127:124] from incoming
// link_rx frames and routes QUOTE (4'h1) to the quote path and FILL (4'h3)
// to the fill path. Unknown types are discarded and counted as errors.
// Also counts total quotes received for AXI status readback.
//
// Latency: 1 cycle (registered outputs for clean pipeline timing).
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

    logic [3:0] msg_type_field;
    assign msg_type_field = frame_in[127:124];

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            quote_frame  <= '0;
            quote_valid  <= 1'b0;
            fill_frame   <= '0;
            fill_valid   <= 1'b0;
            quotes_rcvd  <= '0;
            demux_errors <= '0;
        end else if (clear) begin
            quote_valid  <= 1'b0;
            fill_valid   <= 1'b0;
            quotes_rcvd  <= '0;
            demux_errors <= '0;
        end else begin
            quote_valid <= 1'b0;
            fill_valid  <= 1'b0;

            if (frame_in_valid) begin
                unique case (msg_type_field)
                    MSG_QUOTE: begin
                        quote_frame <= frame_in;
                        quote_valid <= 1'b1;
                        quotes_rcvd <= quotes_rcvd + 1'b1;
                    end
                    MSG_FILL: begin
                        fill_frame <= frame_in;
                        fill_valid <= 1'b1;
                    end
                    default: begin
                        demux_errors <= demux_errors + 1'b1;
                    end
                endcase
            end
        end
    end

endmodule
