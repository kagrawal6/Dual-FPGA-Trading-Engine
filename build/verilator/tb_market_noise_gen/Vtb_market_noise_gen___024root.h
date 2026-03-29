// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_market_noise_gen.h for the primary calling header

#ifndef VERILATED_VTB_MARKET_NOISE_GEN___024ROOT_H_
#define VERILATED_VTB_MARKET_NOISE_GEN___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_market_noise_gen__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_market_noise_gen___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_market_noise_gen__DOT__clk;
    CData/*0:0*/ tb_market_noise_gen__DOT__rst_n;
    CData/*0:0*/ tb_market_noise_gen__DOT__enable;
    CData/*0:0*/ tb_market_noise_gen__DOT__lfsr_load;
    CData/*0:0*/ tb_market_noise_gen__DOT__tick;
    CData/*7:0*/ tb_market_noise_gen__DOT__active_sym_count;
    CData/*0:0*/ tb_market_noise_gen__DOT__unnamedblk4__DOT__diff01;
    CData/*7:0*/ tb_market_noise_gen__DOT__dut__DOT__active_count_eff;
    CData/*0:0*/ tb_market_noise_gen__DOT__dut__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0;
    IData/*31:0*/ tb_market_noise_gen__DOT____Vlvbound_h546553af__0;
    IData/*31:0*/ tb_market_noise_gen__DOT__base_seed;
    IData/*31:0*/ tb_market_noise_gen__DOT__err_count;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    QData/*63:0*/ tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec0;
    QData/*63:0*/ tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec1;
    VlUnpacked<CData/*2:0*/, 4> tb_market_noise_gen__DOT__sector_id;
    VlUnpacked<IData/*31:0*/, 8> tb_market_noise_gen__DOT__sector_noise_q16_16;
    VlUnpacked<IData/*31:0*/, 4> tb_market_noise_gen__DOT__company_noise_q16_16;
    VlUnpacked<IData/*31:0*/, 4> tb_market_noise_gen__DOT__step_out_q16_16;
    VlUnpacked<VlUnpacked<IData/*31:0*/, 24>, 4> tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a;
    VlUnpacked<VlUnpacked<IData/*31:0*/, 24>, 4> tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b;
    VlUnpacked<VlUnpacked<IData/*31:0*/, 3>, 4> tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x;
    VlUnpacked<VlUnpacked<IData/*31:0*/, 3>, 4> tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y;
    VlUnpacked<IData/*31:0*/, 4> tb_market_noise_gen__DOT__dut__DOT__sym_rand;
    VlUnpacked<IData/*31:0*/, 8> tb_market_noise_gen__DOT__dut__DOT__sector_rand;
    VlUnpacked<CData/*7:0*/, 8> tb_market_noise_gen__DOT__dut__DOT__sector_pop;
    VlUnpacked<IData/*31:0*/, 4> tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16;
    VlUnpacked<IData/*31:0*/, 8> tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    std::string __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__5__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check_decomp__7__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check__8__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__11__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check_decomp__13__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check__14__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__20__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check_decomp__22__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check__23__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__25__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check_decomp__27__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check__28__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__30__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check_decomp__32__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check__33__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__35__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check_decomp__37__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check__38__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__41__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check_decomp__43__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check__44__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__check__45__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__check__46__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__49__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check_decomp__51__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check__52__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__check__55__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__58__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check_decomp__60__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check__61__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__check__63__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__65__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check_decomp__67__tag;
    std::string __Vtask_tb_market_noise_gen__DOT__check__68__msg;
    std::string __Vtask_tb_market_noise_gen__DOT__check__69__msg;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h04d2243f__0;
    VlTriggerScheduler __VtrigSched_h55fe2048__0;

    // INTERNAL VARIABLES
    Vtb_market_noise_gen__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_market_noise_gen___024root(Vtb_market_noise_gen__Syms* symsp, const char* namep);
    ~Vtb_market_noise_gen___024root();
    VL_UNCOPYABLE(Vtb_market_noise_gen___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
