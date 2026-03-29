# TODO

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
