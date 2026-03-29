// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_market_sim.h for the primary calling header

#ifndef VERILATED_VTB_MARKET_SIM___024ROOT_H_
#define VERILATED_VTB_MARKET_SIM___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_market_sim__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_market_sim___024root final {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ tb_market_sim__DOT__clk;
        CData/*0:0*/ tb_market_sim__DOT__rst_n;
        CData/*0:0*/ tb_market_sim__DOT__enable;
        CData/*0:0*/ tb_market_sim__DOT__lfsr_load;
        CData/*1:0*/ tb_market_sim__DOT__active_regime;
        CData/*7:0*/ tb_market_sim__DOT__active_sym_count;
        CData/*0:0*/ tb_market_sim__DOT__quote_valid;
        CData/*0:0*/ tb_market_sim__DOT__quote_ready;
        CData/*7:0*/ tb_market_sim__DOT__sym_id_u8;
        CData/*1:0*/ tb_market_sim__DOT__regime_in_frame;
        CData/*0:0*/ tb_market_sim__DOT__unnamedblk2__DOT__seen_volatile;
        CData/*7:0*/ tb_market_sim__DOT__dut__DOT__active_count_eff;
        CData/*1:0*/ tb_market_sim__DOT__dut__DOT__sym_ptr;
        CData/*0:0*/ tb_market_sim__DOT__dut__DOT__tick_raw;
        CData/*0:0*/ tb_market_sim__DOT__dut__DOT__do_quote;
        CData/*7:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff;
        CData/*0:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VstlPhaseResult;
        CData/*0:0*/ __Vtrigprevexpr___TOP__tb_market_sim__DOT__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__tb_market_sim__DOT__rst_n__0;
        CData/*0:0*/ __VactPhaseResult;
        CData/*0:0*/ __VinactPhaseResult;
        CData/*0:0*/ __VnbaPhaseResult;
        SData/*15:0*/ tb_market_sim__DOT__seq_in_frame;
        IData/*31:0*/ tb_market_sim__DOT__lfsr_seed;
        IData/*31:0*/ tb_market_sim__DOT__quote_interval;
        IData/*31:0*/ tb_market_sim__DOT__quotes_generated;
        IData/*31:0*/ tb_market_sim__DOT__err_count;
        IData/*31:0*/ tb_market_sim__DOT__bid_u;
        IData/*31:0*/ tb_market_sim__DOT__ask_u;
        IData/*31:0*/ tb_market_sim__DOT__spread_b;
        IData/*31:0*/ tb_market_sim__DOT__spread_meas;
        IData/*31:0*/ tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
        IData/*31:0*/ tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
        IData/*31:0*/ tb_market_sim__DOT__unnamedblk2__DOT__q;
        IData/*31:0*/ tb_market_sim__DOT__unnamedblk2__DOT__qg_before_block;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__step_size_q16_16;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__base_spread_q16_16;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__quote_ctr;
        VlWide<4>/*127:0*/ tb_market_sim__DOT__dut__DOT__quote_frame_hold;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__new_mid_u_c;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__new_spread_q_c;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__bid_calc_c;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__ask_calc_c;
        VlWide<4>/*127:0*/ tb_market_sim__DOT__dut__DOT__quote_frame_next_c;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
        IData/*31:0*/ __VactIterCount;
        IData/*31:0*/ __VinactIterCount;
        IData/*31:0*/ __Vi;
        VlUnpacked<CData/*2:0*/, 4> tb_market_sim__DOT__sector_id;
        VlUnpacked<IData/*31:0*/, 4> tb_market_sim__DOT__init_mid;
    };
    struct {
        VlUnpacked<IData/*31:0*/, 4> tb_market_sim__DOT__init_spread;
        VlUnpacked<IData/*31:0*/, 4> tb_market_sim__DOT__best_bid;
        VlUnpacked<SData/*15:0*/, 4> tb_market_sim__DOT__seq_expect;
        VlUnpacked<IData/*31:0*/, 4> tb_market_sim__DOT__dut__DOT__mid_price;
        VlUnpacked<SData/*15:0*/, 4> tb_market_sim__DOT__dut__DOT__seq_num;
        VlUnpacked<IData/*31:0*/, 4> tb_market_sim__DOT__dut__DOT__n_step_out;
        VlUnpacked<IData/*31:0*/, 4> tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand;
        VlUnpacked<IData/*31:0*/, 8> tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand;
        VlUnpacked<CData/*7:0*/, 8> tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop;
        VlUnpacked<IData/*31:0*/, 4> tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16;
        VlUnpacked<IData/*31:0*/, 8> tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };
    std::string __Vtask_tb_market_sim__DOT__check_one_quote__3__tag;
    std::string __Vtask_tb_market_sim__DOT__check__5__msg;
    std::string __Vtask_tb_market_sim__DOT__check__6__msg;
    std::string __Vtask_tb_market_sim__DOT__check__7__msg;
    std::string __Vtask_tb_market_sim__DOT__check__8__msg;
    std::string __Vtask_tb_market_sim__DOT__check__9__msg;
    std::string __Vtask_tb_market_sim__DOT__check__10__msg;
    std::string __Vtask_tb_market_sim__DOT__check__11__msg;
    std::string __Vtask_tb_market_sim__DOT__check__13__msg;
    std::string __Vtask_tb_market_sim__DOT__check__15__msg;
    std::string __Vtask_tb_market_sim__DOT__check__16__msg;
    std::string __Vtask_tb_market_sim__DOT__check_one_quote__20__tag;
    std::string __Vtask_tb_market_sim__DOT__check__22__msg;
    std::string __Vtask_tb_market_sim__DOT__check__23__msg;
    std::string __Vtask_tb_market_sim__DOT__check__24__msg;
    std::string __Vtask_tb_market_sim__DOT__check__25__msg;
    std::string __Vtask_tb_market_sim__DOT__check__26__msg;
    std::string __Vtask_tb_market_sim__DOT__check__27__msg;
    std::string __Vtask_tb_market_sim__DOT__check__28__msg;
    std::string __Vtask_tb_market_sim__DOT__check__30__msg;
    std::string __Vtask_tb_market_sim__DOT__check__31__msg;
    std::string __Vtask_tb_market_sim__DOT__check__32__msg;
    std::string __Vtask_tb_market_sim__DOT__check__34__msg;
    std::string __Vtask_tb_market_sim__DOT__check__35__msg;
    std::string __Vtask_tb_market_sim__DOT__check_one_quote__36__tag;
    std::string __Vtask_tb_market_sim__DOT__check__38__msg;
    std::string __Vtask_tb_market_sim__DOT__check__39__msg;
    std::string __Vtask_tb_market_sim__DOT__check__40__msg;
    std::string __Vtask_tb_market_sim__DOT__check__41__msg;
    std::string __Vtask_tb_market_sim__DOT__check__42__msg;
    std::string __Vtask_tb_market_sim__DOT__check__43__msg;
    std::string __Vtask_tb_market_sim__DOT__check__44__msg;
    std::string __Vtask_tb_market_sim__DOT__check__46__msg;
    std::string __Vtask_tb_market_sim__DOT__check_one_quote__48__tag;
    std::string __Vtask_tb_market_sim__DOT__check__50__msg;
    std::string __Vtask_tb_market_sim__DOT__check__51__msg;
    std::string __Vtask_tb_market_sim__DOT__check__52__msg;
    std::string __Vtask_tb_market_sim__DOT__check__53__msg;
    std::string __Vtask_tb_market_sim__DOT__check__54__msg;
    std::string __Vtask_tb_market_sim__DOT__check__55__msg;
    std::string __Vtask_tb_market_sim__DOT__check__56__msg;
    std::string __Vtask_tb_market_sim__DOT__check__58__msg;
    std::string __Vtask_tb_market_sim__DOT__check_one_quote__62__tag;
    std::string __Vtask_tb_market_sim__DOT__check__64__msg;
    std::string __Vtask_tb_market_sim__DOT__check__65__msg;
    std::string __Vtask_tb_market_sim__DOT__check__66__msg;
    std::string __Vtask_tb_market_sim__DOT__check__67__msg;
    std::string __Vtask_tb_market_sim__DOT__check__68__msg;
    std::string __Vtask_tb_market_sim__DOT__check__69__msg;
    std::string __Vtask_tb_market_sim__DOT__check__70__msg;
    std::string __Vtask_tb_market_sim__DOT__check__72__msg;
    std::string __Vtask_tb_market_sim__DOT__check_one_quote__77__tag;
    std::string __Vtask_tb_market_sim__DOT__check__79__msg;
    std::string __Vtask_tb_market_sim__DOT__check__80__msg;
    std::string __Vtask_tb_market_sim__DOT__check__81__msg;
    std::string __Vtask_tb_market_sim__DOT__check__82__msg;
    std::string __Vtask_tb_market_sim__DOT__check__83__msg;
    std::string __Vtask_tb_market_sim__DOT__check__84__msg;
    std::string __Vtask_tb_market_sim__DOT__check__85__msg;
    std::string __Vtask_tb_market_sim__DOT__check__87__msg;
    std::string __Vtask_tb_market_sim__DOT__check__89__msg;
    std::string __Vtask_tb_market_sim__DOT__check__91__msg;
    std::string __Vtask_tb_market_sim__DOT__check_one_quote__92__tag;
    std::string __Vtask_tb_market_sim__DOT__check__94__msg;
    std::string __Vtask_tb_market_sim__DOT__check__95__msg;
    std::string __Vtask_tb_market_sim__DOT__check__96__msg;
    std::string __Vtask_tb_market_sim__DOT__check__97__msg;
    std::string __Vtask_tb_market_sim__DOT__check__98__msg;
    std::string __Vtask_tb_market_sim__DOT__check__99__msg;
    std::string __Vtask_tb_market_sim__DOT__check__100__msg;
    std::string __Vtask_tb_market_sim__DOT__check__102__msg;
    std::string __Vtask_tb_market_sim__DOT__check__103__msg;
    std::string __Vtask_tb_market_sim__DOT__check_one_quote__107__tag;
    std::string __Vtask_tb_market_sim__DOT__check__109__msg;
    std::string __Vtask_tb_market_sim__DOT__check__110__msg;
    std::string __Vtask_tb_market_sim__DOT__check__111__msg;
    std::string __Vtask_tb_market_sim__DOT__check__112__msg;
    std::string __Vtask_tb_market_sim__DOT__check__113__msg;
    std::string __Vtask_tb_market_sim__DOT__check__114__msg;
    std::string __Vtask_tb_market_sim__DOT__check__115__msg;
    std::string __Vtask_tb_market_sim__DOT__check__117__msg;
    std::string __Vtask_tb_market_sim__DOT__check__119__msg;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h8d2e6b5d__0;
    VlTriggerScheduler __VtrigSched_h066a8c7b__0;

    // INTERNAL VARIABLES
    Vtb_market_sim__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_market_sim___024root(Vtb_market_sim__Syms* symsp, const char* namep);
    ~Vtb_market_sim___024root();
    VL_UNCOPYABLE(Vtb_market_sim___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
