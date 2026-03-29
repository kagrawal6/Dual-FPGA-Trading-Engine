// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_market_sim.h for the primary calling header

#include "Vtb_market_sim__pch.h"

VlCoroutine Vtb_market_sim___024root___eval_initial__TOP__Vtiming__0(Vtb_market_sim___024root* vlSelf);
VlCoroutine Vtb_market_sim___024root___eval_initial__TOP__Vtiming__1(Vtb_market_sim___024root* vlSelf);
VlCoroutine Vtb_market_sim___024root___eval_initial__TOP__Vtiming__2(Vtb_market_sim___024root* vlSelf);

void Vtb_market_sim___024root___eval_initial(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_initial\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_sim__DOT__clk = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_market_sim.vcd"s);
    VL_PRINTF_MT("-Info: C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv:78: $dumpvar ignored, as Verilated without --trace\n");
    Vtb_market_sim___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_market_sim___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_market_sim___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

VlCoroutine Vtb_market_sim___024root___eval_initial__TOP__Vtiming__0(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_sim__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000186a0ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                         42);
    vlSelfRef.tb_market_sim__DOT__rst_n = 1U;
    co_return;
}

void Vtb_market_sim___024root____VbeforeTrig_h8d2e6b5d__0(Vtb_market_sim___024root* vlSelf, const char* __VeventDescription);
void Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(Vtb_market_sim___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_market_sim___024root___eval_initial__TOP__Vtiming__1(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_1__DOT____Vrepeat0;
    tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_2__DOT____Vrepeat1;
    tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0;
    IData/*31:0*/ tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_3__DOT____Vrepeat2;
    tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_4__DOT____Vrepeat3;
    tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_4__DOT____Vrepeat3 = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__3__exp_sym;
    __Vtask_tb_market_sim__DOT__check_one_quote__3__exp_sym = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__3__sym_wrap;
    __Vtask_tb_market_sim__DOT__check_one_quote__3__sym_wrap = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__5__cond;
    __Vtask_tb_market_sim__DOT__check__5__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__6__cond;
    __Vtask_tb_market_sim__DOT__check__6__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__7__cond;
    __Vtask_tb_market_sim__DOT__check__7__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__8__cond;
    __Vtask_tb_market_sim__DOT__check__8__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__9__cond;
    __Vtask_tb_market_sim__DOT__check__9__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__10__cond;
    __Vtask_tb_market_sim__DOT__check__10__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__11__cond;
    __Vtask_tb_market_sim__DOT__check__11__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__12__Vfuncout;
    __Vfunc_tb_market_sim__DOT__base_spread_for__12__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__12__r;
    __Vfunc_tb_market_sim__DOT__base_spread_for__12__r = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__13__cond;
    __Vtask_tb_market_sim__DOT__check__13__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__14__Vfuncout;
    __Vfunc_tb_market_sim__DOT__next_sym__14__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__14__cur;
    __Vfunc_tb_market_sim__DOT__next_sym__14__cur = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__14__sym_wrap;
    __Vfunc_tb_market_sim__DOT__next_sym__14__sym_wrap = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__15__cond;
    __Vtask_tb_market_sim__DOT__check__15__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__16__cond;
    __Vtask_tb_market_sim__DOT__check__16__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__20__exp_sym;
    __Vtask_tb_market_sim__DOT__check_one_quote__20__exp_sym = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__20__sym_wrap;
    __Vtask_tb_market_sim__DOT__check_one_quote__20__sym_wrap = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__22__cond;
    __Vtask_tb_market_sim__DOT__check__22__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__23__cond;
    __Vtask_tb_market_sim__DOT__check__23__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__24__cond;
    __Vtask_tb_market_sim__DOT__check__24__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__25__cond;
    __Vtask_tb_market_sim__DOT__check__25__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__26__cond;
    __Vtask_tb_market_sim__DOT__check__26__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__27__cond;
    __Vtask_tb_market_sim__DOT__check__27__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__28__cond;
    __Vtask_tb_market_sim__DOT__check__28__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__29__Vfuncout;
    __Vfunc_tb_market_sim__DOT__base_spread_for__29__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__29__r;
    __Vfunc_tb_market_sim__DOT__base_spread_for__29__r = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__30__cond;
    __Vtask_tb_market_sim__DOT__check__30__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__31__cond;
    __Vtask_tb_market_sim__DOT__check__31__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__32__cond;
    __Vtask_tb_market_sim__DOT__check__32__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__33__Vfuncout;
    __Vfunc_tb_market_sim__DOT__next_sym__33__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__33__cur;
    __Vfunc_tb_market_sim__DOT__next_sym__33__cur = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__33__sym_wrap;
    __Vfunc_tb_market_sim__DOT__next_sym__33__sym_wrap = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__34__cond;
    __Vtask_tb_market_sim__DOT__check__34__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__35__cond;
    __Vtask_tb_market_sim__DOT__check__35__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__36__exp_sym;
    __Vtask_tb_market_sim__DOT__check_one_quote__36__exp_sym = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__36__sym_wrap;
    __Vtask_tb_market_sim__DOT__check_one_quote__36__sym_wrap = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__38__cond;
    __Vtask_tb_market_sim__DOT__check__38__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__39__cond;
    __Vtask_tb_market_sim__DOT__check__39__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__40__cond;
    __Vtask_tb_market_sim__DOT__check__40__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__41__cond;
    __Vtask_tb_market_sim__DOT__check__41__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__42__cond;
    __Vtask_tb_market_sim__DOT__check__42__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__43__cond;
    __Vtask_tb_market_sim__DOT__check__43__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__44__cond;
    __Vtask_tb_market_sim__DOT__check__44__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__45__Vfuncout;
    __Vfunc_tb_market_sim__DOT__base_spread_for__45__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__45__r;
    __Vfunc_tb_market_sim__DOT__base_spread_for__45__r = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__46__cond;
    __Vtask_tb_market_sim__DOT__check__46__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__47__Vfuncout;
    __Vfunc_tb_market_sim__DOT__next_sym__47__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__47__cur;
    __Vfunc_tb_market_sim__DOT__next_sym__47__cur = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__47__sym_wrap;
    __Vfunc_tb_market_sim__DOT__next_sym__47__sym_wrap = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__48__exp_sym;
    __Vtask_tb_market_sim__DOT__check_one_quote__48__exp_sym = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__48__sym_wrap;
    __Vtask_tb_market_sim__DOT__check_one_quote__48__sym_wrap = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__50__cond;
    __Vtask_tb_market_sim__DOT__check__50__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__51__cond;
    __Vtask_tb_market_sim__DOT__check__51__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__52__cond;
    __Vtask_tb_market_sim__DOT__check__52__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__53__cond;
    __Vtask_tb_market_sim__DOT__check__53__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__54__cond;
    __Vtask_tb_market_sim__DOT__check__54__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__55__cond;
    __Vtask_tb_market_sim__DOT__check__55__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__56__cond;
    __Vtask_tb_market_sim__DOT__check__56__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__57__Vfuncout;
    __Vfunc_tb_market_sim__DOT__base_spread_for__57__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__57__r;
    __Vfunc_tb_market_sim__DOT__base_spread_for__57__r = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__58__cond;
    __Vtask_tb_market_sim__DOT__check__58__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__62__exp_sym;
    __Vtask_tb_market_sim__DOT__check_one_quote__62__exp_sym = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__62__sym_wrap;
    __Vtask_tb_market_sim__DOT__check_one_quote__62__sym_wrap = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__64__cond;
    __Vtask_tb_market_sim__DOT__check__64__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__65__cond;
    __Vtask_tb_market_sim__DOT__check__65__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__66__cond;
    __Vtask_tb_market_sim__DOT__check__66__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__67__cond;
    __Vtask_tb_market_sim__DOT__check__67__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__68__cond;
    __Vtask_tb_market_sim__DOT__check__68__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__69__cond;
    __Vtask_tb_market_sim__DOT__check__69__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__70__cond;
    __Vtask_tb_market_sim__DOT__check__70__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__71__Vfuncout;
    __Vfunc_tb_market_sim__DOT__base_spread_for__71__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__71__r;
    __Vfunc_tb_market_sim__DOT__base_spread_for__71__r = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__72__cond;
    __Vtask_tb_market_sim__DOT__check__72__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__73__Vfuncout;
    __Vfunc_tb_market_sim__DOT__next_sym__73__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__73__cur;
    __Vfunc_tb_market_sim__DOT__next_sym__73__cur = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__73__sym_wrap;
    __Vfunc_tb_market_sim__DOT__next_sym__73__sym_wrap = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__77__exp_sym;
    __Vtask_tb_market_sim__DOT__check_one_quote__77__exp_sym = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__77__sym_wrap;
    __Vtask_tb_market_sim__DOT__check_one_quote__77__sym_wrap = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__79__cond;
    __Vtask_tb_market_sim__DOT__check__79__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__80__cond;
    __Vtask_tb_market_sim__DOT__check__80__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__81__cond;
    __Vtask_tb_market_sim__DOT__check__81__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__82__cond;
    __Vtask_tb_market_sim__DOT__check__82__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__83__cond;
    __Vtask_tb_market_sim__DOT__check__83__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__84__cond;
    __Vtask_tb_market_sim__DOT__check__84__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__85__cond;
    __Vtask_tb_market_sim__DOT__check__85__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__86__Vfuncout;
    __Vfunc_tb_market_sim__DOT__base_spread_for__86__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__86__r;
    __Vfunc_tb_market_sim__DOT__base_spread_for__86__r = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__87__cond;
    __Vtask_tb_market_sim__DOT__check__87__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__88__Vfuncout;
    __Vfunc_tb_market_sim__DOT__next_sym__88__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__88__cur;
    __Vfunc_tb_market_sim__DOT__next_sym__88__cur = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__88__sym_wrap;
    __Vfunc_tb_market_sim__DOT__next_sym__88__sym_wrap = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__89__cond;
    __Vtask_tb_market_sim__DOT__check__89__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__91__cond;
    __Vtask_tb_market_sim__DOT__check__91__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__92__exp_sym;
    __Vtask_tb_market_sim__DOT__check_one_quote__92__exp_sym = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__92__sym_wrap;
    __Vtask_tb_market_sim__DOT__check_one_quote__92__sym_wrap = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__94__cond;
    __Vtask_tb_market_sim__DOT__check__94__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__95__cond;
    __Vtask_tb_market_sim__DOT__check__95__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__96__cond;
    __Vtask_tb_market_sim__DOT__check__96__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__97__cond;
    __Vtask_tb_market_sim__DOT__check__97__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__98__cond;
    __Vtask_tb_market_sim__DOT__check__98__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__99__cond;
    __Vtask_tb_market_sim__DOT__check__99__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__100__cond;
    __Vtask_tb_market_sim__DOT__check__100__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__101__Vfuncout;
    __Vfunc_tb_market_sim__DOT__base_spread_for__101__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__101__r;
    __Vfunc_tb_market_sim__DOT__base_spread_for__101__r = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__102__cond;
    __Vtask_tb_market_sim__DOT__check__102__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__103__cond;
    __Vtask_tb_market_sim__DOT__check__103__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__107__exp_sym;
    __Vtask_tb_market_sim__DOT__check_one_quote__107__exp_sym = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__check_one_quote__107__sym_wrap;
    __Vtask_tb_market_sim__DOT__check_one_quote__107__sym_wrap = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__109__cond;
    __Vtask_tb_market_sim__DOT__check__109__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__110__cond;
    __Vtask_tb_market_sim__DOT__check__110__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__111__cond;
    __Vtask_tb_market_sim__DOT__check__111__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__112__cond;
    __Vtask_tb_market_sim__DOT__check__112__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__113__cond;
    __Vtask_tb_market_sim__DOT__check__113__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__114__cond;
    __Vtask_tb_market_sim__DOT__check__114__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__115__cond;
    __Vtask_tb_market_sim__DOT__check__115__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__116__Vfuncout;
    __Vfunc_tb_market_sim__DOT__base_spread_for__116__Vfuncout = 0;
    CData/*1:0*/ __Vfunc_tb_market_sim__DOT__base_spread_for__116__r;
    __Vfunc_tb_market_sim__DOT__base_spread_for__116__r = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__117__cond;
    __Vtask_tb_market_sim__DOT__check__117__cond = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__118__Vfuncout;
    __Vfunc_tb_market_sim__DOT__next_sym__118__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__118__cur;
    __Vfunc_tb_market_sim__DOT__next_sym__118__cur = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__next_sym__118__sym_wrap;
    __Vfunc_tb_market_sim__DOT__next_sym__118__sym_wrap = 0;
    CData/*0:0*/ __Vtask_tb_market_sim__DOT__check__119__cond;
    __Vtask_tb_market_sim__DOT__check__119__cond = 0;
    // Body
    while ((1U & (~ (IData)(vlSelfRef.tb_market_sim__DOT__rst_n)))) {
        Vtb_market_sim___024root____VbeforeTrig_h8d2e6b5d__0(vlSelf, 
                                                             "@( tb_market_sim.rst_n)");
        co_await vlSelfRef.__VtrigSched_h8d2e6b5d__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_market_sim.rst_n)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                             179);
    }
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         180);
    vlSelfRef.tb_market_sim__DOT__enable = 0U;
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 0U;
    vlSelfRef.tb_market_sim__DOT__lfsr_seed = 0xace1cafeU;
    vlSelfRef.tb_market_sim__DOT__quote_ready = 1U;
    vlSelfRef.tb_market_sim__DOT__quote_interval = 1U;
    vlSelfRef.tb_market_sim__DOT__active_regime = 0U;
    vlSelfRef.tb_market_sim__DOT__active_sym_count = 4U;
    vlSelfRef.tb_market_sim__DOT__init_mid[0U] = 0x00640000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[0U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[1U] = 0x00740000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[1U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[1U] = 1U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[2U] = 0x00840000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[2U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[2U] = 2U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[3U] = 0x00940000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[3U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[3U] = 3U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[3U] = 0U;
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 1U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         116);
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 0U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         118);
    vlSelfRef.tb_market_sim__DOT__enable = 1U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap = 3U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym = 0U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__seen_volatile = 0U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__q = 0U;
    while (VL_GTS_III(32, 0x0000003cU, vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__q)) {
        __Vtask_tb_market_sim__DOT__check_one_quote__3__sym_wrap 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
        __Vtask_tb_market_sim__DOT__check_one_quote__3__exp_sym 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
        vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__3__tag 
            = VL_SFORMATF_N_NX("P1 q%0d",0,32,vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__q) ;
        do {
            Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                                 "@(posedge tb_market_sim.clk)");
            co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_market_sim.clk)", 
                                                                 "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                                 109);
        } while ((1U & (~ (IData)(vlSelfRef.tb_market_sim__DOT__quote_valid))));
        __Vtask_tb_market_sim__DOT__check__5__cond 
            = (1U == (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                      >> 0x0000001cU));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__5__msg 
            = VL_SFORMATF_N_NX("%@: msg_type QUOTE",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__3__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__5__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__5__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__sym_id_u8 = (0x000000ffU 
                                                   & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                      >> 0x00000014U));
        __Vtask_tb_market_sim__DOT__check__6__cond 
            = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
               == (0x000000ffU & __Vtask_tb_market_sim__DOT__check_one_quote__3__exp_sym));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__6__msg 
            = VL_SFORMATF_N_NX("%@: symbol_id==%0d",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__3__tag),
                               32,__Vtask_tb_market_sim__DOT__check_one_quote__3__exp_sym) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__6__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__6__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__7__cond 
            = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
               <= (0x000000ffU & __Vtask_tb_market_sim__DOT__check_one_quote__3__sym_wrap));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__7__msg 
            = VL_SFORMATF_N_NX("%@: symbol in active range",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__3__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__7__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__7__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__regime_in_frame 
            = (3U & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                     >> 0x00000012U));
        vlSelfRef.tb_market_sim__DOT__seq_in_frame 
            = (0x0000ffffU & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[0U]);
        __Vtask_tb_market_sim__DOT__check__8__cond 
            = ((IData)(vlSelfRef.tb_market_sim__DOT__seq_in_frame) 
               == vlSelfRef.tb_market_sim__DOT__seq_expect
               [(3U & __Vtask_tb_market_sim__DOT__check_one_quote__3__exp_sym)]);
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__8__msg 
            = VL_SFORMATF_N_NX("%@: seq for sym %0d",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__3__tag),
                               32,__Vtask_tb_market_sim__DOT__check_one_quote__3__exp_sym) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__8__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__8__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__bid_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                << 0x00000010U) 
                                               | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                                  >> 0x00000010U));
        vlSelfRef.tb_market_sim__DOT__ask_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                                << 0x00000010U) 
                                               | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[1U] 
                                                  >> 0x00000010U));
        __Vtask_tb_market_sim__DOT__check__9__cond 
            = VL_GTES_III(32, vlSelfRef.tb_market_sim__DOT__ask_u, vlSelfRef.tb_market_sim__DOT__bid_u);
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__9__msg 
            = VL_SFORMATF_N_NX("%@: ask>=bid",0,-1,
                               &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__3__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__9__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__9__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__10__cond 
            = ((0x00010000U <= vlSelfRef.tb_market_sim__DOT__bid_u) 
               & (0x27100000U >= vlSelfRef.tb_market_sim__DOT__bid_u));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__10__msg 
            = VL_SFORMATF_N_NX("%@: bid range",0,-1,
                               &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__3__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__10__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__10__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__11__cond 
            = ((0x00010000U <= vlSelfRef.tb_market_sim__DOT__ask_u) 
               & (0x27100000U >= vlSelfRef.tb_market_sim__DOT__ask_u));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__11__msg 
            = VL_SFORMATF_N_NX("%@: ask range",0,-1,
                               &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__3__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__11__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__11__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vfunc_tb_market_sim__DOT__base_spread_for__12__r 
            = vlSelfRef.tb_market_sim__DOT__regime_in_frame;
        __Vfunc_tb_market_sim__DOT__base_spread_for__12__Vfuncout = 0;
        __Vfunc_tb_market_sim__DOT__base_spread_for__12__Vfuncout 
            = ((0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__12__r))
                ? 0x00002000U : ((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__12__r))
                                  ? 0x00008000U : (
                                                   (2U 
                                                    == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__12__r))
                                                    ? 0x00002000U
                                                    : 0x00010000U)));
        if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((((2U 
                                                 == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__12__r)) 
                                                << 2U) 
                                               | (((1U 
                                                    == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__12__r)) 
                                                   << 1U) 
                                                  | (0U 
                                                     == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__12__r)))))))))) {
            if ((0U != (((2U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__12__r)) 
                         << 2U) | (((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__12__r)) 
                                    << 1U) | (0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__12__r)))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:85: Assertion failed in %Ntb_market_sim.base_spread_for: unique case, but multiple matches found for '2'h%x'\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name(),
                                 2,(IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__12__r));
                    VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 85, "");
                }
            }
        }
        vlSelfRef.tb_market_sim__DOT__spread_b = __Vfunc_tb_market_sim__DOT__base_spread_for__12__Vfuncout;
        vlSelfRef.tb_market_sim__DOT__spread_meas = 
            (vlSelfRef.tb_market_sim__DOT__ask_u - vlSelfRef.tb_market_sim__DOT__bid_u);
        __Vtask_tb_market_sim__DOT__check__13__cond 
            = (vlSelfRef.tb_market_sim__DOT__spread_meas 
               == ((0U == vlSelfRef.tb_market_sim__DOT__spread_b)
                    ? 1U : vlSelfRef.tb_market_sim__DOT__spread_b));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__13__msg 
            = VL_SFORMATF_N_NX("%@: spread==regime base",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__3__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__13__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__13__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__seq_expect[(3U 
                                                  & __Vtask_tb_market_sim__DOT__check_one_quote__3__exp_sym)] 
            = (0x0000ffffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__seq_expect
                              [(3U & __Vtask_tb_market_sim__DOT__check_one_quote__3__exp_sym)]));
        if ((1U == (IData)(vlSelfRef.tb_market_sim__DOT__regime_in_frame))) {
            vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__seen_volatile = 1U;
        }
        __Vfunc_tb_market_sim__DOT__next_sym__14__sym_wrap 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
        __Vfunc_tb_market_sim__DOT__next_sym__14__cur 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
        __Vfunc_tb_market_sim__DOT__next_sym__14__Vfuncout = 0U;
        __Vfunc_tb_market_sim__DOT__next_sym__14__Vfuncout 
            = ((__Vfunc_tb_market_sim__DOT__next_sym__14__cur 
                == __Vfunc_tb_market_sim__DOT__next_sym__14__sym_wrap)
                ? 0U : ((IData)(1U) + __Vfunc_tb_market_sim__DOT__next_sym__14__cur));
        vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym 
            = __Vfunc_tb_market_sim__DOT__next_sym__14__Vfuncout;
        if ((0x0000001dU == vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__q)) {
            vlSelfRef.tb_market_sim__DOT__active_regime = 1U;
        }
        vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__q 
            = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__q);
    }
    __Vtask_tb_market_sim__DOT__check__15__cond = (0x0000003cU 
                                                   == vlSelfRef.tb_market_sim__DOT__quotes_generated);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__15__msg = "P1: quotes_generated==60"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__15__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__16__cond = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__seen_volatile;
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__16__msg = "P1: saw VOLATILE"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__16__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__enable = 0U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         202);
    vlSelfRef.tb_market_sim__DOT__enable = 0U;
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 0U;
    vlSelfRef.tb_market_sim__DOT__lfsr_seed = 0xace1cafeU;
    vlSelfRef.tb_market_sim__DOT__quote_ready = 1U;
    vlSelfRef.tb_market_sim__DOT__quote_interval = 1U;
    vlSelfRef.tb_market_sim__DOT__active_regime = 0U;
    vlSelfRef.tb_market_sim__DOT__active_sym_count = 4U;
    vlSelfRef.tb_market_sim__DOT__init_mid[0U] = 0x00640000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[0U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[1U] = 0x00740000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[1U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[1U] = 1U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[2U] = 0x00840000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[2U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[2U] = 2U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[3U] = 0x00940000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[3U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[3U] = 3U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[3U] = 0U;
    vlSelfRef.tb_market_sim__DOT__active_sym_count = 4U;
    vlSelfRef.tb_market_sim__DOT__quote_interval = 5U;
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 1U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         116);
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 0U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         118);
    vlSelfRef.tb_market_sim__DOT__enable = 1U;
    vlSelfRef.tb_market_sim__DOT__quote_ready = 1U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap = 3U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[3U] = 0U;
    __Vtask_tb_market_sim__DOT__check_one_quote__20__sym_wrap 
        = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
    __Vtask_tb_market_sim__DOT__check_one_quote__20__exp_sym 
        = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
    vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__20__tag = "P2 pre-block"s;
    do {
        Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                             "@(posedge tb_market_sim.clk)");
        co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_sim.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                             109);
    } while ((1U & (~ (IData)(vlSelfRef.tb_market_sim__DOT__quote_valid))));
    __Vtask_tb_market_sim__DOT__check__22__cond = (1U 
                                                   == 
                                                   (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                    >> 0x0000001cU));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__22__msg 
        = VL_SFORMATF_N_NX("%@: msg_type QUOTE",0,-1,
                           &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__20__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__22__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__22__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__sym_id_u8 = (0x000000ffU 
                                               & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                  >> 0x00000014U));
    __Vtask_tb_market_sim__DOT__check__23__cond = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
                                                   == 
                                                   (0x000000ffU 
                                                    & __Vtask_tb_market_sim__DOT__check_one_quote__20__exp_sym));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__23__msg 
        = VL_SFORMATF_N_NX("%@: symbol_id==%0d",0,-1,
                           &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__20__tag),
                           32,__Vtask_tb_market_sim__DOT__check_one_quote__20__exp_sym) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__23__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__23__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__24__cond = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
                                                   <= 
                                                   (0x000000ffU 
                                                    & __Vtask_tb_market_sim__DOT__check_one_quote__20__sym_wrap));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__24__msg 
        = VL_SFORMATF_N_NX("%@: symbol in active range",0,
                           -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__20__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__24__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__24__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__regime_in_frame = 
        (3U & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
               >> 0x00000012U));
    vlSelfRef.tb_market_sim__DOT__seq_in_frame = (0x0000ffffU 
                                                  & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[0U]);
    __Vtask_tb_market_sim__DOT__check__25__cond = ((IData)(vlSelfRef.tb_market_sim__DOT__seq_in_frame) 
                                                   == vlSelfRef.tb_market_sim__DOT__seq_expect
                                                   [
                                                   (3U 
                                                    & __Vtask_tb_market_sim__DOT__check_one_quote__20__exp_sym)]);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__25__msg 
        = VL_SFORMATF_N_NX("%@: seq for sym %0d",0,
                           -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__20__tag),
                           32,__Vtask_tb_market_sim__DOT__check_one_quote__20__exp_sym) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__25__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__25__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__bid_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                            << 0x00000010U) 
                                           | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                              >> 0x00000010U));
    vlSelfRef.tb_market_sim__DOT__ask_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                            << 0x00000010U) 
                                           | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[1U] 
                                              >> 0x00000010U));
    __Vtask_tb_market_sim__DOT__check__26__cond = VL_GTES_III(32, vlSelfRef.tb_market_sim__DOT__ask_u, vlSelfRef.tb_market_sim__DOT__bid_u);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__26__msg 
        = VL_SFORMATF_N_NX("%@: ask>=bid",0,-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__20__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__26__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__26__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__27__cond = (
                                                   (0x00010000U 
                                                    <= vlSelfRef.tb_market_sim__DOT__bid_u) 
                                                   & (0x27100000U 
                                                      >= vlSelfRef.tb_market_sim__DOT__bid_u));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__27__msg 
        = VL_SFORMATF_N_NX("%@: bid range",0,-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__20__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__27__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__27__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__28__cond = (
                                                   (0x00010000U 
                                                    <= vlSelfRef.tb_market_sim__DOT__ask_u) 
                                                   & (0x27100000U 
                                                      >= vlSelfRef.tb_market_sim__DOT__ask_u));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__28__msg 
        = VL_SFORMATF_N_NX("%@: ask range",0,-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__20__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__28__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__28__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vfunc_tb_market_sim__DOT__base_spread_for__29__r 
        = vlSelfRef.tb_market_sim__DOT__regime_in_frame;
    __Vfunc_tb_market_sim__DOT__base_spread_for__29__Vfuncout = 0;
    __Vfunc_tb_market_sim__DOT__base_spread_for__29__Vfuncout 
        = ((0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__29__r))
            ? 0x00002000U : ((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__29__r))
                              ? 0x00008000U : ((2U 
                                                == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__29__r))
                                                ? 0x00002000U
                                                : 0x00010000U)));
    if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((((2U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__29__r)) 
                                            << 2U) 
                                           | (((1U 
                                                == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__29__r)) 
                                               << 1U) 
                                              | (0U 
                                                 == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__29__r)))))))))) {
        if ((0U != (((2U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__29__r)) 
                     << 2U) | (((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__29__r)) 
                                << 1U) | (0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__29__r)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:85: Assertion failed in %Ntb_market_sim.base_spread_for: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__29__r));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 85, "");
            }
        }
    }
    vlSelfRef.tb_market_sim__DOT__spread_b = __Vfunc_tb_market_sim__DOT__base_spread_for__29__Vfuncout;
    vlSelfRef.tb_market_sim__DOT__spread_meas = (vlSelfRef.tb_market_sim__DOT__ask_u 
                                                 - vlSelfRef.tb_market_sim__DOT__bid_u);
    __Vtask_tb_market_sim__DOT__check__30__cond = (vlSelfRef.tb_market_sim__DOT__spread_meas 
                                                   == 
                                                   ((0U 
                                                     == vlSelfRef.tb_market_sim__DOT__spread_b)
                                                     ? 1U
                                                     : vlSelfRef.tb_market_sim__DOT__spread_b));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__30__msg 
        = VL_SFORMATF_N_NX("%@: spread==regime base",0,
                           -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__20__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__30__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__30__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__seq_expect[(3U & __Vtask_tb_market_sim__DOT__check_one_quote__20__exp_sym)] 
        = (0x0000ffffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__seq_expect
                          [(3U & __Vtask_tb_market_sim__DOT__check_one_quote__20__exp_sym)]));
    __Vtask_tb_market_sim__DOT__check__31__cond = vlSelfRef.tb_market_sim__DOT__quote_valid;
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__31__msg = "P2 quote_valid pulse width: high on emission cycle"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__31__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__31__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         217);
    __Vtask_tb_market_sim__DOT__check__32__cond = (1U 
                                                   & (~ (IData)(vlSelfRef.tb_market_sim__DOT__quote_valid)));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__32__msg = "P2 quote_valid pulse width: low next cycle (no back-to-back tick)"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__32__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__32__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vfunc_tb_market_sim__DOT__next_sym__33__sym_wrap 
        = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
    __Vfunc_tb_market_sim__DOT__next_sym__33__cur = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
    __Vfunc_tb_market_sim__DOT__next_sym__33__Vfuncout = 0U;
    __Vfunc_tb_market_sim__DOT__next_sym__33__Vfuncout 
        = ((__Vfunc_tb_market_sim__DOT__next_sym__33__cur 
            == __Vfunc_tb_market_sim__DOT__next_sym__33__sym_wrap)
            ? 0U : ((IData)(1U) + __Vfunc_tb_market_sim__DOT__next_sym__33__cur));
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym 
        = __Vfunc_tb_market_sim__DOT__next_sym__33__Vfuncout;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__qg_before_block 
        = vlSelfRef.tb_market_sim__DOT__quotes_generated;
    vlSelfRef.tb_market_sim__DOT__quote_ready = 0U;
    tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0x00000028U;
    while (VL_LTS_III(32, 0U, tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                             "@(posedge tb_market_sim.clk)");
        co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_sim.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                             225);
        __Vtask_tb_market_sim__DOT__check__34__cond 
            = (1U & (~ (IData)(vlSelfRef.tb_market_sim__DOT__quote_valid)));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__34__msg = "P2: no quote_valid while blocked"s;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__34__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__34__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__35__cond 
            = (vlSelfRef.tb_market_sim__DOT__quotes_generated 
               == vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__qg_before_block);
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__35__msg = "P2: quotes_generated stable while blocked"s;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__35__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__35__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.tb_market_sim__DOT__quote_ready = 1U;
    __Vtask_tb_market_sim__DOT__check_one_quote__36__sym_wrap 
        = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
    __Vtask_tb_market_sim__DOT__check_one_quote__36__exp_sym 
        = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
    vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__36__tag = "P2 post-block"s;
    do {
        Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                             "@(posedge tb_market_sim.clk)");
        co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_sim.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                             109);
    } while ((1U & (~ (IData)(vlSelfRef.tb_market_sim__DOT__quote_valid))));
    __Vtask_tb_market_sim__DOT__check__38__cond = (1U 
                                                   == 
                                                   (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                    >> 0x0000001cU));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__38__msg 
        = VL_SFORMATF_N_NX("%@: msg_type QUOTE",0,-1,
                           &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__36__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__38__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__38__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__sym_id_u8 = (0x000000ffU 
                                               & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                  >> 0x00000014U));
    __Vtask_tb_market_sim__DOT__check__39__cond = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
                                                   == 
                                                   (0x000000ffU 
                                                    & __Vtask_tb_market_sim__DOT__check_one_quote__36__exp_sym));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__39__msg 
        = VL_SFORMATF_N_NX("%@: symbol_id==%0d",0,-1,
                           &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__36__tag),
                           32,__Vtask_tb_market_sim__DOT__check_one_quote__36__exp_sym) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__39__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__40__cond = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
                                                   <= 
                                                   (0x000000ffU 
                                                    & __Vtask_tb_market_sim__DOT__check_one_quote__36__sym_wrap));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__40__msg 
        = VL_SFORMATF_N_NX("%@: symbol in active range",0,
                           -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__36__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__40__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__40__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__regime_in_frame = 
        (3U & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
               >> 0x00000012U));
    vlSelfRef.tb_market_sim__DOT__seq_in_frame = (0x0000ffffU 
                                                  & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[0U]);
    __Vtask_tb_market_sim__DOT__check__41__cond = ((IData)(vlSelfRef.tb_market_sim__DOT__seq_in_frame) 
                                                   == vlSelfRef.tb_market_sim__DOT__seq_expect
                                                   [
                                                   (3U 
                                                    & __Vtask_tb_market_sim__DOT__check_one_quote__36__exp_sym)]);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__41__msg 
        = VL_SFORMATF_N_NX("%@: seq for sym %0d",0,
                           -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__36__tag),
                           32,__Vtask_tb_market_sim__DOT__check_one_quote__36__exp_sym) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__41__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__41__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__bid_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                            << 0x00000010U) 
                                           | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                              >> 0x00000010U));
    vlSelfRef.tb_market_sim__DOT__ask_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                            << 0x00000010U) 
                                           | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[1U] 
                                              >> 0x00000010U));
    __Vtask_tb_market_sim__DOT__check__42__cond = VL_GTES_III(32, vlSelfRef.tb_market_sim__DOT__ask_u, vlSelfRef.tb_market_sim__DOT__bid_u);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__42__msg 
        = VL_SFORMATF_N_NX("%@: ask>=bid",0,-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__36__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__42__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__42__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__43__cond = (
                                                   (0x00010000U 
                                                    <= vlSelfRef.tb_market_sim__DOT__bid_u) 
                                                   & (0x27100000U 
                                                      >= vlSelfRef.tb_market_sim__DOT__bid_u));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__43__msg 
        = VL_SFORMATF_N_NX("%@: bid range",0,-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__36__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__43__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__43__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__44__cond = (
                                                   (0x00010000U 
                                                    <= vlSelfRef.tb_market_sim__DOT__ask_u) 
                                                   & (0x27100000U 
                                                      >= vlSelfRef.tb_market_sim__DOT__ask_u));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__44__msg 
        = VL_SFORMATF_N_NX("%@: ask range",0,-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__36__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__44__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__44__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vfunc_tb_market_sim__DOT__base_spread_for__45__r 
        = vlSelfRef.tb_market_sim__DOT__regime_in_frame;
    __Vfunc_tb_market_sim__DOT__base_spread_for__45__Vfuncout = 0;
    __Vfunc_tb_market_sim__DOT__base_spread_for__45__Vfuncout 
        = ((0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__45__r))
            ? 0x00002000U : ((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__45__r))
                              ? 0x00008000U : ((2U 
                                                == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__45__r))
                                                ? 0x00002000U
                                                : 0x00010000U)));
    if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((((2U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__45__r)) 
                                            << 2U) 
                                           | (((1U 
                                                == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__45__r)) 
                                               << 1U) 
                                              | (0U 
                                                 == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__45__r)))))))))) {
        if ((0U != (((2U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__45__r)) 
                     << 2U) | (((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__45__r)) 
                                << 1U) | (0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__45__r)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:85: Assertion failed in %Ntb_market_sim.base_spread_for: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__45__r));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 85, "");
            }
        }
    }
    vlSelfRef.tb_market_sim__DOT__spread_b = __Vfunc_tb_market_sim__DOT__base_spread_for__45__Vfuncout;
    vlSelfRef.tb_market_sim__DOT__spread_meas = (vlSelfRef.tb_market_sim__DOT__ask_u 
                                                 - vlSelfRef.tb_market_sim__DOT__bid_u);
    __Vtask_tb_market_sim__DOT__check__46__cond = (vlSelfRef.tb_market_sim__DOT__spread_meas 
                                                   == 
                                                   ((0U 
                                                     == vlSelfRef.tb_market_sim__DOT__spread_b)
                                                     ? 1U
                                                     : vlSelfRef.tb_market_sim__DOT__spread_b));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__46__msg 
        = VL_SFORMATF_N_NX("%@: spread==regime base",0,
                           -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__36__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__46__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__46__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__seq_expect[(3U & __Vtask_tb_market_sim__DOT__check_one_quote__36__exp_sym)] 
        = (0x0000ffffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__seq_expect
                          [(3U & __Vtask_tb_market_sim__DOT__check_one_quote__36__exp_sym)]));
    __Vfunc_tb_market_sim__DOT__next_sym__47__sym_wrap 
        = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
    __Vfunc_tb_market_sim__DOT__next_sym__47__cur = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
    __Vfunc_tb_market_sim__DOT__next_sym__47__Vfuncout = 0U;
    __Vfunc_tb_market_sim__DOT__next_sym__47__Vfuncout 
        = ((__Vfunc_tb_market_sim__DOT__next_sym__47__cur 
            == __Vfunc_tb_market_sim__DOT__next_sym__47__sym_wrap)
            ? 0U : ((IData)(1U) + __Vfunc_tb_market_sim__DOT__next_sym__47__cur));
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym 
        = __Vfunc_tb_market_sim__DOT__next_sym__47__Vfuncout;
    __Vtask_tb_market_sim__DOT__check_one_quote__48__sym_wrap 
        = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
    __Vtask_tb_market_sim__DOT__check_one_quote__48__exp_sym 
        = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
    vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__48__tag = "P2 post-block b"s;
    do {
        Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                             "@(posedge tb_market_sim.clk)");
        co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_sim.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                             109);
    } while ((1U & (~ (IData)(vlSelfRef.tb_market_sim__DOT__quote_valid))));
    __Vtask_tb_market_sim__DOT__check__50__cond = (1U 
                                                   == 
                                                   (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                    >> 0x0000001cU));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__50__msg 
        = VL_SFORMATF_N_NX("%@: msg_type QUOTE",0,-1,
                           &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__48__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__50__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__50__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__sym_id_u8 = (0x000000ffU 
                                               & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                  >> 0x00000014U));
    __Vtask_tb_market_sim__DOT__check__51__cond = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
                                                   == 
                                                   (0x000000ffU 
                                                    & __Vtask_tb_market_sim__DOT__check_one_quote__48__exp_sym));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__51__msg 
        = VL_SFORMATF_N_NX("%@: symbol_id==%0d",0,-1,
                           &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__48__tag),
                           32,__Vtask_tb_market_sim__DOT__check_one_quote__48__exp_sym) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__51__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__51__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__52__cond = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
                                                   <= 
                                                   (0x000000ffU 
                                                    & __Vtask_tb_market_sim__DOT__check_one_quote__48__sym_wrap));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__52__msg 
        = VL_SFORMATF_N_NX("%@: symbol in active range",0,
                           -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__48__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__52__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__52__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__regime_in_frame = 
        (3U & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
               >> 0x00000012U));
    vlSelfRef.tb_market_sim__DOT__seq_in_frame = (0x0000ffffU 
                                                  & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[0U]);
    __Vtask_tb_market_sim__DOT__check__53__cond = ((IData)(vlSelfRef.tb_market_sim__DOT__seq_in_frame) 
                                                   == vlSelfRef.tb_market_sim__DOT__seq_expect
                                                   [
                                                   (3U 
                                                    & __Vtask_tb_market_sim__DOT__check_one_quote__48__exp_sym)]);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__53__msg 
        = VL_SFORMATF_N_NX("%@: seq for sym %0d",0,
                           -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__48__tag),
                           32,__Vtask_tb_market_sim__DOT__check_one_quote__48__exp_sym) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__53__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__53__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__bid_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                            << 0x00000010U) 
                                           | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                              >> 0x00000010U));
    vlSelfRef.tb_market_sim__DOT__ask_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                            << 0x00000010U) 
                                           | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[1U] 
                                              >> 0x00000010U));
    __Vtask_tb_market_sim__DOT__check__54__cond = VL_GTES_III(32, vlSelfRef.tb_market_sim__DOT__ask_u, vlSelfRef.tb_market_sim__DOT__bid_u);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__54__msg 
        = VL_SFORMATF_N_NX("%@: ask>=bid",0,-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__48__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__54__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__54__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__55__cond = (
                                                   (0x00010000U 
                                                    <= vlSelfRef.tb_market_sim__DOT__bid_u) 
                                                   & (0x27100000U 
                                                      >= vlSelfRef.tb_market_sim__DOT__bid_u));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__55__msg 
        = VL_SFORMATF_N_NX("%@: bid range",0,-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__48__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__55__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__55__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__56__cond = (
                                                   (0x00010000U 
                                                    <= vlSelfRef.tb_market_sim__DOT__ask_u) 
                                                   & (0x27100000U 
                                                      >= vlSelfRef.tb_market_sim__DOT__ask_u));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__56__msg 
        = VL_SFORMATF_N_NX("%@: ask range",0,-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__48__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__56__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__56__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vfunc_tb_market_sim__DOT__base_spread_for__57__r 
        = vlSelfRef.tb_market_sim__DOT__regime_in_frame;
    __Vfunc_tb_market_sim__DOT__base_spread_for__57__Vfuncout = 0;
    __Vfunc_tb_market_sim__DOT__base_spread_for__57__Vfuncout 
        = ((0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__57__r))
            ? 0x00002000U : ((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__57__r))
                              ? 0x00008000U : ((2U 
                                                == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__57__r))
                                                ? 0x00002000U
                                                : 0x00010000U)));
    if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((((2U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__57__r)) 
                                            << 2U) 
                                           | (((1U 
                                                == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__57__r)) 
                                               << 1U) 
                                              | (0U 
                                                 == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__57__r)))))))))) {
        if ((0U != (((2U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__57__r)) 
                     << 2U) | (((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__57__r)) 
                                << 1U) | (0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__57__r)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:85: Assertion failed in %Ntb_market_sim.base_spread_for: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__57__r));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 85, "");
            }
        }
    }
    vlSelfRef.tb_market_sim__DOT__spread_b = __Vfunc_tb_market_sim__DOT__base_spread_for__57__Vfuncout;
    vlSelfRef.tb_market_sim__DOT__spread_meas = (vlSelfRef.tb_market_sim__DOT__ask_u 
                                                 - vlSelfRef.tb_market_sim__DOT__bid_u);
    __Vtask_tb_market_sim__DOT__check__58__cond = (vlSelfRef.tb_market_sim__DOT__spread_meas 
                                                   == 
                                                   ((0U 
                                                     == vlSelfRef.tb_market_sim__DOT__spread_b)
                                                     ? 1U
                                                     : vlSelfRef.tb_market_sim__DOT__spread_b));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__58__msg 
        = VL_SFORMATF_N_NX("%@: spread==regime base",0,
                           -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__48__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__58__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__58__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__seq_expect[(3U & __Vtask_tb_market_sim__DOT__check_one_quote__48__exp_sym)] 
        = (0x0000ffffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__seq_expect
                          [(3U & __Vtask_tb_market_sim__DOT__check_one_quote__48__exp_sym)]));
    vlSelfRef.tb_market_sim__DOT__enable = 0U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         238);
    vlSelfRef.tb_market_sim__DOT__enable = 0U;
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 0U;
    vlSelfRef.tb_market_sim__DOT__lfsr_seed = 0xace1cafeU;
    vlSelfRef.tb_market_sim__DOT__quote_ready = 1U;
    vlSelfRef.tb_market_sim__DOT__quote_interval = 1U;
    vlSelfRef.tb_market_sim__DOT__active_regime = 0U;
    vlSelfRef.tb_market_sim__DOT__active_sym_count = 4U;
    vlSelfRef.tb_market_sim__DOT__init_mid[0U] = 0x00640000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[0U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[1U] = 0x00740000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[1U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[1U] = 1U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[2U] = 0x00840000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[2U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[2U] = 2U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[3U] = 0x00940000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[3U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[3U] = 3U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[3U] = 0U;
    vlSelfRef.tb_market_sim__DOT__active_sym_count = 2U;
    vlSelfRef.tb_market_sim__DOT__quote_interval = 1U;
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 1U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         116);
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 0U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         118);
    vlSelfRef.tb_market_sim__DOT__enable = 1U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap = 1U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[3U] = 0U;
    tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_2__DOT____Vrepeat1 = 8U;
    while (VL_LTS_III(32, 0U, tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
        __Vtask_tb_market_sim__DOT__check_one_quote__62__sym_wrap 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
        __Vtask_tb_market_sim__DOT__check_one_quote__62__exp_sym 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
        vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__62__tag = "P3 active2"s;
        do {
            Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                                 "@(posedge tb_market_sim.clk)");
            co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_market_sim.clk)", 
                                                                 "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                                 109);
        } while ((1U & (~ (IData)(vlSelfRef.tb_market_sim__DOT__quote_valid))));
        __Vtask_tb_market_sim__DOT__check__64__cond 
            = (1U == (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                      >> 0x0000001cU));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__64__msg 
            = VL_SFORMATF_N_NX("%@: msg_type QUOTE",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__62__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__64__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__64__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__sym_id_u8 = (0x000000ffU 
                                                   & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                      >> 0x00000014U));
        __Vtask_tb_market_sim__DOT__check__65__cond 
            = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
               == (0x000000ffU & __Vtask_tb_market_sim__DOT__check_one_quote__62__exp_sym));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__65__msg 
            = VL_SFORMATF_N_NX("%@: symbol_id==%0d",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__62__tag),
                               32,__Vtask_tb_market_sim__DOT__check_one_quote__62__exp_sym) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__65__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__65__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__66__cond 
            = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
               <= (0x000000ffU & __Vtask_tb_market_sim__DOT__check_one_quote__62__sym_wrap));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__66__msg 
            = VL_SFORMATF_N_NX("%@: symbol in active range",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__62__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__66__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__66__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__regime_in_frame 
            = (3U & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                     >> 0x00000012U));
        vlSelfRef.tb_market_sim__DOT__seq_in_frame 
            = (0x0000ffffU & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[0U]);
        __Vtask_tb_market_sim__DOT__check__67__cond 
            = ((IData)(vlSelfRef.tb_market_sim__DOT__seq_in_frame) 
               == vlSelfRef.tb_market_sim__DOT__seq_expect
               [(3U & __Vtask_tb_market_sim__DOT__check_one_quote__62__exp_sym)]);
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__67__msg 
            = VL_SFORMATF_N_NX("%@: seq for sym %0d",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__62__tag),
                               32,__Vtask_tb_market_sim__DOT__check_one_quote__62__exp_sym) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__67__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__67__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__bid_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                << 0x00000010U) 
                                               | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                                  >> 0x00000010U));
        vlSelfRef.tb_market_sim__DOT__ask_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                                << 0x00000010U) 
                                               | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[1U] 
                                                  >> 0x00000010U));
        __Vtask_tb_market_sim__DOT__check__68__cond 
            = VL_GTES_III(32, vlSelfRef.tb_market_sim__DOT__ask_u, vlSelfRef.tb_market_sim__DOT__bid_u);
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__68__msg 
            = VL_SFORMATF_N_NX("%@: ask>=bid",0,-1,
                               &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__62__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__68__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__68__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__69__cond 
            = ((0x00010000U <= vlSelfRef.tb_market_sim__DOT__bid_u) 
               & (0x27100000U >= vlSelfRef.tb_market_sim__DOT__bid_u));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__69__msg 
            = VL_SFORMATF_N_NX("%@: bid range",0,-1,
                               &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__62__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__69__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__69__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__70__cond 
            = ((0x00010000U <= vlSelfRef.tb_market_sim__DOT__ask_u) 
               & (0x27100000U >= vlSelfRef.tb_market_sim__DOT__ask_u));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__70__msg 
            = VL_SFORMATF_N_NX("%@: ask range",0,-1,
                               &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__62__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__70__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__70__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vfunc_tb_market_sim__DOT__base_spread_for__71__r 
            = vlSelfRef.tb_market_sim__DOT__regime_in_frame;
        __Vfunc_tb_market_sim__DOT__base_spread_for__71__Vfuncout = 0;
        __Vfunc_tb_market_sim__DOT__base_spread_for__71__Vfuncout 
            = ((0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__71__r))
                ? 0x00002000U : ((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__71__r))
                                  ? 0x00008000U : (
                                                   (2U 
                                                    == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__71__r))
                                                    ? 0x00002000U
                                                    : 0x00010000U)));
        if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((((2U 
                                                 == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__71__r)) 
                                                << 2U) 
                                               | (((1U 
                                                    == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__71__r)) 
                                                   << 1U) 
                                                  | (0U 
                                                     == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__71__r)))))))))) {
            if ((0U != (((2U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__71__r)) 
                         << 2U) | (((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__71__r)) 
                                    << 1U) | (0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__71__r)))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:85: Assertion failed in %Ntb_market_sim.base_spread_for: unique case, but multiple matches found for '2'h%x'\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name(),
                                 2,(IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__71__r));
                    VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 85, "");
                }
            }
        }
        vlSelfRef.tb_market_sim__DOT__spread_b = __Vfunc_tb_market_sim__DOT__base_spread_for__71__Vfuncout;
        vlSelfRef.tb_market_sim__DOT__spread_meas = 
            (vlSelfRef.tb_market_sim__DOT__ask_u - vlSelfRef.tb_market_sim__DOT__bid_u);
        __Vtask_tb_market_sim__DOT__check__72__cond 
            = (vlSelfRef.tb_market_sim__DOT__spread_meas 
               == ((0U == vlSelfRef.tb_market_sim__DOT__spread_b)
                    ? 1U : vlSelfRef.tb_market_sim__DOT__spread_b));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__72__msg 
            = VL_SFORMATF_N_NX("%@: spread==regime base",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__62__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__72__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__72__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__seq_expect[(3U 
                                                  & __Vtask_tb_market_sim__DOT__check_one_quote__62__exp_sym)] 
            = (0x0000ffffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__seq_expect
                              [(3U & __Vtask_tb_market_sim__DOT__check_one_quote__62__exp_sym)]));
        __Vfunc_tb_market_sim__DOT__next_sym__73__sym_wrap 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
        __Vfunc_tb_market_sim__DOT__next_sym__73__cur 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
        __Vfunc_tb_market_sim__DOT__next_sym__73__Vfuncout = 0U;
        __Vfunc_tb_market_sim__DOT__next_sym__73__Vfuncout 
            = ((__Vfunc_tb_market_sim__DOT__next_sym__73__cur 
                == __Vfunc_tb_market_sim__DOT__next_sym__73__sym_wrap)
                ? 0U : ((IData)(1U) + __Vfunc_tb_market_sim__DOT__next_sym__73__cur));
        vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym 
            = __Vfunc_tb_market_sim__DOT__next_sym__73__Vfuncout;
        tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_2__DOT____Vrepeat1 
            = (tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_2__DOT____Vrepeat1 
               - (IData)(1U));
    }
    vlSelfRef.tb_market_sim__DOT__enable = 0U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         255);
    vlSelfRef.tb_market_sim__DOT__enable = 0U;
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 0U;
    vlSelfRef.tb_market_sim__DOT__lfsr_seed = 0xace1cafeU;
    vlSelfRef.tb_market_sim__DOT__quote_ready = 1U;
    vlSelfRef.tb_market_sim__DOT__quote_interval = 1U;
    vlSelfRef.tb_market_sim__DOT__active_regime = 0U;
    vlSelfRef.tb_market_sim__DOT__active_sym_count = 4U;
    vlSelfRef.tb_market_sim__DOT__init_mid[0U] = 0x00640000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[0U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[1U] = 0x00740000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[1U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[1U] = 1U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[2U] = 0x00840000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[2U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[2U] = 2U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[3U] = 0x00940000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[3U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[3U] = 3U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[3U] = 0U;
    vlSelfRef.tb_market_sim__DOT__active_sym_count = 4U;
    vlSelfRef.tb_market_sim__DOT__quote_interval = 1U;
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 1U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         116);
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 0U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         118);
    vlSelfRef.tb_market_sim__DOT__enable = 1U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap = 3U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[3U] = 0U;
    tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_3__DOT____Vrepeat2 = 5U;
    while (VL_LTS_III(32, 0U, tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        __Vtask_tb_market_sim__DOT__check_one_quote__77__sym_wrap 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
        __Vtask_tb_market_sim__DOT__check_one_quote__77__exp_sym 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
        vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__77__tag = "P4 pre-reload"s;
        do {
            Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                                 "@(posedge tb_market_sim.clk)");
            co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_market_sim.clk)", 
                                                                 "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                                 109);
        } while ((1U & (~ (IData)(vlSelfRef.tb_market_sim__DOT__quote_valid))));
        __Vtask_tb_market_sim__DOT__check__79__cond 
            = (1U == (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                      >> 0x0000001cU));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__79__msg 
            = VL_SFORMATF_N_NX("%@: msg_type QUOTE",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__77__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__79__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__79__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__sym_id_u8 = (0x000000ffU 
                                                   & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                      >> 0x00000014U));
        __Vtask_tb_market_sim__DOT__check__80__cond 
            = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
               == (0x000000ffU & __Vtask_tb_market_sim__DOT__check_one_quote__77__exp_sym));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__80__msg 
            = VL_SFORMATF_N_NX("%@: symbol_id==%0d",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__77__tag),
                               32,__Vtask_tb_market_sim__DOT__check_one_quote__77__exp_sym) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__80__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__80__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__81__cond 
            = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
               <= (0x000000ffU & __Vtask_tb_market_sim__DOT__check_one_quote__77__sym_wrap));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__81__msg 
            = VL_SFORMATF_N_NX("%@: symbol in active range",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__77__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__81__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__81__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__regime_in_frame 
            = (3U & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                     >> 0x00000012U));
        vlSelfRef.tb_market_sim__DOT__seq_in_frame 
            = (0x0000ffffU & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[0U]);
        __Vtask_tb_market_sim__DOT__check__82__cond 
            = ((IData)(vlSelfRef.tb_market_sim__DOT__seq_in_frame) 
               == vlSelfRef.tb_market_sim__DOT__seq_expect
               [(3U & __Vtask_tb_market_sim__DOT__check_one_quote__77__exp_sym)]);
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__82__msg 
            = VL_SFORMATF_N_NX("%@: seq for sym %0d",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__77__tag),
                               32,__Vtask_tb_market_sim__DOT__check_one_quote__77__exp_sym) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__82__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__82__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__bid_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                << 0x00000010U) 
                                               | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                                  >> 0x00000010U));
        vlSelfRef.tb_market_sim__DOT__ask_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                                << 0x00000010U) 
                                               | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[1U] 
                                                  >> 0x00000010U));
        __Vtask_tb_market_sim__DOT__check__83__cond 
            = VL_GTES_III(32, vlSelfRef.tb_market_sim__DOT__ask_u, vlSelfRef.tb_market_sim__DOT__bid_u);
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__83__msg 
            = VL_SFORMATF_N_NX("%@: ask>=bid",0,-1,
                               &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__77__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__83__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__83__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__84__cond 
            = ((0x00010000U <= vlSelfRef.tb_market_sim__DOT__bid_u) 
               & (0x27100000U >= vlSelfRef.tb_market_sim__DOT__bid_u));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__84__msg 
            = VL_SFORMATF_N_NX("%@: bid range",0,-1,
                               &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__77__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__84__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__84__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__85__cond 
            = ((0x00010000U <= vlSelfRef.tb_market_sim__DOT__ask_u) 
               & (0x27100000U >= vlSelfRef.tb_market_sim__DOT__ask_u));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__85__msg 
            = VL_SFORMATF_N_NX("%@: ask range",0,-1,
                               &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__77__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__85__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__85__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vfunc_tb_market_sim__DOT__base_spread_for__86__r 
            = vlSelfRef.tb_market_sim__DOT__regime_in_frame;
        __Vfunc_tb_market_sim__DOT__base_spread_for__86__Vfuncout = 0;
        __Vfunc_tb_market_sim__DOT__base_spread_for__86__Vfuncout 
            = ((0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__86__r))
                ? 0x00002000U : ((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__86__r))
                                  ? 0x00008000U : (
                                                   (2U 
                                                    == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__86__r))
                                                    ? 0x00002000U
                                                    : 0x00010000U)));
        if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((((2U 
                                                 == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__86__r)) 
                                                << 2U) 
                                               | (((1U 
                                                    == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__86__r)) 
                                                   << 1U) 
                                                  | (0U 
                                                     == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__86__r)))))))))) {
            if ((0U != (((2U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__86__r)) 
                         << 2U) | (((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__86__r)) 
                                    << 1U) | (0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__86__r)))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:85: Assertion failed in %Ntb_market_sim.base_spread_for: unique case, but multiple matches found for '2'h%x'\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name(),
                                 2,(IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__86__r));
                    VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 85, "");
                }
            }
        }
        vlSelfRef.tb_market_sim__DOT__spread_b = __Vfunc_tb_market_sim__DOT__base_spread_for__86__Vfuncout;
        vlSelfRef.tb_market_sim__DOT__spread_meas = 
            (vlSelfRef.tb_market_sim__DOT__ask_u - vlSelfRef.tb_market_sim__DOT__bid_u);
        __Vtask_tb_market_sim__DOT__check__87__cond 
            = (vlSelfRef.tb_market_sim__DOT__spread_meas 
               == ((0U == vlSelfRef.tb_market_sim__DOT__spread_b)
                    ? 1U : vlSelfRef.tb_market_sim__DOT__spread_b));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__87__msg 
            = VL_SFORMATF_N_NX("%@: spread==regime base",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__77__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__87__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__87__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__seq_expect[(3U 
                                                  & __Vtask_tb_market_sim__DOT__check_one_quote__77__exp_sym)] 
            = (0x0000ffffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__seq_expect
                              [(3U & __Vtask_tb_market_sim__DOT__check_one_quote__77__exp_sym)]));
        __Vfunc_tb_market_sim__DOT__next_sym__88__sym_wrap 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
        __Vfunc_tb_market_sim__DOT__next_sym__88__cur 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
        __Vfunc_tb_market_sim__DOT__next_sym__88__Vfuncout = 0U;
        __Vfunc_tb_market_sim__DOT__next_sym__88__Vfuncout 
            = ((__Vfunc_tb_market_sim__DOT__next_sym__88__cur 
                == __Vfunc_tb_market_sim__DOT__next_sym__88__sym_wrap)
                ? 0U : ((IData)(1U) + __Vfunc_tb_market_sim__DOT__next_sym__88__cur));
        vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym 
            = __Vfunc_tb_market_sim__DOT__next_sym__88__Vfuncout;
        tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    __Vtask_tb_market_sim__DOT__check__89__cond = (5U 
                                                   == vlSelfRef.tb_market_sim__DOT__quotes_generated);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__89__msg = "P4: quotes before reload"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__89__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__89__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__enable = 0U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         274);
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 1U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         116);
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 0U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         118);
    __Vtask_tb_market_sim__DOT__check__91__cond = (0U 
                                                   == vlSelfRef.tb_market_sim__DOT__quotes_generated);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__91__msg = "P4: quotes_generated cleared on lfsr_load"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__91__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__91__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__enable = 1U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[3U] = 0U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym = 0U;
    __Vtask_tb_market_sim__DOT__check_one_quote__92__sym_wrap 
        = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
    __Vtask_tb_market_sim__DOT__check_one_quote__92__exp_sym = 0U;
    vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__92__tag = "P4 after reload"s;
    do {
        Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                             "@(posedge tb_market_sim.clk)");
        co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_sim.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                             109);
    } while ((1U & (~ (IData)(vlSelfRef.tb_market_sim__DOT__quote_valid))));
    __Vtask_tb_market_sim__DOT__check__94__cond = (1U 
                                                   == 
                                                   (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                    >> 0x0000001cU));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__94__msg 
        = VL_SFORMATF_N_NX("%@: msg_type QUOTE",0,-1,
                           &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__92__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__94__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__94__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__sym_id_u8 = (0x000000ffU 
                                               & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                  >> 0x00000014U));
    __Vtask_tb_market_sim__DOT__check__95__cond = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
                                                   == 
                                                   (0x000000ffU 
                                                    & __Vtask_tb_market_sim__DOT__check_one_quote__92__exp_sym));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__95__msg 
        = VL_SFORMATF_N_NX("%@: symbol_id==%0d",0,-1,
                           &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__92__tag),
                           32,__Vtask_tb_market_sim__DOT__check_one_quote__92__exp_sym) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__95__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__95__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__96__cond = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
                                                   <= 
                                                   (0x000000ffU 
                                                    & __Vtask_tb_market_sim__DOT__check_one_quote__92__sym_wrap));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__96__msg 
        = VL_SFORMATF_N_NX("%@: symbol in active range",0,
                           -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__92__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__96__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__96__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__regime_in_frame = 
        (3U & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
               >> 0x00000012U));
    vlSelfRef.tb_market_sim__DOT__seq_in_frame = (0x0000ffffU 
                                                  & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[0U]);
    __Vtask_tb_market_sim__DOT__check__97__cond = ((IData)(vlSelfRef.tb_market_sim__DOT__seq_in_frame) 
                                                   == vlSelfRef.tb_market_sim__DOT__seq_expect
                                                   [
                                                   (3U 
                                                    & __Vtask_tb_market_sim__DOT__check_one_quote__92__exp_sym)]);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__97__msg 
        = VL_SFORMATF_N_NX("%@: seq for sym %0d",0,
                           -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__92__tag),
                           32,__Vtask_tb_market_sim__DOT__check_one_quote__92__exp_sym) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__97__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__97__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__bid_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                            << 0x00000010U) 
                                           | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                              >> 0x00000010U));
    vlSelfRef.tb_market_sim__DOT__ask_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                            << 0x00000010U) 
                                           | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[1U] 
                                              >> 0x00000010U));
    __Vtask_tb_market_sim__DOT__check__98__cond = VL_GTES_III(32, vlSelfRef.tb_market_sim__DOT__ask_u, vlSelfRef.tb_market_sim__DOT__bid_u);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__98__msg 
        = VL_SFORMATF_N_NX("%@: ask>=bid",0,-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__92__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__98__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__98__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__99__cond = (
                                                   (0x00010000U 
                                                    <= vlSelfRef.tb_market_sim__DOT__bid_u) 
                                                   & (0x27100000U 
                                                      >= vlSelfRef.tb_market_sim__DOT__bid_u));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__99__msg 
        = VL_SFORMATF_N_NX("%@: bid range",0,-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__92__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__99__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__99__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vtask_tb_market_sim__DOT__check__100__cond = 
        ((0x00010000U <= vlSelfRef.tb_market_sim__DOT__ask_u) 
         & (0x27100000U >= vlSelfRef.tb_market_sim__DOT__ask_u));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__100__msg 
        = VL_SFORMATF_N_NX("%@: ask range",0,-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__92__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__100__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__100__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    __Vfunc_tb_market_sim__DOT__base_spread_for__101__r 
        = vlSelfRef.tb_market_sim__DOT__regime_in_frame;
    __Vfunc_tb_market_sim__DOT__base_spread_for__101__Vfuncout = 0;
    __Vfunc_tb_market_sim__DOT__base_spread_for__101__Vfuncout 
        = ((0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__101__r))
            ? 0x00002000U : ((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__101__r))
                              ? 0x00008000U : ((2U 
                                                == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__101__r))
                                                ? 0x00002000U
                                                : 0x00010000U)));
    if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((((2U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__101__r)) 
                                            << 2U) 
                                           | (((1U 
                                                == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__101__r)) 
                                               << 1U) 
                                              | (0U 
                                                 == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__101__r)))))))))) {
        if ((0U != (((2U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__101__r)) 
                     << 2U) | (((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__101__r)) 
                                << 1U) | (0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__101__r)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:85: Assertion failed in %Ntb_market_sim.base_spread_for: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__101__r));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 85, "");
            }
        }
    }
    vlSelfRef.tb_market_sim__DOT__spread_b = __Vfunc_tb_market_sim__DOT__base_spread_for__101__Vfuncout;
    vlSelfRef.tb_market_sim__DOT__spread_meas = (vlSelfRef.tb_market_sim__DOT__ask_u 
                                                 - vlSelfRef.tb_market_sim__DOT__bid_u);
    __Vtask_tb_market_sim__DOT__check__102__cond = 
        (vlSelfRef.tb_market_sim__DOT__spread_meas 
         == ((0U == vlSelfRef.tb_market_sim__DOT__spread_b)
              ? 1U : vlSelfRef.tb_market_sim__DOT__spread_b));
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__102__msg 
        = VL_SFORMATF_N_NX("%@: spread==regime base",0,
                           -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__92__tag)) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__102__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__102__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__seq_expect[(3U & __Vtask_tb_market_sim__DOT__check_one_quote__92__exp_sym)] 
        = (0x0000ffffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__seq_expect
                          [(3U & __Vtask_tb_market_sim__DOT__check_one_quote__92__exp_sym)]));
    __Vtask_tb_market_sim__DOT__check__103__cond = 
        (0x00010000U <= vlSelfRef.tb_market_sim__DOT__best_bid[0U]);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__103__msg = "P4: best_bid[0] sane after reload"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__103__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__103__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    vlSelfRef.tb_market_sim__DOT__enable = 0U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         289);
    vlSelfRef.tb_market_sim__DOT__enable = 0U;
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 0U;
    vlSelfRef.tb_market_sim__DOT__lfsr_seed = 0xace1cafeU;
    vlSelfRef.tb_market_sim__DOT__quote_ready = 1U;
    vlSelfRef.tb_market_sim__DOT__quote_interval = 1U;
    vlSelfRef.tb_market_sim__DOT__active_regime = 0U;
    vlSelfRef.tb_market_sim__DOT__active_sym_count = 4U;
    vlSelfRef.tb_market_sim__DOT__init_mid[0U] = 0x00640000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[0U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[1U] = 0x00740000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[1U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[1U] = 1U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[2U] = 0x00840000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[2U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[2U] = 2U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__init_mid[3U] = 0x00940000U;
    vlSelfRef.tb_market_sim__DOT__init_spread[3U] = 0x00002000U;
    vlSelfRef.tb_market_sim__DOT__sector_id[3U] = 3U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[3U] = 0U;
    vlSelfRef.tb_market_sim__DOT__quote_interval = 0U;
    vlSelfRef.tb_market_sim__DOT__active_sym_count = 4U;
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 1U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         116);
    vlSelfRef.tb_market_sim__DOT__lfsr_load = 0U;
    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                         "@(posedge tb_market_sim.clk)");
    co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_sim.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                         118);
    vlSelfRef.tb_market_sim__DOT__enable = 1U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap = 3U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__seq_expect[3U] = 0U;
    tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_4__DOT____Vrepeat3 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_4__DOT____Vrepeat3)) {
        __Vtask_tb_market_sim__DOT__check_one_quote__107__sym_wrap 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
        __Vtask_tb_market_sim__DOT__check_one_quote__107__exp_sym 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
        vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__107__tag = "P5 interval0"s;
        do {
            Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(vlSelf, 
                                                                 "@(posedge tb_market_sim.clk)");
            co_await vlSelfRef.__VtrigSched_h066a8c7b__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_market_sim.clk)", 
                                                                 "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                                                 109);
        } while ((1U & (~ (IData)(vlSelfRef.tb_market_sim__DOT__quote_valid))));
        __Vtask_tb_market_sim__DOT__check__109__cond 
            = (1U == (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                      >> 0x0000001cU));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__109__msg 
            = VL_SFORMATF_N_NX("%@: msg_type QUOTE",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__107__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__109__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__109__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__sym_id_u8 = (0x000000ffU 
                                                   & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                      >> 0x00000014U));
        __Vtask_tb_market_sim__DOT__check__110__cond 
            = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
               == (0x000000ffU & __Vtask_tb_market_sim__DOT__check_one_quote__107__exp_sym));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__110__msg 
            = VL_SFORMATF_N_NX("%@: symbol_id==%0d",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__107__tag),
                               32,__Vtask_tb_market_sim__DOT__check_one_quote__107__exp_sym) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__110__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__110__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__111__cond 
            = ((IData)(vlSelfRef.tb_market_sim__DOT__sym_id_u8) 
               <= (0x000000ffU & __Vtask_tb_market_sim__DOT__check_one_quote__107__sym_wrap));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__111__msg 
            = VL_SFORMATF_N_NX("%@: symbol in active range",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__107__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__111__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__111__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__regime_in_frame 
            = (3U & (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                     >> 0x00000012U));
        vlSelfRef.tb_market_sim__DOT__seq_in_frame 
            = (0x0000ffffU & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[0U]);
        __Vtask_tb_market_sim__DOT__check__112__cond 
            = ((IData)(vlSelfRef.tb_market_sim__DOT__seq_in_frame) 
               == vlSelfRef.tb_market_sim__DOT__seq_expect
               [(3U & __Vtask_tb_market_sim__DOT__check_one_quote__107__exp_sym)]);
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__112__msg 
            = VL_SFORMATF_N_NX("%@: seq for sym %0d",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__107__tag),
                               32,__Vtask_tb_market_sim__DOT__check_one_quote__107__exp_sym) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__112__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__112__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__bid_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                                                << 0x00000010U) 
                                               | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                                  >> 0x00000010U));
        vlSelfRef.tb_market_sim__DOT__ask_u = ((vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                                                << 0x00000010U) 
                                               | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[1U] 
                                                  >> 0x00000010U));
        __Vtask_tb_market_sim__DOT__check__113__cond 
            = VL_GTES_III(32, vlSelfRef.tb_market_sim__DOT__ask_u, vlSelfRef.tb_market_sim__DOT__bid_u);
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__113__msg 
            = VL_SFORMATF_N_NX("%@: ask>=bid",0,-1,
                               &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__107__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__113__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__113__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__114__cond 
            = ((0x00010000U <= vlSelfRef.tb_market_sim__DOT__bid_u) 
               & (0x27100000U >= vlSelfRef.tb_market_sim__DOT__bid_u));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__114__msg 
            = VL_SFORMATF_N_NX("%@: bid range",0,-1,
                               &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__107__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__114__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__114__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vtask_tb_market_sim__DOT__check__115__cond 
            = ((0x00010000U <= vlSelfRef.tb_market_sim__DOT__ask_u) 
               & (0x27100000U >= vlSelfRef.tb_market_sim__DOT__ask_u));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__115__msg 
            = VL_SFORMATF_N_NX("%@: ask range",0,-1,
                               &(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__107__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__115__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__115__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        __Vfunc_tb_market_sim__DOT__base_spread_for__116__r 
            = vlSelfRef.tb_market_sim__DOT__regime_in_frame;
        __Vfunc_tb_market_sim__DOT__base_spread_for__116__Vfuncout = 0;
        __Vfunc_tb_market_sim__DOT__base_spread_for__116__Vfuncout 
            = ((0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__116__r))
                ? 0x00002000U : ((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__116__r))
                                  ? 0x00008000U : (
                                                   (2U 
                                                    == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__116__r))
                                                    ? 0x00002000U
                                                    : 0x00010000U)));
        if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((((2U 
                                                 == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__116__r)) 
                                                << 2U) 
                                               | (((1U 
                                                    == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__116__r)) 
                                                   << 1U) 
                                                  | (0U 
                                                     == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__116__r)))))))))) {
            if ((0U != (((2U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__116__r)) 
                         << 2U) | (((1U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__116__r)) 
                                    << 1U) | (0U == (IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__116__r)))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:85: Assertion failed in %Ntb_market_sim.base_spread_for: unique case, but multiple matches found for '2'h%x'\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name(),
                                 2,(IData)(__Vfunc_tb_market_sim__DOT__base_spread_for__116__r));
                    VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 85, "");
                }
            }
        }
        vlSelfRef.tb_market_sim__DOT__spread_b = __Vfunc_tb_market_sim__DOT__base_spread_for__116__Vfuncout;
        vlSelfRef.tb_market_sim__DOT__spread_meas = 
            (vlSelfRef.tb_market_sim__DOT__ask_u - vlSelfRef.tb_market_sim__DOT__bid_u);
        __Vtask_tb_market_sim__DOT__check__117__cond 
            = (vlSelfRef.tb_market_sim__DOT__spread_meas 
               == ((0U == vlSelfRef.tb_market_sim__DOT__spread_b)
                    ? 1U : vlSelfRef.tb_market_sim__DOT__spread_b));
        vlSelfRef.__Vtask_tb_market_sim__DOT__check__117__msg 
            = VL_SFORMATF_N_NX("%@: spread==regime base",0,
                               -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check_one_quote__107__tag)) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__117__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__117__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
            vlSelfRef.tb_market_sim__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__err_count);
        }
        vlSelfRef.tb_market_sim__DOT__seq_expect[(3U 
                                                  & __Vtask_tb_market_sim__DOT__check_one_quote__107__exp_sym)] 
            = (0x0000ffffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__seq_expect
                              [(3U & __Vtask_tb_market_sim__DOT__check_one_quote__107__exp_sym)]));
        __Vfunc_tb_market_sim__DOT__next_sym__118__sym_wrap 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap;
        __Vfunc_tb_market_sim__DOT__next_sym__118__cur 
            = vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym;
        __Vfunc_tb_market_sim__DOT__next_sym__118__Vfuncout = 0U;
        __Vfunc_tb_market_sim__DOT__next_sym__118__Vfuncout 
            = ((__Vfunc_tb_market_sim__DOT__next_sym__118__cur 
                == __Vfunc_tb_market_sim__DOT__next_sym__118__sym_wrap)
                ? 0U : ((IData)(1U) + __Vfunc_tb_market_sim__DOT__next_sym__118__cur));
        vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym 
            = __Vfunc_tb_market_sim__DOT__next_sym__118__Vfuncout;
        tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_4__DOT____Vrepeat3 
            = (tb_market_sim__DOT__unnamedblk2__DOT__unnamedblk1_4__DOT____Vrepeat3 
               - (IData)(1U));
    }
    __Vtask_tb_market_sim__DOT__check__119__cond = 
        (0x0000000aU == vlSelfRef.tb_market_sim__DOT__quotes_generated);
    vlSelfRef.__Vtask_tb_market_sim__DOT__check__119__msg = "P5: quotes_generated==10"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_sim__DOT__check__119__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_sim.sv:71: Assertion failed in %Ntb_market_sim.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_sim__DOT__check__119__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 71, "");
        vlSelfRef.tb_market_sim__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_market_sim__DOT__err_count);
    }
    if ((0U == vlSelfRef.tb_market_sim__DOT__err_count)) {
        VL_WRITEF_NX("tb_market_sim: PASS (all checks passed)\n",0);
    } else {
        VL_WRITEF_NX("tb_market_sim: FAIL (%0d errors)\n",0,
                     32,vlSelfRef.tb_market_sim__DOT__err_count);
    }
    VL_FINISH_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 310, "");
    co_return;
}

