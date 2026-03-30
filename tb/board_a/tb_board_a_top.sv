// ============================================================================
// Testbench: tb_board_a_top
// Full FSM exercise (RESET→IDLE→RUNNING→STOPPED→RUNNING→RESET), AXI config
// write/readback, STATUS register decode, quote generation, link loopback
// fill path, FIFO fill level, reset clears counters.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_a_top;

    // AXI register addresses (must match board_a_axi_regs.sv)
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

    // AXI signals
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

    board_a_top dut (
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

    // link_rx monitor on TX output (to capture quotes going to Board B)
    logic [127:0] tx_captured_frame;
    logic         tx_frame_valid;
    logic         tx_link_up;
    logic [31:0]  tx_error_count;
    logic         tx_mon_ready;

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

    // link_tx driver for injecting ORDER frames into RX path
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

    // Wait for a frame on the TX monitor
    task automatic wait_tx_frame(output logic [127:0] f, input int timeout = 500);
        int cnt = 0;
        f = '0;
        while (!tx_frame_valid && cnt < timeout) begin
            @(posedge clk);
            cnt++;
        end
        if (tx_frame_valid) f = tx_captured_frame;
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
        // 1) AXI config: write all registers, read back
        // ─────────────────────────────────────────────────────
        $display("--- test_axi_config ---");
        axi_write(ADDR_QUOTE_INT, 32'd0);       // quote every cycle
        axi_write(ADDR_LFSR_SEED, 32'hDEAD_BEEF);
        axi_write(ADDR_REGIME, 32'd0);           // CALM
        axi_write(ADDR_ACTIVE_CNT, 32'd4);

        // Write init_mid for 4 symbols
        axi_write(ADDR_INIT_MID_BASE + 0,  32'h00B4_0000); // $180
        axi_write(ADDR_INIT_MID_BASE + 4,  32'h01A4_0000); // $420
        axi_write(ADDR_INIT_MID_BASE + 8,  32'h0384_0000); // $900
        axi_write(ADDR_INIT_MID_BASE + 12, 32'h0073_0000); // $115

        // Write init_spread for 4 symbols
        axi_write(ADDR_INIT_SPR_BASE + 0,  32'h0000_199A); // $0.10
        axi_write(ADDR_INIT_SPR_BASE + 4,  32'h0000_2666); // $0.15
        axi_write(ADDR_INIT_SPR_BASE + 8,  32'h0000_4000); // $0.25
        axi_write(ADDR_INIT_SPR_BASE + 12, 32'h0000_147B); // $0.08

        // Write sector_ids
        axi_write(ADDR_SECTOR_BASE + 0,  32'd0);
        axi_write(ADDR_SECTOR_BASE + 4,  32'd0);
        axi_write(ADDR_SECTOR_BASE + 8,  32'd1);
        axi_write(ADDR_SECTOR_BASE + 12, 32'd1);

        // Read back and verify
        axi_read(ADDR_QUOTE_INT, rd_val);
        check32("readback QUOTE_INT", rd_val, 32'd0);
        axi_read(ADDR_LFSR_SEED, rd_val);
        check32("readback LFSR_SEED", rd_val, 32'hDEAD_BEEF);
        axi_read(ADDR_REGIME, rd_val);
        check32("readback REGIME", rd_val, 32'd0);
        axi_read(ADDR_ACTIVE_CNT, rd_val);
        check32("readback ACTIVE_CNT", rd_val, 32'd4);
        axi_read(ADDR_INIT_MID_BASE, rd_val);
        check32("readback INIT_MID[0]", rd_val, 32'h00B4_0000);

        // ─────────────────────────────────────────────────────
        // 2) FSM: IDLE → RUNNING (AXI start)
        // ─────────────────────────────────────────────────────
        $display("--- test_fsm_start ---");
        axi_read(ADDR_STATUS, rd_val);
        check("pre-start: running=0", (rd_val & 32'h1) == 0);

        axi_write(ADDR_CTRL, 32'd1); // start pulse
        repeat (4) @(posedge clk);

        axi_read(ADDR_STATUS, rd_val);
        check("post-start: running=1", (rd_val & 32'h1) == 1);
        check("led[2] running", led[2] == 1'b1);

        // ─────────────────────────────────────────────────────
        // 3) Quote generation: verify quotes_sent > 0
        // ─────────────────────────────────────────────────────
        $display("--- test_quote_generation ---");
        repeat (2000) @(posedge clk);

        axi_read(ADDR_QUOTES_SENT, rd_val);
        check("quotes_sent > 0", rd_val > 0);
        $display("  quotes_sent = %0d", rd_val);

        // ─────────────────────────────────────────────────────
        // 4) STATUS register decode
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
            $display("  status: fifo_fill=%0d link_up=%0b", st_fifo_fill, st_link_up);
        end

        // ─────────────────────────────────────────────────────
        // 5) Link loopback: capture a quote, inject an order, get a fill
        // ─────────────────────────────────────────────────────
        $display("--- test_link_loopback ---");
        // Wait for a quote to appear on TX monitor
        wait_tx_frame(captured);
        check("captured quote: msg_type=QUOTE", captured[127:124] == 4'h1);
        $display("  captured quote: sym=%0d bid=%08h ask=%08h",
                 captured[123:116], captured[111:80], captured[79:48]);

        // Build an ORDER from the captured quote
        begin
            logic [7:0]  cap_sym;
            logic [31:0] cap_ask;
            logic [127:0] order_f;
            cap_sym = captured[123:116];
            cap_ask = captured[79:48]; // ask price
            order_f = {MSG_ORDER, cap_sym, 1'b0, 3'b000, cap_ask, 16'd100, 16'd1, 16'hBEEF, 32'h0};

            // Inject via link_tx → pmod_jb → link_rx → exchange
            rx_inject_frame = order_f;
            rx_inject_valid = 1'b1;
            while (!(rx_inject_ready && rx_inject_valid)) @(posedge clk);
            @(posedge clk);
            rx_inject_valid = 1'b0;
        end

        // Wait for fill to come back on TX
        repeat (500) @(posedge clk);
        axi_read(ADDR_ORDERS_RCVD, rd_val);
        check("orders_rcvd > 0", rd_val > 0);
        $display("  orders_rcvd = %0d", rd_val);

        // ─────────────────────────────────────────────────────
        // 6) FSM: RUNNING → STOPPED (BTN1)
        // ─────────────────────────────────────────────────────
        $display("--- test_fsm_stop ---");
        // Use BTN1 (stop) — need to hold for debounce window
        btn[1] = 1'b1;
        repeat (70000) @(posedge clk); // long debounce for BTN_DEB_W=16
        btn[1] = 1'b0;
        repeat (100) @(posedge clk);
        axi_read(ADDR_STATUS, rd_val);
        // In STOPPED state, running=0
        check("stopped: running=0", (rd_val & 32'h1) == 0);

        // ─────────────────────────────────────────────────────
        // 7) FSM: STOPPED → RUNNING (resume, no lfsr_load)
        // ─────────────────────────────────────────────────────
        $display("--- test_fsm_resume ---");
        begin
            logic [31:0] qbefore;
            axi_read(ADDR_QUOTES_SENT, qbefore);
            axi_write(ADDR_CTRL, 32'd1); // start
            repeat (2000) @(posedge clk);
            axi_read(ADDR_STATUS, rd_val);
            check("resume: running=1", (rd_val & 32'h1) == 1);
            axi_read(ADDR_QUOTES_SENT, rd_val);
            check("resume: quotes increased", rd_val > qbefore);
        end

        // ─────────────────────────────────────────────────────
        // 8) Reset clears counters
        // ─────────────────────────────────────────────────────
        $display("--- test_reset_clears ---");
        axi_write(ADDR_CTRL, 32'd2); // reset pulse
        repeat (10) @(posedge clk);
        axi_read(ADDR_QUOTES_SENT, rd_val);
        check32("reset: quotes_sent=0", rd_val, 0);
        axi_read(ADDR_ORDERS_RCVD, rd_val);
        check32("reset: orders_rcvd=0", rd_val, 0);
        axi_read(ADDR_STATUS, rd_val);
        check("reset: running=0", (rd_val & 32'h1) == 0);

        // ─────────────────────────────────────────────────────
        // 9) Re-start after reset
        // ─────────────────────────────────────────────────────
        $display("--- test_restart ---");
        axi_write(ADDR_CTRL, 32'd1); // start
        repeat (500) @(posedge clk);
        axi_read(ADDR_QUOTES_SENT, rd_val);
        check("restart: quotes>0", rd_val > 0);

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
