// ============================================================================
// Module: link_tx
// PMOD link transmitter. Serializes a 128-bit frame into DATA_W-bit nibbles
// at 50 MHz effective rate (clock-enable toggle at 100 MHz). Asserts
// pmod_valid for the duration of frame transmission. Respects remote_ready
// backpressure before starting a new frame.
//
// remote_ready crosses from the remote board's clock domain, so it is
// internally synchronized with a 2-FF chain (same pattern as link_rx).
// ============================================================================

`timescale 1ns / 1ps

module link_tx #(
    parameter int FRAME_W = 128,
    parameter int DATA_W  = 4
)(
    input  logic                  clk,
    input  logic                  rst_n,

    input  logic [FRAME_W-1:0]   frame_in,
    input  logic                  frame_in_valid,
    output logic                  frame_in_ready,

    output logic [DATA_W-1:0]    pmod_data,
    output logic                  pmod_valid,

    input  logic                  remote_ready      // async from remote board
);

    // -----------------------------------------------------------------
    // 2-FF synchronizer for remote_ready (crosses clock domains)
    // -----------------------------------------------------------------
    logic remote_ready_s1, remote_ready_sync;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            remote_ready_s1   <= 1'b0;
            remote_ready_sync <= 1'b0;
        end else begin
            remote_ready_s1   <= remote_ready;
            remote_ready_sync <= remote_ready_s1;
        end
    end

    localparam int BEATS   = FRAME_W / DATA_W;
    localparam int BEAT_W  = (BEATS > 1) ? $clog2(BEATS) : 1;

    typedef enum logic [0:0] { ST_IDLE, ST_SEND } st_e;
    st_e st;

    logic [FRAME_W-1:0] shifter;
    logic [BEAT_W-1:0]  beat;
    logic               half_nibble;

    assign pmod_data      = shifter[FRAME_W-1:FRAME_W-DATA_W];
    assign frame_in_ready = (st == ST_IDLE) && remote_ready_sync;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            st            <= ST_IDLE;
            shifter       <= '0;
            beat          <= '0;
            half_nibble   <= 1'b0;
            pmod_valid    <= 1'b0;
        end else begin
            unique case (st)
                ST_IDLE: begin
                    pmod_valid <= 1'b0;
                    if (frame_in_valid && frame_in_ready) begin
                        shifter     <= frame_in;
                        beat        <= '0;
                        half_nibble <= 1'b0;
                        st          <= ST_SEND;
                        pmod_valid  <= 1'b1;
                    end
                end
                ST_SEND: begin
                    pmod_valid <= 1'b1;
                    if (!half_nibble) begin
                        half_nibble <= 1'b1;
                    end else begin
                        half_nibble <= 1'b0;
                        if (beat == BEAT_W'(BEATS - 1)) begin
                            st         <= ST_IDLE;
                            pmod_valid <= 1'b0;
                        end else begin
                            shifter <= {shifter[FRAME_W-DATA_W-1:0], {DATA_W{1'b0}}};
                            beat    <= beat + 1'b1;
                        end
                    end
                end
                default: st <= ST_IDLE;
            endcase
        end
    end

endmodule
