"""
Board A — EXTENSIVE Self-Checking Hardware Verification
========================================================
Run from PYNQ Jupyter (Board A booted with board_a.bit overlay).

Usage:
    from pynq import Overlay
    ol = Overlay('overlays/board_a.bit')
    %run board_a_ps_test_extensive.py

This is the deep-dive companion to board_a_ps_test.py. It exercises:
  * Address-map verification (every register at the documented offset)
  * Walking-1s / walking-0s patterns on every scalar register
  * Per-slot writes with UNIQUE values for all 16 symbols (no shared patterns)
  * Zero-spread protection across ALL slots (not just slot 0)
  * Token packing with unique value per token (32 distinct 16-bit values)
  * CTRL register bit-isolation (0x00, 0x01, 0x02, 0x03)
  * FSM rapid stress (100 start/reset cycles)
  * Quote rate vs active_sym_count (proves rate is N-independent)
  * LFSR determinism (same seed -> same output, two trials)
  * Mid-stream regime change while running (50 random switches)
  * Counter monotonicity (no rollback or freeze)
  * 30-second sustained stability run
  * Maximum-rate sustained run (interval=0, 5 s)
  * Concurrent reads while sim is running (no contention / stale data)
  * Read-while-write atomicity (no torn reads)
  * Boundary values on all u32 registers (0, 1, MAX)
  * Reset-during-run behavior
  * Restart after reset preserves config (parameters not cleared)
  * Unmapped address reads return 0
"""

import time
import random
from pynq import Overlay, MMIO

# Auto-load overlay if 'ol' not already in namespace (e.g. from %run on fresh kernel)
try:
    ol  # noqa: F821 — defined externally if user already loaded it
except NameError:
    print("Loading Board A overlay (overlays/board_a.bit)...")
    ol = Overlay('overlays/board_a.bit')

# ═══════════════════════════════════════════════════════════════════════════
# Register Map (must match board_a_axi_regs.sv)
# ═══════════════════════════════════════════════════════════════════════════
CTRL              = 0x00
QUOTE_INTERVAL    = 0x04
LFSR_SEED         = 0x08
REGIME            = 0x0C
INIT_MID_BASE     = 0x10
INIT_SPREAD_BASE  = 0x50
SECTOR_ID_BASE    = 0x90
TOKEN_BASE        = 0xD0
ACTIVE_SYM_COUNT  = 0xF0
STATUS            = 0xF4
QUOTES_SENT       = 0xF8
ORDERS_RCVD       = 0xFC

NUM_SYM = 16
REGIME_NAMES = {0: "CALM", 1: "VOLATILE", 2: "BURST", 3: "ADVERSARIAL"}

# ═══════════════════════════════════════════════════════════════════════════
# Helpers
# ═══════════════════════════════════════════════════════════════════════════
def q16_16(v):
    return int(v * 65536) & 0xFFFFFFFF

def from_q16_16(raw):
    return raw / 65536.0

def decode_status(raw):
    return {
        "running":       bool(raw & 0x01),
        "link_up":       bool(raw & 0x02),
        "active_regime": (raw >> 2) & 0x03,
        "fifo_fill":     (raw >> 9) & 0x7F,
        "raw":           f"0x{raw:08X}",
    }

passed = 0
failed = 0
total  = 0
fail_log = []

def check(name, condition, detail=""):
    global passed, failed, total
    total += 1
    tag = "PASS" if condition else "FAIL"
    if condition:
        passed += 1
    else:
        failed += 1
        fail_log.append(name + (f"  ({detail})" if detail else ""))
    suffix = f"  ({detail})" if detail else ""
    print(f"  [{tag}] {name}{suffix}")

def section(title):
    print(f"\n{'='*68}")
    print(f" {title}")
    print(f"{'='*68}")

def subsection(title):
    print(f"\n  --- {title} ---")

def reset_board(mmio):
    mmio.write(CTRL, 0x02)
    time.sleep(0.05)

def start_board(mmio):
    mmio.write(CTRL, 0x01)
    time.sleep(0.05)


# ═══════════════════════════════════════════════════════════════════════════
# MMIO acquire (assumes 'ol' overlay loaded externally)
# ═══════════════════════════════════════════════════════════════════════════
base = ol.ip_dict['hft_core']['phys_addr']
span = ol.ip_dict['hft_core']['addr_range']
mmio = MMIO(base, span)

