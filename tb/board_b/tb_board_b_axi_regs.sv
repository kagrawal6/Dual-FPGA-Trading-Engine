// ============================================================================
// Testbench: tb_board_b_axi_regs
// Tests AXI-Lite write/read for all config and status registers.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_b_axi_regs;

    localparam int TB_NUM_SYM = 4;
    localparam int ADDR_W = 9;

    logic clk, rst_n;
    logic [ADDR_W-1:0] awaddr, araddr;
    logic [2:0]  awprot, arprot;
    logic        awvalid, arvalid;
    logic        awready, arready;
    logic [31:0] wdata, rdata;
    logic [3:0]  wstrb;
    logic        wvalid, wready;
    logic [1:0]  bresp, rresp;
    logic        bvalid, bready;
    logic        rvalid, rready;

    logic         axi_start_pulse, axi_reset_pulse;
    strategy_e    strategy_sel;
    price_t       threshold;
    logic [15:0]  ema_alpha;
    qty_t         base_qty;
    logic [31:0]  max_position, max_order_rate;
    price_t       max_loss;

    b_state_e     fsm_state;
    logic         link_up, risk_halt;
    strategy_e    active_strategy;
    logic [31:0]  quotes_rcvd, orders_sent, fills_rcvd, risk_rejects, link_errors;
    position_t    position [TB_NUM_SYM];
    cash_t        cash;
    logic [31:0]  hist_bins [HIST_BINS];
    logic [31:0]  lat_min, lat_max, lat_sum, lat_count;

    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    board_b_axi_regs #(.NUM_SYM(TB_NUM_SYM)) dut (
        .clk(clk), .rst_n(rst_n),
        .s_axi_awaddr(awaddr), .s_axi_awprot(awprot), .s_axi_awvalid(awvalid), .s_axi_awready(awready),
        .s_axi_wdata(wdata), .s_axi_wstrb(wstrb), .s_axi_wvalid(wvalid), .s_axi_wready(wready),
        .s_axi_bresp(bresp), .s_axi_bvalid(bvalid), .s_axi_bready(bready),
        .s_axi_araddr(araddr), .s_axi_arprot(arprot), .s_axi_arvalid(arvalid), .s_axi_arready(arready),
        .s_axi_rdata(rdata), .s_axi_rresp(rresp), .s_axi_rvalid(rvalid), .s_axi_rready(rready),
        .axi_start_pulse(axi_start_pulse), .axi_reset_pulse(axi_reset_pulse),
        .strategy_sel(strategy_sel), .threshold(threshold), .ema_alpha(ema_alpha),
        .base_qty(base_qty), .max_position(max_position),
        .max_order_rate(max_order_rate), .max_loss(max_loss),
        .fsm_state(fsm_state), .link_up(link_up), .risk_halt(risk_halt),
        .active_strategy(active_strategy),
        .quotes_rcvd(quotes_rcvd), .orders_sent(orders_sent),
        .fills_rcvd(fills_rcvd), .risk_rejects(risk_rejects), .link_errors(link_errors),
        .position(position), .cash(cash),
        .hist_bins(hist_bins), .lat_min(lat_min), .lat_max(lat_max),
        .lat_sum(lat_sum), .lat_count(lat_count)
    );

    integer pass_count = 0;
    integer fail_count = 0;

    task automatic check(input string name, input logic condition);
        if (condition) pass_count++;
        else begin fail_count++; $display("[FAIL] %0s at %0t", name, $time); end
    endtask

    task automatic axi_write(input logic [8:0] addr, input logic [31:0] data);
        awaddr  = addr;
        awvalid = 1'b1;
        wdata   = data;
        wstrb   = 4'hF;
        wvalid  = 1'b1;
        @(posedge clk);
        awvalid = 1'b0;
        wvalid  = 1'b0;
        bready  = 1'b1;
        @(posedge clk);
        while (!bvalid) @(posedge clk);
        @(posedge clk);
        bready = 1'b0;
    endtask

    task automatic axi_read(input logic [8:0] addr, output logic [31:0] data);
        araddr  = addr;
        arvalid = 1'b1;
        @(posedge clk);
        arvalid = 1'b0;
        rready  = 1'b1;
        while (!rvalid) @(posedge clk);
        data = rdata;
        @(posedge clk);
        rready = 1'b0;
    endtask

    logic [31:0] rd_val;

    initial begin
        awaddr = '0; awprot = '0; awvalid = 1'b0;
        wdata = '0; wstrb = '0; wvalid = 1'b0;
        bready = 1'b0;
        araddr = '0; arprot = '0; arvalid = 1'b0;
        rready = 1'b0;
        fsm_state = B_IDLE; link_up = 1'b0; risk_halt = 1'b0;
        active_strategy = STRAT_MEAN_REV;
        quotes_rcvd = 32'd42; orders_sent = 32'd10;
        fills_rcvd = 32'd8; risk_rejects = 32'd2; link_errors = 32'd0;
        for (int i = 0; i < TB_NUM_SYM; i++) position[i] = '0;
        cash = '0;
        for (int i = 0; i < HIST_BINS; i++) hist_bins[i] = '0;
        lat_min = 32'd5; lat_max = 32'd96; lat_sum = 32'd331; lat_count = 32'd8;

        @(posedge rst_n);
        repeat (2) @(posedge clk);

        // ── T1: Write and readback config registers ─────────────
        $display("\n=== T1: Config write/read ===");

        axi_write(9'h008, 32'h0000_8000);  // threshold = $0.50
        check("T1: threshold",       threshold == 32'h0000_8000);

        axi_write(9'h00C, 32'h0000_199A);  // alpha ~10%
        check("T1: ema_alpha",       ema_alpha == 16'h199A);

        axi_write(9'h010, 32'h0000_00C8);  // qty = 200
        check("T1: base_qty",        base_qty == 16'd200);

        axi_write(9'h014, 32'h0000_03E8);  // max_pos = 1000
        check("T1: max_position",    max_position == 32'd1000);

        axi_write(9'h004, 32'h0000_0001);  // strategy = MOMENTUM
        check("T1: strategy",        strategy_sel == STRAT_MOMENTUM);

        // Readback
        axi_read(9'h008, rd_val);
        check("T1: readback threshold", rd_val == 32'h0000_8000);

        axi_read(9'h010, rd_val);
        check("T1: readback base_qty",  rd_val == 32'h0000_00C8);

        // ── T2: CTRL pulses ────────────────────────────────────
        $display("\n=== T2: CTRL pulse ===");
        axi_write(9'h000, 32'h0000_0001);  // start
        // Pulse should have fired (1 cycle)
        @(posedge clk);
        check("T2: start deasserts",    axi_start_pulse == 1'b0);

        // ── T3: Status readback ────────────────────────────────
        $display("\n=== T3: Status readback ===");
        fsm_state = B_TRADING;
        link_up   = 1'b1;
        risk_halt = 1'b0;
        active_strategy = STRAT_MEAN_REV;
        @(posedge clk);

        axi_read(9'h040, rd_val);
        // STATUS: {24'b0, risk_halt, link_up, fsm_state[2:0], active_strategy[1:0]}
        check("T3: status word",
              rd_val == {24'b0, 1'b0, 1'b1, B_TRADING, STRAT_MEAN_REV});

        axi_read(9'h044, rd_val);
        check("T3: quotes_rcvd", rd_val == 32'd42);

        axi_read(9'h048, rd_val);
        check("T3: orders_sent", rd_val == 32'd10);

        axi_read(9'h04C, rd_val);
        check("T3: fills_rcvd",  rd_val == 32'd8);

        // ── T4: Position readback ──────────────────────────────
        $display("\n=== T4: Position readback ===");
        position[0] = 32'd100;
        position[1] = -32'sd50;
        @(posedge clk);

        axi_read(9'h058, rd_val);
        check("T4: pos[0]==100",  rd_val == 32'd100);

        axi_read(9'h05C, rd_val);
        check("T4: pos[1]==-50",  rd_val == 32'hFFFF_FFCE);

        // ── T5: Latency stats readback ─────────────────────────
        $display("\n=== T5: Latency stats ===");
        axi_read(9'h0E0, rd_val);
        check("T5: lat_min==5",   rd_val == 32'd5);
        axi_read(9'h0E4, rd_val);
        check("T5: lat_max==96",  rd_val == 32'd96);
        axi_read(9'h0E8, rd_val);
        check("T5: lat_sum==331", rd_val == 32'd331);
        axi_read(9'h0EC, rd_val);
        check("T5: lat_count==8", rd_val == 32'd8);

        // ── Summary ─────────────────────────────────────────────
        repeat (3) @(posedge clk);
        $display("\n══════════════════════════════════════════");
        $display("  board_b_axi_regs testbench complete");
        $display("  PASSED: %0d", pass_count);
        $display("  FAILED: %0d", fail_count);
        $display("══════════════════════════════════════════\n");

        if (fail_count > 0) $fatal(1, "TESTBENCH FAILED");
        $finish;
    end

endmodule
