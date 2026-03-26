# Dual-FPGA Trading Engine — Module Block Diagrams

## 1. Full System Overview

```
╔══════════════════════════════════════════════╗         ╔══════════════════════════════════════════════════════╗
║              BOARD A (Exchange)               ║         ║                 BOARD B (Trader)                      ║
║              board_a_top.sv                   ║         ║                 board_b_top.sv                        ║
║                                               ║         ║                                                       ║
║  ┌─────────────┐     ┌──────────────────┐    ║         ║    ┌──────────────────┐     ┌─────────────┐          ║
║  │board_a_ctrl │     │board_a_axi_regs  │    ║         ║    │board_b_axi_regs  │     │board_b_ctrl │          ║
║  │   .sv       │     │   .sv            │    ║         ║    │   .sv            │     │   .sv       │          ║
║  │             │     │                  │◄═══╬═AXI═══  ║  ══╬═AXI═══►│                  │     │             │          ║
║  │ 4x debounce│     │ config + status  │    ║  PS     ║  PS║        │ config + status  │     │ 4x debounce│          ║
║  └──────┬──────┘     └────────┬─────────┘    ║         ║    └────────┬─────────┘     └──────┬──────┘          ║
║         │                     │              ║         ║             │                      │                 ║
║         ▼                     ▼              ║         ║             ▼                      ▼                 ║
║  ┌──────────────── 4-State FSM ──────────┐   ║         ║   ┌──────────────── 5-State FSM ──────────┐          ║
║  │  RESET → IDLE → RUNNING ↔ STOPPED    │   ║         ║   │ RESET→IDLE→ARMED→TRADING→HALTED      │          ║
║  └───────────────────┬───────────────────┘   ║         ║   └───────────────────┬───────────────────┘          ║
║                      │ running                ║         ║                       │ order_enable                  ║
║                      ▼                       ║         ║                       ▼                              ║
║  ┌────────────┐  quote   ┌──────────┐        ║         ║  ┌──────────┐  frame  ┌───────────┐                  ║
║  │market_sim  │─────────►│sync_fifo │        ║         ║  │ link_rx  │────────►│msg_demux  │──► QUOTE path    ║
║  │(+ lfsr32)  │ bid/ask  │(64x128b) │        ║         ║  │  .sv     │         │  .sv      │──► FILL path     ║
║  └─────┬──────┘    │     └────┬─────┘        ║         ║  └──────────┘         └───────────┘                  ║
║        │           │          │ low pri       ║         ║       ▲                    │ QUOTE        │ FILL     ║
║        │ bid/ask   │          ▼              ║         ║       │                    ▼              ▼          ║
║        │           │   ┌────────────┐        ║         ║       │          ┌──────────────┐  ┌──────────────┐  ║
║        │           │   │tx_arbiter  │        ║         ║       │          │ quote_book   │  │position_     │  ║
║        │           │   │  .sv       │        ║         ║       │          │  .sv         │  │tracker.sv    │  ║
║        ▼           │   │ hi=fill    │        ║         ║       │          └──────┬───────┘  └──────┬───────┘  ║
║  ┌────────────┐    │   │ lo=quote   │        ║         ║       │                 │                 │          ║
║  │exchange_   │    │   └─────┬──────┘        ║         ║       │                 ▼                 ▼          ║
║  │lite.sv     │ fill│        │              ║         ║       │          ┌──────────────┐  ┌──────────────┐  ║
║  │            │─────┘        │              ║         ║       │          │feature_      │  │latency_      │  ║
║  └─────┬──────┘              ▼              ║         ║       │          │compute.sv    │  │histogram.sv  │  ║
║        ▲              ┌──────────┐           ║         ║       │          └──────┬───────┘  └──────────────┘  ║
║        │              │ link_tx  │           ║         ║       │                 │                            ║
║        │              │  .sv     │           ║         ║       │                 ▼                            ║
║        │              └────┬─────┘           ║         ║       │          ┌──────────────┐                    ║
║        │                   │                 ║         ║       │          │strategy_     │                    ║
║        │                   │                 ║         ║       │          │engine.sv     │                    ║
╠════════╪═══════════════════╪═════════════════╣         ╠═══════╪══════════╪══════╪═══════╪════════════════════╣
║  PMOD  │                   │  PMOD           ║         ║ PMOD  │          │      │       │               PMOD ║
╚════════╪═══════════════════╪═════════════════╝         ╚═══════╪══════════╪══════╪═══════╪══════════════════════╝
         │                   │                                    │                 ▼
         │    Cable 2 (JB)   │         Cable 1 (JA)              │          ┌──────────────┐
         │    ORDER frames   │      QUOTE + FILL frames          │          │risk_manager  │
         │◄──────────────────╪───────────────────────────────────╯          │  .sv         │
         │                   │                                              └──────┬───────┘
         │                   ╰─────────────────────────────────────────────────►   │
         │                                                                         ▼
         │                                                                  ┌──────────────┐
         │                                                                  │order_manager │
         ╰──────────────────────────────────────────────────────────────────│  .sv         │
                                                                            └──────┬───────┘
                                                                                   │
                                                                            ┌──────▼───────┐
                                                                            │  link_tx.sv  │
                                                                            └──────────────┘
```

