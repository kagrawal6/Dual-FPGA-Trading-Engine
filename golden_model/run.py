"""
run.py — Live Dashboard for the Dual-FPGA Trading Engine Golden Model

Auto-refreshing terminal dashboard that mirrors what the real FPGA
system would display. Runs continuously with keyboard controls.

Controls (type while running):
  c/v/b/a     — switch to CALM / VOLATILE / BURST / ADVERSARIAL
  +/-         — raise / lower threshold by $0.10
  s           — toggle start / stop trading
  r           — reset everything
  q           — quit
"""
import os
import sys
import time

if os.name == "nt":
    os.system("")  # enable ANSI escape sequences on Windows
    sys.stdout.reconfigure(encoding="utf-8")

from common import (
    NUM_SYMBOLS, NUM_SECTORS, MASK_16, MASK_32,
    Regime, MsgType, FillStatus,
    LinkLayer, QuoteFrame, OrderFrame, FillFrame,
    frame_type, q16, from_q16, sext32, sext48,
    SYMBOL_UNIVERSE, SECTOR_NAMES,
    default_tickers, default_init_mids, default_init_spreads, default_sector_ids,
)
from board_a import BoardA
from board_b import BoardB

REGIME_NAMES = {0: "CALM", 1: "VOLATILE", 2: "BURST", 3: "ADVERSARIAL"}
BATCH_SIZE = 2000


def clear_screen():
    os.system("cls" if os.name == "nt" else "clear")


def c(text, code):
    """Single ANSI color wrapper. Always produces exactly one \\033[...m + \\033[0m pair."""
    return f"\033[{code}m{text}\033[0m"

def green(t):      return c(t, "32")
def red(t):        return c(t, "31")
def yellow(t):     return c(t, "33")
def cyan(t):       return c(t, "36")
def bold(t):       return c(t, "1")
def dim(t):        return c(t, "2")
def bold_yellow(t): return c(t, "1;33")
def bold_green(t):  return c(t, "1;32")
def bold_red(t):    return c(t, "1;31")
def bold_cyan(t):   return c(t, "1;36")
def bg_green(t):   return c(t, "42;30")
def bg_red(t):     return c(t, "41;37")
def bg_yellow(t):  return c(t, "43;30")
def bg_cyan(t):    return c(t, "46;30")

# ANSI overhead: every c() call adds exactly len("\033[XXXm") + len("\033[0m") invisible chars.
# As long as every cell in a column uses exactly ONE c() call, columns stay aligned.


