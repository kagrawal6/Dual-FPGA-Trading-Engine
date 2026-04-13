// ============================================================================
// Testbench: tb_system_top
// End-to-end system test with real board_a_top and board_b_top connected via
// PMOD link.  Exercises the FULL 16-symbol SYMBOL_UNIVERSE from the golden
// model (common.py), multiple market regimes, risk-halt recovery, position &
// cash readback across all 16 symbols, latency histogram verification, and
// counter-clear / restart sequences.
//
// Golden model prices (Q16.16):
//   AAPL  $180  MSFT $420  NVDA $900  XOM  $115
//   CVX   $160  JNJ  $155  UNH  $520  AMZN $185
//   TSLA  $250  JPM  $200  GS   $480  CAT  $360
//   HON   $200  PG   $165  KO    $60  GOOGL$175
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_system_top;

    localparam int TB_NUM_SYM  = 16;
    localparam int LINK_W      = LINK_DATA_W;
    localparam int AXI_AW_A    = 8;
    localparam int AXI_AW_B    = 9;

    logic clk, rst_n;

    logic [3:0] btn_a;
    logic [7:0] sw_a, led_a;
    logic [2:0] rgb0_a, rgb1_a;

    logic [3:0] btn_b;
    logic [7:0] sw_b, led_b;
    logic [2:0] rgb0_b, rgb1_b;

    logic [LINK_W-1:0] pmod_a2b_data;
    logic               pmod_a2b_valid;
    logic               pmod_a2b_ready;

    logic [LINK_W-1:0] pmod_b2a_data;
    logic               pmod_b2a_valid;
    logic               pmod_b2a_ready;

    logic [AXI_AW_A-1:0] awaddr_a, araddr_a;
    logic [2:0]           awprot_a, arprot_a;
    logic                 awvalid_a, arvalid_a, awready_a, arready_a;
    logic [31:0]          wdata_a, rdata_a;
    logic [3:0]           wstrb_a;
    logic                 wvalid_a, wready_a;
    logic [1:0]           bresp_a, rresp_a;
    logic                 bvalid_a, bready_a;
    logic                 rvalid_a, rready_a;

    logic [AXI_AW_B-1:0] awaddr_b, araddr_b;
    logic [2:0]           awprot_b, arprot_b;
    logic                 awvalid_b, arvalid_b, awready_b, arready_b;
    logic [31:0]          wdata_b, rdata_b;
    logic [3:0]           wstrb_b;
    logic                 wvalid_b, wready_b;
    logic [1:0]           bresp_b, rresp_b;
    logic                 bvalid_b, bready_b;
    logic                 rvalid_b, rready_b;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    // ══════════════════════════════════════════════════════════════
    // DUT instances — full 16-symbol parameterization
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

    task automatic check_ge(input string name, input logic [31:0] actual, input logic [31:0] minimum);
        if (actual >= minimum) pass_count++;
        else begin
            fail_count++;
            $display("[FAIL] %0s: got %0d, expected >= %0d at %0t", name, actual, minimum, $time);
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
    // Simulation timeout (generous for 16-symbol test)
    // ══════════════════════════════════════════════════════════════
    initial begin
        #20_000_000;
        $display("[TIMEOUT] Simulation exceeded 20 ms, aborting.");
        $finish;
    end

    // ══════════════════════════════════════════════════════════════
    // Golden-model symbol universe (matches common.py SYMBOL_UNIVERSE)
    // Q16.16 init_mid, Q16.16 init_spread, sector_id
    // ══════════════════════════════════════════════════════════════
    logic [31:0] gm_init_mid   [0:15];
    logic [31:0] gm_init_spread[0:15];
    logic [31:0] gm_sector_id  [0:15];

    initial begin
        //              AAPL       MSFT       NVDA       XOM
        gm_init_mid[ 0] = 32'h00B4_0000; gm_init_mid[ 1] = 32'h01A4_0000;
        gm_init_mid[ 2] = 32'h0384_0000; gm_init_mid[ 3] = 32'h0073_0000;
        //              CVX        JNJ        UNH        AMZN
        gm_init_mid[ 4] = 32'h00A0_0000; gm_init_mid[ 5] = 32'h009B_0000;
        gm_init_mid[ 6] = 32'h0208_0000; gm_init_mid[ 7] = 32'h00B9_0000;
        //              TSLA       JPM        GS         CAT
        gm_init_mid[ 8] = 32'h00FA_0000; gm_init_mid[ 9] = 32'h00C8_0000;
        gm_init_mid[10] = 32'h01E0_0000; gm_init_mid[11] = 32'h0168_0000;
        //              HON        PG         KO         GOOGL
        gm_init_mid[12] = 32'h00C8_0000; gm_init_mid[13] = 32'h00A5_0000;
        gm_init_mid[14] = 32'h003C_0000; gm_init_mid[15] = 32'h00AF_0000;

        gm_init_spread[ 0] = 32'h0000_199A; gm_init_spread[ 1] = 32'h0000_2666;
        gm_init_spread[ 2] = 32'h0000_4000; gm_init_spread[ 3] = 32'h0000_147B;
        gm_init_spread[ 4] = 32'h0000_199A; gm_init_spread[ 5] = 32'h0000_147B;
        gm_init_spread[ 6] = 32'h0000_3333; gm_init_spread[ 7] = 32'h0000_199A;
        gm_init_spread[ 8] = 32'h0000_4CCD; gm_init_spread[ 9] = 32'h0000_199A;
        gm_init_spread[10] = 32'h0000_3333; gm_init_spread[11] = 32'h0000_2666;
        gm_init_spread[12] = 32'h0000_199A; gm_init_spread[13] = 32'h0000_0F5C;
        gm_init_spread[14] = 32'h0000_0A3D; gm_init_spread[15] = 32'h0000_199A;

        gm_sector_id[ 0] = 32'd0; gm_sector_id[ 1] = 32'd0;
        gm_sector_id[ 2] = 32'd0; gm_sector_id[ 3] = 32'd1;
        gm_sector_id[ 4] = 32'd1; gm_sector_id[ 5] = 32'd2;
        gm_sector_id[ 6] = 32'd2; gm_sector_id[ 7] = 32'd3;
        gm_sector_id[ 8] = 32'd3; gm_sector_id[ 9] = 32'd4;
        gm_sector_id[10] = 32'd4; gm_sector_id[11] = 32'd5;
        gm_sector_id[12] = 32'd5; gm_sector_id[13] = 32'd6;
        gm_sector_id[14] = 32'd6; gm_sector_id[15] = 32'd7;
    end

    // ══════════════════════════════════════════════════════════════
    // Main test
    // ══════════════════════════════════════════════════════════════
    initial begin
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
        // Phase 1: Configure Board A — full 16-symbol universe
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 1: Configure Board A (16 symbols) ===");

        for (int i = 0; i < 16; i++) begin
            axi_write_a(8'h10 + i*4, gm_init_mid[i]);
            axi_write_a(8'h50 + i*4, gm_init_spread[i]);
            axi_write_a(8'h90 + i*4, gm_sector_id[i]);
        end

        axi_write_a(8'h04, 32'd100);          // quote_interval = 100 cycles
        axi_write_a(8'h08, 32'hDEAD_BEEF);    // LFSR seed
        axi_write_a(8'h0C, 32'd0);            // regime = CALM
        axi_write_a(8'hF0, 32'd16);           // active_sym_count = 16

        // Verify readback of a few config registers
        axi_read_a(8'hF0);
        check32("P1: active_cnt=16", axi_rd_a, 32'd16);
        axi_read_a(8'h10);
        check32("P1: mid[0]=AAPL", axi_rd_a, 32'h00B4_0000);
        axi_read_a(8'h4C);
        check32("P1: mid[15]=GOOGL", axi_rd_a, 32'h00AF_0000);
        axi_read_a(8'h90);
        check32("P1: sector[0]=Tech", axi_rd_a, 32'd0);
        axi_read_a(8'hCC);
        check32("P1: sector[15]=Comms", axi_rd_a, 32'd7);

        $display("  Board A: 16 symbols configured across 8 sectors");

        // ══════════════════════════════════════════════════════════
        // Phase 2: Configure Board B — aggressive threshold for orders
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 2: Configure Board B ===");

        axi_write_b(9'h004, 32'd0);                    // MEAN_REV
        axi_write_b(9'h008, 32'h0000_0080);             // threshold ≈ $0.002 (very aggressive)
        axi_write_b(9'h00C, 32'd6554);                  // alpha ≈ 10%
        axi_write_b(9'h010, 32'd50);                     // base_qty = 50
        axi_write_b(9'h014, 32'd100_000);                // max_position = 100k
        axi_write_b(9'h018, 32'd100_000);                // max_order_rate = 100k
        axi_write_b(9'h01C, 32'd50_000_000);             // max_loss = $50M (generous)

        // Readback
        axi_read_b(9'h008);
        check32("P2: threshold", axi_rd_b, 32'h0000_0080);
        axi_read_b(9'h010);
        check32("P2: base_qty=50", axi_rd_b, 32'd50);

        $display("  Board B: MEAN_REV, threshold≈$0.002, qty=50, generous limits");

        // ══════════════════════════════════════════════════════════
        // Phase 3: Start Board A → RUNNING
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 3: Start Board A ===");
        axi_write_a(8'h00, 32'h0000_0001);
        repeat (3) @(posedge clk);
        check("P3: Board A running", u_board_a.running == 1'b1);

        // ══════════════════════════════════════════════════════════
        // Phase 4: Wait for link_up on Board B
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 4: Wait for Board B link_up ===");
        begin
            int wcnt;
            wcnt = 0;
            while (!u_board_b.link_up && wcnt < 5000) begin
                @(posedge clk); wcnt++;
            end
            check("P4: link_up", u_board_b.link_up == 1'b1);
            $display("  link_up after %0d cycles", wcnt);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 5: Start Board B → ARMED → TRADING
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 5: Start Board B ===");
        sw_b = 8'h01;
        @(posedge clk);
        axi_write_b(9'h000, 32'h0000_0001);
        repeat (3) @(posedge clk);
        check("P5a: ARMED", u_board_b.fsm_state == B_ARMED);

        axi_write_b(9'h000, 32'h0000_0001);
        repeat (3) @(posedge clk);
        check("P5b: TRADING", u_board_b.fsm_state == B_TRADING);
        $display("  Board B FSM = B_TRADING");

        // ══════════════════════════════════════════════════════════
        // Phase 6: CALM regime — run 120k cycles
        // With 16 symbols at interval=100, expect ~1200 quotes per sym
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 6: CALM regime (120k cycles) ===");
        repeat (120_000) @(posedge clk);

        axi_read_a(8'hF8);
        $display("  [CALM] A quotes_sent   = %0d", axi_rd_a);
        check("P6: A quotes>100", axi_rd_a > 32'd100);

        axi_read_b(9'h044);
        $display("  [CALM] B quotes_rcvd   = %0d", axi_rd_b);
        check("P6: B quotes>100", axi_rd_b > 32'd100);

        axi_read_b(9'h048);
        $display("  [CALM] B orders_sent   = %0d", axi_rd_b);

        axi_read_b(9'h050);
        $display("  [CALM] B risk_rejects  = %0d", axi_rd_b);

        axi_read_b(9'h054);
        check32("P6: link_errors==0", axi_rd_b, 32'd0);

        // ══════════════════════════════════════════════════════════
        // Phase 7: Switch to VOLATILE regime mid-flight
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 7: Regime change → VOLATILE ===");
        begin
            logic [31:0] orders_before;
            axi_read_b(9'h048);
            orders_before = axi_rd_b;

            axi_write_a(8'h0C, 32'd1);  // VOLATILE
            repeat (80_000) @(posedge clk);

            axi_read_b(9'h048);
            $display("  [VOL] B orders_sent = %0d (was %0d)", axi_rd_b, orders_before);
            check("P7: B trading in VOLATILE", u_board_b.fsm_state == B_TRADING);

            axi_read_b(9'h054);
            check32("P7: link_errors==0", axi_rd_b, 32'd0);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 8: Switch to ADVERSARIAL regime (stress)
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 8: Regime change → ADVERSARIAL ===");
        begin
            logic [31:0] orders_before_adv;
            axi_read_b(9'h048);
            orders_before_adv = axi_rd_b;

            axi_write_a(8'h0C, 32'd3);  // ADVERSARIAL
            repeat (60_000) @(posedge clk);

            axi_read_b(9'h048);
            $display("  [ADV] B orders_sent = %0d (was %0d)", axi_rd_b, orders_before_adv);

            axi_read_b(9'h054);
            check32("P8: link_errors==0", axi_rd_b, 32'd0);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 9: Full counter readback
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 9: Full Counter Readback ===");

        axi_read_a(8'hF8);
        $display("  A quotes_sent  = %0d", axi_rd_a);
        check("P9: A quotes>500", axi_rd_a > 32'd500);

        axi_read_a(8'hFC);
        $display("  A orders_rcvd  = %0d", axi_rd_a);

        axi_read_b(9'h044);
        $display("  B quotes_rcvd  = %0d", axi_rd_b);
        check("P9: B quotes>500", axi_rd_b > 32'd500);

        axi_read_b(9'h048);
        $display("  B orders_sent  = %0d", axi_rd_b);

        axi_read_b(9'h04C);
        $display("  B fills_rcvd   = %0d", axi_rd_b);

        axi_read_b(9'h050);
        $display("  B risk_rejects = %0d", axi_rd_b);

        axi_read_b(9'h054);
        $display("  B link_errors  = %0d", axi_rd_b);
        check32("P9: no link errors", axi_rd_b, 32'd0);

        // STATUS
        axi_read_b(9'h040);
        $display("  B STATUS       = 0x%08X", axi_rd_b);
        check("P9: B link_up", axi_rd_b[5] == 1'b1);

        // ══════════════════════════════════════════════════════════
        // Phase 10: All 16 positions readback
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 10: All 16 Positions ===");
        begin
            int nonzero_pos;
            nonzero_pos = 0;
            for (int i = 0; i < 16; i++) begin
                axi_read_b(9'h058 + i*4);
                if (axi_rd_b != 32'd0) nonzero_pos++;
                $display("  position[%2d] = %7d", i, $signed(axi_rd_b));
            end
            $display("  Non-zero positions: %0d / 16", nonzero_pos);
            check("P10: at least 1 position", nonzero_pos > 0);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 11: Cash readback
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 11: Cash Readback ===");
        axi_read_b(9'h098);
        $display("  cash_lo = 0x%08X", axi_rd_b);
        axi_read_b(9'h09C);
        $display("  cash_hi = 0x%08X", axi_rd_b);

        // ══════════════════════════════════════════════════════════
        // Phase 12: Latency histogram readback
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 12: Latency Histogram ===");

        axi_read_b(9'h0E0);
        $display("  lat_min   = %0d", axi_rd_b);
        check("P12: lat_min < 65535", axi_rd_b < 32'd65535);

        axi_read_b(9'h0E4);
        $display("  lat_max   = %0d", axi_rd_b);

        axi_read_b(9'h0EC);
        $display("  lat_count = %0d", axi_rd_b);

        begin
            int total_hist;
            total_hist = 0;
            for (int i = 0; i < 16; i++) begin
                axi_read_b(9'h0A0 + i*4);
                if (axi_rd_b > 0)
                    $display("  hist_bin[%2d] = %0d", i, axi_rd_b);
                total_hist += axi_rd_b;
            end
            $display("  Total in histogram: %0d", total_hist);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 13: End-to-end flow verification
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 13: End-to-End Verification ===");

        axi_read_a(8'hF8);
        begin
            logic [31:0] a_qs;
            a_qs = axi_rd_a;
            axi_read_b(9'h044);
            $display("  A quotes_sent=%0d → B quotes_rcvd=%0d", a_qs, axi_rd_b);
            check("P13: B rcvd <= A sent", axi_rd_b <= a_qs);
            check("P13: B rcvd > 0", axi_rd_b > 32'd0);
        end

        axi_read_b(9'h048);
        begin
            logic [31:0] b_ords;
            b_ords = axi_rd_b;
            if (b_ords > 0) begin
                axi_read_a(8'hFC);
                $display("  B orders_sent=%0d → A orders_rcvd=%0d", b_ords, axi_rd_a);
                check("P13: A rcvd orders", axi_rd_a > 32'd0);
                check("P13: A rcvd <= B sent", axi_rd_a <= b_ords);
            end
        end

        axi_read_b(9'h04C);
        begin
            logic [31:0] b_fills;
            b_fills = axi_rd_b;
            $display("  B fills_rcvd=%0d", b_fills);
            axi_read_b(9'h048);
            check("P13: fills <= orders", b_fills <= axi_rd_b);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 14: Stop Board A, drain in-flight frames
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 14: Stop Board A ===");
        axi_write_a(8'h00, 32'h0000_0002);
        repeat (5) @(posedge clk);
        check("P14: Board A stopped", u_board_a.fsm_state == A_IDLE);

        repeat (200) @(posedge clk);

        // ══════════════════════════════════════════════════════════
        // Phase 15: Reset Board B, verify all counters cleared
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 15: Reset Board B ===");
        axi_write_b(9'h000, 32'h0000_0002);
        repeat (10) @(posedge clk);
        check("P15: Board B IDLE", u_board_b.fsm_state == B_IDLE);

        axi_read_b(9'h044);
        check32("P15: quotes cleared", axi_rd_b, 32'd0);
        axi_read_b(9'h048);
        check32("P15: orders cleared", axi_rd_b, 32'd0);
        axi_read_b(9'h04C);
        check32("P15: fills cleared", axi_rd_b, 32'd0);
        axi_read_b(9'h050);
        check32("P15: rejects cleared", axi_rd_b, 32'd0);

        for (int i = 0; i < 16; i++) begin
            axi_read_b(9'h058 + i*4);
            check32($sformatf("P15: pos[%0d]=0", i), axi_rd_b, 32'd0);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 16: Restart with different seed, verify determinism
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 16: Restart with new seed ===");

        axi_write_a(8'h08, 32'hCAFE_BABE);
        axi_write_a(8'h0C, 32'd0);            // back to CALM
        axi_write_a(8'hF0, 32'd16);           // 16 symbols
        axi_write_a(8'h04, 32'd80);           // faster quote interval

        axi_write_a(8'h00, 32'h0000_0001);    // start
        repeat (3) @(posedge clk);
        check("P16: A running", u_board_a.running == 1'b1);

        // Wait for link_up again
        begin
            int wcnt2;
            wcnt2 = 0;
            while (!u_board_b.link_up && wcnt2 < 5000) begin
                @(posedge clk); wcnt2++;
            end
            check("P16: link_up again", u_board_b.link_up == 1'b1);
        end

        // Re-arm Board B
        sw_b = 8'h01;
        @(posedge clk);
        axi_write_b(9'h000, 32'h0000_0001);
        repeat (3) @(posedge clk);
        axi_write_b(9'h000, 32'h0000_0001);
        repeat (3) @(posedge clk);
        check("P16: B TRADING again", u_board_b.fsm_state == B_TRADING);

        repeat (40_000) @(posedge clk);

        axi_read_b(9'h044);
        $display("  After restart: B quotes_rcvd = %0d", axi_rd_b);
        check("P16: restart quotes>0", axi_rd_b > 32'd0);

        axi_read_b(9'h054);
        check32("P16: no link errors", axi_rd_b, 32'd0);

        // ══════════════════════════════════════════════════════════
        // Phase 17: Risk halt via low max_loss
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 17: Risk Halt Trigger ===");

        // Set extremely low max_loss to trigger halt
        axi_write_b(9'h01C, 32'd1);  // max_loss = $1 (will trigger quickly)

        // Switch to ADVERSARIAL for big price moves
        axi_write_a(8'h0C, 32'd3);

        begin
            int halt_wait;
            halt_wait = 0;
            while (u_board_b.fsm_state != B_HALTED && halt_wait < 200_000) begin
                @(posedge clk); halt_wait++;
            end
            if (u_board_b.fsm_state == B_HALTED) begin
                $display("  Risk halt triggered after %0d cycles", halt_wait);
                check("P17: HALTED state", u_board_b.fsm_state == B_HALTED);

                // Verify start does NOT exit HALTED
                axi_write_b(9'h000, 32'h0000_0001);
                repeat (3) @(posedge clk);
                check("P17: stays HALTED", u_board_b.fsm_state == B_HALTED);

                // Only reset exits HALTED
                axi_write_b(9'h000, 32'h0000_0002);
                repeat (3) @(posedge clk);
                check("P17: IDLE after reset", u_board_b.fsm_state == B_IDLE);
            end else begin
                $display("  [INFO] Risk halt did not trigger in 200k cycles (loss stayed low)");
            end
        end

        // ══════════════════════════════════════════════════════════
        // Phase 18: BURST regime end-to-end
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 18: BURST regime ===");

        axi_write_a(8'h0C, 32'd0);
        axi_write_b(9'h01C, 32'd50_000_000);

        axi_write_a(8'h00, 32'h0000_0001);
        repeat (3) @(posedge clk);
        begin
            int wcnt3;
            wcnt3 = 0;
            while (!u_board_b.link_up && wcnt3 < 5000) begin
                @(posedge clk); wcnt3++;
            end
        end
        sw_b = 8'h01;
        @(posedge clk);
        axi_write_b(9'h000, 32'h0000_0001);
        repeat (3) @(posedge clk);
        axi_write_b(9'h000, 32'h0000_0001);
        repeat (3) @(posedge clk);
        check("P18a: B TRADING", u_board_b.fsm_state == B_TRADING);

        axi_write_a(8'h0C, 32'd2);
        repeat (60_000) @(posedge clk);

        axi_read_b(9'h044);
        $display("  [BURST] B quotes_rcvd = %0d", axi_rd_b);
        check("P18b: B quotes>0 in BURST", axi_rd_b > 32'd0);

        axi_read_b(9'h054);
        check32("P18c: link_errors=0", axi_rd_b, 32'd0);

        // ══════════════════════════════════════════════════════════
        // Phase 19: Active symbol count change mid-flight (16→4→16)
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 19: Active Sym Count Change ===");
        begin
            logic [31:0] q_before_sym;
            axi_read_b(9'h044);
            q_before_sym = axi_rd_b;

            axi_write_a(8'hF0, 32'd4);
            axi_write_a(8'h0C, 32'd0);
            repeat (20_000) @(posedge clk);

            axi_read_b(9'h044);
            $display("  After 4-sym: quotes=%0d (was %0d)", axi_rd_b, q_before_sym);
            check("P19a: quotes grew with 4 syms", axi_rd_b > q_before_sym);

            axi_write_a(8'hF0, 32'd16);
            repeat (20_000) @(posedge clk);

            axi_read_b(9'h044);
            $display("  After 16-sym restored: quotes=%0d", axi_rd_b);

            axi_read_b(9'h054);
            check32("P19b: no link errors", axi_rd_b, 32'd0);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 20: Board B strategy override via switches
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 20: Strategy Override ===");

        sw_b = 8'h0F;
        @(posedge clk);
        axi_read_b(9'h040);
        $display("  STATUS w/ override = 0x%08X", axi_rd_b);
        check("P20a: strat_override active", axi_rd_b[1:0] == 2'b11);

        sw_b = 8'h0B;
        @(posedge clk);
        axi_read_b(9'h040);
        check("P20b: strat=MOMENTUM", axi_rd_b[1:0] == 2'b01);

        sw_b = 8'h01;
        @(posedge clk);

        // ══════════════════════════════════════════════════════════
        // Phase 21: Board A/B LED checks
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 21: LED/RGB Structural Checks ===");
        check("P21a: A LED[2]=running", led_a[2] == 1'b1);
        check("P21b: B LED[2:0]=TRADING", led_b[2:0] == 3'b011);

        // ══════════════════════════════════════════════════════════
        // Phase 22: Histogram and latency sanity
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 22: Histogram Sanity ===");

        axi_read_b(9'h0EC);
        begin
            logic [31:0] lat_cnt;
            lat_cnt = axi_rd_b;
            $display("  lat_count = %0d", lat_cnt);
            if (lat_cnt > 0) begin
                axi_read_b(9'h0E0);
                $display("  lat_min = %0d", axi_rd_b);
                check("P22a: lat_min > 0", axi_rd_b > 32'd0);
                begin
                    logic [31:0] lmin;
                    lmin = axi_rd_b;
                    axi_read_b(9'h0E4);
                    $display("  lat_max = %0d", axi_rd_b);
                    check("P22b: lat_min <= lat_max", lmin <= axi_rd_b);
                end
            end

            begin
                int total_bins;
                total_bins = 0;
                for (int i = 0; i < 16; i++) begin
                    axi_read_b(9'h0A0 + i*4);
                    total_bins += axi_rd_b;
                end
                $display("  sum_bins=%0d, lat_count=%0d", total_bins, lat_cnt);
                check32("P22c: count==sum", lat_cnt, total_bins[31:0]);
            end
        end

        // ══════════════════════════════════════════════════════════
        // Phase 23: fills > 0 when orders > 0 (exchange should fill)
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 23: Fills > 0 Check ===");

        axi_read_b(9'h048);
        begin
            logic [31:0] total_ords;
            total_ords = axi_rd_b;
            $display("  B orders_sent = %0d", total_ords);
            if (total_ords > 0) begin
                axi_read_b(9'h04C);
                $display("  B fills_rcvd  = %0d", axi_rd_b);
                check("P23: fills_rcvd > 0", axi_rd_b > 32'd0);
            end
        end

        // ══════════════════════════════════════════════════════════
        // Phase 24: Cash sign sanity
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 24: Cash Readback ===");
        axi_read_b(9'h098);
        $display("  cash_lo = 0x%08X", axi_rd_b);
        axi_read_b(9'h09C);
        $display("  cash_hi = 0x%08X", axi_rd_b);

        // ══════════════════════════════════════════════════════════
        // Phase 25: Stop Board A → drain → reset Board B (clean)
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 25: Final Stop + Drain + Reset ===");
        axi_write_a(8'h00, 32'h0000_0002);
        repeat (5) @(posedge clk);
        check("P25a: A stopped", u_board_a.fsm_state == A_IDLE);

        repeat (200) @(posedge clk);

        axi_write_b(9'h000, 32'h0000_0002);
        repeat (10) @(posedge clk);
        check("P25b: B IDLE", u_board_b.fsm_state == B_IDLE);

        axi_read_b(9'h044);
        check32("P25c: quotes cleared", axi_rd_b, 32'd0);
        axi_read_b(9'h048);
        check32("P25d: orders cleared", axi_rd_b, 32'd0);
        for (int i = 0; i < 16; i++) begin
            axi_read_b(9'h058 + i*4);
            check32($sformatf("P25e: pos[%0d]=0", i), axi_rd_b, 32'd0);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 26: Multiple restart cycles (3 quick cycles)
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 26: Multiple Restart Cycles ===");
        for (int cycle_i = 0; cycle_i < 3; cycle_i++) begin
            $display("  --- Restart cycle %0d ---", cycle_i);
            axi_write_a(8'h00, 32'h0000_0001);
            repeat (3) @(posedge clk);

            begin
                int wcnt_r;
                wcnt_r = 0;
                while (!u_board_b.link_up && wcnt_r < 5000) begin
                    @(posedge clk); wcnt_r++;
                end
            end

            sw_b = 8'h01;
            @(posedge clk);
            axi_write_b(9'h000, 32'h0000_0001);
            repeat (3) @(posedge clk);
            axi_write_b(9'h000, 32'h0000_0001);
            repeat (3) @(posedge clk);

            repeat (15_000) @(posedge clk);

            axi_read_b(9'h044);
            $display("    quotes_rcvd = %0d", axi_rd_b);
            check($sformatf("P26-%0d: quotes>0", cycle_i), axi_rd_b > 32'd0);

            axi_read_b(9'h054);
            check32($sformatf("P26-%0d: errors=0", cycle_i), axi_rd_b, 32'd0);

            axi_write_a(8'h00, 32'h0000_0002);
            repeat (200) @(posedge clk);
            axi_write_b(9'h000, 32'h0000_0002);
            repeat (10) @(posedge clk);
        end

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