VlCoroutine Vtb_market_sim___024root___eval_initial__TOP__Vtiming__2(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 
                                             38);
        vlSelfRef.tb_market_sim__DOT__clk = (1U & (~ (IData)(vlSelfRef.tb_market_sim__DOT__clk)));
    }
    co_return;
}

void Vtb_market_sim___024root___eval_triggers_vec__act(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_triggers_vec__act\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((((IData)(vlSelfRef.tb_market_sim__DOT__rst_n) 
                                                        != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_market_sim__DOT__rst_n__0)) 
                                                       << 3U) 
                                                      | (vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                         << 2U)) 
                                                     | ((((~ (IData)(vlSelfRef.tb_market_sim__DOT__rst_n)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_market_sim__DOT__rst_n__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_market_sim__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_market_sim__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_market_sim__DOT__clk__0 
        = vlSelfRef.tb_market_sim__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_market_sim__DOT__rst_n__0 
        = vlSelfRef.tb_market_sim__DOT__rst_n;
}

bool Vtb_market_sim___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vtb_market_sim___024root___act_comb__TOP__0(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___act_comb__TOP__0\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    QData/*63:0*/ tb_market_sim__DOT__dut__DOT__delta_mul_c;
    tb_market_sim__DOT__dut__DOT__delta_mul_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__delta_scaled_c;
    tb_market_sim__DOT__dut__DOT__delta_scaled_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__mid_s_c;
    tb_market_sim__DOT__dut__DOT__mid_s_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__new_mid_s_c;
    tb_market_sim__DOT__dut__DOT__new_mid_s_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__spr_h_s_c;
    tb_market_sim__DOT__dut__DOT__spr_h_s_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__bid_s2_c;
    tb_market_sim__DOT__dut__DOT__bid_s2_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__ask_s2_c;
    tb_market_sim__DOT__dut__DOT__ask_s2_c = 0;
    // Body
    if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)) 
                               << 2U) | (((1U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)) 
                                          << 1U) | 
                                         (0U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)))))))) {
        if ((0U != (((2U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)) 
                     << 2U) | (((1U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)) 
                                << 1U) | (0U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: market_sim.sv:72: Assertion failed in %Ntb_market_sim.dut: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(vlSelfRef.tb_market_sim__DOT__active_regime));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/rtl/board_a\\market_sim.sv", 72, "");
            }
        }
    }
    if ((0U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16 = 0x00000100U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = 0x00002000U;
    } else if ((1U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16 = 0x00001000U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = 0x00008000U;
    } else if ((2U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16 = 0x00000100U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = 0x00002000U;
    } else {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16 = 0x00004000U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = 0x00010000U;
    }
    vlSelfRef.tb_market_sim__DOT__dut__DOT__tick_raw 
        = ((IData)(vlSelfRef.tb_market_sim__DOT__enable) 
           & ((0U == vlSelfRef.tb_market_sim__DOT__quote_interval) 
              | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_ctr 
                 == (vlSelfRef.tb_market_sim__DOT__quote_interval 
                     - (IData)(1U)))));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__active_count_eff 
        = ((0U == (IData)(vlSelfRef.tb_market_sim__DOT__active_sym_count))
            ? 1U : ((4U < (IData)(vlSelfRef.tb_market_sim__DOT__active_sym_count))
                     ? 4U : (IData)(vlSelfRef.tb_market_sim__DOT__active_sym_count)));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__do_quote 
        = ((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__tick_raw) 
           & (IData)(vlSelfRef.tb_market_sim__DOT__quote_ready));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff 
        = ((4U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__active_count_eff))
            ? 4U : (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__active_count_eff));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable 
        = ((IData)(vlSelfRef.tb_market_sim__DOT__enable) 
           & (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__do_quote));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[3U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[4U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[5U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[6U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[7U] = 0U;
    if ((0U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_market_sim__DOT__sector_id[0U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_market_sim__DOT__sector_id[0U]]));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[0U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_sim__DOT__sector_id[0U]]) 
               + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U]);
    } else {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[0U] = 0U;
    }
    if ((1U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_market_sim__DOT__sector_id[1U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_market_sim__DOT__sector_id[1U]]));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[1U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_sim__DOT__sector_id[1U]]) 
               + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U]);
    } else {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[1U] = 0U;
    }
    if ((2U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_market_sim__DOT__sector_id[2U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_market_sim__DOT__sector_id[2U]]));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[2U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_sim__DOT__sector_id[2U]]) 
               + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U]);
    } else {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[2U] = 0U;
    }
    if ((3U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_market_sim__DOT__sector_id[3U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_market_sim__DOT__sector_id[3U]]));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[3U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_sim__DOT__sector_id[3U]]) 
               + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U]);
    } else {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[3U] = 0U;
    }
    tb_market_sim__DOT__dut__DOT__delta_mul_c = 0ULL;
    tb_market_sim__DOT__dut__DOT__delta_scaled_c = 0U;
    tb_market_sim__DOT__dut__DOT__mid_s_c = 0U;
    tb_market_sim__DOT__dut__DOT__new_mid_s_c = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c = 0U;
    tb_market_sim__DOT__dut__DOT__spr_h_s_c = 0U;
    tb_market_sim__DOT__dut__DOT__bid_s2_c = 0U;
    tb_market_sim__DOT__dut__DOT__ask_s2_c = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U] = 0U;
    if (vlSelfRef.tb_market_sim__DOT__dut__DOT__do_quote) {
        tb_market_sim__DOT__dut__DOT__delta_mul_c = 
            VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out
                                          [vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr]), 
                        VL_EXTENDS_QI(64,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16));
        tb_market_sim__DOT__dut__DOT__delta_scaled_c 
            = (IData)(VL_SHIFTRS_QQI(64,64,32, tb_market_sim__DOT__dut__DOT__delta_mul_c, 0x00000010U));
        tb_market_sim__DOT__dut__DOT__mid_s_c = vlSelfRef.tb_market_sim__DOT__dut__DOT__mid_price
            [vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr];
        tb_market_sim__DOT__dut__DOT__new_mid_s_c = 
            (tb_market_sim__DOT__dut__DOT__mid_s_c 
             + tb_market_sim__DOT__dut__DOT__delta_scaled_c);
        vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c 
            = (VL_GTS_III(32, 0x00010000U, tb_market_sim__DOT__dut__DOT__new_mid_s_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_market_sim__DOT__dut__DOT__new_mid_s_c)
                                  ? 0x27100000U : tb_market_sim__DOT__dut__DOT__new_mid_s_c));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c 
            = vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16;
        if ((0U == vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c)) {
            vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c = 1U;
        }
        tb_market_sim__DOT__dut__DOT__spr_h_s_c = VL_SHIFTRS_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c, 1U);
        tb_market_sim__DOT__dut__DOT__bid_s2_c = (vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c 
                                                  - tb_market_sim__DOT__dut__DOT__spr_h_s_c);
        tb_market_sim__DOT__dut__DOT__ask_s2_c = (vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c 
                                                  + tb_market_sim__DOT__dut__DOT__spr_h_s_c);
        vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_market_sim__DOT__dut__DOT__bid_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_market_sim__DOT__dut__DOT__bid_s2_c)
                                  ? 0x27100000U : tb_market_sim__DOT__dut__DOT__bid_s2_c));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_market_sim__DOT__dut__DOT__ask_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_market_sim__DOT__dut__DOT__ask_s2_c)
                                  ? 0x27100000U : tb_market_sim__DOT__dut__DOT__ask_s2_c));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U] 
            = ((0x0003ffffU & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U]) 
               | (0xfffc0000U & (0x10000000U | (((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr) 
                                                 << 0x00000014U) 
                                                | ((IData)(vlSelfRef.tb_market_sim__DOT__active_regime) 
                                                   << 0x00000012U)))));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[0U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                << 0x00000010U) | vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num
               [vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr]);
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[1U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                >> 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   << 0x00000010U));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[2U] 
            = (((IData)((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c))) 
                << 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   >> 0x00000010U));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U] 
            = ((0xfffc0000U & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U]) 
               | (((IData)((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c))) 
                   >> 0x00000010U) | ((IData)(((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c)) 
                                               >> 0x00000020U)) 
                                      << 0x00000010U)));
    }
}

