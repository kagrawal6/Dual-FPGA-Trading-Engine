// ============================================================================
// Testbench: tb_board_a_ctrl
// All 4 buttons, all 4 regime switch values, sw_override, LED encoding for
// all states, RGB0 all regimes, RGB1 all link states, blink LED, debounce
// rejection.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_a_ctrl;

    localparam int CW = 5;
    localparam int STABLE = 1 << CW; // 32

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

    int pass_count = 0;
    int fail_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    board_a_ctrl #(.BTN_DEB_W(CW)) dut (
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

    task automatic check(string msg, logic cond);
        if (cond) pass_count++;
        else begin
            $error("FAIL: %s", msg);
            fail_count++;
        end
    endtask

    // Press and release a single button, count pulses on the output
    task automatic press_button(input int btn_idx, output int pulses_start, output int pulses_stop, output int pulses_reset);
        pulses_start = 0;
        pulses_stop  = 0;
        pulses_reset = 0;
        btn = 4'b0;
        repeat (STABLE + 2) @(posedge clk); // ensure clean low
        btn[btn_idx] = 1'b1;
        for (int i = 0; i < STABLE + 10; i++) begin
            @(posedge clk);
            if (ctrl_start_pulse) pulses_start++;
            if (ctrl_stop_pulse)  pulses_stop++;
            if (ctrl_reset_pulse) pulses_reset++;
        end
        btn[btn_idx] = 1'b0;
        repeat (STABLE + 5) @(posedge clk);
    endtask

    initial begin
        int ps, pp, pr;

        $dumpfile("tb_board_a_ctrl.vcd");
        $dumpvars(0, tb_board_a_ctrl);

        btn           = 4'b0;
        sw            = 8'h00;
        running       = 1'b0;
        active_regime = REGIME_CALM;
        link_up       = 1'b0;
        link_error    = 1'b0;

        @(posedge clk);
        wait (rst_n === 1'b1);
        repeat (4) @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 1) All 4 regime switch values
        // ─────────────────────────────────────────────────────
        $display("--- test_regime_switch ---");
        sw = 8'h00; @(posedge clk);
        check("regime CALM", regime_sw == REGIME_CALM);
        sw = 8'h01; @(posedge clk);
        check("regime VOLATILE", regime_sw == REGIME_VOLATILE);
        sw = 8'h02; @(posedge clk);
        check("regime BURST", regime_sw == REGIME_BURST);
        sw = 8'h03; @(posedge clk);
        check("regime ADVERSARIAL", regime_sw == REGIME_ADVERSARIAL);

        // ─────────────────────────────────────────────────────
        // 2) sw_override
        // ─────────────────────────────────────────────────────
        $display("--- test_sw_override ---");
        sw = 8'h04; @(posedge clk);
        check("sw_override=1", sw_override == 1'b1);
        sw = 8'h00; @(posedge clk);
        check("sw_override=0", sw_override == 1'b0);

        // ─────────────────────────────────────────────────────
        // 3) All 4 buttons: BTN0=start, BTN1=stop, BTN2=reset
        // ─────────────────────────────────────────────────────
        $display("--- test_all_buttons ---");
        // BTN0 → start
        press_button(0, ps, pp, pr);
        check("BTN0: 1 start pulse", ps == 1);
        check("BTN0: 0 stop pulses", pp == 0);
        check("BTN0: 0 reset pulses", pr == 0);

        // BTN1 → stop
        press_button(1, ps, pp, pr);
        check("BTN1: 0 start pulses", ps == 0);
        check("BTN1: 1 stop pulse", pp == 1);
        check("BTN1: 0 reset pulses", pr == 0);

        // BTN2 → reset
        press_button(2, ps, pp, pr);
        check("BTN2: 0 start pulses", ps == 0);
        check("BTN2: 0 stop pulses", pp == 0);
        check("BTN2: 1 reset pulse", pr == 1);

        // BTN3 → unused (no pulses)
        press_button(3, ps, pp, pr);
        check("BTN3: 0 start", ps == 0);
        check("BTN3: 0 stop", pp == 0);
        check("BTN3: 0 reset", pr == 0);

        // ─────────────────────────────────────────────────────
        // 4) LED encoding: idle
        // ─────────────────────────────────────────────────────
        $display("--- test_led_idle ---");
        sw = 8'h00;
        running = 1'b0;
        active_regime = REGIME_CALM;
        link_up = 1'b0;
        link_error = 1'b0;
        @(posedge clk);
        check("idle: led[1:0]=CALM", led[1:0] == 2'b00);
        check("idle: led[2]=0 (not running)", led[2] == 1'b0);
        check("idle: led[4]=0 (no link)", led[4] == 1'b0);
        check("idle: led[5]=0 (no error)", led[5] == 1'b0);

        // ─────────────────────────────────────────────────────
        // 5) LED encoding: running + each regime
        // ─────────────────────────────────────────────────────
        $display("--- test_led_running ---");
        running = 1'b1;
        link_up = 1'b1;

        active_regime = REGIME_CALM;
        @(posedge clk);
        check("run CALM: led[1:0]=00", led[1:0] == 2'b00);
        check("run: led[2]=1", led[2] == 1'b1);
        check("run: led[4]=1", led[4] == 1'b1);

        active_regime = REGIME_VOLATILE;
        @(posedge clk);
        check("run VOLATILE: led[1:0]=01", led[1:0] == 2'b01);

        active_regime = REGIME_BURST;
        @(posedge clk);
        check("run BURST: led[1:0]=10", led[1:0] == 2'b10);

        active_regime = REGIME_ADVERSARIAL;
        @(posedge clk);
        check("run ADVERSARIAL: led[1:0]=11", led[1:0] == 2'b11);

        // ─────────────────────────────────────────────────────
        // 6) RGB0: regime colors
        // ─────────────────────────────────────────────────────
        $display("--- test_rgb0 ---");
        active_regime = REGIME_CALM;        @(posedge clk);
        check("rgb0 CALM=010",        rgb0 == 3'b010);
        active_regime = REGIME_VOLATILE;    @(posedge clk);
        check("rgb0 VOLATILE=110",    rgb0 == 3'b110);
        active_regime = REGIME_BURST;       @(posedge clk);
        check("rgb0 BURST=100",       rgb0 == 3'b100);
        active_regime = REGIME_ADVERSARIAL; @(posedge clk);
        check("rgb0 ADVERSARIAL=101", rgb0 == 3'b101);

        // ─────────────────────────────────────────────────────
        // 7) RGB1: link states
        // ─────────────────────────────────────────────────────
        $display("--- test_rgb1 ---");
        link_up = 1'b0; link_error = 1'b0; @(posedge clk);
        check("rgb1 down=100", rgb1 == 3'b100);

        link_up = 1'b1; link_error = 1'b0; @(posedge clk);
        check("rgb1 ok=010", rgb1 == 3'b010);

        link_up = 1'b1; link_error = 1'b1; @(posedge clk);
        check("rgb1 error=110", rgb1 == 3'b110);

        link_up = 1'b0; link_error = 1'b1; @(posedge clk);
        check("rgb1 down+err=100", rgb1 == 3'b100);

        // ─────────────────────────────────────────────────────
        // 8) Blink LED: led[3] toggles (sample blink_ctr[24])
        // ─────────────────────────────────────────────────────
        $display("--- test_blink ---");
        running = 1'b1;
        // The blink counter wraps at 2^25 cycles. We can't run that long,
        // but we can verify led[3] = running & blink_ctr[24].
        // After reset, blink_ctr starts at 0 → led[3]=0 initially.
        @(posedge clk);
        // led[3] should be running & blink_ctr[24]; at early cycles, blink_ctr[24]=0
        check("blink: led[3] starts low", led[3] == 1'b0);
        // When not running, led[3] should be 0
        running = 1'b0;
        @(posedge clk);
        check("blink: not running → led[3]=0", led[3] == 1'b0);

        // ─────────────────────────────────────────────────────
        // 9) Debounce rejection: rapid toggling
        // ─────────────────────────────────────────────────────
        $display("--- test_debounce_rejection ---");
        begin
            int spurious = 0;
            btn = 4'b0;
            repeat (STABLE + 2) @(posedge clk);
            for (int g = 0; g < 20; g++) begin
                btn[0] = 1'b1;
                repeat (2) @(posedge clk);
                btn[0] = 1'b0;
                repeat (2) @(posedge clk);
                if (ctrl_start_pulse) spurious++;
            end
            check("debounce: no spurious pulses", spurious == 0);
        end

        // ─────────────────────────────────────────────────────
        // Summary
        // ─────────────────────────────────────────────────────
        $display("\n===================================");
        if (fail_count == 0)
            $display("tb_board_a_ctrl: PASS (%0d checks passed)", pass_count);
        else begin
            $display("tb_board_a_ctrl: FAIL (%0d passed, %0d failed)", pass_count, fail_count);
            $fatal;
        end
        $display("===================================");
        $finish;
    end

endmodule
