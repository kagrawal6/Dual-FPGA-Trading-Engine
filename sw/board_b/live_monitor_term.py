#!/usr/bin/env python3
"""
Board B Live Monitor — Terminal Edition (no Jupyter dependency)
================================================================
Standalone real-time dashboard for Board B that runs in a plain terminal
(SSH, serial console, tmux pane). Same panels as live_monitor.py but uses
ANSI cursor positioning instead of IPython clear_output, so it works
anywhere a VT100-compatible terminal does.

Panels rendered each frame:
  * Title box
  * Status bar  (regime, FSM, strategy, link, risk, PnL badge)
  * ACTIVITY  +  P&L  side-by-side panels
  * POSITION EXPOSURE horizontal bar chart (16 symbols)
  * LATENCY stats (LAT_MIN/MAX/SUM/COUNT)
  * LATENCY HISTOGRAM bar chart (16 bins x 32 cycles)

Quick usage:
    python3 live_monitor_term.py                       # uses defaults; runs forever (Ctrl+C to stop)
    python3 live_monitor_term.py --regime VOLATILE
    python3 live_monitor_term.py --no-arm              # skip configure_and_arm; just monitor
    python3 live_monitor_term.py --strategy 1 --threshold 1.0 --base-qty 100

Pre-reqs:
    * Board B PYNQ booted with overlays/board_b.bit at the standard path.
    * Board A already pumping quotes over the PMOD link.
    * Physical SW[0] flipped UP on Board B (else FSM stays in B_ARMED).
"""

import argparse
import os
import signal
import sys
import time

from pynq import Overlay, MMIO


# ═══════════════════════════════════════════════════════════════════════════
# Register map (matches board_b_axi_regs.sv)
# ═══════════════════════════════════════════════════════════════════════════
B_CTRL           = 0x00
B_STRATEGY_SEL   = 0x04
B_THRESHOLD      = 0x08
B_EMA_ALPHA      = 0x0C
B_BASE_QTY       = 0x10
B_MAX_POSITION   = 0x14
B_MAX_ORDER_RATE = 0x18
B_MAX_LOSS       = 0x1C
B_STATUS         = 0x40
B_QUOTES_RCVD    = 0x44
B_ORDERS_SENT    = 0x48
B_FILLS_RCVD     = 0x4C
B_RISK_REJECTS   = 0x50
B_LINK_ERRORS    = 0x54
B_POS_BASE       = 0x58
B_CASH_LO        = 0x98
B_CASH_HI        = 0x9C
B_HIST_BASE      = 0xA0
B_LAT_MIN        = 0xE0
B_LAT_MAX        = 0xE4
B_LAT_SUM        = 0xE8
B_LAT_COUNT      = 0xEC

NUM_SYM        = 16
NUM_HIST_BINS  = 16
HIST_BIN_SHIFT = 5          # 32 cycles per bin (matches hft_pkg::BIN_SHIFT)
HIST_BIN_CY    = 1 << HIST_BIN_SHIFT
NS_PER_CY      = 10         # 100 MHz core clock

STATE_NAMES    = {0: 'B_RESET', 1: 'B_IDLE', 2: 'B_ARMED', 3: 'B_TRADING', 4: 'B_HALTED'}
STRATEGY_NAMES = {0: 'MEAN_REV', 1: 'MOMENTUM', 2: 'NN', 3: 'AUTO'}
SYMBOL_NAMES = ['AAPL', 'MSFT', 'GOOG', 'META', 'NVDA', 'AMD', 'INTC', 'AVGO',
                'AMZN', 'TSLA', 'JPM',  'GS',   'JNJ',  'PFE', 'XOM',  'CVX']

VALID_REGIMES = ('CALM', 'VOLATILE', 'BURST', 'ADVERSARIAL')


# ═══════════════════════════════════════════════════════════════════════════
# ANSI helpers (style matched to sw/board_b/live_monitor.py)
# ═══════════════════════════════════════════════════════════════════════════
def _c(text, code): return f"\033[{code}m{text}\033[0m"
def green(t):       return _c(t, "32")
def red(t):         return _c(t, "31")
def yellow(t):      return _c(t, "33")
def cyan(t):        return _c(t, "36")
def bold(t):        return _c(t, "1")
def dim(t):         return _c(t, "2")
def bold_yellow(t): return _c(t, "1;33")
def bold_green(t):  return _c(t, "1;32")
def bold_red(t):    return _c(t, "1;31")
def bold_cyan(t):   return _c(t, "1;36")
def bg_green(t):    return _c(t, "42;30")
def bg_red(t):      return _c(t, "41;37")
def bg_yellow(t):   return _c(t, "43;30")
def bg_cyan(t):     return _c(t, "46;30")
def bg_magenta(t):  return _c(t, "45;37")

