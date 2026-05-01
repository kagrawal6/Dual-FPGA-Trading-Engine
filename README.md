# ECE 554 Capstone

Dual-FPGA low-latency trading engine for ECE 554.

## Directory Structure

```
new_implementation/
├── rtl/                    SystemVerilog source
│   ├── shared/             Shared modules (both boards)
│   ├── link/               PMOD link layer (TX/RX)
│   ├── board_a/            Board A (Exchange + Market Sim)
│   └── board_b/            Board B (Trader Pipeline)
├── tb/                     Testbenches (mirrors rtl/ layout)
├── constraints/            Vivado XDC pin constraints
├── scripts/                Build & regression scripts
├── sw/                     PS + laptop Python scripts
│   ├── board_a/            config_exchange.py
│   ├── board_b/            telemetry_server.py, register_map.py
│   └── laptop/             dashboard.py
├── docs/                   Implementation notes
└── images/                 Diagrams, screenshots
```

## Design Specification

See `../docs/updated_design_specification.md` for the full spec.

## Quick Reference

| Board | Role | FSM States | Key Modules |
|-------|------|------------|-------------|
| A | Exchange-Lite + Market Sim | RESET → IDLE → RUNNING ↔ STOPPED | market_sim, exchange_lite, tx_arbiter |
| B | Trader (Strategy + Risk) | RESET → IDLE → ARMED → TRADING ↔ HALTED | feature_compute, strategy_engine, risk_manager |

**Clock**: 100 MHz (PS FCLK0) — single domain per board, CDC only at PMOD RX.
**Link**: 4-bit PMOD, 50 MHz data rate, 128-bit fixed frames.
**Pipeline**: 8 cycles (80 ns) quote-to-order on Board B.

To run board A run a new terminal and start these commands:
cd home/xilinx/jupyter_notebooks/
python web_server_a_updated.py --bitfile overlays/board_a.bit

Then jumpstart the prices by going to the board_A.ipynb, running the first 3 cells and finally the cell beginning with:

import time

# Restart Board A with 16 symbols
mmio.write(0x00, 0x02)  # reset
time.sleep(0.1)

symbols_config = [
    (180.00, 0.10), (420.00, 0.15), (175.00, 0.12), (510.00, 0.20),
    (900.00, 0.25), (160.00, 0.08), ( 31.00, 0.05), (170.00, 0.18),
    (185.00, 0.10), (250.00, 0.30), (200.00, 0.08), (470.00, 0.22),
    (155.00, 0.06), ( 27.00, 0.04), (105.00, 0.07), (155.00, 0.09),
]

Make sure that board 2 is on and connected and everything should run properly
