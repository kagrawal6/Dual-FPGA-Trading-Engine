"""
live_prices.py — Robinhood-style terminal trading display.
Runs on your LAPTOP. Connects to pynq_server.py on the PYNQ board.

Install:  pip install requests rich asciichartpy windows-curses
Run:      python live_prices.py --ip 192.168.3.1

Controls:
    0-3        switch market regime
    UP/DOWN    navigate stock list
    ENTER      select stock to view chart
    ESC        back to full table
    q          quit
"""

import argparse
import time
import threading
import collections
import os
import sys
import requests
from datetime import datetime

from rich.console import Console
from rich.table import Table
from rich.live import Live
from rich.panel import Panel
from rich.text import Text
from rich import box
from rich.console import Group

console = Console()

Q16            = 65536.0
HISTORY_LEN    = 240
MAX_CHART_W    = 60

REGIME_NAMES  = {0: "CALM", 1: "VOLATILE", 2: "BURST", 3: "ADVERSARIAL"}
REGIME_COLORS = {0: "green", 1: "yellow", 2: "red", 3: "bold magenta"}

SECTORS = {
    "AAPL":"Tech",  "MSFT":"Tech",  "GOOG":"Tech",  "META":"Tech",
    "NVDA":"Semi",  "AMD":"Semi",   "INTC":"Semi",  "AVGO":"Semi",
    "AMZN":"Cons",  "TSLA":"Cons",
    "JPM":"Fin",    "GS":"Fin",
    "JNJ":"Health", "PFE":"Health",
    "XOM":"Energy", "CVX":"Energy",
}

# ── shared state ──────────────────────────────────────────────────────────────
price_history  = collections.defaultdict(lambda: collections.deque(maxlen=HISTORY_LEN))
selected_idx   = 0
chart_mode     = False
candle_mode    = False
current_regime = 0
status_msg     = ""
running        = True
latest_data    = None
prev_data      = None

# Rich colors for UI panels
TICKER_RICH_COLORS = [
    "bright_cyan", "bright_green", "bright_yellow", "bright_magenta",
    "bright_red",  "bright_blue",  "white",         "cyan",
    "green",       "yellow",       "magenta",       "red",
    "blue",        "bright_white", "bright_cyan",   "bright_green",
]

# ANSI escape codes for asciichartpy colored lines
TICKER_ANSI_COLORS = [
    "\033[96m",   # bright cyan   — AAPL
    "\033[92m",   # bright green  — MSFT
    "\033[93m",   # bright yellow — GOOG
    "\033[95m",   # bright magenta— META
    "\033[91m",   # bright red    — NVDA
    "\033[94m",   # bright blue   — AMD
    "\033[97m",   # bright white  — INTC
    "\033[36m",   # cyan          — AVGO
    "\033[32m",   # green         — AMZN
    "\033[33m",   # yellow        — TSLA
    "\033[35m",   # magenta       — JPM
    "\033[31m",   # red           — GS
    "\033[34m",   # blue          — JNJ
    "\033[37m",   # white         — PFE
    "\033[96m",   # bright cyan   — XOM
    "\033[92m",   # bright green  — CVX
]

def ticker_rich_color(ticker):
    tickers = list(SECTORS.keys())
    idx = tickers.index(ticker) if ticker in tickers else 0
    return TICKER_RICH_COLORS[idx % len(TICKER_RICH_COLORS)]

def ticker_ansi_color(ticker):
    tickers = list(SECTORS.keys())
    idx = tickers.index(ticker) if ticker in tickers else 0
    return TICKER_ANSI_COLORS[idx % len(TICKER_ANSI_COLORS)]


def fetch(ip, port):
    try:
        return requests.get(f"http://{ip}:{port}/prices", timeout=1.0).json()
    except Exception:
        return None


def set_regime(ip, port, val):
    try:
        requests.post(f"http://{ip}:{port}/set_regime",
                      json={"regime": val}, timeout=1.0)
        return True
    except Exception:
        return False


def sparkline(values, width=20):
    if len(values) < 2:
        return " " * width
    mn, mx = min(values), max(values)
    rng = mx - mn or 1e-9
    bars = "▁▂▃▄▅▆▇█"
    vals = list(values)[-width:]
    line = "".join(bars[int((v - mn) / rng * (len(bars) - 1))] for v in vals)
    return " " * (width - len(line)) + line


