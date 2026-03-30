"""
board_b.py — Board B: Trading Pipeline

Board B is the "trader side." When a quote arrives, it flows through
a pipeline of modules that decide whether to trade:

  QuoteFrame arrives
       │
       ▼
  QuoteBook — stores latest bid/ask for each symbol
       │
       ▼
  FeatureEngine — computes EMA (smoothed average) and deviation from it
       │
       ▼
  Strategy — if price deviates enough from EMA, generate a trade signal
       │
       ▼
  RiskManager — check position limits, order rate, max loss
       │
       ▼
  OrderBuilder — pack the approved trade into an OrderFrame
       │
       ▼
  → sent over PMOD link back to Board A

When a FillFrame comes back from Board A:
  FillFrame arrives
       │
       ▼
  PositionTracker — update position and cash
       │
       ▼
  LatencyStats — record how long the round-trip took
       │
       ▼
  RiskManager.on_fill() — clear the "in-flight" pending count

All classes are in this one file so you can read the full Board B logic top-to-bottom.
"""
from common import (
    NUM_SYMBOLS, MASK_16, MASK_32, MASK_48, HIST_BINS, BIN_SHIFT,
    MsgType, FillStatus, SIDE_BUY, SIDE_SELL,
    QuoteFrame, OrderFrame, FillFrame, frame_type,
    sext32, sext48, from_q16, clamp,
)


# ─────────────────────────────────────────────────────────────
# QuoteBook — Per-Symbol Price Storage
#
# Simply stores the latest bid/ask for each symbol.
# When a quote arrives, it overwrites the previous values.
# In RTL this is a small register file (NUM_SYMBOLS × 4 values).
# ─────────────────────────────────────────────────────────────

class QuoteBook:
    def __init__(self, num_sym=NUM_SYMBOLS):
        self.num_sym = num_sym
        self.bid = [0] * num_sym
        self.ask = [0] * num_sym
        self.bid_size = [0] * num_sym
        self.ask_size = [0] * num_sym

    def update(self, q: QuoteFrame):
        """Store new quote data for this symbol."""
        if q.symbol < self.num_sym:
            self.bid[q.symbol] = q.bid
            self.ask[q.symbol] = q.ask
            self.bid_size[q.symbol] = q.bid_size
            self.ask_size[q.symbol] = q.ask_size


# ─────────────────────────────────────────────────────────────
# FeatureEngine — EMA Computation
#
# Computes an Exponential Moving Average (EMA) for each symbol.
# The EMA smooths out price noise to find the "fair value."
#
# Formula (in Q16.16 fixed-point):
#   ema_new = (alpha * mid + (65536 - alpha) * ema_old) >> 16
#
# Where alpha ≈ 0.1 (6554 out of 65536) controls how fast
# the EMA adapts to new prices. Small alpha = slow, smooth.
#
# The "deviation" (mid - ema) tells the strategy how far the
# current price is from fair value:
#   deviation > 0  →  price is ABOVE average (maybe sell)
#   deviation < 0  →  price is BELOW average (maybe buy)
#
# First-sample initialization: on the very first quote for a symbol,
# the EMA is seeded directly to the mid-price instead of computing
# from ema_old=0 (which would create a huge fake deviation).
# ─────────────────────────────────────────────────────────────

class FeatureEngine:
    def __init__(self, num_sym=NUM_SYMBOLS):
        self.num_sym = num_sym
        self.ema = [0] * num_sym          # per-symbol EMA state (Q16.16)
        self.initialized = [False] * num_sym  # has this symbol seen a quote yet?

    def compute(self, symbol: int, mid: int, alpha: int) -> int:
        """Compute EMA update and return deviation (signed Q16.16).

        Args:
            symbol: symbol index
            mid: current mid-price (Q16.16, unsigned)
            alpha: EMA smoothing factor (0..65536, typically ~6554 for 10%)
        Returns:
            deviation = mid - ema (signed, as 32-bit unsigned Q16.16)
        """
        if symbol >= self.num_sym:
            return 0

        if not self.initialized[symbol]:
            # First quote: seed EMA to mid (no computation needed)
            self.ema[symbol] = mid
            self.initialized[symbol] = True
            return 0  # deviation is 0 on first sample

        # EMA formula: ema_new = (alpha * mid + beta * ema_old) >> 16
        ema_old = self.ema[symbol]
        beta = (0x10000 - alpha) & MASK_32
        ema_new = ((alpha * mid) + (beta * ema_old)) >> 16
        ema_new &= MASK_32
        self.ema[symbol] = ema_new

        # deviation = mid - ema (signed)
        deviation = (mid - ema_new) & MASK_32
        return deviation

    def reset(self):
        self.ema = [0] * self.num_sym
        self.initialized = [False] * self.num_sym


