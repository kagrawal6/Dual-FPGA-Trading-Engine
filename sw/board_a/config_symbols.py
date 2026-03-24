"""
Addition: user-friendly symbol loader (tickers -> numeric metadata) for Board A.

What this code does:
1) User selects companies by ticker (CLI or a text file).
2) Script validates tickers against `symbol_universe.SYMBOL_DB`.
3) Assigns `symbol_id = 0..N-1` in the order the user provided.
4) Groups them by sector (for a clean UX summary).
5) Writes per-symbol numeric configuration into Board A AXI-Lite registers:
   - initial mid price (`SYM*_INIT_MID`)
   - per-symbol sector id (`SYM*_SECTOR_ID`) if requested
6) Optional: pulses `CTRL` to start the simulation after loading.

This matches the PDF proposal (software owns parsing/grouping; RTL sees only numeric values).
"""

from __future__ import annotations

import argparse
import random
from collections import Counter
from typing import List

from pynq import Overlay, MMIO

from symbol_universe import (
    SYMBOL_DB,
    extract_sector_groups,
    normalize_symbol,
    ticker_for_token,
    token_for_ticker,
)


# ADDITION: Board A register offsets (extended map for NUM_SYM up to 16).
CTRL = 0x00
QUOTE_INTERVAL = 0x04
LFSR_SEED = 0x08
REGIME = 0x0C

INIT_MID_BASE = 0x10      # +4*i
INIT_SPREAD_BASE = 0x50   # +4*i
SECTOR_ID_BASE = 0x90     # +4*i
ACTIVE_SYM_COUNT = 0xF0
TOKEN_BASE = 0xD0         # +4*(i//2), two 16-bit tokens packed per word

DEFAULT_HW_SLOTS = 16


def q16_16(val: float) -> int:
    """Convert float to unsigned Q16.16 integer."""
    return int(val * 65536) & 0xFFFFFFFF


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Load ticker/token metadata into Board A (supports random 8-16 company selection)."
    )
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--symbols", nargs="+", help="Tickers to load, e.g. AAPL MSFT NVDA XOM CVX")
    group.add_argument("--tokens", nargs="+", type=int, help="Stable global company tokens, e.g. 10 55 230")
    group.add_argument(
        "--symbols-file",
        type=str,
        help="Path to a text file with one ticker per line (e.g. AAPL\\nMSFT\\n...).",
    )
    group.add_argument(
        "--random-count",
        type=int,
        help="Pick a random set of companies of size N (recommended 8..16).",
    )

    parser.add_argument(
        "--hw-slots",
        type=int,
        default=DEFAULT_HW_SLOTS,
        help="Number of active hardware symbol slots available in bitstream (default: 16).",
    )
    parser.add_argument(
        "--allow-truncate",
        action="store_true",
        help="If more are selected than hardware slots, truncate to --hw-slots.",
    )
    parser.add_argument("--start", action="store_true", help="Pulse CTRL after writing config.")
    parser.add_argument("--random-seed", type=int, default=None, help="Seed for deterministic random selection.")

    parser.add_argument(
        "--write-sector-id",
        action="store_true",
        help="Write SYM*_SECTOR_ID registers. Only enable if your RTL/bitstream supports them.",
    )
    parser.add_argument(
        "--write-token-id",
        action="store_true",
        help="Write SYM*_TOKEN registers for fixed global token model.",
    )
    parser.add_argument(
        "--init-spread-default",
        type=float,
        default=0.125,
        help="Default init_spread (Q16.16) for symbols if not otherwise specified by SYMBOL_DB.",
    )
    return parser.parse_args()


def load_symbols_from_file(path: str) -> List[str]:
    out: List[str] = []
    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            s = line.strip()
            if not s or s.startswith("#"):
                continue
            out.append(s)
    return out