---

## 2. Shared Modules (rtl/shared/)

Used by **both** Board A and Board B.

```
┌─────────────────────────────────────────────────────────────────────────┐
│                        hft_pkg.sv  (PACKAGE)                            │
│                                                                         │
│  Imported by every module.  Single source of truth for:                 │
│    • FRAME_W=128, LINK_DATA_W=4, NUM_SYMBOLS=4                        │
│    • Typedefs: price_t, sprice_t, qty_t, symbol_t, position_t, etc.   │
│    • Enums: msg_type_e (QUOTE/ORDER/FILL), regime_e, strategy_e       │
│    • FSM states: a_state_e (4 states), b_state_e (5 states)           │
│    • LFSR_TAPS = 32'h00400007                                          │
└─────────────────────────────────────────────────────────────────────────┘

┌──────────────────────┐  ┌──────────────────────┐  ┌────────────────────────────────┐
│    lfsr32.sv         │  │    debounce.sv       │  │       sync_fifo.sv             │
│                      │  │                      │  │                                │
│  32-bit Galois LFSR  │  │  Button debounce +   │  │  Parameterized sync FIFO       │
│  Maximal-length poly │  │  edge detection      │  │  Configurable width & depth    │
│                      │  │                      │  │                                │
│  Ports:              │  │  Params:             │  │  Params:                       │
│   clk, rst_n         │  │   COUNTER_W (=20)    │  │   DATA_W, DEPTH,              │
│   enable             │  │                      │  │   ALMOST_FULL_THRESH           │
│   load, seed_in[31:0]│  │  Ports:              │  │                                │
│   ──►                │  │   clk, rst_n         │  │  Ports:                        │
│   rand_out[31:0]     │  │   btn_in             │  │   clk, rst_n, flush            │
│                      │  │   ──►                │  │   wr_en, wr_data ──► full      │
│  Used by:            │  │   btn_out (level)    │  │   rd_en ──► rd_data, empty     │
│   market_sim         │  │   btn_pulse (1-cyc)  │  │   almost_full, count           │
│                      │  │                      │  │                                │
│  Status: IMPLEMENTED │  │  Used by:            │  │  Used by:                      │
│          + VERIFIED  │  │   board_a_ctrl (x4)  │  │   Board A: quote FIFO         │
└──────────────────────┘  │   board_b_ctrl (x4)  │  │   Both: link_rx output buffer │
                          │                      │  │                                │
                          │  Status: IMPLEMENTED │  │  Status: STUB (not implemented)│
                          │          + VERIFIED  │  └────────────────────────────────┘
                          └──────────────────────┘
```

---

## 3. Link Layer (rtl/link/)

One instance per direction on each board.

```
  Board A                                                          Board B
  ═══════                                                          ═══════

  ┌──────────────────┐    PMOD JA (Cable 1)     ┌──────────────────┐
  │    link_tx.sv    │    A → B direction        │    link_rx.sv    │
  │                  │                           │                  │
  │ frame_in[127:0]  │    pmod_data[3:0] ──────► │ pmod_data[3:0]   │
  │ frame_in_valid ──┼──► pmod_valid     ──────► │ pmod_valid       │
  │ frame_in_ready ◄─┤    remote_ready  ◄─────── │ local_ready      │
  │                  │                           │                  │
  │  128b shift reg  │    4 bits/beat            │  2-FF CDC sync   │
  │  32 beats @50MHz │    32 beats = 640ns       │  128b shift reg  │
  │  inter-frame gap │    + 40ns gap             │  frame assembly  │
  │                  │                           │                  │
  │ Status: STUB     │    QUOTE + FILL frames    │ ──► frame_out    │
  └──────────────────┘                           │     frame_out_v  │
                                                 │     link_up      │
                                                 │     error_count  │
                                                 │                  │
                                                 │ Status: IMPL+VER│
                                                 └──────────────────┘

  ┌──────────────────┐    PMOD JB (Cable 2)     ┌──────────────────┐
  │    link_rx.sv    │    B → A direction        │    link_tx.sv    │
  │                  │                           │                  │
  │  pmod_data[3:0] ◄┼─── pmod_data[3:0] ◄───── │                  │
  │  pmod_valid     ◄┤    pmod_valid     ◄───── │ frame_in[127:0]  │
  │  local_ready    ─┼──► remote_ready   ──────► │ frame_in_valid   │
  │                  │                           │ frame_in_ready   │
  │ ──► frame_out   │    ORDER frames            │                  │
  │     frame_out_v  │                           │ Status: STUB     │
  │     link_up      │                           └──────────────────┘
  │     error_count  │
  │                  │
  │ Status: IMPL+VER │
  └──────────────────┘

  Throughput: ~1.47M frames/sec per direction (4-bit mode)
  Frame latency: 640ns serialization + 40ns gap = 680ns per frame
  Only CDC boundary in entire design: 2-FF sync in link_rx
```