# ─────────────────────────────────────────────────────────────
# Strategy — Mean-Reversion Trading Logic
#
# The core idea: if a stock's price moves too far from its average,
# it will probably come back. So:
#   - Price ABOVE average by more than threshold → SELL (expect drop)
#   - Price BELOW average by more than threshold → BUY  (expect rise)
#   - Price NEAR average → do nothing (no edge)
#
# The threshold parameter controls how much deviation is needed
# before we trade. Too small = trade too often (costs add up).
# Too large = miss opportunities.
# ─────────────────────────────────────────────────────────────

class Strategy:
    @staticmethod
    def evaluate(deviation: int, bid: int, ask: int,
                 threshold: int, qty: int) -> OrderFrame | None:
        """Check if deviation triggers a trade signal.

        Args:
            deviation: mid - ema (unsigned Q16.16, interpret as signed)
            bid, ask: current prices (for setting limit price)
            threshold: trigger level (unsigned Q16.16)
            qty: order quantity
        Returns:
            OrderFrame if trade signal, None if no trade
        """
        dev_signed = sext32(deviation)
        thr_signed = sext32(threshold)

        if dev_signed > thr_signed:
            # Price above average → SELL at bid
            return OrderFrame(symbol=0, side=SIDE_SELL, price=bid, qty=qty)
        elif dev_signed < -thr_signed:
            # Price below average → BUY at ask
            return OrderFrame(symbol=0, side=SIDE_BUY, price=ask, qty=qty)
        return None


# ─────────────────────────────────────────────────────────────
# RiskManager — Safety Checks Before Sending Orders
#
# Three independent checks must ALL pass:
#   1. Position limit: would this order push our position too large?
#   2. Order rate:     have we sent too many orders?
#   3. Max loss:       have we lost too much money?
#
# Plus: order_enable must be on and risk_halt must be off.
#
# In-flight tracking: when we send an order, we don't know if it
# filled yet (takes ~64 cycles round-trip). So we track "pending"
# orders separately to avoid sending too many while waiting.
# We track BUY and SELL pending counts separately because they
# can overshoot in opposite directions.
# ─────────────────────────────────────────────────────────────

class RiskManager:
    def __init__(self, num_sym=NUM_SYMBOLS):
        self.num_sym = num_sym
        self.order_count = 0
        self.risk_halt = False
        self.risk_rejects = 0
        self.pending_buy = [0] * num_sym
        self.pending_sell = [0] * num_sym

    def check(self, symbol: int, side: int, qty: int,
              position: list, total_pnl: int,
              max_position: int, max_order_rate: int, max_loss: int,
              order_enable: bool) -> bool:
        """Check if an order is safe to send. Returns True if approved."""

        if not order_enable or self.risk_halt:
            self.risk_rejects += 1
            return False

        sym = symbol
        qty = qty & MASK_16
        max_pos = max_position & MASK_32

        # Check 1: worst-case position after all pending orders fill
        if sym < self.num_sym:
            cur_pos = sext32(position[sym])
            if side == SIDE_BUY:
                worst = cur_pos + self.pending_buy[sym] + qty
            else:
                worst = cur_pos - self.pending_sell[sym] - qty
        else:
            worst = qty
        pass_pos = abs(worst) <= max_pos

        # Check 2: order rate
        pass_rate = self.order_count < (max_order_rate & MASK_32)

        # Check 3: max loss
        pnl = sext32(total_pnl & MASK_32)
        loss_limit = -sext32(max_loss & MASK_32)
        pass_loss = pnl > loss_limit

        if not pass_loss:
            self.risk_halt = True

        approved = pass_pos and pass_rate and pass_loss
        if approved:
            self.order_count += 1
            if sym < self.num_sym:
                if side == SIDE_BUY:
                    self.pending_buy[sym] += qty
                else:
                    self.pending_sell[sym] += qty
        else:
            self.risk_rejects += 1

        return approved

    def on_fill(self, symbol: int, side: int, qty: int):
        """Called when a fill or reject comes back — clear pending."""
        if symbol < self.num_sym:
            if side == SIDE_BUY:
                self.pending_buy[symbol] = max(0, self.pending_buy[symbol] - qty)
            else:
                self.pending_sell[symbol] = max(0, self.pending_sell[symbol] - qty)

    def reset(self):
        self.order_count = 0
        self.risk_halt = False
        self.risk_rejects = 0
        self.pending_buy = [0] * self.num_sym
        self.pending_sell = [0] * self.num_sym


