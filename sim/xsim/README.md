# Vivado XSim simulation flow

This folder is an **alternative** to the ModelSim flow in `sim/`. It uses
Vivado's bundled simulator (XSim), which has a few important advantages over
the ModelSim ASE 2020.1 Starter Edition we've been using:

| Concern | ModelSim ASE Starter | Vivado XSim |
| ------- | -------------------- | ----------- |
| RTL line-count limit | ~10K lines (throttles) | None |
| `vopt` (optimizer) overhead with NN modules | Severe (multi-minute hangs) | Negligible |
| License | Free, but throttled | Free with any Vivado install |
| Wave / debug GUI | `vsim -gui` | `xsim -gui` |

If your installed Vivado works for the build flow, XSim already comes with it.

---

## Prerequisites

**The runner scripts auto-locate Vivado** — you normally don't need to source
anything manually. On first invocation each script calls
`_load_vivado_env.ps1`, which:

1. Checks if `xvlog` is already on `PATH` (and skips if so),
2. Otherwise probes these install roots in order:
   - `$env:VIVADO_ROOT` (manual override)
   - `C:\AMDDesignTools\<ver>\Vivado` ← matches this machine (2025.2)
   - `C:\Xilinx\Vivado\<ver>`
   - `C:\AMD\Vivado\<ver>`
   - `D:\AMDDesignTools\<ver>\Vivado`, `D:\Xilinx\Vivado\<ver>`,
     `D:\AMD\Vivado\<ver>`
3. Picks the highest version, runs its `settings64.bat`, and copies the
   resulting environment back into your PowerShell session.

### If auto-detection fails

Either Vivado is in an unusual location, or the install layout is unexpected.
Set `$env:VIVADO_ROOT` to the folder containing `settings64.bat` and re-run:

```powershell
$env:VIVADO_ROOT = 'C:\AMDDesignTools\2025.2\Vivado'
.\run_board_b.ps1
```

### Manual sourcing (if you prefer)

```powershell
& "C:\AMDDesignTools\2025.2\Vivado\settings64.bat"
xvlog -version    # should print "Vivado Simulator v2025.2"
```

---

## Layout

```
sim/xsim/
├── sources.prj         # one-line-per-file source manifest (mirrors compile_all.do)
├── run_board_b.ps1     # compiles + runs all Board B leaf TBs (incl. tb_nn_inference)
├── run_top.ps1         # compiles + runs board_a_top, board_b_top, pipeline, system_top
├── README.md           # this file
├── xsim.dir/           # generated work library (auto-created, can delete)
└── xsim_logs/          # per-test logs + SUMMARY.txt (auto-created)
```

`sources.prj` is consumed by `xvlog -prj sources.prj` in one shot. Compile
order follows `sim/compile_all.do` exactly.

---

## Running

### Board B leaf tests (~13 TBs, including the NN unit test)

```powershell
cd sim/xsim
.\run_board_b.ps1                    # run them all
.\run_board_b.ps1 tb_nn_inference    # run a single TB
```

### Top-level / system tests

```powershell
cd sim/xsim
.\run_top.ps1                        # tb_board_a_top, tb_board_b_top,
                                     # tb_board_b_pipeline, tb_system_top
.\run_top.ps1 tb_board_b_top         # single TB
```

Both scripts:

1. Wipe any prior `xsim.dir/` build,
2. Compile **all** SV sources once (`xvlog -sv -prj sources.prj`),
3. For each TB: `xelab` -> `xsim ... -R` (run-all),
4. Tee output to `xsim_logs/<tb_name>.log`,
5. Scan logs for the same PASS/FAIL banner patterns that `sim/run_all*.do` use,
6. Print a colored summary and write `xsim_logs/SUMMARY.txt`.

Scripts exit non-zero if any test FAILed / ERROred / produced no banner.

---

## Interactive debugging

If a TB fails and you want waveforms:

```powershell
cd sim/xsim
xvlog -sv -prj sources.prj
xelab -debug typical -s mydbg work.tb_system_top -timescale 1ns/1ps
xsim mydbg -gui          # opens the Vivado simulator GUI
```

In the GUI you can drag signals into the wave window, set
`add_force` / `run`, etc. — the same workflow as ModelSim.

---

## Why the `-relax` and `-timescale 1ns/1ps` flags?

* `-relax` — XSim is stricter than ModelSim about a few SystemVerilog corner
  cases (e.g. legality of certain `task` invocations from `always_comb`). It
  downgrades these to warnings, matching the ModelSim flow.
* `-timescale 1ns/1ps` — fallback for any source file that lacks an explicit
  `` `timescale ``. We *do* have it in `hft_pkg.sv`, but XSim resolves
  timescales per-file rather than globally, so this guarantees consistency.

---

## Common issues

| Symptom | Cause | Fix |
| ------- | ----- | --- |
| `'xvlog' is not recognized` | Vivado env not sourced | Run `settings64.bat` first |
| `ERROR: [VRFC 10-2945] type 'price_t' is not declared` | Compile order wrong | Check that `hft_pkg.sv` is the first entry in `sources.prj` |
| `ELAB FAILED` on `tb_board_b_top` | Stale `xsim.dir/` after RTL change | The runners auto-clean it; if running manually, `Remove-Item -Recurse -Force xsim.dir` |
| Test prints "UNKNOWN (no PASS/FAIL banner)" | TB ran fine but never printed an explicit banner | Add `$display("ALL TESTS PASSED");` at the end, or check `xsim_logs/<tb>.log` manually |