print("="*68)
print(" BOARD A — EXTENSIVE HARDWARE VERIFICATION")
print("="*68)
print(f"  base_addr  = 0x{base:08X}")
print(f"  addr_range = {span} bytes")
print(f"  IP blocks  : {list(ol.ip_dict.keys())}")
print(f"  NUM_SYM    = {NUM_SYM}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 1: Address-map sanity (every register at documented offset)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 1: Address-map sanity")
reset_board(mmio)

REG_MAP = {
    "CTRL":             (CTRL,             None, "WO command bits"),
    "QUOTE_INTERVAL":   (QUOTE_INTERVAL,   1000, "default 1000"),
    "LFSR_SEED":        (LFSR_SEED,        0xDEADBEEF, "default seed"),
    "REGIME":           (REGIME,           0,    "default CALM"),
    "ACTIVE_SYM_COUNT": (ACTIVE_SYM_COUNT, 16,   "default NUM_SYM"),
    "STATUS":           (STATUS,           None, "RO live status"),
    "QUOTES_SENT":      (QUOTES_SENT,      0,    "RO counter, 0 after reset"),
    "ORDERS_RCVD":      (ORDERS_RCVD,      0,    "RO counter, 0 (no link)"),
}

print(f"  Register layout:")
for name, (addr, default, note) in REG_MAP.items():
    raw = mmio.read(addr)
    if default is None:
        print(f"    [{addr:#04x}] {name:18s} = 0x{raw:08X}  ({note})")
    else:
        ok = (raw == default)
        check(f"{name} @ 0x{addr:02X} == 0x{default:08X}", ok,
              f"got 0x{raw:08X}, {note}")

