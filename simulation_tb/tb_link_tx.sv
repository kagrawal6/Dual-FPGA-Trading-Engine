`timescale 1ns / 1ps

module tb_link_tx();

    import hft_pkg::*;

    localparam FRAME_W = 128;
    localparam DATA_W  = 4;

    logic                 clk, rst_n;
    logic [FRAME_W-1:0]  frame_in;
    logic                 frame_in_valid, frame_in_ready;
    logic [DATA_W-1:0]   pmod_data;
    logic                 pmod_valid;
    logic                 remote_ready;
    integer err_cnt = 0;
    integer i;
    logic [3:0] exp_nib;

    always #5 clk = ~clk;

    link_tx #(.FRAME_W(FRAME_W), .DATA_W(DATA_W)) dut (
        .clk           (clk),
        .rst_n         (rst_n),
        .frame_in      (frame_in),
        .frame_in_valid(frame_in_valid),
        .frame_in_ready(frame_in_ready),
        .pmod_data     (pmod_data),
        .pmod_valid    (pmod_valid),
        .remote_ready  (remote_ready)
    );

    localparam [FRAME_W-1:0] TEST_FRAME = 128'h1234_5678_9ABC_DEF0_FEDC_BA98_7654_3210;

    initial begin
        clk = 0; rst_n = 0;
        frame_in = '0; frame_in_valid = 0; remote_ready = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // ---- T1: Idle — pmod_valid should be 0 ----
        @(posedge clk); #1;
        if (pmod_valid !== 1'b0) begin
            $display("FAIL: T1 pmod_valid=%0b in idle", pmod_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T1 pmod_valid=0 in idle");

        // Enable remote_ready, let 2-FF sync settle
        remote_ready = 1;
        repeat(3) @(posedge clk);

        // ---- T2: Send QUOTE frame, verify 32 MSB-first nibbles ----
        frame_in = TEST_FRAME;
        frame_in_valid = 1;
        @(posedge clk);
        frame_in_valid = 0;

        // TX now in ST_SEND; each nibble held for 2 clocks
        for (i = 0; i < 32; i = i + 1) begin
            @(posedge clk); #1;
            exp_nib = TEST_FRAME[127 - i*4 -: 4];
            if (pmod_data !== exp_nib) begin
                $display("FAIL: T2 nibble[%0d] pmod_data=%h, expected %h",
                         i, pmod_data, exp_nib);
                err_cnt = err_cnt + 1;
            end
            @(posedge clk);
        end
        $display("T2: checked 32 nibbles (%0d errors so far)", err_cnt);

        // ---- T3: After transmission, pmod_valid returns to 0 ----
        @(posedge clk); #1;
        if (pmod_valid !== 1'b0) begin
            $display("FAIL: T3 pmod_valid=%0b after TX done", pmod_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T3 pmod_valid=0 after TX complete");

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
