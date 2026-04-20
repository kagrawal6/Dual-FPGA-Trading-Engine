# Plan — G8 High-speed UART telemetry (921600 baud)

**Goal:** Increase UART bandwidth so larger JSON payloads (extra fields from G5/G4/NN) still fit **20 Hz** or faster updates.  
**Spec:** `docs/updated_design_specification.md` §8.1 (G8 row), §5.x telemetry discussion.

---

## Phase 1 — PS / BSP side

1. **Locate** Zynq PS UART configuration ( Vivado **Zynq PS** IP: UART0 baud divisor, or PYNQ/Linux `stty` / device tree if applicable).  
2. **921600** is a standard rate; confirm **clock** to UART allows the divisor (check reference manual).  
3. **Linux:** set serial port to 921600 on both **Board B** (telemetry) and **laptop** reader.

## Phase 2 — Python

1. **`telemetry_server.py`:** CLI `--baud` default bump or override (keep **115200** as fallback for cheap USB adapters).  
2. **`dashboard.py` / `serial_reader.py`:** same baud; document USB cable quality (high baud can be flaky on long cables).

## Phase 3 — Bandwidth math

1. Estimate **worst-case JSON** size with all stretch fields (positions, vol, strategy, histogram bins).  
2. Verify **921600 / 10 bits ≈ 92k chars/s** >> your peak message rate.

## Phase 4 — Test

1. **Loopback** USB adapter at 921600 (optional).  
2. **On hardware:** stress telemetry at 20 Hz + extra fields; watch for parse errors / framing.

## Exit criteria

- [ ] Stable JSON lines at 921600 for ≥10 min stress.  
- [ ] README lists **required** baud for full demo vs fallback.
