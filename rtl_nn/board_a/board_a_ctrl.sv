// ============================================================================
// Module: board_a_ctrl
// Board A physical I/O manager. Instantiates 4x debounce for buttons,
// generates edge-detected pulses for start/stop/reset. Samples switches
// for regime selection and override. Drives LEDs and RGB LEDs to reflect
// system state (regime, running, link health).
// Does NOT contain the FSM — that lives in board_a_top.
// ============================================================================

`timescale 1ns / 1ps

module board_a_ctrl
    import hft_pkg::*;
#(
    parameter int BTN_DEB_W = 16
)(
    input  logic        clk,
    input  logic        rst_n,

    input  logic [3:0]  btn,
    input  logic [7:0]  sw,

    output logic        ctrl_start_pulse,
    output logic        ctrl_stop_pulse,
    output logic        ctrl_reset_pulse,

    output regime_e     regime_sw,
    output logic        sw_override,

    input  logic        running,
    input  regime_e     active_regime,
    input  logic        link_up,
    input  logic        link_error,

    output logic [7:0]  led,
    output logic [2:0]  rgb0,
    output logic [2:0]  rgb1
);

    logic db0, db1, db2, db3;
    logic p0, p1, p2, p3;

    debounce #(.COUNTER_W(BTN_DEB_W)) u_db0 (.clk(clk), .rst_n(rst_n), .btn_in(btn[0]), .btn_out(db0), .btn_pulse(p0));
    debounce #(.COUNTER_W(BTN_DEB_W)) u_db1 (.clk(clk), .rst_n(rst_n), .btn_in(btn[1]), .btn_out(db1), .btn_pulse(p1));
    debounce #(.COUNTER_W(BTN_DEB_W)) u_db2 (.clk(clk), .rst_n(rst_n), .btn_in(btn[2]), .btn_out(db2), .btn_pulse(p2));
    debounce #(.COUNTER_W(BTN_DEB_W)) u_db3 (.clk(clk), .rst_n(rst_n), .btn_in(btn[3]), .btn_out(db3), .btn_pulse(p3));

    assign ctrl_start_pulse = p0;
    assign ctrl_stop_pulse  = p1;
    assign ctrl_reset_pulse = p2;

    assign regime_sw   = regime_e'(sw[1:0]);
    assign sw_override = sw[2];

    logic [24:0] blink_ctr;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            blink_ctr <= '0;
        else
            blink_ctr <= blink_ctr + 1'b1;
    end

    assign led[1:0] = active_regime;
    assign led[2]   = running;
    assign led[3]   = running & blink_ctr[24];
    assign led[4]   = link_up;
    assign led[5]   = link_error;
    assign led[7:6] = 2'b00;

    always_comb begin
        unique case (active_regime)
            REGIME_CALM:        rgb0 = 3'b010;
            REGIME_VOLATILE:    rgb0 = 3'b110;
            REGIME_BURST:       rgb0 = 3'b100;
            REGIME_ADVERSARIAL: rgb0 = 3'b101;
            default:              rgb0 = 3'b000;
        endcase
    end

    always_comb begin
        if (!link_up)
            rgb1 = 3'b100;
        else if (link_error)
            rgb1 = 3'b110;
        else
            rgb1 = 3'b010;
    end

endmodule
