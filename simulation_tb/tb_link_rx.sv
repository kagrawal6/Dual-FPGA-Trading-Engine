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
    integer saved_err;
    integer fov_count = 0;
    integer saved_fov;

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

    // Concurrent monitor: count frame_out_valid pulses for back-to-back test
    always @(posedge clk) if (frame_out_valid) fov_count = fov_count + 1;

    // Test frames (msg_type in upper nibble: 1=QUOTE, 2=ORDER, 3=FILL)
    localparam [FRAME_W-1:0] FRAME_QUOTE   = 128'h1234_5678_9ABC_DEF0_FEDC_BA98_7654_3210;
    localparam [FRAME_W-1:0] FRAME_ORDER   = 128'h2AAA_BBBB_CCCC_DDDD_EEEE_FFFF_0000_1111;
    localparam [FRAME_W-1:0] FRAME_FILL    = 128'h3111_2222_3333_4444_5555_6666_7777_8888;
    localparam [FRAME_W-1:0] FRAME_INVALID = 128'h0000_0000_0000_0000_0000_0000_0000_0001;

    // ----------------------------------------------------------------
    // Task: drive nibbles onto PMOD bus (2 clk per nibble, matching TX
    //       rate). 'count' lets us send partial frames for error tests.
    // ----------------------------------------------------------------
    task automatic drive_nibbles(input logic [FRAME_W-1:0] f, input int count);
        integer j;
        pmod_valid = 1;
        for (j = 0; j < count; j = j + 1) begin
            pmod_data = f[127 - j*4 -: 4];
            @(posedge clk); @(posedge clk);
        end
        pmod_valid = 0;
    endtask

    initial begin
        clk = 0; rst_n = 0; counter_clr = 0;
        pmod_data = '0; pmod_valid = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // ============================================================
        // Test 1: Idle — no traffic, frame_out_valid should be 0
        // ============================================================
        @(posedge clk); #1;
        if (frame_out_valid !== 1'b0) begin
            $display("FAIL [idle]: frame_out_valid=%0b (expected 0)", frame_out_valid);
            err_cnt = err_cnt + 1;
        end else $display("PASS [idle]: no frame pulse in idle");

        // ============================================================
        // Test 2: Valid QUOTE frame — drive 32 nibbles, check output
        //         matches golden value, link_up=1, error_count=0
        // ============================================================
        repeat(2) @(posedge clk);
        drive_nibbles(FRAME_QUOTE, 32);
        repeat(10) @(posedge clk); #1;

        if (frame_out !== FRAME_QUOTE) begin
            $display("FAIL [QUOTE]: frame_out=%h", frame_out);
            $display("               expected=%h", FRAME_QUOTE);
            err_cnt = err_cnt + 1;
        end else $display("PASS [QUOTE]: frame_out matches");

        if (link_up !== 1'b1) begin
            $display("FAIL [QUOTE]: link_up=%0b (expected 1)", link_up);
            err_cnt = err_cnt + 1;
        end else $display("PASS [QUOTE]: link_up=1 after good frame");

        if (error_count !== 32'h0) begin
            $display("FAIL [QUOTE]: error_count=%0d (expected 0)", error_count);
            err_cnt = err_cnt + 1;
        end else $display("PASS [QUOTE]: error_count=0");

        // ============================================================
        // Test 3: Back-to-back — ORDER then FILL, both received
        //         (verifies RX re-arms correctly after each frame)
        // ============================================================
        saved_fov = fov_count;

        // ORDER frame
        repeat(5) @(posedge clk);
        drive_nibbles(FRAME_ORDER, 32);
        repeat(10) @(posedge clk); #1;

        if (frame_out !== FRAME_ORDER) begin
            $display("FAIL [b2b ORDER]: frame_out=%h", frame_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS [b2b ORDER]: frame_out matches");

        // FILL frame
        repeat(5) @(posedge clk);
        drive_nibbles(FRAME_FILL, 32);
        repeat(10) @(posedge clk); #1;

        if (frame_out !== FRAME_FILL) begin
            $display("FAIL [b2b FILL]: frame_out=%h", frame_out);
            err_cnt = err_cnt + 1;
        end else $display("PASS [b2b FILL]: frame_out matches");

        if ((fov_count - saved_fov) !== 2) begin
            $display("FAIL [b2b]: expected 2 valid pulses, got %0d", fov_count - saved_fov);
            err_cnt = err_cnt + 1;
        end else $display("PASS [b2b]: frame_out_valid pulsed twice");

        // ============================================================
        // Test 4: Truncated frame — only 16 of 32 nibbles sent.
        //         RX should detect the premature valid drop, increment
        //         error_count, and NOT assert frame_out_valid.
        // ============================================================
        saved_err = error_count;
        saved_fov = fov_count;

        repeat(5) @(posedge clk);
        drive_nibbles(FRAME_QUOTE, 16);
        repeat(15) @(posedge clk); #1;

        if (error_count !== saved_err + 1) begin
            $display("FAIL [truncated]: error_count=%0d (expected %0d)",
                     error_count, saved_err + 1);
            err_cnt = err_cnt + 1;
        end else $display("PASS [truncated]: error_count incremented");

        if (fov_count !== saved_fov) begin
            $display("FAIL [truncated]: frame_out_valid pulsed (should not)");
            err_cnt = err_cnt + 1;
        end else $display("PASS [truncated]: no frame output on truncated input");

        // ============================================================
        // Test 5: counter_clr — pulse clears error_count to 0
        // ============================================================
        counter_clr = 1;
        @(posedge clk);
        counter_clr = 0;
        @(posedge clk); #1;

        if (error_count !== 32'h0) begin
            $display("FAIL [clr]: error_count=%0d (expected 0)", error_count);
            err_cnt = err_cnt + 1;
        end else $display("PASS [clr]: error_count cleared to 0");

        // ============================================================
        // Test 6: Invalid msg_type (4'h0) — RX assembles all 32
        //         nibbles but rejects the frame. error_count++,
        //         frame_out_valid must NOT pulse.
        // ============================================================
        saved_err = error_count;
        saved_fov = fov_count;

        repeat(5) @(posedge clk);
        drive_nibbles(FRAME_INVALID, 32);
        repeat(10) @(posedge clk); #1;

        if (error_count !== saved_err + 1) begin
            $display("FAIL [invalid-msg]: error_count=%0d (expected %0d)",
                     error_count, saved_err + 1);
            err_cnt = err_cnt + 1;
        end else $display("PASS [invalid-msg]: error_count incremented for bad msg_type");

        if (fov_count !== saved_fov) begin
            $display("FAIL [invalid-msg]: frame_out_valid pulsed (should not)");
            err_cnt = err_cnt + 1;
        end else $display("PASS [invalid-msg]: no frame output for invalid msg_type");

        // ============================================================
        $display("--------------------------------------------");
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
