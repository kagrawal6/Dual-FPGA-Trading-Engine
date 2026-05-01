"""
Board B — Simple Live Monitor (Jupyter friendly)
=================================================
Reads every AXI register Board B exposes and prints the values together
with the formulas that derive them. The point of this file (vs.
live_monitor.py) is to make the math *visible*: you can see exactly which
register address every dashboard number came from, and which derivation
combines them.

Loops forever at ~2 Hz, refreshing the cell in place. Ctrl+C to stop.

Usage in a Jupyter cell on Board B's PYNQ:

    %run board_b/live_monitor_simple.py
    monitor()                        # loops forever, Ctrl+C to stop
    monitor(initial_cash=500_000)    # different starting balance
    monitor(duration=30)             # bounded run for 30 s
    snapshot()                       # one-shot read + print

The monitor never writes to the board, so it's safe to leave running while
you experiment elsewhere. Use configure_and_arm() in live_monitor.py if
you need to start the trader FSM.
"""

import time
from pynq import Overlay, MMIO
from IPython.display import clear_output


# ════════════════════════════════════════════════════════════════════════════
# AXI offsets — match board_b_axi_regs.sv exactly
# ════════════════════════════════════════════════════════════════════════════
B_CTRL              = 0x000
B_STRATEGY_SEL      = 0x004
B_THRESHOLD         = 0x008
B_EMA_ALPHA         = 0x00C
B_BASE_QTY          = 0x010
B_MAX_POSITION      = 0x014
B_MAX_ORDER_RATE    = 0x018
B_MAX_LOSS          = 0x01C
B_STATUS            = 0x040
B_QUOTES_RCVD       = 0x044
B_ORDERS_SENT       = 0x048
B_FILLS_RCVD        = 0x04C
B_RISK_REJECTS      = 0x050
B_LINK_ERRORS       = 0x054
B_POS_BASE          = 0x058
B_CASH_LO           = 0x098
B_CASH_HI           = 0x09C
B_HIST_BASE         = 0x0A0
B_LAT_MIN           = 0x0E0
B_LAT_MAX           = 0x0E4
B_LAT_SUM           = 0x0E8
B_LAT_COUNT         = 0x0EC
B_BID_BASE          = 0x100
B_ASK_BASE          = 0x140
B_PNL_LO_BASE       = 0x180
B_PNL_HI_BASE       = 0x1C0
B_LAST_FILL_BASE    = 0x200
B_TRADES_PACK_BASE  = 0x240
B_EMA_BASE          = 0x260           # B3
B_LAST_SIG_PACK     = 0x2A0           # B3
B_LAST_LATENCY      = 0x2A8           # B3

NUM_SYM        = 16
NUM_HIST_BINS  = 16
NS_PER_CY      = 20      # 50 MHz core clock → 20 ns/cycle

STATE_NAMES    = {0: 'B_RESET', 1: 'B_IDLE', 2: 'B_ARMED', 3: 'B_TRADING', 4: 'B_HALTED'}
STRATEGY_NAMES = {0: 'MEAN_REV', 1: 'MOMENTUM', 2: 'NN', 3: 'AUTO'}
SIGNAL_LABELS  = {0: 'NONE', 1: 'BUY', 2: 'SELL', 3: 'RISK_BLOCKED'}
SYMBOL_NAMES   = ['AAPL','MSFT','GOOG','META','NVDA','AMD','INTC','AVGO',
                  'AMZN','TSLA','JPM','GS','JNJ','PFE','XOM','CVX']


# ════════════════════════════════════════════════════════════════════════════
# Overlay + MMIO acquisition (idempotent)
# ════════════════════════════════════════════════════════════════════════════
try:
    ol_b  # noqa: F821
except NameError:
    print("Loading Board B overlay (overlays/board_b.bit)...")
    ol_b = Overlay('overlays/board_b.bit')

base_b = ol_b.ip_dict['hft_core']['phys_addr']
span_b = ol_b.ip_dict['hft_core']['addr_range']
mmio = MMIO(base_b, span_b)