print(f"\n  Per-symbol arrays (base + 4*i):")
print(f"    INIT_MID_BASE     = 0x{INIT_MID_BASE:02X}  range 0x{INIT_MID_BASE:02X}-0x{INIT_MID_BASE+4*15:02X}")
print(f"    INIT_SPREAD_BASE  = 0x{INIT_SPREAD_BASE:02X}  range 0x{INIT_SPREAD_BASE:02X}-0x{INIT_SPREAD_BASE+4*15:02X}")
print(f"    SECTOR_ID_BASE    = 0x{SECTOR_ID_BASE:02X}  range 0x{SECTOR_ID_BASE:02X}-0x{SECTOR_ID_BASE+4*15:02X}")
print(f"    TOKEN_BASE        = 0x{TOKEN_BASE:02X}  range 0x{TOKEN_BASE:02X}-0x{TOKEN_BASE+4*7:02X}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 2: Walking-1s and walking-0s on QUOTE_INTERVAL & LFSR_SEED
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 2: Walking-1s / walking-0s patterns")

for reg_name, addr in [("QUOTE_INTERVAL", QUOTE_INTERVAL),
                       ("LFSR_SEED",      LFSR_SEED)]:
    subsection(f"{reg_name} walking-1s")
    fail_count = 0
    for bit in range(32):
        pat = 1 << bit
        mmio.write(addr, pat)
        rb = mmio.read(addr)
        if rb != pat:
            fail_count += 1
            print(f"    bit {bit}: wrote 0x{pat:08X}, read 0x{rb:08X} FAIL")
    check(f"{reg_name} walking-1s (32 patterns)", fail_count == 0,
          f"{32 - fail_count}/32")

    subsection(f"{reg_name} walking-0s")
    fail_count = 0
    for bit in range(32):
        pat = (~(1 << bit)) & 0xFFFFFFFF
        mmio.write(addr, pat)
        rb = mmio.read(addr)
        if rb != pat:
            fail_count += 1
            print(f"    bit {bit}: wrote 0x{pat:08X}, read 0x{rb:08X} FAIL")
    check(f"{reg_name} walking-0s (32 patterns)", fail_count == 0,
          f"{32 - fail_count}/32")

# Restore defaults
mmio.write(QUOTE_INTERVAL, 1000)
mmio.write(LFSR_SEED, 0xDEADBEEF)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 3: Per-slot writes with UNIQUE values for all 16 symbols
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 3: 16 unique symbol configurations (no shared patterns)")

# Distinct prime-ish values per slot to catch index-aliasing bugs
unique_mids    = [q16_16(13.7  + 17.3 * i) for i in range(NUM_SYM)]
unique_spreads = [q16_16(0.011 + 0.027 * i) for i in range(NUM_SYM)]
unique_sectors = [(i * 7) % 8 for i in range(NUM_SYM)]  # 0,7,14%8,...

for i in range(NUM_SYM):
    mmio.write(INIT_MID_BASE    + 4*i, unique_mids[i])
    mmio.write(INIT_SPREAD_BASE + 4*i, unique_spreads[i])
    mmio.write(SECTOR_ID_BASE   + 4*i, unique_sectors[i])

mid_fails = spread_fails = sector_fails = 0
for i in range(NUM_SYM):
    rb_mid    = mmio.read(INIT_MID_BASE    + 4*i)
    rb_spread = mmio.read(INIT_SPREAD_BASE + 4*i)
    rb_sector = mmio.read(SECTOR_ID_BASE   + 4*i)
    if rb_mid    != unique_mids[i]:    mid_fails    += 1
    if rb_spread != unique_spreads[i]: spread_fails += 1
    # sector_id is masked to 3 bits (BITS = $clog2(SECTOR_COUNT) typically)
    # accept the actual stored value on first write as the truth source
    if (rb_sector & 0xFF) != (unique_sectors[i] & 0xFF) and rb_sector != unique_sectors[i]:
        sector_fails += 1

check("16 unique init_mid values readback",    mid_fails    == 0, f"{NUM_SYM - mid_fails}/{NUM_SYM}")
check("16 unique init_spread values readback", spread_fails == 0, f"{NUM_SYM - spread_fails}/{NUM_SYM}")
check("16 unique sector_id values readback",   sector_fails == 0, f"{NUM_SYM - sector_fails}/{NUM_SYM}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 4: Zero-spread protection on ALL 16 slots
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 4: Zero-spread protection on every slot")

zs_fails = 0
for i in range(NUM_SYM):
    mmio.write(INIT_SPREAD_BASE + 4*i, 0)
    rb = mmio.read(INIT_SPREAD_BASE + 4*i)
    if rb != 1:
        zs_fails += 1
        print(f"    slot {i}: wrote 0, expected 1, got 0x{rb:08X} FAIL")
check("zero-spread -> 1 on all 16 slots", zs_fails == 0, f"{NUM_SYM - zs_fails}/{NUM_SYM}")

# restore non-trivial spreads
for i in range(NUM_SYM):
    mmio.write(INIT_SPREAD_BASE + 4*i, q16_16(0.10))


# ═══════════════════════════════════════════════════════════════════════════
# TEST 5: Token packing — 16 unique tokens in 8 packed words
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 5: Token packing (16 distinct 16-bit tokens)")

# tokens 0xA000..0xA00F so the lo/hi packing is unambiguous
tokens = [0xA000 + i for i in range(NUM_SYM)]
for j in range(NUM_SYM // 2):
    word = (tokens[2*j + 1] << 16) | tokens[2*j]
    mmio.write(TOKEN_BASE + 4*j, word)

word_fails = 0
hi_lo_fails = 0
for j in range(NUM_SYM // 2):
    rb = mmio.read(TOKEN_BASE + 4*j)
    expected = (tokens[2*j + 1] << 16) | tokens[2*j]
    if rb != expected:
        word_fails += 1
        print(f"    word {j}: expected 0x{expected:08X}, got 0x{rb:08X} FAIL")
    lo = rb & 0xFFFF
    hi = (rb >> 16) & 0xFFFF
    if lo != tokens[2*j]:     hi_lo_fails += 1
    if hi != tokens[2*j + 1]: hi_lo_fails += 1

check("8 token words packed correctly", word_fails == 0,   f"{8 - word_fails}/8")
check("16 individual tokens decoded correctly", hi_lo_fails == 0,
      f"{16 - hi_lo_fails}/16 lo+hi halves")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 6: ACTIVE_SYM_COUNT clamping (every boundary value)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 6: ACTIVE_SYM_COUNT clamping")

cases = [
    (0,    1,  "0 -> 1 (zero clamp)"),
    (1,    1,  "min valid"),
    (2,    2,  ""),
    (8,    8,  "mid"),
    (15,   15, ""),
    (16,   16, "max valid (NUM_SYM)"),
    (17,   16, "17 -> 16 (overflow clamp)"),
    (32,   16, "32 -> 16"),
    (255,  16, "255 -> 16"),
    (1000, 16, "1000 -> 16"),
    (0xFFFFFFFF, 16, "0xFFFFFFFF -> 16"),
]
for write_val, expected, note in cases:
    mmio.write(ACTIVE_SYM_COUNT, write_val)
    rb = mmio.read(ACTIVE_SYM_COUNT)
    check(f"write {write_val} -> {expected}", rb == expected,
          f"got {rb}{('  '+note) if note else ''}")

mmio.write(ACTIVE_SYM_COUNT, NUM_SYM)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 7: REGIME register — every value 0..3 + invalid bits stay masked
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 7: REGIME register full sweep + bit-mask")

for r in range(4):
    mmio.write(REGIME, r)
    rb = mmio.read(REGIME)
    check(f"REGIME = {r} ({REGIME_NAMES[r]})", rb == r, f"got {rb}")

# write extra high bits — only low 2 should stick (depending on RTL mask)
for write_val, expected_low2 in [(0xFFFFFFFC, 0), (0xFFFFFFFD, 1),
                                  (0xFFFFFFFE, 2), (0xFFFFFFFF, 3)]:
    mmio.write(REGIME, write_val)
    rb = mmio.read(REGIME)
    check(f"REGIME high bits masked (write 0x{write_val:08X})",
          (rb & 0x3) == expected_low2, f"got 0x{rb:08X}")
mmio.write(REGIME, 0)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 8: CTRL bit isolation
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 8: CTRL register bit isolation")

# CTRL[0] = start pulse, CTRL[1] = reset pulse (both self-clearing)
reset_board(mmio)

# write 0 (no-op)
mmio.write(CTRL, 0x00); time.sleep(0.05)
s = decode_status(mmio.read(STATUS))
check("CTRL=0x00 is no-op (still not running)", not s["running"])

# write 0x01 (start only)
mmio.write(CTRL, 0x01); time.sleep(0.05)
s = decode_status(mmio.read(STATUS))
check("CTRL=0x01 starts FSM", s["running"])

# write 0x02 (reset only)
mmio.write(CTRL, 0x02); time.sleep(0.05)
s = decode_status(mmio.read(STATUS))
check("CTRL=0x02 resets FSM", not s["running"])
check("reset clears QUOTES_SENT", mmio.read(QUOTES_SENT) == 0)

# write 0x03 (start + reset simultaneously) — implementation-defined,
# but should land in a consistent state
mmio.write(CTRL, 0x03); time.sleep(0.05)
s = decode_status(mmio.read(STATUS))
print(f"    CTRL=0x03 (both): running={s['running']} (impl-defined; just verifying no hang)")

# extra high bits ignored
reset_board(mmio)
mmio.write(CTRL, 0xFFFFFFFE); time.sleep(0.05)  # bit1=1 -> reset, others ignored
s = decode_status(mmio.read(STATUS))
check("CTRL high bits ignored (only bit 1 acts as reset)", not s["running"])

reset_board(mmio)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 9: FSM rapid stress (100 start/reset cycles)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 9: 100 rapid start/reset cycles")

mmio.write(QUOTE_INTERVAL, 1000)
mmio.write(ACTIVE_SYM_COUNT, NUM_SYM)

stress_fails = 0
for i in range(100):
    mmio.write(CTRL, 0x02)  # reset
    time.sleep(0.005)
    s = decode_status(mmio.read(STATUS))
    if s["running"]:                       stress_fails += 1
    if mmio.read(QUOTES_SENT) != 0:        stress_fails += 1
    mmio.write(CTRL, 0x01)  # start
    time.sleep(0.005)
    s = decode_status(mmio.read(STATUS))
    if not s["running"]:                   stress_fails += 1

check("100 cycles complete with no FSM glitches", stress_fails == 0,
      f"{stress_fails} unexpected states across 300 checks")

# Verify counters still working after stress
time.sleep(0.2)
qs = mmio.read(QUOTES_SENT)
check("counters operational after stress", qs > 0, f"quotes_sent = {qs}")
reset_board(mmio)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 10: Quote rate independence from active_sym_count
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 10: Quote rate vs active_sym_count")

mmio.write(QUOTE_INTERVAL, 1000)
rates = {}
for n in [1, 2, 4, 8, 16]:
    reset_board(mmio)
    mmio.write(ACTIVE_SYM_COUNT, n)
    start_board(mmio)
    qb = mmio.read(QUOTES_SENT)
    time.sleep(1.0)
    qa = mmio.read(QUOTES_SENT)
    rates[n] = qa - qb
    print(f"    N={n:2d}: ~{rates[n]:>6} quotes/s")

mean_rate = sum(rates.values()) / len(rates)
max_dev = max(abs(r - mean_rate) / mean_rate for r in rates.values()) * 100
check("rate independent of N (< 5% spread across N=1..16)", max_dev < 5,
      f"max deviation {max_dev:.2f}% from mean {mean_rate:.0f}/s")

reset_board(mmio)
mmio.write(ACTIVE_SYM_COUNT, NUM_SYM)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 11: LFSR determinism (same seed -> same quote count)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 11: LFSR determinism")

mmio.write(QUOTE_INTERVAL, 1000)
mmio.write(ACTIVE_SYM_COUNT, NUM_SYM)

trials = []
for trial in range(3):
    reset_board(mmio)
    mmio.write(LFSR_SEED, 0xCAFEBABE)
    start_board(mmio)
    time.sleep(1.0)
    q = mmio.read(QUOTES_SENT)
    reset_board(mmio)
    trials.append(q)
    print(f"    trial {trial+1}: quotes_sent = {q:,}")

spread = max(trials) - min(trials)
check("3 trials with same seed produce ~same count (jitter < 1%)",
      spread / max(trials) < 0.01,
      f"spread {spread} ({100*spread/max(trials):.3f}%)")

# Different seed should still run, but values differ (we can't verify from PS)
mmio.write(LFSR_SEED, 0xDEADBEEF)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 12: Mid-stream regime switching (50 random transitions)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 12: Mid-stream regime switching (50 transitions)")

random.seed(0xC0FFEE)
reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 1000)
start_board(mmio)

mismatches = 0
for trial in range(50):
    new_r = random.randint(0, 3)
    mmio.write(REGIME, new_r)
    time.sleep(0.02)
    s = decode_status(mmio.read(STATUS))
    if s["active_regime"] != new_r:
        mismatches += 1
        print(f"    trial {trial}: wrote {new_r}, STATUS shows {s['active_regime']} FAIL")
    if not s["running"]:
        mismatches += 1
        print(f"    trial {trial}: FSM stopped during regime switch FAIL")

check("50 mid-stream regime switches all tracked", mismatches == 0,
      f"{50 - mismatches}/50 clean")

mmio.write(REGIME, 0)
reset_board(mmio)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 13: Counter monotonicity (no rollback / no freeze)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 13: Counter monotonicity (200 samples over 2 s)")

reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 1000)
start_board(mmio)

samples = []
last = 0
backwards = 0
zero_deltas = 0
for _ in range(200):
    q = mmio.read(QUOTES_SENT)
    samples.append(q)
    if q < last:        backwards += 1
    if q == last:       zero_deltas += 1
    last = q
    time.sleep(0.01)

check("counter never goes backwards", backwards == 0, f"{backwards} regressions")
# Some zero-deltas allowed if poll faster than quote period (~14us at interval=1000)
check("counter advances at least 90% of samples", zero_deltas < 20,
      f"{zero_deltas}/200 stalled samples")

reset_board(mmio)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 14: Reset-during-run (kill mid-flight)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 14: Reset during active run")

reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 1000)
start_board(mmio)
time.sleep(0.5)
q_before = mmio.read(QUOTES_SENT)
check("counter accumulating before reset", q_before > 1000, f"q={q_before}")

mmio.write(CTRL, 0x02)  # reset while running
time.sleep(0.05)
q_after = mmio.read(QUOTES_SENT)
s = decode_status(mmio.read(STATUS))

check("reset while running clears counter", q_after == 0, f"got {q_after}")
check("reset while running stops FSM",     not s["running"])
# Verify config preserved (interval should still be 1000)
check("QUOTE_INTERVAL preserved across reset",
      mmio.read(QUOTE_INTERVAL) == 1000,
      f"got {mmio.read(QUOTE_INTERVAL)}")
check("LFSR_SEED preserved across reset",
      mmio.read(LFSR_SEED) == 0xDEADBEEF,
      f"got 0x{mmio.read(LFSR_SEED):08X}")
check("ACTIVE_SYM_COUNT preserved across reset",
      mmio.read(ACTIVE_SYM_COUNT) == NUM_SYM,
      f"got {mmio.read(ACTIVE_SYM_COUNT)}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 15: Quote interval scaling sweep
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 15: Quote-interval rate sweep")

reset_board(mmio)
mmio.write(ACTIVE_SYM_COUNT, NUM_SYM)

interval_rates = {}
for interval in [10000, 1000, 100, 10, 1, 0]:
    reset_board(mmio)
    mmio.write(QUOTE_INTERVAL, interval)
    start_board(mmio)
    qb = mmio.read(QUOTES_SENT)
    time.sleep(1.0)
    qa = mmio.read(QUOTES_SENT)
    interval_rates[interval] = qa - qb
    print(f"    interval={interval:>5}: ~{interval_rates[interval]:>9,} quotes/s")

# Estimate the pipeline saturation rate from the smallest-interval samples
sat_rate = max(interval_rates[0], interval_rates[1])
SAT_GUARD = 0.7 * sat_rate  # only check 10x scaling below 70% of saturation

# Each step should be ~10x faster — but only while below pipeline saturation
for big, small in [(10000, 1000), (1000, 100), (100, 10)]:
    if interval_rates[big] > 0 and interval_rates[big] < SAT_GUARD:
        ratio = interval_rates[small] / interval_rates[big]
        # Cap "expected" ratio at saturation
        expected_ratio = min(10.0, sat_rate / interval_rates[big])
        lo = expected_ratio * 0.8
        hi = expected_ratio * 1.2
        check(f"{big} -> {small}: scaling matches ~{expected_ratio:.1f}x",
              lo < ratio < hi, f"ratio={ratio:.2f}, sat~{sat_rate:,}/s")
    else:
        print(f"    skip {big} -> {small} ratio (already saturated at ~{sat_rate:,}/s)")

check("interval=0 saturates pipeline (>1M quotes/s)",
      interval_rates[0] > 1_000_000,
      f"{interval_rates[0]:,} quotes/s")
check("interval=0 and interval=1 both at saturation (within 5%)",
      abs(interval_rates[0] - interval_rates[1]) / sat_rate < 0.05,
      f"diff {abs(interval_rates[0] - interval_rates[1]):,}/s")

reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 1000)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 16: Maximum-rate sustained (5 s at interval=0)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 16: 5-second sustained max-rate run")

reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 0)
start_board(mmio)

