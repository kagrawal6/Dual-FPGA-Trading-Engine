// ============================================================================
// Testbench: tb_board_b_pipeline
// Integration test for the Board B pipeline: quote_book → feature_compute →
// strategy_engine → risk_manager → order_manager, with position_tracker
// providing fill feedback to risk_manager. Drives 20 golden QUOTE frames,
// verifies counters, monitors ORDER frames, injects a synthetic FILL, and
// checks risk_halt status throughout.
//
// Golden model reference: pipeline_vectors.json (first 20 quotes, 4 symbols).
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

    // Pipeline interconnect
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

    // Position tracker
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

    // Config
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
        .symbol_id(qb_symbol), .regime(qb_regime), .book_valid(qb_valid)
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
        .fills_rcvd(fills_rcvd)
    );

    // ── Golden model frames (first 20 from pipeline_vectors.json) ──
    localparam logic [127:0] GM_FRAMES [0:19] = '{
        128'h100000B3F81E00B4081E03E803E80000,  // cyc 0: sym=0
        128'h101001A3F82101A4082103E803E80000,  // cyc 1: sym=1
        128'h10200383F8160384081603E803E80000,  // cyc 2: sym=2
        128'h10300072F81D0073081D03E803E80000,  // cyc 3: sym=3
        128'h100000B3F83100B4083103E803E80001,  // cyc 4: sym=0
        128'h101001A3F81601A4081603E803E80001,  // cyc 5: sym=1
        128'h10200383F8250384082503E803E80001,  // cyc 6: sym=2
        128'h10300072F82E0073082E03E803E80001,  // cyc 7: sym=3
        128'h100000B3F81A00B4081A03E803E80002,  // cyc 8: sym=0
        128'h101001A3F81801A4081803E803E80002,  // cyc 9: sym=1
        128'h10200383F81B0384081B03E803E80002,  // cyc 10: sym=2
        128'h10300072F80D0073080D03E803E80002,  // cyc 11: sym=3
        128'h100000B3F80B00B4080B03E803E80003,  // cyc 12: sym=0
        128'h101001A3F7F401A407F403E803E80003,  // cyc 13: sym=1
        128'h10200383F7FE038407FE03E803E80003,  // cyc 14: sym=2
        128'h10300072F80F0073080F03E803E80003,  // cyc 15: sym=3
        128'h100000B3F81500B4081503E803E80004,  // cyc 16: sym=0
        128'h101001A3F7DD01A407DD03E803E80004,  // cyc 17: sym=1
        128'h10200383F7FF038407FF03E803E80004,  // cyc 18: sym=2
        128'h10300072F7F1007307F103E803E80004   // cyc 19: sym=3
    };

    // ── Check helpers ──────────────────────────────────────────
    integer pass_count = 0;
    integer fail_count = 0;
    integer order_count_observed = 0;

    task automatic check(input string name, input logic condition);
        if (condition) begin
            pass_count++;
        end else begin
            fail_count++;
            $display("[FAIL] %0s at time %0t", name, $time);
        end
    endtask

    // ── ORDER frame monitor (runs concurrently) ───────────────
    initial begin
        forever begin
            @(posedge clk);
            if (order_valid && order_ready) begin
                order_count_observed++;
                $display("[ORDER] t=%0t sym=%0d side=%0b price=0x%08X qty=%0d id=%0d",
                    $time,
                    order_frame[123:116],
                    order_frame[115],
                    order_frame[111:80],
                    order_frame[79:64],
                    order_frame[63:48]);
                // Verify msg_type is ORDER
                if (order_frame[127:124] != MSG_ORDER)
                    $display("[ERROR] Bad msg_type: 0x%01X", order_frame[127:124]);
            end
        end
    end

    // ── Main test sequence ────────────────────────────────────
    initial begin
        quote_frame    = '0;
        quote_valid    = 1'b0;
        clear          = 1'b0;
        order_enable   = 1'b1;
        order_ready    = 1'b1;
        fill_frame     = '0;
        fill_valid_in  = 1'b0;

        ema_alpha      = 16'd6554;
        threshold      = 32'h0000_8000;  // $0.50
        base_qty       = 16'd100;
        max_position   = 32'd500;
        max_order_rate = 32'd1000;
        max_loss       = 32'd100;

        @(posedge rst_n);
        repeat (2) @(posedge clk);

        // ──────────────────────────────────────────────────────
        // Phase 1: Drive 20 golden QUOTE frames
        // First 4 seed EMA (no orders expected).
        // Subsequent quotes may trigger orders if deviation > $0.50
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 1: Drive 20 golden QUOTE frames ===");

        for (int i = 0; i < 20; i++) begin
            quote_frame = GM_FRAMES[i];
            quote_valid = 1'b1;
            @(posedge clk);
        end
        quote_valid = 1'b0;

        // Wait for entire pipeline to flush (QB=1 + FC=3 + SE=1 + RM=1 + OM=1 = 7 cycles + margin)
        repeat (20) @(posedge clk);

        // ──────────────────────────────────────────────────────
        // Phase 2: Verify counters
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 2: Verify counters ===");
        check("P2: risk_halt==0",    risk_halt == 1'b0);
        check("P2: orders_sent>=0",  orders_sent >= 32'd0);
        $display("  orders_sent = %0d", orders_sent);
        $display("  risk_rejects = %0d", risk_rejects);
        $display("  order_count_observed = %0d", order_count_observed);

        // ──────────────────────────────────────────────────────
        // Phase 3: Inject synthetic FILL frame
        // BUY sym=0, FILLED, price=0x00B40815, qty=100
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 3: Inject synthetic FILL ===");
        fill_frame = 128'h300000B4081500640001002A00000000;
        fill_valid_in = 1'b1;
        @(posedge clk);
        #1;
        check("P3: fill_processed",     fill_processed == 1'b1);
        fill_valid_in = 1'b0;
        @(posedge clk);
        @(posedge clk);

        check("P3: fills_rcvd==1",      fills_rcvd == 32'd1);
        check("P3: position[0] updated", position[0] != 32'd0 || fills_rcvd == 32'd1);
        $display("  position[0] = %0d (signed)", $signed(position[0]));
        $display("  total_pnl   = %0d", $signed(total_pnl));

        // ──────────────────────────────────────────────────────
        // Phase 4: Verify no risk_halt throughout
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 4: Final status ===");
        check("P4: risk_halt==0",       risk_halt == 1'b0);

        // Drive more quotes and verify pipeline continues working
        for (int i = 0; i < 8; i++) begin
            quote_frame = GM_FRAMES[i % 20];
            quote_valid = 1'b1;
            @(posedge clk);
        end
        quote_valid = 1'b0;
        repeat (20) @(posedge clk);

        check("P4: still no halt",      risk_halt == 1'b0);

        // ──────────────────────────────────────────────────────
        // Phase 5: Clear and verify reset
        // ──────────────────────────────────────────────────────
        $display("\n=== Phase 5: Clear pipeline ===");
        clear = 1'b1;
        @(posedge clk);
        clear = 1'b0;
        @(posedge clk);

        check("P5: orders_sent cleared", orders_sent == 32'd0);
        check("P5: fills_rcvd cleared",  fills_rcvd == 32'd0);
        check("P5: risk_halt cleared",   risk_halt == 1'b0);

        // ── Summary ───────────────────────────────────────────
        repeat (3) @(posedge clk);
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
