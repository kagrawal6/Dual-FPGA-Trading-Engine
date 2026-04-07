`timescale 1ns / 1ps

module tb_debounce();

    import hft_pkg::*;

    logic clk, rst_n, btn_in, btn_out, btn_pulse;
    integer err_cnt = 0;

    always #5 clk = ~clk;

    // COUNTER_W=2 -> need 2^2+1 = 5 stable cycles to flip output
    debounce #(.COUNTER_W(2)) dut (
        .clk      (clk),
        .rst_n    (rst_n),
        .btn_in   (btn_in),
        .btn_out  (btn_out),
        .btn_pulse(btn_pulse)
    );

    initial begin
        clk = 0; rst_n = 0; btn_in = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // Reset clears debounced output (btn_out = 0).
        @(posedge clk); #1;
        if (btn_out !== 1'b0) begin
            $display("FAIL: btn_out=%0b after reset (wanted 0)", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("ok: btn low after reset");

        // Glitch: only 3 clocks high; need 5 stable so output must stay 0.
        btn_in = 1;
        repeat(3) @(posedge clk);
        btn_in = 0;
        repeat(3) @(posedge clk); #1;
        if (btn_out !== 1'b0) begin
            $display("FAIL: glitch got through, btn_out=%0b", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("ok: short press ignored");

        // Stable press: 6 clocks high (>5 threshold) -> btn_out goes to 1.
        btn_in = 1;
        repeat(6) @(posedge clk); #1;
        if (btn_out !== 1'b1) begin
            $display("FAIL: btn_out=%0b after long press", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("ok: stable press works");

        // btn_pulse: one cycle high on 0->1 of debounced output.
        if (btn_pulse !== 1'b1) begin
            $display("FAIL: btn_pulse=%0b (wanted 1)", btn_pulse);
            err_cnt = err_cnt + 1;
        end else $display("ok: pulse high");

        @(posedge clk); #1;
        if (btn_pulse !== 1'b0) begin
            $display("FAIL: btn_pulse stuck at %0b", btn_pulse);
            err_cnt = err_cnt + 1;
        end else $display("ok: pulse dropped next cycle");

        // Release: hold low long enough -> btn_out returns to 0.
        btn_in = 0;
        repeat(6) @(posedge clk); #1;
        if (btn_out !== 1'b0) begin
            $display("FAIL: btn_out=%0b after release", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("ok: back to 0");

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