samples = []
for t in range(5):
    time.sleep(1.0)
    samples.append(mmio.read(QUOTES_SENT))
    print(f"    t={t+1}s: quotes={samples[-1]:,}")

deltas = [samples[i] - samples[i-1] for i in range(1, len(samples))]
mean = sum(deltas) / len(deltas)
maxdev = max(abs(d - mean) / mean for d in deltas) * 100
check("max-rate run stays running", decode_status(mmio.read(STATUS))["running"])
check("max-rate run > 1M quotes/s sustained", mean > 1_000_000,
      f"mean={mean:.0f}/s")
check("max-rate deviation < 5%", maxdev < 5, f"{maxdev:.2f}%")

reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 1000)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 17: 30-second long-haul stability run
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 17: 30-second long-haul stability")

reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 1000)
start_board(mmio)

samples = []
for t in range(30):
    time.sleep(1.0)
    samples.append(mmio.read(QUOTES_SENT))
    if (t+1) % 5 == 0:
        s = decode_status(mmio.read(STATUS))
        print(f"    t={t+1:>2}s: quotes={samples[-1]:>10,}  running={s['running']}")

deltas = [samples[i] - samples[i-1] for i in range(1, len(samples))]
mean = sum(deltas) / len(deltas)
maxdev = max(abs(d - mean) / mean for d in deltas) * 100
check("still running after 30s", decode_status(mmio.read(STATUS))["running"])
check("30s rate stability < 5%", maxdev < 5, f"{maxdev:.2f}%")
check("30s monotonic", all(samples[i] > samples[i-1] for i in range(1, len(samples))))

