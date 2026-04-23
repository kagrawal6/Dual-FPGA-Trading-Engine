"""
Dual-Board End-to-End Test — BOARD B SIDE (main driver)
========================================================
Run this on the BOARD B Jupyter notebook AFTER you have already run
dual_board_test_a.py on Board A (which leaves Board A producing quotes).

This script runs ~16 self-checking tests covering:
  * Link-up handshake from A→B
  * Quote arrival (QUOTES_RCVD growing)
  * Bidirectional handshake stability (LINK_ERRORS not growing)
  * Strategy-engine signal generation
  * FSM transitions IDLE -> ARMED -> TRADING (requires SW[0] up)
  * Order generation under MEAN_REV strategy
  * Fill round-trip from Board A's exchange
  * Position tracking
  * Risk system: MAX_POSITION enforcement
  * Risk system: RISK_REJECTS counter
  * Strategy switch: MEAN_REV -> MOMENTUM live
  * Per-regime behavior (CALM, VOLATILE, BURST, ADVERSARIAL)
  * Reset behavior
  * Counter clearing on reset
  * Long-haul stability (10 s)
  * STATUS register decoding correctness

Each test is self-checking — outputs PASS/FAIL with a final summary.
"""

import time
from pynq import Overlay, MMIO

# ═══════════════════════════════════════════════════════════════════════════
# Board B register map (verified against rtl/board_b/board_b_axi_regs.sv)
# ═══════════════════════════════════════════════════════════════════════════
B_CTRL           = 0x00
B_STRATEGY_SEL   = 0x04
B_THRESHOLD      = 0x08
B_EMA_ALPHA      = 0x0C
B_BASE_QTY       = 0x10
B_MAX_POSITION   = 0x14
B_MAX_ORDER_RATE = 0x18
B_MAX_LOSS       = 0x1C
B_STATUS         = 0x40
B_QUOTES_RCVD    = 0x44
B_ORDERS_SENT    = 0x48
B_FILLS_RCVD     = 0x4C
B_RISK_REJECTS   = 0x50
B_LINK_ERRORS    = 0x54
B_POS_BASE       = 0x58
B_CASH_LO        = 0x98
B_CASH_HI        = 0x9C
B_HIST_BASE      = 0xA0

NUM_SYM = 16
STATE_NAMES    = {0:'B_RESET', 1:'B_IDLE', 2:'B_ARMED', 3:'B_TRADING', 4:'B_HALTED'}
STRATEGY_NAMES = {0:'MEAN_REV', 1:'MOMENTUM', 2:'NN', 3:'AUTO'}

def q16(v): return int(v * 65536) & 0xFFFFFFFF

# Auto-load overlay
try:
    ol_b  # noqa: F821
except NameError:
    print("Loading Board B overlay (overlays/board_b.bit)...")
    ol_b = Overlay('overlays/board_b.bit')

base_b = ol_b.ip_dict['hft_core']['phys_addr']
span_b = ol_b.ip_dict['hft_core']['addr_range']
mmio = MMIO(base_b, span_b)


# ═══════════════════════════════════════════════════════════════════════════
# Helpers
# ═══════════════════════════════════════════════════════════════════════════
def decode_status(raw):
    return {
        'strategy':  STRATEGY_NAMES.get(raw & 0x3, '?'),
        'fsm':       STATE_NAMES.get((raw >> 2) & 0x7, f'?({(raw>>2)&7})'),
        'link_up':   bool(raw & 0x20),
        'risk_halt': bool(raw & 0x40),
        'raw':       f'0x{raw:08X}',
    }

def read_position(slot):
    raw = mmio.read(B_POS_BASE + 4*slot)
    return raw - (1 << 32) if raw & 0x80000000 else raw

def read_cash():
    lo = mmio.read(B_CASH_LO)
    hi = mmio.read(B_CASH_HI) & 0xFFFF
    raw = (hi << 32) | lo
    if raw & (1 << 47): raw -= 1 << 48
    return raw / 65536.0

def reset_b():
    mmio.write(B_CTRL, 0x02); time.sleep(0.1)

