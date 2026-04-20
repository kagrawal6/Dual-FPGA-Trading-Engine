# Board A — laptop connection, prompts, and polished demo flow

This guide answers four things:

0. **Complete development setup** — **§0** below: hardware, host tools, Vivado → bitstream → overlays → Board A filesystem → verify → iteration loops.  
1. **Do you need Board A telemetry?** (Short answer: **no** for the core demo.)  
2. **How to connect your computer to Board A** so you can type at a prompt and have that drive the FPGA.  
3. **Ideas for a good-looking terminal** when an audience is watching — **§3 is the deep dive** (banners, ANSI, `rich`, projector, `ssh -t`).

Related optional stretch (continuous streaming to the laptop): [`plan_board_a_ps_telemetry.md`](plan_board_a_ps_telemetry.md).

---

## 0. Complete development setup — exact steps

Use this section to go from **empty desk** to **editing RTL or Python and running on Board A**. Paths below assume repo root `Dual-FPGA-Trading-Engine/` (adjust if yours differs).

### 0.1 What you need (checklist)

| Item | Purpose |
|------|---------|
| **Board A** (e.g. AUP-ZU3 / PYNQ UltraScale+ image) | Runs Linux + PYNQ; loads `board_a.bit` |
| **Board B** + **2× PMOD ribbons** | Full system: quotes/orders between boards |
| **Development PC** (Windows or macOS or Linux) | Vivado for FPGA; editor; optional `scp`/`rsync` |
| **AMD Vivado** | Version must match what your team uses for this project (same year / IP compatibility) |
| **USB cable(s)** | Board power / serial / gadget Ethernet (per board manual) |
| **Ethernet** (recommended) | Laptop ↔ same LAN as boards for stable **SSH** |
| **Git** | Clone and update `Dual-FPGA-Trading-Engine` |
| **Python 3.10+** on laptop | `sw/laptop/dashboard.py`; local lint/edit of `sw/board_a` |
| **Python on the board** | PYNQ image includes `pynq`; use `python3` |

### 0.2 One-time: get the repository on your development PC

```bash
git clone https://github.com/<your-org-or-fork>/Dual-FPGA-Trading-Engine.git
cd Dual-FPGA-Trading-Engine
```

Confirm Board A RTL and scripts exist:

```bash
ls rtl/board_a/board_a_top.sv sw/board_a/config_symbols.py constraints/hft_top.xdc
```

### 0.3 One-time: install Vivado and confirm the FPGA part

This repo’s Board A Vivado script targets **`xczu3eg-sfvc784-2-e`** (see `vivado/create_board_a.tcl`). Your installed Vivado must support that part.

### 0.4 Build Board A bitstream and hardware handoff (on the development PC)

These steps produce `system_wrapper.bit` and `system.hwh` inside the Vivado project tree, then copy them into `pynq/overlays/` for PYNQ.

**Step A — Start Vivado** (GUI or `vivado` in PATH).

**Step B — Create the Board A project and block design** (once per clean tree, or after deleting `vivado/hft_board_a/`):

```tcl
cd {C:/path/to/Dual-FPGA-Trading-Engine}   ;# use your real path; Tcl uses forward slashes on Windows too
source vivado/create_board_a.tcl
```

Wait until it finishes without errors.

**Step C — Synthesize, implement, generate bitstream** (project must be open — `create_board_a.tcl` leaves it open):

```tcl
source vivado/build.tcl
```

If `build.tcl` reports “no project open”, open the project first:

```tcl
open_project {C:/path/to/Dual-FPGA-Trading-Engine/vivado/hft_board_a/hft_board_a.xpr}
source vivado/build.tcl
```

**Alternative (batch from shell)** — useful for CI; path must point at your `.xpr`:

```bash
vivado -mode batch -source vivado/build.tcl -tclargs /path/to/Dual-FPGA-Trading-Engine/vivado/hft_board_a/hft_board_a.xpr
```

**Step D — Package overlays for PYNQ** (run **Tcl current directory = repo root** so `package_pynq.tcl` resolves paths correctly):

```tcl
cd {C:/path/to/Dual-FPGA-Trading-Engine}
source vivado/package_pynq.tcl
```

Confirm on disk:

```bash
ls pynq/overlays/board_a.bit pynq/overlays/board_a.hwh
```