def chart_string(ticker, values, width=70, height=16):
    """Draw a colored connected line chart using asciichartpy."""
    if len(values) < 2:
        return "Not enough data yet — waiting for price history..."
    try:
        import asciichartpy as acp
        vals  = list(values)[-width:]
        ansi  = ticker_ansi_color(ticker)
        chart = acp.plot(vals, {
            "height": height,
            "format": "{:8.3f}",
            "colors": [ansi],
        })
        return chart
    except ImportError:
        return "Install asciichartpy: pip install asciichartpy"


def candlestick_chart(ticker, values, candle_size=8, width=70, height=20):
    """
    Draw an ASCII candlestick chart.
    Each candle covers `candle_size` price points.
    Green candle = close > open, Red candle = close < open.
    Candles are thin (1 char wide) with 2-char spacing between them.
    """
    if len(values) < candle_size * 2:
        return "Not enough data yet for candlestick — keep watching..."

    vals = list(values)

    # Build candles from price history
    candles = []
    for i in range(0, len(vals) - candle_size + 1, candle_size):
        window = vals[i:i + candle_size]
        o = window[0]
        c = window[-1]
        h = max(window)
        l = min(window)
        candles.append((o, h, l, c))

    # Each candle is candle_stride chars wide — limit to fit terminal
    candle_stride = 6
    max_candles   = min(len(candles), (width) // candle_stride)
    candles       = candles[-max_candles:]  # always show most recent

    if not candles:
        return "Not enough candles yet..."

    # Price range across all candles
    all_highs = [c[1] for c in candles]
    all_lows  = [c[2] for c in candles]
    price_min = min(all_lows)
    price_max = max(all_highs)
    price_rng = price_max - price_min or 0.001

    def price_to_row(p):
        # row 0 = top (price_max), row height-1 = bottom (price_min)
        return int((price_max - p) / price_rng * (height - 1))

    # ANSI colors
    GREEN  = "\033[92m"
    RED    = "\033[91m"
    RESET  = "\033[0m"

    # grid width based on capped candle count
    grid_w = len(candles) * candle_stride
    grid = [[" "] * grid_w for _ in range(height)]

    for ci, (o, h, l, c) in enumerate(candles):
        base  = ci * candle_stride
        wick  = base + 2   # center of candle
        left  = base + 1   # body left char
        mid   = base + 2   # body middle char
        right = base + 3   # body right char
        color = GREEN if c >= o else RED

        body_top = price_to_row(max(o, c))
        body_bot = price_to_row(min(o, c))
        wick_top = price_to_row(h)
        wick_bot = price_to_row(l)

        if body_bot < body_top:
            body_bot = body_top

        # Upper wick — center col only, only above body
        for r in range(wick_top, body_top):
            if 0 <= wick < grid_w:
                grid[r][wick] = color + "│" + RESET

        # Body — 3 chars wide, all filled
        for r in range(body_top, body_bot + 1):
            for col in (left, mid, right):
                if 0 <= col < grid_w:
                    grid[r][col] = color + "█" + RESET

        # Lower wick — center col only, only below body
        for r in range(body_bot + 1, wick_bot + 1):
            if 0 <= wick < grid_w:
                grid[r][wick] = color + "│" + RESET

    # Convert grid to strings — label every 4 rows like line plot
    lines = []
    for r, row in enumerate(grid):
        price_at_row = price_max - (r / (height - 1)) * price_rng
        if r % 4 == 0:
            label = f"{price_at_row:8.3f} ┤"
        else:
            label = "         │"
        lines.append(label + "".join(row))

    # Bottom axis
    axis_w = grid_w + 1
    lines.append("         └" + "─" * axis_w)
    lines.append(f"  {ticker}  {len(candles)} candles × {candle_size} pts each  "
                 f"Hi:{price_max:.3f}  Lo:{price_min:.3f}")
    return "\n".join(lines)


def build_candle_view(data):
    """Candlestick chart view — triggered by left/right in chart mode."""
    if data is None:
        return Panel("[red]No data[/red]")

    prices = data.get("prices", [])
    s      = data.get("stats", {})
    rv     = s.get("regime", 0)
    rc     = REGIME_COLORS.get(rv, "white")
    rn     = REGIME_NAMES.get(rv, "?")

    if selected_idx >= len(prices):
        return Panel("No symbol selected")

    p      = prices[selected_idx]
    ticker = p.get("ticker", f"SYM{selected_idx}")
    hist   = price_history[ticker]
    tc     = ticker_rich_color(ticker)

    bid    = p.get("bid", 0) / Q16
    ask    = p.get("ask", 0) / Q16
    mid    = (bid + ask) / 2

    hist_list = list(hist)
    chg = hist_list[-1] - hist_list[0] if len(hist_list) > 1 else 0
    chg_color = "bright_green" if chg >= 0 else "bright_red"
    chg_str   = f"▲{chg:.4f}" if chg >= 0 else f"▼{abs(chg):.4f}"

    chart = candlestick_chart(ticker, hist_list, candle_size=8, width=100, height=20)

    stats_line = (
        f"[bold {tc}]{ticker}[/bold {tc}]  "
        f"[dim]{SECTORS.get(ticker,'?')}[/dim]  "
        f"[bold white]${mid:.4f}[/bold white]  "
        f"[{chg_color}]{chg_str}[/{chg_color}]  "
        f"[dim]Pts: {len(hist_list)}[/dim]"
    )

    controls = (
        f"[{rc}]● {rn}[/{rc}]  "
        f"[bold]Regime:[/bold] "
        f"[green][0]CALM[/green]  "
        f"[yellow][1]VOLATILE[/yellow]  "
        f"[red][2]BURST[/red]  "
        f"[magenta][3]ADVERSARIAL[/magenta]  "
        f"[dim]←/→ line chart  ESC/ENTER back  ↑↓ prev/next  q quit[/dim]"
    )

    legend = "[bright_green]█ Bullish (close > open)[/bright_green]   [bright_red]█ Bearish (close < open)[/bright_red]"

    return Group(
        Panel(stats_line, title=f"[bold {tc}]{ticker} — Candlestick Chart[/bold {tc}]",
              border_style="cyan"),
        Panel(legend, border_style="dim", padding=(0,1)),
        Panel(Text.from_ansi(chart), border_style="dim"),
        Panel(controls, border_style="dim", padding=(0, 1)),
    )


def build_table_view(data, prev):
    if data is None:
        return Panel("[red]No connection[/red]", title="Error")

    prices      = data.get("prices", [])
    prev_prices = prev.get("prices", []) if prev else []
    s           = data.get("stats", {})
    rv          = s.get("regime", 0)
    rc          = REGIME_COLORS.get(rv, "white")
    rn          = REGIME_NAMES.get(rv, "?")

    t = Table(
        box=box.SIMPLE, border_style="cyan",
        header_style="bold white", show_edge=False, padding=(0, 1),
    )
    t.add_column("#",      width=3,  justify="right", style="dim")
    t.add_column("",       width=2)
    t.add_column("Ticker", width=5,  style="bold yellow")
    t.add_column("Sector", width=6,  style="dim")
    t.add_column("Mid",    width=9,  justify="right", style="bold white")
    t.add_column("Spread", width=7,  justify="right", style="dim")
    t.add_column("Chg",    width=8,  justify="right")
    t.add_column("Chart",  width=22, style="dim")

    for i, p in enumerate(prices):
        ticker  = p.get("ticker", f"SYM{i}")
        bid_q16 = p.get("bid", 0)
        ask_q16 = p.get("ask", 0)
        sel     = "▶" if i == selected_idx else " "

        if bid_q16 == 0 and ask_q16 == 0:
            t.add_row(str(i), sel, ticker, SECTORS.get(ticker,"?"),
                      "---","---","---","")
            continue

        bid    = bid_q16 / Q16
        ask    = ask_q16 / Q16
        mid    = (bid + ask) / 2
        spread = ask - bid

        chg_str   = "─"
        chg_color = "dim white"
        if i < len(prev_prices) and prev_prices[i].get("bid", 0) != 0:
            pm = (prev_prices[i]["bid"] + prev_prices[i]["ask"]) / 2 / Q16
            d  = mid - pm
            if d > 0.001:
                chg_str, chg_color = f"▲{d:.3f}", "bright_green"
            elif d < -0.001:
                chg_str, chg_color = f"▼{abs(d):.3f}", "bright_red"

        hist       = list(price_history[ticker])
        spark      = sparkline(price_history[ticker], width=20)
        net        = hist[-1] - hist[0] if len(hist) > 1 else 0
        spark_color = "bright_green" if net >= 0 else "bright_red"
        row_style  = "on grey11" if i == selected_idx else ""

        t.add_row(
            str(i), sel, ticker, SECTORS.get(ticker, "?"),
            f"${mid:.3f}", f"${spread:.4f}",
            f"[{chg_color}]{chg_str}[/{chg_color}]",
            f"[{spark_color}]{spark}[/{spark_color}]",
            style=row_style,
        )

    header = Text()
    header.append("⚡ Dual-FPGA Trading Engine", style="bold cyan")
    header.append("  ")
    header.append(f"● {rn}", style=rc)
    header.append(f"  {datetime.now().strftime('%H:%M:%S')}", style="dim")

    running_icon = "🟢" if s.get("running_a") else "🔴"
    link_icon    = "🔗" if s.get("link_up")   else "❌"

    controls = (
        f"{running_icon} Board A  {link_icon} Link  "
        f"[dim]Quotes:{s.get('quotes_sent',0):,}  "
        f"Orders:{s.get('orders_sent',0):,}[/dim]\n"
        f"[bold]Regime:[/bold] "
        f"[green][0]CALM[/green]  "
        f"[yellow][1]VOLATILE[/yellow]  "
        f"[red][2]BURST[/red]  "
        f"[magenta][3]ADVERSARIAL[/magenta]  "
        f"[dim]↑↓ navigate  ENTER chart  q quit[/dim]"
        + (f"  [cyan]{status_msg}[/cyan]" if status_msg else "")
    )

    return Group(
        Panel(header, border_style="cyan", padding=(0, 1)),
        t,
        Panel(controls, border_style="dim", padding=(0, 1)),
    )


def build_chart_view(data):
    if data is None:
        return Panel("[red]No data[/red]")

    prices = data.get("prices", [])
    s      = data.get("stats", {})
    rv     = s.get("regime", 0)
    rc     = REGIME_COLORS.get(rv, "white")
    rn     = REGIME_NAMES.get(rv, "?")

    if selected_idx >= len(prices):
        return Panel("No symbol selected")

    p      = prices[selected_idx]
    ticker = p.get("ticker", f"SYM{selected_idx}")
    hist   = price_history[ticker]
    tc     = ticker_rich_color(ticker)

    bid    = p.get("bid", 0) / Q16
    ask    = p.get("ask", 0) / Q16
    mid    = (bid + ask) / 2
    spread = ask - bid

    hist_list = list(hist)
    if hist_list:
        hi  = max(hist_list)
        lo  = min(hist_list)
        chg = hist_list[-1] - hist_list[0] if len(hist_list) > 1 else 0
        chg_color = "bright_green" if chg >= 0 else "bright_red"
        chg_str   = f"▲{chg:.4f}" if chg >= 0 else f"▼{abs(chg):.4f}"
    else:
        hi = lo = mid
        chg_str, chg_color = "─", "dim"

    chart = chart_string(ticker, hist, width=70, height=16)

    stats_line = (
        f"[bold {tc}]{ticker}[/bold {tc}]  "
        f"[dim]{SECTORS.get(ticker,'?')}[/dim]  "
        f"[bold white]${mid:.4f}[/bold white]  "
        f"[{chg_color}]{chg_str}[/{chg_color}]\n"
        f"[dim]Bid:[/dim] ${bid:.4f}  "
        f"[dim]Ask:[/dim] ${ask:.4f}  "
        f"[dim]Spread:[/dim] ${spread:.4f}  "
        f"[dim]Hi:[/dim] ${hi:.4f}  "
        f"[dim]Lo:[/dim] ${lo:.4f}  "
        f"[dim]Pts:[/dim] {len(hist_list)}"
    )

    controls = (
        f"[{rc}]● {rn}[/{rc}]  "
        f"[bold]Regime:[/bold] "
        f"[green][0]CALM[/green]  "
        f"[yellow][1]VOLATILE[/yellow]  "
        f"[red][2]BURST[/red]  "
        f"[magenta][3]ADVERSARIAL[/magenta]  "
        f"[dim]ESC/ENTER back  ↑↓ prev/next  q quit[/dim]"
    )

    return Group(
        Panel(stats_line, title=f"[bold {tc}]{ticker} — Price Chart[/bold {tc}]",
              border_style="cyan"),
        Panel(Text.from_ansi(chart), border_style="dim"),
        Panel(controls, border_style="dim", padding=(0, 1)),
    )


def input_thread(ip, port):
    global selected_idx, chart_mode, candle_mode, current_regime, status_msg, running

    num_symbols = 16

    if os.name == "nt":
        import msvcrt
        while running:
            if msvcrt.kbhit():
                key = msvcrt.getwch()
                if key == 'q':
                    running = False
                elif key in '0123':
                    val = int(key)
                    if set_regime(ip, port, val):
                        current_regime = val
                        status_msg = f"Regime → {REGIME_NAMES[val]}"
                elif key == '\r':
                    chart_mode = not chart_mode
                elif key == '\x1b':
                    chart_mode = False
                elif key == '\x00' or key == '\xe0':
                    key2 = msvcrt.getwch()
                    if key2 == 'H':
                        selected_idx = (selected_idx - 1) % num_symbols
                        status_msg = ""
                    elif key2 == 'P':
                        selected_idx = (selected_idx + 1) % num_symbols
                        status_msg = ""
                    elif key2 in ('K', 'M'):  # left or right arrow
                        if chart_mode:
                            candle_mode = not candle_mode
            time.sleep(0.05)
    else:
        import tty, termios
        fd  = sys.stdin.fileno()
        old = termios.tcgetattr(fd)
        try:
            tty.setraw(fd)
            while running:
                ch = sys.stdin.read(1)
                if ch == 'q':
                    running = False
                elif ch in '0123':
                    val = int(ch)
                    if set_regime(ip, port, val):
                        current_regime = val
                        status_msg = f"Regime → {REGIME_NAMES[val]}"
                elif ch in ('\r', '\n'):
                    chart_mode = not chart_mode
                    if not chart_mode:
                        candle_mode = False
                elif ch == '\x1b':
                    nxt = sys.stdin.read(1)
                    if nxt == '[':
                        arrow = sys.stdin.read(1)
                        if arrow == 'A':
                            selected_idx = (selected_idx - 1) % num_symbols
                            chart_mode = False
                            candle_mode = False
                            status_msg = ""
                        elif arrow == 'B':
                            selected_idx = (selected_idx + 1) % num_symbols
                            chart_mode = False
                            candle_mode = False
                            status_msg = ""
                        elif arrow in ('C', 'D'):  # right or left
                            if chart_mode:
                                candle_mode = not candle_mode
                    else:
                        chart_mode = False
                        candle_mode = False
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old)


