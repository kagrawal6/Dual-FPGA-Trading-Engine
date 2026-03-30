// ============================================================================
// Module: board_b_ctrl
// Board B physical I/O manager. Instantiates 4x debounce for buttons,
// generates edge-detected pulses for start/stop/reset. Samples switches
// for trading_enable and strategy selection. Drives LEDs for FSM state
// and RGB LEDs for PnL and risk status.
// Does NOT contain the FSM — that lives in board_b_top.
// ============================================================================

`timescale 1ns / 1ps

module board_b_ctrl
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

    output logic        trading_enable,
    output strategy_e   strategy_sw,
    output logic        sw_strategy_override,

    input  b_state_e    fsm_state,
    input  logic        order_enable,
    input  logic        risk_halt,
    input  logic        link_up,
    input  sprice_t     total_pnl,

    output logic [7:0]  led,
    output logic [2:0]  rgb0,
    output logic [2:0]  rgb1
);

    // ── Button debounce ─────────────────────────────────────────
    logic db0, db1, db2, db3;
    logic p0, p1, p2, p3;

    debounce #(.COUNTER_W(BTN_DEB_W)) u_db0 (.clk(clk), .rst_n(rst_n), .btn_in(btn[0]), .btn_out(db0), .btn_pulse(p0));
    debounce #(.COUNTER_W(BTN_DEB_W)) u_db1 (.clk(clk), .rst_n(rst_n), .btn_in(btn[1]), .btn_out(db1), .btn_pulse(p1));
    debounce #(.COUNTER_W(BTN_DEB_W)) u_db2 (.clk(clk), .rst_n(rst_n), .btn_in(btn[2]), .btn_out(db2), .btn_pulse(p2));
    debounce #(.COUNTER_W(BTN_DEB_W)) u_db3 (.clk(clk), .rst_n(rst_n), .btn_in(btn[3]), .btn_out(db3), .btn_pulse(p3));

    assign ctrl_start_pulse = p0;
    assign ctrl_stop_pulse  = p1;
    assign ctrl_reset_pulse = p2;

    // ── Switch sampling ─────────────────────────────────────────
    assign trading_enable     = sw[0];
    assign strategy_sw        = strategy_e'(sw[2:1]);
    assign sw_strategy_override = sw[3];

    // ── Blink counter for activity indication ───────────────────
    logic [24:0] blink_ctr;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            blink_ctr <= '0;
        else
            blink_ctr <= blink_ctr + 1'b1;
    end

    // ── LED outputs ─────────────────────────────────────────────
    // LED[2:0] = FSM state
    // LED[3]   = trading blink (active while TRADING)
    // LED[4]   = link_up
    // LED[5]   = risk_halt
    // LED[6]   = order_enable
    // LED[7]   = unused
    assign led[2:0] = fsm_state[2:0];
    assign led[3]   = (fsm_state == B_TRADING) & blink_ctr[24];
    assign led[4]   = link_up;
    assign led[5]   = risk_halt;
    assign led[6]   = order_enable;
    assign led[7]   = 1'b0;

    // ── RGB0: PnL indicator ─────────────────────────────────────
    // Green = profit (PnL > 0), Red = loss (PnL < 0), Off = flat
    always_comb begin
        if (total_pnl > 0)
            rgb0 = 3'b010;     // green
        else if (total_pnl < 0)
            rgb0 = 3'b100;     // red
        else
            rgb0 = 3'b000;     // off
    end

    // ── RGB1: risk/link status ──────────────────────────────────
    // Green = healthy (no halt, link up)
    // Yellow = link down but no halt
    // Red = risk halt
    always_comb begin
        if (risk_halt)
            rgb1 = 3'b100;     // red
        else if (!link_up)
            rgb1 = 3'b110;     // yellow (R+G)
        else
            rgb1 = 3'b010;     // green
    end

endmodule
