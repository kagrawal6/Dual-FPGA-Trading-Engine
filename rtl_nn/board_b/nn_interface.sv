// ============================================================================
// Module: nn_inference
// Fully parallel neural network inference — drop-in replacement for
// strategy_engine. Implements ProfitPolicyNet (9→128→128→64→3).
//
// Fixed-point format:
//   Weights/biases: signed 8-bit, scale=64 (from policy_weights.sv)
//   Activations:    signed 16-bit
//   Accumulators:   signed 24-bit (8+16)
//   Renormalize:    right-shift by 6 after each layer
//
// Pipeline: 4 registered stages, fully unrolled (one per layer).
//   Latency:    4 clock cycles
//   Throughput: 1 decision per clock cycle
//
// Compatible with ModelSim 2020 — no 'automatic' variables inside
// procedural blocks. All temporaries declared at module scope.
// ============================================================================

`timescale 1ns / 1ps

module nn_inference
    import hft_pkg::*;
    import policy_net_pkg::*;
(
    input  logic        clk,
    input  logic        rst_n,

    // ── Ports matching strategy_engine exactly ───────────────────
    input  sprice_t     deviation,
    input  price_t      bid_price,
    input  price_t      ask_price,
    input  symbol_t     symbol_id,
    input  logic        feature_valid,
    input  qty_t        base_qty,

    // ── Additional ports for 9-feature vector ────────────────────
    input  price_t      spread,
    input  sprice_t     mid_delta,
    input  sprice_t     ema_delta,
    input  signed [31:0] position,
    input  logic [1:0]  regime,
    input  sprice_t     entry_mid,
    input  logic [7:0]  holding_time,
    input  logic [31:0] max_position,

    // ── Outputs matching strategy_engine exactly ──────────────────
    output logic        signal_valid,
    output logic        signal_side,
    output price_t      signal_price,
    output qty_t        signal_qty,
    output symbol_t     signal_symbol
);

    // ============================================================
    // CONSTANTS
    // ============================================================
    localparam int SCALE     = 64;
    localparam int LOG2SCALE = 6;
    localparam int WBITS     = 8;
    localparam int ABITS     = 16;
    localparam int MACBITS   = 24;

    localparam logic [1:0] ACT_HOLD = 2'd0;
    localparam logic [1:0] ACT_BUY  = 2'd1;
    localparam logic [1:0] ACT_SELL = 2'd2;

    // ============================================================
    // FEATURE EXTRACTION — combinational
    // All temporaries declared at module scope (ModelSim 2020)
    // ============================================================
    logic signed [ABITS-1:0] feat [0:8];

    // Temporaries for feat[4] position_norm
    logic signed [31:0] pos_scaled;
    assign pos_scaled = (max_position != '0) ?
                        ($signed(position) * SCALE) / $signed(max_position) : '0;

    // Temporaries for feat[6] dev_spread_ratio
    logic signed [31:0] dev_spread;
    assign dev_spread = (spread != '0) ?
                        ($signed(deviation) * SCALE) / $signed({1'b0, spread}) : '0;

    // Temporaries for feat[7] entry_price_delta
    logic signed [31:0] cur_mid2;
    logic signed [31:0] delta2;
    logic signed [31:0] entry_delta;
    assign cur_mid2     = $signed({1'b0, bid_price}) + $signed({1'b0, ask_price});
    assign delta2       = cur_mid2 - ($signed(entry_mid) <<< 1);
    assign entry_delta  = (position < 0) ? -delta2 : delta2;

    logic signed [31:0] entry_price_delta_raw;
    assign entry_price_delta_raw =
        (position != '0 && spread != '0 && entry_mid != '0) ?
        (entry_delta * SCALE) / ($signed({1'b0, spread}) <<< 1) : '0;

    // Clip function implemented as continuous assignments per feature
    function automatic signed [ABITS-1:0] clip16(input signed [31:0] x);
        localparam signed [31:0] HI =  4 * SCALE;
        localparam signed [31:0] LO = -4 * SCALE;
        if      (x > HI) clip16 = signed'(16'(signed'(HI)));
        else if (x < LO) clip16 = signed'(16'(signed'(LO)));
        else             clip16 = x[ABITS-1:0];
    endfunction

    always_comb begin : feat_extract
        feat[0] = clip16($signed(deviation) >>> 11);
        feat[1] = clip16($signed({1'b0, spread}) >>> 9);
        feat[2] = clip16($signed(mid_delta) >>> 10);
        feat[3] = clip16($signed(ema_delta) >>> 9);
        feat[4] = clip16(pos_scaled);
        case (regime)
            2'd0: feat[5] = -16'sd64;
            2'd1: feat[5] = -16'sd21;
            2'd2: feat[5] =  16'sd21;
            2'd3: feat[5] =  16'sd64;
            default: feat[5] = '0;
        endcase
        feat[6] = clip16(dev_spread);
        feat[7] = clip16(entry_price_delta_raw);
        feat[8] = clip16(($signed({24'b0, holding_time}) * SCALE) / 20);
    end

    // ============================================================
    // STAGE 1 — Layer 0: Linear(9→128) + ReLU
    // acc declared as module-level array, computed combinationally
    // then registered.
    // ============================================================
    logic signed [MACBITS-1:0] l0_acc [0:127];
    logic signed [ABITS-1:0]   h0     [0:127];
    logic                      h0_valid;
    price_t                    h0_bid, h0_ask;
    qty_t                      h0_qty;
    symbol_t                   h0_sym;

    genvar gi, gj;

    // Combinational MAC for layer 0
    generate
        for (gi = 0; gi < 128; gi++) begin : l0_mac
            logic signed [MACBITS-1:0] l0_sum;
            always_comb begin
                l0_sum = {{(MACBITS-WBITS){L0_B[gi][WBITS-1]}}, L0_B[gi]};
                for (int j = 0; j < 9; j++)
                    l0_sum += {{(MACBITS-WBITS){L0_W[gi*9+j][WBITS-1]}}, L0_W[gi*9+j]} *
                              {{(MACBITS-ABITS){feat[j][ABITS-1]}}, feat[j]};
                l0_acc[gi] = l0_sum >>> LOG2SCALE;
            end
        end
    endgenerate

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            h0_valid <= 1'b0;
            for (int i = 0; i < 128; i++) h0[i] <= '0;
        end else begin
            h0_valid <= feature_valid;
            h0_bid   <= bid_price;
            h0_ask   <= ask_price;
            h0_qty   <= base_qty;
            h0_sym   <= symbol_id;
            if (feature_valid) begin
                for (int i = 0; i < 128; i++)
                    h0[i] <= l0_acc[i][MACBITS-1] ? '0 :
                              (l0_acc[i] > 24'sh007FFF) ? 16'sh7FFF :
                              l0_acc[i][ABITS-1:0];
            end
        end
    end

    // ============================================================
    // STAGE 2 — Layer 1: Linear(128→128) + ReLU
    // ============================================================
    logic signed [MACBITS-1:0] l1_acc [0:127];
    logic signed [ABITS-1:0]   h1     [0:127];
    logic                      h1_valid;
    price_t                    h1_bid, h1_ask;
    qty_t                      h1_qty;
    symbol_t                   h1_sym;

    generate
        for (gi = 0; gi < 128; gi++) begin : l1_mac
            logic signed [MACBITS-1:0] l1_sum;
            always_comb begin
                l1_sum = {{(MACBITS-WBITS){L1_B[gi][WBITS-1]}}, L1_B[gi]};
                for (int j = 0; j < 128; j++)
                    l1_sum += {{(MACBITS-WBITS){L1_W[gi*128+j][WBITS-1]}}, L1_W[gi*128+j]} *
                              {{(MACBITS-ABITS){h0[j][ABITS-1]}}, h0[j]};
                l1_acc[gi] = l1_sum >>> LOG2SCALE;
            end
        end
    endgenerate

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            h1_valid <= 1'b0;
            for (int i = 0; i < 128; i++) h1[i] <= '0;
        end else begin
            h1_valid <= h0_valid;
            h1_bid   <= h0_bid;
            h1_ask   <= h0_ask;
            h1_qty   <= h0_qty;
            h1_sym   <= h0_sym;
            if (h0_valid) begin
                for (int i = 0; i < 128; i++)
                    h1[i] <= l1_acc[i][MACBITS-1] ? '0 :
                              (l1_acc[i] > 24'sh007FFF) ? 16'sh7FFF :
                              l1_acc[i][ABITS-1:0];
            end
        end
    end

    // ============================================================
    // STAGE 3 — Layer 2: Linear(128→64) + ReLU
    // ============================================================
    logic signed [MACBITS-1:0] l2_acc [0:63];
    logic signed [ABITS-1:0]   h2     [0:63];
    logic                      h2_valid;
    price_t                    h2_bid, h2_ask;
    qty_t                      h2_qty;
    symbol_t                   h2_sym;

    generate
        for (gi = 0; gi < 64; gi++) begin : l2_mac
            logic signed [MACBITS-1:0] l2_sum;
            always_comb begin
                l2_sum = {{(MACBITS-WBITS){L2_B[gi][WBITS-1]}}, L2_B[gi]};
                for (int j = 0; j < 128; j++)
                    l2_sum += {{(MACBITS-WBITS){L2_W[gi*128+j][WBITS-1]}}, L2_W[gi*128+j]} *
                              {{(MACBITS-ABITS){h1[j][ABITS-1]}}, h1[j]};
                l2_acc[gi] = l2_sum >>> LOG2SCALE;
            end
        end
    endgenerate

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            h2_valid <= 1'b0;
            for (int i = 0; i < 64; i++) h2[i] <= '0;
        end else begin
            h2_valid <= h1_valid;
            h2_bid   <= h1_bid;
            h2_ask   <= h1_ask;
            h2_qty   <= h1_qty;
            h2_sym   <= h1_sym;
            if (h1_valid) begin
                for (int i = 0; i < 64; i++)
                    h2[i] <= l2_acc[i][MACBITS-1] ? '0 :
                              (l2_acc[i] > 24'sh007FFF) ? 16'sh7FFF :
                              l2_acc[i][ABITS-1:0];
            end
        end
    end

    // ============================================================
    // STAGE 4 — Layer 3: Linear(64→3) → argmax → outputs
    // ============================================================
    logic signed [MACBITS-1:0] logit [0:2];
    logic [1:0]                action_comb;

    generate
        for (gi = 0; gi < 3; gi++) begin : l3_mac
            logic signed [MACBITS-1:0] l3_sum;
            always_comb begin
                l3_sum = {{(MACBITS-WBITS){L3_B[gi][WBITS-1]}}, L3_B[gi]};
                for (int j = 0; j < 64; j++)
                    l3_sum += {{(MACBITS-WBITS){L3_W[gi*64+j][WBITS-1]}}, L3_W[gi*64+j]} *
                              {{(MACBITS-ABITS){h2[j][ABITS-1]}}, h2[j]};
                logit[gi] = l3_sum >>> LOG2SCALE;
            end
        end
    endgenerate

    // Combinational argmax
    always_comb begin
        if (logit[ACT_BUY] >= logit[ACT_HOLD] &&
            logit[ACT_BUY] >= logit[ACT_SELL])
            action_comb = ACT_BUY;
        else if (logit[ACT_SELL] >= logit[ACT_HOLD] &&
                 logit[ACT_SELL] >  logit[ACT_BUY])
            action_comb = ACT_SELL;
        else
            action_comb = ACT_HOLD;
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            signal_valid  <= 1'b0;
            signal_side   <= 1'b0;
            signal_price  <= '0;
            signal_qty    <= '0;
            signal_symbol <= '0;
        end else begin
            signal_valid <= 1'b0;
            if (h2_valid) begin
                // Only trade on:
                //   symbols 0-7  (trained symbols — confirmed profitable)
                //   VOLATILE (1) or ADVERSARIAL (3) regimes only
                if (h2_sym < 8 &&
                    (regime == 2'd1 || regime == 2'd3)) begin
                    case (action_comb)
                        ACT_BUY: begin
                            signal_valid  <= 1'b1;
                            signal_side   <= 1'b0;
                            signal_price  <= h2_ask;
                            signal_qty    <= h2_qty;
                            signal_symbol <= h2_sym;
                        end
                        ACT_SELL: begin
                            signal_valid  <= 1'b1;
                            signal_side   <= 1'b1;
                            signal_price  <= h2_bid;
                            signal_qty    <= h2_qty;
                            signal_symbol <= h2_sym;
                        end
                        default: ;
                    endcase
                end
                // symbols 8-15 or CALM/BURST regime → HOLD (signal_valid stays 0)
            end
        end
    end

endmodule