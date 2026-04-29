"""
YOU UPLOAD THIS TO THE PYNQ BOARD AND RUN IT THERE
pynq_server.py — Runs ON the PYNQ board.
Reads Board A AXI registers and serves price data over HTTP.
Also accepts regime change commands from live_prices.py.

Upload to PYNQ and run:
    python pynq_server.py --bitfile-a overlays/board_a.bit

Demo mode (no hardware):
    python pynq_server.py --demo
"""

import json
import time
import argparse
from http.server import HTTPServer, BaseHTTPRequestHandler
from threading import Thread

try:
    from pynq import Overlay, MMIO
    PYNQ_AVAILABLE = True
except ImportError:
    PYNQ_AVAILABLE = False

# ── Board A AXI register offsets ────────────────────────────────
CTRL             = 0x00
REGIME_REG       = 0x0C
INIT_MID_BASE    = 0x10
INIT_SPREAD_BASE = 0x50
ACTIVE_SYM_COUNT = 0xF0
STATUS_REG       = 0xF4
QUOTES_SENT      = 0xF8
ORDERS_RCVD      = 0xFC

NUM_SYMBOLS = 16
Q16 = 65536.0

SYMBOLS = [
    ("AAPL", 180.00, 0.10), ("MSFT", 420.00, 0.15),
    ("GOOG", 175.00, 0.12), ("META", 510.00, 0.20),
    ("NVDA", 900.00, 0.25), ("AMD",  160.00, 0.08),
    ("INTC",  31.00, 0.05), ("AVGO", 170.00, 0.18),
    ("AMZN", 185.00, 0.10), ("TSLA", 250.00, 0.30),
    ("JPM",  200.00, 0.08), ("GS",   470.00, 0.22),
    ("JNJ",  155.00, 0.06), ("PFE",   27.00, 0.04),
    ("XOM",  105.00, 0.07), ("CVX",  155.00, 0.09),
]

latest_data = {
    "prices": [{"ticker": s[0], "bid": int(s[1]*Q16), "ask": int((s[1]+s[2])*Q16), "regime": 0}
               for s in SYMBOLS],
    "stats":  {"quotes_sent": 0, "orders_sent": 0, "fills_rcvd": 0,
                "regime": 0, "running_a": False, "link_up": False}
}

mmio_a = None
demo_mode = False


def init_hardware(bitfile_a):
    global mmio_a
    try:
        ol = Overlay(bitfile_a)
        base = ol.ip_dict['hft_core']['phys_addr']
        rng  = ol.ip_dict['hft_core']['addr_range']
        mmio_a = MMIO(base, rng)
        print(f"Board A loaded: {bitfile_a}")
        return True
    except Exception as e:
        print(f"Board A load failed: {e}")
        return False


def set_regime_hw(val):
    """Write regime to hardware."""
    if mmio_a is not None:
        mmio_a.write(REGIME_REG, int(val) & 0x3)
        return True
    return False