---

## 4. Board A Detail (rtl/board_a/)

```
╔═══════════════════════════════════════════════════════════════════════════════════╗
║                        board_a_top.sv                                             ║
║                                                                                   ║
║  ┌─────────────────────────────────┐         ┌─────────────────────────────────┐  ║
║  │      board_a_ctrl.sv            │         │      board_a_axi_regs.sv        │  ║
║  │                                 │         │                                 │  ║
║  │  btn[3:0]──►┌────────┐         │         │  AXI-Lite Bus (from PS ARM)     │  ║
║  │             │debounce│x4       │         │         │                       │  ║
║  │             └───┬────┘         │         │         ▼                       │  ║
║  │                 │              │         │  ┌─────────────────────────┐    │  ║
║  │  ctrl_start_pulse ◄────────────┤         │  │ CONFIG REGISTERS:       │    │  ║
║  │  ctrl_stop_pulse  ◄────────────┤         │  │  CTRL (start/reset)    │    │  ║
║  │  ctrl_reset_pulse ◄────────────┤         │  │  QUOTE_INTERVAL        │    │  ║
║  │                                │         │  │  LFSR_SEED             │    │  ║
║  │  sw[1:0] ──► regime_sw[1:0]   │         │  │  REGIME                │    │  ║
║  │  sw[2]   ──► sw_override      │         │  │  SYMx_INIT_MID (x4)   │    │  ║
║  │                                │         │  │  SYMx_INIT_SPREAD (x4)│    │  ║
║  │  ◄── running, active_regime   │         │  └────────────┬────────────┘    │  ║
║  │  ◄── link_up, link_errors     │         │               │                 │  ║
║  │                                │         │  axi_start_pulse ──────────────►│  ║
║  │  led[7:0]  ──► LED pins       │         │  axi_reset_pulse ──────────────►│  ║
║  │  rgb0[2:0] ──► RGB0 (regime)  │         │  regime_from_ps ───────────────►│  ║
║  │  rgb1[2:0] ──► RGB1 (link)    │         │  quote_interval ───────────────►│  ║
║  │                                │         │  lfsr_seed ────────────────────►│  ║
║  │  Status: STUB                  │         │  sym_init_mid[], spread[] ─────►│  ║
║  └────────────────────────────────┘         │                                 │  ║
║                                              │  ◄── STATUS REGISTERS:         │  ║
║                                              │      running, link_up,         │  ║
║  ┌───────────────────────────────────────┐   │      quotes_sent, orders_rcvd, │  ║
║  │           4-State Moore FSM           │   │      fills_sent, rejects_sent, │  ║
║  │                                       │   │      link_errors, fifo_fill    │  ║
║  │  Inputs:                              │   │                                 │  ║
║  │    start = axi_start | ctrl_start    │   │  Status: STUB                   │  ║
║  │    stop  = ctrl_stop                  │   └─────────────────────────────────┘  ║
║  │    reset = axi_reset | ctrl_reset    │                                        ║
║  │                                       │                                        ║
║  │  ┌───────┐  auto  ┌──────┐           │                                        ║
║  │  │ RESET ├───────►│ IDLE │           │                                        ║
║  │  └───────┘        └──┬───┘           │                                        ║
║  │       ▲          start│               │                                        ║
║  │       │reset          ▼               │                                        ║
║  │       │         ┌──────────┐          │                                        ║
║  │  ┌────┴────┐◄───┤ RUNNING  │          │                                        ║
║  │  │ STOPPED │stop└──────────┘          │                                        ║
║  │  └─────────┘►start(resume)            │                                        ║
║  │                                       │                                        ║
║  │  Outputs:                             │                                        ║
║  │    running, counter_clr, fifo_flush   │                                        ║
║  │    lfsr_load (Mealy: IDLE→RUNNING)    │                                        ║
║  │                                       │                                        ║
║  │  active_regime = sw_override          │                                        ║
║  │                  ? regime_sw           │                                        ║
║  │                  : regime_from_ps      │                                        ║
║  └───────────────────────────────────────┘                                        ║
║                      │                                                            ║
║      ┌───────────────┴───────────────────────────────┐                            ║
║      │  running   lfsr_load    active_regime         │                            ║
║      ▼            ▼            ▼                     │                            ║
║  ┌────────────────────────────────────────────┐      │                            ║
║  │            market_sim.sv                   │      │                            ║
║  │                                            │      │                            ║
║  │  ┌──────────┐                              │      │                            ║
║  │  │lfsr32.sv │  LFSR seed from AXI regs    │      │                            ║
║  │  │          │  loaded on IDLE→RUNNING      │      │                            ║
║  │  └────┬─────┘                              │      │                            ║
║  │       │ rand_out[4:0]                      │      │                            ║
║  │       ▼                                    │      │                            ║
║  │  signed_step = rand[4:0] - 16              │      │                            ║
║  │  mid_price[sym] += step * step_size[regime]│      │                            ║
║  │  bid = mid - spread/2                      │      │                            ║
║  │  ask = mid + spread/2                      │      │                            ║
║  │  Round-robin: sym 0→1→2→3→0...            │      │                            ║
║  │                                            │      │                            ║
║  │  ──► quote_frame[127:0], quote_valid       │      │                            ║
║  │  ──► best_bid[NUM_SYM], best_ask[NUM_SYM] ┼──────┼──────┐                     ║
║  │  ──► quotes_generated (counter)            │      │      │                     ║
║  │                                            │      │      │                     ║
║  │  Status: IMPLEMENTED + VERIFIED            │      │      │                     ║
║  └─────────────────┬──────────────────────────┘      │      │                     ║
║                    │ quote_frame                      │      │                     ║
║                    ▼                                  │      │                     ║
║  ┌────────────────────────────┐                      │      │                     ║
║  │      sync_fifo.sv          │                      │      │                     ║
║  │      (Quote FIFO 64x128b) │                      │      │                     ║
║  │                            │                      │      │                     ║
║  │  wr ◄── quote_frame/valid │                      │      │                     ║
║  │  rd ──► tx_arbiter (low)  │                      │      │                     ║
║  │  almost_full ──► backpress│                      │      │                     ║
║  │                            │                      │      │                     ║
║  │  Status: STUB              │                      │      │                     ║
║  └─────────────┬──────────────┘                      │      │                     ║
║                │                                     │      │ best_bid/ask        ║
║                │ quote (low priority)                │      │                     ║
║                ▼                                     │      │                     ║
║  ┌────────────────────────────┐                      │      │                     ║
║  │      tx_arbiter.sv         │                      │      │                     ║
║  │                            │  fill (high priority)│      │                     ║
║  │  FILL  ──► (wins) ──┐     │◄─────────────────────┘      │                     ║
║  │  QUOTE ──► (waits)──┼──►  │                              │                     ║
║  │                     │     │                              │                     ║
║  │  ──► tx_frame, tx_valid   │                              │                     ║
║  │                            │                              │                     ║
║  │  Status: STUB              │                              │                     ║
║  └─────────────┬──────────────┘                              │                     ║
║                │                                             │                     ║
║                ▼                                             │                     ║
║  ┌────────────────────────────┐                              │                     ║
║  │      link_tx.sv            │                              │                     ║
║  │  128b→32 nibbles @50MHz   │          ┌────────────────────┴──────────────┐     ║
║  │                            │          │                                   │     ║
║  │  ──► pmod_ja_data[3:0]    │          │      exchange_lite.sv             │     ║
║  │  ──► pmod_ja_valid        │          │                                   │     ║
║  │  ◄── remote_ready         │          │  order_frame ◄── link_rx          │     ║
║  │                            │          │  best_bid[] ◄── market_sim       │     ║
║  │  Status: STUB              │          │  best_ask[] ◄── market_sim       │     ║
║  └────────────────────────────┘          │                                   │     ║
║                                          │  BUY:  limit >= ask? → FILL      │     ║
║  ┌────────────────────────────┐          │  SELL: limit <= bid? → FILL      │     ║
║  │      link_rx.sv            │          │  else → REJECT                   │     ║
║  │  2-FF CDC + deserialize   │          │                                   │     ║
║  │                            │          │  ──► fill_frame[127:0]           │     ║
║  │  ◄── pmod_jb_data[3:0]   │ order    │  ──► orders_rcvd, fills_sent,    │     ║
║  │  ◄── pmod_jb_valid       ├─────────►│       rejects_sent               │     ║
║  │  ──► pmod_jb_ready       │          │                                   │     ║
║  │  ──► link_up, error_count │          │  Status: IMPLEMENTED + VERIFIED   │     ║
║  │                            │          └───────────────────────────────────┘     ║
║  │  Status: IMPLEMENTED+VER  │                                                    ║
║  └────────────────────────────┘                                                    ║
║                                                                                   ║
║  board_a_top Status: SKELETON (FSM + wiring TODO)                                 ║
╚═══════════════════════════════════════════════════════════════════════════════════╝
```

