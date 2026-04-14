`timescale 1ns / 1ps

module tb_board_a_top();
    import hft_pkg::*;

    localparam NUM_SYM = 4;

    logic        clk, rst_n;
    logic [3:0]  btn;
    logic [7:0]  sw;
    logic [7:0]  led;
    logic [2:0]  rgb0, rgb1;
    logic [3:0]  pmod_ja;
    logic        pmod_ja_valid, pmod_ja_ready;
    logic [3:0]  pmod_jb;
    logic        pmod_jb_valid, pmod_jb_ready;

    // AXI-Lite signals
    logic [7:0]  s_axi_awaddr;
    logic        s_axi_awvalid, s_axi_awready;
    logic [31:0] s_axi_wdata;
    logic [3:0]  s_axi_wstrb;
    logic        s_axi_wvalid, s_axi_wready;
    logic [1:0]  s_axi_bresp;
    logic        s_axi_bvalid, s_axi_bready;
    logic [7:0]  s_axi_araddr;
    logic        s_axi_arvalid, s_axi_arready;
    logic [31:0] s_axi_rdata;
    logic [1:0]  s_axi_rresp;
    logic        s_axi_rvalid, s_axi_rready;

    integer err_cnt = 0;
    logic [31:0] read_data;
    always #5 clk = ~clk;

    board_a_top #(.NUM_SYM(NUM_SYM)) dut (
        .clk(clk), .rst_n(rst_n),
        .btn(btn), .sw(sw), .led(led), .rgb0(rgb0), .rgb1(rgb1),
        .pmod_ja(pmod_ja), .pmod_ja_valid(pmod_ja_valid), .pmod_ja_ready(pmod_ja_ready),
        .pmod_jb(pmod_jb), .pmod_jb_valid(pmod_jb_valid), .pmod_jb_ready(pmod_jb_ready),
        .s_axi_awaddr(s_axi_awaddr), .s_axi_awprot(3'b0),
        .s_axi_awvalid(s_axi_awvalid), .s_axi_awready(s_axi_awready),
        .s_axi_wdata(s_axi_wdata), .s_axi_wstrb(s_axi_wstrb),
        .s_axi_wvalid(s_axi_wvalid), .s_axi_wready(s_axi_wready),
        .s_axi_bresp(s_axi_bresp), .s_axi_bvalid(s_axi_bvalid), .s_axi_bready(s_axi_bready),
        .s_axi_araddr(s_axi_araddr), .s_axi_arprot(3'b0),
        .s_axi_arvalid(s_axi_arvalid), .s_axi_arready(s_axi_arready),
        .s_axi_rdata(s_axi_rdata), .s_axi_rresp(s_axi_rresp),
        .s_axi_rvalid(s_axi_rvalid), .s_axi_rready(s_axi_rready)
    );

    initial begin
        clk = 0; rst_n = 0;
        btn = 4'b0; sw = 8'b0;
        pmod_ja_ready = 1; pmod_jb = 4'b0; pmod_jb_valid = 0;
        s_axi_awaddr = 0; s_axi_awvalid = 0;
        s_axi_wdata = 0; s_axi_wstrb = 4'hF; s_axi_wvalid = 0;
        s_axi_bready = 1;
        s_axi_araddr = 0; s_axi_arvalid = 0; s_axi_rready = 1;

        #20; rst_n = 1;
        repeat(3) @(posedge clk);

        // AXI writes: configure before start
        // Write LFSR_SEED = 0xDEADBEEF (addr 0x08)
        s_axi_awaddr = 8'h08; s_axi_awvalid = 1;
        s_axi_wdata = 32'hDEAD_BEEF; s_axi_wvalid = 1;
        @(posedge clk); s_axi_awvalid = 0; s_axi_wvalid = 0;
        @(posedge clk);

        // Write QUOTE_INTERVAL = 0 (addr 0x04)
        s_axi_awaddr = 8'h04; s_axi_awvalid = 1;
        s_axi_wdata = 32'd0; s_axi_wvalid = 1;
        @(posedge clk); s_axi_awvalid = 0; s_axi_wvalid = 0;
        @(posedge clk);

        // Write REGIME = CALM (addr 0x0C)
        s_axi_awaddr = 8'h0C; s_axi_awvalid = 1;
        s_axi_wdata = 32'd0; s_axi_wvalid = 1;
        @(posedge clk); s_axi_awvalid = 0; s_axi_wvalid = 0;
        @(posedge clk);

        // Write ACTIVE_CNT = 4 (addr 0xF0)
        s_axi_awaddr = 8'hF0; s_axi_awvalid = 1;
        s_axi_wdata = 32'd4; s_axi_wvalid = 1;
        @(posedge clk); s_axi_awvalid = 0; s_axi_wvalid = 0;
        @(posedge clk);

        // Write INIT_MID[0] = $180 Q16.16 (addr 0x10)
        s_axi_awaddr = 8'h10; s_axi_awvalid = 1;
        s_axi_wdata = 32'h00B4_0000; s_axi_wvalid = 1;
        @(posedge clk); s_axi_awvalid = 0; s_axi_wvalid = 0;
        @(posedge clk);

        // Test 1: write CTRL[0]=1 to start
        s_axi_awaddr = 8'h00; s_axi_awvalid = 1;
        s_axi_wdata = 32'h0000_0001; s_axi_wvalid = 1;
        @(posedge clk); s_axi_awvalid = 0; s_axi_wvalid = 0;
        @(posedge clk);

        // Test 2: check led[2] = running
        repeat(5) @(posedge clk); #1;
        if (led[2] !== 1'b1) begin
            $display("FAIL: led[2]=%b, expected 1 (running)", led[2]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: led[2]=1, FSM is RUNNING");

        // Test 3: wait for link TX activity (quotes)
        repeat(50) @(posedge clk);
        @(posedge clk); #1;
        if (pmod_ja_valid !== 1'b1) begin
            $display("FAIL: pmod_ja_valid=%b, expected 1", pmod_ja_valid);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: quotes appearing on link TX");

        // Test 4: read STATUS register (addr 0xF4)
        s_axi_araddr = 8'hF4; s_axi_arvalid = 1;
        @(posedge clk); #1;
        s_axi_arvalid = 0;
        read_data = s_axi_rdata;
        @(posedge clk);

        if (read_data[0] !== 1'b1) begin
            $display("FAIL: STATUS.running=%b, expected 1", read_data[0]);
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: STATUS register shows running=1");

        // Test 5: read QUOTES_SENT (addr 0xF8), should be >0
        s_axi_araddr = 8'hF8; s_axi_arvalid = 1;
        @(posedge clk); #1;
        s_axi_arvalid = 0;
        read_data = s_axi_rdata;
        @(posedge clk);

        if (read_data == 32'd0) begin
            $display("FAIL: quotes_sent=0, expected >0");
            err_cnt = err_cnt + 1;
        end else
            $display("PASS: quotes_sent=%0d", read_data);

        // ──────────────────────────────────────────────────────────
        // Phase 6: Read ORDERS_RCVD (0xFC)
        //   No Board B connected, so should be 0
        // ──────────────────────────────────────────────────────────
        $display("Phase 6: ORDERS_RCVD with no Board B");
        s_axi_araddr = 8'hFC; s_axi_arvalid = 1;
        @(posedge clk); #1;
        s_axi_arvalid = 0;
        read_data = s_axi_rdata;
        @(posedge clk);

        if (read_data == 32'd0) begin
            $display("  PASS: orders_rcvd = 0 (no Board B connected)");
        end else begin
            $display("  FAIL: orders_rcvd = %0d, expected 0", read_data);
            err_cnt = err_cnt + 1;
        end

        // ──────────────────────────────────────────────────────────
        // Phase 7: Regime change — write REGIME=VOLATILE (0x0C = 1)
        //   Verify quotes still flowing after regime switch
        // ──────────────────────────────────────────────────────────
        $display("Phase 7: Regime change to VOLATILE");
        s_axi_awaddr = 8'h0C; s_axi_awvalid = 1;
        s_axi_wdata = 32'd1; s_axi_wvalid = 1;
        @(posedge clk); s_axi_awvalid = 0; s_axi_wvalid = 0;
        @(posedge clk);
        repeat (50) @(posedge clk); #1;

        if (pmod_ja_valid === 1'b1)
            $display("  PASS: quotes still flowing after regime change");
        else begin
            $display("  FAIL: pmod_ja_valid=%b, expected quotes flowing", pmod_ja_valid);
            err_cnt = err_cnt + 1;
        end

        // ──────────────────────────────────────────────────────────
        // Phase 8: Stop via AXI — write CTRL=2 (reset/stop)
        //   led[2] should go to 0 (not running)
        // ──────────────────────────────────────────────────────────
        $display("Phase 8: Stop via AXI (CTRL=2)");
        s_axi_awaddr = 8'h00; s_axi_awvalid = 1;
        s_axi_wdata = 32'h0000_0002; s_axi_wvalid = 1;
        @(posedge clk); s_axi_awvalid = 0; s_axi_wvalid = 0;
        repeat (5) @(posedge clk); #1;

        if (led[2] === 1'b0)
            $display("  PASS: led[2]=0, FSM stopped");
        else begin
            $display("  FAIL: led[2]=%b, expected 0 after stop", led[2]);
            err_cnt = err_cnt + 1;
        end

        // ──────────────────────────────────────────────────────────
        // Phase 9: Restart — write CTRL=1 (start)
        //   led[2] goes back to 1, more quotes generated
        // ──────────────────────────────────────────────────────────
        $display("Phase 9: Restart (CTRL=1)");
        // Capture current quotes_sent before restart
        s_axi_araddr = 8'hF8; s_axi_arvalid = 1;
        @(posedge clk); #1;
        s_axi_arvalid = 0;
        read_data = s_axi_rdata;
        @(posedge clk);
        begin
            logic [31:0] quotes_before;
            quotes_before = read_data;

            s_axi_awaddr = 8'h00; s_axi_awvalid = 1;
            s_axi_wdata = 32'h0000_0001; s_axi_wvalid = 1;
            @(posedge clk); s_axi_awvalid = 0; s_axi_wvalid = 0;
            repeat (5) @(posedge clk); #1;

            if (led[2] !== 1'b1) begin
                $display("  FAIL: led[2]=%b, expected 1 after restart", led[2]);
                err_cnt = err_cnt + 1;
            end else
                $display("  PASS: led[2]=1, FSM restarted");

            repeat (50) @(posedge clk);
            s_axi_araddr = 8'hF8; s_axi_arvalid = 1;
            @(posedge clk); #1;
            s_axi_arvalid = 0;
            read_data = s_axi_rdata;
            @(posedge clk);

            if (read_data > quotes_before)
                $display("  PASS: quotes_sent increased %0d -> %0d",
                         quotes_before, read_data);
            else begin
                $display("  FAIL: quotes_sent=%0d, was %0d (no new quotes)",
                         read_data, quotes_before);
                err_cnt = err_cnt + 1;
            end
        end

        // Summary
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end

endmodule
