`timescale 1ns / 1ps

module tb_debounce();

    import hft_pkg::*;

    logic clk, rst_n, btn_in, btn_out, btn_pulse;
    integer err_cnt = 0;

    always #5 clk = ~clk;

    // COUNTER_W=2 → need 2^2+1 = 5 stable cycles to flip output
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

        // ---- T1: Reset clears output ----
        @(posedge clk); #1;
        if (btn_out !== 1'b0) begin
            $display("FAIL: T1 btn_out=%0b after reset, expected 0", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T1 btn_out=0 after reset");

        // ---- T2: Glitch rejection (3 clk < 5 needed) ----
        btn_in = 1;
        repeat(3) @(posedge clk);
        btn_in = 0;
        repeat(3) @(posedge clk); #1;
        if (btn_out !== 1'b0) begin
            $display("FAIL: T2 glitch not rejected, btn_out=%0b", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T2 short glitch rejected");

        // ---- T3: Clean press accepted (6 clk > 5 threshold) ----
        btn_in = 1;
        repeat(6) @(posedge clk); #1;
        if (btn_out !== 1'b1) begin
            $display("FAIL: T3 btn_out=%0b, expected 1", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T3 btn_out=1 after stable press");

        // ---- T4: btn_pulse fires on 0→1 edge, is single-cycle ----
        if (btn_pulse !== 1'b1) begin
            $display("FAIL: T4a btn_pulse=%0b, expected 1 on rising edge", btn_pulse);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T4a btn_pulse=1 on rising edge");

        @(posedge clk); #1;
        if (btn_pulse !== 1'b0) begin
            $display("FAIL: T4b btn_pulse=%0b, expected 0 (single-cycle)", btn_pulse);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T4b btn_pulse returns to 0");

        // ---- T5: Release — btn_out returns to 0 ----
        btn_in = 0;
        repeat(6) @(posedge clk); #1;
        if (btn_out !== 1'b0) begin
            $display("FAIL: T5 btn_out=%0b after release, expected 0", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T5 btn_out=0 after release");

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
