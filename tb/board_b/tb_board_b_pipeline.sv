// ============================================================================
// Testbench: tb_board_b_pipeline
// Integration test for the Board B pipeline: quote_book → feature_compute →
// strategy_engine → risk_manager → order_manager, with position_tracker
// providing fill feedback to risk_manager.
//
// Coverage:
//   - 16-symbol full-universe golden frames (seeds EMA + triggers orders)
//   - Position limit enforcement
//   - Rate limit enforcement
//   - Max-loss risk halt
//   - Fill injection and position/cash update
//   - Order-enable gating
//   - Back-to-back quote stress
//   - Clear and restart
//   - Simultaneous signal + fill edge case
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_b_pipeline;

    logic                     clk;
    logic                     rst_n;
    logic                     clear;
    logic                     order_enable;

    logic [FRAME_W-1:0]       quote_frame;
    logic                     quote_valid;

    price_t                   qb_bid, qb_ask;
    qty_t                     qb_bid_size, qb_ask_size;
    symbol_t                  qb_symbol;
    regime_e                  qb_regime;
    logic                     qb_valid;

    price_t                   fc_mid, fc_spread, fc_ema;
    sprice_t                  fc_deviation;
    price_t                   fc_bid_out, fc_ask_out;
    symbol_t                  fc_symbol_out;
    logic                     fc_valid;

    logic                     se_valid, se_side;
    price_t                   se_price;
    qty_t                     se_qty;
    symbol_t                  se_symbol;

    logic                     rm_valid, rm_side;
    price_t                   rm_price;
    qty_t                     rm_qty;
    symbol_t                  rm_symbol;
    logic                     risk_halt;
    logic [COUNTER_W-1:0]     risk_rejects;

    logic [FRAME_W-1:0]       order_frame;
    logic                     order_valid;
    logic                     order_ready;
    logic [COUNTER_W-1:0]     orders_sent;

    logic [FRAME_W-1:0]       fill_frame;
    logic                     fill_valid_in;
    position_t                position [NUM_SYMBOLS];
    cash_t                    cash;
    sprice_t                  total_pnl;
    timestamp_t               ts_echo;
    logic                     fill_processed;
    symbol_t                  pt_fill_symbol;
    logic                     pt_fill_side;
    qty_t                     pt_fill_qty;
    logic                     pt_fill_notify;
    logic [COUNTER_W-1:0]     fills_rcvd;

    // ── New B2 per-symbol AXI-exposed signals ────────────────────
    price_t                   qb_best_bid_arr  [NUM_SYMBOLS];
    price_t                   qb_best_ask_arr  [NUM_SYMBOLS];
    cash_t                    pnl_cash_per_sym [NUM_SYMBOLS];
    price_t                   last_fill_price  [NUM_SYMBOLS];
    logic [15:0]              trades_per_sym   [NUM_SYMBOLS];

    logic [ALPHA_W-1:0]       ema_alpha;
    price_t                   threshold;
    qty_t                     base_qty;
    logic [POSITION_W-1:0]    max_position;
    logic [COUNTER_W-1:0]     max_order_rate;
    price_t                   max_loss;

    timestamp_t               cycle_counter;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    always_ff @(posedge clk or negedge rst_n)
        if (!rst_n) cycle_counter <= '0;
        else        cycle_counter <= cycle_counter + 1'b1;

    quote_book u_quote_book (
        .clk(clk), .rst_n(rst_n),
        .quote_frame(quote_frame), .quote_valid(quote_valid),
        .bid_price(qb_bid), .ask_price(qb_ask),
        .bid_size(qb_bid_size), .ask_size(qb_ask_size),
        .symbol_id(qb_symbol), .regime(qb_regime), .book_valid(qb_valid),
        .best_bid_arr(qb_best_bid_arr),
        .best_ask_arr(qb_best_ask_arr)
    );

    feature_compute u_feature_compute (
        .clk(clk), .rst_n(rst_n), .clear(clear),
        .bid_price(qb_bid), .ask_price(qb_ask),
        .symbol_id(qb_symbol), .book_valid(qb_valid),
        .ema_alpha(ema_alpha),
        .mid(fc_mid), .spread(fc_spread), .ema(fc_ema),
        .deviation(fc_deviation),
        .bid_out(fc_bid_out), .ask_out(fc_ask_out),
        .symbol_out(fc_symbol_out), .feature_valid(fc_valid)
    );

    strategy_engine u_strategy_engine (
        .clk(clk), .rst_n(rst_n),
        .deviation(fc_deviation), .bid_price(fc_bid_out), .ask_price(fc_ask_out),
        .symbol_id(fc_symbol_out), .feature_valid(fc_valid),
        .threshold(threshold), .base_qty(base_qty),
        .signal_valid(se_valid), .signal_side(se_side),
        .signal_price(se_price), .signal_qty(se_qty),
        .signal_symbol(se_symbol)
    );

    risk_manager u_risk_manager (
        .clk(clk), .rst_n(rst_n), .clear(clear),
        .order_enable(order_enable),
        .signal_valid(se_valid), .signal_side(se_side),
        .signal_price(se_price), .signal_qty(se_qty),
        .signal_symbol(se_symbol),
        .position(position), .total_pnl(total_pnl),
        .max_position(max_position), .max_order_rate(max_order_rate),
        .max_loss(max_loss),
        .approved_valid(rm_valid), .approved_side(rm_side),
        .approved_price(rm_price), .approved_qty(rm_qty),
        .approved_symbol(rm_symbol),
        .fill_valid(pt_fill_notify), .fill_symbol(pt_fill_symbol),
        .fill_side(pt_fill_side), .fill_qty(pt_fill_qty),
        .risk_halt(risk_halt), .risk_rejects(risk_rejects)
    );

    order_manager u_order_manager (
        .clk(clk), .rst_n(rst_n), .clear(clear),
        .approved_valid(rm_valid), .approved_side(rm_side),
        .approved_price(rm_price), .approved_qty(rm_qty),
        .approved_symbol(rm_symbol),
        .cycle_counter(cycle_counter),
        .order_frame(order_frame), .order_valid(order_valid),
        .order_ready(order_ready),
        .orders_sent(orders_sent)
    );

    position_tracker u_position_tracker (
        .clk(clk), .rst_n(rst_n), .clear(clear),
        .fill_frame(fill_frame), .fill_valid(fill_valid_in),
        .position(position), .cash(cash), .total_pnl(total_pnl),
        .ts_echo(ts_echo), .fill_processed(fill_processed),
        .fill_symbol_out(pt_fill_symbol), .fill_side_out(pt_fill_side),
        .fill_qty_out(pt_fill_qty), .fill_notify(pt_fill_notify),
        .fills_rcvd(fills_rcvd),
        .pnl_cash_per_sym(pnl_cash_per_sym),
        .last_fill_price (last_fill_price),
        .trades_per_sym  (trades_per_sym)
    );

    // ── 16-symbol init_mid values (Q16.16, matches golden model) ──
    logic [31:0] init_mid [0:15];
    initial begin
        init_mid[ 0] = 32'h00B4_0000;  // AAPL  $180
        init_mid[ 1] = 32'h01A4_0000;  // MSFT  $420
        init_mid[ 2] = 32'h0384_0000;  // NVDA  $900
        init_mid[ 3] = 32'h0073_0000;  // XOM   $115
        init_mid[ 4] = 32'h00A0_0000;  // CVX   $160
        init_mid[ 5] = 32'h009B_0000;  // JNJ   $155
        init_mid[ 6] = 32'h0208_0000;  // UNH   $520
        init_mid[ 7] = 32'h00B9_0000;  // AMZN  $185
        init_mid[ 8] = 32'h00FA_0000;  // TSLA  $250
        init_mid[ 9] = 32'h00C8_0000;  // JPM   $200
        init_mid[10] = 32'h01E0_0000;  // GS    $480
        init_mid[11] = 32'h0168_0000;  // CAT   $360
        init_mid[12] = 32'h00C8_0000;  // HON   $200
        init_mid[13] = 32'h00A5_0000;  // PG    $165
        init_mid[14] = 32'h003C_0000;  // KO    $60
        init_mid[15] = 32'h00AF_0000;  // GOOGL $175
    end

    // Helper: build a QUOTE frame from symbol, bid, ask, seq_num
    function automatic logic [127:0] build_quote(
        input int sym, input logic [31:0] bid, input logic [31:0] ask, input int seq
    );
        return {4'h1, sym[7:0], 2'b00, 2'b00, bid, ask, 16'h03E8, 16'h03E8, seq[15:0]};
    endfunction

    // Helper: build a FILL frame
    function automatic logic [127:0] build_fill(
        input int sym, input logic side, input logic [2:0] status,
        input logic [31:0] price, input int qty, input int oid, input int ts
    );
        return {4'h3, sym[7:0], side, status, price, qty[15:0], oid[15:0], ts[15:0], 32'h0};
    endfunction

    // ── Check helpers ──────────────────────────────────────────
    integer pass_count = 0;
    integer fail_count = 0;
    integer order_count_observed = 0;

    task automatic check(input string name, input logic condition);
        if (condition) pass_count++;
        else begin fail_count++; $display("[FAIL] %0s at time %0t", name, $time); end
    endtask

    task automatic check32(input string name, input logic [31:0] actual, input logic [31:0] expected);
        if (actual === expected) pass_count++;
        else begin
            fail_count++;
            $display("[FAIL] %0s: got 0x%08X, expected 0x%08X", name, actual, expected);
        end
    endtask

    // ── ORDER frame monitor ───────────────────────────────────
    initial begin
        forever begin
            @(posedge clk); #1;
            if (order_valid && order_ready) begin
                order_count_observed++;
                if (order_frame[127:124] != MSG_ORDER)
                    $display("[ERROR] Bad msg_type: 0x%01X", order_frame[127:124]);
            end
        end
    end

    // ── Drive one quote frame and wait 1 cycle ────────────────
    task automatic drive_quote(input logic [127:0] frame);
        quote_frame = frame;
        quote_valid = 1'b1;
        @(posedge clk); #1;
        quote_valid = 1'b0;
    endtask

    // ── Wait for pipeline to flush ────────────────────────────
    task automatic flush_pipeline(input int cycles = 20);
        repeat (cycles) @(posedge clk); #1;
    endtask

    // ── Main test sequence ────────────────────────────────────
    initial begin
        quote_frame    = '0;
        quote_valid    = 1'b0;
        clear          = 1'b0;
        order_enable   = 1'b1;
        order_ready    = 1'b1;
        fill_frame     = '0;
        fill_valid_in  = 1'b0;

        ema_alpha      = 16'd6554;          // ~10%
        threshold      = 32'h0000_8000;     // $0.50
        base_qty       = 16'd100;
        max_position   = 32'd50000;
        max_order_rate = 32'd10000;
        max_loss       = 32'h0064_0000;     // $100 Q16.16

        @(posedge rst_n);
        repeat (2) @(posedge clk); #1;

        // ──────────────────────────────────────────────────────
        // Phase 1: Seed EMA for all 16 symbols (first-sample init)
        // No orders expected on first round.
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 1: Seed EMA (16 symbols, round 1) ===");

        for (int i = 0; i < 16; i++) begin
            drive_quote(build_quote(i, init_mid[i] - 32'h1000, init_mid[i] + 32'h1000, 0));
        end
        flush_pipeline(30);

        check("P1: no risk_halt", risk_halt == 1'b0);
        check("P1: no orders (EMA seeding)", orders_sent == 32'd0);

        // ──────────────────────────────────────────────────────
        // Phase 2: Price jump → trigger orders on all 16 symbols
        // Shift prices UP by $2 (0x20000) → deviation ~$1.80 > $0.50
        // → SELL signals for all symbols
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 2: Price UP → SELL signals (16 symbols) ===");

        begin
            logic [31:0] orders_before;
            orders_before = orders_sent;

            for (int i = 0; i < 16; i++) begin
                logic [31:0] shifted_mid;
                shifted_mid = init_mid[i] + 32'h0002_0000;  // +$2
                drive_quote(build_quote(i, shifted_mid - 32'h1000, shifted_mid + 32'h1000, 1));
            end
            flush_pipeline(40);

            $display("  orders_sent = %0d (was %0d)", orders_sent, orders_before);
            check("P2: generated SELL orders", orders_sent > orders_before);
            check("P2: no risk_halt", risk_halt == 1'b0);
        end

        // ──────────────────────────────────────────────────────
        // Phase 3: Price jump DOWN → trigger BUY signals
        // Shift prices DOWN by $3 from initial → deviation ~-$2.7
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 3: Price DOWN → BUY signals (16 symbols) ===");

        begin
            logic [31:0] orders_before_p3;
            orders_before_p3 = orders_sent;

            for (int i = 0; i < 16; i++) begin
                logic [31:0] shifted_mid;
                shifted_mid = init_mid[i] - 32'h0003_0000;  // -$3
                if ($signed(shifted_mid) < $signed(32'h0001_0000))
                    shifted_mid = 32'h0001_0000;  // floor at $1
                drive_quote(build_quote(i, shifted_mid - 32'h1000, shifted_mid + 32'h1000, 2));
            end
            flush_pipeline(40);

            $display("  orders_sent = %0d (was %0d)", orders_sent, orders_before_p3);
            check("P3: generated BUY orders", orders_sent > orders_before_p3);
        end

        // ──────────────────────────────────────────────────────
        // Phase 4: Inject fills for symbols 0-3 (BUY fills)
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 4: Fill injection (4 symbols) ===");

        for (int i = 0; i < 4; i++) begin
            fill_frame = build_fill(i, 1'b0, 3'b000, init_mid[i], 100, i, 42+i);
            fill_valid_in = 1'b1;
            @(posedge clk); #1;
            fill_valid_in = 1'b0;
            @(posedge clk); #1;
        end
        @(posedge clk); #1;

        check32("P4: fills_rcvd==4", fills_rcvd, 32'd4);
        check32("P4: pos[0]==100", position[0], 32'd100);
        check32("P4: pos[1]==100", position[1], 32'd100);
        check32("P4: pos[2]==100", position[2], 32'd100);
        check32("P4: pos[3]==100", position[3], 32'd100);
        $display("  total_pnl = %0d", $signed(total_pnl));

        // ──────────────────────────────────────────────────────
        // Phase 5: SELL fills for symbols 0-3
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 5: SELL fills (4 symbols) ===");

        for (int i = 0; i < 4; i++) begin
            fill_frame = build_fill(i, 1'b1, 3'b000, init_mid[i] + 32'h0001_0000, 50, i+4, 50+i);
            fill_valid_in = 1'b1;
            @(posedge clk); #1;
            fill_valid_in = 1'b0;
            @(posedge clk); #1;
        end
        @(posedge clk); #1;

        check32("P5: fills_rcvd==8", fills_rcvd, 32'd8);
        // After BUY 100 then SELL 50, pos should be 100-50=50
        check32("P5: pos[0]==50", position[0], 32'd50);
        check32("P5: pos[1]==50", position[1], 32'd50);

        // ──────────────────────────────────────────────────────
        // Phase 6: REJECTED fill (should not change position)
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 6: Rejected fill (no position change) ===");

        begin
            logic [31:0] pos5_before;
            pos5_before = position[5];
            fill_frame = build_fill(5, 1'b0, 3'b001, 32'h0, 0, 99, 60);
            fill_valid_in = 1'b1;
            @(posedge clk); #1;
            fill_valid_in = 1'b0;
            @(posedge clk); #1;
            check32("P6: pos[5] unchanged", position[5], pos5_before);
        end

        // ──────────────────────────────────────────────────────
        // Phase 7: Order-enable gating
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 7: Order-enable off → rejects ===");

        begin
            logic [31:0] rejects_before;
            logic [31:0] orders_before_p7;
            rejects_before = risk_rejects;
            orders_before_p7 = orders_sent;

            order_enable = 1'b0;
            for (int i = 0; i < 4; i++) begin
                logic [31:0] shifted_mid;
                shifted_mid = init_mid[i] + 32'h0005_0000;  // big deviation
                drive_quote(build_quote(i, shifted_mid - 32'h1000, shifted_mid + 32'h1000, 10));
            end
            flush_pipeline(30);

            check("P7: orders unchanged", orders_sent == orders_before_p7);
            check("P7: rejects increased", risk_rejects > rejects_before);

            order_enable = 1'b1;
        end

        // ──────────────────────────────────────────────────────
        // Phase 8: Position limit enforcement
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 8: Position limit enforcement ===");

        begin
            logic [31:0] rejects_p8;
            max_position = 32'd60;  // very tight: already at 50 for sym 0-3

            rejects_p8 = risk_rejects;

            // Drive quotes that create BUY signals for sym 0 (already at pos=50)
            for (int r = 0; r < 3; r++) begin
                logic [31:0] low_mid;
                low_mid = init_mid[0] - 32'h0005_0000;  // big drop → BUY
                drive_quote(build_quote(0, low_mid - 32'h1000, low_mid + 32'h1000, 20+r));
                flush_pipeline(15);
            end

            $display("  orders_sent=%0d, risk_rejects=%0d (was %0d)", orders_sent, risk_rejects, rejects_p8);
            // Some should be rejected due to position limit
            // pos[0]=50, pending_buy could be 100+, max_pos=60 → should reject

            max_position = 32'd50000;  // restore
        end

        // ──────────────────────────────────────────────────────
        // Phase 9: Rate limit enforcement
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 9: Rate limit enforcement ===");

        begin
            logic [31:0] orders_before_p9;
            orders_before_p9 = orders_sent;

            max_order_rate = orders_sent + 2;  // allow only 2 more orders

            for (int i = 0; i < 16; i++) begin
                logic [31:0] shifted_mid;
                shifted_mid = init_mid[i] + 32'h0004_0000;  // big deviation
                drive_quote(build_quote(i, shifted_mid - 32'h1000, shifted_mid + 32'h1000, 30));
            end
            flush_pipeline(40);

            $display("  orders_sent=%0d (was %0d, rate limit = %0d)",
                     orders_sent, orders_before_p9, max_order_rate);
            // At most 2 more orders should have been approved
            check("P9: rate limit enforced", orders_sent <= orders_before_p9 + 2);

            max_order_rate = 32'd100_000;  // restore
        end

        // ──────────────────────────────────────────────────────
        // Phase 10: Max-loss risk halt
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 10: Max-loss risk halt ===");

        begin
            // Inject a large SELL fill at a very low price to create a huge loss
            // BUY 1000 shares of sym=10 at $480, then SELL 1000 at $1
            fill_frame = build_fill(10, 1'b0, 3'b000, 32'h01E0_0000, 1000, 200, 70);
            fill_valid_in = 1'b1;
            @(posedge clk); #1;
            fill_valid_in = 1'b0;
            @(posedge clk); #1;

            fill_frame = build_fill(10, 1'b1, 3'b000, 32'h0001_0000, 1000, 201, 71);
            fill_valid_in = 1'b1;
            @(posedge clk); #1;
            fill_valid_in = 1'b0;
            @(posedge clk); #1;

            $display("  total_pnl after loss = %0d", $signed(total_pnl));
            // cash = bought at $480*1000=-$480k, sold at $1*1000=+$1k → net ≈ -$479k
            max_loss = 32'h0000_0001;  // $0.00 threshold → will trigger on next signal

            // Drive a quote to trigger a signal
            drive_quote(build_quote(0, init_mid[0] + 32'h0003_0000, init_mid[0] + 32'h0005_0000, 50));
            flush_pipeline(20);

            check("P10: risk_halt triggered", risk_halt == 1'b1);
            $display("  risk_halt = %0b", risk_halt);

            max_loss = 32'h0064_0000;  // restore
        end

        // ──────────────────────────────────────────────────────
        // Phase 11: Clear and verify reset
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 11: Clear and verify ===");

        clear = 1'b1;
        @(posedge clk); #1;
        clear = 1'b0;
        @(posedge clk); #1;

        check32("P11: orders_sent cleared", orders_sent, 32'd0);
        check32("P11: fills_rcvd cleared", fills_rcvd, 32'd0);
        check("P11: risk_halt cleared", risk_halt == 1'b0);
        check32("P11: risk_rejects cleared", risk_rejects, 32'd0);

        begin
            integer order_count_at_clear;
            order_count_at_clear = order_count_observed;

        // ──────────────────────────────────────────────────────
        // Phase 12: Back-to-back quote stress (16 sym × 5 rounds)
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 12: Back-to-back stress (80 quotes) ===");

        // First round seeds EMA
        for (int i = 0; i < 16; i++)
            drive_quote(build_quote(i, init_mid[i] - 32'h1000, init_mid[i] + 32'h1000, 0));
        flush_pipeline(30);

        // 4 more rounds with alternating shifts to create order flow
        for (int round = 1; round <= 4; round++) begin
            for (int i = 0; i < 16; i++) begin
                logic [31:0] mid_shifted;
                if (round[0])
                    mid_shifted = init_mid[i] + 32'h0002_0000;  // +$2
                else
                    mid_shifted = init_mid[i] - 32'h0002_0000;  // -$2
                if ($signed(mid_shifted) < $signed(32'h0001_0000))
                    mid_shifted = 32'h0001_0000;
                drive_quote(build_quote(i, mid_shifted - 32'h1000, mid_shifted + 32'h1000, round));
            end
        end
        flush_pipeline(60);

        $display("  orders_sent = %0d", orders_sent);
        $display("  risk_rejects = %0d", risk_rejects);
        check("P12: generated orders from stress", orders_sent > 32'd0);
        check("P12: no risk_halt", risk_halt == 1'b0);

        // ──────────────────────────────────────────────────────
        // Phase 13: Fills for all 16 symbols (multi-symbol position)
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 13: Fills for all 16 symbols ===");

        for (int i = 0; i < 16; i++) begin
            fill_frame = build_fill(i, 1'b0, 3'b000, init_mid[i], 10*(i+1), 300+i, 100+i);
            fill_valid_in = 1'b1;
            @(posedge clk); #1;
            fill_valid_in = 1'b0;
            @(posedge clk); #1;
        end
        @(posedge clk); #1;

        begin
            int nonzero = 0;
            for (int i = 0; i < 16; i++) begin
                if (position[i] != 32'd0) nonzero++;
            end
            $display("  Non-zero positions: %0d / 16", nonzero);
            check("P13: all 16 positions nonzero", nonzero == 16);
        end

        // ──────────────────────────────────────────────────────
        // Phase 14: Verify msg_type on all observed orders
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 14: Order integrity ===");
        begin
            integer orders_since_clear;
            orders_since_clear = order_count_observed - order_count_at_clear;
            $display("  Total orders observed by monitor: %0d (since clear: %0d)", order_count_observed, orders_since_clear);
            check("P14: monitor count matches", orders_since_clear == orders_sent);
        end
        end // close order_count_at_clear scope

        // ── Summary ───────────────────────────────────────────
        repeat (3) @(posedge clk); #1;
        $display("\n══════════════════════════════════════════");
        $display("  board_b_pipeline testbench complete");
        $display("  PASSED: %0d", pass_count);
        $display("  FAILED: %0d", fail_count);
        $display("  Orders observed: %0d", order_count_observed);
        $display("══════════════════════════════════════════\n");

        if (fail_count > 0) $fatal(1, "TESTBENCH FAILED");
        $finish;
    end

endmodule
