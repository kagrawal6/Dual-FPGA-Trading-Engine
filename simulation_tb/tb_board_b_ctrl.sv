`timescale 1ns / 1ps
import hft_pkg::*;

module tb_board_b_ctrl();

    logic       clk = 0;
    logic       rst_n;
    logic [3:0] btn;
    logic [7:0] sw;

    logic       ctrl_start_pulse, ctrl_stop_pulse, ctrl_reset_pulse;
    logic       trading_enable;
    strategy_e  strategy_sw;
    logic       sw_strategy_override;

    b_state_e   fsm_state;
    logic       order_enable;
    logic       risk_halt;
    logic       link_up;
    sprice_t    total_pnl;

    logic [7:0] led;
    logic [2:0] rgb0, rgb1;

    integer err_cnt = 0;

    always #5 clk = ~clk;

    board_b_ctrl #(.BTN_DEB_W(2)) dut (
        .clk(clk), .rst_n(rst_n),
        .btn(btn), .sw(sw),
        .ctrl_start_pulse(ctrl_start_pulse),
        .ctrl_stop_pulse(ctrl_stop_pulse),
        .ctrl_reset_pulse(ctrl_reset_pulse),
        .trading_enable(trading_enable),
        .strategy_sw(strategy_sw),
        .sw_strategy_override(sw_strategy_override),
        .fsm_state(fsm_state), .order_enable(order_enable),
        .risk_halt(risk_halt), .link_up(link_up),
        .total_pnl(total_pnl),
        .led(led), .rgb0(rgb0), .rgb1(rgb1)
    );

    initial begin
        $display("=== tb_board_b_ctrl ===");
        rst_n = 0; btn = 0; sw = 0;
        fsm_state = B_IDLE; order_enable = 0;
        risk_halt = 0; link_up = 1; total_pnl = 0;
        #20; rst_n = 1; @(posedge clk);

        // Test 1: Switch mapping - sw[0]=trading_en, sw[2:1]=strategy, sw[3]=override
        $display("Test 1: Switch mapping");
        sw = 8'b0000_1001;
        @(posedge clk); #1;
        if (trading_enable == 1 && sw_strategy_override == 1 &&
            strategy_sw == STRAT_MEAN_REV)
            $display("  PASS: switches decoded correctly");
        else begin
            $display("  FAIL: en=%b ovr=%b strat=%0d",
                     trading_enable, sw_strategy_override, strategy_sw);
            err_cnt = err_cnt + 1;
        end

        // Test 2: Button 0 press -> start pulse (BTN_DEB_W=2 -> 4+1 stable cycles)
        $display("Test 2: Button start pulse");
        btn[0] = 1;
        begin
            integer saw_pulse = 0;
            repeat (10) begin
                @(posedge clk); #1;
                if (ctrl_start_pulse) saw_pulse = 1;
            end
            if (saw_pulse)
                $display("  PASS: ctrl_start_pulse detected");
            else begin
                $display("  FAIL: no start pulse after 10 cycles");
                err_cnt = err_cnt + 1;
            end
        end
        btn[0] = 0;
        repeat (10) @(posedge clk);

        // Test 3: LED reflects FSM state
        $display("Test 3: LED mirrors FSM state");
        fsm_state = B_TRADING; order_enable = 1;
        @(posedge clk); #1;
        if (led[2:0] == B_TRADING[2:0] && led[4] == 1 && led[6] == 1)
            $display("  PASS: led[2:0]=TRADING, led[4]=link_up, led[6]=order_en");
        else begin
            $display("  FAIL: led=0x%02X", led);
            err_cnt = err_cnt + 1;
        end

        // Test 4: RGB0 - positive PnL -> green
        $display("Test 4: RGB0 PnL color");
        total_pnl = 32'sd500;
        @(posedge clk); #1;
        if (rgb0 == 3'b010)
            $display("  PASS: rgb0=green for positive PnL");
        else begin
            $display("  FAIL: rgb0=%b, expected 010", rgb0);
            err_cnt = err_cnt + 1;
        end

        // Test 5: RGB1 - risk_halt -> red
        $display("Test 5: RGB1 risk halt");
        risk_halt = 1;
        @(posedge clk); #1;
        if (rgb1 == 3'b100)
            $display("  PASS: rgb1=red for risk halt");
        else begin
            $display("  FAIL: rgb1=%b, expected 100", rgb1);
            err_cnt = err_cnt + 1;
        end

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
