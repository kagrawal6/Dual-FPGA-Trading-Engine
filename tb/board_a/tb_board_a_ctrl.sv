// ============================================================================
// Testbench: tb_board_a_ctrl
// Debounced pulses and LED/RGB mapping (fast debounce via parameter).
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_a_ctrl;

    localparam int CW = 5;
    localparam int STABLE = 1 << CW;

    logic        clk;
    logic        rst_n;
    logic [3:0]  btn;
    logic [7:0]  sw;
    logic        ctrl_start_pulse;
    logic        ctrl_stop_pulse;
    logic        ctrl_reset_pulse;
    regime_e     regime_sw;
    logic        sw_override;
    logic        running;
    regime_e     active_regime;
    logic        link_up;
    logic        link_error;
    logic [7:0]  led;
    logic [2:0]  rgb0;
    logic [2:0]  rgb1;

    int err_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    board_a_ctrl #(
        .BTN_DEB_W(CW)
    ) dut (
        .clk              (clk),
        .rst_n            (rst_n),
        .btn              (btn),
        .sw               (sw),
        .ctrl_start_pulse (ctrl_start_pulse),
        .ctrl_stop_pulse  (ctrl_stop_pulse),
        .ctrl_reset_pulse (ctrl_reset_pulse),
        .regime_sw        (regime_sw),
        .sw_override      (sw_override),
        .running          (running),
        .active_regime    (active_regime),
        .link_up          (link_up),
        .link_error       (link_error),
        .led              (led),
        .rgb0             (rgb0),
        .rgb1             (rgb1)
    );

    task automatic check(string msg, logic pass);
        if (!pass) begin
            $error("FAIL: %s", msg);
            err_count++;
        end
    endtask

    initial begin
        btn           = 4'b0;
        sw            = 8'h00;
        running       = 1'b0;
        active_regime = REGIME_CALM;
        link_up       = 1'b0;
        link_error    = 1'b0;

        @(posedge clk);
        wait (rst_n === 1'b1);
        @(posedge clk);

        check("regime_sw from sw[1:0]", regime_sw == REGIME_CALM);
        sw = 8'h01;
        @(posedge clk);
        check("regime_sw VOLATILE", regime_sw == REGIME_VOLATILE);
        sw = 8'h04;
        @(posedge clk);
        check("sw_override", sw_override == 1'b1);

        sw            = 8'h00;
        running       = 1'b1;
        active_regime = REGIME_BURST;
        link_up       = 1'b1;
        link_error    = 1'b0;
        @(posedge clk);
        check("led[2] running", led[2] == 1'b1);
        check("led[4] link_up", led[4] == 1'b1);
        check("rgb0 BURST red", rgb0 == 3'b100);
        check("rgb1 ok green", rgb1 == 3'b010);

        link_error = 1'b1;
        @(posedge clk);
        check("rgb1 error yellow", rgb1 == 3'b110);

        link_error = 1'b0;
        link_up    = 1'b0;
        @(posedge clk);
        check("rgb1 down red", rgb1 == 3'b100);

        // start pulse on BTN0
        btn = 4'b0;
        repeat (STABLE + 2) @(posedge clk);
        btn[0] = 1'b1;
        begin
            automatic int p = 0;
            repeat (STABLE + 10) begin
                @(posedge clk);
                if (ctrl_start_pulse) p++;
            end
            check("one start pulse", p == 1);
        end

        if (err_count == 0)
            $display("tb_board_a_ctrl: PASS (all checks passed)");
        else
            $display("tb_board_a_ctrl: FAIL (%0d errors)", err_count);
        $finish;
    end

endmodule
