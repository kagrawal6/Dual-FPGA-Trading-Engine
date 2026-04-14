`timescale 1ns / 1ps
import hft_pkg::*;

module tb_board_b_axi_regs();
    logic        clk = 0;
    logic        rst_n;
    logic [8:0]  s_axi_awaddr;  logic [2:0] s_axi_awprot;
    logic        s_axi_awvalid, s_axi_awready;
    logic [31:0] s_axi_wdata;   logic [3:0] s_axi_wstrb;
    logic        s_axi_wvalid,  s_axi_wready;
    logic [1:0]  s_axi_bresp;   logic s_axi_bvalid, s_axi_bready;
    logic [8:0]  s_axi_araddr;  logic [2:0] s_axi_arprot;
    logic        s_axi_arvalid, s_axi_arready;
    logic [31:0] s_axi_rdata;   logic [1:0] s_axi_rresp;
    logic        s_axi_rvalid,  s_axi_rready;

    logic        axi_start_pulse, axi_reset_pulse;
    strategy_e   strategy_sel;    price_t threshold;
    logic [ALPHA_W-1:0] ema_alpha;  qty_t base_qty;
    logic [POSITION_W-1:0] max_position;
    logic [COUNTER_W-1:0]  max_order_rate;  price_t max_loss;

    b_state_e    fsm_state    = B_IDLE;
    logic        link_up      = 1;
    logic        risk_halt    = 0;
    strategy_e   active_strat = STRAT_MEAN_REV;
    logic [COUNTER_W-1:0] quotes_in=42, orders_in=10, fills_in=5;
    logic [COUNTER_W-1:0] rejects_in=2, lerrors_in=0;
    position_t   pos_in [NUM_SYMBOLS];
    cash_t       cash_in = 0;
    logic [HIST_BIN_W-1:0] hbins_in [HIST_BINS];
    logic [COUNTER_W-1:0] lmin_in=100, lmax_in=200, lsum_in=300, lcnt_in=3;
    integer err_cnt = 0;

    always #5 clk = ~clk;

    board_b_axi_regs dut (
        .clk(clk), .rst_n(rst_n),
        .s_axi_awaddr(s_axi_awaddr), .s_axi_awprot(s_axi_awprot),
        .s_axi_awvalid(s_axi_awvalid), .s_axi_awready(s_axi_awready),
        .s_axi_wdata(s_axi_wdata), .s_axi_wstrb(s_axi_wstrb),
        .s_axi_wvalid(s_axi_wvalid), .s_axi_wready(s_axi_wready),
        .s_axi_bresp(s_axi_bresp), .s_axi_bvalid(s_axi_bvalid),
        .s_axi_bready(s_axi_bready),
        .s_axi_araddr(s_axi_araddr), .s_axi_arprot(s_axi_arprot),
        .s_axi_arvalid(s_axi_arvalid), .s_axi_arready(s_axi_arready),
        .s_axi_rdata(s_axi_rdata), .s_axi_rresp(s_axi_rresp),
        .s_axi_rvalid(s_axi_rvalid), .s_axi_rready(s_axi_rready),
        .axi_start_pulse(axi_start_pulse), .axi_reset_pulse(axi_reset_pulse),
        .strategy_sel(strategy_sel), .threshold(threshold),
        .ema_alpha(ema_alpha), .base_qty(base_qty),
        .max_position(max_position), .max_order_rate(max_order_rate),
        .max_loss(max_loss),
        .fsm_state(fsm_state), .link_up(link_up), .risk_halt(risk_halt),
        .active_strategy(active_strat),
        .quotes_rcvd(quotes_in), .orders_sent(orders_in),
        .fills_rcvd(fills_in), .risk_rejects(rejects_in),
        .link_errors(lerrors_in),
        .position(pos_in), .cash(cash_in),
        .hist_bins(hbins_in), .lat_min(lmin_in), .lat_max(lmax_in),
        .lat_sum(lsum_in), .lat_count(lcnt_in)
    );

    initial begin
        for (int i = 0; i < NUM_SYMBOLS; i++) pos_in[i] = 0;
        for (int i = 0; i < HIST_BINS; i++) hbins_in[i] = 0;
        $display("=== tb_board_b_axi_regs ===");
        rst_n = 0;
        s_axi_awaddr=0; s_axi_awprot=0; s_axi_awvalid=0;
        s_axi_wdata=0; s_axi_wstrb=0; s_axi_wvalid=0; s_axi_bready=0;
        s_axi_araddr=0; s_axi_arprot=0; s_axi_arvalid=0; s_axi_rready=0;
        #20; rst_n = 1; @(posedge clk);

        // Test 1: Write & readback STRATEGY_SEL (0x004)
        $display("Test 1: Write+readback STRATEGY_SEL");
        @(posedge clk);
        s_axi_awaddr=9'h004; s_axi_awvalid=1; s_axi_wdata=32'd0;
        s_axi_wstrb=4'hF; s_axi_wvalid=1; s_axi_bready=1;
        @(posedge clk); s_axi_awvalid=0; s_axi_wvalid=0;
        while (!s_axi_bvalid) @(posedge clk);
        @(posedge clk); s_axi_bready=0;
        @(posedge clk);
        s_axi_araddr=9'h004; s_axi_arvalid=1; s_axi_rready=1;
        @(posedge clk); s_axi_arvalid=0;
        while (!s_axi_rvalid) @(posedge clk);
        if (s_axi_rdata[1:0] == 2'b00) $display("  PASS: strategy = MEAN_REV");
        else begin $display("  FAIL: strategy = %b", s_axi_rdata[1:0]); err_cnt = err_cnt+1; end
        @(posedge clk); s_axi_rready=0;

        // Test 2: Write & readback THRESHOLD (0x008)
        $display("Test 2: Write+readback THRESHOLD");
        @(posedge clk);
        s_axi_awaddr=9'h008; s_axi_awvalid=1; s_axi_wdata=32'h0000_8000;
        s_axi_wstrb=4'hF; s_axi_wvalid=1; s_axi_bready=1;
        @(posedge clk); s_axi_awvalid=0; s_axi_wvalid=0;
        while (!s_axi_bvalid) @(posedge clk);
        @(posedge clk); s_axi_bready=0;
        @(posedge clk);
        s_axi_araddr=9'h008; s_axi_arvalid=1; s_axi_rready=1;
        @(posedge clk); s_axi_arvalid=0;
        while (!s_axi_rvalid) @(posedge clk);
        if (s_axi_rdata == 32'h0000_8000) $display("  PASS: threshold = 0x%08X", s_axi_rdata);
        else begin $display("  FAIL: threshold = 0x%08X", s_axi_rdata); err_cnt = err_cnt+1; end
        @(posedge clk); s_axi_rready=0;

        // Test 3: Write & readback BASE_QTY (0x010)
        $display("Test 3: Write+readback BASE_QTY");
        @(posedge clk);
        s_axi_awaddr=9'h010; s_axi_awvalid=1; s_axi_wdata=32'd200;
        s_axi_wstrb=4'hF; s_axi_wvalid=1; s_axi_bready=1;
        @(posedge clk); s_axi_awvalid=0; s_axi_wvalid=0;
        while (!s_axi_bvalid) @(posedge clk);
        @(posedge clk); s_axi_bready=0;
        @(posedge clk);
        s_axi_araddr=9'h010; s_axi_arvalid=1; s_axi_rready=1;
        @(posedge clk); s_axi_arvalid=0;
        while (!s_axi_rvalid) @(posedge clk);
        if (s_axi_rdata[15:0] == 16'd200) $display("  PASS: base_qty = %0d", s_axi_rdata[15:0]);
        else begin $display("  FAIL: base_qty = %0d", s_axi_rdata[15:0]); err_cnt = err_cnt+1; end
        @(posedge clk); s_axi_rready=0;

        // Test 4: Read STATUS (0x040) - expect {risk_halt=0,link_up=1,B_IDLE=001,strat=00}=0x24
        $display("Test 4: Read STATUS");
        @(posedge clk);
        s_axi_araddr=9'h040; s_axi_arvalid=1; s_axi_rready=1;
        @(posedge clk); s_axi_arvalid=0;
        while (!s_axi_rvalid) @(posedge clk);
        if (s_axi_rdata == 32'h0000_0024) $display("  PASS: STATUS = 0x%08X", s_axi_rdata);
        else begin $display("  FAIL: STATUS = 0x%08X, exp 0x24", s_axi_rdata); err_cnt = err_cnt+1; end
        @(posedge clk); s_axi_rready=0;

        // Test 5: CTRL write -> start pulse
        $display("Test 5: CTRL start pulse");
        @(posedge clk);
        s_axi_awaddr=9'h000; s_axi_awvalid=1; s_axi_wdata=32'h1;
        s_axi_wstrb=4'hF; s_axi_wvalid=1; s_axi_bready=1;
        @(posedge clk); s_axi_awvalid=0; s_axi_wvalid=0; #1;
        if (axi_start_pulse == 1) $display("  PASS: axi_start_pulse fired");
        else begin $display("  FAIL: axi_start_pulse not set"); err_cnt = err_cnt+1; end
        while (!s_axi_bvalid) @(posedge clk);
        @(posedge clk); s_axi_bready=0;

        // Test 6: Read QUOTES_RCVD counter (0x044) — driven as quotes_in=42
        $display("Test 6: Read QUOTES_RCVD");
        @(posedge clk);
        s_axi_araddr=9'h044; s_axi_arvalid=1; s_axi_rready=1;
        @(posedge clk); s_axi_arvalid=0;
        while (!s_axi_rvalid) @(posedge clk);
        if (s_axi_rdata == 32'd42) $display("  PASS: QUOTES_RCVD = 42");
        else begin $display("  FAIL: QUOTES_RCVD = %0d, exp 42", s_axi_rdata); err_cnt = err_cnt+1; end
        @(posedge clk); s_axi_rready=0;

        // Test 7: Read POSITION[0] (0x058) — signed value readback
        $display("Test 7: Read POSITION[0]");
        pos_in[0] = -32'sd50;
        @(posedge clk);
        s_axi_araddr=9'h058; s_axi_arvalid=1; s_axi_rready=1;
        @(posedge clk); s_axi_arvalid=0;
        while (!s_axi_rvalid) @(posedge clk);
        if ($signed(s_axi_rdata) == -32'sd50) $display("  PASS: POSITION[0] = -50");
        else begin $display("  FAIL: POSITION[0] = %0d, exp -50", $signed(s_axi_rdata)); err_cnt = err_cnt+1; end
        @(posedge clk); s_axi_rready=0;

        // Test 8: Read HIST_BIN[0] (0x0A0) — histogram bin readback
        $display("Test 8: Read HIST_BIN[0]");
        hbins_in[0] = 32'd123;
        @(posedge clk);
        s_axi_araddr=9'h0A0; s_axi_arvalid=1; s_axi_rready=1;
        @(posedge clk); s_axi_arvalid=0;
        while (!s_axi_rvalid) @(posedge clk);
        if (s_axi_rdata == 32'd123) $display("  PASS: HIST_BIN[0] = 123");
        else begin $display("  FAIL: HIST_BIN[0] = %0d, exp 123", s_axi_rdata); err_cnt = err_cnt+1; end
        @(posedge clk); s_axi_rready=0;

        // Test 9: CTRL write 2 -> axi_reset_pulse fires
        $display("Test 9: CTRL reset pulse");
        @(posedge clk);
        s_axi_awaddr=9'h000; s_axi_awvalid=1; s_axi_wdata=32'h2;
        s_axi_wstrb=4'hF; s_axi_wvalid=1; s_axi_bready=1;
        @(posedge clk); s_axi_awvalid=0; s_axi_wvalid=0; #1;
        if (axi_reset_pulse == 1) $display("  PASS: axi_reset_pulse fired");
        else begin $display("  FAIL: axi_reset_pulse not set"); err_cnt = err_cnt+1; end
        while (!s_axi_bvalid) @(posedge clk);
        @(posedge clk); s_axi_bready=0;

        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $stop;
    end
endmodule
