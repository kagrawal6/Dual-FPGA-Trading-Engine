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
│   ├── board_b/            telemetry_server.py, register_map.py (see sw/board_b/README.md)
│   └── laptop/             board_b_dashboard.py (TradeMark), dashboard.py
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

## Board B PYNQ (PS) + laptop UI

- **On the Board B PYNQ:** configure MMIO and stream telemetry — see **[`sw/board_b/README.md`](sw/board_b/README.md)** (`telemetry_server.py`, overlay path, UART/stdout).
- **On the laptop:** TradeMark terminal — `sw/laptop/board_b_dashboard.py` (see `python3 board_b_dashboard.py -h`). Use **`board_b_dashboard.py`**, not `dashboard.py`, for the terminal layout.
