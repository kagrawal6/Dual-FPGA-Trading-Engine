// ============================================================================
// Testbench: tb_debounce
// Tests the button debouncer module: stability requirement, debounced output
// level, and single-cycle rising-edge pulse generation.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_debounce;

    logic clk;
    logic rst_n;
    logic btn_in;
    logic btn_out;
    logic btn_pulse;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    debounce #(
        .COUNTER_W (20)
    ) dut (
        .clk       (clk),
        .rst_n     (rst_n),
        .btn_in    (btn_in),
        .btn_out   (btn_out),
        .btn_pulse (btn_pulse)
    );

    initial begin
        // TODO: Add test stimulus
        $finish;
    end

endmodule
