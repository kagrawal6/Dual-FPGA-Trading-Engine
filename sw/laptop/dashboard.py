#!/usr/bin/env python3
"""
Laptop Dashboard — dashboard.py
Plotly Dash application that reads JSON telemetry from Board B's USB-UART
serial port and displays real-time panels for throughput, PnL, positions,
latency histogram, and link health. See §5.4 of design spec.

Usage: python dashboard.py --port COM5 --baud 115200
"""

import argparse
import json
import threading
import serial
# import dash
# from dash import html, dcc
# from dash.dependencies import Input, Output
# import plotly.graph_objects as go

# TODO: Implementation
# 1. Serial reader thread: reads JSON lines from UART, parses into dict,
#    stores latest snapshot in a thread-safe variable.
# 2. Dash layout: 8 panels (throughput, PnL, positions, latency histogram,
#    latency percentiles, order/fill rates, link health, scalar stats).
# 3. Interval callback (500 ms): reads latest snapshot, updates all figures.
# 4. Cash reconstruction: cash = (cash_hi << 32) | cash_lo (signed Q32.16).
# 5. Mean latency: lat_sum / lat_count * 10 ns.


def parse_args():
    p = argparse.ArgumentParser(description="HFT Dashboard")
    p.add_argument("--port", default="COM5", help="Serial port for Board B UART")
    p.add_argument("--baud", type=int, default=115200, help="Baud rate")
    return p.parse_args()


def main():
    args = parse_args()
    print(f"Dashboard starting on {args.port} @ {args.baud} baud")
    # TODO: Launch serial reader thread + Dash app


if __name__ == "__main__":
    main()
