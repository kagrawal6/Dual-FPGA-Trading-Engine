// ============================================================================
// Testbench: tb_debounce
// Verifies stability filtering and single-cycle rising-edge pulse.
// Uses COUNTER_W=4 → 16-cycle stability window (160 ns @ 100 MHz) for speed.
// ============================================================================

`timescale 1ns / 1ps

module tb_debounce;

    localparam int CW = 4;
    localparam int STABLE = 1 << CW;  // 16

    logic clk;
    logic rst_n;
    logic btn_in;
    logic btn_out;
    logic btn_pulse;

    int err_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

    debounce #(.COUNTER_W(CW)) dut (
        .clk       (clk),
        .rst_n     (rst_n),
        .btn_in    (btn_in),
        .btn_out   (btn_out),
        .btn_pulse (btn_pulse)
    );

    task automatic check(string msg, logic pass);
        if (!pass) begin
            $error("FAIL: %s", msg);
            err_count++;
        end
    endtask

    initial begin
        $dumpfile("tb_debounce.vcd");
        $dumpvars(0, tb_debounce);
    end

    task automatic wait_reset();
        rst_n  = 1'b0;
        btn_in = 1'b0;
        repeat (4) @(posedge clk);
        rst_n = 1'b1;
        @(posedge clk);
    endtask

    initial begin
        wait_reset();
        check("After reset, btn_out=0", btn_out == 1'b0);
        check("After reset, btn_pulse=0", btn_pulse == 1'b0);

        // Rapid glitches: never accumulate STABLE cycles of mismatch
        for (int g = 0; g < 12; g++) begin
            btn_in = 1'b1;
            repeat (3) @(posedge clk);
            btn_in = 1'b0;
            repeat (3) @(posedge clk);
        end
        check("After glitches, btn_out still 0", btn_out == 1'b0);

        // Stable high long enough → btn_out rises
        btn_in = 1'b1;
        repeat (STABLE + 2) @(posedge clk);
        check("Stable high: btn_out should be 1", btn_out == 1'b1);

        // Stable low → btn_out falls (no falling-edge pulse on btn_pulse)
        btn_in = 1'b0;
        repeat (STABLE + 2) @(posedge clk);
        check("Stable low: btn_out should be 0", btn_out == 1'b0);

        // Exactly one pulse on next 0→1 debounced transition
        begin
            automatic int pulses = 0;
            btn_in = 1'b1;
            for (int i = 0; i < STABLE + 10; i++) begin
                @(posedge clk);
                if (btn_pulse) pulses++;
            end
            check("Rising debounce: exactly one btn_pulse", pulses == 1);
        end

        // Held high: no extra pulses
        begin
            automatic int pulses = 0;
            repeat (40) begin
                @(posedge clk);
                if (btn_pulse) pulses++;
            end
            check("Held high: no extra pulses", pulses == 0);
        end

        if (err_count == 0)
            $display("tb_debounce: PASS (all checks passed, VCD: tb_debounce.vcd)");
        else
            $display("tb_debounce: FAIL (%0d errors)", err_count);

        $finish;
    end

endmodule
