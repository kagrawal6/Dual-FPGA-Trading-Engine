"""
RUN THIS IN YOU OWN TERMINAL FOR IP
live_prices.py — Interactive terminal display for Dual-FPGA Trading Engine.
Runs on your LAPTOP. Connects to pynq_server.py on the PYNQ board.

Controls:
    0  →  CALM regime
    1  →  VOLATILE regime
    2  →  BURST regime
    3  →  ADVERSARIAL regime
    q  →  Quit

Install:  pip install requests rich windows-curses
Run:      python live_prices.py --ip 192.168.3.1
"""

import argparse
import time
import threading
import requests
from rich.console import Console
from rich.table import Table
from rich.live import Live
from rich.panel import Panel
from rich.text import Text
from rich import box
from datetime import datetime

console = Console()

Q16 = 65536.0

REGIME_NAMES  = {0: "CALM", 1: "VOLATILE", 2: "BURST", 3: "ADVERSARIAL"}
REGIME_COLORS = {0: "green", 1: "yellow", 2: "red", 3: "bold magenta"}

SECTORS = {
    "AAPL": "Tech",    "MSFT": "Tech",    "GOOG": "Tech",    "META": "Tech",
    "NVDA": "Semicon", "AMD":  "Semicon", "INTC": "Semicon", "AVGO": "Semicon",
    "AMZN": "Cons",    "TSLA": "Cons",
    "JPM":  "Finance", "GS":   "Finance",
    "JNJ":  "Health",  "PFE":  "Health",
    "XOM":  "Energy",  "CVX":  "Energy",
}

# Shared state
current_regime = 0
status_msg     = "Press 0=CALM  1=VOLATILE  2=BURST  3=ADVERSARIAL  q=quit"
running        = True


def fetch(ip, port):
    try:
        return requests.get(f"http://{ip}:{port}/prices", timeout=1.0).json()
    except Exception:
        return None


def set_regime(ip, port, regime_val):
    try:
        requests.post(f"http://{ip}:{port}/set_regime",
                      json={"regime": regime_val}, timeout=1.0)
        return True
    except Exception:
        return False


def build_display(data, prev, ip, port):
    if data is None:
        return Panel(
            f"[red]Cannot reach {ip}:{port}[/red]\n[dim]Is pynq_server.py running?[/dim]",
            title="[red]Connection Error[/red]"
        )

    prices     = data.get("prices", [])
    prev_prices = prev.get("prices", []) if prev else []
    s          = data.get("stats", {})
    rv         = s.get("regime", 0)
    rc         = REGIME_COLORS.get(rv, "white")
    rn         = REGIME_NAMES.get(rv, "?")

    # Price table
    t = Table(
        title=(
            f"[bold cyan]⚡ Dual-FPGA Trading Engine[/bold cyan]  "
            f"[{rc}]● {rn}[/{rc}]  "
            f"[dim]{datetime.now().strftime('%H:%M:%S.%f')[:-3]}[/dim]"
        ),
        box=box.ROUNDED,
        border_style="cyan",
        header_style="bold white on navy_blue",
    )

    t.add_column("#",      width=3,  justify="right", style="dim")
    t.add_column("Ticker", width=6,  style="bold yellow")
    t.add_column("Sector", width=8,  style="dim white")
    t.add_column("Bid",    width=10, justify="right")
    t.add_column("Ask",    width=10, justify="right")
    t.add_column("Mid",    width=10, justify="right", style="bold white")
    t.add_column("Spread", width=8,  justify="right", style="dim")
    t.add_column("Chg",    width=9,  justify="right")

    for i, p in enumerate(prices):
        ticker  = p.get("ticker", f"SYM{i}")
        bid_q16 = p.get("bid", 0)
        ask_q16 = p.get("ask", 0)

        if bid_q16 == 0 and ask_q16 == 0:
            t.add_row(str(i), ticker, SECTORS.get(ticker, "?"),
                      "---", "---", "---", "---", "---")
            continue

        bid    = bid_q16 / Q16
        ask    = ask_q16 / Q16
        mid    = (bid + ask) / 2
        spread = ask - bid

        chg_str   = "─"
        chg_color = "dim white"
        if i < len(prev_prices) and prev_prices[i].get("bid", 0) != 0:
            prev_mid = (prev_prices[i]["bid"] + prev_prices[i]["ask"]) / 2 / Q16
            delta    = mid - prev_mid
            if delta > 0.001:
                chg_str   = f"▲{delta:.3f}"
                chg_color = "bright_green"
            elif delta < -0.001:
                chg_str   = f"▼{abs(delta):.3f}"
                chg_color = "bright_red"

        t.add_row(
            str(i), ticker, SECTORS.get(ticker, "?"),
            f"[cyan]${bid:.3f}[/cyan]",
            f"[cyan]${ask:.3f}[/cyan]",
            f"${mid:.3f}",
            f"[dim]${spread:.4f}[/dim]",
            f"[{chg_color}]{chg_str}[/{chg_color}]",
        )

    # Stats + controls panel
    running_icon = "🟢" if s.get("running_a") else "🔴"
    link_icon    = "🔗" if s.get("link_up")   else "❌"

    controls = (
        f"{running_icon} Board A  {link_icon} Link  "
        f"[{rc}]● {rn}[/{rc}]  "
        f"[dim]Quotes: {s.get('quotes_sent',0):,}  "
        f"Orders: {s.get('orders_sent',0):,}  "
        f"Fills: {s.get('fills_rcvd',0):,}[/dim]\n"
        f"[bold]Controls:[/bold] "
        f"[green][0] CALM[/green]  "
        f"[yellow][1] VOLATILE[/yellow]  "
        f"[red][2] BURST[/red]  "
        f"[magenta][3] ADVERSARIAL[/magenta]  "
        f"[white][q] Quit[/white]  "
        f"[dim]{status_msg}[/dim]"
    )

    from rich.console import Group
    return Group(t, Panel(controls, border_style="cyan", padding=(0, 1)))


