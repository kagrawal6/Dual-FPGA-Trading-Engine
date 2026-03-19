# Verilator terminal PASS excerpts

Combined log snippets for **`tb_lfsr32`**, **`tb_debounce`**, and **`tb_link_rx`**.  
Each block is **11 lines**: five lines before the `PASS` line, the `PASS` line, then five lines after (last line may be blank).

You can keep this file here under `docs/images/`, convert it to PDF/screenshot locally, or replace these lines with your own terminal copy-paste.

---

## tb_lfsr32 (11 lines)

```text
c++  -Wl,-U,__Z15vl_time_stamp64v,-U,__Z13sc_time_stampv   verilated.o verilated_vcd_c.o verilated_timing.o verilated_threads.o Vtb_lfsr32__ALL.a    -pthread -lpthread   -o Vtb_lfsr32
rm Vtb_lfsr32__ALL.verilator_deplist.tmp
- V e r i l a t i o n   R e p o r t: Verilator 5.046 2026-02-28 rev vUNKNOWN-built20260228
- Verilator: Built from 0.083 MB sources in 5 modules, into 0.074 MB in 11 C++ files needing 0.000 MB
- Verilator: Walltime 9.054 s (elab=0.007, cvt=0.021, bld=9.004); cpu 0.027 s on 1 threads; allocated 10.844 MB
tb_lfsr32: PASS (all checks passed, VCD: tb_lfsr32.vcd)
- tb/shared/tb_lfsr32.sv:180: Verilog $finish
- S i m u l a t i o n   R e p o r t: Verilator 5.046 2026-02-28
- Verilator: $finish at 5us; walltime 0.003 s; speed 6.283 ms/s
- Verilator: cpu 0.001 s on 1 threads; allocated 2 MB

```

## tb_debounce (11 lines)

```text
c++  -Wl,-U,__Z15vl_time_stamp64v,-U,__Z13sc_time_stampv   verilated.o verilated_vcd_c.o verilated_timing.o verilated_threads.o Vtb_debounce__ALL.a    -pthread -lpthread   -o Vtb_debounce
rm Vtb_debounce__ALL.verilator_deplist.tmp
- V e r i l a t i o n   R e p o r t: Verilator 5.046 2026-02-28 rev vUNKNOWN-built20260228
- Verilator: Built from 0.056 MB sources in 3 modules, into 0.063 MB in 9 C++ files needing 0.000 MB
- Verilator: Walltime 7.843 s (elab=0.001, cvt=0.007, bld=7.825); cpu 0.015 s on 1 threads; allocated 10.500 MB
tb_debounce: PASS (all checks passed, VCD: tb_debounce.vcd)
- new_implementation/tb/shared/tb_debounce.sv:103: Verilog $finish
- S i m u l a t i o n   R e p o r t: Verilator 5.046 2026-02-28
- Verilator: $finish at 2us; walltime 0.000 s; speed 4.103 ms/s
- Verilator: cpu 0.000 s on 1 threads; allocated 2 MB

```

## tb_link_rx (11 lines)

```text
c++  -Wl,-U,__Z15vl_time_stamp64v,-U,__Z13sc_time_stampv   verilated.o verilated_vcd_c.o verilated_timing.o verilated_threads.o Vtb_link_rx__ALL.a    -pthread -lpthread   -o Vtb_link_rx
rm Vtb_link_rx__ALL.verilator_deplist.tmp
- V e r i l a t i o n   R e p o r t: Verilator 5.046 2026-02-28 rev vUNKNOWN-built20260228
- Verilator: Built from 0.096 MB sources in 5 modules, into 0.130 MB in 11 C++ files needing 0.001 MB
- Verilator: Walltime 8.322 s (elab=0.002, cvt=0.011, bld=8.298); cpu 0.022 s on 1 threads; allocated 11.547 MB
tb_link_rx: PASS (all tests passed)
- new_implementation/tb/link/tb_link_rx.sv:219: Verilog $finish
- S i m u l a t i o n   R e p o r t: Verilator 5.046 2026-02-28
- Verilator: $finish at 4us; walltime 0.001 s; speed 3.452 ms/s
- Verilator: cpu 0.001 s on 1 threads; allocated 2 MB

```
