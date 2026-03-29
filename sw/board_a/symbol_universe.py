"""
Addition: user-friendly ticker -> sector mapping database for Board A.

What this code does:
1) Provides `SYMBOL_DB`, mapping ticker symbols to:
   - `sector` (human-readable)
   - `sector_id` (compact numeric for RTL storage)
   - `init_price` (initial mid price in dollars)
2) Supplies small helpers used by `config_symbols.py`.

This matches the PDF proposal:
 - Hardware should receive only structured numeric values (sector_id + init_price),
   while software owns the string/ticker UX.
"""

from __future__ import annotations

import csv
import io
import urllib.request
import re
from collections import defaultdict
from typing import Dict, List


# Full constituents source (ticker + sector):
# https://github.com/datasets/s-and-p-500-companies
SP500_CSV_URL = "https://raw.githubusercontent.com/datasets/s-and-p-500-companies/master/data/constituents.csv"

# Deterministic sector baseline initial prices.
SECTOR_DEFAULT_INIT_PRICE = {
    "Communication Services": 140.0,
    "Consumer Discretionary": 180.0,
    "Consumer Staples": 90.0,
    "Energy": 120.0,
    "Financials": 130.0,
    "Health Care": 150.0,
    "Industrials": 110.0,
    "Information Technology": 220.0,
    "Materials": 95.0,
    "Real Estate": 85.0,
    "Utilities": 70.0,
}

# Offline fallback so scripts still work without network.
_FALLBACK_DB: Dict[str, Dict[str, object]] = {
    "AAPL": {"sector": "Information Technology", "sector_id": 0, "init_price": 180.00},
    "MSFT": {"sector": "Information Technology", "sector_id": 0, "init_price": 420.00},
    "NVDA": {"sector": "Information Technology", "sector_id": 0, "init_price": 900.00},
    "XOM": {"sector": "Energy", "sector_id": 1, "init_price": 115.00},
    "CVX": {"sector": "Energy", "sector_id": 1, "init_price": 160.00},
    "JPM": {"sector": "Financials", "sector_id": 2, "init_price": 200.00},
}


def normalize_symbol(sym: str) -> str:
    """Normalize user input into an uppercase ticker."""
    return sym.strip().upper()


def _download_sp500_rows() -> List[Dict[str, str]]:
    """Download S&P500 constituents CSV and return parsed rows."""
    req = urllib.request.Request(
        SP500_CSV_URL,
        headers={"User-Agent": "Dual-FPGA-Trading-Engine/1.0"},
    )
    with urllib.request.urlopen(req, timeout=8) as resp:
        raw = resp.read().decode("utf-8")
    return list(csv.DictReader(io.StringIO(raw)))


def _build_symbol_db_from_rows(rows: List[Dict[str, str]]) -> Dict[str, Dict[str, object]]:
    """Build SYMBOL_DB from CSV rows (Symbol + GICS Sector)."""
    sectors = sorted({r["GICS Sector"].strip() for r in rows if r.get("GICS Sector")})
    sector_to_id = {sector: idx for idx, sector in enumerate(sectors)}

    out: Dict[str, Dict[str, object]] = {}
    for row in rows:
        symbol_raw = row.get("Symbol", "")
        sector = row.get("GICS Sector", "").strip()
        if not symbol_raw or not sector:
            continue
        symbol = normalize_symbol(symbol_raw.replace(".", "-"))
        init_price = float(SECTOR_DEFAULT_INIT_PRICE.get(sector, 100.0))
        out[symbol] = {
            "sector": sector,
            "sector_id": sector_to_id[sector],
            "init_price": init_price,
            "company_name": row.get("Security", "").strip(),
        }

    return out


def _build_symbol_db() -> Dict[str, Dict[str, object]]:
    """
    Build full SYMBOL_DB.

    Priority:
    1) Full S&P 500 list from remote CSV.
    2) Small offline fallback list.
    """
    try:
        rows = _download_sp500_rows()
        db = _build_symbol_db_from_rows(rows)
        if db:
            return db
    except Exception:
        pass
    return dict(_FALLBACK_DB)


