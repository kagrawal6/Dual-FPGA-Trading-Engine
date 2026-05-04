// ============================================================================
// Testbench: tb_nn_inference
//
// Unit-level functional verification of the time-multiplexed NN strategy
// module. The post-merge `nn_inference` runs each layer over 4 phases
// (one slice per cycle) and only releases h*_valid for one cycle when its
// last slice writes — yielding a monitor-visible pipeline latency of
// ~16 cycles (top capture 1 + L0 4 + L1 4 + L2 4 + output gate 1, plus
// inter-stage handoff slack). The TB encodes this as PIPE_LATENCY = 16
// and uses parametric drain windows so future depth tweaks need only
// updating that constant.
//
//   1. Reset behavior — all outputs zero, signal_valid deasserted.
//   2. Pipeline latency — for an isolated `feature_valid` pulse, the NN's
//      `signal_valid` (when it fires at all) appears no sooner than
//      PIPE_LATENCY clocks later, never before.
//   3. Symbol gating — for any symbol_id >= 4 the NN must NEVER assert
//      signal_valid (post-merge RTL gates h2_sym < 4).
//   4. Regime gating — the NN must NEVER assert signal_valid when the
//      regime captured at input time was CALM (00) or BURST (10); only
//      VOLATILE (01) and ADVERSARIAL (11) are tradable. The RTL pipelines
//      regime through h*_regime, so the gate sees the source-cycle's
//      regime, not the live input.
//   5. Liveness — over a long random feature stream restricted to
//      tradable (symbol<4, regime ∈ {VOLATILE, ADVERSARIAL}) inputs the
//      NN must fire at least once, proving the trained 4-bit-quantised
//      weights actually drive the argmax (a fully-zero output would
//      mean the weight ROM was misloaded).
//   6. Position-aware sanity — flat (position=0) vs long (position=large)
//      feature vectors must both produce well-defined (no-X) outputs.
//      We do NOT require disagreement; we only require liveness + no Xs.
//   7. Mid-pipeline reset — let a captured input advance partway through
//      the L0/L1/L2 sequence, then assert rst_n LOW. signal_valid must
//      stay 0 throughout the reset interval AND for a full pipe-fill
//      window after release (with no new inputs).
//   8. Saturated continuous stream (backpressure stress) — drive
//      feature_valid HIGH every clock for 200 cycles. The top FSM only
//      accepts a new input when computing==0, so most are dropped. The
//      monitor still validates every fire (using the source-cycle
//      snapshot at hist[PIPE_LATENCY-1]) and we assert >=1 fire to
//      detect a jammed pipeline.
//
//   Tag propagation invariant (checked on EVERY fire across all phases):
//      - signal_qty   == base_qty of the source cycle
//      - signal_symbol matches input symbol from PIPE_LATENCY-1 cycles ago
//      - signal_price equals the bid OR ask of that same cycle
//      - source-cycle's feature_valid was high (no fires from drops/X)
//      - source-cycle's regime was tradable (matches the gate's view)
//
// We do NOT compare logits against a software reference here — that is
// future work. The tests above catch the structural integration bugs we
// actually care about for this merge (latency, gating, tag pairing,
// position channel wired, reset-clean, sustained throughput).
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
    //
    // The post-merge time-multiplexed NN has a much deeper pipeline than the
    // original 4-stage parallel version. Each layer runs over 4 phases (one
    // slice per cycle) and only releases h*_valid for one cycle when its
    // last slice writes. Tracing the FSMs (top capture + L0/L1/L2 phase
    // counters + output gate):
    //
    //   posedge T          monitor sees feature_valid=1
    //   posedge T+1..T+4   top FSM phase 0..3, l0 slices written
    //   posedge T+5        h0_valid pulse, l1_computing handoff
    //   posedge T+6..T+9   l1 slices written; T+9 produces h1_valid pulse
    //   posedge T+10       h1 -> l2 handoff
    //   posedge T+11..T+14 l2 slices written; T+14 produces h2_valid pulse
    //   posedge T+15       output gate samples h2_valid + h2_regime
    //                       and asserts signal_valid <= 1 (NBA)
    //   posedge T+16       monitor sees signal_valid = 1
    //
    // So source input is `PIPE_LATENCY - 1` shifts deep in hist[] when the
    // monitor observes signal_valid. Also: the new RTL gates the output on
    // `h2_regime` (the regime captured at INPUT time and pipelined), not the
    // live `regime` input — so the regime check uses the SAME hist depth as
    // the symbol/price tag-prop checks (no off-by-one race anymore).
    localparam int PIPE_LATENCY = 16;     // monitor-visible latency in cycles
    localparam int HIST_DEPTH   = PIPE_LATENCY + 4;  // small extra margin

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
    in_snap_t hist [0:HIST_DEPTH-1];
    integer   buy_count;
    integer   sell_count;
    integer   fire_count;

    initial begin
        buy_count  = 0;
        sell_count = 0;
        fire_count = 0;
        for (int i = 0; i < HIST_DEPTH; i++) hist[i] = '0;
    end

    always @(posedge clk) begin
        // Shift history at every clock edge so hist[N] is "N cycles ago"
        for (int i = HIST_DEPTH-1; i > 0; i--) hist[i] <= hist[i-1];
        hist[0].fv   <= feature_valid;
        hist[0].sym  <= symbol_id;
        hist[0].bid  <= bid_price;
        hist[0].ask  <= ask_price;
        hist[0].reg_ <= regime;
        hist[0].qty  <= base_qty;
    end

    // ── Pipeline-latency monitor ────────────────────────────────
    always @(posedge clk) begin
        if (rst_n && signal_valid) begin : firing_check
            // Source-cycle snapshot for this fire (PIPE_LATENCY-1 shifts back).
            automatic in_snap_t src = hist[PIPE_LATENCY-1];

            fire_count = fire_count + 1;
            if (signal_side == 1'b0) buy_count  = buy_count  + 1;
            else                     sell_count = sell_count + 1;

            // 1. Latency check -- the input that produced this signal must
            //    have had feature_valid asserted (and must NOT have been
            //    backpressure-dropped by the top FSM).
            check($sformatf("LIVE@%0t: feature_valid was high for source cycle", $time),
                  src.fv === 1'b1);

            // 2. Symbol-gate check. New RTL gates on h2_sym < 4 (not < 8).
            check($sformatf("LIVE@%0t: signal_symbol < 4 (sym=%0d)", $time, signal_symbol),
                  signal_symbol < 4);

            // 3. Regime-gate check. The new RTL pipelines the regime as
            //    h0_regime -> h1_regime -> h2_regime, and the output stage
            //    gates on h2_regime — i.e. the regime captured AT input
            //    time. So we compare against the source-cycle's regime
            //    (PIPE_LATENCY-1 shifts back), same depth as symbol/price.
            check($sformatf("LIVE@%0t: regime tradable at source (reg=%0d)",
                            $time, src.reg_),
                  src.reg_ === 2'b01 || src.reg_ === 2'b11);

            // 4. Tag-propagation: symbol must match input from source cycle.
            check($sformatf("LIVE@%0t: signal_symbol==src.sym (got %0d, exp %0d)",
                            $time, signal_symbol, src.sym),
                  signal_symbol === src.sym);

            // 5. Quantity == base_qty from source cycle.
            check($sformatf("LIVE@%0t: signal_qty==base_qty (got %0d, exp %0d)",
                            $time, signal_qty, src.qty),
                  signal_qty === src.qty);

            // 6. Price is ask (BUY) or bid (SELL) from source cycle.
            if (signal_side == 1'b0)
                check($sformatf("LIVE@%0t: BUY signal_price==src.ask", $time),
                      signal_price === src.ask);
            else
                check($sformatf("LIVE@%0t: SELL signal_price==src.bid", $time),
                      signal_price === src.bid);
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
        $display($sformatf("\n--- Phase 2: pipeline latency (%0d cycles) ---", PIPE_LATENCY));
        // For cycles 1..PIPE_LATENCY-2 after the pulse, signal_valid MUST
        // stay low. At cycle PIPE_LATENCY-1 the source input has just begun
        // exiting the L2 stage, so the NEXT cycle (PIPE_LATENCY) is the
        // earliest legal observation of signal_valid=1.  At cycle
        // PIPE_LATENCY+1 the pulse has dropped (single-cycle output).
        drive_one(1'b1, 8'd2, 32'h00B40000, 32'h00B40400, 2'b01,
                  -32'sd16384, 32'sd1024, 32'sd512, 32'sd0, 32'sd0, 8'd0);
        @(posedge clk); #1;
        drive_one(1'b0, '0, '0, '0, 2'b00, '0, '0, '0, '0, '0, '0);

        for (int k = 1; k <= PIPE_LATENCY-2; k++) begin
            @(posedge clk); #1;
            check($sformatf("P2: signal_valid==0 after +%0d cycles", k),
                  signal_valid === 1'b0);
        end
        // From cycle PIPE_LATENCY-1 onward signal_valid may fire (if the
        // NN argmaxes to BUY/SELL on this synthetic input) or stay 0.
        // Either is legal; the always-monitor enforces the latency
        // property if it does fire.

        repeat (PIPE_LATENCY + 4) @(posedge clk); #1;

        // ────────────────────────────────────────────────────────
        // Phase 3: Symbol gating — sym >= 4 must never fire signal_valid
        // (post-merge RTL tightened the gate to symbols 0-3 only)
        // ────────────────────────────────────────────────────────
        $display("\n--- Phase 3: symbol gating (sym >= 4 → no signal) ---");
        begin
            int saw_fire_sym_high;
            saw_fire_sym_high = 0;
            for (int s = 4; s < 16; s++) begin
                drive_one(1'b1, s[7:0],
                          32'h00640000, 32'h00640200, 2'b11, // ADVERSARIAL
                          -32'sd32768, 32'sd2048, 32'sd1024, 32'sd5,
                          32'sd0, 8'd3);
                @(posedge clk); #1;
                drive_one(1'b0, '0, '0, '0, 2'b00, '0, '0, '0, '0, '0, '0);
                // Wait through the full pipeline plus a margin so each
                // symbol's would-be fire window has fully elapsed before
                // we drive the next symbol.
                repeat (PIPE_LATENCY + 4) begin
                    @(posedge clk); #1;
                    if (signal_valid && signal_symbol >= 4)
                        saw_fire_sym_high = saw_fire_sym_high + 1;
                end
            end
            check("P3: no NN fire for any symbol >= 4", saw_fire_sym_high == 0);
        end

        repeat (PIPE_LATENCY + 4) @(posedge clk); #1;

        // ────────────────────────────────────────────────────────
        // Phase 4: Regime gating — CALM and BURST must never fire
        // ────────────────────────────────────────────────────────
        $display("\n--- Phase 4: regime gating (CALM, BURST → no signal) ---");
        begin
            int last_count_at_phase_start;
            last_count_at_phase_start = fire_count;
            // CALM (00) -- symbols restricted to 0..3 so the only thing
            // that can possibly block a fire is the regime gate itself.
            for (int i = 0; i < 16; i++) begin
                drive_one(1'b1, 8'(i % 4),
                          32'h00B40000, 32'h00B40400, 2'b00,
                          -32'sd16384, 32'sd1024, 32'sd512, 32'sd0,
                          32'sd0, 8'd0);
                @(posedge clk); #1;
            end
            // BURST (10)
            for (int i = 0; i < 16; i++) begin
                drive_one(1'b1, 8'(i % 4),
                          32'h01000000, 32'h01000800, 2'b10,
                          32'sd32768, 32'sd2048, -32'sd1024, 32'sd0,
                          32'sd0, 8'd0);
                @(posedge clk); #1;
            end
            drive_one(1'b0, '0, '0, '0, 2'b00, '0, '0, '0, '0, '0, '0);
            // Drain through the full pipeline before checking the count.
            repeat (PIPE_LATENCY + 4) @(posedge clk); #1;
            // Any fires recorded since phase start would have been caught
            // by the always-monitor regime check above; here we additionally
            // insist that fire_count did NOT advance — zero firings on bad
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
                // Symbol in 0..3 (post-merge gate), regime alternates
                // VOLATILE / ADVERSARIAL. Sweep deviation across a wide
                // signed range so the NN sees both "below EMA"
                // (BUY-friendly) and "above EMA" (SELL-friendly) inputs.
                if (idx_local & 1) dev_v = -32'sd65536 * (idx_local % 8 + 1);
                else               dev_v =  32'sd65536 * (idx_local % 8 + 1);
                drive_one(1'b1, 8'(idx_local & 3),
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
            repeat (PIPE_LATENCY + 4) @(posedge clk); #1;

            $display("P5: fires=%0d (BUY=%0d, SELL=%0d) over 400 inputs",
                     fire_count - fires_at_start,
                     buy_count - buys_at_start,
                     sell_count - sells_at_start);
            // The NN must fire at least once on a tradable stream -- this
            // catches a misloaded weight ROM (always-HOLD) or a dead pipeline.
            // We deliberately do NOT require both BUY and SELL: the trained
            // weights may argmax to a single side on this synthetic input
            // pattern, which is fine (the policy is data-driven).
            check("P5: NN fires at least once on tradable stream",
                  (buy_count - buys_at_start) + (sell_count - sells_at_start) >= 1);
        end

        // ────────────────────────────────────────────────────────
        // Phase 6: Position-aware sanity
        //   Drive identical price/feature inputs twice -- once flat
        //   (position=0) and once long (position=+max). Both runs must
        //   stay X-free and produce countable output statistics. We do
        //   NOT require the two runs to disagree (the trained net might
        //   choose the same action), but we do log the counts so a
        //   human can see the position channel actually moves the
        //   policy in interesting cases.
        // ────────────────────────────────────────────────────────
        $display("\n--- Phase 6: position-aware sanity ---");
        begin
            int flat_fires;
            int long_fires;
            int saw_x_flat;
            int saw_x_long;
            int phase_start_count;

            // -- Subphase 6a: flat position (0) --
            phase_start_count = fire_count;
            saw_x_flat = 0;
            for (int i = 0; i < 64; i++) begin
                drive_one(1'b1, 8'(i & 3),
                          32'h00B40000 + 32'(i << 4),
                          32'h00B40400 + 32'(i << 4),
                          (i & 1) ? 2'b01 : 2'b11,
                          (i & 1) ? -32'sd32768 : 32'sd32768,
                          32'sd512, -32'sd512,
                          32'sd0,                 // position = FLAT
                          32'sd0, 8'd0);
                @(posedge clk); #1;
                if (signal_valid === 1'bx ||
                    signal_side  === 1'bx ||
                    ^signal_price === 1'bx ||
                    ^signal_qty   === 1'bx)
                    saw_x_flat = saw_x_flat + 1;
            end
            drive_one(1'b0, '0, '0, '0, 2'b00, '0, '0, '0, '0, '0, '0);
            repeat (PIPE_LATENCY + 4) @(posedge clk); #1;
            flat_fires = fire_count - phase_start_count;
            check("P6a: no X on outputs (flat run)", saw_x_flat == 0);

            // -- Subphase 6b: long position (+90 of max=100), same prices --
            phase_start_count = fire_count;
            saw_x_long = 0;
            for (int i = 0; i < 64; i++) begin
                drive_one(1'b1, 8'(i & 3),
                          32'h00B40000 + 32'(i << 4),
                          32'h00B40400 + 32'(i << 4),
                          (i & 1) ? 2'b01 : 2'b11,
                          (i & 1) ? -32'sd32768 : 32'sd32768,
                          32'sd512, -32'sd512,
                          32'sd90,                // position = LONG (near max)
                          32'sd0, 8'd25);         // also non-zero holding_time
                @(posedge clk); #1;
                if (signal_valid === 1'bx ||
                    signal_side  === 1'bx ||
                    ^signal_price === 1'bx ||
                    ^signal_qty   === 1'bx)
                    saw_x_long = saw_x_long + 1;
            end
            drive_one(1'b0, '0, '0, '0, 2'b00, '0, '0, '0, '0, '0, '0);
            repeat (PIPE_LATENCY + 4) @(posedge clk); #1;
            long_fires = fire_count - phase_start_count;
            check("P6b: no X on outputs (long run)", saw_x_long == 0);

            $display("P6: flat_fires=%0d long_fires=%0d (informational)",
                     flat_fires, long_fires);
        end

        // ────────────────────────────────────────────────────────
        // Phase 7: Mid-pipeline reset
        //   Prime the pipeline with valid inputs, advance partway
        //   through the time-multiplexed L0/L1/L2 sequence, then yank
        //   rst_n LOW while data is in flight. signal_valid must be 0
        //   throughout the reset interval and during the post-release
        //   pipe-fill window before any new input is presented.
        // ────────────────────────────────────────────────────────
        $display("\n--- Phase 7: mid-pipeline reset ---");
        begin
            int saw_fire_during_reset;
            int saw_fire_in_drain;
            saw_fire_during_reset = 0;
            saw_fire_in_drain     = 0;

            // Prime the pipeline: drive 5 valid inputs spaced enough
            // (one per cycle) to ensure the first one has been captured
            // and is mid-way through L0/L1/L2.
            for (int i = 0; i < 5; i++) begin
                drive_one(1'b1, 8'(i % 4),
                          32'h00B40000, 32'h00B40400, 2'b11,
                          -32'sd32768, 32'sd1024, 32'sd512,
                          32'sd5, 32'sd0, 8'd2);
                @(posedge clk); #1;
            end
            // Let the captured input advance a few stages
            drive_one(1'b0, '0, '0, '0, 2'b00, '0, '0, '0, '0, '0, '0);
            repeat (PIPE_LATENCY/2) @(posedge clk); #1;

            // Yank reset mid-flight
            rst_n = 1'b0;
            for (int j = 0; j < PIPE_LATENCY + 4; j++) begin
                @(posedge clk); #1;
                if (signal_valid === 1'b1)
                    saw_fire_during_reset = saw_fire_during_reset + 1;
            end
            check("P7: no signal_valid pulse while rst_n is LOW",
                  saw_fire_during_reset == 0);

            // Release reset, verify outputs cleared and pipeline empty
            rst_n = 1'b1;
            @(posedge clk); #1;
            check("P7: signal_valid==0 immediately after rst release",
                  signal_valid === 1'b0);
            check("P7: signal_side ==0 after rst release",
                  signal_side  === 1'b0);
            check("P7: signal_price==0 after rst release",
                  signal_price === '0);

            // Drain a full pipeline depth post-reset with NO new inputs
            // - no spurious fires allowed.
            for (int j = 0; j < PIPE_LATENCY + 2; j++) begin
                @(posedge clk); #1;
                if (signal_valid === 1'b1)
                    saw_fire_in_drain = saw_fire_in_drain + 1;
            end
            check("P7: no spurious fire during empty drain post-reset",
                  saw_fire_in_drain == 0);
        end

        // ────────────────────────────────────────────────────────
        // Phase 8: Saturated continuous stream (backpressure stress)
        //   Drive feature_valid HIGH for 200 consecutive cycles -- one
        //   tradable quote per clock, sustained throughput. The
        //   time-multiplexed top FSM only accepts a new input when
        //   `computing==0`, so back-to-back fv=1 inputs are dropped
        //   while a layer-0/1/2 batch is in flight. Roughly 1 in
        //   ~5 inputs ends up captured at steady state. The
        //   per-fire monitor (always @posedge clk above) still checks
        //   every invariant on every signal_valid pulse using
        //   hist[PIPE_LATENCY-1] as the source snapshot, which
        //   correctly identifies the captured (not dropped) input.
        // ────────────────────────────────────────────────────────
        $display("\n--- Phase 8: saturated continuous stream (backpressure) ---");
        begin
            int fires_at_start;
            int phase_fires;
            sprice_t dev_v;
            fires_at_start = fire_count;

            for (int i = 0; i < 200; i++) begin
                if (i & 1) dev_v = -32'sd16384 * (i % 4 + 1);
                else       dev_v =  32'sd16384 * (i % 4 + 1);
                drive_one(1'b1, 8'(i & 3),
                          32'h00C00000 + 32'(i << 6),
                          32'h00C00400 + 32'(i << 6),
                          (i & 1) ? 2'b01 : 2'b11,
                          dev_v,
                          32'sd256, -32'sd256,
                          32'sd0,
                          32'sd0,
                          8'(i & 8'hFF));
                @(posedge clk); #1;
                // No drive_one(0) gap -- back-to-back valid every cycle
            end
            drive_one(1'b0, '0, '0, '0, 2'b00, '0, '0, '0, '0, '0, '0);
            repeat (PIPE_LATENCY + 4) @(posedge clk); #1;

            phase_fires = fire_count - fires_at_start;
            $display("P8: fires=%0d over 200 back-to-back valid cycles",
                     phase_fires);
            check("P8: pipeline produced at least 1 fire under sustained load",
                  phase_fires >= 1);
            // With the time-multiplexed pipeline + backpressure, only
            // ~1-in-5 of these 200 inputs is captured -- so a healthy
            // pipeline yields on the order of ~10-30 fires here. The
            // exact number is trained-weight-dependent, so we only
            // assert ">=1" but log the count for inspection.
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
