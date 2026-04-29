// ============================================================================
// Module: board_a_top
// Top-level wrapper for Board A (Exchange + Market Simulator).
// Contains the 4-state FSM (RESET/IDLE/RUNNING/STOPPED), instantiates all
// Board A sub-modules, and performs structural wiring. This is the module
// packaged as a Vivado custom IP with an AXI-Lite slave interface.
// ============================================================================

`timescale 1ns / 1ps

module board_a_top
    import hft_pkg::*;
#(
    parameter NUM_SYM            = NUM_SYMBOLS,
    parameter LINK_W             = LINK_DATA_W,
    parameter C_S_AXI_ADDR_WIDTH = 8,
    parameter C_S_AXI_DATA_WIDTH = 32
)(
    input  logic        clk,
    input  logic        rst_n,

    // ── Physical I/O ────────────────────────────────────────────────────────
    input  logic [3:0]  btn,
    input  logic [7:0]  sw,
    output logic [7:0]  led,
    output logic [2:0]  rgb0,
    output logic [2:0]  rgb1,

    // ── PMOD JA — TX direction (Board A → Board B) ─────────────────────────
    output logic [LINK_W-1:0] pmod_ja,           // JA[3:0] data
    output logic              pmod_ja_valid,      // JA[4]
    input  logic              pmod_ja_ready,      // JA[5] (from Board B)

    // ── PMOD JB — RX direction (Board B → Board A) ─────────────────────────
    input  logic [LINK_W-1:0] pmod_jb,           // JB[3:0] data
    input  logic              pmod_jb_valid,      // JB[4]
    output logic              pmod_jb_ready,      // JB[5] (to Board B)

    // ── AXI-Lite Slave Interface ────────────────────────────────────────────
    input  logic [C_S_AXI_ADDR_WIDTH-1:0] s_axi_awaddr,
    input  logic [2:0]                     s_axi_awprot,
    input  logic                           s_axi_awvalid,
    output logic                           s_axi_awready,
    input  logic [C_S_AXI_DATA_WIDTH-1:0] s_axi_wdata,
    input  logic [3:0]                     s_axi_wstrb,
    input  logic                           s_axi_wvalid,
    output logic                           s_axi_wready,
    output logic [1:0]                     s_axi_bresp,
    output logic                           s_axi_bvalid,
    input  logic                           s_axi_bready,
    input  logic [C_S_AXI_ADDR_WIDTH-1:0] s_axi_araddr,
    input  logic [2:0]                     s_axi_arprot,
    input  logic                           s_axi_arvalid,
    output logic                           s_axi_arready,
    output logic [C_S_AXI_DATA_WIDTH-1:0] s_axi_rdata,
    output logic [1:0]                     s_axi_rresp,
    output logic                           s_axi_rvalid,
    input  logic                           s_axi_rready
);

    // ── Internal wires ──────────────────────────────────────────────────────
    // FSM
    a_state_e fsm_state, fsm_next;
    logic running, lfsr_load, counter_clr, fifo_flush;

    // AXI config outputs
    logic        axi_start_pulse, axi_reset_pulse;
    regime_e     regime_from_ps;
    logic [31:0] quote_interval, lfsr_seed;
    price_t      sym_init_mid    [NUM_SYM];
    price_t      sym_init_spread [NUM_SYM];
    logic [SECTOR_ID_W-1:0] sym_sector_id [NUM_SYM];
    logic [15:0]            sym_company_token [NUM_SYM];
    logic [7:0]              active_sym_count;

    // Ctrl outputs
    logic   ctrl_start_pulse, ctrl_stop_pulse, ctrl_reset_pulse;
    regime_e regime_sw;
    logic   sw_override;

    // Combined triggers
    logic start_combined, stop_combined, reset_combined;
    assign start_combined = axi_start_pulse | ctrl_start_pulse;
    assign stop_combined  = ctrl_stop_pulse;
    assign reset_combined = axi_reset_pulse | ctrl_reset_pulse;

    // Active regime: switch override or PS register
    regime_e active_regime;
    assign active_regime = sw_override ? regime_sw : regime_from_ps;

    // Data plane wires
    logic [FRAME_W-1:0] quote_frame, fill_frame;
    logic               quote_valid_ms, quote_ready_ms;
    logic [FRAME_W-1:0] quote_frame_fifo;
    logic               quote_valid_fifo, quote_ready_arb;
    logic               fill_valid, fill_ready;
    logic               order_valid_rx;
    logic [FRAME_W-1:0] tx_frame;
    logic               tx_valid, tx_ready;

    // Status
    logic [COUNTER_W-1:0] quotes_generated, orders_rcvd, fills_sent, rejects_sent;
    logic [COUNTER_W-1:0] link_errors;
    logic                 link_up;
    logic [$clog2(64):0]  quote_fifo_count;
    logic [6:0]            fifo_fill_level;
    price_t               best_bid [NUM_SYM];
    price_t               best_ask [NUM_SYM];
    logic [FRAME_W-1:0]   frame_out;
    logic                 frame_out_valid;

    // ── FSM (§4.4.4) ────────────────────────────────────────────────────────
    always_comb begin
        fsm_next = fsm_state;
        unique case (fsm_state)
            A_RESET: fsm_next = A_IDLE;
            A_IDLE: begin
                if (reset_combined) fsm_next = A_RESET;
                else if (start_combined) fsm_next = A_RUNNING;
            end
            A_RUNNING: begin
                if (reset_combined) fsm_next = A_RESET;
                else if (stop_combined) fsm_next = A_STOPPED;
            end
            A_STOPPED: begin
                if (reset_combined) fsm_next = A_RESET;
                else if (start_combined) fsm_next = A_RUNNING;
            end
            default: fsm_next = A_IDLE;
        endcase
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            fsm_state <= A_RESET;
        else
            fsm_state <= fsm_next;
    end

    assign running      = (fsm_state == A_RUNNING);
    assign counter_clr  = (fsm_state == A_RESET);
    assign fifo_flush   = (fsm_state == A_RESET);
    assign lfsr_load    = (fsm_state == A_IDLE) && (fsm_next == A_RUNNING);

    // exchange only when market is live (Option A — clean demo: frozen market ⇒ no matching).
    // Alternate (spec “drain in STOPPED”): assign exchange_enable = running || (fsm_state==A_STOPPED);
    logic exchange_enable;
    assign exchange_enable = running;

    // Quote FIFO (write side = market_sim, read side = tx_arbiter)
    logic quote_fifo_wr_en;
    logic quote_fifo_rd_en;
    logic quote_fifo_full;
    logic quote_fifo_empty;
    logic quote_fifo_af_unused;
    assign quote_ready_ms = !quote_fifo_full;
    assign quote_fifo_wr_en = quote_valid_ms && !quote_fifo_full;

    assign quote_valid_fifo = !quote_fifo_empty;
    assign quote_fifo_rd_en = quote_ready_arb && quote_valid_fifo;

    // Same-cycle: frame_out stable while frame_out_valid (link_rx pulse); OK for single-slot exchange_lite.
    assign order_valid_rx = frame_out_valid && (frame_out[127:124] == MSG_ORDER);

    assign fifo_fill_level = quote_fifo_count[6:0];

    board_a_axi_regs #(
        .NUM_SYM(NUM_SYM),
        .C_S_AXI_ADDR_WIDTH(C_S_AXI_ADDR_WIDTH),
        .C_S_AXI_DATA_WIDTH(C_S_AXI_DATA_WIDTH)
    ) u_axi_regs (
        .clk               (clk),
        .rst_n             (rst_n),
        .s_axi_awaddr      (s_axi_awaddr),
        .s_axi_awprot      (s_axi_awprot),
        .s_axi_awvalid     (s_axi_awvalid),
        .s_axi_awready     (s_axi_awready),
        .s_axi_wdata       (s_axi_wdata),
        .s_axi_wstrb       (s_axi_wstrb),
        .s_axi_wvalid      (s_axi_wvalid),
        .s_axi_wready      (s_axi_wready),
        .s_axi_bresp       (s_axi_bresp),
        .s_axi_bvalid      (s_axi_bvalid),
        .s_axi_bready      (s_axi_bready),
        .s_axi_araddr      (s_axi_araddr),
        .s_axi_arprot      (s_axi_arprot),
        .s_axi_arvalid     (s_axi_arvalid),
        .s_axi_arready     (s_axi_arready),
        .s_axi_rdata       (s_axi_rdata),
        .s_axi_rresp       (s_axi_rresp),
        .s_axi_rvalid      (s_axi_rvalid),
        .s_axi_rready      (s_axi_rready),
        .axi_start_pulse   (axi_start_pulse),
        .axi_reset_pulse   (axi_reset_pulse),
        .regime_from_ps    (regime_from_ps),
        .quote_interval    (quote_interval),
        .lfsr_seed         (lfsr_seed),
        .sym_init_mid      (sym_init_mid),
        .sym_init_spread   (sym_init_spread),
        .sym_sector_id     (sym_sector_id),
        .sym_company_token (sym_company_token),
        .active_sym_count  (active_sym_count),
        .running           (running),
        .link_up           (link_up),
        .active_regime     (active_regime),
        .quotes_sent       (quotes_generated),
        .orders_rcvd       (orders_rcvd),
        .fills_sent        (fills_sent),
        .rejects_sent      (rejects_sent),
        .link_errors       (link_errors),
        .fifo_fill         (fifo_fill_level)
    );

    board_a_ctrl u_ctrl (
        .clk               (clk),
        .rst_n             (rst_n),
        .btn               (btn),
        .sw                (sw),
        .ctrl_start_pulse  (ctrl_start_pulse),
        .ctrl_stop_pulse   (ctrl_stop_pulse),
        .ctrl_reset_pulse  (ctrl_reset_pulse),
        .regime_sw         (regime_sw),
        .sw_override       (sw_override),
        .running           (running),
        .active_regime     (active_regime),
        .link_up           (link_up),
        .link_error        (link_errors != '0),
        .led               (led),
        .rgb0              (rgb0),
        .rgb1              (rgb1)
    );

    market_sim #(
        .NUM_SYM(NUM_SYM)
    ) u_market_sim (
        .clk               (clk),
        .rst_n             (rst_n),
        .enable            (running),
        .counter_clr       (counter_clr),
        .lfsr_load         (lfsr_load),
        .lfsr_seed         (lfsr_seed),
        .active_regime     (active_regime),
        .quote_interval    (quote_interval),
        .active_sym_count  (active_sym_count),
        .sector_id         (sym_sector_id),
        .init_mid          (sym_init_mid),
        .init_spread       (sym_init_spread),
        .quote_frame       (quote_frame),
        .quote_valid       (quote_valid_ms),
        .quote_ready       (quote_ready_ms),
        .best_bid          (best_bid),
        .best_ask          (best_ask),
        .quotes_generated  (quotes_generated)
    );

    sync_fifo #(
        .DATA_W(128),
        .DEPTH(64),
        .ALMOST_FULL_THRESH(60)
    ) u_quote_fifo (
        .clk         (clk),
        .rst_n       (rst_n),
        .flush       (fifo_flush),
        .wr_en       (quote_fifo_wr_en),
        .wr_data     (quote_frame),
        .full        (quote_fifo_full),
        .rd_en       (quote_fifo_rd_en),
        .rd_data     (quote_frame_fifo),
        .empty       (quote_fifo_empty),
        .almost_full (quote_fifo_af_unused),
        .count       (quote_fifo_count)
    );

    exchange_lite #(
        .NUM_SYM(NUM_SYM)
    ) u_exchange_lite (
        .clk          (clk),
        .rst_n        (rst_n),
        .enable       (exchange_enable),
        .counter_clr  (counter_clr),
        .best_bid     (best_bid),
        .best_ask     (best_ask),
        .order_frame  (frame_out),
        .order_valid  (order_valid_rx),
        .fill_frame   (fill_frame),
        .fill_valid   (fill_valid),
        .fill_ready   (fill_ready),
        .orders_rcvd  (orders_rcvd),
        .fills_sent   (fills_sent),
        .rejects_sent (rejects_sent)
    );

    tx_arbiter u_tx_arb (
        .clk         (clk),
        .rst_n       (rst_n),
        .fill_frame  (fill_frame),
        .fill_valid  (fill_valid),
        .fill_ready  (fill_ready),
        .quote_frame (quote_frame_fifo),
        .quote_valid (quote_valid_fifo),
        .quote_ready (quote_ready_arb),
        .tx_frame    (tx_frame),
        .tx_valid    (tx_valid),
        .tx_ready    (tx_ready)
    );

    link_tx #(
        .FRAME_W(FRAME_W),
        .DATA_W(LINK_W)
    ) u_link_tx (
        .clk             (clk),
        .rst_n           (rst_n),
        .frame_in        (tx_frame),
        .frame_in_valid  (tx_valid),
        .frame_in_ready  (tx_ready),
        .pmod_data       (pmod_ja),
        .pmod_valid      (pmod_ja_valid),
        .remote_ready    (pmod_ja_ready)
    );

    logic [31:0] rx_error_count;

    link_rx #(
        .FRAME_W(FRAME_W),
        .DATA_W(LINK_W)
    ) u_link_rx (
        .clk             (clk),
        .rst_n           (rst_n),
        .counter_clr     (counter_clr),
        .pmod_data       (pmod_jb),
        .pmod_valid      (pmod_jb_valid),
        .local_ready     (pmod_jb_ready),
        .frame_out       (frame_out),
        .frame_out_valid (frame_out_valid),
        .link_up         (link_up),
        .error_count     (rx_error_count)
    );

    assign link_errors = COUNTER_W'(rx_error_count);

    // -------------------------------------------------------------------------
    // FUTURE IMPROVEMENTS (not in core demo)
    // -------------------------------------------------------------------------
    // 1. Exchange decoupling: small FIFO between link_rx and exchange_lite for
    //    multi-beat / multi-order buffering and cleaner timing closure.
    // 2. Multi-order pipeline: replace single-slot exchange_lite with deeper
    //    or pipelined matching.
    // 3. tx_arbiter fairness: strict fill>quote today; optional weighted or RR.
    // 4. Latency instrumentation: timestamp capture at RX/TX link boundaries.
    // 5. Link layer: CRC / framing robustness / retry (beyond error_count).
    // 6. market_sim: richer sector/volatility coupling if product needs it.
    // 7. STOPPED semantics: if exchange should drain pending orders while quotes
    //    are off, revert exchange_enable to (RUNNING || STOPPED) and document.
    // -------------------------------------------------------------------------

endmodule
