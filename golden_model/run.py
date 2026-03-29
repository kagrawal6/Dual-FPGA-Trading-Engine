"""
run.py — Interactive Demo Runner for the Dual-FPGA Trading Engine

This simulates the full system as it would run on real hardware:
  - Board A generates market quotes and matches orders
  - Board B receives quotes, makes trading decisions, sends orders
  - Frames travel over a simulated PMOD serial link (64-cycle delay)

You control the system with keyboard commands, just like you would
via the PYNQ Python interface on the real FPGA:
  regime <0-3>    — change market conditions
  threshold <$>   — set trading sensitivity (in dollars)
  qty <n>         — set order quantity
  stop            — pause trading
  start           — resume trading
  reset           — reset everything
  quit / q        — exit

Press Enter to advance the simulation by another batch of cycles.
"""
import os
import sys
from common import (
    NUM_SYMBOLS, NUM_SECTORS, MASK_16, MASK_32,
    Regime, MsgType, FillStatus,
    LinkLayer, QuoteFrame, OrderFrame, FillFrame,
    frame_type, q16, from_q16, sext32, sext48,
)
from board_a import BoardA
from board_b import BoardB

REGIME_NAMES = {0: "CALM", 1: "VOLATILE", 2: "BURST", 3: "ADVERSARIAL"}
BATCH_SIZE = 5000   # cycles per batch before showing stats


def clear_screen():
    os.system("cls" if os.name == "nt" else "clear")


class Simulation:
    def __init__(self, num_sym=4, num_sectors=4):
        self.num_sym = num_sym
        self.board_a = BoardA(num_sym, num_sectors)
        self.board_b = BoardB(num_sym)

        # PMOD links (Board A → Board B, Board B → Board A)
        self.link_ab = LinkLayer()  # carries quotes and fills
        self.link_ba = LinkLayer()  # carries orders

        self.cycle = 0
        self.regime = Regime.CALM

        # Default configuration
        self.seed = 0xDEAD_BEEF
        self.init_mid = [q16(150.0)] * num_sym
        self.init_spread = [q16(0.125)] * num_sym
        self.sector_ids = list(range(min(num_sectors, num_sym))) + [0] * max(0, num_sym - num_sectors)
        self.batch_size = BATCH_SIZE

    def setup(self, regime=Regime.CALM, threshold_dollars=1.0):
        """Initialize both boards (like power-on + PYNQ configuration)."""
        self.regime = regime
        self.board_a.configure(
            regime=int(regime), quote_interval=0, seed=self.seed,
            init_mid=self.init_mid, init_spread=self.init_spread,
            sector_ids=self.sector_ids, active_count=self.num_sym,
        )
        self.board_a.start()

        self.board_b.threshold = q16(threshold_dollars)
        self.board_b.start()
        self.cycle = 0

    def run_batch(self, num_cycles: int):
        """Run the simulation for a batch of cycles."""
        for _ in range(num_cycles):
            # Check if any frames arrived at their destination this cycle
            ab_frame = self.link_ab.receive(self.cycle)
            ba_frame = self.link_ba.receive(self.cycle)

            # Board A: process incoming order (if any), maybe send a quote/fill
            order_in = None
            if ba_frame is not None and frame_type(ba_frame) == MsgType.ORDER:
                order_in = OrderFrame.from_bits(ba_frame)

            # Only generate a quote/fill if the link can accept it
            if self.link_ab.can_send(self.cycle):
                a_out = self.board_a.step(self.cycle, order_in=order_in)
                if a_out is not None:
                    self.link_ab.send(a_out, self.cycle)
            elif order_in is not None:
                # Link busy but we got an order — process it, queue fill internally
                self.board_a.step(self.cycle, order_in=order_in)

            # Board B: process incoming frame (quote or fill), maybe send an order
            b_out = self.board_b.step(self.cycle, frame_bits=ab_frame)
            if b_out is not None:
                self.link_ba.send(b_out, self.cycle)

            self.cycle += 1

    def change_regime(self, new_regime: int):
        """Switch market regime mid-simulation (like changing AXI register)."""
        self.regime = Regime(new_regime)
        self.board_a.market.regime = self.regime

    def print_dashboard(self):
        """Print the stats dashboard."""
        ms = self.board_a.market
        ex = self.board_a.exchange
        bb = self.board_b
        pt = bb.positions
        lat = bb.latency

        regime_name = REGIME_NAMES.get(int(self.regime), "UNKNOWN")
        status = "TRADING" if bb.trading else "STOPPED"
        if bb.risk.risk_halt:
            status = "RISK HALT"

        print("=" * 58)
        print("       DUAL-FPGA TRADING ENGINE  —  GOLDEN MODEL")
        print("=" * 58)
        print(f" Cycle: {self.cycle:,}  |  Regime: {regime_name}  |  Status: {status}")
        print(f" Threshold: ${from_q16(bb.threshold):.4f}  |  Qty: {bb.base_qty}")
        print("-" * 58)

        # Market table
        print(" MARKET")
        print(f" {'Sym':>3}  {'Bid':>10}  {'Ask':>10}  {'Spread':>8}  {'Position':>9}  {'EMA':>10}")
        for i in range(self.num_sym):
            bid = ms.best_bid[i]
            ask = ms.best_ask[i]
            spread = ask - bid
            pos = sext32(pt.position[i])
            ema = bb.features.ema[i]
            ema_str = f"${from_q16(ema):.2f}" if bb.features.initialized[i] else "    —"
            print(f"  {i:>2}   ${from_q16(bid):>8.4f}  ${from_q16(ask):>8.4f}"
                  f"  ${from_q16(spread):>6.4f}  {pos:>9}  {ema_str:>10}")
        print()

        # Trading stats
        print(" TRADING ACTIVITY")
        print(f"   Quotes received:  {bb.quotes_rcvd:>8,}")
        print(f"   Orders sent:      {bb.orders_sent:>8,}")
        print(f"   Fills received:   {pt.fills_rcvd:>8,}")
        print(f"   Exchange rejects: {ex.rejects_sent:>8,}")
        print(f"   Risk rejects:     {bb.risk.risk_rejects:>8,}")
        print()

        # P&L
        cash_dollars = sext48(pt.cash) / 65536.0
        unrealized = 0.0
        for i in range(self.num_sym):
            pos = sext32(pt.position[i])
            if pos != 0:
                mid = (ms.best_bid[i] + ms.best_ask[i]) / 2
                unrealized += pos * mid / 65536.0
        mtm = cash_dollars + unrealized

        print(" PROFIT & LOSS")
        print(f"   Cash (realized):  ${cash_dollars:>12,.2f}")
        print(f"   Unrealized:       ${unrealized:>12,.2f}")
        print(f"   Mark-to-Market:   ${mtm:>12,.2f}")
        print()

        # Latency
        if lat.lat_count > 0:
            print(" LATENCY (round-trip)")
            print(f"   Min/Avg/Max: {lat.lat_min} / {lat.avg:.1f} / {lat.lat_max} cycles"
                  f"  ({lat.lat_count} fills)")
        else:
            print(" LATENCY: no fills yet")

        print("=" * 58)