void Vtb_market_sim___024root___eval_act(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_act\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((9ULL & vlSelfRef.__VactTriggered[0U])) {
        Vtb_market_sim___024root___act_comb__TOP__0(vlSelf);
    }
}

void Vtb_market_sim___024root___nba_sequent__TOP__0(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___nba_sequent__TOP__0\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<IData/*31:0*/, 4> tb_market_sim__DOT__best_ask;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        tb_market_sim__DOT__best_ask[__Vi0] = 0;
    }
    VlUnpacked<IData/*31:0*/, 4> tb_market_sim__DOT__dut__DOT__spread;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        tb_market_sim__DOT__dut__DOT__spread[__Vi0] = 0;
    }
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv;
    __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv;
    __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv;
    __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv;
    __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv;
    __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv;
    __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv;
    __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv;
    __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv;
    __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv = 0;
    IData/*31:0*/ __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv;
    __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__acc;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__acc = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__delta;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__delta = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos = 0;
    QData/*63:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__Vfuncout;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__r;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__r = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta = 0;
    QData/*63:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r = 0;
    CData/*7:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base = 0;
    QData/*63:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r;
    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r = 0;
    CData/*1:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__sym_ptr;
    __Vdly__tb_market_sim__DOT__dut__DOT__sym_ptr = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__quotes_generated;
    __Vdly__tb_market_sim__DOT__quotes_generated = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v0;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v0;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v0;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v1;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v1;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v1;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v2;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v2 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v2;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v2 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v2;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v2 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v3;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v3 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v3;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v3 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v3;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v3 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_bid__v0;
    __VdlyVal__tb_market_sim__DOT__best_bid__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_ask__v0;
    __VdlyVal__tb_market_sim__DOT__best_ask__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_bid__v1;
    __VdlyVal__tb_market_sim__DOT__best_bid__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__best_bid__v1;
    __VdlySet__tb_market_sim__DOT__best_bid__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_ask__v1;
    __VdlyVal__tb_market_sim__DOT__best_ask__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_bid__v2;
    __VdlyVal__tb_market_sim__DOT__best_bid__v2 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__best_bid__v2;
    __VdlySet__tb_market_sim__DOT__best_bid__v2 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_ask__v2;
    __VdlyVal__tb_market_sim__DOT__best_ask__v2 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_bid__v3;
    __VdlyVal__tb_market_sim__DOT__best_bid__v3 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__best_bid__v3;
    __VdlySet__tb_market_sim__DOT__best_bid__v3 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_ask__v3;
    __VdlyVal__tb_market_sim__DOT__best_ask__v3 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v4;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v4 = 0;
    CData/*1:0*/ __VdlyDim0__tb_market_sim__DOT__dut__DOT__mid_price__v4;
    __VdlyDim0__tb_market_sim__DOT__dut__DOT__mid_price__v4 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v4;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v4 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v4;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v4 = 0;
    CData/*1:0*/ __VdlyDim0__tb_market_sim__DOT__dut__DOT__spread__v4;
    __VdlyDim0__tb_market_sim__DOT__dut__DOT__spread__v4 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_bid__v4;
    __VdlyVal__tb_market_sim__DOT__best_bid__v4 = 0;
    CData/*1:0*/ __VdlyDim0__tb_market_sim__DOT__best_bid__v4;
    __VdlyDim0__tb_market_sim__DOT__best_bid__v4 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_ask__v4;
    __VdlyVal__tb_market_sim__DOT__best_ask__v4 = 0;
    CData/*1:0*/ __VdlyDim0__tb_market_sim__DOT__best_ask__v4;
    __VdlyDim0__tb_market_sim__DOT__best_ask__v4 = 0;
    SData/*15:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__seq_num__v4;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__seq_num__v4 = 0;
    CData/*1:0*/ __VdlyDim0__tb_market_sim__DOT__dut__DOT__seq_num__v4;
    __VdlyDim0__tb_market_sim__DOT__dut__DOT__seq_num__v4 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v5;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v5 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v5;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v5 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v5;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v5 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v6;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v6 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v6;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v6 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v6;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v6 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v7;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v7 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v7;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v7 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v7;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v7 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v8;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v8 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v8;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v8 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v8;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v8 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_bid__v5;
    __VdlyVal__tb_market_sim__DOT__best_bid__v5 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_ask__v5;
    __VdlyVal__tb_market_sim__DOT__best_ask__v5 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_bid__v6;
    __VdlyVal__tb_market_sim__DOT__best_bid__v6 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__best_bid__v6;
    __VdlySet__tb_market_sim__DOT__best_bid__v6 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_ask__v6;
    __VdlyVal__tb_market_sim__DOT__best_ask__v6 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_bid__v7;
    __VdlyVal__tb_market_sim__DOT__best_bid__v7 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__best_bid__v7;
    __VdlySet__tb_market_sim__DOT__best_bid__v7 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_ask__v7;
    __VdlyVal__tb_market_sim__DOT__best_ask__v7 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_bid__v8;
    __VdlyVal__tb_market_sim__DOT__best_bid__v8 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__best_bid__v8;
    __VdlySet__tb_market_sim__DOT__best_bid__v8 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__best_ask__v8;
    __VdlyVal__tb_market_sim__DOT__best_ask__v8 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v0;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v4;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v4 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v4;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v4 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v5;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v5 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v5;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v5 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v6;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v6 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v6;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v6 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v7;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v7 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v7;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v7 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15;
    __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15 = 0;
    CData/*0:0*/ __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v16;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v16 = 0;
    // Body
    __Vdly__tb_market_sim__DOT__quotes_generated = vlSelfRef.tb_market_sim__DOT__quotes_generated;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v4 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v5 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v6 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v7 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v0 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v16 = 0U;
    __Vdly__tb_market_sim__DOT__dut__DOT__sym_ptr = vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr;
    __VdlySet__tb_market_sim__DOT__best_bid__v1 = 0U;
    __VdlySet__tb_market_sim__DOT__best_bid__v2 = 0U;
    __VdlySet__tb_market_sim__DOT__best_bid__v3 = 0U;
    __VdlySet__tb_market_sim__DOT__best_bid__v6 = 0U;
    __VdlySet__tb_market_sim__DOT__best_bid__v7 = 0U;
    __VdlySet__tb_market_sim__DOT__best_bid__v8 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v0 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v1 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v2 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v5 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v6 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v7 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v3 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v4 = 0U;
    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v8 = 0U;
    if (vlSelfRef.tb_market_sim__DOT__rst_n) {
        if (vlSelfRef.tb_market_sim__DOT__lfsr_load) {
            __Vdly__tb_market_sim__DOT__quotes_generated = 0U;
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0xc13fa9a9U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0xc13fa9a9U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x5f772362U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0x5f772362U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0xfdae9d1bU ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0xfdae9d1bU ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x9be616d4U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0x9be616d4U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x3a1d908dU ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0x3a1d908dU ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0xd8550a46U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0xd8550a46U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x768c83ffU ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0x768c83ffU ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x14c3fdb8U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0x14c3fdb8U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x9e3779b9U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0x9e3779b9U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x3c6ef372U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0x3c6ef372U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0xdaa66d2bU ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0xdaa66d2bU ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x78dde6e4U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0x78dde6e4U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg 
                = ((0U == (0xa11fe511U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed))
                    ? 1U : (0xa11fe511U ^ vlSelfRef.tb_market_sim__DOT__lfsr_seed));
            vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_ctr = 0U;
        } else {
            if (vlSelfRef.tb_market_sim__DOT__enable) {
                if (vlSelfRef.tb_market_sim__DOT__dut__DOT__do_quote) {
                    __Vdly__tb_market_sim__DOT__quotes_generated 
                        = ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__quotes_generated);
                }
                vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_ctr 
                    = ((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__tick_raw)
                        ? ((IData)(vlSelfRef.tb_market_sim__DOT__quote_ready)
                            ? 0U : vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_ctr)
                        : ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_ctr));
            } else {
                vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_ctr = 0U;
            }
            if (vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) {
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (0U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (1U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (2U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (3U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
        }
    } else {
        __Vdly__tb_market_sim__DOT__quotes_generated = 0U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg = 1U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_ctr = 0U;
    }
    if (vlSelfRef.tb_market_sim__DOT__rst_n) {
        if (vlSelfRef.tb_market_sim__DOT__lfsr_load) {
            __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v0 = 1U;
        } else if (((IData)(vlSelfRef.tb_market_sim__DOT__enable) 
                    & (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__do_quote))) {
            if ((0U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos = 0x02000000U;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg = 0xfe000000U;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__r 
                    = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[0U];
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__delta 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__Vfuncout;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__acc 
                    = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U];
                {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout = 0;
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s = 0;
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos))) {
                        __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout 
                            = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos;
                        goto __Vlabel0;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg))) {
                        __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout 
                            = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg;
                        goto __Vlabel0;
                    }
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout 
                        = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s);
                    __Vlabel0: ;
                }
                __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v4 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout;
                __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v4 = 1U;
            }
            if ((1U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos = 0x02000000U;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg = 0xfe000000U;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__r 
                    = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[1U];
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__delta 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__Vfuncout;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__acc 
                    = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U];
                {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout = 0;
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s = 0;
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos))) {
                        __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout 
                            = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos;
                        goto __Vlabel1;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg))) {
                        __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout 
                            = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg;
                        goto __Vlabel1;
                    }
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout 
                        = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s);
                    __Vlabel1: ;
                }
                __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v5 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout;
                __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v5 = 1U;
            }
            if ((2U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos = 0x02000000U;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg = 0xfe000000U;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__r 
                    = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[2U];
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__delta 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__Vfuncout;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__acc 
                    = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U];
                {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout = 0;
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s = 0;
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos))) {
                        __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout 
                            = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos;
                        goto __Vlabel2;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg))) {
                        __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout 
                            = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg;
                        goto __Vlabel2;
                    }
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout 
                        = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s);
                    __Vlabel2: ;
                }
                __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v6 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout;
                __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v6 = 1U;
            }
            if ((3U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos = 0x02000000U;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg = 0xfe000000U;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__r 
                    = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[3U];
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__delta 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__company_tick_delta__123__Vfuncout;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__acc 
                    = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U];
                {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout = 0;
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s = 0;
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos))) {
                        __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout 
                            = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_pos;
                        goto __Vlabel3;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg))) {
                        __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout 
                            = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__lim_neg;
                        goto __Vlabel3;
                    }
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout 
                        = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__s);
                    __Vlabel3: ;
                }
                __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v7 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__122__Vfuncout;
                __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v7 = 1U;
            }
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[0U];
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[0U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x7fffffffU;
                    goto __Vlabel4;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x80000000U;
                    goto __Vlabel4;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod);
                __Vlabel4: ;
            }
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[0U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0x02000000U;
                    goto __Vlabel5;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0xfe000000U;
                    goto __Vlabel5;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s);
                __Vlabel5: ;
            }
            __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout;
            __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8 = 1U;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[1U];
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[1U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x7fffffffU;
                    goto __Vlabel6;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x80000000U;
                    goto __Vlabel6;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod);
                __Vlabel6: ;
            }
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[1U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0x02000000U;
                    goto __Vlabel7;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0xfe000000U;
                    goto __Vlabel7;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s);
                __Vlabel7: ;
            }
            __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout;
            __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9 = 1U;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[2U];
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[2U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x7fffffffU;
                    goto __Vlabel8;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x80000000U;
                    goto __Vlabel8;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod);
                __Vlabel8: ;
            }
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[2U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0x02000000U;
                    goto __Vlabel9;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0xfe000000U;
                    goto __Vlabel9;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s);
                __Vlabel9: ;
            }
            __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout;
            __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10 = 1U;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[3U];
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[3U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x7fffffffU;
                    goto __Vlabel10;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x80000000U;
                    goto __Vlabel10;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod);
                __Vlabel10: ;
            }
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[3U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0x02000000U;
                    goto __Vlabel11;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0xfe000000U;
                    goto __Vlabel11;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s);
                __Vlabel11: ;
            }
            __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout;
            __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11 = 1U;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[4U];
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[4U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x7fffffffU;
                    goto __Vlabel12;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x80000000U;
                    goto __Vlabel12;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod);
                __Vlabel12: ;
            }
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[4U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0x02000000U;
                    goto __Vlabel13;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0xfe000000U;
                    goto __Vlabel13;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s);
                __Vlabel13: ;
            }
            __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout;
            __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12 = 1U;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[5U];
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[5U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x7fffffffU;
                    goto __Vlabel14;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x80000000U;
                    goto __Vlabel14;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod);
                __Vlabel14: ;
            }
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[5U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0x02000000U;
                    goto __Vlabel15;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0xfe000000U;
                    goto __Vlabel15;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s);
                __Vlabel15: ;
            }
            __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout;
            __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13 = 1U;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[6U];
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[6U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x7fffffffU;
                    goto __Vlabel16;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x80000000U;
                    goto __Vlabel16;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod);
                __Vlabel16: ;
            }
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[6U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0x02000000U;
                    goto __Vlabel17;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0xfe000000U;
                    goto __Vlabel17;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s);
                __Vlabel17: ;
            }
            __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout;
            __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14 = 1U;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[7U];
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[7U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__r;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base 
                    = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_base_delta__126__Vfuncout;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x7fffffffU;
                    goto __Vlabel18;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout = 0x80000000U;
                    goto __Vlabel18;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__prod);
                __Vlabel18: ;
            }
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_scaled_delta__125__Vfuncout;
            __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc 
                = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[7U];
            {
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s = 0;
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0x02000000U;
                    goto __Vlabel19;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s)) {
                    __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout = 0xfe000000U;
                    goto __Vlabel19;
                }
                __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout 
                    = (IData)(__Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__s);
                __Vlabel19: ;
            }
            __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15 
                = __Vfunc_tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__add_sat32__124__Vfuncout;
            __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15 = 1U;
        }
    } else {
        __VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v16 = 1U;
    }
    if (vlSelfRef.tb_market_sim__DOT__rst_n) {
        if (vlSelfRef.tb_market_sim__DOT__lfsr_load) {
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv 
                = vlSelfRef.tb_market_sim__DOT__init_mid[0U];
            __Vdly__tb_market_sim__DOT__dut__DOT__sym_ptr = 0U;
            __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v0 
                = vlSelfRef.tb_market_sim__DOT__init_mid[0U];
            __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v0 = 1U;
            if ((0U == vlSelfRef.tb_market_sim__DOT__init_spread[0U])) {
                __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v0 = 1U;
                __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv = 1U;
            } else {
                __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v0 
                    = vlSelfRef.tb_market_sim__DOT__init_spread[0U];
                __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv 
                    = vlSelfRef.tb_market_sim__DOT__init_spread[0U];
            }
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv 
                = VL_SHIFTRS_III(32,32,32, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv, 1U);
            __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v1 
                = vlSelfRef.tb_market_sim__DOT__init_mid[1U];
            __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v1 = 1U;
            if ((0U == vlSelfRef.tb_market_sim__DOT__init_spread[1U])) {
                __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v1 = 1U;
                __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv = 1U;
            } else {
                __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v1 
                    = vlSelfRef.tb_market_sim__DOT__init_spread[1U];
                __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv 
                    = vlSelfRef.tb_market_sim__DOT__init_spread[1U];
            }
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv 
                = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv 
                   - __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv);
            __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v2 
                = vlSelfRef.tb_market_sim__DOT__init_mid[2U];
            __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v2 = 1U;
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv 
                = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv 
                   + __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv);
            __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v3 
                = vlSelfRef.tb_market_sim__DOT__init_mid[3U];
            __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v3 = 1U;
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv 
                = vlSelfRef.tb_market_sim__DOT__init_mid[1U];
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv 
                = VL_SHIFTRS_III(32,32,32, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv, 1U);
            if ((0U == vlSelfRef.tb_market_sim__DOT__init_spread[2U])) {
                __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v2 = 1U;
                __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv = 1U;
            } else {
                __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v2 
                    = vlSelfRef.tb_market_sim__DOT__init_spread[2U];
                __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv 
                    = vlSelfRef.tb_market_sim__DOT__init_spread[2U];
            }
            __VdlyVal__tb_market_sim__DOT__best_bid__v0 
                = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv)
                    ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv)
                                      ? 0x27100000U
                                      : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv));
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv 
                = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv 
                   - __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv);
            __VdlyVal__tb_market_sim__DOT__best_ask__v0 
                = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv)
                    ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv)
                                      ? 0x27100000U
                                      : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv));
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv 
                = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv 
                   + __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv);
            __VdlySet__tb_market_sim__DOT__best_bid__v1 = 1U;
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv 
                = vlSelfRef.tb_market_sim__DOT__init_mid[2U];
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv 
                = VL_SHIFTRS_III(32,32,32, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv, 1U);
            if ((0U == vlSelfRef.tb_market_sim__DOT__init_spread[3U])) {
                __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v3 = 1U;
                __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv = 1U;
            } else {
                __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v3 
                    = vlSelfRef.tb_market_sim__DOT__init_spread[3U];
                __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv 
                    = vlSelfRef.tb_market_sim__DOT__init_spread[3U];
            }
            __VdlyVal__tb_market_sim__DOT__best_bid__v1 
                = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv)
                    ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv)
                                      ? 0x27100000U
                                      : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv));
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv 
                = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv 
                   - __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv);
            __VdlyVal__tb_market_sim__DOT__best_ask__v1 
                = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv)
                    ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv)
                                      ? 0x27100000U
                                      : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv));
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv 
                = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv 
                   + __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv);
            __VdlySet__tb_market_sim__DOT__best_bid__v2 = 1U;
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv 
                = vlSelfRef.tb_market_sim__DOT__init_mid[3U];
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv 
                = VL_SHIFTRS_III(32,32,32, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_sv, 1U);
            __VdlyVal__tb_market_sim__DOT__best_bid__v2 
                = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv)
                    ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv)
                                      ? 0x27100000U
                                      : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv));
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv 
                = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv 
                   - __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv);
            __VdlyVal__tb_market_sim__DOT__best_bid__v3 
                = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv)
                    ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv)
                                      ? 0x27100000U
                                      : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__bid_sv));
            __VdlyVal__tb_market_sim__DOT__best_ask__v2 
                = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv)
                    ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv)
                                      ? 0x27100000U
                                      : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv));
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv 
                = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__mid_sv 
                   + __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__spr_hv);
            __VdlyVal__tb_market_sim__DOT__best_ask__v3 
                = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv)
                    ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv)
                                      ? 0x27100000U
                                      : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__120__ask_sv));
            __VdlySet__tb_market_sim__DOT__best_bid__v3 = 1U;
            vlSelfRef.tb_market_sim__DOT__quote_valid = 0U;
            vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[0U] = 0U;
            vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[1U] = 0U;
            vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] = 0U;
            vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] = 0U;
        } else {
            vlSelfRef.tb_market_sim__DOT__quote_valid = 0U;
            if (vlSelfRef.tb_market_sim__DOT__enable) {
                if (vlSelfRef.tb_market_sim__DOT__dut__DOT__do_quote) {
                    __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v4 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c;
                    __VdlyDim0__tb_market_sim__DOT__dut__DOT__mid_price__v4 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr;
                    __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v4 = 1U;
                    __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v4 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c;
                    __VdlyDim0__tb_market_sim__DOT__dut__DOT__spread__v4 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr;
                    __VdlyVal__tb_market_sim__DOT__best_bid__v4 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c;
                    __VdlyDim0__tb_market_sim__DOT__best_bid__v4 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr;
                    __VdlyVal__tb_market_sim__DOT__best_ask__v4 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c;
                    __VdlyDim0__tb_market_sim__DOT__best_ask__v4 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr;
                    __VdlyVal__tb_market_sim__DOT__dut__DOT__seq_num__v4 
                        = (0x0000ffffU & ((IData)(1U) 
                                          + vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num
                                          [vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr]));
                    __VdlyDim0__tb_market_sim__DOT__dut__DOT__seq_num__v4 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr;
                    __Vdly__tb_market_sim__DOT__dut__DOT__sym_ptr 
                        = (((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr) 
                            == (3U & ((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__active_count_eff) 
                                      - (IData)(1U))))
                            ? 0U : (3U & ((IData)(1U) 
                                          + (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr))));
                    vlSelfRef.tb_market_sim__DOT__quote_valid = 1U;
                    vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[0U] 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[0U];
                    vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[1U] 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[1U];
                    vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[2U];
                    vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] 
                        = vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U];
                }
            }
        }
    } else {
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv 
            = vlSelfRef.tb_market_sim__DOT__init_mid[0U];
        __Vdly__tb_market_sim__DOT__dut__DOT__sym_ptr = 0U;
        __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v5 
            = vlSelfRef.tb_market_sim__DOT__init_mid[0U];
        __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v5 = 1U;
        if ((0U == vlSelfRef.tb_market_sim__DOT__init_spread[0U])) {
            __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v5 = 1U;
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv = 1U;
        } else {
            __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v5 
                = vlSelfRef.tb_market_sim__DOT__init_spread[0U];
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv 
                = vlSelfRef.tb_market_sim__DOT__init_spread[0U];
        }
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv, 1U);
        __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v6 
            = vlSelfRef.tb_market_sim__DOT__init_mid[1U];
        __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v6 = 1U;
        if ((0U == vlSelfRef.tb_market_sim__DOT__init_spread[1U])) {
            __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v6 = 1U;
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv = 1U;
        } else {
            __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v6 
                = vlSelfRef.tb_market_sim__DOT__init_spread[1U];
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv 
                = vlSelfRef.tb_market_sim__DOT__init_spread[1U];
        }
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv 
            = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv 
               - __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv);
        __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v7 
            = vlSelfRef.tb_market_sim__DOT__init_mid[2U];
        __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v7 = 1U;
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv 
            = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv 
               + __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv);
        __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v8 
            = vlSelfRef.tb_market_sim__DOT__init_mid[3U];
        __VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v8 = 1U;
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv 
            = vlSelfRef.tb_market_sim__DOT__init_mid[1U];
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_market_sim__DOT__init_spread[2U])) {
            __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v7 = 1U;
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv = 1U;
        } else {
            __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v7 
                = vlSelfRef.tb_market_sim__DOT__init_spread[2U];
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv 
                = vlSelfRef.tb_market_sim__DOT__init_spread[2U];
        }
        __VdlyVal__tb_market_sim__DOT__best_bid__v5 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv));
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv 
            = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv 
               - __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv);
        __VdlyVal__tb_market_sim__DOT__best_ask__v5 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv));
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv 
            = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv 
               + __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv);
        __VdlySet__tb_market_sim__DOT__best_bid__v6 = 1U;
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv 
            = vlSelfRef.tb_market_sim__DOT__init_mid[2U];
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_market_sim__DOT__init_spread[3U])) {
            __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v8 = 1U;
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv = 1U;
        } else {
            __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v8 
                = vlSelfRef.tb_market_sim__DOT__init_spread[3U];
            __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv 
                = vlSelfRef.tb_market_sim__DOT__init_spread[3U];
        }
        __VdlyVal__tb_market_sim__DOT__best_bid__v6 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv));
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv 
            = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv 
               - __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv);
        __VdlyVal__tb_market_sim__DOT__best_ask__v6 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv));
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv 
            = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv 
               + __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv);
        __VdlySet__tb_market_sim__DOT__best_bid__v7 = 1U;
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv 
            = vlSelfRef.tb_market_sim__DOT__init_mid[3U];
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_sv, 1U);
        __VdlyVal__tb_market_sim__DOT__best_bid__v7 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv));
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv 
            = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv 
               - __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv);
        __VdlyVal__tb_market_sim__DOT__best_bid__v8 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__bid_sv));
        __VdlyVal__tb_market_sim__DOT__best_ask__v7 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv));
        __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv 
            = (__Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__mid_sv 
               + __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__spr_hv);
        __VdlyVal__tb_market_sim__DOT__best_ask__v8 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_market_sim__DOT__dut__DOT__init_symbol_tables__121__ask_sv));
        __VdlySet__tb_market_sim__DOT__best_bid__v8 = 1U;
        vlSelfRef.tb_market_sim__DOT__quote_valid = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[0U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[1U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[2U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_hold[3U] = 0U;
    }
    vlSelfRef.tb_market_sim__DOT__quotes_generated 
        = __Vdly__tb_market_sim__DOT__quotes_generated;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg;
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v0) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[0U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[1U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[2U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[3U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[4U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[5U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[6U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[7U] = 0U;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v4) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v4;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v5) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v5;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v6) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v6;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v7) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v7;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[0U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[1U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[2U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[3U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[4U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[5U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[6U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[7U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v16) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[0U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[1U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[2U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[3U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[4U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[5U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[6U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[7U] = 0U;
    }
    vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr 
        = __Vdly__tb_market_sim__DOT__dut__DOT__sym_ptr;
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v0) {
        tb_market_sim__DOT__dut__DOT__spread[0U] = __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v0;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num[0U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__mid_price[0U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v0;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v1) {
        tb_market_sim__DOT__dut__DOT__spread[1U] = __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v1;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num[1U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__mid_price[1U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v1;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v2) {
        tb_market_sim__DOT__dut__DOT__spread[2U] = __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v2;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num[2U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__mid_price[2U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v2;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v3) {
        tb_market_sim__DOT__dut__DOT__spread[3U] = __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v3;
        vlSelfRef.tb_market_sim__DOT__best_bid[0U] 
            = __VdlyVal__tb_market_sim__DOT__best_bid__v0;
        tb_market_sim__DOT__best_ask[0U] = __VdlyVal__tb_market_sim__DOT__best_ask__v0;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num[3U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__mid_price[3U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v3;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v4) {
        tb_market_sim__DOT__dut__DOT__spread[__VdlyDim0__tb_market_sim__DOT__dut__DOT__spread__v4] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v4;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v5) {
        tb_market_sim__DOT__dut__DOT__spread[0U] = __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v5;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v6) {
        tb_market_sim__DOT__dut__DOT__spread[1U] = __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v6;
    }
    if (__VdlySet__tb_market_sim__DOT__best_bid__v1) {
        vlSelfRef.tb_market_sim__DOT__best_bid[1U] 
            = __VdlyVal__tb_market_sim__DOT__best_bid__v1;
        tb_market_sim__DOT__best_ask[1U] = __VdlyVal__tb_market_sim__DOT__best_ask__v1;
    }
    if (__VdlySet__tb_market_sim__DOT__best_bid__v2) {
        vlSelfRef.tb_market_sim__DOT__best_bid[2U] 
            = __VdlyVal__tb_market_sim__DOT__best_bid__v2;
        tb_market_sim__DOT__best_ask[2U] = __VdlyVal__tb_market_sim__DOT__best_ask__v2;
    }
    if (__VdlySet__tb_market_sim__DOT__best_bid__v3) {
        vlSelfRef.tb_market_sim__DOT__best_bid[3U] 
            = __VdlyVal__tb_market_sim__DOT__best_bid__v3;
        tb_market_sim__DOT__best_ask[3U] = __VdlyVal__tb_market_sim__DOT__best_ask__v3;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v4) {
        vlSelfRef.tb_market_sim__DOT__best_bid[__VdlyDim0__tb_market_sim__DOT__best_bid__v4] 
            = __VdlyVal__tb_market_sim__DOT__best_bid__v4;
        tb_market_sim__DOT__best_ask[__VdlyDim0__tb_market_sim__DOT__best_ask__v4] 
            = __VdlyVal__tb_market_sim__DOT__best_ask__v4;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num[__VdlyDim0__tb_market_sim__DOT__dut__DOT__seq_num__v4] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__seq_num__v4;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__mid_price[__VdlyDim0__tb_market_sim__DOT__dut__DOT__mid_price__v4] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v4;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v5) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num[0U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__mid_price[0U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v5;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v6) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num[1U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__mid_price[1U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v6;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v7) {
        tb_market_sim__DOT__dut__DOT__spread[2U] = __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v7;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num[2U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__mid_price[2U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v7;
    }
    if (__VdlySet__tb_market_sim__DOT__dut__DOT__mid_price__v8) {
        tb_market_sim__DOT__dut__DOT__spread[3U] = __VdlyVal__tb_market_sim__DOT__dut__DOT__spread__v8;
        vlSelfRef.tb_market_sim__DOT__best_bid[0U] 
            = __VdlyVal__tb_market_sim__DOT__best_bid__v5;
        tb_market_sim__DOT__best_ask[0U] = __VdlyVal__tb_market_sim__DOT__best_ask__v5;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num[3U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__mid_price[3U] 
            = __VdlyVal__tb_market_sim__DOT__dut__DOT__mid_price__v8;
    }
    if (__VdlySet__tb_market_sim__DOT__best_bid__v6) {
        vlSelfRef.tb_market_sim__DOT__best_bid[1U] 
            = __VdlyVal__tb_market_sim__DOT__best_bid__v6;
        tb_market_sim__DOT__best_ask[1U] = __VdlyVal__tb_market_sim__DOT__best_ask__v6;
    }
    if (__VdlySet__tb_market_sim__DOT__best_bid__v7) {
        vlSelfRef.tb_market_sim__DOT__best_bid[2U] 
            = __VdlyVal__tb_market_sim__DOT__best_bid__v7;
        tb_market_sim__DOT__best_ask[2U] = __VdlyVal__tb_market_sim__DOT__best_ask__v7;
    }
    if (__VdlySet__tb_market_sim__DOT__best_bid__v8) {
        vlSelfRef.tb_market_sim__DOT__best_bid[3U] 
            = __VdlyVal__tb_market_sim__DOT__best_bid__v8;
        tb_market_sim__DOT__best_ask[3U] = __VdlyVal__tb_market_sim__DOT__best_ask__v8;
    }
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[0U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[1U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[2U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[3U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[4U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[5U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[6U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[7U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[0U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[1U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[2U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[3U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
}

void Vtb_market_sim___024root___nba_comb__TOP__0(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___nba_comb__TOP__0\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)) 
                               << 2U) | (((1U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)) 
                                          << 1U) | 
                                         (0U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)))))))) {
        if ((0U != (((2U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)) 
                     << 2U) | (((1U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)) 
                                << 1U) | (0U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: market_sim.sv:72: Assertion failed in %Ntb_market_sim.dut: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(vlSelfRef.tb_market_sim__DOT__active_regime));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/rtl/board_a\\market_sim.sv", 72, "");
            }
        }
    }
    if ((0U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16 = 0x00000100U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = 0x00002000U;
    } else if ((1U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16 = 0x00001000U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = 0x00008000U;
    } else if ((2U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16 = 0x00000100U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = 0x00002000U;
    } else {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16 = 0x00004000U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = 0x00010000U;
    }
    vlSelfRef.tb_market_sim__DOT__dut__DOT__active_count_eff 
        = ((0U == (IData)(vlSelfRef.tb_market_sim__DOT__active_sym_count))
            ? 1U : ((4U < (IData)(vlSelfRef.tb_market_sim__DOT__active_sym_count))
                     ? 4U : (IData)(vlSelfRef.tb_market_sim__DOT__active_sym_count)));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff 
        = ((4U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__active_count_eff))
            ? 4U : (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__active_count_eff));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[3U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[4U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[5U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[6U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[7U] = 0U;
    if ((0U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_market_sim__DOT__sector_id[0U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_market_sim__DOT__sector_id[0U]]));
    }
    if ((1U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_market_sim__DOT__sector_id[1U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_market_sim__DOT__sector_id[1U]]));
    }
    if ((2U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_market_sim__DOT__sector_id[2U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_market_sim__DOT__sector_id[2U]]));
    }
    if ((3U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_market_sim__DOT__sector_id[3U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_market_sim__DOT__sector_id[3U]]));
    }
}

void Vtb_market_sim___024root___nba_comb__TOP__1(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___nba_comb__TOP__1\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    QData/*63:0*/ tb_market_sim__DOT__dut__DOT__delta_mul_c;
    tb_market_sim__DOT__dut__DOT__delta_mul_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__delta_scaled_c;
    tb_market_sim__DOT__dut__DOT__delta_scaled_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__mid_s_c;
    tb_market_sim__DOT__dut__DOT__mid_s_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__new_mid_s_c;
    tb_market_sim__DOT__dut__DOT__new_mid_s_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__spr_h_s_c;
    tb_market_sim__DOT__dut__DOT__spr_h_s_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__bid_s2_c;
    tb_market_sim__DOT__dut__DOT__bid_s2_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__ask_s2_c;
    tb_market_sim__DOT__dut__DOT__ask_s2_c = 0;
    // Body
    vlSelfRef.tb_market_sim__DOT__dut__DOT__tick_raw 
        = ((IData)(vlSelfRef.tb_market_sim__DOT__enable) 
           & ((0U == vlSelfRef.tb_market_sim__DOT__quote_interval) 
              | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_ctr 
                 == (vlSelfRef.tb_market_sim__DOT__quote_interval 
                     - (IData)(1U)))));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[0U] 
        = ((0U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))
            ? ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_sim__DOT__sector_id[0U]]) 
               + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U])
            : 0U);
    vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[1U] 
        = ((1U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))
            ? ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_sim__DOT__sector_id[1U]]) 
               + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U])
            : 0U);
    vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[2U] 
        = ((2U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))
            ? ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_sim__DOT__sector_id[2U]]) 
               + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U])
            : 0U);
    vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[3U] 
        = ((3U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))
            ? ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_sim__DOT__sector_id[3U]]) 
               + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U])
            : 0U);
    vlSelfRef.tb_market_sim__DOT__dut__DOT__do_quote 
        = ((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__tick_raw) 
           & (IData)(vlSelfRef.tb_market_sim__DOT__quote_ready));
    if (vlSelfRef.tb_market_sim__DOT__dut__DOT__do_quote) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable 
            = vlSelfRef.tb_market_sim__DOT__enable;
        tb_market_sim__DOT__dut__DOT__delta_mul_c = 0ULL;
        tb_market_sim__DOT__dut__DOT__delta_scaled_c = 0U;
        tb_market_sim__DOT__dut__DOT__mid_s_c = 0U;
        tb_market_sim__DOT__dut__DOT__new_mid_s_c = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c = 0U;
        tb_market_sim__DOT__dut__DOT__spr_h_s_c = 0U;
        tb_market_sim__DOT__dut__DOT__bid_s2_c = 0U;
        tb_market_sim__DOT__dut__DOT__ask_s2_c = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[0U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[1U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[2U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U] = 0U;
        tb_market_sim__DOT__dut__DOT__delta_mul_c = 
            VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out
                                          [vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr]), 
                        VL_EXTENDS_QI(64,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16));
        tb_market_sim__DOT__dut__DOT__delta_scaled_c 
            = (IData)(VL_SHIFTRS_QQI(64,64,32, tb_market_sim__DOT__dut__DOT__delta_mul_c, 0x00000010U));
        tb_market_sim__DOT__dut__DOT__mid_s_c = vlSelfRef.tb_market_sim__DOT__dut__DOT__mid_price
            [vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr];
        tb_market_sim__DOT__dut__DOT__new_mid_s_c = 
            (tb_market_sim__DOT__dut__DOT__mid_s_c 
             + tb_market_sim__DOT__dut__DOT__delta_scaled_c);
        vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c 
            = (VL_GTS_III(32, 0x00010000U, tb_market_sim__DOT__dut__DOT__new_mid_s_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_market_sim__DOT__dut__DOT__new_mid_s_c)
                                  ? 0x27100000U : tb_market_sim__DOT__dut__DOT__new_mid_s_c));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c 
            = vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16;
        if ((0U == vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c)) {
            vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c = 1U;
        }
        tb_market_sim__DOT__dut__DOT__spr_h_s_c = VL_SHIFTRS_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c, 1U);
        tb_market_sim__DOT__dut__DOT__bid_s2_c = (vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c 
                                                  - tb_market_sim__DOT__dut__DOT__spr_h_s_c);
        tb_market_sim__DOT__dut__DOT__ask_s2_c = (vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c 
                                                  + tb_market_sim__DOT__dut__DOT__spr_h_s_c);
        vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_market_sim__DOT__dut__DOT__bid_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_market_sim__DOT__dut__DOT__bid_s2_c)
                                  ? 0x27100000U : tb_market_sim__DOT__dut__DOT__bid_s2_c));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_market_sim__DOT__dut__DOT__ask_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_market_sim__DOT__dut__DOT__ask_s2_c)
                                  ? 0x27100000U : tb_market_sim__DOT__dut__DOT__ask_s2_c));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U] 
            = ((0x0003ffffU & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U]) 
               | (0xfffc0000U & (0x10000000U | (((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr) 
                                                 << 0x00000014U) 
                                                | ((IData)(vlSelfRef.tb_market_sim__DOT__active_regime) 
                                                   << 0x00000012U)))));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[0U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                << 0x00000010U) | vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num
               [vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr]);
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[1U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                >> 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   << 0x00000010U));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[2U] 
            = (((IData)((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c))) 
                << 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   >> 0x00000010U));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U] 
            = ((0xfffc0000U & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U]) 
               | (((IData)((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c))) 
                   >> 0x00000010U) | ((IData)(((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c)) 
                                               >> 0x00000020U)) 
                                      << 0x00000010U)));
    } else {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable = 0U;
        tb_market_sim__DOT__dut__DOT__delta_mul_c = 0ULL;
        tb_market_sim__DOT__dut__DOT__delta_scaled_c = 0U;
        tb_market_sim__DOT__dut__DOT__mid_s_c = 0U;
        tb_market_sim__DOT__dut__DOT__new_mid_s_c = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c = 0U;
        tb_market_sim__DOT__dut__DOT__spr_h_s_c = 0U;
        tb_market_sim__DOT__dut__DOT__bid_s2_c = 0U;
        tb_market_sim__DOT__dut__DOT__ask_s2_c = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[0U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[1U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[2U] = 0U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U] = 0U;
    }
}