If `package_pynq.tcl` warns that bit/hwh are missing, `build.tcl` did not complete `write_bitstream` — re-run implementation.

### 0.5 Prepare the Board A filesystem layout (Linux on the board)

You need a single working directory on the board that contains **`overlays/`** next to **`sw/board_a/`** (because `config_symbols.py` uses `Overlay("overlays/board_a.bit")` relative to **current working directory**).

**On Board A (SSH as `xilinx`):**

```bash
mkdir -p ~/hft_capstone/overlays ~/hft_capstone/sw/board_a
```

**On your development PC** (replace `BOARD_A_IP`):

```bash
cd /path/to/Dual-FPGA-Trading-Engine
scp pynq/overlays/board_a.bit pynq/overlays/board_a.hwh xilinx@BOARD_A_IP:~/hft_capstone/overlays/
scp sw/board_a/config_symbols.py sw/board_a/symbol_universe.py xilinx@BOARD_A_IP:~/hft_capstone/sw/board_a/
# If you use the Jupyter panel or other helpers:
scp -r sw/board_a/*.py xilinx@BOARD_A_IP:~/hft_capstone/sw/board_a/   # or entire directory
```

**Alternative:** `git clone` the repo **on the board** into `~/hft_capstone`, then only **`scp`** the two overlay files into `~/hft_capstone/pynq/overlays/` — but then you must **`cd`** to the directory that actually contains `overlays/board_a.bit` (either move/copy to match `config_symbols.py` or change the path in code). Simplest convention: **flatten** to `~/hft_capstone/overlays/` as in §0.5.

### 0.6 Verify PYNQ can load the design

**On Board A:**

```bash
cd ~/hft_capstone
python3 -c "from pynq import Overlay; o=Overlay('overlays/board_a.bit'); print('OK', list(o.ip_dict.keys()))"
```

You should see **`hft_core`** (or the name in your `.hwh`) in `ip_dict`. If `Overlay` fails, the `.hwh` next to the `.bit` is missing or mismatched name.

### 0.7 Run the real configuration script (end-to-end)

```bash
cd ~/hft_capstone
python3 sw/board_a/config_symbols.py --status
python3 sw/board_a/config_symbols.py --symbols AAPL MSFT NVDA --regime 0 --start
python3 sw/board_a/config_symbols.py --status
```

If `--start` was used and PMOD is connected to a live Board B pipeline, you should see activity on the other board / telemetry later.

### 0.8 Development iteration loops (what to repeat daily)

**A) Python-only changes** (`sw/board_a/*.py`)

1. Edit on PC → `scp` changed files to `xilinx@BOARD_A:~/hft_capstone/sw/board_a/`  
2. SSH to board → `cd ~/hft_capstone` → run `python3 sw/board_a/config_symbols.py ...`  
3. Optional: `git commit` on PC when stable.

**B) RTL / constraints / block design changes**

1. Edit files under `rtl/`, `constraints/`, or regenerate BD in Vivado.  
2. Re-run **`source vivado/build.tcl`** (with `hft_board_a` open).  
3. Re-run **`source vivado/package_pynq.tcl`** from repo root.  
4. **`scp`** new `pynq/overlays/board_a.bit` and `board_a.hwh` to the board.  
5. On board: **reload overlay** — simplest is to exit Python and rerun a script that constructs `Overlay(...)` again (full power-cycle only if something hangs).

**C) Optional: Verilator / simulation** (if your team uses it)

1. Follow `tb/` and any `sim/` README in-repo.  
2. Run before every long Vivado build when you changed combinatorial logic.

### 0.9 Optional: nicer terminal for interactive runs

On the board:

```bash
pip3 install --user rich
```

Use **`ssh -t`** from the laptop when driving `--interactive` (see **§4**).

### 0.10 Full dual-board + laptop dashboard (development smoke test)

1. **Board A:** §0.7 with `--start` after PMOD cables are correct.  
2. **Board B:** deploy `board_b.bit` / `board_b.hwh`, run `telemetry_server.py` per team README.  
3. **Laptop:** install dashboard deps (see `sw/laptop/` and design spec — typically `pyserial`, `dash`, `plotly`), then `python3 sw/laptop/dashboard.py --port <COM> --baud 115200` for Board B’s USB serial.

