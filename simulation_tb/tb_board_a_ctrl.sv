`timescale 1ns / 1ps

module tb_board_a_ctrl();
    import hft_pkg::*;

    logic        clk, rst_n;
    logic [3:0]  btn;
    logic [7:0]  sw;
    logic        ctrl_start_pulse, ctrl_stop_pulse, ctrl_reset_pulse;
    regime_e     regime_sw;
    logic        sw_override;
    logic        running;
    regime_e     active_regime;
    logic        link_up, link_error;
    logic [7:0]  led;
    logic [2:0]  rgb0, rgb1;

    integer err_cnt = 0;

    always #5 clk = ~clk;

    board_a_ctrl #(.BTN_DEB_W(1)) dut (
        .clk(clk), .rst_n(rst_n),
        .btn(btn), .sw(sw),
        .ctrl_start_pulse(ctrl_start_pulse),
        .ctrl_stop_pulse(ctrl_stop_pulse),
        .ctrl_reset_pulse(ctrl_reset_pulse),
        .regime_sw(regime_sw), .sw_override(sw_override),
        .running(running), .active_regime(active_regime),
        .link_up(link_up), .link_error(link_error),
        .led(led), .rgb0(rgb0), .rgb1(rgb1)
    );

    initial begin
        clk = 0; rst_n = 0;
        btn = 4'b0000; sw = 8'h00;
        running = 0; active_regime = REGIME_CALM;
        link_up = 0; link_error = 0;

        #20; rst_n = 1; @(posedge clk);

        // Test 1: btn[0] press -> ctrl_start_pulse
        btn[0] = 1;
        repeat(4) @(posedge clk); #1;
        if (ctrl_start_pulse !== 1'b1) begin
            $display("FAIL: ctrl_start_pulse=%b, expected 1", ctrl_start_pulse);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: ctrl_start_pulse fired");
        btn[0] = 0;
        repeat(5) @(posedge clk);

        // Test 2: btn[1] press -> ctrl_stop_pulse
        btn[1] = 1;
        repeat(4) @(posedge clk); #1;
        if (ctrl_stop_pulse !== 1'b1) begin
            $display("FAIL: ctrl_stop_pulse=%b, expected 1", ctrl_stop_pulse);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: ctrl_stop_pulse fired");
        btn[1] = 0;
        repeat(5) @(posedge clk);

        // Test 3: sw[1:0] decodes regime
        sw[1:0] = REGIME_VOLATILE;
        @(posedge clk); #1;
        if (regime_sw !== REGIME_VOLATILE) begin
            $display("FAIL: regime_sw=%b, expected VOLATILE", regime_sw);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: regime_sw = VOLATILE");

        // Test 4: LED reflects running status
        running = 1; active_regime = REGIME_CALM;
        @(posedge clk); #1;
        if (led[2] !== 1'b1) begin
            $display("FAIL: led[2]=%b, expected 1 (running)", led[2]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: led[2]=1 when running");

        if (led[1:0] !== 2'b00) begin
            $display("FAIL: led[1:0]=%b, expected 00 (CALM)", led[1:0]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: led[1:0]=00 for REGIME_CALM");

        // Test 5: RGB1 reflects link status
        link_up = 0; link_error = 0;
        @(posedge clk); #1;
        if (rgb1 !== 3'b100) begin
            $display("FAIL: rgb1=%b, expected 100 (link down=red)", rgb1);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: rgb1=100 (link down)");

        link_up = 1; link_error = 0;
        @(posedge clk); #1;
        if (rgb1 !== 3'b010) begin
            $display("FAIL: rgb1=%b, expected 010 (link ok=green)", rgb1);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: rgb1=010 (link ok)");

        // ----------------------------------------------------------------
        // Test 6: btn[2] press -> ctrl_reset_pulse
        // ----------------------------------------------------------------
        btn[2] = 1;
        repeat(4) @(posedge clk); #1;
        if (ctrl_reset_pulse !== 1'b1) begin
            $display("FAIL: ctrl_reset_pulse=%b, expected 1", ctrl_reset_pulse);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: ctrl_reset_pulse fired");
        btn[2] = 0;
        repeat(5) @(posedge clk);

        // ----------------------------------------------------------------
        // Test 7: LED[1:0] reflects all four regimes
        //   CALM=00, VOLATILE=01, BURST=10, ADVERSARIAL=11
        // ----------------------------------------------------------------
        running = 1;

        active_regime = REGIME_CALM;
        @(posedge clk); #1;
        if (led[1:0] !== 2'b00) begin
            $display("FAIL: led[1:0]=%b for CALM, expected 00", led[1:0]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: led[1:0]=00 for REGIME_CALM");

        active_regime = REGIME_VOLATILE;
        @(posedge clk); #1;
        if (led[1:0] !== 2'b01) begin
            $display("FAIL: led[1:0]=%b for VOLATILE, expected 01", led[1:0]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: led[1:0]=01 for REGIME_VOLATILE");

        active_regime = REGIME_BURST;
        @(posedge clk); #1;
        if (led[1:0] !== 2'b10) begin
            $display("FAIL: led[1:0]=%b for BURST, expected 10", led[1:0]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: led[1:0]=10 for REGIME_BURST");

        active_regime = REGIME_ADVERSARIAL;
        @(posedge clk); #1;
        if (led[1:0] !== 2'b11) begin
            $display("FAIL: led[1:0]=%b for ADVERSARIAL, expected 11", led[1:0]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: led[1:0]=11 for REGIME_ADVERSARIAL");

        // ----------------------------------------------------------------
        // Test 8: RGB0 color per regime
        //   CALM       = green   = 3'b010
        //   VOLATILE   = yellow  = 3'b110
        //   BURST      = red     = 3'b100
        //   ADVERSARIAL = magenta = 3'b101
        // ----------------------------------------------------------------
        active_regime = REGIME_CALM;
        @(posedge clk); #1;
        if (rgb0 !== 3'b010) begin
            $display("FAIL: rgb0=%b for CALM, expected 010 (green)", rgb0);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: rgb0=010 (green) for REGIME_CALM");

        active_regime = REGIME_VOLATILE;
        @(posedge clk); #1;
        if (rgb0 !== 3'b110) begin
            $display("FAIL: rgb0=%b for VOLATILE, expected 110 (yellow)", rgb0);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: rgb0=110 (yellow) for REGIME_VOLATILE");

        active_regime = REGIME_BURST;
        @(posedge clk); #1;
        if (rgb0 !== 3'b100) begin
            $display("FAIL: rgb0=%b for BURST, expected 100 (red)", rgb0);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: rgb0=100 (red) for REGIME_BURST");

        active_regime = REGIME_ADVERSARIAL;
        @(posedge clk); #1;
        if (rgb0 !== 3'b101) begin
            $display("FAIL: rgb0=%b for ADVERSARIAL, expected 101 (magenta)", rgb0);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: rgb0=101 (magenta) for REGIME_ADVERSARIAL");

        // ----------------------------------------------------------------
        // Test 9: sw_override = sw[2]
        // ----------------------------------------------------------------
        sw[2] = 1'b0;
        @(posedge clk); #1;
        if (sw_override !== 1'b0) begin
            $display("FAIL: sw_override=%b with sw[2]=0, expected 0", sw_override);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: sw_override=0 when sw[2]=0");

        sw[2] = 1'b1;
        @(posedge clk); #1;
        if (sw_override !== 1'b1) begin
            $display("FAIL: sw_override=%b with sw[2]=1, expected 1", sw_override);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: sw_override=1 when sw[2]=1");

        // Summary
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
