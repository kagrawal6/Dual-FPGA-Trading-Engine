"""
board_a.py — Board A: Market Simulator + Exchange

Board A is the "exchange side." It does two things:
  1. Generates fake market quotes (price updates for each symbol)
  2. Matches incoming orders against current prices (like a stock exchange)

Data flow:
  MarketSim generates QuoteFrames (one symbol at a time, round-robin)
       │
       ▼
  Exchange receives OrderFrames from Board B, matches them, returns FillFrames
       │
       ▼
  BoardA.step() decides what to send: fill (high priority) or quote (low priority)
       │
       ▼
  → sent over the PMOD link to Board B

All classes are in this one file so you can read the full Board A logic top-to-bottom.
"""
from common import (
    NUM_SYMBOLS, NUM_SECTORS, MASK_16, MASK_32,
    MIN_PRICE, MAX_PRICE, DRIFT_SATURATION, PULLBACK_SHIFT,
    GOLDEN, GLOBAL_SEED_XOR, SECTOR_SEED_XOR,
    Regime, REGIME_PARAMS, MsgType, FillStatus,
    SIDE_BUY, SIDE_SELL,
    LFSR32, QuoteFrame, OrderFrame, FillFrame,
    sext32, from_q16, clamp,
)


# ─────────────────────────────────────────────────────────────
# NoiseGen — 3-Tier Market Noise Generator
#
# Produces a random "step" for each symbol's price, combining:
#   1. Global noise   — affects all symbols equally (market-wide shock)
#   2. Sector noise   — affects symbols in the same sector
#   3. Company noise  — unique to each symbol
#
# Each tier uses its own LFSR (pseudo-random generator) with drift
# accumulators that create realistic trending behavior.
# ─────────────────────────────────────────────────────────────

class NoiseGen:
    def __init__(self, num_sym=NUM_SYMBOLS, num_sectors=NUM_SECTORS):
        self.num_sym = num_sym
        self.num_sectors = num_sectors
        self.drift_sat = sext32(DRIFT_SATURATION)

        # Each channel gets its own LFSR
        self.global_lfsr = LFSR32(1)
        self.sym_lfsrs = [LFSR32(1) for _ in range(num_sym)]
        self.sec_lfsrs = [LFSR32(1) for _ in range(num_sectors)]

        # Drift accumulators — create trending behavior
        self.sym_drift = [0] * num_sym
        self.sec_drift = [0] * num_sectors

    def seed(self, base_seed: int):
        """Initialize all LFSRs from a single base seed."""
        u = lambda x: x & MASK_32
        self.global_lfsr = LFSR32(u(base_seed ^ GLOBAL_SEED_XOR))
        for i in range(self.num_sym):
            self.sym_lfsrs[i] = LFSR32(u(base_seed ^ u(GOLDEN * (i + 1))))
        for g in range(self.num_sectors):
            self.sec_lfsrs[g] = LFSR32(u(base_seed ^ u(SECTOR_SEED_XOR + g * GOLDEN)))
        self.sym_drift = [0] * self.num_sym
        self.sec_drift = [0] * self.num_sectors

    def generate(self, active_count: int, sector_ids: list) -> list[int]:
        """Advance all LFSRs and return per-symbol noise values.

        Returns a list of signed integers — the total noise step for each
        active symbol. Inactive symbols get 0.

        Timing matches RTL: noise is computed from the CURRENT LFSR values
        and CURRENT drift accumulators (pre-update), then LFSRs and drifts
        are advanced for the next call. This matches the RTL where rand_out
        reflects the registered value and updates happen on the clock edge.
        """
        active = min(max(active_count, 1), self.num_sym)

        # Count how many symbols are in each sector
        sector_pop = [0] * self.num_sectors
        for i in range(active):
            sector_pop[sector_ids[i] % self.num_sectors] += 1

        # ── Read CURRENT LFSR values (before stepping) ──
        # RTL: rand_out = lfsr_reg (shows pre-clock-edge value)
        gr = self.global_lfsr.value
        g_raw = (gr & 0x3F) - 32
        if g_raw == -32:
            g_raw = 0  # clamp to symmetric range [-31..+31], mean=0
        global_noise = g_raw << 6

        sec_rand = [self.sec_lfsrs[k].value for k in range(self.num_sectors)]
        sym_rand = [self.sym_lfsrs[i].value for i in range(self.num_sym)]

        # ── Compute step_out from CURRENT (pre-update) drifts ──
        # RTL: step_out is combinational from registered drift values
        step_out = [0] * self.num_sym
        for i in range(active):
            sid = sector_ids[i] % self.num_sectors
            step_out[i] = global_noise + self.sec_drift[sid] + self.sym_drift[i]

        # ── Now advance LFSRs (takes effect next call) ──
        self.global_lfsr.step()
        for k in range(self.num_sectors):
            self.sec_lfsrs[k].step()
        for i in range(active):
            self.sym_lfsrs[i].step()

        # ── Update drift accumulators (takes effect next call) ──
        for k in range(self.num_sectors):
            sec_raw = ((sec_rand[k] >> 12) & 0x3F) - 32
            if sec_raw == -32:
                sec_raw = 0  # clamp to symmetric [-31..+31], mean=0
            base_delta = sec_raw << 2
            scaled = clamp(base_delta * sector_pop[k], -0x8000_0000, 0x7FFF_FFFF)
            self.sec_drift[k] = self._sat_add(self.sec_drift[k], scaled)

        for i in range(active):
            sym_raw = ((sym_rand[i] >> 6) & 0x3F) - 32
            if sym_raw == -32:
                sym_raw = 0  # clamp to symmetric [-31..+31], mean=0
            delta = sym_raw << 3
            self.sym_drift[i] = self._sat_add(self.sym_drift[i], delta)

        return step_out

    def _sat_add(self, acc: int, delta: int) -> int:
        return clamp(acc + delta, -self.drift_sat, self.drift_sat)


