// ============================================================================
// Testbench: tb_nn_inference
//
// Unit-level functional verification of the parallel NN strategy module.
//   1. Reset behavior — all outputs zero, signal_valid deasserted.
//   2. Pipeline latency — for an isolated `feature_valid` pulse, the NN's
//      `signal_valid` (when it fires at all) appears exactly 4 clock cycles
//      later, never sooner.
//   3. Symbol gating — for any symbol_id >= 8 the NN must NEVER assert
//      signal_valid (training only covers symbols 0..7).
//   4. Regime gating — the NN must NEVER assert signal_valid when the
//      current regime is CALM (00) or BURST (10); only VOLATILE (01) and
//      ADVERSARIAL (11) are tradable.
//   5. Tag propagation — when signal_valid fires, signal_qty == base_qty,
//      signal_symbol matches the input symbol from 4 cycles prior, and
//      signal_price equals the bid OR ask of that same cycle (depending
//      on side). This catches any pipeline-symbol scrambling.
//   6. Liveness — over a long random feature stream restricted to
//      tradable (symbol<8, regime ∈ {VOLATILE, ADVERSARIAL}) inputs the
//      NN must produce at least one BUY and one SELL signal, proving
//      the trained weights actually fire (a fully-zero output would
//      mean the weight ROM was misloaded).
//
// We do NOT compare logits against a software reference here — that is
// future work. The tests above catch the structural integration bugs we
// actually care about for this merge (latency, gating, tag pairing).
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_nn_inference;

    // ── DUT I/O ─────────────────────────────────────────────────
    logic        clk;
    logic        rst_n;

    sprice_t     deviation;
    price_t      bid_price;
    price_t      ask_price;
    symbol_t     symbol_id;
    logic        feature_valid;
    qty_t        base_qty;
    price_t      spread;
    sprice_t     mid_delta;
    sprice_t     ema_delta;
    logic signed [31:0] position;
    logic [1:0]  regime;
    sprice_t     entry_mid;
    logic [7:0]  holding_time;
    logic [31:0] max_position;

    logic        signal_valid;
    logic        signal_side;
    price_t      signal_price;
    qty_t        signal_qty;
    symbol_t     signal_symbol;

    // ── Clock + reset ───────────────────────────────────────────
    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    nn_inference dut (
        .clk(clk), .rst_n(rst_n),
        .deviation(deviation),
        .bid_price(bid_price), .ask_price(ask_price),
        .symbol_id(symbol_id), .feature_valid(feature_valid),
        .base_qty(base_qty),
        .spread(spread),
        .mid_delta(mid_delta), .ema_delta(ema_delta),
        .position(position), .regime(regime),
        .entry_mid(entry_mid), .holding_time(holding_time),
        .max_position(max_position),
        .signal_valid(signal_valid), .signal_side(signal_side),
        .signal_price(signal_price), .signal_qty(signal_qty),
        .signal_symbol(signal_symbol)
    );

    // ── Pass/fail tracking ──────────────────────────────────────
    integer pass_count = 0;
    integer fail_count = 0;

    task automatic check(input string name, input logic condition);
        if (condition) begin
            pass_count++;
        end else begin
            fail_count++;
            $display("[FAIL] %0s at time %0t", name, $time);
        end
    endtask

    // ── Drive helper ────────────────────────────────────────────
    task automatic drive_one(
        input bit              fv,
        input symbol_t         sym,
        input price_t          bid,
        input price_t          ask,
        input logic [1:0]      reg_,
        input sprice_t         dev,
        input sprice_t         mdelt,
        input sprice_t         edelt,
        input logic signed [31:0] pos,
        input sprice_t         entry,
        input logic [7:0]      hold
    );
        @(negedge clk);
        feature_valid = fv;
        symbol_id     = sym;
        bid_price     = bid;
        ask_price     = ask;
        regime        = reg_;
        deviation     = dev;
        spread        = ask - bid;
        mid_delta     = mdelt;
        ema_delta     = edelt;
        position      = pos;
        entry_mid     = entry;
        holding_time  = hold;
    endtask

    // ── Per-cycle history shifter (for tag-propagation check) ──
    // The NN has 4 register stages — we record the 4-cycles-old input
    // alongside each clock edge so we can compare it against signal_*
    // when signal_valid asserts.
    typedef struct packed {
        logic     fv;
        symbol_t  sym;
        price_t   bid;
        price_t   ask;
        logic [1:0] reg_;
        qty_t     qty;
    } in_snap_t;

    // History buffer + liveness counters. We use plain `always @(posedge clk)`
    // (NOT `always_ff`) because ModelSim's strict always_ff driver check
    // (vlog-7061) forbids these variables being driven by both an `initial`
    // block and an `always_ff` block. Functionally these blocks are still
    // synchronous, edge-triggered processes — they just opt out of the
    // exclusive-driver enforcement so we can seed them in `initial`.
    in_snap_t hist [0:5];
    integer   buy_count;
    integer   sell_count;
    integer   fire_count;

    initial begin
        buy_count  = 0;
        sell_count = 0;
        fire_count = 0;
        for (int i = 0; i < 6; i++) hist[i] = '0;
    end

    always @(posedge clk) begin
        // Shift history at every clock edge so hist[4] is "4 cycles ago"
        for (int i = 5; i > 0; i--) hist[i] <= hist[i-1];
        hist[0].fv   <= feature_valid;
        hist[0].sym  <= symbol_id;
        hist[0].bid  <= bid_price;
        hist[0].ask  <= ask_price;
        hist[0].reg_ <= regime;
        hist[0].qty  <= base_qty;
    end

    // ── Pipeline-latency monitor ────────────────────────────────
    // For any signal_valid pulse, the corresponding feature_valid must
    // have been high exactly 4 cycles earlier (hist[4]).
    always @(posedge clk) begin
        if (rst_n && signal_valid) begin
            fire_count = fire_count + 1;
            if (signal_side == 1'b0) buy_count  = buy_count  + 1;
            else                     sell_count = sell_count + 1;

            // 1. Latency check
            check($sformatf("LIVE@%0t: feature_valid was high 4 cycles ago", $time),
                  hist[4].fv === 1'b1);

            // 2. Symbol-gate check
            check($sformatf("LIVE@%0t: signal_symbol < 8 (sym=%0d)", $time, signal_symbol),
                  signal_symbol < 8);

            // 3. Regime-gate check (only VOLATILE/ADVERSARIAL = 01 or 11)
            check($sformatf("LIVE@%0t: regime tradable (reg=%0d)", $time, hist[4].reg_),
                  hist[4].reg_ === 2'b01 || hist[4].reg_ === 2'b11);

            // 4. Tag-propagation: symbol must match input from 4 cycles ago.
            check($sformatf("LIVE@%0t: signal_symbol==hist[4].sym (got %0d, exp %0d)",
                            $time, signal_symbol, hist[4].sym),
                  signal_symbol === hist[4].sym);

            // 5. Quantity == base_qty from 4 cycles ago.
            check($sformatf("LIVE@%0t: signal_qty==base_qty (got %0d, exp %0d)",
                            $time, signal_qty, hist[4].qty),
                  signal_qty === hist[4].qty);

            // 6. Price is bid (SELL) or ask (BUY) from 4 cycles ago.
            if (signal_side == 1'b0)
                check($sformatf("LIVE@%0t: BUY signal_price==hist[4].ask", $time),
                      signal_price === hist[4].ask);
            else
                check($sformatf("LIVE@%0t: SELL signal_price==hist[4].bid", $time),
                      signal_price === hist[4].bid);
        end
    end

    // ── Test sequence ───────────────────────────────────────────
    initial begin
        $display("=== tb_nn_inference: NN strategy unit checks ===");

        feature_valid = 1'b0;
        symbol_id = '0; bid_price = '0; ask_price = '0; regime = 2'b00;
        deviation = '0; spread = '0; mid_delta = '0; ema_delta = '0;
        position = '0; entry_mid = '0; holding_time = '0;
        base_qty = 16'd10;
        max_position = 32'd100;

        @(posedge rst_n);
        repeat (8) @(posedge clk); #1;

        // ────────────────────────────────────────────────────────
        // Phase 1: Reset behavior
        // ────────────────────────────────────────────────────────
        $display("\n--- Phase 1: post-reset values ---");
        check("P1: signal_valid==0 after reset",  signal_valid  === 1'b0);
        check("P1: signal_side==0 after reset",   signal_side   === 1'b0);
        check("P1: signal_price==0 after reset",  signal_price  === '0);
        check("P1: signal_qty==0 after reset",    signal_qty    === '0);
        check("P1: signal_symbol==0 after reset", signal_symbol === '0);

        // ────────────────────────────────────────────────────────
        // Phase 2: Pipeline latency — single pulse + drain
        // ────────────────────────────────────────────────────────
        $display("\n--- Phase 2: pipeline latency (4 cycles) ---");
        // For cycles 1..3 after the pulse, signal_valid MUST stay low.
        // (At cycle 4 the always_ff above will check the latency property
        // if the NN decides to fire — which it may or may not on a single
        // synthetic input.)
        drive_one(1'b1, 8'd2, 32'h00B40000, 32'h00B40400, 2'b01,
                  -32'sd16384, 32'sd1024, 32'sd512, 32'sd0, 32'sd0, 8'd0);
        @(posedge clk); #1;
        drive_one(1'b0, '0, '0, '0, 2'b00, '0, '0, '0, '0, '0, '0);

        @(posedge clk); #1;
        check("P2: signal_valid==0 after +1 cycle", signal_valid === 1'b0);
        @(posedge clk); #1;
        check("P2: signal_valid==0 after +2 cycles", signal_valid === 1'b0);
        @(posedge clk); #1;
        check("P2: signal_valid==0 after +3 cycles", signal_valid === 1'b0);
        // After +4 cycles signal_valid may fire or stay 0 — both legal
        // depending on weights; we only check the property in the always_ff.

        repeat (8) @(posedge clk); #1;

        // ────────────────────────────────────────────────────────
        // Phase 3: Symbol gating — sym >= 8 must never fire signal_valid
        // ────────────────────────────────────────────────────────
        $display("\n--- Phase 3: symbol gating (sym >= 8 → no signal) ---");
        begin
            int saw_fire_sym_high;
            saw_fire_sym_high = 0;
            for (int s = 8; s < 16; s++) begin
                drive_one(1'b1, s[7:0],
                          32'h00640000, 32'h00640200, 2'b11, // ADVERSARIAL
                          -32'sd32768, 32'sd2048, 32'sd1024, 32'sd5,
                          32'sd0, 8'd3);
                @(posedge clk); #1;
                drive_one(1'b0, '0, '0, '0, 2'b00, '0, '0, '0, '0, '0, '0);
                // Wait through the 4-stage pipeline plus margin
                repeat (6) begin
                    @(posedge clk); #1;
                    if (signal_valid && signal_symbol >= 8)
                        saw_fire_sym_high = saw_fire_sym_high + 1;
                end
            end
            check("P3: no NN fire for any symbol >= 8", saw_fire_sym_high == 0);
        end

        repeat (8) @(posedge clk); #1;

        // ────────────────────────────────────────────────────────
        // Phase 4: Regime gating — CALM and BURST must never fire
        // ────────────────────────────────────────────────────────
        $display("\n--- Phase 4: regime gating (CALM, BURST → no signal) ---");
        begin
            int saw_fire_bad_regime;
            int last_count_at_phase_start;
            saw_fire_bad_regime = 0;
            last_count_at_phase_start = fire_count;
            // CALM (00)
            for (int i = 0; i < 8; i++) begin
                drive_one(1'b1, 8'(i % 8),
                          32'h00B40000, 32'h00B40400, 2'b00,
                          -32'sd16384, 32'sd1024, 32'sd512, 32'sd0,
                          32'sd0, 8'd0);
                @(posedge clk); #1;
            end
            // BURST (10)
            for (int i = 0; i < 8; i++) begin
                drive_one(1'b1, 8'(i % 8),
                          32'h01000000, 32'h01000800, 2'b10,
                          32'sd32768, 32'sd2048, -32'sd1024, 32'sd0,
                          32'sd0, 8'd0);
                @(posedge clk); #1;
            end
            drive_one(1'b0, '0, '0, '0, 2'b00, '0, '0, '0, '0, '0, '0);
            repeat (8) @(posedge clk); #1;
            // Any fires recorded since phase start would have been caught
            // by the always_ff regime check; here we additionally insist
            // that fire_count did NOT advance — i.e. zero firings on bad
            // regime.
            check("P4: zero NN fires across CALM+BURST batch",
                  fire_count == last_count_at_phase_start);
        end

        // ────────────────────────────────────────────────────────
        // Phase 5: Liveness — random tradable stream produces some BUY+SELL
        // ────────────────────────────────────────────────────────
        $display("\n--- Phase 5: liveness on tradable stream ---");
        begin
            int fires_at_start;
            int buys_at_start;
            int sells_at_start;
            sprice_t dev_v;
            int      idx_local;
            fires_at_start  = fire_count;
            buys_at_start   = buy_count;
            sells_at_start  = sell_count;
            for (int i = 0; i < 400; i++) begin
                idx_local = i;
                // Symbol in 0..7, regime alternates VOLATILE / ADVERSARIAL.
                // Sweep deviation across a wide signed range so the NN
                // sees both "below EMA" (BUY-friendly) and "above EMA"
                // (SELL-friendly) inputs.
                if (idx_local & 1) dev_v = -32'sd65536 * (idx_local % 8 + 1);
                else               dev_v =  32'sd65536 * (idx_local % 8 + 1);
                drive_one(1'b1, 8'(idx_local & 7),
                          32'h00B40000 + idx_local * 32'd16,
                          32'h00B40400 + idx_local * 32'd16,
                          (idx_local & 1) ? 2'b01 : 2'b11,
                          dev_v,
                          32'sd512 * (idx_local & 3),
                          -32'sd512 * (idx_local & 3),
                          32'sd0,
                          32'sd0,
                          8'(idx_local & 8'hFF));
                @(posedge clk); #1;
            end
            drive_one(1'b0, '0, '0, '0, 2'b00, '0, '0, '0, '0, '0, '0);
            repeat (8) @(posedge clk); #1;

            $display("P5: fires=%0d (BUY=%0d, SELL=%0d) over 400 inputs",
                     fire_count - fires_at_start,
                     buy_count - buys_at_start,
                     sell_count - sells_at_start);
            check("P5: at least one BUY in 400 tradable inputs",
                  buy_count - buys_at_start >= 1);
            check("P5: at least one SELL in 400 tradable inputs",
                  sell_count - sells_at_start >= 1);
        end

        // ────────────────────────────────────────────────────────
        // Summary
        // ────────────────────────────────────────────────────────
        $display("\n==============================");
        $display("tb_nn_inference: PASSED: %0d", pass_count);
        $display("tb_nn_inference: FAILED: %0d", fail_count);
        $display("==============================");
        if (fail_count == 0)
            $display("tb_nn_inference: PASS (%0d checks passed)", pass_count);
        else
            $display("tb_nn_inference: TESTBENCH FAILED (%0d failed)", fail_count);
        $finish;
    end

    initial begin
        #500us;
        $display("tb_nn_inference: TESTBENCH FAILED (timeout)");
        $finish;
    end

endmodule
