"""
symbol_config.py — Interactive symbol picker for Dual-FPGA Trading Engine.
Runs on the PYNQ board BEFORE pynq_server.py.

Usage:
    python symbol_config.py              # interactive — pick your sectors
    python symbol_config.py --default    # use default 16-stock universe
    python symbol_config.py --default --start  # configure + start Board A

The user picks a sector, then how many stocks from that sector.
Repeats until 16 slots are filled. Prices/spreads are fixed per stock.
"""

import argparse
import json
import time

# ── S&P 500 universe by sector (ticker, mid_price, spread) ──────────────────
UNIVERSE = {
    "Tech": [
        ("AAPL",  180.00, 0.10), ("MSFT",  420.00, 0.15),
        ("GOOG",  175.00, 0.12), ("META",  510.00, 0.20),
        ("ORCL",  115.00, 0.08), ("CRM",   270.00, 0.18),
        ("ADBE",  520.00, 0.22), ("SNOW",  165.00, 0.14),
    ],
    "Semiconductor": [
        ("NVDA",  900.00, 0.25), ("AMD",   160.00, 0.08),
        ("INTC",   31.00, 0.05), ("AVGO",  170.00, 0.18),
        ("QCOM",  170.00, 0.12), ("MU",     85.00, 0.07),
        ("AMAT",  190.00, 0.14), ("LRCX",  850.00, 0.30),
    ],
    "Consumer": [
        ("AMZN",  185.00, 0.10), ("TSLA",  250.00, 0.30),
        ("HD",    350.00, 0.15), ("NKE",    90.00, 0.08),
        ("MCD",   290.00, 0.12), ("SBUX",   90.00, 0.07),
        ("TGT",   145.00, 0.10), ("COST",  730.00, 0.25),
    ],
    "Finance": [
        ("JPM",   200.00, 0.08), ("GS",    470.00, 0.22),
        ("BAC",    35.00, 0.04), ("WFC",    55.00, 0.05),
        ("MS",     95.00, 0.07), ("BLK",   820.00, 0.35),
        ("C",      60.00, 0.05), ("AXP",   230.00, 0.12),
    ],
    "Health": [
        ("JNJ",   155.00, 0.06), ("PFE",    27.00, 0.04),
        ("UNH",   520.00, 0.22), ("ABBV",  175.00, 0.10),
        ("MRK",   125.00, 0.08), ("LLY",   780.00, 0.30),
        ("BMY",    50.00, 0.05), ("GILD",   75.00, 0.06),
    ],
    "Energy": [
        ("XOM",   105.00, 0.07), ("CVX",   155.00, 0.09),
        ("COP",   115.00, 0.08), ("SLB",    45.00, 0.05),
        ("EOG",   115.00, 0.08), ("PXD",   225.00, 0.14),
        ("MPC",   170.00, 0.10), ("VLO",   145.00, 0.09),
    ],
    "Industrial": [
        ("CAT",   360.00, 0.15), ("HON",   200.00, 0.10),
        ("GE",    150.00, 0.08), ("BA",    190.00, 0.14),
        ("MMM",    95.00, 0.07), ("LMT",   450.00, 0.20),
        ("RTX",    95.00, 0.07), ("DE",    375.00, 0.16),
    ],
    "Staples": [
        ("PG",    165.00, 0.08), ("KO",     60.00, 0.04),
        ("PEP",   170.00, 0.09), ("WMT",   170.00, 0.09),
        ("CL",     90.00, 0.06), ("GIS",    65.00, 0.05),
        ("K",      65.00, 0.05), ("SYY",    80.00, 0.06),
    ],
    "Comms": [
        ("NFLX",  630.00, 0.28), ("DIS",    90.00, 0.07),
        ("CMCSA",  40.00, 0.04), ("T",      17.00, 0.03),
        ("VZ",     40.00, 0.04), ("TMUS",  160.00, 0.10),
        ("PARA",   15.00, 0.03), ("WBD",    10.00, 0.02),
    ],
    "Real Estate": [
        ("AMT",   195.00, 0.12), ("PLD",   120.00, 0.08),
        ("CCI",   105.00, 0.08), ("EQIX",  780.00, 0.32),
        ("PSA",   285.00, 0.14), ("DLR",   140.00, 0.09),
        ("O",      55.00, 0.05), ("SPG",   150.00, 0.10),
    ],
}