# ════════════════════════════════════════════════════════════════════════════
# ANSI color helpers (minimal subset of live_monitor.py)
# ════════════════════════════════════════════════════════════════════════════
def _c(t, code): return f"\033[{code}m{t}\033[0m"
def green(t):  return _c(t, "32")
def red(t):    return _c(t, "31")
def yellow(t): return _c(t, "33")
def cyan(t):   return _c(t, "36")
def bold(t):   return _c(t, "1")
def dim(t):    return _c(t, "2")
def bold_cyan(t): return _c(t, "1;36")


# ════════════════════════════════════════════════════════════════════════════
# Decoders — each is a one-line formula straight out of the RTL spec
# ════════════════════════════════════════════════════════════════════════════
def q16_16_to_float(raw):
    """Q16.16 unsigned → float dollars."""
    return raw / 65536.0

def signed32(raw):
    """Interpret 32-bit unsigned as signed."""
    return raw - 0x100000000 if raw & 0x80000000 else raw

def cash_q32_16(lo, hi):
    """Reconstruct 48-bit signed Q32.16 from two AXI words.
    raw = (hi[15:0] << 32) | lo[31:0], sign-extended at bit 47."""
    raw = ((hi & 0xFFFF) << 32) | (lo & 0xFFFFFFFF)
    if raw & (1 << 47):
        raw -= 1 << 48
    return raw / 65536.0

def unpack_trades(packed_word, sym_idx):
    """TRADES_PACK[j] holds 2 syms × 16 bits. sym_idx → low or high half."""
    return (packed_word & 0xFFFF) if (sym_idx % 2 == 0) else ((packed_word >> 16) & 0xFFFF)

def unpack_signal(packed_word, sym_idx_in_word):
    """LAST_SIGNAL_PACK[j] holds 8 syms × 4 bits. sym_idx_in_word: 0..7."""
    return (packed_word >> (4 * sym_idx_in_word)) & 0xF


