// ============================================================================
// Testbench: tb_debounce
// Falling-edge no-pulse, reset during press, double-press, glitch rejection,
// and COUNTER_W=3 fast-parameter test.
// ============================================================================

`timescale 1ns / 1ps

module tb_debounce;

    localparam int CW = 4;
    localparam int STABLE = 1 << CW;  // 16

    logic clk, rst_n, btn_in, btn_out, btn_pulse;

    int pass_count = 0;
    int fail_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

    debounce #(.COUNTER_W(CW)) dut (
        .clk       (clk),
        .rst_n     (rst_n),
        .btn_in    (btn_in),
        .btn_out   (btn_out),
        .btn_pulse (btn_pulse)
    );

    // ── Fast debounce instance (COUNTER_W=3, 8 cycles) ──
    logic btn_in_f, btn_out_f, btn_pulse_f;
    debounce #(.COUNTER_W(3)) dut_fast (
        .clk       (clk),
        .rst_n     (rst_n),
        .btn_in    (btn_in_f),
        .btn_out   (btn_out_f),
        .btn_pulse (btn_pulse_f)
    );

    task automatic check(string msg, logic cond);
        if (cond) pass_count++;
        else begin
            $error("FAIL: %s", msg);
            fail_count++;
        end
    endtask

    initial begin
        $dumpfile("tb_debounce.vcd");
        $dumpvars(0, tb_debounce);
    end

    task automatic do_reset();
        rst_n = 1'b0;
        btn_in = 1'b0;
        btn_in_f = 1'b0;
        repeat (4) @(posedge clk);
        rst_n = 1'b1;
        @(posedge clk);
    endtask

    initial begin
        do_reset();

        // ─────────────────────────────────────────────────────
        // 1) Post-reset state
        // ─────────────────────────────────────────────────────
        $display("--- test_reset ---");
        check("reset: btn_out=0", btn_out == 1'b0);
        check("reset: btn_pulse=0", btn_pulse == 1'b0);

        // ─────────────────────────────────────────────────────
        // 2) Glitch rejection
        // ─────────────────────────────────────────────────────
        $display("--- test_glitch ---");
        for (int g = 0; g < 15; g++) begin
            btn_in = 1'b1;
            repeat (3) @(posedge clk);
            btn_in = 1'b0;
            repeat (3) @(posedge clk);
        end
        check("glitch: btn_out still 0", btn_out == 1'b0);

        // ─────────────────────────────────────────────────────
        // 3) Rising edge → single pulse
        // ─────────────────────────────────────────────────────
        $display("--- test_rising_edge ---");
        begin
            automatic int pulses = 0;
            btn_in = 1'b1;
            for (int i = 0; i < STABLE + 10; i++) begin
                @(posedge clk);
                if (btn_pulse) pulses++;
            end
            check("rising: exactly one pulse", pulses == 1);
            check("rising: btn_out=1", btn_out == 1'b1);
        end

        // ─────────────────────────────────────────────────────
        // 4) Held high → no extra pulses
        // ─────────────────────────────────────────────────────
        $display("--- test_held_high ---");
        begin
            automatic int pulses = 0;
            repeat (50) begin
                @(posedge clk);
                if (btn_pulse) pulses++;
            end
            check("held: no extra pulses", pulses == 0);
        end

        // ─────────────────────────────────────────────────────
        // 5) Falling edge → no pulse (only btn_out falls)
        // ─────────────────────────────────────────────────────
        $display("--- test_falling_edge ---");
        begin
            automatic int pulses = 0;
            btn_in = 1'b0;
            for (int i = 0; i < STABLE + 10; i++) begin
                @(posedge clk);
                if (btn_pulse) pulses++;
            end
            check("falling: no pulse on fall", pulses == 0);
            check("falling: btn_out=0", btn_out == 1'b0);
        end

        // ─────────────────────────────────────────────────────
        // 6) Double-press: 0→1→0→1 = exactly 2 pulses
        // ─────────────────────────────────────────────────────
        $display("--- test_double_press ---");
        begin
            automatic int pulses = 0;
            // First press
            btn_in = 1'b1;
            repeat (STABLE + 5) @(posedge clk);
            // Release
            btn_in = 1'b0;
            repeat (STABLE + 5) @(posedge clk);
            // Second press
            btn_in = 1'b1;
            repeat (STABLE + 5) @(posedge clk);
            btn_in = 1'b0;
            repeat (STABLE + 5) @(posedge clk);
            // Count pulses over entire window
            // Need to redo with manual tracking
        end
        // Redo with explicit tracking
        do_reset();
        begin
            automatic int total_pulses = 0;
            // Press 1
            btn_in = 1'b1;
            for (int i = 0; i < STABLE + 5; i++) begin
                @(posedge clk);
                if (btn_pulse) total_pulses++;
            end
            // Release
            btn_in = 1'b0;
            for (int i = 0; i < STABLE + 5; i++) begin
                @(posedge clk);
                if (btn_pulse) total_pulses++;
            end
            // Press 2
            btn_in = 1'b1;
            for (int i = 0; i < STABLE + 5; i++) begin
                @(posedge clk);
                if (btn_pulse) total_pulses++;
            end
            check("double-press: exactly 2 pulses", total_pulses == 2);
        end

        // ─────────────────────────────────────────────────────
        // 7) Reset during bounce
        // ─────────────────────────────────────────────────────
        $display("--- test_reset_during_bounce ---");
        btn_in = 1'b1;
        repeat (STABLE / 2) @(posedge clk);
        // Reset mid-bounce
        rst_n = 1'b0;
        repeat (4) @(posedge clk);
        rst_n = 1'b1;
        @(posedge clk);
        check("reset during bounce: btn_out=0", btn_out == 1'b0);
        check("reset during bounce: btn_pulse=0", btn_pulse == 1'b0);
        btn_in = 1'b0;
        repeat (4) @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 8) Fast debounce (COUNTER_W=3, 8-cycle window)
        // ─────────────────────────────────────────────────────
        $display("--- test_fast_debounce ---");
        begin
            automatic int pulses = 0;
            btn_in_f = 1'b1;
            for (int i = 0; i < 20; i++) begin
                @(posedge clk);
                if (btn_pulse_f) pulses++;
            end
            check("fast: exactly one pulse", pulses == 1);
            check("fast: btn_out_f=1", btn_out_f == 1'b1);
        end
        btn_in_f = 1'b0;
        repeat (20) @(posedge clk);

        // ─────────────────────────────────────────────────────
        // Summary
        // ─────────────────────────────────────────────────────
        $display("\n===================================");
        if (fail_count == 0)
            $display("tb_debounce: PASS (%0d checks passed)", pass_count);
        else begin
            $display("tb_debounce: FAIL (%0d passed, %0d failed)", pass_count, fail_count);
            $fatal;
        end
        $display("===================================");
        $finish;
    end

endmodule