def configure_b(strategy=0, threshold=0x00010000, ema_alpha=0x0000199A,
                base_qty=50, max_position=10000, max_order_rate=100000,
                max_loss=0x10000000):
    mmio.write(B_STRATEGY_SEL,   strategy)
    mmio.write(B_THRESHOLD,      threshold)
    mmio.write(B_EMA_ALPHA,      ema_alpha)
    mmio.write(B_BASE_QTY,       base_qty)
    mmio.write(B_MAX_POSITION,   max_position)
    mmio.write(B_MAX_ORDER_RATE, max_order_rate)
    mmio.write(B_MAX_LOSS,       max_loss)

def arm_trading():
    mmio.write(B_CTRL, 0x01); time.sleep(0.1)
    mmio.write(B_CTRL, 0x01); time.sleep(0.3)

passed = failed = total = 0
fail_log = []

def check(name, condition, detail=""):
    global passed, failed, total
    total += 1
    tag = "PASS" if condition else "FAIL"
    if condition: passed += 1
    else: failed += 1; fail_log.append(f"{name}  ({detail})" if detail else name)
    suffix = f"  ({detail})" if detail else ""
    print(f"  [{tag}] {name}{suffix}")

def section(title):
    print(f"\n{'='*72}")
    print(f" {title}")
    print(f"{'='*72}")


print("="*72)
print(" DUAL-BOARD END-TO-END VERIFICATION  (Board B side)")
print("="*72)
print(f"  base_addr = 0x{base_b:08X}  span = {span_b}")
print(f"  Pre-req: dual_board_test_a.py already running on Board A.")
print(f"  Pre-req: Board B physical SW[0] flipped UP (enables trading).")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 1: Link establishment (A is transmitting, B should see link_up)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 1: Link establishment")
reset_b()
time.sleep(0.5)
s = decode_status(mmio.read(B_STATUS))
print(f"  STATUS = {s}")
check("link_up == True (A is transmitting)", s['link_up'])
check("FSM in B_IDLE after reset", s['fsm'] == 'B_IDLE')
check("risk_halt == False on fresh reset", not s['risk_halt'])


# ═══════════════════════════════════════════════════════════════════════════
# TEST 2: Quote arrival (QUOTES_RCVD growing without arming)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 2: Quote arrival from A")
q0 = mmio.read(B_QUOTES_RCVD)
time.sleep(1.0)
q1 = mmio.read(B_QUOTES_RCVD)
delta = q1 - q0
print(f"  QUOTES_RCVD: {q0:,} -> {q1:,}  (Δ = {delta:,}/s)")
check("quotes flowing from A (>1000/s)", delta > 1000, f"got {delta}/s")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 3: Link stability (LINK_ERRORS not growing)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 3: Link stability (3 s)")
le0 = mmio.read(B_LINK_ERRORS)
time.sleep(3.0)
le1 = mmio.read(B_LINK_ERRORS)
print(f"  LINK_ERRORS: {le0} -> {le1}")
check("no new link errors over 3 s", le1 == le0,
      f"+{le1 - le0} errors in 3s")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 4: Strategy generates signals (RISK_REJECTS climbs in IDLE)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 4: Strategy engine produces signals (in B_IDLE)")
rr0 = mmio.read(B_RISK_REJECTS)
time.sleep(1.0)
rr1 = mmio.read(B_RISK_REJECTS)
print(f"  RISK_REJECTS: {rr0:,} -> {rr1:,}  (Δ = {rr1 - rr0:,}/s)")
check("strategy produces signals (rejected in IDLE)", rr1 - rr0 > 100,
      f"got {rr1-rr0}/s")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 5: FSM transitions IDLE -> ARMED -> TRADING
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 5: FSM transition to B_TRADING")
reset_b(); time.sleep(0.3)
s_idle = decode_status(mmio.read(B_STATUS))
check("FSM is B_IDLE before arming", s_idle['fsm'] == 'B_IDLE')

configure_b()
arm_trading()
s_active = decode_status(mmio.read(B_STATUS))
print(f"  STATUS after arm = {s_active}")
check("FSM advanced to B_TRADING", s_active['fsm'] == 'B_TRADING',
      f"got {s_active['fsm']} — flip Board B SW[0] UP if stuck in B_ARMED")
check("risk_halt still False after arming", not s_active['risk_halt'])