---

## 5. Board B Detail (rtl/board_b/)

```
╔═══════════════════════════════════════════════════════════════════════════════════════╗
║                              board_b_top.sv                                           ║
║                                                                                       ║
║  ┌─────────────────────────────┐             ┌─────────────────────────────────────┐  ║
║  │    board_b_ctrl.sv          │             │       board_b_axi_regs.sv           │  ║
║  │                             │             │                                     │  ║
║  │  btn[3:0]──►4x debounce    │             │  AXI-Lite Bus ◄══► PS ARM (PYNQ)   │  ║
║  │  ctrl_start_pulse ──────────┤             │         │                           │  ║
║  │  ctrl_stop_pulse  ──────────┤             │         ▼                           │  ║
║  │  ctrl_reset_pulse ──────────┤             │  CONFIG:                            │  ║
║  │                             │             │   CTRL, STRATEGY_SEL, THRESHOLD,    │  ║
║  │  sw[0] ──► trading_enable   │             │   EMA_ALPHA, BASE_QTY,             │  ║
║  │  sw[2:1]──► strategy_sw     │             │   MAX_POSITION, MAX_ORDER_RATE,    │  ║
║  │  sw[3] ──► sw_strat_override│             │   MAX_LOSS                         │  ║
║  │                             │             │                                     │  ║
║  │  ◄── order_enable, risk_halt│             │  STATUS (read-only):               │  ║
║  │  ◄── link_up, total_pnl    │             │   fsm_state, link_up, risk_halt,   │  ║
║  │                             │             │   quotes_rcvd, orders_sent,        │  ║
║  │  led[3:0] ──► order flash   │             │   fills_rcvd, risk_rejects,        │  ║
║  │  led[7:4] ──► fill flash    │             │   link_errors, position[0:3],      │  ║
║  │  rgb0 ──► PnL (grn/red)    │             │   cash_lo, cash_hi,               │  ║
║  │  rgb1 ──► Risk (grn/yel/red)│             │   hist_bins[0:15], lat_min/max/   │  ║
║  │                             │             │   lat_sum/lat_count               │  ║
║  │  Status: STUB               │             │                                     │  ║
║  └─────────────────────────────┘             │  Status: STUB                       │  ║
║                                               └────────────┬──────────────────────┘  ║
║                                                             │ config params            ║
║  ┌───────────────────────────────────────────────────────┐  │                         ║
║  │                   5-State Moore FSM                    │  │                         ║
║  │                                                       │  │                         ║
║  │  Inputs:                                              │  │                         ║
║  │    start = axi_start | ctrl_start                    │  │                         ║
║  │    stop  = ctrl_stop                                  │  │                         ║
║  │    reset = axi_reset | ctrl_reset                    │  │                         ║
║  │    link_up, trading_enable, risk_halt                 │  │                         ║
║  │                                                       │  │                         ║
║  │  ┌───────┐ auto ┌──────┐ link_up ┌───────┐           │  │                         ║
║  │  │ RESET ├─────►│ IDLE ├────────►│ ARMED │           │  │                         ║
║  │  └───────┘      └──────┘         └───┬───┘           │  │                         ║
║  │       ▲                         start│& enable        │  │                         ║
║  │       │reset                         ▼               │  │                         ║
║  │       │                        ┌──────────┐          │  │                         ║
║  │       ├────────────────────────┤ TRADING  │          │  │                         ║
║  │       │                  stop/ └────┬─────┘          │  │                         ║
║  │       │                !enable      │risk_halt       │  │                         ║
║  │       │                ──►ARMED     ▼               │  │                         ║
║  │       │                       ┌──────────┐          │  │                         ║
║  │       ╰───────────────────────┤ HALTED   │          │  │                         ║
║  │                          reset└──────────┘          │  │                         ║
║  │  Key output: order_enable (HIGH only in TRADING)     │  │                         ║
║  │  Also: counter_clr, position_clr, hist_clr, flush   │  │                         ║
║  └──────────────────────┬────────────────────────────────┘  │                         ║
║                         │                                    │                         ║
║ ════════════════════════╪════════════════════════════════════╪═════════════════════   ║
║  INBOUND LINK           │                                    │                        ║
║ ════════════════════════╪════════════════════════════════════╪═════════════════════   ║
║                         │                                    │                        ║
║  ┌──────────────────┐   │                                    │                        ║
║  │   link_rx.sv     │   │                                    │                        ║
║  │                  │   │                                    │                        ║
║  │ ◄── pmod_ja     │   │   frame_out[127:0]                 │                        ║
║  │     (from A)     │───┼──────────────────┐                 │                        ║
║  │                  │   │                  │                 │                        ║
║  │ ──► link_up      │   │                  │                 │                        ║
║  │ ──► error_count  │   │                  │                 │                        ║
║  │ IMPLEMENTED+VER  │   │                  │                 │                        ║
║  └──────────────────┘   │                  │                 │                        ║
║                         │                  │                 │                        ║
║ ════════════════════════╪══════════════════╪═════════════════╪═════════════════════   ║
║  PIPELINE (Stages 1-7)  │                  │                 │                        ║
║ ════════════════════════╪══════════════════╪═════════════════╪═════════════════════   ║
║                         │                  ▼                 │                        ║
║                         │  ┌──────────────────────────────┐  │                        ║
║                         │  │ STAGE 1: msg_demux.sv [1 cyc]│  │                        ║
║                         │  │                              │  │                        ║
║                         │  │  frame_in[127:124] decode:   │  │                        ║
║                         │  │   4'h1 (QUOTE) ──► quote out │  │                        ║
║                         │  │   4'h3 (FILL)  ──► fill out  │  │                        ║
║                         │  │   other ──► demux_errors++   │  │                        ║
║                         │  │                              │  │                        ║
║                         │  │  IMPLEMENTED                 │  │                        ║
║                         │  └───────┬──────────────┬───────┘  │                        ║
║                         │          │QUOTE         │FILL      │                        ║
║                         │          ▼              ▼          │                        ║
║                         │  ┌───────────────┐  ┌───────────────────────────┐           ║
║                         │  │ STAGE 2:      │  │  FILL PATH               │           ║
║                         │  │ quote_book.sv │  │  (parallel to pipeline)   │           ║
║                         │  │ [1 cycle]     │  │                           │           ║
║                         │  │               │  │  ┌─────────────────────┐  │           ║
║                         │  │ Per-symbol    │  │  │position_tracker.sv  │  │           ║
║                         │  │ register file:│  │  │                     │  │           ║
║                         │  │ best_bid[N]   │  │  │ BUY:  pos += qty   │  │           ║
║                         │  │ best_ask[N]   │  │  │ SELL: pos -= qty   │  │           ║
║                         │  │ bid_size[N]   │  │  │ cash += ±price*qty │  │           ║
║                         │  │ ask_size[N]   │  │  │ (1x DSP48E2)      │  │           ║
║                         │  │               │  │  │                     │  │           ║
║                         │  │ IMPLEMENTED   │  │  │ ──► position[N]    │──┼──► risk   ║
║                         │  └──────┬────────┘  │  │ ──► cash[47:0]    │  │    mgr    ║
║                         │         │           │  │ ──► total_pnl     │──┼──► risk   ║
║                         │         ▼           │  │ ──► ts_echo       │  │    mgr    ║
║                         │  ┌───────────────┐  │  │ ──► fills_rcvd    │  │           ║
║                         │  │ STAGE 3-4:    │  │  │                     │  │           ║
║                         │  │feature_compute│  │  │ Status: STUB       │  │           ║
║                         │  │ .sv           │  │  └──────────┬──────────┘  │           ║
║                         │  │ [3 cycles]    │  │             │             │           ║
║                         │  │               │  │             ▼             │           ║
║                         │  │ Cyc1: mid =   │  │  ┌─────────────────────┐  │           ║
║                         │  │  (bid+ask)>>1 │  │  │latency_histogram.sv│  │           ║
║                         │  │  spread =     │  │  │                     │  │           ║
║                         │  │  ask - bid    │  │  │ lat = cycle_ctr     │  │           ║
║                         │  │               │  │  │       - ts_echo     │  │           ║
║                         │  │ Cyc2-3: EMA   │  │  │ bin = lat >> 5     │  │           ║
║                         │  │  2x DSP48E2   │  │  │ hist_bins[bin]++   │  │           ║
║                         │  │  ema_new =    │  │  │ lat_min/max/sum/cnt│  │           ║
║                         │  │  (a*mid +     │  │  │                     │  │           ║
║                         │  │  (1-a)*ema)   │  │  │ Status: STUB       │  │           ║
║                         │  │  >> 16        │  │  └─────────────────────┘  │           ║
║                         │  │               │  │                           │           ║
║                         │  │ deviation =   │  └───────────────────────────┘           ║
║                         │  │  mid - ema    │                                          ║
║                         │  │               │                                          ║
║                         │  │ Pass-through: │                                          ║
║                         │  │  bid, ask, sym│                                          ║
║                         │  │               │                                          ║
║                         │  │ IMPLEMENTED   │                                          ║
║                         │  └──────┬────────┘                                          ║
║                         │         │                                                   ║
║                         │         ▼                                                   ║
║                         │  ┌───────────────┐                                          ║
║                         │  │ STAGE 5:      │                                          ║
║                         │  │strategy_engine│                                          ║
║                         │  │ .sv           │                                          ║
║                         │  │ [1 cycle]     │                                          ║
║                         │  │               │   threshold                              ║
║                         │  │ Mean-reversion│◄──────────── (from AXI regs)             ║
║                         │  │               │   base_qty                               ║
║                         │  │ dev > +thr    │◄──────────── (from AXI regs)             ║
║                         │  │  → SELL @ bid │                                          ║
║                         │  │ dev < -thr    │                                          ║
║                         │  │  → BUY  @ ask │                                          ║
║                         │  │ else → NONE   │                                          ║
║                         │  │               │                                          ║
║                         │  │ IMPLEMENTED   │                                          ║
║                         │  └──────┬────────┘                                          ║
║                         │         │ signal_valid/side/price/qty/symbol                 ║
║                         │         ▼                                                   ║
║                         │  ┌───────────────┐                                          ║
║                         │  │ STAGE 6:      │  position[N] ◄── position_tracker        ║
║                         │  │risk_manager.sv│  total_pnl   ◄── position_tracker        ║
║                         │  │ [1 cycle]     │                                          ║
║                         │  │               │  max_position  ◄── AXI regs              ║
║                         │  │ 3 parallel    │  max_order_rate◄── AXI regs              ║
║                         │  │ checks:       │  max_loss      ◄── AXI regs              ║
║          order_enable──►│  │               │  order_enable  ◄── FSM                   ║
║          (from FSM)     │  │ 1. |pos+qty|  │                                          ║
║                         │  │    <= max_pos │                                          ║
║                         │  │ 2. rate <     │                                          ║
║                         │  │    max_rate   │                                          ║
║                         │  │ 3. pnl >     │                                          ║
║                         │  │    -max_loss  │                                          ║
║                         │  │               │                                          ║
║                         │  │ risk_halt ────┼──► FSM (TRADING→HALTED)                  ║
║                         │  │ risk_rejects  │                                          ║
║                         │  │               │                                          ║
║                         │  │ IMPLEMENTED   │                                          ║
║                         │  └──────┬────────┘                                          ║
║                         │         │ approved_valid/side/price/qty/symbol               ║
║                         │         ▼                                                   ║
║                         │  ┌───────────────┐                                          ║
║                         │  │ STAGE 7:      │                                          ║
║                         │  │order_manager  │                                          ║
║                         │  │ .sv           │                                          ║
║                         │  │ [1 cycle]     │                                          ║
║                         │  │               │  cycle_counter ◄── free-running 16-bit   ║
║                         │  │ Pack ORDER:   │                                          ║
║                         │  │ [127:124]=0x2 │                                          ║
║                         │  │ [123:116]=sym │                                          ║
║                         │  │ [115]=side    │                                          ║
║                         │  │ [111:80]=price│                                          ║
║                         │  │ [79:64]=qty   │                                          ║
║                         │  │ [63:48]=id++  │                                          ║
║                         │  │ [47:32]=tstamp│                                          ║
║                         │  │               │                                          ║
║                         │  │ IMPLEMENTED   │                                          ║
║                         │  └──────┬────────┘                                          ║
║                         │         │ order_frame[127:0]                                ║
║ ════════════════════════╪═════════╪═══════════════════════════════════════════════    ║
║  OUTBOUND LINK          │         ▼                                                   ║
║ ════════════════════════╪═════════════════════════════════════════════════════════    ║
║                         │  ┌──────────────────┐                                       ║
║                         │  │   link_tx.sv     │                                       ║
║                         │  │                  │                                       ║
║                         │  │ ──► pmod_jb      │                                       ║
║                         │  │     (to Board A) │                                       ║
║                         │  │                  │                                       ║
║                         │  │ Status: STUB     │                                       ║
║                         │  └──────────────────┘                                       ║
║                         │                                                             ║
║  Total pipeline latency: 8 cycles = 80 ns @ 100 MHz                                  ║
║                                                                                       ║
║  board_b_top Status: SKELETON (FSM + cycle_counter only)                              ║
╚═══════════════════════════════════════════════════════════════════════════════════════╝
```

