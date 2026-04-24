# ML-Guided Adaptive Strategy Selection — Partner Brief

**Audience:** teammate implementing ML for Board B  
**Ground truth in repo:** `docs/updated_design_specification.md` (§8 stretch goals, Appendix F), `rtl/shared/hft_pkg.sv` (`regime_e`, `strategy_e`)

This note explains **how to let the model choose or switch among real trading strategies** based on **live market features** (not just the operator’s Board A regime switch), ties the math to classical quant ideas, and outlines a concrete implementation path that fits the existing hardware story.

---

## 1. Two different “regimes” (do not conflate them)

| Concept | Where it lives | What it means |
|--------|----------------|---------------|
| **Market stress regime** | Board A (`REGIME_CALM` … `ADVERSARIAL`) | Operator/PS sets **quote dynamics**: step size, spread, and (with BURST) quote rate. See Appendix E / regime table in the spec. |
| **Trading strategy** | Board B (`STRAT_MEAN_REV` … `STRAT_AUTO`) | **How the trader responds** to quotes: mean-reversion, momentum, NN, or auto. |

The ML goal you described is on **Board B**: infer from **streaming quotes and derived features** which *strategy* (or blend) is appropriate **right now**, and change that choice as conditions change. Board A can still be flipped through CALM/VOLATILE/BURST/ADVERSARIAL for demos; the model should treat those as **exogenous stress factors** (they appear in each QUOTE frame as `regime`) but **not** as the only input—volatility and trend can move inside a single Board A regime.

---

## 2. What the pipeline already computes (mathematical core)

Everything below is in fixed-point **Q16.16** unless noted; EMA uses **Q0.16** \(\alpha\).

### 2.1 Mid, spread, deviation (mean-reversion signal)

Per quote (per symbol):

- \(\text{mid}_t = \frac{\text{bid}_t + \text{ask}_t}{2}\)
- \(\text{spread}_t = \text{ask}_t - \text{bid}_t\)

Exponential moving average of mid:

\[
\text{EMA}_t = \alpha \cdot \text{mid}_t + (1-\alpha)\cdot \text{EMA}_{t-1}
\]

In integer form (as in the spec):

\[
\text{EMA}_t = \frac{\alpha \cdot \text{mid}_t + (65536-\alpha)\cdot \text{EMA}_{t-1}}{65536}
\]

**Deviation** (core mean-reversion feature):

\[
d_t = \text{mid}_t - \text{EMA}_t
\]

**Mean-reversion hypothesis:** if prices are mean-reverting, large \(|d_t|\) tends to **shrink** afterward; the baseline strategy buys when \(d_t \ll 0\) and sells when \(d_t \gg 0\) beyond a threshold.  
**Failure mode:** in a **trend**, \(d_t\) can stay one-signed for a long time—mean-reversion keeps fading the trend.

*Real-world analogue:* short-horizon **statistical arbitrage / OTC mean reversion** on slow-moving fair value; pairs trading is a multi-asset variant.

### 2.2 Momentum (trend) signal — dual EMA (stretch G1)

Fast EMA \(\text{EMA}^f\) (already in `feature_compute`) vs slow EMA \(\text{EMA}^s\) (new state):

\[
\text{trend}_t = \text{EMA}^f_t - \text{EMA}^s_t
\]

Trade when \(\text{trend}_t\) exceeds a threshold (sign determines side).  
**Complement to mean-reversion:** momentum wins when **returns are positively autocorrelated** over your horizon; mean-reversion wins when **innovations mean-revert**.

*Real-world analogue:** **time-series momentum** and **EMA crossover** systems (classic CTA-style building blocks).

### 2.3 Volatility proxy (stretch G5)

Let \(\Delta_t = \left|\text{mid}_t - \text{mid}_{t-1}\right|\). Smoothed:

\[
\hat{\sigma}_t = \beta \cdot \Delta_t + (1-\beta)\cdot \hat{\sigma}_{t-1}
\]

