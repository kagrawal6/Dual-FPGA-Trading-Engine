// ============================================================================
// Module: board_a_axi_regs
// AXI-Lite slave register interface for Board A. Provides config registers
// (CTRL, QUOTE_INTERVAL, LFSR_SEED, REGIME, per-symbol init prices) and
// read-only status registers (STATUS, counters). Generates single-cycle
// pulses on CTRL write for start/reset triggers.
// See Appendix D.1 of the design spec for the full register map.
// ============================================================================

`timescale 1ns / 1ps

module board_a_axi_regs
    import hft_pkg::*;
#(
    parameter NUM_SYM            = NUM_SYMBOLS,
    parameter C_S_AXI_ADDR_WIDTH = 8,
    parameter C_S_AXI_DATA_WIDTH = 32
)(
    input  logic        clk,
    input  logic        rst_n,

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
    input  logic                           s_axi_rready,

    // ── Config Outputs (directly drive Board A data plane) ──────────────────
    output logic                           axi_start_pulse,    // 1-cycle pulse on CTRL[0] write
    output logic                           axi_reset_pulse,    // 1-cycle pulse on CTRL[1] write
    output regime_e                        regime_from_ps,      // REGIME register [1:0]
    output logic [31:0]                    quote_interval,      // cycles between quotes
    output logic [31:0]                    lfsr_seed,
    output price_t                         sym_init_mid    [NUM_SYM],
    output price_t                         sym_init_spread [NUM_SYM],
    output logic [SECTOR_ID_W-1:0]         sym_sector_id [NUM_SYM],
    output logic [15:0]                    sym_company_token [NUM_SYM],
    output logic [7:0]                     active_sym_count,

    // ── Status Inputs (from Board A data plane + link) ──────────────────────
    input  logic                           running,
    input  logic                           link_up,
    input  regime_e                        active_regime,
    input  logic [COUNTER_W-1:0]           quotes_sent,
    input  logic [COUNTER_W-1:0]           orders_rcvd,
    input  logic [COUNTER_W-1:0]           fills_sent,
    input  logic [COUNTER_W-1:0]           rejects_sent,
    input  logic [COUNTER_W-1:0]           link_errors,
    input  logic [6:0]                     fifo_fill
);
    // -------------------------------------------------------------------------
    // ADDITION: Extended register map for dynamic symbol metadata (up to NUM_SYM)
    // -------------------------------------------------------------------------
    // These addresses were added to support:
    // - per-symbol init_mid / init_spread
    // - per-symbol sector_id
    // - fixed company tokens
    // - runtime active symbol count
    localparam logic [7:0] ADDR_CTRL             = 8'h00;
    localparam logic [7:0] ADDR_QUOTE_INTERVAL   = 8'h04;
    localparam logic [7:0] ADDR_LFSR_SEED        = 8'h08;
    localparam logic [7:0] ADDR_REGIME           = 8'h0C;
    localparam logic [7:0] ADDR_INIT_MID_BASE    = 8'h10; // +4*i
    localparam logic [7:0] ADDR_INIT_SPREAD_BASE = 8'h50; // +4*i
    localparam logic [7:0] ADDR_SECTOR_BASE      = 8'h90; // +4*i
    localparam logic [7:0] ADDR_TOKEN_BASE       = 8'hD0; // +4*j, two 16b tokens per word
    localparam logic [7:0] ADDR_ACTIVE_CNT       = 8'hF0;
    localparam logic [7:0] ADDR_STATUS           = 8'hF4;
    localparam logic [7:0] ADDR_QUOTES_SENT      = 8'hF8;
    localparam logic [7:0] ADDR_ORDERS_RCVD      = 8'hFC;

    logic write_fire;
    logic read_fire;
    logic [7:0] wr_addr;
    logic [7:0] rd_addr;
    integer i;
    integer idx;
    integer tok_idx;

    assign wr_addr = s_axi_awaddr[7:0];
    assign rd_addr = s_axi_araddr[7:0];

    assign write_fire = s_axi_awvalid && s_axi_wvalid && !s_axi_bvalid;
    assign read_fire  = s_axi_arvalid && !s_axi_rvalid;

    assign s_axi_awready = !s_axi_bvalid;
    assign s_axi_wready  = !s_axi_bvalid;
    assign s_axi_bresp   = 2'b00;
    assign s_axi_arready = !s_axi_rvalid;
    assign s_axi_rresp   = 2'b00;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // ADDITION: reset defaults for new config outputs.
            axi_start_pulse <= 1'b0;
            axi_reset_pulse <= 1'b0;
            regime_from_ps  <= REGIME_CALM;
            quote_interval  <= 32'd1000;
            lfsr_seed       <= 32'hDEAD_BEEF;
            active_sym_count <= (NUM_SYM < 255) ? NUM_SYM[7:0] : 8'd255;
            s_axi_bvalid    <= 1'b0;
            s_axi_rvalid    <= 1'b0;
            s_axi_rdata     <= '0;

            for (i = 0; i < NUM_SYM; i++) begin
                sym_init_mid[i]      <= '0;
                sym_init_spread[i]   <= 32'h0000_0001;
                sym_sector_id[i]     <= '0;
                sym_company_token[i] <= i[15:0];
            end
        end else begin
            axi_start_pulse <= 1'b0;
            axi_reset_pulse <= 1'b0;

            if (write_fire) begin
                // ADDITION: write decode supports extended metadata windows.
                if (wr_addr == ADDR_CTRL) begin
                    axi_start_pulse <= s_axi_wdata[0];
                    axi_reset_pulse <= s_axi_wdata[1];
                end else if (wr_addr == ADDR_QUOTE_INTERVAL) begin
                    quote_interval <= s_axi_wdata;
                end else if (wr_addr == ADDR_LFSR_SEED) begin
                    lfsr_seed <= s_axi_wdata;
                end else if (wr_addr == ADDR_REGIME) begin
                    regime_from_ps <= regime_e'(s_axi_wdata[1:0]);
                end else if ((wr_addr >= ADDR_INIT_MID_BASE) && (wr_addr < (ADDR_INIT_MID_BASE + NUM_SYM*4))) begin
                    idx = (wr_addr - ADDR_INIT_MID_BASE) >> 2;
                    if (idx < NUM_SYM) sym_init_mid[idx] <= price_t'(s_axi_wdata);
                end else if ((wr_addr >= ADDR_INIT_SPREAD_BASE) && (wr_addr < (ADDR_INIT_SPREAD_BASE + NUM_SYM*4))) begin
                    idx = (wr_addr - ADDR_INIT_SPREAD_BASE) >> 2;
                    if (idx < NUM_SYM) sym_init_spread[idx] <= price_t'((s_axi_wdata == 32'h0) ? 32'h1 : s_axi_wdata);
                end else if ((wr_addr >= ADDR_SECTOR_BASE) && (wr_addr < (ADDR_SECTOR_BASE + NUM_SYM*4))) begin
                    idx = (wr_addr - ADDR_SECTOR_BASE) >> 2;
                    if (idx < NUM_SYM) sym_sector_id[idx] <= s_axi_wdata[SECTOR_ID_W-1:0];
                end else if ((wr_addr >= ADDR_TOKEN_BASE) && (wr_addr < (ADDR_TOKEN_BASE + ((NUM_SYM+1)/2)*4))) begin
                    // ADDITION: packed tokens, 2x16b per 32b word.
                    tok_idx = ((wr_addr - ADDR_TOKEN_BASE) >> 2) * 2;
                    if (tok_idx < NUM_SYM) sym_company_token[tok_idx] <= s_axi_wdata[15:0];
                    if ((tok_idx + 1) < NUM_SYM) sym_company_token[tok_idx+1] <= s_axi_wdata[31:16];
                end else if (wr_addr == ADDR_ACTIVE_CNT) begin
                    if (s_axi_wdata[7:0] == 8'd0) active_sym_count <= 8'd1;
                    else if (s_axi_wdata[7:0] > NUM_SYM[7:0]) active_sym_count <= NUM_SYM[7:0];
                    else active_sym_count <= s_axi_wdata[7:0];
                end
                s_axi_bvalid <= 1'b1;
            end else if (s_axi_bvalid && s_axi_bready) begin
                s_axi_bvalid <= 1'b0;
            end

            if (read_fire) begin
                // ADDITION: readback support for all new metadata windows.
                s_axi_rdata <= 32'h0;
                if (rd_addr == ADDR_QUOTE_INTERVAL) begin
                    s_axi_rdata <= quote_interval;
                end else if (rd_addr == ADDR_LFSR_SEED) begin
                    s_axi_rdata <= lfsr_seed;
                end else if (rd_addr == ADDR_REGIME) begin
                    s_axi_rdata <= {{30{1'b0}}, regime_from_ps};
                end else if ((rd_addr >= ADDR_INIT_MID_BASE) && (rd_addr < (ADDR_INIT_MID_BASE + NUM_SYM*4))) begin
                    idx = (rd_addr - ADDR_INIT_MID_BASE) >> 2;
                    if (idx < NUM_SYM) s_axi_rdata <= sym_init_mid[idx];
                end else if ((rd_addr >= ADDR_INIT_SPREAD_BASE) && (rd_addr < (ADDR_INIT_SPREAD_BASE + NUM_SYM*4))) begin
                    idx = (rd_addr - ADDR_INIT_SPREAD_BASE) >> 2;
                    if (idx < NUM_SYM) s_axi_rdata <= sym_init_spread[idx];
                end else if ((rd_addr >= ADDR_SECTOR_BASE) && (rd_addr < (ADDR_SECTOR_BASE + NUM_SYM*4))) begin
                    idx = (rd_addr - ADDR_SECTOR_BASE) >> 2;
                    if (idx < NUM_SYM)
                        s_axi_rdata <= {{(32 - SECTOR_ID_W){1'b0}}, sym_sector_id[idx]};
                end else if ((rd_addr >= ADDR_TOKEN_BASE) && (rd_addr < (ADDR_TOKEN_BASE + ((NUM_SYM+1)/2)*4))) begin
                    tok_idx = ((rd_addr - ADDR_TOKEN_BASE) >> 2) * 2;
                    s_axi_rdata[15:0] <= (tok_idx < NUM_SYM) ? sym_company_token[tok_idx] : 16'h0;
                    s_axi_rdata[31:16] <= ((tok_idx + 1) < NUM_SYM) ? sym_company_token[tok_idx+1] : 16'h0;
                end else if (rd_addr == ADDR_ACTIVE_CNT) begin
                    s_axi_rdata <= {{24{1'b0}}, active_sym_count};
                end else if (rd_addr == ADDR_STATUS) begin
                    // {16 spare, fifo_fill[6:0], 5 spare, regime[1:0], link_up, running} = 32b
                    s_axi_rdata <= {16'd0, fifo_fill, 5'd0, active_regime, link_up, running};
                end else if (rd_addr == ADDR_QUOTES_SENT) begin
                    s_axi_rdata <= quotes_sent;
                end else if (rd_addr == ADDR_ORDERS_RCVD) begin
                    s_axi_rdata <= orders_rcvd;
                end
                s_axi_rvalid <= 1'b1;
            end else if (s_axi_rvalid && s_axi_rready) begin
                s_axi_rvalid <= 1'b0;
            end
        end
    end

endmodule
