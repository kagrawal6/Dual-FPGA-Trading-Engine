# Adding Complexity — Project Notes

**Source:** `Adding_complexity.pdf` (design notes this document was derived from; implementation status is summarized in *Implemented Changes In This Repo* below.)

Best user-friendly flow

What the user sees

Something like:
• 	enter company tickers: AAPL, MSFT, NVDA, XOM, CVX
• 	click run / execute script

Then the system automatically:
• 	validates the tickers
• 	finds their sectors
• 	groups them
• 	assigns symbol IDs
• 	loads initial prices/metadata into the FPGA
• 	starts the simulation

That is the clean user experience.

a) What the hardware should see

The hardware should only receive structured values like:
• 	symbol_id
• 	sector_id
• 	initial price
• 	maybe packed ticker code for display/debug
• 	maybe sector gain / company gain

So for example:

Ticker symbol_id sector_id init_price
AAPL 0 	0 	180.00

-- 1 of 13 --

MSFT 1 	0 	420.00
NVDA 2 	0 	900.00
XOM 3 	1 	115.00
CVX 4 	1 	160.00

Where maybe:
● 0 = tech
● 1 = energy

That is what gets written into hardware registers or BRAM.

The right architecture

Software side: user-friendly symbol loader

This should live in software, not RTL.

Suggested new file
sw/board_a/symbol_universe.py
Purpose:
• 	store known ticker → sector mapping
• 	store default initial price
• 	maybe store company name for display

-- 2 of 13 --

Suggested new file
sw/board_a/config_symbols.py
Purpose:
• 	ask user for tickers or accept a list
• 	validate them
• 	map them to sectors
• 	assign symbol IDs
• 	write configuration into AXI-Lite registers
• 	print a summary of what got loaded

Suggested folder layout
sw/
board_a/
config_exchange.py
config_symbols.py
symbol_config_panel.py
symbol_universe.py
board_b/
telemetry_server.py
dashboard/
dashboard.py

So:
1. New software files under `sw/board_a/` (universe + loader; optional Jupyter panel)
2. Hardware only needs small modifications to accept sector metadata cleanly

What symbol_universe.py should contain

A simple dictionary is enough.

Example:
SYMBOL_DB = {
"AAPL": {"sector": "Technology", "sector_id": 0, "init_price": 180.00},
"MSFT": {"sector": "Technology", "sector_id": 0, "init_price": 420.00},

-- 3 of 13 --

"NVDA": {"sector": "Technology", "sector_id": 0, "init_price": 900.00},
"XOM": {"sector": "Energy", "sector_id": 1, "init_price": 115.00},
"CVX": {"sector": "Energy", "sector_id": 1, "init_price": 160.00},
"JPM": {"sector": "Finance", "sector_id": 2, "init_price": 200.00},
}

However, just expand it to the full thing for SMP500

What config_symbols.py should do

User enters:
selected = ["AAPL", "MSFT", "NVDA", "XOM", "CVX"]

Script does:
1. uppercase/clean input
2. check every symbol exists in SYMBOL_DB
3. assign symbol_id = 0..N-1
4. collect sector IDs
5. collect prices
6. optionally print grouping summary
7. write values to FPGA registers

Example user-friendly behavior

User runs:
python config_symbols.py --symbols AAPL MSFT NVDA XOM CVX

-- 4 of 13 --

Script prints:
Loaded 5 symbols:
0: AAPL -> Technology
1: MSFT -> Technology
2: NVDA -> Technology
3: XOM -> Energy
4: CVX -> Energy

Sector groups:
Technology: AAPL, MSFT, NVDA
Energy: XOM, CVX

That is user-friendly and clean.

How hardware uses this

Hardware does not parse strings.

Hardware just stores:
sector_id[symbol_id]
Init_mid[symbol_id]

Then in market_sim or market_noise_gen:
step_out[s] = global_term
+ sector_term[sector_id[s]]
+ local_term[s]
+ trend_term[s];

-- 5 of 13 --

So if the user chooses three tech names and two energy names, the grouping behavior comes
naturally from the sector_id values software loaded.

Step 4 — Runtime Behavior

Hardware uses:
price[s] = global_noise
+ sector_noise[sector_id[s]]
+ company_noise[s];

→ Companies in same sector move together
→ Each company still has independent variation
→ Fully deterministic

Do you need company names in hardware?

