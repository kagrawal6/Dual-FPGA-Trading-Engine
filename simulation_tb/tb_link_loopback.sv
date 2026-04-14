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
    integer rx_valid_cnt = 0;
    integer saved_cnt;
    integer k;

    always #5 clk = ~clk;

    link_tx #(.FRAME_W(FRAME_W), .DATA_W(DATA_W)) u_tx (
        .clk           (clk),
        .rst_n         (rst_n),
        .frame_in      (tx_frame_in),
        .frame_in_valid(tx_frame_in_valid),
        .frame_in_ready(tx_frame_in_ready),
        .pmod_data     (pmod_data),
        .pmod_valid    (pmod_valid),
        .remote_ready  (local_ready)       // RX backpressure -> TX
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

    // Concurrent monitor: count rx_frame_out_valid pulses for stress test
    always @(posedge clk) if (rx_frame_out_valid) rx_valid_cnt = rx_valid_cnt + 1;

    // Test frames — one per message type
    localparam [FRAME_W-1:0] FRAME_QUOTE = 128'h1234_5678_9ABC_DEF0_FEDC_BA98_7654_3210;
    localparam [FRAME_W-1:0] FRAME_ORDER = 128'h2111_1111_1111_1111_1111_1111_1111_1111;
    localparam [FRAME_W-1:0] FRAME_FILL  = 128'h3999_8888_7777_6666_5555_4444_3333_2222;

    // Distinct data patterns (QUOTE msg_type so RX accepts them)
    localparam [FRAME_W-1:0] PAT_ZEROS = 128'h1000_0000_0000_0000_0000_0000_0000_0000;
    localparam [FRAME_W-1:0] PAT_ONES  = 128'h1FFF_FFFF_FFFF_FFFF_FFFF_FFFF_FFFF_FFFF;
    localparam [FRAME_W-1:0] PAT_ALT   = 128'h1555_5555_5555_5555_5555_5555_5555_5555;

    // Stress test array (5 distinct patterns)
    logic [FRAME_W-1:0] stress [0:4];

    initial begin
        stress[0] = FRAME_QUOTE;
        stress[1] = FRAME_ORDER;
        stress[2] = FRAME_FILL;
        stress[3] = PAT_ZEROS;
        stress[4] = PAT_ONES;

        clk = 0; rst_n = 0;
        tx_frame_in = '0; tx_frame_in_valid = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // Let remote_ready (local_ready) sync through TX's 2-FF chain
        repeat(5) @(posedge clk);

        // ============================================================
        // Test 1: QUOTE loopback — TX serializes, RX reassembles
        // ============================================================
        tx_frame_in       = FRAME_QUOTE;
        tx_frame_in_valid = 1;
        @(posedge clk);
        tx_frame_in_valid = 0;

        // Wait for TX serialization + RX reassembly (~70 clk)
        repeat(100) @(posedge clk); #1;

        if (rx_frame_out !== FRAME_QUOTE) begin
            $display("FAIL [QUOTE]: rx_frame_out=%h", rx_frame_out);
            $display("               expected    =%h", FRAME_QUOTE);
            err_cnt = err_cnt + 1;
        end else $display("PASS [QUOTE]: loopback frame matches TX");

        if (rx_link_up !== 1'b1) begin
            $display("FAIL [QUOTE]: link_up=%0b (expected 1)", rx_link_up);
            err_cnt = err_cnt + 1;
        end else $display("PASS [QUOTE]: link_up=1");

        if (rx_error_count !== 32'h0) begin
            $display("FAIL [QUOTE]: error_count=%0d", rx_error_count);
            err_cnt = err_cnt + 1;
        end else $display("PASS [QUOTE]: error_count=0");

        // ============================================================
        // Test 2: ORDER loopback (msg_type=2)
        // ============================================================
        repeat(5) @(posedge clk);
        tx_frame_in       = FRAME_ORDER;
        tx_frame_in_valid = 1;
        @(posedge clk);
        tx_frame_in_valid = 0;
        repeat(100) @(posedge clk); #1;

        if (rx_frame_out !== FRAME_ORDER) begin
            $display("FAIL [ORDER]: rx_frame_out=%h", rx_frame_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS [ORDER]: loopback OK");

        // ============================================================
        // Test 3: FILL loopback (msg_type=3)
        // ============================================================
        repeat(5) @(posedge clk);
        tx_frame_in       = FRAME_FILL;
        tx_frame_in_valid = 1;
        @(posedge clk);
        tx_frame_in_valid = 0;
        repeat(100) @(posedge clk); #1;

        if (rx_frame_out !== FRAME_FILL) begin
            $display("FAIL [FILL]: rx_frame_out=%h", rx_frame_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS [FILL]: loopback OK");

        // ============================================================
        // Test 4: Distinct data patterns — all-zeros, all-ones,
        //         and alternating-bits payloads (exercises shift path)
        // ============================================================

        // All-zeros payload
        repeat(5) @(posedge clk);
        tx_frame_in       = PAT_ZEROS;
        tx_frame_in_valid = 1;
        @(posedge clk);
        tx_frame_in_valid = 0;
        repeat(100) @(posedge clk); #1;

        if (rx_frame_out !== PAT_ZEROS) begin
            $display("FAIL [zeros]: rx_frame_out=%h", rx_frame_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS [zeros]: all-zeros payload OK");

        // All-ones payload
        repeat(5) @(posedge clk);
        tx_frame_in       = PAT_ONES;
        tx_frame_in_valid = 1;
        @(posedge clk);
        tx_frame_in_valid = 0;
        repeat(100) @(posedge clk); #1;

        if (rx_frame_out !== PAT_ONES) begin
            $display("FAIL [ones]: rx_frame_out=%h", rx_frame_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS [ones]: all-ones payload OK");

        // Alternating-bits payload
        repeat(5) @(posedge clk);
        tx_frame_in       = PAT_ALT;
        tx_frame_in_valid = 1;
        @(posedge clk);
        tx_frame_in_valid = 0;
        repeat(100) @(posedge clk); #1;

        if (rx_frame_out !== PAT_ALT) begin
            $display("FAIL [alt]: rx_frame_out=%h", rx_frame_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS [alt]: alternating-bits payload OK");

        // ============================================================
        // Test 5: Back-to-back stress — send 5 frames in rapid
        //         sequence, verify all 5 arrive via pulse counter.
        //         TX waits for frame_in_ready (which requires RX to
        //         finish assembling) before sending each frame.
        // ============================================================
        saved_cnt = rx_valid_cnt;

        repeat(5) @(posedge clk);
        for (k = 0; k < 5; k = k + 1) begin
            tx_frame_in       = stress[k];
            tx_frame_in_valid = 1;
            @(posedge clk);
            tx_frame_in_valid = 0;
            wait (tx_frame_in_ready === 1'b1);
            repeat(50) @(posedge clk);
        end

        // Wait for last frame to propagate through RX pipeline
        repeat(200) @(posedge clk); #1;

        if ((rx_valid_cnt - saved_cnt) !== 5) begin
            $display("FAIL [stress]: expected 5 valid pulses, got %0d",
                     rx_valid_cnt - saved_cnt);
            err_cnt = err_cnt + 1;
        end else $display("PASS [stress]: all 5 frames received");

        if (rx_error_count !== 32'h0) begin
            $display("FAIL [stress]: error_count=%0d (expected 0)", rx_error_count);
            err_cnt = err_cnt + 1;
        end else $display("PASS [stress]: no errors during stress test");

        // ============================================================
        $display("--------------------------------------------");
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