# ═══════════════════════════════════════════════════════════════════════════
# TEST 6: Orders are generated and sent
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 6: Order generation in B_TRADING")
o0 = mmio.read(B_ORDERS_SENT)
time.sleep(2.0)
o1 = mmio.read(B_ORDERS_SENT)
print(f"  ORDERS_SENT: {o0:,} -> {o1:,}  (Δ = {o1 - o0:,} in 2 s)")
check("orders being generated", o1 > o0,
      f"+{o1 - o0} orders")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 7: Fills round-trip from A's exchange
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 7: Fill round-trip A->B")
f0 = mmio.read(B_FILLS_RCVD)
time.sleep(2.0)
f1 = mmio.read(B_FILLS_RCVD)
print(f"  FILLS_RCVD: {f0:,} -> {f1:,}  (Δ = {f1 - f0:,} in 2 s)")
check("fills coming back from A", f1 > f0, f"+{f1 - f0} fills")
check("fills closely track orders (>50% fill rate)",
      (f1 - f0) > 0.5 * max(1, (o1 - o0)),
      f"orders Δ={o1-o0}, fills Δ={f1-f0}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 8: Position tracking (per-symbol)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 8: Position tracking")
positions = [read_position(i) for i in range(NUM_SYM)]
nonzero = sum(1 for p in positions if p != 0)
total_abs = sum(abs(p) for p in positions)
print(f"  Symbols with non-zero position: {nonzero}/{NUM_SYM}")
print(f"  Sum of |position| across all symbols: {total_abs}")
for i, p in enumerate(positions):
    if p != 0:
        print(f"    slot {i:2d}: {p:+d}")