Usually: no
For actual datapath behavior, no.

Optional: yes, for display/debug
If you want dashboard labels or debug visibility, you can store packed ticker codes.

Example:
● "AAPL" packed into 32 bits
● "MSFT" packed into 32 bits

Then dashboard can display the names that correspond to symbol IDs.

-- 6 of 13 --

Clean hardware support you need

To make this work well, hardware should support per-symbol metadata storage.

In market_sim.sv , add arrays like
logic [2:0] sector_id [NUM_SYMBOLS];
logic [31:0] mid_price [NUM_SYMBOLS];

In AXI-Lite registers, add per-symbol config
For each symbol s, software should be able to write:
● initial mid price
● sector ID

For example:
● SYM0_INIT_MID
● SYM0_SECTOR_ID
● SYM1_INIT_MID
● SYM1_SECTOR_ID
● etc.

That is how software tells hardware what each selected company belongs to.

-- 7 of 13 --

Best user-friendly model (original PDF)

Option A: command-line
python config_symbols.py --symbols AAPL MSFT NVDA XOM CVX

Option B: simple text file
User edits:
AAPL
MSFT
NVDA
XOM
CVX

Then script loads it.

Option C: dashboard dropdown
Later, if you want it slick:
● multi-select dropdown in Dash
● click “load symbols”
● script updates config
That is very demo-friendly, but I would start with command-line or file input first.

**Current repo (beyond A/B):**

- **Terminal interactive:** `python3 config_symbols.py --interactive` — prompts on stdin (SSH/serial from a laptop). Use `--write-sector-id`, `--write-token-id`, and `--start` when your bitstream supports them (same as non-interactive CLI).
- **Jupyter / ipywidgets:** `sw/board_a/symbol_config_panel.py` — call `show_symbol_config_panel()` from a notebook for a small UI (paste tickers or random sample, checkboxes, **Apply to FPGA**). Same MMIO path as `config_symbols.py`; typical on PYNQ with a browser.
- **Shared implementation:** `config_symbols.py` exposes `parse_ticker_paste`, `prepare_loaded_symbols`, `print_configuration_summary`, and `write_mmio_board_config` so CLI, `--interactive`, and the Jupyter panel stay aligned.

-- 8 of 13 --

Does this add latency?

Still no, because:
● user selection happens before run
● mapping happens in software before run
● hardware only sees numeric metadata during run

So you get:
● friendly UX
● no live latency penalty

My recommendation

For your project, the smartest version is:

Software
● create symbol_universe.py
● create config_symbols.py
● let user choose tickers by name

Hardware
● support NUM_SYMBOLS active symbols
● store sector_id[s]

-- 9 of 13 --

● use sector-aware movement in market_noise_gen / market_sim
That gives you exactly what you want without making the RTL ugly.

Tiny example software

Here is a very simple version of what the Python side could look like:

# sw/board_a/symbol_universe.py
SYMBOL_DB = {
"AAPL": {"sector": "Technology", "sector_id": 0, "init_price": 180.00},
"MSFT": {"sector": "Technology", "sector_id": 0, "init_price": 420.00},
"NVDA": {"sector": "Technology", "sector_id": 0, "init_price": 900.00},
"XOM": {"sector": "Energy", "sector_id": 1, "init_price": 115.00},
"CVX": {"sector": "Energy", "sector_id": 1, "init_price": 160.00},
}

# sw/board_a/config_symbols.py

-- 10 of 13 --

from symbol_universe import SYMBOL_DB
selected = ["AAPL", "MSFT", "NVDA", "XOM", "CVX"]
loaded = []
for i, sym in enumerate(selected):
sym = sym.upper()
if sym not in SYMBOL_DB:
raise ValueError(f"Unknown symbol: {sym}")
info = SYMBOL_DB[sym]
loaded.append({
"symbol_id": i,
"ticker": sym,
"sector": info["sector"],
"sector_id": info["sector_id"],
"init_price": info["init_price"],
})
print("Loaded symbols:")
for x in loaded:
print(f'{x["symbol_id"]}: {x["ticker"]} -> {x["sector"]}, init={x["init_price"]}')
Then you would extend that to write MMIO registers.

-- 11 of 13 --

Yes — you can absolutely make it user-friendly so the user selects companies by ticker, software
automatically finds their sectors and groups them, and hardware uses that metadata without any
runtime latency penalty.

