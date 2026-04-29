// ============================================================================
// Testbench: tb_board_b_axi_regs
// Tests AXI-Lite write/read for all config and status registers.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_board_b_axi_regs;

    localparam int TB_NUM_SYM = 4;
    localparam int ADDR_W = 10;  // bumped 9→10 for B2 per-symbol AXI exposure

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

    // ── B2 per-symbol arrays driven into the DUT ────────────────
    price_t       qb_best_bid       [TB_NUM_SYM];
    price_t       qb_best_ask       [TB_NUM_SYM];
    cash_t        pnl_cash_per_sym  [TB_NUM_SYM];
    price_t       last_fill_price   [TB_NUM_SYM];
    logic [15:0]  trades_per_sym    [TB_NUM_SYM];

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
        .lat_sum(lat_sum), .lat_count(lat_count),
        .qb_best_bid(qb_best_bid),
        .qb_best_ask(qb_best_ask),
        .pnl_cash_per_sym(pnl_cash_per_sym),
        .last_fill_price (last_fill_price),
        .trades_per_sym  (trades_per_sym)
    );

    integer pass_count = 0;
    integer fail_count = 0;

    task automatic check(input string name, input logic condition);
        if (condition) pass_count++;
        else begin fail_count++; $display("[FAIL] %0s at %0t", name, $time); end
    endtask

    task automatic axi_write(input logic [ADDR_W-1:0] addr, input logic [31:0] data);
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

    task automatic axi_read(input logic [ADDR_W-1:0] addr, output logic [31:0] data);
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

        // Init B2 per-symbol arrays
        for (int i = 0; i < TB_NUM_SYM; i++) begin
            qb_best_bid[i]      = '0;
            qb_best_ask[i]      = '0;
            pnl_cash_per_sym[i] = '0;
            last_fill_price[i]  = '0;
            trades_per_sym[i]   = '0;
        end

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

        // ── T6: Default register values ──────────────────────
        $display("\n=== T6: Default values ===");
        // Read defaults BEFORE any writes (need fresh DUT for this)
        // We already wrote some registers, so check the ones we didn't touch
        axi_read(9'h018, rd_val);
        check("T6: default max_order_rate==1000", max_order_rate == 32'd1000);

        axi_read(9'h01C, rd_val);
        check("T6: default max_loss==100", max_loss == 32'd100);

        axi_read(9'h014, rd_val);
        check("T6: max_position readback", rd_val == 32'd1000);

        // ── T7: STATUS register bit packing ──────────────────
        $display("\n=== T7: STATUS register packing ===");
        // Test all combinations of status bits
        fsm_state = B_ARMED;
        link_up   = 1'b0;
        risk_halt = 1'b1;
        active_strategy = STRAT_NN;
        @(posedge clk);

        axi_read(9'h040, rd_val);
        // STATUS: {25'b0, risk_halt, link_up, fsm_state[2:0], active_strategy[1:0]}
        check("T7a: status ARMED+halt+NN",
              rd_val == {25'b0, 1'b1, 1'b0, B_ARMED, STRAT_NN});

        fsm_state = B_HALTED;
        link_up   = 1'b1;
        risk_halt = 1'b1;
        active_strategy = STRAT_AUTO;
        @(posedge clk);

        axi_read(9'h040, rd_val);
        check("T7b: status HALTED+link+halt+AUTO",
              rd_val == {25'b0, 1'b1, 1'b1, B_HALTED, STRAT_AUTO});

        fsm_state = B_IDLE;
        link_up   = 1'b0;
        risk_halt = 1'b0;
        active_strategy = STRAT_MEAN_REV;
        @(posedge clk);

        axi_read(9'h040, rd_val);
        check("T7c: status IDLE clean",
              rd_val == {25'b0, 1'b0, 1'b0, B_IDLE, STRAT_MEAN_REV});

        // ── T8: Histogram bin readback ───────────────────────
        $display("\n=== T8: Histogram bin readback ===");
        hist_bins[0] = 32'd42;
        hist_bins[5] = 32'd999;
        @(posedge clk);

        axi_read(9'h0A0, rd_val);
        check("T8a: hist_bin[0]==42",  rd_val == 32'd42);

        axi_read(9'h0A0 + 9'd20, rd_val);  // bin[5] at offset 5*4=20
        check("T8b: hist_bin[5]==999", rd_val == 32'd999);

        // ── T9: Cash readback (high word sign extension) ─────
        $display("\n=== T9: Cash readback ===");
        cash = -48'sd12345;
        @(posedge clk);

        axi_read(9'h098, rd_val);
        check("T9a: cash_lo",    rd_val == cash[31:0]);

        axi_read(9'h09C, rd_val);
        check("T9b: cash_hi sign-ext", rd_val == {{16{cash[47]}}, cash[47:32]});

        // ── T10: Reset pulse ─────────────────────────────────
        $display("\n=== T10: Reset pulse ===");
        axi_write(10'h000, 32'h0000_0002);
        @(posedge clk);
        check("T10: reset deasserts", axi_reset_pulse == 1'b0);

        // ── T11: B2 — per-symbol BID/ASK readback (0x100/0x140 base) ─
        $display("\n=== T11: B2 per-symbol BID/ASK arrays ===");
        qb_best_bid[0] = 32'h00B3_F800;  qb_best_ask[0] = 32'h00B4_0800;
        qb_best_bid[1] = 32'h01A3_F800;  qb_best_ask[1] = 32'h01A4_0800;
        qb_best_bid[2] = 32'h0383_F800;  qb_best_ask[2] = 32'h0384_0800;
        qb_best_bid[3] = 32'h0072_F800;  qb_best_ask[3] = 32'h0073_0800;
        @(posedge clk);

        for (int i = 0; i < TB_NUM_SYM; i++) begin
            axi_read(10'(10'h100 + i*4), rd_val);
            check($sformatf("T11: BID[%0d]", i),  rd_val == qb_best_bid[i]);
            axi_read(10'(10'h140 + i*4), rd_val);
            check($sformatf("T11: ASK[%0d]", i),  rd_val == qb_best_ask[i]);
        end

        // ── T12: B2 — per-symbol PNL_CASH 48-bit split readback (0x180/0x1C0) ─
        $display("\n=== T12: B2 per-symbol PNL_CASH (LO/HI) ===");
        // Use a positive and a negative cash value to verify sign-extension
        pnl_cash_per_sym[0] =  48'h0000_5200_FFE2;   // positive
        pnl_cash_per_sym[1] = -48'sd1000;            // negative
        pnl_cash_per_sym[2] = -48'sh4654_FFB0;       // larger negative
        pnl_cash_per_sym[3] =  48'h0000_0000_C8C8;
        @(posedge clk);

        for (int i = 0; i < TB_NUM_SYM; i++) begin
            axi_read(10'(10'h180 + i*4), rd_val);
            check($sformatf("T12: PNL_LO[%0d]", i), rd_val == pnl_cash_per_sym[i][31:0]);
            axi_read(10'(10'h1C0 + i*4), rd_val);
            check($sformatf("T12: PNL_HI[%0d] (sign-ext)", i),
                  rd_val == {{16{pnl_cash_per_sym[i][47]}}, pnl_cash_per_sym[i][47:32]});
        end

        // ── T13: B2 — per-symbol LAST_FILL_PRICE readback (0x200) ─
        $display("\n=== T13: B2 last_fill_price array ===");
        last_fill_price[0] = 32'h00B4_0CCC;
        last_fill_price[1] = 32'h01A4_1999;
        last_fill_price[2] = 32'h0384_0816;
        last_fill_price[3] = 32'h0073_080F;
        @(posedge clk);
        for (int i = 0; i < TB_NUM_SYM; i++) begin
            axi_read(10'(10'h200 + i*4), rd_val);
            check($sformatf("T13: LAST_FILL[%0d]", i), rd_val == last_fill_price[i]);
        end

        // ── T14: B2 — TRADES_PACK readback (2× 16b per word, base 0x240) ─
        $display("\n=== T14: B2 trades_per_sym packed readback ===");
        trades_per_sym[0] = 16'h0003;
        trades_per_sym[1] = 16'h0001;
        trades_per_sym[2] = 16'h0007;
        trades_per_sym[3] = 16'h0000;
        @(posedge clk);
        // Pack0 word should hold {trades[1], trades[0]} = {16'h0001, 16'h0003}
        axi_read(10'h240, rd_val);
        check("T14a: TRADES_PACK[0]={trades[1],trades[0]}",
              rd_val == {trades_per_sym[1], trades_per_sym[0]});
        // Pack1 word should hold {trades[3], trades[2]} = {16'h0000, 16'h0007}
        axi_read(10'h244, rd_val);
        check("T14b: TRADES_PACK[1]={trades[3],trades[2]}",
              rd_val == {trades_per_sym[3], trades_per_sym[2]});

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