def poll_registers():
    global latest_data
    import math, random
    tick = 0

    while True:
        tick += 1
        try:
            if not demo_mode and mmio_a is not None:
                status     = mmio_a.read(STATUS_REG)
                running_a  = bool(status & 0x01)
                link_up    = bool(status & 0x02)
                regime_val = mmio_a.read(REGIME_REG) & 0x3
                quotes     = mmio_a.read(QUOTES_SENT)
                num_sym    = mmio_a.read(ACTIVE_SYM_COUNT)

                prices = []
                for i in range(NUM_SYMBOLS):
                    mid_q16 = mmio_a.read(INIT_MID_BASE    + 4*i)
                    spr_q16 = mmio_a.read(INIT_SPREAD_BASE + 4*i)
                    noise_scale = {0: 0.0005, 1: 0.002, 2: 0.008, 3: 0.003}
                    spread_mult = {0: 1.0,    1: 2.5,   2: 5.0,   3: 3.0}
                    amp        = noise_scale.get(regime_val, 0.001)
                    mult       = spread_mult.get(regime_val, 1.0)
                    t          = time.time()
                    drift      = math.sin(t * 0.3 + i * 0.7) * mid_q16 * amp * 3
                    noise      = random.gauss(0, mid_q16 * amp)
                    mid        = int(mid_q16 + drift + noise)
                    scaled_spr = int(spr_q16 * mult)
                    bid        = max(0, mid - scaled_spr // 2)
                    ask        = max(0, mid + scaled_spr // 2)
                    prices.append({
                        "ticker": SYMBOLS[i][0] if i < len(SYMBOLS) else f"SYM{i}",
                        "bid": bid, "ask": ask, "regime": regime_val
                    })

                latest_data = {
                    "prices": prices,
                    "stats": {
                        "quotes_sent": quotes,
                        "orders_sent": 0,
                        "fills_rcvd":  0,
                        "regime":      regime_val,
                        "running_a":   running_a,
                        "link_up":     link_up,
                    }
                }
            else:
                # Demo mode
                regime_val  = latest_data["stats"]["regime"]
                noise_scale = {0: 0.0005, 1: 0.003, 2: 0.01,  3: 0.004}
                spread_mult = {0: 1.0,    1: 2.5,   2: 5.0,   3: 3.0}
                amp  = noise_scale.get(regime_val, 0.001)
                mult = spread_mult.get(regime_val, 1.0)
                prices = []
                for i, (ticker, init_p, spread) in enumerate(SYMBOLS):
                    t          = time.time()
                    drift      = math.sin(t * 0.3 + i * 0.7) * init_p * amp * 3
                    noise      = random.gauss(0, init_p * amp)
                    mid        = init_p + drift + noise
                    scaled_spr = spread * mult
                    prices.append({
                        "ticker": ticker,
                        "bid": int((mid - scaled_spr/2) * Q16),
                        "ask": int((mid + scaled_spr/2) * Q16),
                        "regime": regime_val,
                    })
                latest_data = {
                    "prices": prices,
                    "stats": {
                        "quotes_sent": tick * 1000,
                        "orders_sent": tick // 10,
                        "fills_rcvd":  tick // 12,
                        "regime":      regime_val,
                        "running_a":   True,
                        "link_up":     True,
                    }
                }
        except Exception as e:
            print(f"Poll error: {e}")

        time.sleep(0.05)


class Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == "/prices":
            body = json.dumps(latest_data).encode()
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.send_header("Content-Length", len(body))
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(body)
        else:
            self.send_response(404)
            self.end_headers()

    def do_POST(self):
        if self.path == "/set_regime":
            length = int(self.headers.get("Content-Length", 0))
            body   = self.rfile.read(length)
            try:
                data = json.loads(body)
                val  = int(data.get("regime", 0)) & 0x3
                # Write to hardware or update demo state
                if not demo_mode:
                    set_regime_hw(val)
                latest_data["stats"]["regime"] = val
                self.send_response(200)
                self.send_header("Content-Type", "application/json")
                self.end_headers()
                self.wfile.write(json.dumps({"ok": True, "regime": val}).encode())
                print(f"Regime → {val}")
            except Exception as e:
                self.send_response(400)
                self.end_headers()
        else:
            self.send_response(404)
            self.end_headers()

    def log_message(self, fmt, *args):
        pass


def main():
    global demo_mode
    parser = argparse.ArgumentParser()
    parser.add_argument("--bitfile-a", default="overlays/board_a.bit")
    parser.add_argument("--port",      default=8080, type=int)
    parser.add_argument("--demo",      action="store_true")
    args = parser.parse_args()

    demo_mode = args.demo or not PYNQ_AVAILABLE
    if not demo_mode:
        init_hardware(args.bitfile_a)
    else:
        print("Demo mode — simulated prices")

    Thread(target=poll_registers, daemon=True).start()
    print(f"Server on port {args.port} — on laptop: python live_prices.py --ip <pynq_ip>")
    try:
        HTTPServer(("0.0.0.0", args.port), Handler).serve_forever()
    except KeyboardInterrupt:
        print("Stopped.")


if __name__ == "__main__":
    main()