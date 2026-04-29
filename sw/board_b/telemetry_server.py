#!/usr/bin/env python3
"""
Board B PS Script — telemetry_server.py
Configures the trader pipeline, then enters a 20 Hz telemetry loop
that reads all status registers (including per-symbol BBO and per-symbol
P&L arrays) and prints JSON lines to stdout.
Stdout is routed through UART → FTDI → USB to the laptop dashboard.

JSON schema (per line):
{
  "ts":         <unix epoch sec>,
  "state":      "B_TRADING" | ...,
  "link_up":    bool,
  "risk_halt":  bool,
  "strategy":   "MEAN_REV" | ...,
  "qps":        <quotes_rcvd cumulative>,
  "ops":        <orders_sent cumulative>,
  "fps":        <fills_rcvd cumulative>,
  "rej":        <risk_rejects cumulative>,
  "link_err":   <link_errors cumulative>,

  "cash_lo":    int,           # raw CASH_LO register (for laptop dashboard)
  "cash_hi":    int,           # raw CASH_HI register
  "cash":       <total cash float, dollars>,
  "total_pnl":  <total mark-to-market PnL float, dollars>,
  "port_value": <cash + Σ position[i]*mid[i], float dollars>,

  "pos":        [int, ...]      # signed position per symbol (NUM_SYMBOLS)
  "bid":        [float, ...]    # Board B's view of best bid per symbol
  "ask":        [float, ...]    # Board B's view of best ask per symbol
  "mid":        [float, ...]    # (bid+ask)/2
  "spread":     [float, ...]
  "pnl_cash":   [float, ...]    # per-symbol cash flow accumulator (Q32.16 → float)
  "pnl_mtm":    [float, ...]    # per-symbol mark-to-market PnL = pnl_cash + pos*mid
  "pos_value":  [float, ...]    # per-symbol position value = pos*mid
  "last_fill":  [float, ...]    # last execution price per symbol
  "trades":     [int, ...]      # per-symbol fill count

  "hist":       [int, ...]      # 16 latency bins
  "lat_min":    int,
  "lat_max":    int,
  "lat_sum":    int,
  "lat_cnt":    int,

  # Optional (dashboard): regime id/name and/or monotonic regime_changes — add
  # in PS or a wrapper if you have them; not emitted by this script by default.
  "regime":         int,        # optional, 0..3
  "regime_name":    str,        # optional, e.g. CALM / VOLATILE / ...
  "regime_changes": int         # optional edge counter; dashboard prefers this when present
}

See §5.1.2 of design spec.
"""

import argparse
import json
import time
from pynq import Overlay, MMIO
from register_map import (
    CTRL, STRATEGY_SEL, THRESHOLD, EMA_ALPHA, BASE_QTY,
    MAX_POSITION, MAX_ORDER_RATE, MAX_LOSS,
    STATUS, QUOTES_RCVD, ORDERS_SENT, FILLS_RCVD, RISK_REJECTS, LINK_ERRORS,
    POS_BASE, CASH_LO, CASH_HI,
    HIST_BASE, LAT_MIN, LAT_MAX, LAT_SUM, LAT_COUNT,
    BID_BASE, ASK_BASE,
    PNL_CASH_LO_BASE, PNL_CASH_HI_BASE,
    LAST_FILL_BASE, TRADES_PACK_BASE,
    NUM_SYMBOLS, NUM_HIST_BINS,
    q16_16, from_q16_16, signed32, cash_q32_16, read_trades_pack,
)

FSM_NAMES = {0: "B_RESET", 1: "B_IDLE", 2: "B_ARMED", 3: "B_TRADING", 4: "B_HALTED"}
STRATEGY_NAMES = {0: "MEAN_REV", 1: "MOMENTUM", 2: "NN", 3: "AUTO"}
# Optional JSON fields for the laptop dashboard (no RTL required): add
# "regime", "regime_name", and/or monotonic "regime_changes" to each line from
# any source you have (e.g. PS-side decode, wrapper script). The dashboard
# infers regime edges from successive regime / regime_name when regime_changes
# is absent.


def decode_status(raw: int) -> dict:
    """Decode the packed STATUS register into named fields."""
    return {
        "strategy":   STRATEGY_NAMES.get(raw & 0x03, "?"),
        "fsm_state":  FSM_NAMES.get((raw >> 2) & 0x07, "?"),
        "link_up":    bool((raw >> 5) & 1),
        "risk_halt":  bool((raw >> 6) & 1),
    }


