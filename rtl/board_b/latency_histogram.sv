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
    input  logic        clear,              // reset bins + scalar stats

    // Fill event (from position_tracker)
    input  logic        fill_processed,
    input  timestamp_t  ts_echo,

    // Cycle counter (from board_b_top)
    input  timestamp_t  cycle_counter,

    // Histogram bins (read by AXI regs)
    output logic [HIST_BIN_W-1:0] hist_bins [HIST_BINS],

    // Scalar stats (read by AXI regs)
    output logic [COUNTER_W-1:0]  lat_min,
    output logic [COUNTER_W-1:0]  lat_max,
    output logic [COUNTER_W-1:0]  lat_sum,
    output logic [COUNTER_W-1:0]  lat_count
);

    // TODO: Implementation
    // latency = cycle_counter - ts_echo (16-bit wrapping subtraction)
    // bin_idx = latency[15:BIN_SHIFT] (upper bits select bin)
    // if (bin_idx >= HIST_BINS) bin_idx = HIST_BINS - 1;  // overflow bucket
    // hist_bins[bin_idx]++
    // lat_min = min(lat_min, latency); lat_max = max(lat_max, latency);
    // lat_sum += latency; lat_count++;

endmodule
