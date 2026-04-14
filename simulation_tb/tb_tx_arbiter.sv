`timescale 1ns / 1ps

module tb_tx_arbiter();
    import hft_pkg::*;

    logic                clk, rst_n;
    logic [FRAME_W-1:0] fill_frame, quote_frame;
    logic                fill_valid, fill_ready;
    logic                quote_valid, quote_ready;
    logic [FRAME_W-1:0] tx_frame;
    logic                tx_valid, tx_ready;

    integer err_cnt = 0;
    integer cyc;
    logic   quote_leaked;

    always #5 clk = ~clk;

    tx_arbiter dut (
        .clk(clk), .rst_n(rst_n),
        .fill_frame(fill_frame),   .fill_valid(fill_valid),   .fill_ready(fill_ready),
        .quote_frame(quote_frame), .quote_valid(quote_valid), .quote_ready(quote_ready),
        .tx_frame(tx_frame),       .tx_valid(tx_valid),       .tx_ready(tx_ready)
    );

    // Marker patterns for identification
    localparam [FRAME_W-1:0] FILL_PAT  = {MSG_FILL,  124'hAAA_BBBB_CCCC_DDDD_EEEE_FFFF_0000};
    localparam [FRAME_W-1:0] QUOTE_PAT = {MSG_QUOTE, 124'h111_2222_3333_4444_5555_6666_0000};

    initial begin
        clk = 0; rst_n = 0;
        fill_frame  = '0; fill_valid  = 0;
        quote_frame = '0; quote_valid = 0;
        tx_ready = 1;

        #20; rst_n = 1; @(posedge clk);

        // Test 1: idle - nothing valid in, nothing out
        @(posedge clk); #1;
        if (tx_valid !== 1'b0) begin
            $display("FAIL: tx_valid=%b in idle, expected 0", tx_valid);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: idle, tx_valid=0");

        // Test 2: present fill only -> appears on tx
        fill_frame = FILL_PAT; fill_valid = 1;
        @(posedge clk); #1;
        if (tx_valid !== 1'b1) begin
            $display("FAIL: tx_valid=%b, expected 1", tx_valid);
            err_cnt = err_cnt + 1;
        end else if (tx_frame !== FILL_PAT) begin
            $display("FAIL: tx_frame mismatch");
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: fill frame forwarded");

        fill_valid = 0;
        // Consume (tx_ready=1), wait for buffer to clear
        @(posedge clk); @(posedge clk); #1;

        // Test 3: present quote only -> appears on tx
        quote_frame = QUOTE_PAT; quote_valid = 1;
        @(posedge clk); #1;
        if (tx_valid !== 1'b1) begin
            $display("FAIL: tx_valid=%b, expected 1", tx_valid);
            err_cnt = err_cnt + 1;
        end else if (tx_frame !== QUOTE_PAT) begin
            $display("FAIL: tx_frame mismatch");
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: quote frame forwarded");

        quote_valid = 0;
        @(posedge clk); @(posedge clk); #1;

        // Test 4: both valid simultaneously -> fill wins
        fill_frame  = FILL_PAT;  fill_valid  = 1;
        quote_frame = QUOTE_PAT; quote_valid = 1;
        @(posedge clk); #1;
        if (tx_frame !== FILL_PAT) begin
            $display("FAIL: fill did not win arbitration");
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: fill wins priority over quote");

        fill_valid = 0; quote_valid = 0;
        @(posedge clk); @(posedge clk); #1;

        // Test 5: backpressure - tx_ready=0 holds frame
        tx_ready = 0;
        fill_frame = FILL_PAT; fill_valid = 1;
        @(posedge clk); #1;
        if (tx_valid !== 1'b1) begin
            $display("FAIL: frame not buffered under backpressure");
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: frame held under backpressure");

        fill_valid = 0;
        // Release backpressure
        tx_ready = 1;
        @(posedge clk); @(posedge clk); #1;
        if (tx_valid !== 1'b0) begin
            $display("FAIL: frame not consumed after ready");
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: frame consumed after tx_ready");

        // ----------------------------------------------------------------
        // Test 6: mid-reset — assert rst_n=0 while a frame is buffered,
        //         verify tx_valid goes 0 after reset release.
        // ----------------------------------------------------------------
        // Buffer a fill frame under backpressure
        tx_ready = 0;
        fill_frame = FILL_PAT; fill_valid = 1;
        @(posedge clk); #1;

        // Frame should be buffered
        if (tx_valid !== 1'b1) begin
            $display("FAIL: setup for mid-reset — frame not buffered");
            err_cnt = err_cnt + 1;
        end

        fill_valid = 0;
        // Assert reset while frame is held
        rst_n = 0;
        repeat(2) @(posedge clk);
        rst_n = 1;
        @(posedge clk); #1;

        if (tx_valid !== 1'b0) begin
            $display("FAIL: tx_valid=%b after mid-reset, expected 0", tx_valid);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: mid-reset cleared buffered frame (tx_valid=0)");

        tx_ready = 1;
        @(posedge clk); @(posedge clk); #1;

        // ----------------------------------------------------------------
        // Test 7: quote starvation — continuous fill_valid prevents quote
        //         from ever appearing on output.
        // ----------------------------------------------------------------
        quote_leaked = 0;
        fill_frame  = FILL_PAT;  fill_valid  = 1;
        quote_frame = QUOTE_PAT; quote_valid = 1;
        tx_ready = 1;

        for (cyc = 0; cyc < 20; cyc = cyc + 1) begin
            @(posedge clk); #1;
            if (tx_valid && tx_frame[127:124] === MSG_QUOTE)
                quote_leaked = 1;
        end

        fill_valid = 0; quote_valid = 0;

        if (quote_leaked) begin
            $display("FAIL: quote appeared on output despite continuous fill");
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: quote starved — fill always wins with strict priority");

        // Summary
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