def read_per_symbol(mmio: MMIO) -> dict:
    """Read all per-symbol arrays in one pass and compute derived dashboards."""
    pos       = [signed32(mmio.read(POS_BASE + i * 4))      for i in range(NUM_SYMBOLS)]
    bid       = [from_q16_16(mmio.read(BID_BASE + i * 4))   for i in range(NUM_SYMBOLS)]
    ask       = [from_q16_16(mmio.read(ASK_BASE + i * 4))   for i in range(NUM_SYMBOLS)]
    last_fill = [from_q16_16(mmio.read(LAST_FILL_BASE + i * 4)) for i in range(NUM_SYMBOLS)]

    pnl_cash = [
        cash_q32_16(
            mmio.read(PNL_CASH_LO_BASE + i * 4),
            mmio.read(PNL_CASH_HI_BASE + i * 4),
        )
        for i in range(NUM_SYMBOLS)
    ]

    trades = [read_trades_pack(mmio, i) for i in range(NUM_SYMBOLS)]

    # Derived per-symbol quantities
    mid = [(b + a) * 0.5 if (a > 0 or b > 0) else 0.0 for b, a in zip(bid, ask)]
    spread    = [(a - b) if (a > 0 and b > 0) else 0.0 for b, a in zip(bid, ask)]
    pos_value = [p * m for p, m in zip(pos, mid)]
    pnl_mtm   = [pc + p * m for pc, p, m in zip(pnl_cash, pos, mid)]

    return {
        "pos": pos, "bid": bid, "ask": ask, "mid": mid, "spread": spread,
        "pnl_cash": pnl_cash, "pnl_mtm": pnl_mtm, "pos_value": pos_value,
        "last_fill": last_fill, "trades": trades,
    }


def read_telemetry_snapshot(mmio: MMIO) -> dict:
    """One JSON-serializable telemetry sample from Board B AXI (no random data)."""
    st = decode_status(mmio.read(STATUS))
    cash_lo_raw = mmio.read(CASH_LO) & 0xFFFFFFFF
    cash_hi_raw = mmio.read(CASH_HI) & 0xFFFFFFFF
    cash = cash_q32_16(cash_lo_raw, cash_hi_raw)
    psd = read_per_symbol(mmio)
    total_pnl_mtm = sum(psd["pnl_mtm"])
    port_value = cash + sum(psd["pos_value"])
    return {
        "ts": round(time.time(), 3),
        "state": st["fsm_state"],
        "link_up": st["link_up"],
        "risk_halt": st["risk_halt"],
        "strategy": st["strategy"],
        "qps": mmio.read(QUOTES_RCVD),
        "ops": mmio.read(ORDERS_SENT),
        "fps": mmio.read(FILLS_RCVD),
        "rej": mmio.read(RISK_REJECTS),
        "link_err": mmio.read(LINK_ERRORS),
        "cash_lo": int(cash_lo_raw),
        "cash_hi": int(cash_hi_raw),
        "cash": round(cash, 4),
        "total_pnl": round(total_pnl_mtm, 4),
        "port_value": round(port_value, 4),
        "pos": psd["pos"],
        "bid": [round(v, 4) for v in psd["bid"]],
        "ask": [round(v, 4) for v in psd["ask"]],
        "mid": [round(v, 4) for v in psd["mid"]],
        "spread": [round(v, 4) for v in psd["spread"]],
        "pnl_cash": [round(v, 4) for v in psd["pnl_cash"]],
        "pnl_mtm": [round(v, 4) for v in psd["pnl_mtm"]],
        "pos_value": [round(v, 4) for v in psd["pos_value"]],
        "last_fill": [round(v, 4) for v in psd["last_fill"]],
        "trades": psd["trades"],
        "hist": [mmio.read(HIST_BASE + i * 4) for i in range(NUM_HIST_BINS)],
        "lat_min": mmio.read(LAT_MIN),
        "lat_max": mmio.read(LAT_MAX),
        "lat_sum": mmio.read(LAT_SUM),
        "lat_cnt": mmio.read(LAT_COUNT),
    }


def print_status(mmio: MMIO) -> None:
    """Read and display all Board B status registers (human-readable)."""
    st = decode_status(mmio.read(STATUS))
    print(f"  fsm_state    : {st['fsm_state']}")
    print(f"  link_up      : {st['link_up']}")
    print(f"  risk_halt    : {st['risk_halt']}")
    print(f"  strategy     : {st['strategy']}")
    print(f"  quotes_rcvd  : {mmio.read(QUOTES_RCVD)}")
    print(f"  orders_sent  : {mmio.read(ORDERS_SENT)}")
    print(f"  fills_rcvd   : {mmio.read(FILLS_RCVD)}")
    print(f"  risk_rejects : {mmio.read(RISK_REJECTS)}")
    print(f"  link_errors  : {mmio.read(LINK_ERRORS)}")
    cash = cash_q32_16(mmio.read(CASH_LO), mmio.read(CASH_HI))
    print(f"  cash         : ${cash:+,.2f}")
    psd = read_per_symbol(mmio)
    total_mtm = sum(psd["pnl_mtm"])
    port_val  = cash + sum(psd["pos_value"])
    print(f"  total_pnl_mtm: ${total_mtm:+,.2f}")
    print(f"  port_value   : ${port_val:+,.2f}")
    for i in range(min(4, NUM_SYMBOLS)):
        print(f"  sym[{i:2}]: pos={psd['pos'][i]:>+5}  "
              f"mid=${psd['mid'][i]:>8.2f}  "
              f"pnl_mtm=${psd['pnl_mtm'][i]:+,.2f}  "
              f"trades={psd['trades'][i]}")


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
            print(json.dumps(read_telemetry_snapshot(mmio)), flush=True)
            time.sleep(interval)
    except KeyboardInterrupt:
        print("\nTelemetry stopped.", flush=True)


if __name__ == "__main__":
    main()
