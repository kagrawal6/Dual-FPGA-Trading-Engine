`timescale 1ns / 1ps
import hft_pkg::*;

module tb_system_top();
    localparam LINK_W = LINK_DATA_W;
    logic clk = 0;
    logic rst_n;
    logic [3:0] btn_a;  logic [7:0] sw_a, led_a;  logic [2:0] rgb0_a, rgb1_a;
    logic [3:0] btn_b;  logic [7:0] sw_b, led_b;  logic [2:0] rgb0_b, rgb1_b;
    logic [LINK_W-1:0] pmod_a2b;  logic a2b_valid, a2b_ready;
    logic [LINK_W-1:0] pmod_b2a;  logic b2a_valid, b2a_ready;
    // Board A AXI
    logic [7:0]  awaddr_a, araddr_a;
    logic awvalid_a, arvalid_a, awready_a, arready_a;
    logic [31:0] wdata_a, rdata_a;  logic [3:0] wstrb_a;
    logic wvalid_a, wready_a, bvalid_a, bready_a, rvalid_a, rready_a;
    logic [1:0] bresp_a, rresp_a;
    // Board B AXI
    logic [8:0]  awaddr_b, araddr_b;
    logic awvalid_b, arvalid_b, awready_b, arready_b;
    logic [31:0] wdata_b, rdata_b;  logic [3:0] wstrb_b;
    logic wvalid_b, wready_b, bvalid_b, bready_b, rvalid_b, rready_b;
    logic [1:0] bresp_b, rresp_b;
    integer err_cnt = 0;
    logic [31:0] init_mids [4] = '{32'h00B40000, 32'h01A40000, 32'h03840000, 32'h00730000};
    logic [8:0]  bcfg_addr [7] = '{9'h004,9'h008,9'h00C,9'h010,9'h014,9'h018,9'h01C};
    logic [31:0] bcfg_data [7] = '{32'd0, 32'h100, 32'd6554, 32'd100, 32'd50000, 32'd10000, 32'd10_000_000};

    always #5 clk = ~clk;

    board_a_top #(.NUM_SYM(4), .LINK_W(LINK_W)) u_board_a (
        .clk(clk), .rst_n(rst_n),
        .btn(btn_a), .sw(sw_a), .led(led_a), .rgb0(rgb0_a), .rgb1(rgb1_a),
        .pmod_ja(pmod_a2b), .pmod_ja_valid(a2b_valid), .pmod_ja_ready(a2b_ready),
        .pmod_jb(pmod_b2a), .pmod_jb_valid(b2a_valid), .pmod_jb_ready(b2a_ready),
        .s_axi_awaddr(awaddr_a), .s_axi_awprot(3'b0),
        .s_axi_awvalid(awvalid_a), .s_axi_awready(awready_a),
        .s_axi_wdata(wdata_a), .s_axi_wstrb(wstrb_a),
        .s_axi_wvalid(wvalid_a), .s_axi_wready(wready_a),
        .s_axi_bresp(bresp_a), .s_axi_bvalid(bvalid_a), .s_axi_bready(bready_a),
        .s_axi_araddr(araddr_a), .s_axi_arprot(3'b0),
        .s_axi_arvalid(arvalid_a), .s_axi_arready(arready_a),
        .s_axi_rdata(rdata_a), .s_axi_rresp(rresp_a),
        .s_axi_rvalid(rvalid_a), .s_axi_rready(rready_a)
    );

    board_b_top #(.NUM_SYM(4), .LINK_W(LINK_W)) u_board_b (
        .clk(clk), .rst_n(rst_n),
        .btn(btn_b), .sw(sw_b), .led(led_b), .rgb0(rgb0_b), .rgb1(rgb1_b),
        .pmod_ja(pmod_a2b), .pmod_ja_valid(a2b_valid), .pmod_ja_ready(a2b_ready),
        .pmod_jb(pmod_b2a), .pmod_jb_valid(b2a_valid), .pmod_jb_ready(b2a_ready),
        .s_axi_awaddr(awaddr_b), .s_axi_awprot(3'b0),
        .s_axi_awvalid(awvalid_b), .s_axi_awready(awready_b),
        .s_axi_wdata(wdata_b), .s_axi_wstrb(wstrb_b),
        .s_axi_wvalid(wvalid_b), .s_axi_wready(wready_b),
        .s_axi_bresp(bresp_b), .s_axi_bvalid(bvalid_b), .s_axi_bready(bready_b),
        .s_axi_araddr(araddr_b), .s_axi_arprot(3'b0),
        .s_axi_arvalid(arvalid_b), .s_axi_arready(arready_b),
        .s_axi_rdata(rdata_b), .s_axi_rresp(rresp_b),
        .s_axi_rvalid(rvalid_b), .s_axi_rready(rready_b)
    );

    initial begin
        $display("=== tb_system_top ===");
        btn_a=0; sw_a=0; btn_b=0; sw_b=0;
        awaddr_a=0; awvalid_a=0; wdata_a=0; wstrb_a=0; wvalid_a=0; bready_a=0;
        araddr_a=0; arvalid_a=0; rready_a=0;
        awaddr_b=0; awvalid_b=0; wdata_b=0; wstrb_b=0; wvalid_b=0; bready_b=0;
        araddr_b=0; arvalid_b=0; rready_b=0;
        rst_n=0; #20; rst_n=1; @(posedge clk); repeat(5) @(posedge clk);

        // Configure Board A: init_mid[0..3]
        for (int i = 0; i < 4; i++) begin
            @(posedge clk); awaddr_a=8'h10+i*4; awvalid_a=1;
            wdata_a=init_mids[i]; wstrb_a=4'hF; wvalid_a=1; bready_a=1;
            @(posedge clk); awvalid_a=0; wvalid_a=0;
            while(!bvalid_a) @(posedge clk); bready_a=0;
        end
        // init_spread[0..3]
        for (int i = 0; i < 4; i++) begin
            @(posedge clk); awaddr_a=8'h50+i*4; awvalid_a=1;
            wdata_a=32'h00001000; wstrb_a=4'hF; wvalid_a=1; bready_a=1;
            @(posedge clk); awvalid_a=0; wvalid_a=0;
            while(!bvalid_a) @(posedge clk); bready_a=0;
        end
        // quote_interval=200, active_sym_count=4
        @(posedge clk); awaddr_a=8'h04; awvalid_a=1; wdata_a=32'd200; wstrb_a=4'hF; wvalid_a=1; bready_a=1;
        @(posedge clk); awvalid_a=0; wvalid_a=0; while(!bvalid_a) @(posedge clk); bready_a=0;
        @(posedge clk); awaddr_a=8'hF0; awvalid_a=1; wdata_a=32'd4; wstrb_a=4'hF; wvalid_a=1; bready_a=1;
        @(posedge clk); awvalid_a=0; wvalid_a=0; while(!bvalid_a) @(posedge clk); bready_a=0;

        // Configure Board B: strategy, threshold, alpha, qty, max_pos, max_rate, max_loss
        for (int i = 0; i < 7; i++) begin
            @(posedge clk); awaddr_b=bcfg_addr[i]; awvalid_b=1;
            wdata_b=bcfg_data[i]; wstrb_b=4'hF; wvalid_b=1; bready_b=1;
            @(posedge clk); awvalid_b=0; wvalid_b=0;
            while(!bvalid_b) @(posedge clk); bready_b=0;
        end

        // Test 1: Start Board A
        $display("Test 1: Start Board A");
        @(posedge clk); awaddr_a=8'h00; awvalid_a=1; wdata_a=32'h1; wstrb_a=4'hF; wvalid_a=1; bready_a=1;
        @(posedge clk); awvalid_a=0; wvalid_a=0; while(!bvalid_a) @(posedge clk); bready_a=0;
        repeat(3) @(posedge clk); #1;
        if (u_board_a.running) $display("  PASS: Board A running");
        else begin $display("  FAIL: Board A not running"); err_cnt=err_cnt+1; end

        // Test 2: Wait for Board B link_up
        $display("Test 2: Board B link_up");
        begin
            integer w = 0;
            while (!u_board_b.link_up && w < 5000) begin @(posedge clk); w=w+1; end
            if (u_board_b.link_up) $display("  PASS: link_up after %0d cycles", w);
            else begin $display("  FAIL: no link_up"); err_cnt=err_cnt+1; end
        end

        // Test 3: Start Board B -> ARMED -> TRADING
        $display("Test 3: Board B -> TRADING");
        sw_b = 8'h01;
        @(posedge clk); awaddr_b=9'h000; awvalid_b=1; wdata_b=32'h1; wstrb_b=4'hF; wvalid_b=1; bready_b=1;
        @(posedge clk); awvalid_b=0; wvalid_b=0; while(!bvalid_b) @(posedge clk); bready_b=0;
        repeat(3) @(posedge clk);
        @(posedge clk); awaddr_b=9'h000; awvalid_b=1; wdata_b=32'h1; wstrb_b=4'hF; wvalid_b=1; bready_b=1;
        @(posedge clk); awvalid_b=0; wvalid_b=0; while(!bvalid_b) @(posedge clk); bready_b=0;
        repeat(3) @(posedge clk); #1;
        if (u_board_b.fsm_state == B_TRADING) $display("  PASS: Board B TRADING");
        else begin $display("  FAIL: Board B state=%0d", u_board_b.fsm_state); err_cnt=err_cnt+1; end

        // Run for 10k cycles
        $display("Running system for 10000 cycles...");
        repeat(10000) @(posedge clk);

        // Test 4: Board B received quotes
        $display("Test 4: Board B quotes_rcvd > 0");
        @(posedge clk); araddr_b=9'h044; arvalid_b=1; rready_b=1;
        @(posedge clk); arvalid_b=0; while(!rvalid_b) @(posedge clk);
        $display("  quotes_rcvd = %0d", rdata_b);
        if (rdata_b > 0) $display("  PASS: quotes flowing A -> B");
        else begin $display("  FAIL: no quotes received"); err_cnt=err_cnt+1; end
        @(posedge clk); rready_b=0;

        // Test 5: No link errors
        $display("Test 5: No link errors");
        @(posedge clk); araddr_b=9'h054; arvalid_b=1; rready_b=1;
        @(posedge clk); arvalid_b=0; while(!rvalid_b) @(posedge clk);
        if (rdata_b == 0) $display("  PASS: link_errors = 0");
        else begin $display("  FAIL: link_errors = %0d", rdata_b); err_cnt=err_cnt+1; end
        @(posedge clk); rready_b=0;

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end
endmodule