# ─────────────────────────────────────────────────────────────
# PositionTracker — Position and Cash Accounting
#
# Processes filled orders:
#   - BUY:  position goes UP, cash goes DOWN (we paid money)
#   - SELL: position goes DOWN, cash goes UP (we received money)
#
# Cash is tracked in Q32.16 (48-bit) to avoid overflow when
# multiplying Q16.16 prices by quantities.
# ─────────────────────────────────────────────────────────────

class PositionTracker:
    def __init__(self, num_sym=NUM_SYMBOLS):
        self.num_sym = num_sym
        self.position = [0] * num_sym  # signed per-symbol position
        self.cash = 0                  # 48-bit Q32.16 accumulator
        self.fills_rcvd = 0

    def process_fill(self, fill: FillFrame):
        """Update position and cash from a fill."""
        if fill.status != FillStatus.FILLED:
            return
        if fill.symbol >= self.num_sym:
            return

        sym = fill.symbol
        cur_pos = sext32(self.position[sym])
        product = fill.fill_price * fill.fill_qty  # Q16.16 result

        if fill.side == SIDE_BUY:
            self.position[sym] = (cur_pos + fill.fill_qty) & MASK_32
            self.cash = (sext48(self.cash) - product) & MASK_48
        else:
            self.position[sym] = (cur_pos - fill.fill_qty) & MASK_32
            self.cash = (sext48(self.cash) + product) & MASK_48

        self.fills_rcvd += 1

    @property
    def total_pnl(self) -> int:
        """Cash in integer dollars (signed) — the realized P&L."""
        return sext32((self.cash >> 16) & MASK_32)

    def reset(self):
        self.position = [0] * self.num_sym
        self.cash = 0
        self.fills_rcvd = 0


# ─────────────────────────────────────────────────────────────
# LatencyStats — Round-Trip Latency Measurement
#
# Each order carries a timestamp. When the fill comes back, we
# subtract to get round-trip latency. Stats are collected into
# a 16-bin histogram (each bin = 32 cycles) plus min/max/avg.
# ─────────────────────────────────────────────────────────────

class LatencyStats:
    def __init__(self):
        self.hist = [0] * HIST_BINS
        self.lat_min = 0xFFFF
        self.lat_max = 0
        self.lat_sum = 0
        self.lat_count = 0

    def record(self, ts_echo: int, current_cycle: int):
        """Record one latency measurement."""
        latency = (current_cycle - ts_echo) & MASK_16  # 16-bit wrapping

        # Update stats
        if latency < self.lat_min:
            self.lat_min = latency
        if latency > self.lat_max:
            self.lat_max = latency
        self.lat_sum += latency
        self.lat_count += 1

        # Histogram bin
        bin_idx = min(latency >> BIN_SHIFT, HIST_BINS - 1)
        self.hist[bin_idx] += 1

    @property
    def avg(self) -> float:
        return self.lat_sum / self.lat_count if self.lat_count > 0 else 0.0

    def reset(self):
        self.hist = [0] * HIST_BINS
        self.lat_min = 0xFFFF
        self.lat_max = 0
        self.lat_sum = 0
        self.lat_count = 0


# ─────────────────────────────────────────────────────────────
# BoardB — Top-Level Integration
#
# Wires all pipeline stages together. Has two main paths:
#   Quote path: QuoteFrame → QuoteBook → FeatureEngine → Strategy
#               → RiskManager → build OrderFrame → send
#   Fill path:  FillFrame → PositionTracker → LatencyStats
#               → RiskManager.on_fill()
#
# step() processes one incoming frame (quote or fill) and
# optionally returns an OrderFrame to send back.
# ─────────────────────────────────────────────────────────────

