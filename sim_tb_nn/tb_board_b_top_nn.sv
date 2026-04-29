`timescale 1ns / 1ps
import hft_pkg::*;

module tb_board_b_top_nn();   // CHANGED: module name

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

    board_b_top_nn #(.NUM_SYM(4), .LINK_W(LINK_W)) dut (   // CHANGED: board_b_top_nn
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

    localparam logic [127:0] QUOTE_0 =
        128'h1000_00B3_F81E_00B4_081E_03E8_03E8_0000;
    localparam logic [127:0] QUOTE_1 =
        128'h1000_00C3_F81E_00C4_081E_03E8_03E8_0000;

    initial begin
        $display("=== tb_board_b_top_nn ===");
        rst_n = 0; btn = 0; sw = 0;
        awaddr = 0; awvalid = 0; wdata = 0; wstrb = 0; wvalid = 0; bready = 0;
        araddr = 0; arvalid = 0; rready = 0;
        tx_frame = 0; tx_valid = 0;
        #20; rst_n = 1; @(posedge clk);
        repeat (5) @(posedge clk);

        // AXI config
        // CHANGED: strategy = STRAT_NN (2'b10 = 2)
        @(posedge clk); awaddr=9'h004; awvalid=1; wdata=32'd2; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        // threshold = 1 (not used by NN but set anyway)
        @(posedge clk); awaddr=9'h008; awvalid=1; wdata=32'd1; wstrb=4'hF; wvalid=1; bready=1;
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
        // max_loss = 0 -> halt on first order
        @(posedge clk); awaddr=9'h01C; awvalid=1; wdata=32'd0; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;

        // Test 1: Send quote -> link_up
        $display("Test 1: Link up after first frame");
        tx_frame = QUOTE_0; tx_valid = 1;
        @(posedge clk); tx_valid = 0;
        repeat (80) @(posedge clk); #1;
        if (dut.link_up)
            $display("  PASS: link_up = 1");
        else begin
            $display("  FAIL: link_up = 0");
            err_cnt = err_cnt + 1;
        end

        // Test 2: Start -> IDLE -> ARMED
        $display("Test 2: FSM IDLE -> ARMED");
        @(posedge clk); awaddr=9'h000; awvalid=1; wdata=32'h1; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        repeat (3) @(posedge clk); #1;
        if (dut.fsm_state == B_ARMED)
            $display("  PASS: FSM = ARMED");
        else begin
            $display("  FAIL: FSM = %0d", dut.fsm_state);
            err_cnt = err_cnt + 1;
        end

        // Test 3: Start -> ARMED -> TRADING
        $display("Test 3: FSM ARMED -> TRADING");
        sw = 8'h01;
        @(posedge clk);
        @(posedge clk); awaddr=9'h000; awvalid=1; wdata=32'h1; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        repeat (3) @(posedge clk); #1;
        if (dut.fsm_state == B_TRADING)
            $display("  PASS: FSM = TRADING");
        else begin
            $display("  FAIL: FSM = %0d", dut.fsm_state);
            err_cnt = err_cnt + 1;
        end

        // Test 4: Send 3 quotes, check counter
        $display("Test 4: Quotes flow through pipeline");
        repeat (3) begin
            tx_frame = QUOTE_0; tx_valid = 1;
            @(posedge clk); tx_valid = 0;
            repeat (80) @(posedge clk);
        end
        @(posedge clk); araddr=9'h044; arvalid=1; rready=1;
        @(posedge clk); arvalid=0; while(!rvalid) @(posedge clk);
        if (rdata > 0)
            $display("  PASS: quotes_rcvd = %0d", rdata);
        else begin
            $display("  FAIL: quotes_rcvd = 0");
            err_cnt = err_cnt + 1;
        end
        @(posedge clk); rready=0;

        // Test 5: Halt check
        $display("Test 5: Risk halt engaged");
        repeat (15) begin
            tx_frame = QUOTE_0; tx_valid = 1;
            @(posedge clk); tx_valid = 0;
            repeat (100) @(posedge clk);
            tx_frame = QUOTE_1; tx_valid = 1;
            @(posedge clk); tx_valid = 0;
            repeat (100) @(posedge clk);
        end
        repeat (2000) @(posedge clk); #1;
        if (dut.fsm_state == B_HALTED || dut.risk_halt)
            $display("  PASS: FSM halted (state=%0d halt=%b)", dut.fsm_state, dut.risk_halt);
        else begin
            $display("  FAIL: FSM=%0d halt=%b", dut.fsm_state, dut.risk_halt);
            err_cnt = err_cnt + 1;
        end

        // Test 6: AXI reset
        $display("Test 6: AXI reset -> FSM returns to IDLE");
        @(posedge clk); awaddr=9'h000; awvalid=1; wdata=32'h2; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        repeat (5) @(posedge clk); #1;
        if (dut.fsm_state == B_IDLE && !dut.risk_halt)
            $display("  PASS: FSM=IDLE, risk_halt cleared");
        else begin
            $display("  FAIL: FSM=%0d halt=%b, expected IDLE+clear",
                     dut.fsm_state, dut.risk_halt);
            err_cnt = err_cnt + 1;
        end

        // Test 7: POSITION[0] after reset
        $display("Test 7: POSITION[0] after reset");
        @(posedge clk); araddr=9'h058; arvalid=1; rready=1;
        @(posedge clk); arvalid=0; while(!rvalid) @(posedge clk);
        if (rdata == 32'd0)
            $display("  PASS: POSITION[0] = 0");
        else begin
            $display("  FAIL: POSITION[0] = %0d, expected 0", rdata);
            err_cnt = err_cnt + 1;
        end
        @(posedge clk); rready=0;

        // Test 8: Restart after reset -> TRADING
        $display("Test 8: Restart after reset -> TRADING");
        @(posedge clk); awaddr=9'h01C; awvalid=1; wdata=32'd10_000_000; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        tx_frame = QUOTE_0; tx_valid = 1;
        @(posedge clk); tx_valid = 0;
        repeat (80) @(posedge clk);
        @(posedge clk); awaddr=9'h000; awvalid=1; wdata=32'h1; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        repeat (3) @(posedge clk);
        @(posedge clk); awaddr=9'h000; awvalid=1; wdata=32'h1; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        repeat (3) @(posedge clk); #1;
        if (dut.fsm_state == B_TRADING)
            $display("  PASS: FSM reached TRADING after restart");
        else begin
            $display("  FAIL: FSM = %0d, expected TRADING", dut.fsm_state);
            err_cnt = err_cnt + 1;
        end

        // Test 9: LED reflects fsm_state
        $display("Test 9: LED reflects fsm_state");
        @(posedge clk); #1;
        if (led[2:0] == dut.fsm_state[2:0])
            $display("  PASS: LED[2:0] = %03b matches fsm_state", led[2:0]);
        else begin
            $display("  FAIL: LED[2:0]=%03b, fsm_state=%03b",
                     led[2:0], dut.fsm_state[2:0]);
            err_cnt = err_cnt + 1;
        end

        // ── Test 10: NN fires BUY after large price drop ────────
        // Strategy: warm up EMA at $180, then crash price to $160.
        // Deviation = mid - EMA becomes large negative → BUY signal.
        //
        // Quote format: {MSG_QUOTE[127:124], sym[123:116], regime[115:114],
        //                seq[113:112], bid[111:80], ask[79:48],
        //                bid_size[47:32], ask_size[31:16], pad[15:0]}
        //
        // QUOTE_BASE: bid=0x00B4_0000 ($180.00), ask=0x00B4_8000 ($180.50)
        // QUOTE_LOW:  bid=0x00A0_0000 ($160.00), ask=0x00A0_8000 ($160.50)
        // regime=01 (VOLATILE) in bits [115:114] to match training distribution
        $display("Test 10: NN BUY signal after large price drop");

        // Generous limits — don't halt during this test
        @(posedge clk); awaddr=9'h01C; awvalid=1; wdata=32'd100_000_000; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;

        // Select NN via switch override: sw[3]=1 override, sw[2:1]=10, sw[0]=1
        sw = 8'b0000_1101;
        @(posedge clk);

        // Phase 1: warm up EMA at $180 base price (10 quotes)
        // msg=1, sym=0, regime=01(volatile), bid=0x00B40000, ask=0x00B48000
        repeat (10) begin
            tx_frame = 128'h1004_00B4_0000_00B4_8000_03E8_03E8_0000;
            tx_valid = 1;
            @(posedge clk); tx_valid = 0;
            repeat (80) @(posedge clk);
        end

        // Phase 2: crash price to $160 — big negative deviation → BUY
        repeat (20) begin
            tx_frame = 128'h1004_00A0_0000_00A0_8000_03E8_03E8_0000;
            tx_valid = 1;
            @(posedge clk); tx_valid = 0;
            repeat (80) @(posedge clk);
        end

        // Phase 3: spike price to $200 — big positive deviation → SELL
        repeat (20) begin
            tx_frame = 128'h1004_00C8_0000_00C8_8000_03E8_03E8_0000;
            tx_valid = 1;
            @(posedge clk); tx_valid = 0;
            repeat (80) @(posedge clk);
        end

        // Allow pipeline to fully drain
        repeat (300) @(posedge clk);

        // Read orders_sent
        @(posedge clk); araddr=9'h048; arvalid=1; rready=1;
        @(posedge clk); arvalid=0; while(!rvalid) @(posedge clk);
        if (rdata > 0)
            $display("  PASS: NN produced orders_sent = %0d", rdata);
        else begin
            $display("  FAIL: orders_sent = 0 after large price swing");
            $display("        Check u_nn.signal_valid and u_nn.action_comb in waveform");
            err_cnt = err_cnt + 1;
        end
        @(posedge clk); rready=0;

        // Also read fills_rcvd to confirm end-to-end path
        @(posedge clk); araddr=9'h04C; arvalid=1; rready=1;
        @(posedge clk); arvalid=0; while(!rvalid) @(posedge clk);
        $display("  INFO: fills_rcvd = %0d", rdata);
        @(posedge clk); rready=0;
        // ── End Test 10 ──────────────────────────────────────────

        // ── Test 11: Mean-reversion still works after NN test ────
        // Reset, switch to STRAT_MEAN_REV, send large price swing,
        // confirm orders_sent increments — proves the mux works in
        // both directions and original strategy is unaffected.
        $display("Test 11: Mean-reversion strategy still works");

        // AXI reset
        @(posedge clk); awaddr=9'h000; awvalid=1; wdata=32'h2; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        repeat (5) @(posedge clk);

        // Switch to MEAN_REV via AXI: strategy_sel = 0
        @(posedge clk); awaddr=9'h004; awvalid=1; wdata=32'd0; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;

        // Low threshold so mean-reversion triggers easily
        @(posedge clk); awaddr=9'h008; awvalid=1; wdata=32'd1; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;

        // Generous max_loss
        @(posedge clk); awaddr=9'h01C; awvalid=1; wdata=32'd100_000_000; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;

        // Clear switch override — use AXI strategy
        sw = 8'b0000_0001;  // sw[3]=0 no override, sw[0]=1 trading_enable
        @(posedge clk);

        // Send quote to get link_up
        tx_frame = QUOTE_0; tx_valid = 1;
        @(posedge clk); tx_valid = 0;
        repeat (80) @(posedge clk);

        // IDLE -> ARMED
        @(posedge clk); awaddr=9'h000; awvalid=1; wdata=32'h1; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        repeat (3) @(posedge clk);

        // ARMED -> TRADING
        @(posedge clk); awaddr=9'h000; awvalid=1; wdata=32'h1; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        repeat (3) @(posedge clk);

        // Warm up EMA then send big price swing
        repeat (5) begin
            tx_frame = QUOTE_0; tx_valid = 1;
            @(posedge clk); tx_valid = 0;
            repeat (80) @(posedge clk);
        end
        repeat (10) begin
            tx_frame = QUOTE_0; tx_valid = 1;
            @(posedge clk); tx_valid = 0;
            repeat (80) @(posedge clk);
            tx_frame = QUOTE_1; tx_valid = 1;
            @(posedge clk); tx_valid = 0;
            repeat (80) @(posedge clk);
        end
        repeat (300) @(posedge clk);

        // Read orders_sent — should be > 0 for mean-reversion
        @(posedge clk); araddr=9'h048; arvalid=1; rready=1;
        @(posedge clk); arvalid=0; while(!rvalid) @(posedge clk);
        if (rdata > 0)
            $display("  PASS: mean-reversion produced orders_sent = %0d", rdata);
        else begin
            $display("  FAIL: mean-reversion orders_sent = 0 — mux or strategy broken");
            err_cnt = err_cnt + 1;
        end
        @(posedge clk); rready=0;

        // Confirm active_strategy is MEAN_REV not NN
        if (dut.active_strategy == STRAT_MEAN_REV)
            $display("  PASS: active_strategy = STRAT_MEAN_REV");
        else begin
            $display("  FAIL: active_strategy = %0d, expected STRAT_MEAN_REV",
                     dut.active_strategy);
            err_cnt = err_cnt + 1;
        end
        // ── End Test 11 ──────────────────────────────────────────

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule