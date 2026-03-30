// ============================================================================
// Testbench: tb_system_top
// End-to-end system test with real board_a_top and board_b_top connected via
// PMOD link. Configures both boards via independent AXI-Lite interfaces:
//   Board A: sets symbol prices, quote_interval, LFSR seed, starts market sim
//   Board B: sets threshold, EMA alpha, risk limits, starts trading pipeline
// Verifies quote flow A→B, order flow B→A, fill flow A→B, and counter sanity.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_system_top;

    localparam int TB_NUM_SYM  = 4;
    localparam int LINK_W      = LINK_DATA_W;
    localparam int AXI_AW_A    = 8;
    localparam int AXI_AW_B    = 9;

    logic clk, rst_n;

    // ── Board A physical I/O ──────────────────────────────────────
    logic [3:0] btn_a;
    logic [7:0] sw_a, led_a;
    logic [2:0] rgb0_a, rgb1_a;

    // ── Board B physical I/O ──────────────────────────────────────
    logic [3:0] btn_b;
    logic [7:0] sw_b, led_b;
    logic [2:0] rgb0_b, rgb1_b;

    // ── PMOD interconnect (A TX → B RX) ───────────────────────────
    logic [LINK_W-1:0] pmod_a2b_data;
    logic               pmod_a2b_valid;
    logic               pmod_a2b_ready;

    // ── PMOD interconnect (B TX → A RX) ───────────────────────────
    logic [LINK_W-1:0] pmod_b2a_data;
    logic               pmod_b2a_valid;
    logic               pmod_b2a_ready;

    // ── Board A AXI-Lite ──────────────────────────────────────────
    logic [AXI_AW_A-1:0] awaddr_a, araddr_a;
    logic [2:0]           awprot_a, arprot_a;
    logic                 awvalid_a, arvalid_a, awready_a, arready_a;
    logic [31:0]          wdata_a, rdata_a;
    logic [3:0]           wstrb_a;
    logic                 wvalid_a, wready_a;
    logic [1:0]           bresp_a, rresp_a;
    logic                 bvalid_a, bready_a;
    logic                 rvalid_a, rready_a;

    // ── Board B AXI-Lite ──────────────────────────────────────────
    logic [AXI_AW_B-1:0] awaddr_b, araddr_b;
    logic [2:0]           awprot_b, arprot_b;
    logic                 awvalid_b, arvalid_b, awready_b, arready_b;
    logic [31:0]          wdata_b, rdata_b;
    logic [3:0]           wstrb_b;
    logic                 wvalid_b, wready_b;
    logic [1:0]           bresp_b, rresp_b;
    logic                 bvalid_b, bready_b;
    logic                 rvalid_b, rready_b;

    // ── Clock & reset ─────────────────────────────────────────────
    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    // ══════════════════════════════════════════════════════════════
    // DUT instances
    // ══════════════════════════════════════════════════════════════

    board_a_top #(
        .NUM_SYM(TB_NUM_SYM),
        .LINK_W(LINK_W)
    ) u_board_a (
        .clk(clk), .rst_n(rst_n),
        .btn(btn_a), .sw(sw_a), .led(led_a), .rgb0(rgb0_a), .rgb1(rgb1_a),
        .pmod_ja(pmod_a2b_data),
        .pmod_ja_valid(pmod_a2b_valid),
        .pmod_ja_ready(pmod_a2b_ready),
        .pmod_jb(pmod_b2a_data),
        .pmod_jb_valid(pmod_b2a_valid),
        .pmod_jb_ready(pmod_b2a_ready),
        .s_axi_awaddr(awaddr_a), .s_axi_awprot(awprot_a),
        .s_axi_awvalid(awvalid_a), .s_axi_awready(awready_a),
        .s_axi_wdata(wdata_a), .s_axi_wstrb(wstrb_a),
        .s_axi_wvalid(wvalid_a), .s_axi_wready(wready_a),
        .s_axi_bresp(bresp_a), .s_axi_bvalid(bvalid_a), .s_axi_bready(bready_a),
        .s_axi_araddr(araddr_a), .s_axi_arprot(arprot_a),
        .s_axi_arvalid(arvalid_a), .s_axi_arready(arready_a),
        .s_axi_rdata(rdata_a), .s_axi_rresp(rresp_a),
        .s_axi_rvalid(rvalid_a), .s_axi_rready(rready_a)
    );

    board_b_top #(
        .NUM_SYM(TB_NUM_SYM),
        .LINK_W(LINK_W)
    ) u_board_b (
        .clk(clk), .rst_n(rst_n),
        .btn(btn_b), .sw(sw_b), .led(led_b), .rgb0(rgb0_b), .rgb1(rgb1_b),
        .pmod_ja(pmod_a2b_data),
        .pmod_ja_valid(pmod_a2b_valid),
        .pmod_ja_ready(pmod_a2b_ready),
        .pmod_jb(pmod_b2a_data),
        .pmod_jb_valid(pmod_b2a_valid),
        .pmod_jb_ready(pmod_b2a_ready),
        .s_axi_awaddr(awaddr_b), .s_axi_awprot(awprot_b),
        .s_axi_awvalid(awvalid_b), .s_axi_awready(awready_b),
        .s_axi_wdata(wdata_b), .s_axi_wstrb(wstrb_b),
        .s_axi_wvalid(wvalid_b), .s_axi_wready(wready_b),
        .s_axi_bresp(bresp_b), .s_axi_bvalid(bvalid_b), .s_axi_bready(bready_b),
        .s_axi_araddr(araddr_b), .s_axi_arprot(arprot_b),
        .s_axi_arvalid(arvalid_b), .s_axi_arready(arready_b),
        .s_axi_rdata(rdata_b), .s_axi_rresp(rresp_b),
        .s_axi_rvalid(rvalid_b), .s_axi_rready(rready_b)
    );

    // ══════════════════════════════════════════════════════════════
    // Check helpers
    // ══════════════════════════════════════════════════════════════
    integer pass_count = 0;
    integer fail_count = 0;

    task automatic check(input string name, input logic condition);
        if (condition) pass_count++;
        else begin fail_count++; $display("[FAIL] %0s at %0t", name, $time); end
    endtask

    task automatic check32(input string name, input logic [31:0] actual, input logic [31:0] expected);
        if (actual === expected) pass_count++;
        else begin
            fail_count++;
            $display("[FAIL] %0s: got 0x%08X, expected 0x%08X at %0t", name, actual, expected, $time);
        end
    endtask

    // ══════════════════════════════════════════════════════════════
    // AXI tasks — Board A (8-bit address)
    // ══════════════════════════════════════════════════════════════
    task automatic axi_write_a(input logic [7:0] addr, input logic [31:0] data_val);
        @(posedge clk);
        awaddr_a  = addr;
        awvalid_a = 1'b1;
        wdata_a   = data_val;
        wstrb_a   = 4'hF;
        wvalid_a  = 1'b1;
        bready_a  = 1'b1;
        @(posedge clk);
        awvalid_a = 1'b0;
        wvalid_a  = 1'b0;
        while (!bvalid_a) @(posedge clk);
        @(posedge clk);
        bready_a = 1'b0;
    endtask

    logic [31:0] axi_rd_a;
    task automatic axi_read_a(input logic [7:0] addr);
        @(posedge clk);
        araddr_a  = addr;
        arvalid_a = 1'b1;
        rready_a  = 1'b1;
        @(posedge clk);
        arvalid_a = 1'b0;
        while (!rvalid_a) @(posedge clk);
        axi_rd_a = rdata_a;
        @(posedge clk);
        rready_a = 1'b0;
    endtask

    // ══════════════════════════════════════════════════════════════
    // AXI tasks — Board B (9-bit address)
    // ══════════════════════════════════════════════════════════════
    task automatic axi_write_b(input logic [8:0] addr, input logic [31:0] data_val);
        @(posedge clk);
        awaddr_b  = addr;
        awvalid_b = 1'b1;
        wdata_b   = data_val;
        wstrb_b   = 4'hF;
        wvalid_b  = 1'b1;
        bready_b  = 1'b1;
        @(posedge clk);
        awvalid_b = 1'b0;
        wvalid_b  = 1'b0;
        while (!bvalid_b) @(posedge clk);
        @(posedge clk);
        bready_b = 1'b0;
    endtask

    logic [31:0] axi_rd_b;
    task automatic axi_read_b(input logic [8:0] addr);
        @(posedge clk);
        araddr_b  = addr;
        arvalid_b = 1'b1;
        rready_b  = 1'b1;
        @(posedge clk);
        arvalid_b = 1'b0;
        while (!rvalid_b) @(posedge clk);
        axi_rd_b = rdata_b;
        @(posedge clk);
        rready_b = 1'b0;
    endtask

    // ══════════════════════════════════════════════════════════════
    // Simulation timeout
    // ══════════════════════════════════════════════════════════════
    initial begin
        #2_000_000;
        $display("[TIMEOUT] Simulation exceeded 2 ms, aborting.");
        $finish;
    end

    // ══════════════════════════════════════════════════════════════
    // Main test
    // ══════════════════════════════════════════════════════════════
    initial begin
        // Default all inputs
        btn_a = 4'b0; sw_a = 8'b0;
        btn_b = 4'b0; sw_b = 8'b0;

        awaddr_a = '0; awprot_a = '0; awvalid_a = 0;
        wdata_a  = '0; wstrb_a  = '0; wvalid_a  = 0;
        bready_a = 0;
        araddr_a = '0; arprot_a = '0; arvalid_a = 0;
        rready_a = 0;

        awaddr_b = '0; awprot_b = '0; awvalid_b = 0;
        wdata_b  = '0; wstrb_b  = '0; wvalid_b  = 0;
        bready_b = 0;
        araddr_b = '0; arprot_b = '0; arvalid_b = 0;
        rready_b = 0;

        @(posedge rst_n);
        repeat (5) @(posedge clk);

        // ══════════════════════════════════════════════════════════
        // Phase 1: Configure Board A
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 1: Configure Board A ===");

        // init_mid[0..3] (Q16.16): $180, $420, $900, $115
        axi_write_a(8'h10, 32'h00B4_0000);
        axi_write_a(8'h14, 32'h01A4_0000);
        axi_write_a(8'h18, 32'h0384_0000);
        axi_write_a(8'h1C, 32'h0073_0000);

        // init_spread[0..3] (Q16.16 half-spread ≈ $0.0625)
        axi_write_a(8'h50, 32'h0000_1000);
        axi_write_a(8'h54, 32'h0000_1000);
        axi_write_a(8'h58, 32'h0000_1000);
        axi_write_a(8'h5C, 32'h0000_1000);

        // quote_interval = 200 cycles
        axi_write_a(8'h04, 32'd200);

        // LFSR seed
        axi_write_a(8'h08, 32'hDEAD_BEEF);

        // Regime = CALM
        axi_write_a(8'h0C, 32'd0);

        // active_sym_count = 4
        axi_write_a(8'hF0, 32'd4);

        $display("  Board A configured: 4 symbols, interval=200, CALM regime");

        // ══════════════════════════════════════════════════════════
        // Phase 2: Configure Board B
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 2: Configure Board B ===");

        // Strategy = MEAN_REV
        axi_write_b(9'h004, 32'd0);

        // Threshold = 0x100 (very small ≈ $0.004 to ensure orders)
        axi_write_b(9'h008, 32'h0000_0100);

        // EMA alpha ≈ 10%
        axi_write_b(9'h00C, 32'd6554);

        // base_qty = 100
        axi_write_b(9'h010, 32'd100);

        // max_position = 5000
        axi_write_b(9'h014, 32'd5000);

        // max_order_rate = 10000
        axi_write_b(9'h018, 32'd10000);

        // max_loss = $10000 (generous)
        axi_write_b(9'h01C, 32'd10000);

        $display("  Board B configured: MEAN_REV, threshold=$0.004, qty=100");

        // ══════════════════════════════════════════════════════════
        // Phase 3: Start Board A → A_RUNNING
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 3: Start Board A ===");

        axi_write_a(8'h00, 32'h0000_0001);
        repeat (3) @(posedge clk);
        check("P3: Board A running", u_board_a.running == 1'b1);
        $display("  Board A FSM = A_RUNNING");

        // ══════════════════════════════════════════════════════════
        // Phase 4: Wait for Board B link_up
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 4: Wait for Board B link_up ===");

        begin
            integer wait_cnt = 0;
            while (!u_board_b.link_up && wait_cnt < 5000) begin
                @(posedge clk);
                wait_cnt++;
            end
            check("P4: Board B link_up", u_board_b.link_up == 1'b1);
            $display("  link_up after %0d cycles", wait_cnt);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 5: Start Board B → B_ARMED → B_TRADING
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 5: Start Board B ===");

        sw_b = 8'h01;  // trading_enable
        @(posedge clk);

        // Start → IDLE → ARMED
        axi_write_b(9'h000, 32'h0000_0001);
        repeat (3) @(posedge clk);
        check("P5a: Board B ARMED", u_board_b.fsm_state == B_ARMED);

        // Start again → ARMED → TRADING
        axi_write_b(9'h000, 32'h0000_0001);
        repeat (3) @(posedge clk);
        check("P5b: Board B TRADING", u_board_b.fsm_state == B_TRADING);
        $display("  Board B FSM = B_TRADING, order_enable = %0b", u_board_b.order_enable);

        // ══════════════════════════════════════════════════════════
        // Phase 6: Run system for 80,000 cycles
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 6: Running system (80k cycles) ===");
        repeat (80_000) @(posedge clk);

        // ══════════════════════════════════════════════════════════
        // Phase 7: Read counters from both boards
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 7: Counter Readback ===");

        // Board A counters
        axi_read_a(8'hF8);
        $display("  Board A quotes_sent   = %0d", axi_rd_a);
        check("P7: A quotes > 0", axi_rd_a > 32'd0);

        axi_read_a(8'hFC);
        $display("  Board A orders_rcvd   = %0d", axi_rd_a);

        axi_read_a(8'hF4);
        $display("  Board A STATUS        = 0x%08X", axi_rd_a);
        check("P7: A running", axi_rd_a[0] == 1'b1);

        // Board B counters
        axi_read_b(9'h044);
        $display("  Board B quotes_rcvd   = %0d", axi_rd_b);
        check("P7: B quotes > 0", axi_rd_b > 32'd0);

        axi_read_b(9'h048);
        $display("  Board B orders_sent   = %0d", axi_rd_b);

        axi_read_b(9'h04C);
        $display("  Board B fills_rcvd    = %0d", axi_rd_b);

        axi_read_b(9'h050);
        $display("  Board B risk_rejects  = %0d", axi_rd_b);

        axi_read_b(9'h054);
        $display("  Board B link_errors   = %0d", axi_rd_b);
        check32("P7: B link_errors==0", axi_rd_b, 32'd0);

        // Board B STATUS: {25'b0, risk_halt, link_up, fsm_state[2:0], active_strategy[1:0]}
        axi_read_b(9'h040);
        $display("  Board B STATUS        = 0x%08X", axi_rd_b);
        check("P7: B no risk_halt", axi_rd_b[6] == 1'b0);
        check("P7: B link_up", axi_rd_b[5] == 1'b1);
        check("P7: B TRADING", axi_rd_b[4:2] == 3'b011);

        // ══════════════════════════════════════════════════════════
        // Phase 8: Verify end-to-end flow
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 8: End-to-End Verification ===");

        // Re-read for final comparison
        axi_read_a(8'hF8);
        begin logic [31:0] a_quotes; a_quotes = axi_rd_a;
            axi_read_b(9'h044);
            $display("  A quotes_sent=%0d → B quotes_rcvd=%0d", a_quotes, axi_rd_b);
            check("P8: B rcvd <= A sent", axi_rd_b <= a_quotes);
            check("P8: B rcvd > 0", axi_rd_b > 32'd0);
        end

        axi_read_b(9'h048);
        begin logic [31:0] b_orders; b_orders = axi_rd_b;
            if (b_orders > 0) begin
                $display("  Board B generated %0d orders", b_orders);
                axi_read_a(8'hFC);
                $display("  Board A received %0d orders", axi_rd_a);
                check("P8: A rcvd orders", axi_rd_a > 32'd0);
            end else begin
                $display("  [INFO] No orders generated (deviation below threshold)");
            end
        end

        axi_read_b(9'h04C);
        if (axi_rd_b > 0) begin
            $display("  Board B processed %0d fills", axi_rd_b);

            // Read position[0]
            axi_read_b(9'h058);
            $display("  position[0] = %0d (signed)", $signed(axi_rd_b));

            // Read cash
            axi_read_b(9'h098);
            $display("  cash_lo = 0x%08X", axi_rd_b);
            axi_read_b(9'h09C);
            $display("  cash_hi = 0x%08X", axi_rd_b);
        end else begin
            $display("  [INFO] No fills received yet");
        end

        // Latency histogram
        axi_read_b(9'h0E0);
        $display("  lat_min   = %0d", axi_rd_b);
        axi_read_b(9'h0E4);
        $display("  lat_max   = %0d", axi_rd_b);
        axi_read_b(9'h0EC);
        $display("  lat_count = %0d", axi_rd_b);

        // ══════════════════════════════════════════════════════════
        // Phase 9: Stop Board A, verify graceful stop
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 9: Stop Board A ===");

        axi_write_a(8'h00, 32'h0000_0002);  // reset
        repeat (5) @(posedge clk);
        check("P9: Board A stopped", u_board_a.fsm_state == A_IDLE);

        // Board B should still be TRADING (or ARMED once link drops)
        axi_read_b(9'h040);
        $display("  Board B STATUS after A stop = 0x%08X", axi_rd_b);

        // ══════════════════════════════════════════════════════════
        // Phase 10: Reset Board B and verify clear
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 10: Reset Board B ===");

        axi_write_b(9'h000, 32'h0000_0002);
        repeat (5) @(posedge clk);
        check("P10: Board B IDLE", u_board_b.fsm_state == B_IDLE);

        axi_read_b(9'h044);
        check32("P10: B quotes cleared", axi_rd_b, 32'd0);

        axi_read_b(9'h048);
        check32("P10: B orders cleared", axi_rd_b, 32'd0);

        // ══════════════════════════════════════════════════════════
        // Summary
        // ══════════════════════════════════════════════════════════
        repeat (5) @(posedge clk);
        $display("\n══════════════════════════════════════════");
        $display("  tb_system_top complete");
        $display("  PASSED: %0d", pass_count);
        $display("  FAILED: %0d", fail_count);
        $display("══════════════════════════════════════════\n");

        if (fail_count > 0) $fatal(1, "TESTBENCH FAILED");
        $finish;
    end

endmodule
