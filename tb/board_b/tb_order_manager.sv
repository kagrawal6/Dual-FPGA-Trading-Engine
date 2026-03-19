// ============================================================================
// Testbench: tb_order_manager
// Tests the order_manager module: ORDER frame packing, order_id and seq_num
// auto-increment, timestamp capture, and order_ready handshake.
// ============================================================================

`timescale 1ns / 1ps

import hft_pkg::*;

module tb_order_manager;

    logic                     clk;
    logic                     rst_n;
    logic                     clear;
    logic                     approved_valid;
    logic                     approved_side;
    price_t                   approved_price;
    qty_t                     approved_qty;
    symbol_t                  approved_symbol;
    timestamp_t               cycle_counter;
    logic [FRAME_W-1:0]       order_frame;
    logic                     order_valid;
    logic                     order_ready;
    logic [COUNTER_W-1:0]     orders_sent;

    // Clock generation (100 MHz)
    initial clk = 0;
    always #5 clk = ~clk;

    // Reset generation (active-low, deassert after 100ns)
    initial begin
        rst_n = 0;
        #100;
        rst_n = 1;
    end

    order_manager dut (
        .clk             (clk),
        .rst_n           (rst_n),
        .clear           (clear),
        .approved_valid  (approved_valid),
        .approved_side   (approved_side),
        .approved_price  (approved_price),
        .approved_qty    (approved_qty),
        .approved_symbol (approved_symbol),
        .cycle_counter   (cycle_counter),
        .order_frame     (order_frame),
        .order_valid     (order_valid),
        .order_ready     (order_ready),
        .orders_sent     (orders_sent)
    );

    initial begin
        // TODO: Add test stimulus
        $finish;
    end

endmodule