# ADDITION: full S&P500-aware database used by config scripts.
SYMBOL_DB: Dict[str, Dict[str, object]] = _build_symbol_db()

# One canonical ordering: alphabetical ticker = sheet row order for user picks (#N) and company_token.
ORDERED_TICKERS: List[str] = sorted(SYMBOL_DB.keys())

# ADDITION: stable global token table (0..N-1) aligned with ORDERED_TICKERS.
# This gives users a persistent numeric input form in addition to symbols.
COMPANY_TOKEN_BY_TICKER: Dict[str, int] = {
    ticker: idx for idx, ticker in enumerate(ORDERED_TICKERS)
}
TICKER_BY_COMPANY_TOKEN: Dict[int, str] = {
    token: ticker for ticker, token in COMPANY_TOKEN_BY_TICKER.items()
}

# ADDITION: enrich entries in-place for convenience (`SYMBOL_DB[t]["company_token"]`).
for _ticker, _token in COMPANY_TOKEN_BY_TICKER.items():
    SYMBOL_DB[_ticker]["company_token"] = _token


def token_for_ticker(sym: str) -> int:
    """Return stable global token for a ticker."""
    s = normalize_symbol(sym)
    if s not in COMPANY_TOKEN_BY_TICKER:
        raise ValueError(f"Unknown symbol: {s}")
    return COMPANY_TOKEN_BY_TICKER[s]


def ticker_for_token(token: int) -> str:
    """Return ticker symbol for a stable global token."""
    if token not in TICKER_BY_COMPANY_TOKEN:
        raise ValueError(f"Unknown token: {token}")
    return TICKER_BY_COMPANY_TOKEN[token]


def catalog_row_to_ticker(one_based_row: int) -> str:
    """Map printed catalog row (1..N) to ticker; same order as ORDERED_TICKERS / company_token."""
    if one_based_row < 1 or one_based_row > len(ORDERED_TICKERS):
        raise ValueError(f"Catalog row must be 1..{len(ORDERED_TICKERS)}, got {one_based_row}")
    return ORDERED_TICKERS[one_based_row - 1]


def resolve_user_company_pick(raw: str) -> str:
    """
    Resolve one user token to a normalized ticker.

    Accepts:
    - Ticker symbol, e.g. AAPL, brk-b
    - Catalog row: 42 or #42 (1-based index in ORDERED_TICKERS — alphabetical list)

    Row numbers match ``universe_catalog.txt`` and printed excerpts.
    """
    s = raw.strip()
    if not s:
        raise ValueError("empty pick")
    sym_try = normalize_symbol(s)
    if sym_try in SYMBOL_DB:
        return sym_try
    num_part = s[1:].strip() if s.startswith("#") else s
    if num_part.isdigit():
        n = int(num_part)
        return catalog_row_to_ticker(n)
    raise ValueError(f"Unknown company {raw!r}: not a ticker and not a catalog row 1..{len(ORDERED_TICKERS)}")


def write_universe_catalog(path: str = "universe_catalog.txt") -> str:
    """
    Write full numbered list: row, ticker, company name (when known).
    Same row numbers as resolve_user_company_pick (#N).
    """
    with open(path, "w", encoding="utf-8") as f:
        f.write("Row   Ticker   Company\n")
        for i, t in enumerate(ORDERED_TICKERS, start=1):
            name = str(SYMBOL_DB[t].get("company_name", t))
            f.write(f"{i:5d}  {t:6s}  {name}\n")
    return path


