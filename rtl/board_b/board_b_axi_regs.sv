// ============================================================================
// Module: board_b_axi_regs
// AXI-Lite slave register interface for Board B.
//
// Config registers (write):
//   0x00 CTRL         — bit[0]=start pulse, bit[1]=reset pulse
//   0x04 STRATEGY_SEL — [1:0] strategy enum
//   0x08 THRESHOLD    — Q16.16 deviation threshold
//   0x0C EMA_ALPHA    — Q0.16 smoothing factor
//   0x10 BASE_QTY     — order quantity
//   0x14 MAX_POSITION — per-symbol position limit
//   0x18 MAX_ORDER_RATE — orders per session
//   0x1C MAX_LOSS     — Q16.16 loss threshold
//
// Status registers (read-only):
//   0x40 STATUS       — {risk_halt, link_up, fsm_state[2:0], active_strategy[1:0]}
//   0x44 QUOTES_RCVD
//   0x48 ORDERS_SENT
//   0x4C FILLS_RCVD
//   0x50 RISK_REJECTS
//   0x54 LINK_ERRORS
//   0x58..0x94 POS_SYM[0..15] — per-symbol position (NUM_SYM words)
//   0x98 CASH_LO      — cash[31:0]
//   0x9C CASH_HI      — cash[47:32] sign-extended to 32 bits
//   0xA0..0xDC HIST_BIN[0..15]
//   0xE0 LAT_MIN
//   0xE4 LAT_MAX
//   0xE8 LAT_SUM
//   0xEC LAT_COUNT
// ============================================================================