This \(\hat{\sigma}_t\) (“`vol_hat`” in the spec) is **not** annualized Black–Scholes vol; it is a **scale tracker** for absolute short-horizon moves. It is ideal as an input to **regime detection** (quiet vs jumpy).

*Real-world analogue:* **realized volatility** estimators and **GARCH-like** smoothing, heavily simplified for hardware.

### 2.4 Why switching strategies is rational (informal “math”)

A single fixed strategy implies a **stationary** world: one rule optimizes one objective. Here the **data-generating process changes** (Board A regimes + OU pull-back + sector noise). A useful mental model is **mixture models**:

\[
P(r_{t+1} \mid \text{history}) = \sum_k \pi_k(\text{state}_t)\, P_k(r_{t+1})
\]

where \(\pi_k\) are **regime weights** driven by observables (vol, trend, spread, Board A `regime` field). Different \(P_k\) favor **contrarian vs trend** behavior. Learning \(\pi_k\) or the discrete choice \(k\) is exactly **adaptive strategy selection**.

---

## 3. Mapping “real world” strategies to this project

| Strategy mode (Board B) | Classical name | When it tends to work | Main risk |
|-------------------------|----------------|------------------------|-----------|
| Mean-reversion | MR / contrarian / short-horizon RV | Range-bound noise, moderate spreads | Trend + blow-ups (keeps selling rallies) |
| Momentum | Trend / TSM / MA crossover | Sustained directional drift | Whipsaws in ranges |
| Neural (MLP) | Learned policy / nonlinear filter | Corners cases, mixed regimes | Overfit to simulator; opaque failures |
| Auto (G4) | **Regime-switching model** | Matches rule to estimated state | Lag, threshold tuning |

The spec’s **G4 rule sketch** is already a transparent baseline:

- Low \(\hat{\sigma}\), tight spread → **mean-reversion**
- High \(\hat{\sigma}\) and strong \(|\text{trend}|\) → **momentum**
- Crisis-level vol or very wide spread → **NN** as a **defensive / nonlinear** fallback

Your ML work can **replace or sit above** these rules.

---

## 4. ML design options (choose one for the capstone timeline)

### Option A — **Strategy classifier** (recommended first)

**Input vector** per symbol (and optionally last \(k\) quotes):  
\([\text{mid}, \text{spread}, d, \text{EMA}, \text{trend}, \hat{\sigma}, \text{regime}_\text{A}, \text{sector features}…]\)

**Output:** one of \(\{\text{MR}, \text{MOM}, \text{HOLD}/\text{NN}\}\) or logits over the same.

**Training:**

- **Supervised:** label each timestep with the strategy that would have maximized **risk-adjusted PnL** over a short forward window under simulation (the spec’s “hindsight labeling” idea for the NN).  
- **Pros:** stable, matches G2 data pipeline.  
- **Cons:** labels depend on simulator; generalization is only as good as the sim.

**Inference on FPGA:** low-rate **PS** classification (AXI write to `STRATEGY_SEL`) for demos, or eventual **`regime_detector` RTL** if you quantize thresholds / small net.

### Option B — **Replace the MLP head (G2) with a richer net**

Keep the same 3-way action (BUY/SELL/HOLD) but widen inputs and use a small **temporal** model in training (1D CNN / shallow GRU) exported to static MLP for FPGA if needed.

**Pros:** single coherent policy.  
**Cons:** harder to prove determinism and latency story unless inference stays on PS or heavily pipelined.

### Option C — **Hierarchical “gating”**

Train a **lightweight gate** \(g_\phi\) that outputs mixture weights over expert heads (MR expert, MOM expert, NN expert). This mirrors **mixture-of-experts** and **ensemble policies**.

\[
\text{action} = \sum_i w_i(\text{features}) \cdot \text{Expert}_i
\]

For discrete orders, use \(w\) to pick argmax or sample (sampling is usually avoided in deterministic FPGA demos).

