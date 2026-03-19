# Dual-FPGA Deterministic Trading Engine

## Updated Design Specification

**Project**: ECE 554 Capstone  
**Platform**: 2x AMD AUP-ZU3 (Zynq UltraScale+ XCZU3EG-2SFVC784E)  
**Revision**: B1 -- March 2026

---

## Table of Contents

1. [Problem Statement](#1-problem-statement)
2. [Proposed Solution](#2-proposed-solution)
3. [Design Requirements](#3-design-requirements)
4. [Hardware System Specification](#4-hardware-system-specification)
   - 4.1 [Target Device Resources](#41-target-device-resources)
   - 4.2 [Clock Architecture](#42-clock-architecture)
   - 4.3 [Data Plane Architecture](#43-data-plane-architecture)
     - 4.3.1 [Board A — Exchange-Lite + Market Simulator](#431-board-a--exchange-lite--market-simulator)
     - 4.3.2 [Board B — Trader (Strategy + Risk + Telemetry)](#432-board-b--trader-strategy--risk--telemetry)
   - 4.4 [Control Logic and Operational Flow](#44-control-logic-and-operational-flow)
     - 4.4.1 [Why No Custom Processor in PL](#441-why-no-custom-processor-in-pl)
     - 4.4.2 [Button / Switch / LED Mapping](#442-button--switch--led-mapping)
     - 4.4.3 [Debounce and Edge Detection](#443-debounce-and-edge-detection)
     - 4.4.4 [Board A Operational States](#444-board-a-operational-states)
     - 4.4.5 [Board B Operational States](#445-board-b-operational-states)
   - 4.5 [Board-to-Board Link Layer](#45-board-to-board-link-layer)
     - 4.5.1 [Physical Layout](#451-physical-layout)
     - 4.5.2 [Clocking Strategy — Mesochronous](#452-clocking-strategy--mesochronous-no-forwarded-clock)
     - 4.5.3 [Data Protocol — Message Frames](#453-data-protocol--message-frames)
     - 4.5.4 [Throughput and Latency](#454-throughput-and-latency)
     - 4.5.5 [Number Representation](#455-number-representation)
   - 4.6 [Submodule Inventory and Scalability](#46-submodule-inventory-and-scalability)
     - 4.6.1 [Module Summary](#461-module-summary)
     - 4.6.2 [Shared / Common Modules](#462-shared--common-modules)
     - 4.6.3 [Link Layer Modules](#463-link-layer-modules)
     - 4.6.4 [Board A Modules](#464-board-a-modules)
     - 4.6.5 [Board B Modules](#465-board-b-modules)
     - 4.6.6 [Stretch Goal Modules (Board B)](#466-stretch-goal-modules-board-b)
     - 4.6.7 [Module Interconnection Overview](#467-module-interconnection-overview)
     - 4.6.8 [Scalability and Parameterization](#468-scalability-and-parameterization)
5. [PS and Laptop Software Specification](#5-ps-and-laptop-software-specification)
   - 5.1 [PS Software Architecture](#51-ps-software-architecture)
     - 5.1.1 [Board A PS Script](#511-board-a-ps-script--config_exchangepy)
     - 5.1.2 [Board B PS Script](#512-board-b-ps-script--telemetry_serverpy)
   - 5.2 [Board B to Laptop Connection](#52-board-b-to-laptop-connection)
     - 5.2.1 [Physical Path](#521-physical-path)
     - 5.2.2 [UART Configuration](#522-uart-configuration)
     - 5.2.3 [Why Not Ethernet / TCP?](#523-why-not-ethernet--tcp)
   - 5.3 [Telemetry Data Format](#53-telemetry-data-format)
   - 5.4 [Laptop Dashboard](#54-laptop-dashboard--dashboardpy)
   - 5.5 [Complete Software File Inventory](#55-complete-software-file-inventory)
   - 5.6 [Demo Workflow — End to End](#56-demo-workflow--end-to-end)
6. [Vivado Build Strategy](#6-vivado-build-strategy)
   - 6.1 [Block Design Structure](#61-block-design-structure)
   - 6.2 [IP Packaging Approach](#62-ip-packaging-approach)
   - 6.3 [XDC Constraints](#63-xdc-constraints)
   - 6.4 [PYNQ Overlay Packaging](#64-pynq-overlay-packaging)
   - 6.5 [Build Checklist](#65-build-checklist-per-board)
   - 6.6 [Synthesis Expectations](#66-synthesis-expectations)
7. [Testing Plan](#7-testing-plan)
   - 7.1 [Simulation Environment](#71-simulation-environment)
   - 7.2 [Unit Testing](#72-unit-testing-simulation)
   - 7.3 [Integration Testing](#73-integration-testing-simulation)
   - 7.4 [Hardware Bring-Up (10 Phases)](#74-hardware-bring-up-10-phases)
   - 7.5 [Stress Testing Protocol](#75-stress-testing-protocol)
   - 7.6 [Acceptance Criteria Matrix](#76-acceptance-criteria-matrix)
   - 7.7 [Debugging Toolkit](#77-debugging-toolkit)
   - 7.8 [Test File Inventory](#78-test-file-inventory)
8. [Stretch Goals](#8-stretch-goals)
   - 8.1 [Stretch Goal Summary](#81-stretch-goal-summary)
   - 8.2 [G1 — Momentum / Trend-Following Strategy](#82-g1--momentum--trend-following-strategy)
   - 8.3 [G2 — Neural Network Inference Strategy](#83-g2--neural-network-inference-strategy)
   - 8.4 [G4 — Adaptive Regime Detection](#84-g4--adaptive-regime-detection)
   - 8.5 [G5 — Volatility Estimator](#85-g5--volatility-estimator)
   - 8.6 [G6 — Symbol Scaling](#86-g6--symbol-scaling)
   - 8.7 [G7 — 8-Bit Link Upgrade](#87-g7--8-bit-link-upgrade)
   - 8.8 [How Stretch Goals Enhance the Demo](#88-how-stretch-goals-enhance-the-demo)
9. [Project Risk Management](#9-project-risk-management)
10. [Bill of Materials](#10-bill-of-materials)
11. [Appendix](#11-appendix)
    - A. [Glossary of Financial and Technical Terms](#appendix-a--glossary-of-financial-and-technical-terms)
    - B. [XDC Constraints Reference](#appendix-b--xdc-constraints-reference)
    - C. [Message Frame Bit-Field Reference](#appendix-c--message-frame-bit-field-reference)
    - D. [AXI-Lite Register Maps](#appendix-d--axi-lite-register-maps)
    - E. [Market Simulator and LFSR Detail](#appendix-e--market-simulator-and-lfsr-detail)
    - F. [Trading Strategy Reference (Board B Modes)](#appendix-f--trading-strategy-reference-board-b-modes)
    - G. [Additional References](#appendix-g--additional-references)
- [References](#references)

---

## 1. Problem Statement

### 1.1 The Core Challenge

Modern electronic trading demands **deterministic, sub-microsecond decision-making**. General-purpose CPUs cannot guarantee this: OS scheduling, cache misses, and interrupts introduce unpredictable jitter (typically 10--100 us), making software-based latency measurement unreliable and software-based trading non-deterministic.

We build a **closed-loop, dual-FPGA trading testbed** that demonstrates:

- **Hardware-deterministic processing** -- every market quote processed and responded to in a fixed, predictable number of clock cycles with zero jitter.
- **Accurate hardware-based measurement** -- latency, throughput, and risk metrics computed entirely in FPGA fabric, free from OS/software contamination.
- **Realistic market stress testing** -- the system behaves differently under four market regimes (calm, volatile, burst, adversarial), and all behavioral changes are measurable in real time.

### 1.2 Why Two Separate FPGAs?

A single FPGA looping back to itself would be trivially simple and unrealistic. Two physically separate boards force real engineering problems:

- **Physical-layer link design** -- a deterministic, high-throughput serial bus across a cable.
- **Clock domain crossing** -- two independent oscillators require proper CDC.
- **Separation of concerns** -- Exchange and Trader are distinct entities with distinct logic, mirroring the real world.
- **Demo credibility** -- judges see two physical boards with a visible cable carrying live data.

### 1.3 What This Is NOT

- Not a full stock exchange (no deep order book, no multiple participants).
- Not algorithmic trading research (strategy is intentionally simple; the point is the hardware pipeline).
- Not a networking project (the link is custom PL-to-PL, not Ethernet/TCP).

The project is an **FPGA systems engineering demonstration**: custom interconnect, real-time pipelines, hardware measurement, and a polished demo.

---

## 2. Proposed Solution

### 2.1 Concept

| Board | Role | Real-World Analogy |
|-------|------|--------------------|
| Board A | Exchange-Lite + Market Simulator | A simplified NASDAQ |
| Board B | Trader (strategy + risk + telemetry) | A trading firm's FPGA engine |
| Laptop | Dashboard (read-only display) | Operations monitoring screen |

Board A continuously generates synthetic market quotes (bid/ask prices for multiple symbols) and sends them to Board B over a custom PMOD streaming link. Board B processes quotes through a deterministic pipeline -- feature computation, strategy, risk checks -- and sends orders back. Board A matches orders against current prices and returns fill or reject responses. Board B measures round-trip latency in hardware and exposes all metrics to a laptop dashboard via UART.

### 2.2 Data Lifecycle

```
Board A                          Cable               Board B
--------                     (2x PMOD)               --------
Market Sim generates quote ─────────────────────────> Quote book update
                                                      Feature compute (EMA)
                                                      Strategy decision
                                                      Risk check
                             <───────────────────────── Order sent
Exchange matches order
Fill (or reject) generated ─────────────────────────> Fill received
                                                      Position + PnL update
                                                      Latency measured
                                                      Stats to dashboard
```

### 2.3 Why This Solution

- **Meaningful closed loop** -- quotes, orders, and fills form a realistic market data cycle with clear semantics.
- **Demoable** -- judges see live throughput, latency histograms, PnL, and regime changes in real time.
- **Scalable complexity** -- baseline achievable in 10 weeks; stretch goals exist.
- **Teaching value** -- touches CDC, fixed-point DSP, AXI-Lite, state machines, PYNQ, and physical I/O.

### 2.4 Demo Approach

> **NOTE**: This section will be updated after the full design specification is complete. The demo story will be revisited to reflect the final architecture, including how stretch goals (additional strategies, adaptive regime switching, symbol scaling, speed upgrades) could enhance the demo experience.

#### 2.4.1 Physical Setup

```
     ┌─────────────────┐    2x PMOD cables    ┌─────────────────┐
     │   Board A        │◄────────────────────►│   Board B        │
     │   (Exchange)      │                      │   (Trader)        │
     │   AUP-ZU3 #1     │                      │   AUP-ZU3 #2     │
     └─────────────────┘                      └────────┬────────┘
                                                       │ USB-C UART
                                                       ▼
                                               ┌───────────────┐
                                               │    Laptop      │
                                               │  (Dashboard)   │
                                               └───────────────┘
```

#### 2.4.2 Dashboard Panels (8 total)

1. **Throughput gauges** -- quotes/sec, orders/sec, fills/sec
2. **Latency histogram** -- 16-bin bar chart with p50/p99/max annotated
3. **Position bars** -- per-symbol position (green = long, red = short)
4. **PnL line chart** -- running profit/loss over time
5. **Regime indicator** -- current stress mode label + color
6. **Risk reject counter** -- jumps when limits hit
7. **Link health** -- error count (should be 0)
8. **Scalar stats** -- p50, p99, max latency in nanoseconds

#### 2.4.3 Scripted Demo Flow

| Step | Action | What Audience Sees |
|------|--------|--------------------|
| 1 | Power on boards, PYNQ boots | LEDs come on, dashboard connects |
| 2 | Run config script on Board A (CALM regime) | Quotes flowing on dashboard |
| 3 | Enable trading on Board B (switch or script) | Orders + fills begin, PnL moves |
| 4 | Switch to VOLATILE (flip switch on Board A) | Spread widens, PnL swings larger |
| 5 | Switch to BURST | Quote rate spikes to ~1M+/sec |
| 6 | Switch to ADVERSARIAL | Risk rejects spike, position limits hit |
| 7 | Return to CALM | System stabilizes, proves resilience |
| 8 | Highlight link errors = 0 | Proves zero frame loss under all regimes |

---

## 3. Design Requirements

Each requirement is traced from a **functional need** to a **technical approach** to a **quantitative acceptance metric**.

### 3.1 Processing Speed

| Layer | Description |
|-------|-------------|
| **Functional** | Board B must process market quotes and generate orders in real-time with no buffering delay |
| **Technical** | Fully pipelined RTL in PL. No software, OS, cache, or interrupts in the critical path. Valid/ready handshake between stages. |
| **Quantitative** | Internal pipeline latency: **<= 10 clock cycles = 100 ns** at 100 MHz. Jitter: **0 ns** (deterministic). |
| **Industry Reference** | Production FPGA trading firms achieve **50--300 ns** tick-to-trade latency, compared to 3--8 us for optimized CPU systems. Algo-Logic Systems' CME tick-to-trade system achieves 89.6 ns PHY+MAC round trip. Our 100 ns internal pipeline (excluding wire latency) is competitive with commercial FPGA implementations. ([source](https://digitaloneagency.com.au/fpga-in-high-frequency-trading-a-deep-faq-on-firing-orders-at-hardware-speed-2026-guide/), [source](https://www.algo-logic.com/fpga-tick-to-trade)) |

### 3.2 Throughput

| Layer | Description |
|-------|-------------|
| **Functional** | System must handle high quote rates including burst stress scenarios |
| **Technical** | 4-bit parallel PMOD link at 50 MHz effective data rate. 128-bit frames. 64-deep FIFOs absorb bursts. Hardware backpressure prevents loss. |
| **Quantitative** | Max sustained: **~1.47 million frames/sec per direction**. Demo target: >= 100K quotes/sec (CALM), >= 1M quotes/sec (BURST). |
| **Industry Reference** | The NYSE processed **~1.2 trillion order messages/day** in April 2025 (~13.9M msgs/sec average), driven by AI and algorithmic trading -- nearly 3x the volume from 2020. NASDAQ's INET gateway tests at burst loads of 510K msgs/sec. Our ~1.47M frames/sec max rate positions the system between NASDAQ burst-test loads and NYSE peak throughput. ([source](https://fortune.com/2025/10/15/ai-trading-flooding-wall-street-nyse-president-lynn-martin-1-2-trillion-messages/)) |

### 3.3 Board-to-Board Connectivity

| Layer | Description |
|-------|-------------|
| **Functional** | Full-duplex, deterministic link between two physically separate FPGA boards |
| **Technical** | Custom streaming bus over 2x standard 12-pin PMOD ribbon cables. 4-bit data + valid + ready per direction. Mesochronous clocking (both boards use local 100 MHz, data output at 50 MHz rate via clock enable). |
| **Quantitative** | Wire latency per 128-bit frame: **680 ns** (34 link beats at 20 ns each). Frame loss: **0** (hardware backpressure). Bit error rate: **0** (LVCMOS33 digital signaling over 30 cm cable). |

### 3.4 Latency Measurement Accuracy

| Layer | Description |
|-------|-------------|
| **Functional** | Measure true round-trip trading latency in hardware, not contaminated by OS jitter |
| **Technical** | Board B embeds 16-bit cycle-counter timestamp in each ORDER. Board A echoes it in FILL. Board B computes `latency = current_cycle - echoed_timestamp` entirely in PL. 16-bin histogram in PL registers. |
| **Quantitative** | Resolution: **10 ns** (1 cycle at 100 MHz). Histogram: 16 bins x 32 cycles. Scalar stats: min, max, sum, count. p50/p99 computed on laptop from bins. |

### 3.5 Laptop Telemetry

| Layer | Description |
|-------|-------------|
| **Functional** | Real-time dashboard showing all trading metrics for demo audience |
| **Technical** | Board B PS reads AXI-Lite registers at 20 Hz, sends JSON over USB-UART (FTDI FT2232) to laptop. Laptop runs Python Plotly Dash web dashboard. |
| **Quantitative** | Refresh: **20 Hz** (50 ms). Panels: **8** (throughput, latency histogram, position, PnL, regime, risk rejects, link health, scalar stats). Baud: 115200 (upgradeable to 921600). |

### 3.6 Determinism

| Layer | Description |
|-------|-------------|
| **Functional** | Given same LFSR seed and regime sequence, system produces identical results |
| **Technical** | LFSR PRNG with configurable seed. All logic synchronous. No variable-latency operations. Proper CDC at link boundary only. |
| **Quantitative** | Pipeline latency variance: **0 cycles**. Identical seed + regime + parameters = identical trade sequence. |

### 3.7 Stress Resilience

| Layer | Description |
|-------|-------------|
| **Functional** | System stable under all 4 stress regimes with no data loss |
| **Technical** | FIFO backpressure. Error counters. 4 configurable regimes. |
| **Quantitative** | Sustained run: **>= 10 minutes** per regime. Frame loss: **0**. FIFO max fill: **< 75%**. |

### 3.8 Risk Management

| Layer | Description |
|-------|-------------|
| **Functional** | Trader enforces position, rate, and loss limits before every order |
| **Technical** | Three independent checks in 1 pipeline stage. Any failure suppresses the order and increments reject counter. |
| **Quantitative** | Risk check latency: **1 cycle (10 ns)**. Default limits (all PS-configurable): position ±500 shares, rate 1000 orders/window, loss halt $100.00 (see Appendix D.2 for register defaults). |

---

## 4. Hardware System Specification

### 4.1 Target Device Resources

From the XCZU3EG-2SFVC784E (DS891 datasheet [7]):

| Resource | Available |
|----------|-----------|
| System Logic Cells | 154,350 |
| CLB LUTs | 70,560 |
| CLB Flip-Flops | 141,120 |
| Distributed RAM | 1.8 Mb |
| Block RAM (36Kb blocks) | 216 (7.6 Mb total) |
| Block RAM (18Kb equivalent) | 432 |
| UltraRAM | 0 |
| DSP48E2 Slices | 360 |
| Clock Management Tiles (CMTs) | 3 |

### 4.2 Clock Architecture

From the AUP-ZU3 reference manual [4], the clocking scheme:

- **PS Reference Clock**: 33.33 MHz oscillator -> PS PLL -> FCLK outputs to PL
- **PL System Clock**: 100 MHz LVDS from TI CDCE6214 clock generator on pins D6 (P) / D7 (N)

**Our design uses PS FCLK0 = 100 MHz** as the single core clock for all PL logic. This is the standard PYNQ approach and eliminates clock domain crossings between AXI-Lite and our data-plane. The FCLK0 frequency is configured in the Zynq PS IP block within the Vivado block design.

The ONLY clock domain crossing in the entire design is at the PMOD link RX boundary, where incoming data (from the other board's clock domain) is synchronized via 2-FF synchronizers.

```
Clock Domains (per board):

  ┌──────────────────────────────────────────┐
  │  PS FCLK0 = 100 MHz                      │
  │  Drives: ALL PL logic                    │
  │    - Pipeline modules                     │
  │    - AXI-Lite interconnect                │
  │    - Counters, FIFOs, state machines     │
  │    - LED/button/switch logic              │
  │    - Link TX (with 50 MHz clock enable)  │
  │    - Link RX (after 2-FF synchronizer)   │
  └──────────────────────────────────────────┘

  Only CDC boundary: incoming PMOD data/valid
  synchronized via 2-FF synchronizers into core_clk domain
```

### 4.3 Data Plane Architecture

#### 4.3.1 Board A — Exchange-Lite + Market Simulator

**Role**: Board A simulates a simplified stock exchange. It generates synthetic market quotes and sends them to Board B. When Board B sends back orders, Board A matches them against current prices and returns fill or reject responses.

**Block Diagram**:

```
╔══════════════════════════════════════════════════════════════════════════════╗
║                               BOARD A  (PL)                                 ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                              ║
║                                                                              ║
║  ┌────────────┐  regime, interval,   ┌─────────────────────┐                 ║
║  │            │  seed, init_prices   │                     │                 ║
║  │  AXI-LITE  │═════════════════════>│    MARKET SIM       │                 ║
║  │  REGISTERS │                      │    (LFSR price      │                 ║
║  │            │                      │     evolution)      │                 ║
║  │  (config   │                      │                     │                 ║
║  │   + status)│                      └──────┬────────┬─────┘                 ║
║  │            │                             │        │                       ║
║  │      ▲     │                        QUOTE frames  │ bid/ask               ║
║  │      │     │                        (128-bit)     │ prices                ║
║  │  counters  │                             │        │ per symbol            ║
║  │  + status  │                             ▼        │                       ║
║  │  from all  │                      ┌────────────┐  │                       ║
║  │  modules:  │                      │            │  │                       ║
║  │            │<─ ─ ─ ─ ─ ─ ─ ─ ─ ─ │ QUOTE FIFO │  │                       ║
║  │ quotes_sent│  fifo_fill_level     │ (64x128b)  │  │                       ║
║  │ orders_rcvd│                      │            │  │                       ║
║  │ fills_sent │                      └──────┬─────┘  │                       ║
║  │ rejects    │                             │        │                       ║
║  │ link_errors│                        QUOTE frames  │                       ║
║  │ running    │                        (low priority)│                       ║
║  │ link_up    │                             │        │                       ║
║  └─────┬──────┘                             ▼        │                       ║
║        │                             ┌────────────┐  │                       ║
║        │ config              ┌──────>│            │  │                       ║
║        │ params    FILL/REJECT│      │ TX ARBITER │  │                       ║
║        ▼           frames    │       │            │  │                       ║
║  ┌────────────┐    (high     │       │ fills      │  │                       ║
║  │            │    priority)  │       │  before    │  │                       ║
║  │   CTRL     │              │       │   quotes   │  │                       ║
║  │            │              │       └──────┬─────┘  │                       ║
║  │  btn[3:0]  │              │              │        │                       ║
║  │  sw[7:0]   │              │         muxed frame   │                       ║
║  │  led[7:0]  │              │         (128-bit)     │                       ║
║  │  rgb[1:0]  │              │              │        │                       ║
║  │            │              │              ▼        │                       ║
║  └────────────┘              │       ┌────────────┐  │                       ║
║                              │       │  LINK TX   │  │                       ║
║  PMOD A ◄════════════════════╪═══════│ serializer │  │                       ║
║  (to Board B)                │       └────────────┘  │                       ║
║  QUOTE + FILL frames         │                       │                       ║
║                              │                       │                       ║
║                              │                       │                       ║
║  PMOD B ═════════════════════╪═══╗   ┌────────────┐  │                       ║
║  (from Board B)              │   ╚══>│  LINK RX   │  │                       ║
║  ORDER frames                │       │deserializer│  │                       ║
║                              │       └──────┬─────┘  │                       ║
║                              │              │        │                       ║
║                              │         ORDER frame   │                       ║
║                              │         (128-bit)     │                       ║
║                              │              │        │                       ║
║                              │              ▼        ▼                       ║
║                              │       ┌─────────────────────┐                 ║
║                              │       │                     │                 ║
║                              └───────│   EXCHANGE LITE     │                 ║
║                                      │   (order matching)  │                 ║
║                                      │                     │                 ║
║                                      │  BUY:  limit ≥ ask? │                 ║
║                                      │  SELL: limit ≤ bid? │                 ║
║                                      │  ──► FILL or REJECT │                 ║
║                                      └─────────────────────┘                 ║
║                                                                              ║
║  ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─  ║
║  Status readback (dashed): all module counters feed back to AXI-Lite Regs    ║
║  Market Sim ─ ─> quotes_sent           Exchange Lite ─ ─> orders_rcvd,       ║
║                                                           fills_sent,        ║
║                                                           rejects_sent       ║
║  Link RX ─ ─ ─> link_errors, link_up   Ctrl ─ ─ ─ ─ ─ > running            ║
╚══════════════════════════════════════════════════════════════════════════════╝

                        ▲                              ▲
                        │  AXI-Lite                    │
                 ┌──────┴───────┐                      │
                 │   PS ARM     │               Physical I/O
                 │   (PYNQ)     │            (buttons, switches,
                 └──────────────┘              LEDs, RGB LEDs)
```

**Legend**: `═══>` data path (frame flow) · `───>` config/control path · `─ ─ >` status/readback path

**Data Flow — Step by Step**:

1. **Configuration (PS → AXI-Lite Registers → Market Sim)**
   The PS ARM writes configuration parameters via AXI-Lite: the market `regime` (CALM / VOLATILE / BURST / ADVERSARIAL), `quote_interval` (cycles between quote rounds), `lfsr_seed` (32-bit PRNG seed), and per-symbol `init_mid` and `init_spread` values (Q16.16 fixed-point). These flow from the AXI-Lite Register block into the Market Simulator. The Ctrl block also receives config params for button/switch override behavior (e.g., SW[1:0] can override the regime register).

2. **Quote Generation (Market Sim → QUOTE frames)**
   The Market Simulator contains a 32-bit Galois LFSR that produces a pseudo-random 5-bit value each cycle. This is converted to a signed step, scaled by the regime-dependent `step_size`, and added to the symbol's `mid_price`. From the updated mid-price it computes `bid = mid - spread/2` and `ask = mid + spread/2`, then packs a 128-bit QUOTE frame containing `{msg_type, symbol_id, regime, bid_price, ask_price, bid_size, ask_size, seq_num}`. Symbols are generated in round-robin order (0 → 1 → 2 → 3 → 0 ...), one per `quote_interval` tick. The Market Sim also exposes the current `bid_price[s]` and `ask_price[s]` arrays directly to Exchange Lite for order matching.

3. **Quote Buffering (QUOTE frames → Quote FIFO)**
   Generated QUOTE frames enter a 64-entry deep, 128-bit wide synchronous FIFO. This absorbs timing mismatches between the quote generation rate and the link's frame transmission rate. The FIFO provides backpressure to the Market Sim — if the FIFO is full, quote generation stalls (no data is lost).

4. **Outbound Arbitration (Quote FIFO + Exchange Lite → TX Arbiter)**
   The TX Arbiter accepts frames from two sources: the Quote FIFO (low priority) and the Exchange Lite's FILL/REJECT output (high priority). It implements **strict priority** — whenever a FILL or REJECT frame is available, it is selected over any pending quote. This ensures order responses are never delayed by quote traffic. The arbiter outputs one 128-bit frame at a time to the Link TX.

5. **Serialization and Transmission (TX Arbiter → Link TX → PMOD A)**
   Link TX takes the 128-bit frame from the arbiter and serializes it into 32 consecutive 4-bit nibbles, MSB first, at a 50 MHz effective data rate (one nibble every 20 ns). It drives the `pmod_data[3:0]` and `pmod_valid` signals on the PMOD A pins. The frame takes 640 ns to transmit, followed by a minimum 40 ns inter-frame gap. The `pmod_ready` signal from the remote board provides hardware backpressure — Link TX will not begin a new frame if the receiver is not ready.

6. **Order Reception (PMOD B → Link RX → ORDER frame)**
   ORDER frames arrive from Board B as 4-bit nibbles on the PMOD B pins. Link RX synchronizes the incoming `pmod_valid` and `pmod_data` signals through 2-FF synchronizers (this is the only CDC boundary on the board). It detects the rising edge of synchronized valid, then samples 32 nibbles to reassemble a 128-bit ORDER frame. Framing errors (e.g., truncated frames) increment the `link_error` counter.

7. **Order Matching (Link RX → Exchange Lite → FILL / REJECT)**
   The assembled ORDER frame enters Exchange Lite, which extracts `symbol_id`, `side`, and `limit_price`. It compares against the live bid/ask state from Market Sim:
   - **BUY order**: fills at `ask_price` if `limit_price >= ask_price`, otherwise rejected.
   - **SELL order**: fills at `bid_price` if `limit_price <= bid_price`, otherwise rejected.

   The result is a 128-bit FILL frame (with `fill_price`, `fill_qty`, echoed `order_id` and `ts_echo`) or a REJECT frame (with zero fill fields). This frame feeds back to the TX Arbiter at high priority, completing the loop.

8. **Status Reporting (all modules → AXI-Lite Registers → PS)**
   Every data-plane module maintains 32-bit counters: `quotes_sent`, `orders_received`, `fills_sent`, `rejects_sent`, `link_errors`. These are continuously written to AXI-Lite status registers and are readable by the PS at any time. A `running` status bit and `link_up` indicator are also reported.

9. **Physical I/O (Ctrl block)**
   The Ctrl block handles all button, switch, LED, and RGB LED logic. Buttons pass through a 20 ms debounce filter before generating single-cycle edge pulses (e.g., BTN[0] = start, BTN[1] = stop, BTN[2] = reset). Switches are sampled directly (e.g., SW[1:0] = regime override). LEDs reflect system state — lower 4 LEDs show regime in binary, upper 4 flash on link frame TX/RX activity. RGB LEDs indicate regime color and link health.

#### 4.3.2 Board B — Trader (Strategy + Risk + Telemetry)

**Role**: Board B is the trading engine. It receives market quotes from Board A, computes trading features, makes strategy decisions, enforces risk limits, and sends orders back. It also tracks positions, measures round-trip latency in hardware, and streams all metrics to the laptop dashboard via UART.

**Block Diagram**:

```
╔══════════════════════════════════════════════════════════════════════════════╗
║                               BOARD B  (PL)                                 ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                              ║
║  ┌────────────┐  threshold, ema_alpha,  ┌──────────────────────────────┐     ║
║  │            │  base_qty, risk limits  │                              │     ║
║  │  AXI-LITE  │════════════════════════>│  Pipeline modules (config)   │     ║
║  │  REGISTERS │                         └──────────────────────────────┘     ║
║  │            │                                                              ║
║  │  (config   │                                                              ║
║  │   + status │                                                              ║
║  │   + hist)  │                                                              ║
║  │            │                                                              ║
║  │      ▲     │                                                              ║
║  │  counters, │                                                              ║
║  │  positions,│                                                              ║
║  │  histogram,│                                                              ║
║  │  latency   │                                                              ║
║  │  stats     │                                                              ║
║  │  from all  │                                                              ║
║  │  modules   │                                                              ║
║  └─────┬──────┘                                                              ║
║        │ config                                                              ║
║        │ params                                                              ║
║        ▼                                                                     ║
║  ┌────────────┐                                                              ║
║  │   CTRL     │                                                              ║
║  │  btn[3:0]  │                                                              ║
║  │  sw[7:0]   │                                                              ║
║  │  led[7:0]  │                                                              ║
║  │  rgb[1:0]  │                                                              ║
║  └────────────┘                                                              ║
║                                                                              ║
║ ═════════════════════════════════════════════════════════════════════════     ║
║  INBOUND: QUOTE + FILL frames from Board A                                  ║
║ ═════════════════════════════════════════════════════════════════════════     ║
║                                                                              ║
║  PMOD A ══════════════════════╗                                              ║
║  (from Board A)               ║                                              ║
║  QUOTE + FILL frames          ▼                                              ║
║                        ┌────────────┐                                        ║
║                        │  LINK RX   │                                        ║
║                        │deserializer│                                        ║
║                        │ (2-FF CDC) │                                        ║
║                        └──────┬─────┘                                        ║
║                               │                                              ║
║                          128-bit frame                                       ║
║                               │                                              ║
║                               ▼                                              ║
║  ┌─────────────────────────────────────────────────────────────────────┐     ║
║  │  STAGE 1 ── MSG DEMUX                                    [1 cycle] │     ║
║  │                                                                     │     ║
║  │  Read msg_type field [127:124]                                      │     ║
║  │    msg_type == 4'h1 (QUOTE) ──► route to QUOTE path                 │     ║
║  │    msg_type == 4'h3 (FILL)  ──► route to FILL path                  │     ║
║  │    other                    ──► discard + increment error counter    │     ║
║  └───────────┬──────────────────────────────────┬──────────────────────┘     ║
║              │                                  │                            ║
║         QUOTE frame                        FILL frame                        ║
║         (128-bit)                          (128-bit)                         ║
║              │                                  │                            ║
║              ▼                                  │                            ║
║  ┌─────────────────────────────────────────┐    │                            ║
║  │  STAGE 2 ── QUOTE BOOK       [1 cycle]  │    │                            ║
║  │                                         │    │                            ║
║  │  Extract symbol_id, bid, ask, sizes     │    │                            ║
║  │  Update register file:                  │    │                            ║
║  │    best_bid[symbol_id] = bid_price      │    │                            ║
║  │    best_ask[symbol_id] = ask_price      │    │                            ║
║  │    bid_size[symbol_id] = bid_size       │    │                            ║
║  │    ask_size[symbol_id] = ask_size       │    │                            ║
║  └───────────┬─────────────────────────────┘    │                            ║
║              │                                  │                            ║
║         bid, ask, symbol_id                     │                            ║
║              │                                  │                            ║
║              ▼                                  │                            ║
║  ┌─────────────────────────────────────────┐    │                            ║
║  │  STAGE 3-4 ── FEATURE COMPUTE [3 cycles]│    │                            ║
║  │                                         │    │                            ║
║  │  Cycle 1: mid = (bid + ask) >> 1        │    │                            ║
║  │           spread = ask - bid             │    │                            ║
║  │                                         │    │                            ║
║  │  Cycle 2-3: EMA update (DSP48E2 MAC)   │    │                            ║
║  │    ema_new = (alpha × mid               │    │                            ║
║  │         + (1-alpha) × ema_old) >> 16    │    │                            ║
║  │                                         │    │                            ║
║  │  Output: deviation = mid - ema (signed) │    │                            ║
║  └───────────┬─────────────────────────────┘    │                            ║
║              │                                  │                            ║
║         deviation, mid, spread,                 │                            ║
║         bid, ask, symbol_id                     │                            ║
║              │                                  │                            ║
║              ▼                                  │                            ║
║  ┌─────────────────────────────────────────┐    │                            ║
║  │  STAGE 5 ── STRATEGY ENGINE  [1 cycle]  │    │                            ║
║  │                                         │    │                            ║
║  │  Mean-reversion decision:               │    │                            ║
║  │    deviation > +threshold ──► SELL       │    │                            ║
║  │      order_price = bid  (aggressive)    │    │                            ║
║  │    deviation < -threshold ──► BUY        │    │                            ║
║  │      order_price = ask  (aggressive)    │    │                            ║
║  │    else ──► NO TRADE                    │    │                            ║
║  └───────────┬─────────────────────────────┘    │                            ║
║              │                                  │                            ║
║         signal_valid, side,                     │                            ║
║         price, qty, symbol_id                   │                            ║
║              │                                  │                            ║
║              ▼                                  │                            ║
║  ┌─────────────────────────────────────────┐    │                            ║
║  │  STAGE 6 ── RISK MANAGER     [1 cycle]  │    │                            ║
║  │                                         │    │                            ║
║  │  Three parallel checks:                 │    │                            ║
║  │  ┌─────────────┐ ┌───────────┐ ┌──────┐│    │                            ║
║  │  │ POSITION    │ │ ORDER     │ │ LOSS ││    │                            ║
║  │  │ abs(new_pos)│ │ orders_in │ │ pnl >││    │                            ║
║  │  │ ≤ max_pos?  │ │ window <  │ │-max? ││    │                            ║
║  │  │             │ │ max_rate? │ │      ││    │                            ║
║  │  └──────┬──────┘ └─────┬─────┘ └──┬───┘│    │                            ║
║  │         │              │           │    │    │                            ║
║  │         └──────────────┴───────────┘    │    │                            ║
║  │                    │                    │    │                            ║
║  │         approved = pass1 & pass2 & pass3│    │                            ║
║  │                  & trading_enable       │    │                            ║
║  │                  & !risk_halt           │    │                            ║
║  │                                         │    │                            ║
║  │  FAIL ──► increment risk_rejects        │    │                            ║
║  └───────────┬─────────────────────────────┘    │                            ║
║              │                                  │                            ║
║         approved_valid, side,                   │                            ║
║         price, qty, symbol_id                   │                            ║
║              │                                  │                            ║
║              ▼                                  │                            ║
║  ┌─────────────────────────────────────────┐    │                            ║
║  │  STAGE 7 ── ORDER MANAGER    [1 cycle]  │    │                            ║
║  │                                         │    │                            ║
║  │  Build 128-bit ORDER frame:             │    │                            ║
║  │    order_id   = wrapping counter (++)   │    │                            ║
║  │    timestamp  = cycle_counter[15:0]     │    │                            ║
║  │    Pack: {msg_type=ORDER, symbol_id,    │    │                            ║
║  │           side, limit_price, qty,       │    │                            ║
║  │           order_id, timestamp}          │    │                            ║
║  └───────────┬─────────────────────────────┘    │                            ║
║              │                                  │                            ║
║         ORDER frame (128-bit)                   │                            ║
║              │                                  │                            ║
║ ═════════════╪══════════════════════════════════╪═══════════════════════     ║
║  OUTBOUND    │                                  │                            ║
║ ═════════════╪══════════════════════════════════╪═══════════════════════     ║
║              ▼                                  │                            ║
║       ┌────────────┐                            │                            ║
║       │  LINK TX   │                            │                            ║
║       │ serializer │                            │                            ║
║       └──────┬─────┘                            │                            ║
║              │                                  │                            ║
║  PMOD B ◄════╝                                  │                            ║
║  (to Board A)                                   │                            ║
║  ORDER frames                                   │                            ║
║                                                 │                            ║
║ ════════════════════════════════════════════════╪═══════════════════════     ║
║  FILL PATH (post-trade processing)              │                            ║
║ ════════════════════════════════════════════════╪═══════════════════════     ║
║                                                 │                            ║
║                                                 ▼                            ║
║                                  ┌─────────────────────────────────┐        ║
║                                  │  POSITION TRACKER               │        ║
║                                  │                                  │        ║
║                                  │  Extract fill_price, fill_qty,  │        ║
║                                  │  symbol_id, side from FILL      │        ║
║                                  │                                  │        ║
║                                  │  position[s] += (BUY ? +qty     │        ║
║                                  │                      : -qty)    │        ║
║                                  │  cash += (SELL ? +price×qty     │        ║
║                                  │               : -price×qty)     │        ║
║                                  │  (48-bit Q32.16 accumulator,    │        ║
║                                  │   uses DSP48E2)                 │        ║
║                                  └────────────┬────────────────────┘        ║
║                                               │                             ║
║                                          fill_valid,                        ║
║                                          ts_echo[15:0]                      ║
║                                               │                             ║
║                                               ▼                             ║
║                                  ┌─────────────────────────────────┐        ║
║                                  │  LATENCY HISTOGRAM              │        ║
║                                  │                                  │        ║
║                                  │  latency = cycle_counter[15:0]  │        ║
║                                  │            - ts_echo             │        ║
║                                  │                                  │        ║
║                                  │  bin = latency >> BIN_SHIFT      │        ║
║                                  │  hist_bins[bin]++                │        ║
║                                  │                                  │        ║
║                                  │  Update: lat_min, lat_max,      │        ║
║                                  │          lat_sum, lat_count     │        ║
║                                  └─────────────────────────────────┘        ║
║                                                                              ║
║  ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─  ║
║  Status readback (dashed): all module counters feed back to AXI-Lite Regs    ║
║  Msg Demux ─ ─ ─> quotes_rcvd, errors    Risk Mgr ─ ─ ─ ─> risk_rejects    ║
║  Order Mgr ─ ─ ─> orders_sent             Pos Tracker ─ ─ > position[s],    ║
║  Link RX ─ ─ ─ ─> link_errors, link_up                      cash, fills_rcvd║
║  Latency Hist ─ ─> hist_bins[0:15], lat_min, lat_max, lat_sum, lat_count    ║
║  Ctrl ─ ─ ─ ─ ─ > running, risk_halt                                        ║
╚══════════════════════════════════════════════════════════════════════════════╝

                        ▲                              ▲
                        │  AXI-Lite                    │
                 ┌──────┴───────┐                      │
                 │   PS ARM     │               Physical I/O
                 │   (PYNQ)     │            (buttons, switches,
                 │  sends JSON  │              LEDs, RGB LEDs)
                 │  over UART   │
                 └──────────────┘
```

**Legend**: `═══>` data path (frame flow) · `───>` config/control path · `─ ─ >` status/readback path

**Pipeline Stages (quote arrival to order departure)**:

| Stage | Module | Cycles | Operation |
|-------|--------|--------|-----------|
| 1 | msg_demux | 1 | Route frame by msg_type field |
| 2 | quote_book | 1 | Update per-symbol bid/ask register file |
| 3 | feature_compute | 1 | mid = (bid+ask)>>1, spread = ask-bid |
| 4 | feature_compute | 2 | EMA multiply-accumulate (DSP48E2) |
| 5 | strategy_engine | 1 | Compare deviation vs threshold → BUY/SELL/NONE |
| 6 | risk_manager | 1 | 3 parallel limit checks (position, rate, loss) |
| 7 | order_manager | 1 | Build ORDER frame, assign ID + capture timestamp |
| **Total** | | **8** | **80 ns at 100 MHz** |

**Data Flow — Step by Step**:

1. **Configuration (PS → AXI-Lite Registers → Pipeline)**
   The PS ARM writes trading parameters via AXI-Lite: `threshold` (Q16.16, how far price must deviate from EMA to trigger a trade), `ema_alpha` (Q0.16, smoothing factor — default ~0.1), `base_qty` (shares per order), and three risk limits: `max_position` (max absolute shares per symbol), `max_order_rate` (max orders per time window), and `max_loss` (Q16.16, PnL halt threshold). The Ctrl block receives start/stop/reset signals from buttons and exposes `trading_enable` from SW[0].

2. **Frame Reception (PMOD A → Link RX → 128-bit frame)**
   Frames from Board A arrive as 4-bit nibbles on the PMOD A pins. Link RX synchronizes via 2-FF CDC synchronizers, assembles 32 nibbles into a 128-bit frame, and outputs it with a `frame_valid` pulse. Both QUOTE and FILL frames arrive on this same link — the Msg Demux separates them.

3. **Stage 1 — Message Demux (1 cycle)**
   Reads `msg_type` from bits [127:124]. QUOTE frames (4'h1) are routed to the quote processing pipeline. FILL frames (4'h3) are routed to the position tracker / latency histogram path. Unknown types are discarded and an error counter increments. This is the fork point where the two paths diverge.

4. **Stage 2 — Quote Book (1 cycle)**
   Extracts `symbol_id`, `bid_price`, `ask_price`, `bid_size`, and `ask_size` from the QUOTE frame. Updates a per-symbol register file: `best_bid[symbol_id]`, `best_ask[symbol_id]`, etc. This is a simple write — the latest quote always overwrites the previous one (no order book depth, just best bid/ask). Outputs the updated bid/ask pair along with the symbol_id to the next stage.

5. **Stages 3-4 — Feature Compute (3 cycles total)**
   This is the computational heart of the pipeline, using DSP48E2 slices for fixed-point arithmetic:
   - **Cycle 1**: Computes `mid = (bid + ask) >> 1` (arithmetic mean of bid and ask) and `spread = ask - bid` (market width).
   - **Cycles 2-3**: Updates the per-symbol exponential moving average (EMA) using a multiply-accumulate: `ema_new = (alpha × mid + (1-alpha) × ema_old) >> 16`. This uses two DSP48E2 slices for the Q0.16 × Q16.16 multiplications. The EMA is a smoothed price history — it tracks the "fair value" of the symbol.
   - **Output**: `deviation = mid - ema` (signed Q16.16). A positive deviation means the current price is above the smoothed average; negative means below.

6. **Stage 5 — Strategy Engine (1 cycle)**
   Implements mean-reversion logic — the idea that prices tend to return to their average:
   - `deviation > +threshold` → price is unusually HIGH → **SELL** at bid_price (expect reversion down)
   - `deviation < -threshold` → price is unusually LOW → **BUY** at ask_price (expect reversion up)
   - otherwise → no trade (deviation within normal range)

   Outputs `signal_valid` (1 = trade, 0 = no trade), `order_side`, `order_price`, `order_qty`, and `order_symbol`.

7. **Stage 6 — Risk Manager (1 cycle)**
   Three independent checks execute in parallel on the same clock edge:
   - **Position check**: Would the new order push `abs(position[symbol])` beyond `max_position`?
   - **Rate check**: Have we sent too many orders in the current time window (sliding window counter)?
   - **Loss check**: Is `total_pnl` below `-max_loss` (halt threshold)?

   All three must pass AND `trading_enable` must be high AND `risk_halt` must be low. Any failure suppresses the order and increments `risk_rejects`. If the loss check fails, `risk_halt` latches — all trading stops until reset.

8. **Stage 7 — Order Manager (1 cycle)**
   Only fires when risk_manager outputs `approved_valid`. Builds a 128-bit ORDER frame:
   - `order_id` = wrapping 16-bit counter (increments per order)
   - `timestamp` = low 16 bits of a free-running cycle counter (this is the value Board A will echo back in the FILL, enabling round-trip latency measurement)
   - Packs all fields: `{MSG_ORDER, symbol_id, side, limit_price, qty, order_id, timestamp, reserved}`

   The frame goes to Link TX for serialization and transmission to Board A via PMOD B.

9. **Fill Processing — Position Tracker (on FILL arrival)**
   When a FILL frame arrives (routed by Msg Demux), the Position Tracker extracts `symbol_id`, `side`, `fill_price`, and `fill_qty`:
   - Updates signed position: `position[symbol_id] += (side==BUY ? +fill_qty : -fill_qty)`
   - Updates 48-bit cash accumulator (Q32.16): `cash += (side==SELL ? +fill_price×fill_qty : -fill_price×fill_qty)`. The multiplication uses a DSP48E2 slice. Buying costs cash (negative), selling earns cash (positive).

   Position and cash values are exposed to AXI-Lite for telemetry and are read by the risk manager for position limit checks.

10. **Fill Processing — Latency Histogram (on FILL arrival)**
    After position tracking, the FILL frame's `ts_echo` field (the timestamp Board B originally embedded in the ORDER) is used to compute round-trip latency:
    - `latency = cycle_counter[15:0] - ts_echo` (wrapping subtraction, result in cycles)
    - `bin = latency >> BIN_SHIFT` (BIN_SHIFT=5, so each bin spans 32 cycles = 320 ns)
    - `hist_bins[bin]++` (16 bins, bin 15 is the overflow bucket for latency ≥ 480 cycles)
    - Scalar stats updated: `lat_min = min(lat_min, latency)`, `lat_max = max(lat_max, latency)`, `lat_sum += latency`, `lat_count++`

    All histogram bins and stats are readable via AXI-Lite. The laptop dashboard computes p50/p99 by walking the bins cumulatively.

11. **Status Reporting (all modules → AXI-Lite Registers → PS → UART → Laptop)**
    Every module feeds counters and state back to the AXI-Lite register block:

    | Module | Signals reported |
    |--------|-----------------|
    | Msg Demux | `quotes_rcvd`, `demux_errors` |
    | Order Manager | `orders_sent` |
    | Risk Manager | `risk_rejects`, `risk_halt` |
    | Position Tracker | `position[0..3]`, `cash`, `fills_rcvd` |
    | Latency Histogram | `hist_bins[0..15]`, `lat_min`, `lat_max`, `lat_sum`, `lat_count` |
    | Link RX | `link_errors`, `link_up` |
    | Ctrl | `running` |

    The PS reads all these registers at 20 Hz, formats them as a JSON line, and prints to stdout which flows over USB-UART to the laptop dashboard.

12. **Physical I/O (Ctrl block)**
    Same structure as Board A: buttons debounced with 20 ms filter, single-cycle edge pulses for start/stop/reset. SW[0] = `trading_enable` (arm vs. live). LEDs[3:0] flash on order activity, LEDs[7:4] flash on fill activity. RGB0 = PnL indicator (green=profit, red=loss). RGB1 = risk status (green=OK, yellow=near limit, red=halted).

### 4.4 Control Logic and Operational Flow

#### 4.4.1 Why No Custom Processor in PL

The Zynq UltraScale+ already contains a hard ARM Cortex-A53 quad-core processor (the PS). We use it for all slow-path tasks: overlay loading, AXI-Lite register configuration, and telemetry streaming. **We do not implement a soft-core processor (MicroBlaze, RISC-V, or custom ISA) in the PL.**

The reasoning is straightforward: a processor in the trading pipeline would hurt performance.

| Concern | Pure RTL (our approach) | Processor in pipeline |
|---------|------------------------|----------------------|
| Latency per stage | 1 cycle (10 ns) | 10-100+ cycles per operation (fetch/decode/execute) |
| Determinism | Fully deterministic, 0 jitter | Cache misses, branch stalls, interrupts |
| Parallelism | Risk manager: 3 checks in 1 cycle | Sequential instruction execution |
| Throughput | 1 result/cycle sustained | Pipeline bubbles, data hazards |

The entire value proposition of this project is **deterministic, hardware-speed processing**. Inserting a processor into the data path would introduce the exact non-determinism we're designed to eliminate.

The PS handles what processors are good at — flexible configuration, string formatting (JSON telemetry), and OS-level I/O (UART, USB). The PL handles what dedicated hardware is good at — fixed-latency, high-throughput, parallel computation. This PS/PL split is the standard Zynq SoC design pattern and is the correct architectural choice for latency-critical applications [6].

The base PYNQ overlay's "Pmod IO Processors" (MicroBlaze instances for GPIO) are **not used**. We replace the base overlay entirely with our own custom design.

#### 4.4.2 Button / Switch / LED Mapping

All pin assignments are from the AUP-ZU3 Reference Manual [4] and verified against the official XDC constraints file.

**Board A**:

| I/O | Pin(s) | FPGA Ball(s) | IOSTD | Function |
|-----|--------|-------------|-------|----------|
| SW[1:0] | PL_USER_SW0, SW1 | AB1, AF1 | LVCMOS12 | Regime: 00=CALM, 01=VOLATILE, 10=BURST, 11=ADVERSARIAL |
| SW[2] | PL_USER_SW2 | AE3 | LVCMOS12 | Override: 0=regime from PS register, 1=regime from switches |
| SW[3:7] | PL_USER_SW3..7 | AC2,AC1,AD6,AD1,AD2 | LVCMOS12 | Reserved |
| BTN[0] | PL_USER_PB0 | AB6 | LVCMOS33 | Start market simulator (edge-detected) |
| BTN[1] | PL_USER_PB1 | AB7 | LVCMOS33 | Stop market simulator |
| BTN[2] | PL_USER_PB2 | AB2 | LVCMOS33 | Reset all counters and state |
| BTN[3] | PL_USER_PB3 | AC6 | LVCMOS33 | Reserved |
| LED[3:0] | PL_USER_LED0..3 | AF5,AE7,AH2,AE5 | LVCMOS12 | Regime indicator (binary + blink when running) |
| LED[7:4] | PL_USER_LED4..7 | AH1,AE4,AG1,AF2 | LVCMOS12 | Link activity (flash on frame TX/RX) |
| RGB0 | PL_LEDRGB0_R/G/B | AD7,AD9,AE9 | LVCMOS12 | Regime color: green=CALM, yellow=VOLATILE, red=BURST, purple=ADVERSARIAL |
| RGB1 | PL_LEDRGB1_R/G/B | AG9,AE8,AF8 | LVCMOS12 | Link status: green=healthy, red=errors |

**Board B (core)**:

| I/O | Pin(s) | FPGA Ball(s) | IOSTD | Function |
|-----|--------|-------------|-------|----------|
| SW[0] | PL_USER_SW0 | AB1 | LVCMOS12 | Trading enable: 0=armed (observe only), 1=live trading |
| SW[1:2] | PL_USER_SW1..2 | AF1, AE3 | LVCMOS12 | Reserved (core build) |
| SW[3:7] | PL_USER_SW3..7 | AC2,... | LVCMOS12 | Reserved |
| BTN[0] | PL_USER_PB0 | AB6 | LVCMOS33 | Start pipeline (edge-detected) |
| BTN[1] | PL_USER_PB1 | AB7 | LVCMOS33 | Stop pipeline |
| BTN[2] | PL_USER_PB2 | AB2 | LVCMOS33 | Reset counters, positions, histogram |
| BTN[3] | PL_USER_PB3 | AC6 | LVCMOS33 | Reserved |
| LED[3:0] | PL_USER_LED0..3 | AF5,AE7,AH2,AE5 | LVCMOS12 | Order activity (flash per order) |
| LED[7:4] | PL_USER_LED4..7 | AH1,AE4,AG1,AF2 | LVCMOS12 | Fill activity (flash per fill) |
| RGB0 | PL_LEDRGB0_R/G/B | AD7,AD9,AE9 | LVCMOS12 | PnL: green=profit, red=loss, off=flat |
| RGB1 | PL_LEDRGB1_R/G/B | AG9,AE8,AF8 | LVCMOS12 | Risk: green=OK, yellow=near limit (>80%), red=halted |

**Board B (with stretch goals — strategy switching)**:

When stretch goal strategies are implemented (momentum, neural net, adaptive), SW[1:2] on Board B become active:

| I/O | Function (stretch) |
|-----|-------------------|
| SW[1] | Strategy select bit 0 |
| SW[2] | Strategy select bit 1 / override |

| SW[2:1] | Selected Strategy |
|---------|------------------|
| 00 | Mean-reversion (default, core) |
| 01 | Momentum / trend-following |
| 10 | Neural network inference |
| 11 | Auto (adaptive regime-aware switching) |

In auto mode (11), the `regime_detector` module selects the strategy based on real-time volatility and spread conditions. The active strategy is reported via the `STRATEGY_SEL` AXI-Lite status register and displayed on the dashboard.

#### 4.4.3 Debounce and Edge Detection

All 4 buttons on each board pass through `debounce.sv` before use. Mechanical pushbuttons produce electrical bounce — rapid on/off transitions lasting 1-10 ms after a press — which would register as multiple false triggers without filtering.

**Debounce mechanism**: A 20-bit shift register clocked at 100 MHz. The raw button signal is shifted in every cycle. The debounced output only changes when **all 20 samples agree** (all 1s or all 0s). This creates a ~200 us debounce window (20 bits × 10 ns), well above typical mechanical bounce duration.

```
Raw button input (with bounce):
  ____/‾‾\__/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\___
       ^^^^
       bounce

Debounced output (clean):
  __________/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\___
             ^                              ^
             200 us delay                   200 us delay
```

**Edge detection**: After debounce, a 1-cycle rising-edge pulse is generated by comparing the current debounced value to the previous cycle's value: `pulse = debounced & ~debounced_prev`. This gives a single clean trigger per button press, regardless of how long the button is held.

**Dual trigger**: The `board_x_ctrl` module ORs the hardware button pulse with the corresponding AXI-Lite register write pulse. This means the same action (start, stop, reset) can be triggered either by pressing a physical button or by the PS writing to a control register — useful for scripted demos where you don't want to manually press buttons.

#### 4.4.4 Board A Operational States

**FSM Type**: Moore machine — outputs depend only on the current state, not on inputs.

**State Encoding**: 2-bit (`state[1:0]`), 4 states.

**Inputs to the FSM**:

| Signal | Source | Description |
|--------|--------|-------------|
| `rst` | System reset (power-on or external) | Global synchronous reset |
| `start_combined` | `axi_start_pulse OR ctrl_start_pulse` | Start from PS register write OR BTN[0] press |
| `stop_combined` | `ctrl_stop_pulse` | Stop from BTN[1] press |
| `reset_combined` | `axi_reset_pulse OR ctrl_reset_pulse` | Reset from PS register write OR BTN[2] press |

**State Diagram**:

```
                              rst (global)
                                  │
                                  ▼
                     ┌───────────────────────┐
                     │        RESET          │
                     │    (state = 2'b00)    │
                     │                       │
                     │  Outputs:             │
                     │   running     = 0     │
                     │   counter_clr = 1     │
                     │   fifo_flush  = 1     │
                     │                       │
                     │  All counters cleared  │
                     │  All FIFOs flushed     │
                     │  Prices held at init   │
                     └───────────┬───────────┘
                                 │
                                 │ (automatic, 1 cycle)
                                 │
                                 ▼
                     ┌───────────────────────┐
                     │         IDLE          │
                     │    (state = 2'b01)    │
                     │                       │
                     │  Outputs:             │
                     │   running     = 0     │
                     │   counter_clr = 0     │
                     │   fifo_flush  = 0     │
                     │                       │
                     │  PS writes config:    │
                     │   regime, interval,   │
                     │   seed, init_prices   │
                     │                       │
         ┌───────────│  market_sim  OFF      │
         │           │  exchange_lite OFF    │
         │           └───────────┬───────────┘
         │                       │
         │                       │ start_combined
         │                       │ (loads LFSR seed,
         │                       │  latches init prices)
         │                       │
         │  reset_combined       ▼
         │           ┌───────────────────────┐
         │           │       RUNNING         │
         ├───────────│    (state = 2'b10)    │
         │           │                       │
         │           │  Outputs:             │
         │           │   running     = 1     │
         │           │   counter_clr = 0     │
         │           │   fifo_flush  = 0     │
         │           │                       │
         │           │  market_sim  ON       │
         │           │  exchange_lite ON     │
         │           │  regime selectable    │
         │           │   live via switches   │
         │           └───────────┬───────────┘
         │                       │
         │                       │ stop_combined
         │                       │
         │  reset_combined       ▼
         │           ┌───────────────────────┐
         │           │       STOPPED         │
         ├───────────│    (state = 2'b11)    │
         │           │                       │
         │           │  Outputs:             │
         │           │   running     = 0     │
         │           │   counter_clr = 0     │
         │           │   fifo_flush  = 0     │
         │           │                       │
         │           │  market_sim  OFF      │
         │           │  exchange_lite ON     │
         │           │  (drains pending      │
         │           │   orders/fills)       │──── start_combined ──┐
         │           │                       │                      │
         │           │  Counters preserved   │                      │
         │           │  Positions preserved  │                      │
         │           └───────────────────────┘                      │
         │                                                          │
         │                                         (resumes without │
         │                                          reloading LFSR  │
         │                                          or clearing     │
         ▼                                          counters)       │
  ┌──────────────┐                                                  │
  │    RESET     │                                    RUNNING ◄─────┘
  └──────────────┘
```

**Key design decision — IDLE → RUNNING vs STOPPED → RUNNING**:

These two transitions behave differently:

| Transition | What happens | Why |
|------------|-------------|-----|
| IDLE → RUNNING | `lfsr_load` fires (seed loaded into LFSR), init prices latched, fresh start | First run after configuration — start clean |
| STOPPED → RUNNING | NO `lfsr_load`, NO counter clear — simply resumes quote generation | Pause/resume — prices continue where they left off |

This distinction matters: if you stop and restart, the price walk should continue smoothly from where it paused, not jump back to the initial seed. The LFSR seed is only loaded on the IDLE → RUNNING edge.

**State Transition Table**:

| Current State | Input | Next State | Notes |
|---------------|-------|------------|-------|
| RESET | (automatic, 1 cycle) | IDLE | Counters cleared, FIFOs flushed |
| IDLE | `start_combined` | RUNNING | Loads LFSR seed, latches init prices |
| IDLE | `reset_combined` | RESET | Re-clears (no-op effectively) |
| IDLE | (no input) | IDLE | Waiting for config + start |
| RUNNING | `stop_combined` | STOPPED | Quotes stop, exchange drains |
| RUNNING | `reset_combined` | RESET | Full reset, clears everything |
| RUNNING | (no input) | RUNNING | Active trading |
| STOPPED | `start_combined` | RUNNING | Resumes (no seed reload, no clear) |
| STOPPED | `reset_combined` | RESET | Full reset, clears everything |
| STOPPED | (no input) | STOPPED | Paused, exchange draining |
| Any state | `rst` (global) | RESET | Power-on / hard reset |

**Moore Output Table**:

| State | `running` | `counter_clr` | `lfsr_load` | `fifo_flush` | market_sim | exchange_lite |
|-------|-----------|---------------|-------------|-------------|------------|---------------|
| RESET | 0 | 1 | 0 | 1 | OFF | OFF |
| IDLE | 0 | 0 | 0 | 0 | OFF | OFF |
| RUNNING | 1 | 0 | 0 | 0 | ON | ON |
| STOPPED | 0 | 0 | 0 | 0 | OFF | ON (draining) |

**Note**: `lfsr_load` is NOT a Moore output — it is a **transition-triggered pulse** (Mealy-style) that fires for exactly 1 cycle on the IDLE → RUNNING edge only. All other outputs are pure Moore (depend only on current state).

**Expanded Control Flow — How Signals Connect**:

This diagram shows how the FSM, AXI registers, Ctrl block, and data-plane modules interact with actual signal names from the RTL.

```
╔══════════════════════════════════════════════════════════════════════════════╗
║                    BOARD A — CONTROL SIGNAL FLOW                            ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                              ║
║  PHYSICAL INPUTS                          AXI-LITE REGISTER INPUTS           ║
║  ────────────────                         ──────────────────────────          ║
║                                                                              ║
║  btn[3:0] ──►┌────────────────┐           ┌────────────────────────┐         ║
║  sw[7:0]  ──►│  BOARD_A_CTRL  │           │  BOARD_A_AXI_REGS      │         ║
║              │                │           │                        │         ║
║              │  Debounce x4   │           │  CTRL_REG[0]     ──────┼──► axi_start_pulse  ║
║              │  Edge detect   │           │  CTRL_REG[1]     ──────┼──► axi_reset_pulse  ║
║              │                │           │  REGIME_REG[1:0] ──────┼──► regime_from_ps   ║
║              │  btn_pulse[0] ─┼──► ctrl_start_pulse                │         ║
║              │  btn_pulse[1] ─┼──► ctrl_stop_pulse                 │         ║
║              │  btn_pulse[2] ─┼──► ctrl_reset_pulse                │         ║
║              │                │           │  QUOTE_INTERVAL  ──────┼──► quote_interval_reg║
║              │  sw[1:0]  ────┼──► regime_sw[1:0]                  │         ║
║              │  sw[2]    ────┼──► sw_override                     │         ║
║              └────────────────┘           │  LFSR_SEED       ──────┼──► lfsr_seed_reg    ║
║                                           │  SYMx_INIT_MID   ─────┼──► sym_init_mid[s]  ║
║                                           │  SYMx_INIT_SPREAD ────┼──► sym_init_spread[s]║
║              SIGNAL COMBINING             └────────────────────────┘         ║
║              ─────────────────                                               ║
║                                                                              ║
║  start_combined = axi_start_pulse | ctrl_start_pulse                         ║
║  stop_combined  = ctrl_stop_pulse                                            ║
║  reset_combined = axi_reset_pulse | ctrl_reset_pulse                         ║
║                                                                              ║
║  active_regime  = sw_override ? regime_sw : ctrl_reg[3:2]                    ║
║       (switches take priority when SW[2] is high)                            ║
║                                                                              ║
║                         │ start_combined                                     ║
║                         │ stop_combined                                      ║
║                         │ reset_combined                                     ║
║                         ▼                                                    ║
║              ┌─────────────────────────┐                                     ║
║              │      BOARD A FSM        │                                     ║
║              │  (Moore + 1 Mealy edge) │                                     ║
║              │                         │                                     ║
║              │  RESET ──► IDLE ──►     │                                     ║
║              │    RUNNING ◄──► STOPPED │                                     ║
║              └───────┬─────────────────┘                                     ║
║                      │                                                       ║
║              ┌───────┴─────────────────────────────────────────┐             ║
║              │                                                 │             ║
║              │  MOORE OUTPUTS (depend only on current state):  │             ║
║              │  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  │             ║
║              │                                                 │             ║
║              │  running ─────────► market_sim.enable            │             ║
║              │          ─────────► status_reg[0]               │             ║
║              │          ─────────► led[2] (running LED)        │             ║
║              │                                                 │             ║
║              │  counter_clr ─────► clears quotes_sent,         │             ║
║              │                     orders_rcvd, fills_sent,    │             ║
║              │                     rejects_sent, link_errors   │             ║
║              │                     (active in RESET only)      │             ║
║              │                                                 │             ║
║              │  fifo_flush ──────► quote_fifo.clear            │             ║
║              │                     (active in RESET only)      │             ║
║              │                                                 │             ║
║              │  MEALY EDGE PULSE (transition-triggered):       │             ║
║              │  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  │             ║
║              │                                                 │             ║
║              │  lfsr_load ───────► market_sim.load_seed        │             ║
║              │    (1-cycle pulse, fires ONLY on                │             ║
║              │     IDLE → RUNNING transition;                  │             ║
║              │     loads lfsr_seed_reg into LFSR32;            │             ║
║              │     does NOT fire on STOPPED → RUNNING          │             ║
║              │     so price walk resumes smoothly)             │             ║
║              │                                                 │             ║
║              └─────────────────────────────────────────────────┘             ║
║                                                                              ║
║  ACTIVE_REGIME ──► market_sim.regime ──► controls step_size, base_spread,    ║
║  (live, can change    quote_interval                                         ║
║   during RUNNING)                                                            ║
║                                                                              ║
║                                                                              ║
║  STATUS FEEDBACK TO AXI REGS & CTRL                                          ║
║  ────────────────────────────────────                                        ║
║                                                                              ║
║  running ──────────────► ctrl.running (drives LED[2], LED[3] blink)          ║
║  active_regime ────────► ctrl.active_regime (drives LED[1:0], RGB0 color)    ║
║  link_up ──────────────► ctrl.link_up (drives LED[4], RGB1 health)           ║
║  link_error_count ─────► ctrl.link_error_count (drives LED[5] error flag)    ║
║                                                                              ║
║  LED SUMMARY:                                                                ║
║    led[1:0] = active_regime (binary)                                         ║
║    led[2]   = running                                                        ║
║    led[3]   = running & blink (25-bit counter MSB, ~3 Hz)                    ║
║    led[4]   = link_up                                                        ║
║    led[5]   = (link_error_count != 0)                                        ║
║    led[7:6] = 2'b00 (unused)                                                ║
║                                                                              ║
║  RGB0: regime color (green/yellow/red/magenta)                               ║
║  RGB1: link health (green=OK, red=down)                                      ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
```

**Note — Regime selection is FSM-independent**: The `active_regime` signal is a purely combinational mux (`sw_override ? regime_sw : ctrl_reg[3:2]`) that feeds `market_sim.regime` directly, bypassing the FSM entirely. You can flip the regime switches at any time — even mid-run — and the market simulator picks up the new regime on its next quote cycle. The FSM only controls *whether* quotes are generated (`running`); the regime controls *how* they are generated (step size, spread, interval). These are orthogonal control paths.

**How to implement Board A control — summary**:

1. **Ctrl block** (`board_a_ctrl.sv`): Instantiate 4 debounce modules (one per button), extract `btn_pulse[0..2]` for start/stop/reset, wire `sw[1:0]` as `regime_sw` and `sw[2]` as `sw_override`. Drive LEDs and RGB based on status inputs.

2. **Signal combining** (in `board_a_top.sv`): OR the AXI register pulses with the Ctrl button pulses to produce `start_combined`, `stop_combined`, `reset_combined`. Select regime via `sw_override ? regime_sw : ctrl_reg[3:2]`.

3. **FSM** (in `board_a_top.sv`): A 4-state machine (RESET → IDLE → RUNNING ↔ STOPPED). `running` is the key Moore output — it gates `market_sim.enable`. `lfsr_load` is a Mealy-style 1-cycle pulse that fires **only** on the IDLE → RUNNING transition (never on STOPPED → RUNNING) to load the LFSR seed without disrupting the price walk on resume. In RESET, `counter_clr` and `fifo_flush` are asserted. In STOPPED, exchange_lite remains active to drain pending fills.

4. **Status feedback**: Wire `running`, `active_regime`, `link_up`, and `link_error_count` back to both the Ctrl block (for LED/RGB display) and the AXI register block (for PS readback).

#### 4.4.5 Board B Operational States

**FSM Type**: Moore machine — outputs depend only on the current state (with one exception: `risk_halt` causes a forced transition to HALTED, which is closer to Mealy but acts like an asynchronous override).

**State Encoding**: 3-bit (`state[2:0]`), 5 states.

**Inputs to the FSM**:

| Signal | Source | Description |
|--------|--------|-------------|
| `rst` | System reset (power-on or external) | Global synchronous reset |
| `start_combined` | `axi_start_pulse OR ctrl_start_pulse` | Start trading from PS register write OR BTN[0] press |
| `stop_combined` | `ctrl_stop_pulse` | Stop trading from BTN[1] press |
| `reset_combined` | `axi_reset_pulse OR ctrl_reset_pulse` | Full reset from PS register write OR BTN[2] press |
| `link_up` | `link_rx` module | Link layer synchronized and receiving valid frames |
| `trading_enable` | SW[0] | 0 = armed/observe only, 1 = live trading allowed |
| `risk_halt` | `risk_manager` | Asserted when `total_pnl < -max_loss` (latched in risk_manager until cleared) |

**State Diagram**:

```
                              rst (global)
                                  │
                                  ▼
                     ┌───────────────────────┐
                     │        RESET          │
                     │    (state = 3'b000)   │
                     │                       │
                     │  Outputs:             │
                     │   order_enable  = 0   │
                     │   counter_clr   = 1   │
                     │   position_clr  = 1   │
                     │   hist_clr      = 1   │
                     │   fifo_flush    = 1   │
                     │                       │
                     │  All counters cleared  │
                     │  All positions zeroed  │
                     │  Histogram cleared     │
                     │  All FIFOs flushed     │
                     └───────────┬───────────┘
                                 │
                                 │ (automatic, 1 cycle)
                                 │
                                 ▼
                     ┌───────────────────────┐
                     │         IDLE          │
                     │    (state = 3'b001)   │
                     │                       │
                     │  No quotes arriving.  │
                     │  Waiting for Board A  │
                     │  link to synchronize. │
                     │                       │
                     │  PS can write config: │
                     │   threshold, ema_α,   │
                     │   base_qty, max_pos,  │
                     │   max_loss, strategy  │
                     └───────────┬───────────┘
                                 │
                                 │ link_up
                                 │ (link_rx receiving valid frames)
                                 │
         reset_combined          ▼
         ┌───────────┌───────────────────────┐
         │           │        ARMED          │◄──────────────────────┐
         │           │    (state = 3'b010)   │                       │
         │           │                       │                       │
         ├───────────│  Quotes flowing.      │                       │
         │           │  quote_book updating. │                       │
         │           │  feature_compute:     │                       │
         │           │   EMA converging.     │                       │
         │           │                       │                       │
         │           │  Orders SUPPRESSED    │                       │
         │           │  (order_enable = 0)   │                       │
         │           │                       │                       │
         │           │  Observe market       │                       │
         │           │  before committing.   │                       │
         │           └───────────┬───────────┘                       │
         │                       │                                   │
         │                       │ start_combined                    │
         │                       │ AND trading_enable (SW[0] = 1)    │
         │                       │                                   │
         │  reset_combined       ▼                                   │
         │           ┌───────────────────────┐  stop_combined        │
         ├───────────│       TRADING         │──── OR ───────────────┘
         │           │    (state = 3'b011)   │  !trading_enable
         │           │                       │  (SW[0] flipped to 0)
         │           │  Full pipeline live.  │
         │           │  Orders generated     │
         │           │   and sent.           │
         │           │                       │
         │           │  order_enable = 1     │
         │           │                       │
         │           └───────────┬───────────┘
         │                       │
         │                       │ risk_halt
         │                       │ (total_pnl < -max_loss)
         │                       │
         │  reset_combined       ▼
         │           ┌───────────────────────┐
         └───────────│       HALTED          │
                     │    (state = 3'b100)   │
                     │                       │
                     │  CIRCUIT BREAKER      │
                     │  Max loss breached.   │
                     │  Orders suppressed.   │
                     │  Positions frozen.    │
                     │                       │
                     │  order_enable = 0     │
                     │  risk_halt_led = 1    │
                     │                       │
                     │  ONLY exit: reset     │
                     └───────────────────────┘
```

**Why 5 states (vs Board A's 4)?**

Board B has two extra concerns that Board A doesn't:

| Concern | Board A | Board B |
|---------|---------|---------|
| Link dependency | Board A *generates* the link data — it's always available | Board B *receives* link data — must wait for `link_up` |
| Risk circuit breaker | Board A has no PnL exposure — no risk of runaway loss | Board B executes trades — must be able to hard-stop on max loss |

The **ARMED** state bridges the gap between "link is up" and "human says go." This gives:
1. **EMA warmup** — feature_compute runs for several hundred quotes, allowing EMA values to converge before any trading decisions are made
2. **Observation** — the operator can watch dashboard telemetry (prices, spreads, features) and confirm the market looks sane before committing capital
3. **Strategy warmup** (stretch goals) — momentum and NN strategies also need warmup data; ARMED lets them stabilize

The **HALTED** state is a **one-way circuit breaker**: once max loss is breached, the only way back is a full reset. This prevents a malfunctioning strategy from losing more money.

**State Transition Table**:

| Current State | Input | Next State | Notes |
|---------------|-------|------------|-------|
| RESET | (automatic, 1 cycle) | IDLE | All counters/positions/histogram cleared |
| IDLE | `link_up` | ARMED | Link synchronized, quotes arriving |
| IDLE | `reset_combined` | RESET | Re-clears (no-op effectively) |
| IDLE | (no input) | IDLE | Waiting for Board A |
| ARMED | `start_combined` AND `trading_enable` | TRADING | Human commits to live trading |
| ARMED | `reset_combined` | RESET | Full reset |
| ARMED | (no input) | ARMED | Observing, EMA converging |
| TRADING | `stop_combined` | ARMED | Voluntary stop — back to observation |
| TRADING | `!trading_enable` | ARMED | SW[0] flipped down — immediate disengage |
| TRADING | `risk_halt` | HALTED | Max loss breached — circuit breaker |
| TRADING | `reset_combined` | RESET | Full reset |
| TRADING | (no input) | TRADING | Active trading |
| HALTED | `reset_combined` | RESET | Only exit — clears everything |
| HALTED | (no input) | HALTED | Dead stop |
| Any state | `rst` (global) | RESET | Power-on / hard reset |

**Transition priority** (highest first within TRADING): `rst` > `reset_combined` > `risk_halt` > `stop_combined / !trading_enable` > hold.

**Moore Output Table**:

| State | `order_enable` | `counter_clr` | `position_clr` | `hist_clr` | `fifo_flush` | `risk_halt_led` |
|-------|---------------|---------------|----------------|-----------|-------------|----------------|
| RESET | 0 | 1 | 1 | 1 | 1 | 0 |
| IDLE | 0 | 0 | 0 | 0 | 0 | 0 |
| ARMED | 0 | 0 | 0 | 0 | 0 | 0 |
| TRADING | 1 | 0 | 0 | 0 | 0 | 0 |
| HALTED | 0 | 0 | 0 | 0 | 0 | 1 |

**Key output**: `order_enable` — this single bit gates the strategy→risk→order pipeline. In ARMED, the entire upstream pipeline (quote_book → feature_compute → strategy_engine) runs normally, but `order_enable = 0` prevents `order_manager` from emitting any ORDER frames. This means the strategy is "thinking" but not acting.

**How `order_enable` connects to the pipeline**:

```
risk_manager output:
  approved = pass_position & pass_rate & pass_loss & order_enable & !risk_halt

When order_enable = 0 (ARMED or HALTED):
  approved is always 0 → order_manager never fires → no ORDER frames → no fills → no PnL change
```

**Note — Strategy selection is FSM-independent**: Just like Board A's regime selection, the active strategy is controlled by a purely combinational path that does not interact with the FSM:

```
                                  ┌──────────────┐
                       ┌──────────│  Core build   │
                       │          │  (no stretch) │
                       │          └──────────────┘
                       │
                       │   strategy_engine ──────────────────────► risk_manager
                       │   (mean-reversion only, direct connection)
                       │
                       │
  ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┤ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─
                       │
                       │          ┌──────────────┐
                       └──────────│ With stretch │
                                  │   goals      │
                                  └──────────────┘
                                                           active_strategy
                                                              [1:0]
                                                                │
                       ┌─────────────────┐                      │
                       │ strategy_engine  │──(mean-rev)──┐      │
                       │ strategy_momentum│──(momentum)──┤      ▼
                       │ strategy_nn      │──(neural )──┤ ┌──────────┐
                       └─────────────────┘              └─│ strategy │──► risk_manager
                         (all run in parallel)            │ _selector│
                                                          └──────────┘
                                                           (comb mux)
```

**Strategy selection logic** (in `board_b_top.sv`):

```
active_strategy = sw_strategy_override ? strategy_sw[1:0] : strategy_sel_reg[1:0]
```

| `active_strategy` | Strategy module | Build |
|-------------------|----------------|-------|
| 2'b00 | Mean-reversion (`strategy_engine`) | Core (default) |
| 2'b01 | Momentum (`strategy_momentum`) | Stretch |
| 2'b10 | Neural network (`strategy_nn`) | Stretch |
| 2'b11 | Auto / adaptive (`regime_detector` selects) | Stretch |

**Modularity design**: In core build, `board_b_top.sv` simply wires `strategy_engine` output directly to `risk_manager` input. The `active_strategy` signal exists but is hardwired to `2'b00`. SW[1:2] are mapped as "reserved." To add stretch goals:

1. Instantiate `strategy_momentum`, `strategy_nn`, and `strategy_selector` in `board_b_top.sv`
2. Route all three strategy outputs into `strategy_selector`
3. Replace the direct wire with the selector output
4. SW[1:2] become active (no XDC or ctrl changes needed — pins were already mapped)
5. Add `regime_detector` + `volatility_estimator` for auto mode

**No FSM changes required.** The FSM continues to produce `order_enable` regardless of which strategy is active. The strategy path is purely a data-plane concern.

**Expanded Control Flow — How Signals Connect**:

```
╔══════════════════════════════════════════════════════════════════════════════╗
║                    BOARD B — CONTROL SIGNAL FLOW                            ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                              ║
║  PHYSICAL INPUTS                          AXI-LITE REGISTER INPUTS           ║
║  ────────────────                         ──────────────────────────          ║
║                                                                              ║
║  btn[3:0] ──►┌────────────────┐           ┌────────────────────────┐         ║
║  sw[7:0]  ──►│  BOARD_B_CTRL  │           │  BOARD_B_AXI_REGS      │         ║
║              │                │           │                        │         ║
║              │  Debounce x4   │           │  CTRL_REG[0]     ──────┼──► axi_start_pulse  ║
║              │  Edge detect   │           │  CTRL_REG[1]     ──────┼──► axi_reset_pulse  ║
║              │                │           │                        │         ║
║              │  btn_pulse[0] ─┼──► ctrl_start_pulse                │         ║
║              │  btn_pulse[1] ─┼──► ctrl_stop_pulse                 │         ║
║              │  btn_pulse[2] ─┼──► ctrl_reset_pulse                │         ║
║              │                │           │  STRATEGY_SEL    ──────┼──► strategy_sel_reg  ║
║              │  sw[0]    ────┼──► trading_enable                  │         ║
║              │  sw[2:1]  ────┼──► strategy_sw[1:0]               │         ║
║              │  sw[3]    ────┼──► sw_strategy_override            │         ║
║              └────────────────┘           │  THRESHOLD       ──────┼──► threshold_reg     ║
║                                           │  EMA_ALPHA       ──────┼──► ema_alpha_reg     ║
║              SIGNAL COMBINING             │  BASE_QTY        ──────┼──► base_qty_reg      ║
║              ─────────────────            │  MAX_POSITION    ──────┼──► max_position_reg  ║
║                                           │  MAX_ORDER_RATE  ──────┼──► max_order_rate_reg║
║  start_combined = axi_start_pulse         │  MAX_LOSS        ──────┼──► max_loss_reg      ║
║                   | ctrl_start_pulse      └────────────────────────┘         ║
║  stop_combined  = ctrl_stop_pulse                                            ║
║  reset_combined = axi_reset_pulse                                            ║
║                   | ctrl_reset_pulse                                         ║
║                                                                              ║
║  active_strategy = sw_strategy_override                                      ║
║                    ? strategy_sw[1:0]                                        ║
║                    : strategy_sel_reg[1:0]                                   ║
║       (core build: hardwired to 2'b00 = mean-reversion)                     ║
║                                                                              ║
║                         │ start_combined                                     ║
║                         │ stop_combined                                      ║
║                         │ reset_combined                                     ║
║                         │ link_up                                            ║
║                         │ trading_enable                                     ║
║                         │ risk_halt                                          ║
║                         ▼                                                    ║
║              ┌─────────────────────────┐                                     ║
║              │      BOARD B FSM        │                                     ║
║              │     (5-state Moore)     │                                     ║
║              │                         │                                     ║
║              │  RESET → IDLE →         │                                     ║
║              │    ARMED ↔ TRADING      │                                     ║
║              │              → HALTED   │                                     ║
║              └───────┬─────────────────┘                                     ║
║                      │                                                       ║
║              ┌───────┴─────────────────────────────────────────┐             ║
║              │                                                 │             ║
║              │  MOORE OUTPUTS:                                 │             ║
║              │  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  │             ║
║              │                                                 │             ║
║              │  order_enable ────► risk_manager.order_enable    │             ║
║              │    (1 only in TRADING — gates order generation)  │             ║
║              │                                                 │             ║
║              │  counter_clr ─────► clears orders_sent,         │             ║
║              │                     risk_rejects, quotes_rcvd,  │             ║
║              │                     demux_errors, fills_rcvd,   │             ║
║              │                     link_errors                 │             ║
║              │                     (active in RESET only)      │             ║
║              │                                                 │             ║
║              │  position_clr ────► position_tracker.clear       │             ║
║              │                     (zeros position[0..3],      │             ║
║              │                      cash accumulator)          │             ║
║              │                     (active in RESET only)      │             ║
║              │                                                 │             ║
║              │  hist_clr ────────► latency_histogram.clear      │             ║
║              │                     (zeros all 16 bins,         │             ║
║              │                      min/max/sum/count)         │             ║
║              │                     (active in RESET only)      │             ║
║              │                                                 │             ║
║              │  fifo_flush ──────► clears RX/TX FIFOs          │             ║
║              │                     (active in RESET only)      │             ║
║              │                                                 │             ║
║              │  risk_halt_led ───► ctrl.risk_halted             │             ║
║              │                     (drives RGB1 red,           │             ║
║              │                      LED pattern)               │             ║
║              │                     (1 only in HALTED)          │             ║
║              │                                                 │             ║
║              └─────────────────────────────────────────────────┘             ║
║                                                                              ║
║  ACTIVE_STRATEGY ──► strategy_selector.sel ──► muxes strategy output         ║
║  (FSM-independent,   to risk_manager input                                   ║
║   live, can change    (core build: no selector, direct wire)                 ║
║   during any state)                                                          ║
║                                                                              ║
║                                                                              ║
║  STATUS FEEDBACK TO AXI REGS & CTRL                                          ║
║  ────────────────────────────────────                                        ║
║                                                                              ║
║  state[2:0] ──────────► status_reg (PS can read current state)               ║
║  order_enable ─────────► ctrl.trading_active (LED indicator)                 ║
║  risk_halt ────────────► ctrl.risk_halted (RGB1 red, LED flash)              ║
║  link_up ──────────────► ctrl.link_up (LED[4])                               ║
║  link_error_count ─────► ctrl.link_errors (LED[5] error flag)                ║
║  active_strategy ──────► status_reg (PS reads for dashboard)                 ║
║                                                                              ║
║  LED SUMMARY:                                                                ║
║    led[3:0] = order_activity (4-bit shift register, flash per order sent)    ║
║    led[7:4] = fill_activity (4-bit shift register, flash per fill received)  ║
║                                                                              ║
║  RGB0: PnL indicator                                                         ║
║    green  = total_pnl > 0 (profit)                                           ║
║    red    = total_pnl < 0 (loss)                                             ║
║    off    = total_pnl == 0 (flat)                                            ║
║                                                                              ║
║  RGB1: Risk status                                                           ║
║    green  = OK (position < 80% of max)                                       ║
║    yellow = near limit (position ≥ 80% of max)                               ║
║    red    = HALTED (risk_halt asserted)                                      ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
```

**How to implement Board B control — summary**:

1. **Ctrl block** (`board_b_ctrl.sv`): Same architecture as Board A — 4 debounce modules, edge detect for `btn_pulse[0..2]`. Wire `sw[0]` as `trading_enable`, `sw[2:1]` as `strategy_sw` (reserved in core), `sw[3]` as `sw_strategy_override` (reserved in core). Drive LEDs with order/fill activity shift registers, RGB0 with PnL sign, RGB1 with risk status.

2. **Signal combining** (in `board_b_top.sv`): OR AXI pulses with button pulses for `start_combined`, `stop_combined`, `reset_combined`. Strategy mux: `sw_strategy_override ? strategy_sw : strategy_sel_reg` (hardwired to `2'b00` in core build).

3. **FSM** (in `board_b_top.sv`): 5-state Moore machine. `order_enable` is the key output — it gates `risk_manager.approved`. In RESET, clear all counters, positions, histogram, and FIFOs. IDLE waits for `link_up`. ARMED runs the full upstream pipeline but suppresses orders (EMA warmup + observation). TRADING enables order flow. HALTED is a one-way circuit breaker — only exit is `reset_combined`.

4. **Risk halt path**: `risk_manager` latches `risk_halt` when `total_pnl < -max_loss`. This signal feeds back to the FSM as an input. The FSM transitions TRADING → HALTED on `risk_halt`. The latch in `risk_manager` is cleared by `counter_clr` (which fires in RESET state).

5. **Strategy modularity** (stretch goal upgrade path):
   - **Core**: `strategy_engine` → `risk_manager` (direct wire). No selector module.
   - **Stretch**: Add `strategy_selector` between strategy outputs and `risk_manager`. Instantiate `strategy_momentum`, `strategy_nn`. All run in parallel; selector muxes. Zero latency overhead. FSM unchanged.

6. **Status feedback**: Wire `state`, `order_enable`, `risk_halt`, `link_up`, `link_error_count`, and `active_strategy` back to both Ctrl (LED/RGB) and AXI register block (PS readback → UART → dashboard).

### 4.5 Board-to-Board Link Layer

The link layer is the physical and logical bridge between Board A and Board B. It must be **full-duplex** (both directions simultaneously), **deterministic** (fixed latency per frame), and **lossless** (hardware backpressure, no dropped data).

#### 4.5.1 Physical Layout

The AUP-ZU3 board [4] has a single **Pmod+ connector** providing:
- **PmodA header** (JA): 8 signal pins + 2 VCC + 2 GND (standard 12-pin)
- **PmodB header** (JB): 8 signal pins + 2 VCC + 2 GND (standard 12-pin)
- **Pmod+ extension** (JAB): 6 additional signal pins

All PMOD signal pins are routed to **LVCMOS33** (3.3V I/O bank) on the XCZU3EG.

**Critical constraint from reference manual [4]**: PMOD signals support speeds **up to approximately 50 MHz**.

We use **two standard 12-pin PMOD ribbon cables** — one per direction. Each cable carries 4 data bits + 1 valid + 1 ready, leaving 2 spare pins per header.

**Cable 1 — PmodA: Board A → Board B (Quotes + Fills)**

| PMOD Pin | Signal Name | FPGA Ball | Board A Dir | Board B Dir | Function |
|----------|-------------|-----------|-------------|-------------|----------|
| JA[0] | `link_a2b_data[0]` | J12 | OUTPUT | INPUT | Data nibble bit 0 |
| JA[1] | `link_a2b_data[1]` | H12 | OUTPUT | INPUT | Data nibble bit 1 |
| JA[2] | `link_a2b_data[2]` | H11 | OUTPUT | INPUT | Data nibble bit 2 |
| JA[3] | `link_a2b_data[3]` | G10 | OUTPUT | INPUT | Data nibble bit 3 |
| JA[4] | `link_a2b_valid` | K13 | OUTPUT | INPUT | High during active frame transmission |
| JA[5] | `link_a2b_ready` | K12 | INPUT | OUTPUT | Backpressure: Board B can accept data |
| JA[6] | spare_a0 | J11 | — | — | Reserved (8-bit upgrade) |
| JA[7] | spare_a1 | J10 | — | — | Reserved (8-bit upgrade) |

**Cable 2 — PmodB: Board B → Board A (Orders)**

| PMOD Pin | Signal Name | FPGA Ball | Board A Dir | Board B Dir | Function |
|----------|-------------|-----------|-------------|-------------|----------|
| JB[0] | `link_b2a_data[0]` | E12 | INPUT | OUTPUT | Data nibble bit 0 |
| JB[1] | `link_b2a_data[1]` | D11 | INPUT | OUTPUT | Data nibble bit 1 |
| JB[2] | `link_b2a_data[2]` | B11 | INPUT | OUTPUT | Data nibble bit 2 |
| JB[3] | `link_b2a_data[3]` | A10 | INPUT | OUTPUT | Data nibble bit 3 |
| JB[4] | `link_b2a_valid` | C11 | INPUT | OUTPUT | High during active frame transmission |
| JB[5] | `link_b2a_ready` | B10 | OUTPUT | INPUT | Backpressure: Board A can accept data |
| JB[6] | spare_b0 | A12 | — | — | Reserved (8-bit upgrade) |
| JB[7] | spare_b1 | A11 | — | — | Reserved (8-bit upgrade) |

**Physical wiring diagram**:

```
  Board A (Exchange)                              Board B (Trader)
  ════════════════                                ════════════════

  ┌──────────────┐   Cable 1 (PmodA ribbon)       ┌──────────────┐
  │  link_tx     │──── data[3:0] ────────────────►│  link_rx     │
  │  (serialize) │──── valid     ────────────────►│  (deserialize)│
  │              │◄─── ready     ─────────────────│              │
  │              │          Quotes + Fills         │              │
  └──────────────┘                                └──────────────┘

  ┌──────────────┐   Cable 2 (PmodB ribbon)       ┌──────────────┐
  │  link_rx     │◄─── data[3:0] ─────────────────│  link_tx     │
  │  (deserialize)│◄─── valid     ─────────────────│  (serialize) │
  │              │──── ready     ────────────────►│              │
  │              │          Orders                 │              │
  └──────────────┘                                └──────────────┘
```

Both directions are **completely independent and full-duplex**. Board A can be sending a QUOTE while simultaneously receiving an ORDER. There is no shared bus, no arbitration between directions, and no turn-around penalty.

**Stretch goal — 8-bit upgrade** (`LINK_DATA_W = 8`):

In 8-bit mode, all 8 pins on each PMOD header carry data. The `valid` and `ready` signals move to the Pmod+ JAB extension pins:

| JAB Pin | FPGA Ball | Signal (8-bit mode) |
|---------|-----------|---------------------|
| JAB[0] | F12 | `link_a2b_valid` |
| JAB[1] | G11 | `link_a2b_ready` |
| JAB[2] | E10 | `link_b2a_valid` |
| JAB[3] | F10 | `link_b2a_ready` |
| JAB[4] | — | Spare |
| JAB[5] | — | Spare |

JAB pins are not on the standard PMOD ribbon cable — they require individual **Dupont jumper wires** soldered or clipped to the Pmod+ through-holes.

#### 4.5.2 Clocking Strategy — Mesochronous (No Forwarded Clock)

Both boards run their PL at **100 MHz** from their own independent PS FCLK0 oscillator. These are nominally the same frequency but come from **separate crystal oscillators** — they are not phase-locked and may drift by up to ±50 ppm relative to each other.

**Data is output at an effective 50 MHz rate** using a clock-enable toggle: each data nibble is held stable for 2 `core_clk` cycles (20 ns), which is within the ~50 MHz PMOD speed limit.

**No forwarded clock pin is needed.** The receiver synchronizes the incoming `valid` signal through a **2-FF synchronizer** and uses it to detect frame boundaries. Data is sampled on the `core_clk` edge where synchronized `valid` is stable.

```
TX side (Board A or B sending):
  core_clk: _/‾\_/‾\_/‾\_/‾\_/‾\_/‾\_/‾\_/‾\_ ...    (100 MHz)
  tick:      0  1  0  1  0  1  0  1  0  1  0  1 ...    (toggles every cycle = 50 MHz enable)

  On each tick=1 edge:
    Drive data[3:0] with next nibble of 128-bit frame (MSB first)
    Hold data stable until next tick=1 (2 core_clk cycles = 20 ns)

  valid: ___/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\___
              |<----------- 32 data beats (640 ns) -------->| gap
              N0   N1   N2   N3   ...   N30  N31    idle
```

```
RX side (Board A or B receiving):
  1. 2-FF synchronize incoming valid and data[3:0] into local core_clk domain
  2. Detect rising edge of synchronized valid → start frame capture
  3. Generate internal 50 MHz tick (phase-aligned to detected edge)
  4. Sample synchronized data on each tick for 32 beats
  5. Assemble 128-bit frame in shift register (MSB first)
  6. After 32 beats: frame complete → push to output FIFO, pulse frame_out_valid
  7. Assert ready = !(output_fifo_almost_full)     // backpressure
```

**Why mesochronous works here (no forwarded clock needed)**:

| Concern | Analysis |
|---------|----------|
| Data rate vs sample rate | Data changes every 20 ns (50 MHz). Receiver samples every 10 ns (100 MHz). This gives **2x oversampling** — ample setup/hold margin. |
| Clock drift over one frame | A frame is 32 beats × 20 ns = 640 ns. At ±50 ppm, max cumulative drift = 640 ns × 100 ppm = 0.064 ns — **completely negligible** (< 1% of a 10 ns clock period). |
| Inter-frame gap absorbs drift | Minimum gap of 2 data beats (40 ns) between frames resets any accumulated phase error. |
| Metastability | 2-FF synchronizer has MTBF > 10 years at 100 MHz sample rate with 20 ns data rate. |

**The only clock domain crossing in the entire design** is at the link RX boundary on each board:

```
  Board A core_clk (100 MHz)                     Board B core_clk (100 MHz)
  ┌────────────────────────────┐                 ┌────────────────────────────┐
  │  All PL logic runs here   │                 │  All PL logic runs here    │
  │  (market_sim, exchange,   │                 │  (pipeline, strategy,      │
  │   link_tx, AXI, ctrl)     │                 │   risk, link_tx, AXI)      │
  │                           │                 │                            │
  │            link_tx ───────┼── PMOD pins ───┼──► 2-FF sync ──► link_rx   │
  │            link_rx ◄──────┼── PMOD pins ◄──┼─── link_tx ◄───────────    │
  │              ▲            │                 │                            │
  │         2-FF sync         │                 │                            │
  └────────────────────────────┘                 └────────────────────────────┘
                 ▲                                              ▲
              CDC here                                       CDC here
          (only boundary)                                (only boundary)
```

#### 4.5.3 Data Protocol — Message Frames

All messages are exactly **128 bits (16 bytes)** — a fixed frame size that simplifies serialization, deserialization, and routing. The first 4 bits of every frame are the `msg_type` field, which determines how the remaining 124 bits are interpreted.

**Message types**:

| Code | Name | Direction | Purpose |
|------|------|-----------|---------|
| `4'h1` | QUOTE | A → B | Market data: bid/ask prices and sizes for one symbol |
| `4'h2` | ORDER | B → A | Trade request: buy or sell at a limit price |
| `4'h3` | FILL | A → B | Trade result: filled or rejected, with echoed timestamp |

**QUOTE frame (Board A → Board B)** — `msg_type = 4'h1`:

```
Bit Range   Width   Field            Description
─────────   ─────   ──────────────   ────────────────────────────────────────────
[127:124]     4     msg_type         4'h1 = QUOTE
[123:116]     8     symbol_id        Instrument index (0..NUM_SYMBOLS-1)
[115:114]     2     regime           00=CALM, 01=VOLATILE, 10=BURST, 11=ADVERSARIAL
[113:112]     2     reserved         2'b00
[111:80]     32     bid_price        Best bid price (unsigned Q16.16)
[79:48]      32     ask_price        Best ask price (unsigned Q16.16)
[47:32]      16     bid_size         Shares available at bid
[31:16]      16     ask_size         Shares available at ask
[15:0]       16     seq_num          Per-symbol monotonic counter
```

**ORDER frame (Board B → Board A)** — `msg_type = 4'h2`:

```
Bit Range   Width   Field            Description
─────────   ─────   ──────────────   ────────────────────────────────────────────
[127:124]     4     msg_type         4'h2 = ORDER
[123:116]     8     symbol_id        Instrument index
[115]         1     side             0 = BUY, 1 = SELL
[114:112]     3     reserved         3'b000
[111:80]     32     limit_price      Max buy / min sell price (unsigned Q16.16)
[79:64]      16     quantity         Shares to trade
[63:48]      16     order_id         Wrapping 16-bit counter assigned by Board B
[47:32]      16     timestamp        cycle_counter[15:0] at ORDER creation time
[31:0]       32     reserved         32'h0
```

**FILL frame (Board A → Board B)** — `msg_type = 4'h3`:

```
Bit Range   Width   Field            Description
─────────   ─────   ──────────────   ────────────────────────────────────────────
[127:124]     4     msg_type         4'h3 = FILL
[123:116]     8     symbol_id        Instrument index (echoed from ORDER)
[115]         1     side             Echoed from ORDER
[114:112]     3     status           000 = FILLED, 001 = REJECTED
[111:80]     32     fill_price       Execution price (Q16.16), 0 if rejected
[79:64]      16     fill_qty         Shares filled, 0 if rejected
[63:48]      16     order_id         Echoed from ORDER
[47:32]      16     ts_echo          Echoed timestamp (Board B uses for latency)
[31:0]       32     reserved         32'h0
```

**How the `timestamp` / `ts_echo` round-trip works**:

```
Board B                              Board A                              Board B
───────                              ───────                              ───────
ORDER created:                       Receives ORDER:                      Receives FILL:
  timestamp = cycle_counter[15:0]      Extracts timestamp field             ts_echo arrives
  (e.g., 0x1A3F)                       Copies into FILL.ts_echo             latency = cycle_counter[15:0] - ts_echo
                                       (0x1A3F)                             (wrapping subtraction → cycles)
         ──── link_tx ────►                   ──── link_tx ────►
              ORDER frame                          FILL frame
```

This gives **cycle-accurate round-trip latency measurement** entirely in hardware, with no software involvement.

**Serialization — link_tx**:

The 128-bit frame is serialized MSB-first into 32 nibbles (4-bit mode) or 16 bytes (8-bit mode):

```
frame[127:124] → first nibble on wire (N0)
frame[123:120] → N1
  ...
frame[3:0]     → last nibble on wire (N31)
```

The serializer uses a shift register that shifts `LINK_DATA_W` bits per tick. `valid` is held high for all 32 (or 16) beats, then driven low during the inter-frame gap.

**Deserialization — link_rx**:

The receiver assembles nibbles into a 128-bit shift register, MSB-first. After counting `BEATS_PER_FRAME` beats, the assembled frame is pushed to an output FIFO and `frame_out_valid` pulses for 1 cycle.

**Backpressure**:

- `ready` is driven by the **receiver**: `ready = !(output_fifo_almost_full)`
- The **transmitter** checks `remote_ready` (synchronized) before starting a new frame
- If `remote_ready` is low, the transmitter holds and waits — no data is lost
- FIFO depth: 64 entries per direction (sufficient for burst absorption)

**Error detection**:

- `link_rx` maintains a 32-bit `error_count` register
- Incremented when: `valid` deasserts mid-frame (before expected beat count), or `msg_type` field is not a recognized value
- Exposed to AXI-Lite for PS readback and to `ctrl` block for LED indication

#### 4.5.4 Throughput and Latency

All calculations assume the default 4-bit data width (`LINK_DATA_W = 4`).

| Metric | Value | Derivation |
|--------|-------|------------|
| Raw data rate per direction | 200 Mbps | 4 bits × 50 MHz |
| Frame size | 128 bits | Fixed for all message types |
| Beats per frame | 32 | 128 bits ÷ 4 bits |
| Time per beat | 20 ns | 2 core_clk cycles at 100 MHz |
| Serialization time per frame | 640 ns | 32 beats × 20 ns |
| Inter-frame gap (minimum) | 40 ns | 2 beats × 20 ns (absorbs clock drift) |
| Total frame period (min) | 680 ns | 640 + 40 ns |
| Max sustained frame rate | **~1.47 million frames/sec** | 1 / 680 ns |
| Link utilization at 100K qps (CALM) | ~6.8% | 100K / 1.47M |
| Link utilization at 1M qps (BURST) | ~68% | 1M / 1.47M |

**Latency breakdown for one QUOTE → ORDER → FILL round trip**:

| Step | Latency | Notes |
|------|---------|-------|
| 1. QUOTE serialization (A→B) | 640 ns | 32 beats × 20 ns |
| 2. CDC synchronizer (B side) | 20 ns | 2 FF stages × 10 ns |
| 3. Board B pipeline | 80 ns | 8 stages × 10 ns (see §4.3.2) |
| 4. ORDER serialization (B→A) | 640 ns | 32 beats × 20 ns |
| 5. CDC synchronizer (A side) | 20 ns | 2 FF stages × 10 ns |
| 6. Exchange matching (A) | 10 ns | 1 cycle |
| 7. FILL serialization (A→B) | 640 ns | 32 beats × 20 ns |
| 8. CDC synchronizer (B side) | 20 ns | 2 FF stages × 10 ns |
| **Total round trip** | **~2.07 μs** | Wire-dominated |

The pipeline processing (80 ns) is < 4% of the total round trip. The link serialization dominates. This is why the 8-bit stretch goal upgrade matters — it halves all serialization times.

**8-bit upgrade comparison** (stretch goal):

| Metric | 4-bit (core) | 8-bit (stretch) |
|--------|-------------|-----------------|
| Beats per frame | 32 | 16 |
| Serialization time | 640 ns | 320 ns |
| Max frame rate | ~1.47M fps | ~2.78M fps |
| Round-trip wire time | ~2.07 μs | ~1.11 μs |
| Wiring | 2 standard PMOD ribbon cables | 2 PMOD cables + 4 Dupont jumpers on JAB |

**Parameterization**: Only `LINK_DATA_W` in `hft_pkg.sv` changes. `link_tx` and `link_rx` are parameterized:

```systemverilog
module link_tx #(
    parameter int DATA_W = hft_pkg::LINK_DATA_W,       // 4 or 8
    parameter int FRAME_W = hft_pkg::FRAME_WIDTH,       // 128
    parameter int BEATS = FRAME_W / DATA_W              // 32 or 16
)(
    output logic [DATA_W-1:0] pmod_data,
    output logic              pmod_valid,
    input  logic              remote_ready,
    // ...
);
    logic [$clog2(BEATS)-1:0] beat_count;
    // shift DATA_W bits per beat, MSB first
endmodule
```

#### 4.5.5 Number Representation

All fixed-point formats used across the link and within both boards:

| Type | Width | Format | Range | Example |
|------|-------|--------|-------|---------|
| Price | 32 bits | Unsigned Q16.16 | 0 to 65535.9999 | $150.25 = `0x0096_4000` |
| Signed Price / PnL | 32 bits | Signed Q16.16 | −32768 to +32767.9999 | −$5.50 = `0xFFFA_8000` |
| Cash Accumulator | 48 bits | Signed Q32.16 | ±2 billion | Prevents overflow on accumulation |
| Quantity | 16 bits | Unsigned integer | 0 to 65535 | 100 shares = `0x0064` |
| Symbol ID | 8 bits | Unsigned integer | 0 to 255 | 0 = "SYM0" |
| Order ID | 16 bits | Unsigned integer | 0 to 65535 | Wrapping counter |
| Timestamp | 16 bits | Unsigned integer | 0 to 65535 | Low 16 bits of cycle counter |
| EMA Alpha | 16 bits | Unsigned Q0.16 | 0.0 to 0.9999 | α=0.1 → `6554` (6554/65536) |

**Why Q16.16 for prices?**

- 16 integer bits cover prices $0 to $65,535 — more than sufficient for any simulated instrument
- 16 fractional bits give precision to ~$0.000015 (1/65536) — well below 1 cent
- 32-bit total fits neatly in a single AXI-Lite register and one DSP48E2 operand
- Addition/subtraction of same-format values is direct — no alignment needed

**Why 48-bit Q32.16 for cash?**

Each trade adds `±(price × qty)` to cash. With `price` up to 32 bits and `qty` up to 16 bits, the product is up to 48 bits. Using a 48-bit accumulator prevents overflow even after millions of trades. The 16 fractional bits are inherited from the Q16.16 price format — the multiplication `price_32 × qty_16` naturally produces a Q32.16 result.

**Fixed-point arithmetic operations and DSP48E2 usage**:

| Operation | Formula | Width | DSP slices |
|-----------|---------|-------|-----------|
| Addition / subtraction | `a ± b` (same Q format) | 32-bit | 0 (fabric) |
| Price × Quantity | `result_48 = price_32 × qty_16` | 48-bit Q32.16 | 1 DSP48E2 |
| EMA update | `ema_new = (α × sample + (65536−α) × ema_old) >> 16` | 32-bit Q16.16 | 2 DSP48E2 |
| Deviation | `deviation = mid − ema` (signed subtraction) | 32-bit signed Q16.16 | 0 (fabric) |
| Mid price | `mid = (bid + ask) >> 1` | 32-bit Q16.16 | 0 (fabric) |
| Spread | `spread = ask − bid` | 32-bit Q16.16 | 0 (fabric) |

**EMA computation detail** (uses 2 DSP48E2 slices):

```
Given:
  alpha     : Q0.16 (e.g., 0.1 = 6554)
  sample    : Q16.16 (current mid price)
  ema_old   : Q16.16 (previous EMA value)

Compute:
  term_a = alpha × sample              // DSP #1: 16×32 → 48-bit intermediate
  term_b = (65536 - alpha) × ema_old   // DSP #2: 16×32 → 48-bit intermediate
  ema_new = (term_a + term_b) >> 16    // truncate back to Q16.16
```

The `>> 16` truncation discards the extra fractional bits introduced by the multiplication, maintaining Q16.16 format throughout the pipeline.

### 4.6 Submodule Inventory and Scalability

This section enumerates every RTL module in the design, organized by where it lives in the project hierarchy. The module list is derived directly from the data-plane architecture (§4.3), control logic (§4.4), and link layer (§4.5) sections above.

#### 4.6.1 Module Summary

**Total core modules: 23** (4 shared + 2 link + 6 Board A + 11 Board B)
**Stretch goal modules: 5** (Board B only)

#### 4.6.2 Shared / Common Modules

These modules are instantiated on **both boards** and contain no board-specific logic.

| # | Module | Description | Key Ports | Est. Resources |
|---|--------|-------------|-----------|---------------|
| 1 | `hft_pkg.sv` | **Package** — all compile-time parameters, typedefs (`price_t`, `pnl_t`, `qty_t`, `symbol_t`, `order_id_t`, `timestamp_t`), message type enum (`MSG_QUOTE`, `MSG_ORDER`, `MSG_FILL`), regime enum, frame width constants. **Single source of truth** for all parameterization. | N/A (package) | — |
| 2 | `lfsr32.sv` | 32-bit Galois LFSR with configurable polynomial. Outputs a pseudo-random 32-bit value each cycle. Used by `market_sim` for price evolution. `load` input latches a new seed from the AXI-Lite register. | `clk`, `rst`, `load`, `seed_in[31:0]` → `rand_out[31:0]` | 32 FFs |
| 3 | `debounce.sv` | 20-bit shift register debouncer for mechanical pushbuttons. Raw input is shifted in every cycle; output changes only when all 20 samples agree. Parameterized filter width. | `clk`, `rst`, `raw_in` → `clean_out` | ~20 FFs |
| 4 | `sync_fifo.sv` | Parameterized synchronous FIFO (single-clock domain). Configurable depth and width via parameters. Provides `almost_full` for backpressure and `count` for monitoring. Used for quote buffering (Board A), link RX output buffering (both boards). | `clk`, `rst`, `wr_en`, `wr_data`, `rd_en` → `rd_data`, `full`, `empty`, `almost_full`, `count` | Depth-dependent: ~64×128b = 4 BRAM18K (or distributed RAM for shallow FIFOs) |

**Why `sync_fifo` is a shared module**: Both boards need FIFO buffering — Board A for quote/fill queuing before the TX arbiter, and both boards for link RX output buffering. A single parameterized module avoids duplication. The `almost_full` output is critical: it drives the `ready` backpressure signal on the link.

#### 4.6.3 Link Layer Modules

Instantiated **once per direction on each board** (Board A: 1× link_tx for A→B, 1× link_rx for B→A; Board B: mirror).

| # | Module | Description | Key Ports | Est. Resources |
|---|--------|-------------|-----------|---------------|
| 5 | `link_tx.sv` | Serializer: loads a 128-bit frame into a shift register, outputs `DATA_W` bits per tick (50 MHz rate). Asserts `pmod_valid` for `BEATS_PER_FRAME` beats, then deasserts for the inter-frame gap. Waits for `remote_ready` before starting a new frame. Parameterized by `DATA_W` (4 or 8). | `clk`, `rst`, `frame_in[127:0]`, `frame_in_valid`, `remote_ready` → `frame_in_ready`, `pmod_data[DATA_W-1:0]`, `pmod_valid` | ~200 LUTs, 128 FFs (shift reg) |
| 6 | `link_rx.sv` | Deserializer: 2-FF synchronizes incoming `pmod_valid` and `pmod_data`, detects rising edge to start frame capture. Samples `DATA_W` bits per internal tick for `BEATS_PER_FRAME` beats. Assembles 128-bit frame in shift register. Pushes completed frames to output (via internal sync_fifo or direct output). Maintains `error_count` for framing errors. Drives `pmod_ready` from `!fifo_almost_full`. | `clk`, `rst`, `pmod_data[DATA_W-1:0]`, `pmod_valid` → `frame_out[127:0]`, `frame_out_valid`, `pmod_ready`, `error_count[31:0]`, `link_up` | ~250 LUTs, 128 FFs (shift reg), ~40 FFs (2-FF sync) |

**Valid/ready handshake at module boundaries**: Every data-plane module uses:
```
Producer drives:  out_data, out_valid
Consumer drives:  out_ready
Transfer when:    out_valid && out_ready (both high on same rising edge)
```

#### 4.6.4 Board A Modules

| # | Category | Module | Description | Key I/O (beyond clk/rst) | Est. Resources |
|---|----------|--------|-------------|--------------------------|---------------|
| 7 | Data | `market_sim.sv` | LFSR-driven price random walk. Maintains per-symbol `mid_price[NUM_SYMBOLS]` and `spread[NUM_SYMBOLS]`. On each `quote_interval` cycle (when `running` is high), updates one symbol's prices using the LFSR output scaled by `step_size` (regime-dependent). Builds a 128-bit QUOTE frame and pushes to quote_fifo. Round-robins through symbols. | `running`, `regime[1:0]`, `quote_interval`, `load_seed`, `seed[31:0]`, `sym_init_mid[0:N-1]`, `sym_init_spread[0:N-1]` → `quote_frame[127:0]`, `quote_valid`, `bid_price[0:N-1]`, `ask_price[0:N-1]`, `quotes_sent[31:0]` | ~500 LUTs, 1 DSP48E2, ~NUM_SYMBOLS×64 FFs |
| 8 | Data | `exchange_lite.sv` | Order matching engine. Receives ORDER frames from link_rx. Extracts `symbol_id`, `side`, `limit_price`. Compares against live bid/ask from market_sim. BUY fills at ask if `limit_price >= ask_price`; SELL fills at bid if `limit_price <= bid_price`; else REJECT. Builds 128-bit FILL frame with echoed `order_id` and `ts_echo`. | `order_frame[127:0]`, `order_valid`, `bid_price[0:N-1]`, `ask_price[0:N-1]` → `fill_frame[127:0]`, `fill_valid`, `orders_rcvd[31:0]`, `fills_sent[31:0]`, `rejects_sent[31:0]` | ~300 LUTs |
| 9 | Data | `tx_arbiter.sv` | Strict-priority 2:1 frame mux. Two input ports: fill (high priority) and quote (low priority). When both have valid frames, fills always go first. Outputs one frame at a time to link_tx. Ensures no frame starvation: once a quote starts serialization, it completes before a fill can preempt. | `fill_frame`, `fill_valid`, `quote_frame`, `quote_valid`, `tx_ready` → `out_frame[127:0]`, `out_valid`, `fill_ready`, `quote_ready` | ~100 LUTs |
| 10 | Control | `board_a_axi_regs.sv` | AXI-Lite slave interface. Config registers: CTRL (start/reset/regime), QUOTE_INTERVAL, LFSR_SEED, SYMx_INIT_MID, SYMx_INIT_SPREAD. Status registers (read-only): STATUS (running, link_up), quotes_sent, orders_rcvd, fills_sent, rejects_sent, link_errors, fifo_fill_level. Generates single-cycle pulses on CTRL write. | AXI-Lite bus (awaddr, wdata, araddr, rdata, etc.) → config outputs, ← status inputs | ~400 LUTs |
| 11 | Control | `board_a_ctrl.sv` | Physical I/O manager. Instantiates 4× `debounce` for buttons. Generates `btn_pulse[0..2]` (start/stop/reset). Samples switches for `regime_sw[1:0]` and `sw_override`. Drives LEDs: [1:0]=regime, [2]=running, [3]=running blink, [4]=link_up, [5]=link_errors. Drives RGB0=regime color, RGB1=link health. | `btn[3:0]`, `sw[7:0]`, `running`, `active_regime`, `link_up`, `link_error_count` → `btn_pulse[2:0]`, `regime_sw[1:0]`, `sw_override`, `led[7:0]`, `rgb0[2:0]`, `rgb1[2:0]` | ~150 LUTs |
| 12 | Top | `board_a_top.sv` | Structural wiring: instantiates all Board A modules. Contains the 4-state FSM (RESET/IDLE/RUNNING/STOPPED). Combines button + AXI trigger signals. Routes config from AXI regs to data-plane modules. Routes status from data-plane back to AXI regs and ctrl. | Top-level FPGA ports: PMOD_A, PMOD_B, btn, sw, led, rgb, AXI-Lite bus | — (structural) |

#### 4.6.5 Board B Modules

| # | Category | Module | Description | Key I/O (beyond clk/rst) | Est. Resources |
|---|----------|--------|-------------|--------------------------|---------------|
| 13 | Data | `msg_demux.sv` | Frame router. Reads `msg_type` field `[127:124]` from incoming frames. Routes QUOTE (4'h1) to quote path, FILL (4'h3) to fill path. Discards unknown types and increments `demux_errors`. | `frame_in[127:0]`, `frame_in_valid` → `quote_frame`, `quote_valid`, `fill_frame`, `fill_valid`, `demux_errors[31:0]`, `quotes_rcvd[31:0]` | ~50 LUTs |
| 14 | Data | `quote_book.sv` | Per-symbol register file. Stores latest `bid_price`, `ask_price`, `bid_size`, `ask_size` for each of `NUM_SYMBOLS` instruments. Updated by incoming QUOTE frames. Outputs current values for the symbol being processed. | `quote_frame[127:0]`, `quote_valid` → `bid_price[31:0]`, `ask_price[31:0]`, `bid_size[15:0]`, `ask_size[15:0]`, `symbol_id[7:0]`, `book_valid` | ~NUM_SYMBOLS × 96 FFs |
| 15 | Data | `feature_compute.sv` | Computes mid price, spread, and EMA for each symbol. `mid = (bid + ask) >> 1`, `spread = ask - bid`. EMA uses DSP48E2 multiply-accumulate: `ema_new = (α × mid + (65536−α) × ema_old) >> 16`. Maintains `ema[NUM_SYMBOLS]` state array. | `bid_price`, `ask_price`, `symbol_id`, `book_valid`, `ema_alpha[15:0]` → `mid[31:0]`, `spread[31:0]`, `ema[31:0]`, `deviation[31:0]` (signed), `feature_valid` | ~400 LUTs, 2 DSP48E2, ~NUM_SYMBOLS × 32 FFs |
| 16 | Data | `strategy_engine.sv` | Mean-reversion strategy (core). Compares `deviation` against configurable `threshold`. If `deviation > +threshold`: SELL at bid (price reverts down). If `deviation < -threshold`: BUY at ask (price reverts up). Else: no trade. Outputs `signal_valid`, `signal_side`, `signal_price`, `signal_qty`. | `deviation[31:0]`, `mid[31:0]`, `bid_price[31:0]`, `ask_price[31:0]`, `feature_valid`, `threshold[31:0]`, `base_qty[15:0]` → `signal_valid`, `signal_side`, `signal_price[31:0]`, `signal_qty[15:0]`, `signal_symbol[7:0]` | ~200 LUTs |
| 17 | Data | `risk_manager.sv` | Three parallel limit checks executed in 1 cycle (10 ns). (1) Position limit: `abs(position[symbol]) < max_position`. (2) Order rate: `orders_this_window < max_order_rate` (sliding window counter). (3) Max loss: `total_pnl > -max_loss`. Final gate: `approved = pass_1 & pass_2 & pass_3 & order_enable`. Latches `risk_halt` when check 3 fails (cleared by `counter_clr`). | `signal_valid`, `signal_side`, `signal_price`, `signal_qty`, `signal_symbol`, `position[0:N-1]`, `total_pnl`, `order_enable`, `max_position`, `max_order_rate`, `max_loss` → `approved_valid`, pass-through order fields, `risk_rejects[31:0]`, `risk_halt` | ~300 LUTs |
| 18 | Data | `order_manager.sv` | Builds 128-bit ORDER frames when `approved_valid` is high. Assigns `order_id` from a 16-bit wrapping counter (increments per order). Captures `timestamp = cycle_counter[15:0]`. Packs all fields into the ORDER frame format. | `approved_valid`, order fields (side, price, qty, symbol) → `order_frame[127:0]`, `order_valid`, `orders_sent[31:0]` | ~200 LUTs |
| 19 | Data | `position_tracker.sv` | Processes FILL frames. Updates signed `position[NUM_SYMBOLS]`: BUY adds qty, SELL subtracts qty. Updates 48-bit signed cash accumulator (Q32.16): SELL adds `price × qty`, BUY subtracts `price × qty`. The multiplication uses 1 DSP48E2. Exposes position array and cash for risk manager readback and AXI telemetry. | `fill_frame[127:0]`, `fill_valid`, `counter_clr`, `position_clr` → `position[0:N-1]`, `cash[47:0]`, `total_pnl[31:0]`, `fills_rcvd[31:0]` | ~300 LUTs, 1 DSP48E2, ~NUM_SYMBOLS × 48 FFs |
| 20 | Measurement | `latency_histogram.sv` | Hardware latency measurement. On each FILL, computes `latency = cycle_counter[15:0] - ts_echo` (wrapping subtraction). Maps to bin: `bin = latency >> BIN_SHIFT`. Increments `hist_bins[bin]` (16 bins × 32-bit). Updates scalar stats: `lat_min`, `lat_max`, `lat_sum`, `lat_count`. All readable via AXI-Lite. | `fill_valid`, `ts_echo[15:0]`, `hist_clr` → `hist_bins[0:15]`, `lat_min`, `lat_max`, `lat_sum`, `lat_count` | ~300 LUTs, 16 × 32 FFs (bins) |
| 21 | Control | `board_b_axi_regs.sv` | AXI-Lite slave. Config registers: CTRL (start/reset), STRATEGY_SEL, THRESHOLD, EMA_ALPHA, BASE_QTY, MAX_POSITION, MAX_ORDER_RATE, MAX_LOSS. Status registers (read-only): STATUS (state, link_up, risk_halt, active_strategy), counters (orders_sent, risk_rejects, quotes_rcvd, fills_rcvd, link_errors), per-symbol positions, cash, histogram bins, latency stats. | AXI-Lite bus → config outputs, ← status inputs | ~500 LUTs |
| 22 | Control | `board_b_ctrl.sv` | Physical I/O manager. Instantiates 4× `debounce`. Generates `btn_pulse[0..2]` (start/stop/reset). Samples `sw[0]` as `trading_enable`, `sw[2:1]` as `strategy_sw` (reserved in core), `sw[3]` as `sw_strategy_override` (reserved in core). Drives LEDs: [3:0]=order activity (flash per order), [7:4]=fill activity (flash per fill). RGB0=PnL indicator (green/red/off). RGB1=risk status (green/yellow/red). | `btn[3:0]`, `sw[7:0]`, `order_enable`, `risk_halt`, `link_up`, `total_pnl`, `position` → `btn_pulse[2:0]`, `trading_enable`, `strategy_sw[1:0]`, `sw_strategy_override`, `led[7:0]`, `rgb0[2:0]`, `rgb1[2:0]` | ~150 LUTs |
| 23 | Top | `board_b_top.sv` | Structural wiring: instantiates all Board B modules. Contains the 5-state FSM (RESET/IDLE/ARMED/TRADING/HALTED). Combines button + AXI trigger signals. Routes config from AXI regs to pipeline modules. Routes status from pipeline back to AXI regs and ctrl. In core build, wires `strategy_engine` directly to `risk_manager`. In stretch build, inserts `strategy_selector`. | Top-level FPGA ports: PMOD_A, PMOD_B, btn, sw, led, rgb, AXI-Lite bus | — (structural) |

#### 4.6.6 Stretch Goal Modules (Board B)

These modules are **not present in the core build**. They are added to `board_b_top.sv` only when the corresponding stretch goal is implemented. The FSM and control logic remain unchanged — only data-plane wiring in `board_b_top.sv` is modified (see §4.4.5 modularity design).

| # | Module | Description | Trigger to Add | Est. Resources |
|---|--------|-------------|----------------|---------------|
| S1 | `strategy_momentum.sv` | Dual-EMA crossover trend-following. Computes `trend = EMA_short(mid) - EMA_long(mid)`. If `trend > +momentum_threshold`: BUY. If `trend < -momentum_threshold`: SELL. Requires `EMA_LONG_ALPHA` config register. | Strategy stretch goal | ~300 LUTs, 2 DSP48E2 |
| S2 | `strategy_nn.sv` | 2-layer MLP inference engine. Architecture: 4 inputs → 8 hidden (ReLU) → 3 outputs (BUY/SELL/HOLD scores). Weights pretrained in Python (PyTorch), quantized to Q8.8, loaded by PS into registers or BRAM at boot. argmax over outputs → trading decision. Pipelined over ~8-10 cycles (still sub-100 ns). | Strategy stretch goal | ~1K LUTs, 8–16 DSP48E2, 1 BRAM18K |
| S3 | `strategy_selector.sv` | Combinational mux: takes outputs from all 3 strategies (mean-reversion, momentum, NN), selects one based on `active_strategy[1:0]`. All strategies run in parallel every cycle; selector just picks which one feeds `risk_manager`. **Zero additional latency** (pure combinational). | Required when S1 or S2 is added | ~50 LUTs |
| S4 | `regime_detector.sv` | Rule-based market regime classifier with hysteresis. Reads `vol_hat` (from S5) and `spread`, applies threshold-based rules to select optimal strategy. Requires condition to persist for N consecutive quotes before switching (prevents thrashing). Feeds `strategy_selector` when `active_strategy = 2'b11` (auto mode). | Adaptive switching stretch goal | ~100 LUTs |
| S5 | `volatility_estimator.sv` | Cheap real-time volatility proxy: `delta_mid = abs(mid_new - mid_old)`, `vol_hat = EMA(delta_mid, vol_alpha)`. Per-symbol state. Feeds `regime_detector`. | Required when S4 is added | ~200 LUTs, 2 DSP48E2 |

**Dependency graph for stretch modules**:

```
  S1 (strategy_momentum) ──────┐
                                ├──► S3 (strategy_selector) ──► risk_manager
  S2 (strategy_nn)       ──────┤         ▲
                                │         │
  strategy_engine (core) ──────┘    active_strategy[1:0]
                                         │
                                         │ (when auto mode = 2'b11)
                                         │
                               S4 (regime_detector)
                                         ▲
                                         │
                               S5 (volatility_estimator)
```

You can add S1 alone (just mean-rev + momentum), S1+S2 (all three strategies, manual switching), or the full set S1+S2+S3+S4+S5 (all three + auto-adaptive). S3 is always needed when more than one strategy exists.

#### 4.6.7 Module Interconnection Overview

```
┌─────────────────────── BOARD A ───────────────────────┐
│                                                        │
│  board_a_top.sv                                        │
│  ├── board_a_axi_regs.sv ◄══ AXI-Lite ══► PS          │
│  ├── board_a_ctrl.sv                                   │
│  │   └── debounce.sv ×4                                │
│  ├── market_sim.sv                                     │
│  │   └── lfsr32.sv                                     │
│  ├── sync_fifo.sv (quote_fifo, 64×128)                 │
│  ├── exchange_lite.sv                                  │
│  ├── tx_arbiter.sv                                     │
│  ├── link_tx.sv (A→B direction)                        │
│  └── link_rx.sv (B→A direction)                        │
│       └── sync_fifo.sv (rx_fifo)                       │
│                                                        │
└───────────── PMOD A (out) ─── PMOD B (in) ────────────┘
                    │                   ▲
                    ▼                   │
                PMOD A (in)       PMOD B (out)
┌───────────────────────────────────────────────────────┐
│                                                        │
│  board_b_top.sv                           BOARD B      │
│  ├── board_b_axi_regs.sv ◄══ AXI-Lite ══► PS          │
│  ├── board_b_ctrl.sv                                   │
│  │   └── debounce.sv ×4                                │
│  ├── link_rx.sv (A→B direction)                        │
│  │   └── sync_fifo.sv (rx_fifo)                        │
│  ├── msg_demux.sv                                      │
│  ├── quote_book.sv                                     │
│  ├── feature_compute.sv                                │
│  ├── strategy_engine.sv                                │
│  │   └── [strategy_selector.sv ← stretch]              │
│  │       ├── [strategy_momentum.sv ← stretch]          │
│  │       ├── [strategy_nn.sv ← stretch]                │
│  │       ├── [regime_detector.sv ← stretch]            │
│  │       └── [volatility_estimator.sv ← stretch]       │
│  ├── risk_manager.sv                                   │
│  ├── order_manager.sv                                  │
│  ├── position_tracker.sv                               │
│  ├── latency_histogram.sv                              │
│  └── link_tx.sv (B→A direction)                        │
│                                                        │
└────────────────────────────────────────────────────────┘
```

#### 4.6.8 Scalability and Parameterization

The design is built around compile-time parameters that allow scaling **without architectural changes**. All RTL must be coded against these parameters from day one — no hardcoded sizes.

**4.6.8.1 Design Parameters**

All parameters live in `hft_pkg.sv` (single source of truth):

```systemverilog
package hft_pkg;
    localparam int NUM_SYMBOLS     = 4;     // 4 for core, 8+ for stretch
    localparam int LINK_DATA_W     = 4;     // 4 for core, 8 for stretch
    localparam int FRAME_WIDTH     = 128;
    localparam int BEATS_PER_FRAME = FRAME_WIDTH / LINK_DATA_W;
    localparam int NUM_HIST_BINS   = 16;
    localparam int BIN_SHIFT       = 5;     // 32-cycle histogram bins

    // Type definitions
    typedef logic [31:0]        price_t;
    typedef logic signed [31:0] pnl_t;
    typedef logic [15:0]        qty_t;
    typedef logic [7:0]         symbol_t;
    typedef logic [15:0]        order_id_t;
    typedef logic [15:0]        timestamp_t;

    // Message types
    typedef enum logic [3:0] {
        MSG_QUOTE = 4'h1,
        MSG_ORDER = 4'h2,
        MSG_FILL  = 4'h3
    } msg_type_e;

    // Market regimes
    typedef enum logic [1:0] {
        REGIME_CALM        = 2'b00,
        REGIME_VOLATILE    = 2'b01,
        REGIME_BURST       = 2'b10,
        REGIME_ADVERSARIAL = 2'b11
    } regime_e;
endpackage
```

**4.6.8.2 Symbol Count Scaling (`NUM_SYMBOLS`)**

Every module with per-symbol state uses `NUM_SYMBOLS` to size its arrays. Changing this single parameter (and re-synthesizing) scales the entire system.

**Modules affected by `NUM_SYMBOLS`**:

| Module | What scales | Coding pattern |
|--------|-----------|---------------|
| `market_sim.sv` | `mid_price[NUM_SYMBOLS]`, `spread[NUM_SYMBOLS]`, round-robin counter width | `for (genvar s = 0; s < NUM_SYMBOLS; s++)` |
| `exchange_lite.sv` | `bid_price[NUM_SYMBOLS]`, `ask_price[NUM_SYMBOLS]` lookup | `if (symbol_id < NUM_SYMBOLS)` bounds check |
| `quote_book.sv` | `best_bid[NUM_SYMBOLS]`, `best_ask[NUM_SYMBOLS]`, sizes | Parameterized register array |
| `feature_compute.sv` | `ema[NUM_SYMBOLS]` per-symbol EMA state | Per-symbol `genvar` loop |
| `position_tracker.sv` | `position[NUM_SYMBOLS]`, single shared `cash` | Parameterized array |
| `risk_manager.sv` | Reads `position[symbol_id]` — array depth scales | Bounds-checked index |
| `board_a_axi_regs.sv` | 2 config registers per symbol (init_mid, init_spread) | `offset = 0x10 + symbol_id * 0x08` |
| `board_b_axi_regs.sv` | 1 position register per symbol (readback) | `offset = 0x58 + symbol_id * 0x04` |

**Resource cost per symbol**:

| Resource | Per Symbol | 4 Symbols | 8 Symbols | 16 Symbols |
|----------|-----------|-----------|-----------|------------|
| FFs (all modules combined) | ~208 | ~832 | ~1,664 | ~3,328 |
| % of 141,120 FFs available | — | 0.6% | 1.2% | 2.4% |

No resource concern at any practical symbol count. The `symbol_id` field is 8 bits (supports up to 256 instruments).

**Throughput impact**: Quotes are generated round-robin. Per-symbol rate = `100 MHz / (quote_interval × NUM_SYMBOLS)`. Total system throughput is unchanged — it just spreads across more instruments.

**Mandatory coding pattern** — every per-symbol array must use the parameter:

```systemverilog
logic [31:0] mid_price [NUM_SYMBOLS];           // CORRECT — scales automatically
// logic [31:0] mid_price [4];                  // WRONG — never hardcode array sizes
```

**4.6.8.3 Link Width Scaling (`LINK_DATA_W`)**

Controls how many PMOD data pins carry frame data per direction. Only `link_tx.sv` and `link_rx.sv` are affected — all other modules see the same 128-bit frames regardless of link width.

| Metric | 4-bit (core) | 8-bit (stretch) |
|--------|-------------|-----------------|
| Beats per frame | 32 | 16 |
| Serialization time | 640 ns | 320 ns |
| Max frame rate | ~1.47M fps | ~2.78M fps |
| Round-trip wire time | ~2.07 μs | ~1.11 μs |
| Physical wiring | 2 PMOD ribbon cables | 2 PMOD cables + 4 Dupont jumpers on JAB |
| Pin usage | 6 per header (4 data + valid + ready) | 8 per header (data) + 4 JAB (valid/ready) |

**4.6.8.4 Strategy Modularity**

The strategy subsystem is designed as a **hot-swappable slot**. In core build, `strategy_engine` feeds `risk_manager` directly. To add stretch strategies:

| Step | Change | Files Modified |
|------|--------|---------------|
| 1 | Add `strategy_momentum.sv` to project | New file |
| 2 | Add `strategy_nn.sv` to project | New file |
| 3 | Add `strategy_selector.sv` to project | New file |
| 4 | In `board_b_top.sv`: instantiate new modules, replace direct wire with selector output | `board_b_top.sv` only |
| 5 | Activate SW[1:2] mapping (already reserved in `board_b_ctrl.sv`) | No change needed |
| 6 | Add config registers for new strategies (momentum threshold, NN weights) | `board_b_axi_regs.sv` |

**What does NOT change**: FSM (§4.4.5), pin constraints (XDC), `board_b_ctrl.sv` (SW[1:2] already mapped as reserved), frame formats (§4.5.3), link layer, Board A (no changes at all).

**4.6.8.5 Estimated Total Resource Usage (Core Build)**

| Category | LUTs | FFs | DSP48E2 | BRAM18K |
|----------|------|-----|---------|---------|
| Shared per board (lfsr, debounce ×4, fifo ×2) | ~200 | ~150 | 0 | 2 |
| Link layer per board (1× tx + 1× rx) | ~450 | ~300 | 0 | 0 |
| Board A data plane | ~900 | ~500 | 1 | 0 |
| Board A control plane | ~500 | ~200 | 0 | 0 |
| Board B data plane | ~1,650 | ~1,000 | 3 | 0 |
| Board B measurement | ~300 | ~600 | 0 | 0 |
| Board B control plane | ~650 | ~200 | 0 | 0 |
| **Board A total** | **~2,050** | **~1,150** | **1** | **2** |
| **Board B total (heavier)** | **~3,250** | **~2,250** | **3** | **2** |
| **Board B % of XCZU3EG** | **~4.6%** | **~1.6%** | **~0.8%** | **~1%** |

Even the heavier board (Board B) uses under 5% of available LUTs, leaving substantial headroom for stretch goals (especially the neural network strategy, which adds ~1K LUTs and up to 16 DSPs).

---

## 5. PS and Laptop Software Specification

The PL (programmable logic) handles all real-time, deterministic processing. But the PL cannot configure itself, read its own status registers, or display results to a human. That is the job of the **PS** (processing system — the ARM Cortex-A53 running PYNQ Linux) and the **laptop** (running a Python dashboard). This section specifies every piece of software in the system, the data path from PL registers to the laptop screen, and every file that must be written.

### 5.1 PS Software Architecture

Both boards run **PYNQ Linux** [6] on the quad-core ARM Cortex-A53 PS. PYNQ provides a Python-based environment with two key facilities:

1. **Overlay loading** (`pynq.Overlay`): loads the `.bit` bitstream and `.hwh` hardware handshake file into the PL at runtime.
2. **MMIO register access** (`pynq.MMIO`): reads and writes AXI-Lite mapped registers from Python using physical memory-mapped I/O.

We do **not** implement a soft-core processor (MicroBlaze, RISC-V, or custom ISA) in the PL. The hard ARM PS handles all slow-path tasks; the PL handles all fast-path logic. See §4.4.1 for the rationale.

```
┌─────────────────────────────────────────────────────────────────┐
│  PYNQ Linux (on ARM Cortex-A53, both boards)                    │
│                                                                  │
│  ┌────────────────────────────────────────────────────────────┐ │
│  │  pynq.Overlay("board_x.bit")                               │ │
│  │  Loads bitstream + hardware metadata into PL at boot        │ │
│  └────────────────────────────────────────────────────────────┘ │
│                                                                  │
│  ┌────────────────────────────────────────────────────────────┐ │
│  │  pynq.MMIO(base_addr, addr_range)                          │ │
│  │  .write(offset, value)   → AXI-Lite write to PL register   │ │
│  │  .read(offset)           → AXI-Lite read from PL register  │ │
│  └────────────────────────────────────────────────────────────┘ │
│                                                                  │
│  Board-specific Python scripts run on top of these primitives:   │
│                                                                  │
│  ┌──────────────────────────┐  ┌───────────────────────────┐   │
│  │  Board A:                │  │  Board B:                  │   │
│  │  config_exchange.py      │  │  telemetry_server.py       │   │
│  │  (configure + start)     │  │  (configure + poll + UART) │   │
│  └──────────────────────────┘  └───────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
```

#### 5.1.1 Board A PS Script — `config_exchange.py`

**Purpose**: Configure the exchange simulator and start quote generation. This script runs once at boot (or when the operator wants to reconfigure), not in a loop.

**Workflow**:

```
1. Load overlay
   ol = Overlay("board_a.bit")
   mmio = MMIO(base_addr, 0x100)

2. Write configuration registers
   mmio.write(LFSR_SEED,        0xDEADBEEF)
   mmio.write(QUOTE_INTERVAL,   1000)          # cycles between quotes
   mmio.write(REGIME,           0)              # 0=CALM (unless switch override)
   mmio.write(SYM0_INIT_MID,    0x0096_4000)   # $150.25 in Q16.16
   mmio.write(SYM0_INIT_SPREAD, 0x0000_2000)   # $0.125 spread
   ... (repeat for SYM1..SYM3)

3. Start simulation
   mmio.write(CTRL, 0x01)       # set start bit (single-cycle pulse)
   # FSM transitions IDLE → RUNNING, LFSR seed loaded, quotes begin

4. (Optional) Live regime change
   mmio.write(CTRL, (new_regime << 2))
   # Only effective if sw_override is low (physical switches not overriding)

5. (Optional) Read status
   status = mmio.read(STATUS)
   quotes  = mmio.read(QUOTES_SENT)
   print(f"Running: {status & 1}, Quotes sent: {quotes}")
```

**Key design choice**: Board A's PS script is simple — configure and fire. Board A has no telemetry loop. All Board A status (quotes_sent, link_errors, etc.) is available via AXI-Lite registers, but in the core demo we only read these manually for debugging. The real-time monitoring happens on Board B.

#### 5.1.2 Board B PS Script — `telemetry_server.py`

**Purpose**: Configure the trading pipeline, then enter a 20 Hz polling loop that reads all PL status registers and streams them as JSON lines over UART to the laptop.

**Workflow**:

```
1. Load overlay
   ol = Overlay("board_b.bit")
   mmio = MMIO(base_addr, 0x200)

2. Write configuration registers
   mmio.write(THRESHOLD,        0x0001_0000)   # 1.0 in Q16.16 (deviation threshold)
   mmio.write(EMA_ALPHA,        6554)          # ~0.1 in Q0.16
   mmio.write(BASE_QTY,         100)           # 100 shares per order
   mmio.write(MAX_POSITION,     500)           # max 500 shares per symbol
   mmio.write(MAX_ORDER_RATE,   1000)          # max 1000 orders per window
   mmio.write(MAX_LOSS,         0x0064_0000)   # $100.00 in Q16.16
   mmio.write(STRATEGY_SEL,     0)             # 0 = mean-reversion (core)

3. Start trading (FSM: IDLE → ARMED, waits for link_up, then start)
   mmio.write(CTRL, 0x01)       # set start bit

4. Enter telemetry loop (20 Hz)
   while True:
       data = {}
       data["qps"]      = mmio.read(QUOTES_RCVD)
       data["ops"]      = mmio.read(ORDERS_SENT)
       data["fps"]      = mmio.read(FILLS_RCVD)
       data["rej"]      = mmio.read(RISK_REJECTS)
       data["pos"]      = [mmio.read(POS_SYM0 + i*4) for i in range(NUM_SYMBOLS)]
       data["cash_lo"]  = mmio.read(CASH_LO)
       data["cash_hi"]  = mmio.read(CASH_HI)
       data["hist"]     = [mmio.read(HIST_BIN0 + i*4) for i in range(16)]
       data["lat_min"]  = mmio.read(LAT_MIN)
       data["lat_max"]  = mmio.read(LAT_MAX)
       data["lat_sum"]  = mmio.read(LAT_SUM)
       data["lat_cnt"]  = mmio.read(LAT_COUNT)
       data["link_err"] = mmio.read(LINK_ERRORS)
       data["state"]    = mmio.read(STATUS)

       print(json.dumps(data), flush=True)   # → stdout → UART TX → FTDI → USB → laptop
       time.sleep(0.05)                       # 50 ms = 20 Hz
```

**Critical detail — `flush=True`**: Without explicit flush, Python's stdout buffering would hold output in a 4 KB buffer before sending. `flush=True` ensures every JSON line is immediately written to the UART TX, maintaining the 20 Hz update rate.

**Register read timing**: Reading ~30 AXI-Lite registers at 100 MHz AXI clock takes ~30 × 2 cycles = ~600 ns total — negligible compared to the 50 ms sleep. The polling loop does not interfere with PL operation in any way (AXI-Lite reads are non-destructive).

### 5.2 Board B to Laptop Connection

#### 5.2.1 Physical Path

The laptop communicates with Board B via a **USB-C cable** plugged into the AUP-ZU3's **PROG UART** port (J2). This port connects to a dual-channel **FTDI FT2232HQ** USB-to-UART bridge on the board [4].

```
Board B (AUP-ZU3)                USB-C cable              Laptop
┌──────────────────────┐                                  ┌────────────────────┐
│  ARM PS (PYNQ Linux) │                                  │  Windows / Linux    │
│                       │                                  │                     │
│  telemetry_server.py  │                                  │  ┌──────────────┐  │
│  ┌──────────────────┐│                                  │  │  pyserial     │  │
│  │ print(json_line, ││  stdout → UART TX                │  │  (reads COM   │  │
│  │   flush=True)    ││  ──────────────────────────────►│  │   port at     │  │
│  └──────────────────┘│                                  │  │   115200 baud)│  │
│                       │  FTDI FT2232HQ (on-board)        │  └───────┬──────┘  │
│                       │  Channel 1: JTAG (programming)   │          │         │
│                       │  Channel 2: UART (telemetry)     │          ▼         │
│  PL (our design)      │  ──────────────────────────────►│  ┌──────────────┐  │
│  [AXI-Lite regs]      │  appears as COMx / /dev/ttyUSBx  │  │  dashboard.py│  │
│                       │                                  │  │  (Plotly Dash)│  │
└──────────────────────┘                                  │  │  localhost:   │  │
                                                           │  │  8050         │  │
                                                           │  └──────────────┘  │
                                                           └────────────────────┘
```

**Step-by-step data path**:

| Step | Location | What happens |
|------|----------|-------------|
| 1 | PL (Board B) | Status counters, positions, histogram bins, latency stats continuously written to AXI-Lite status registers by hardware |
| 2 | PS (Board B) | `telemetry_server.py` reads registers via `pynq.MMIO.read()` every 50 ms |
| 3 | PS (Board B) | Python formats readings as a single JSON line and calls `print(..., flush=True)` |
| 4 | PS → FTDI | PYNQ Linux sends stdout bytes to `/dev/ttyPS0` → UART TX at 115200 baud |
| 5 | FTDI → USB | FTDI FT2232HQ serializes UART data into USB packets over the USB-C cable |
| 6 | USB → Laptop | Laptop OS receives USB data, presents as COM port (Windows) or `/dev/ttyUSBx` (Linux) |
| 7 | Laptop | `dashboard.py` reads JSON line via `pyserial`, parses, computes rates |
| 8 | Laptop | Plotly Dash updates 8 browser panels at 20 Hz |

#### 5.2.2 UART Configuration

| Parameter | Value | Notes |
|-----------|-------|-------|
| Baud rate | 115200 | Standard, universally supported |
| Data bits | 8 | Standard |
| Parity | None | No parity check needed (USB is reliable) |
| Stop bits | 1 | Standard (8N1) |
| Flow control | None | Not needed at our data rates |

**Bandwidth analysis**: At 115200 baud (8N1), effective throughput is **11,520 bytes/sec**. Each JSON line is ~200 bytes. At 20 Hz: 200 × 20 = **4,000 bytes/sec** — 35% of capacity, leaving **65% headroom**.

If extended telemetry is needed (e.g., streaming per-symbol volatility for stretch goals), the FTDI FT2232HQ supports up to **921600 baud** (8× higher). No hardware changes required — just change the baud rate in both `telemetry_server.py` and `dashboard.py`.

#### 5.2.3 Why Not Ethernet / TCP?

The AUP-ZU3 board has a Gigabit Ethernet port, but using it would require:
- Configuring the PS Ethernet driver and IP stack
- Setting up a network between laptop and board (DHCP or static IP)
- Writing TCP/UDP socket code on both ends
- Handling connection drops, buffering, etc.

The UART approach is **zero-configuration**: plug in USB-C, open the COM port, done. For 4 KB/s of telemetry data, Ethernet is overkill. We keep it as a stretch goal for raw-data streaming (e.g., live fill-by-fill dumps at full speed).

### 5.3 Telemetry Data Format

#### 5.3.1 JSON Line Format

Each telemetry message is a single JSON line (no pretty-printing, no newlines within the object). One line per 50 ms poll.

```json
{"qps":125000,"ops":5000,"fps":4950,"rej":42,"pos":[10,-5,0,0],"cash_lo":1234567,"cash_hi":0,"hist":[100,500,300,50,10,0,0,0,0,0,0,0,0,0,0,0],"lat_min":28,"lat_max":487,"lat_sum":245000,"lat_cnt":4950,"link_err":0,"state":3,"strat":0}
```

#### 5.3.2 Field Definitions

| JSON Field | AXI Register(s) | Type | Description |
|-----------|-----------------|------|-------------|
| `qps` | QUOTES_RCVD | uint32 | Total quotes received (monotonic counter) |
| `ops` | ORDERS_SENT | uint32 | Total orders sent (monotonic counter) |
| `fps` | FILLS_RCVD | uint32 | Total fills received (monotonic counter) |
| `rej` | RISK_REJECTS | uint32 | Total orders rejected by risk manager |
| `pos` | POS_SYM0..3 | int32[] | Per-symbol signed position (shares held) |
| `cash_lo` | CASH_LO | uint32 | Cash accumulator bits [31:0] |
| `cash_hi` | CASH_HI | int32 | Cash accumulator bits [47:32] (signed) |
| `hist` | HIST_BIN0..15 | uint32[] | 16-bin latency histogram (bin counts) |
| `lat_min` | LAT_MIN | uint16 | Minimum observed round-trip latency (cycles) |
| `lat_max` | LAT_MAX | uint16 | Maximum observed round-trip latency (cycles) |
| `lat_sum` | LAT_SUM | uint32 | Sum of all latencies (for mean computation) |
| `lat_cnt` | LAT_COUNT | uint32 | Total fills measured (= denominator for mean) |
| `link_err` | LINK_ERRORS | uint32 | Link framing errors (should be 0) |
| `state` | STATUS[2:0] | uint3 | FSM state (0=RESET,1=IDLE,2=ARMED,3=TRADING,4=HALTED) |
| `strat` | STATUS[4:3] | uint2 | Active strategy (0=mean-rev, 1=momentum, 2=NN, 3=auto) |

**Counters are monotonic**: they only increment, never reset (unless the FSM enters RESET state). The laptop computes instantaneous rates by differencing consecutive readings:

```
rate = (counter_now - counter_prev) / delta_time
```

For example, if `qps` goes from 125,000 to 131,250 over 0.25 seconds (5 polls), the quote rate is `(131250 - 125000) / 0.25 = 25,000 quotes/sec`.

**Cash reconstruction**: The 48-bit Q32.16 cash accumulator is split across two 32-bit registers. On the laptop:

```python
cash_raw = (cash_hi << 32) | cash_lo     # 48-bit signed
if cash_hi & 0x8000:                      # sign extend from bit 47
    cash_raw -= (1 << 48)
cash_dollars = cash_raw / 65536.0         # Q32.16 → float
```

**PnL computation**: `total_pnl = cash + sum(position[s] * mid_price[s])` — this is mark-to-market PnL. The `cash` component is the realized PnL from closed trades; the unrealized component requires current prices (which could be added as additional telemetry fields in a stretch goal, or computed from the last known prices on the dashboard).

#### 5.3.3 Stretch Goal Telemetry Fields

When stretch goal strategies are implemented, additional fields are appended:

| JSON Field | Source | Description |
|-----------|--------|-------------|
| `vol` | VOL_HAT_SYM0..3 | Per-symbol volatility estimate (Q16.16) |
| `regime_det` | STATUS[6:5] | Detected market regime (auto mode) |
| `ema_long` | EMA_LONG_SYM0..3 | Long-window EMA values (momentum strategy) |
| `nn_scores` | NN_SCORES | BUY/SELL/HOLD confidence scores (NN strategy) |

These fields are only present when the corresponding stretch modules exist in the PL build. The dashboard ignores unknown fields gracefully.

### 5.4 Laptop Dashboard — `dashboard.py`

#### 5.4.1 Architecture

The dashboard is a single Python script using **Plotly Dash** [6], a web framework that renders interactive charts in a browser. It runs locally — no internet connection needed.

```
┌──────────────────────────────────────────────────────────────────────┐
│  dashboard.py                                                         │
│                                                                       │
│  ┌────────────────────┐     ┌─────────────────────────────────────┐  │
│  │  SerialReader       │     │  Dash App (localhost:8050)          │  │
│  │  (background thread)│     │                                     │  │
│  │                     │     │  ┌───────┐ ┌───────┐ ┌───────┐    │  │
│  │  1. Open COM port   │     │  │ Thru- │ │Latency│ │Posit- │    │  │
│  │     at 115200 baud  │     │  │ put   │ │ Hist  │ │ ion   │    │  │
│  │  2. readline()      │────►│  │Gauges │ │ Chart │ │ Bars  │    │  │
│  │  3. json.loads()    │     │  └───────┘ └───────┘ └───────┘    │  │
│  │  4. Store in shared │     │  ┌───────┐ ┌───────┐ ┌───────┐    │  │
│  │     dict (latest)   │     │  │  PnL  │ │Regime │ │ Risk  │    │  │
│  │  5. Compute deltas  │     │  │ Line  │ │ Ind.  │ │Reject │    │  │
│  │     for rates       │     │  └───────┘ └───────┘ └───────┘    │  │
│  └────────────────────┘     │  ┌───────┐ ┌───────┐               │  │
│                              │  │ Link  │ │Scalar │               │  │
│                              │  │Health │ │ Stats │               │  │
│                              │  └───────┘ └───────┘               │  │
│                              └─────────────────────────────────────┘  │
└──────────────────────────────────────────────────────────────────────┘
```

**Threading model**: A background thread handles serial I/O (blocking `readline()`). The main thread runs the Dash server. Communication is via a shared `dict` protected by a lock. The Dash callback reads the latest data every 50 ms (interval timer).

#### 5.4.2 Dashboard Panels (8 total)

| # | Panel | Type | Data Source | Description |
|---|-------|------|-------------|-------------|
| 1 | **Throughput** | 3 gauge dials | `qps`, `ops`, `fps` deltas | Quotes/sec, Orders/sec, Fills/sec (computed from counter deltas). Red zone at > 80% link capacity. |
| 2 | **Latency Histogram** | Bar chart | `hist[0:15]` | 16 bins, x-axis in nanoseconds (bin × 32 cycles × 10 ns), y-axis = count. p50/p99/max annotated as vertical lines. |
| 3 | **Position** | Grouped bar | `pos[0:N]` | Per-symbol signed position. Green = long, Red = short, Gray = flat. Auto-scales to `NUM_SYMBOLS`. |
| 4 | **PnL** | Rolling line chart | `cash_lo`, `cash_hi` | Running profit/loss in dollars. Green when positive, red when negative. Last 5 minutes of history. |
| 5 | **Regime** | Status indicator | `state`, Board A status | Current stress mode label + color badge. Shows FSM state name. |
| 6 | **Risk Rejects** | Counter + sparkline | `rej` delta | Reject rate over time. Spikes visible when position/rate/loss limits are hit. |
| 7 | **Link Health** | Status badge | `link_err`, `state` | Green = OK (0 errors), Yellow = errors detected, Red = link down. Shows error count. |
| 8 | **Scalar Stats** | Text table | `lat_min`, `lat_max`, `lat_sum`, `lat_cnt`, `strat` | Min/mean/max latency in nanoseconds, active strategy name, FSM state name. |

**p50/p99 computation from histogram**:

```python
def compute_percentiles(hist_bins, bin_width_ns=320):
    total = sum(hist_bins)
    if total == 0:
        return 0, 0
    cumulative = 0
    p50 = p99 = 0
    for i, count in enumerate(hist_bins):
        cumulative += count
        if cumulative >= total * 0.50 and p50 == 0:
            p50 = i * bin_width_ns
        if cumulative >= total * 0.99 and p99 == 0:
            p99 = i * bin_width_ns
            break
    return p50, p99
```

#### 5.4.3 Dashboard Startup Sequence

```bash
# On the laptop:
python dashboard.py --port COM3 --baud 115200

# dashboard.py:
# 1. Opens COM3 at 115200 baud
# 2. Starts background SerialReader thread
# 3. Launches Dash server at http://localhost:8050
# 4. Opens browser automatically
# 5. Callbacks fire every 50 ms, pulling latest data from SerialReader
```

The dashboard handles gracefully:
- **No serial data yet**: shows "Waiting for data..." placeholder
- **Stale data** (> 500 ms since last update): shows yellow "STALE" warning
- **JSON parse errors**: skips malformed lines, increments error counter
- **COM port disconnect**: shows red "DISCONNECTED" banner, auto-reconnects

### 5.5 Complete Software File Inventory

#### 5.5.1 Files on Board A PS (SD card, PYNQ image)

| File | Location | Description |
|------|----------|-------------|
| `board_a.bit` | `/home/xilinx/overlays/` | Vivado-generated bitstream for Board A PL |
| `board_a.hwh` | `/home/xilinx/overlays/` | Hardware handshake file (register map metadata) |
| `config_exchange.py` | `/home/xilinx/` | Config + start script (see §5.1.1) |

**Usage**: SSH into Board A (or use Jupyter), run `python3 config_exchange.py`. Script exits after starting the simulation. To reconfigure, stop the FSM (BTN[1] or AXI reset), edit parameters in the script, re-run.

#### 5.5.2 Files on Board B PS (SD card, PYNQ image)

| File | Location | Description |
|------|----------|-------------|
| `board_b.bit` | `/home/xilinx/overlays/` | Vivado-generated bitstream for Board B PL |
| `board_b.hwh` | `/home/xilinx/overlays/` | Hardware handshake file (register map metadata) |
| `telemetry_server.py` | `/home/xilinx/` | Config + 20 Hz telemetry streaming script (see §5.1.2) |
| `register_map.py` | `/home/xilinx/` | Shared constants: register offsets, field masks, Q16.16 helpers |

**Usage**: SSH into Board B, run `python3 telemetry_server.py`. Script runs indefinitely (Ctrl+C to stop). The UART output is captured by the laptop dashboard.

**`register_map.py` — why a separate file**: Both `telemetry_server.py` and any debug/test scripts need to know register offsets. Keeping them in one place avoids drift:

```python
# register_map.py
CTRL           = 0x00
STRATEGY_SEL   = 0x04
THRESHOLD      = 0x08
EMA_ALPHA      = 0x0C
BASE_QTY       = 0x10
MAX_POSITION   = 0x14
MAX_ORDER_RATE = 0x18
MAX_LOSS       = 0x1C
STATUS         = 0x40
QUOTES_RCVD    = 0x44
ORDERS_SENT    = 0x48
FILLS_RCVD     = 0x4C
RISK_REJECTS   = 0x50
LINK_ERRORS    = 0x54
POS_SYM0       = 0x58
CASH_LO        = 0x68
CASH_HI        = 0x6C
HIST_BIN0      = 0x80
LAT_MIN        = 0xC0
LAT_MAX        = 0xC4
LAT_SUM        = 0xC8
LAT_COUNT      = 0xCC

def q16_16(val):
    """Convert float to Q16.16 integer."""
    return int(val * 65536) & 0xFFFFFFFF

def from_q16_16(raw):
    """Convert Q16.16 integer to float (signed)."""
    if raw & 0x80000000:
        raw -= 0x100000000
    return raw / 65536.0
```

#### 5.5.3 Files on the Laptop

| File | Location | Description |
|------|----------|-------------|
| `dashboard.py` | `sw/laptop/` | Main dashboard application (Plotly Dash + pyserial) |
| `serial_reader.py` | `sw/laptop/` | Background thread: reads COM port, parses JSON, computes rates |
| `requirements.txt` | `sw/laptop/` | Python dependency list |

**`requirements.txt`**:

```
pyserial>=3.5
dash>=2.14
plotly>=5.18
```

**Installation**: `pip install -r requirements.txt`

#### 5.5.4 Stretch Goal: Board A PS Telemetry

In the core build, Board A runs a fire-and-forget script. For enhanced demos, a stretch goal adds a second telemetry stream from Board A to the laptop:

| Approach | Method | Complexity |
|----------|--------|-----------|
| **USB-UART (same as Board B)** | Second USB-C cable from Board A's PROG port to laptop. Second COM port. Dashboard reads both. | Low — duplicate the Board B approach |
| **SSH polling** | Laptop SSHes into Board A over Ethernet, runs a script that reads registers and prints JSON. Dashboard captures SSH stdout. | Medium — requires Ethernet setup |
| **PL-to-PL telemetry** | Board A counters sent to Board B via the existing PMOD link (extra frame type). Board B's telemetry includes Board A stats. | Medium — requires new message type and Board A changes |

For the core demo, Board A telemetry is **not required** — all trading metrics (latency, PnL, positions) are on Board B. Board A's only relevant numbers (quotes_sent, link_errors) can be read manually via the Board A PS.

### 5.6 Demo Workflow — End to End

This section ties together the entire software stack into the operational sequence for a live demo.

```
Step  Who           Action
────  ────────────  ──────────────────────────────────────────────────────────
 1    Operator      Power on both AUP-ZU3 boards. PYNQ Linux boots (~30 sec).
 2    Operator      Connect USB-C cables:
                      - Board A PROG port → laptop (for SSH/Jupyter access)
                      - Board B PROG port → laptop (for telemetry UART)
                      - PMOD ribbon cables between boards (already connected)
 3    Operator      On laptop: identify COM ports (Board A = COMx, Board B = COMy)
 4    Operator      SSH into Board A:  python3 config_exchange.py
                      → Overlay loads, config written, start bit set
                      → Board A FSM: RESET → IDLE → RUNNING
                      → Quotes begin flowing over PMOD A → Board B
 5    Operator      SSH into Board B:  python3 telemetry_server.py
                      → Overlay loads, config written, start bit set
                      → Board B FSM: RESET → IDLE → (link_up) → ARMED
                      → Telemetry JSON begins streaming to UART
 6    Operator      On laptop: python dashboard.py --port COMy --baud 115200
                      → Dashboard opens in browser at localhost:8050
                      → Shows "ARMED" state, EMA converging, no orders yet
 7    Operator      Flip SW[0] on Board B to HIGH (trading_enable = 1)
                      → Board B FSM: ARMED → TRADING
                      → Orders flow, fills return, PnL updates, histogram fills
 8    Audience      Watch dashboard: throughput gauges, latency histogram,
                    position bars, PnL line, regime indicator — all updating
                    at 20 Hz in real time
 9    Operator      Flip SW[1:0] on Board A to change regime (CALM → VOLATILE)
                      → Quote behavior changes immediately
                      → Dashboard shows throughput/latency shift
10    Operator      Press BTN[1] on Board B (stop)
                      → Board B FSM: TRADING → ARMED
                      → Orders stop, but fills for pending orders still arrive
11    Operator      (Optional) Flip SW[0] down → confirm ARMED
                    Press BTN[2] on Board B (reset) → RESET → IDLE
                      → All counters, positions, histogram cleared
```

---

## 6. Vivado Build Strategy

This section describes how the RTL described in §4 is packaged, synthesized, and deployed onto the AUP-ZU3 boards using Vivado and PYNQ.

### 6.1 Block Design Structure

Both boards use the same Vivado block design topology. The only difference is which custom IP block is instantiated (Board A vs Board B).

```
┌──────────────────────────────────────────────────────────────────────┐
│  Vivado Block Design (same structure for both boards)                 │
│                                                                       │
│  ┌─────────────────────────────┐                                     │
│  │  Zynq UltraScale+ PS IP     │                                     │
│  │                              │                                     │
│  │  Configuration:              │                                     │
│  │   FCLK0 = 100 MHz           │  ← single PL clock for all logic   │
│  │   M_AXI_HPM0_LPD (master)   │  ← PS-to-PL AXI master port       │
│  │   UART0 = enabled            │  ← for PYNQ console / telemetry   │
│  │   DDR = default              │  ← for PYNQ Linux (not used by PL) │
│  │   USB = enabled              │  ← for PYNQ SSH/Jupyter access     │
│  └──────────────┬──────────────┘                                     │
│                  │ M_AXI_HPM0_LPD (AXI Master)                       │
│                  ▼                                                    │
│  ┌─────────────────────────────┐                                     │
│  │  Processor System Reset      │                                     │
│  │  (Xilinx IP, auto-generated) │                                     │
│  │                              │                                     │
│  │  Inputs: FCLK0, ext_reset   │                                     │
│  │  Outputs: peripheral_reset,  │                                     │
│  │           interconnect_reset  │                                     │
│  └──────────────┬──────────────┘                                     │
│                  │                                                    │
│  ┌──────────────▼──────────────┐                                     │
│  │  AXI Interconnect            │                                     │
│  │  (1 master → 1 slave)        │                                     │
│  │                              │                                     │
│  │  Handles address decoding,   │                                     │
│  │  protocol conversion         │                                     │
│  └──────────────┬──────────────┘                                     │
│                  │ S00_AXI                                            │
│  ┌──────────────▼──────────────────────────────────────────────────┐ │
│  │  board_x_custom_ip  (our packaged IP)                            │ │
│  │                                                                   │ │
│  │  Contains: board_x_top.sv  (instantiates ALL RTL modules)        │ │
│  │            board_x_axi_regs.sv (AXI-Lite slave interface)        │ │
│  │            all data-plane, control, and link modules              │ │
│  │                                                                   │ │
│  │  External ports (exposed to top-level FPGA pins):                │ │
│  │   - pmod_a[7:0]     (PMOD header A signals)                      │ │
│  │   - pmod_b[7:0]     (PMOD header B signals)                      │ │
│  │   - sw[7:0]         (slide switches)                              │ │
│  │   - btn[3:0]        (pushbuttons)                                 │ │
│  │   - led[7:0]        (user LEDs)                                   │ │
│  │   - rgb0[2:0]       (RGB LED 0: R, G, B)                         │ │
│  │   - rgb1[2:0]       (RGB LED 1: R, G, B)                         │ │
│  └───────────────────────────────────────────────────────────────────┘ │
└──────────────────────────────────────────────────────────────────────┘
```

**Key design decision**: We package **all** of our RTL into a single custom IP block. This keeps the Vivado block design minimal (just the PS, reset, interconnect, and our IP) and avoids complexity from multiple AXI slaves or custom interconnect topologies. All module-to-module wiring happens inside our IP's top-level file, which we control entirely in RTL.

### 6.2 IP Packaging Approach

**Step-by-step workflow**:

| Step | Action | Tool | Output |
|------|--------|------|--------|
| 1 | Create AXI-Lite slave template | Vivado → Tools → Create and Package New IP | Auto-generated AXI handshake logic + register stub |
| 2 | Edit register template | Manual RTL editing | `board_x_axi_regs.sv` with our config/status registers |
| 3 | Add all RTL source files | Vivado → Add Sources | All `.sv` files from §4.6 added to IP project |
| 4 | Instantiate data-plane modules | Edit `board_x_top.sv` | Structural wiring of all modules (see §4.6.7) |
| 5 | Expose external ports | Edit IP wrapper | PMOD, LED, switch, button ports routed to top-level |
| 6 | Package IP | Vivado → Package IP wizard | `.xci` IP component file |
| 7 | Add IP to block design | Vivado block design → Add IP | Connect AXI, clock, reset, make external ports |
| 8 | Assign pin constraints | Add XDC file | Map external ports to FPGA balls (see §4.5.1, §4.4.2) |
| 9 | Synthesize + Implement | Vivado → Run Implementation | Timing closure at 100 MHz |
| 10 | Generate bitstream | Vivado → Generate Bitstream | `.bit` file for PYNQ overlay |
| 11 | Export hardware handshake | Vivado → File → Export → .hwh | `.hwh` file for PYNQ overlay |

**Why a custom AXI-Lite slave (not Vivado IP Integrator GPIO)**:

Vivado's built-in GPIO IP could technically map switches and LEDs, but:
- We need ~30+ custom registers with specific read/write behaviors (counters, histogram bins, config fields)
- The AXI register block is tightly integrated with our data-plane (direct wiring, not bus transactions)
- A single custom IP gives us full control over timing and port mapping

### 6.3 XDC Constraints

The XDC (Xilinx Design Constraints) file maps our RTL port names to physical FPGA ball locations. The AUP-ZU3 board vendor provides a master constraints file [4] which we subset for our design.

**Constraint categories**:

| Category | Pins | IOSTD | Source |
|----------|------|-------|--------|
| PMOD A data + valid + ready | 6 | LVCMOS33 | §4.5.1 Cable 1 table |
| PMOD B data + valid + ready | 6 | LVCMOS33 | §4.5.1 Cable 2 table |
| PMOD+ JAB (8-bit stretch) | 4 | LVCMOS33 | §4.5.1 JAB table |
| User switches SW[7:0] | 8 | LVCMOS12 | §4.4.2 tables |
| User pushbuttons BTN[3:0] | 4 | LVCMOS33 | §4.4.2 tables |
| User LEDs LED[7:0] | 8 | LVCMOS12 | §4.4.2 tables |
| RGB LEDs (2 × 3 pins) | 6 | LVCMOS12 | §4.4.2 tables |

**Timing constraints**: The only timing constraint needed is a 100 MHz clock definition for `FCLK0`. Since all PL logic runs in a single clock domain and the data rate on PMOD pins is 50 MHz (well within LVCMOS33 I/O capability), no special I/O timing constraints are required. The 2-FF synchronizers in `link_rx` handle the CDC boundary.

```tcl
# Clock definition (FCLK0 is generated by PS, declared for timing analysis)
create_clock -period 10.000 -name clk_pl [get_pins zynq_ps/FCLK_CLK0]

# All I/O constraints use the board-vendor XDC as reference
# PMOD pins, switches, buttons, LEDs — see §4.5.1 and §4.4.2 for ball assignments
```

**Both boards use the same XDC file** — the physical pin assignments are identical because both boards are the same AUP-ZU3 hardware. The directionality of PMOD pins (input vs output) is determined by the RTL, not the constraints.

### 6.4 PYNQ Overlay Packaging

The Vivado build produces two files needed by PYNQ:

| File | Extension | Purpose | Size (typical) |
|------|-----------|---------|---------------|
| Bitstream | `.bit` | FPGA configuration data | ~4 MB |
| Hardware Handshake | `.hwh` | XML describing address map, IP blocks, clock/reset topology | ~50 KB |

**Deployment**:

```
1. Copy to Board A SD card:
   /home/xilinx/overlays/board_a.bit
   /home/xilinx/overlays/board_a.hwh

2. Copy to Board B SD card:
   /home/xilinx/overlays/board_b.bit
   /home/xilinx/overlays/board_b.hwh

3. From Python (PYNQ):
   from pynq import Overlay
   ol = Overlay("board_a.bit")   # loads bitstream, parses hwh
   mmio = ol.ip_dict['board_a_custom_ip']['phys_addr']
   # or: mmio = MMIO(base_addr, addr_range)
```

The `.hwh` file is critical — PYNQ uses it to determine the base address of our AXI-Lite slave, which it passes to `MMIO`. Without it, we would have to hardcode addresses.

### 6.5 Build Checklist (per board)

A checklist for building each board's overlay from scratch:

- [ ] Create Vivado project targeting `xczu3eg-sfvc784-2-e`
- [ ] Add Zynq PS IP, configure FCLK0 = 100 MHz, enable M_AXI_HPM0_LPD and UART0
- [ ] Run block automation (adds reset and interconnect)
- [ ] Create custom AXI-Lite IP using Vivado wizard (1 slave, 32-bit data)
- [ ] Add all RTL source files to the IP project
- [ ] Edit AXI register template → `board_x_axi_regs.sv`
- [ ] Wire all modules in `board_x_top.sv`
- [ ] Expose external ports (PMOD, switches, buttons, LEDs, RGB)
- [ ] Package IP, add to block design
- [ ] Connect AXI, clock, reset; make external ports
- [ ] Add XDC constraints file
- [ ] Run Synthesis → check for warnings (especially undriven ports, latch inference)
- [ ] Run Implementation → check timing closure (WNS > 0 at 100 MHz)
- [ ] Generate Bitstream
- [ ] Export `.hwh`
- [ ] Copy `.bit` + `.hwh` to board SD card
- [ ] Test with PYNQ `Overlay()` load + basic MMIO read/write

### 6.6 Synthesis Expectations

Based on the resource estimates in §4.6.8.5:

| Metric | Expected | Limit | Margin |
|--------|----------|-------|--------|
| LUT utilization (Board B) | ~4.6% (~3,250) | 70,560 | >95% free |
| FF utilization (Board B) | ~1.6% (~2,250) | 141,120 | >98% free |
| DSP utilization (Board B) | ~0.8% (~3) | 360 | >99% free |
| BRAM utilization (Board B) | ~1% (~2) | 216 (18Kb blocks) | >99% free |
| Timing (WNS) | > 2 ns | 0 ns (10 ns period) | ~2 ns slack expected |

**If timing fails**: At 100 MHz on this device, timing failure is extremely unlikely given our design's modest complexity. If it occurs: (1) check for combinational loops, (2) add pipeline registers on long paths, (3) use Vivado's timing report to identify the critical path.

---

## 7. Testing Plan

Testing proceeds in three phases: **simulation** (pure software, no hardware needed), **hardware bring-up** (incremental on real boards), and **stress/acceptance** (full system validation). Every phase is **gated** — do not advance until the current phase passes all criteria.

### 7.1 Simulation Environment

**Tool**: Vivado XSIM (included with Vivado, no separate license) or ModelSim/Questa (if available).

**Language**: All testbenches in SystemVerilog with self-checking assertions. No manual waveform inspection required for pass/fail — every testbench prints `PASS` or `FAIL` and returns a nonzero exit code on failure.

**Regression script**: A batch file (`sim/run_all_tests.bat` / `sim/run_all_tests.sh`) that compiles and runs all testbenches sequentially, collecting results:

```
============================================
  HFT Capstone — Regression Test Suite
============================================
[ 1/21] tb_lfsr32          ... PASS  (  0.2s)
[ 2/21] tb_debounce         ... PASS  (  0.3s)
[ 3/21] tb_sync_fifo        ... PASS  (  0.4s)
[ 4/21] tb_link_tx          ... PASS  (  0.5s)
...
[21/21] tb_system            ... PASS  ( 12.1s)
============================================
  RESULTS: 21/21 passed, 0 failed
============================================
```

### 7.2 Unit Testing (Simulation)

Every synthesizable module from §4.6 gets a dedicated self-checking testbench. The testbench applies stimulus, checks outputs against expected values, and flags mismatches as assertion failures.

#### 7.2.1 Shared Module Tests

| TB | Module Under Test | Stimulus | Key Checks | Edge Cases |
|----|-------------------|----------|------------|------------|
| `tb_lfsr32` | `lfsr32.sv` | Provide seed, clock 100 cycles, then load new seed | Output never zero; sequence matches known Galois polynomial output; `load` correctly latches new seed | seed = 0 (prevented or handled), seed = all-ones, load during active output |
| `tb_debounce` | `debounce.sv` | Drive raw input with bounce pattern (rapid toggling for 1000 cycles, then stable) | Output stays stable during bounce; transitions only after all 20 samples agree; rising edge pulse fires once | Held button (no bounce), very fast bounce (every cycle), release bounce |
| `tb_sync_fifo` | `sync_fifo.sv` | Write until full, read until empty, simultaneous read/write | FIFO count tracks correctly; `full`/`empty`/`almost_full` flags accurate; data integrity (read order = write order) | Write when full (should not corrupt), read when empty (should not corrupt), `almost_full` threshold |

#### 7.2.2 Link Layer Tests

| TB | Module(s) | Stimulus | Key Checks | Edge Cases |
|----|-----------|----------|------------|------------|
| `tb_link_tx` | `link_tx.sv` | Feed 5 known 128-bit frames | Correct nibble sequence (MSB first); `pmod_valid` high for exactly `2 × BEATS_PER_FRAME` core_clk cycles; inter-frame gap ≥ 2 beats; `frame_in_ready` deasserts during transmission | Back-to-back frames, `remote_ready` deassert mid-idle, `remote_ready` deassert mid-frame (should complete current frame) |
| `tb_link_rx` | `link_rx.sv` | Drive PMOD pins with known nibble pattern | Assembled 128-bit frame matches expected; `frame_out_valid` pulses once per frame; `link_up` asserts after first valid frame | Glitch on valid (should not start false capture), valid staying low indefinitely (no spurious frames), truncated frame (error_count increments) |
| `tb_link_loopback` | `link_tx` + `link_rx` | Loopback: tx output pins wired to rx input pins | 1000 random frames sent = 1000 identical frames received; zero errors | Max rate (back-to-back, no idle gaps), intermittent pauses, `ready` toggling mid-stream |

#### 7.2.3 Board A Data Plane Tests

| TB | Module | Stimulus | Key Checks | Edge Cases |
|----|--------|----------|------------|------------|
| `tb_market_sim` | `market_sim.sv` | Set CALM regime, run 100 quote cycles; then switch regime mid-run | Prices within expected range; spread > 0 always; `seq_num` incrementing per symbol; correct round-robin order; regime change takes effect on next quote | All 4 regimes, `NUM_SYMBOLS = 1`, `running` toggled mid-stream, `load_seed` during active generation |
| `tb_exchange_lite` | `exchange_lite.sv` | BUY order at ask, BUY below ask, SELL at bid, SELL above bid | FILL with correct `fill_price` and echoed `order_id`/`ts_echo`; REJECT with zero fill fields; counters (`orders_rcvd`, `fills_sent`, `rejects_sent`) accurate | Exact boundary (limit = ask for BUY, limit = bid for SELL), unknown `symbol_id`, rapid back-to-back orders |
| `tb_tx_arbiter` | `tx_arbiter.sv` | Simultaneous quote + fill available | Fill sent first (strict priority); no frame corruption; both `quote_ready` and `fill_ready` properly handshake | Only quotes, only fills, alternating, rapid toggle |

#### 7.2.4 Board B Pipeline Tests

| TB | Module | Stimulus | Key Checks | Edge Cases |
|----|--------|----------|------------|------------|
| `tb_msg_demux` | `msg_demux.sv` | Mixed QUOTE, FILL, and invalid frames | QUOTE frames routed to quote port; FILL frames to fill port; invalid types discarded + `demux_errors` incremented; counters accurate | All QUOTEs, all FILLs, unknown `msg_type` = 4'hF, rapid alternation |
| `tb_quote_book` | `quote_book.sv` | Sequence of QUOTE frames for different symbols | Register file updated correctly; read-back matches last written values per symbol | Same symbol updated twice rapidly, out-of-order symbols, `symbol_id` at boundary (0, NUM_SYMBOLS-1) |
| `tb_feature_compute` | `feature_compute.sv` | Known bid/ask sequence → known mid, spread, EMA | `mid` exact; `spread` exact; EMA converges within 1 LSB tolerance after N quotes; `deviation = mid - ema` correct sign | Large price jump (EMA slow to follow), `spread = 0` (bid = ask), `alpha = 0` (EMA never moves), `alpha = 65535` (EMA = sample) |
| `tb_strategy_engine` | `strategy_engine.sv` | Deviation values: above threshold, below threshold, at threshold, zero | Correct BUY/SELL/NONE signals; correct prices (BUY at ask, SELL at bid); correct quantity | Exactly at threshold (no trade expected), `deviation = 0`, very large deviation, `base_qty = 0` |
| `tb_risk_manager` | `risk_manager.sv` | Orders with various position/rate/PnL conditions | Position at limit → rejected; rate at max → rejected; PnL at -max_loss → `risk_halt` latched; all pass → approved; `order_enable = 0` → all rejected | Position at max-1 (approve), rate at max (reject), PnL exactly at -max_loss (reject), `risk_halt` latch persists until `counter_clr` |
| `tb_order_manager` | `order_manager.sv` | Approved signals with known fields | Correct ORDER frame format; `order_id` incrementing; `timestamp` matches cycle counter; `orders_sent` counter accurate | Rapid back-to-back (ID wrap at 65535→0), no approved signal (no output), single cycle approved pulse |
| `tb_position_tracker` | `position_tracker.sv` | BUY fill then SELL fill for same symbol | Position tracks correctly (BUY adds, SELL subtracts); cash accumulates correctly (Q32.16); `total_pnl` computed | Large quantity, alternating buy/sell back to zero, multiple symbols, signed overflow (should saturate or wrap safely), `position_clr` resets everything |
| `tb_latency_histogram` | `latency_histogram.sv` | FILL frames with known `ts_echo` values and known `cycle_counter` | Correct bin incremented; `lat_min`/`lat_max` updated; `lat_sum` accumulates; `lat_count` matches fill count | `latency = 0` (ts_echo = now), latency > max bin (overflow bucket), timestamp wrap (0xFFFF → 0x0000), `hist_clr` resets all bins and stats |

#### 7.2.5 Control Plane Tests

| TB | Module | Stimulus | Key Checks | Edge Cases |
|----|--------|----------|------------|------------|
| `tb_board_a_axi_regs` | `board_a_axi_regs.sv` | Write config registers, read back; read status registers | Write/read round-trip correct; status registers reflect PL inputs; single-cycle pulse generation on CTRL write | Write to read-only register (ignored), read from write-only register (returns 0 or default), rapid successive writes |
| `tb_board_b_axi_regs` | `board_b_axi_regs.sv` | Same pattern as Board A, plus histogram bin reads | All config/status registers correct; histogram bins readable; position registers sign-correct | Same edge cases + reading histogram while fills are arriving (should be coherent) |

### 7.3 Integration Testing (Simulation)

Integration tests wire multiple modules together and verify end-to-end behavior. These catch inter-module interface bugs that unit tests cannot.

| # | Test | Setup | Duration | Pass Criteria |
|---|------|-------|----------|---------------|
| I1 | **Board A standalone** | `board_a_top` with synthetic ORDER frames injected (replacing `link_rx` with a stimulus module that sends known orders) | 10K quotes generated | `quotes_sent` = 10K; fills match expected (BUY at ask, SELL at bid); `rejects_sent` matches orders that should fail; no FIFO overflow (`fifo_count < 64`) |
| I2 | **Board B standalone** | `board_b_top` with synthetic QUOTE frames injected (replacing `link_rx` with a stimulus module that sends known quote sequences) | 5K quotes injected | `orders_sent > 0`; positions match expected strategy behavior; `fills_rcvd` matches injected fills; histogram populated; `risk_halt` fires when PnL crosses `-max_loss` |
| I3 | **Full system (behavioral link)** | `board_a_top` + `board_b_top` with tx/rx pins directly wired (ideal wire model, no CDC delay) | 50K quotes across all 4 regimes (12.5K per regime) | Zero frame loss (`link_errors = 0` on both sides); PnL tracks consistently; histogram non-empty; `risk_halt` triggers under ADVERSARIAL if PnL drops; positions never exceed `max_position` |
| I4 | **Full system (CDC model)** | Same as I3 but with a 2-cycle delay model on PMOD connections (simulating the 2-FF synchronizer) | 50K quotes | Same as I3 — verifies that the mesochronous clocking strategy works correctly in simulation |

**Golden model** (for I3/I4): A Python script that simulates the trading pipeline arithmetically: given the same LFSR seed, initial prices, and strategy parameters, it computes expected positions, cash, and PnL. The testbench compares hardware output against the golden model's predictions, allowing ±1 LSB tolerance for fixed-point rounding.

### 7.4 Hardware Bring-Up (10 Phases)

Each phase is **gated** — do not proceed until the current phase passes. This prevents debugging compound failures.

| Phase | Goal | Method | Pass Criteria | Estimated Time |
|-------|------|--------|---------------|---------------|
| **1: LED Blinker** | Verify Vivado flow + PYNQ boot | Build minimal overlay: clock divider → LED toggle. Load via PYNQ `Overlay()`. | LED blinks at expected rate (~3 Hz). PYNQ Jupyter accessible via browser. | 2 hours |
| **2: AXI-Lite Smoke** | Verify PS ↔ PL register access | Add AXI-Lite slave with 1 R/W register. Write 0xDEADBEEF from Python, read back. | Read returns 0xDEADBEEF. Write different values, all round-trip correctly. | 2 hours |
| **3: Board A Standalone** | Verify market_sim + exchange | Load full Board A overlay. Run `config_exchange.py`. Read counters via MMIO. Optional: Vivado ILA on quote frames. | `quotes_sent` incrementing; correct regime behavior (step size changes with switch/register); LFSR seed loads correctly. | 4 hours |
| **4: Board B Standalone** | Verify trader pipeline without link | Load Board B overlay with internal synthetic quote generator (hardcoded stimulus in RTL, replacing `link_rx`). Run config script. | `orders_sent > 0`; `position != 0`; histogram bins populated; `risk_halt` fires when expected. | 4 hours |
| **5: Link Smoke** | Verify PMOD physical data transfer | Board A sends incrementing counter frames (not real quotes — just 128-bit counters). Board B checks sequence continuity. | `rx_frame_count = tx_frame_count`; zero sequence errors; `link_up` asserted on Board B. | 3 hours |
| **6: One-Way Quotes** | Verify real quote reception | Board A sends real quotes (market_sim running). Board B receives, updates quote_book. No orders sent yet (ARMED state). | `quotes_rcvd` on Board B matches `quotes_sent` on Board A (within timing tolerance). | 2 hours |
| **7: Closed Loop** | Verify full trading cycle | Enable trading on Board B (`trading_enable = 1`, press start). Orders flow back to Board A. Fills return. | `fills_rcvd > 0`; `position != 0`; `cash != 0`; PnL updating; histogram populated. | 3 hours |
| **8: Dashboard** | Verify laptop telemetry | Connect USB-UART cable. Run `telemetry_server.py` on Board B. Run `dashboard.py` on laptop. | All 8 dashboard panels update with plausible data at ~20 Hz. No JSON parse errors. | 2 hours |
| **9: Stress Test** | Verify stability under all regimes | Cycle through CALM → VOLATILE → BURST → ADVERSARIAL, 10 minutes each. Monitor dashboard. | `link_errors = 0`; no FIFO overflow; no crashes; PnL/positions/histogram all consistent. | 1 hour |
| **10: Full Demo Dry Run** | End-to-end demo rehearsal | Follow §5.6 demo workflow exactly. Time each step. Practice narration. | Complete workflow in < 5 minutes setup. All transitions clean. Dashboard visually compelling. | 1 hour |

### 7.5 Stress Testing Protocol

After hardware bring-up, dedicated stress tests validate system stability under sustained load and extreme conditions.

#### 7.5.1 Regime Stress Matrix

| Test | Regime | Duration | Metrics to Monitor | Expected Behavior |
|------|--------|----------|--------------------|-------------------|
| S1 | CALM | 10 min | ~100K qps, steady PnL, low risk rejects | Stable, predictable. PnL drifts slowly. |
| S2 | VOLATILE | 10 min | Same throughput, wider PnL swings, more rejects | PnL oscillates with larger amplitude. Position limits hit more often. |
| S3 | BURST | 10 min | ~1M+ qps, FIFO fill levels, link utilization | Throughput gauges near max. FIFO fill must stay < 75% (48/64 entries). |
| S4 | ADVERSARIAL | 10 min | High risk rejects, rapid PnL changes, `risk_halt` may trigger | Risk system heavily engaged. Possible HALTED state if PnL drops fast. |
| S5 | RAPID SWITCH | 10 min | Switch regime every 30 sec via hardware switches | No glitches on regime transitions. Throughput/latency shift cleanly. |
| S6 | START/STOP CYCLING | 10 min | Start → trade 30 sec → stop → start (repeat) | Positions preserved across stop/start. No frame loss on transitions. |
| S7 | RESET CYCLING | 10 min | Start → trade 30 sec → reset → start (repeat) | All counters/positions/histogram clear on reset. Clean restart. |

#### 7.5.2 Link Robustness Tests

| Test | Setup | Duration | Pass Criteria |
|------|-------|----------|---------------|
| L1: Sustained max rate | BURST regime, continuous | 30 min | `link_errors = 0`, no FIFO overflow |
| L2: Cable disconnect/reconnect | Unplug PMOD cable for 5 sec, replug | 3 cycles | `link_up` deasserts, `link_errors` may increment, system recovers after reconnect (Board B returns to IDLE, re-arms) |
| L3: Asymmetric load | Board A sends max rate quotes, Board B sends orders only when strategy triggers | 10 min | Both directions stable, no backpressure starvation |

#### 7.5.3 Risk System Validation

| Test | Setup | Expected Outcome |
|------|-------|-----------------|
| R1: Position limit | Set `max_position = 10`, trade VOLATILE regime | Position never exceeds ±10 shares per symbol. `risk_rejects` > 0. |
| R2: Order rate limit | Set `max_order_rate = 5` (very low) | Most orders rejected. `risk_rejects >> orders_sent`. |
| R3: Max loss halt | Set `max_loss = $1.00` (very tight), trade VOLATILE | `risk_halt` asserts quickly. FSM → HALTED. No more orders after halt. Only reset clears halt. |
| R4: Combined stress | All limits tight, ADVERSARIAL regime | System hits limits rapidly. Verify no invalid state transitions, no frame corruption, no counter overflow. |

### 7.6 Acceptance Criteria Matrix

The project is considered **complete** when all criteria in this matrix are met simultaneously during a single continuous test run.

| # | Criterion | Target | How Verified | Priority |
|---|-----------|--------|-------------|----------|
| A1 | **Closed-loop operation** | Quote → Order → Fill cycle completes | All counters incrementing on dashboard | Must-have |
| A2 | **Determinism** | 0 cycles pipeline jitter | Histogram shows narrow concentration (1-2 bins) for consistent input patterns | Must-have |
| A3 | **Throughput — CALM** | ≥ 100K quotes/sec | Dashboard throughput gauge | Must-have |
| A4 | **Throughput — BURST** | ≥ 1M quotes/sec | Dashboard throughput gauge | Must-have |
| A5 | **Round-trip latency** | < 3 μs typical (p50) | Histogram p50 annotation | Must-have |
| A6 | **Latency measurement** | Hardware histogram populated with correct bins | Histogram non-empty, p50/p99/max displayed | Must-have |
| A7 | **Zero frame loss** | `link_errors = 0` over 10 min per regime | Dashboard link health panel | Must-have |
| A8 | **Risk enforcement** | Position never exceeds limit | `max(abs(position[s])) <= max_position` for all symbols | Must-have |
| A9 | **Risk halt** | Trading stops when PnL < -max_loss | FSM enters HALTED, `orders_sent` freezes | Must-have |
| A10 | **Telemetry** | 8 dashboard panels update at ≥ 10 Hz | Visual confirmation + timestamp delta check | Must-have |
| A11 | **Multi-regime** | All 4 regimes operate correctly | Separate 10-min test per regime, all other criteria hold | Must-have |
| A12 | **Stress stability** | Zero errors across full stress suite (S1-S7) | `link_errors = 0`, no FIFO overflow, no crashes | Must-have |
| A13 | **Strategy switching** (stretch) | SW[1:0] selects strategy, dashboard shows active strategy | `strat` field in telemetry changes, order behavior changes | Stretch |
| A14 | **Adaptive regime** (stretch) | Auto-mode selects strategy based on market conditions | `regime_det` field in telemetry tracks regime changes | Stretch |
| A15 | **8-bit link** (stretch) | Halved round-trip latency with 8-bit PMOD | p50 ≈ 1.1 μs (vs 2.1 μs at 4-bit) | Stretch |

### 7.7 Debugging Toolkit

When a test fails, these tools and techniques are available:

| Tool | Where | Purpose |
|------|-------|---------|
| **Vivado XSIM waveform** | Simulation | Inspect any internal signal cycle-by-cycle. First resort for unit test failures. |
| **$display / $monitor** | Simulation | Print key values at runtime. Useful for long-running integration tests where waveforms are unwieldy. |
| **Vivado ILA (Integrated Logic Analyzer)** | On-chip | Capture real-time PL signals on the actual FPGA. Insert ILA probes on frame data, valid/ready, FSM state, counters. Triggered by condition (e.g., `risk_halt` rising edge). |
| **VIO (Virtual I/O)** | On-chip | Read/write internal signals from Vivado hardware manager. Useful for forcing states or reading values not mapped to AXI-Lite. |
| **AXI-Lite register readback** | On-chip via PS | Read any status register from Python. Counters, FSM state, FIFO fill levels, error counts — all visible. |
| **UART debug prints** | PS console | Add `print()` statements to `telemetry_server.py` for live debugging. |
| **Dashboard error log** | Laptop | `dashboard.py` logs JSON parse errors, stale data warnings, connection drops. |

**ILA insertion strategy**: Don't add ILA probes to the core build by default (they consume BRAM and routing). Instead, maintain a separate Vivado project configuration with ILA probes on critical nets (link data/valid, FSM state, frame_valid, risk_halt). Synthesize this configuration only when debugging hardware issues.

### 7.8 Test File Inventory

| # | File | Type | Tests |
|---|------|------|-------|
| 1 | `tb_lfsr32.sv` | Unit | LFSR seed, output sequence, load behavior |
| 2 | `tb_debounce.sv` | Unit | Bounce filtering, edge detection |
| 3 | `tb_sync_fifo.sv` | Unit | FIFO operations, flags, overflow/underflow safety |
| 4 | `tb_link_tx.sv` | Unit | Serialization, timing, backpressure |
| 5 | `tb_link_rx.sv` | Unit | Deserialization, CDC sync, error detection |
| 6 | `tb_link_loopback.sv` | Unit | TX→RX round-trip, 1000 random frames |
| 7 | `tb_market_sim.sv` | Unit | Price evolution, regime switching, round-robin |
| 8 | `tb_exchange_lite.sv` | Unit | Order matching, fill/reject generation |
| 9 | `tb_tx_arbiter.sv` | Unit | Priority muxing, handshake correctness |
| 10 | `tb_msg_demux.sv` | Unit | Frame routing by msg_type |
| 11 | `tb_quote_book.sv` | Unit | Per-symbol register file updates |
| 12 | `tb_feature_compute.sv` | Unit | Mid, spread, EMA computation accuracy |
| 13 | `tb_strategy_engine.sv` | Unit | Mean-reversion decision logic |
| 14 | `tb_risk_manager.sv` | Unit | Three parallel checks, halt latch, order_enable gate |
| 15 | `tb_order_manager.sv` | Unit | ORDER frame packing, ID/timestamp assignment |
| 16 | `tb_position_tracker.sv` | Unit | Position tracking, cash accumulation |
| 17 | `tb_latency_histogram.sv` | Unit | Bin mapping, min/max/sum/count stats |
| 18 | `tb_board_a_axi_regs.sv` | Unit | AXI-Lite read/write, pulse generation |
| 19 | `tb_board_b_axi_regs.sv` | Unit | AXI-Lite read/write, histogram readout |
| 20 | `tb_board_a.sv` | Integration | Full Board A with synthetic orders |
| 21 | `tb_board_b.sv` | Integration | Full Board B with synthetic quotes |
| 22 | `tb_system.sv` | Integration | Full system, behavioral link, all regimes |
| 23 | `tb_system_cdc.sv` | Integration | Full system with 2-cycle CDC delay model |

**Total: 23 testbench files** (19 unit + 4 integration).

---

## 8. Stretch Goals

The core build delivers a fully functional dual-FPGA trading system with a single mean-reversion strategy, 4 symbols, 4-bit link, and 115200-baud telemetry. The stretch goals below extend the system's capability without requiring architectural changes — every extension was designed into the core from day one (reserved switch pins, parameterized arrays, modular strategy slot). This section covers **only** the algorithm and implementation details not already described elsewhere.

> **Cross-references**: Module definitions → §4.6.6 · Wiring changes → §4.6.8.4 · FSM independence → §4.4.5 · Pin mapping → §4.4.2 · Telemetry fields → §5.3.3 · Acceptance criteria → §7.6 (A13–A15) · Link width scaling → §4.5.4, §4.6.8.3 · Symbol scaling → §4.6.8.2

### 8.1 Stretch Goal Summary

| # | Goal | Category | Priority | Difficulty | Dependencies | Demo Impact |
|---|------|----------|----------|-----------|-------------|-------------|
| G1 | Momentum strategy | Board B strategy | High | Medium | None (standalone module) | Dashboard shows different trading behavior under trending markets |
| G2 | Neural network strategy | Board B strategy | Medium | High | PS weight-loading script | Dashboard shows ML-driven decisions; strong talking point |
| G3 | Strategy selector mux | Board B control | High | Low | G1 or G2 (needs >1 strategy) | Live strategy switching via switches during demo |
| G4 | Adaptive regime detector | Board B intelligence | Low | Medium | G1 + G2 + G3 + G5 | System auto-selects strategy — no human intervention |
| G5 | Volatility estimator | Board B feature | Low | Low | None (feeds G4) | Dashboard shows live vol estimates per symbol |
| G6 | Symbol scaling (8–16) | Both boards | Medium | Low | None (parameter change) | More instruments on dashboard; more realistic |
| G7 | 8-bit link upgrade | Link layer | Low | Low | 4 Dupont jumper wires | Halved latency — visible on histogram |
| G8 | 921600 baud telemetry | Software | Low | Trivial | None | Not visible to audience — only needed if telemetry payload grows |

**Recommended implementation order**: G1 → G3 → G6 → G2 → G5 → G4 → G7 → G8

Rationale: G1 (momentum) is the simplest new strategy and immediately enables G3 (selector), which makes the demo interactive. G6 (more symbols) is a one-line parameter change. G2 (NN) is the most impressive but requires offline training. G4 (adaptive) requires all strategies + vol estimator. G7/G8 are polish.

### 8.2 G1 — Momentum / Trend-Following Strategy

**Algorithm**: Dual-EMA crossover — a classic trend-following signal. When the fast EMA crosses above the slow EMA, the instrument is trending up (buy). When it crosses below, trending down (sell).

```
Inputs (per symbol, per quote):
  mid_price      : Q16.16 (from feature_compute)
  ema_short      : Q16.16 (already computed in core feature_compute, α ≈ 0.1)

New state (per symbol):
  ema_long[s]    : Q16.16 (slower EMA, α ≈ 0.02)

Computation:
  ema_long_new = (alpha_long × mid + (65536 - alpha_long) × ema_long_old) >> 16

  trend = ema_short - ema_long           // signed Q16.16

Decision:
  if trend > +momentum_threshold  →  BUY at ask  (riding uptrend)
  if trend < -momentum_threshold  →  SELL at bid  (riding downtrend)
  else                            →  no trade
```

**Key difference from mean-reversion**: Mean-reversion bets that price returns to the average (contrarian). Momentum bets that price continues in the current direction (trend-following). They perform well under opposite market conditions — which is exactly why adaptive switching (G4) is valuable.

**New AXI-Lite registers**:

| Register | Width | Default | Description |
|----------|-------|---------|-------------|
| `EMA_LONG_ALPHA` | 16 | 1311 (~0.02 in Q0.16) | Slow EMA smoothing factor |
| `MOMENTUM_THRESHOLD` | 32 | 0x0000_8000 ($0.50 Q16.16) | Trend signal threshold |

**Hardware cost**: 2 DSP48E2 (for the long EMA MAC), ~300 LUTs. The short EMA is reused from `feature_compute` — no duplication.

### 8.3 G2 — Neural Network Inference Strategy

**Algorithm**: A 2-layer multi-layer perceptron (MLP) maps real-time market features to a trading decision (BUY / SELL / HOLD).

```
Architecture:
  Input layer:  4 neurons  (mid_price, spread, deviation, ema)  — all Q16.16
  Hidden layer: 8 neurons  (ReLU activation)
  Output layer: 3 neurons  (BUY score, SELL score, HOLD score)
  Decision:     argmax(output)  →  highest score wins

Weight count:
  Layer 1:  4×8 weights + 8 biases = 40 parameters
  Layer 2:  8×3 weights + 3 biases = 27 parameters
  Total:    67 parameters × 16 bits (Q8.8) = 134 bytes
```

**Offline training pipeline** (Python, runs on laptop before deployment):

| Step | Tool | Input | Output |
|------|------|-------|--------|
| 1. Generate training data | `generate_training_data.py` | LFSR seed, regime params | CSV of `(mid, spread, deviation, ema, optimal_action)` |
| 2. Train MLP | `train_strategy_nn.py` (PyTorch) | Training CSV | Trained model `.pt` file |
| 3. Quantize weights | Same script | Float32 weights | Q8.8 fixed-point weight array |
| 4. Export for FPGA | Same script | Q8.8 weights | Python list or binary blob |
| 5. Load into FPGA | `telemetry_server.py` (extended) | Weight list | AXI-Lite writes to weight registers at boot |

**How training data is generated**: Run the market simulator in Python (replicating the LFSR price walk) and label each quote with the "optimal action" — the action that would have been most profitable given the next N quotes. This is hindsight labeling, but it gives the NN a reasonable signal to learn from.

**Hardware inference pipeline** (in `strategy_nn.sv`):

```
Cycle 1-4:  Layer 1 — 8 neurons, each = dot_product(4 inputs, 4 weights) + bias
            Uses 8 DSP48E2 slices (one per neuron, pipelined over 4 cycles)
            Q16.16 inputs × Q8.8 weights → Q24.24 intermediate → truncate to Q16.16
            Apply ReLU: output = max(0, result)

Cycle 5-7:  Layer 2 — 3 neurons, each = dot_product(8 hidden outputs, 8 weights) + bias
            Reuses 3 of the 8 DSPs (pipelined over 3 cycles)

Cycle 8:    argmax over 3 output scores → select BUY (0), SELL (1), or HOLD (2)
            If HOLD: signal_valid = 0 (no order)
            If BUY/SELL: signal_valid = 1, price/qty set like mean-reversion

Total: ~8 cycles = 80 ns  (still sub-100 ns, same pipeline depth as core)
```

**Weight storage**: 67 × 16-bit parameters = 134 bytes. Stored in AXI-Lite registers (small enough — no BRAM needed for weights alone, though 1 BRAM18K can be used for cleaner addressing). PS writes weights at overlay load time.

### 8.4 G4 — Adaptive Regime Detection

**Algorithm**: A rule-based classifier that observes real-time market conditions (volatility and spread from G5) and selects the optimal strategy without human intervention.

```
Inputs (per symbol, smoothed):
  vol_hat[s]     : Q16.16 (from volatility_estimator, G5)
  spread[s]      : Q16.16 (from feature_compute)
  trend[s]       : Q16.16 (from momentum strategy, G1 — ema_short - ema_long)

Classification rules:
  if vol_hat < V_LOW  and spread < S_LOW:
      detected_mode = MEAN_REVERSION        // calm, mean-reverting market
  elif vol_hat > V_HIGH and abs(trend) > T_THRESH:
      detected_mode = MOMENTUM              // trending, directional market
  elif vol_hat > V_CRISIS or spread > S_WIDE:
      detected_mode = NEURAL_NET            // stressed/unusual — use defensive NN
  else:
      detected_mode = KEEP_CURRENT          // hysteresis — don't switch yet

Hysteresis:
  A detected_mode must persist for N consecutive quotes (default N=64)
  before the strategy actually switches. This prevents thrashing between
  strategies on noisy boundary conditions.

Output:
  active_strategy[1:0]  →  feeds strategy_selector when STRATEGY_SEL = 2'b11 (auto)
  detected_regime[1:0]  →  reported to AXI-Lite status register → dashboard
```

**Configurable thresholds** (all via AXI-Lite):

| Parameter | Default (Q16.16) | Meaning |
|-----------|-------------------|---------|
| `V_LOW` | 0x0000_1000 (~0.06) | Below this vol → calm (mean-reversion territory) |
| `V_HIGH` | 0x0000_8000 (~0.50) | Above this vol → trending (momentum territory) |
| `V_CRISIS` | 0x0001_0000 (~1.00) | Above this vol → crisis (NN territory) |
| `S_LOW` | 0x0000_2000 (~0.13) | Below this spread → tight market (mean-reversion) |
| `S_WIDE` | 0x0001_0000 (~1.00) | Above this spread → wide market (NN defense) |
| `T_THRESH` | 0x0000_4000 (~0.25) | Trend magnitude needed for momentum classification |
| `HYSTERESIS_N` | 64 | Quotes before strategy switch commits |

### 8.5 G5 — Volatility Estimator

**Algorithm**: A cheap per-symbol volatility proxy using the exponential moving average of absolute price changes.

```
Per symbol, per quote:
  delta_mid = abs(mid_new - mid_old)               // unsigned Q16.16
  vol_hat[s] = (vol_alpha × delta_mid
              + (65536 - vol_alpha) × vol_hat_old) >> 16

State:
  mid_old[NUM_SYMBOLS]     : Q16.16 (previous mid price)
  vol_hat[NUM_SYMBOLS]     : Q16.16 (smoothed absolute return)

Parameter:
  vol_alpha                : Q0.16, default 3277 (~0.05)
```

This is the same EMA structure as `feature_compute` but applied to `abs(delta_mid)` instead of `mid`. Uses 2 DSP48E2 for the MAC, ~200 LUTs for abs + subtraction.

**Why this works**: `vol_hat` tracks how "jumpy" the market is. In calm markets it's low (small price steps), in volatile markets it's high (large price steps). This is a simplified version of realized volatility used in production trading systems.

### 8.6 G6 — Symbol Scaling

Change one parameter in `hft_pkg.sv` and re-synthesize:

```systemverilog
localparam int NUM_SYMBOLS = 8;   // was 4
```

**What else changes** (all automatic if coding patterns followed):
- Board A AXI register map grows: +2 registers per symbol (init_mid, init_spread) → +8 registers for 8 symbols
- Board B AXI register map grows: +1 position register per symbol → +4 registers for 8 symbols
- `config_exchange.py` and `telemetry_server.py` loops extend to cover additional symbols
- Dashboard position bar chart auto-sizes (reads array length from JSON)
- Total frame rate stays the same — just spread across more symbols (per-symbol rate = total / NUM_SYMBOLS)

**No RTL code changes**. No XDC changes. No Vivado block design changes.

### 8.7 G7 — 8-Bit Link Upgrade

Change one parameter and re-wire 4 Dupont jumper cables:

```systemverilog
localparam int LINK_DATA_W = 8;   // was 4
```

**Physical change**: All 8 pins on each PMOD header now carry data. The `valid` and `ready` signals move to the JAB extension pins (see §4.5.1 JAB table). Four Dupont wires must be connected between boards at the JAB through-holes.

**Impact**: Round-trip latency drops from ~2.07 μs to ~1.11 μs. Visible as a left-shift in the dashboard histogram. Max throughput nearly doubles (1.47M → 2.78M fps).

### 8.8 How Stretch Goals Enhance the Demo

| Step | Core Demo | With Stretch Goals |
|------|-----------|-------------------|
| Setup | 4 symbols, 1 strategy | 8 symbols, 3 strategies visible on dashboard |
| Start CALM | Mean-reversion trades | Mean-reversion selected (auto or manual) |
| Switch to VOLATILE | Same strategy, wider swings | Operator flips SW to momentum → trades follow trends. Or auto-mode selects momentum itself. |
| Switch to ADVERSARIAL | Same strategy, many rejects | Auto-mode switches to NN (defensive). NN reduces rejects. |
| Highlight latency | ~2 μs histogram | 8-bit link shows ~1 μs histogram — "we halved latency with a parameter change" |
| Return to CALM | System stabilizes | Auto-mode returns to mean-reversion. Dashboard shows strategy transitions in real time. |

The stretch goals transform the demo from "look, it works" to "look, it adapts to market conditions and we can tune it live."

---

## 9. Project Risk Management

| # | Risk Area | Likelihood | Impact | Mitigation |
|---|-----------|-----------|--------|------------|
| R1 | **PMOD link metastability / bit errors** — Two independent 100 MHz oscillators with no forwarded clock. CDC synchronizers may fail under drift or temperature change. | Medium | High (corrupted frames → wrong trades) | 2-FF synchronizers on every input. CRC-4 error detection on each frame. `link_error` counter monitored on dashboard. Bring-up Phase 4 (§7.4) validates link with 10M+ frames before proceeding. |
| R2 | **Timing closure failure** — Board B pipeline (8 stages + risk + AXI regs) may not meet 100 MHz WNS, especially with DSP48E2 chains in `feature_compute` and `strategy_engine`. | Medium | High (must re-architect pipeline) | Pipeline cut points already placed between every module. Synthesis targets 10 ns with ≥0.5 ns WNS margin. If WNS < 0, first add register slices at DSP outputs; worst case, drop to 80 MHz (still sub-μs). |
| R3 | **Fixed-point overflow / precision loss** — Q16.16 arithmetic overflows silently, producing nonsense PnL or positions. | Medium | Medium (incorrect telemetry, risk bypass) | Q32.16 cash accumulator for large sums. Saturation logic on position tracker (clamp at ±MAX). Unit testbenches sweep boundary values (§7.2). |
| R4 | **PYNQ image / driver incompatibility** — AUP-ZU3 PYNQ image may not support our Vivado version or overlay format, blocking PS-PL integration. | Low | High (no demo without PS) | Validate PYNQ overlay load in hardware bring-up Phase 2 (§7.4) before writing any pipeline RTL. Keep a fallback bare-metal C script that writes AXI registers via devmem. |
| R5 | **Schedule overrun** — 10-week capstone timeline is tight. Integration bugs or PMOD wiring issues can consume days. | High | High (incomplete demo) | Gated 10-phase hardware bring-up (§7.4) — each phase is independently demoable. Core build (no stretch) is the "ship it" baseline; stretch goals are additive. Regression script catches regressions early. |
| R6 | **FPGA resource exhaustion** — Two strategy engines + NN weights + histograms may exceed ZU3 capacity (70K LUTs, 360 DSPs). | Low | Medium (stretch goals dropped) | Core build estimated at ~35% LUT, ~25% DSP (§4.6.8.5). Stretch goals only added after core passes timing. `ifdef` guards allow per-module inclusion. |
| R7 | **UART telemetry bandwidth saturation** — At 115200 baud, JSON lines exceeding ~576 bytes/frame cause dropped data at 20 Hz. | Low | Low (dashboard gaps) | Core JSON payload is ~200 bytes — well within budget. If stretch telemetry fields push past limit, bump to 921600 baud (FTDI supports it, no HW change). |
| R8 | **Demo day hardware failure** — Loose PMOD cable, dead board, or corrupted SD card during live demo. | Low | Critical (no demo) | Bring two pre-flashed SD cards per board. Verify cables with continuity test the night before. Dashboard has a "link health" panel — if it shows errors, re-seat cables. Keep a recorded backup video of a successful run. |

---

## 10. Bill of Materials

| # | Item | Qty | Source | Notes |
|---|------|-----|--------|-------|
| 1 | AMD AUP-ZU3 (Zynq UltraScale+ XCZU3EG) | 2 | ECE 554 lab kit | Board A + Board B |
| 2 | microSD card (≥16 GB, Class 10) | 2 | Provided / personal | Pre-flashed with PYNQ image |
| 3 | USB-C cable | 2 | Provided | Power + JTAG + UART per board |
| 4 | 12-pin PMOD ribbon cable (6" / 15 cm) | 2 | Provided with board | Cable 1: A→B data · Cable 2: B→A data |
| 5 | Dupont jumper wires (F-F) | 4 | Personal / lab | Stretch only: JAB pins for 8-bit link upgrade (G7) |
| 6 | Laptop (Windows / Linux / macOS) | 1 | Personal | Runs Vivado, dashboard, serial reader |
| 7 | 5V / 3A USB-C power adapter | 2 | Provided | One per board (or powered via laptop USB-C) |

All core hardware is provided by the ECE 554 lab kit. The only additional purchase for stretch goals is 4 Dupont jumper wires (~$0.10).

---

## 11. Appendix

### Appendix A — Glossary of Financial and Technical Terms

> **Related sections**: §1 (Problem Statement), §2 (Proposed Solution), §4.3 (Data Plane), §4.5.5 (Number Representation)

#### A.1 Financial / Trading Terms

| Term | Definition | Where Used |
|------|-----------|------------|
| **Ask (Ask Price)** | The lowest price at which a seller is willing to sell a security. In our system, set by the market simulator for each symbol. A BUY order must meet or exceed the ask to be filled. | §4.3.1, §4.5.3 |
| **Bid (Bid Price)** | The highest price at which a buyer is willing to buy a security. In our system, set by the market simulator. A SELL order must be at or below the bid to be filled. | §4.3.1, §4.5.3 |
| **Spread** | The difference between the ask and bid prices: `spread = ask − bid`. A tighter spread means a more liquid market; a wider spread indicates higher risk or lower activity. Always positive. | §4.3.2 (stage 3) |
| **Mid Price** | The midpoint between bid and ask: `mid = (bid + ask) / 2`. Used as a proxy for the "true" price. Our EMA and strategy computations are based on mid price. | §4.3.2 (stage 3) |
| **Market Quote** | A message from an exchange (Board A) announcing the current best bid and ask prices and available quantities for a particular instrument. Our QUOTE frame (§4.5.3) carries this data. | §4.3.1, §4.5.3 |
| **Order** | A request to buy or sell a security at a specified price (limit price) and quantity. In our system, Board B sends ORDER frames to Board A requesting fills. | §4.3.2 (stage 7), §4.5.3 |
| **Limit Price** | The maximum price a buyer will pay (BUY) or the minimum price a seller will accept (SELL). If the market price is worse than the limit, the order is rejected. | §4.5.3 ORDER frame |
| **Fill** | Confirmation that an order has been executed (matched against the market). The FILL message contains the execution price, quantity, and echoed order ID for tracking. | §4.3.1 (step 7), §4.5.3 |
| **Reject** | Notification that an order could not be executed because the limit price did not meet the current market price. Represented as a FILL frame with `status = REJECTED` and zero fill fields. | §4.3.1 (step 7) |
| **Position** | The net quantity of shares held for a given instrument. Positive = long (net buyer), negative = short (net seller), zero = flat. Tracked per-symbol on Board B. | §4.3.2 (step 9) |
| **PnL (Profit and Loss)** | The net financial gain or loss from all trades. Our system computes **realized PnL** (cash from completed trades) and the dashboard can estimate **mark-to-market PnL** (realized + unrealized value of current positions). | §4.3.2 (step 9), §5.3.2 |
| **Cash** | The accumulated net cash flow from all fills: selling earns cash, buying spends cash. Stored in a 48-bit Q32.16 accumulator to prevent overflow. | §4.3.2 (step 9), §4.5.5 |
| **Quote Book (Order Book)** | A data structure that stores the latest bid/ask prices for each instrument. Real exchanges maintain a full *depth* of book (multiple price levels with sizes). Our `quote_book.sv` stores only the best (top-of-book) bid and ask per symbol — a simplified version. | §4.3.2 (stage 2) |
| **EMA (Exponential Moving Average)** | A smoothed average that gives more weight to recent data points. Defined as: `EMA_new = α × sample + (1−α) × EMA_old`. The smoothing factor α (0 < α < 1) controls responsiveness — higher α tracks price more tightly, lower α smooths more aggressively. ([ref](https://www.investopedia.com/terms/e/ema.asp)) | §4.3.2 (stages 3–4), §4.5.5 |
| **Mean-Reversion** | A trading strategy based on the hypothesis that prices tend to return to their historical average. When price deviates far above the EMA, it sells (expecting a drop); when far below, it buys (expecting a rise). ([ref](https://www.investopedia.com/terms/m/meanreversion.asp)) | §4.3.2 (stage 5), §8.2 |
| **Momentum / Trend-Following** | A trading strategy that bets price will continue in its current direction. Uses two EMAs (fast and slow) — when the fast crosses above the slow, it indicates an uptrend (buy signal). ([ref](https://www.investopedia.com/terms/m/momentum.asp)) | §8.2 |
| **Circuit Breaker** | A safety mechanism that halts trading when losses exceed a predefined threshold. In our system, `risk_halt` latches when `total_pnl < −max_loss`, forcing the FSM into the HALTED state. Analogous to NYSE trading halts. ([ref](https://www.investopedia.com/terms/c/circuitbreaker.asp)) | §4.4.5 (HALTED state) |
| **Risk Management** | The practice of limiting financial exposure. Our `risk_manager.sv` enforces three limits in parallel: max position per symbol, max order rate, and max cumulative loss. | §3.8, §4.3.2 (stage 6) |
| **Latency** | The time delay between a cause and its effect. In trading, *tick-to-trade latency* is the time from receiving a market quote to sending an order. Our system measures *round-trip latency* — quote departure (Board A) to fill arrival (Board B). | §3.1, §3.4, §4.3.2 (step 10) |
| **Throughput** | The rate at which the system processes messages, measured in frames/sec or quotes/sec. Our PMOD link sustains ~1.47M frames/sec (4-bit) or ~2.78M (8-bit). | §3.2, §4.5.4 |
| **Regime** | A distinct market behavior mode. Our simulator supports 4: CALM (small price steps, tight spread), VOLATILE (large steps, wide spread), BURST (high quote rate), ADVERSARIAL (extreme volatility + tight limits to trigger risk rejects). | §4.3.1 (step 2), §4.4.2 |

#### A.2 FPGA / Hardware Terms

| Term | Definition | Where Used |
|------|-----------|------------|
| **FPGA** | Field-Programmable Gate Array — a chip whose logic can be configured after manufacturing by loading a bitstream. Our platform is the Zynq UltraScale+ XCZU3EG. ([ref](https://docs.amd.com/v/u/en-US/ds891-zynq-ultrascale-plus-overview)) | Throughout |
| **PL (Programmable Logic)** | The FPGA fabric portion of a Zynq SoC. Contains LUTs, FFs, DSPs, BRAM — where our trading pipeline runs. | §4, §6 |
| **PS (Processing System)** | The hard ARM Cortex-A53 processor cores in a Zynq SoC. Runs PYNQ Linux, handles configuration and telemetry. | §5 |
| **LUT (Look-Up Table)** | The basic combinational logic element in an FPGA. A 6-input LUT can implement any Boolean function of 6 variables. Our device has 70,560 LUTs. | §4.1, §4.6.8.5 |
| **FF (Flip-Flop)** | A 1-bit storage element clocked on a clock edge. Used for registers, counters, state machines. Our device has 141,120 FFs. | §4.1, §4.6.8.5 |
| **DSP48E2** | A dedicated multiply-accumulate hard block in AMD UltraScale+ FPGAs. Can perform 27×18-bit multiplications in a single cycle. We use them for EMA computation and price×quantity products. Our device has 360 DSP slices. ([ref](https://docs.amd.com/v/u/en-US/ug579-ultrascale-dsp)) | §4.5.5, §4.6 |
| **BRAM (Block RAM)** | Dedicated dual-port memory blocks in the FPGA. Each 18Kb block can store 1024×18 or 2048×9 bits. Used for FIFOs and potential weight storage. | §4.1, §4.6.2 |
| **AXI-Lite** | A lightweight memory-mapped bus protocol from ARM/AMD used to connect the PS to PL peripherals. Supports 32-bit reads/writes at addressed register offsets. ([ref](https://docs.amd.com/r/en-US/ug1399-vitis-hls/AXI4-Lite-Interface)) | §5.1, §6.2, Appendix D |
| **MMIO (Memory-Mapped I/O)** | A technique where hardware registers are accessed via memory addresses. The PYNQ `MMIO` class provides Python read/write access to AXI-Lite mapped registers. | §5.1 |
| **LFSR (Linear Feedback Shift Register)** | A shift register whose input bit is a linear function (XOR) of its previous state. Produces a pseudo-random sequence of maximum length 2^n − 1 (for an n-bit register). Used in our market simulator for deterministic random price evolution. ([ref](https://en.wikipedia.org/wiki/Linear-feedback_shift_register)) | §4.3.1 (step 2), Appendix E |
| **CDC (Clock Domain Crossing)** | The transfer of a signal from one clock domain to another. Requires synchronization (typically a 2-FF synchronizer) to prevent metastability. Our only CDC boundary is at the PMOD link RX. ([ref](https://www.sunburst-design.com/papers/CummingsSNUG2008-Boston_CDC.pdf)) | §4.2, §4.5.2 |
| **Mesochronous** | A clocking scheme where two clock domains have the same nominal frequency but unknown phase relationship. Applies to our inter-board link — both boards use 100 MHz from independent oscillators. | §4.5.2 |
| **Metastability** | A condition where a flip-flop captures a signal during its setup/hold window, producing an indeterminate output for a brief period. The 2-FF synchronizer chain allows the first FF to resolve before the second FF samples. | §4.5.2 |
| **FSM (Finite State Machine)** | A sequential logic circuit that transitions between a finite number of states based on inputs. **Moore**: outputs depend only on current state. **Mealy**: outputs depend on current state + inputs. Board A uses a 4-state Moore FSM; Board B uses a 5-state Moore FSM. | §4.4.4, §4.4.5 |
| **FIFO (First-In First-Out)** | A queue data structure where the first item written is the first item read. Used for buffering between producer and consumer modules operating at different rates. | §4.3.1 (step 3), §4.6.2 |
| **Backpressure** | A flow-control mechanism where a downstream consumer signals upstream to stop sending data (via the `ready` signal). Prevents data loss when the consumer cannot keep up. | §4.5.3 |
| **Fixed-Point (Q-format)** | A number representation where a fixed number of bits represent the integer and fractional parts. **Qm.n** means m integer bits and n fractional bits. Q16.16 is a 32-bit number with 16 integer bits (range 0–65535) and 16 fractional bits (precision ~0.000015). ([ref](https://en.wikipedia.org/wiki/Q_(number_format))) | §4.5.5 |
| **PMOD** | A standard 12-pin connector interface for FPGA boards, originally defined by Digilent. Provides 8 signal pins + VCC + GND. Our AUP-ZU3 has a Pmod+ connector with an additional 6 JAB extension pins. ([ref](https://digilent.com/reference/pmod/start)) | §4.5.1 |
| **PYNQ** | "Python Productivity for Zynq" — an open-source framework from AMD that provides Python APIs for loading FPGA overlays and accessing PL registers from Linux on the PS. ([ref](https://www.pynq.io/)) | §5.1 |
| **XDC (Xilinx Design Constraints)** | A TCL-based constraints file that maps RTL port names to physical FPGA pin locations and defines timing constraints. | §6.3, Appendix B |
| **ILA (Integrated Logic Analyzer)** | A Vivado debug core inserted into the FPGA design to capture and display internal signals in real time. Uses BRAM for trace storage. | §7.7 |
| **VIO (Virtual I/O)** | A Vivado debug core that allows reading/writing internal FPGA signals from the Vivado hardware manager without modifying the design's functional behavior. | §7.7 |
| **Bitstream** | The binary file (`.bit`) that configures an FPGA. Generated by Vivado after synthesis and implementation. Loaded onto the device at power-on or at runtime via PYNQ `Overlay()`. | §6.4 |

### Appendix B — XDC Constraints Reference

> **Related sections**: §4.4.2 (Button/Switch/LED Mapping), §4.5.1 (PMOD Physical Layout), §6.3 (XDC Constraints)
>
> **Source**: AUP-ZU3 board master XDC file from [Real Digital](https://www.realdigital.org/hardware/aup-zu3) [4]

The following is the complete XDC constraints file used by **both boards**. Pin direction (input/output) is determined by the RTL, not the constraints.

```tcl
# ==============================================================================
# HFT Capstone — XDC Constraints for AMD AUP-ZU3
# Applies to BOTH Board A and Board B (same physical hardware)
# ==============================================================================

# --- Clock (PS FCLK0, declared for timing analysis) ---
create_clock -period 10.000 -name clk_pl [get_pins zynq_ps/FCLK_CLK0]

# --- PMOD Header A (JA) — Cable 1: data link direction 1 ---
set_property PACKAGE_PIN J12  [get_ports {pmod_a[0]}]
set_property PACKAGE_PIN H12  [get_ports {pmod_a[1]}]
set_property PACKAGE_PIN H11  [get_ports {pmod_a[2]}]
set_property PACKAGE_PIN G10  [get_ports {pmod_a[3]}]
set_property PACKAGE_PIN K13  [get_ports {pmod_a[4]}]
set_property PACKAGE_PIN K12  [get_ports {pmod_a[5]}]
set_property PACKAGE_PIN J11  [get_ports {pmod_a[6]}]
set_property PACKAGE_PIN J10  [get_ports {pmod_a[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {pmod_a[*]}]

# --- PMOD Header B (JB) — Cable 2: data link direction 2 ---
set_property PACKAGE_PIN E12  [get_ports {pmod_b[0]}]
set_property PACKAGE_PIN D11  [get_ports {pmod_b[1]}]
set_property PACKAGE_PIN B11  [get_ports {pmod_b[2]}]
set_property PACKAGE_PIN A10  [get_ports {pmod_b[3]}]
set_property PACKAGE_PIN C11  [get_ports {pmod_b[4]}]
set_property PACKAGE_PIN B10  [get_ports {pmod_b[5]}]
set_property PACKAGE_PIN A12  [get_ports {pmod_b[6]}]
set_property PACKAGE_PIN A11  [get_ports {pmod_b[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {pmod_b[*]}]

# --- PMOD+ Extension (JAB) — Stretch goal 8-bit link only ---
set_property PACKAGE_PIN F12  [get_ports {pmod_jab[0]}]
set_property PACKAGE_PIN G11  [get_ports {pmod_jab[1]}]
set_property PACKAGE_PIN E10  [get_ports {pmod_jab[2]}]
set_property PACKAGE_PIN F10  [get_ports {pmod_jab[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {pmod_jab[*]}]

# --- User Switches SW[7:0] ---
set_property PACKAGE_PIN AB1  [get_ports {sw[0]}]
set_property PACKAGE_PIN AF1  [get_ports {sw[1]}]
set_property PACKAGE_PIN AE3  [get_ports {sw[2]}]
set_property PACKAGE_PIN AC2  [get_ports {sw[3]}]
set_property PACKAGE_PIN AC1  [get_ports {sw[4]}]
set_property PACKAGE_PIN AD6  [get_ports {sw[5]}]
set_property PACKAGE_PIN AD1  [get_ports {sw[6]}]
set_property PACKAGE_PIN AD2  [get_ports {sw[7]}]
set_property IOSTANDARD LVCMOS12 [get_ports {sw[*]}]

# --- User Pushbuttons BTN[3:0] ---
set_property PACKAGE_PIN AB6  [get_ports {btn[0]}]
set_property PACKAGE_PIN AB7  [get_ports {btn[1]}]
set_property PACKAGE_PIN AB2  [get_ports {btn[2]}]
set_property PACKAGE_PIN AC6  [get_ports {btn[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {btn[*]}]

# --- User LEDs LED[7:0] ---
set_property PACKAGE_PIN AF5  [get_ports {led[0]}]
set_property PACKAGE_PIN AE7  [get_ports {led[1]}]
set_property PACKAGE_PIN AH2  [get_ports {led[2]}]
set_property PACKAGE_PIN AE5  [get_ports {led[3]}]
set_property PACKAGE_PIN AH1  [get_ports {led[4]}]
set_property PACKAGE_PIN AE4  [get_ports {led[5]}]
set_property PACKAGE_PIN AG1  [get_ports {led[6]}]
set_property PACKAGE_PIN AF2  [get_ports {led[7]}]
set_property IOSTANDARD LVCMOS12 [get_ports {led[*]}]

# --- RGB LED 0 ---
set_property PACKAGE_PIN AD7  [get_ports {rgb0[0]}] ;# Red
set_property PACKAGE_PIN AD9  [get_ports {rgb0[1]}] ;# Green
set_property PACKAGE_PIN AE9  [get_ports {rgb0[2]}] ;# Blue
set_property IOSTANDARD LVCMOS12 [get_ports {rgb0[*]}]

# --- RGB LED 1 ---
set_property PACKAGE_PIN AG9  [get_ports {rgb1[0]}] ;# Red
set_property PACKAGE_PIN AE8  [get_ports {rgb1[1]}] ;# Green
set_property PACKAGE_PIN AF8  [get_ports {rgb1[2]}] ;# Blue
set_property IOSTANDARD LVCMOS12 [get_ports {rgb1[*]}]
```

### Appendix C — Message Frame Bit-Field Reference

> **Related section**: §4.5.3 (Data Protocol — Message Frames)

All three frame types in a single reference, 128 bits each, MSB serialized first.

**QUOTE (4'h1) — Board A → Board B**

```
 127     124 123     116 115 114 113 112 111               80 79                48 47        32 31        16 15         0
┌──────────┬───────────┬────┬────┬───────┬──────────────────┬──────────────────┬──────────┬──────────┬──────────┐
│ msg_type │ symbol_id │ regime │ rsvd  │    bid_price     │    ask_price     │ bid_size │ ask_size │  seq_num │
│  4'h1    │   8-bit   │ 2b │ 2b │ 2'b0 │  Q16.16 (32b)   │  Q16.16 (32b)   │  16-bit  │  16-bit  │  16-bit  │
└──────────┴───────────┴────┴────┴───────┴──────────────────┴──────────────────┴──────────┴──────────┴──────────┘
```

**ORDER (4'h2) — Board B → Board A**

```
 127     124 123     116 115 114   112 111               80 79        64 63        48 47        32 31                  0
┌──────────┬───────────┬─────┬───────┬──────────────────┬──────────┬──────────┬──────────┬─────────────────────┐
│ msg_type │ symbol_id │side │ rsvd  │   limit_price    │ quantity │ order_id │timestamp │      reserved       │
│  4'h2    │   8-bit   │ 1b │ 3'b0  │  Q16.16 (32b)   │  16-bit  │  16-bit  │  16-bit  │      32'h0          │
└──────────┴───────────┴─────┴───────┴──────────────────┴──────────┴──────────┴──────────┴─────────────────────┘
```

**FILL (4'h3) — Board A → Board B**

```
 127     124 123     116 115 114   112 111               80 79        64 63        48 47        32 31                  0
┌──────────┬───────────┬─────┬───────┬──────────────────┬──────────┬──────────┬──────────┬─────────────────────┐
│ msg_type │ symbol_id │side │status │   fill_price     │ fill_qty │ order_id │ ts_echo  │      reserved       │
│  4'h3    │   8-bit   │ 1b │ 3-bit │  Q16.16 (32b)   │  16-bit  │  16-bit  │  16-bit  │      32'h0          │
└──────────┴───────────┴─────┴───────┴──────────────────┴──────────┴──────────┴──────────┴─────────────────────┘
  status: 000 = FILLED, 001 = REJECTED
  fill_price / fill_qty = 0 when REJECTED
  ts_echo = echoed timestamp from ORDER (for round-trip latency measurement)
```

### Appendix D — AXI-Lite Register Maps

> **Related sections**: §5.1 (PS Software Architecture), §5.3.2 (Telemetry Fields), §5.5.2 (`register_map.py`)

#### D.1 Board A Register Map

Base address: auto-assigned by Vivado block design (read from `.hwh` via PYNQ).

| Offset | Name | Width | R/W | Default | Description |
|--------|------|-------|-----|---------|-------------|
| `0x00` | `CTRL` | 32 | W | 0 | Bit 0: start pulse, Bit 1: reset pulse. Writing generates 1-cycle pulses. |
| `0x04` | `QUOTE_INTERVAL` | 32 | R/W | 1000 | Clock cycles between consecutive quote rounds (per-symbol). Lower = faster quotes. |
| `0x08` | `LFSR_SEED` | 32 | R/W | `0xDEADBEEF` | Initial seed for the 32-bit Galois LFSR. Loaded into LFSR on IDLE→RUNNING transition. |
| `0x0C` | `REGIME` | 32 | R/W | 0 | Bits 1:0: regime (00=CALM, 01=VOLATILE, 10=BURST, 11=ADVERSARIAL). Effective when `sw_override` (SW[2]) is low. |
| `0x10` | `SYM0_INIT_MID` | 32 | R/W | `0x0096_4000` | Symbol 0 initial mid price (Q16.16). $150.25 |
| `0x14` | `SYM0_INIT_SPREAD` | 32 | R/W | `0x0000_2000` | Symbol 0 initial spread (Q16.16). $0.125 |
| `0x18` | `SYM1_INIT_MID` | 32 | R/W | `0x00C8_0000` | Symbol 1 initial mid price. $200.00 |
| `0x1C` | `SYM1_INIT_SPREAD` | 32 | R/W | `0x0000_4000` | Symbol 1 initial spread. $0.25 |
| `0x20` | `SYM2_INIT_MID` | 32 | R/W | `0x0032_0000` | Symbol 2 initial mid price. $50.00 |
| `0x24` | `SYM2_INIT_SPREAD` | 32 | R/W | `0x0000_1000` | Symbol 2 initial spread. $0.0625 |
| `0x28` | `SYM3_INIT_MID` | 32 | R/W | `0x004B_0000` | Symbol 3 initial mid price. $75.00 |
| `0x2C` | `SYM3_INIT_SPREAD` | 32 | R/W | `0x0000_3000` | Symbol 3 initial spread. $0.1875 |
| `0x40` | `STATUS` | 32 | R | — | Bit 0: `running`, Bit 1: `link_up`, Bits 3:2: `active_regime` |
| `0x44` | `QUOTES_SENT` | 32 | R | 0 | Monotonic counter: total QUOTE frames generated |
| `0x48` | `ORDERS_RCVD` | 32 | R | 0 | Monotonic counter: total ORDER frames received from Board B |
| `0x4C` | `FILLS_SENT` | 32 | R | 0 | Monotonic counter: total FILL frames sent (includes rejects) |
| `0x50` | `REJECTS_SENT` | 32 | R | 0 | Monotonic counter: orders that failed price match |
| `0x54` | `LINK_ERRORS` | 32 | R | 0 | Link RX framing error count |
| `0x58` | `FIFO_FILL` | 32 | R | 0 | Current quote FIFO fill level (0–64) |

#### D.2 Board B Register Map

| Offset | Name | Width | R/W | Default | Description |
|--------|------|-------|-----|---------|-------------|
| `0x00` | `CTRL` | 32 | W | 0 | Bit 0: start pulse, Bit 1: reset pulse. 1-cycle pulses. |
| `0x04` | `STRATEGY_SEL` | 32 | R/W | 0 | Bits 1:0: strategy (0=mean-rev, 1=momentum, 2=NN, 3=auto). Core build: hardwired 0. |
| `0x08` | `THRESHOLD` | 32 | R/W | `0x0001_0000` | Mean-reversion deviation threshold (Q16.16). $1.00 |
| `0x0C` | `EMA_ALPHA` | 32 | R/W | 6554 | EMA smoothing factor (Q0.16). ~0.1 |
| `0x10` | `BASE_QTY` | 32 | R/W | 100 | Shares per order |
| `0x14` | `MAX_POSITION` | 32 | R/W | 500 | Max absolute position per symbol (shares) |
| `0x18` | `MAX_ORDER_RATE` | 32 | R/W | 1000 | Max orders per rate-limit window |
| `0x1C` | `MAX_LOSS` | 32 | R/W | `0x0064_0000` | Max cumulative loss before halt (Q16.16). $100.00 |
| | | | | | |
| `0x40` | `STATUS` | 32 | R | — | Bits 2:0: FSM state, Bit 3: `link_up`, Bit 4: `risk_halt`, Bits 6:5: `active_strategy` |
| `0x44` | `QUOTES_RCVD` | 32 | R | 0 | Total QUOTE frames received |
| `0x48` | `ORDERS_SENT` | 32 | R | 0 | Total ORDER frames sent |
| `0x4C` | `FILLS_RCVD` | 32 | R | 0 | Total FILL frames received |
| `0x50` | `RISK_REJECTS` | 32 | R | 0 | Total orders rejected by risk manager |
| `0x54` | `LINK_ERRORS` | 32 | R | 0 | Link RX framing error count |
| `0x58` | `POS_SYM0` | 32 | R | 0 | Symbol 0 position (signed int32) |
| `0x5C` | `POS_SYM1` | 32 | R | 0 | Symbol 1 position |
| `0x60` | `POS_SYM2` | 32 | R | 0 | Symbol 2 position |
| `0x64` | `POS_SYM3` | 32 | R | 0 | Symbol 3 position |
| `0x68` | `CASH_LO` | 32 | R | 0 | Cash accumulator bits [31:0] |
| `0x6C` | `CASH_HI` | 32 | R | 0 | Cash accumulator bits [47:32] (signed) |
| `0x80` | `HIST_BIN0` | 32 | R | 0 | Latency histogram bin 0 count (0–31 cycles) |
| `0x84` | `HIST_BIN1` | 32 | R | 0 | Bin 1 (32–63 cycles) |
| … | … | … | … | … | … |
| `0xBC` | `HIST_BIN15` | 32 | R | 0 | Bin 15 (≥480 cycles, overflow bucket) |
| `0xC0` | `LAT_MIN` | 32 | R | `0xFFFF` | Minimum observed latency (cycles) |
| `0xC4` | `LAT_MAX` | 32 | R | 0 | Maximum observed latency (cycles) |
| `0xC8` | `LAT_SUM` | 32 | R | 0 | Sum of all latencies (for mean) |
| `0xCC` | `LAT_COUNT` | 32 | R | 0 | Number of latency samples (= fills measured) |

**Stretch goal additions** (appended when modules exist):

| Offset | Name | R/W | Description |
|--------|------|-----|-------------|
| `0xD0` | `EMA_LONG_ALPHA` | R/W | Momentum: slow EMA alpha (Q0.16) |
| `0xD4` | `MOMENTUM_THRESH` | R/W | Momentum: trend threshold (Q16.16) |
| `0xD8`–`0xF4` | `NN_WEIGHT_0..66` | R/W | Neural network: 67 × 16-bit weights (Q8.8), packed 2 per 32-bit register |
| `0x100`–`0x10C` | `VOL_HAT_SYM0..3` | R | Volatility estimates per symbol (Q16.16) |

### Appendix E — Market Simulator and LFSR Detail

> **Related sections**: §4.3.1 (Board A Data Plane), §4.6.4 (`market_sim.sv`, `lfsr32.sv`)

#### E.1 32-Bit Galois LFSR

The market simulator uses a 32-bit Galois LFSR to generate a deterministic pseudo-random sequence. Galois LFSRs are chosen over Fibonacci LFSRs because all XOR operations happen in parallel (faster critical path).

**Polynomial**: `x^32 + x^22 + x^2 + x^1 + 1` (maximal-length, period = 2^32 − 1 = 4,294,967,295)

**Tap positions** (feedback mask): `0x00400007` — bits 22, 2, 1, 0

**Operation per clock cycle** ([ref](https://en.wikipedia.org/wiki/Linear-feedback_shift_register#Galois_LFSRs)):

```
if lfsr[0] == 1:
    lfsr = (lfsr >> 1) XOR 0x00400007
else:
    lfsr = (lfsr >> 1)
```

This produces a new 32-bit pseudo-random value every cycle. The sequence is fully deterministic given the initial seed — identical seeds produce identical sequences across runs and across different FPGA boards.

**Seed loading**: When `load` is asserted (IDLE → RUNNING transition only), `lfsr <= seed_in`. The seed must be non-zero (an all-zero LFSR is a fixed point). The PS writes the seed via AXI-Lite register `LFSR_SEED` (Appendix D.1, offset `0x08`).

#### E.2 Price Evolution Algorithm

Each quote cycle, the market simulator updates one symbol's prices:

```
1. Extract 5-bit random step from LFSR
   raw_step = lfsr_out[4:0]                         // 0 to 31

2. Convert to signed step centered at zero
   signed_step = raw_step - 16                       // -16 to +15

3. Scale by regime-dependent step size
   price_delta = signed_step × step_size[regime]     // Q16.16

4. Update mid price
   mid_price[symbol] += price_delta                  // Q16.16, wrapping

5. Clamp mid price to valid range
   if mid_price[symbol] < MIN_PRICE:
       mid_price[symbol] = MIN_PRICE                 // e.g., $1.00
   if mid_price[symbol] > MAX_PRICE:
       mid_price[symbol] = MAX_PRICE                 // e.g., $10,000

6. Compute bid and ask from mid + regime-dependent spread
   spread = base_spread[regime]
   bid_price[symbol] = mid_price[symbol] - (spread >> 1)
   ask_price[symbol] = mid_price[symbol] + (spread >> 1)

7. Pack QUOTE frame and push to FIFO
   frame = {MSG_QUOTE, symbol_id, regime, bid_price, ask_price, bid_size, ask_size, seq_num++}
```

#### E.3 Regime Parameters

| Regime | `step_size` (Q16.16) | `base_spread` (Q16.16) | `quote_interval` (cycles) | Behavior |
|--------|---------------------|------------------------|---------------------------|----------|
| CALM | `0x0000_0100` ($0.004) | `0x0000_2000` ($0.125) | 1000 (100K qps) | Small price steps, tight spread. Mean-reversion profitable. |
| VOLATILE | `0x0000_1000` ($0.063) | `0x0000_8000` ($0.50) | 1000 (100K qps) | Large price steps, wide spread. Momentum may outperform. |
| BURST | `0x0000_0100` ($0.004) | `0x0000_2000` ($0.125) | 100 (1M qps) | Same steps as CALM, but 10× faster. Stress-tests throughput. |
| ADVERSARIAL | `0x0000_4000` ($0.25) | `0x0001_0000` ($1.00) | 500 (200K qps) | Very large steps + very wide spread. Many risk rejects. PnL may hit max loss → HALTED. |

All parameters are configurable via AXI-Lite registers and can be overridden at runtime. The regime is selected by `active_regime` (§4.4.4) — either from switches or PS register.

### Appendix F — Trading Strategy Reference (Board B Modes)

> **Related sections**: §4.3.2 (Stage 5 — Strategy Engine), §8.2 (G1 Momentum), §8.3 (G2 Neural Network)

#### F.1 Mode 0 — Mean-Reversion (Core)

**Module**: `strategy_engine.sv` — always present in every build.

**Concept**: Prices fluctuate around a fair value (the EMA). When the current price deviates far from the EMA, it will likely revert. Buy low deviations (undervalued), sell high deviations (overvalued).

**Inputs**: `deviation` (= `mid − ema`, signed Q16.16), `threshold` (configurable Q16.16), `bid_price`, `ask_price`, `base_qty`.

**Decision logic**:

```
if deviation > +threshold:     // price is ABOVE average → overvalued
    action     = SELL
    order_price = bid_price    // aggressive: sell at current bid
    order_qty   = base_qty

elif deviation < -threshold:   // price is BELOW average → undervalued
    action     = BUY
    order_price = ask_price    // aggressive: buy at current ask
    order_qty   = base_qty

else:                          // price is near average → no trade
    action     = NONE
    signal_valid = 0
```

**Worked example** (Q16.16):
- `mid = $150.50` → `0x0096_8000`
- `ema = $150.00` → `0x0096_0000`
- `deviation = mid − ema = +$0.50` → `0x0000_8000`
- `threshold = $1.00` → `0x0001_0000`
- `$0.50 < $1.00` → **no trade** (deviation within normal range)

If instead `ema = $149.00` → `deviation = +$1.50` → exceeds threshold → **SELL** at bid.

**When it works well**: Calm, range-bound markets where prices oscillate around a stable mean.

**When it fails**: Trending markets — it keeps selling into a rising market (or buying into a falling one).

**Reference**: [Investopedia — Mean Reversion](https://www.investopedia.com/terms/m/meanreversion.asp)

#### F.2 Mode 1 — Momentum / Trend-Following (Stretch G1)

**Module**: `strategy_momentum.sv`

**Concept**: Prices that are rising tend to keep rising; prices that are falling tend to keep falling. Detect the trend by comparing a fast EMA (reacts quickly) to a slow EMA (reacts slowly). When the fast crosses above the slow, the market is trending up.

**Inputs**: `ema_short` (fast, α≈0.1, from `feature_compute`), `ema_long` (slow, α≈0.02, computed internally), `momentum_threshold`, `bid_price`, `ask_price`, `base_qty`.

**Decision logic**:

```
trend = ema_short - ema_long           // signed Q16.16

if trend > +momentum_threshold:        // uptrend: fast EMA above slow
    action     = BUY
    order_price = ask_price

elif trend < -momentum_threshold:      // downtrend: fast EMA below slow
    action     = SELL
    order_price = bid_price

else:
    action     = NONE
```

**Worked example**:
- `ema_short = $150.75` → `0x0096_C000`
- `ema_long  = $150.00` → `0x0096_0000`
- `trend = +$0.75` → `0x0000_C000`
- `momentum_threshold = $0.50` → `0x0000_8000`
- `$0.75 > $0.50` → **BUY** at ask (riding the uptrend)

**When it works well**: Trending, directional markets (volatile regime).

**When it fails**: Range-bound markets — it gets whipsawed by false crossover signals.

**Reference**: [Investopedia — Momentum Trading](https://www.investopedia.com/terms/m/momentum.asp), [EMA Crossover Strategy](https://www.investopedia.com/ask/answers/122414/what-exponential-moving-average-ema-formula-and-how-ema-calculated.asp)

#### F.3 Mode 2 — Neural Network Inference (Stretch G2)

**Module**: `strategy_nn.sv`

**Concept**: A small neural network (MLP) learns a mapping from market features to optimal actions by training on historical data. Unlike the rule-based strategies above, the NN can capture nonlinear patterns that simple threshold comparisons miss.

**Inputs**: 4-element feature vector (`mid_price`, `spread`, `deviation`, `ema`), all Q16.16. Weights pre-trained offline and loaded at boot.

**Decision logic**:

```
// Layer 1: 4 inputs → 8 hidden neurons, ReLU activation
for h in 0..7:
    hidden[h] = max(0, dot(inputs, weights_L1[h]) + bias_L1[h])

// Layer 2: 8 hidden → 3 output scores
scores[BUY]  = dot(hidden, weights_L2[0]) + bias_L2[0]
scores[SELL] = dot(hidden, weights_L2[1]) + bias_L2[1]
scores[HOLD] = dot(hidden, weights_L2[2]) + bias_L2[2]

// Decision: highest score wins
action = argmax(scores)
if action == HOLD:
    signal_valid = 0
elif action == BUY:
    order_price = ask_price, order_qty = base_qty
elif action == SELL:
    order_price = bid_price, order_qty = base_qty
```

**Weight format**: Q8.8 (8 integer bits, 8 fractional bits). Range ±127.996. Sufficient for small networks with normalized inputs.

**Training**: Run the LFSR market simulator in Python, label each quote with the "optimal" action (the action that would have maximized profit given the next N quotes), train using PyTorch cross-entropy loss, quantize to Q8.8, export as a list of integers, and load via AXI-Lite at boot time. See §8.3 for the full 5-step pipeline.

**When it works well**: Unusual or mixed market conditions where simple rules underperform. The NN can learn to be defensive (prefer HOLD) under extreme stress.

**When it fails**: Overfitting to the training regime parameters — may not generalize if deployed with very different market settings than it was trained on.

**Reference**: [PyTorch MLP Tutorial](https://pytorch.org/tutorials/beginner/basics/buildmodel_tutorial.html), [Fixed-Point Neural Networks — Xilinx/AMD](https://docs.amd.com/r/en-US/ug1399-vitis-hls/Fixed-Point-Types)

### Appendix G — Additional References

These references supplement those in the main References section (§References) and are cited within the Appendix.

| # | Source | Used In | Description |
|---|--------|---------|-------------|
| [A1] | [Investopedia — EMA](https://www.investopedia.com/terms/e/ema.asp) | Appendix A | Exponential Moving Average definition and formula |
| [A2] | [Investopedia — Mean Reversion](https://www.investopedia.com/terms/m/meanreversion.asp) | Appendix A, F.1 | Mean-reversion trading strategy overview |
| [A3] | [Investopedia — Momentum](https://www.investopedia.com/terms/m/momentum.asp) | Appendix A, F.2 | Momentum/trend-following strategy overview |
| [A4] | [Investopedia — Circuit Breaker](https://www.investopedia.com/terms/c/circuitbreaker.asp) | Appendix A | NYSE-style circuit breaker mechanism |
| [A5] | [Wikipedia — LFSR](https://en.wikipedia.org/wiki/Linear-feedback_shift_register) | Appendix A, E.1 | Linear Feedback Shift Register theory, Galois vs Fibonacci |
| [A6] | [Wikipedia — Q (number format)](https://en.wikipedia.org/wiki/Q_(number_format)) | Appendix A | Fixed-point Q-format notation |
| [A7] | [Sunburst Design — CDC Paper](https://www.sunburst-design.com/papers/CummingsSNUG2008-Boston_CDC.pdf) | Appendix A | Clock domain crossing best practices (Clifford Cummings) |
| [A8] | [Digilent — Pmod Standard](https://digilent.com/reference/pmod/start) | Appendix A | Pmod connector specification |
| [A9] | [AMD — DSP48E2 User Guide (UG579)](https://docs.amd.com/v/u/en-US/ug579-ultrascale-dsp) | Appendix A | DSP48E2 architecture and multiply-accumulate operations |
| [A10] | [AMD — AXI-Lite Interface](https://docs.amd.com/r/en-US/ug1399-vitis-hls/AXI4-Lite-Interface) | Appendix A | AXI4-Lite bus protocol for PL register access |
| [A11] | [PyTorch — Build the Neural Network](https://pytorch.org/tutorials/beginner/basics/buildmodel_tutorial.html) | Appendix F.3 | PyTorch MLP tutorial for the NN training pipeline |

---

## References

| # | Source | Used In | Description |
|---|--------|---------|-------------|
| [1] | [FPGA In High-Frequency Trading: A Deep FAQ (2026 Guide)](https://digitaloneagency.com.au/fpga-in-high-frequency-trading-a-deep-faq-on-firing-orders-at-hardware-speed-2026-guide/) | §3.1 Processing Speed | Production FPGA tick-to-trade latency benchmarks (50--300 ns) and CPU comparison (3--8 us) |
| [2] | [Algo-Logic Systems FPGA Tick-To-Trade](https://www.algo-logic.com/fpga-tick-to-trade) | §3.1 Processing Speed | Algo-Logic CME tick-to-trade system achieving 89.6 ns PHY+MAC round trip |
| [3] | [NYSE Sees Record Message Volumes as AI Fuels Trading (Fortune, 2025)](https://fortune.com/2025/10/15/ai-trading-flooding-wall-street-nyse-president-lynn-martin-1-2-trillion-messages/) | §3.2 Throughput | NYSE processing ~1.2 trillion order messages/day (~13.9M msgs/sec average) |
| [4] | [AUP-ZU3 Board — Real Digital](https://www.realdigital.org/hardware/aup-zu3) | §1, §4.5, §5.2, App. B | AUP-ZU3 Reference Manual, board schematic, XDC constraints, FTDI UART port |
| [5] | [AUP-ZU3 Support — AMD/Xilinx](https://xilinx.github.io/AUP-ZU3/support.html) | §5, §6 | AUP-ZU3 PYNQ image, Vivado board files, and support resources |
| [6] | [PYNQ — Python Productivity for AMD Adaptive Computing](https://www.pynq.io/) | §5.1, §5.4 | PYNQ framework documentation for overlay loading, MMIO register access, and PS-PL integration |
| [7] | [Zynq UltraScale+ MPSoC Data Sheet: Overview (DS891)](https://docs.amd.com/api/khub/documents/7AkqIn2hABg5~JsARg8IGA/content) | §4.1 (Device Resources) | Official AMD datasheet with XCZU3EG PL resource counts (LUTs, FFs, BRAM, DSP, UltraRAM) |

