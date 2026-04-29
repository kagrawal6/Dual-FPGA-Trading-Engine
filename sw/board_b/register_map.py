"""
Board B Register Map — register_map.py
Shared constants for telemetry_server.py, live_monitor.py, and debug scripts.
Offsets match board_b_axi_regs.sv (Appendix D.2 of the design spec).

Address space: 10-bit byte address (1 KiB window) — bumped from 9-bit
to expose per-symbol BBO and per-symbol P&L arrays for the dashboard.
"""

# ── Config registers (R/W) ──────────────────────────────────────
CTRL           = 0x000
STRATEGY_SEL   = 0x004
THRESHOLD      = 0x008
EMA_ALPHA      = 0x00C
BASE_QTY       = 0x010
MAX_POSITION   = 0x014
MAX_ORDER_RATE = 0x018
MAX_LOSS       = 0x01C

# ── Status registers (R) ────────────────────────────────────────
STATUS         = 0x040
QUOTES_RCVD    = 0x044
ORDERS_SENT    = 0x048
FILLS_RCVD     = 0x04C
RISK_REJECTS   = 0x050
LINK_ERRORS    = 0x054

POS_BASE       = 0x058   # +4*i, 16 symbols → 0x058..0x094 (signed int32)
CASH_LO        = 0x098
CASH_HI        = 0x09C   # sign-extended upper 16 bits of 48-bit Q32.16

HIST_BASE      = 0x0A0   # +4*i, 16 bins → 0x0A0..0x0DC

LAT_MIN        = 0x0E0
LAT_MAX        = 0x0E4
LAT_SUM        = 0x0E8
LAT_COUNT      = 0x0EC

# ── Extended per-symbol arrays (added) ──────────────────────────
# Board B's view of the BBO (one link delay behind Board A — realistic trader view)
BID_BASE          = 0x100   # +4*i, 16 → 0x100..0x13C (Q16.16)
ASK_BASE          = 0x140   # +4*i, 16 → 0x140..0x17C (Q16.16)

# Per-symbol cash flow accumulator (Q32.16 signed, 48-bit packed lo/hi)
# Mark-to-market PnL per symbol = pnl_cash[i] + position[i] * mid[i]
PNL_CASH_LO_BASE  = 0x180   # +4*i, 16 → 0x180..0x1BC
PNL_CASH_HI_BASE  = 0x1C0   # +4*i, 16 → 0x1C0..0x1FC (sign-extended upper 16 bits)

# Last execution price per symbol (Q16.16)
LAST_FILL_BASE    = 0x200   # +4*i, 16 → 0x200..0x23C

# Per-symbol trade count, two 16-bit values packed per word
# Word j → trades[2*j] in [15:0], trades[2*j+1] in [31:16]
TRADES_PACK_BASE  = 0x240   # +4*j, 8 words → 0x240..0x25C

# ── B3 extensions ──────────────────────────────────────────────
# Per-symbol EMA snapshot from feature_compute (Q16.16). Tracks the strategy's
# fair-value estimate — useful for plotting alongside bid/ask to visualize
# mean-reversion in real time.
EMA_BASE          = 0x260   # +4*i, 16 → 0x260..0x29C

# Per-symbol last-signal classification, packed 8 symbols per 32-bit word.
# Word j: bits [4*k +: 4] = signal_code for symbol (8*j + k).
# Encoding: 0=NONE, 1=BUY, 2=SELL, 3=RISK_BLOCKED, others=reserved.
LAST_SIGNAL_PACK_BASE = 0x2A0  # +4*j, 2 words → 0x2A0, 0x2A4

# Most recent single latency sample (cycles), latched on each fill_processed.
# Distinct from LAT_MIN/MAX/SUM/COUNT which are aggregates.
LAST_LATENCY      = 0x2A8

# Last-signal encoding (used by laptop/dashboard.py)
LAST_SIGNAL_NONE          = 0
LAST_SIGNAL_BUY           = 1
LAST_SIGNAL_SELL          = 2
LAST_SIGNAL_RISK_BLOCKED  = 3
LAST_SIGNAL_LABELS = {
    LAST_SIGNAL_NONE:         "NONE",
    LAST_SIGNAL_BUY:          "BUY",
    LAST_SIGNAL_SELL:         "SELL",
    LAST_SIGNAL_RISK_BLOCKED: "RISK_BLOCKED",
}

NUM_SYMBOLS    = 16
NUM_HIST_BINS  = 16


# ── Helpers ──────────────────────────────────────────────────────
def q16_16(val):
    """Convert float to unsigned Q16.16 integer."""
    return int(val * 65536) & 0xFFFFFFFF


def from_q16_16(raw):
    """Convert unsigned Q16.16 integer to float."""
    return raw / 65536.0


def signed32(raw):
    """Interpret 32-bit unsigned as signed."""
    return raw - 0x100000000 if raw >= 0x80000000 else raw


def signed16(raw):
    """Interpret 16-bit unsigned as signed."""
    return raw - 0x10000 if raw >= 0x8000 else raw


def cash_q32_16(lo: int, hi: int) -> float:
    """Reconstruct a 48-bit signed Q32.16 cash value from lo/hi register reads.
    `hi` is the sign-extended upper 16 bits (the AXI register pads to 32).
    Returns the value in dollars (float)."""
    raw = ((hi & 0xFFFF) << 32) | (lo & 0xFFFFFFFF)
    if raw & (1 << 47):
        raw -= 1 << 48
    return raw / 65536.0


def read_trades_pack(mmio, sym_idx: int) -> int:
    """Unpack the per-symbol trade counter from the packed 32-bit register."""
    word = mmio.read(TRADES_PACK_BASE + 4 * (sym_idx // 2))
    return (word & 0xFFFF) if (sym_idx % 2 == 0) else ((word >> 16) & 0xFFFF)


def read_last_signal(mmio, sym_idx: int) -> int:
    """Unpack the per-symbol last-signal code (0..3) from the packed 32-bit
    register. Layout: word j packs 8 symbols × 4 bits."""
    word = mmio.read(LAST_SIGNAL_PACK_BASE + 4 * (sym_idx // 8))
    return (word >> (4 * (sym_idx % 8))) & 0xF


def last_signal_label(code: int) -> str:
    """Return a human-readable label for a last-signal code."""
    return LAST_SIGNAL_LABELS.get(code & 0xF, "RESERVED")
