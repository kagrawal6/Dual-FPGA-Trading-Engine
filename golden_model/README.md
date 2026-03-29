# Golden Model — Dual-FPGA Trading Engine

Software simulation of the full trading system. Use this to understand
the algorithm, test Verilog modules, and run demos.

## Files

| File | What it does |
|------|-------------|
| `common.py` | Constants, frame formats, LFSR, link layer, **symbol universe** (16 S&P 500 tickers) |
| `board_a.py` | Market simulator + exchange (generates quotes, matches orders) |
| `board_b.py` | Trading pipeline (EMA, strategy, risk manager, position tracker) |
| `run.py` | Interactive demo runner with live stats dashboard |

## Default Symbol Universe

The model ships with 16 real S&P 500 tickers across 8 GICS sectors:

| Slot | Ticker | Sector | Init Price |
|------|--------|--------|-----------|
| 0 | AAPL | Tech | $180.00 |
| 1 | MSFT | Tech | $420.00 |
| 2 | NVDA | Tech | $900.00 |
| 3 | XOM | Energy | $115.00 |
| 4 | CVX | Energy | $160.00 |
| 5 | JNJ | Health | $155.00 |
| 6 | UNH | Health | $520.00 |
| 7 | AMZN | Cons.Disc | $185.00 |
| 8 | TSLA | Cons.Disc | $250.00 |
| 9 | JPM | Financ. | $200.00 |
| 10 | GS | Financ. | $480.00 |
| 11 | CAT | Indust. | $360.00 |
| 12 | HON | Indust. | $200.00 |
| 13 | PG | Staples | $165.00 |
| 14 | KO | Staples | $60.00 |
| 15 | GOOGL | Comms | $175.00 |

Symbols in the same sector share correlated price drift (sector noise).

## How to Run

```
cd golden_model
python run.py
```

The dashboard auto-refreshes continuously. Use single-key controls:

| Key | Action |
|-----|--------|
| `c` | Switch to **CALM** market |
| `v` | Switch to **VOLATILE** market |
| `b` | Switch to **BURST** market |
| `a` | Switch to **ADVERSARIAL** market (stress test) |
| `+` | Raise trading threshold by $0.10 |
| `-` | Lower trading threshold by $0.10 |
| `s` | Toggle start / stop trading |
| `r` | Reset everything |
| `q` | Quit |

### Command-line options

```
python run.py --regime 3 --threshold 0.30 --sym 4
```

Use `--sym 4` to run with fewer symbols (first 4 from the universe).

## How to Use for RTL Testing

Run the golden model to get expected values, then compare in your Verilog testbench:

```python
from common import QuoteFrame, q16, default_init_mids
from board_b import FeatureEngine

fe = FeatureEngine(num_sym=16)
mid = default_init_mids()[0]              # AAPL's init price in Q16.16
deviation = fe.compute(symbol=0, mid=mid, alpha=6554)
print(f"Expected deviation: 0x{deviation:08X}")
```

Use that hex value in your SystemVerilog testbench assertion:

```systemverilog
assert (dut.deviation === 32'h<value_from_python>);
```
