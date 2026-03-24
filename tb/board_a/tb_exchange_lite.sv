// ============================================================================
// Testbench: tb_exchange_lite
// Tests the exchange_lite module: simplified exchange matching engine that
// receives ORDER frames, compares limit_price against live bid/ask from
// market_sim, and generates FILL frames (FILLED or REJECTED).
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_exchange_lite;
    localparam int TB_NUM_SYM = 4;

    logic                     clk;
    logic                     rst_n;
    logic                     enable;
    price_t                   best_bid    [TB_NUM_SYM];
    price_t                   best_ask    [TB_NUM_SYM];
    logic [FRAME_W-1:0]       order_frame;
    logic                     order_valid;
    logic [FRAME_W-1:0]       fill_frame;
    logic                     fill_valid;
    logic                     fill_ready;
    logic [COUNTER_W-1:0]     orders_rcvd;
    logic [COUNTER_W-1:0]     fills_sent;
    logic [COUNTER_W-1:0]     rejects_sent;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    exchange_lite #(
        .NUM_SYM(TB_NUM_SYM)
    ) dut (
        .clk         (clk),
        .rst_n       (rst_n),
        .enable      (enable),
        .counter_clr (1'b0),
        .best_bid    (best_bid),
        .best_ask    (best_ask),
        .order_frame (order_frame),
        .order_valid (order_valid),
        .fill_frame  (fill_frame),
        .fill_valid  (fill_valid),
        .fill_ready  (fill_ready),
        .orders_rcvd (orders_rcvd),
        .fills_sent  (fills_sent),
        .rejects_sent(rejects_sent)
    );

    int err_count = 0;

    task automatic check(input string msg, input logic cond);
        if (!cond) begin
            $error("FAIL: %s", msg);
            err_count++;
        end
    endtask

    // ORDER frame builder per spec:
    // [127:124]=MSG_ORDER, [123:116]=symbol, [115]=side, [114:112]=reserved
    // [111:80]=limit_price, [79:64]=qty, [63:48]=order_id, [47:32]=timestamp
    // [31:0]=reserved
    function automatic logic [127:0] build_order(
        input logic [7:0]  sym,
        input logic        side,
        input logic [31:0] limit_price,
        input logic [15:0] qty,
        input logic [15:0] oid,
        input logic [15:0] ts
    );
        build_order = {
            MSG_ORDER, sym, side, 3'b000,
            limit_price, qty, oid, ts, 32'h0000_0000
        };
    endfunction

    task automatic send_order(input logic [127:0] frame);
        begin
            order_frame = frame;
            order_valid = 1'b1;
            @(posedge clk);
            order_valid = 1'b0;
        end
    endtask

    task automatic wait_for_fill(input int timeout_cycles, input string why);
        int i;
        begin
            i = 0;
            while (!fill_valid && i < timeout_cycles) begin
                @(posedge clk);
                i++;
            end
            check($sformatf("%s: fill_valid should assert within %0d cycles", why, timeout_cycles),
                  fill_valid);
        end
    endtask

    task automatic expect_no_fill_for_cycles(input int cycles, input string why);
        begin
            for (int i = 0; i < cycles; i++) begin
                @(posedge clk);
                check($sformatf("%s (cycle %0d): no fill_valid expected", why, i), !fill_valid);
            end
        end
    endtask

    // Waveform dump
    initial begin
        $dumpfile("tb_exchange_lite.vcd");
        $dumpvars(0, tb_exchange_lite);
    end

    initial begin
        // Defaults
        enable      = 1'b0;
        order_frame = '0;
        order_valid = 1'b0;
        fill_ready  = 1'b1;

        // Seed best bid/ask
        for (int s = 0; s < TB_NUM_SYM; s++) begin
            best_bid[s] = 32'h0064_0000; // 100.0
            best_ask[s] = 32'h0065_0000; // 101.0
        end
        // Symbol 1 has different prices to verify symbol routing
        best_bid[1] = 32'h0032_0000; // 50.0
        best_ask[1] = 32'h0033_0000; // 51.0

        // Wait reset release
        @(posedge clk);
        wait (rst_n === 1'b1);
        @(posedge clk);
        enable = 1'b1;

        // -------------------------------------------------------------
        // 1) BUY at ask -> FILLED at ask
        // -------------------------------------------------------------
        send_order(build_order(8'd0, 1'b0, 32'h0065_0000, 16'd50, 16'd1, 16'hAAAA));
        wait_for_fill(4, "BUY at ask");
        check("BUY at ask: fill_valid", fill_valid);
        check("BUY at ask: msg_type=FILL", fill_frame[127:124] == MSG_FILL);
        check("BUY at ask: symbol echoed", fill_frame[123:116] == 8'd0);
        check("BUY at ask: side echoed", fill_frame[115] == 1'b0);
        check("BUY at ask: status=FILLED", fill_frame[114:112] == 3'b000);
        check("BUY at ask: fill_price=ask", fill_frame[111:80] == 32'h0065_0000);
        check("BUY at ask: fill_qty=order qty", fill_frame[79:64] == 16'd50);
        check("BUY at ask: order_id echoed", fill_frame[63:48] == 16'd1);
        check("BUY at ask: ts_echo echoed", fill_frame[47:32] == 16'hAAAA);
        check("BUY at ask: reserved low bits zero", fill_frame[31:0] == 32'h0);
        @(posedge clk);

        // -------------------------------------------------------------
        // 2) BUY below ask -> REJECT
        // -------------------------------------------------------------
        send_order(build_order(8'd0, 1'b0, 32'h0063_0000, 16'd25, 16'd2, 16'hBBBB));
        wait_for_fill(4, "BUY below ask");
        check("BUY below ask: fill_valid", fill_valid);
        check("BUY below ask: status=REJECTED", fill_frame[114:112] == 3'b001);
        check("BUY below ask: fill_price=0", fill_frame[111:80] == 32'h0);
        check("BUY below ask: fill_qty=0", fill_frame[79:64] == 16'h0);
        check("BUY below ask: order_id echoed", fill_frame[63:48] == 16'd2);
        check("BUY below ask: ts_echo echoed", fill_frame[47:32] == 16'hBBBB);
        @(posedge clk);

        // -------------------------------------------------------------
        // 3) SELL at bid -> FILLED at bid
        // -------------------------------------------------------------
        send_order(build_order(8'd0, 1'b1, 32'h0064_0000, 16'd30, 16'd3, 16'hCCCC));
        wait_for_fill(4, "SELL at bid");
        check("SELL at bid: fill_valid", fill_valid);
        check("SELL at bid: status=FILLED", fill_frame[114:112] == 3'b000);
        check("SELL at bid: fill_price=bid", fill_frame[111:80] == 32'h0064_0000);
        check("SELL at bid: fill_qty=order qty", fill_frame[79:64] == 16'd30);
        @(posedge clk);

        // -------------------------------------------------------------
        // 4) SELL above bid -> REJECT
        // -------------------------------------------------------------
        send_order(build_order(8'd0, 1'b1, 32'h0066_0000, 16'd30, 16'd4, 16'hDDDD));
        wait_for_fill(4, "SELL above bid");
        check("SELL above bid: fill_valid", fill_valid);
        check("SELL above bid: status=REJECTED", fill_frame[114:112] == 3'b001);
        check("SELL above bid: fill_price=0", fill_frame[111:80] == 32'h0);
        check("SELL above bid: fill_qty=0", fill_frame[79:64] == 16'h0);
        @(posedge clk);

        // -------------------------------------------------------------
        // 5) Symbol routing: use symbol 1 bid/ask
        // -------------------------------------------------------------
        send_order(build_order(8'd1, 1'b0, 32'h0033_0000, 16'd10, 16'd5, 16'hEEEE));
        wait_for_fill(4, "Symbol1 BUY at ask");
        check("Symbol1 BUY at ask: fill_valid", fill_valid);
        check("Symbol1 BUY at ask: symbol echoed", fill_frame[123:116] == 8'd1);
        check("Symbol1 BUY at ask: fill_price uses symbol1 ask", fill_frame[111:80] == 32'h0033_0000);
        @(posedge clk);

        // -------------------------------------------------------------
        // 6) Backpressure: fill_ready=0 should hold response valid (not drop)
        // -------------------------------------------------------------
        fill_ready = 1'b0;
        send_order(build_order(8'd0, 1'b0, 32'h0065_0000, 16'd11, 16'd6, 16'h1234));
        wait_for_fill(4, "fill_ready low");
        check("fill_ready low: held order_id", fill_frame[63:48] == 16'd6);
        check("fill_ready low: held ts_echo", fill_frame[47:32] == 16'h1234);
        repeat (4) begin
            @(posedge clk);
            check("fill_ready low: fill_valid stays asserted", fill_valid);
            check("fill_ready low: frame stable", fill_frame[63:48] == 16'd6);
        end
        fill_ready = 1'b1;
        @(posedge clk);
        check("held fill consumed when ready returns", !fill_valid);
        @(posedge clk);

        // -------------------------------------------------------------
        // 7) enable=0 should suppress processing
        // -------------------------------------------------------------
        enable = 1'b0;
        send_order(build_order(8'd0, 1'b0, 32'h0065_0000, 16'd12, 16'd7, 16'h5678));
        expect_no_fill_for_cycles(4, "enable low");
        enable = 1'b1;

        // -------------------------------------------------------------
        // 8) Invalid msg_type should be ignored (no order count increment)
        // -------------------------------------------------------------
        order_frame = {4'hF, 124'h0};
        order_valid = 1'b1;
        @(posedge clk);
        order_valid = 1'b0;
        expect_no_fill_for_cycles(3, "invalid msg_type");

        // -------------------------------------------------------------
        // 9) Out-of-range symbol should return REJECT (not silent drop)
        // -------------------------------------------------------------
        send_order(build_order(8'd99, 1'b0, 32'h0065_0000, 16'd7, 16'd8, 16'h9ABC));
        wait_for_fill(4, "out-of-range symbol");
        check("out-of-range: symbol echoed", fill_frame[123:116] == 8'd99);
        check("out-of-range: status=REJECTED", fill_frame[114:112] == 3'b001);
        check("out-of-range: fill_price=0", fill_frame[111:80] == 32'h0);
        check("out-of-range: fill_qty=0", fill_frame[79:64] == 16'h0);
        check("out-of-range: order_id echoed", fill_frame[63:48] == 16'd8);
        check("out-of-range: ts_echo echoed", fill_frame[47:32] == 16'h9ABC);
        @(posedge clk);

        // -------------------------------------------------------------
        // 10) Handshake-cycle bubble: consuming response does not emit next
        //     response in the same cycle (minimal one-order-at-a-time model).
        // -------------------------------------------------------------
        send_order(build_order(8'd0, 1'b0, 32'h0065_0000, 16'd21, 16'd9, 16'h1111));
        wait_for_fill(4, "bubble prefill");
        check("bubble prefill: order_id=9", fill_frame[63:48] == 16'd9);
        // First response consumes on this edge; no replacement in same cycle.
        @(posedge clk);
        check("bubble: no same-cycle replacement after consume", !fill_valid);
        // Submit next order after consume; response should appear later and be correct.
        send_order(build_order(8'd0, 1'b0, 32'h0065_0000, 16'd22, 16'd10, 16'h2222));
        wait_for_fill(4, "bubble second response");
        check("bubble second response: order_id=10", fill_frame[63:48] == 16'd10);
        check("bubble second response: ts_echo", fill_frame[47:32] == 16'h2222);
        @(posedge clk);

        // Counter checks
        // Processed valid ORDER frames while enable=1 and msg_type==ORDER:
        // tests 1,2,3,4,5,6,9,10 => 9 orders_rcvd (test 7 is enable=0; test 8 invalid type)
        check("orders_rcvd count", orders_rcvd == 32'd9);
        // Filled tests: 1,3,5,6,10(oid9,oid10) -> 6
        check("fills_sent count", fills_sent == 32'd6);
        // Rejected tests: 2,4,9 -> 3
        check("rejects_sent count", rejects_sent == 32'd3);

        if (err_count == 0)
            $display("tb_exchange_lite: PASS (all checks passed, VCD: tb_exchange_lite.vcd)");
        else
            $display("tb_exchange_lite: FAIL (%0d errors)", err_count);

        $finish;
    end

endmodule
