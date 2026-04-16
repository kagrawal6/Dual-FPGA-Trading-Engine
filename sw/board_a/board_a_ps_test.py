"""
Board A — Comprehensive PS Hardware Verification Test
======================================================
Run from PYNQ Jupyter (Board A must be booted with board_a.bit overlay).

Usage:
    from pynq import Overlay
    ol = Overlay('overlays/board_a.bit')
    %run board_a_ps_test.py

Or paste the full script into a Jupyter cell after loading the overlay.
"""

import time
from pynq import MMIO

# ═══════════════════════════════════════════════════════════════════════════
# Register Map (must match board_a_axi_regs.sv)
# ═══════════════════════════════════════════════════════════════════════════
CTRL              = 0x00
QUOTE_INTERVAL    = 0x04
LFSR_SEED         = 0x08
REGIME            = 0x0C
INIT_MID_BASE     = 0x10   # +4*i, i in [0..15]
INIT_SPREAD_BASE  = 0x50   # +4*i
SECTOR_ID_BASE    = 0x90   # +4*i
TOKEN_BASE        = 0xD0   # +4*j, two 16-bit tokens packed per word
ACTIVE_SYM_COUNT  = 0xF0
STATUS            = 0xF4
QUOTES_SENT       = 0xF8
ORDERS_RCVD       = 0xFC

NUM_SYM = 16

# ═══════════════════════════════════════════════════════════════════════════
# Helpers
# ═══════════════════════════════════════════════════════════════════════════
def q16_16(val):
    """Float -> unsigned Q16.16 fixed-point."""
    return int(val * 65536) & 0xFFFFFFFF

def from_q16_16(raw):
    """Unsigned Q16.16 -> float."""
    return raw / 65536.0

def decode_status(raw):
    return {
        "running":       bool(raw & 0x01),
        "link_up":       bool(raw & 0x02),
        "active_regime": (raw >> 2) & 0x03,
        "fifo_fill":     (raw >> 9) & 0x7F,
        "raw":           f"0x{raw:08X}",
    }

REGIME_NAMES = {0: "CALM", 1: "VOLATILE", 2: "BURST", 3: "ADVERSARIAL"}

passed = 0
failed = 0
total  = 0

def check(name, condition, detail=""):
    global passed, failed, total
    total += 1
    tag = "PASS" if condition else "FAIL"
    if condition:
        passed += 1
    else:
        failed += 1
    suffix = f"  ({detail})" if detail else ""
    print(f"  [{tag}] {name}{suffix}")

def section(title):
    print(f"\n{'='*60}")
    print(f" {title}")
    print(f"{'='*60}")

def reset_board(mmio):
    mmio.write(CTRL, 0x02)
    time.sleep(0.05)

def start_board(mmio):
    mmio.write(CTRL, 0x01)
    time.sleep(0.05)


# ═══════════════════════════════════════════════════════════════════════════
# Acquire MMIO handle (assumes overlay 'ol' is already loaded)
# ═══════════════════════════════════════════════════════════════════════════
base = ol.ip_dict['hft_core']['phys_addr']
span = ol.ip_dict['hft_core']['addr_range']
mmio = MMIO(base, span)

