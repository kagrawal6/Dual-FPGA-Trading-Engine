"""
Board B — Simple Live Monitor (Jupyter friendly) + React UI bridge
=================================================
Reads every AXI register Board B exposes and prints the values together
with the formulas that derive them.

This variant also supports pushing the snapshot to the laptop TradeMark React UI:
  - Start the laptop API with:  python react_boardb_server.py --ingest-http --host 0.0.0.0 --api-port 8765
  - In this notebook script, set API_BASE to your laptop's IP (NOT 127.0.0.1).
  - Call monitor(push_http=True) to POST each snapshot to /api/ingest.

Loops forever at ~2 Hz, refreshing the cell in place. Ctrl+C to stop.

Usage in a Jupyter cell on Board B's PYNQ:

    %run sw/board_b/live_monitor_simple.py
    monitor()                              # loops forever, Ctrl+C to stop
    monitor(initial_cash=500_000)          # different starting balance
    monitor(duration=30)                   # bounded run for 30 s
    monitor(push_http=True)                # also push to React UI
    snapshot()                             # one-shot read + print
"""

from __future__ import annotations

import time
from typing import Any, Dict, List

from pynq import MMIO, Overlay
from IPython.display import clear_output

try:
    import requests  # type: ignore
except Exception:
    requests = None  # type: ignore


# ════════════════════════════════════════════════════════════════════════════
# AXI offsets — match board_b_axi_regs.sv exactly
# ════════════════════════════════════════════════════════════════════════════
B_CTRL = 0x000
B_STRATEGY_SEL = 0x004
B_THRESHOLD = 0x008
B_EMA_ALPHA = 0x00C
B_BASE_QTY = 0x010
B_MAX_POSITION = 0x014
B_MAX_ORDER_RATE = 0x018
B_MAX_LOSS = 0x01C
B_STATUS = 0x040
B_QUOTES_RCVD = 0x044
B_ORDERS_SENT = 0x048
B_FILLS_RCVD = 0x04C
B_RISK_REJECTS = 0x050
B_LINK_ERRORS = 0x054
B_POS_BASE = 0x058
B_CASH_LO = 0x098
B_CASH_HI = 0x09C
B_HIST_BASE = 0x0A0
B_LAT_MIN = 0x0E0
B_LAT_MAX = 0x0E4
B_LAT_SUM = 0x0E8
B_LAT_COUNT = 0x0EC
B_BID_BASE = 0x100
B_ASK_BASE = 0x140
B_PNL_LO_BASE = 0x180
B_PNL_HI_BASE = 0x1C0
B_LAST_FILL_BASE = 0x200
B_TRADES_PACK_BASE = 0x240
B_EMA_BASE = 0x260  # B3
B_LAST_SIG_PACK = 0x2A0  # B3
B_LAST_LATENCY = 0x2A8  # B3

NUM_SYM = 16
NUM_HIST_BINS = 16
NS_PER_CY = 20  # 50 MHz core clock → 20 ns/cycle

STATE_NAMES = {0: "B_RESET", 1: "B_IDLE", 2: "B_ARMED", 3: "B_TRADING", 4: "B_HALTED"}
STRATEGY_NAMES = {0: "MEAN_REV", 1: "MOMENTUM", 2: "NN", 3: "AUTO"}
SIGNAL_LABELS = {0: "NONE", 1: "BUY", 2: "SELL", 3: "RISK_BLOCKED"}
SYMBOL_NAMES = [
    "AAPL",
    "MSFT",
    "GOOG",
    "META",
    "NVDA",
    "AMD",
    "INTC",
    "AVGO",
    "AMZN",
    "TSLA",
    "JPM",
    "GS",
    "JNJ",
    "PFE",
    "XOM",
    "CVX",
]

# Laptop API base (set to your laptop's IP on the LAN).
# Example: API_BASE = "http://192.168.4.1:8765"
API_BASE = "http://192.168.4.2:8765"


# ════════════════════════════════════════════════════════════════════════════
# Overlay + MMIO acquisition (idempotent)
# ════════════════════════════════════════════════════════════════════════════
try:
    ol_b  # noqa: F821
