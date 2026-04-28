"""
common.py — Shared constants, frame formats, LFSR, and link layer.

This file contains everything that both Board A and Board B need:
  - System constants (how many symbols, price widths, etc.)
  - Frame dataclasses (QuoteFrame, OrderFrame, FillFrame) with exact
    bit-field layouts matching the RTL wire format
  - LFSR32 pseudo-random number generator (drives market noise)
  - LinkLayer model (simplified PMOD serial link as a delay queue)
  - Helper functions for Q16.16 fixed-point math
"""
from dataclasses import dataclass
from enum import IntEnum
from collections import deque

# ─────────────────────────────────────────────────────────────
# System Constants (mirrors rtl/shared/hft_pkg.sv)
# ─────────────────────────────────────────────────────────────

NUM_SYMBOLS = 16
NUM_SECTORS = 8
FRAME_W     = 128       # bits per frame on the wire

# Fixed-point format: Q16.16 means 16 integer bits + 16 fractional bits
# So $150.00 = 150 * 65536 = 0x0096_0000
MIN_PRICE = 0x0001_0000   # $1.00 in Q16.16
MAX_PRICE = 0x2710_0000   # $10,000.00 in Q16.16

# How many cycles a frame takes to cross the PMOD link
# Real hardware: 128 bits / 4 bits per nibble = 32 nibbles * 2 clocks = 64
LINK_DELAY = 64

# LFSR polynomial for random number generation
LFSR_TAPS = 0x00400007   # x^32 + x^22 + x^2 + x + 1

# Noise generator seed constants
GOLDEN          = 0x9E37_79B9
GLOBAL_SEED_XOR = 0xA11F_E511
SECTOR_SEED_XOR = 0xC13F_A9A9
DRIFT_SATURATION = 0x0000_1000  # max drift accumulator value (small for fast saturation)
PULLBACK_SHIFT   = 5            # mean-reversion spring: pull_back = (init - current) >> 5

# Latency histogram parameters
HIST_BINS = 16
BIN_SHIFT = 5  # each bin covers 2^5 = 32 cycles

# Bit masks (for keeping values within hardware widths)
MASK_16  = 0xFFFF
MASK_32  = 0xFFFF_FFFF
MASK_48  = 0xFFFF_FFFF_FFFF
MASK_128 = (1 << 128) - 1


# ─────────────────────────────────────────────────────────────
# Enums (match RTL encodings exactly)
# ─────────────────────────────────────────────────────────────

class MsgType(IntEnum):
    QUOTE = 0x1
    ORDER = 0x2
    FILL  = 0x3

class Regime(IntEnum):
    CALM        = 0   # small price moves, tight spread
    VOLATILE    = 1   # larger moves, wider spread
    BURST       = 2   # same as CALM (reserved for future)
    ADVERSARIAL = 3   # big moves, wide spread — stress test

class FillStatus(IntEnum):
    FILLED   = 0
    REJECTED = 1

SIDE_BUY  = 0
SIDE_SELL = 1

# Regime-dependent parameters: how much prices move and how wide the spread is
# step_size: multiplier for noise → price delta (Q16.16)
# base_spread: bid-ask spread width (Q16.16)
REGIME_PARAMS = {
    Regime.CALM:        {"step_size": 0x0000_0400, "base_spread": 0x0000_1000},
    Regime.VOLATILE:    {"step_size": 0x0000_8000, "base_spread": 0x0000_4000},
    Regime.BURST:       {"step_size": 0x0000_0400, "base_spread": 0x0000_1000},
    Regime.ADVERSARIAL: {"step_size": 0x0001_0000, "base_spread": 0x0000_8000},
}


# ─────────────────────────────────────────────────────────────
# Default Symbol Universe
#
# 16 symbols across 8 GICS sectors, mirroring real S&P 500 companies.
# On real hardware, the PYNQ script (config_symbols.py) writes these
# per-symbol values into AXI registers. Here we hardcode a realistic
# default so the golden model produces diverse, sector-correlated
# price movements out of the box.
#
# Sector ID mapping (matches config_symbols.py → board_a_axi_regs):
#   0 = Information Technology    4 = Financials
#   1 = Energy                    5 = Industrials
#   2 = Health Care               6 = Consumer Staples
#   3 = Consumer Discretionary    7 = Communication Services
# ─────────────────────────────────────────────────────────────