The clean implementation is:
● 2 software files
● small hardware support for sector IDs
● no string parsing in RTL

11. Final Summary

What we added:
Software:
● symbol_universe.py -> defines companies + sectors
● config_symbols.py -> user selects companies (CLI, `--interactive`, shared MMIO helpers)
● symbol_config_panel.py -> optional Jupyter/ipywidgets panel calling the same MMIO path

Hardware:
● per-symbol sector_id
● sector-aware price movement

What this gives you:

-- 12 of 13 --

● User selects real companies
● System groups them automatically
● Market behaves realistically
● Still fully deterministic
● No latency penalty
● Scales cleanly

-- 13 of 13 --

## Concerns / Integration Risks (Current Repo State)

1. **Top-level wiring still matters:** even if `board_a_axi_regs.sv`, `market_sim.sv`, and `market_noise_gen.sv` implement the new interfaces, end-to-end behavior depends on `board_a_top.sv` correctly plumbing the new signals (e.g., `active_sym_count`, `sector_id`).
2. **Register-map skew risk:** the software MMIO offsets must match the RTL decode map in the running bitstream. Any mismatch (old bitstream vs new SW, or vice versa) can cause silent misconfiguration.
3. **Resource / timing pressure:** moving from `NUM_SYMBOLS=4` to `NUM_SYMBOLS=16` and adding per-symbol LFSR instances increases area and may reduce timing margin.
4. **Active-symbol gating correctness:** the runtime `active_sym_count` gating must be consistent across RTL modules (token/metadata writes, pointer wrap logic, and noise update enable conditions).
5. **Sector-id encoding width assumptions:** current sector correlation logic assumes a compact `sector_id` width (e.g., 3 bits) and a bounded number of sectors. If the software’s sector-id assignment exceeds what the RTL expects, correlation will be incorrect.
6. **Determinism verification:** `market_noise_gen` uses multiple LFSRs with derived seeds; deterministic behavior depends on consistent seeding and reset/load semantics.

## Implemented Changes In This Repo (Final State)

This section captures what is actually implemented now, why it was done, and what it means behaviorally.

### 1) Shared Package Constants and Type Safety

- File: `rtl/shared/hft_pkg.sv`
- `NUM_SYMBOLS` increased to `16`.
- Added sector constants:
  - `NUM_SECTORS = 8`
  - `SECTOR_ID_W = $clog2(NUM_SECTORS)`
- Added shared noise saturation constant:
  - `MARKET_NOISE_DRIFT_SAT_Q16`

**Why:** keep sector dimensions and saturation policy centralized and consistent across RTL + testbenches.  
**Meaning:** sector-id width and drift limits are explicit project-wide, reducing silent mismatch risk.

### 2) Software Universe + Loader (User UX and MMIO Programming)

- Files:
  - `sw/board_a/symbol_universe.py`
  - `sw/board_a/config_symbols.py`
  - `sw/board_a/symbol_config_panel.py` (Jupyter / ipywidgets UI; optional)
- Supports ticker/token/file/random selection workflows (CLI flags on `config_symbols.py`).
- **Terminal interactive:** `--interactive` on `config_symbols.py` for prompt-driven selection over SSH/serial.
- **Jupyter:** `show_symbol_config_panel()` for a browser-based panel (paste tickers or random sample); uses the same helpers as the CLI (`prepare_loaded_symbols`, `write_mmio_board_config`, etc.).
- Supports stable per-company tokens.
- Programs symbol metadata via AXI map:
  - init mid/spread
  - sector id
  - packed token words
  - active symbol count
- Prints sector grouping summaries and sector population counts (including hardware sector-id counts).

**Why:** preserve a friendly “select real companies by ticker” interface while hardware consumes only numeric metadata.  
**Meaning:** no runtime string handling in RTL; deterministic, inspectable pre-run configuration.

### 3) AXI Register Block Extended for Symbol Metadata

- File: `rtl/board_a/board_a_axi_regs.sv`
- Implements read/write decode for:
  - `CTRL`, `QUOTE_INTERVAL`, `LFSR_SEED`, `REGIME`
  - per-symbol init mid / init spread / sector id / token
  - `ACTIVE_SYM_COUNT`
  - status/counter readback
- Uses `SECTOR_ID_W` consistently for sector-id IO and readback formatting.

