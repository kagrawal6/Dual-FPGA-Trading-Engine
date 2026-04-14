`timescale 1ns / 1ps

module tb_debounce();

    import hft_pkg::*;

    logic clk, rst_n, btn_in, btn_out, btn_pulse;
    integer err_cnt;

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
        clk = 0; rst_n = 0; btn_in = 0; err_cnt = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // ----------------------------------------------------------------
        // Test 1: Reset clears debounced output (btn_out = 0).
        // ----------------------------------------------------------------
        @(posedge clk); #1;
        if (btn_out !== 1'b0) begin
            $display("FAIL: btn_out=%0b after reset (wanted 0)", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: btn low after reset");

        // ----------------------------------------------------------------
        // Test 2: Glitch — only 3 clocks high; need 5 stable so output
        //         must stay 0.
        // ----------------------------------------------------------------
        btn_in = 1;
        repeat(3) @(posedge clk);
        btn_in = 0;
        repeat(3) @(posedge clk); #1;
        if (btn_out !== 1'b0) begin
            $display("FAIL: glitch got through, btn_out=%0b", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: short press ignored");

        // ----------------------------------------------------------------
        // Test 3: Stable press — 6 clocks high (>5 threshold) -> btn_out
        //         goes to 1.
        // ----------------------------------------------------------------
        btn_in = 1;
        repeat(6) @(posedge clk); #1;
        if (btn_out !== 1'b1) begin
            $display("FAIL: btn_out=%0b after long press", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: stable press works");

        // ----------------------------------------------------------------
        // Test 4: btn_pulse — one-cycle high on 0->1 of debounced output.
        // ----------------------------------------------------------------
        if (btn_pulse !== 1'b1) begin
            $display("FAIL: btn_pulse=%0b (wanted 1)", btn_pulse);
            err_cnt = err_cnt + 1;
        end else $display("PASS: pulse high");

        @(posedge clk); #1;
        if (btn_pulse !== 1'b0) begin
            $display("FAIL: btn_pulse stuck at %0b", btn_pulse);
            err_cnt = err_cnt + 1;
        end else $display("PASS: pulse dropped next cycle");

        // ----------------------------------------------------------------
        // Test 5: Release — hold low long enough -> btn_out returns to 0.
        // ----------------------------------------------------------------
        btn_in = 0;
        repeat(6) @(posedge clk); #1;
        if (btn_out !== 1'b0) begin
            $display("FAIL: btn_out=%0b after release", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: back to 0");

        // ----------------------------------------------------------------
        // Test 6: Double press — press, release fully, press again.
        //         Second press must also produce a pulse.
        // ----------------------------------------------------------------
        btn_in = 1;
        repeat(6) @(posedge clk); #1;
        if (btn_out !== 1'b1) begin
            $display("FAIL: first press of double-press, btn_out=%0b", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: double-press first press registered");

        btn_in = 0;
        repeat(6) @(posedge clk); #1;
        if (btn_out !== 1'b0) begin
            $display("FAIL: release between double-press, btn_out=%0b", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: double-press release OK");

        btn_in = 1;
        repeat(6) @(posedge clk); #1;
        if (btn_out !== 1'b1) begin
            $display("FAIL: second press of double-press, btn_out=%0b", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: double-press second press registered");

        if (btn_pulse !== 1'b1) begin
            $display("FAIL: no pulse on second press, btn_pulse=%0b", btn_pulse);
            err_cnt = err_cnt + 1;
        end else $display("PASS: pulse fired on second press");

        // Return to idle for next test
        btn_in = 0;
        repeat(6) @(posedge clk);

        // ----------------------------------------------------------------
        // Test 7: Reset during active bounce resets btn_out to 0.
        //         Start a press, then assert reset mid-bounce.
        // ----------------------------------------------------------------
        btn_in = 1;
        repeat(6) @(posedge clk); #1;
        if (btn_out !== 1'b1) begin
            $display("FAIL: btn_out not 1 before mid-bounce reset", btn_out);
            err_cnt = err_cnt + 1;
        end

        rst_n = 0;
        @(posedge clk); #1;
        if (btn_out !== 1'b0) begin
            $display("FAIL: btn_out=%0b after mid-bounce reset (wanted 0)", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: reset during active bounce clears btn_out");

        rst_n = 1;
        btn_in = 0;
        repeat(2) @(posedge clk);

        // ----------------------------------------------------------------
        // Test 8: Fast toggle — alternate btn_in 1/0 every cycle for 10
        //         cycles. btn_out should stay at its last stable state (0).
        // ----------------------------------------------------------------
        begin : fast_toggle_blk
            integer i;
            for (i = 0; i < 10; i = i + 1) begin
                btn_in = ~btn_in;
                @(posedge clk);
            end
        end
        btn_in = 0;
        #1;
        if (btn_out !== 1'b0) begin
            $display("FAIL: fast toggle changed btn_out to %0b (wanted 0)", btn_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: fast toggle did not change btn_out");

        // ----------------------------------------------------------------
        // Summary
        // ----------------------------------------------------------------
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