SYMBOL_UNIVERSE = [
    # slot  ticker   sector_id  init_price($)  init_spread($)
    {"ticker": "AAPL",  "sector_id": 0, "init_price": 180.00, "init_spread": 0.10},
    {"ticker": "MSFT",  "sector_id": 0, "init_price": 420.00, "init_spread": 0.15},
    {"ticker": "NVDA",  "sector_id": 0, "init_price": 900.00, "init_spread": 0.25},
    {"ticker": "XOM",   "sector_id": 1, "init_price": 115.00, "init_spread": 0.08},
    {"ticker": "CVX",   "sector_id": 1, "init_price": 160.00, "init_spread": 0.10},
    {"ticker": "JNJ",   "sector_id": 2, "init_price": 155.00, "init_spread": 0.08},
    {"ticker": "UNH",   "sector_id": 2, "init_price": 520.00, "init_spread": 0.20},
    {"ticker": "AMZN",  "sector_id": 3, "init_price": 185.00, "init_spread": 0.10},
    {"ticker": "TSLA",  "sector_id": 3, "init_price": 250.00, "init_spread": 0.30},
    {"ticker": "JPM",   "sector_id": 4, "init_price": 200.00, "init_spread": 0.10},
    {"ticker": "GS",    "sector_id": 4, "init_price": 480.00, "init_spread": 0.20},
    {"ticker": "CAT",   "sector_id": 5, "init_price": 360.00, "init_spread": 0.15},
    {"ticker": "HON",   "sector_id": 5, "init_price": 200.00, "init_spread": 0.10},
    {"ticker": "PG",    "sector_id": 6, "init_price": 165.00, "init_spread": 0.06},
    {"ticker": "KO",    "sector_id": 6, "init_price":  60.00, "init_spread": 0.04},
    {"ticker": "GOOGL", "sector_id": 7, "init_price": 175.00, "init_spread": 0.10},
]

SECTOR_NAMES = {
    0: "Tech", 1: "Energy", 2: "Health", 3: "Cons.Disc",
    4: "Financ.", 5: "Indust.", 6: "Staples", 7: "Comms",
}


def default_tickers() -> list[str]:
    return [s["ticker"] for s in SYMBOL_UNIVERSE]

def default_init_mids() -> list[int]:
    return [int(s["init_price"] * 65536) & MASK_32 for s in SYMBOL_UNIVERSE]

def default_init_spreads() -> list[int]:
    return [int(s["init_spread"] * 65536) & MASK_32 for s in SYMBOL_UNIVERSE]

def default_sector_ids() -> list[int]:
    return [s["sector_id"] for s in SYMBOL_UNIVERSE]


# ─────────────────────────────────────────────────────────────
# Fixed-Point Helpers
# ─────────────────────────────────────────────────────────────

def q16(dollars: float) -> int:
    """Convert a dollar amount to Q16.16 fixed-point (unsigned 32-bit)."""
    return int(dollars * 65536) & MASK_32

def from_q16(val: int) -> float:
    """Convert unsigned Q16.16 to float dollars."""
    return val / 65536.0

def sext32(val: int) -> int:
    """Sign-extend a 32-bit value to Python's arbitrary-precision int."""
    val &= MASK_32
    return val - 0x1_0000_0000 if val & 0x8000_0000 else val

def sext48(val: int) -> int:
    """Sign-extend a 48-bit value."""
    val &= MASK_48
    return val - 0x1_0000_0000_0000 if val & 0x8000_0000_0000 else val

def clamp(val, lo, hi):
    """Clamp a value to [lo, hi]."""
    return max(lo, min(hi, val))


