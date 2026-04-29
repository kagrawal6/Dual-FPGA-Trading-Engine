// ============================================================================
// Testbench: tb_exchange_lite
// Golden fill frames, boundary prices, counter_clr, enable=0, back-to-back
// orders, all symbols, out-of-range, backpressure, wrong msg_type.
// Golden vectors from gen_board_a_vectors.py.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_exchange_lite;
    localparam int TB_NUM_SYM = 4;

    logic                     clk;
    logic                     rst_n;
    logic                     enable;
    logic                     counter_clr_sig;
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

    int pass_count = 0;
    int fail_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    exchange_lite #(.NUM_SYM(TB_NUM_SYM)) dut (
        .clk         (clk),
        .rst_n       (rst_n),
        .enable      (enable),
        .counter_clr (counter_clr_sig),
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

    task automatic check(string msg, logic cond);
        if (cond) pass_count++;
        else begin
            $error("FAIL: %s", msg);
            fail_count++;
        end
    endtask

    task automatic check32(string msg, logic [31:0] actual, logic [31:0] expected);
        if (actual === expected) pass_count++;
        else begin
            $error("FAIL: %s — got %08h, exp %08h", msg, actual, expected);
            fail_count++;
        end
    endtask

    task automatic check128(string msg, logic [127:0] actual, logic [127:0] expected);
        if (actual === expected) pass_count++;
        else begin
            $error("FAIL: %s", msg);
            $error("  got: %032h", actual);
            $error("  exp: %032h", expected);
            fail_count++;
        end
    endtask

    function automatic logic [127:0] build_order(
        input logic [7:0]  sym,
        input logic        side,
        input logic [31:0] limit_price,
        input logic [15:0] qty,
        input logic [15:0] oid,
        input logic [15:0] ts
    );
        build_order = {MSG_ORDER, sym, side, 3'b000, limit_price, qty, oid, ts, 32'h0};
    endfunction

    task automatic send_order(input logic [127:0] frame);
        order_frame = frame;
        order_valid = 1'b1;
        @(posedge clk); #1;
        order_valid = 1'b0;
    endtask

    task automatic wait_fill(input int timeout = 10, input string tag = "");
        int cnt = 0;
        while (!fill_valid && cnt < timeout) begin
            @(posedge clk); #1;
            cnt++;
        end
        check($sformatf("%s: fill arrived", tag), fill_valid);
    endtask

    task automatic no_fill_for(input int cycles, input string tag);
        for (int i = 0; i < cycles; i++) begin
            @(posedge clk); #1;
            check($sformatf("%s[%0d]: no fill", tag, i), !fill_valid);
        end
    endtask

    // Golden bid/ask after 16 quotes in CALM regime from golden model
    localparam logic [31:0] G_BID [4] = '{32'h00B3F80B, 32'h01A3F7F4, 32'h0383F7FE, 32'h0072F80F};
    localparam logic [31:0] G_ASK [4] = '{32'h00B4080B, 32'h01A407F4, 32'h038407FE, 32'h0073080F};

    // Golden fill frames from gen_board_a_vectors.py
    localparam logic [127:0] GF_BUY_AT_ASK = 128'h300000B4080B00640000006400000000;
    localparam logic [127:0] GF_BUY_BELOW  = 128'h30010000000000000001006500000000;
    localparam logic [127:0] GF_SELL_AT_BID = 128'h301801A3F7F4004B0002006600000000;
    localparam logic [127:0] GF_SELL_ABOVE  = 128'h30190000000000000003006700000000;
    localparam logic [127:0] GF_OOR_SYM4   = 128'h30410000000000000004006800000000;
    localparam logic [127:0] GF_BUY_SYM3   = 128'h30300073080F00C80005006900000000;

    initial begin
        $dumpfile("tb_exchange_lite.vcd");
        $dumpvars(0, tb_exchange_lite);

        enable          = 1'b0;
        counter_clr_sig = 1'b0;
        order_frame     = '0;
        order_valid     = 1'b0;
        fill_ready      = 1'b1;

        for (int s = 0; s < TB_NUM_SYM; s++) begin
            best_bid[s] = G_BID[s];
            best_ask[s] = G_ASK[s];
        end

        @(posedge clk); #1;
        wait (rst_n === 1'b1);
        @(posedge clk); #1;
        enable = 1'b1;

        // ─────────────────────────────────────────────────────
        // 1) Golden: BUY at ask → FILLED
        // ─────────────────────────────────────────────────────
        $display("--- test_golden_fills ---");
        send_order(128'h200000B4080B00640000006400000000);
        wait_fill(10, "BUY@ask");
        check128("BUY@ask golden fill", fill_frame, GF_BUY_AT_ASK);
        @(posedge clk); #1;

        // 2) BUY below ask → REJECTED
        send_order(128'h200000B4080A00320001006500000000);
        wait_fill(10, "BUY<ask");
        check128("BUY<ask golden fill", fill_frame, GF_BUY_BELOW);
        @(posedge clk); #1;

        // 3) SELL at bid → FILLED
        send_order(128'h201801A3F7F4004B0002006600000000);
        wait_fill(10, "SELL@bid");
        check128("SELL@bid golden fill", fill_frame, GF_SELL_AT_BID);
        @(posedge clk); #1;

        // 4) SELL above bid → REJECTED
        send_order(128'h201801A3F7F500190003006700000000);
        wait_fill(10, "SELL>bid");
        check128("SELL>bid golden fill", fill_frame, GF_SELL_ABOVE);
        @(posedge clk); #1;

        // 5) Out-of-range symbol → REJECTED
        send_order(128'h204000C80000000A0004006800000000);
        wait_fill(10, "OOR sym");
        check128("OOR golden fill", fill_frame, GF_OOR_SYM4);
        @(posedge clk); #1;

        // 6) BUY sym=3 above ask → FILLED at ask
        send_order(128'h20300074080F00C80005006900000000);
        wait_fill(10, "BUY sym3");
        check128("BUY sym3 golden fill", fill_frame, GF_BUY_SYM3);
        @(posedge clk); #1;

        // Verify counters
        check32("orders_rcvd=6", orders_rcvd, 6);
        check32("fills_sent=3", fills_sent, 3);
        check32("rejects_sent=3", rejects_sent, 3);

        // ─────────────────────────────────────────────────────
        // 7) Boundary: BUY exactly at ask (1 tick)
        // ─────────────────────────────────────────────────────
        $display("--- test_boundary ---");
        // Exactly at ask = FILL
        send_order(build_order(8'd0, 1'b0, G_ASK[0], 16'd10, 16'd10, 16'h1111));
        wait_fill(10, "exact ask");
        check("exact ask: FILLED", fill_frame[114:112] == 3'b000);
        check32("exact ask: price=ask", fill_frame[111:80], G_ASK[0]);
        @(posedge clk); #1;

        // One tick below ask = REJECT
        send_order(build_order(8'd0, 1'b0, G_ASK[0]-1, 16'd10, 16'd11, 16'h2222));
        wait_fill(10, "below ask");
        check("below ask: REJECTED", fill_frame[114:112] == 3'b001);
        @(posedge clk); #1;

        // SELL exactly at bid = FILL
        send_order(build_order(8'd0, 1'b1, G_BID[0], 16'd10, 16'd12, 16'h3333));
        wait_fill(10, "exact bid");
        check("exact bid: FILLED", fill_frame[114:112] == 3'b000);
        check32("exact bid: price=bid", fill_frame[111:80], G_BID[0]);
        @(posedge clk); #1;

        // One tick above bid = REJECT
        send_order(build_order(8'd0, 1'b1, G_BID[0]+1, 16'd10, 16'd13, 16'h4444));
        wait_fill(10, "above bid");
        check("above bid: REJECTED", fill_frame[114:112] == 3'b001);
        @(posedge clk); #1;

        // ─────────────────────────────────────────────────────
        // 8) counter_clr: all counters reset
        // ─────────────────────────────────────────────────────
        $display("--- test_counter_clr ---");
        counter_clr_sig = 1'b1;
        @(posedge clk); #1;
        counter_clr_sig = 1'b0;
        @(posedge clk); #1;
        check32("clr: orders_rcvd=0", orders_rcvd, 0);
        check32("clr: fills_sent=0", fills_sent, 0);
        check32("clr: rejects_sent=0", rejects_sent, 0);
        check("clr: fill_valid=0", fill_valid == 1'b0);

        // ─────────────────────────────────────────────────────
        // 9) enable=0: orders not processed
        // ─────────────────────────────────────────────────────
        $display("--- test_enable_low ---");
        enable = 1'b0;
        send_order(build_order(8'd0, 1'b0, G_ASK[0], 16'd10, 16'd20, 16'h5555));
        no_fill_for(5, "enable=0");
        check32("enable=0: orders_rcvd still 0", orders_rcvd, 0);
        enable = 1'b1;
        @(posedge clk); #1;

        // ─────────────────────────────────────────────────────
        // 10) Fill backpressure: fill_ready=0
        // ─────────────────────────────────────────────────────
        $display("--- test_backpressure ---");
        fill_ready = 1'b0;
        send_order(build_order(8'd0, 1'b0, G_ASK[0], 16'd5, 16'd30, 16'hAAAA));
        wait_fill(10, "bp fill");
        repeat (4) begin
            @(posedge clk); #1;
            check("bp: fill_valid held", fill_valid == 1'b1);
            check("bp: frame stable", fill_frame[63:48] == 16'd30);
        end
        fill_ready = 1'b1;
        @(posedge clk); #1;
        check("bp: consumed", fill_valid == 1'b0);

        // ─────────────────────────────────────────────────────
        // 11) Wrong msg_type: QUOTE frame → ignored
        // ─────────────────────────────────────────────────────
        $display("--- test_wrong_msg_type ---");
        begin
            logic [COUNTER_W-1:0] ord_before;
            ord_before = orders_rcvd;
            order_frame = {4'h1, 124'hAAAA_BBBB_CCCC_DDDD_EEEE_FFFF_0000_000};
            order_valid = 1'b1;
            @(posedge clk); #1;
            order_valid = 1'b0;
            no_fill_for(5, "wrong msg");
            check("wrong msg: orders_rcvd unchanged", orders_rcvd == ord_before);
        end

        // ─────────────────────────────────────────────────────
        // 12) Rapid back-to-back orders
        // ─────────────────────────────────────────────────────
        $display("--- test_back_to_back ---");
        send_order(build_order(8'd0, 1'b0, G_ASK[0], 16'd1, 16'd40, 16'hB001));
        wait_fill(10, "b2b first");
        check("b2b first: oid=40", fill_frame[63:48] == 16'd40);
        @(posedge clk); #1;
        send_order(build_order(8'd1, 1'b1, G_BID[1], 16'd2, 16'd41, 16'hB002));
        wait_fill(10, "b2b second");
        check("b2b second: oid=41", fill_frame[63:48] == 16'd41);
        @(posedge clk); #1;

        // ─────────────────────────────────────────────────────
        // 13) Symbol routing: sym=3
        // ─────────────────────────────────────────────────────
        $display("--- test_sym3 ---");
        send_order(build_order(8'd3, 1'b0, G_ASK[3], 16'd7, 16'd50, 16'hCC00));
        wait_fill(10, "sym3");
        check("sym3: fill_price=ask[3]", fill_frame[111:80] == G_ASK[3]);
        check("sym3: FILLED", fill_frame[114:112] == 3'b000);
        @(posedge clk); #1;

        // ─────────────────────────────────────────────────────
        // Summary
        // ─────────────────────────────────────────────────────
        $display("\n===================================");
        if (fail_count == 0)
            $display("tb_exchange_lite: PASS (%0d checks passed)", pass_count);
        else begin
            $display("tb_exchange_lite: FAIL (%0d passed, %0d failed)", pass_count, fail_count);
            $fatal;
        end
        $display("===================================");
        $finish;
    end

endmodule