### Option D — **Contextual bandits / offline RL** (stretch)

Treat **strategy index** as arms; context = features; reward = realized PnL minus penalty for turnover/rejects. **Conservative bandits** (e.g., LinUCB-style) need fewer samples than full RL. Good for research flavor; more engineering than A.

---

## 5. Objective functions (what to optimize)

Whatever you train should align with what the desk cares about in this system:

1. **PnL** (cash + mark — already tracked in hardware telemetry).  
2. **Drawdown / `MAX_LOSS`** — hard halt exists; exceeding it is worse than missing profit.  
3. **Risk rejects** — surge under ADVERSARIAL; a “good” strategy might **trade less**.  
4. **Stability** — penalize **frequent strategy flips** (the spec uses **hysteresis** \(N\) quotes; mirror this in training with a switching cost).

A practical scalar reward for supervised labeling of “best strategy” at time \(t\):

\[
J = \mathbb{E}\Big[ \sum_{\tau=t}^{t+H} \Delta \text{PnL}_\tau - \lambda_\text{flip} \cdot \mathbf{1}[\text{strat}_\tau \neq \text{strat}_{\tau-1}] - \lambda_\text{risk} \cdot \text{Rejects}_\tau \Big]
\]

Tune \(\lambda\) so the model does not churn.

---

## 6. Implementation checklist (aligned with repo stretch goals)

| Step | Spec ref | ML partner action |
|------|----------|-------------------|
| Features ready | G5, `feature_compute` | Log `mid`, `spread`, `d`, `EMA`, \(\hat{\sigma}\), trend, Board A `regime` |
| Experts ready | G1 + core | Train/eval MR and MOM baselines (rules are fine) |
| Policy | G2 / G4 | Train classifier or MLP; quantize if moving to PL |
| Integration | G3 mux, `STRATEGY_SEL=AUTO` | PS or RTL writes selected strategy; **enforce hysteresis** |
| Validation | §7 acceptance | Same seed + config → reproducibility; compare against fixed-strategy ablations |

**Determinism note:** The project emphasizes deterministic RTL. If ML runs on **PS**, strategy updates happen at **telemetry rates** unless you add a dedicated coprocessor—plan latency expectations accordingly. Full PL inference of a net is possible but is a **large** RTL effort.

---

## 7. Suggested narrative for demos

- **CALM:** classifier should favor **mean-reversion** (small \(\hat{\sigma}\), small spreads).  
- **VOLATILE:** often **momentum** when \(\hat{\sigma}\) and \(|\text{trend}|\) are high.  
- **BURST:** stress **throughput and risk limits**—strategy may matter less than **order-rate limits**; ML might learn to **stand down** (HOLD).  
- **ADVERSARIAL:** wide spreads + large moves → **reduce aggression**; NN or “no trade” patterns dominate if trained with reject penalties.

---

## 8. References (conceptual)

- **Mean reversion vs momentum** — classic stylized fact: different horizons show different autocorrelation structure; see any empirical asset-pricing survey.  
- **Regime-switching models** — Hamilton-style models (discrete latent regimes) justify adaptive rules.  
- **Realized volatility** — Andersen et al. line of work (for intuition; your \(\hat{\sigma}\) is a toy version).  
- **Project spec** — `docs/updated_design_specification.md` §8.2–8.5, Appendix F (worked examples).

---

## 9. One-page summary for your partner

**Goal:** Learn a mapping from **live features** (vol, trend, deviation, spread, Board A regime, …) to **one of several hand-built expert strategies**, minimizing a **PnL minus risk/turnover** objective, with **hysteresis** to avoid thrashing.  
**Baselines:** G4 rules in the spec; beat them on held-out simulator runs with identical seeds.  
**Deployment path:** start on **PS** (updates strategy register), prove value, then consider PL or quantized gates.  
**Mind the gap:** Board A regime is **not** the same as “market state”; ML should use **observed** microstructure, not only the 2-bit regime label.
