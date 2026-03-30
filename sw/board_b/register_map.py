"""
Board B Register Map — register_map.py
Shared constants for telemetry_server.py and debug scripts.
Offsets match board_b_axi_regs.sv (Appendix D.2 of the design spec).
"""

# Config registers (R/W)
CTRL           = 0x00
STRATEGY_SEL   = 0x04
THRESHOLD      = 0x08
EMA_ALPHA      = 0x0C
BASE_QTY       = 0x10
MAX_POSITION   = 0x14
MAX_ORDER_RATE = 0x18
MAX_LOSS       = 0x1C

# Status registers (R)
STATUS         = 0x40
QUOTES_RCVD    = 0x44
ORDERS_SENT    = 0x48
FILLS_RCVD     = 0x4C
RISK_REJECTS   = 0x50
LINK_ERRORS    = 0x54

POS_BASE       = 0x58   # +4*i, 16 symbols → 0x58..0x94
CASH_LO        = 0x98
CASH_HI        = 0x9C

HIST_BASE      = 0xA0   # +4*i, 16 bins → 0xA0..0xDC

LAT_MIN        = 0xE0
LAT_MAX        = 0xE4
LAT_SUM        = 0xE8
LAT_COUNT      = 0xEC

NUM_SYMBOLS    = 16
NUM_HIST_BINS  = 16


def q16_16(val):
    """Convert float to unsigned Q16.16 integer."""
    return int(val * 65536) & 0xFFFFFFFF


def from_q16_16(raw):
    """Convert unsigned Q16.16 integer to float."""
    return raw / 65536.0


def signed32(raw):
    """Interpret 32-bit unsigned as signed."""
    return raw - 0x100000000 if raw >= 0x80000000 else raw