def main():
    global running, latest_data, prev_data

    parser = argparse.ArgumentParser()
    parser.add_argument("--ip",       default="192.168.2.99")
    parser.add_argument("--port",     default=8080, type=int)
    parser.add_argument("--interval", default=0.25, type=float)
    args = parser.parse_args()

    console.print(f"[cyan]Connecting to {args.ip}:{args.port}...[/cyan]")
    time.sleep(0.3)

    t = threading.Thread(target=input_thread, args=(args.ip, args.port), daemon=True)
    t.start()

    with Live(console=console, refresh_per_second=int(1/args.interval),
              screen=True) as live:
        while running:
            data = fetch(args.ip, args.port)
            if data:
                prev_data   = latest_data
                latest_data = data
                for p in data.get("prices", []):
                    ticker  = p.get("ticker")
                    bid_q16 = p.get("bid", 0)
                    ask_q16 = p.get("ask", 0)
                    if ticker and bid_q16 > 0 and ask_q16 > 0:
                        price_history[ticker].append(
                            (bid_q16 + ask_q16) / 2 / Q16
                        )

            if candle_mode and chart_mode:
                live.update(build_candle_view(latest_data))
            elif chart_mode:
                live.update(build_chart_view(latest_data))
            else:
                live.update(build_table_view(latest_data, prev_data))

            time.sleep(args.interval)

    console.print("\n[yellow]Stopped.[/yellow]")


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        console.print("\n[yellow]Stopped.[/yellow]")