def main():
    # Parse optional command-line args
    num_sym = 4
    regime = Regime.CALM
    threshold = 1.0

    for i, arg in enumerate(sys.argv[1:], 1):
        if arg == "--sym" and i < len(sys.argv) - 1:
            num_sym = int(sys.argv[i + 1])
        elif arg == "--regime" and i < len(sys.argv) - 1:
            regime = Regime(int(sys.argv[i + 1]))
        elif arg == "--threshold" and i < len(sys.argv) - 1:
            threshold = float(sys.argv[i + 1])

    sim = Simulation(num_sym=num_sym, num_sectors=min(num_sym, NUM_SECTORS))
    sim.setup(regime=regime, threshold_dollars=threshold)

    clear_screen()
    print("Dual-FPGA Trading Engine — Golden Model Simulator")
    print(f"  Symbols: {num_sym}  |  Starting regime: {REGIME_NAMES[int(regime)]}")
    print(f"  Threshold: ${threshold:.4f}  |  Batch size: {sim.batch_size} cycles")
    print()
    print("Press Enter to start simulation...")
    input()

    while True:
        # Run a batch
        sim.run_batch(sim.batch_size)

        # Display dashboard
        clear_screen()
        sim.print_dashboard()
        print()
        print(" Commands:  regime <0-3>  |  threshold <$>  |  qty <n>")
        print("            stop  |  start  |  reset  |  batch <n>  |  quit")
        print()

        # Get user input
        try:
            cmd = input(" > ").strip().lower()
        except (EOFError, KeyboardInterrupt):
            break

        if not cmd:
            continue  # just press Enter to continue

        parts = cmd.split()
        action = parts[0]

        if action in ("quit", "q", "exit"):
            break
        elif action == "regime" and len(parts) > 1:
            try:
                r = int(parts[1])
                if 0 <= r <= 3:
                    sim.change_regime(r)
                    print(f"  → Regime changed to {REGIME_NAMES[r]}")
                else:
                    print("  Regime must be 0-3")
            except ValueError:
                print("  Usage: regime <0-3>")
        elif action == "threshold" and len(parts) > 1:
            try:
                t = float(parts[1])
                sim.board_b.threshold = q16(t)
                print(f"  → Threshold set to ${t:.4f}")
            except ValueError:
                print("  Usage: threshold <dollars>")
        elif action == "qty" and len(parts) > 1:
            try:
                sim.board_b.base_qty = int(parts[1])
                print(f"  → Quantity set to {sim.board_b.base_qty}")
            except ValueError:
                print("  Usage: qty <number>")
        elif action == "stop":
            sim.board_b.stop()
            print("  → Trading stopped")
        elif action == "start":
            sim.board_b.start()
            print("  → Trading started")
        elif action == "reset":
            sim.setup(regime=sim.regime, threshold_dollars=from_q16(sim.board_b.threshold))
            print("  → System reset")
        elif action == "batch" and len(parts) > 1:
            try:
                sim.batch_size = int(parts[1])
                print(f"  → Batch size set to {sim.batch_size}")
            except ValueError:
                print("  Usage: batch <cycles>")
        else:
            print(f"  Unknown command: {cmd}")


if __name__ == "__main__":
    main()