# ─────────────────────────────────────────────────────────────
# Frame Dataclasses
#
# These represent the 128-bit frames that travel between boards.
# Each has to_bits() to pack into a 128-bit integer (matching RTL)
# and from_bits() to unpack. The bit positions are documented
# inline — these ARE the hardware wire format.
# ─────────────────────────────────────────────────────────────

@dataclass
class QuoteFrame:
    """A market quote: current bid/ask for one symbol.
    Sent by Board A (market simulator) to Board B (trader).

    128-bit layout:
      [127:124] msg_type = 0x1 (QUOTE)
      [123:116] symbol     8-bit symbol ID
      [115:114] regime     2-bit market regime
      [113:112] reserved   2'b00
      [111:80]  bid        32-bit Q16.16 best bid price
      [79:48]   ask        32-bit Q16.16 best ask price
      [47:32]   bid_size   16-bit quantity available at bid
      [31:16]   ask_size   16-bit quantity available at ask
      [15:0]    seq_num    16-bit per-symbol sequence number
    """
    symbol: int
    regime: int
    bid: int        # Q16.16
    ask: int        # Q16.16
    bid_size: int = 1000
    ask_size: int = 1000
    seq_num: int = 0

    @property
    def mid(self) -> int:
        """Mid-price = (bid + ask) / 2, in Q16.16."""
        return (self.bid + self.ask) >> 1

    @property
    def spread(self) -> int:
        """Spread = ask - bid, in Q16.16."""
        return self.ask - self.bid

    def to_bits(self) -> int:
        f  = (MsgType.QUOTE & 0xF) << 124
        f |= (self.symbol & 0xFF) << 116
        f |= (self.regime & 0x3) << 114
        f |= (self.bid & MASK_32) << 80
        f |= (self.ask & MASK_32) << 48
        f |= (self.bid_size & MASK_16) << 32
        f |= (self.ask_size & MASK_16) << 16
        f |= (self.seq_num & MASK_16)
        return f & MASK_128

    @classmethod
    def from_bits(cls, frame: int) -> "QuoteFrame":
        return cls(
            symbol   = (frame >> 116) & 0xFF,
            regime   = (frame >> 114) & 0x3,
            bid      = (frame >> 80)  & MASK_32,
            ask      = (frame >> 48)  & MASK_32,
            bid_size = (frame >> 32)  & MASK_16,
            ask_size = (frame >> 16)  & MASK_16,
            seq_num  = frame & MASK_16,
        )

    def __str__(self):
        return (f"QUOTE sym={self.symbol} bid=${from_q16(self.bid):.4f} "
                f"ask=${from_q16(self.ask):.4f} seq={self.seq_num}")


@dataclass
class OrderFrame:
    """A trade order: request to buy or sell.
    Sent by Board B (trader) to Board A (exchange).

    128-bit layout:
      [127:124] msg_type = 0x2 (ORDER)
      [123:116] symbol     8-bit symbol ID
      [115]     side       0=BUY, 1=SELL
      [114:112] reserved   3'b000
      [111:80]  price      32-bit Q16.16 limit price
      [79:64]   qty        16-bit quantity
      [63:48]   order_id   16-bit unique order identifier
      [47:32]   timestamp  16-bit cycle counter snapshot
      [31:0]    reserved   32'h0
    """
    symbol: int
    side: int       # 0=BUY, 1=SELL
    price: int      # Q16.16
    qty: int
    order_id: int = 0
    timestamp: int = 0

    def to_bits(self) -> int:
        f  = (MsgType.ORDER & 0xF) << 124
        f |= (self.symbol & 0xFF) << 116
        f |= (self.side & 0x1) << 115
        f |= (self.price & MASK_32) << 80
        f |= (self.qty & MASK_16) << 64
        f |= (self.order_id & MASK_16) << 48
        f |= (self.timestamp & MASK_16) << 32
        return f & MASK_128

    @classmethod
    def from_bits(cls, frame: int) -> "OrderFrame":
        return cls(
            symbol    = (frame >> 116) & 0xFF,
            side      = (frame >> 115) & 0x1,
            price     = (frame >> 80)  & MASK_32,
            qty       = (frame >> 64)  & MASK_16,
            order_id  = (frame >> 48)  & MASK_16,
            timestamp = (frame >> 32)  & MASK_16,
        )

    def __str__(self):
        side_s = "BUY" if self.side == SIDE_BUY else "SELL"
        return (f"ORDER {side_s} sym={self.symbol} price=${from_q16(self.price):.2f} "
                f"qty={self.qty} id={self.order_id}")