**Why:** software needed a complete, scalable register interface to load symbol/sector/token state.  
**Meaning:** Board A dataplane can be parameterized at runtime without recompiling RTL.

### 4) market_noise_gen Reworked to Population-Scaled Sector Model

- File: `rtl/board_a/market_noise_gen.sv`
- Noise architecture now includes:
  - one global LFSR
  - one per-symbol LFSR (company path)
  - one per-sector LFSR (sector base path)
- Sector population model:
  - builds `sector_pop[k]` from active symbols
  - computes sector base delta once per sector
  - scales by `sector_pop[k]`
  - accumulates into sector drift with saturation
- Company drift remains per-symbol and saturated.
- Output decomposition remains:
  - `step_out[s] = global + sector[sector_id[s]] + company[s]`
- Inactive symbols still output zero.
- Defensive clamp added:
  - internal `active_count_eff = min(active_sym_count, NUM_SYM)`
- `lfsr_load` semantics aligned to “fresh run”:
  - reseeds RNGs and clears sector/company drift state.

**Why:** gives predictable sector correlation with explicit intensity scaling based on selected active sector population, and aligns reload semantics with `market_sim`.  
**Meaning:** sectors with more selected names move more aggressively by design; behavior is deterministic under fixed seed/config.

### 5) market_sim Integration and Runtime Behavior

- File: `rtl/board_a/market_sim.sv`
- Consumes the noise decomposition buses from `market_noise_gen`.
- Uses runtime `active_sym_count` clamp (`active_count_eff`) for safe symbol scheduling.
- Round-robin wraps at `active_count_eff - 1`.
- Keeps documented valid/ready pulse behavior and `quote_interval==0` fast-path semantics.
- Supports `lfsr_load` reload of market state/counters.

**Why:** runtime-selected active symbols and sector-aware noise needed to feed quote generation safely and deterministically.  
**Meaning:** quote stream reflects current active subset, regime scaling, and reload behavior without requiring reset.

### 6) Verification Coverage (What Is Tested)

- Files:
  - `tb/board_a/tb_market_sim.sv`
  - `tb/board_a/tb_market_noise_gen.sv`

`tb_market_sim` now checks:
- round-robin and sequence behavior
- regime-switch handling
- backpressure behavior (`quote_ready=0`) including `quotes_generated` stability
- `active_sym_count < NUM_SYM` subset wrap behavior
- mid-run `lfsr_load` reload behavior
- `quote_interval==0` path
- pulse-style `quote_valid` semantics in a non-back-to-back interval case
- final `quotes_generated` expectations

`tb_market_noise_gen` now checks:
- deterministic repeatability for same seed/config
- decomposition identity:
  - `step_out = global + sector + company` (active symbols)
- inactive symbol zero outputs
- reset/lfsr_load state expectations
- sector population scaling trend:
  - cumulative `|sector_noise[0]| > |sector_noise[1]|` for pop 3 vs 1 (sanity/trend check, not strict theorem)
- drift saturation bounds at outputs

**Why:** this closes the key behavioral gaps around gating, active subsets, reload semantics, decomposition correctness, and boundedness.  
**Meaning:** we now test both integration-level quote behavior and standalone noise-model properties.

### 7) What This Means for Bring-Up

- Current repo state is logically strong for this feature set.
- Remaining practical dependency is top-level wiring and bitstream parity:
  - `board_a_top.sv` integration
  - matching software offsets with the running bitstream
  - post-integration synthesis/timing/board validation

In other words: feature logic and tests are in place; hardware bring-up risk is now mostly integration/toolflow rather than missing model behavior.

### 8) exchange_lite Contract (Current Minimal Version)

Current limitation
- `exchange_lite` does not queue incoming orders while a response is pending.
- If `order_valid` is asserted while Stage 1 is blocked or a response is being held (`fill_valid=1 && !fill_ready`), that order is not captured.
- This is intentional for the current minimal demo implementation.

Future upgrade path
- Add a small input FIFO or one-entry pending-order buffer.
- That allows accepting a new order while a previous response is still waiting on `fill_ready`.
- This removes the intentional throughput bubble and makes the exchange behavior more realistic under bursts.

Bottom line
- The updated `tb_exchange_lite.sv` now checks the implemented contract instead of assuming deeper buffering.
- For the current project phase, `exchange_lite.sv` is considered locked as the minimal version.

