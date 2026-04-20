# Plan — G2 Neural network inference strategy (clarification + complexity tiers)

**Goal:** Add `strategy_nn.sv` and a training/export path so Board B can trade from a **fixed-point MLP**.  
**Spec:** `docs/updated_design_specification.md` §8.3.  
**Status:** In progress — use this file to **choose scope** before writing more RTL.

---

## 1. What “G2” means in the spec (baseline)

- **Architecture:** 4 inputs → 8 hidden (ReLU) → 3 outputs (BUY / SELL / HOLD scores); **argmax** → decision.
- **I/O features:** `mid_price`, `spread`, `deviation`, `ema` (all Q16.16 from / aligned with `feature_compute`).
- **Weights:** Q8.8 quantization; **~67 parameters** (~134 bytes) — small enough for AXI registers or one BRAM.
- **Latency:** ~8–10 cycles pipelined (spec target ~80 ns at 100 MHz).
- **Training (offline):** Python generates labels, PyTorch trains, export quantized weights, PS writes to PL at boot.

---

## 2. Clarifications (decide explicitly)

| Question | Options | Impact |
|----------|---------|--------|
| **Label quality** | Hindsight “optimal action” vs PnL-based vs imitation of MR strategy | Training stability, defensibility for capstone |
| **Per-symbol or shared net** | One MLP for all symbols vs per-symbol weights | BRAM / register count, training time |
| **Hold semantics** | `argmax == HOLD` → `signal_valid = 0` | Must match `order_manager` idle behavior |
| **Feature scaling** | Raw Q16.16 vs normalized features | Quantization error, overflow in MAC |
| **Nonstationary markets** | Retrain per regime vs single model | Extra `.pt` files and PS load logic |

**Recommendation:** Start with **one global MLP**, **spec features**, **hindsight labels** from `golden_model` / `board_a.py` style simulator — document limitations in the report.

---

## 3. Complexity tiers (pick one to ship first)

### Tier A — “Inference shell” (lowest risk)

- Fixed **random** or **hand-tuned** Q8.8 weights (no training pipeline).
- **Prove** DSP MAC + ReLU + argmax in RTL matches a **Python bit-accurate model** (same rounding).
- **No** demo claim about “learned” behavior until Tier B.

**Deliverables:** `strategy_nn.sv`, small TB, PS script that **pokes** weight registers.

### Tier B — Spec-sized MLP + offline training (full G2)

- Implement **exact** 4×8×3 + biases; pipeline per spec.
- `train_strategy_nn.py` (PyTorch) + `export_weights.py` → hex/headers for PS or `$readmemh` for sim.
- Extend **`telemetry_server.py`** (or dedicated script) to **stream weights to AXI** after overlay load.

**Deliverables:** Tier A + training repo folder + reproducible `make train` / `make export`.

### Tier C — Richer model (stretch beyond spec)

- Deeper / wider hidden layer, or second hidden layer.
- **Per-symbol** bias only, or **embedding** for symbol id.
- More BRAM/DSP; longer latency — **re-pipeline** and re-close timing.

**Warning:** Only after Tier B works; avoid science-fair scope creep before demo.

---

## Step-by-step plan (Tier B aligned)

### Step 1 — Golden / Python reference

1. Implement **`tools/nn_bitexact.py`** (or under `golden_model/`) that mirrors RTL: Q8.8 × Q16.16 MAC, ReLU, argmax.
2. Lock **rounding**: trunc vs round; document in appendix.

### Step 2 — Training pipeline

1. **`generate_training_data.py`:** CSV of features + label (`0/1/2` or BUY/SELL/HOLD).
2. **`train_strategy_nn.py`:** Train with constraint toward **low weight entropy** for fixed-point friendliness.
3. **Export:** Coefficient array + checksum for PS sanity check.

### Step 3 — RTL

1. **`strategy_nn.sv`:** Pipelined MAC array; reuse DSPs across cycles if needed.
2. **Weight ports:** From AXI shadow regs or BRAM interface; idle until weights **valid** flag.
3. **Integrate** into `strategy_engine` same as G1.

### Step 4 — Software

1. **AXI map:** contiguous weight addresses or indirect index + data port (avoid 134 separate named constants if possible).
2. **`register_map.py`:** generated or scripted from a single CSV.
3. **Load sequence:** reset NN → write weights → set `weights_loaded` → enable strategy.

### Step 5 — Verification

1. **Cosim:** same inputs → Python vs RTL (within 1 LSB if stochastic).
2. **Hardware:** switch `active_strategy` to NN; compare order rate and direction to offline sim.

### Step 6 — Demo narrative

1. **Poster:** diagram of dataflow + “trained offline, deployed fixed-point.”
2. **Honesty:** state nonstationarity and label heuristic limits.

---

## Exit criteria

- [ ] Bit-accurate reference matches RTL on test vectors.  
- [ ] At least one **trained** weight set runs on hardware without overflow.  
- [ ] Clear **Tier A vs B** label in README / report.
