// ============================================================================
// Testbench: tb_board_a_axi_regs
//
// Direct unit test for the Board A AXI-Lite slave register file. Mirrors
// the structure of tb_board_b_axi_regs so failures in the Board A register
// map surface in a focused 5-second sim instead of the much larger
// tb_board_a_top integration test.
//
// Coverage (one phase per group):
//   T1  Scalar config writes + readbacks (QUOTE_INTERVAL, LFSR_SEED, REGIME)
//   T2  CTRL pulses (start, reset) -- single-cycle pulse semantics
//   T3  STATUS register packing (running, link_up, regime, fifo_fill)
//   T4  Read-only counter readbacks (quotes/orders/fills/rejects/link_errors)
//   T5  Per-symbol INIT_MID write + readback
//   T6  Per-symbol INIT_SPREAD write + readback (0 -> 1 saturation rule)
//   T7  Per-symbol SECTOR_ID write + readback
//   T8  TOKEN_PACK -- two 16-bit tokens packed per 32-bit word
//   T9  ACTIVE_SYM_COUNT clamping (0 -> 1, > NUM_SYM -> NUM_SYM)
//   T10 Reset clears all writable state to defaults
//   T11 B3 per-symbol LIVE_BID readback
//   T12 B3 per-symbol LIVE_ASK readback
//   T13 B3 per-symbol LIVE_MID readback
//   T14 Address space sanity -- unmapped reads return 0
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_a_axi_regs;

    // Use the same NUM_SYM the Board A top runs with so the address ranges
    // match what tb_board_a_top would see.
    localparam int TB_NUM_SYM = 16;
    localparam int ADDR_W     = 9;

    // ── DUT I/O ─────────────────────────────────────────────────
    logic clk, rst_n;

    // AXI-Lite
    logic [ADDR_W-1:0] awaddr, araddr;
    logic [2:0]        awprot, arprot;
    logic              awvalid, arvalid;
    logic              awready, arready;
    logic [31:0]       wdata, rdata;
    logic [3:0]        wstrb;
    logic              wvalid, wready;
    logic [1:0]        bresp, rresp;
    logic              bvalid, bready;
    logic              rvalid, rready;

    // DUT-driven outputs
    logic                       axi_start_pulse, axi_reset_pulse;
    regime_e                    regime_from_ps;
    logic [31:0]                quote_interval, lfsr_seed;
    price_t                     sym_init_mid       [TB_NUM_SYM];
    price_t                     sym_init_spread    [TB_NUM_SYM];
    logic [SECTOR_ID_W-1:0]     sym_sector_id      [TB_NUM_SYM];
    logic [15:0]                sym_company_token  [TB_NUM_SYM];
    logic [7:0]                 active_sym_count;

    // Status inputs we drive from the TB
    logic                       running, link_up;
    regime_e                    active_regime;
    logic [COUNTER_W-1:0]       quotes_sent, orders_rcvd, fills_sent;
    logic [COUNTER_W-1:0]       rejects_sent, link_errors;
    logic [6:0]                 fifo_fill;

    // B3 live price snapshots
    price_t                     live_bid [TB_NUM_SYM];
    price_t                     live_ask [TB_NUM_SYM];
    price_t                     live_mid [TB_NUM_SYM];

    // ── Clock + reset ───────────────────────────────────────────
    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    // ── DUT ─────────────────────────────────────────────────────
    board_a_axi_regs #(.NUM_SYM(TB_NUM_SYM)) dut (
        .clk(clk), .rst_n(rst_n),
        .s_axi_awaddr(awaddr), .s_axi_awprot(awprot),
        .s_axi_awvalid(awvalid), .s_axi_awready(awready),
        .s_axi_wdata(wdata), .s_axi_wstrb(wstrb),
        .s_axi_wvalid(wvalid), .s_axi_wready(wready),
        .s_axi_bresp(bresp), .s_axi_bvalid(bvalid), .s_axi_bready(bready),
        .s_axi_araddr(araddr), .s_axi_arprot(arprot),
        .s_axi_arvalid(arvalid), .s_axi_arready(arready),
        .s_axi_rdata(rdata), .s_axi_rresp(rresp),
        .s_axi_rvalid(rvalid), .s_axi_rready(rready),
        .axi_start_pulse(axi_start_pulse), .axi_reset_pulse(axi_reset_pulse),
        .regime_from_ps(regime_from_ps),
        .quote_interval(quote_interval), .lfsr_seed(lfsr_seed),
        .sym_init_mid(sym_init_mid), .sym_init_spread(sym_init_spread),
        .sym_sector_id(sym_sector_id), .sym_company_token(sym_company_token),
        .active_sym_count(active_sym_count),
        .running(running), .link_up(link_up), .active_regime(active_regime),
        .quotes_sent(quotes_sent), .orders_rcvd(orders_rcvd),
        .fills_sent(fills_sent), .rejects_sent(rejects_sent),
        .link_errors(link_errors), .fifo_fill(fifo_fill),
        .live_bid(live_bid), .live_ask(live_ask), .live_mid(live_mid)
    );

    // ── Pass/fail tracking ──────────────────────────────────────
    integer pass_count = 0;
    integer fail_count = 0;

    task automatic check(input string name, input logic condition);
        if (condition) pass_count++;
        else begin
            fail_count++;
            $display("[FAIL] %0s at %0t", name, $time);
        end
    endtask

    task automatic check32(input string name,
                           input logic [31:0] got,
                           input logic [31:0] exp);
        if (got === exp) pass_count++;
        else begin
            fail_count++;
            $display("[FAIL] %0s : got 0x%08x exp 0x%08x at %0t",
                     name, got, exp, $time);
        end
    endtask

    // ── AXI helpers (mirror tb_board_b_axi_regs flow) ───────────
    task automatic axi_write(input logic [ADDR_W-1:0] addr,
                             input logic [31:0] data);
        awaddr  = addr;
        awvalid = 1'b1;
        wdata   = data;
        wstrb   = 4'hF;
        wvalid  = 1'b1;
        @(posedge clk);
        awvalid = 1'b0;
        wvalid  = 1'b0;
        bready  = 1'b1;
        @(posedge clk);
        while (!bvalid) @(posedge clk);
        @(posedge clk);
        bready = 1'b0;
    endtask

    task automatic axi_read(input  logic [ADDR_W-1:0] addr,
                            output logic [31:0]       data);
        araddr  = addr;
        arvalid = 1'b1;
        @(posedge clk);
        arvalid = 1'b0;
        rready  = 1'b1;
        while (!rvalid) @(posedge clk);
        data = rdata;
        @(posedge clk);
        rready = 1'b0;
    endtask

    logic [31:0] rd_val;

    initial begin
        // ── Drive defaults on every signal ─────────────────────
        awaddr = '0; awprot = '0; awvalid = 1'b0;
        wdata  = '0; wstrb = '0; wvalid = 1'b0; bready = 1'b0;
        araddr = '0; arprot = '0; arvalid = 1'b0; rready = 1'b0;
        running = 1'b0; link_up = 1'b0; active_regime = REGIME_CALM;
        quotes_sent = '0; orders_rcvd = '0; fills_sent = '0;
        rejects_sent = '0; link_errors = '0; fifo_fill = 7'd0;
        for (int i = 0; i < TB_NUM_SYM; i++) begin
            live_bid[i] = '0;
            live_ask[i] = '0;
            live_mid[i] = '0;
        end

        @(posedge rst_n);
        repeat (2) @(posedge clk);

        $display("=== tb_board_a_axi_regs: start ===");

        // ──────────────────────────────────────────────────────
        // T1: Scalar config writes + readbacks
        // ──────────────────────────────────────────────────────
        $display("\n=== T1: Scalar config write/read ===");
        axi_write(9'h004, 32'h0000_0500);             // QUOTE_INTERVAL = 1280
        check32("T1: quote_interval drive",  quote_interval, 32'h0000_0500);
        axi_read (9'h004, rd_val);
        check32("T1: quote_interval rdback", rd_val, 32'h0000_0500);

        axi_write(9'h008, 32'hCAFE_BABE);             // LFSR_SEED
        check32("T1: lfsr_seed drive",       lfsr_seed, 32'hCAFE_BABE);
        axi_read (9'h008, rd_val);
        check32("T1: lfsr_seed rdback",      rd_val, 32'hCAFE_BABE);

        axi_write(9'h00C, 32'h0000_0001);             // REGIME = VOLATILE
        check("T1: regime_from_ps", regime_from_ps == REGIME_VOLATILE);
        axi_read (9'h00C, rd_val);
        check32("T1: regime rdback", rd_val[1:0], 2'b01);

        // ──────────────────────────────────────────────────────
        // T2: CTRL pulses (start, reset)
        // ──────────────────────────────────────────────────────
        $display("\n=== T2: CTRL pulses ===");
        axi_write(9'h000, 32'h0000_0001);  // start
        // The pulse is 1-cycle wide -- by the time axi_write's BVALID
        // handshake completes the start_pulse should already have fallen.
        @(posedge clk);
        check("T2: axi_start_pulse low after burst", axi_start_pulse == 1'b0);

        axi_write(9'h000, 32'h0000_0002);  // reset
        @(posedge clk);
        check("T2: axi_reset_pulse low after burst", axi_reset_pulse == 1'b0);

        // ──────────────────────────────────────────────────────
        // T3: STATUS register packing -- the RTL builds it as
        //   {16'd0, fifo_fill[6:0], 5'd0, regime[1:0], link_up, running}
        // so the fields land at:
        //   [0]    running
        //   [1]    link_up
        //   [3:2]  active_regime
        //   [8:4]  5'd0 (padding)
        //   [15:9] fifo_fill
        //   [31:16] zero
        // ──────────────────────────────────────────────────────
        $display("\n=== T3: STATUS register packing ===");
        running = 1'b1; link_up = 1'b1; active_regime = REGIME_BURST;
        fifo_fill = 7'd42;
        @(posedge clk); @(posedge clk);
        axi_read(9'h0F4, rd_val);
        check("T3: STATUS.running",    rd_val[0]    == 1'b1);
        check("T3: STATUS.link_up",    rd_val[1]    == 1'b1);
        check("T3: STATUS.regime",     rd_val[3:2]  == 2'b10);
        check("T3: STATUS.pad_zero",   rd_val[8:4]  == 5'd0);
        check("T3: STATUS.fifo_fill",  rd_val[15:9] == 7'd42);
        check("T3: STATUS.high_zero",  rd_val[31:16] == 16'd0);

        running = 1'b0; link_up = 1'b0; active_regime = REGIME_CALM;
        fifo_fill = 7'd0;
        @(posedge clk); @(posedge clk);
        axi_read(9'h0F4, rd_val);
        check32("T3: STATUS cleared", rd_val, 32'd0);

        // ──────────────────────────────────────────────────────
        // T4: Read-only counter readbacks
        // ──────────────────────────────────────────────────────
        $display("\n=== T4: Counter readbacks ===");
        quotes_sent  = 32'd1234;
        orders_rcvd  = 32'd567;
        fills_sent   = 32'd456;
        rejects_sent = 32'd12;
        link_errors  = 32'd3;
        @(posedge clk);

        axi_read(9'h0F8, rd_val); check32("T4: QUOTES_SENT",   rd_val, 32'd1234);
        axi_read(9'h0FC, rd_val); check32("T4: ORDERS_RCVD",   rd_val, 32'd567);
        axi_read(9'h100, rd_val); check32("T4: FILLS_SENT",    rd_val, 32'd456);
        axi_read(9'h104, rd_val); check32("T4: REJECTS_SENT",  rd_val, 32'd12);
        axi_read(9'h108, rd_val); check32("T4: LINK_ERRORS",   rd_val, 32'd3);

        // ──────────────────────────────────────────────────────
        // T5: Per-symbol INIT_MID writes + readbacks
        // ──────────────────────────────────────────────────────
        $display("\n=== T5: INIT_MID array ===");
        for (int i = 0; i < TB_NUM_SYM; i++) begin
            // Distinct value per symbol so a wrong-index bug shows up
            axi_write(9'h010 + 9'(4*i), 32'h00B4_0000 + 32'(i << 16));
        end
        for (int i = 0; i < TB_NUM_SYM; i++) begin
            axi_read(9'h010 + 9'(4*i), rd_val);
            check32($sformatf("T5: INIT_MID[%0d] rdback", i),
                    rd_val, 32'h00B4_0000 + 32'(i << 16));
            check32($sformatf("T5: INIT_MID[%0d] drive",  i),
                    sym_init_mid[i], 32'h00B4_0000 + 32'(i << 16));
        end

        // ──────────────────────────────────────────────────────
        // T6: INIT_SPREAD with 0->1 saturation rule
        //     The DUT replaces 0 with 1 to avoid degenerate spreads.
        // ──────────────────────────────────────────────────────
        $display("\n=== T6: INIT_SPREAD array (with 0 saturation) ===");
        // Symbol 0: write 0 -> should clamp to 1
        axi_write(9'h050, 32'h0000_0000);
        axi_read (9'h050, rd_val);
        check32("T6: INIT_SPREAD[0]=0 clamped to 1", rd_val, 32'h0000_0001);

        // Other symbols: distinct nonzero values
        for (int i = 1; i < TB_NUM_SYM; i++) begin
            axi_write(9'h050 + 9'(4*i), 32'h0000_1000 + 32'(i));
        end
        for (int i = 1; i < TB_NUM_SYM; i++) begin
            axi_read(9'h050 + 9'(4*i), rd_val);
            check32($sformatf("T6: INIT_SPREAD[%0d] rdback", i),
                    rd_val, 32'h0000_1000 + 32'(i));
        end

        // ──────────────────────────────────────────────────────
        // T7: Per-symbol SECTOR_ID writes + readbacks
        // ──────────────────────────────────────────────────────
        $display("\n=== T7: SECTOR_ID array ===");
        for (int i = 0; i < TB_NUM_SYM; i++) begin
            axi_write(9'h090 + 9'(4*i), 32'(i % 8));   // 8 sectors
        end
        for (int i = 0; i < TB_NUM_SYM; i++) begin
            axi_read(9'h090 + 9'(4*i), rd_val);
            check32($sformatf("T7: SECTOR_ID[%0d] rdback", i),
                    rd_val[SECTOR_ID_W-1:0], 32'(i % 8));
            check($sformatf("T7: SECTOR_ID[%0d] drive", i),
                  sym_sector_id[i] == (i % 8));
        end

        // ──────────────────────────────────────────────────────
        // T8: TOKEN_PACK -- two 16-bit tokens per 32-bit word
        //     word j: lo = sym_token[2*j], hi = sym_token[2*j+1]
        // ──────────────────────────────────────────────────────
        $display("\n=== T8: TOKEN_PACK ===");
        for (int j = 0; j < (TB_NUM_SYM+1)/2; j++) begin
            logic [31:0] packed_w;
            packed_w[15:0]  = 16'hA000 + 16'(2*j);
            packed_w[31:16] = ((2*j+1) < TB_NUM_SYM) ? (16'hA000 + 16'(2*j+1)) : 16'h0;
            axi_write(9'h0D0 + 9'(4*j), packed_w);
        end
        @(posedge clk);
        for (int i = 0; i < TB_NUM_SYM; i++) begin
            check($sformatf("T8: token[%0d] drive", i),
                  sym_company_token[i] == (16'hA000 + 16'(i)));
        end
        // Readback: pull the same words out of the AXI map and verify
        for (int j = 0; j < (TB_NUM_SYM+1)/2; j++) begin
            logic [31:0] expw;
            expw[15:0]  = 16'hA000 + 16'(2*j);
            expw[31:16] = ((2*j+1) < TB_NUM_SYM) ? (16'hA000 + 16'(2*j+1)) : 16'h0;
            axi_read(9'h0D0 + 9'(4*j), rd_val);
            check32($sformatf("T8: TOKEN_PACK[%0d] rdback", j), rd_val, expw);
        end

        // ──────────────────────────────────────────────────────
        // T9: ACTIVE_SYM_COUNT clamping
        //     write 0   -> reads back 1 (DUT clamps)
        //     write 99  -> clamps to NUM_SYM
        //     write 5   -> passes through
        // ──────────────────────────────────────────────────────
        $display("\n=== T9: ACTIVE_SYM_COUNT clamp ===");
        axi_write(9'h0F0, 32'd0);
        check("T9: 0  clamped to 1",          active_sym_count == 8'd1);
        axi_write(9'h0F0, 32'd99);
        check("T9: 99 clamped to NUM_SYM",    active_sym_count == TB_NUM_SYM[7:0]);
        axi_write(9'h0F0, 32'd5);
        check("T9: 5  passes through",        active_sym_count == 8'd5);
        axi_read(9'h0F0, rd_val);
        check32("T9: ACTIVE_CNT readback",    rd_val[7:0], 32'd5);

        // ──────────────────────────────────────────────────────
        // T10: Reset clears everything to spec'd defaults
        //   quote_interval -> 1000, lfsr_seed -> 0xDEADBEEF
        //   regime_from_ps -> CALM, active_sym_count -> NUM_SYM
        // ──────────────────────────────────────────────────────
        $display("\n=== T10: Reset defaults ===");
        rst_n = 1'b0;
        repeat (4) @(posedge clk);
        rst_n = 1'b1;
        repeat (4) @(posedge clk);
        check32("T10: quote_interval default", quote_interval, 32'd1000);
        check32("T10: lfsr_seed default",      lfsr_seed, 32'hDEAD_BEEF);
        check("T10: regime default = CALM",    regime_from_ps == REGIME_CALM);
        check("T10: active_sym_count default", active_sym_count == TB_NUM_SYM[7:0]);
        for (int i = 0; i < TB_NUM_SYM; i++) begin
            check($sformatf("T10: sym_init_mid[%0d] = 0", i),
                  sym_init_mid[i] === '0);
            check($sformatf("T10: sym_init_spread[%0d] = 1", i),
                  sym_init_spread[i] == 32'h1);
            check($sformatf("T10: sym_company_token[%0d] = i", i),
                  sym_company_token[i] == 16'(i));
        end

        // ──────────────────────────────────────────────────────
        // T11: B3 LIVE_BID readback
        // ──────────────────────────────────────────────────────
        $display("\n=== T11: B3 LIVE_BID readback ===");
        for (int i = 0; i < TB_NUM_SYM; i++)
            live_bid[i] = 32'h00B3_0000 + 32'(i << 12);
        @(posedge clk);
        for (int i = 0; i < TB_NUM_SYM; i++) begin
            axi_read(9'h110 + 9'(4*i), rd_val);
            check32($sformatf("T11: LIVE_BID[%0d]", i),
                    rd_val, 32'h00B3_0000 + 32'(i << 12));
        end

        // ──────────────────────────────────────────────────────
        // T12: B3 LIVE_ASK readback
        // ──────────────────────────────────────────────────────
        $display("\n=== T12: B3 LIVE_ASK readback ===");
        for (int i = 0; i < TB_NUM_SYM; i++)
            live_ask[i] = 32'h00B5_0000 + 32'(i << 12);
        @(posedge clk);
        for (int i = 0; i < TB_NUM_SYM; i++) begin
            axi_read(9'h150 + 9'(4*i), rd_val);
            check32($sformatf("T12: LIVE_ASK[%0d]", i),
                    rd_val, 32'h00B5_0000 + 32'(i << 12));
        end

        // ──────────────────────────────────────────────────────
        // T13: B3 LIVE_MID readback
        // ──────────────────────────────────────────────────────
        $display("\n=== T13: B3 LIVE_MID readback ===");
        for (int i = 0; i < TB_NUM_SYM; i++)
            live_mid[i] = 32'h00B4_0000 + 32'(i << 12);
        @(posedge clk);
        for (int i = 0; i < TB_NUM_SYM; i++) begin
            axi_read(9'h190 + 9'(4*i), rd_val);
            check32($sformatf("T13: LIVE_MID[%0d]", i),
                    rd_val, 32'h00B4_0000 + 32'(i << 12));
        end

        // ──────────────────────────────────────────────────────
        // T14: Unmapped address returns 0 (no X)
        //     0x1F0 sits between LIVE_MID range (ends 0x1CC) and the
        //     9-bit address ceiling (0x1FF). It must NOT be in the
        //     decode list -- if it is, this check catches it.
        // ──────────────────────────────────────────────────────
        $display("\n=== T14: Unmapped read returns 0 ===");
        axi_read(9'h1F0, rd_val);
        check32("T14: unmapped read = 0", rd_val, 32'd0);

        // ──────────────────────────────────────────────────────
        // Summary
        // ──────────────────────────────────────────────────────
        $display("\n══════════════════════════════════════════");
        $display("  tb_board_a_axi_regs complete");
        $display("  PASSED: %0d", pass_count);
        $display("  FAILED: %0d", fail_count);
        $display("══════════════════════════════════════════");
        if (fail_count == 0)
            $display("tb_board_a_axi_regs: PASS (%0d checks passed)", pass_count);
        else
            $display("tb_board_a_axi_regs: TESTBENCH FAILED (%0d failed)", fail_count);
        $finish;
    end

    // Watchdog
    initial begin
        #1ms;
        $display("tb_board_a_axi_regs: TESTBENCH FAILED (timeout)");
        $finish;
    end

endmodule
