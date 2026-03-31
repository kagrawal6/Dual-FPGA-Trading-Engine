// ============================================================================
// Testbench: tb_board_b_top
// Full integration test for board_b_top. Exercises:
//   - 5-state FSM (RESET→IDLE→ARMED→TRADING→HALTED) via link injection + AXI
//   - Pipeline: golden QUOTE frames via PMOD link → order generation
//   - FILL injection → position_tracker → AXI readback
//   - AXI config write/readback and status verification
//   - Counter clear on FSM RESET
//   - LED/RGB structural checks
//   - Strategy override via switches
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_b_top;

    localparam int TB_NUM_SYM = 4;
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

    logic [8:0]  awaddr, araddr;
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
    task automatic axi_write(input logic [8:0] addr, input logic [31:0] data_val);
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
    task automatic axi_read(input logic [8:0] addr);
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

    // ── Link frame injection (mimics link_tx protocol) ────────────
    // Sends MSB nibble first, each held 2 core clocks. Keeps
    // pmod_ja_valid HIGH for the entire 32-nibble frame duration.
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

    // ── Golden QUOTE frames (pipeline_vectors.json, first 20) ─────
    localparam logic [127:0] GM_FRAMES [0:19] = '{
        128'h100000B3F81E00B4081E03E803E80000,  // sym 0
        128'h101001A3F82101A4082103E803E80000,  // sym 1
        128'h10200383F8160384081603E803E80000,  // sym 2
        128'h10300072F81D0073081D03E803E80000,  // sym 3
        128'h100000B3F83100B4083103E803E80001,  // sym 0
        128'h101001A3F81601A4081603E803E80001,  // sym 1
        128'h10200383F8250384082503E803E80001,  // sym 2
        128'h10300072F82E0073082E03E803E80001,  // sym 3
        128'h100000B3F81A00B4081A03E803E80002,  // sym 0
        128'h101001A3F81801A4081803E803E80002,  // sym 1
        128'h10200383F81B0384081B03E803E80002,  // sym 2
        128'h10300072F80D0073080D03E803E80002,  // sym 3
        128'h100000B3F80B00B4080B03E803E80003,  // sym 0
        128'h101001A3F7F401A407F403E803E80003,  // sym 1
        128'h10200383F7FE038407FE03E803E80003,  // sym 2
        128'h10300072F80F0073080F03E803E80003,  // sym 3
        128'h100000B3F81500B4081503E803E80004,  // sym 0
        128'h101001A3F7DD01A407DD03E803E80004,  // sym 1
        128'h10200383F7FF038407FF03E803E80004,  // sym 2
        128'h10300072F7F1007307F103E803E80004   // sym 3
    };

    // FILL: sym=0, BUY, FILL_OK, price=0x00B40815, qty=100, oid=1, ts=42
    localparam logic [127:0] FILL_SYM0_BUY =
        128'h3000_00B4_0815_0064_0001_002A_0000_0000;

    // FILL: sym=1, SELL, FILL_OK, price=0x01A40821, qty=50, oid=2, ts=55
    localparam logic [127:0] FILL_SYM1_SELL =
        128'h3010_8000_0000_0032_0002_0037_0000_0000;

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
        // Phase 1: FSM transitions
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 1: FSM Transitions ===");

        // T1: RESET → IDLE (automatic 1-cycle)
        check("T1: starts RESET",  dut.fsm_state == B_RESET);
        @(posedge clk);
        check("T1: → IDLE",        dut.fsm_state == B_IDLE);

        // T2: start without link_up → stays IDLE
        check("T2: link_up==0",    dut.link_up == 1'b0);
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("T2: stays IDLE",    dut.fsm_state == B_IDLE);

        // T3: send golden QUOTE → link_up asserts
        $display("  Sending first QUOTE via link...");
        send_link_frame(GM_FRAMES[0]);
        check("T3: link_up==1",    dut.link_up == 1'b1);

        // T4: start with link_up → IDLE → ARMED
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("T4: → ARMED",       dut.fsm_state == B_ARMED);
        check("T4: order_en==0",   dut.order_enable == 1'b0);

        // T5: start + trading_enable → ARMED → TRADING
        sw = 8'h01;
        @(posedge clk);
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("T5: → TRADING",     dut.fsm_state == B_TRADING);
        check("T5: order_en==1",   dut.order_enable == 1'b1);

        // ══════════════════════════════════════════════════════════
        // Phase 2: Pipeline — 11 more golden quotes in TRADING
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 2: Pipeline (12 quotes total) ===");

        for (int i = 1; i < 12; i++)
            send_link_frame(GM_FRAMES[i]);

        repeat (30) @(posedge clk);

        // Verify quotes_rcvd
        axi_read(9'h044);
        $display("  quotes_rcvd = %0d (expect 12)", axi_rd_data);
        check32("P2: quotes==12", axi_rd_data, 32'd12);

        // STATUS: risk_halt=0, link_up=1, fsm=B_TRADING(011), strat=MEAN_REV(00)
        // {25'b0, 0, 1, 011, 00} = 0x2C
        axi_read(9'h040);
        $display("  STATUS = 0x%08X (expect 0x2C)", axi_rd_data);
        check32("P2: STATUS", axi_rd_data, 32'h0000_002C);

        axi_read(9'h048);
        $display("  orders_sent = %0d", axi_rd_data);

        // ══════════════════════════════════════════════════════════
        // Phase 3: FSM control — TRADING ↔ ARMED
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 3: FSM Control ===");

        // Disable trading_enable → TRADING → ARMED
        sw = 8'h00;
        @(posedge clk); #1;
        check("P3a: → ARMED",      dut.fsm_state == B_ARMED);
        check("P3a: order_en==0",  dut.order_enable == 1'b0);

        // Re-enable + start → ARMED → TRADING
        sw = 8'h01;
        @(posedge clk);
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("P3b: → TRADING",    dut.fsm_state == B_TRADING);

        // ══════════════════════════════════════════════════════════
        // Phase 4: Fill injection via link
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 4: Fill Injection ===");

        send_link_frame(FILL_SYM0_BUY);

        axi_read(9'h04C);
        $display("  fills_rcvd = %0d", axi_rd_data);
        check32("P4: fills==1", axi_rd_data, 32'd1);

        axi_read(9'h058);
        $display("  position[0] = %0d (signed)", $signed(axi_rd_data));
        check32("P4: pos[0]==100", axi_rd_data, 32'd100);

        axi_read(9'h098);
        $display("  cash_lo = 0x%08X", axi_rd_data);

        // ══════════════════════════════════════════════════════════
        // Phase 5: Risk halt → HALTED, only reset exits
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 5: Risk Halt → HALTED ===");

        force dut.risk_halt = 1'b1;
        @(posedge clk); #1;
        check("P5a: → HALTED",     dut.fsm_state == B_HALTED);
        release dut.risk_halt;

        // Start in HALTED → stays HALTED
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("P5b: stays HALTED", dut.fsm_state == B_HALTED);

        // Reset → HALTED → RESET → IDLE
        axi_write(9'h000, 32'h0000_0002);
        check("P5c: → RESET",      dut.fsm_state == B_RESET);
        @(posedge clk); #1;
        check("P5d: → IDLE",       dut.fsm_state == B_IDLE);

        // ══════════════════════════════════════════════════════════
        // Phase 6: AXI config write + readback
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 6: AXI Config Registers ===");

        axi_write(9'h008, 32'h0002_0000);
        axi_read(9'h008);
        check32("P6: threshold",     axi_rd_data, 32'h0002_0000);

        axi_write(9'h00C, 32'h0000_3333);
        axi_read(9'h00C);
        check32("P6: ema_alpha",     axi_rd_data, 32'h0000_3333);

        axi_write(9'h010, 32'h0000_00C8);
        axi_read(9'h010);
        check32("P6: base_qty",      axi_rd_data, 32'h0000_00C8);

        axi_write(9'h014, 32'h0000_03E8);
        axi_read(9'h014);
        check32("P6: max_position",  axi_rd_data, 32'h0000_03E8);

        axi_read(9'h018);
        check32("P6: max_ord_rate",  axi_rd_data, 32'd1000);

        axi_read(9'h01C);
        check32("P6: max_loss",      axi_rd_data, 32'd100);

        axi_write(9'h004, 32'h0000_0001);
        axi_read(9'h004);
        check32("P6: strategy=MOM",  axi_rd_data, 32'h0000_0001);

        // Strategy override via switches
        sw = 8'h0E;  // sw[3]=override, sw[2:1]=11=AUTO, sw[0]=0
        @(posedge clk);
        axi_read(9'h040);
        $display("  STATUS w/ override = 0x%08X", axi_rd_data);
        check("P6: strat override=AUTO", axi_rd_data[1:0] == 2'b11);
        sw = 8'h00;
        @(posedge clk);

        // ══════════════════════════════════════════════════════════
        // Phase 7: Counter clear on FSM RESET
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 7: Counter Clear ===");

        send_link_frame(GM_FRAMES[0]);
        axi_read(9'h044);
        $display("  quotes after 1 frame = %0d", axi_rd_data);
        check("P7a: quotes>=1", axi_rd_data >= 32'd1);

        axi_write(9'h000, 32'h0000_0002);
        repeat (3) @(posedge clk);

        axi_read(9'h044);
        check32("P7b: quotes cleared", axi_rd_data, 32'd0);

        axi_read(9'h048);
        check32("P7c: orders cleared", axi_rd_data, 32'd0);

        axi_read(9'h04C);
        check32("P7d: fills cleared",  axi_rd_data, 32'd0);

        // ══════════════════════════════════════════════════════════
        // Phase 8: LED / RGB structural
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 8: LED/RGB Outputs ===");

        // Currently in IDLE (B_IDLE = 3'b001)
        check("P8a: LED[2:0]=IDLE",  led[2:0] == 3'b001);
        check("P8b: LED[5]=0 halt",  led[5] == 1'b0);
        check("P8c: LED[6]=0 ord_en",led[6] == 1'b0);

        // RGB1: link_up is cleared by the reset in phase 7
        // After counter_clr, link_up=0, so rgb1 = yellow (110)
        check("P8d: rgb1 yellow",    rgb1 == 3'b110);

        // ══════════════════════════════════════════════════════════
        // Phase 9: Full round-trip with more golden frames
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 9: Full Round-Trip ===");

        send_link_frame(GM_FRAMES[0]);
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        sw = 8'h01;
        @(posedge clk);
        axi_write(9'h000, 32'h0000_0001);
        repeat (2) @(posedge clk);
        check("P9a: in TRADING",     dut.fsm_state == B_TRADING);

        // LED should reflect TRADING
        check("P9b: LED[2:0]=TRADING", led[2:0] == 3'b011);
        check("P9c: LED[6]=order_en",  led[6] == 1'b1);

        for (int i = 1; i < 20; i++)
            send_link_frame(GM_FRAMES[i]);

        repeat (30) @(posedge clk);

        axi_read(9'h044);
        $display("  Final quotes = %0d (expect 21: 1 setup + 19 pipeline + 1 from phase 9 setup)", axi_rd_data);
        check("P9d: quotes>=20", axi_rd_data >= 32'd20);

        axi_read(9'h048);
        $display("  Final orders = %0d", axi_rd_data);

        axi_read(9'h050);
        $display("  Final rejects = %0d", axi_rd_data);

        axi_read(9'h054);
        $display("  link_errors = %0d", axi_rd_data);
        check32("P9e: link_errors==0", axi_rd_data, 32'd0);

        // ══════════════════════════════════════════════════════════
        // Phase 10: Second fill + position readback
        // ══════════════════════════════════════════════════════════
        $display("\n=== Phase 10: Second Fill + Position ===");

        // Construct valid FILL for sym=1, SELL, qty=50
        // {MSG_FILL, sym=1, side=1(SELL), status=000, price=0x01A40821, qty=50, ...}
        // [127:124]=3, [123:116]=0x01, [115]=1, [114:112]=000, [111:80]=0x01A40821
        // Hex: 3 01 8 01A40821 0032 0002 0037 00000000
        // Bytes: 30 18 01A40821 0032 0002 0037 00000000
        // Actually let me construct carefully:
        // [127:120] = {4'h3, 4'h0} = 0x30 (msg_type + upper nibble of symbol)
        // [119:112] = {4'h1, 1'b1, 3'b000} = 0001_1000 = 0x18 (lower nibble of sym + side + status)
        // [111:80]  = 0x01A40821
        // [79:64]   = 0x0032 (qty=50)
        // [63:48]   = 0x0002
        // [47:32]   = 0x0037 (ts=55)
        // [31:0]    = 0x00000000
        send_link_frame(128'h3018_01A4_0821_0032_0002_0037_0000_0000);
        repeat (5) @(posedge clk);

        axi_read(9'h04C);
        $display("  fills_rcvd = %0d", axi_rd_data);

        axi_read(9'h05C);  // POS_SYM[1] = 0x058 + 4 = 0x05C
        $display("  position[1] = %0d (signed)", $signed(axi_rd_data));
        // SELL fill: position goes down → -50
        check32("P10: pos[1]==-50", axi_rd_data, 32'hFFFF_FFCE);  // -50 in 2's complement

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
