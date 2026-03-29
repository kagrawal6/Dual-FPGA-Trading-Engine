# Stretch Goals

## 1. Per-Symbol Proportional Spread

**Current behavior:** All symbols use the same flat `base_spread` determined by the regime (e.g., $0.125 in CALM). A $900 stock (NVDA) and a $60 stock (KO) get identical spreads.

**Goal:** Scale the spread by each symbol's price level so higher-priced stocks have proportionally wider dollar spreads, matching real market behavior.

**Approach:**
- `spread[s] = (base_spread * mid_price[s]) >> 16` (one Q16.16 multiply)
- Costs 1 DSP48E2 slice in `market_sim.sv`
- Update golden model `board_a.py` to match
- Optionally make the reference price configurable via AXI register

**Impact:** More realistic quote data; better demo talking point for market microstructure accuracy.
