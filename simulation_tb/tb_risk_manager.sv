`timescale 1ns / 1ps

module tb_risk_manager();
    import hft_pkg::*;

    logic        clk, rst_n, clear, order_enable;
    logic        signal_valid, signal_side;
    price_t      signal_price;
    qty_t        signal_qty;
    symbol_t     signal_symbol;
    position_t   position [NUM_SYMBOLS];
    sprice_t     total_pnl;
    logic [POSITION_W-1:0] max_position;
    logic [COUNTER_W-1:0]  max_order_rate;
    price_t                max_loss;
    logic        approved_valid, approved_side;
    price_t      approved_price;
    qty_t        approved_qty;
    symbol_t     approved_symbol;
    logic        fill_valid, fill_side;
    symbol_t     fill_symbol;
    qty_t        fill_qty;
    logic        risk_halt;
    logic [COUNTER_W-1:0] risk_rejects;

    integer err_cnt = 0;

    always #5 clk = ~clk;

    risk_manager dut (
        .clk(clk), .rst_n(rst_n), .clear(clear),
        .order_enable(order_enable),
        .signal_valid(signal_valid), .signal_side(signal_side),
        .signal_price(signal_price), .signal_qty(signal_qty),
        .signal_symbol(signal_symbol),
        .position(position), .total_pnl(total_pnl),
        .max_position(max_position), .max_order_rate(max_order_rate),
        .max_loss(max_loss),
        .approved_valid(approved_valid), .approved_side(approved_side),
        .approved_price(approved_price), .approved_qty(approved_qty),
        .approved_symbol(approved_symbol),
        .fill_valid(fill_valid), .fill_symbol(fill_symbol),
        .fill_side(fill_side), .fill_qty(fill_qty),
        .risk_halt(risk_halt), .risk_rejects(risk_rejects)
    );

    integer i;
    initial begin
        clk = 0; rst_n = 0; clear = 0;
        order_enable = 1; signal_valid = 0; signal_side = 0;
        signal_price = 0; signal_qty = 0; signal_symbol = 0;
        total_pnl = 0; max_position = 32'd1000;
        max_order_rate = 32'd100; max_loss = 32'd5000;
        fill_valid = 0; fill_symbol = 0; fill_side = 0; fill_qty = 0;
        for (i = 0; i < NUM_SYMBOLS; i = i + 1) position[i] = 0;
        #20; rst_n = 1;
        @(posedge clk);

        // Test 1: Normal order, all limits OK -> approved
        $display("TEST 1: Normal order -> approved");
        signal_valid = 1; signal_side = 0;
        signal_price = 32'd500; signal_qty = 16'd10; signal_symbol = 8'd0;
        @(posedge clk);
        signal_valid = 0;
        @(posedge clk); #1;
        if (approved_valid !== 1'b1) begin
            $display("FAIL: approved_valid should be 1"); err_cnt = err_cnt + 1;
        end else $display("PASS: order approved");
        if (approved_price !== 32'd500) begin
            $display("FAIL: approved_price=%0d, exp 500", approved_price); err_cnt = err_cnt + 1;
        end else $display("PASS: approved_price=500");
        @(posedge clk); #1;

        // Test 2: order_enable=0 -> rejected
        $display("TEST 2: order_enable=0 -> rejected");
        order_enable = 0;
        signal_valid = 1; signal_side = 0;
        signal_price = 32'd500; signal_qty = 16'd10; signal_symbol = 8'd0;
        @(posedge clk);
        signal_valid = 0;
        @(posedge clk); #1;
        if (approved_valid !== 1'b0) begin
            $display("FAIL: approved_valid should be 0"); err_cnt = err_cnt + 1;
        end else $display("PASS: rejected (enable=0)");
        order_enable = 1;
        @(posedge clk); #1;

        // Test 3: Position at limit -> rejected
        $display("TEST 3: Position at limit -> rejected");
        position[0] = 32'sd995;
        signal_valid = 1; signal_side = 0;
        signal_price = 32'd500; signal_qty = 16'd10; signal_symbol = 8'd0;
        @(posedge clk);
        signal_valid = 0;
        @(posedge clk); #1;
        if (approved_valid !== 1'b0) begin
            $display("FAIL: should reject (pos limit)"); err_cnt = err_cnt + 1;
        end else $display("PASS: rejected (position limit)");
        position[0] = 0;
        @(posedge clk); #1;

        // Test 4: max_loss exceeded -> risk_halt latches
        $display("TEST 4: PnL below -max_loss -> risk_halt");
        total_pnl = -32'sd6000;
        signal_valid = 1; signal_side = 0;
        signal_price = 32'd500; signal_qty = 16'd1; signal_symbol = 8'd1;
        @(posedge clk);
        signal_valid = 0;
        @(posedge clk); #1;
        if (risk_halt !== 1'b1) begin
            $display("FAIL: risk_halt should latch high"); err_cnt = err_cnt + 1;
        end else $display("PASS: risk_halt latched");

        // Test 5: Clear resets risk_halt
        $display("TEST 5: Clear resets risk_halt");
        total_pnl = 0; clear = 1;
        @(posedge clk);
        clear = 0;
        @(posedge clk); #1;
        if (risk_halt !== 1'b0) begin
            $display("FAIL: risk_halt should clear"); err_cnt = err_cnt + 1;
        end else $display("PASS: risk_halt cleared");

        $display("=================================");
        if (err_cnt == 0) $display("ALL TESTS PASSED");
        else $display("FAILED: %0d errors", err_cnt);
        $display("=================================");
        $stop;
    end

endmodule