### 0.11 Quick “am I ready?” checklist

- [ ] Vivado builds **`hft_board_a`** without timing failure.  
- [ ] **`pynq/overlays/board_a.bit`** and **`board_a.hwh`** exist and timestamps match last build.  
- [ ] Board A has **`~/hft_capstone/overlays/`** + **`sw/board_a/`** and you always **`cd ~/hft_capstone`** before Python.  
- [ ] `python3 -c "from pynq import Overlay; Overlay('overlays/board_a.bit')"` prints OK.  
- [ ] `config_symbols.py --status` runs without traceback.  
- [ ] PMOD + Board B + dashboard path exercised at least once before demo week.

---

## 1. Is Board A telemetry required?

**No — not for the standard dual-FPGA demo.**

- **Board B** already streams **telemetry JSON** over UART to the laptop (`telemetry_server.py` + `dashboard.py`). That carries trading, latency, PnL, positions, and link health from the **trader** side.  
- **Board A** is the **exchange + market simulator**. You normally **configure it once** (symbols, regime, seed, start) and then it runs **open-loop** into the PMOD link. Anything you need to “peek” at (running, quotes sent, link) is available with **`python3 config_symbols.py --status`** over the same SSH session — that is **on-demand**, not a second telemetry stream.

**When Board A telemetry would matter:** only if you want the **laptop dashboard** to plot Board A–specific counters **without** SSH (see optional plan above). That is polish, not core functionality.

**You are not wrong** to skip Board A telemetry if your story is: “Board A is configured from the terminal; Board B feeds the dashboard.”

---

## 2. Connect your computer to Board A (for prompting)

You need a path where **Python on the board** can talk to the **PL** via **PYNQ** (`Overlay` + `MMIO`). The usual pattern is **SSH from the laptop into the board**, then run scripts **on the board** (or mount the repo over `scp`/`git clone`).

### 2.1 Physical connections

| Connection | Purpose |
|-------------|---------|
| **USB** from laptop → Board A **USB / PROG** (as your board manual labels it) | Power + **serial console** and/or **USB Ethernet gadget** (depends on PYNQ image). Often used for first boot and `screen` / PuTTY. |
| **Ethernet** (optional) | Board A on same **LAN / Wi‑Fi router** as laptop → SSH by **IP address** (most reliable for demos). |
| **PMOD ribbon** Board A ↔ Board B | **Required** for the full system so quotes/orders flow between FPGAs. |

### 2.2 Get a shell on Board A

Pick what your lab image supports:

1. **SSH over Ethernet (recommended for demo)**  
   - Find IP (router admin page, `nmap`, or plug a monitor once and run `hostname -I`).  
   - From laptop: `ssh xilinx@<BOARD_A_IP>`  
   - Default password is often `xilinx` (change in a real deployment).

2. **SSH over USB gadget**  
   - Some images expose `192.168.3.1` or `192.168.2.99` on the USB NIC; see your PYNQ / vendor quickstart.

3. **Serial terminal only**  
   - Good for bring-up; awkward for running Python. Prefer SSH once networking works.

### 2.3 Put software and the bitstream where the board expects them

On Board A, you need:

- **`overlays/board_a.bit`** and **`overlays/board_a.hwh`** (from `vivado/package_pynq.tcl` in the repo, copied to the board’s `overlays/` or your project layout).  
- **`sw/board_a/`** tree: at minimum `config_symbols.py`, `symbol_universe.py`, and dependencies (`pynq` already on image).

Typical layout **on the board**:

```text
/home/xilinx/hft_capstone/
  overlays/board_a.bit
  overlays/board_a.hwh
  sw/board_a/config_symbols.py
  sw/board_a/symbol_universe.py
  ...
```

`config_symbols.py` loads `Overlay("overlays/board_a.bit")` **relative to the current working directory**, so **always `cd` into the folder that contains `overlays/`** before running Python.

### 2.4 "User enters a number → Board A" (already in the repo)

`sw/board_a/config_symbols.py` supports **`--interactive`**, which prompts on **stdin**:

1. User chooses **1** (sector mix) or **2** (fully random universe sample).  
2. For option **2**, user can enter a **random seed** (or Enter for nondeterministic).  
3. For option **1**, the script walks through **sector mix** until `hw_slots` are filled.

