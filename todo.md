# TODO

## Resolved (this session)

- [x] **CRITICAL: `feature_compute.sv` beta truncation** — `beta[15:0]` dropped MSB; when `ema_alpha=0`, beta=65536 wraps to 0. Fixed: use `{15'b0, beta}`.
- [x] **CRITICAL: `order_manager.sv` held order drop** — simultaneous held-release + new-order NBA race silently lost the held frame. Fixed: 3-branch priority (direct → hold → reuse-freeing-slot).
- [x] **CRITICAL: `risk_manager.sv` pending count race** — simultaneous `signal_valid` + `fill_valid` on same symbol/side caused last-NBA-wins. Fixed: merged delta computation in both blocks.
- [x] **HIGH: Board B PS incomplete** — `telemetry_server.py` had all config hardcoded, no CLI, no reset/status, no Ctrl+C. Fixed: full `argparse`, `--reset`, `--status`, decoded STATUS, graceful shutdown.
- [x] **HIGH: `register_map.py` wrong addresses** — assumed 4 symbols; CASH_LO/HI, HIST, LAT addresses all wrong. Fixed: matches RTL 16-symbol layout.
- [x] **HIGH: `MAX_LOSS` unit mismatch** — PS wrote Q16.16 ($6.5M effective limit), RTL default was Q16.16. Fixed: integer dollars in RTL default, PS, and golden model.
- [x] **HIGH: `MAX_ORDER_RATE` default mismatch** — RTL default was 10000, spec/PS says 1000. Fixed: aligned RTL and golden model to 1000.
- [x] **HIGH: `link_up` sticky in `link_rx.sv`** — never deasserted after first valid frame. Fixed: deasserts on `counter_clr`, truncated frame, or invalid msg_type.
- [x] **MEDIUM: `board_b_axi_regs.sv` STATUS width** — concatenation was 31 bits, not 32. Fixed: `25'b0` padding.
- [x] **MEDIUM: `--write-sector-id` off by default** — critical for 3-tier noise model. Fixed: default-on.
- [x] **MEDIUM: Board A PS no status readback** — Added `read_board_a_status()`, `--status`, post-config print.
- [x] **MEDIUM: Board A PS no reset** — Added `--reset` (CTRL[1] pulse).

---

## Medium priority — remaining

### RTL

- [ ] **Board A: no RX→exchange FIFO** — `link_rx` output directly feeds `exchange_lite`. If exchange is busy (processing a previous order or waiting for fill to be consumed), the incoming order pulse is silently dropped. A 2–4 deep elastic buffer between `link_rx` and `exchange_lite` in `board_a_top.sv` would prevent this. Low risk at normal quote rates since Board B sends orders much slower than link throughput, but a burst of orders could trigger loss.

- [ ] **Board A: AXI address space full** — 8-bit address bus (256 bytes) is completely packed. `fills_sent`, `rejects_sent`, and `link_errors` counters are wired into `board_a_axi_regs` as inputs but have no read addresses. Widening `C_S_AXI_ADDR_WIDTH` to 10 bits (1024 bytes) would allow adding these and future registers.

- [ ] **Board A: no AXI stop pulse** — only physical button can stop the FSM (`ctrl_stop_pulse`). CTRL register provides start (bit 0) and reset (bit 1) but no stop (bit 2). Adding a stop bit requires a 1-line change in `board_a_axi_regs.sv` and `board_a_top.sv`.

- [ ] **Board B: `position_tracker.sv` signed product overflow** — `$signed(product)` where `product` is `logic [47:0]` (unsigned). If `frame_price * frame_qty >= 2^47` (~$32K Q16.16 at max qty), bit 47 is set, causing `$signed(product)` to go negative. SELL fills would subtract from cash instead of adding. Unlikely at normal simulation ranges but a latent overflow for extreme prices.

- [ ] **Board B: only mean-reversion strategy implemented** — `active_strategy` is computed but `strategy_engine` ignores it. `STRAT_MOMENTUM`, `STRAT_NN`, `STRAT_AUTO` defined in `hft_pkg` but unimplemented.

- [ ] **Board B: `demux_errors` not in AXI register map** — Frame demux errors are counted in `msg_demux` but not wired to any readable AXI register. Software cannot observe them.

- [ ] **Link: no CRC/checksum on frames** — A single bit-flip on the PMOD could corrupt price/quantity fields without detection. Only msg_type validation catches totally garbled frames.

### Testbenches

- [ ] **`tb_board_b_pipeline.sv` is empty** — Contains only `#1000; $finish;`. Needs real stimulus: drive synthetic QUOTE frames through the full pipeline (quote_book → feature_compute → strategy_engine → risk_manager → order_manager), verify ORDER frames emerge with golden model values.