void Vtb_market_sim___024root___eval_nba(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_nba\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_market_sim___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((9ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_market_sim___024root___nba_comb__TOP__0(vlSelf);
    }
    if ((0x000000000000000bULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_market_sim___024root___nba_comb__TOP__1(vlSelf);
    }
}

void Vtb_market_sim___024root___timing_ready(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___timing_ready\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((8ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h8d2e6b5d__0.ready("@( tb_market_sim.rst_n)");
    }
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready("@(posedge tb_market_sim.clk)");
    }
}

void Vtb_market_sim___024root___timing_resume(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___timing_resume\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h8d2e6b5d__0.moveToResumeQueue(
                                                          "@( tb_market_sim.rst_n)");
    vlSelfRef.__VtrigSched_h066a8c7b__0.moveToResumeQueue(
                                                          "@(posedge tb_market_sim.clk)");
    vlSelfRef.__VtrigSched_h8d2e6b5d__0.resume("@( tb_market_sim.rst_n)");
    vlSelfRef.__VtrigSched_h066a8c7b__0.resume("@(posedge tb_market_sim.clk)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_market_sim___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_market_sim___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_market_sim___024root___eval_phase__act(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_phase__act\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_market_sim___024root___eval_triggers_vec__act(vlSelf);
    Vtb_market_sim___024root___timing_ready(vlSelf);
    Vtb_market_sim___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_market_sim___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_market_sim___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_market_sim___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_market_sim___024root___timing_resume(vlSelf);
        Vtb_market_sim___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_market_sim___024root___eval_phase__inact(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_phase__inact\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 16, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_market_sim___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_market_sim___024root___eval_phase__nba(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_phase__nba\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_market_sim___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_market_sim___024root___eval_nba(vlSelf);
        Vtb_market_sim___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_market_sim___024root___eval(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_market_sim___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 16, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 16, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_market_sim___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 16, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_market_sim___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_market_sim___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_market_sim___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_market_sim___024root____VbeforeTrig_h8d2e6b5d__0(Vtb_market_sim___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root____VbeforeTrig_h8d2e6b5d__0\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.tb_market_sim__DOT__rst_n) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_market_sim__DOT__rst_n__0)) 
                                  << 3U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_market_sim__DOT__rst_n__0 
        = vlSelfRef.tb_market_sim__DOT__rst_n;
    if ((8ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h8d2e6b5d__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0(Vtb_market_sim___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root____VbeforeTrig_h066a8c7b__0\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_market_sim__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_market_sim__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_market_sim__DOT__clk__0 
        = vlSelfRef.tb_market_sim__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h066a8c7b__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_market_sim___024root___eval_debug_assertions(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_debug_assertions\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
