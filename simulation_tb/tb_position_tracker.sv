`timescale 1ns / 1ps
import hft_pkg::*;

module tb_position_tracker();

    logic        clk = 0;
    logic        rst_n;
    logic        clear;
    logic [FRAME_W-1:0] fill_frame;
    logic        fill_valid;

    position_t   position [NUM_SYMBOLS];
    cash_t       cash;
    sprice_t     total_pnl;
    timestamp_t  ts_echo;
    logic        fill_processed;
    symbol_t     fill_symbol_out;
    logic        fill_side_out;
    qty_t        fill_qty_out;
    logic        fill_notify;
    logic [COUNTER_W-1:0] fills_rcvd;

    integer err_cnt = 0;

    always #5 clk = ~clk;

    position_tracker #(.NUM_SYM(NUM_SYMBOLS)) dut (
        .clk(clk), .rst_n(rst_n), .clear(clear),
        .fill_frame(fill_frame), .fill_valid(fill_valid),
        .position(position), .cash(cash), .total_pnl(total_pnl),
        .ts_echo(ts_echo), .fill_processed(fill_processed),
        .fill_symbol_out(fill_symbol_out), .fill_side_out(fill_side_out),
        .fill_qty_out(fill_qty_out), .fill_notify(fill_notify),
        .fills_rcvd(fills_rcvd)
    );

    // Frame layout (from RTL):
    //   [127:124]=msg_type, [123:116]=symbol, [115]=side(0=BUY,1=SELL),
    //   [114:112]=status(000=FILLED), [111:80]=price(Q16.16),
    //   [79:64]=qty, [63:48]=order_id, [47:32]=ts_echo

    initial begin
        $display("=== tb_position_tracker ===");
        rst_n = 0; clear = 0; fill_frame = 0; fill_valid = 0;
        #20; rst_n = 1; @(posedge clk);

        // Test 1: BUY fill sym=0, qty=100, price=$1.00 (Q16.16=0x00010000)
        $display("Test 1: BUY sym=0 qty=100 @ $1.00");
        fill_frame = 128'h3000_0001_0000_0064_0001_0032_0000_0000;
        fill_valid = 1;
        @(posedge clk); fill_valid = 0;
        @(posedge clk); #1;
        if (position[0] == 32'sd100)
            $display("  PASS: position[0] = 100");
        else begin
            $display("  FAIL: position[0] = %0d, expected 100", $signed(position[0]));
            err_cnt = err_cnt + 1;
        end
        if (total_pnl == -32'sd100)
            $display("  PASS: total_pnl = -100");
        else begin
            $display("  FAIL: total_pnl = %0d, expected -100", $signed(total_pnl));
            err_cnt = err_cnt + 1;
        end

        // Test 2: SELL fill sym=0, qty=50, price=$1.00
        // side=1(SELL) -> byte [119:112]=0x08
        $display("Test 2: SELL sym=0 qty=50 @ $1.00");
        fill_frame = 128'h3008_0001_0000_0032_0002_0050_0000_0000;
        fill_valid = 1;
        @(posedge clk); fill_valid = 0;
        @(posedge clk); #1;
        if (position[0] == 32'sd50)
            $display("  PASS: position[0] = 50");
        else begin
            $display("  FAIL: position[0] = %0d, expected 50", $signed(position[0]));
            err_cnt = err_cnt + 1;
        end

        // Test 3: fills_rcvd counter
        $display("Test 3: fills_rcvd count");
        if (fills_rcvd == 32'd2)
            $display("  PASS: fills_rcvd = 2");
        else begin
            $display("  FAIL: fills_rcvd = %0d, expected 2", fills_rcvd);
            err_cnt = err_cnt + 1;
        end

        // Test 4: REJECTED fill (status=001) -> position unchanged
        $display("Test 4: REJECTED fill unchanged");
        fill_frame = 128'h3001_0001_0000_0064_0003_0060_0000_0000;
        fill_valid = 1;
        @(posedge clk); fill_valid = 0;
        @(posedge clk); #1;
        if (position[0] == 32'sd50 && fills_rcvd == 32'd2)
            $display("  PASS: position still 50, fills still 2");
        else begin
            $display("  FAIL: pos=%0d fills=%0d", $signed(position[0]), fills_rcvd);
            err_cnt = err_cnt + 1;
        end

        // Test 5: Clear resets all
        $display("Test 5: Clear resets");
        clear = 1; @(posedge clk); clear = 0;
        @(posedge clk); #1;
        if (position[0] == 0 && cash == 0 && fills_rcvd == 0)
            $display("  PASS: all cleared");
        else begin
            $display("  FAIL: pos=%0d cash=%0d fills=%0d",
                     $signed(position[0]), $signed(cash), fills_rcvd);
            err_cnt = err_cnt + 1;
        end

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
