"""
gen_board_a_vectors.py — Generate Board A golden vectors for RTL testbenches.
Prints hex constants suitable for embedding as localparam arrays in SystemVerilog.
"""
import sys, os
sys.path.insert(0, os.path.dirname(__file__))

from common import (
    MASK_16, MASK_32, MASK_128, LFSR_TAPS,
    LFSR32, GOLDEN, GLOBAL_SEED_XOR, SECTOR_SEED_XOR,
    MsgType, Regime, FillStatus, SIDE_BUY, SIDE_SELL,
    QuoteFrame, OrderFrame, FillFrame,
    q16, from_q16, sext32, clamp,
    REGIME_PARAMS, DRIFT_SATURATION, PULLBACK_SHIFT,
    MIN_PRICE, MAX_PRICE,
)
from board_a import BoardA, NoiseGen, MarketSim, Exchange


def main():
    print("=" * 70)
    print("LFSR GOLDEN VECTORS")
    print("=" * 70)

    for seed_name, seed_val in [("0xDEADBEEF", 0xDEADBEEF), ("0x00000001", 1), ("0x00000000", 0)]:
        lfsr = LFSR32(seed_val)
        effective_seed = lfsr.value
        vals = []
        for i in range(16):
            v = lfsr.step()
            vals.append(v)
        print(f"\n// Seed = {seed_name}, effective initial reg = 0x{effective_seed:08X}")
        for i, v in enumerate(vals):
            print(f"//   step[{i:2d}] = 32'h{v:08X}")

    # Also print after-seed-1 golden (matches existing TB)
    lfsr = LFSR32(1)
    print(f"\n// Seed = 1 (RTL reset default)")
    print(f"//   initial reg = 0x{lfsr.value:08X}")
    for i in range(8):
        v = lfsr.step()
        print(f"//   step[{i}] = 32'h{v:08X}")

    print("\n" + "=" * 70)
    print("NOISE GENERATOR GOLDEN VECTORS")
    print("=" * 70)

    noise = NoiseGen(num_sym=4, num_sectors=4)
    noise.seed(0xDEADBEEF)
    sector_ids = [0, 0, 1, 1]

    for tick in range(8):
        step_out = noise.generate(active_count=4, sector_ids=sector_ids)
        print(f"\n// Tick {tick}: step_out[0..3]")
        for s in range(4):
            sv = step_out[s] & MASK_32
            print(f"//   step_out[{s}] = 32'h{sv:08X}  ({sext32(sv):+d})")

    print("\n" + "=" * 70)
    print("MARKET SIM QUOTE FRAME GOLDEN VECTORS")
    print("=" * 70)

    board_a = BoardA(num_sym=4, num_sectors=4)
    board_a.configure(
        regime=Regime.CALM, quote_interval=0, seed=0xDEADBEEF,
        init_mid=[q16(180.0), q16(420.0), q16(900.0), q16(115.0)],
        init_spread=[q16(0.10), q16(0.15), q16(0.25), q16(0.08)],
        sector_ids=[0, 0, 1, 1],
        active_count=4,
    )
    board_a.start()

    quote_frames = []
    for cyc in range(16):
        bits = board_a.step(cyc)
        if bits is not None:
            mt = (bits >> 124) & 0xF
            if mt == MsgType.QUOTE:
                qf = QuoteFrame.from_bits(bits)
                quote_frames.append((cyc, bits, qf))
                print(f"\n// Quote {len(quote_frames)-1}: cycle={cyc} sym={qf.symbol} seq={qf.seq_num}")
                print(f"//   128'h{bits:032X}")
                print(f"//   bid=0x{qf.bid:08X} (${from_q16(qf.bid):.4f})")
                print(f"//   ask=0x{qf.ask:08X} (${from_q16(qf.ask):.4f})")
                print(f"//   sizes=({qf.bid_size},{qf.ask_size}) regime={qf.regime}")

    print(f"\n// best_bid / best_ask after {len(quote_frames)} quotes:")
    for s in range(4):
        print(f"//   sym[{s}]: bid=0x{board_a.market.best_bid[s]:08X} ask=0x{board_a.market.best_ask[s]:08X}")

    print("\n" + "=" * 70)
    print("EXCHANGE LITE GOLDEN VECTORS")
    print("=" * 70)

    bid = [board_a.market.best_bid[s] for s in range(4)]
    ask = [board_a.market.best_ask[s] for s in range(4)]

    exchange = Exchange(num_sym=4)
    test_orders = [
        ("BUY at ask (fill)",   OrderFrame(symbol=0, side=SIDE_BUY,  price=ask[0],       qty=100, order_id=0, timestamp=100)),
        ("BUY below ask (rej)", OrderFrame(symbol=0, side=SIDE_BUY,  price=ask[0]-1,     qty=50,  order_id=1, timestamp=101)),
        ("SELL at bid (fill)",  OrderFrame(symbol=1, side=SIDE_SELL, price=bid[1],       qty=75,  order_id=2, timestamp=102)),
        ("SELL above bid (rej)",OrderFrame(symbol=1, side=SIDE_SELL, price=bid[1]+1,     qty=25,  order_id=3, timestamp=103)),
        ("OORange sym=4 (rej)", OrderFrame(symbol=4, side=SIDE_BUY,  price=q16(200.0),   qty=10,  order_id=4, timestamp=104)),
        ("BUY sym=3 (fill)",    OrderFrame(symbol=3, side=SIDE_BUY,  price=ask[3]+q16(1.0), qty=200, order_id=5, timestamp=105)),
    ]

    for desc, order in test_orders:
        fill = exchange.match(order, bid, ask)
        ob = order.to_bits()
        fb = fill.to_bits()
        stat = "FILLED" if fill.is_filled else "REJECTED"
        print(f"\n// {desc} -> {stat}")
        print(f"//   ORDER: 128'h{ob:032X}")
        print(f"//   FILL:  128'h{fb:032X}")
        print(f"//   fill_price=0x{fill.fill_price:08X} fill_qty={fill.fill_qty}")

    print(f"\n// Exchange counters: orders_rcvd={exchange.orders_rcvd} fills_sent={exchange.fills_sent} rejects_sent={exchange.rejects_sent}")

    print("\n" + "=" * 70)
    print("ALL REGIME SPREADS")
    print("=" * 70)
    for r in [Regime.CALM, Regime.VOLATILE, Regime.BURST, Regime.ADVERSARIAL]:
        p = REGIME_PARAMS[r]
        print(f"// {r.name}: step_size=0x{p['step_size']:08X} base_spread=0x{p['base_spread']:08X}")

    print("\nDone.")


if __name__ == "__main__":
    main()
