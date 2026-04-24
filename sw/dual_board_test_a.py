"""
Dual-Board End-to-End Test — BOARD A SIDE
=========================================
Run this on the BOARD A Jupyter notebook FIRST. It puts Board A into a known,
deterministic configuration: 16 symbols, CALM regime, interval=1000.

After this runs successfully, switch to BOARD B's notebook and run
dual_board_test_b.py — that's where all the actual validation happens.

This script is intentionally minimal — it just brings A up and exposes a
report() function the user can call from the Board A notebook to print
A-side counters at any time during B's test.
"""

import time
from pynq import Overlay, MMIO

# ═══════════════════════════════════════════════════════════════════════════
# Board A register map
# ═══════════════════════════════════════════════════════════════════════════
A_CTRL             = 0x00
A_QUOTE_INTERVAL   = 0x04
A_LFSR_SEED        = 0x08
A_REGIME           = 0x0C
A_INIT_MID_BASE    = 0x10
A_INIT_SPREAD_BASE = 0x50
A_SECTOR_ID_BASE   = 0x90
A_TOKEN_BASE       = 0xD0
A_ACTIVE_SYM_COUNT = 0xF0
A_STATUS           = 0xF4
A_QUOTES_SENT      = 0xF8
A_ORDERS_RCVD      = 0xFC

NUM_SYM = 16
REGIME_NAMES = {0: 'CALM', 1: 'VOLATILE', 2: 'BURST', 3: 'ADVERSARIAL'}

def q16(v):
    return int(v * 65536) & 0xFFFFFFFF

# Auto-load overlay if not already in namespace
try:
    ol_a  # noqa: F821
except NameError:
    print("Loading Board A overlay (overlays/board_a.bit)...")
    ol_a = Overlay('overlays/board_a.bit')

base_a = ol_a.ip_dict['hft_core']['phys_addr']
span_a = ol_a.ip_dict['hft_core']['addr_range']
mmio_a = MMIO(base_a, span_a)


# ═══════════════════════════════════════════════════════════════════════════
# Standard 16-symbol market configuration
# ═══════════════════════════════════════════════════════════════════════════
SYMBOLS = [
    ('AAPL', 180.00, 0.10, 0), ('MSFT', 420.00, 0.15, 0),
    ('GOOG', 175.00, 0.12, 0), ('META', 510.00, 0.20, 0),
    ('NVDA', 900.00, 0.25, 1), ('AMD',  160.00, 0.08, 1),
    ('INTC',  31.00, 0.05, 1), ('AVGO', 170.00, 0.18, 1),
    ('AMZN', 185.00, 0.10, 2), ('TSLA', 250.00, 0.30, 2),
    ('JPM',  200.00, 0.08, 3), ('GS',   470.00, 0.22, 3),
    ('JNJ',  155.00, 0.06, 4), ('PFE',   27.00, 0.04, 4),
    ('XOM',  105.00, 0.07, 5), ('CVX',  155.00, 0.09, 5),
]


def setup(quote_interval=1000, regime=0, lfsr_seed=0xDEADBEEF):
    """Reset Board A, load 16 symbols, set regime, start the market sim."""
    mmio_a.write(A_CTRL, 0x02); time.sleep(0.05)
    for i, (sym, mid, spread, sect) in enumerate(SYMBOLS):
        mmio_a.write(A_INIT_MID_BASE    + 4*i, q16(mid))
        mmio_a.write(A_INIT_SPREAD_BASE + 4*i, q16(spread))
        mmio_a.write(A_SECTOR_ID_BASE   + 4*i, sect)
    mmio_a.write(A_QUOTE_INTERVAL,   quote_interval)
    mmio_a.write(A_LFSR_SEED,        lfsr_seed)
    mmio_a.write(A_REGIME,           regime)
    mmio_a.write(A_ACTIVE_SYM_COUNT, NUM_SYM)
    mmio_a.write(A_CTRL, 0x01); time.sleep(0.1)
    print(f"Board A configured & running:")
    print(f"  16 symbols loaded  |  interval={quote_interval}  |  "
          f"regime={REGIME_NAMES[regime]}")
    report()


def report():
    s = mmio_a.read(A_STATUS)
    qs = mmio_a.read(A_QUOTES_SENT)
    ord_r = mmio_a.read(A_ORDERS_RCVD)
    print(f"  STATUS=0x{s:08X}  running={bool(s & 1)}  link_up={bool(s & 2)}  "
          f"regime={REGIME_NAMES[(s >> 2) & 3]}")
    print(f"  quotes_sent = {qs:,}")
    print(f"  orders_rcvd = {ord_r:,}")
    return {'status': s, 'quotes_sent': qs, 'orders_rcvd': ord_r}


def set_regime(r):
    mmio_a.write(A_REGIME, r)
    print(f"Board A regime -> {REGIME_NAMES[r]}")


def reset():
    mmio_a.write(A_CTRL, 0x02); time.sleep(0.05)
    print("Board A reset")
    report()


# Run setup on import
setup()
print("\nReady. Now go to BOARD B's notebook and run dual_board_test_b.py.")
print("Use report() in this notebook anytime to see A's counters.")
print("Use set_regime(0|1|2|3) to change A's regime mid-test.")
