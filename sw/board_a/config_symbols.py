"""
Addition: user-friendly symbol loader (tickers -> numeric metadata) for Board A.

What this code does:
1) User selects companies by GICS sector mix (counts summing to hw-slots), ticker/#row paste, CLI, Jupyter, or files.
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
from typing import Any, Dict, List, Optional

from pynq import Overlay, MMIO

from symbol_universe import (
    SYMBOL_DB,
    extract_sector_groups,
    line_is_catalog_row_token,
    normalize_symbol,
    ordered_sector_names,
    resolve_sector_choice,
    resolve_user_company_pick,
    ticker_for_token,
    tickers_grouped_by_sector,
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

STATUS      = 0xF4
QUOTES_SENT = 0xF8
ORDERS_RCVD = 0xFC

DEFAULT_HW_SLOTS = 16

REGIME_NAMES = {0: "CALM", 1: "VOLATILE", 2: "BURST", 3: "ADVERSARIAL"}


def q16_16(val: float) -> int:
    """Convert float to unsigned Q16.16 integer."""
    return int(val * 65536) & 0xFFFFFFFF


def read_board_a_status(mmio: MMIO) -> Dict[str, Any]:
    """Read and decode Board A status registers (STATUS, QUOTES_SENT, ORDERS_RCVD)."""
    raw = mmio.read(STATUS)
    return {
        "running":     bool(raw & 0x01),
        "link_up":     bool(raw & 0x02),
        "regime":      (raw >> 2) & 0x03,
        "regime_name": REGIME_NAMES.get((raw >> 2) & 0x03, "?"),
        "fifo_fill":   (raw >> 9) & 0x7F,
        "quotes_sent": mmio.read(QUOTES_SENT),
        "orders_rcvd": mmio.read(ORDERS_RCVD),
    }


def print_board_a_status(mmio: MMIO) -> None:
    s = read_board_a_status(mmio)
    print(f"  running     : {s['running']}")
    print(f"  link_up     : {s['link_up']}")
    print(f"  regime      : {s['regime']} ({s['regime_name']})")
    print(f"  fifo_fill   : {s['fifo_fill']}")
    print(f"  quotes_sent : {s['quotes_sent']}")
    print(f"  orders_rcvd : {s['orders_rcvd']}")


def parse_company_picks(text: str) -> List[str]:
    """
    Split pasted text (lines and/or spaces) into tickers.

    Each token may be a ticker (AAPL) or a catalog row number (42 or #42).
    Row numbers match ``universe_catalog.txt`` (alphabetical order).
    """
    out: List[str] = []
    for line in text.splitlines():
        for tok in line.split():
            out.append(resolve_user_company_pick(tok))
    return out


def parse_ticker_paste(text: str) -> List[str]:
    """Ticker-only paste (no #row). Prefer parse_company_picks for interactive/Jupyter."""
    parts: List[str] = []
    for line in text.splitlines():
        parts.extend(line.split())
    return [normalize_symbol(p) for p in parts if normalize_symbol(p)]


def validate_sector_allocation(
    allocation: Dict[str, int],
    hw_slots: int,
    groups: Dict[str, List[str]],
) -> None:
    total = sum(allocation.values())
    if total != hw_slots:
        raise ValueError(f"Sector counts must sum to exactly {hw_slots}, got {total}.")
    for name, k in allocation.items():
        if k < 0:
            raise ValueError(f"Negative count for {name}.")
        if name not in groups:
            raise ValueError(f"Unknown sector {name!r}.")
        if k > len(groups[name]):
            raise ValueError(
                f"Sector {name!r}: requested {k} but only {len(groups[name])} symbol(s) in universe."
            )


def sample_tickers_from_sector_allocation(
    allocation: Dict[str, int],
    rng: random.Random,
) -> List[str]:
    """For each sector, draw `k` distinct random tickers; shuffle combined list (length = sum k)."""
    groups = tickers_grouped_by_sector()
    picked: List[str] = []
    for name in sorted(allocation.keys()):
        k = allocation[name]
        if k <= 0:
            continue
        pool = list(groups[name])
        picked.extend(rng.sample(pool, k))
    rng.shuffle(picked)
    return picked


def parse_sector_mix_compact(spec: str, hw_slots: int) -> Dict[str, int]:
    """Parse 'Energy:6,Information Technology:10' (comma-separated Sector:count)."""
    names = ordered_sector_names()
    allocation: Dict[str, int] = {}
    for part in spec.split(","):
        part = part.strip()
        if not part:
            continue
        if ":" not in part:
            raise ValueError(f"Expected Sector:count in {part!r}")
        sec, _, cnt_s = part.rpartition(":")
        cnt = int(cnt_s.strip())
        name = resolve_sector_choice(sec.strip(), names)
        allocation[name] = allocation.get(name, 0) + cnt
    groups = tickers_grouped_by_sector()
    validate_sector_allocation(allocation, hw_slots, groups)
    return allocation


def parse_sector_mix_lines(text: str, hw_slots: int) -> Dict[str, int]:
    """
    One allocation per non-comment line: 'SectorName 4' or '3 4' or 'Energy:6'.
    Lines starting with # are comments unless #<digits> catalog row (ignored here).
    """
    names = ordered_sector_names()
    allocation: Dict[str, int] = {}
    for raw in text.splitlines():
        line = raw.strip()
        if not line:
            continue
        if line.startswith("#") and not line_is_catalog_row_token(line):
            continue
        if ":" in line:
            sec, _, cnt_s = line.rpartition(":")
            spec, cnt_s = sec.strip(), cnt_s.strip()
        else:
            parts = line.rsplit(None, 1)
            if len(parts) != 2:
                raise ValueError(f"Bad line {raw!r}: use 'SectorName count' or 'Sector:count'")
            spec, cnt_s = parts[0].strip(), parts[1].strip()
        cnt = int(cnt_s)
        name = resolve_sector_choice(spec, names)
        allocation[name] = allocation.get(name, 0) + cnt
    groups = tickers_grouped_by_sector()
    validate_sector_allocation(allocation, hw_slots, groups)
    return allocation


def sector_mix_intro_text(hw_slots: int) -> str:
    groups = tickers_grouped_by_sector()
    names = ordered_sector_names()
    nsec = len(names)
    lines = [
        f"There are {nsec} sectors in the universe. You assign counts per sector that sum to exactly {hw_slots}.",
        "Companies are then chosen uniformly at random within each sector (no replacement).",
        "Any feasible split is allowed (e.g. two sectors only: 10 + 6, or many sectors with smaller counts).",
        "",
        "Sector list (#, symbol count, name):",
    ]
    for i, name in enumerate(names, start=1):
        lines.append(f"  {i:2d}. ({len(groups[name]):3d} symbols)  {name}")
    return "\n".join(lines)


def prompt_sector_mix_dialog(hw_slots: int, random_seed: Optional[int]) -> List[str]:
    groups = tickers_grouped_by_sector()
    names = ordered_sector_names()
    print(sector_mix_intro_text(hw_slots))
    allocation: Dict[str, int] = {}
    print(f"\nEnter assignments until all {hw_slots} slots are filled.")
    print("Each line:  <sector # or partial name>  <count>")
    print("Example:  `Energy 6`  or  `3 10`  (sector #3, ten companies)\n")

    while sum(allocation.values()) < hw_slots:
        rem = hw_slots - sum(allocation.values())
        line = input(f"Slots left {rem}/{hw_slots} — sector and count> ").strip()
        if not line:
            raise ValueError("Incomplete sector mix (empty line).")
        parts = line.rsplit(None, 1)
        if len(parts) != 2:
            print("Need two fields: sector (number or name) and count.")
            continue
        spec, cnt_s = parts[0], parts[1]
        try:
            cnt = int(cnt_s)
        except ValueError:
            print("Second field must be an integer.")
            continue
        if cnt < 0 or cnt > rem:
            print(f"Count must be between 0 and {rem}.")
            continue
        if cnt == 0:
            continue
        try:
            name = resolve_sector_choice(spec, names)
        except ValueError as e:
            print(e)
            continue
        already = allocation.get(name, 0)
        cap = len(groups[name])
        if already + cnt > cap:
            print(f"{name}: can take at most {cap - already} more (already {already}, universe {cap}).")
            continue
        allocation[name] = already + cnt

    validate_sector_allocation(allocation, hw_slots, groups)
    seed_in = input("Random seed within sectors (Enter = nondeterministic): ").strip()
    seed: Optional[int] = int(seed_in) if seed_in else random_seed
    rng = random.Random(seed)
    picks = sample_tickers_from_sector_allocation(allocation, rng)
    print("\nSelected tickers (random within each sector):")
    for t in picks:
        print(f"  {t}")
    return picks


def prepare_loaded_symbols(
    selected: List[str],
    hw_slots: int,
    allow_truncate: bool,
    init_spread_default: float,
) -> List[dict[str, Any]]:
    """
    Validate tickers against SYMBOL_DB, apply hw slot limit, return per-slot dicts
    for printing and MMIO (same shape as the rest of this module).
    """
    if not selected:
        raise ValueError("No valid tickers provided.")

    if len(selected) > hw_slots and not allow_truncate:
        raise ValueError(
            f"Too many symbols ({len(selected)}). Hardware slots={hw_slots}. "
            "Use --allow-truncate to proceed."
        )
    selected = selected[:hw_slots]

    loaded: List[dict[str, Any]] = []
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
                "init_spread": float(info.get("init_spread", init_spread_default)),
            }
        )
    return loaded