# ─────────────────────────────────────────────────────────────
# MarketSim — Generates Quotes
#
# Each "step" it:
#   1. Picks the next symbol (round-robin: 0, 1, 2, ... N-1, 0, ...)
#   2. Gets a noise value from NoiseGen
#   3. Updates the mid-price: new_mid = old_mid + noise * step_size
#   4. Computes bid and ask from mid and spread
#   5. Packs it into a QuoteFrame
# ─────────────────────────────────────────────────────────────

class MarketSim:
    def __init__(self, num_sym=NUM_SYMBOLS, num_sectors=NUM_SECTORS):
        self.num_sym = num_sym
        self.noise = NoiseGen(num_sym, num_sectors)

        self.mid_price = [0] * num_sym    # Q16.16 per symbol
        self.init_mid_ref = [0] * num_sym # saved for pull-back force
        self.best_bid = [0] * num_sym
        self.best_ask = [0] * num_sym
        self.seq_num = [0] * num_sym
        self.sym_ptr = 0                  # round-robin pointer
        self.quotes_generated = 0
        self.regime = Regime.CALM
        self.sector_ids = list(range(min(num_sectors, num_sym))) + [0] * max(0, num_sym - num_sectors)
        self.active_count = num_sym

    def init_prices(self, init_mid: list, init_spread: list, seed: int):
        """Set initial prices and seed the noise generator."""
        self.noise.seed(seed)
        for i in range(self.num_sym):
            self.mid_price[i] = init_mid[i]
            self.init_mid_ref[i] = init_mid[i]
            sp = init_spread[i] or 1
            half = sext32(sp) >> 1
            self.best_bid[i] = self._clamp(sext32(init_mid[i]) - half)
            self.best_ask[i] = self._clamp(sext32(init_mid[i]) + half)
            self.seq_num[i] = 0
        self.sym_ptr = 0
        self.quotes_generated = 0

    def generate_quote(self) -> QuoteFrame:
        """Generate the next quote (one symbol per call, round-robin)."""
        rp = REGIME_PARAMS.get(self.regime, REGIME_PARAMS[Regime.ADVERSARIAL])
        step_size = rp["step_size"]
        base_spread = rp["base_spread"] or 1

        active = min(max(self.active_count, 1), self.num_sym)

        # Get noise for all symbols and pick the current one
        step_out = self.noise.generate(active, self.sector_ids)
        s = self.sym_ptr

        # Update mid-price: delta = (noise * step_size) >> 16
        delta = (step_out[s] * sext32(step_size)) >> 16

        # Ornstein-Uhlenbeck pull-back: restoring force toward initial price
        displacement = sext32(self.init_mid_ref[s]) - sext32(self.mid_price[s])
        pull_back = displacement >> PULLBACK_SHIFT

        new_mid = self._clamp(sext32(self.mid_price[s]) + delta + pull_back)

        # Compute bid/ask from spread
        half_spread = sext32(base_spread) >> 1
        bid = self._clamp(sext32(new_mid) - half_spread)
        ask = self._clamp(sext32(new_mid) + half_spread)

        # Build quote
        quote = QuoteFrame(
            symbol=s, regime=int(self.regime),
            bid=bid, ask=ask,
            bid_size=1000, ask_size=1000,
            seq_num=self.seq_num[s],
        )

        # Commit
        self.mid_price[s] = new_mid
        self.best_bid[s] = bid
        self.best_ask[s] = ask
        self.seq_num[s] = (self.seq_num[s] + 1) & MASK_16
        self.quotes_generated += 1
        self.sym_ptr = (s + 1) % active

        return quote

    @staticmethod
    def _clamp(signed_val: int) -> int:
        lo = sext32(MIN_PRICE)
        hi = sext32(MAX_PRICE)
        if signed_val < lo:
            return MIN_PRICE
        if signed_val > hi:
            return MAX_PRICE
        return signed_val & MASK_32