# Terminal-control sequences
ANSI_HIDE_CURSOR = "\033[?25l"
ANSI_SHOW_CURSOR = "\033[?25h"
ANSI_CLEAR_SCREEN = "\033[2J"
ANSI_HOME = "\033[H"
ANSI_CLEAR_TO_END = "\033[J"


# ═══════════════════════════════════════════════════════════════════════════
# MMIO helpers
# ═══════════════════════════════════════════════════════════════════════════
def open_mmio(overlay_path, ip_block):
    print(f"Loading Board B overlay ({overlay_path})...")
    ol = Overlay(overlay_path)
    base = ol.ip_dict[ip_block]['phys_addr']
    span = ol.ip_dict[ip_block]['addr_range']
    print(f"  base=0x{base:08X}  span={span}  ip_block='{ip_block}'")
    return ol, MMIO(base, span)


def decode_status(raw):
    return {
        'strategy':  STRATEGY_NAMES.get(raw & 0x3, '?'),
        'fsm':       STATE_NAMES.get((raw >> 2) & 0x7, f'?({(raw>>2)&7})'),
        'link_up':   bool(raw & 0x20),
        'risk_halt': bool(raw & 0x40),
    }


def read_position(mmio, slot):
    raw = mmio.read(B_POS_BASE + 4 * slot)
    return raw - (1 << 32) if raw & 0x80000000 else raw


def read_cash(mmio):
    lo = mmio.read(B_CASH_LO)
    hi = mmio.read(B_CASH_HI) & 0xFFFF
    raw = (hi << 32) | lo
    if raw & (1 << 47):
        raw -= 1 << 48
    return raw / 65536.0


def read_latency(mmio):
    cnt = mmio.read(B_LAT_COUNT)
    if cnt == 0:
        return None
    lat_min = mmio.read(B_LAT_MIN)
    lat_max = mmio.read(B_LAT_MAX)
    lat_sum = mmio.read(B_LAT_SUM)
    return {
        'min':   lat_min,
        'max':   lat_max,
        'sum':   lat_sum,
        'count': cnt,
        'avg':   lat_sum / cnt,
    }


def read_hist_bins(mmio):
    return [mmio.read(B_HIST_BASE + 4 * i) for i in range(NUM_HIST_BINS)]


def snapshot(mmio, start_t, t):
    return {
        't':       t,
        's':       decode_status(mmio.read(B_STATUS)),
        'q':       mmio.read(B_QUOTES_RCVD),
        'o':       mmio.read(B_ORDERS_SENT),
        'f':       mmio.read(B_FILLS_RCVD),
        'rr':      mmio.read(B_RISK_REJECTS),
        'le':      mmio.read(B_LINK_ERRORS),
        'pos':     [read_position(mmio, i) for i in range(NUM_SYM)],
        'cash':    read_cash(mmio),
        'lat':     read_latency(mmio),
        'hist':    read_hist_bins(mmio),
        'start_t': start_t,
    }


# ═══════════════════════════════════════════════════════════════════════════
# Configuration helpers
# ═══════════════════════════════════════════════════════════════════════════
def configure_and_arm(mmio, strategy, threshold_dollars, ema_alpha,
                      base_qty, max_position, max_order_rate, max_loss):
    """Reset, write config registers, then pulse start. Mirrors live_monitor.py."""
    threshold_q = int(threshold_dollars * 65536) & 0xFFFFFFFF
    mmio.write(B_CTRL, 0x02); time.sleep(0.1)         # reset pulse
    mmio.write(B_STRATEGY_SEL,   strategy)
    mmio.write(B_THRESHOLD,      threshold_q)
    mmio.write(B_EMA_ALPHA,      ema_alpha)
    mmio.write(B_BASE_QTY,       base_qty)
    mmio.write(B_MAX_POSITION,   max_position)
    mmio.write(B_MAX_ORDER_RATE, max_order_rate)
    mmio.write(B_MAX_LOSS,       max_loss)
    mmio.write(B_CTRL, 0x01); time.sleep(0.1)         # IDLE -> ARMED
    mmio.write(B_CTRL, 0x01); time.sleep(0.3)         # ARMED -> TRADING (needs SW[0] up)
    s = decode_status(mmio.read(B_STATUS))
    print(f"Board B armed.  STATUS = {s}")
    if s['fsm'] != 'B_TRADING':
        print("  WARNING: not in B_TRADING.  Flip physical SW[0] UP on Board B.")
    return s