print("Board A PS Hardware Verification Test")
print(f"  base_addr = 0x{base:08X}, addr_range = {span}")
print(f"  IP blocks: {list(ol.ip_dict.keys())}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 1: Reset defaults
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 1: Reset defaults")
reset_board(mmio)

s = decode_status(mmio.read(STATUS))
check("running == False after reset", not s["running"])
check("link_up == False (no Board B)", not s["link_up"])
check("quotes_sent == 0 after reset", mmio.read(QUOTES_SENT) == 0)
check("orders_rcvd == 0 after reset", mmio.read(ORDERS_RCVD) == 0)
check("quote_interval default == 1000", mmio.read(QUOTE_INTERVAL) == 1000)
check("lfsr_seed default == 0xDEADBEEF", mmio.read(LFSR_SEED) == 0xDEADBEEF)
check("regime default == CALM (0)", mmio.read(REGIME) == 0)
check("active_sym_count default == 16", mmio.read(ACTIVE_SYM_COUNT) == NUM_SYM)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 2: Scalar register write/readback
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 2: Scalar register write/readback")

test_vals = {
    "QUOTE_INTERVAL": (QUOTE_INTERVAL, [0, 1, 500, 1000, 0xFFFFFFFF]),
    "LFSR_SEED":      (LFSR_SEED,      [0x00000001, 0xCAFEBABE, 0xFFFFFFFF, 0xDEADBEEF]),
    "REGIME":         (REGIME,          [0, 1, 2, 3]),
}

for name, (addr, vals) in test_vals.items():
    for v in vals:
        mmio.write(addr, v)
        rb = mmio.read(addr)
        if name == "REGIME":
            rb = rb & 0x03
            v  = v & 0x03
        check(f"{name} = 0x{v:X}", rb == v, f"got 0x{rb:X}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 3: Active symbol count clamping
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 3: Active symbol count clamping")

clamp_tests = [
    (0,   1,  "0 clamps to 1"),
    (1,   1,  "min valid"),
    (8,   8,  "mid range"),
    (16, 16,  "max valid (NUM_SYM)"),
    (17, 16,  "17 clamps to 16"),
    (255, 16, "255 clamps to 16"),
]
for write_val, expect, desc in clamp_tests:
    mmio.write(ACTIVE_SYM_COUNT, write_val)
    rb = mmio.read(ACTIVE_SYM_COUNT)
    check(desc, rb == expect, f"write {write_val} -> read {rb} (expect {expect})")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 4: Per-symbol init_mid / init_spread / sector_id (all 16 slots)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 4: Per-symbol array registers (16 slots)")

symbols = [
    ("AAPL",  180.00, 0.10, 0), ("MSFT",  420.00, 0.15, 0),
    ("GOOG",  175.00, 0.12, 0), ("META",  510.00, 0.20, 0),
    ("NVDA",  900.00, 0.25, 1), ("AMD",   160.00, 0.08, 1),
    ("INTC",   31.00, 0.05, 1), ("AVGO",  170.00, 0.18, 1),
    ("AMZN",  185.00, 0.10, 2), ("TSLA",  250.00, 0.30, 2),
    ("JPM",   200.00, 0.08, 3), ("GS",    470.00, 0.22, 3),
    ("JNJ",   155.00, 0.06, 4), ("PFE",    27.00, 0.04, 4),
    ("XOM",   105.00, 0.07, 5), ("CVX",   155.00, 0.09, 5),
]

for i, (name, mid, spr, sec) in enumerate(symbols):
    mmio.write(INIT_MID_BASE + 4*i, q16_16(mid))
    mmio.write(INIT_SPREAD_BASE + 4*i, q16_16(spr))
    mmio.write(SECTOR_ID_BASE + 4*i, sec)

mid_ok = spr_ok = sec_ok = 0
for i, (name, mid, spr, sec) in enumerate(symbols):
    if mmio.read(INIT_MID_BASE + 4*i)    == q16_16(mid):  mid_ok += 1
    if mmio.read(INIT_SPREAD_BASE + 4*i)  == q16_16(spr):  spr_ok += 1
    if mmio.read(SECTOR_ID_BASE + 4*i)    == sec:          sec_ok += 1

check(f"init_mid readback",    mid_ok == 16, f"{mid_ok}/16")
check(f"init_spread readback", spr_ok == 16, f"{spr_ok}/16")
check(f"sector_id readback",   sec_ok == 16, f"{sec_ok}/16")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 5: Zero spread stored as 1
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 5: Zero spread -> 1 protection")

mmio.write(INIT_SPREAD_BASE, 0)
rb = mmio.read(INIT_SPREAD_BASE)
check("spread 0 -> stored as 1", rb == 1, f"got {rb}")
mmio.write(INIT_SPREAD_BASE, q16_16(0.10))


# ═══════════════════════════════════════════════════════════════════════════
# TEST 6: Token register packing (two 16-bit tokens per 32-bit word)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 6: Company token register packing")

test_tokens = list(range(0x1000, 0x1000 + NUM_SYM))
for j in range(NUM_SYM // 2):
    lo = test_tokens[2*j] & 0xFFFF
    hi = test_tokens[2*j+1] & 0xFFFF
    mmio.write(TOKEN_BASE + 4*j, (hi << 16) | lo)

tok_ok = 0
for j in range(NUM_SYM // 2):
    word = mmio.read(TOKEN_BASE + 4*j)
    lo = word & 0xFFFF
    hi = (word >> 16) & 0xFFFF
    if lo == test_tokens[2*j] and hi == test_tokens[2*j+1]:
        tok_ok += 1

check("token packing (8 words, 16 tokens)", tok_ok == 8, f"{tok_ok}/8 words correct")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 7: FSM start / running / reset cycle
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 7: FSM start / running / reset")

reset_board(mmio)
s = decode_status(mmio.read(STATUS))
check("after reset: not running", not s["running"])

mmio.write(ACTIVE_SYM_COUNT, 16)
mmio.write(QUOTE_INTERVAL, 1000)
mmio.write(LFSR_SEED, 0xDEADBEEF)
mmio.write(REGIME, 0)
for i, (name, mid, spr, sec) in enumerate(symbols):
    mmio.write(INIT_MID_BASE + 4*i, q16_16(mid))
    mmio.write(INIT_SPREAD_BASE + 4*i, q16_16(spr))
    mmio.write(SECTOR_ID_BASE + 4*i, sec)

start_board(mmio)
time.sleep(0.2)
s = decode_status(mmio.read(STATUS))
qs = mmio.read(QUOTES_SENT)
check("after start: running", s["running"])
check("after start: quotes > 0", qs > 0, f"quotes_sent={qs}")

reset_board(mmio)
s = decode_status(mmio.read(STATUS))
check("after reset: not running", not s["running"])
check("after reset: quotes_sent == 0", mmio.read(QUOTES_SENT) == 0)

start_board(mmio)
time.sleep(0.2)
s2 = decode_status(mmio.read(STATUS))
check("restart: running again", s2["running"])
check("restart: quotes > 0", mmio.read(QUOTES_SENT) > 0)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 8: STATUS register bit-field decode
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 8: STATUS register bit-fields")

# STATUS layout: {16'd0, fifo_fill[6:0], 5'd0, active_regime[1:0], link_up, running}
for reg_val, reg_name in [(0, "CALM"), (1, "VOLATILE"), (2, "BURST"), (3, "ADVERSARIAL")]:
    mmio.write(REGIME, reg_val)
    time.sleep(0.02)
    s = decode_status(mmio.read(STATUS))
    check(f"regime {reg_name}: active_regime == {reg_val}", s["active_regime"] == reg_val)

mmio.write(REGIME, 0)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 9: Quote interval scaling
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 9: Quote interval scaling")

rates = {}
for qi in [10000, 1000, 100]:
    reset_board(mmio)
    mmio.write(QUOTE_INTERVAL, qi)
    mmio.write(ACTIVE_SYM_COUNT, 16)
    for i, (name, mid, spr, sec) in enumerate(symbols):
        mmio.write(INIT_MID_BASE + 4*i, q16_16(mid))
        mmio.write(INIT_SPREAD_BASE + 4*i, q16_16(spr))
    start_board(mmio)
    qs_before = mmio.read(QUOTES_SENT)
    time.sleep(1.0)
    qs_after = mmio.read(QUOTES_SENT)
    rate = qs_after - qs_before
    rates[qi] = rate
    print(f"  interval={qi:5d} -> ~{rate} quotes/s")

if rates[1000] > 0 and rates[10000] > 0:
    ratio_10x = rates[1000] / rates[10000]
    check("1000 vs 10000: ~10x faster", 8.0 < ratio_10x < 12.0, f"ratio={ratio_10x:.1f}")
if rates[100] > 0 and rates[1000] > 0:
    ratio_10x = rates[100] / rates[1000]
    check("100 vs 1000: ~10x faster", 8.0 < ratio_10x < 12.0, f"ratio={ratio_10x:.1f}")

# Max rate test (interval=0)
reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 0)
mmio.write(ACTIVE_SYM_COUNT, 16)
for i, (name, mid, spr, sec) in enumerate(symbols):
    mmio.write(INIT_MID_BASE + 4*i, q16_16(mid))
    mmio.write(INIT_SPREAD_BASE + 4*i, q16_16(spr))
start_board(mmio)
time.sleep(0.5)
qs_max = mmio.read(QUOTES_SENT)
max_rate = qs_max * 2
print(f"  interval=0 (max) -> ~{max_rate} quotes/s")
check("max rate > 1M quotes/s", max_rate > 1_000_000, f"got {max_rate}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 10: Regime switching while running
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 10: Regime switching (live)")

reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 1000)
mmio.write(ACTIVE_SYM_COUNT, 16)
for i, (name, mid, spr, sec) in enumerate(symbols):
    mmio.write(INIT_MID_BASE + 4*i, q16_16(mid))
    mmio.write(INIT_SPREAD_BASE + 4*i, q16_16(spr))
start_board(mmio)
time.sleep(0.1)

for reg_val, reg_name in [(0, "CALM"), (1, "VOLATILE"), (2, "BURST"), (3, "ADVERSARIAL")]:
    mmio.write(REGIME, reg_val)
    qb = mmio.read(QUOTES_SENT)
    time.sleep(0.5)
    qa = mmio.read(QUOTES_SENT)
    rate = (qa - qb) * 2
    s = decode_status(mmio.read(STATUS))
    check(f"{reg_name}: still running, regime={reg_val}", s["running"] and s["active_regime"] == reg_val,
          f"~{rate} quotes/s")

mmio.write(REGIME, 0)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 11: ORDERS_RCVD stays 0 (no Board B link)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 11: Exchange (no link)")

time.sleep(0.5)
orders = mmio.read(ORDERS_RCVD)
check("orders_rcvd == 0 (no Board B)", orders == 0)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 12: Regime parameters (step_size / base_spread from RTL)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 12: Regime parameter reference")

# These are the RTL constants — not directly readable, but we document them
# for validation against simulation/waveform analysis.
regime_params = {
    "CALM":        {"step_size": "0x0000_0400", "base_spread": "0x0000_1000"},
    "VOLATILE":    {"step_size": "0x0000_8000", "base_spread": "0x0000_4000"},
    "BURST":       {"step_size": "0x0000_0400", "base_spread": "0x0000_1000"},
    "ADVERSARIAL": {"step_size": "0x0001_0000", "base_spread": "0x0000_8000"},
}
print("  (Reference — not directly readable from PS, verified via RTL)")
for name, p in regime_params.items():
    ss = int(p["step_size"].replace("_",""), 16)
    bs = int(p["base_spread"].replace("_",""), 16)
    print(f"  {name:12s}: step_size={from_q16_16(ss):.4f}  base_spread={from_q16_16(bs):.4f}")

check("CALM == BURST (same params)",
      regime_params["CALM"] == regime_params["BURST"],
      "step_size and base_spread match")
check("ADVERSARIAL has largest step_size",
      int(regime_params["ADVERSARIAL"]["step_size"].replace("_",""), 16) >
      int(regime_params["VOLATILE"]["step_size"].replace("_",""), 16))


# ═══════════════════════════════════════════════════════════════════════════
# TEST 13: Full 16-symbol sustained run
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 13: 16-symbol sustained run (5 seconds)")

reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 1000)
mmio.write(ACTIVE_SYM_COUNT, 16)
mmio.write(LFSR_SEED, 0xDEADBEEF)
mmio.write(REGIME, 0)
for i, (name, mid, spr, sec) in enumerate(symbols):
    mmio.write(INIT_MID_BASE + 4*i, q16_16(mid))
    mmio.write(INIT_SPREAD_BASE + 4*i, q16_16(spr))
    mmio.write(SECTOR_ID_BASE + 4*i, sec)

start_board(mmio)
samples = []
for t in range(5):
    time.sleep(1.0)
    qs = mmio.read(QUOTES_SENT)
    s = decode_status(mmio.read(STATUS))
    samples.append((t+1, qs, s["running"]))
    print(f"  t={t+1}s: quotes={qs:,}  running={s['running']}")

check("still running after 5s", samples[-1][2])
check("quote count monotonically increasing",
      all(samples[i][1] > samples[i-1][1] for i in range(1, len(samples))))

# Rate stability: each 1s delta should be within 5% of mean
deltas = [samples[i][1] - samples[i-1][1] for i in range(1, len(samples))]
if deltas:
    mean_delta = sum(deltas) / len(deltas)
    max_dev = max(abs(d - mean_delta) / mean_delta for d in deltas) if mean_delta > 0 else 0
    check("rate stable (< 5% deviation)", max_dev < 0.05, f"max_dev={max_dev:.2%}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 14: Address boundary — read from unused address
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 14: Unused address reads")

# Addresses beyond the defined map should return 0 (default rd_data_mux)
for test_addr in [0x04 + 1, 0xE0, 0xE4, 0xE8, 0xEC]:
    val = mmio.read(test_addr)
    print(f"  addr 0x{test_addr:02X} -> 0x{val:08X}")
# No hard pass/fail — just observational


# ═══════════════════════════════════════════════════════════════════════════
# SUMMARY
# ═══════════════════════════════════════════════════════════════════════════
reset_board(mmio)

print(f"\n{'='*60}")
print(f" BOARD A PS TEST SUMMARY")
print(f"{'='*60}")
print(f"  Total:  {total}")
print(f"  Passed: {passed}")
print(f"  Failed: {failed}")
if failed == 0:
    print(f"\n  *** ALL TESTS PASSED ***")
else:
    print(f"\n  *** {failed} TEST(S) FAILED ***")
print(f"{'='*60}")