# ─────────────────────────────────────────────────────────────
# Exchange — Order Matching Engine
#
# When an order comes in:
#   - BUY order:  fills at the ask price if limit_price >= ask
#   - SELL order: fills at the bid price if limit_price <= bid
#   - Otherwise:  rejected
#
# This is a simplified exchange — no order book, no partial fills.
# Every order either fills immediately at the current market price
# or gets rejected.
# ─────────────────────────────────────────────────────────────

class Exchange:
    def __init__(self, num_sym=NUM_SYMBOLS):
        self.num_sym = num_sym
        self.orders_rcvd = 0
        self.fills_sent = 0
        self.rejects_sent = 0

    def match(self, order: OrderFrame, best_bid: list, best_ask: list) -> FillFrame:
        """Try to match an order. Always returns a FillFrame (filled or rejected)."""
        self.orders_rcvd += 1
        sym = order.symbol

        if sym >= self.num_sym:
            self.rejects_sent += 1
            return FillFrame(
                symbol=sym, side=order.side, status=FillStatus.REJECTED,
                fill_price=0, fill_qty=0,
                order_id=order.order_id, ts_echo=order.timestamp,
            )

        if order.side == SIDE_BUY:
            filled = order.price >= best_ask[sym]
            fill_price = best_ask[sym] if filled else 0
        else:
            filled = order.price <= best_bid[sym]
            fill_price = best_bid[sym] if filled else 0

        status = FillStatus.FILLED if filled else FillStatus.REJECTED
        fill_qty = order.qty if filled else 0

        if filled:
            self.fills_sent += 1
        else:
            self.rejects_sent += 1

        return FillFrame(
            symbol=sym, side=order.side, status=status,
            fill_price=fill_price, fill_qty=fill_qty,
            order_id=order.order_id, ts_echo=order.timestamp,
        )


# ─────────────────────────────────────────────────────────────
# BoardA — Top-Level Integration
#
# Wires MarketSim + Exchange together. Manages the quote generation
# rate and fill-vs-quote priority (fills always go first).
#
# step() is called once per cycle. It:
#   1. Checks if an order arrived → match it → queue the fill
#   2. If no fill to send, maybe generate a quote
#   3. Returns whatever frame to send to Board B (or None)
# ─────────────────────────────────────────────────────────────

