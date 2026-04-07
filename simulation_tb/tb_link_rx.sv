`timescale 1ns / 1ps

module tb_link_rx();

    import hft_pkg::*;

    localparam FRAME_W = 128;
    localparam DATA_W  = 4;

    logic                 clk, rst_n, counter_clr;
    logic [DATA_W-1:0]   pmod_data;
    logic                 pmod_valid;
    logic                 local_ready;
    logic [FRAME_W-1:0]  frame_out;
    logic                 frame_out_valid;
    logic                 link_up;
    logic [31:0]          error_count;
    integer err_cnt = 0;
    integer i;

    always #5 clk = ~clk;

    link_rx #(.FRAME_W(FRAME_W), .DATA_W(DATA_W)) dut (
        .clk            (clk),
        .rst_n          (rst_n),
        .counter_clr    (counter_clr),
        .pmod_data      (pmod_data),
        .pmod_valid     (pmod_valid),
        .local_ready    (local_ready),
        .frame_out      (frame_out),
        .frame_out_valid(frame_out_valid),
        .link_up        (link_up),
        .error_count    (error_count)
    );

    // msg_type = 4'h1 (QUOTE) so RX accepts it
    localparam [FRAME_W-1:0] TEST_FRAME = 128'h1234_5678_9ABC_DEF0_FEDC_BA98_7654_3210;

    initial begin
        clk = 0; rst_n = 0; counter_clr = 0;
        pmod_data = '0; pmod_valid = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // Before any traffic: frame_out_valid should be 0.
        @(posedge clk); #1;
        if (frame_out_valid !== 1'b0) begin
            $display("FAIL: idle frame_out_valid=%0b (expected 0)", frame_out_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS: no frame pulse in idle");

        // Drive 32 nibbles, 2 clk per nibble (same timing as link_tx).
        // RX has 2-FF sync, so data arrives 2 clocks late; hold each nibble 2 clk
        repeat(2) @(posedge clk);
        pmod_valid = 1;
        for (i = 0; i < 32; i = i + 1) begin
            pmod_data = TEST_FRAME[127 - i*4 -: 4];
            @(posedge clk); @(posedge clk);
        end
        pmod_valid = 0;

        // Wait for frame assembly to complete through 2-FF pipeline
        repeat(10) @(posedge clk); #1;

        if (frame_out !== TEST_FRAME) begin
            $display("FAIL: frame_out=%h", frame_out);
            $display("       expected =%h", TEST_FRAME);
            err_cnt = err_cnt + 1;
        end else $display("PASS: frame_out matches TEST_FRAME");

        // Valid QUOTE frame assembled -> link_up should be 1.
        if (link_up !== 1'b1) begin
            $display("FAIL: link_up=%0b (expected 1)", link_up);
            err_cnt = err_cnt + 1;
        end else $display("PASS: link_up after good frame");

        // No framing/msg errors on this path -> error_count stays 0.
        if (error_count !== 32'h0) begin
            $display("FAIL: error_count=%0d (expected 0)", error_count);
            err_cnt = err_cnt + 1;
        end else $display("PASS: error_count=0");

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
