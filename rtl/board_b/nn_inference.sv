// ============================================================================
// Module: nn_inference
// Time-multiplexed neural network inference — 9→128→128→64→3.
//
// Key changes vs fully-parallel version:
//   - 4-bit weights (policy_weights_4bit.sv, scale=8)
//   - 4-cycle time-multiplexed MAC pipeline (one quarter of neurons per cycle)
//   - Only trades symbols 0-3 in VOLATILE or ADVERSARIAL regime
//
// Fixed-point format:
//   Weights/biases : signed 4-bit,  scale=8   (policy_weights_4bit.sv)
//   Activations    : signed 16-bit
//   Accumulators   : signed 24-bit
//   Renormalize    : right-shift by 3 (log2(scale=8)) after each layer
//
// Time-multiplexing:
//   Layer 0 (128 neurons) → 32 neurons/cycle × 4 cycles
//   Layer 1 (128 neurons) → 32 neurons/cycle × 4 cycles
//   Layer 2 ( 64 neurons) → 16 neurons/cycle × 4 cycles
//   Layer 3 (  3 neurons) → combinational (tiny)
//   Total latency: ~13 cycles
//
// With 16 symbols at 1000-cycle quote interval:
//   16,000 cycles per rotation — 13 cycles << 16,000
//   Only symbols 0-3 active → 4,000 cycles per symbol
// ============================================================================

