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

        // Idle: no frame in flight -> pmod_valid should stay 0.
        @(posedge clk); #1;
        if (pmod_valid !== 1'b0) begin
            $display("FAIL: idle pmod_valid=%0b (expected 0)", pmod_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS: idle pmod_valid=0");

        // Enable remote_ready, let 2-FF sync settle
        remote_ready = 1;
        repeat(3) @(posedge clk);

        // Send one 128b frame; check each of 32 nibbles MSB-first vs TEST_FRAME (golden).
        frame_in = TEST_FRAME;
        frame_in_valid = 1;
        @(posedge clk);
        frame_in_valid = 0;

        // TX now in ST_SEND; each nibble held for 2 clocks
        for (i = 0; i < 32; i = i + 1) begin
            @(posedge clk); #1;
            exp_nib = TEST_FRAME[127 - i*4 -: 4];
            if (pmod_data !== exp_nib) begin
                $display("FAIL: nibble[%0d] got %h expected %h",
                         i, pmod_data, exp_nib);
                err_cnt = err_cnt + 1;
            end
            @(posedge clk);
        end
        $display("done nibbles, err_cnt=%0d", err_cnt);

        // After last nibble, pmod_valid must drop back to 0.
        @(posedge clk); #1;
        if (pmod_valid !== 1'b0) begin
            $display("FAIL: after TX pmod_valid=%0b (expected 0)", pmod_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS: pmod_valid low after packet");

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