# ════════════════════════════════════════════════════════════════════════════
# Snapshot — one read pass for every exposed signal
# ════════════════════════════════════════════════════════════════════════════
def take_snapshot(initial_cash):
    """Read every AXI register once and apply all derivation formulas.
    Returns a dict where every key is annotated with its source addr/formula."""
    # ── Status word ────────────────────────────────────────────────────────
    raw_status = mmio.read(B_STATUS)
    status = {
        'strategy':  STRATEGY_NAMES.get(raw_status & 0x3, '?'),
        'fsm':       STATE_NAMES.get((raw_status >> 2) & 0x7, '?'),
        'link_up':   bool(raw_status & 0x20),
        'risk_halt': bool(raw_status & 0x40),
        'raw':       raw_status,
    }

    # ── Aggregate counters ─────────────────────────────────────────────────
    counters = {
        'quotes_rcvd':  mmio.read(B_QUOTES_RCVD),
        'orders_sent':  mmio.read(B_ORDERS_SENT),
        'fills_rcvd':   mmio.read(B_FILLS_RCVD),
        'risk_rejects': mmio.read(B_RISK_REJECTS),
        'link_errors':  mmio.read(B_LINK_ERRORS),
    }

    # ── Latency aggregates + B3 last-sample ────────────────────────────────
    lat_count = mmio.read(B_LAT_COUNT)
    lat = {
        'min':   mmio.read(B_LAT_MIN),
        'max':   mmio.read(B_LAT_MAX),
        'sum':   mmio.read(B_LAT_SUM),
        'count': lat_count,
        'avg':   (mmio.read(B_LAT_SUM) / lat_count) if lat_count else 0.0,
        'last':  mmio.read(B_LAST_LATENCY),
    }

    # ── Latency histogram (16 bins) ────────────────────────────────────────
    hist = [mmio.read(B_HIST_BASE + 4*i) for i in range(NUM_HIST_BINS)]

    # ── Per-symbol arrays (read everything in one pass) ────────────────────
    pos       = [signed32(mmio.read(B_POS_BASE + 4*i))           for i in range(NUM_SYM)]
    bid       = [q16_16_to_float(mmio.read(B_BID_BASE + 4*i))    for i in range(NUM_SYM)]
    ask       = [q16_16_to_float(mmio.read(B_ASK_BASE + 4*i))    for i in range(NUM_SYM)]
    ema       = [q16_16_to_float(mmio.read(B_EMA_BASE + 4*i))    for i in range(NUM_SYM)]
    last_fill = [q16_16_to_float(mmio.read(B_LAST_FILL_BASE + 4*i)) for i in range(NUM_SYM)]
    pnl_cash  = [cash_q32_16(mmio.read(B_PNL_LO_BASE + 4*i),
                             mmio.read(B_PNL_HI_BASE + 4*i))     for i in range(NUM_SYM)]
    trades_packs = [mmio.read(B_TRADES_PACK_BASE + 4*j) for j in range((NUM_SYM + 1) // 2)]
    trades = [unpack_trades(trades_packs[i // 2], i) for i in range(NUM_SYM)]
    sig_packs = [mmio.read(B_LAST_SIG_PACK + 4*j) for j in range((NUM_SYM + 7) // 8)]
    sig_codes = [unpack_signal(sig_packs[i // 8], i % 8) for i in range(NUM_SYM)]

    # ── Derived per-symbol formulas ────────────────────────────────────────
    mid       = [(b + a) * 0.5 if (a > 0 or b > 0) else 0.0 for b, a in zip(bid, ask)]
    spread    = [(a - b) if (a > 0 and b > 0) else 0.0 for b, a in zip(bid, ask)]
    dev       = [m - e for m, e in zip(mid, ema)]              # mid − EMA  (strategy input)
    pos_value = [p * m for p, m in zip(pos, mid)]              # mark-to-market position
    pnl_mtm   = [pc + p * m for pc, p, m in zip(pnl_cash, pos, mid)]

    # ── Account-level math ─────────────────────────────────────────────────
    cash_raw       = cash_q32_16(mmio.read(B_CASH_LO), mmio.read(B_CASH_HI))
    portfolio_val  = sum(pos_value)
    account_cash   = initial_cash + cash_raw
    total_account  = account_cash + portfolio_val
    total_pnl      = cash_raw + portfolio_val           # = total_account − initial_cash
    return_pct     = (total_pnl / initial_cash * 100.0) if initial_cash else 0.0

    return {
        'ts': time.time(),
        'status': status,
        'counters': counters,
        'lat': lat,
        'hist': hist,
        # Per-symbol arrays
        'pos': pos, 'bid': bid, 'ask': ask, 'ema': ema,
        'last_fill': last_fill, 'pnl_cash': pnl_cash, 'trades': trades,
        'sig_codes': sig_codes,
        'mid': mid, 'spread': spread, 'dev': dev,
        'pos_value': pos_value, 'pnl_mtm': pnl_mtm,
        # Account
        'initial_cash': initial_cash,
        'cash_raw': cash_raw,
        'account_cash': account_cash,
        'portfolio_value': portfolio_val,
        'total_account': total_account,
        'total_pnl': total_pnl,
        'return_pct': return_pct,
    }


# ════════════════════════════════════════════════════════════════════════════
# Renderers — every panel labels each value with its addr/formula
# ════════════════════════════════════════════════════════════════════════════
def _money(v, signed=True):
    sign = '+' if (signed and v >= 0) else ('-' if v < 0 else ' ')
    return f"${sign}{abs(v):>14,.2f}"

def _color_pnl(v):
    if v > 0.005:  return green
    if v < -0.005: return red
    return dim


def render(snap):
    s     = snap['status']
    cnt   = snap['counters']
    lat   = snap['lat']

    print(bold_cyan("╔══════════════════════════════════════════════════════════════════════╗"))
    print(bold_cyan("║       BOARD B  ·  AXI SIGNAL MONITOR  (every formula visible)        ║"))
    print(bold_cyan("╚══════════════════════════════════════════════════════════════════════╝"))

    # ── Status line ────────────────────────────────────────────────────────
    fsm_color = (green if s['fsm'] == 'B_TRADING' else
                 yellow if s['fsm'] == 'B_ARMED' else
                 red if s['fsm'] == 'B_HALTED' else cyan)
    link_str = green('UP') if s['link_up'] else red('DOWN')
    risk_str = red('HALTED') if s['risk_halt'] else green('OK')
    raw_str = dim(f"[STATUS@0x040 = 0x{s['raw']:08X}]")
    print(f"  STATUS  fsm={fsm_color(s['fsm']):<14}  "
          f"link={link_str:<5}  risk={risk_str:<8}  "
          f"strat={cyan(s['strategy'])}    {raw_str}")
    print()

    # ── ACCOUNT MATH (the cash/portfolio/PnL story) ────────────────────────
    print(bold("  ACCOUNT MATH ─ how every dollar figure is built up"))
    print(f"    initial_cash       (python const)             = {_money(snap['initial_cash'])}")
    print(f"    cash_raw           [CASH_LO|HI 0x098|0x09C]   = {_color_pnl(snap['cash_raw'])(_money(snap['cash_raw']))}    "
          f"{dim('← signed Q32.16 cash flow (RTL starts at 0)')}")
    print(f"    account_cash        = initial + cash_raw      = {_money(snap['account_cash'])}    "
          f"{dim('← what is in the account right now')}")
    print(f"    portfolio_value     = Σ pos[i] * mid[i]       = {_color_pnl(snap['portfolio_value'])(_money(snap['portfolio_value']))}    "
          f"{dim('← holdings marked-to-market')}")
    print(f"    total_account       = account + portfolio     = {bold(_money(snap['total_account']))}")
    pnl_clr = _color_pnl(snap['total_pnl'])
    pct_str = pnl_clr(f"({snap['return_pct']:+.3f}%)")
    print(f"    total_pnl           = cash_raw + portfolio    = "
          f"{pnl_clr(_money(snap['total_pnl']))}    {pct_str}")
    print()

    # ── COUNTERS ───────────────────────────────────────────────────────────
    print(bold("  COUNTERS"))
    print(f"    quotes_rcvd  [0x044] = {cnt['quotes_rcvd']:>10,}    "
          f"orders_sent [0x048] = {cnt['orders_sent']:>10,}    "
          f"fills_rcvd  [0x04C] = {cnt['fills_rcvd']:>10,}")
    print(f"    risk_rejects [0x050] = {cnt['risk_rejects']:>10,}    "
          f"link_errors [0x054] = {cnt['link_errors']:>10,}")
    do = cnt['orders_sent']; df = cnt['fills_rcvd']; drr = cnt['risk_rejects']
    fill_rate = (df / do * 100.0) if do else 0.0
    rej_rate  = (drr / (do + drr) * 100.0) if (do + drr) else 0.0
    print(dim(f"    derived: fill_rate = fills/orders = {fill_rate:5.1f}%   "
              f"reject_rate = rej/(ord+rej) = {rej_rate:5.1f}%"))
    print()

    # ── LATENCY ────────────────────────────────────────────────────────────
    print(bold("  LATENCY  (cycles → ns at 50 MHz, 1 cy = 20 ns)"))
    if lat['count']:
        print(f"    min  [0x0E0] = {lat['min']:>5} cy ({lat['min']*NS_PER_CY:>5} ns)    "
              f"max  [0x0E4] = {lat['max']:>5} cy ({lat['max']*NS_PER_CY:>5} ns)")
        print(f"    sum  [0x0E8] = {lat['sum']:>10}     "
              f"count [0x0EC] = {lat['count']:>10}     "
              f"avg = sum/count = {lat['avg']:>6.2f} cy ({lat['avg']*NS_PER_CY:>6.1f} ns)")
        print(f"    last [0x2A8] = {bold(str(lat['last']))} cy "
              f"({lat['last']*NS_PER_CY} ns)    "
              f"{dim('← B3: most recent single fill_processed sample')}")
    else:
        print(dim("    (no fills measured yet)"))
    print()

    # ── PER-SYMBOL TABLE ───────────────────────────────────────────────────
    print(bold("  PER-SYMBOL  (every column derived from registers shown to its right)"))
    hdr = (f"    {'sym':<5} {'pos':>5} {'bid':>8} {'ask':>8} {'mid':>8} "
           f"{'spread':>7} {'ema':>8} {'dev':>7} {'last_fill':>10} "
           f"{'pnl_mtm':>10} {'trd':>4} {'sig':<13}")
    print(dim(hdr))
    for i in range(NUM_SYM):
        sig_lbl = SIGNAL_LABELS.get(snap['sig_codes'][i], f"R({snap['sig_codes'][i]})")
        sig_color = (green if sig_lbl == 'BUY' else
                     red if sig_lbl == 'SELL' else
                     yellow if sig_lbl == 'RISK_BLOCKED' else dim)

        pos      = snap['pos'][i]
        pos_str  = f"{pos:>+5}" if pos != 0 else "    0"
        pos_str  = green(pos_str) if pos > 0 else (red(pos_str) if pos < 0 else dim(pos_str))

        pnl_str  = f"{snap['pnl_mtm'][i]:>+10.2f}"
        pnl_str  = _color_pnl(snap['pnl_mtm'][i])(pnl_str)

        dev      = snap['dev'][i]
        dev_str  = f"{dev:>+7.3f}"
        dev_str  = (green(dev_str) if dev > 0.001 else
                    red(dev_str) if dev < -0.001 else dim(dev_str))

        print(f"    {SYMBOL_NAMES[i]:<5} "
              f"{pos_str} "
              f"{snap['bid'][i]:>8.2f} "
              f"{snap['ask'][i]:>8.2f} "
              f"{snap['mid'][i]:>8.2f} "
              f"{snap['spread'][i]:>7.3f} "
              f"{snap['ema'][i]:>8.2f} "
              f"{dev_str} "
              f"{snap['last_fill'][i]:>10.2f} "
              f"{pnl_str} "
              f"{snap['trades'][i]:>4} "
              f"{sig_color(sig_lbl)}")

    # ── Formula key (printed once per refresh so the user sees the math) ──
    print()
    print(dim("  KEY (per symbol i):"))
    print(dim("    pos[i]       = signed32(mmio[0x058 + 4*i])"))
    print(dim("    bid[i]       = mmio[0x100 + 4*i] / 65536        ; ask[i] = mmio[0x140 + 4*i] / 65536"))
    print(dim("    mid[i]       = (bid[i] + ask[i]) / 2             ; spread[i] = ask[i] − bid[i]"))
    print(dim("    ema[i]       = mmio[0x260 + 4*i] / 65536         ; dev[i] = mid[i] − ema[i]   ← strategy input"))
    print(dim("    last_fill[i] = mmio[0x200 + 4*i] / 65536"))
    print(dim("    pnl_cash[i]  = cash_q32_16(mmio[0x180+4*i], mmio[0x1C0+4*i])"))
    print(dim("    pnl_mtm[i]   = pnl_cash[i] + pos[i] * mid[i]     ← realized + unrealized"))
    print(dim("    trades[i]    = unpack(mmio[0x240 + 4*(i//2)], i % 2)"))
    print(dim("    signal[i]    = unpack(mmio[0x2A0 + 4*(i//8)], i % 8)   {0=NONE 1=BUY 2=SELL 3=RISK_BLOCKED}"))
    print()
    print(dim(f"  ts={time.strftime('%H:%M:%S', time.localtime(snap['ts']))}   "
              f"refresh: 2 Hz · Ctrl+C to stop"))


# ════════════════════════════════════════════════════════════════════════════
# Public entry points
# ════════════════════════════════════════════════════════════════════════════
def snapshot(initial_cash=1_000_000.0):
    """Read everything once, render, return the dict. Useful for one-shot debug."""
    snap = take_snapshot(initial_cash)
    render(snap)
    return snap


def monitor(duration=None, poll_hz=2.0, initial_cash=1_000_000.0):
    """Loop forever (or until `duration` seconds), refreshing the cell.

    Args:
        duration     : seconds to run, or None for forever (Ctrl+C to stop).
        poll_hz      : refresh rate. 2 Hz is comfortable; AXI reads are cheap.
        initial_cash : Python-side starting balance (RTL `cash` is just the
                       cumulative cash flow, starts at 0).
    """
    interval = 1.0 / poll_hz
    t_start = time.monotonic()
    deadline = float('inf') if duration is None else (t_start + duration)
    try:
        while time.monotonic() < deadline:
            snap = take_snapshot(initial_cash)
            clear_output(wait=True)
            render(snap)
            time.sleep(interval)
    except KeyboardInterrupt:
        print("\n  monitor stopped.")


# ════════════════════════════════════════════════════════════════════════════
# Trader control — start / stop / arm. (writes CTRL + config registers)
# ════════════════════════════════════════════════════════════════════════════
def configure_and_arm(strategy=0,
                       threshold=0x00010000,    # $1.00 deviation (Q16.16)
                       ema_alpha=0x0000199A,    # ~0.1
                       base_qty=50,
                       max_position=10000,
                       max_order_rate=100000,
                       max_loss=0x10000000,     # ~$4096
                       verbose=True):
    """Reset → write all config regs → pulse CTRL=1 twice to advance the FSM
    through IDLE → ARMED → TRADING. Returns the resulting STATUS dict.

    If FSM stays at B_ARMED instead of B_TRADING, **flip SW[0] UP** on the
    physical Board B board — that switch is the human kill-switch gate."""
    # 1. Reset (CTRL[1] pulse) — clears counters, drops back to IDLE
    mmio.write(B_CTRL, 0x02); time.sleep(0.1)

    # 2. Write all writable config registers
    mmio.write(B_STRATEGY_SEL,   strategy)
    mmio.write(B_THRESHOLD,      threshold)
    mmio.write(B_EMA_ALPHA,      ema_alpha)
    mmio.write(B_BASE_QTY,       base_qty)
    mmio.write(B_MAX_POSITION,   max_position)
    mmio.write(B_MAX_ORDER_RATE, max_order_rate)
    mmio.write(B_MAX_LOSS,       max_loss)

    # 3. Start (CTRL[0] pulse). Pulsed twice: first edge IDLE→ARMED,
    #    second edge ARMED→TRADING (gated by SW[0] high & link_up).
    mmio.write(B_CTRL, 0x01); time.sleep(0.1)
    mmio.write(B_CTRL, 0x01); time.sleep(0.3)

    raw = mmio.read(B_STATUS)
    s = {
        'strategy':  STRATEGY_NAMES.get(raw & 0x3, '?'),
        'fsm':       STATE_NAMES.get((raw >> 2) & 0x7, '?'),
        'link_up':   bool(raw & 0x20),
        'risk_halt': bool(raw & 0x40),
    }

    if verbose:
        print(f"Board B armed.  STATUS = {s}")
        if s['fsm'] == 'B_TRADING':
            print(green("  ✓ Trading live. Run monitor() to watch."))
        elif s['fsm'] == 'B_ARMED':
            print(yellow("  ⚠ Stuck at B_ARMED — flip physical SW[0] UP on Board B,"))
            print(yellow("    then call configure_and_arm() again."))
        elif s['fsm'] == 'B_IDLE':
            print(yellow("  ⚠ Still at B_IDLE — usually means the second CTRL pulse"))
            print(yellow("    didn't advance. Check link_up (Board A must be running"))
            print(yellow("    and the PMOD cable connected)."))
        elif s['fsm'] == 'B_HALTED':
            print(red("  ✗ B_HALTED — risk_halt tripped. Increase max_loss and re-arm."))
        if not s['link_up']:
            print(red("  ✗ link_up == 0 — Board A is not sending. Start Board A first."))
    return s


def stop_trading():
    """Pulse CTRL[1] — drops the FSM back to IDLE. Positions remain readable."""
    mmio.write(B_CTRL, 0x02); time.sleep(0.1)
    raw = mmio.read(B_STATUS)
    print(f"  STATUS now = fsm={STATE_NAMES.get((raw >> 2) & 0x7, '?')}")


def start_trading(**kwargs):
    """Alias for configure_and_arm(). Same args."""
    return configure_and_arm(**kwargs)


print("Loaded. Quick start:")
print("    configure_and_arm()               # configure + start (FSM → B_TRADING)")
print("    monitor()                         # live dashboard, Ctrl+C to stop")
print("    stop_trading()                    # pause (CTRL=2)")
print()
print("One-shot helpers:")
print("    snapshot()                        # one-shot read of every AXI signal")
print("    monitor(duration=30)              # bounded 30 s")
print("    monitor(initial_cash=500_000)     # different starting balance")