`timescale 1ns / 1ps

module board_b_axi_regs
    import hft_pkg::*;
#(
    parameter NUM_SYM            = NUM_SYMBOLS,
    parameter C_S_AXI_ADDR_WIDTH = 9,
    parameter C_S_AXI_DATA_WIDTH = 32
)(
    input  logic        clk,
    input  logic        rst_n,

    // AXI-Lite Slave
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
    input  logic                           s_axi_rready,

    // Config outputs
    output logic                  axi_start_pulse,
    output logic                  axi_reset_pulse,
    output strategy_e             strategy_sel,
    output price_t                threshold,
    output logic [ALPHA_W-1:0]    ema_alpha,
    output qty_t                  base_qty,
    output logic [POSITION_W-1:0] max_position,
    output logic [COUNTER_W-1:0]  max_order_rate,
    output price_t                max_loss,

    // Status inputs
    input  b_state_e              fsm_state,
    input  logic                  link_up,
    input  logic                  risk_halt,
    input  strategy_e             active_strategy,
    input  logic [COUNTER_W-1:0]  quotes_rcvd,
    input  logic [COUNTER_W-1:0]  orders_sent,
    input  logic [COUNTER_W-1:0]  fills_rcvd,
    input  logic [COUNTER_W-1:0]  risk_rejects,
    input  logic [COUNTER_W-1:0]  link_errors,
    input  position_t             position     [NUM_SYM],
    input  cash_t                 cash,
    input  logic [HIST_BIN_W-1:0] hist_bins    [HIST_BINS],
    input  logic [COUNTER_W-1:0]  lat_min,
    input  logic [COUNTER_W-1:0]  lat_max,
    input  logic [COUNTER_W-1:0]  lat_sum,
    input  logic [COUNTER_W-1:0]  lat_count
);

    // ── Address constants ───────────────────────────────────────
    localparam logic [8:0] ADDR_CTRL          = 9'h000;
    localparam logic [8:0] ADDR_STRATEGY_SEL  = 9'h004;
    localparam logic [8:0] ADDR_THRESHOLD     = 9'h008;
    localparam logic [8:0] ADDR_EMA_ALPHA     = 9'h00C;
    localparam logic [8:0] ADDR_BASE_QTY      = 9'h010;
    localparam logic [8:0] ADDR_MAX_POSITION  = 9'h014;
    localparam logic [8:0] ADDR_MAX_ORD_RATE  = 9'h018;
    localparam logic [8:0] ADDR_MAX_LOSS      = 9'h01C;

    localparam logic [8:0] ADDR_STATUS        = 9'h040;
    localparam logic [8:0] ADDR_QUOTES_RCVD   = 9'h044;
    localparam logic [8:0] ADDR_ORDERS_SENT   = 9'h048;
    localparam logic [8:0] ADDR_FILLS_RCVD    = 9'h04C;
    localparam logic [8:0] ADDR_RISK_REJECTS  = 9'h050;
    localparam logic [8:0] ADDR_LINK_ERRORS   = 9'h054;
    localparam logic [8:0] ADDR_POS_BASE      = 9'h058; // +4*i, 16 symbols → 0x058..0x094
    localparam logic [8:0] ADDR_CASH_LO       = 9'h098;
    localparam logic [8:0] ADDR_CASH_HI       = 9'h09C;
    localparam logic [8:0] ADDR_HIST_BASE     = 9'h0A0; // +4*i, 16 bins → 0x0A0..0x0DC
    localparam logic [8:0] ADDR_LAT_MIN       = 9'h0E0;
    localparam logic [8:0] ADDR_LAT_MAX       = 9'h0E4;
    localparam logic [8:0] ADDR_LAT_SUM       = 9'h0E8;
    localparam logic [8:0] ADDR_LAT_COUNT     = 9'h0EC;

    // ── AXI handshake ───────────────────────────────────────────
    logic write_fire, read_fire;
    logic [8:0] wr_addr, rd_addr;

    assign wr_addr    = s_axi_awaddr;
    assign rd_addr    = s_axi_araddr;
    assign write_fire = s_axi_awvalid && s_axi_wvalid && !s_axi_bvalid;
    assign read_fire  = s_axi_arvalid && !s_axi_rvalid;

    assign s_axi_awready = !s_axi_bvalid;
    assign s_axi_wready  = !s_axi_bvalid;
    assign s_axi_bresp   = 2'b00;
    assign s_axi_arready = !s_axi_rvalid;
    assign s_axi_rresp   = 2'b00;

    // Combinational read mux — avoids dynamic indexing in always_ff
    logic [31:0] rd_data_mux;
    always_comb begin
        rd_data_mux = 32'h0;

        if      (rd_addr == ADDR_CTRL)          rd_data_mux = 32'h0;
        else if (rd_addr == ADDR_STRATEGY_SEL)  rd_data_mux = {30'b0, strategy_sel};
        else if (rd_addr == ADDR_THRESHOLD)     rd_data_mux = threshold;
        else if (rd_addr == ADDR_EMA_ALPHA)     rd_data_mux = {16'b0, ema_alpha};
        else if (rd_addr == ADDR_BASE_QTY)      rd_data_mux = {16'b0, base_qty};
        else if (rd_addr == ADDR_MAX_POSITION)  rd_data_mux = max_position;
        else if (rd_addr == ADDR_MAX_ORD_RATE)  rd_data_mux = max_order_rate;
        else if (rd_addr == ADDR_MAX_LOSS)      rd_data_mux = max_loss;
        else if (rd_addr == ADDR_STATUS)
            rd_data_mux = {25'b0, risk_halt, link_up, fsm_state, active_strategy};
        else if (rd_addr == ADDR_QUOTES_RCVD)   rd_data_mux = quotes_rcvd;
        else if (rd_addr == ADDR_ORDERS_SENT)   rd_data_mux = orders_sent;
        else if (rd_addr == ADDR_FILLS_RCVD)    rd_data_mux = fills_rcvd;
        else if (rd_addr == ADDR_RISK_REJECTS)  rd_data_mux = risk_rejects;
        else if (rd_addr == ADDR_LINK_ERRORS)   rd_data_mux = link_errors;
        else if (rd_addr == ADDR_CASH_LO)       rd_data_mux = cash[31:0];
        else if (rd_addr == ADDR_CASH_HI)       rd_data_mux = {{16{cash[47]}}, cash[47:32]};
        else if (rd_addr == ADDR_LAT_MIN)       rd_data_mux = lat_min;
        else if (rd_addr == ADDR_LAT_MAX)       rd_data_mux = lat_max;
        else if (rd_addr == ADDR_LAT_SUM)       rd_data_mux = lat_sum;
        else if (rd_addr == ADDR_LAT_COUNT)     rd_data_mux = lat_count;

        for (int i = 0; i < NUM_SYM; i++)
            if (rd_addr == 9'(ADDR_POS_BASE + 4*i))
                rd_data_mux = position[i];

        for (int i = 0; i < HIST_BINS; i++)
            if (rd_addr == 9'(ADDR_HIST_BASE + 4*i))
                rd_data_mux = hist_bins[i];
    end

    // ── Write + Read logic ──────────────────────────────────────
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            axi_start_pulse <= 1'b0;
            axi_reset_pulse <= 1'b0;
            strategy_sel    <= STRAT_MEAN_REV;
            threshold       <= 32'h0001_0000;
            ema_alpha       <= 16'd6554;
            base_qty        <= 16'd100;
            max_position    <= 32'd500;
            max_order_rate  <= 32'd1000;
            max_loss        <= 32'd100;
            s_axi_bvalid    <= 1'b0;
            s_axi_rvalid    <= 1'b0;
            s_axi_rdata     <= '0;
        end else begin
            axi_start_pulse <= 1'b0;
            axi_reset_pulse <= 1'b0;

            // ── Write path ──────────────────────────────────────
            if (write_fire) begin
                case (wr_addr)
                    ADDR_CTRL: begin
                        axi_start_pulse <= s_axi_wdata[0];
                        axi_reset_pulse <= s_axi_wdata[1];
                    end
                    ADDR_STRATEGY_SEL: strategy_sel   <= strategy_e'(s_axi_wdata[1:0]);
                    ADDR_THRESHOLD:    threshold      <= s_axi_wdata;
                    ADDR_EMA_ALPHA:    ema_alpha       <= s_axi_wdata[ALPHA_W-1:0];
                    ADDR_BASE_QTY:     base_qty        <= s_axi_wdata[QTY_W-1:0];
                    ADDR_MAX_POSITION: max_position    <= s_axi_wdata;
                    ADDR_MAX_ORD_RATE: max_order_rate  <= s_axi_wdata;
                    ADDR_MAX_LOSS:     max_loss        <= s_axi_wdata;
                    default: ;
                endcase
                s_axi_bvalid <= 1'b1;
            end else if (s_axi_bvalid && s_axi_bready) begin
                s_axi_bvalid <= 1'b0;
            end

            // ── Read path ───────────────────────────────────────
            if (read_fire) begin
                s_axi_rdata  <= rd_data_mux;
                s_axi_rvalid <= 1'b1;
            end else if (s_axi_rvalid && s_axi_rready) begin
                s_axi_rvalid <= 1'b0;
            end
        end
    end

endmodule