except NameError:
    print("Loading Board B overlay (overlays/board_b.bit)...")
    ol_b = Overlay("overlays/board_b.bit")

base_b = ol_b.ip_dict["hft_core"]["phys_addr"]
span_b = ol_b.ip_dict["hft_core"]["addr_range"]
mmio = MMIO(base_b, span_b)


# ════════════════════════════════════════════════════════════════════════════
# ANSI color helpers
# ════════════════════════════════════════════════════════════════════════════
def _c(t: str, code: str) -> str:
    return f"\033[{code}m{t}\033[0m"


def green(t: str) -> str:
    return _c(t, "32")


def red(t: str) -> str:
    return _c(t, "31")


def yellow(t: str) -> str:
    return _c(t, "33")


def cyan(t: str) -> str:
    return _c(t, "36")


def bold(t: str) -> str:
    return _c(t, "1")


def dim(t: str) -> str:
    return _c(t, "2")


def bold_cyan(t: str) -> str:
    return _c(t, "1;36")


# ════════════════════════════════════════════════════════════════════════════
# Decoders — each is a one-line formula straight out of the RTL spec
# ════════════════════════════════════════════════════════════════════════════
def q16_16_to_float(raw: int) -> float:
    """Q16.16 unsigned → float dollars."""
    return raw / 65536.0


def signed32(raw: int) -> int:
    """Interpret 32-bit unsigned as signed."""
    return raw - 0x100000000 if raw & 0x80000000 else raw


def cash_q32_16(lo: int, hi: int) -> float:
    """Reconstruct 48-bit signed Q32.16 from two AXI words."""
    raw = ((hi & 0xFFFF) << 32) | (lo & 0xFFFFFFFF)
    if raw & (1 << 47):
        raw -= 1 << 48
    return raw / 65536.0


def unpack_trades(packed_word: int, sym_idx: int) -> int:
    """TRADES_PACK[j] holds 2 syms × 16 bits. sym_idx → low or high half."""
    return (packed_word & 0xFFFF) if (sym_idx % 2 == 0) else ((packed_word >> 16) & 0xFFFF)


def unpack_signal(packed_word: int, sym_idx_in_word: int) -> int:
    """LAST_SIGNAL_PACK[j] holds 8 syms × 4 bits. sym_idx_in_word: 0..7."""
    return (packed_word >> (4 * sym_idx_in_word)) & 0xF


