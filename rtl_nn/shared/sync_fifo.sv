// ============================================================================
// Module: sync_fifo
// Parameterized synchronous FIFO (single clock domain). Provides almost_full
// for link-layer backpressure and count for AXI status readback.
// ============================================================================

`timescale 1ns / 1ps

module sync_fifo #(
    parameter DATA_W             = 128,
    parameter DEPTH              = 64,
    parameter ALMOST_FULL_THRESH = DEPTH - 4
)(
    input  logic                       clk,
    input  logic                       rst_n,
    input  logic                       flush,

    input  logic                       wr_en,
    input  logic [DATA_W-1:0]          wr_data,
    output logic                       full,

    input  logic                       rd_en,
    output logic [DATA_W-1:0]          rd_data,
    output logic                       empty,

    output logic                       almost_full,
    output logic [$clog2(DEPTH):0]     count
);

    localparam int PTR_W = (DEPTH <= 2) ? 1 : $clog2(DEPTH);

    logic [DATA_W-1:0] mem[0:DEPTH-1];
    logic [PTR_W-1:0] wr_ptr, rd_ptr;
    logic [$clog2(DEPTH):0] count_r;

    assign full        = (count_r == DEPTH[$clog2(DEPTH):0]);
    assign empty       = (count_r == '0);
    assign almost_full = (count_r >= ALMOST_FULL_THRESH[$clog2(DEPTH):0]);
    assign count       = count_r;
    assign rd_data     = mem[rd_ptr];

    function automatic logic [PTR_W-1:0] ptr_next(input logic [PTR_W-1:0] p);
        if (DEPTH <= 1)
            ptr_next = '0;
        else if (p == PTR_W'(DEPTH - 1))
            ptr_next = '0;
        else
            ptr_next = p + 1'b1;
    endfunction

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            wr_ptr  <= '0;
            rd_ptr  <= '0;
            count_r <= '0;
        end else if (flush) begin
            wr_ptr  <= '0;
            rd_ptr  <= '0;
            count_r <= '0;
        end else begin
            unique case ({wr_en && !full, rd_en && !empty})
                2'b10: count_r <= count_r + 1'b1;
                2'b01: count_r <= count_r - 1'b1;
                default: ;
            endcase

            if (wr_en && !full) begin
                mem[wr_ptr] <= wr_data;
                wr_ptr      <= ptr_next(wr_ptr);
            end
            if (rd_en && !empty) begin
                rd_ptr <= ptr_next(rd_ptr);
            end
        end
    end

endmodule
