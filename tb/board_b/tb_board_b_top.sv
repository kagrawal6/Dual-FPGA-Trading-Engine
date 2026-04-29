// ============================================================================
// Testbench: tb_board_b_top
// Full integration test for board_b_top with 16 symbols. Exercises:
//   - 5-state FSM (RESET→IDLE→ARMED→TRADING→HALTED) via link + AXI
//   - Full 16-symbol pipeline via PMOD link injection
//   - FILL injection → position_tracker → AXI readback for all 16 symbols
//   - Cash accounting and histogram readback
//   - AXI config write/readback and status verification
//   - Counter clear on FSM RESET
//   - LED/RGB structural checks
//   - Strategy override via switches
//   - Risk halt trigger and recovery
//   - Multiple regime values
//   - Back-to-back frame stress
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_b_top;

    localparam int TB_NUM_SYM = 16;
    localparam int LINK_W     = 4;

    logic        clk, rst_n;
    logic [3:0]  btn;
    logic [7:0]  sw;
    logic [7:0]  led;
    logic [2:0]  rgb0, rgb1;

    logic [LINK_W-1:0] pmod_ja;
    logic        pmod_ja_valid, pmod_ja_ready;
    logic [LINK_W-1:0] pmod_jb;
    logic        pmod_jb_valid, pmod_jb_ready;

    logic [9:0]  awaddr, araddr;  // bumped 9→10 bits for B2 per-symbol AXI exposure
    logic [2:0]  awprot, arprot;
    logic        awvalid, arvalid, awready, arready;
    logic [31:0] wdata, rdata;
    logic [3:0]  wstrb;
    logic        wvalid, wready;
    logic [1:0]  bresp, rresp;
    logic        bvalid, bready;
    logic        rvalid, rready;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    board_b_top #(
        .NUM_SYM(TB_NUM_SYM),
        .LINK_W(LINK_W)
    ) dut (
        .clk(clk), .rst_n(rst_n),
        .btn(btn), .sw(sw), .led(led), .rgb0(rgb0), .rgb1(rgb1),
        .pmod_ja(pmod_ja), .pmod_ja_valid(pmod_ja_valid), .pmod_ja_ready(pmod_ja_ready),
        .pmod_jb(pmod_jb), .pmod_jb_valid(pmod_jb_valid), .pmod_jb_ready(pmod_jb_ready),
        .s_axi_awaddr(awaddr), .s_axi_awprot(awprot),
        .s_axi_awvalid(awvalid), .s_axi_awready(awready),
        .s_axi_wdata(wdata), .s_axi_wstrb(wstrb),
        .s_axi_wvalid(wvalid), .s_axi_wready(wready),
        .s_axi_bresp(bresp), .s_axi_bvalid(bvalid), .s_axi_bready(bready),
        .s_axi_araddr(araddr), .s_axi_arprot(arprot),
        .s_axi_arvalid(arvalid), .s_axi_arready(arready),
        .s_axi_rdata(rdata), .s_axi_rresp(rresp),
        .s_axi_rvalid(rvalid), .s_axi_rready(rready)
    );

    // ── Check helpers ─────────────────────────────────────────────
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

    // ── AXI-Lite write ────────────────────────────────────────────
    task automatic axi_write(input logic [9:0] addr, input logic [31:0] data_val);
        @(posedge clk);
        awaddr  = addr;
        awvalid = 1'b1;
        wdata   = data_val;
        wstrb   = 4'hF;
        wvalid  = 1'b1;
        bready  = 1'b1;
        @(posedge clk);
        awvalid = 1'b0;
        wvalid  = 1'b0;
        while (!bvalid) @(posedge clk);
        @(posedge clk);
        bready = 1'b0;
    endtask

    // ── AXI-Lite read ─────────────────────────────────────────────
    logic [31:0] axi_rd_data;
    task automatic axi_read(input logic [9:0] addr);
        @(posedge clk);
        araddr  = addr;
        arvalid = 1'b1;
        rready  = 1'b1;
        @(posedge clk);
        arvalid = 1'b0;
        while (!rvalid) @(posedge clk);
        axi_rd_data = rdata;
        @(posedge clk);
        rready = 1'b0;
    endtask

    // ── Link frame injection ──────────────────────────────────────
    task automatic send_link_frame(input logic [127:0] frame);
        pmod_ja_valid = 1'b0;
        pmod_ja = '0;
        repeat (4) @(posedge clk);

        pmod_ja_valid = 1'b1;
        for (int i = 0; i < 32; i++) begin
            pmod_ja = frame[127 - 4*i -: 4];
            @(posedge clk);
            @(posedge clk);
        end
        pmod_ja_valid = 1'b0;
        pmod_ja = '0;
        repeat (10) @(posedge clk);
    endtask

    // ── 16-symbol init_mid values ─────────────────────────────────
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

    // Helper: build QUOTE frame
    function automatic logic [127:0] build_quote(
        input int sym, input logic [31:0] bid, input logic [31:0] ask,
        input int regime, input int seq
    );
        return {4'h1, sym[7:0], regime[1:0], 2'b00, bid, ask, 16'h03E8, 16'h03E8, seq[15:0]};
    endfunction

    // Helper: build FILL frame
    function automatic logic [127:0] build_fill(
        input int sym, input logic side, input logic [2:0] status,
        input logic [31:0] price, input int qty, input int oid, input int ts
    );
        return {4'h3, sym[7:0], side, status, price, qty[15:0], oid[15:0], ts[15:0], 32'h0};
    endfunction

    // ── Simulation timeout ────────────────────────────────────────
    initial begin
        #5_000_000;
        $display("[TIMEOUT] tb_board_b_top exceeded 5 ms");
        $finish;
    end

    // ── Main test ─────────────────────────────────────────────────
    initial begin
        btn = 4'b0;
        sw  = 8'b0;
        pmod_ja       = '0;
        pmod_ja_valid = 1'b0;
        pmod_jb_ready = 1'b1;
        awaddr = '0; awprot = '0; awvalid = 1'b0;
        wdata  = '0; wstrb  = '0; wvalid  = 1'b0;
        bready = 1'b0;
        araddr = '0; arprot = '0; arvalid = 1'b0;
        rready = 1'b0;

        @(posedge rst_n);
        @(posedge clk);

        // ══════════════════════════════════════════════════════════
        // Phase 1: FSM transitions (same as before, quick check)
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 1: FSM Transitions ===");

        check("T1: starts RESET", dut.fsm_state == B_RESET);
        @(posedge clk);
        check("T1: → IDLE", dut.fsm_state == B_IDLE);

        // Start without link_up
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("T2: stays IDLE", dut.fsm_state == B_IDLE);

        // Send first QUOTE to establish link_up
        send_link_frame(build_quote(0, init_mid[0] - 32'h1000, init_mid[0] + 32'h1000, 0, 0));
        check("T3: link_up", dut.link_up == 1'b1);

        // IDLE → ARMED → TRADING
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("T4: ARMED", dut.fsm_state == B_ARMED);

        sw = 8'h01;
        @(posedge clk);
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("T5: TRADING", dut.fsm_state == B_TRADING);

        // ══════════════════════════════════════════════════════════
        // Phase 2: AXI config — write all params and verify
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 2: AXI Config ===");

        axi_write(9'h008, 32'h0000_0100);  // threshold ≈ $0.004
        axi_write(9'h00C, 32'd6554);        // alpha
        axi_write(9'h010, 32'd50);           // base_qty
        axi_write(9'h014, 32'd100_000);      // max_position
        axi_write(9'h018, 32'd100_000);      // max_order_rate
        axi_write(9'h01C, 32'd50_000_000);   // max_loss

        axi_read(9'h008);
        check32("P2: threshold", axi_rd_data, 32'h0000_0100);
        axi_read(9'h010);
        check32("P2: base_qty", axi_rd_data, 32'd50);
        axi_read(9'h014);
        check32("P2: max_pos", axi_rd_data, 32'd100_000);

        // ══════════════════════════════════════════════════════════
        // Phase 3: Send 16-symbol QUOTE frames (EMA seeding)
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 3: 16-Symbol EMA Seeding ===");

        for (int i = 1; i < 16; i++)
            send_link_frame(build_quote(i, init_mid[i] - 32'h1000, init_mid[i] + 32'h1000, 0, 0));
        repeat (30) @(posedge clk);

        axi_read(9'h044);
        $display("  quotes_rcvd = %0d (expect 16)", axi_rd_data);
        check32("P3: 16 quotes", axi_rd_data, 32'd16);

        // ══════════════════════════════════════════════════════════
        // Phase 4: 2nd round with price shifts → orders
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 4: Price Shifts → Orders ===");

        for (int i = 0; i < 16; i++) begin
            logic [31:0] shifted;
            shifted = init_mid[i] + 32'h0002_0000;  // +$2
            send_link_frame(build_quote(i, shifted - 32'h1000, shifted + 32'h1000, 0, 1));
        end
        repeat (50) @(posedge clk);

        axi_read(9'h044);
        $display("  quotes_rcvd = %0d (expect 32)", axi_rd_data);
        check32("P4: 32 quotes", axi_rd_data, 32'd32);

        axi_read(9'h048);
        $display("  orders_sent = %0d", axi_rd_data);

        // STATUS check
        axi_read(9'h040);
        $display("  STATUS = 0x%08X", axi_rd_data);
        check("P4: no risk_halt", axi_rd_data[6] == 1'b0);
        check("P4: link_up", axi_rd_data[5] == 1'b1);
        check("P4: TRADING", axi_rd_data[4:2] == 3'b011);

        // ══════════════════════════════════════════════════════════
        // Phase 5: FILL injection for 8 symbols
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 5: Fill Injection (8 symbols) ===");

        for (int i = 0; i < 8; i++) begin
            send_link_frame(build_fill(i, 1'b0, 3'b000, init_mid[i], 100, i, 42+i));
        end

        axi_read(9'h04C);
        $display("  fills_rcvd = %0d", axi_rd_data);
        check("P5: fills>=8", axi_rd_data >= 32'd8);

        // Read all 16 positions
        $display("  --- Position readback ---");
        for (int i = 0; i < 16; i++) begin
            axi_read(9'h058 + i*4);
            $display("  pos[%2d] = %7d", i, $signed(axi_rd_data));
        end

        // First 8 should be 100 (BUY fill)
        axi_read(9'h058);
        check32("P5: pos[0]=100", axi_rd_data, 32'd100);
        axi_read(9'h07C);  // pos[9] at 0x058+9*4=0x07C
        check32("P5: pos[9]=0 (no fill)", axi_rd_data, 32'd0);

        // ══════════════════════════════════════════════════════════
        // Phase 6: SELL fills for symbols 0-3
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 6: SELL Fills (sym 0-3) ===");

        for (int i = 0; i < 4; i++)
            send_link_frame(build_fill(i, 1'b1, 3'b000, init_mid[i] + 32'h0001_0000, 50, 20+i, 80+i));

        axi_read(9'h058);
        $display("  pos[0] after SELL = %0d (expect 50)", $signed(axi_rd_data));
        check32("P6: pos[0]=50", axi_rd_data, 32'd50);

        // ══════════════════════════════════════════════════════════
        // Phase 7: Cash readback
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 7: Cash Readback ===");

        axi_read(9'h098);
        $display("  cash_lo = 0x%08X", axi_rd_data);
        axi_read(9'h09C);
        $display("  cash_hi = 0x%08X", axi_rd_data);

        // ══════════════════════════════════════════════════════════
        // Phase 8: Latency histogram
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 8: Latency Histogram ===");

        axi_read(9'h0E0);
        $display("  lat_min   = %0d", axi_rd_data);

        axi_read(9'h0E4);
        $display("  lat_max   = %0d", axi_rd_data);

        axi_read(9'h0EC);
        $display("  lat_count = %0d", axi_rd_data);

        begin
            int total_hist;
            total_hist = 0;
            for (int i = 0; i < 16; i++) begin
                axi_read(9'h0A0 + i*4);
                if (axi_rd_data > 0)
                    $display("  hist[%2d] = %0d", i, axi_rd_data);
                total_hist += axi_rd_data;
            end
            $display("  Total histogram entries: %0d", total_hist);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 9: Strategy override via switches
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 9: Strategy Override ===");

        // sw[3]=override, sw[2:1]=strategy, sw[0]=trading_enable
        sw = 8'h0F;  // override=1, strat=11(AUTO), enable=1
        @(posedge clk);
        axi_read(9'h040);
        $display("  STATUS w/ override = 0x%08X", axi_rd_data);
        check("P9a: strat=AUTO", axi_rd_data[1:0] == 2'b11);

        sw = 8'h07;  // override=0, strat=11, enable=1
        @(posedge clk);
        axi_read(9'h040);
        check("P9b: strat=MEAN_REV (no override)", axi_rd_data[1:0] == 2'b00);

        sw = 8'h0B;  // override=1, strat=01(MOMENTUM), enable=1
        @(posedge clk);
        axi_read(9'h040);
        check("P9c: strat=MOMENTUM", axi_rd_data[1:0] == 2'b01);

        sw = 8'h01;  // restore normal
        @(posedge clk);

        // ══════════════════════════════════════════════════════════
        // Phase 10: FSM control — TRADING ↔ ARMED
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 10: FSM Control ===");

        sw = 8'h00;  // disable trading
        @(posedge clk); #1;
        check("P10a: → ARMED", dut.fsm_state == B_ARMED);

        sw = 8'h01;
        @(posedge clk);
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("P10b: → TRADING", dut.fsm_state == B_TRADING);

        // ══════════════════════════════════════════════════════════
        // Phase 11: Risk halt → HALTED, only reset exits
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 11: Risk Halt ===");

        force dut.risk_halt = 1'b1;
        @(posedge clk); #1;
        check("P11a: → HALTED", dut.fsm_state == B_HALTED);
        release dut.risk_halt;

        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("P11b: stays HALTED", dut.fsm_state == B_HALTED);

        axi_write(9'h000, 32'h0000_0002);
        check("P11c: → RESET", dut.fsm_state == B_RESET);
        @(posedge clk); #1;
        check("P11d: → IDLE", dut.fsm_state == B_IDLE);

        // ══════════════════════════════════════════════════════════
        // Phase 12: Counter clear verification
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 12: Counter Clear ===");

        axi_read(9'h044);
        check32("P12: quotes=0", axi_rd_data, 32'd0);
        axi_read(9'h048);
        check32("P12: orders=0", axi_rd_data, 32'd0);
        axi_read(9'h04C);
        check32("P12: fills=0", axi_rd_data, 32'd0);
        axi_read(9'h050);
        check32("P12: rejects=0", axi_rd_data, 32'd0);

        // All 16 positions should be cleared
        for (int i = 0; i < 16; i++) begin
            axi_read(9'h058 + i*4);
            check32($sformatf("P12: pos[%0d]=0", i), axi_rd_data, 32'd0);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 13: Full restart + back-to-back stress
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 13: Restart + Stress ===");

        send_link_frame(build_quote(0, init_mid[0] - 32'h1000, init_mid[0] + 32'h1000, 0, 0));

        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        sw = 8'h01;
        @(posedge clk);
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("P13a: TRADING", dut.fsm_state == B_TRADING);

        // Burst: 16 symbols × 4 rounds = 64 frames
        for (int round = 0; round < 4; round++) begin
            for (int i = 0; i < 16; i++) begin
                logic [31:0] mid_s;
                if (round == 0)
                    mid_s = init_mid[i];
                else if (round[0])
                    mid_s = init_mid[i] + 32'h0003_0000;
                else
                    mid_s = init_mid[i] - 32'h0002_0000;
                if ($signed(mid_s) < $signed(32'h0001_0000))
                    mid_s = 32'h0001_0000;
                send_link_frame(build_quote(i, mid_s - 32'h1000, mid_s + 32'h1000, 0, round));
            end
        end
        repeat (50) @(posedge clk);

        axi_read(9'h044);
        $display("  Final quotes = %0d", axi_rd_data);
        check("P13b: quotes>=64", axi_rd_data >= 32'd64);

        axi_read(9'h048);
        $display("  Final orders = %0d", axi_rd_data);

        axi_read(9'h054);
        $display("  link_errors = %0d", axi_rd_data);
        check32("P13c: link_errors==0", axi_rd_data, 32'd0);

        // ══════════════════════════════════════════════════════════
        // Phase 14: LED structural checks
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 14: LED/RGB ===");
        check("P14a: LED[2:0]=TRADING", led[2:0] == 3'b011);
        check("P14b: LED[6]=order_en", led[6] == 1'b1);

        // ══════════════════════════════════════════════════════════
        // Phase 15: Rejected fill (no position change)
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 15: Rejected Fill ===");

        begin
            logic [31:0] pos7_before;
            axi_read(9'h058 + 7*4);
            pos7_before = axi_rd_data;

            send_link_frame(build_fill(7, 1'b0, 3'b001, 32'h0, 0, 99, 60));

            axi_read(9'h058 + 7*4);
            check32("P15: pos[7] unchanged", axi_rd_data, pos7_before);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 16: Regime field propagation
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 16: Regime Field ===");

        send_link_frame(build_quote(0, init_mid[0], init_mid[0] + 32'h2000, 2, 99));
        repeat (5) @(posedge clk);

        send_link_frame(build_quote(0, init_mid[0], init_mid[0] + 32'h2000, 3, 100));
        repeat (5) @(posedge clk);

        // Quotes counted
        axi_read(9'h044);
        check("P16: more quotes", axi_rd_data > 32'd64);

        // ══════════════════════════════════════════════════════════
        // Phase 17: All 16 positions via BUY+SELL fills
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 17: Full 16-sym Position Test ===");

        for (int i = 0; i < 16; i++)
            send_link_frame(build_fill(i, 1'b0, 3'b000, init_mid[i], 200, 200+i, 500+i));

        for (int i = 0; i < 16; i++) begin
            axi_read(9'h058 + i*4);
            check($sformatf("P17: pos[%0d]>0", i), $signed(axi_rd_data) > 0);
        end

        for (int i = 8; i < 16; i++)
            send_link_frame(build_fill(i, 1'b1, 3'b000, init_mid[i] + 32'h0001_0000, 100, 300+i, 600+i));

        axi_read(9'h058 + 8*4);
        $display("  pos[8] after partial sell = %0d", $signed(axi_rd_data));
        check("P17: pos[8]>0 after partial sell", $signed(axi_rd_data) > 0);

        // ══════════════════════════════════════════════════════════
        // Phase 18: Histogram consistency (lat_count == sum bins)
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 18: Histogram Consistency ===");

        begin
            int sum_bins;
            logic [31:0] lat_count_reg;
            sum_bins = 0;
            for (int i = 0; i < 16; i++) begin
                axi_read(9'h0A0 + i*4);
                sum_bins += axi_rd_data;
            end
            axi_read(9'h0EC);
            lat_count_reg = axi_rd_data;
            $display("  lat_count=%0d, sum_bins=%0d", lat_count_reg, sum_bins);
            check32("P18: lat_count == sum bins", lat_count_reg, sum_bins[31:0]);

            axi_read(9'h0E0);
            begin
                logic [31:0] lmin;
                lmin = axi_rd_data;
                axi_read(9'h0E4);
                if (lat_count_reg > 0)
                    check("P18: lat_min <= lat_max", lmin <= axi_rd_data);
            end
        end

        // ══════════════════════════════════════════════════════════
        // Phase 19: Out-of-range symbol fill (no crash)
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 19: Out-of-range Symbol Fill ===");
        begin
            logic [31:0] fills_before;
            axi_read(9'h04C);
            fills_before = axi_rd_data;

            send_link_frame(build_fill(255, 1'b0, 3'b000, 32'h00FF_0000, 50, 999, 999));
            repeat (5) @(posedge clk);

            axi_read(9'h04C);
            $display("  fills after OOR: %0d (was %0d)", axi_rd_data, fills_before);
        end

        // ══════════════════════════════════════════════════════════
        // Phase 20: Double risk halt + recovery
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 20: Double Halt/Recovery ===");

        force dut.risk_halt = 1'b1;
        @(posedge clk); #1;
        check("P20a: HALTED", dut.fsm_state == B_HALTED);
        release dut.risk_halt;

        axi_write(9'h000, 32'h0000_0002);
        @(posedge clk); #1;
        check("P20b: IDLE after reset", dut.fsm_state == B_IDLE);

        send_link_frame(build_quote(0, init_mid[0] - 32'h1000, init_mid[0] + 32'h1000, 0, 0));
        sw = 8'h01;
        @(posedge clk);
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("P20c: TRADING again", dut.fsm_state == B_TRADING);

        force dut.risk_halt = 1'b1;
        @(posedge clk); #1;
        check("P20d: HALTED again", dut.fsm_state == B_HALTED);
        release dut.risk_halt;

        axi_write(9'h000, 32'h0000_0002);
        @(posedge clk); #1;
        check("P20e: IDLE after 2nd reset", dut.fsm_state == B_IDLE);

        // ══════════════════════════════════════════════════════════
        // Phase 21: link_errors stays 0
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 21: Link Error Check ===");
        axi_read(9'h054);
        check32("P21: link_errors=0", axi_rd_data, 32'd0);

        // ══════════════════════════════════════════════════════════
        // Phase 22: Config survives FSM transitions
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 22: Config Persistence ===");
        axi_read(9'h008);
        check32("P22: threshold intact", axi_rd_data, 32'h0000_0100);
        axi_read(9'h010);
        check32("P22: base_qty intact", axi_rd_data, 32'd50);
        axi_read(9'h014);
        check32("P22: max_pos intact", axi_rd_data, 32'd100_000);
        axi_read(9'h01C);
        check32("P22: max_loss intact", axi_rd_data, 32'd50_000_000);

        // ══════════════════════════════════════════════════════════
        // Phase 23: AXI alpha and max_order_rate readback
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 23: Extra AXI Readback ===");
        axi_read(9'h00C);
        check32("P23: alpha", axi_rd_data, 32'd6554);
        axi_read(9'h018);
        check32("P23: max_order_rate", axi_rd_data, 32'd100_000);

        // ══════════════════════════════════════════════════════════
        // Phase 24: B2 — per-symbol AXI exposure (BID/ASK/PNL/LAST_FILL/TRADES)
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 24: B2 per-symbol AXI exposure ===");

        // Push fresh quotes so quote_book.best_bid_arr / best_ask_arr update
        for (int i = 0; i < 4; i++)
            send_link_frame(build_quote(i, init_mid[i] - 32'h1000, init_mid[i] + 32'h1000, 0, 200+i));
        repeat (10) @(posedge clk);

        // Read BID[0..3] (base 0x100) and ASK[0..3] (base 0x140)
        for (int i = 0; i < 4; i++) begin
            axi_read(10'h100 + i*4);
            $display("  BID[%0d]  = 0x%08X (expect 0x%08X)", i, axi_rd_data, init_mid[i] - 32'h1000);
            check32($sformatf("P24: BID[%0d]", i),
                    axi_rd_data, init_mid[i] - 32'h1000);
            axi_read(10'h140 + i*4);
            $display("  ASK[%0d]  = 0x%08X (expect 0x%08X)", i, axi_rd_data, init_mid[i] + 32'h1000);
            check32($sformatf("P24: ASK[%0d]", i),
                    axi_rd_data, init_mid[i] + 32'h1000);
        end

        // Inject a clean BUY fill for symbol 0 and verify LAST_FILL + TRADES + PNL_LO
        send_link_frame(build_fill(0, 1'b0, 3'b000, init_mid[0], 50, 555, 700));
        repeat (10) @(posedge clk);

        axi_read(10'h200);  // LAST_FILL_PRICE[0]
        $display("  LAST_FILL[0] = 0x%08X (expect 0x%08X)", axi_rd_data, init_mid[0]);
        check32("P24: LAST_FILL[0]", axi_rd_data, init_mid[0]);

        axi_read(10'h240);  // TRADES_PACK[0] = {trades[1],trades[0]}
        $display("  TRADES_PACK[0] = 0x%08X (low=trades[0], high=trades[1])", axi_rd_data);
        check("P24: trades[0] >= 1", axi_rd_data[15:0] >= 16'd1);

        // Verify PNL_HI sign-extends correctly when cumulative cash on sym 0 is negative
        axi_read(10'h180);  // PNL_LO[0]
        begin : pnl_check
            logic [31:0] pnl_lo, pnl_hi;
            pnl_lo = axi_rd_data;
            axi_read(10'h1C0);  // PNL_HI[0]
            pnl_hi = axi_rd_data;
            $display("  PNL[0] = HI:0x%08X LO:0x%08X (signed 48b)", pnl_hi, pnl_lo);
            // Sign-ext check: upper 16 bits of HI must equal sign of bit15 of HI
            check("P24: PNL_HI[0] sign-ext valid",
                  pnl_hi[31:16] == {16{pnl_hi[15]}});
        end

        // ══════════════════════════════════════════════════════════
        // Summary
        // ══════════════════════════════════════════════════════════
        repeat (5) @(posedge clk);
        $display("\n══════════════════════════════════════════");
        $display("  board_b_top testbench complete");
        $display("  PASSED: %0d", pass_count);
        $display("  FAILED: %0d", fail_count);
        $display("══════════════════════════════════════════\n");

        if (fail_count > 0) $fatal(1, "TESTBENCH FAILED");
        $finish;
    end

endmodule