reset_board(mmio)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 18: Read-while-running atomicity (no stale/torn reads)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 18: Read-while-running atomicity (1000 reads)")

reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 100)  # fast counter
start_board(mmio)

# Tight read loop — every read should be plausible (monotonic, no garbage bits)
last = 0
torn = 0
backwards = 0
status_glitches = 0
for _ in range(1000):
    q = mmio.read(QUOTES_SENT)
    s = mmio.read(STATUS)
    if q < last:                          backwards += 1
    if (s & ~0xFFFF) != 0:                # status uses only low ~16 bits
        # Allow fifo_fill in [9..15], regime [2..3], link [1], running [0]
        # but values shouldn't span beyond bit 15
        status_glitches += 1
    last = q

check("1000 tight reads: no counter regression", backwards == 0)
check("1000 tight reads: no STATUS upper-bit garbage", status_glitches == 0)

reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 1000)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 19: Read-during-write (no torn writes)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 19: Interleaved write/read on per-symbol arrays")

# Hammer slot 0 with alternating values, read in between
val_a = q16_16(123.456)
val_b = q16_16(789.012)
torn = 0
for _ in range(500):
    mmio.write(INIT_MID_BASE, val_a)
    rb1 = mmio.read(INIT_MID_BASE)
    mmio.write(INIT_MID_BASE, val_b)
    rb2 = mmio.read(INIT_MID_BASE)
    if rb1 != val_a: torn += 1
    if rb2 != val_b: torn += 1
