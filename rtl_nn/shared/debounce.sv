// ============================================================================
// Module: debounce
// Button debouncer: raw input must stay stable for 2^COUNTER_W consecutive
// clock cycles before btn_out updates. Produces a single-cycle rising-edge
// pulse on btn_out when it transitions 0→1.
// ============================================================================

`timescale 1ns / 1ps

module debounce #(
    // Default matches hft_pkg::DEBOUNCE_COUNTER_W (instantiate with that for boards).
    parameter int COUNTER_W = 20           // 2^COUNTER_W cycles of stability
)(
    input  logic clk,
    input  logic rst_n,
    input  logic btn_in,                   // raw mechanical button (async — sync externally if required)
    output logic btn_out,                 // debounced level
    output logic btn_pulse                // 1-cycle high on rising edge of btn_out
);

    // Need (COUNTER_W+1) bits to count up to 2^COUNTER_W inclusive.
    localparam int STABLE_CYCLES = 1 << COUNTER_W;
    localparam int CNT_W         = COUNTER_W + 1;
    localparam logic [CNT_W-1:0] STABLE_TOP = CNT_W'(STABLE_CYCLES);

    logic [CNT_W-1:0] counter;
    logic             btn_out_prev;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            counter      <= '0;
            btn_out      <= 1'b0;
            btn_out_prev <= 1'b0;
            btn_pulse    <= 1'b0;
        end
        else begin
            // Count only while input disagrees with debounced output.
            // Any agreement resets the integrator (bounce / noise).
            if (btn_in != btn_out) begin
                if (counter == STABLE_TOP) begin
                    btn_out   <= btn_in;
                    counter   <= '0;
                end
                else begin
                    counter <= counter + 1'b1;
                end
            end
            else begin
                counter <= '0;
            end

            // Rising-edge detect (1 cycle wide), same pattern as legacy debounce.
            btn_out_prev <= btn_out;
            btn_pulse    <= btn_out & ~btn_out_prev;
        end
    end

endmodule