def take_snapshot(initial_cash: float) -> Dict[str, Any]:
    """Read every AXI register once and apply all derivation formulas."""
    raw_status = mmio.read(B_STATUS)
    status = {
        "strategy": STRATEGY_NAMES.get(raw_status & 0x3, "?"),
        "fsm": STATE_NAMES.get((raw_status >> 2) & 0x7, "?"),
        "link_up": bool(raw_status & 0x20),
        "risk_halt": bool(raw_status & 0x40),
        "raw": raw_status,
    }

    counters = {
        "quotes_rcvd": mmio.read(B_QUOTES_RCVD),
        "orders_sent": mmio.read(B_ORDERS_SENT),
        "fills_rcvd": mmio.read(B_FILLS_RCVD),
        "risk_rejects": mmio.read(B_RISK_REJECTS),
        "link_errors": mmio.read(B_LINK_ERRORS),
    }

    lat_count = mmio.read(B_LAT_COUNT)
    lat_sum = mmio.read(B_LAT_SUM)
    lat = {
        "min": mmio.read(B_LAT_MIN),
        "max": mmio.read(B_LAT_MAX),
        "sum": lat_sum,
        "count": lat_count,
        "avg": (lat_sum / lat_count) if lat_count else 0.0,
        "last": mmio.read(B_LAST_LATENCY),
    }

    hist = [mmio.read(B_HIST_BASE + 4 * i) for i in range(NUM_HIST_BINS)]

    pos = [signed32(mmio.read(B_POS_BASE + 4 * i)) for i in range(NUM_SYM)]
    bid = [q16_16_to_float(mmio.read(B_BID_BASE + 4 * i)) for i in range(NUM_SYM)]
    ask = [q16_16_to_float(mmio.read(B_ASK_BASE + 4 * i)) for i in range(NUM_SYM)]
    ema = [q16_16_to_float(mmio.read(B_EMA_BASE + 4 * i)) for i in range(NUM_SYM)]
    last_fill = [q16_16_to_float(mmio.read(B_LAST_FILL_BASE + 4 * i)) for i in range(NUM_SYM)]
    pnl_cash = [
        cash_q32_16(mmio.read(B_PNL_LO_BASE + 4 * i), mmio.read(B_PNL_HI_BASE + 4 * i))
        for i in range(NUM_SYM)
    ]
    trades_packs = [mmio.read(B_TRADES_PACK_BASE + 4 * j) for j in range((NUM_SYM + 1) // 2)]
    trades = [unpack_trades(trades_packs[i // 2], i) for i in range(NUM_SYM)]
    sig_packs = [mmio.read(B_LAST_SIG_PACK + 4 * j) for j in range((NUM_SYM + 7) // 8)]
    sig_codes = [unpack_signal(sig_packs[i // 8], i % 8) for i in range(NUM_SYM)]

    mid = [(b + a) * 0.5 if (a > 0 or b > 0) else 0.0 for b, a in zip(bid, ask)]
    spread = [(a - b) if (a > 0 and b > 0) else 0.0 for b, a in zip(bid, ask)]
    dev = [m - e for m, e in zip(mid, ema)]
    pos_value = [p * m for p, m in zip(pos, mid)]
    pnl_mtm = [pc + p * m for pc, p, m in zip(pnl_cash, pos, mid)]

    cash_raw = cash_q32_16(mmio.read(B_CASH_LO), mmio.read(B_CASH_HI))
    portfolio_val = sum(pos_value)
    account_cash = float(initial_cash) + cash_raw
    total_account = account_cash + portfolio_val
    total_pnl = cash_raw + portfolio_val
    return_pct = (total_pnl / initial_cash * 100.0) if initial_cash else 0.0

    return {
        "ts": time.time(),
        "status": status,
        "counters": counters,
        "lat": lat,
        "hist": hist,
        "pos": pos,
        "bid": bid,
        "ask": ask,
        "ema": ema,
        "last_fill": last_fill,
        "pnl_cash": pnl_cash,
        "trades": trades,
        "sig_codes": sig_codes,
        "mid": mid,
        "spread": spread,
        "dev": dev,
        "pos_value": pos_value,
        "pnl_mtm": pnl_mtm,
        "initial_cash": float(initial_cash),
        "cash_raw": cash_raw,
        "account_cash": account_cash,
        "portfolio_value": portfolio_val,
        "total_account": total_account,
        "total_pnl": total_pnl,
        "return_pct": return_pct,
    }


def _money(v: float, signed: bool = True) -> str:
    sign = "+" if (signed and v >= 0) else ("-" if v < 0 else " ")
    return f"${sign}{abs(v):>14,.2f}"


def _color_pnl(v: float):
    if v > 0.005:
        return green
    if v < -0.005:
        return red
    return dim


def render(snap: Dict[str, Any]) -> None:
    s = snap["status"]
    cnt = snap["counters"]
    lat = snap["lat"]

    print(bold_cyan("╔══════════════════════════════════════════════════════════════════════╗"))
    print(bold_cyan("║       BOARD B  ·  AXI SIGNAL MONITOR  (every formula visible)        ║"))
    print(bold_cyan("╚══════════════════════════════════════════════════════════════════════╝"))

    fsm_color = green if s["fsm"] == "B_TRADING" else yellow if s["fsm"] == "B_ARMED" else red if s["fsm"] == "B_HALTED" else cyan
    link_str = green("UP") if s["link_up"] else red("DOWN")
    risk_str = red("HALTED") if s["risk_halt"] else green("OK")
    raw_str = dim(f"[STATUS@0x040 = 0x{s['raw']:08X}]")
    print(
        f"  STATUS  fsm={fsm_color(s['fsm']):<14}  "
        f"link={link_str:<5}  risk={risk_str:<8}  "
        f"strat={cyan(s['strategy'])}    {raw_str}"
    )
    print()

    print(bold("  ACCOUNT MATH ─ how every dollar figure is built up"))
    print(f"    initial_cash       (python const)             = {_money(snap['initial_cash'])}")
    print(
        f"    cash_raw           [CASH_LO|HI 0x098|0x09C]   = "
        f"{_color_pnl(snap['cash_raw'])(_money(snap['cash_raw']))}    "
        f"{dim('← signed Q32.16 cash flow (RTL starts at 0)')}"
    )
    print(f"    account_cash        = initial + cash_raw      = {_money(snap['account_cash'])}")
    print(
        f"    portfolio_value     = Σ pos[i] * mid[i]       = "
        f"{_color_pnl(snap['portfolio_value'])(_money(snap['portfolio_value']))}"
    )
    print(f"    total_account       = account + portfolio     = {bold(_money(snap['total_account']))}")
    pnl_clr = _color_pnl(snap["total_pnl"])
    pct_str = pnl_clr(f"({snap['return_pct']:+.3f}%)")
    print(f"    total_pnl           = cash_raw + portfolio    = {pnl_clr(_money(snap['total_pnl']))}    {pct_str}")
    print()

    print(bold("  COUNTERS"))
    print(
        f"    quotes_rcvd  [0x044] = {cnt['quotes_rcvd']:>10,}    "
        f"orders_sent [0x048] = {cnt['orders_sent']:>10,}    "
        f"fills_rcvd  [0x04C] = {cnt['fills_rcvd']:>10,}"
    )
    print(
        f"    risk_rejects [0x050] = {cnt['risk_rejects']:>10,}    "
        f"link_errors [0x054] = {cnt['link_errors']:>10,}"
    )
    print()

    print(bold("  LATENCY  (cycles → ns at 50 MHz, 1 cy = 20 ns)"))
    if lat["count"]:
        print(
            f"    min  [0x0E0] = {lat['min']:>5} cy ({lat['min']*NS_PER_CY:>5} ns)    "
            f"max  [0x0E4] = {lat['max']:>5} cy ({lat['max']*NS_PER_CY:>5} ns)"
        )
        print(
            f"    sum  [0x0E8] = {lat['sum']:>10}     "
            f"count [0x0EC] = {lat['count']:>10}     "
            f"avg = sum/count = {lat['avg']:>6.2f} cy ({lat['avg']*NS_PER_CY:>6.1f} ns)"
        )
        print(f"    last [0x2A8] = {bold(str(lat['last']))} cy ({lat['last']*NS_PER_CY} ns)")
    else:
        print(dim("    (no fills measured yet)"))
    print()

    print(bold("  PER-SYMBOL  (every column derived from registers shown to its right)"))
    hdr = (
        f"    {'sym':<5} {'pos':>5} {'bid':>8} {'ask':>8} {'mid':>8} "
        f"{'spread':>7} {'ema':>8} {'dev':>7} {'last_fill':>10} "
        f"{'pnl_mtm':>10} {'trd':>4} {'sig':<13}"
    )
    print(dim(hdr))
    for i in range(NUM_SYM):
        sig_lbl = SIGNAL_LABELS.get(int(snap["sig_codes"][i]), f"R({snap['sig_codes'][i]})")
        sig_color = green if sig_lbl == "BUY" else red if sig_lbl == "SELL" else yellow if sig_lbl == "RISK_BLOCKED" else dim

        p = int(snap["pos"][i])
        pos_str = f"{p:>+5}" if p != 0 else "    0"
        pos_str = green(pos_str) if p > 0 else red(pos_str) if p < 0 else dim(pos_str)

        pv = float(snap["pnl_mtm"][i])
        pnl_str = _color_pnl(pv)(f"{pv:>+10.2f}")

        dv = float(snap["dev"][i])
        dev_str = f"{dv:>+7.3f}"
        dev_str = green(dev_str) if dv > 0.001 else red(dev_str) if dv < -0.001 else dim(dev_str)

        print(
            f"    {SYMBOL_NAMES[i]:<5} "
            f"{pos_str} "
            f"{float(snap['bid'][i]):>8.2f} "
            f"{float(snap['ask'][i]):>8.2f} "
            f"{float(snap['mid'][i]):>8.2f} "
            f"{float(snap['spread'][i]):>7.3f} "
            f"{float(snap['ema'][i]):>8.2f} "
            f"{dev_str} "
            f"{float(snap['last_fill'][i]):>10.2f} "
            f"{pnl_str} "
            f"{int(snap['trades'][i]):>4} "
            f"{sig_color(sig_lbl)}"
        )

    print()
    print(dim(f"  ts={time.strftime('%H:%M:%S', time.localtime(snap['ts']))}   refresh: 2 Hz · Ctrl+C to stop"))


def push_to_site(snap: Dict[str, Any]) -> Dict[str, Any]:
    if requests is None:
        raise RuntimeError("requests not installed. In a cell:  !pip install requests")

    url = f"{API_BASE}/api/ingest"
    payload: Dict[str, Any] = {
        "ts": float(snap["ts"]),
        "state": str(snap["status"]["fsm"]),
        "link_up": bool(snap["status"]["link_up"]),
        "risk_halt": bool(snap["status"]["risk_halt"]),
        "strategy": str(snap["status"]["strategy"]),
        "q": int(snap["counters"]["quotes_rcvd"]),
        "o": int(snap["counters"]["orders_sent"]),
        "f": int(snap["counters"]["fills_rcvd"]),
        "rej": int(snap["counters"]["risk_rejects"]),
        "link_err": int(snap["counters"]["link_errors"]),
        "cash": float(snap["account_cash"]),
        "total_pnl": float(snap["total_pnl"]),
        "port_value": float(snap["total_account"]),
        "pos": list(map(int, snap["pos"])),
        "bid": list(map(float, snap["bid"])),
        "ask": list(map(float, snap["ask"])),
        "mid": list(map(float, snap["mid"])),
        "spread": list(map(float, snap["spread"])),
        "ema": list(map(float, snap["ema"])),
        "signal_code": list(map(int, snap["sig_codes"])),
        "signal": [SIGNAL_LABELS.get(int(x), "NONE") for x in snap["sig_codes"]],
        "pnl_cash": list(map(float, snap["pnl_cash"])),
        "pnl_mtm": list(map(float, snap["pnl_mtm"])),
        "pos_value": list(map(float, snap["pos_value"])),
        "last_fill": list(map(float, snap["last_fill"])),
        "trades": list(map(int, snap["trades"])),
        "hist": list(map(int, snap["hist"])),
        "lat_min": int(snap["lat"]["min"]),
        "lat_max": int(snap["lat"]["max"]),
        "lat_sum": int(snap["lat"]["sum"]),
        "lat_cnt": int(snap["lat"]["count"]),
        "last_latency": int(snap["lat"]["last"]),
        "symbol_names": list(SYMBOL_NAMES),
    }

    r = requests.post(url, json=payload, timeout=0.25)
    r.raise_for_status()
    out = r.json()
    if not out.get("ok", False):
        raise RuntimeError(f"ingest failed: {out}")
    return out


def snapshot(initial_cash: float = 1_000_000.0) -> Dict[str, Any]:
    snap = take_snapshot(initial_cash)
    render(snap)
    return snap


def monitor(
    duration: float | None = None,
    poll_hz: float = 2.0,
    initial_cash: float = 1_000_000.0,
    push_http: bool = False,
) -> None:
    interval = 1.0 / float(poll_hz)
    t_start = time.monotonic()
    deadline = float("inf") if duration is None else (t_start + float(duration))
    try:
        while time.monotonic() < deadline:
            snap = take_snapshot(initial_cash)
            if push_http:
                push_to_site(snap)
            clear_output(wait=True)
            render(snap)
            time.sleep(interval)
    except KeyboardInterrupt:
        print("\n  monitor stopped.")


print("Loaded. Quick start:")
print("    snapshot()")
print("    monitor()")
print("    monitor(push_http=True)   # also drives the React UI via POST /api/ingest")