class Simulation:
    def __init__(self, num_sym=NUM_SYMBOLS, num_sectors=NUM_SECTORS):
        self.num_sym = num_sym
        self.board_a = BoardA(num_sym, num_sectors)
        self.board_b = BoardB(num_sym)
        self.link_ab = LinkLayer()
        self.link_ba = LinkLayer()
        self.cycle = 0
        self.regime = Regime.VOLATILE
        self.tickers = default_tickers()[:num_sym]
        self.seed = 0xDEAD_BEEF
        self.init_mid = default_init_mids()[:num_sym]
        self.init_spread = default_init_spreads()[:num_sym]
        self.sector_ids = default_sector_ids()[:num_sym]
        self.batch_size = BATCH_SIZE
        self.last_trade_log: list[str] = []
        self.max_trade_log = 6

    def setup(self, regime=Regime.VOLATILE, threshold_dollars=0.30):
        self.regime = regime
        self.board_a.configure(
            regime=int(regime), quote_interval=0, seed=self.seed,
            init_mid=self.init_mid, init_spread=self.init_spread,
            sector_ids=self.sector_ids, active_count=self.num_sym,
        )
        self.board_a.start()
        self.board_b.threshold = q16(threshold_dollars)
        self.board_b.base_qty = 100
        self.board_b.start()
        self.cycle = 0
        self.last_trade_log.clear()

    def run_batch(self, num_cycles: int):
        for _ in range(num_cycles):
            ab_frame = self.link_ab.receive(self.cycle)
            ba_frame = self.link_ba.receive(self.cycle)

            order_in = None
            if ba_frame is not None and frame_type(ba_frame) == MsgType.ORDER:
                order_in = OrderFrame.from_bits(ba_frame)

            if self.link_ab.can_send(self.cycle):
                a_out = self.board_a.step(self.cycle, order_in=order_in)
                if a_out is not None:
                    self.link_ab.send(a_out, self.cycle)
            elif order_in is not None:
                self.board_a.step(self.cycle, order_in=order_in)

            b_out = self.board_b.step(self.cycle, frame_bits=ab_frame)
            if b_out is not None:
                self.link_ba.send(b_out, self.cycle)
                order = OrderFrame.from_bits(b_out)
                side_s = "BUY " if order.side == 0 else "SELL"
                ticker = self.tickers[order.symbol] if order.symbol < len(self.tickers) else f"S{order.symbol}"
                entry = f"{side_s} {order.qty:>3}x {ticker:>5} @ ${from_q16(order.price):>8.2f}"
                self.last_trade_log.append(entry)
                if len(self.last_trade_log) > self.max_trade_log:
                    self.last_trade_log.pop(0)

            self.cycle += 1

    def change_regime(self, new_regime: int):
        self.regime = Regime(new_regime)
        self.board_a.market.regime = self.regime

    def render_dashboard(self) -> str:
        ms = self.board_a.market
        ex = self.board_a.exchange
        bb = self.board_b
        pt = bb.positions
        lat = bb.latency

        regime_name = REGIME_NAMES.get(int(self.regime), "?")
        status = "TRADING" if bb.trading else "STOPPED"
        if bb.risk.risk_halt:
            status = "HALTED"

        # P&L computation
        cash_dollars = sext48(pt.cash) / 65536.0
        unrealized = 0.0
        for i in range(self.num_sym):
            pos = sext32(pt.position[i])
            if pos != 0:
                mid = (ms.best_bid[i] + ms.best_ask[i]) / 2
                unrealized += pos * mid / 65536.0
        mtm = cash_dollars + unrealized

        lines = []

        # Header — width is derived from table header so everything matches
        # We build the header string first to measure its visible width,
        # then use that for the box and all other panels.

        # (table_w is computed below when we build hdr_raw, but we need it here
        #  for the title box, so pre-compute it)
        sample_hdr = (f"  │ {'#':>2} {'Tick':>5} {'Sector':>9} │"
                      f" {'Bid':>9}  {'Ask':>9}  {'Sprd':>6} │"
                      f" {'Pos':>6}  {'Dev':>7} │"
                      f" {'EMA':>9}  {'Chg':>7} │")
        W = len(sample_hdr)  # total visible width including leading "  "
        bw = W - 2  # inner box width (between the leading "  " and nothing)

        lines.append("")
        title1 = "DUAL-FPGA TRADING ENGINE"
        title2 = "Golden Model  ·  Software Simulation of Hardware Pipeline"
        lines.append(bold_cyan(f"  ╔{'═' * (bw - 2)}╗"))
        lines.append(bold_cyan("  ║") + bold(title1.center(bw - 2)) + bold_cyan("║"))
        lines.append(bold_cyan("  ║") + dim(title2.center(bw - 2)) + bold_cyan("║"))
        lines.append(bold_cyan(f"  ╚{'═' * (bw - 2)}╝"))
        lines.append("")

        # Status bar
        regime_colors = {
            0: bg_green(f" {regime_name} "),
            1: bg_yellow(f" {regime_name} "),
            2: bg_cyan(f" {regime_name} "),
            3: bg_red(f" {regime_name} "),
        }
        regime_badge = regime_colors.get(int(self.regime), regime_name)

        if status == "TRADING":
            status_badge = bg_green(" TRADING ")
        elif status == "HALTED":
            status_badge = bg_red(" HALTED ")
        else:
            status_badge = bg_yellow(" STOPPED ")

        pnl_badge = bg_green(f" ${mtm:>+10,.2f} ") if mtm >= 0 else bg_red(f" ${mtm:>+10,.2f} ")

        lines.append(f"  {regime_badge}  {status_badge}  "
                      f"Cycle: {bold(f'{self.cycle:>10,}')}  "
                      f"Thresh: {bold(f'${from_q16(bb.threshold):.2f}')}  "
                      f"PnL: {pnl_badge}")
        lines.append("")

        # Market table — build each cell as raw fixed-width text, then color once.
        # Every colored cell uses exactly one c() call so ANSI overhead is uniform.
        #
        # Column layout (visible chars):
        #   "  │ "  ##  " " XXXXX " " XXXXXXXXX " │ " $XXXXX.XX  $XXXXX.XX  $X.XXX " │ " XXXXXX  $XX.XX " │ " $XXXXX.XX  $XX.XX " │"
        #   4       2   1  5      1  9           3     9          9          6       3     6       7      3     9          7      3

        hdr_raw = (f"  │ {'#':>2} {'Tick':>5} {'Sector':>9} │"
                   f" {'Bid':>9}  {'Ask':>9}  {'Sprd':>6} │"
                   f" {'Pos':>6}  {'Dev':>7} │"
                   f" {'EMA':>9}  {'Chg':>7} │")
        table_w = len(hdr_raw) - 2  # inner width (minus leading "  ")
        lines.append(bold("  ┌" + "─" * (table_w - 2) + "┐"))
        lines.append(dim(hdr_raw))
        lines.append(dim("  │" + "─" * (table_w - 2) + "│"))

        for i in range(self.num_sym):
            bid = ms.best_bid[i]
            ask = ms.best_ask[i]
            mid_val = (bid + ask) >> 1
            spread = ask - bid
            pos = sext32(pt.position[i])
            ema = bb.features.ema[i]
            init = self.init_mid[i]

            ticker = self.tickers[i] if i < len(self.tickers) else f"S{i}"
            sec_id = self.sector_ids[i] if i < len(self.sector_ids) else 0
            sec_name = SECTOR_NAMES.get(sec_id, f"S{sec_id}")

            # Format all raw cells to fixed widths FIRST, then color
            r_tk  = f"{ticker:>5}"
            r_sec = f"{sec_name:>9}"
            r_bid = f"${from_q16(bid):>8.2f}"
            r_ask = f"${from_q16(ask):>8.2f}"
            r_spd = f"${from_q16(spread):>5.3f}"
            r_ema = f"${from_q16(ema):>8.2f}" if bb.features.initialized[i] else f"{'—':>9}"

            # Deviation: all paths produce the same 7-char raw string
            if bb.features.initialized[i] and ema != 0:
                dev = sext32((mid_val - ema) & MASK_32)
                dev_d = dev / 65536.0
                r_dev = f"${dev_d:>+6.2f}"
            else:
                dev_d = 0.0
                r_dev = f"{'—':>7}"

            # Change from init
            chg = sext32((mid_val - init) & MASK_32) / 65536.0
            r_chg = f"${chg:>+6.2f}"

            # Position
            if pos != 0:
                r_pos = f"{pos:>+6}"
            else:
                r_pos = f"{'0':>6}"

            # Apply exactly ONE color to each cell
            c_tk  = bold(r_tk)
            c_sec = dim(r_sec)

            if pos > 0:      c_pos = green(r_pos)
            elif pos < 0:    c_pos = red(r_pos)
            else:            c_pos = dim(r_pos)

            if bb.features.initialized[i] and ema != 0:
                if abs(dev_d) >= from_q16(bb.threshold):
                    c_dev = bold_yellow(r_dev)
                elif dev_d > 0:   c_dev = green(r_dev)
                elif dev_d < 0:   c_dev = red(r_dev)
                else:             c_dev = dim(r_dev)
            else:
                c_dev = dim(r_dev)

            if chg > 0:      c_chg = green(r_chg)
            elif chg < 0:    c_chg = red(r_chg)
            else:            c_chg = dim(r_chg)

            lines.append(
                f"  │ {i:>2} {c_tk} {c_sec} │"
                f" {r_bid}  {r_ask}  {r_spd} │"
                f" {c_pos}  {c_dev} │"
                f" {r_ema}  {c_chg} │"
            )

        lines.append(bold("  └" + "─" * (table_w - 2) + "┘"))
        lines.append("")

        # Bottom panels: side by side
        lw_inner = 40  # inner width of left panel
        rw_inner = table_w - lw_inner - 7  # inner width of right panel

        # Build left panel (fixed-width, no ANSI in structure)
        left = []
        def lrow(content):
            return f"  │ {content:<{lw_inner}}│"
        left.append(bold(f"  ┌─ ACTIVITY {'─' * (lw_inner - 11)}┐"))
        left.append(lrow(f"Quotes received  {bb.quotes_rcvd:>12,}"))
        left.append(lrow(f"Orders sent      {bb.orders_sent:>12,}"))
        left.append(lrow(f"Fills received   {pt.fills_rcvd:>12,}"))
        left.append(lrow(f"Exch. rejects    {ex.rejects_sent:>12,}"))
        left.append(lrow(f"Risk rejects     {bb.risk.risk_rejects:>12,}"))
        left.append(lrow(""))
        left.append(bold(f"  ├─ P&L {'─' * (lw_inner - 6)}┤"))
        left.append(lrow(f"Cash (realized)  ${cash_dollars:>+12,.2f}"))
        left.append(lrow(f"Unrealized       ${unrealized:>+12,.2f}"))
        r_mtm = f"${mtm:>+12,.2f}"
        c_mtm = green(r_mtm) if mtm >= 0 else red(r_mtm)
        # Mark-to-Market row: pad raw text, then inject color on the number
        mtm_label = "Mark-to-Market"
        mtm_raw = f"{mtm_label}   {r_mtm}"
        mtm_colored = f"{bold(mtm_label)}   {c_mtm}"
        left.append(f"  │ {mtm_colored}{' ' * (lw_inner - len(mtm_raw))}│")
        left.append(bold(f"  └{'─' * (lw_inner + 1)}┘"))

        # Build right panel
        right = []
        def rrow(content):
            return f"│ {content:<{rw_inner}}│"
        right.append(bold(f"┌─ RECENT TRADES {'─' * (rw_inner - 15)}┐"))
        trade_lines = self.last_trade_log[-self.max_trade_log:]
        for t in trade_lines:
            raw = f"{t:<{rw_inner}}"
            if t.startswith("BUY"):
                right.append(f"│ {green(raw)}│")
            else:
                right.append(f"│ {red(raw)}│")
        for _ in range(self.max_trade_log - len(trade_lines)):
            raw = f"{'  waiting...':>{rw_inner}}"
            right.append(f"│ {dim(raw)}│")
        right.append(rrow(""))
        right.append(bold(f"├─ LATENCY {'─' * (rw_inner - 9)}┤"))
        if lat.lat_count > 0:
            right.append(rrow(f"Min: {lat.lat_min:>4}  Avg: {lat.avg:>5.1f}  Max: {lat.lat_max:>4} cy"))
            right.append(rrow(f"Fills measured: {lat.lat_count:>8,}"))
        else:
            raw = f"{'No fills yet':>{rw_inner}}"
            right.append(f"│ {dim(raw)}│")
            right.append(rrow(""))
        right.append(bold(f"└{'─' * (rw_inner + 1)}┘"))

        # Merge left and right panels side by side
        max_rows = max(len(left), len(right))
        for row_i in range(max_rows):
            l = left[row_i] if row_i < len(left) else f"  │{' ' * (lw_inner + 1)}│"
            r = right[row_i] if row_i < len(right) else ""
            lines.append(f"{l}  {r}")

        lines.append("")

        # Position bar chart — bar fills available width
        bar_inner = table_w - 2  # inner width between │ and │
        # Layout: " XXXXX BBBB...BBB LLLLLLL " → 1+5+1+bar_max+1+7+1 = bar_max+16
        bar_max = bar_inner - 16
        lines.append(bold(f"  ┌─ POSITION EXPOSURE {'─' * (bar_inner - 22)}┐"))
        max_pos = 1
        for i in range(self.num_sym):
            p = abs(sext32(pt.position[i]))
            if p > max_pos:
                max_pos = p
        for i in range(self.num_sym):
            ticker = self.tickers[i] if i < len(self.tickers) else f"S{i}"
            pos = sext32(pt.position[i])
            bar_len = int(abs(pos) / max_pos * bar_max) if max_pos > 0 else 0
            r_label = f"{pos:>+7}" if pos != 0 else f"{'0':>7}"
            r_bar = "█" * bar_len
            r_bar_padded = f"{r_bar:<{bar_max}}"
            if pos > 0:
                c_bar = green(r_bar_padded)
                c_label = green(r_label)
            elif pos < 0:
                c_bar = red(r_bar_padded)
                c_label = red(r_label)
            else:
                c_bar = dim(f"{'·':<{bar_max}}")
                c_label = dim(r_label)
            lines.append(f"  │ {ticker:>5} {c_bar} {c_label} │")
        lines.append(bold(f"  └{'─' * bar_inner}┘"))
        lines.append("")

        # Controls
        lines.append(dim("  Controls:  "
                         "c=Calm  v=Volatile  b=Burst  a=Adversarial  "
                         "+/-=Threshold  s=Start/Stop  r=Reset  q=Quit"))
        lines.append("")

        return "\n".join(lines)