# ═══════════════════════════════════════════════════════════════════════════
# Dashboard renderer (returns list of lines; caller writes them out)
# ═══════════════════════════════════════════════════════════════════════════
W = 76                 # total dashboard width
BAR_MAX = W - 22       # position-bar width


def build_frame(prev, cur, session, regime_name):
    s = cur['s']
    dt = max(cur['t'] - prev['t'], 1e-6)
    dq    = cur['q']    - prev['q']
    do    = cur['o']    - prev['o']
    df    = cur['f']    - prev['f']
    drr   = cur['rr']   - prev['rr']
    dcash = cur['cash'] - prev['cash']

    session['min_cash'] = min(session['min_cash'], cur['cash'])
    session['max_cash'] = max(session['max_cash'], cur['cash'])

    lines = []
    inner = W - 2

    # ── Title ────────────────────────────────────────────────
    lines.append("")
    lines.append(bold_cyan(f"  ╔{'═' * inner}╗"))
    title1 = "DUAL-FPGA TRADING ENGINE"
    title2 = "Live Hardware Monitor (terminal) - Board B - AUP-ZU3"
    lines.append(bold_cyan("  ║") + bold(title1.center(inner)) + bold_cyan("║"))
    lines.append(bold_cyan("  ║") + dim(title2.center(inner))  + bold_cyan("║"))
    lines.append(bold_cyan(f"  ╚{'═' * inner}╝"))
    lines.append("")

    # ── Status bar ────────────────────────────────────────────
    regime_badges = {
        'CALM':         bg_green(f" {regime_name} "),
        'VOLATILE':     bg_yellow(f" {regime_name} "),
        'BURST':        bg_cyan(f" {regime_name} "),
        'ADVERSARIAL':  bg_red(f" {regime_name} "),
    }
    regime_badge = regime_badges.get(regime_name, bg_magenta(f" {regime_name} "))

    fsm = s['fsm']
    if   fsm == 'B_TRADING': fsm_badge = bg_green(f" {fsm} ")
    elif fsm == 'B_ARMED':   fsm_badge = bg_yellow(f" {fsm} ")
    elif fsm == 'B_HALTED':  fsm_badge = bg_red(f" {fsm} ")
    else:                    fsm_badge = bg_cyan(f" {fsm} ")

    link_badge = bg_green(" LINK UP ") if s['link_up'] else bg_red(" LINK DOWN ")
    risk_badge = bg_red(" RISK HALT ") if s['risk_halt'] else ""

    if cur['cash'] > 0.5:
        pnl_badge = bg_green(f" ${cur['cash']:>+10,.2f} ")
    elif cur['cash'] < -0.5:
        pnl_badge = bg_red(f" ${cur['cash']:>+10,.2f} ")
    else:
        pnl_badge = bg_yellow(f" ${cur['cash']:>+10,.2f} ")

    lines.append(f"  {regime_badge}  {fsm_badge}  {link_badge}  "
                 f"Strategy: {bold(s['strategy'])}  PnL: {pnl_badge}")
    if s['risk_halt']:
        lines.append(f"  {risk_badge}")
    lines.append("")

    # ── ACTIVITY + P&L side-by-side ─────────────────────────
    lw = 36
    rw = W - lw - 4

    left = []
    left.append(bold(f"  ┌─ ACTIVITY {'─' * (lw - 11)}┐"))
    left.append(f"  │ Quotes received   {cur['q']:>14,}  │")
    left.append(f"  │ Orders sent       {cur['o']:>14,}  │")
    left.append(f"  │ Fills received    {cur['f']:>14,}  │")
    left.append(f"  │ Risk rejects      {cur['rr']:>14,}  │")
    left.append(f"  │ Link errors       {cur['le']:>14,}  │")
    left.append(f"  │ {'':<{lw-1}}│")
    fill_rate  = (df / do * 100) if do > 0 else 0.0
    reject_pct = (drr / (do + drr) * 100) if (do + drr) > 0 else 0.0
    left.append(f"  │ Quote rate      {dq/dt:>12,.0f}/s  │")
    left.append(f"  │ Order rate      {do/dt:>12,.0f}/s  │")
    left.append(f"  │ Fill rate           {fill_rate:>7.1f}%     │")
    left.append(f"  │ Reject rate         {reject_pct:>7.1f}%     │")
    left.append(bold(f"  └{'─' * (lw + 1)}┘"))

    right = []
    right.append(bold(f"┌─ P&L {'─' * (rw - 5)}┐"))
    r_cash = f"${cur['cash']:>+12,.2f}"
    c_cash = green(r_cash) if cur['cash'] >= 0 else red(r_cash)
    right.append(f"│ Cash (realized)  {c_cash}    │")
    r_rate = f"${dcash/dt:>+10,.2f}/s"
    c_rate = green(r_rate) if dcash >= 0 else red(r_rate)
    right.append(f"│ P&L rate         {c_rate}  │")
    right.append(f"│ {'':<{rw-1}}│")
    right.append(dim(f"│ -- SESSION --{' ' * (rw - 14)}│"))
    r_min = f"${session['min_cash']:>+12,.2f}"
    r_max = f"${session['max_cash']:>+12,.2f}"
    c_min = red(r_min)   if session['min_cash'] < 0 else dim(r_min)
    c_max = green(r_max) if session['max_cash'] > 0 else dim(r_max)
    right.append(f"│ Session min      {c_min}    │")
    right.append(f"│ Session max      {c_max}    │")
    r_range = f"${session['max_cash'] - session['min_cash']:>12,.2f}"
    right.append(f"│ Session range    {dim(r_range)}    │")
    right.append(f"│ {'':<{rw-1}}│")
    right.append(f"│ {'':<{rw-1}}│")
    right.append(f"│ {'':<{rw-1}}│")
    right.append(bold(f"└{'─' * (rw + 1)}┘"))

    for row in range(max(len(left), len(right))):
        l = left[row]  if row < len(left)  else "  │" + " " * (lw + 1) + "│"
        r = right[row] if row < len(right) else ""
        lines.append(f"{l}  {r}")
    lines.append("")

    # ── POSITION EXPOSURE ────────────────────────────────────
    lines.append(bold(f"  ┌─ POSITION EXPOSURE {'─' * (inner - 21)}┐"))
    positions = cur['pos']
    max_abs = max((abs(p) for p in positions), default=1) or 1
    for i, p in enumerate(positions):
        ticker = SYMBOL_NAMES[i]
        bar_len = int(abs(p) / max_abs * BAR_MAX) if max_abs else 0
        r_label = f"{p:>+6}" if p != 0 else f"{'0':>6}"
        r_bar = "█" * bar_len
        r_bar_padded = f"{r_bar:<{BAR_MAX}}"
        if p > 0:
            c_bar = green(r_bar_padded);    c_label = green(r_label)
        elif p < 0:
            c_bar = red(r_bar_padded);      c_label = red(r_label)
        else:
            c_bar = dim(f"{'·':<{BAR_MAX}}"); c_label = dim(r_label)
        lines.append(f"  │ {ticker:>5} {c_bar} {c_label} │")
    lines.append(bold(f"  └{'─' * inner}┘"))
    lines.append("")

    # ── LATENCY (scalar stats) ───────────────────────────────
    lat = cur['lat']
    lines.append(bold(f"  ┌─ LATENCY (quote→fill, 10 ns cycles) {'─' * (inner - 38)}┐"))
    if lat is not None:
        ns_min = lat['min'] * NS_PER_CY
        ns_max = lat['max'] * NS_PER_CY
        ns_avg = lat['avg'] * NS_PER_CY
        s_min = bold(f"{lat['min']:>4}")
        s_avg = bold(f"{lat['avg']:>6.1f}")
        s_max = bold(f"{lat['max']:>4}")
        lines.append(
            f"  │ Min: {s_min} cy ({ns_min:>4} ns)   "
            f"Avg: {s_avg} cy ({ns_avg:>6.1f} ns)   "
            f"Max: {s_max} cy ({ns_max:>4} ns)   │"
        )
        lines.append(f"  │ Fills measured: {lat['count']:>10,}"
                     f"{' ' * (inner - 30)}│")
    else:
        msg = '(no fills measured yet — start trading first)'
        lines.append(f"  │ {dim(msg):<{inner + 10}}│")
        lines.append(f"  │ {'':<{inner - 2}}│")
    lines.append(bold(f"  └{'─' * inner}┘"))
    lines.append("")

    # ── LATENCY HISTOGRAM (16 bins x 32 cy) ──────────────────
    hist = cur['hist']
    title = f" LATENCY HISTOGRAM ({HIST_BIN_CY} cy/bin) "
    lines.append(bold(f"  ┌─{title}{'─' * (inner - len(title) - 1)}┐"))
    total_h = sum(hist)
    max_h   = max(hist) if hist else 0
    HBAR = max(20, inner - 30)
    if total_h == 0:
        empty_msg = '(no fills measured yet — histogram empty)'
        lines.append(f"  │ {dim(empty_msg):<{inner + 10}}│")
        for _ in range(NUM_HIST_BINS - 1):
            lines.append(f"  │{' ' * inner}│")
    else:
        for i, count in enumerate(hist):
            lo_cy = i * HIST_BIN_CY
            if i < NUM_HIST_BINS - 1:
                hi_cy = lo_cy + HIST_BIN_CY - 1
                label = f"{lo_cy:>3}-{hi_cy:<3} cy"          # 10 chars
            else:
                label = f"  >={lo_cy:<3}  cy"                # 10 chars (sat)
            pct = (count / total_h * 100.0) if total_h else 0.0
            bar_len = int(count / max_h * HBAR) if max_h else 0
            bar_padded = f"{'█' * bar_len:<{HBAR}}"
            if count == 0:
                c_bar = dim(f"{'·':<{HBAR}}"); c_lbl = dim(label)
                c_pct = dim(f"{pct:>5.1f}%");  c_cnt = dim(f"{count:>9,}")
            elif i <= 1:
                c_bar = green(bar_padded);  c_lbl = green(label)
                c_pct = green(f"{pct:>5.1f}%"); c_cnt = f"{count:>9,}"
            elif i <= 4:
                c_bar = cyan(bar_padded);   c_lbl = cyan(label)
                c_pct = cyan(f"{pct:>5.1f}%");  c_cnt = f"{count:>9,}"
            elif i <= 9:
                c_bar = yellow(bar_padded); c_lbl = yellow(label)
                c_pct = yellow(f"{pct:>5.1f}%"); c_cnt = f"{count:>9,}"
            else:
                c_bar = red(bar_padded);    c_lbl = red(label)
                c_pct = red(f"{pct:>5.1f}%"); c_cnt = f"{count:>9,}"
            lines.append(f"  │ {c_lbl} {c_bar} {c_pct} {c_cnt} │")
    lines.append(bold(f"  └{'─' * inner}┘"))
    lines.append("")

    # ── Footer ────────────────────────────────────────────────
    elapsed = cur['t'] - prev['start_t']
    lines.append(dim(
        f"  Running {elapsed:>7.1f}s  ·  "
        f"{time.strftime('%H:%M:%S')}  ·  "
        f"Ctrl+C to stop  ·  "
        f"regime_name='{regime_name}' (set on Board A)"
    ))
    lines.append("")

    return lines


