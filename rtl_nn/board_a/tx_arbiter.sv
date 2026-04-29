// ============================================================================
// Module: tx_arbiter
// Strict-priority 2:1 frame multiplexer. Fill frames (high priority) always
// win over quote frames (low priority). Once a frame starts serialization
// it completes without preemption. Outputs one frame at a time to link_tx.
// ============================================================================

// -----------------------------------------------------------------------------
// Future complexity / upgrade ideas for tx_arbiter
//
// Current version is intentionally minimal:
//   - strict priority: fill > quote
//   - one-entry output buffer
//   - no dropped frame under backpressure
//   - no fairness logic
//   - one-cycle bubble between consume and next accept is acceptable
//
// Ways this file could become more complex in the future:
//
// 1) Quote starvation prevention
//    - Right now, continuous fill traffic can starve quotes forever.
//    - Future version could add fairness or weighted scheduling so quotes
//      still get occasional service under heavy fill load.
//
// 2) Same-cycle consume + refill
//    - Current arbiter inserts a bubble after tx_ready consumes a frame.
//    - Future version could support refill in the same cycle for higher
//      throughput, but logic becomes trickier.
//
// 3) More message classes
//    - Right now there are only two inputs: fill and quote.
//    - Future versions could arbitrate among fills, rejects, quotes,
//      control/status frames, telemetry, etc.
//
// 4) Weighted / policy-based scheduling
//    - Instead of fixed priority, future logic could support round-robin,
//      weighted priority, or configurable QoS rules.
//
// 5) Input-side buffering
//    - Current design assumes producers hold valid correctly until accepted.
//    - Future version could add FIFOs on fill/quote inputs for burst absorption.
//
// 6) Burst-aware arbitration
//    - Could choose to drain several fills before returning to quotes, or vice
//      versa, depending on system goals.
//
// 7) Runtime-configurable arbitration policy
//    - Priority mode could later become software-configurable via AXI-Lite
//      registers instead of hardcoded fill > quote.
//
// Keep current version simple for the original demo. Only add these if needed
// after the baseline system is fully stable.
// -----------------------------------------------------------------------------

`timescale 1ns / 1ps

module tx_arbiter
    import hft_pkg::*;
(
    input  logic                clk,
    input  logic                rst_n,

    // Fill frame input (high priority)
    input  logic [FRAME_W-1:0] fill_frame,
    input  logic                fill_valid,
    output logic                fill_ready,

    // Quote frame input (low priority)
    input  logic [FRAME_W-1:0] quote_frame,
    input  logic                quote_valid,
    output logic                quote_ready,

    // Arbitrated output (to link_tx)
    output logic [FRAME_W-1:0] tx_frame,
    output logic                tx_valid,
    input  logic                tx_ready
);

    // One-entry output buffer:
    // - strict selection when empty: fill > quote
    // - once buffered, frame is held until tx_ready handshake
    // - no frame dropping due to downstream backpressure
    logic [FRAME_W-1:0] tx_frame_buf;
    logic               tx_buf_valid;

    // Upstream ready signals (never both high at once):
    // - fill gets priority
    // - quote ready only when fill is not currently requesting
    assign fill_ready  = !tx_buf_valid;
    assign quote_ready = !tx_buf_valid && !fill_valid;

    // Link-side output from buffered frame
    assign tx_frame = tx_frame_buf;
    assign tx_valid = tx_buf_valid;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tx_frame_buf <= '0;
            tx_buf_valid <= 1'b0;
        end else begin
            // Consume buffered frame when downstream accepts it.
            if (tx_buf_valid && tx_ready) begin
                tx_buf_valid <= 1'b0;
            end

            // If buffer is empty this cycle, accept one input frame.
            if (!tx_buf_valid) begin
                if (fill_valid) begin
                    tx_frame_buf <= fill_frame;
                    tx_buf_valid <= 1'b1;
                end else if (quote_valid) begin
                    tx_frame_buf <= quote_frame;
                    tx_buf_valid <= 1'b1;
                end
            end
        end
    end

endmodule
