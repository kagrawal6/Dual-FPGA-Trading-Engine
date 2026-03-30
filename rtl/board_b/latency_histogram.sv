// ============================================================================
// Module: latency_histogram
// Hardware round-trip latency measurement. On each processed FILL, computes
// latency = cycle_counter - ts_echo (wrapping 16-bit subtraction). Maps to
// one of 16 histogram bins (bin = latency >> BIN_SHIFT). Maintains scalar
// stats: lat_min, lat_max, lat_sum, lat_count. All outputs readable via AXI.
// ============================================================================

`timescale 1ns / 1ps

module latency_histogram
    import hft_pkg::*;
(
    input  logic        clk,
    input  logic        rst_n,
    input  logic        clear,

    input  logic        fill_processed,
    input  timestamp_t  ts_echo,

    input  timestamp_t  cycle_counter,

    output logic [HIST_BIN_W-1:0] hist_bins [HIST_BINS],

    output logic [COUNTER_W-1:0]  lat_min,
    output logic [COUNTER_W-1:0]  lat_max,
    output logic [COUNTER_W-1:0]  lat_sum,
    output logic [COUNTER_W-1:0]  lat_count
);

    // ── Latency computation (16-bit wrapping) ───────────────────
    logic [15:0] latency;
    assign latency = cycle_counter - ts_echo;

    // ── Bin index (clamped to HIST_BINS-1) ──────────────────────
    logic [3:0] bin_idx;
    always_comb begin
        if (latency[15:BIN_SHIFT] >= HIST_BINS[15:0])
            bin_idx = HIST_BINS[3:0] - 4'd1;
        else
            bin_idx = latency[BIN_SHIFT+3:BIN_SHIFT];
    end

    // ── Registered update ───────────────────────────────────────
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            lat_min   <= 32'hFFFF_FFFF;
            lat_max   <= '0;
            lat_sum   <= '0;
            lat_count <= '0;
            for (int i = 0; i < HIST_BINS; i++)
                hist_bins[i] <= '0;
        end else if (clear) begin
            lat_min   <= 32'hFFFF_FFFF;
            lat_max   <= '0;
            lat_sum   <= '0;
            lat_count <= '0;
            for (int i = 0; i < HIST_BINS; i++)
                hist_bins[i] <= '0;
        end else if (fill_processed) begin
            // Histogram bin
            hist_bins[bin_idx] <= hist_bins[bin_idx] + 1'b1;

            // Scalar stats
            if ({16'b0, latency} < lat_min)
                lat_min <= {16'b0, latency};
            if ({16'b0, latency} > lat_max)
                lat_max <= {16'b0, latency};

            lat_sum   <= lat_sum + {16'b0, latency};
            lat_count <= lat_count + 1'b1;
        end
    end

endmodule