Then the script writes **AXI registers** and, with **`--start`**, pulses **CTRL[0]** to start the market.

**Example (on Board A, from directory that contains `overlays/`):**

```bash
cd ~/hft_capstone   # or your path; must contain ./overlays/board_a.bit
python3 sw/board_a/config_symbols.py --interactive --start
```

**Non-interactive** (good for scripted demos): fixed tickers, regime, seed:

```bash
python3 sw/board_a/config_symbols.py --symbols AAPL MSFT NVDA --regime 0 --start
python3 sw/board_a/config_symbols.py --status
```

### 2.5 Full system order (demo checklist)

1. **Power** both boards; wait for Linux.  
2. **SSH** to Board A → `cd` to project root with `overlays/` → run **`config_symbols.py`** (interactive or fixed).  
3. **PMOD** cables already connected A↔B.  
4. **SSH** to Board B → run **`telemetry_server.py`** (with overlay and config as your README describes).  
5. **Laptop:** `python3 sw/laptop/dashboard.py --port <Board B COM> --baud 115200` (or your port).  
6. Operator actions on **switches / buttons** match your script (e.g. trading enable on B).

---

## 3. Demo-friendly terminal — in depth

Audience goals: **read from ~3 m away**, **no confusion** about what to type, **confidence** that Board A started correctly. Subsections: environment constraints, layout, ANSI color, optional `rich`, projector discipline, advanced TUI.

### 3.1 Constraints (SSH, TTY, environment)

| Constraint | Effect | Mitigation |
|--------------|--------|------------|
| **No TTY** | `sys.stdin.isatty()` is false; `input()` and line discipline can misbehave; some libraries skip prompts. | Use **`ssh -t`** (§4). |
| **`NO_COLOR`** | User or CI sets this to disable color. | If `os.environ.get("NO_COLOR")`: skip all ANSI / tell `rich` no color. |
| **`TERM=dumb`** | No cursor positioning / colors. | Plain text only; skip `\033[2J` clear. |
| **Unicode / font** | Box-drawing and checkmarks become tofu on some Windows fonts. | Prefer **ASCII** `+---+` and `OK` for universal demos. |
| **Kernel prints** | `dmesg` traffic on serial USB can interleave with Python. | Prefer **Ethernet + SSH** for clean capture / screen share. |
| **Terminal width** | Projectors clip; narrow SSH windows wrap awkwardly. | Target **72–76** effective columns; detect with `shutil.get_terminal_size((80, 24)).columns` and soft-wrap hints. |

### 3.2 ASCII banners and horizontal rhythm

**Purpose:** The first screenful tells the audience **which board** and **what will happen next** (config only; dashboard is elsewhere).

**Width:** Use **76** or **72** character lines so **80-column** terminals and slightly narrow screen-share regions still show full lines without wrap.

**Centered title inside a rule of `=`:**

```python
def banner_line(text: str, width: int = 76, fill: str = "=") -> str:
    text = f"  {text.strip()}  "
    if len(text) >= width:
        return text[:width]
    pad = width - len(text)
    left = pad // 2
    right = pad - left
    return fill * left + text + fill * right

print(banner_line("HFT CAPSTONE — BOARD A"))
print(banner_line("Exchange + Market simulator"))
print("=" * 76)
```

**Optional `figlet`:** `subprocess.run(["figlet", "-f", "small", "BOARD A"], check=False)` adds drama if the package exists on the image; **rehearse** — default fonts are often **wider than 80** columns.

**Clear screen (`\033[2J\033[H`):** Looks crisp at program start; **avoid** clearing before every `input()` during **Zoom / HDMI** capture — repeated clears flash and distract.

### 3.3 Fixed-width sections, menus, and two-column summaries

**Visual hierarchy:** one character for **major** rules (`=`), another for **minor** (`-`). Inconsistent mixes (`~` vs `-`) look accidental.

**Menu pattern** — label left, short explanation right (manual padding or `str.ljust` / `rjust`):

```text
  Select load mode:
    [1]  Sector mix (fills all hardware slots)
    [2]  Random sample from full universe

  Type 1 or 2, then Enter
```

**Two-column summary without extra libraries:**

