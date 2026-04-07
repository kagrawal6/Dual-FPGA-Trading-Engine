`timescale 1ns / 1ps
import hft_pkg::*;

module tb_board_b_top();

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

    localparam logic [127:0] QUOTE_0 =
        128'h1000_00B3_F81E_00B4_081E_03E8_03E8_0000;

    initial begin
        $display("=== tb_board_b_top ===");
        rst_n = 0; btn = 0; sw = 0;
        awaddr = 0; awvalid = 0; wdata = 0; wstrb = 0; wvalid = 0; bready = 0;
        araddr = 0; arvalid = 0; rready = 0;
        tx_frame = 0; tx_valid = 0;
        #20; rst_n = 1; @(posedge clk);
        repeat (5) @(posedge clk);

        // AXI config
        // strategy = MEAN_REV
        @(posedge clk); awaddr=9'h004; awvalid=1; wdata=32'd0; wstrb=4'hF; wvalid=1; bready=1;
        @(posedge clk); awvalid=0; wvalid=0; while(!bvalid) @(posedge clk); bready=0;
        // threshold = $0.004 (tiny -> always triggers)
        @(posedge clk); awaddr=9'h008; awvalid=1; wdata=32'h100; wstrb=4'hF; wvalid=1; bready=1;
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
        // max_loss = 0 -> halt on first strategy signal
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

        // Test 5: Halt check (max_loss=0 -> halt after first signal)
        $display("Test 5: Risk halt engaged");
        repeat (20) @(posedge clk); #1;
        if (dut.fsm_state == B_HALTED || dut.risk_halt)
            $display("  PASS: FSM halted (state=%0d halt=%b)", dut.fsm_state, dut.risk_halt);
        else begin
            $display("  FAIL: FSM=%0d halt=%b", dut.fsm_state, dut.risk_halt);
            err_cnt = err_cnt + 1;
        end

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
