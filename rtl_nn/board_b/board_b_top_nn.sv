// ============================================================================
// Module: board_b_top_nn
// Identical to board_b_top with NN inference integrated:
//   - feature_compute replaced with feature_compute_nn (adds mid_delta, ema_delta)
//   - position_tracker replaced with position_tracker_nn (adds entry_mid, holding_time)
//   - nn_inference instantiated alongside strategy_engine
//   - active_strategy mux routes to nn_inference when STRAT_NN selected (sw[2:1]=01)
//   - current_mid array maintained per symbol for position_tracker_nn
// All other logic is unchanged.
// ============================================================================

`timescale 1ns / 1ps

module board_b_top_nn
    import hft_pkg::*;
#(
    parameter NUM_SYM            = NUM_SYMBOLS,
    parameter LINK_W             = LINK_DATA_W,
    parameter C_S_AXI_ADDR_WIDTH = 9,
    parameter C_S_AXI_DATA_WIDTH = 32
)(
    input  logic        clk,
    input  logic        rst_n,

    input  logic [3:0]  btn,
    input  logic [7:0]  sw,
    output logic [7:0]  led,
    output logic [2:0]  rgb0,
    output logic [2:0]  rgb1,

    input  logic [LINK_W-1:0] pmod_ja,
    input  logic              pmod_ja_valid,
    output logic              pmod_ja_ready,

    output logic [LINK_W-1:0] pmod_jb,
    output logic              pmod_jb_valid,
    input  logic              pmod_jb_ready,

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

    // ── Free-running cycle counter ──────────────────────────────
    timestamp_t cycle_counter;
    always_ff @(posedge clk or negedge rst_n)
        if (!rst_n) cycle_counter <= '0;
        else        cycle_counter <= cycle_counter + 1'b1;

    // ── Internal wires ──────────────────────────────────────────
    b_state_e fsm_state;
    logic order_enable, counter_clr;

    // AXI config
    logic        axi_start_pulse, axi_reset_pulse;
    strategy_e   strategy_sel;
    price_t      threshold;
    logic [ALPHA_W-1:0] ema_alpha;
    qty_t        base_qty;
    logic [POSITION_W-1:0] max_position;
    logic [COUNTER_W-1:0]  max_order_rate;
    price_t      max_loss;

    // Ctrl
    logic   ctrl_start_pulse, ctrl_stop_pulse, ctrl_reset_pulse;
    logic   trading_enable;
    strategy_e strategy_sw;
    logic   sw_strategy_override;

    // Combined triggers
    logic start_combined, reset_combined;
    assign start_combined = axi_start_pulse | ctrl_start_pulse;
    assign reset_combined = axi_reset_pulse | ctrl_reset_pulse;

    // Active strategy
    strategy_e active_strategy;
    assign active_strategy = sw_strategy_override ? strategy_sw : strategy_sel;

    // Link RX
    logic [FRAME_W-1:0] rx_frame;
    logic               rx_frame_valid;
    logic               link_up;
    logic [COUNTER_W-1:0] link_errors;

    // Demux
    logic [FRAME_W-1:0] quote_frame_demux, fill_frame_demux;
    logic               quote_valid_demux,  fill_valid_demux;
    logic [COUNTER_W-1:0] quotes_rcvd, demux_errors;

    // Quote book
    price_t  qb_bid, qb_ask;
    qty_t    qb_bid_size, qb_ask_size;
    symbol_t qb_symbol;
    regime_e qb_regime;
    logic    qb_valid;

    // Feature compute (now from feature_compute_nn)
    price_t  fc_mid, fc_spread, fc_ema;
    sprice_t fc_deviation;
    price_t  fc_bid_out, fc_ask_out;
    symbol_t fc_symbol_out;
    logic    fc_valid;
    sprice_t fc_mid_delta;   // NEW
    sprice_t fc_ema_delta;   // NEW

    // Strategy engine (mean reversion) outputs
    logic    se_valid, se_side;
    price_t  se_price;
    qty_t    se_qty;
    symbol_t se_symbol;

    // NN inference outputs                                        // NEW
    logic    nn_valid, nn_side;                                   // NEW
    price_t  nn_price;                                            // NEW
    qty_t    nn_qty;                                              // NEW
    symbol_t nn_symbol;                                           // NEW

    // Muxed strategy outputs → risk_manager                      // NEW
    logic    strat_valid, strat_side;                             // NEW
    price_t  strat_price;                                         // NEW
    qty_t    strat_qty;                                           // NEW
    symbol_t strat_symbol;                                        // NEW

    // Mux: select NN or mean-reversion based on active_strategy  // NEW
    assign strat_valid  = (active_strategy == STRAT_NN) ? nn_valid  : se_valid;   // NEW
    assign strat_side   = (active_strategy == STRAT_NN) ? nn_side   : se_side;   // NEW
    assign strat_price  = (active_strategy == STRAT_NN) ? nn_price  : se_price;  // NEW
    assign strat_qty    = (active_strategy == STRAT_NN) ? nn_qty    : se_qty;    // NEW
    assign strat_symbol = (active_strategy == STRAT_NN) ? nn_symbol : se_symbol; // NEW

    // Risk manager
    logic    rm_valid, rm_side;
    price_t  rm_price;
    qty_t    rm_qty;
    symbol_t rm_symbol;
    logic    risk_halt;
    logic [COUNTER_W-1:0] risk_rejects;

    // Position tracker outputs (now from position_tracker_nn)
    symbol_t pt_fill_symbol;
    logic    pt_fill_side;
    qty_t    pt_fill_qty;
    logic    pt_fill_notify;

    // Order manager
    logic [FRAME_W-1:0] order_frame;
    logic               order_valid, order_ready;
    logic [COUNTER_W-1:0] orders_sent;

    // Position tracker
    position_t   position [NUM_SYM];
    cash_t       cash;
    sprice_t     total_pnl;
    timestamp_t  ts_echo;
    logic        fill_processed;
    logic [COUNTER_W-1:0] fills_rcvd;

    // NEW: per-symbol entry_mid and holding_time from position_tracker_nn
    price_t     pt_entry_mid    [NUM_SYM];  // NEW
    logic [7:0] pt_holding_time [NUM_SYM];  // NEW

    // NEW: per-symbol current_mid array — updated each time a quote arrives
    // position_tracker_nn needs mid at fill time to seed entry_mid correctly
    price_t current_mid [NUM_SYM];          // NEW

    always_ff @(posedge clk or negedge rst_n) begin  // NEW
        if (!rst_n) begin                             // NEW
            for (int i = 0; i < NUM_SYM; i++)        // NEW
                current_mid[i] <= '0;                // NEW
        end else if (fc_valid) begin                  // NEW
            current_mid[fc_symbol_out] <= fc_mid;    // NEW
        end                                           // NEW
    end                                               // NEW

    // Latency histogram
    logic [HIST_BIN_W-1:0] hist_bins [HIST_BINS];
    logic [COUNTER_W-1:0]  lat_min, lat_max, lat_sum, lat_count;

    // ════════════════════════════════════════════════════════════
    // 5-STATE FSM (unchanged)
    // ════════════════════════════════════════════════════════════
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            fsm_state <= B_RESET;
        end else begin
            if (reset_combined) begin
                fsm_state <= B_RESET;
            end else begin
                unique case (fsm_state)
                    B_RESET:   fsm_state <= B_IDLE;
                    B_IDLE:    if (start_combined && link_up)
                                   fsm_state <= B_ARMED;
                    B_ARMED:   if (start_combined && trading_enable)
                                   fsm_state <= B_TRADING;
                    B_TRADING: begin
                        if (risk_halt)
                            fsm_state <= B_HALTED;
                        else if (ctrl_stop_pulse || !trading_enable)
                            fsm_state <= B_ARMED;
                    end
                    B_HALTED:  ;
                    default:   fsm_state <= B_RESET;
                endcase
            end
        end
    end

    assign order_enable = (fsm_state == B_TRADING);
    assign counter_clr  = (fsm_state == B_RESET);

    // ════════════════════════════════════════════════════════════
    // MODULE INSTANCES
    // ════════════════════════════════════════════════════════════

    // ── AXI Registers (unchanged) ────────────────────────────────
    board_b_axi_regs #(
        .NUM_SYM(NUM_SYM),
        .C_S_AXI_ADDR_WIDTH(C_S_AXI_ADDR_WIDTH),
        .C_S_AXI_DATA_WIDTH(C_S_AXI_DATA_WIDTH)
    ) u_axi_regs (
        .clk(clk), .rst_n(rst_n),
        .s_axi_awaddr(s_axi_awaddr), .s_axi_awprot(s_axi_awprot),
        .s_axi_awvalid(s_axi_awvalid), .s_axi_awready(s_axi_awready),
        .s_axi_wdata(s_axi_wdata), .s_axi_wstrb(s_axi_wstrb),
        .s_axi_wvalid(s_axi_wvalid), .s_axi_wready(s_axi_wready),
        .s_axi_bresp(s_axi_bresp), .s_axi_bvalid(s_axi_bvalid), .s_axi_bready(s_axi_bready),
        .s_axi_araddr(s_axi_araddr), .s_axi_arprot(s_axi_arprot),
        .s_axi_arvalid(s_axi_arvalid), .s_axi_arready(s_axi_arready),
        .s_axi_rdata(s_axi_rdata), .s_axi_rresp(s_axi_rresp),
        .s_axi_rvalid(s_axi_rvalid), .s_axi_rready(s_axi_rready),
        .axi_start_pulse(axi_start_pulse), .axi_reset_pulse(axi_reset_pulse),
        .strategy_sel(strategy_sel), .threshold(threshold), .ema_alpha(ema_alpha),
        .base_qty(base_qty), .max_position(max_position),
        .max_order_rate(max_order_rate), .max_loss(max_loss),
        .fsm_state(fsm_state), .link_up(link_up), .risk_halt(risk_halt),
        .active_strategy(active_strategy),
        .quotes_rcvd(quotes_rcvd), .orders_sent(orders_sent),
        .fills_rcvd(fills_rcvd), .risk_rejects(risk_rejects), .link_errors(link_errors),
        .position(position), .cash(cash),
        .hist_bins(hist_bins), .lat_min(lat_min), .lat_max(lat_max),
        .lat_sum(lat_sum), .lat_count(lat_count)
    );

    // ── Physical I/O Controller (unchanged) ─────────────────────
    board_b_ctrl u_ctrl (
        .clk(clk), .rst_n(rst_n),
        .btn(btn), .sw(sw),
        .ctrl_start_pulse(ctrl_start_pulse), .ctrl_stop_pulse(ctrl_stop_pulse),
        .ctrl_reset_pulse(ctrl_reset_pulse),
        .trading_enable(trading_enable), .strategy_sw(strategy_sw),
        .sw_strategy_override(sw_strategy_override),
        .fsm_state(fsm_state), .order_enable(order_enable),
        .risk_halt(risk_halt), .link_up(link_up), .total_pnl(total_pnl),
        .led(led), .rgb0(rgb0), .rgb1(rgb1)
    );

    // ── Link RX (unchanged) ─────────────────────────────────────
    link_rx #(
        .FRAME_W(FRAME_W), .DATA_W(LINK_W)
    ) u_link_rx (
        .clk(clk), .rst_n(rst_n),
        .counter_clr(counter_clr),
        .pmod_data(pmod_ja), .pmod_valid(pmod_ja_valid),
        .local_ready(),
        .frame_out(rx_frame), .frame_out_valid(rx_frame_valid),
        .link_up(link_up), .error_count(link_errors)
    );

    assign pmod_ja_ready = 1'b1;

    // ── Message Demux (unchanged) ────────────────────────────────
    msg_demux u_demux (
        .clk(clk), .rst_n(rst_n), .clear(counter_clr),
        .frame_in(rx_frame), .frame_in_valid(rx_frame_valid),
        .quote_frame(quote_frame_demux), .quote_valid(quote_valid_demux),
        .fill_frame(fill_frame_demux), .fill_valid(fill_valid_demux),
        .quotes_rcvd(quotes_rcvd), .demux_errors(demux_errors)
    );

    // ── Quote Book (unchanged) ───────────────────────────────────
    quote_book #(.NUM_SYM(NUM_SYM)) u_quote_book (
        .clk(clk), .rst_n(rst_n),
        .quote_frame(quote_frame_demux), .quote_valid(quote_valid_demux),
        .bid_price(qb_bid), .ask_price(qb_ask),
        .bid_size(qb_bid_size), .ask_size(qb_ask_size),
        .symbol_id(qb_symbol), .regime(qb_regime), .book_valid(qb_valid)
    );

    // ── Feature Compute (NEW: feature_compute_nn) ───────────────
    feature_compute_nn #(.NUM_SYM(NUM_SYM)) u_feature (
        .clk(clk), .rst_n(rst_n), .clear(counter_clr),
        .bid_price(qb_bid), .ask_price(qb_ask),
        .symbol_id(qb_symbol), .book_valid(qb_valid),
        .ema_alpha(ema_alpha),
        .mid(fc_mid), .spread(fc_spread), .ema(fc_ema),
        .deviation(fc_deviation),
        .bid_out(fc_bid_out), .ask_out(fc_ask_out),
        .symbol_out(fc_symbol_out), .feature_valid(fc_valid),
        .mid_delta(fc_mid_delta),   // NEW
        .ema_delta(fc_ema_delta)    // NEW
    );

    // ── Strategy Engine — mean reversion (unchanged) ─────────────
    strategy_engine u_strategy (
        .clk(clk), .rst_n(rst_n),
        .deviation(fc_deviation),
        .bid_price(fc_bid_out), .ask_price(fc_ask_out),
        .symbol_id(fc_symbol_out), .feature_valid(fc_valid),
        .threshold(threshold), .base_qty(base_qty),
        .signal_valid(se_valid), .signal_side(se_side),
        .signal_price(se_price), .signal_qty(se_qty),
        .signal_symbol(se_symbol)
    );

    // ── NN Inference (NEW) ───────────────────────────────────────
    nn_inference u_nn (                                           // NEW
        .clk(clk), .rst_n(rst_n),                                // NEW
        .deviation(fc_deviation),                                 // NEW
        .bid_price(fc_bid_out), .ask_price(fc_ask_out),          // NEW
        .symbol_id(fc_symbol_out), .feature_valid(fc_valid),     // NEW
        .base_qty(base_qty),                                      // NEW
        .spread(fc_spread),                                       // NEW
        .mid_delta(fc_mid_delta),                                 // NEW
        .ema_delta(fc_ema_delta),                                 // NEW
        .position(position[fc_symbol_out]),                       // NEW
        .regime(qb_regime),                                       // NEW
        .entry_mid(pt_entry_mid[fc_symbol_out]),                  // NEW
        .holding_time(pt_holding_time[fc_symbol_out]),            // NEW
        .max_position(max_position),                              // NEW
        .signal_valid(nn_valid), .signal_side(nn_side),          // NEW
        .signal_price(nn_price), .signal_qty(nn_qty),            // NEW
        .signal_symbol(nn_symbol)                                 // NEW
    );                                                            // NEW

    // ── Risk Manager (now uses strat_* mux) ─────────────────────
    risk_manager #(.NUM_SYM(NUM_SYM)) u_risk (
        .clk(clk), .rst_n(rst_n), .clear(counter_clr),
        .order_enable(order_enable),
        .signal_valid(strat_valid),    // CHANGED: was se_valid
        .signal_side(strat_side),      // CHANGED: was se_side
        .signal_price(strat_price),    // CHANGED: was se_price
        .signal_qty(strat_qty),        // CHANGED: was se_qty
        .signal_symbol(strat_symbol),  // CHANGED: was se_symbol
        .position(position), .total_pnl(total_pnl),
        .max_position(max_position), .max_order_rate(max_order_rate),
        .max_loss(max_loss),
        .approved_valid(rm_valid), .approved_side(rm_side),
        .approved_price(rm_price), .approved_qty(rm_qty),
        .approved_symbol(rm_symbol),
        .fill_valid(pt_fill_notify), .fill_symbol(pt_fill_symbol),
        .fill_side(pt_fill_side), .fill_qty(pt_fill_qty),
        .risk_halt(risk_halt), .risk_rejects(risk_rejects)
    );

    // ── Order Manager (unchanged) ────────────────────────────────
    order_manager u_order_mgr (
        .clk(clk), .rst_n(rst_n), .clear(counter_clr),
        .approved_valid(rm_valid), .approved_side(rm_side),
        .approved_price(rm_price), .approved_qty(rm_qty),
        .approved_symbol(rm_symbol),
        .cycle_counter(cycle_counter),
        .order_frame(order_frame), .order_valid(order_valid),
        .order_ready(order_ready),
        .orders_sent(orders_sent)
    );

    // ── Link TX (unchanged) ──────────────────────────────────────
    link_tx #(
        .FRAME_W(FRAME_W), .DATA_W(LINK_W)
    ) u_link_tx (
        .clk(clk), .rst_n(rst_n),
        .frame_in(order_frame), .frame_in_valid(order_valid),
        .frame_in_ready(order_ready),
        .pmod_data(pmod_jb), .pmod_valid(pmod_jb_valid),
        .remote_ready(pmod_jb_ready)
    );

    // ── Position Tracker (NEW: position_tracker_nn) ──────────────
    position_tracker_nn #(.NUM_SYM(NUM_SYM)) u_pos_tracker (    // NEW
        .clk(clk), .rst_n(rst_n), .clear(counter_clr),
        .fill_frame(fill_frame_demux), .fill_valid(fill_valid_demux),
        .current_mid(current_mid),                               // NEW
        .feature_valid_in(fc_valid),                             // NEW
        .feature_symbol_in(fc_symbol_out),                       // NEW
        .position(position), .cash(cash), .total_pnl(total_pnl),
        .ts_echo(ts_echo), .fill_processed(fill_processed),
        .fill_symbol_out(pt_fill_symbol), .fill_side_out(pt_fill_side),
        .fill_qty_out(pt_fill_qty), .fill_notify(pt_fill_notify),
        .fills_rcvd(fills_rcvd),
        .entry_mid(pt_entry_mid),                                // NEW
        .holding_time(pt_holding_time)                           // NEW
    );

    // ── Latency Histogram (unchanged) ────────────────────────────
    latency_histogram u_lat_hist (
        .clk(clk), .rst_n(rst_n), .clear(counter_clr),
        .fill_processed(fill_processed), .ts_echo(ts_echo),
        .cycle_counter(cycle_counter),
        .hist_bins(hist_bins),
        .lat_min(lat_min), .lat_max(lat_max),
        .lat_sum(lat_sum), .lat_count(lat_count)
    );

endmodule