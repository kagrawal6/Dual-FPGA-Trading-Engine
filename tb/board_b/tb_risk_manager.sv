// ============================================================================
// Testbench: tb_risk_manager
// Tests the risk_manager module: position limit, order rate, max loss checks,
// approved output gating, risk_halt latch, and clear functionality.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_risk_manager;

    logic                     clk;
    logic                     rst_n;
    logic                     clear;
    logic                     order_enable;
    logic                     signal_valid;
    logic                     signal_side;
    price_t                   signal_price;
    qty_t                     signal_qty;
    symbol_t                  signal_symbol;
    position_t                position [4];
    sprice_t                  total_pnl;
    logic [POSITION_W-1:0]     max_position;
    logic [COUNTER_W-1:0]     max_order_rate;
    price_t                   max_loss;
    logic                     approved_valid;
    logic                     approved_side;
    price_t                   approved_price;
    qty_t                     approved_qty;
    symbol_t                  approved_symbol;
    logic                     risk_halt;
    logic [COUNTER_W-1:0]     risk_rejects;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    risk_manager dut (
        .clk             (clk),
        .rst_n           (rst_n),
        .clear           (clear),
        .order_enable    (order_enable),
        .signal_valid    (signal_valid),
        .signal_side     (signal_side),
        .signal_price    (signal_price),
        .signal_qty      (signal_qty),
        .signal_symbol   (signal_symbol),
        .position        (position),
        .total_pnl       (total_pnl),
        .max_position    (max_position),
        .max_order_rate  (max_order_rate),
        .max_loss        (max_loss),
        .approved_valid  (approved_valid),
        .approved_side   (approved_side),
        .approved_price  (approved_price),
        .approved_qty    (approved_qty),
        .approved_symbol (approved_symbol),
        .risk_halt       (risk_halt),
        .risk_rejects    (risk_rejects)
    );

    initial begin
        // TODO: Add test stimulus
        $finish;
    end

endmodule
