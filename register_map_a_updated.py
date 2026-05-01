#!/usr/bin/env python3
"""
register_map_a_updated.py — Board A AXI-Lite register map.
All addresses match board_a_axi_regs.sv exactly.
"""

# ── Write registers ──────────────────────────────────────────────
CTRL             = 0x000   # [0]=start_pulse, [1]=reset_pulse
QUOTE_INTERVAL   = 0x004   # cycles between quotes
LFSR_SEED        = 0x008   # loaded on IDLE→RUNNING
REGIME           = 0x00C   # [1:0] regime enum

INIT_MID_BASE    = 0x010   # init_mid[i]    at 0x010 + 4*i  (16 regs → 0x04C)
INIT_SPREAD_BASE = 0x050   # init_spread[i] at 0x050 + 4*i  (16 regs → 0x08C)
SECTOR_BASE      = 0x090   # sector_id[i]   at 0x090 + 4*i  (16 regs → 0x0CC)
TOKEN_BASE       = 0x0D0   # company tokens, 2 per word      (8  regs → 0x0EC)
ACTIVE_SYM_COUNT = 0x0F0   # [7:0] clamped to [1, 16]

# ── Read registers ───────────────────────────────────────────────
STATUS           = 0x0F4   # {fifo_fill[6:0], 5'd0, regime[1:0], link_up, running}
QUOTES_SENT      = 0x0F8
ORDERS_RCVD      = 0x0FC
FILLS_SENT       = 0x100   # (B3 added)
REJECTS_SENT     = 0x104   # (B3 added)
LINK_ERRORS      = 0x108   # (B3 added)

# B3: live price snapshots from market_sim (read-only)
LIVE_BID_BASE    = 0x110   # live_bid[i] at 0x110 + 4*i  (16 regs → 0x14C)
LIVE_ASK_BASE    = 0x150   # live_ask[i] at 0x150 + 4*i  (16 regs → 0x18C)
LIVE_MID_BASE    = 0x190   # live_mid[i] at 0x190 + 4*i  (16 regs → 0x1CC)

# ── Regime constants ─────────────────────────────────────────────
REGIME_CALM        = 0
REGIME_VOLATILE    = 1
REGIME_BURST       = 2
REGIME_ADVERSARIAL = 3

REGIME_NAMES = {
    REGIME_CALM:        "CALM",
    REGIME_VOLATILE:    "VOLATILE",
    REGIME_BURST:       "BURST",
    REGIME_ADVERSARIAL: "ADVERSARIAL",
}

NUM_SYMBOLS = 16
Q16         = 65536


def q16_16(val: float) -> int:
    """Convert float dollars to Q16.16 fixed-point integer."""
    return int(val * Q16) & 0xFFFFFFFF


def from_q16_16(raw: int) -> float:
    """Convert Q16.16 fixed-point integer to float dollars."""
    return raw / Q16


def decode_status(raw: int) -> dict:
    return {
        "running":      bool(raw & 0x01),
        "link_up":      bool((raw >> 1) & 0x01),
        "active_regime": (raw >> 2) & 0x03,
        "fifo_fill":    (raw >> 9) & 0x7F,
    }