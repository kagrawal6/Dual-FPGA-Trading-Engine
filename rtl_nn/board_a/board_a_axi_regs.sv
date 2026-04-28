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

    assign wr_addr = s_axi_awaddr[7:0];
    assign rd_addr = s_axi_araddr[7:0];

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
        if      (rd_addr == ADDR_QUOTE_INTERVAL) rd_data_mux = quote_interval;
        else if (rd_addr == ADDR_LFSR_SEED)      rd_data_mux = lfsr_seed;
        else if (rd_addr == ADDR_REGIME)          rd_data_mux = {{30{1'b0}}, regime_from_ps};
        else if (rd_addr == ADDR_ACTIVE_CNT)      rd_data_mux = {{24{1'b0}}, active_sym_count};
        else if (rd_addr == ADDR_STATUS)
            rd_data_mux = {16'd0, fifo_fill, 5'd0, active_regime, link_up, running};
        else if (rd_addr == ADDR_QUOTES_SENT)     rd_data_mux = quotes_sent;
        else if (rd_addr == ADDR_ORDERS_RCVD)     rd_data_mux = orders_rcvd;

        for (int i = 0; i < NUM_SYM; i++) begin
            if (rd_addr == 8'(ADDR_INIT_MID_BASE + 4*i))
                rd_data_mux = sym_init_mid[i];
            if (rd_addr == 8'(ADDR_INIT_SPREAD_BASE + 4*i))
                rd_data_mux = sym_init_spread[i];
            if (rd_addr == 8'(ADDR_SECTOR_BASE + 4*i))
                rd_data_mux = {{(32-SECTOR_ID_W){1'b0}}, sym_sector_id[i]};
        end
        for (int j = 0; j < (NUM_SYM+1)/2; j++) begin
            if (rd_addr == 8'(ADDR_TOKEN_BASE + 4*j)) begin
                rd_data_mux[15:0]  = sym_company_token[2*j];
                rd_data_mux[31:16] = ((2*j+1) < NUM_SYM) ? sym_company_token[2*j+1] : 16'h0;
            end
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            axi_start_pulse  <= 1'b0;
            axi_reset_pulse  <= 1'b0;
            regime_from_ps   <= REGIME_CALM;
            quote_interval   <= 32'd1000;
            lfsr_seed        <= 32'hDEAD_BEEF;
            active_sym_count <= (NUM_SYM < 255) ? NUM_SYM[7:0] : 8'd255;
            s_axi_bvalid     <= 1'b0;
            s_axi_rvalid     <= 1'b0;
            s_axi_rdata      <= '0;

            for (int i = 0; i < NUM_SYM; i++) begin
                sym_init_mid[i]      <= '0;
                sym_init_spread[i]   <= 32'h0000_0001;
                sym_sector_id[i]     <= '0;
                sym_company_token[i] <= i[15:0];
            end
        end else begin
            axi_start_pulse <= 1'b0;
            axi_reset_pulse <= 1'b0;

            // ── Scalar register writes ──────────────────────────────
            if (write_fire) begin
                if (wr_addr == ADDR_CTRL) begin
                    axi_start_pulse <= s_axi_wdata[0];
                    axi_reset_pulse <= s_axi_wdata[1];
                end else if (wr_addr == ADDR_QUOTE_INTERVAL) begin
                    quote_interval <= s_axi_wdata;
                end else if (wr_addr == ADDR_LFSR_SEED) begin
                    lfsr_seed <= s_axi_wdata;
                end else if (wr_addr == ADDR_REGIME) begin
                    regime_from_ps <= regime_e'(s_axi_wdata[1:0]);
                end else if (wr_addr == ADDR_ACTIVE_CNT) begin
                    if (s_axi_wdata[7:0] == 8'd0)              active_sym_count <= 8'd1;
                    else if (s_axi_wdata[7:0] > NUM_SYM[7:0])  active_sym_count <= NUM_SYM[7:0];
                    else                                        active_sym_count <= s_axi_wdata[7:0];
                end
                s_axi_bvalid <= 1'b1;
            end else if (s_axi_bvalid && s_axi_bready) begin
                s_axi_bvalid <= 1'b0;
            end

            // ── Per-symbol array writes (for-loop eliminates latches) ─
            for (int i = 0; i < NUM_SYM; i++) begin
                if (write_fire && wr_addr == 8'(ADDR_INIT_MID_BASE + 4*i))
                    sym_init_mid[i] <= price_t'(s_axi_wdata);

                if (write_fire && wr_addr == 8'(ADDR_INIT_SPREAD_BASE + 4*i))
                    sym_init_spread[i] <= price_t'((s_axi_wdata == 32'h0) ? 32'h1 : s_axi_wdata);

                if (write_fire && wr_addr == 8'(ADDR_SECTOR_BASE + 4*i))
                    sym_sector_id[i] <= s_axi_wdata[SECTOR_ID_W-1:0];

                if (write_fire && wr_addr == 8'(ADDR_TOKEN_BASE + 4*(i/2))) begin
                    if (i[0] == 1'b0)
                        sym_company_token[i] <= s_axi_wdata[15:0];
                    else
                        sym_company_token[i] <= s_axi_wdata[31:16];
                end
            end

            // ── Read path ───────────────────────────────────────────
            if (read_fire) begin
                s_axi_rdata  <= rd_data_mux;
                s_axi_rvalid <= 1'b1;
            end else if (s_axi_rvalid && s_axi_rready) begin
                s_axi_rvalid <= 1'b0;
            end
        end
    end

endmodule