class BoardA:
    def __init__(self, num_sym=NUM_SYMBOLS, num_sectors=NUM_SECTORS):
        self.num_sym = num_sym
        self.market = MarketSim(num_sym, num_sectors)
        self.exchange = Exchange(num_sym)

        # Pending fills waiting to be sent (fills have priority over quotes)
        self._fill_queue: list[FillFrame] = []
        # Pending quotes waiting to be sent
        self._quote_queue: list[QuoteFrame] = []

        # Configuration
        self.quote_interval = 0     # 0 = generate as fast as possible
        self._quote_counter = 0

        self.running = False

    def configure(self, regime: int, quote_interval: int, seed: int,
                  init_mid: list, init_spread: list,
                  sector_ids: list, active_count: int):
        """Set up market parameters (like writing AXI registers on real HW)."""
        self.market.regime = Regime(regime)
        self.market.sector_ids = list(sector_ids)
        self.market.active_count = active_count
        self.market.init_prices(init_mid, init_spread, seed)
        self.quote_interval = quote_interval
        self._quote_counter = 0
        self._fill_queue.clear()
        self._quote_queue.clear()

    def start(self):
        self.running = True

    def stop(self):
        self.running = False

    def step(self, cycle: int, order_in: OrderFrame | None = None) -> int | None:
        """One cycle of Board A. Returns frame bits to send, or None.

        Args:
            cycle: current cycle number
            order_in: an OrderFrame from Board B, if one arrived this cycle
        Returns:
            128-bit frame (int) to send to Board B, or None
        """
        # Process incoming order
        if order_in is not None:
            fill = self.exchange.match(order_in, self.market.best_bid, self.market.best_ask)
            self._fill_queue.append(fill)

        # Generate quotes if running
        if self.running:
            should_quote = False
            if self.quote_interval == 0:
                should_quote = True
            else:
                self._quote_counter += 1
                if self._quote_counter >= self.quote_interval:
                    should_quote = True
                    self._quote_counter = 0

            if should_quote:
                quote = self.market.generate_quote()
                self._quote_queue.append(quote)

        # Send one frame: fills first (priority), then quotes
        if self._fill_queue:
            return self._fill_queue.pop(0).to_bits()
        elif self._quote_queue:
            return self._quote_queue.pop(0).to_bits()
        return None


# ─────────────────────────────────────────────────────────────
# Self-test
# ─────────────────────────────────────────────────────────────

if __name__ == "__main__":
    from common import (
        q16, default_init_mids, default_init_spreads, default_sector_ids,
        SYMBOL_UNIVERSE,
    )

    mids = default_init_mids()
    spreads = default_init_spreads()
    sids = default_sector_ids()

    board = BoardA(num_sym=NUM_SYMBOLS, num_sectors=NUM_SECTORS)
    board.configure(
        regime=Regime.CALM, quote_interval=0, seed=0xDEAD_BEEF,
        init_mid=mids, init_spread=spreads,
        sector_ids=sids, active_count=NUM_SYMBOLS,
    )
    board.start()

    # Run 20 cycles — should generate quotes with diverse prices
    quotes_seen = 0
    for c in range(20):
        bits = board.step(c)
        if bits is not None:
            q_frame = QuoteFrame.from_bits(bits)
            quotes_seen += 1
            ticker = SYMBOL_UNIVERSE[q_frame.symbol]["ticker"]
            print(f"Cycle {c}: {ticker:>5} {q_frame}")
    assert quotes_seen > 0
    print(f"\nGenerated {quotes_seen} quotes in 20 cycles")

    # Verify prices are actually different across symbols
    prices = set()
    for i in range(NUM_SYMBOLS):
        prices.add(board.market.mid_price[i])
    assert len(prices) > 1, "All symbols have the same price — universe not working!"
    print(f"Unique mid prices across {NUM_SYMBOLS} symbols: {len(prices)}")

    # Send an order and get a fill back (AAPL, symbol 0)
    order = OrderFrame(symbol=0, side=SIDE_BUY, price=q16(200.0), qty=100,
                       order_id=1, timestamp=42)
    bits = board.step(20, order_in=order)
    assert bits is not None
    fill = FillFrame.from_bits(bits)
    assert fill.is_filled
    assert fill.fill_qty == 100
    print(f"Order matched: {fill}")

    # Send order that should be rejected (bid too low)
    bad_order = OrderFrame(symbol=0, side=SIDE_BUY, price=q16(1.0), qty=50,
                           order_id=2, timestamp=43)
    bits = board.step(21, order_in=bad_order)
    assert bits is not None
    reject = FillFrame.from_bits(bits)
    assert not reject.is_filled
    print(f"Order rejected: {reject}")

    print(f"\nExchange stats: {board.exchange.orders_rcvd} orders, "
          f"{board.exchange.fills_sent} fills, {board.exchange.rejects_sent} rejects")
    print("\nBoardA self-test PASSED")
