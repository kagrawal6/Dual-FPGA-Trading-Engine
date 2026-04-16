#!/usr/bin/env python3
"""
Board B PS Script — telemetry_server.py
Configures the trader pipeline, then enters a 20 Hz telemetry loop
that reads all status registers and prints JSON lines to stdout.
Stdout is routed through UART → FTDI → USB to the laptop dashboard.
See §5.1.2 of design spec.
"""

import argparse
import json
import time
from pynq import Overlay, MMIO
from register_map import *

FSM_NAMES = {0: "B_RESET", 1: "B_IDLE", 2: "B_ARMED", 3: "B_TRADING", 4: "B_HALTED"}
STRATEGY_NAMES = {0: "MEAN_REV", 1: "MOMENTUM", 2: "NN", 3: "AUTO"}


def decode_status(raw: int) -> dict:
    """Decode the packed STATUS register into named fields."""
    return {
        "strategy":   STRATEGY_NAMES.get(raw & 0x03, "?"),
        "fsm_state":  FSM_NAMES.get((raw >> 2) & 0x07, "?"),
        "link_up":    bool((raw >> 5) & 1),
        "risk_halt":  bool((raw >> 6) & 1),
    }


def print_status(mmio: MMIO) -> None:
    """Read and display all Board B status registers."""
    st = decode_status(mmio.read(STATUS))
    print(f"  fsm_state   : {st['fsm_state']}")
    print(f"  link_up     : {st['link_up']}")
    print(f"  risk_halt   : {st['risk_halt']}")
    print(f"  strategy    : {st['strategy']}")
    print(f"  quotes_rcvd : {mmio.read(QUOTES_RCVD)}")
    print(f"  orders_sent : {mmio.read(ORDERS_SENT)}")
    print(f"  fills_rcvd  : {mmio.read(FILLS_RCVD)}")
    print(f"  risk_rejects: {mmio.read(RISK_REJECTS)}")
    print(f"  link_errors : {mmio.read(LINK_ERRORS)}")
    cash_lo = mmio.read(CASH_LO)
    cash_hi = signed32(mmio.read(CASH_HI))
    cash_q32_16 = (cash_hi << 32) | cash_lo
    print(f"  cash (Q32.16): 0x{cash_q32_16 & 0xFFFFFFFFFFFF:012X}  (${cash_q32_16 / 65536:.2f})")
    for i in range(min(4, NUM_SYMBOLS)):
        pos = signed32(mmio.read(POS_BASE + i * 4))
        print(f"  pos[{i}]      : {pos}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Configure Board B trader and run telemetry loop."
    )
    parser.add_argument("--status", action="store_true",
                        help="Read and print status registers, then exit.")
    parser.add_argument("--reset", action="store_true",
                        help="Pulse CTRL[1] (reset FSM) before configuring.")
    parser.add_argument("--no-start", action="store_true",
                        help="Write config but do not pulse CTRL[0] (start).")
    parser.add_argument("--no-telemetry", action="store_true",
                        help="Configure and start, but skip the telemetry loop.")

    parser.add_argument("--strategy", type=int, default=0, choices=[0, 1, 2, 3],
                        help="Strategy: 0=MEAN_REV, 1=MOMENTUM, 2=NN, 3=AUTO (default: 0).")
    parser.add_argument("--threshold", type=float, default=1.00,
                        help="Deviation threshold in dollars (Q16.16). Default: $1.00.")
    parser.add_argument("--ema-alpha", type=int, default=6554,
                        help="EMA smoothing factor (Q0.16, ~0.1 = 6554). Default: 6554.")
    parser.add_argument("--base-qty", type=int, default=100,
                        help="Shares per order. Default: 100.")
    parser.add_argument("--max-position", type=int, default=500,
                        help="Per-symbol absolute position limit. Default: 500.")
    parser.add_argument("--max-order-rate", type=int, default=1000,
                        help="Total order count cap. Default: 1000.")
    parser.add_argument("--max-loss", type=int, default=100,
                        help="Max loss in integer dollars (total_pnl threshold). Default: $100.")

    parser.add_argument("--poll-hz", type=float, default=20.0,
                        help="Telemetry polling rate in Hz. Default: 20.")
    parser.add_argument("--overlay", type=str, default="overlays/board_b.bit",
                        help="Path to the Board B overlay bitstream.")
    parser.add_argument("--ip-block", type=str, default="hft_core",
                        help="IP block name in the overlay for MMIO.")

    return parser.parse_args()


def main():
    args = parse_args()

    ol = Overlay(args.overlay)
    mmio = MMIO(ol.ip_dict[args.ip_block]['phys_addr'],
                ol.ip_dict[args.ip_block]['addr_range'])

    if args.status:
        print("Board B status:")
        print_status(mmio)
        return

    if args.reset:
        print("Resetting Board B FSM (CTRL[1] pulse)...")
        mmio.write(CTRL, 0x02)

    # Configure
    mmio.write(STRATEGY_SEL,   args.strategy)
    mmio.write(THRESHOLD,      q16_16(args.threshold))
    mmio.write(EMA_ALPHA,      args.ema_alpha)
    mmio.write(BASE_QTY,       args.base_qty)
    mmio.write(MAX_POSITION,   args.max_position)
    mmio.write(MAX_ORDER_RATE, args.max_order_rate)
    mmio.write(MAX_LOSS,       args.max_loss)

    print(f"Config: strategy={STRATEGY_NAMES[args.strategy]}, threshold=${args.threshold:.2f}, "
          f"ema_alpha={args.ema_alpha}, base_qty={args.base_qty}, "
          f"max_pos={args.max_position}, max_rate={args.max_order_rate}, "
          f"max_loss=${args.max_loss}")

    if not args.no_start:
        mmio.write(CTRL, 0x01)
        print("Board B started.")
    else:
        print("Config written (start not pulsed).")

    print("\nPost-config status:")
    print_status(mmio)

    if args.no_telemetry or args.no_start:
        return

    # Telemetry loop
    interval = 1.0 / max(args.poll_hz, 0.1)
    print(f"\nEntering telemetry loop ({args.poll_hz:.0f} Hz). Ctrl+C to stop.", flush=True)

    try:
        while True:
            st = decode_status(mmio.read(STATUS))
            data = {
                "ts":        round(time.time(), 3),
                "state":     st["fsm_state"],
                "link_up":   st["link_up"],
                "risk_halt": st["risk_halt"],
                "strategy":  st["strategy"],
                "qps":       mmio.read(QUOTES_RCVD),
                "ops":       mmio.read(ORDERS_SENT),
                "fps":       mmio.read(FILLS_RCVD),
                "rej":       mmio.read(RISK_REJECTS),
                "pos":       [signed32(mmio.read(POS_BASE + i * 4))
                              for i in range(NUM_SYMBOLS)],
                "cash_lo":   mmio.read(CASH_LO),
                "cash_hi":   mmio.read(CASH_HI),
                "hist":      [mmio.read(HIST_BASE + i * 4)
                              for i in range(NUM_HIST_BINS)],
                "lat_min":   mmio.read(LAT_MIN),
                "lat_max":   mmio.read(LAT_MAX),
                "lat_sum":   mmio.read(LAT_SUM),
                "lat_cnt":   mmio.read(LAT_COUNT),
                "link_err":  mmio.read(LINK_ERRORS),
            }
            print(json.dumps(data), flush=True)
            time.sleep(interval)
    except KeyboardInterrupt:
        print("\nTelemetry stopped.", flush=True)


if __name__ == "__main__":
    main()