# ═══════════════════════════════════════════════════════════════════════════
# Terminal main loop
# ═══════════════════════════════════════════════════════════════════════════
def print_summary(start_cash, final_cash, session):
    inner = W - 2
    print()
    print(bold_cyan(f"  ╔{'═' * inner}╗"))
    title = "SESSION SUMMARY"
    print(bold_cyan("  ║") + bold(title.center(inner)) + bold_cyan("║"))
    print(bold_cyan(f"  ╚{'═' * inner}╝"))
    print()
    net = final_cash - start_cash
    c_net = green(f"${net:+,.2f}") if net >= 0 else red(f"${net:+,.2f}")
    max_p = f"${session['max_cash']:+,.2f}"
    max_l = f"${session['min_cash']:+,.2f}"
    print(f"  Start cash : ${start_cash:+,.2f}")
    print(f"  End cash   : ${final_cash:+,.2f}")
    print(f"  Net P&L    : {c_net}")
    print(f"  Max profit : {green(max_p)}")
    print(f"  Max loss   : {red(max_l)}")
    print()


def run_dashboard(mmio, regime_name, poll_hz, duration_sec):
    interval = 1.0 / max(poll_hz, 0.1)
    start_t  = time.monotonic()
    deadline = float('inf') if duration_sec is None else start_t + duration_sec

    prev = snapshot(mmio, start_t, start_t)
    session = {
        'min_cash':   prev['cash'],
        'max_cash':   prev['cash'],
        'start_cash': prev['cash'],
    }

    sys.stdout.write(ANSI_HIDE_CURSOR + ANSI_CLEAR_SCREEN + ANSI_HOME)
    sys.stdout.flush()

    try:
        while time.monotonic() < deadline:
            time.sleep(interval)
            cur = snapshot(mmio, start_t, time.monotonic())
            frame = build_frame(prev, cur, session, regime_name)
            # Cursor home + write all lines + clear-to-end-of-screen for shrink-safety
            sys.stdout.write(ANSI_HOME)
            sys.stdout.write("\n".join(frame))
            sys.stdout.write(ANSI_CLEAR_TO_END)
            sys.stdout.flush()
            prev = cur
    except KeyboardInterrupt:
        pass
    finally:
        sys.stdout.write(ANSI_SHOW_CURSOR + "\n")
        sys.stdout.flush()

    print_summary(session['start_cash'], read_cash(mmio), session)


