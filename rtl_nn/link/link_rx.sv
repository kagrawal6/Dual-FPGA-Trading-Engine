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
    input  logic                  counter_clr,       // FSM RESET: clear error counter

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

    // Message types (msg_type field = frame_out[127:124])
    localparam logic [3:0] MSG_QUOTE = 4'h1;
    localparam logic [3:0] MSG_ORDER = 4'h2;
    localparam logic [3:0] MSG_FILL  = 4'h3;

    localparam int LAST_BEAT = BEATS - 1;
    localparam int BEAT_W    = (BEATS > 1) ? $clog2(BEATS) : 1;

    // ---------------------------------------------------------------------
    // 2-FF synchronizers for incoming PMOD pins
    // ---------------------------------------------------------------------
    logic               valid_s1, valid_sync;
    logic [DATA_W-1:0]  data_s1,  data_sync;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            valid_s1   <= 1'b0;
            valid_sync <= 1'b0;
            data_s1    <= '0;
            data_sync  <= '0;
        end
        else begin
            valid_s1   <= pmod_valid;
            valid_sync <= valid_s1;
            data_s1    <= pmod_data;
            data_sync  <= data_s1;
        end
    end

    // Rising-edge detect on synced valid
    logic valid_prev;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) valid_prev <= 1'b0;
        else        valid_prev <= valid_sync;
    end

    wire valid_rise = valid_sync & ~valid_prev;

    // ---------------------------------------------------------------------
    // Frame assembly
    // ---------------------------------------------------------------------
    typedef enum logic [0:0] { S_IDLE, S_CAPTURE } state_e;
    state_e state;

    logic [FRAME_W-1:0] assemble_reg;
    logic [BEAT_W-1:0]  beat_count;
    logic                phase; // toggles each core_clk; beat sample when phase==0

    // local_ready is backpressure to remote link_tx. With no extra buffering,
    // we only accept a new frame when idle.
    assign local_ready = (state == S_IDLE);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state           <= S_IDLE;
            assemble_reg    <= '0;
            beat_count      <= '0;
            phase           <= 1'b0;
            frame_out       <= '0;
            frame_out_valid <= 1'b0;
            link_up         <= 1'b0;
            error_count     <= '0;
        end
        else begin
            frame_out_valid <= 1'b0; // 1-cycle pulse

            case (state)
                S_IDLE: begin
                    if (valid_rise) begin
                        assemble_reg <= '0;
                        beat_count   <= '0;
                        phase        <= 1'b0; // first sample occurs immediately on next cycle
                        state        <= S_CAPTURE;
                    end
                end

                S_CAPTURE: begin
                    // We sample every other core clock to match the PMOD beat
                    // rate (nibbles held for 2 core_clk cycles).
                    if (!phase) begin
                        // If valid drops before completing the expected beats, count an error
                        // and deassert link_up (framing failure = link unreliable).
                        if (!valid_sync) begin
                            error_count <= error_count + 1'b1;
                            link_up     <= 1'b0;
                            state       <= S_IDLE;
                        end
                        else begin
                            logic [FRAME_W-1:0] assembled_next;
                            assembled_next = {assemble_reg[FRAME_W-DATA_W-1:0], data_sync};

                            if (beat_count == LAST_BEAT[BEAT_W-1:0]) begin
                                // Frame completion: validate msg_type and either output or drop.
                                unique case (assembled_next[FRAME_W-1 -: 4])
                                    MSG_QUOTE, MSG_ORDER, MSG_FILL: begin
                                        frame_out       <= assembled_next;
                                        frame_out_valid <= 1'b1;
                                        link_up         <= 1'b1;
                                    end
                                    default: begin
                                        error_count <= error_count + 1'b1;
                                        link_up     <= 1'b0;
                                    end
                                endcase

                                assemble_reg <= '0;
                                beat_count   <= '0;
                                phase        <= 1'b0;
                                state        <= S_IDLE;
                            end
                            else begin
                                assemble_reg <= assembled_next;
                                beat_count   <= beat_count + 1'b1;
                            end
                        end
                    end

                    // Toggle sampling phase every core clock during capture.
                    phase <= ~phase;
                end

                default: state <= S_IDLE;
            endcase

            if (counter_clr) begin
                error_count <= '0;
                link_up     <= 1'b0;
            end
        end
    end

endmodule
