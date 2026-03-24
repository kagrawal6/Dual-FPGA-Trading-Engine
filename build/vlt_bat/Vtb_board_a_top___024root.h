// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_board_a_top.h for the primary calling header

#ifndef VERILATED_VTB_BOARD_A_TOP___024ROOT_H_
#define VERILATED_VTB_BOARD_A_TOP___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_board_a_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_board_a_top___024root final {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ tb_board_a_top__DOT__clk;
        CData/*0:0*/ tb_board_a_top__DOT__rst_n;
        CData/*3:0*/ tb_board_a_top__DOT__btn;
        CData/*7:0*/ tb_board_a_top__DOT__sw;
        CData/*0:0*/ tb_board_a_top__DOT__pmod_ja_ready;
        CData/*3:0*/ tb_board_a_top__DOT__pmod_jb;
        CData/*0:0*/ tb_board_a_top__DOT__pmod_jb_valid;
        CData/*7:0*/ tb_board_a_top__DOT__s_axi_awaddr;
        CData/*0:0*/ tb_board_a_top__DOT__s_axi_awvalid;
        CData/*0:0*/ tb_board_a_top__DOT__s_axi_wvalid;
        CData/*0:0*/ tb_board_a_top__DOT__s_axi_bvalid;
        CData/*0:0*/ tb_board_a_top__DOT__s_axi_bready;
        CData/*7:0*/ tb_board_a_top__DOT__s_axi_araddr;
        CData/*0:0*/ tb_board_a_top__DOT__s_axi_arvalid;
        CData/*0:0*/ tb_board_a_top__DOT__s_axi_rvalid;
        CData/*0:0*/ tb_board_a_top__DOT__s_axi_rready;
        CData/*1:0*/ tb_board_a_top__DOT__dut__DOT__fsm_state;
        CData/*1:0*/ tb_board_a_top__DOT__dut__DOT__fsm_next;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__lfsr_load;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__axi_start_pulse;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__axi_reset_pulse;
        CData/*1:0*/ tb_board_a_top__DOT__dut__DOT__regime_from_ps;
        CData/*7:0*/ tb_board_a_top__DOT__dut__DOT__active_sym_count;
        CData/*1:0*/ tb_board_a_top__DOT__dut__DOT__active_regime;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__quote_valid_ms;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__fill_valid;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__tx_ready;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__link_up;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__frame_out_valid;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__exchange_enable;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__quote_fifo_wr_en;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__quote_fifo_rd_en;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__quote_fifo_full;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__quote_fifo_empty;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__write_fire;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__read_fire;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p0;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p1;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p2;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__btn_out_prev;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__btn_out_prev;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__btn_out_prev;
        CData/*7:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__active_count_eff;
        CData/*3:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__tick_raw;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote;
        CData/*7:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable;
        CData/*5:0*/ tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr;
        CData/*5:0*/ tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr;
        CData/*6:0*/ tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_sym_in_range;
        CData/*7:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_symbol;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__is_filled;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st;
        CData/*4:0*/ tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__beat;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__half_nibble;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_s1;
    };
    struct {
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_sync;
        CData/*3:0*/ tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__data_s1;
        CData/*3:0*/ tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__data_sync;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_prev;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__state;
        CData/*4:0*/ tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count;
        CData/*0:0*/ tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__tb_board_a_top__DOT__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__tb_board_a_top__DOT__rst_n__0;
        CData/*0:0*/ __Vtrigprevexpr_h972aab23__1;
        CData/*0:0*/ __Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_bvalid__0;
        CData/*0:0*/ __Vtrigprevexpr_h113370fe__1;
        CData/*0:0*/ __Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_rvalid__0;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VinactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        SData/*15:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_qty;
        SData/*15:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id;
        SData/*15:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp;
        SData/*15:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_qty_val;
        IData/*31:0*/ tb_board_a_top__DOT__s_axi_wdata;
        IData/*31:0*/ tb_board_a_top__DOT__s_axi_rdata;
        IData/*31:0*/ tb_board_a_top__DOT__err_count;
        IData/*31:0*/ tb_board_a_top__DOT__unnamedblk1__DOT__q;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__quote_interval;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__lfsr_seed;
        VlWide<4>/*127:0*/ tb_board_a_top__DOT__dut__DOT__fill_frame;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__quotes_generated;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__orders_rcvd;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__fills_sent;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__rejects_sent;
        VlWide<4>/*127:0*/ tb_board_a_top__DOT__dut__DOT__frame_out;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__rx_error_count;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__tok_idx;
        IData/*24:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__blink_ctr;
        IData/*16:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter;
        IData/*16:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter;
        IData/*16:0*/ tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_ctr;
        VlWide<4>/*127:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c;
        VlWide<4>/*127:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    };
    struct {
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_limit_price;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_bid;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_ask;
        IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_price_val;
        VlWide<4>/*127:0*/ tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf;
        VlWide<4>/*127:0*/ tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter;
        VlWide<4>/*127:0*/ tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg;
        VlWide<4>/*127:0*/ tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next;
        IData/*31:0*/ __VactIterCount;
        IData/*31:0*/ __VinactIterCount;
        IData/*31:0*/ __Vi;
        VlUnpacked<IData/*31:0*/, 16> tb_board_a_top__DOT__dut__DOT__sym_init_mid;
        VlUnpacked<IData/*31:0*/, 16> tb_board_a_top__DOT__dut__DOT__sym_init_spread;
        VlUnpacked<CData/*2:0*/, 16> tb_board_a_top__DOT__dut__DOT__sym_sector_id;
        VlUnpacked<SData/*15:0*/, 16> tb_board_a_top__DOT__dut__DOT__sym_company_token;
        VlUnpacked<IData/*31:0*/, 16> tb_board_a_top__DOT__dut__DOT__best_bid;
        VlUnpacked<IData/*31:0*/, 16> tb_board_a_top__DOT__dut__DOT__best_ask;
        VlUnpacked<IData/*31:0*/, 16> tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price;
        VlUnpacked<SData/*15:0*/, 16> tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num;
        VlUnpacked<IData/*31:0*/, 16> tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out;
        VlUnpacked<IData/*31:0*/, 16> tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand;
        VlUnpacked<IData/*31:0*/, 8> tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand;
        VlUnpacked<CData/*7:0*/, 8> tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop;
        VlUnpacked<IData/*31:0*/, 16> tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16;
        VlUnpacked<IData/*31:0*/, 8> tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16;
        VlUnpacked<VlWide<4>/*127:0*/, 64> tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };
    std::string __Vtask_tb_board_a_top__DOT__check__3__msg;
    std::string __Vtask_tb_board_a_top__DOT__check__4__msg;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h6fd192e6__0;
    VlTriggerScheduler __VtrigSched_h68e7d246__0;
    VlTriggerScheduler __VtrigSched_h0f1c9fb4__0;
    VlTriggerScheduler __VtrigSched_h43444ce6__0;
    VlTriggerScheduler __VtrigSched_h950459ef__0;
    VlTriggerScheduler __VtrigSched_hc95c02d3__0;

    // INTERNAL VARIABLES
    Vtb_board_a_top__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_board_a_top___024root(Vtb_board_a_top__Syms* symsp, const char* namep);
    ~Vtb_board_a_top___024root();
    VL_UNCOPYABLE(Vtb_board_a_top___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