class BoardB:
    def __init__(self, num_sym=NUM_SYMBOLS):
        self.num_sym = num_sym
        self.book = QuoteBook(num_sym)
        self.features = FeatureEngine(num_sym)
        self.strategy = Strategy()
        self.risk = RiskManager(num_sym)
        self.positions = PositionTracker(num_sym)
        self.latency = LatencyStats()

        # Configuration (set before running)
        self.ema_alpha = 6554       # ~10% smoothing
        self.threshold = 0x0001_0000  # $1.00 deviation to trigger trade
        self.base_qty = 100         # shares per order
        self.max_position = 500     # max shares per symbol
        self.max_order_rate = 1000
        self.max_loss = 100  # $100 integer dollars (matches total_pnl = cash >> 16)

        # Auto-incrementing order ID
        self._next_order_id = 0
        self._cycle = 0

        # Counters
        self.quotes_rcvd = 0
        self.orders_sent = 0
        self.trading = False

    def start(self):
        self.trading = True

    def stop(self):
        self.trading = False

    def step(self, cycle: int, frame_bits: int | None = None) -> int | None:
        """Process one incoming frame. Returns OrderFrame bits to send, or None.

        Args:
            cycle: current cycle number
            frame_bits: raw 128-bit frame from Board A (quote or fill), or None
        Returns:
            128-bit OrderFrame to send to Board A, or None
        """
        self._cycle = cycle

        if frame_bits is None:
            return None

        msg = frame_type(frame_bits)

        if msg == MsgType.QUOTE:
            return self._handle_quote(QuoteFrame.from_bits(frame_bits))
        elif msg == MsgType.FILL:
            self._handle_fill(FillFrame.from_bits(frame_bits))
            return None
        return None  # unknown frame type — discard

    def _handle_quote(self, quote: QuoteFrame) -> int | None:
        """Process a quote through the trading pipeline."""
        self.quotes_rcvd += 1

        # Step 1: Update quote book
        self.book.update(quote)

        # Step 2: Compute features (EMA and deviation)
        mid = quote.mid
        deviation = self.features.compute(quote.symbol, mid, self.ema_alpha)

        # Step 3: Strategy decision
        if not self.trading:
            return None

        signal = self.strategy.evaluate(
            deviation, quote.bid, quote.ask, self.threshold, self.base_qty
        )
        if signal is None:
            return None

        # Fill in the symbol (strategy returns a template)
        signal.symbol = quote.symbol

        # Step 4: Risk check
        approved = self.risk.check(
            signal.symbol, signal.side, signal.qty,
            self.positions.position, self.positions.total_pnl,
            self.max_position, self.max_order_rate, self.max_loss,
            order_enable=True,
        )
        if not approved:
            return None

        # Step 5: Build order with ID and timestamp
        signal.order_id = self._next_order_id & MASK_16
        signal.timestamp = self._cycle & MASK_16
        self._next_order_id = (self._next_order_id + 1) & MASK_16
        self.orders_sent += 1

        return signal.to_bits()

    def _handle_fill(self, fill: FillFrame):
        """Process a fill: update positions, record latency, clear pending."""
        # Position and cash update (only for actual fills, not rejects)
        self.positions.process_fill(fill)

        # Latency measurement (only for actual fills)
        if fill.is_filled:
            self.latency.record(fill.ts_echo, self._cycle)

        # Clear in-flight pending count (for both fills AND rejects)
        self.risk.on_fill(fill.symbol, fill.side, fill.fill_qty if fill.is_filled else self.base_qty)

    def reset(self):
        self.book = QuoteBook(self.num_sym)
        self.features.reset()
        self.risk.reset()
        self.positions.reset()
        self.latency.reset()
        self._next_order_id = 0
        self.quotes_rcvd = 0
        self.orders_sent = 0


# ─────────────────────────────────────────────────────────────
# Self-test
# ─────────────────────────────────────────────────────────────

if __name__ == "__main__":
    from common import q16

    board = BoardB(num_sym=4)
    board.threshold = q16(0.5)  # $0.50
    board.start()

    # Send a quote — first one seeds EMA, no trade
    q1 = QuoteFrame(symbol=0, regime=0, bid=q16(150.0), ask=q16(151.0))
    result = board.step(0, q1.to_bits())
    assert result is None, "First quote should not trigger trade (EMA seeding)"
    print(f"After first quote: EMA=${from_q16(board.features.ema[0]):.2f}")

    # Send a quote with big price jump — should trigger trade
    q2 = QuoteFrame(symbol=0, regime=0, bid=q16(155.0), ask=q16(156.0))
    result = board.step(1, q2.to_bits())
    if result:
        order = OrderFrame.from_bits(result)
        print(f"Trade signal: {order}")
    else:
        print("No trade (deviation within threshold)")

    # Send another big quote to trigger trade
    q3 = QuoteFrame(symbol=0, regime=0, bid=q16(160.0), ask=q16(161.0))
    result = board.step(2, q3.to_bits())
    if result:
        order = OrderFrame.from_bits(result)
        print(f"Trade signal: {order}")

    # Process a fill
    fill = FillFrame(symbol=0, side=SIDE_SELL, status=FillStatus.FILLED,
                     fill_price=q16(155.0), fill_qty=100, order_id=0, ts_echo=1)
    board.step(100, fill.to_bits())
    print(f"Position after fill: {sext32(board.positions.position[0])}")
    print(f"Fills received: {board.positions.fills_rcvd}")
    print(f"Latency: {board.latency.lat_min} cycles")

    print(f"\nStats: {board.quotes_rcvd} quotes, {board.orders_sent} orders, "
          f"{board.risk.risk_rejects} risk rejects")
    print("\nBoardB self-test PASSED")