def input_thread(ip, port):
    """Read keypresses and send regime changes to server."""
    global current_regime, status_msg, running
    import sys
    import os

    # Use different input method based on OS
    if os.name == "nt":  # Windows
        import msvcrt
        while running:
            if msvcrt.kbhit():
                key = msvcrt.getwch()
                if key == "q":
                    running = False
                elif key in "0123":
                    val = int(key)
                    if set_regime(ip, port, val):
                        current_regime = val
                        status_msg = f"✅ Regime changed to {REGIME_NAMES[val]}"
                    else:
                        status_msg = "❌ Failed to set regime"
            time.sleep(0.05)
    else:  # Linux/Mac
        import tty
        import termios
        fd = sys.stdin.fileno()
        old = termios.tcgetattr(fd)
        try:
            tty.setraw(fd)
            while running:
                ch = sys.stdin.read(1)
                if ch == "q":
                    running = False
                elif ch in "0123":
                    val = int(ch)
                    if set_regime(ip, port, val):
                        current_regime = val
                        status_msg = f"✅ Regime → {REGIME_NAMES[val]}"
                    else:
                        status_msg = "❌ Failed to set regime"
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old)


def main():
    global running, status_msg
    parser = argparse.ArgumentParser()
    parser.add_argument("--ip",       default="192.168.2.99")
    parser.add_argument("--port",     default=8080, type=int)
    parser.add_argument("--interval", default=0.15, type=float)
    args = parser.parse_args()

    console.print(f"[cyan]Connecting to {args.ip}:{args.port}...[/cyan]")
    console.print("[dim]Controls: 0=CALM  1=VOLATILE  2=BURST  3=ADVERSARIAL  q=quit[/dim]")
    time.sleep(0.5)

    # Start input thread
    t = threading.Thread(target=input_thread, args=(args.ip, args.port), daemon=True)
    t.start()

    prev = None
    with Live(console=console, refresh_per_second=int(1/args.interval),
              screen=True) as live:
        while running:
            data = fetch(args.ip, args.port)
            live.update(build_display(data, prev, args.ip, args.port))
            if data:
                prev = data
            time.sleep(args.interval)

    console.print("\n[yellow]Stopped.[/yellow]")


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        console.print("\n[yellow]Stopped.[/yellow]")