```python
def col(left: str, right: str, width: int = 76) -> str:
    gap = width - len(left) - len(right)
    return left + (" " * max(gap, 1)) + right

print(col("Regime", "CALM (0)", 76))
print(col("Quote interval (cycles)", "1000", 76))
```

**Long symbol lists:** For **16** tickers, a projector cannot show all rows legibly. Show **first 8** plus a footer `(+8 more)` or write full list to **`/tmp/board_a_symbols.txt`** and print that path once.

### 3.4 ANSI colors — SGR codes, discipline, and Python helpers

Terminal colors use **CSI SGR** sequences: **ESC** `[` *codes* `m`. In Python, `"\033[...m"` or `"\x1b[...m"`.

**Small palette (readable on dark backgrounds):**

| Sequence | Typical use |
|----------|-------------|
| `\033[1m` | Bold (often brighter) |
| `\033[96m` | Bright cyan — titles |
| `\033[92m` | Bright green — success |
| `\033[93m` | Bright yellow — warnings / "look here" |
| `\033[91m` | Bright red — **errors only** (overuse reads as alarm fatigue) |
| `\033[90m` | Gray — secondary hints |
| `\033[0m` | Reset all |

**One-line highlight** (sparingly): `\033[30;103m` black on bright yellow + `\033[0m` for "START asserted".

**256-color** (`\033[38;5;208m` orange): Only if `TERM` contains `256color` or you verified in your SSH client.

**Respect `NO_COLOR` and non-TTY:**

```python
import os
import sys

def color_enabled() -> bool:
    if os.environ.get("NO_COLOR"):
        return False
    return sys.stdout.isatty() and os.environ.get("TERM", "") not in ("", "dumb")

def green(s: str) -> str:
    return f"\033[92m{s}\033[0m" if color_enabled() else s
```

**Demo discipline:** Pick **at most two** semantic colors (e.g. cyan + green). Rainbow traces read as noise from the back row.

### 3.5 Optional `rich` — panels, tables, spinners, prompts, JSON

Install once on the board: `pip install --user rich`

**Why `rich`:** Automatic wrapping-aware tables, word wrapping in panels, spinners that do not corrupt the scrollback when they finish, and **Prompt.ask** with constrained choices.

**Console with forced terminal** (only if colors were wrongly disabled over SSH):

```python
from rich.console import Console
console = Console(force_terminal=True)  # use sparingly; test first
```

**Panel** for the opening "card":

```python
from rich.panel import Panel

console.print(Panel.fit(
    "[bold cyan]Board A setup[/bold cyan]\n\n[1] Sector mix\n[2] Random universe",
    title="HFT Capstone",
    border_style="cyan",
))
```

**Table** with row cap for projector:

```python
from rich.table import Table

def print_symbols_table(console, loaded_rows, max_rows: int = 8):
    t = Table(title="Loaded symbols", show_lines=True)
    t.add_column("ID", justify="right", style="dim")
    t.add_column("Ticker", style="bold")
    t.add_column("Sector")
    for row in loaded_rows[:max_rows]:
        t.add_row(str(row["symbol_id"]), row["ticker"], row["sector"])
    console.print(t)
    if len(loaded_rows) > max_rows:
        console.print(f"[dim](+{len(loaded_rows) - max_rows} more)[/dim]")
```

**Spinner** around **`Overlay(...)`** (seconds of dead air otherwise):

```python
from rich.console import Console
from rich.status import Status

console = Console()
with console.status("[bold green]Loading FPGA overlay…"):
    pass  # ol = Overlay("overlays/board_a.bit")
```

**Validated choice** (no infinite loop on `9`):

```python
from rich.prompt import Prompt
choice = Prompt.ask("Mode", choices=["1", "2"], default="1")
```

**Syntax-highlighted JSON** (debug / "trust but verify" beat):

```python
from rich.syntax import Syntax
payload = '{"regime":0,"active_symbols":16}'
console.print(Syntax(payload, "json", theme="monokai", line_numbers=False))
```

**Fallback** when `rich` is missing:

```python
try:
    from rich.console import Console
    console = Console()
    HAVE_RICH = True
except ImportError:
    HAVE_RICH = False
```

**Tracebacks in rehearsal:** `from rich.traceback import install; install()` in `main` — remove or guard for final "polished" run if you prefer stock tracebacks.

