`timescale 1ns / 1ps
import hft_pkg::*;

module tb_board_b_pipeline();

    localparam LINK_W = LINK_DATA_W;

    logic clk = 0;
    logic rst_n;
    logic [3:0] btn;
    logic [7:0] sw;
    logic [7:0] led;
    logic [2:0] rgb0, rgb1;

    logic [LINK_W-1:0] pmod_ja;
    logic pmod_ja_valid, pmod_ja_ready;
    logic [LINK_W-1:0] pmod_jb;
    logic pmod_jb_valid;

    logic [8:0]  awaddr;  logic awvalid, awready;
    logic [31:0] wdata;   logic [3:0] wstrb;
    logic        wvalid,  wready;
    logic [1:0]  bresp;   logic bvalid, bready;
    logic [8:0]  araddr;  logic arvalid, arready;
    logic [31:0] rdata;   logic [1:0] rresp;
    logic        rvalid,  rready;

    logic [FRAME_W-1:0] tx_frame;
    logic tx_valid, tx_ready;

    integer err_cnt = 0;

    always #5 clk = ~clk;

    board_b_top #(.NUM_SYM(4), .LINK_W(LINK_W)) dut (
        .clk(clk), .rst_n(rst_n),
        .btn(btn), .sw(sw), .led(led), .rgb0(rgb0), .rgb1(rgb1),
        .pmod_ja(pmod_ja), .pmod_ja_valid(pmod_ja_valid),
        .pmod_ja_ready(pmod_ja_ready),
        .pmod_jb(pmod_jb), .pmod_jb_valid(pmod_jb_valid),
        .pmod_jb_ready(1'b1),
        .s_axi_awaddr(awaddr), .s_axi_awprot(3'b0),
        .s_axi_awvalid(awvalid), .s_axi_awready(awready),
        .s_axi_wdata(wdata), .s_axi_wstrb(wstrb),
        .s_axi_wvalid(wvalid), .s_axi_wready(wready),
        .s_axi_bresp(bresp), .s_axi_bvalid(bvalid), .s_axi_bready(bready),
        .s_axi_araddr(araddr), .s_axi_arprot(3'b0),
        .s_axi_arvalid(arvalid), .s_axi_arready(arready),
        .s_axi_rdata(rdata), .s_axi_rresp(rresp),
        .s_axi_rvalid(rvalid), .s_axi_rready(rready)
    );

    link_tx #(.FRAME_W(FRAME_W), .DATA_W(LINK_W)) u_tx (
        .clk(clk), .rst_n(rst_n),
        .frame_in(tx_frame), .frame_in_valid(tx_valid),
        .frame_in_ready(tx_ready),
        .pmod_data(pmod_ja), .pmod_valid(pmod_ja_valid),
        .remote_ready(pmod_ja_ready)
    );

    // Golden QUOTE frames for 4 symbols
    localparam logic [127:0] QUOTES [0:4] = '{
        128'h1000_00B3_F81E_00B4_081E_03E8_03E8_0000,
        128'h1010_01A3_F821_01A4_0821_03E8_03E8_0001,
        128'h1020_0383_F816_0384_0816_03E8_03E8_0002,
        128'h1030_0072_F81D_0073_081D_03E8_03E8_0003,
        128'h1000_00B3_F831_00B4_0831_03E8_03E8_0004
    };

    initial begin
        $display("=== tb_board_b_pipeline ===");
        rst_n = 0; btn = 0; sw = 0;
        awaddr = 0; awvalid = 0; wdata = 0; wstrb = 0; wvalid = 0; bready = 0;
        araddr = 0; arvalid = 0; rready = 0;
        tx_frame = 0; tx_valid = 0;
        #20; rst_n = 1; @(posedge clk);
        repeat (5) @(posedge clk);

        // Configure via AXI (generous risk limits)
        // strategy = MEAN_REV
        @(posedge clk); awaddr=9'h004; awvalid=1; wdata=32'd0; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        // threshold = $0.50
        @(posedge clk); awaddr=9'h008; awvalid=1; wdata=32'h8000; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        // ema_alpha ~ 10%
        @(posedge clk); awaddr=9'h00C; awvalid=1; wdata=32'd6554; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        // base_qty = 100
        @(posedge clk); awaddr=9'h010; awvalid=1; wdata=32'd100; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        // max_position = 50000
        @(posedge clk); awaddr=9'h014; awvalid=1; wdata=32'd50000; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        // max_order_rate = 10000
        @(posedge clk); awaddr=9'h018; awvalid=1; wdata=32'd10000; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        // max_loss = $10,000,000 (very generous)
        @(posedge clk); awaddr=9'h01C; awvalid=1; wdata=32'd10_000_000; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;

        // Send first frame to establish link_up
        tx_frame = QUOTES[0]; tx_valid = 1;
        @(posedge clk); tx_valid = 0;
        repeat (80) @(posedge clk);

        // Start FSM -> ARMED -> TRADING
        sw = 8'h01;
        @(posedge clk); awaddr=9'h000; awvalid=1; wdata=32'h1; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        repeat (3) @(posedge clk);
        @(posedge clk); awaddr=9'h000; awvalid=1; wdata=32'h1; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        repeat (3) @(posedge clk);

        // Test 1: Pipeline processes 5 quote frames
        $display("Test 1: Drive 5 quotes through pipeline");
        for (int i = 0; i < 5; i++) begin
            tx_frame = QUOTES[i]; tx_valid = 1;
            @(posedge clk); tx_valid = 0;
            repeat (80) @(posedge clk);
        end
        repeat (30) @(posedge clk);

        // Test 2: Check quotes_rcvd
        $display("Test 2: quotes_rcvd counter");
        @(posedge clk); araddr=9'h044; arvalid=1; rready=1;
        @(posedge clk); arvalid=0; while(!rvalid) @(posedge clk);
        if (rdata >= 32'd5)
            $display("  PASS: quotes_rcvd = %0d (>= 5)", rdata);
        else begin
            $display("  FAIL: quotes_rcvd = %0d, expected >= 5", rdata);
            err_cnt = err_cnt + 1;
        end
        @(posedge clk); rready=0;

        // Test 3: Check orders_sent (pipeline generated orders)
        $display("Test 3: orders_sent counter");
        @(posedge clk); araddr=9'h048; arvalid=1; rready=1;
        @(posedge clk); arvalid=0; while(!rvalid) @(posedge clk);
        $display("  orders_sent = %0d", rdata);
        if (rdata > 0)
            $display("  PASS: pipeline generated orders");
        else
            $display("  INFO: no orders (deviation below threshold)");
        @(posedge clk); rready=0;

        // Test 4: No risk halt (generous limits)
        $display("Test 4: No risk halt");
        @(posedge clk); #1;
        if (!dut.risk_halt)
            $display("  PASS: risk_halt = 0");
        else begin
            $display("  FAIL: risk_halt = 1");
            err_cnt = err_cnt + 1;
        end

        // Test 5: Check link_errors = 0
        $display("Test 5: No link errors");
        @(posedge clk); araddr=9'h054; arvalid=1; rready=1;
        @(posedge clk); arvalid=0; while(!rvalid) @(posedge clk);
        if (rdata == 0)
            $display("  PASS: link_errors = 0");
        else begin
            $display("  FAIL: link_errors = %0d", rdata);
            err_cnt = err_cnt + 1;
        end
        @(posedge clk); rready=0;

        // ──────────────────────────────────────────────────────────
        // Test 6: Send a golden FILL frame and verify fills_rcvd
        //   Frame: MSG_FILL=3, sym=0, side=0(BUY), status=000(FILLED),
        //          price=$180 (Q16.16), qty=100, oid=1, ts_echo=0x0032
        // ──────────────────────────────────────────────────────────
        $display("Test 6: Inject FILL frame -> fills_rcvd increments");
        begin
            logic [127:0] fill_pkt;
            fill_pkt = {4'h3, 8'h00, 1'b0, 3'b000,
                        32'h00B4_0000, 16'd100, 16'd1, 16'h0032, 32'h0};
            tx_frame = fill_pkt; tx_valid = 1;
            @(posedge clk); tx_valid = 0;
            repeat (80) @(posedge clk);
        end
        @(posedge clk); araddr=9'h04C; arvalid=1; rready=1;
        @(posedge clk); arvalid=0; while(!rvalid) @(posedge clk);
        if (rdata > 0)
            $display("  PASS: fills_rcvd = %0d", rdata);
        else begin
            $display("  FAIL: fills_rcvd = 0, expected > 0");
            err_cnt = err_cnt + 1;
        end
        @(posedge clk); rready=0;

        // ──────────────────────────────────────────────────────────
        // Test 7: Read POSITION[0] (addr 0x058)
        //   After a BUY fill of qty=100, position should be +100
        // ──────────────────────────────────────────────────────────
        $display("Test 7: POSITION[0] after BUY fill");
        @(posedge clk); araddr=9'h058; arvalid=1; rready=1;
        @(posedge clk); arvalid=0; while(!rvalid) @(posedge clk);
        if (rdata == 32'd100)
            $display("  PASS: POSITION[0] = %0d", rdata);
        else begin
            $display("  FAIL: POSITION[0] = %0d, expected 100", rdata);
            err_cnt = err_cnt + 1;
        end
        @(posedge clk); rready=0;

        // ──────────────────────────────────────────────────────────
        // Test 8: Read CASH_LO (addr 0x098)
        //   After a BUY fill, cash should be non-zero (negative cost)
        // ──────────────────────────────────────────────────────────
        $display("Test 8: CASH_LO after fill");
        @(posedge clk); araddr=9'h098; arvalid=1; rready=1;
        @(posedge clk); arvalid=0; while(!rvalid) @(posedge clk);
        if (rdata != 32'd0)
            $display("  PASS: CASH_LO = 0x%08h (non-zero)", rdata);
        else begin
            $display("  FAIL: CASH_LO = 0, expected non-zero after fill");
            err_cnt = err_cnt + 1;
        end
        @(posedge clk); rready=0;

        // ──────────────────────────────────────────────────────────
        // Test 9: Read STATUS (addr 0x040)
        //   Format: {25'b0, risk_halt, link_up, fsm_state[2:0], strategy[1:0]}
        //   Expect: link_up=1, strategy=MEAN_REV(0)
        // ──────────────────────────────────────────────────────────
        $display("Test 9: STATUS register bit fields");
        @(posedge clk); araddr=9'h040; arvalid=1; rready=1;
        @(posedge clk); arvalid=0; while(!rvalid) @(posedge clk);
        begin
            logic       stat_link_up;
            logic [1:0] stat_strategy;
            stat_link_up  = rdata[5];
            stat_strategy = rdata[1:0];
            if (stat_link_up && stat_strategy == 2'b00)
                $display("  PASS: link_up=1, strategy=MEAN_REV");
            else begin
                $display("  FAIL: STATUS=0x%08h (link_up=%b strat=%b)",
                         rdata, stat_link_up, stat_strategy);
                err_cnt = err_cnt + 1;
            end
        end
        @(posedge clk); rready=0;

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
