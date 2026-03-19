#!/usr/bin/env python3
"""
Board B PS Script — telemetry_server.py
Configures the trader pipeline, then enters a 20 Hz telemetry loop
that reads all status registers and prints JSON lines to stdout.
Stdout is routed through UART → FTDI → USB to the laptop dashboard.
See §5.1.2 of design spec.
"""

import json
import time
from pynq import Overlay, MMIO
from register_map import *


def main():
    ol = Overlay("overlays/board_b.bit")
    mmio = MMIO(ol.ip_dict['board_b_top_0']['phys_addr'], 512)

    # Configure
    mmio.write(STRATEGY_SEL,   0)                # 0=mean-reversion
    mmio.write(THRESHOLD,      q16_16(1.00))     # $1.00 deviation threshold
    mmio.write(EMA_ALPHA,      6554)             # ~0.1 in Q0.16
    mmio.write(BASE_QTY,       100)              # 100 shares per order
    mmio.write(MAX_POSITION,   500)
    mmio.write(MAX_ORDER_RATE, 1000)
    mmio.write(MAX_LOSS,       q16_16(100.00))

    # Start
    mmio.write(CTRL, 0x01)
    print("Board B started. Entering telemetry loop.", flush=True)

    # Telemetry loop (20 Hz)
    while True:
        data = {}
        data["qps"]      = mmio.read(QUOTES_RCVD)
        data["ops"]      = mmio.read(ORDERS_SENT)
        data["fps"]      = mmio.read(FILLS_RCVD)
        data["rej"]      = mmio.read(RISK_REJECTS)
        data["pos"]      = [signed32(mmio.read(POS_SYM0 + i * 4))
                            for i in range(NUM_SYMBOLS)]
        data["cash_lo"]  = mmio.read(CASH_LO)
        data["cash_hi"]  = mmio.read(CASH_HI)
        data["hist"]     = [mmio.read(HIST_BIN0 + i * 4)
                            for i in range(NUM_HIST_BINS)]
        data["lat_min"]  = mmio.read(LAT_MIN)
        data["lat_max"]  = mmio.read(LAT_MAX)
        data["lat_sum"]  = mmio.read(LAT_SUM)
        data["lat_cnt"]  = mmio.read(LAT_COUNT)
        data["link_err"] = mmio.read(LINK_ERRORS)
        data["state"]    = mmio.read(STATUS)

        print(json.dumps(data), flush=True)
        time.sleep(0.05)  # 50 ms = 20 Hz


if __name__ == "__main__":
    main()