DEFAULT_SYMBOLS = [
    ("AAPL",  180.00, 0.10), ("MSFT",  420.00, 0.15),
    ("GOOG",  175.00, 0.12), ("META",  510.00, 0.20),
    ("NVDA",  900.00, 0.25), ("AMD",   160.00, 0.08),
    ("INTC",   31.00, 0.05), ("AVGO",  170.00, 0.18),
    ("AMZN",  185.00, 0.10), ("TSLA",  250.00, 0.30),
    ("JPM",   200.00, 0.08), ("GS",    470.00, 0.22),
    ("JNJ",   155.00, 0.06), ("PFE",    27.00, 0.04),
    ("XOM",   105.00, 0.07), ("CVX",   155.00, 0.09),
]

# Symbols 0-7 are LOCKED prices/spreads — must match NN training exactly
# User can assign any ticker name to these slots
LOCKED_PRICES = [
    (180.00, 0.10),
    (420.00, 0.15),
    (175.00, 0.12),
    (510.00, 0.20),
    (900.00, 0.25),
    (160.00, 0.08),
    ( 31.00, 0.05),
    (170.00, 0.18),
]

Q16 = 65536


def q16_16(val):
    return int(val * Q16) & 0xFFFFFFFF


def write_to_board(mmio, symbols):
    print("\nConfiguring Board A...")
    mmio.write(0x00, 0x02)
    time.sleep(0.1)
    for i, (ticker, mid, spread) in enumerate(symbols):
        mmio.write(0x10 + 4*i, q16_16(mid))
        mmio.write(0x50 + 4*i, q16_16(spread))
        print(f"  [{i:2d}] {ticker:5s}  mid=${mid:7.2f}  spread=${spread:.3f}")
    mmio.write(0xF0, len(symbols))
    mmio.write(0x04, 1000)
    mmio.write(0x08, 0xDEADBEEF)
    mmio.write(0x0C, 0)
    mmio.write(0x00, 0x01)
    time.sleep(0.3)
    running = bool(mmio.read(0xF4) & 0x01)
    print(f"\nBoard A running: {running}  Quotes: {mmio.read(0xF8)}")
    return running


def save_config(symbols, filename="symbols.json"):
    config = [{"ticker": t, "mid": m, "spread": s} for t, m, s in symbols]
    with open(filename, "w") as f:
        json.dump(config, f, indent=2)
    print(f"Saved {len(symbols)} symbols to {filename}")


