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

# ADDITION: stable global token table (0..N-1) built from sorted tickers.
# This gives users a persistent numeric input form in addition to symbols.
COMPANY_TOKEN_BY_TICKER: Dict[str, int] = {
    ticker: idx for idx, ticker in enumerate(sorted(SYMBOL_DB.keys()))
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
