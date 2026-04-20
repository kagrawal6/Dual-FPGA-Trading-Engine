# Plan — Board A / link infrastructure extras (from `todo.md`)

These are **not** named G1–G8 in the spec but are common “stretch” hardening items. Track separately from strategy work.

---

## 1. Elastic buffer: `link_rx` → `exchange_lite`

**Problem:** Order pulse can be dropped if exchange is busy.  
**Plan:**

1. Insert **small sync FIFO** (2–4 entries) between `link_rx` output and `exchange_lite` input in `board_a_top.sv`.  
2. Match **frame** width and backpressure (`ready` to link_rx).  
3. TB: burst orders; assert no loss until FIFO full.

---

## 2. AXI address space + counter readback

**Problem:** 8-bit AXI space full; some counters wired but not mapped.  
**Plan:**

1. Widen `C_S_AXI_ADDR_WIDTH` on Board A (e.g. 9–10 bits) in RTL + BD wrapper.  
2. **Assign** addresses for `fills_sent`, `rejects_sent`, `link_errors`.  
3. Update **`config_symbols.py`** / docs for reads.

---

## 3. AXI stop pulse

**Problem:** Stop only from physical button; no PS stop bit.  
**Plan:**

1. Add **CTRL[2]** (or dedicated register) in `board_a_axi_regs.sv` → `ctrl_stop_pulse` one-shot.  
2. Document pulse width and FSM interaction with `STOPPED`.

---

## 4. Link CRC / checksum

**Problem:** Bit errors on PMOD can corrupt price/qty undetected.  
**Plan:**

1. Choose **CRC8** or **CRC16** over payload + header.  
2. **TX:** append check; **RX:** verify; increment **error** stat on fail.  
3. **Compatibility:** bump protocol version or frame layout — **both** boards must upgrade together.

---

## 5. `exchange_plus.sv` integration

**Problem:** Module exists; not instantiated in `board_a_top`.  
**Plan:**

1. Parameter-gate **features** (partial fill, resting orders, queue).  
2. Swap `exchange_lite` ↔ `exchange_plus` in top; rerun TB + hw.  
3. Update resource / timing reports for report.

---

## Suggested order

1. Elastic buffer (risk reduction).  
2. AXI stop + counter readback (demo UX).  
3. `exchange_plus` (feature).  
4. CRC (protocol change — coordinate with Board B).
