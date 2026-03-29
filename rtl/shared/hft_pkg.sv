// ============================================================================
// Package: hft_pkg
// Single source of truth for all compile-time parameters, typedefs, enums,
// and constants used across the HFT dual-FPGA design.
// ============================================================================

package hft_pkg;

    // ── Frame dimensions ────────────────────────────────────────────────────
    localparam int FRAME_W         = 128;
    localparam int LINK_DATA_W     = 4;      // 4-bit core, 8-bit stretch
    localparam int BEATS_PER_FRAME = FRAME_W / LINK_DATA_W;  // 32

    // ── Symbol configuration ────────────────────────────────────────────────
    localparam int NUM_SYMBOLS     = 16;
    localparam int SYMBOL_W        = 8;
    // Sector metadata for market_noise_gen / MMIO (must match $clog2(NUM_SECTORS)).
    localparam int NUM_SECTORS     = 8;
    localparam int SECTOR_ID_W     = (NUM_SECTORS > 1) ? $clog2(NUM_SECTORS) : 1;
    // market_noise_gen sym/sec drift integrator clamp.
    localparam logic signed [31:0] MARKET_NOISE_DRIFT_SAT_Q16 = 32'sh0000_1000;
    // Mean-reversion restoring force: pull_back = (init_mid - mid_price) >>> PULLBACK_SHIFT
    localparam int PULLBACK_SHIFT = 5;

    // ── Data widths ─────────────────────────────────────────────────────────
    localparam int PRICE_W         = 32;     // Q16.16 fixed-point
    localparam int QTY_W           = 16;
    localparam int ALPHA_W         = 16;     // Q0.16 (EMA smoothing factor)
    localparam int CASH_W          = 48;     // Q32.16 (large accumulator)
    localparam int POSITION_W      = 32;     // signed integer
    localparam int COUNTER_W       = 32;
    localparam int ORDER_ID_W      = 16;
    localparam int TIMESTAMP_W     = 16;
    localparam int SEQ_NUM_W       = 16;

    // ── Histogram ───────────────────────────────────────────────────────────
    localparam int HIST_BINS       = 16;
    localparam int HIST_BIN_W      = 32;
    localparam int BIN_SHIFT       = 5;      // each bin = 32 cycles

    // ── Typedefs ────────────────────────────────────────────────────────────
    typedef logic [PRICE_W-1:0]             price_t;
    typedef logic signed [PRICE_W-1:0]      sprice_t;
    typedef logic signed [POSITION_W-1:0]   position_t;
    typedef logic [QTY_W-1:0]               qty_t;
    typedef logic [SYMBOL_W-1:0]            symbol_t;
    typedef logic [ORDER_ID_W-1:0]          order_id_t;
    typedef logic [TIMESTAMP_W-1:0]         timestamp_t;
    typedef logic signed [CASH_W-1:0]       cash_t;

    // ── Message types ───────────────────────────────────────────────────────
    typedef enum logic [3:0] {
        MSG_QUOTE = 4'h1,
        MSG_ORDER = 4'h2,
        MSG_FILL  = 4'h3
    } msg_type_e;

    // ── Market regimes ──────────────────────────────────────────────────────
    typedef enum logic [1:0] {
        REGIME_CALM        = 2'b00,
        REGIME_VOLATILE    = 2'b01,
        REGIME_BURST       = 2'b10,
        REGIME_ADVERSARIAL = 2'b11
    } regime_e;

    // ── Strategy selection ──────────────────────────────────────────────────
    typedef enum logic [1:0] {
        STRAT_MEAN_REV = 2'b00,
        STRAT_MOMENTUM = 2'b01,
        STRAT_NN       = 2'b10,
        STRAT_AUTO     = 2'b11
    } strategy_e;

    // ── Board A FSM states (2-bit) ──────────────────────────────────────────
    typedef enum logic [1:0] {
        A_RESET   = 2'b00,
        A_IDLE    = 2'b01,
        A_RUNNING = 2'b10,
        A_STOPPED = 2'b11
    } a_state_e;

    // ── Board B FSM states (3-bit) ──────────────────────────────────────────
    typedef enum logic [2:0] {
        B_RESET   = 3'b000,
        B_IDLE    = 3'b001,
        B_ARMED   = 3'b010,
        B_TRADING = 3'b011,
        B_HALTED  = 3'b100
    } b_state_e;

    // ── Fill status ─────────────────────────────────────────────────────────
    typedef enum logic [2:0] {
        FILL_OK       = 3'b000,
        FILL_REJECTED = 3'b001
    } fill_status_e;

    // ── LFSR polynomial (32-bit Galois, maximal-length) ─────────────────────
    localparam logic [31:0] LFSR_TAPS = 32'h00400007;

endpackage