def interactive_mode():
    sectors      = list(UNIVERSE.keys())
    chosen       = []        # final list of (ticker, mid, spread)
    used_tickers = set()

    print("\n" + "="*58)
    print("  Dual-FPGA Trading Engine — Symbol Picker")
    print("="*58)
    print("  Slots 0-7:  locked prices (NN trained values)")
    print("              You choose which companies fill these slots.")
    print("  Slots 8-15: free — choose any sector and stock.")
    print("="*58)

    # ── Phase 1: Pick names for locked price slots 0-7 ──────────
    print(f"\n  PHASE 1 — Pick 8 company names for the NN trading slots")
    print(f"  (prices and spreads are fixed by the trained model)\n")

    locked_prices = LOCKED_PRICES.copy()

    for slot in range(8):
        mid, spread = locked_prices[slot]
        print(f"\n  Slot {slot} — mid=${mid:.2f}  spread=${spread:.3f}")
        print(f"  Pick a sector:")
        for i, s in enumerate(sectors):
            available = sum(1 for stk in UNIVERSE[s] if stk[0] not in used_tickers)
            if available > 0:
                print(f"    [{i+1:2d}] {s:14s} ({available} available)")

        while True:
            raw = input(f"  Sector for slot {slot}: ").strip()
            try:
                idx = int(raw) - 1
                if idx < 0 or idx >= len(sectors):
                    print("  Invalid.")
                    continue
            except ValueError:
                print("  Invalid.")
                continue

            sector = sectors[idx]
            available = [s for s in UNIVERSE[sector] if s[0] not in used_tickers]
            if not available:
                print(f"  No stocks left in {sector}, pick another sector.")
                continue

            print(f"  {sector} stocks:")
            for i, (ticker, _, _) in enumerate(available):
                print(f"    [{i+1}] {ticker}")

            raw2 = input(f"  Pick stock for slot {slot}: ").strip()
            try:
                sidx = int(raw2) - 1
                if sidx < 0 or sidx >= len(available):
                    print("  Invalid.")
                    continue
            except ValueError:
                print("  Invalid.")
                continue

            ticker = available[sidx][0]
            chosen.append((ticker, mid, spread))
            used_tickers.add(ticker)
            print(f"  Slot {slot} → {ticker}  ${mid:.2f}  spread=${spread:.3f}")
            break

    # ── Phase 2: Pick 8 free stocks for slots 8-15 ───────────────
    print(f"\n  PHASE 2 — Pick 8 stocks for slots 8-15 (free choice)\n")

    while len(chosen) < 16:
        remaining = 16 - len(chosen)
        print(f"\n  Slots filled: {len(chosen)}/16  ({remaining} remaining)")
        print(f"  Chosen so far: {', '.join(t for t,_,_ in chosen)}")
        print(f"\n  Available sectors:")
        for i, s in enumerate(sectors):
            available = sum(1 for stk in UNIVERSE[s] if stk[0] not in used_tickers)
            if available > 0:
                print(f"    [{i+1:2d}] {s:14s} ({available} available)")
        print(f"    [ d] Done")

        raw = input("\n  Choose sector: ").strip().lower()

        if raw == 'd':
            if len(chosen) < 16:
                print(f"  Need {16 - len(chosen)} more symbols.")
                continue
            break

        try:
            idx = int(raw) - 1
            if idx < 0 or idx >= len(sectors):
                print("  Invalid.")
                continue
        except ValueError:
            print("  Invalid.")
            continue

        sector = sectors[idx]
        available = [s for s in UNIVERSE[sector] if s[0] not in used_tickers]

        if not available:
            print(f"  No stocks left in {sector}.")
            continue

        print(f"\n  {sector} — available stocks:")
        for i, (ticker, mid, spread) in enumerate(available):
            print(f"    [{i+1:2d}] {ticker:5s}  ${mid:7.2f}  spread=${spread:.3f}")

        max_n = min(len(available), remaining)
        print(f"\n  How many from {sector}? (1-{max_n})")
        try:
            count = int(input("  Count: ").strip())
        except ValueError:
            print("  Invalid.")
            continue

        if count < 1 or count > max_n:
            print(f"  Must be 1-{max_n}.")
            continue

        print(f"  Pick {count} stock(s) — enter numbers or 'top':")
        picks_raw = input("  Pick: ").strip().lower()

        if picks_raw == 'top':
            selected = available[:count]
        else:
            try:
                indices = [int(x)-1 for x in picks_raw.split()]
                if len(indices) != count or any(i < 0 or i >= len(available) for i in indices):
                    print("  Invalid.")
                    continue
                selected = [available[i] for i in indices]
            except ValueError:
                print("  Invalid.")
                continue

        for s in selected:
            chosen.append(s)
            used_tickers.add(s[0])
            print(f"  + {s[0]}  ${s[1]:.2f}")

        if len(chosen) == 16:
            print("\n  16 slots filled!")
            break

    print(f"\n{'='*58}")
    print(f"  Final selection:")
    for i, (t, m, s) in enumerate(chosen):
        print(f"    [{i:2d}] {t:5s}  ${m:7.2f}  spread=${s:.3f}")
    print(f"{'='*58}")

    confirm = input("\n  Confirm? (y/n): ").strip().lower()
    if confirm != 'y':
        print("  Cancelled.")
        return None
    return chosen


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--default", action="store_true",
                        help="Use default 16-stock S&P 500 universe")
    parser.add_argument("--start",   action="store_true",
                        help="Write config to Board A and start it")
    parser.add_argument("--config",  default="symbols.json",
                        help="Output config file (default: symbols.json)")
    args = parser.parse_args()

    if args.default:
        symbols = DEFAULT_SYMBOLS
        print(f"Using default 16-stock universe.")
    else:
        symbols = interactive_mode()
        if symbols is None:
            return

    save_config(symbols, args.config)

    if args.start:
        try:
            from pynq import Overlay, MMIO
            ol   = Overlay("overlays/board_a.bit")
            base = ol.ip_dict["hft_core"]["phys_addr"]
            rng  = ol.ip_dict["hft_core"]["addr_range"]
            mmio = MMIO(base, rng)
            write_to_board(mmio, symbols)
        except Exception as e:
            print(f"Could not write to Board A: {e}")
            print("Run the Jupyter notebook restart cell manually.")
    else:
        print("\nTo apply to hardware:")
        print("  python symbol_config.py --default --start")


if __name__ == "__main__":
    main()