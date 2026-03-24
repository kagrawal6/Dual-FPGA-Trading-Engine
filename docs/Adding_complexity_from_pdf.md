# Adding Complexity — PDF Extract & Project Notes

**Source:** `Adding_complexity.pdf`

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
symbol_universe.py
board_b/
telemetry_server.py
dashboard/
dashboard.py

So:
1. 2 new software files
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

Best user-friendly model

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
● config_symbols.py -> user selects companies

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

## Implemented Changes In This Repo

This section describes the concrete code changes that were added after the PDF extract.

### 1) Software Symbol Universe and Stable Tokens

- File: `sw/board_a/symbol_universe.py`
- Added full S&P 500-aware symbol loading (with offline fallback).
- Added deterministic sector mapping fields in `SYMBOL_DB`:
  - `sector`
  - `sector_id`
  - `init_price`
- Added stable global tokenization:
  - `COMPANY_TOKEN_BY_TICKER`
  - `TICKER_BY_COMPANY_TOKEN`
  - `token_for_ticker()`
  - `ticker_for_token()`
- Added in-place symbol enrichment:
  - `SYMBOL_DB[ticker]["company_token"]`

**Runtime effect:** users can refer to companies by either symbol or stable numeric token.

### 2) Software Loader Supports Symbol/Token/File/Random Selection

- File: `sw/board_a/config_symbols.py`
- Added multi-mode input selection:
  - `--symbols`
  - `--tokens`
  - `--symbols-file`
  - `--random-count` (+ `--random-seed`)
- Added configurable slot count:
  - `--hw-slots` (default 16)
  - `--allow-truncate`
- Added write paths for extended metadata:
  - `INIT_MID_BASE` (`0x10 + 4*i`)
  - `INIT_SPREAD_BASE` (`0x50 + 4*i`)
  - `SECTOR_ID_BASE` (`0x90 + 4*i`)
  - `TOKEN_BASE` (`0xD0 + 4*j`, two 16-bit tokens packed into one 32-bit word)
  - `ACTIVE_SYM_COUNT` (`0xF0`)
- Added optional flags:
  - `--write-sector-id`
  - `--write-token-id`

**Runtime effect:** script can load 8-16 (or any `--hw-slots`) selected symbols and program active count + metadata consistently.

### 3) Hardware Symbol Capacity Increased

- File: `rtl/shared/hft_pkg.sv`
- `NUM_SYMBOLS` changed from `4` to `16`.

**Runtime effect:** design-wide symbol arrays and loops now compile for 16 slots (subject to full top-level integration and timing closure).

### 4) Executable Sector-Aware Noise Generator

- File: `rtl/board_a/market_noise_gen.sv`
- Converted scaffold to executable RTL.
- Implements:
  - one independent LFSR per symbol
  - per-symbol local drift state
  - per-sector drift accumulation
  - shared global term
  - output decomposition:
    - `global_noise_q16_16`
    - `sector_noise_q16_16`
    - `company_noise_q16_16`
    - `step_out_q16_16[s] = global + sector + company`
- Uses `active_sym_count` to gate active symbols.

**Runtime effect:** symbol-local randomness and sector correlation are now generated in hardware logic.

### 5) AXI-Lite Register Logic Implemented for New Metadata

- File: `rtl/board_a/board_a_axi_regs.sv`
- Implemented active AXI read/write logic with extended register map:
  - base config: `CTRL`, `QUOTE_INTERVAL`, `LFSR_SEED`, `REGIME`
  - per-symbol arrays: init mid/spread, sector id, company token
  - runtime active symbol count
  - readback for status and counters
- Added outputs:
  - `sym_sector_id[NUM_SYM]`
  - `sym_company_token[NUM_SYM]`
  - `active_sym_count`

**Runtime effect:** Board A register block can store and expose all metadata needed by symbol-aware datapath.

### 6) Market Simulator Integrated With Noise Generator

- File: `rtl/board_a/market_sim.sv`
- Added inputs:
  - `active_sym_count`
  - `sector_id[NUM_SYM]`
- Instantiates `market_noise_gen`.
- Replaced prior scalar random-step update with:
  - `delta_s = n_step_out[sym_ptr]`
- Added `active_count_eff` clamp to keep runtime count in `[1, NUM_SYM]`.
- Round-robin pointer wraps at `active_count_eff - 1`.

**Runtime effect:** quote evolution uses sector-aware, symbol-local noise and respects runtime active symbol count.

### 7) Added Logistic Comment Headers

- Files updated with explicit `ADDITION` comments:
  - `rtl/board_a/board_a_axi_regs.sv`
  - `rtl/board_a/market_sim.sv`
  - `rtl/board_a/market_noise_gen.sv`
  - `sw/board_a/symbol_universe.py`
  - `sw/board_a/config_symbols.py`

**Runtime effect:** no logic change from these comments; improves collaborator readability and review.

### 8) Current Integration Status

- Implemented modules now support:
  - stable company tokens
  - variable active symbol count
  - per-symbol independent random sources
  - sector-aware movement
- End-to-end behavior still depends on top-level module wiring consistency (especially `board_a_top.sv`) and bitstream rebuild.

