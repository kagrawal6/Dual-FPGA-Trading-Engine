// ============================================================================
// Module: position_tracker
// Processes FILL frames from the exchange. Updates per-symbol signed position
// (BUY adds, SELL subtracts) and a 48-bit signed cash accumulator (Q32.16):
// SELL adds price*qty, BUY subtracts price*qty. Uses 1 DSP48E2 for the
// price*qty multiplication. Exports position array and cash for risk_manager
// readback and AXI telemetry. Also extracts ts_echo for latency measurement.
// ============================================================================

`timescale 1ns / 1ps

module position_tracker
    import hft_pkg::*;
#(
    parameter NUM_SYM = NUM_SYMBOLS
)(
    input  logic        clk,
    input  logic        rst_n,
    input  logic        clear,              // reset positions, cash, counters

    // FILL frame input (from msg_demux)
    input  logic [FRAME_W-1:0] fill_frame,
    input  logic                fill_valid,

    // Position and cash outputs (active registers, read by risk_manager + AXI)
    output position_t           position [NUM_SYM],
    output cash_t               cash,
    output sprice_t             total_pnl,       // = cash[47:16] (integer part)

    // Latency echo (to latency_histogram)
    output timestamp_t          ts_echo,
    output logic                fill_processed,  // pulse: valid fill handled

    // Status
    output logic [COUNTER_W-1:0] fills_rcvd
);

    // TODO: Implementation
    // Decode FILL frame per §4.5.3:
    //   [127:124]=msg_type, [123:116]=symbol_id, [115]=side, [114:112]=status,
    //   [111:80]=fill_price, [79:64]=fill_qty, [63:48]=order_id,
    //   [31:16]=ts_echo, [15:0]=seq_num
    // Only process if status == FILL_OK (3'b000).
    // Position update: BUY → position[sym] += qty; SELL → position[sym] -= qty.
    // Cash update: BUY → cash -= price * qty; SELL → cash += price * qty.
    //   (price is Q16.16, qty is integer → product is Q16.16, widen to Q32.16)
    // total_pnl = cash[47:16] (signed integer dollar value).

endmodule
