// ============================================================================
// Testbench: tb_board_a_top
// Full 16-symbol integration test for Board A. Exercises:
//   - AXI config: all 16 init_mid, init_spread, sector_id values
//   - FSM: RESET→IDLE→RUNNING→STOPPED→RUNNING→RESET cycle
//   - Quote generation with 16 symbols (round-robin verification)
//   - Link loopback: capture quote, inject order, receive fill
//   - Multiple order injections across different symbols
//   - Regime change mid-flight (CALM→VOLATILE→ADVERSARIAL→CALM)
//   - Active symbol count change
//   - Counter verification and reset
//   - STATUS register decode
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_a_top;

    localparam logic [7:0] ADDR_CTRL           = 8'h00;
    localparam logic [7:0] ADDR_QUOTE_INT      = 8'h04;
    localparam logic [7:0] ADDR_LFSR_SEED      = 8'h08;
    localparam logic [7:0] ADDR_REGIME         = 8'h0C;
    localparam logic [7:0] ADDR_INIT_MID_BASE  = 8'h10;
    localparam logic [7:0] ADDR_INIT_SPR_BASE  = 8'h50;
    localparam logic [7:0] ADDR_SECTOR_BASE    = 8'h90;
    localparam logic [7:0] ADDR_ACTIVE_CNT     = 8'hF0;
    localparam logic [7:0] ADDR_STATUS         = 8'hF4;
    localparam logic [7:0] ADDR_QUOTES_SENT    = 8'hF8;
    localparam logic [7:0] ADDR_ORDERS_RCVD    = 8'hFC;

    localparam C_AW = 8;
    localparam C_DW = 32;
    localparam LINK_W = LINK_DATA_W;
    localparam TB_NUM_SYM = 16;

    logic        clk;
    logic        rst_n;
    logic [3:0]  btn;
    logic [7:0]  sw;
    logic [7:0]  led;
    logic [2:0]  rgb0, rgb1;
    logic [LINK_W-1:0] pmod_ja;
    logic               pmod_ja_valid;
    logic               pmod_ja_ready;
    logic [LINK_W-1:0] pmod_jb;
    logic               pmod_jb_valid;
    logic               pmod_jb_ready;

    logic [C_AW-1:0] s_axi_awaddr;
    logic [2:0]       s_axi_awprot;
    logic             s_axi_awvalid;
    logic             s_axi_awready;
    logic [C_DW-1:0]  s_axi_wdata;
    logic [3:0]       s_axi_wstrb;
    logic             s_axi_wvalid;
    logic             s_axi_wready;
    logic [1:0]       s_axi_bresp;
    logic             s_axi_bvalid;
    logic             s_axi_bready;
    logic [C_AW-1:0]  s_axi_araddr;
    logic [2:0]       s_axi_arprot;
    logic             s_axi_arvalid;
    logic             s_axi_arready;
    logic [C_DW-1:0]  s_axi_rdata;
    logic [1:0]       s_axi_rresp;
    logic             s_axi_rvalid;
    logic             s_axi_rready;

    int pass_count = 0;
    int fail_count = 0;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    board_a_top #(.NUM_SYM(TB_NUM_SYM)) dut (
        .clk           (clk),
        .rst_n         (rst_n),
        .btn           (btn),
        .sw            (sw),
        .led           (led),
        .rgb0          (rgb0),
        .rgb1          (rgb1),
        .pmod_ja       (pmod_ja),
        .pmod_ja_valid (pmod_ja_valid),
        .pmod_ja_ready (pmod_ja_ready),
        .pmod_jb       (pmod_jb),
        .pmod_jb_valid (pmod_jb_valid),
        .pmod_jb_ready (pmod_jb_ready),
        .s_axi_awaddr  (s_axi_awaddr),
        .s_axi_awprot  (s_axi_awprot),
        .s_axi_awvalid (s_axi_awvalid),
        .s_axi_awready (s_axi_awready),
        .s_axi_wdata   (s_axi_wdata),
        .s_axi_wstrb   (s_axi_wstrb),
        .s_axi_wvalid  (s_axi_wvalid),
        .s_axi_wready  (s_axi_wready),
        .s_axi_bresp   (s_axi_bresp),
        .s_axi_bvalid  (s_axi_bvalid),
        .s_axi_bready  (s_axi_bready),
        .s_axi_araddr  (s_axi_araddr),
        .s_axi_arprot  (s_axi_arprot),
        .s_axi_arvalid (s_axi_arvalid),
        .s_axi_arready (s_axi_arready),
        .s_axi_rdata   (s_axi_rdata),
        .s_axi_rresp   (s_axi_rresp),
        .s_axi_rvalid  (s_axi_rvalid),
        .s_axi_rready  (s_axi_rready)
    );

    // TX monitor: captures quotes going out on PMOD JA
    logic [127:0] tx_captured_frame;
    logic         tx_frame_valid;
    logic         tx_link_up;
    logic [31:0]  tx_error_count;

    link_rx #(.FRAME_W(128), .DATA_W(LINK_W)) u_tx_mon (
        .clk             (clk),
        .rst_n           (rst_n),
        .counter_clr     (1'b0),
        .pmod_data       (pmod_ja),
        .pmod_valid      (pmod_ja_valid),
        .local_ready     (pmod_ja_ready),
        .frame_out       (tx_captured_frame),
        .frame_out_valid (tx_frame_valid),
        .link_up         (tx_link_up),
        .error_count     (tx_error_count)
    );

    // RX driver: injects ORDER frames into Board A's RX path
    logic [127:0] rx_inject_frame;
    logic         rx_inject_valid;
    logic         rx_inject_ready;

    link_tx #(.FRAME_W(128), .DATA_W(LINK_W)) u_rx_driver (
        .clk            (clk),
        .rst_n          (rst_n),
        .frame_in       (rx_inject_frame),
        .frame_in_valid (rx_inject_valid),
        .frame_in_ready (rx_inject_ready),
        .pmod_data      (pmod_jb),
        .pmod_valid     (pmod_jb_valid),
        .remote_ready   (pmod_jb_ready)
    );

    // ── Golden model 16-symbol config ─────────────────────────
    logic [31:0] gm_mid    [0:15];
    logic [31:0] gm_spread [0:15];
    logic [31:0] gm_sector [0:15];

    initial begin
        gm_mid[ 0]=32'h00B4_0000; gm_mid[ 1]=32'h01A4_0000;
        gm_mid[ 2]=32'h0384_0000; gm_mid[ 3]=32'h0073_0000;
        gm_mid[ 4]=32'h00A0_0000; gm_mid[ 5]=32'h009B_0000;
        gm_mid[ 6]=32'h0208_0000; gm_mid[ 7]=32'h00B9_0000;
        gm_mid[ 8]=32'h00FA_0000; gm_mid[ 9]=32'h00C8_0000;
        gm_mid[10]=32'h01E0_0000; gm_mid[11]=32'h0168_0000;
        gm_mid[12]=32'h00C8_0000; gm_mid[13]=32'h00A5_0000;
        gm_mid[14]=32'h003C_0000; gm_mid[15]=32'h00AF_0000;

        gm_spread[ 0]=32'h0000_199A; gm_spread[ 1]=32'h0000_2666;
        gm_spread[ 2]=32'h0000_4000; gm_spread[ 3]=32'h0000_147B;
        gm_spread[ 4]=32'h0000_199A; gm_spread[ 5]=32'h0000_147B;
        gm_spread[ 6]=32'h0000_3333; gm_spread[ 7]=32'h0000_199A;
        gm_spread[ 8]=32'h0000_4CCD; gm_spread[ 9]=32'h0000_199A;
        gm_spread[10]=32'h0000_3333; gm_spread[11]=32'h0000_2666;
        gm_spread[12]=32'h0000_199A; gm_spread[13]=32'h0000_0F5C;
        gm_spread[14]=32'h0000_0A3D; gm_spread[15]=32'h0000_199A;

        gm_sector[ 0]=0; gm_sector[ 1]=0; gm_sector[ 2]=0; gm_sector[ 3]=1;
        gm_sector[ 4]=1; gm_sector[ 5]=2; gm_sector[ 6]=2; gm_sector[ 7]=3;
        gm_sector[ 8]=3; gm_sector[ 9]=4; gm_sector[10]=4; gm_sector[11]=5;
        gm_sector[12]=5; gm_sector[13]=6; gm_sector[14]=6; gm_sector[15]=7;
    end

    // ── Simulation timeout ────────────────────────────────────
    initial begin
        #10_000_000;
        $display("[TIMEOUT] tb_board_a_top exceeded 10 ms");
        $finish;
    end

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

    task automatic axi_write(input logic [7:0] addr, input logic [31:0] data);
        @(posedge clk);
        s_axi_awaddr  = addr;
        s_axi_awvalid = 1'b1;
        s_axi_wdata   = data;
        s_axi_wstrb   = 4'hF;
        s_axi_wvalid  = 1'b1;
        @(posedge clk);
        while (!(s_axi_awready && s_axi_wready)) @(posedge clk);
        s_axi_awvalid = 1'b0;
        s_axi_wvalid  = 1'b0;
        s_axi_bready  = 1'b1;
        while (!s_axi_bvalid) @(posedge clk);
        @(posedge clk);
        s_axi_bready  = 1'b0;
    endtask

    task automatic axi_read(input logic [7:0] addr, output logic [31:0] data);
        @(posedge clk);
        s_axi_araddr  = addr;
        s_axi_arvalid = 1'b1;
        @(posedge clk);
        while (!s_axi_arready) @(posedge clk);
        s_axi_arvalid = 1'b0;
        s_axi_rready  = 1'b1;
        while (!s_axi_rvalid) @(posedge clk);
        data = s_axi_rdata;
        @(posedge clk);
        s_axi_rready  = 1'b0;
    endtask

    task automatic wait_tx_frame(output logic [127:0] f, input int timeout = 500);
        int cnt = 0;
        f = '0;
        @(posedge clk);
        while (!tx_frame_valid && cnt < timeout) begin
            @(posedge clk);
            cnt++;
        end
        if (tx_frame_valid) begin
            f = tx_captured_frame;
            @(posedge clk);
        end
    endtask

    // Inject an ORDER and wait for it to be accepted
    task automatic inject_order(
        input logic [7:0]  sym,
        input logic        side,
        input logic [31:0] price,
        input int          qty,
        input int          oid,
        input int          ts
    );
        rx_inject_frame = {MSG_ORDER, sym, side, 3'b000, price, qty[15:0], oid[15:0], ts[15:0], 32'h0};
        rx_inject_valid = 1'b1;
        while (!(rx_inject_ready && rx_inject_valid)) @(posedge clk);
        @(posedge clk);
        rx_inject_valid = 1'b0;
    endtask

    initial begin
        logic [31:0] rd_val;
        logic [127:0] captured;

        $dumpfile("tb_board_a_top.vcd");
        $dumpvars(0, tb_board_a_top);

        btn              = 4'b0;
        sw               = 8'h0;
        rx_inject_frame  = '0;
        rx_inject_valid  = 1'b0;
        s_axi_awaddr     = '0;
        s_axi_awprot     = 3'b0;
        s_axi_awvalid    = 1'b0;
        s_axi_wdata      = '0;
        s_axi_wstrb      = 4'h0;
        s_axi_wvalid     = 1'b0;
        s_axi_bready     = 1'b0;
        s_axi_araddr     = '0;
        s_axi_arprot     = 3'b0;
        s_axi_arvalid    = 1'b0;
        s_axi_rready     = 1'b0;

        @(posedge clk);
        wait (rst_n === 1'b1);
        repeat (20) @(posedge clk);

        // ─────────────────────────────────────────────────────
        // 1) AXI config: full 16-symbol universe
        // ─────────────────────────────────────────────────────
        $display("--- test_axi_config_16sym ---");

        axi_write(ADDR_QUOTE_INT, 32'd0);
        axi_write(ADDR_LFSR_SEED, 32'hDEAD_BEEF);
        axi_write(ADDR_REGIME, 32'd0);
        axi_write(ADDR_ACTIVE_CNT, 32'd16);

        for (int i = 0; i < 16; i++) begin
            axi_write(ADDR_INIT_MID_BASE + i*4, gm_mid[i]);
            axi_write(ADDR_INIT_SPR_BASE + i*4, gm_spread[i]);
            axi_write(ADDR_SECTOR_BASE   + i*4, gm_sector[i]);
        end

        // Verify readback of config
        axi_read(ADDR_ACTIVE_CNT, rd_val);
        check32("readback ACTIVE_CNT", rd_val, 32'd16);

        for (int i = 0; i < 16; i++) begin
            axi_read(ADDR_INIT_MID_BASE + i*4, rd_val);
            check32($sformatf("readback mid[%0d]", i), rd_val, gm_mid[i]);
        end

        axi_read(ADDR_INIT_SPR_BASE, rd_val);
        check32("readback spread[0]", rd_val, gm_spread[0]);

        axi_read(ADDR_SECTOR_BASE + 15*4, rd_val);
        check32("readback sector[15]", rd_val, gm_sector[15]);

        // ─────────────────────────────────────────────────────
        // 2) FSM: IDLE → RUNNING
        // ─────────────────────────────────────────────────────
        $display("--- test_fsm_start ---");
        axi_read(ADDR_STATUS, rd_val);
        check("pre-start: running=0", (rd_val & 32'h1) == 0);

        axi_write(ADDR_CTRL, 32'd1);
        repeat (4) @(posedge clk);

        axi_read(ADDR_STATUS, rd_val);
        check("post-start: running=1", (rd_val & 32'h1) == 1);

        // ─────────────────────────────────────────────────────
        // 3) Quote generation with 16 symbols
        // ─────────────────────────────────────────────────────
        $display("--- test_quote_generation_16sym ---");
        repeat (3000) @(posedge clk);

        axi_read(ADDR_QUOTES_SENT, rd_val);
        check("quotes_sent > 0", rd_val > 0);
        $display("  quotes_sent = %0d", rd_val);

        // ─────────────────────────────────────────────────────
        // 4) Capture quotes and verify diversity of symbols
        // ─────────────────────────────────────────────────────
        $display("--- test_symbol_diversity ---");
        begin
            logic [15:0] symbols_seen;
            symbols_seen = 16'h0;

            for (int i = 0; i < 32; i++) begin
                wait_tx_frame(captured, 200);
                if (captured[127:124] == 4'h1) begin
                    logic [7:0] cap_sym;
                    cap_sym = captured[123:116];
                    if (cap_sym < 16)
                        symbols_seen[cap_sym] = 1'b1;
                end
            end

            begin
                int sym_count = 0;
                for (int i = 0; i < 16; i++)
                    sym_count += symbols_seen[i];
                $display("  Unique symbols seen: %0d / 16", sym_count);
                check("diversity: >=4 symbols", sym_count >= 4);
            end
        end

        // ─────────────────────────────────────────────────────
        // 5) STATUS register decode
        // ─────────────────────────────────────────────────────
        $display("--- test_status_decode ---");
        axi_read(ADDR_STATUS, rd_val);
        begin
            logic       st_running;
            logic       st_link_up;
            logic [1:0] st_regime;
            logic [6:0] st_fifo_fill;
            st_running   = rd_val[0];
            st_link_up   = rd_val[1];
            st_regime    = rd_val[3:2];
            st_fifo_fill = rd_val[22:16];
            check("status: running=1", st_running == 1'b1);
            check32("status: regime=CALM", {30'b0, st_regime}, 32'd0);
            $display("  fifo_fill=%0d link_up=%0b", st_fifo_fill, st_link_up);
        end

        // ─────────────────────────────────────────────────────
        // 6) Link loopback: inject ORDER for sym 0, verify fill
        // ─────────────────────────────────────────────────────
        $display("--- test_link_order_sym0 ---");

        wait_tx_frame(captured);
        check("cap: msg_type=QUOTE", captured[127:124] == 4'h1);

        begin
            logic [7:0]  cap_sym;
            logic [31:0] cap_ask;
            cap_sym = captured[123:116];
            cap_ask = captured[79:48];
            $display("  Captured: sym=%0d ask=0x%08X", cap_sym, cap_ask);

            inject_order(cap_sym, 1'b0, cap_ask, 100, 1, 16'hBEEF);
        end

        repeat (500) @(posedge clk);
        axi_read(ADDR_ORDERS_RCVD, rd_val);
        check("orders_rcvd > 0", rd_val > 0);
        $display("  orders_rcvd = %0d", rd_val);

        // ─────────────────────────────────────────────────────
        // 7) Multiple order injections: different symbols
        // ─────────────────────────────────────────────────────
        $display("--- test_multi_order ---");

        begin
            logic [31:0] orders_before;
            axi_read(ADDR_ORDERS_RCVD, orders_before);

            // Inject orders for symbols 1, 5, 10, 15
            for (int i = 0; i < 4; i++) begin
                int sym_idx;
                sym_idx = (i == 0) ? 1 : (i == 1) ? 5 : (i == 2) ? 10 : 15;
                inject_order(sym_idx[7:0], 1'b0, gm_mid[sym_idx] + 32'h0001_0000, 50, 10+i, 16'h1000+i);
                repeat (200) @(posedge clk);
            end

            axi_read(ADDR_ORDERS_RCVD, rd_val);
            $display("  orders_rcvd after multi = %0d (was %0d)", rd_val, orders_before);
            check("multi-order: rcvd increased", rd_val > orders_before);
        end

        // ─────────────────────────────────────────────────────
        // 8) Regime change: CALM → VOLATILE → ADVERSARIAL → CALM
        // ─────────────────────────────────────────────────────
        $display("--- test_regime_change ---");

        begin
            logic [31:0] q_before, q_after;
            axi_read(ADDR_QUOTES_SENT, q_before);

            // VOLATILE
            axi_write(ADDR_REGIME, 32'd1);
            repeat (1000) @(posedge clk);
            axi_read(ADDR_STATUS, rd_val);
            check("regime=VOLATILE", rd_val[3:2] == 2'b01);

            // ADVERSARIAL
            axi_write(ADDR_REGIME, 32'd3);
            repeat (1000) @(posedge clk);
            axi_read(ADDR_STATUS, rd_val);
            check("regime=ADVERSARIAL", rd_val[3:2] == 2'b11);

            // Back to CALM
            axi_write(ADDR_REGIME, 32'd0);
            repeat (500) @(posedge clk);
            axi_read(ADDR_STATUS, rd_val);
            check("regime=CALM again", rd_val[3:2] == 2'b00);

            axi_read(ADDR_QUOTES_SENT, q_after);
            check("quotes still flowing", q_after > q_before);
        end

        // ─────────────────────────────────────────────────────
        // 9) Active symbol count change (16 → 4 → 16)
        // ─────────────────────────────────────────────────────
        $display("--- test_active_sym_change ---");

        begin
            logic [31:0] q_4sym, q_16sym;
            axi_write(ADDR_ACTIVE_CNT, 32'd4);
            axi_read(ADDR_ACTIVE_CNT, rd_val);
            check32("active=4", rd_val, 32'd4);
            repeat (1000) @(posedge clk);

            axi_write(ADDR_ACTIVE_CNT, 32'd16);
            axi_read(ADDR_ACTIVE_CNT, rd_val);
            check32("active=16", rd_val, 32'd16);
        end

        // ─────────────────────────────────────────────────────
        // 10) FSM: RUNNING → STOPPED
        // ─────────────────────────────────────────────────────
        $display("--- test_fsm_stop ---");
        btn[1] = 1'b1;
        repeat (70000) @(posedge clk);
        btn[1] = 1'b0;
        repeat (100) @(posedge clk);
        axi_read(ADDR_STATUS, rd_val);
        check("stopped: running=0", (rd_val & 32'h1) == 0);

        // ─────────────────────────────────────────────────────
        // 11) FSM: STOPPED → RUNNING (resume)
        // ─────────────────────────────────────────────────────
        $display("--- test_fsm_resume ---");
        begin
            logic [31:0] qbefore;
            axi_read(ADDR_QUOTES_SENT, qbefore);
            axi_write(ADDR_CTRL, 32'd1);
            repeat (2000) @(posedge clk);
            axi_read(ADDR_STATUS, rd_val);
            check("resume: running=1", (rd_val & 32'h1) == 1);
            axi_read(ADDR_QUOTES_SENT, rd_val);
            check("resume: quotes increased", rd_val > qbefore);
        end

        // ─────────────────────────────────────────────────────
        // 12) Reset clears counters
        // ─────────────────────────────────────────────────────
        $display("--- test_reset_clears ---");
        axi_write(ADDR_CTRL, 32'd2);
        repeat (10) @(posedge clk);
        axi_read(ADDR_QUOTES_SENT, rd_val);
        check32("reset: quotes=0", rd_val, 0);
        axi_read(ADDR_ORDERS_RCVD, rd_val);
        check32("reset: orders=0", rd_val, 0);
        axi_read(ADDR_STATUS, rd_val);
        check("reset: running=0", (rd_val & 32'h1) == 0);

        // ─────────────────────────────────────────────────────
        // 13) Re-start with different seed
        // ─────────────────────────────────────────────────────
        $display("--- test_restart_new_seed ---");
        axi_write(ADDR_LFSR_SEED, 32'hCAFE_BABE);
        axi_write(ADDR_CTRL, 32'd1);
        repeat (1000) @(posedge clk);
        axi_read(ADDR_QUOTES_SENT, rd_val);
        check("restart: quotes>0", rd_val > 0);
        $display("  quotes after restart = %0d", rd_val);

        // ─────────────────────────────────────────────────────
        // 14) SELL order injection (verify both sides)
        // ─────────────────────────────────────────────────────
        $display("--- test_sell_order ---");

        wait_tx_frame(captured);
        if (captured[127:124] == 4'h1) begin
            logic [31:0] cap_bid;
            logic [7:0]  cap_sym;
            cap_bid = captured[111:80];
            cap_sym = captured[123:116];
            inject_order(cap_sym, 1'b1, cap_bid, 75, 50, 16'hDEAD);
            repeat (300) @(posedge clk);
            axi_read(ADDR_ORDERS_RCVD, rd_val);
            check("sell order rcvd", rd_val > 0);
            $display("  SELL order for sym=%0d, orders_rcvd=%0d", cap_sym, rd_val);
        end

        // ─────────────────────────────────────────────────────
        // 15) Edge case: active_sym_count=1
        // ─────────────────────────────────────────────────────
        $display("--- test_single_symbol ---");
        axi_write(ADDR_CTRL, 32'd2);  // reset
        repeat (10) @(posedge clk);
        axi_write(ADDR_ACTIVE_CNT, 32'd1);
        axi_write(ADDR_CTRL, 32'd1);  // start
        repeat (1000) @(posedge clk);

        begin
            int sym0_count = 0;
            for (int i = 0; i < 8; i++) begin
                wait_tx_frame(captured, 300);
                if (captured[127:124] == 4'h1 && captured[123:116] == 8'd0)
                    sym0_count++;
            end
            $display("  With 1 symbol: sym0 quotes = %0d / 8", sym0_count);
            check("single sym: all sym=0", sym0_count >= 6);
        end

        // Restore
        axi_write(ADDR_ACTIVE_CNT, 32'd16);

        // ─────────────────────────────────────────────────────
        // 16) Edge case: active_sym_count=0 → clamped to 1
        // ─────────────────────────────────────────────────────
        $display("--- test_zero_sym_clamp ---");
        axi_write(ADDR_ACTIVE_CNT, 32'd0);
        axi_read(ADDR_ACTIVE_CNT, rd_val);
        check32("zero clamped to 1", rd_val, 32'd1);

        axi_write(ADDR_ACTIVE_CNT, 32'd16);

        // ─────────────────────────────────────────────────────
        // 17) Edge case: active_sym_count > NUM_SYM → clamped
        // ─────────────────────────────────────────────────────
        $display("--- test_oversized_sym_clamp ---");
        axi_write(ADDR_ACTIVE_CNT, 32'd255);
        axi_read(ADDR_ACTIVE_CNT, rd_val);
        check32("oversized clamped to 16", rd_val, 32'd16);

        // ─────────────────────────────────────────────────────
        // 18) Quote frame field validation (bid < ask, sizes, regime)
        // ─────────────────────────────────────────────────────
        $display("--- test_quote_fields ---");
        begin
            logic [127:0] qf;
            logic [31:0]  qf_bid, qf_ask;
            logic [15:0]  qf_bsz, qf_asz;
            logic [1:0]   qf_regime;
            int valid_frames;
            valid_frames = 0;
            for (int i = 0; i < 8; i++) begin
                wait_tx_frame(qf, 300);
                if (qf[127:124] == 4'h1) begin
                    qf_bid    = qf[111:80];
                    qf_ask    = qf[79:48];
                    qf_bsz   = qf[47:32];
                    qf_asz   = qf[31:16];
                    qf_regime = qf[115:114];
                    if (qf_bid < qf_ask && qf_bsz > 0 && qf_asz > 0)
                        valid_frames++;
                end
            end
            $display("  Valid quote frames: %0d / 8", valid_frames);
            check("quote fields: bid<ask, sizes>0", valid_frames >= 4);
        end

        // ─────────────────────────────────────────────────────
        // 19) Fill capture after order: verify exchange responds
        // ─────────────────────────────────────────────────────
        $display("--- test_fill_response ---");
        begin
            logic [127:0] qcap, fcap;
            logic [7:0]   ord_sym;
            logic [31:0]  ord_price;
            int found_fill;

            wait_tx_frame(qcap, 300);
            if (qcap[127:124] == 4'h1) begin
                ord_sym   = qcap[123:116];
                ord_price = qcap[79:48];
                inject_order(ord_sym, 1'b0, ord_price, 200, 77, 16'hFACE);

                found_fill = 0;
                for (int i = 0; i < 16; i++) begin
                    wait_tx_frame(fcap, 300);
                    if (fcap[127:124] == 4'h3) begin
                        check32("fill sym matches", {24'd0, fcap[123:116]}, {24'd0, ord_sym});
                        check("fill side=BUY", fcap[115] == 1'b0);
                        found_fill = 1;
                        break;
                    end
                end
                check("received fill frame", found_fill == 1);
            end
        end

        // ─────────────────────────────────────────────────────
        // 20) BURST regime
        // ─────────────────────────────────────────────────────
        $display("--- test_burst_regime ---");
        axi_write(ADDR_REGIME, 32'd2);
        repeat (500) @(posedge clk);
        axi_read(ADDR_STATUS, rd_val);
        check("regime=BURST", rd_val[3:2] == 2'b10);
        axi_write(ADDR_REGIME, 32'd0);

        // ─────────────────────────────────────────────────────
        // 21) LED/RGB checks for RUNNING state
        // ─────────────────────────────────────────────────────
        $display("--- test_led_running ---");
        check("LED[2]=running", led[2] == 1'b1);
        check("LED[1:0]=CALM", led[1:0] == 2'b00);

        // ─────────────────────────────────────────────────────
        // 22) Spread readback for all 16 symbols
        // ─────────────────────────────────────────────────────
        $display("--- test_spread_readback ---");
        for (int i = 0; i < 16; i++) begin
            axi_read(ADDR_INIT_SPR_BASE + i*4, rd_val);
            check32($sformatf("spread[%0d]", i), rd_val, gm_spread[i]);
        end

        // ─────────────────────────────────────────────────────
        // 23) Non-zero quote interval (slower generation)
        // ─────────────────────────────────────────────────────
        $display("--- test_slow_interval ---");
        axi_write(ADDR_CTRL, 32'd2);
        repeat (10) @(posedge clk);
        axi_write(ADDR_QUOTE_INT, 32'd500);
        axi_write(ADDR_CTRL, 32'd1);
        repeat (3000) @(posedge clk);
        axi_read(ADDR_QUOTES_SENT, rd_val);
        $display("  With interval=500: quotes = %0d (expect ~5-6)", rd_val);
        check("slow interval: quotes in range", rd_val >= 32'd3 && rd_val <= 32'd20);
        axi_write(ADDR_QUOTE_INT, 32'd0);

        // ─────────────────────────────────────────────────────
        // 24) Back-to-back rapid order injection (4 orders, no gap)
        // ─────────────────────────────────────────────────────
        $display("--- test_rapid_orders ---");
        begin
            logic [31:0] ords_before;
            axi_read(ADDR_ORDERS_RCVD, ords_before);
            for (int i = 0; i < 4; i++)
                inject_order(i[7:0], 1'b0, gm_mid[i] + 32'h0005_0000, 25, 100+i, 16'h2000+i);
            repeat (500) @(posedge clk);
            axi_read(ADDR_ORDERS_RCVD, rd_val);
            check("rapid orders: rcvd+=4", rd_val == ords_before + 32'd4);
        end

        // ─────────────────────────────────────────────────────
        // 25) LED/RGB in STOPPED state
        // ─────────────────────────────────────────────────────
        $display("--- test_led_stopped ---");
        btn[1] = 1'b1;
        repeat (70000) @(posedge clk);
        btn[1] = 1'b0;
        repeat (100) @(posedge clk);
        check("stopped: LED[2]=0", led[2] == 1'b0);

        // ─────────────────────────────────────────────────────
        // 26) RGB0 per-regime (quick cycle through all 4)
        // ─────────────────────────────────────────────────────
        $display("--- test_rgb0_regimes ---");
        axi_write(ADDR_CTRL, 32'd1);
        repeat (4) @(posedge clk);

        axi_write(ADDR_REGIME, 32'd0);
        repeat (2) @(posedge clk);
        check("rgb0 CALM=green", rgb0 == 3'b010);

        axi_write(ADDR_REGIME, 32'd1);
        repeat (2) @(posedge clk);
        check("rgb0 VOL=yellow", rgb0 == 3'b110);

        axi_write(ADDR_REGIME, 32'd2);
        repeat (2) @(posedge clk);
        check("rgb0 BURST=red", rgb0 == 3'b100);

        axi_write(ADDR_REGIME, 32'd3);
        repeat (2) @(posedge clk);
        check("rgb0 ADV=magenta", rgb0 == 3'b101);

        axi_write(ADDR_REGIME, 32'd0);

        // ─────────────────────────────────────────────────────
        // 27) Verify link monitor had zero errors
        // ─────────────────────────────────────────────────────
        $display("--- test_link_no_errors ---");
        check32("TX monitor: 0 errors", tx_error_count, 32'd0);
        check("TX monitor: link_up", tx_link_up == 1'b1);

        // ─────────────────────────────────────────────────────
        // Summary
        // ─────────────────────────────────────────────────────
        $display("\n===================================");
        if (fail_count == 0)
            $display("tb_board_a_top: PASS (%0d checks passed)", pass_count);
        else begin
            $display("tb_board_a_top: FAIL (%0d passed, %0d failed)", pass_count, fail_count);
            $fatal;
        end
        $display("===================================");
        $finish;
    end

endmodule