`timescale 1ns / 1ps

module nn_inference
    import hft_pkg::*;
    import policy_net_pkg::*;
(
    input  logic        clk,
    input  logic        rst_n,

    input  sprice_t     deviation,
    input  price_t      bid_price,
    input  price_t      ask_price,
    input  symbol_t     symbol_id,
    input  logic        feature_valid,
    input  qty_t        base_qty,

    input  price_t      spread,
    input  sprice_t     mid_delta,
    input  sprice_t     ema_delta,
    input  signed [31:0] position,
    input  logic [1:0]  regime,
    input  sprice_t     entry_mid,
    input  logic [7:0]  holding_time,
    input  logic [31:0] max_position,

    output logic        signal_valid,
    output logic        signal_side,
    output price_t      signal_price,
    output qty_t        signal_qty,
    output symbol_t     signal_symbol
);

    localparam int SCALE     = 8;
    localparam int LOG2SCALE = 3;
    localparam int WBITS     = 4;
    localparam int ABITS     = 16;
    localparam int MACBITS   = 24;
    localparam int L0_SLICE  = 32;
    localparam int L1_SLICE  = 32;
    localparam int L2_SLICE  = 16;

    localparam logic [1:0] ACT_HOLD = 2'd0;
    localparam logic [1:0] ACT_BUY  = 2'd1;
    localparam logic [1:0] ACT_SELL = 2'd2;

    // ── Feature extraction ───────────────────────────────────────
    logic signed [ABITS-1:0] feat [0:8];

    logic signed [31:0] pos_scaled;
    assign pos_scaled = (max_position != '0) ?
                        ($signed(position) * SCALE) / $signed(max_position) : '0;

    logic signed [31:0] dev_spread;
    assign dev_spread = (spread != '0) ?
                        ($signed(deviation) * SCALE) / $signed({1'b0, spread}) : '0;

    logic signed [31:0] cur_mid2, delta2, entry_delta, entry_price_delta_raw;
    assign cur_mid2     = $signed({1'b0, bid_price}) + $signed({1'b0, ask_price});
    assign delta2       = cur_mid2 - ($signed(entry_mid) <<< 1);
    assign entry_delta  = (position < 0) ? -delta2 : delta2;
    assign entry_price_delta_raw =
        (position != '0 && spread != '0 && entry_mid != '0) ?
        (entry_delta * SCALE) / ($signed({1'b0, spread}) <<< 1) : '0;

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
            2'd0: feat[5] = -16'sd8;
            2'd1: feat[5] = -16'sd3;
            2'd2: feat[5] =  16'sd3;
            2'd3: feat[5] =  16'sd8;
            default: feat[5] = '0;
        endcase
        feat[6] = clip16(dev_spread);
        feat[7] = clip16(entry_price_delta_raw);
        feat[8] = clip16(($signed({24'b0, holding_time}) * SCALE) / 20);
    end

    // ── Input capture + phase counter ────────────────────────────
    logic signed [ABITS-1:0] feat_r [0:8];
    price_t                  cap_bid, cap_ask;
    qty_t                    cap_qty;
    symbol_t                 cap_sym;
    logic [1:0]              cap_regime;
    logic [1:0]              phase;
    logic                    computing;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            phase     <= 2'd0;
            computing <= 1'b0;
        end else begin
            if (feature_valid && !computing) begin
                for (int i = 0; i < 9; i++) feat_r[i] <= feat[i];
                cap_bid    <= bid_price;
                cap_ask    <= ask_price;
                cap_qty    <= base_qty;
                cap_sym    <= symbol_id;
                cap_regime <= regime;
                phase      <= 2'd0;
                computing  <= 1'b1;
            end else if (computing) begin
                if (phase == 2'd3) computing <= 1'b0;
                else               phase <= phase + 2'd1;
            end
        end
    end

    // ── Layer 0: 9→128, 32 neurons/cycle ─────────────────────────
    logic signed [ABITS-1:0] h0 [0:127];
    logic                    h0_valid;
    price_t                  h0_bid, h0_ask;
    qty_t                    h0_qty;
    symbol_t                 h0_sym;
    logic [1:0]              h0_regime;

    logic signed [MACBITS-1:0] l0_slice [0:L0_SLICE-1];
    always_comb begin
        for (int gi = 0; gi < L0_SLICE; gi++) begin
            automatic int ni = int'(phase) * L0_SLICE + gi;
            automatic logic signed [MACBITS-1:0] s;
            s = {{(MACBITS-WBITS){L0_B[ni][WBITS-1]}}, L0_B[ni]};
            for (int j = 0; j < 9; j++)
                s += {{(MACBITS-WBITS){L0_W[ni*9+j][WBITS-1]}}, L0_W[ni*9+j]} *
                     {{(MACBITS-ABITS){feat_r[j][ABITS-1]}}, feat_r[j]};
            s = s >>> LOG2SCALE;
            l0_slice[gi] = s[MACBITS-1] ? '0 :
                           (s > 24'sh007FFF) ? 16'sh7FFF : s[ABITS-1:0];
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            h0_valid <= 1'b0;
            for (int i = 0; i < 128; i++) h0[i] <= '0;
        end else if (computing) begin
            for (int gi = 0; gi < L0_SLICE; gi++)
                h0[int'(phase)*L0_SLICE + gi] <= l0_slice[gi];
            if (phase == 2'd3) begin
                h0_valid <= 1'b1; h0_bid <= cap_bid; h0_ask <= cap_ask;
                h0_qty <= cap_qty; h0_sym <= cap_sym; h0_regime <= cap_regime;
            end else h0_valid <= 1'b0;
        end else h0_valid <= 1'b0;
    end

    // ── Layer 1: 128→128, 32 neurons/cycle ───────────────────────
    logic signed [ABITS-1:0] h1 [0:127];
    logic                    h1_valid;
    price_t                  h1_bid, h1_ask;
    qty_t                    h1_qty;
    symbol_t                 h1_sym;
    logic [1:0]              h1_regime;
    logic [1:0]              l1_phase;
    logic                    l1_computing;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin l1_phase <= 2'd0; l1_computing <= 1'b0; end
        else begin
            if (h0_valid && !l1_computing) begin
                l1_phase <= 2'd0; l1_computing <= 1'b1;
            end else if (l1_computing) begin
                if (l1_phase == 2'd3) l1_computing <= 1'b0;
                else l1_phase <= l1_phase + 2'd1;
            end
        end
    end

    logic signed [MACBITS-1:0] l1_slice [0:L1_SLICE-1];
    always_comb begin
        for (int gi = 0; gi < L1_SLICE; gi++) begin
            automatic int ni = int'(l1_phase) * L1_SLICE + gi;
            automatic logic signed [MACBITS-1:0] s;
            s = {{(MACBITS-WBITS){L1_B[ni][WBITS-1]}}, L1_B[ni]};
            for (int j = 0; j < 128; j++)
                s += {{(MACBITS-WBITS){L1_W[ni*128+j][WBITS-1]}}, L1_W[ni*128+j]} *
                     {{(MACBITS-ABITS){h0[j][ABITS-1]}}, h0[j]};
            s = s >>> LOG2SCALE;
            l1_slice[gi] = s[MACBITS-1] ? '0 :
                           (s > 24'sh007FFF) ? 16'sh7FFF : s[ABITS-1:0];
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            h1_valid <= 1'b0;
            for (int i = 0; i < 128; i++) h1[i] <= '0;
        end else if (l1_computing) begin
            for (int gi = 0; gi < L1_SLICE; gi++)
                h1[int'(l1_phase)*L1_SLICE + gi] <= l1_slice[gi];
            if (l1_phase == 2'd3) begin
                h1_valid <= 1'b1; h1_bid <= h0_bid; h1_ask <= h0_ask;
                h1_qty <= h0_qty; h1_sym <= h0_sym; h1_regime <= h0_regime;
            end else h1_valid <= 1'b0;
        end else h1_valid <= 1'b0;
    end

    // ── Layer 2: 128→64, 16 neurons/cycle ────────────────────────
    logic signed [ABITS-1:0] h2 [0:63];
    logic                    h2_valid;
    price_t                  h2_bid, h2_ask;
    qty_t                    h2_qty;
    symbol_t                 h2_sym;
    logic [1:0]              h2_regime;
    logic [1:0]              l2_phase;
    logic                    l2_computing;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin l2_phase <= 2'd0; l2_computing <= 1'b0; end
        else begin
            if (h1_valid && !l2_computing) begin
                l2_phase <= 2'd0; l2_computing <= 1'b1;
            end else if (l2_computing) begin
                if (l2_phase == 2'd3) l2_computing <= 1'b0;
                else l2_phase <= l2_phase + 2'd1;
            end
        end
    end

    logic signed [MACBITS-1:0] l2_slice [0:L2_SLICE-1];
    always_comb begin
        for (int gi = 0; gi < L2_SLICE; gi++) begin
            automatic int ni = int'(l2_phase) * L2_SLICE + gi;
            automatic logic signed [MACBITS-1:0] s;
            s = {{(MACBITS-WBITS){L2_B[ni][WBITS-1]}}, L2_B[ni]};
            for (int j = 0; j < 128; j++)
                s += {{(MACBITS-WBITS){L2_W[ni*128+j][WBITS-1]}}, L2_W[ni*128+j]} *
                     {{(MACBITS-ABITS){h1[j][ABITS-1]}}, h1[j]};
            s = s >>> LOG2SCALE;
            l2_slice[gi] = s[MACBITS-1] ? '0 :
                           (s > 24'sh007FFF) ? 16'sh7FFF : s[ABITS-1:0];
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            h2_valid <= 1'b0;
            for (int i = 0; i < 64; i++) h2[i] <= '0;
        end else if (l2_computing) begin
            for (int gi = 0; gi < L2_SLICE; gi++)
                h2[int'(l2_phase)*L2_SLICE + gi] <= l2_slice[gi];
            if (l2_phase == 2'd3) begin
                h2_valid <= 1'b1; h2_bid <= h1_bid; h2_ask <= h1_ask;
                h2_qty <= h1_qty; h2_sym <= h1_sym; h2_regime <= h1_regime;
            end else h2_valid <= 1'b0;
        end else h2_valid <= 1'b0;
    end

    // ── Layer 3: 64→3, combinational ─────────────────────────────
    logic signed [MACBITS-1:0] logit [0:2];
    logic [1:0]                action_comb;

    generate
        for (genvar gi = 0; gi < 3; gi++) begin : l3_mac
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

    // ── Output gate: sym 0-3, VOLATILE/ADVERSARIAL only ──────────
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            signal_valid  <= 1'b0;
            signal_side   <= 1'b0;
            signal_price  <= '0;
            signal_qty    <= '0;
            signal_symbol <= '0;
        end else begin
            signal_valid <= 1'b0;
            if (h2_valid &&
                h2_sym < 4 &&
                (h2_regime == 2'd1 || h2_regime == 2'd3)) begin
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
        end
    end

endmodule