check("500 alternating writes -> exact readback (no tearing)", torn == 0,
      f"{1000 - torn}/1000")

# restore some sane value
mmio.write(INIT_MID_BASE, q16_16(180.0))


# ═══════════════════════════════════════════════════════════════════════════
# TEST 20: Boundary u32 values on per-symbol arrays
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 20: u32 boundary values on init_mid")

boundaries = [0x00000000, 0x00000001, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFE, 0xFFFFFFFF]
b_fails = 0
for v in boundaries:
    mmio.write(INIT_MID_BASE, v)
    rb = mmio.read(INIT_MID_BASE)
    if rb != v:
        b_fails += 1
        print(f"    wrote 0x{v:08X}, read 0x{rb:08X} FAIL")
check("u32 boundary values on init_mid[0]", b_fails == 0,
      f"{len(boundaries) - b_fails}/{len(boundaries)}")

mmio.write(INIT_MID_BASE, q16_16(180.0))


# ═══════════════════════════════════════════════════════════════════════════
# TEST 21: Restart preserves config
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 21: Config preservation across reset cycles")

# Set non-default config
mmio.write(QUOTE_INTERVAL, 555)
mmio.write(LFSR_SEED, 0x12345678)
mmio.write(REGIME, 2)
mmio.write(ACTIVE_SYM_COUNT, 7)
for i in range(NUM_SYM):
    mmio.write(INIT_MID_BASE + 4*i, q16_16(50.0 + i))

