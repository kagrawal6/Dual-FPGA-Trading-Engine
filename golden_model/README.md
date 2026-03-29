# Golden Model — Dual-FPGA Trading Engine

Software simulation of the full trading system. Use this to understand
the algorithm, test Verilog modules, and run demos.

## Files

| File | What it does |
|------|-------------|
| `common.py` | Constants, frame formats (QuoteFrame/OrderFrame/FillFrame), LFSR, link layer |
| `board_a.py` | Market simulator + exchange (generates quotes, matches orders) |
| `board_b.py` | Trading pipeline (EMA, strategy, risk manager, position tracker) |
| `run.py` | Interactive demo runner with live stats dashboard |

## How to Run

```
cd golden_model
python run.py
```

Press Enter to advance the simulation. Type commands to control it:

```
regime 0        Switch to CALM market (small price moves)
regime 1        Switch to VOLATILE market
regime 3        Switch to ADVERSARIAL market (stress test)
threshold 0.5   Set trading threshold to $0.50
qty 200         Set order quantity to 200 shares
stop            Pause trading
start           Resume trading
reset           Reset everything
quit            Exit
```

### Command-line options

```
python run.py --regime 3 --threshold 0.03 --sym 4
```

## How to Use for RTL Testing

Run the golden model to get expected values, then compare in your Verilog testbench:

```python
from common import QuoteFrame, q16
from board_b import FeatureEngine

fe = FeatureEngine(num_sym=4)
mid = q16(150.5)                          # $150.50 in Q16.16
deviation = fe.compute(symbol=0, mid=mid, alpha=6554)
print(f"Expected deviation: 0x{deviation:08X}")
```

Use that hex value in your SystemVerilog testbench assertion:

```systemverilog
assert (dut.deviation === 32'h<value_from_python>);
```
