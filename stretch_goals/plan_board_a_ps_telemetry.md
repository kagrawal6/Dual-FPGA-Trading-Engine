# Plan — Board A PS telemetry to laptop (spec stretch)

**Not required for the core demo.** Board B’s UART telemetry plus occasional **`config_symbols.py --status`** over SSH to Board A is enough for most capstone demos. This document is only if you want **continuous** Board A stats on the **laptop dashboard** without SSH.

**See also:** [`board_a_laptop_setup_and_prompt_demo.md`](board_a_laptop_setup_and_prompt_demo.md) for laptop ↔ Board A connection and interactive prompts.

---

**Goal:** Stream **Board A** statistics (quotes sent, link errors, optional FIFO depth) to the laptop **in addition to** Board B telemetry.  
**Spec:** `docs/updated_design_specification.md` §5.5.3 (Stretch Goal: Board A PS Telemetry).

---

## Option comparison (from spec)

| Option | Effort | Notes |
|--------|--------|------|
| **A — Second USB-UART** | Low | Duplicate Board B approach: second cable, second COM port, dashboard merges streams |
| **B — SSH polling** | Medium | Laptop polls Board A over Ethernet; dashboard ingests stdout |
| **C — PMOD tunnel** | Medium–High | New frame type Board A → Board B; Board B JSON includes A’s counters |

---

## Recommended path for class demo — Option A

### Steps

1. **Enable** UART on Board A PS in Vivado if not already (match Board B BSP).  
2. **Python on Board A:** small daemon that periodically **MMIO-reads** AXI counters and prints **one JSON line** per sample (mirror `telemetry_server.py` style).  
3. **Laptop:** extend `dashboard.py` to open **two serial ports** (CLI `--port-a`, `--port-b`) or use threading like `serial_reader.py` TODO.  
4. **Dashboard UI:** optional small panel “Board A: quotes/sec, link errors.”

### Steps for Option C (single cable)

1. **Define** new **MSG_*** type or side channel in link protocol (requires **both** RTL and spec update).  
2. **Board A:** mux periodic stats into TX path when idle (careful not to starve quotes).  
3. **Board B:** parse, merge into telemetry dict.

## Exit criteria

- [ ] Laptop shows live Board A health without manual SSH `peek` at registers.  
- [ ] Document cable count in demo setup (1 vs 2 USB).