@dataclass
class FillFrame:
    """An execution report: order was filled or rejected.
    Sent by Board A (exchange) back to Board B (trader).

    128-bit layout:
      [127:124] msg_type = 0x3 (FILL)
      [123:116] symbol     8-bit symbol ID
      [115]     side       0=BUY, 1=SELL
      [114:112] status     3-bit (000=FILLED, 001=REJECTED)
      [111:80]  fill_price 32-bit Q16.16 execution price
      [79:64]   fill_qty   16-bit executed quantity
      [63:48]   order_id   16-bit echoed order identifier
      [47:32]   ts_echo    16-bit echoed timestamp (for latency measurement)
      [31:0]    reserved   32'h0
    """
    symbol: int
    side: int
    status: int     # FillStatus enum
    fill_price: int # Q16.16
    fill_qty: int
    order_id: int = 0
    ts_echo: int = 0

    @property
    def is_filled(self) -> bool:
        return self.status == FillStatus.FILLED

    def to_bits(self) -> int:
        f  = (MsgType.FILL & 0xF) << 124
        f |= (self.symbol & 0xFF) << 116
        f |= (self.side & 0x1) << 115
        f |= (self.status & 0x7) << 112
        f |= (self.fill_price & MASK_32) << 80
        f |= (self.fill_qty & MASK_16) << 64
        f |= (self.order_id & MASK_16) << 48
        f |= (self.ts_echo & MASK_16) << 32
        return f & MASK_128

    @classmethod
    def from_bits(cls, frame: int) -> "FillFrame":
        return cls(
            symbol     = (frame >> 116) & 0xFF,
            side       = (frame >> 115) & 0x1,
            status     = (frame >> 112) & 0x7,
            fill_price = (frame >> 80)  & MASK_32,
            fill_qty   = (frame >> 64)  & MASK_16,
            order_id   = (frame >> 48)  & MASK_16,
            ts_echo    = (frame >> 32)  & MASK_16,
        )

    def __str__(self):
        side_s = "BUY" if self.side == SIDE_BUY else "SELL"
        stat_s = "FILLED" if self.is_filled else "REJECTED"
        return (f"FILL {side_s} sym={self.symbol} {stat_s} "
                f"price=${from_q16(self.fill_price):.2f} qty={self.fill_qty}")


def frame_type(bits: int) -> int:
    """Extract msg_type [127:124] from a raw 128-bit frame."""
    return (bits >> 124) & 0xF


# ─────────────────────────────────────────────────────────────
# LFSR32 — Pseudo-Random Number Generator
#
# 32-bit Galois LFSR. The RTL uses this to drive market noise.
# Each symbol, sector, and global noise channel gets its own LFSR
# seeded with a different value derived from a base seed.
# ─────────────────────────────────────────────────────────────

class LFSR32:
    def __init__(self, seed: int = 1):
        self.reg = (seed & MASK_32) or 1  # zero maps to 1

    def step(self) -> int:
        """Advance the LFSR by one step. Returns the NEW value."""
        if self.reg & 1:
            self.reg = ((self.reg >> 1) ^ LFSR_TAPS) & MASK_32
        else:
            self.reg = (self.reg >> 1) & MASK_32
        return self.reg

    @property
    def value(self) -> int:
        return self.reg