### 3.6 Projector and stagecraft

| Technique | Why it helps |
|-----------|----------------|
| **Font 16–20 pt** | Readable from the back row on mirrored laptop. |
| **Dark theme + light text** | Less glare than black-on-white in lit rooms. |
| **<= ~20 content lines** | Scrolling loses the audience; paginate or summarize. |
| **Explicit pause before START** | `input("Press Enter to assert START on FPGA…")` lets you narrate. |
| **One SUCCESS line** | Single bright/green line: `STATUS: Board A RUNNING — OK` |
| **Region screen-share** | Share only the terminal window so the browser UI does not shrink text. |
| **Rehearse on the projector** | Laptop-only font sizes lie; **wrap** differs at HDMI resolution. |
| **Cheat sheet** | `DEMO_CHEATSHEET_board_a.txt` with IPs, `ssh -t` one-liner, and fallback non-interactive command. |

### 3.7 Full-screen TUI (`textual`, `curses`)

Possible, but **days** of work and resize bugs over SSH. Only worth it if the story is "operator console product" rather than "FPGA trading path + web dashboard."

---

## 4. `ssh -t` and TTY behavior — in depth

### 4.1 What a TTY is

A **pseudo-TTY (PTY)** pairs a **master** and **slave** side. Your SSH client holds the master; the remote shell (and child `python3`) sees the **slave** as a character device with **line discipline** (echo, erase, Ctrl+C → SIGINT). **Without** a PTY, the remote command often runs with **pipes** for stdin/stdout — fine for `ls`, wrong for interactive `input()`.

### 4.2 What breaks without `-t`

Command form: `ssh user@host 'python3 -c "import sys; print(sys.stdin.isatty())"'` often prints **`False`**.

Symptoms:

- **`input()`** may still read but **echo** and **backspace** can be wrong.  
- **`rich`** may suppress color and alter **Live** / **Status** behavior.  
- **sudo**, **password prompts**, and **pinentry** expect a TTY.

### 4.3 The fix

```bash
ssh -t xilinx@BOARD_A_IP 'cd ~/hft_capstone && python3 sw/board_a/config_symbols.py --interactive --start'
```

OpenSSH **`ssh -t`** forces pseudo-terminal allocation. **`ssh -tt`** forces TTY even if local stdin is not a TTY (nested automation edge cases).

### 4.4 SSH multiplexing (demo QoL)

In `~/.ssh/config`:

```text
Host board-a
    HostName 192.168.1.50
    User xilinx
    ControlMaster auto
    ControlPath ~/.ssh/cm-%r@%h:%p
    ControlPersist 10m
```

Second `ssh -t board-a ...` reuses the TCP connection — faster if you reconnect during live demo.

### 4.5 Escape and interrupt

Know **`~.`** (tilde then dot) to kill an **stuck** SSH session (when enabled). **`Ctrl+C`** sends SIGINT to the **remote** foreground process — practice so you do not kill the whole session accidentally mid-demo.

### 4.6 When you intentionally skip `-t`

Fully **non-interactive** remote runs avoid TTY need entirely:

```bash
ssh xilinx@BOARD_A_IP 'cd ~/hft_capstone && python3 sw/board_a/config_symbols.py --random-count 16 --regime 0 --start'
```

Use this for **scripted** or **CI** demos where no human types.

---

## 5. Files to read in-repo

| File | Role |
|------|------|
| `sw/board_a/config_symbols.py` | `--interactive`, `--start`, `--status`, MMIO |
| `sw/board_a/symbol_universe.py` | Ticker DB for prompts |
| `vivado/package_pynq.tcl` | Builds `pynq/overlays/board_a.bit` + `.hwh` |

---

## Summary

| Question | Answer |
|----------|--------|
| Must Board A stream telemetry like Board B? | **No** for the core demo; SSH + `--status` is enough. |
| How does the laptop "talk" to Board A? | **SSH** into PYNQ, run **`config_symbols.py`** (already has numeric **menu** prompts). |
| How to make the terminal demo-friendly? | See **§3**: banners + fixed width + **ANSI** with `NO_COLOR` / TTY checks; optional **`rich`** Panel/Table/Status/Prompt; **§3.6** projector tips; **`ssh -t`** in **§4** so **`input()`** works remotely. |