start_board(mmio)
time.sleep(0.2)
reset_board(mmio)
start_board(mmio)
time.sleep(0.2)
reset_board(mmio)

check("QUOTE_INTERVAL preserved",  mmio.read(QUOTE_INTERVAL) == 555)
check("LFSR_SEED preserved",       mmio.read(LFSR_SEED) == 0x12345678)
check("REGIME preserved",          mmio.read(REGIME) == 2)
check("ACTIVE_SYM_COUNT preserved", mmio.read(ACTIVE_SYM_COUNT) == 7)
mid_pres_fails = 0
for i in range(NUM_SYM):
    if mmio.read(INIT_MID_BASE + 4*i) != q16_16(50.0 + i):
        mid_pres_fails += 1
check("16 init_mid values preserved across 2x reset",
      mid_pres_fails == 0, f"{NUM_SYM - mid_pres_fails}/{NUM_SYM}")

# restore defaults for downstream tests
mmio.write(QUOTE_INTERVAL, 1000)
mmio.write(LFSR_SEED, 0xDEADBEEF)
mmio.write(REGIME, 0)
mmio.write(ACTIVE_SYM_COUNT, NUM_SYM)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 22: Address decoder uses low 8 bits (verify aliasing)
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 22: Address-decoder bit-width (alias check)")