def get_key_nonblocking():
    """Non-blocking single-character read. Returns None if no input."""
    if os.name == "nt":
        import msvcrt
        if msvcrt.kbhit():
            ch = msvcrt.getch()
            try:
                return ch.decode("utf-8", errors="ignore")
            except Exception:
                return None
        return None
    else:
        import select, tty, termios
        fd = sys.stdin.fileno()
        old = termios.tcgetattr(fd)
        try:
            tty.setcbreak(fd)
            rlist, _, _ = select.select([sys.stdin], [], [], 0)
            if rlist:
                return sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old)
        return None


def main():
    num_sym = NUM_SYMBOLS
    regime = Regime.VOLATILE
    threshold = 0.30

    for i, arg in enumerate(sys.argv[1:], 1):
        if arg == "--sym" and i < len(sys.argv) - 1:
            num_sym = int(sys.argv[i + 1])
        elif arg == "--regime" and i < len(sys.argv) - 1:
            regime = Regime(int(sys.argv[i + 1]))
        elif arg == "--threshold" and i < len(sys.argv) - 1:
            threshold = float(sys.argv[i + 1])

    sim = Simulation(num_sym=num_sym, num_sectors=NUM_SECTORS)
    sim.setup(regime=regime, threshold_dollars=threshold)

    try:
        while True:
            sim.run_batch(sim.batch_size)

            clear_screen()
            print(sim.render_dashboard())

            key = get_key_nonblocking()
            if key is None:
                time.sleep(0.05)
                continue

            if key in ("q", "Q", "\x1b"):
                break
            elif key in ("c", "C"):
                sim.change_regime(0)
            elif key in ("v", "V"):
                sim.change_regime(1)
            elif key in ("b", "B"):
                sim.change_regime(2)
            elif key in ("a", "A"):
                sim.change_regime(3)
            elif key == "+":
                cur = from_q16(sim.board_b.threshold)
                sim.board_b.threshold = q16(cur + 0.10)
            elif key == "-":
                cur = from_q16(sim.board_b.threshold)
                new_t = max(0.05, cur - 0.10)
                sim.board_b.threshold = q16(new_t)
            elif key in ("s", "S"):
                if sim.board_b.trading:
                    sim.board_b.stop()
                else:
                    sim.board_b.start()
            elif key in ("r", "R"):
                sim.setup(regime=sim.regime,
                          threshold_dollars=from_q16(sim.board_b.threshold))
    except KeyboardInterrupt:
        pass

    print("\n  Simulation ended.\n")


if __name__ == "__main__":
    main()
