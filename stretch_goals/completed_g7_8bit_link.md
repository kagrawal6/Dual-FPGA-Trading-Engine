# G7 — 8-bit link upgrade (completed)

**Status:** Completed by the team (not visible in this repository snapshot).

**Spec reference:** `docs/updated_design_specification.md` §8.7.

## What this stretch delivered

- `LINK_DATA_W = 8` (vs 4) for the PMOD data path.
- **Physical:** Extra PMOD/JAB wiring per the pin tables so `valid` / `ready` move to extension pins when all 8 data lines are used on the main header.
- **Effect:** Roughly **halved** serialization time per frame vs 4-bit; histogram / round-trip latency shifts left.

## Archive checklist (for your own records)

- [ ] RTL: `hft_pkg` / link params, `link_tx` / `link_rx`, tops — consistent `LINK_DATA_W`.
- [ ] XDC: JAB + PMOD pins enabled and match board routing.
- [ ] Bitstreams rebuilt for Board A and Board B; `vivado/package_pynq.tcl` run.
- [ ] Cable loopback or A↔B test at max sustained rate; compare to pre–8-bit latency.

No further step-by-step implementation plan is listed here because the work is done.