def catalog_excerpt_lines(max_head: int = 20, max_tail: int = 5) -> List[str]:
    """Short numbered lines for terminal display (head + tail if universe is large)."""
    n = len(ORDERED_TICKERS)
    lines: List[str] = []
    head = min(max_head, n)
    for i in range(head):
        t = ORDERED_TICKERS[i]
        name = str(SYMBOL_DB[t].get("company_name", t))
        lines.append(f"  {i + 1:5d}  {t:6s}  {name}")
    if n > head + max_tail:
        lines.append(f"  ... ({n - head - max_tail} rows omitted) ...")
        for j in range(max(0, n - max_tail), n):
            t = ORDERED_TICKERS[j]
            name = str(SYMBOL_DB[t].get("company_name", t))
            lines.append(f"  {j + 1:5d}  {t:6s}  {name}")
    elif n > head:
        for j in range(head, n):
            t = ORDERED_TICKERS[j]
            name = str(SYMBOL_DB[t].get("company_name", t))
            lines.append(f"  {j + 1:5d}  {t:6s}  {name}")
    return lines


_ROW_ONLY = re.compile(r"^#\s*\d+\s*$")


def line_is_catalog_row_token(line: str) -> bool:
    """True if whole line is only '#42' style (not a free-text comment)."""
    return bool(_ROW_ONLY.match(line.strip()))


def tickers_grouped_by_sector() -> Dict[str, List[str]]:
    """All tickers in SYMBOL_DB grouped by GICS sector name (sorted tickers per sector)."""
    g: Dict[str, List[str]] = defaultdict(list)
    for t, info in SYMBOL_DB.items():
        sector = str(info["sector"])
        g[sector].append(t)
    for sector in g:
        g[sector].sort()
    return dict(sorted(g.items(), key=lambda x: x[0].lower()))


def ordered_sector_names() -> List[str]:
    return list(tickers_grouped_by_sector().keys())


def resolve_sector_choice(user_input: str, canonical_names: List[str]) -> str:
    """
    Map user text to a canonical sector name: 1-based index, exact name, unique prefix, or unique substring.
    """
    u = user_input.strip()
    if not u:
        raise ValueError("empty sector name")
    if u.isdigit():
        idx = int(u)
        if 1 <= idx <= len(canonical_names):
            return canonical_names[idx - 1]
        raise ValueError(f"Sector # must be 1..{len(canonical_names)}")
    ul = u.lower()
    exact = [c for c in canonical_names if c.lower() == ul]
    if len(exact) == 1:
        return exact[0]
    pref = [c for c in canonical_names if c.lower().startswith(ul)]
    if len(pref) == 1:
        return pref[0]
    sub = [c for c in canonical_names if ul in c.lower()]
    if len(sub) == 1:
        return sub[0]
    if len(sub) > 1:
        raise ValueError(f"Ambiguous sector {user_input!r}: try a longer name or the list number. Matches: {sub[:6]}")
    raise ValueError(f"Unknown sector {user_input!r}")


def get_symbol_info(sym: str) -> Dict[str, object]:
    """Return the SYMBOL_DB entry for `sym` or raise ValueError."""
    sym_n = normalize_symbol(sym)
    if sym_n not in SYMBOL_DB:
        raise ValueError(f"Unknown symbol: {sym_n}")
    return SYMBOL_DB[sym_n]


def sector_name_by_id() -> Dict[int, str]:
    """Build a sector_id -> sector name mapping from SYMBOL_DB."""
    out: Dict[int, str] = {}
    for info in SYMBOL_DB.values():
        sid = int(info["sector_id"])
        name = str(info["sector"])
        out[sid] = name
    return out


def extract_sector_groups(tickers: List[str]) -> Dict[str, List[str]]:
    """
    Group tickers by sector name.

    Returns:
      { "Technology": ["AAPL", "MSFT", ...], "Energy": [...] }
    """
    groups: Dict[str, List[str]] = {}
    for t in tickers:
        info = get_symbol_info(t)
        sector = str(info["sector"])
        groups.setdefault(sector, []).append(normalize_symbol(t))
    return groups