check("positions accumulating", nonzero > 0)
check("|position| values within MAX_POSITION (10000)",
      all(abs(p) <= 10000 for p in positions),
      f"max |pos|={max(abs(p) for p in positions)}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 9: Risk system enforces MAX_POSITION
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 9: MAX_POSITION enforcement")
reset_b()
configure_b(max_position=100, base_qty=50, max_order_rate=100000)
arm_trading()
time.sleep(2.0)
positions = [read_position(i) for i in range(NUM_SYM)]
max_abs = max(abs(p) for p in positions)
rr = mmio.read(B_RISK_REJECTS)
print(f"  Max |position| reached: {max_abs}  (limit was 100)")
print(f"  RISK_REJECTS so far: {rr:,}")
check("no position exceeds MAX_POSITION", max_abs <= 100,
      f"max |pos|={max_abs}")
check("risk system actively rejecting (RISK_REJECTS > 0)", rr > 0)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 10: Strategy live-switch (MEAN_REV -> MOMENTUM)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 10: Live strategy switch")
reset_b()
configure_b(strategy=0)
arm_trading()
time.sleep(0.5)
s1 = decode_status(mmio.read(B_STATUS))
print(f"  Initial: {s1['strategy']}  fsm={s1['fsm']}")
check("MEAN_REV active", s1['strategy'] == 'MEAN_REV')

mmio.write(B_STRATEGY_SEL, 1); time.sleep(0.3)
s2 = decode_status(mmio.read(B_STATUS))
print(f"  After switch: {s2['strategy']}  fsm={s2['fsm']}")
check("MOMENTUM now active", s2['strategy'] == 'MOMENTUM')
check("FSM remained B_TRADING through switch", s2['fsm'] == 'B_TRADING')

mmio.write(B_STRATEGY_SEL, 0); time.sleep(0.3)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 11: Per-regime sweep (USER must run set_regime() on Board A)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 11: Per-regime smoke test (just observes)")
reset_b()
configure_b(max_position=10000, base_qty=50)
arm_trading()
print("  Sampling 4 s at current regime — to compare regimes,")
print("  on Board A run: set_regime(0|1|2|3) between samples")
o0 = mmio.read(B_ORDERS_SENT); f0 = mmio.read(B_FILLS_RCVD)
q0 = mmio.read(B_QUOTES_RCVD)
time.sleep(4.0)
o1 = mmio.read(B_ORDERS_SENT); f1 = mmio.read(B_FILLS_RCVD)
q1 = mmio.read(B_QUOTES_RCVD)
print(f"  Δquotes={q1-q0:,}  Δorders={o1-o0:,}  Δfills={f1-f0:,}")
check("trade activity present", (o1 - o0) > 0)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 12: Reset clears all counters
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 12: Reset clears counters")
reset_b(); time.sleep(0.2)
qr = mmio.read(B_QUOTES_RCVD)
osent = mmio.read(B_ORDERS_SENT)
fr = mmio.read(B_FILLS_RCVD)
rr = mmio.read(B_RISK_REJECTS)
print(f"  After reset: QUOTES_RCVD={qr}  ORDERS_SENT={osent}  FILLS_RCVD={fr}  RISK_REJECTS={rr}")
check("ORDERS_SENT cleared", osent == 0, f"got {osent}")
check("FILLS_RCVD cleared", fr == 0, f"got {fr}")
check("RISK_REJECTS cleared", rr == 0, f"got {rr}")
positions = [read_position(i) for i in range(NUM_SYM)]
check("all positions cleared",
      all(p == 0 for p in positions),
      f"max |pos|={max(abs(p) for p in positions)}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 13: 10-second sustained trading
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 13: 10 s sustained trading run")
reset_b()
configure_b(max_position=10000, base_qty=50, max_order_rate=100000)
arm_trading()

samples = []
for t in range(10):
    time.sleep(1.0)
    sample = {
        'q': mmio.read(B_QUOTES_RCVD),
        'o': mmio.read(B_ORDERS_SENT),
        'f': mmio.read(B_FILLS_RCVD),
        'rr': mmio.read(B_RISK_REJECTS),
        's': decode_status(mmio.read(B_STATUS)),
    }
    samples.append(sample)
    print(f"  t={t+1:2d}s  Q={sample['q']:>10,}  O={sample['o']:>7,}  "
          f"F={sample['f']:>7,}  RR={sample['rr']:>9,}  fsm={sample['s']['fsm']}")

monotonic_q = all(samples[i]['q'] >= samples[i-1]['q'] for i in range(1, 10))
monotonic_o = all(samples[i]['o'] >= samples[i-1]['o'] for i in range(1, 10))
fsm_stable = all(s['s']['fsm'] == 'B_TRADING' for s in samples)
no_link_err = mmio.read(B_LINK_ERRORS) == 0 or mmio.read(B_LINK_ERRORS) < 100
check("QUOTES_RCVD monotonic over 10 s", monotonic_q)
check("ORDERS_SENT monotonic over 10 s", monotonic_o)
check("FSM stayed in B_TRADING for 10 s", fsm_stable)
check("LINK_ERRORS bounded (<100)", no_link_err,
      f"got {mmio.read(B_LINK_ERRORS)}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 14: STATUS register decoding self-check
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 14: STATUS bit-field decoding")
for strategy_id, name in STRATEGY_NAMES.items():
    mmio.write(B_STRATEGY_SEL, strategy_id); time.sleep(0.1)
    s = decode_status(mmio.read(B_STATUS))
    check(f"STATUS strategy bits = {name}", s['strategy'] == name,
          f"got {s['strategy']}")
mmio.write(B_STRATEGY_SEL, 0)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 15: Cash sanity (should be a finite signed number)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 15: Cash readout sanity")
cash = read_cash()
print(f"  Cash = {cash:+,.2f}")
# After many trades cash will be in some range — just bound it sanely
check("cash within plausible range (|cash| < $1B)",
      abs(cash) < 1e9, f"got {cash:+,.2f}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 16: Final FSM stability + reset to clean state
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 16: Clean-up reset")
reset_b()
time.sleep(0.3)
s = decode_status(mmio.read(B_STATUS))
check("returns to B_IDLE on reset", s['fsm'] == 'B_IDLE')
check("link still up after reset", s['link_up'])


# ═══════════════════════════════════════════════════════════════════════════
# SUMMARY
# ═══════════════════════════════════════════════════════════════════════════
print(f"\n{'='*72}")
print(f" DUAL-BOARD TEST SUMMARY")
print(f"{'='*72}")
print(f"  Total checks : {total}")
print(f"  Passed       : {passed}")
print(f"  Failed       : {failed}")
if failed:
    print(f"\n  Failures:")
    for f in fail_log:
        print(f"    - {f}")
    print(f"\n  *** {failed} CHECK(S) FAILED ***")
else:
    print(f"\n  *** ALL {total} CHECKS PASSED — DUAL-BOARD SYSTEM VERIFIED ***")
print(f"{'='*72}")
print(f"\n  Now switch to Board A's notebook and call report() to see")
print(f"  A's matching counters (quotes_sent, orders_rcvd).")