- [ ] **`tb_system_top.sv` uses stub** — Uses `board_b_top_stub` instead of real `board_b_top`. Should test full Board A → Board B → Board A data flow with AXI configuration on both sides.

- [ ] **No TB for `board_a_axi_regs.sv`** — Only indirectly tested via `tb_board_a_top`. Needs dedicated AXI register read/write verification.

- [ ] **`exchange_plus.sv` has no TB and is not compiled** — Either add a TB and integrate it, or remove the file if deprecated.

- [ ] **No run scripts for shared/link TBs** — `run_all_board_a.do` and `run_all_board_b.do` exist, but there is no `run_all_shared.do` or `run_all_link.do`.

- [ ] **No run script for `tb_system_top`** — System-level test is compiled but has no runner script.

### Documentation

- [ ] **Design spec D.2 has stale register addresses** — Board B register table still shows 4-symbol layout (CASH_LO=0x68, HIST_BIN0=0x80). Should be updated to 16-symbol addresses (CASH_LO=0x98, HIST_BASE=0xA0, etc.).

- [ ] **Design spec D.2 STATUS bit ordering wrong** — Spec says `[2:0]=fsm_state, [3]=link_up, [4]=risk_halt`. RTL is actually `[1:0]=active_strategy, [4:2]=fsm_state, [5]=link_up, [6]=risk_halt`.

---

## Board A — Update Testbenches

All Board A testbenches need to be updated to reflect the current RTL implementation
(OU pull-back, 3-tier noise, 16-symbol universe, sector-aware pricing, per-symbol
AXI configuration, 2-FF synchronizer in link_tx, etc.).

### Testbenches to update

- [ ] `tb/board_a/tb_market_sim.sv` — verify OU pull-back keeps prices near init_mid; test all four regimes
- [ ] `tb/board_a/tb_market_noise_gen.sv` — confirm zero-mean noise, sector population scaling, drift saturation
- [ ] `tb/board_a/tb_exchange_lite.sv` — BUY/SELL fill/reject logic, out-of-range symbol reject, backpressure stall
- [ ] `tb/board_a/tb_tx_arbiter.sv` — fill priority over quote, 1-cycle bubble, backpressure hold
- [ ] `tb/board_a/tb_board_a_ctrl.sv` — debounced buttons, switch regime override, LED/RGB outputs
- [ ] `tb/board_a/tb_board_a_top.sv` — full integration: FSM transitions, lfsr_load, end-to-end quote→order→fill
- [ ] `tb/shared/tb_lfsr32.sv` — seed load, zero-seed remap, deterministic sequence
- [ ] `tb/shared/tb_sync_fifo.sv` — fill/drain, flush, almost_full, simultaneous read+write
- [ ] `tb/shared/tb_debounce.sv` — bounce rejection, stability counter, pulse generation
- [ ] `tb/link/tb_link_tx.sv` — serialization, 2-FF synchronizer on remote_ready, backpressure
- [ ] `tb/link/tb_link_rx.sv` — 2-FF sync, phase alignment, error counting, msg_type validation
- [ ] `tb/link/tb_link_loopback.sv` — link_tx → link_rx round-trip, frame integrity

### Golden model reference cases

Use the golden model (`golden_model/`) to generate expected values for RTL testbenches.
The golden model is bit-accurate for the algorithm and frame formats, making it a reliable
cross-verification reference.

#### Suggested test vectors to extract from golden model

- [ ] **LFSR sequences**: Run `board_a.py` LFSR with known seeds, record first N outputs → compare against `tb_lfsr32` with same seed
- [ ] **Noise generation**: For a known seed + sector assignment, record global/sector/company noise values per tick → compare against `tb_market_noise_gen`
- [ ] **Price evolution**: For a known seed + init_mid + regime, record mid_price trajectory for ~100 ticks → compare against `tb_market_sim` (verifies OU pull-back + noise scaling)
- [ ] **Quote frame packing**: Record raw 128-bit quote frames from golden model → compare bit-for-bit against `tb_market_sim` output
- [ ] **Order matching**: Send known orders at known prices, record fill/reject decisions and fill frames → compare against `tb_exchange_lite`
- [ ] **End-to-end flow**: Run golden model for N cycles, capture the full sequence of quote frames and fill frames → compare against `tb_board_a_top` or `tb_system_top`

#### How to generate test vectors

```bash
cd golden_model
python board_a.py --seed 0xDEADBEEF --regime calm --ticks 100 --dump-vectors vectors/
```

> Note: the `--dump-vectors` CLI is not yet implemented in `board_a.py`.
> When added, it should write CSV or hex files that testbenches can `$readmemh` to load
> expected values for self-checking comparisons.