# ═══════════════════════════════════════════════════════════════════════════
# CLI
# ═══════════════════════════════════════════════════════════════════════════
def parse_args():
    p = argparse.ArgumentParser(
        description="Board B live terminal dashboard (no Jupyter required).",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    p.add_argument("--overlay",  default="overlays/board_b.bit",
                   help="Path to the Board B overlay bitstream.")
    p.add_argument("--ip-block", default="hft_core",
                   help="IP block name in the overlay for MMIO.")
    p.add_argument("--regime",   default="CALM", choices=VALID_REGIMES,
                   help="Informational only — name of the regime currently set on Board A.")
    p.add_argument("--poll-hz",  type=float, default=5.0,
                   help="Dashboard refresh rate in Hz.")
    p.add_argument("--duration", type=float, default=None,
                   help="Run for this many seconds, then exit. Omit to run forever.")
    p.add_argument("--no-arm",   action="store_true",
                   help="Skip configure_and_arm; just monitor whatever Board B is doing.")

    p.add_argument("--strategy", type=int, default=0, choices=[0, 1, 2, 3],
                   help="0=MEAN_REV, 1=MOMENTUM, 2=NN, 3=AUTO.")
    p.add_argument("--threshold", type=float, default=1.00,
                   help="Deviation threshold in dollars (Q16.16).")
    p.add_argument("--ema-alpha", type=int, default=0x199A,
                   help="EMA alpha (Q0.16). 0x199A ~ 0.1.")
    p.add_argument("--base-qty", type=int, default=50,
                   help="Shares per order.")
    p.add_argument("--max-position", type=int, default=10000,
                   help="Per-symbol absolute position limit.")
    p.add_argument("--max-order-rate", type=int, default=100000,
                   help="Total order count cap before risk halt.")
    p.add_argument("--max-loss", type=int, default=0x10000000,
                   help="Max loss in raw register units (Q16.16 dollars).")
    return p.parse_args()


def install_signal_handlers():
    # Make sure Ctrl+C also restores the cursor if we're ever killed mid-write.
    def _bye(signum, frame):
        sys.stdout.write(ANSI_SHOW_CURSOR + "\n")
        sys.stdout.flush()
        sys.exit(128 + signum)

    signal.signal(signal.SIGTERM, _bye)
    if hasattr(signal, "SIGHUP"):
        signal.signal(signal.SIGHUP, _bye)


def main():
    args = parse_args()
    install_signal_handlers()

    if not os.path.exists(args.overlay):
        print(f"ERROR: overlay not found: {args.overlay}", file=sys.stderr)
        sys.exit(1)

    _, mmio = open_mmio(args.overlay, args.ip_block)

    if not args.no_arm:
        configure_and_arm(
            mmio,
            strategy=args.strategy,
            threshold_dollars=args.threshold,
            ema_alpha=args.ema_alpha,
            base_qty=args.base_qty,
            max_position=args.max_position,
            max_order_rate=args.max_order_rate,
            max_loss=args.max_loss,
        )
    else:
        s = decode_status(mmio.read(B_STATUS))
        print(f"Skipping arm.  Current STATUS = {s}")

    print()
    print(f"Entering dashboard ({args.poll_hz:.1f} Hz, "
          f"{'forever' if args.duration is None else f'{args.duration:.1f}s'}).  "
          f"Ctrl+C to stop.")
    time.sleep(0.5)

    run_dashboard(mmio,
                  regime_name=args.regime,
                  poll_hz=args.poll_hz,
                  duration_sec=args.duration)


if __name__ == "__main__":
    main()