---

## 6. Module Status Summary

| # | Area | Module File | Status | Testbench |
|---|------|-------------|--------|-----------|
| — | Shared | `hft_pkg.sv` | **Complete** (package) | N/A |
| 1 | Shared | `lfsr32.sv` | **Implemented + Verified** | `tb_lfsr32.sv` PASS |
| 2 | Shared | `debounce.sv` | **Implemented + Verified** | `tb_debounce.sv` PASS |
| 3 | Shared | `sync_fifo.sv` | Stub | `tb_sync_fifo.sv` empty |
| 4 | Link | `link_rx.sv` | **Implemented + Verified** | `tb_link_rx.sv` PASS |
| 5 | Link | `link_tx.sv` | Stub | `tb_link_tx.sv` empty |
| 6 | Board A | `market_sim.sv` | **Implemented + Verified** | `tb_market_sim.sv` PASS |
| 7 | Board A | `exchange_lite.sv` | **Implemented + Verified** | `tb_exchange_lite.sv` PASS |
| 8 | Board A | `tx_arbiter.sv` | Stub | `tb_tx_arbiter.sv` empty |
| 9 | Board A | `board_a_axi_regs.sv` | Stub | `tb_board_a_axi_regs.sv` empty |
| 10 | Board A | `board_a_ctrl.sv` | Stub | `tb_board_a_ctrl.sv` empty |
| 11 | Board A | `board_a_top.sv` | Skeleton | `tb_board_a_top.sv` empty |
| 12 | Board B | `msg_demux.sv` | **Implemented** | `tb_msg_demux.sv` (7 tests) |
| 13 | Board B | `quote_book.sv` | **Implemented** | `tb_quote_book.sv` (5 tests) |
| 14 | Board B | `feature_compute.sv` | **Implemented** | `tb_feature_compute.sv` (6 tests) |
| 15 | Board B | `strategy_engine.sv` | **Implemented** | `tb_strategy_engine.sv` (10 tests) |
| 16 | Board B | `risk_manager.sv` | **Implemented** | `tb_risk_manager.sv` (11 tests) |
| 17 | Board B | `order_manager.sv` | **Implemented** | `tb_order_manager.sv` (6 tests) |
| 18 | Board B | `position_tracker.sv` | Stub | `tb_position_tracker.sv` empty |
| 19 | Board B | `latency_histogram.sv` | Stub | `tb_latency_histogram.sv` empty |
| 20 | Board B | `board_b_axi_regs.sv` | Stub | `tb_board_b_axi_regs.sv` empty |
| 21 | Board B | `board_b_ctrl.sv` | Stub | `tb_board_b_ctrl.sv` empty |
| 22 | Board B | `board_b_top.sv` | Skeleton | `tb_board_b_top.sv` empty |