# ─────────────────────────────────────────────────────────────
# LinkLayer — Simplified PMOD Serial Link
#
# On real hardware, the 4-bit PMOD link works like this:
#   1. A 128-bit frame is loaded into a shift register
#   2. Every 2 clock cycles, 4 bits (one nibble) are shifted out
#   3. 128 / 4 = 32 nibbles × 2 clocks each = 64 clock cycles total
#   4. The receiver reassembles nibbles back into a 128-bit frame
#
# This model skips the nibble-level detail and just delays frames
# by LINK_DELAY cycles. A frame goes in, comes out 64 cycles later.
# This preserves the latency behavior without the serialization code.
# ─────────────────────────────────────────────────────────────

class LinkLayer:
    def __init__(self, delay: int = LINK_DELAY):
        self.delay = delay
        self._queue: deque[tuple[int, int]] = deque()  # (frame_bits, deliver_at)
        self._free_at = 0  # cycle when the link finishes its current transmission

    def can_send(self, current_cycle: int) -> bool:
        """True if the link is idle and can accept a new frame."""
        return current_cycle >= self._free_at

    def send(self, frame_bits: int, current_cycle: int) -> bool:
        """Try to send a frame. Returns True if accepted, False if link busy.

        On real hardware, the serializer takes 64 cycles per frame.
        No new frame can be sent until the previous one finishes.
        """
        if current_cycle < self._free_at:
            return False  # link busy serializing previous frame
        self._queue.append((frame_bits, current_cycle + self.delay))
        self._free_at = current_cycle + self.delay  # busy for 64 cycles
        return True

    def receive(self, current_cycle: int) -> int | None:
        """Check if a frame has arrived. Returns raw 128-bit int or None."""
        if self._queue and self._queue[0][1] <= current_cycle:
            return self._queue.popleft()[0]
        return None

    @property
    def busy(self) -> bool:
        """True if a frame is currently in transit."""
        return len(self._queue) > 0


# ─────────────────────────────────────────────────────────────
# Self-test
# ─────────────────────────────────────────────────────────────

if __name__ == "__main__":
    # Test LFSR
    lfsr = LFSR32(0xDEAD_BEEF)
    vals = [lfsr.step() for _ in range(5)]
    assert all(0 < v <= MASK_32 for v in vals), "LFSR values out of range"
    print(f"LFSR first 5 values: {[f'0x{v:08X}' for v in vals]}")

    # Test frame round-trip
    q = QuoteFrame(symbol=3, regime=1, bid=q16(150.0), ask=q16(151.0))
    bits = q.to_bits()
    q2 = QuoteFrame.from_bits(bits)
    assert q2.symbol == 3 and q2.regime == 1
    assert q2.bid == q16(150.0) and q2.ask == q16(151.0)
    print(f"QuoteFrame round-trip: {q2}")

    o = OrderFrame(symbol=0, side=SIDE_BUY, price=q16(152.0), qty=100, order_id=1, timestamp=0xABCD)
    bits = o.to_bits()
    o2 = OrderFrame.from_bits(bits)
    assert o2.symbol == 0 and o2.side == SIDE_BUY and o2.qty == 100
    assert o2.timestamp == 0xABCD
    print(f"OrderFrame round-trip: {o2}")

    f = FillFrame(symbol=0, side=SIDE_BUY, status=FillStatus.FILLED,
                  fill_price=q16(151.0), fill_qty=100, order_id=1, ts_echo=0xABCD)
    bits = f.to_bits()
    f2 = FillFrame.from_bits(bits)
    assert f2.is_filled and f2.fill_qty == 100 and f2.ts_echo == 0xABCD
    print(f"FillFrame round-trip: {f2}")

    # Test link layer
    link = LinkLayer(delay=64)
    assert link.send(q.to_bits(), 0), "Should accept frame"
    assert not link.send(q.to_bits(), 1), "Should reject (link busy)"
    assert link.receive(63) is None, "Too early"
    got = link.receive(64)
    assert got is not None, "Should arrive at cycle 64"
    assert QuoteFrame.from_bits(got).symbol == 3
    assert link.send(q.to_bits(), 64), "Should accept again (link free)"
    print("LinkLayer delay + busy test passed")

    print("\nAll common.py tests PASSED")