def print_configuration_summary(loaded: List[dict[str, Any]], hw_slots: int) -> None:
    print(f"Loaded {len(loaded)} symbols (hw_slots={hw_slots}):")
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

    by_sector_name = Counter(x["sector"] for x in loaded)
    by_sector_id = Counter(x["sector_id"] for x in loaded)
    print("Sector population (hardware sector_id counts — used for noise gain):")
    for sid in sorted(by_sector_id.keys()):
        print(f"  sector_id {sid}: {by_sector_id[sid]} symbol(s)")
    print("Sector population (by name, demo / debug):")
    for name, cnt in sorted(by_sector_name.items(), key=lambda z: (-z[1], z[0])):
        print(f"  {name}: {cnt}")


def write_mmio_board_config(
    mmio: MMIO,
    loaded: List[dict[str, Any]],
    hw_slots: int,
    *,
    write_sector_id: bool,
    write_token_id: bool,
    init_spread_default: float,
    pulse_start: bool,
    quote_interval: int = 1000,
    lfsr_seed: int = 0xDEADBEEF,
    regime: int = 0,
) -> None:
    mmio.write(QUOTE_INTERVAL, quote_interval)
    mmio.write(LFSR_SEED, lfsr_seed)
    mmio.write(REGIME, regime & 0x3)
    mmio.write(ACTIVE_SYM_COUNT, len(loaded))

    for i in range(hw_slots):
        if i < len(loaded):
            init_mid = loaded[i]["init_price"]
            init_spread = loaded[i]["init_spread"]
            sector_id = loaded[i]["sector_id"]
            company_token = loaded[i]["company_token"]
        else:
            init_mid = 0.0
            init_spread = float(init_spread_default)
            sector_id = 0
            company_token = 0

        mmio.write(INIT_MID_BASE + 4 * i, q16_16(init_mid))
        mmio.write(INIT_SPREAD_BASE + 4 * i, q16_16(init_spread))

        if write_sector_id:
            mmio.write(SECTOR_ID_BASE + 4 * i, int(sector_id))
        if write_token_id:
            token_reg = TOKEN_BASE + 4 * (i // 2)
            if i % 2 == 0:
                packed = int(company_token) & 0xFFFF
                if (i + 1) < hw_slots:
                    nxt = loaded[i + 1]["company_token"] if (i + 1) < len(loaded) else 0
                    packed |= (int(nxt) & 0xFFFF) << 16
                mmio.write(token_reg, packed)

    if pulse_start:
        mmio.write(CTRL, 0x01)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Load ticker/token metadata into Board A (supports random 8-16 company selection)."
    )
    parser.add_argument(
        "--interactive",
        action="store_true",
        help="Prompt on stdin: sector mix (fills --hw-slots) or full-universe random sample (laptop SSH).",
    )
    group = parser.add_mutually_exclusive_group(required=False)
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
    group.add_argument(
        "--sector-mix",
        type=str,
        help='Allocate all hw-slots by GICS sector, e.g. "Energy:6,Information Technology:10" (must sum to --hw-slots).',
    )
    group.add_argument(
        "--sector-mix-file",
        type=str,
        help="File with sector lines: 'SectorName count' or 'Sector:count'; counts must sum to --hw-slots.",
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
    parser.add_argument("--start", action="store_true", help="Pulse CTRL[0] after writing config.")
    parser.add_argument("--reset", action="store_true", help="Pulse CTRL[1] (reset FSM) before writing config. Use to reconfigure a running board.")
    parser.add_argument(
        "--status",
        action="store_true",
        help="Read and print Board A status registers, then exit (no configuration).",
    )
    parser.add_argument("--random-seed", type=int, default=None, help="Seed for deterministic random selection.")

    parser.add_argument(
        "--write-sector-id",
        action="store_true",
        default=True,
        help="Write SYM*_SECTOR_ID registers (default: on).",
    )
    parser.add_argument(
        "--no-write-sector-id",
        dest="write_sector_id",
        action="store_false",
        help="Skip writing SYM*_SECTOR_ID registers.",
    )
    parser.add_argument(
        "--write-token-id",
        action="store_true",
        default=True,
        help="Write SYM*_TOKEN registers (default: on).",
    )
    parser.add_argument(
        "--no-write-token-id",
        dest="write_token_id",
        action="store_false",
        help="Skip writing SYM*_TOKEN registers.",
    )
    parser.add_argument(
        "--init-spread-default",
        type=float,
        default=0.125,
        help="Default init_spread (Q16.16) for symbols if not otherwise specified by SYMBOL_DB.",
    )
    parser.add_argument(
        "--quote-interval",
        type=int,
        default=1000,
        help="Clock cycles between consecutive quote rounds (0 = every cycle, fastest). RTL default: 1000.",
    )
    parser.add_argument(
        "--lfsr-seed",
        type=lambda x: int(x, 0),
        default=0xDEADBEEF,
        help="32-bit PRNG seed for market noise (hex or decimal). RTL default: 0xDEADBEEF.",
    )
    parser.add_argument(
        "--regime",
        type=int,
        default=0,
        choices=[0, 1, 2, 3],
        help="Market regime: 0=CALM, 1=VOLATILE, 2=BURST, 3=ADVERSARIAL. Overridden by SW[2] on board.",
    )
    args = parser.parse_args()

    has_cli = (
        args.symbols is not None
        or args.tokens is not None
        or args.symbols_file is not None
        or args.random_count is not None
        or args.sector_mix is not None
        or args.sector_mix_file is not None
    )
    if args.status:
        if args.interactive or has_cli:
            parser.error("--status is standalone: do not combine with symbol selection flags.")
        return args
    if args.interactive and has_cli:
        parser.error(
            "Do not combine --interactive with other selection flags "
            "(--symbols / --tokens / --symbols-file / --random-count / --sector-mix / --sector-mix-file)."
        )
    if not args.interactive and not has_cli:
        parser.error(
            "Choose one: --status OR --interactive OR --symbols OR --tokens OR --symbols-file OR "
            "--random-count OR --sector-mix OR --sector-mix-file."
        )
    return args


def prompt_interactive(hw_slots: int, random_seed: int | None) -> List[str]:
    """
    Ask the user (stdin) for sector mix or full-universe random sample.
    Sector path always fills exactly `hw_slots` companies (default 16).
    """
    print(
        f"\nBoard A — interactive load: exactly {hw_slots} active symbols "
        f"(universe has {len(SYMBOL_DB)} tickers).\n"
    )
    print("  1) Sector mix — you choose how many from each sector (totals to full slot count); companies random within sector")
    print(f"  2) Fully random — uniform random {hw_slots} companies from entire universe (ignore sectors)")
    choice = ""
    while choice not in ("1", "2"):
        choice = input("Enter 1 or 2: ").strip()

    if choice == "2":
        seed_in = input("Random seed (Enter for nondeterministic): ").strip()
        seed: int | None = int(seed_in) if seed_in else random_seed
        rng = random.Random(seed)
        universe = sorted(SYMBOL_DB.keys())
        if hw_slots > len(universe):
            raise ValueError(f"hw_slots={hw_slots} exceeds universe size {len(universe)}.")
        return rng.sample(universe, hw_slots)

    return prompt_sector_mix_dialog(hw_slots, random_seed)


def load_symbols_from_file(path: str) -> List[str]:
    """Load picks from lines; supports tickers and #row. Lines starting with # are comments unless #<digits> only."""
    out: List[str] = []
    with open(path, "r", encoding="utf-8") as f:
        for line in f:
            s = line.strip()
            if not s:
                continue
            if s.startswith("#") and not line_is_catalog_row_token(s):
                continue
            for tok in s.split():
                out.append(resolve_user_company_pick(tok))
    return out


def main() -> None:
    args = parse_args()

    if args.hw_slots < 1:
        raise ValueError("--hw-slots must be >= 1.")

    ol = Overlay("overlays/board_a.bit")
    mmio = MMIO(ol.ip_dict["hft_core"]["phys_addr"],
                ol.ip_dict["hft_core"]["addr_range"])

    if args.status:
        print("Board A status:")
        print_board_a_status(mmio)
        return

    if args.reset:
        print("Resetting Board A FSM (CTRL[1] pulse)...")
        mmio.write(CTRL, 0x02)

    if args.interactive:
        selected = prompt_interactive(args.hw_slots, args.random_seed)
    elif args.symbols_file:
        selected = load_symbols_from_file(args.symbols_file)
    elif args.sector_mix is not None:
        alloc = parse_sector_mix_compact(args.sector_mix, args.hw_slots)
        rng = random.Random(args.random_seed)
        selected = sample_tickers_from_sector_allocation(alloc, rng)
    elif args.sector_mix_file is not None:
        with open(args.sector_mix_file, encoding="utf-8") as f:
            alloc = parse_sector_mix_lines(f.read(), args.hw_slots)
        rng = random.Random(args.random_seed)
        selected = sample_tickers_from_sector_allocation(alloc, rng)
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
        selected = [resolve_user_company_pick(s) for s in args.symbols]

    loaded = prepare_loaded_symbols(
        selected,
        args.hw_slots,
        args.allow_truncate,
        args.init_spread_default,
    )
    print_configuration_summary(loaded, args.hw_slots)

    print(f"\nGlobal config: quote_interval={args.quote_interval}, "
          f"lfsr_seed=0x{args.lfsr_seed:08X}, regime={REGIME_NAMES[args.regime]}")

    write_mmio_board_config(
        mmio,
        loaded,
        args.hw_slots,
        write_sector_id=args.write_sector_id,
        write_token_id=args.write_token_id,
        init_spread_default=args.init_spread_default,
        pulse_start=args.start,
        quote_interval=args.quote_interval,
        lfsr_seed=args.lfsr_seed,
        regime=args.regime,
    )
    if args.start:
        print("Board A started.")
    print("\nPost-config status:")
    print_board_a_status(mmio)


if __name__ == "__main__":
    main()