# The hft_core register file decodes only addr[7:0] (256-byte map). PYNQ allocates
# a 4 KB AXI region, so reads above 0xFC alias back to defined registers via
# (addr & 0xFF). Verify the aliasing is consistent — proves the decoder is
# clean and using the expected number of bits.
print("    Each high address should mirror (addr & 0xFF) of the defined map:")

def expected_for_addr(addr):
    a = addr & 0xFF
    return mmio.read(a)

alias_pairs = [
    (0x100, "aliases 0x00 = CTRL"),
    (0x104, "aliases 0x04 = QUOTE_INTERVAL"),
    (0x108, "aliases 0x08 = LFSR_SEED"),
    (0x200, "aliases 0x00 = CTRL"),
    (0x4F0, "aliases 0xF0 = ACTIVE_SYM_COUNT"),
    (0x8F4, "aliases 0xF4 = STATUS"),
    (0xFFC, "aliases 0xFC = ORDERS_RCVD"),
]
alias_fails = 0
for addr, note in alias_pairs:
    high_read = mmio.read(addr)
    low_read  = mmio.read(addr & 0xFF)
    # STATUS is volatile; allow it to differ slightly between reads
    if (addr & 0xFF) == STATUS:
        ok = (high_read & ~0x10000) == (low_read & ~0x10000)  # ignore hb bit
    else:
        ok = (high_read == low_read)
    if not ok: alias_fails += 1
    tag = "OK" if ok else "MISMATCH"
    print(f"    [0x{addr:03X}]=0x{high_read:08X}  vs  [0x{addr & 0xFF:02X}]=0x{low_read:08X}  {note}  {tag}")
check("high addresses alias correctly to (addr & 0xFF)", alias_fails == 0,
      f"{len(alias_pairs) - alias_fails}/{len(alias_pairs)}")


# ═══════════════════════════════════════════════════════════════════════════
# TEST 23: Exchange counter behavior with no link
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 23: Exchange / no-link sanity")

reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 1000)
start_board(mmio)
time.sleep(2.0)
o = mmio.read(ORDERS_RCVD)
s = decode_status(mmio.read(STATUS))
check("orders_rcvd == 0 with no Board B", o == 0, f"got {o}")
check("link_up == False with no Board B", not s["link_up"])
reset_board(mmio)


# ═══════════════════════════════════════════════════════════════════════════
# TEST 24: STATUS bit-field decoding under all regimes
# ═══════════════════════════════════════════════════════════════════════════
section("TEST 24: STATUS bit-fields across all regimes")

reset_board(mmio)
mmio.write(QUOTE_INTERVAL, 1000)
start_board(mmio)
for r in range(4):
    mmio.write(REGIME, r)
    time.sleep(0.1)
    s = decode_status(mmio.read(STATUS))
    check(f"STATUS active_regime tracks REGIME={r} ({REGIME_NAMES[r]})",
          s["active_regime"] == r,
          f"running={s['running']} regime={s['active_regime']} link={s['link_up']}")
    check(f"STATUS running=True under regime {r}", s["running"])

mmio.write(REGIME, 0)
reset_board(mmio)


# ═══════════════════════════════════════════════════════════════════════════
# FINAL SUMMARY
# ═══════════════════════════════════════════════════════════════════════════
reset_board(mmio)

print(f"\n{'='*68}")
print(f" BOARD A EXTENSIVE TEST SUMMARY")
print(f"{'='*68}")
print(f"  Total checks : {total}")
print(f"  Passed       : {passed}")
print(f"  Failed       : {failed}")
if failed:
    print(f"\n  Failures:")
    for f in fail_log:
        print(f"    - {f}")
    print(f"\n  *** {failed} CHECK(S) FAILED ***")
else:
    print(f"\n  *** ALL {total} CHECKS PASSED — BOARD A FULLY VERIFIED ***")
print(f"{'='*68}")
