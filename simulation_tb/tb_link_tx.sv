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

    // One test frame per message type (msg_type in upper nibble)
    localparam [FRAME_W-1:0] FRAME_QUOTE = 128'h1234_5678_9ABC_DEF0_FEDC_BA98_7654_3210;
    localparam [FRAME_W-1:0] FRAME_ORDER = 128'h2AAA_BBBB_CCCC_DDDD_EEEE_FFFF_0000_1111;
    localparam [FRAME_W-1:0] FRAME_FILL  = 128'h3111_2222_3333_4444_5555_6666_7777_8888;

    initial begin
        clk = 0; rst_n = 0;
        frame_in = '0; frame_in_valid = 0; remote_ready = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // ============================================================
        // Test 1: Idle — no frame, remote not ready
        // ============================================================
        @(posedge clk); #1;
        if (pmod_valid !== 1'b0) begin
            $display("FAIL [idle]: pmod_valid=%0b (expected 0)", pmod_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS [idle]: pmod_valid=0");

        if (frame_in_ready !== 1'b0) begin
            $display("FAIL [idle]: frame_in_ready=%0b (expected 0)", frame_in_ready);
            err_cnt = err_cnt + 1;
        end else $display("PASS [idle]: frame_in_ready=0 (remote not ready)");

        // ============================================================
        // Test 2: Backpressure — remote_ready=0 prevents TX from
        //         accepting a new frame even when valid is asserted
        // ============================================================
        frame_in       = FRAME_QUOTE;
        frame_in_valid = 1;
        repeat(4) @(posedge clk); #1;

        if (frame_in_ready !== 1'b0) begin
            $display("FAIL [backpressure]: frame_in_ready=%0b (expected 0)", frame_in_ready);
            err_cnt = err_cnt + 1;
        end else $display("PASS [backpressure]: TX refuses frame while remote not ready");

        if (pmod_valid !== 1'b0) begin
            $display("FAIL [backpressure]: pmod_valid=%0b (expected 0)", pmod_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS [backpressure]: no transmission started");

        frame_in_valid = 0;

        // Release backpressure — let 2-FF sync settle
        remote_ready = 1;
        repeat(3) @(posedge clk); #1;

        if (frame_in_ready !== 1'b1) begin
            $display("FAIL [bp-release]: frame_in_ready=%0b (expected 1)", frame_in_ready);
            err_cnt = err_cnt + 1;
        end else $display("PASS [bp-release]: TX ready after remote_ready asserts");

        // ============================================================
        // Test 3: QUOTE nibble-accurate serialization — check all 32
        //         nibbles MSB-first against golden value
        // ============================================================
        frame_in       = FRAME_QUOTE;
        frame_in_valid = 1;
        @(posedge clk);
        frame_in_valid = 0;

        // TX in ST_SEND: each nibble held for 2 clocks
        for (i = 0; i < 32; i = i + 1) begin
            @(posedge clk); #1;
            exp_nib = FRAME_QUOTE[127 - i*4 -: 4];
            if (pmod_data !== exp_nib) begin
                $display("FAIL [nibble]: nibble[%0d] got %h expected %h",
                         i, pmod_data, exp_nib);
                err_cnt = err_cnt + 1;
            end
            @(posedge clk);
        end
        $display("INFO [QUOTE nibbles]: 32 nibbles checked, err_cnt=%0d", err_cnt);

        // After last nibble, pmod_valid must drop back to 0
        @(posedge clk); #1;
        if (pmod_valid !== 1'b0) begin
            $display("FAIL [post-QUOTE]: pmod_valid=%0b (expected 0)", pmod_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS [post-QUOTE]: pmod_valid=0 after packet");

        // ============================================================
        // Test 4: ORDER frame — handshake accepted, full serialization
        // ============================================================
        #1;
        if (frame_in_ready !== 1'b1) begin
            $display("FAIL [ORDER-ready]: frame_in_ready=%0b (expected 1)", frame_in_ready);
            err_cnt = err_cnt + 1;
        end else $display("PASS [ORDER-ready]: TX ready for next frame");

        frame_in       = FRAME_ORDER;
        frame_in_valid = 1;
        @(posedge clk);
        frame_in_valid = 0;

        // 32 nibbles × 2 clk = 64 clk for serialization
        repeat(64) @(posedge clk);
        @(posedge clk); #1;

        if (pmod_valid !== 1'b0) begin
            $display("FAIL [ORDER]: pmod_valid=%0b after TX (expected 0)", pmod_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS [ORDER]: frame serialized, pmod_valid=0");

        // ============================================================
        // Test 5: FILL frame — handshake accepted, full serialization
        // ============================================================
        #1;
        if (frame_in_ready !== 1'b1) begin
            $display("FAIL [FILL-ready]: frame_in_ready=%0b (expected 1)", frame_in_ready);
            err_cnt = err_cnt + 1;
        end else $display("PASS [FILL-ready]: TX ready for next frame");

        frame_in       = FRAME_FILL;
        frame_in_valid = 1;
        @(posedge clk);
        frame_in_valid = 0;

        repeat(64) @(posedge clk);
        @(posedge clk); #1;

        if (pmod_valid !== 1'b0) begin
            $display("FAIL [FILL]: pmod_valid=%0b after TX (expected 0)", pmod_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS [FILL]: frame serialized, pmod_valid=0");

        // ============================================================
        // Test 6: Back-to-back — send 2 frames in quick succession,
        //         verify pmod_valid returns to 0 between and after
        // ============================================================

        // First frame (QUOTE)
        frame_in       = FRAME_QUOTE;
        frame_in_valid = 1;
        @(posedge clk);
        frame_in_valid = 0;

        repeat(64) @(posedge clk);
        @(posedge clk); #1;

        if (pmod_valid !== 1'b0) begin
            $display("FAIL [b2b-1]: pmod_valid=%0b after first frame (expected 0)", pmod_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS [b2b-1]: first frame done, pmod_valid=0");

        // Immediately send second frame (ORDER)
        frame_in       = FRAME_ORDER;
        frame_in_valid = 1;
        @(posedge clk);
        frame_in_valid = 0;

        repeat(64) @(posedge clk);
        @(posedge clk); #1;

        if (pmod_valid !== 1'b0) begin
            $display("FAIL [b2b-2]: pmod_valid=%0b after second frame (expected 0)", pmod_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS [b2b-2]: second frame done, pmod_valid=0");

        // ============================================================
        $display("--------------------------------------------");
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
