`timescale 1ns / 1ps

module tb_link_loopback();

    import hft_pkg::*;

    localparam FRAME_W = 128;
    localparam DATA_W  = 4;

    logic                 clk, rst_n;
    logic [FRAME_W-1:0]  tx_frame_in;
    logic                 tx_frame_in_valid, tx_frame_in_ready;
    logic [DATA_W-1:0]   pmod_data;
    logic                 pmod_valid;
    logic                 local_ready;
    logic [FRAME_W-1:0]  rx_frame_out;
    logic                 rx_frame_out_valid;
    logic                 rx_link_up;
    logic [31:0]          rx_error_count;
    integer err_cnt = 0;

    always #5 clk = ~clk;

    link_tx #(.FRAME_W(FRAME_W), .DATA_W(DATA_W)) u_tx (
        .clk           (clk),
        .rst_n         (rst_n),
        .frame_in      (tx_frame_in),
        .frame_in_valid(tx_frame_in_valid),
        .frame_in_ready(tx_frame_in_ready),
        .pmod_data     (pmod_data),
        .pmod_valid    (pmod_valid),
        .remote_ready  (local_ready)       // RX backpressure → TX
    );

    link_rx #(.FRAME_W(FRAME_W), .DATA_W(DATA_W)) u_rx (
        .clk            (clk),
        .rst_n          (rst_n),
        .counter_clr    (1'b0),
        .pmod_data      (pmod_data),
        .pmod_valid     (pmod_valid),
        .local_ready    (local_ready),
        .frame_out      (rx_frame_out),
        .frame_out_valid(rx_frame_out_valid),
        .link_up        (rx_link_up),
        .error_count    (rx_error_count)
    );

    localparam [FRAME_W-1:0] TEST_FRAME = 128'h1234_5678_9ABC_DEF0_FEDC_BA98_7654_3210;

    initial begin
        clk = 0; rst_n = 0;
        tx_frame_in = '0; tx_frame_in_valid = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // Let remote_ready sync through TX's 2-FF chain
        repeat(5) @(posedge clk);

        // ---- T1: Send a QUOTE frame through TX → RX ----
        tx_frame_in = TEST_FRAME;
        tx_frame_in_valid = 1;
        @(posedge clk);
        tx_frame_in_valid = 0;

        // Wait for TX serialization + RX reassembly (~70 clk)
        repeat(100) @(posedge clk); #1;

        // ---- T2: RX frame matches TX frame ----
        if (rx_frame_out !== TEST_FRAME) begin
            $display("FAIL: T2 rx_frame_out=%h", rx_frame_out);
            $display("       expected      =%h", TEST_FRAME);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T2 loopback frame matches");

        // ---- T3: link_up asserted ----
        if (rx_link_up !== 1'b1) begin
            $display("FAIL: T3 link_up=%0b, expected 1", rx_link_up);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T3 link_up=1");

        // ---- T4: No framing errors ----
        if (rx_error_count !== 32'h0) begin
            $display("FAIL: T4 error_count=%0d", rx_error_count);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T4 error_count=0");

        // ---- T5: Send a second frame (ORDER type) ----
        repeat(5) @(posedge clk);
        tx_frame_in = 128'h2111_1111_1111_1111_1111_1111_1111_1111;
        tx_frame_in_valid = 1;
        @(posedge clk);
        tx_frame_in_valid = 0;
        repeat(100) @(posedge clk); #1;

        if (rx_frame_out !== 128'h2111_1111_1111_1111_1111_1111_1111_1111) begin
            $display("FAIL: T5 second frame mismatch, got %h", rx_frame_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS: T5 second frame (ORDER) loopback OK");

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