---

## 7. Data Flow Summary

```
                    BOARD A                                    BOARD B
                    ═══════                                    ═══════

                ┌──────────────┐                          ┌──────────────┐
                │  PS ARM      │                          │  PS ARM      │
                │config_       │                          │telemetry_    │
                │exchange.py   │                          │server.py     │
                └──────┬───────┘                          └──────┬───────┘
                       │ AXI-Lite                                │ AXI-Lite
                       ▼                                         ▼
        config ──► market_sim                    link_rx ──► msg_demux ──┬── QUOTE path:
                       │                                                │   quote_book
                       │ QUOTE frames                                   │   feature_compute
                       ▼                                                │   strategy_engine
                   sync_fifo ──► tx_arbiter ──► link_tx ════════════►  │   risk_manager
                                    ▲                  Cable 1 (JA)     │   order_manager
                                    │ FILL                              │       │
                              exchange_lite                              │       │
                                    ▲                                   │       ▼
                                    │ ORDER                              │   link_tx
                                link_rx  ◄════════════════════════════  │
                                              Cable 2 (JB)              │
                                                                        └── FILL path:
                                                                            position_tracker
                                                                            latency_histogram
                                                                                │
                                                                                ▼
                                                                        PS ──► UART ──► Laptop
                                                                                        dashboard.py
```