def main() -> None:
    args = parse_args()

    if args.hw_slots < 1:
        raise ValueError("--hw-slots must be >= 1.")

    # ADDITION: multi-mode selection input (symbols, tokens, file, or random sample).
    if args.symbols_file:
        raw_symbols = load_symbols_from_file(args.symbols_file)
        selected = [normalize_symbol(s) for s in raw_symbols if normalize_symbol(s)]
    elif args.tokens:
        selected = [ticker_for_token(t) for t in args.tokens]
    elif args.random_count is not None:
        if args.random_count < 1:
            raise ValueError("--random-count must be >= 1.")
        rng = random.Random(args.random_seed)
        universe = sorted(SYMBOL_DB.keys())
        if args.random_count > len(universe):
            raise ValueError(f"--random-count={args.random_count} exceeds universe size {len(universe)}.")
        selected = rng.sample(universe, args.random_count)
    else:
        raw_symbols = args.symbols
        selected = [normalize_symbol(s) for s in raw_symbols if normalize_symbol(s)]

    if not selected:
        raise ValueError("No valid tickers provided.")

    if len(selected) > args.hw_slots and not args.allow_truncate:
        raise ValueError(
            f"Too many symbols ({len(selected)}). Hardware slots={args.hw_slots}. "
            "Use --allow-truncate to proceed."
        )
    selected = selected[: args.hw_slots]

    # ADDITION: resolve normalized per-slot metadata (includes fixed global token).
    loaded = []
    for symbol_id, sym in enumerate(selected):
        if sym not in SYMBOL_DB:
            raise ValueError(f"Unknown symbol: {sym}")
        info = SYMBOL_DB[sym]
        loaded.append(
            {
                "symbol_id": symbol_id,
                "ticker": sym,
                "sector": str(info["sector"]),
                "sector_id": int(info["sector_id"]),
                "company_token": int(info["company_token"]),
                "init_price": float(info["init_price"]),
                # The PDF only specifies init_price; we use a default spread for current RTL.
                "init_spread": float(info.get("init_spread", args.init_spread_default)),
            }
        )

    # UX summary (matches the PDF style).
    print(f"Loaded {len(loaded)} symbols (hw_slots={args.hw_slots}):")
    for x in loaded:
        print(
            f'{x["symbol_id"]}: token={x["company_token"]} {x["ticker"]} -> '
            f'{x["sector"]}, init={x["init_price"]}'
        )

    sector_groups = extract_sector_groups([x["ticker"] for x in loaded])
    print("Sector groups:")
    for sector_name, tickers in sector_groups.items():
        joined = ", ".join(tickers)
        print(f"{sector_name}: {joined}")

    # RTL scales per-sector noise by active population in each sector_id.
    by_sector_name = Counter(x["sector"] for x in loaded)
    by_sector_id = Counter(x["sector_id"] for x in loaded)
    print("Sector population (hardware sector_id counts — used for noise gain):")
    for sid in sorted(by_sector_id.keys()):
        print(f"  sector_id {sid}: {by_sector_id[sid]} symbol(s)")
    print("Sector population (by name, demo / debug):")
    for name, cnt in sorted(by_sector_name.items(), key=lambda z: (-z[1], z[0])):
        print(f"  {name}: {cnt}")

    # ADDITION: write extended metadata config into AXI-Lite map.
    ol = Overlay("overlays/board_a.bit")
    mmio = MMIO(ol.ip_dict["board_a_top_0"]["phys_addr"], 256)
    mmio.write(ACTIVE_SYM_COUNT, len(loaded))

    # Write init prices/spreads for all active hardware slots.
    # If user provides fewer than slots, unused slots get init_mid=0.
    for i in range(args.hw_slots):
        if i < len(loaded):
            init_mid = loaded[i]["init_price"]
            init_spread = loaded[i]["init_spread"]
            sector_id = loaded[i]["sector_id"]
            company_token = loaded[i]["company_token"]
        else:
            init_mid = 0.0
            init_spread = float(args.init_spread_default)
            sector_id = 0
            company_token = 0

        mmio.write(INIT_MID_BASE + 4 * i, q16_16(init_mid))
        mmio.write(INIT_SPREAD_BASE + 4 * i, q16_16(init_spread))

        if args.write_sector_id:
            mmio.write(SECTOR_ID_BASE + 4 * i, int(sector_id))
        if args.write_token_id:
            token_reg = TOKEN_BASE + 4 * (i // 2)
            if i % 2 == 0:
                packed = int(company_token) & 0xFFFF
                if (i + 1) < args.hw_slots:
                    nxt = loaded[i + 1]["company_token"] if (i + 1) < len(loaded) else 0
                    packed |= (int(nxt) & 0xFFFF) << 16
                mmio.write(token_reg, packed)

    if args.start:
        # Start pulse matches sw/board_a/config_exchange.py.
        mmio.write(CTRL, 0x01)
        print("Board A started.")


if __name__ == "__main__":
    main()
