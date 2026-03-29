// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_market_noise_gen.h for the primary calling header

#include "Vtb_market_noise_gen__pch.h"

VlCoroutine Vtb_market_noise_gen___024root___eval_initial__TOP__Vtiming__0(Vtb_market_noise_gen___024root* vlSelf);
VlCoroutine Vtb_market_noise_gen___024root___eval_initial__TOP__Vtiming__1(Vtb_market_noise_gen___024root* vlSelf);
VlCoroutine Vtb_market_noise_gen___024root___eval_initial__TOP__Vtiming__2(Vtb_market_noise_gen___024root* vlSelf);

void Vtb_market_noise_gen___024root___eval_initial(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_initial\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_noise_gen__DOT__clk = 0U;
    Vtb_market_noise_gen___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_market_noise_gen___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_market_noise_gen___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

VlCoroutine Vtb_market_noise_gen___024root___eval_initial__TOP__Vtiming__0(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_noise_gen__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000186a0ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                         62);
    vlSelfRef.tb_market_noise_gen__DOT__rst_n = 1U;
    co_return;
}

void Vtb_market_noise_gen___024root____VbeforeTrig_h04d2243f__0(Vtb_market_noise_gen___024root* vlSelf, const char* __VeventDescription);
void Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(Vtb_market_noise_gen___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_market_noise_gen___024root___eval_initial__TOP__Vtiming__1(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk1_1__DOT____Vrepeat0;
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk8__DOT__k;
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk8__DOT__k = 0;
    IData/*31:0*/ tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk1_2__DOT____Vrepeat1;
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0;
    IData/*31:0*/ tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk10__DOT__k;
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk10__DOT__k = 0;
    IData/*31:0*/ tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_3__DOT____Vrepeat2;
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_4__DOT____Vrepeat3;
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_4__DOT____Vrepeat3 = 0;
    IData/*31:0*/ tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_5__DOT____Vrepeat4;
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0;
    IData/*31:0*/ tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_6__DOT____Vrepeat5;
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__1__cond;
    __Vtask_tb_market_noise_gen__DOT__check__1__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__2__cond;
    __Vtask_tb_market_noise_gen__DOT__check__2__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__capture_stream__4__n;
    __Vtask_tb_market_noise_gen__DOT__capture_stream__4__n = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0;
    __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0 = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t;
    __Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__5__n_act;
    __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__5__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__7__n_act;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__7__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__7__exp_step;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__7__exp_step = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__8__cond;
    __Vtask_tb_market_noise_gen__DOT__check__8__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__capture_stream__10__n;
    __Vtask_tb_market_noise_gen__DOT__capture_stream__10__n = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0;
    __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0 = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t;
    __Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__11__n_act;
    __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__11__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__13__n_act;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__13__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__13__exp_step;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__13__exp_step = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__14__cond;
    __Vtask_tb_market_noise_gen__DOT__check__14__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__15__cond;
    __Vtask_tb_market_noise_gen__DOT__check__15__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__16__cond;
    __Vtask_tb_market_noise_gen__DOT__check__16__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__17__cond;
    __Vtask_tb_market_noise_gen__DOT__check__17__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__18__cond;
    __Vtask_tb_market_noise_gen__DOT__check__18__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__20__n_act;
    __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__20__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__22__n_act;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__22__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__22__exp_step;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__22__exp_step = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__23__cond;
    __Vtask_tb_market_noise_gen__DOT__check__23__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__25__n_act;
    __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__25__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__27__n_act;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__27__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__27__exp_step;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__27__exp_step = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__28__cond;
    __Vtask_tb_market_noise_gen__DOT__check__28__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__30__n_act;
    __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__30__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__32__n_act;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__32__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__32__exp_step;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__32__exp_step = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__33__cond;
    __Vtask_tb_market_noise_gen__DOT__check__33__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__35__n_act;
    __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__35__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__37__n_act;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__37__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__37__exp_step;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__37__exp_step = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__38__cond;
    __Vtask_tb_market_noise_gen__DOT__check__38__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__39__cond;
    __Vtask_tb_market_noise_gen__DOT__check__39__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__41__n_act;
    __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__41__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__43__n_act;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__43__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__43__exp_step;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__43__exp_step = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__44__cond;
    __Vtask_tb_market_noise_gen__DOT__check__44__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__45__cond;
    __Vtask_tb_market_noise_gen__DOT__check__45__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__46__cond;
    __Vtask_tb_market_noise_gen__DOT__check__46__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__49__n_act;
    __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__49__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__51__n_act;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__51__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__51__exp_step;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__51__exp_step = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__52__cond;
    __Vtask_tb_market_noise_gen__DOT__check__52__cond = 0;
    QData/*63:0*/ __Vfunc_tb_market_noise_gen__DOT__abs32__53__Vfuncout;
    __Vfunc_tb_market_noise_gen__DOT__abs32__53__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__abs32__53__v;
    __Vfunc_tb_market_noise_gen__DOT__abs32__53__v = 0;
    QData/*63:0*/ __Vfunc_tb_market_noise_gen__DOT__abs32__54__Vfuncout;
    __Vfunc_tb_market_noise_gen__DOT__abs32__54__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__abs32__54__v;
    __Vfunc_tb_market_noise_gen__DOT__abs32__54__v = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__55__cond;
    __Vtask_tb_market_noise_gen__DOT__check__55__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__58__n_act;
    __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__58__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__60__n_act;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__60__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__60__exp_step;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__60__exp_step = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__61__cond;
    __Vtask_tb_market_noise_gen__DOT__check__61__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__62__cond;
    __Vtask_tb_market_noise_gen__DOT__check__62__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__63__cond;
    __Vtask_tb_market_noise_gen__DOT__check__63__cond = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__65__n_act;
    __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__65__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__67__n_act;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__67__n_act = 0;
    IData/*31:0*/ __Vtask_tb_market_noise_gen__DOT__check_decomp__67__exp_step;
    __Vtask_tb_market_noise_gen__DOT__check_decomp__67__exp_step = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__68__cond;
    __Vtask_tb_market_noise_gen__DOT__check__68__cond = 0;
    CData/*0:0*/ __Vtask_tb_market_noise_gen__DOT__check__69__cond;
    __Vtask_tb_market_noise_gen__DOT__check__69__cond = 0;
    // Body
    while ((1U & (~ (IData)(vlSelfRef.tb_market_noise_gen__DOT__rst_n)))) {
        Vtb_market_noise_gen___024root____VbeforeTrig_h04d2243f__0(vlSelf, 
                                                                   "@( tb_market_noise_gen.rst_n)");
        co_await vlSelfRef.__VtrigSched_h04d2243f__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_market_noise_gen.rst_n)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             128);
    }
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         129);
    vlSelfRef.tb_market_noise_gen__DOT__base_seed = 0xa5a55a5aU;
    vlSelfRef.tb_market_noise_gen__DOT__enable = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__tick = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__active_sym_count = 4U;
    vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U] = 1U;
    __Vtask_tb_market_noise_gen__DOT__check__1__cond 
        = (0U == vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[0U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__1__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: post-rst sector_noise[0] zero\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__1__cond 
        = (0U == vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[1U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__1__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: post-rst sector_noise[1] zero\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__1__cond 
        = (0U == vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[2U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__1__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: post-rst sector_noise[2] zero\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__1__cond 
        = (0U == vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[3U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__1__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: post-rst sector_noise[3] zero\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__1__cond 
        = (0U == vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[4U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__1__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: post-rst sector_noise[4] zero\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__1__cond 
        = (0U == vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[5U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__1__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: post-rst sector_noise[5] zero\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__1__cond 
        = (0U == vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[6U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__1__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: post-rst sector_noise[6] zero\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__1__cond 
        = (0U == vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[7U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__1__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: post-rst sector_noise[7] zero\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__2__cond 
        = (0U == vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__2__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: post-rst company[0] zero\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__2__cond 
        = (0U == vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__2__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: post-rst company[1] zero\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__2__cond 
        = (0U == vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__2__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: post-rst company[2] zero\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__2__cond 
        = (0U == vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__2__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: post-rst company[3] zero\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    vlSelfRef.tb_market_noise_gen__DOT__enable = 1U;
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         98);
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 0U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         100);
    __Vtask_tb_market_noise_gen__DOT__capture_stream__4__n = 0x00000018U;
    __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0 = 0;
    __Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t = 0U;
    __Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t = 0U;
    while (VL_LTS_III(32, __Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t, __Vtask_tb_market_noise_gen__DOT__capture_stream__4__n)) {
        __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__5__n_act = 4U;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__5__tag 
            = VL_SFORMATF_N_NX("cap t%0d",0,32,__Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t) ;
        vlSelfRef.tb_market_noise_gen__DOT__tick = 1U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             86);
        vlSelfRef.tb_market_noise_gen__DOT__tick = 0U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             88);
        __Vtask_tb_market_noise_gen__DOT__check_decomp__7__n_act 
            = __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__5__n_act;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__7__tag 
            = vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__5__tag;
        __Vtask_tb_market_noise_gen__DOT__check_decomp__7__exp_step = 0;
        if (VL_LTS_III(32, 0U, __Vtask_tb_market_noise_gen__DOT__check_decomp__7__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__7__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]);
            __Vtask_tb_market_noise_gen__DOT__check__8__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__7__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__8__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym0",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__7__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__8__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__8__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 1U, __Vtask_tb_market_noise_gen__DOT__check_decomp__7__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__7__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]);
            __Vtask_tb_market_noise_gen__DOT__check__8__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__7__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__8__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym1",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__7__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__8__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__8__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 2U, __Vtask_tb_market_noise_gen__DOT__check_decomp__7__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__7__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]);
            __Vtask_tb_market_noise_gen__DOT__check__8__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__7__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__8__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym2",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__7__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__8__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__8__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 3U, __Vtask_tb_market_noise_gen__DOT__check_decomp__7__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__7__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]);
            __Vtask_tb_market_noise_gen__DOT__check__8__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__7__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__8__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym3",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__7__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__8__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__8__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0 
            = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U];
        if (VL_LIKELY(((0x17U >= (0x0000001fU & __Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t))))) {
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][(0x0000001fU 
                                                                             & __Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t)] 
                = __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0;
            __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U];
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][(0x0000001fU 
                                                                             & __Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t)] 
                = __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0;
            __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U];
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][(0x0000001fU 
                                                                             & __Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t)] 
                = __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0;
            __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U];
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][(0x0000001fU 
                                                                             & __Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t)] 
                = __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0;
        } else {
            __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U];
            __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U];
            __Vtask_tb_market_noise_gen__DOT__capture_stream__4____Vlvbound_hdafee137__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U];
        }
        __Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t 
            = ((IData)(1U) + __Vtask_tb_market_noise_gen__DOT__capture_stream__4__unnamedblk2__DOT__t);
    }
    vlSelfRef.tb_market_noise_gen__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000009c40ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                         155);
    vlSelfRef.tb_market_noise_gen__DOT__rst_n = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         157);
    vlSelfRef.tb_market_noise_gen__DOT__enable = 1U;
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         98);
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 0U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         100);
    __Vtask_tb_market_noise_gen__DOT__capture_stream__10__n = 0x00000018U;
    __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0 = 0;
    __Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t = 0U;
    __Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t = 0U;
    while (VL_LTS_III(32, __Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t, __Vtask_tb_market_noise_gen__DOT__capture_stream__10__n)) {
        __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__11__n_act = 4U;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__11__tag 
            = VL_SFORMATF_N_NX("cap t%0d",0,32,__Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t) ;
        vlSelfRef.tb_market_noise_gen__DOT__tick = 1U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             86);
        vlSelfRef.tb_market_noise_gen__DOT__tick = 0U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             88);
        __Vtask_tb_market_noise_gen__DOT__check_decomp__13__n_act 
            = __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__11__n_act;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__13__tag 
            = vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__11__tag;
        __Vtask_tb_market_noise_gen__DOT__check_decomp__13__exp_step = 0;
        if (VL_LTS_III(32, 0U, __Vtask_tb_market_noise_gen__DOT__check_decomp__13__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__13__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]);
            __Vtask_tb_market_noise_gen__DOT__check__14__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__13__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__14__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym0",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__13__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__14__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__14__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 1U, __Vtask_tb_market_noise_gen__DOT__check_decomp__13__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__13__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]);
            __Vtask_tb_market_noise_gen__DOT__check__14__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__13__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__14__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym1",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__13__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__14__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__14__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 2U, __Vtask_tb_market_noise_gen__DOT__check_decomp__13__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__13__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]);
            __Vtask_tb_market_noise_gen__DOT__check__14__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__13__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__14__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym2",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__13__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__14__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__14__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 3U, __Vtask_tb_market_noise_gen__DOT__check_decomp__13__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__13__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]);
            __Vtask_tb_market_noise_gen__DOT__check__14__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__13__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__14__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym3",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__13__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__14__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__14__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0 
            = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U];
        if (VL_LIKELY(((0x17U >= (0x0000001fU & __Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t))))) {
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][(0x0000001fU 
                                                                             & __Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t)] 
                = __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0;
            __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U];
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][(0x0000001fU 
                                                                             & __Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t)] 
                = __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0;
            __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U];
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][(0x0000001fU 
                                                                             & __Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t)] 
                = __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0;
            __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U];
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][(0x0000001fU 
                                                                             & __Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t)] 
                = __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0;
        } else {
            __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U];
            __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U];
            __Vtask_tb_market_noise_gen__DOT__capture_stream__10____Vlvbound_hdafee137__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U];
        }
        __Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t 
            = ((IData)(1U) + __Vtask_tb_market_noise_gen__DOT__capture_stream__10__unnamedblk2__DOT__t);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][0U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][0U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][0]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][0U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][0U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][0]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][0U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][0U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][0]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][0U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][0U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][0]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][1U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][1U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][1]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][1U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][1U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][1]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][1U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][1U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][1]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][1U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][1U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][1]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][2U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][2U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][2]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][2U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][2U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][2]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][2U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][2U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][2]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][2U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][2U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][2]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][3U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][3U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][3]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][3U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][3U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][3]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][3U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][3U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][3]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][3U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][3U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][3]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][4U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][4U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][4]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][4U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][4U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][4]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][4U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][4U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][4]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][4U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][4U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][4]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][5U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][5U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][5]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][5U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][5U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][5]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][5U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][5U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][5]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][5U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][5U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][5]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][6U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][6U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][6]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][6U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][6U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][6]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][6U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][6U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][6]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][6U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][6U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][6]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][7U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][7U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][7]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][7U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][7U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][7]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][7U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][7U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][7]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][7U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][7U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][7]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][8U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][8U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][8]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][8U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][8U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][8]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][8U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][8U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][8]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][8U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][8U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][8]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][9U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][9U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][9]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][9U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][9U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][9]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][9U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][9U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][9]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][9U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][9U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][9]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][10U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][10U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][10]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][10U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][10U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][10]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][10U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][10U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][10]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][10U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][10U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][10]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][11U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][11U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][11]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][11U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][11U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][11]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][11U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][11U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][11]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][11U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][11U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][11]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][12U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][12U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][12]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][12U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][12U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][12]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][12U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][12U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][12]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][12U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][12U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][12]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][13U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][13U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][13]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][13U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][13U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][13]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][13U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][13U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][13]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][13U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][13U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][13]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][14U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][14U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][14]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][14U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][14U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][14]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][14U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][14U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][14]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][14U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][14U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][14]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][15U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][15U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][15]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][15U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][15U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][15]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][15U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][15U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][15]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][15U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][15U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][15]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][16U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][16U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][16]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][16U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][16U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][16]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][16U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][16U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][16]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][16U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][16U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][16]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][17U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][17U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][17]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][17U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][17U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][17]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][17U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][17U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][17]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][17U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][17U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][17]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][18U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][18U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][18]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][18U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][18U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][18]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][18U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][18U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][18]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][18U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][18U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][18]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][19U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][19U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][19]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][19U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][19U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][19]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][19U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][19U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][19]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][19U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][19U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][19]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][20U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][20U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][20]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][20U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][20U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][20]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][20U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][20U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][20]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][20U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][20U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][20]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][21U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][21U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][21]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][21U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][21U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][21]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][21U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][21U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][21]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][21U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][21U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][21]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][22U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][22U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][22]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][22U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][22U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][22]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][22U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][22U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][22]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][22U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][22U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][22]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__15__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[0U][23U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[0U][23U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[0][23]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__16__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[1U][23U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[1U][23U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__16__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[1][23]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__17__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[2U][23U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[2U][23U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[2][23]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__18__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[3U][23U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[3U][23U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: det step_out[3][23]\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    vlSelfRef.tb_market_noise_gen__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000009c40ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                         174);
    vlSelfRef.tb_market_noise_gen__DOT__rst_n = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         176);
    vlSelfRef.tb_market_noise_gen__DOT__enable = 1U;
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         98);
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 0U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         100);
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__20__n_act = 4U;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__20__tag = "warm"s;
        vlSelfRef.tb_market_noise_gen__DOT__tick = 1U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             86);
        vlSelfRef.tb_market_noise_gen__DOT__tick = 0U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             88);
        __Vtask_tb_market_noise_gen__DOT__check_decomp__22__n_act 
            = __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__20__n_act;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__22__tag 
            = vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__20__tag;
        __Vtask_tb_market_noise_gen__DOT__check_decomp__22__exp_step = 0;
        if (VL_LTS_III(32, 0U, __Vtask_tb_market_noise_gen__DOT__check_decomp__22__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__22__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]);
            __Vtask_tb_market_noise_gen__DOT__check__23__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__22__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__23__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym0",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__22__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__23__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__23__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 1U, __Vtask_tb_market_noise_gen__DOT__check_decomp__22__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__22__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]);
            __Vtask_tb_market_noise_gen__DOT__check__23__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__22__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__23__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym1",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__22__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__23__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__23__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 2U, __Vtask_tb_market_noise_gen__DOT__check_decomp__22__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__22__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]);
            __Vtask_tb_market_noise_gen__DOT__check__23__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__22__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__23__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym2",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__22__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__23__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__23__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 3U, __Vtask_tb_market_noise_gen__DOT__check_decomp__22__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__22__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]);
            __Vtask_tb_market_noise_gen__DOT__check__23__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__22__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__23__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym3",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__22__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__23__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__23__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         98);
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 0U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         100);
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk8__DOT__k = 0U;
    while (VL_GTS_III(32, 3U, tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk8__DOT__k)) {
        __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__25__n_act = 4U;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__25__tag 
            = VL_SFORMATF_N_NX("tail_x k%0d",0,32,tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk8__DOT__k) ;
        vlSelfRef.tb_market_noise_gen__DOT__tick = 1U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             86);
        vlSelfRef.tb_market_noise_gen__DOT__tick = 0U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             88);
        __Vtask_tb_market_noise_gen__DOT__check_decomp__27__n_act 
            = __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__25__n_act;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__27__tag 
            = vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__25__tag;
        __Vtask_tb_market_noise_gen__DOT__check_decomp__27__exp_step = 0;
        if (VL_LTS_III(32, 0U, __Vtask_tb_market_noise_gen__DOT__check_decomp__27__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__27__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]);
            __Vtask_tb_market_noise_gen__DOT__check__28__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__27__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__28__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym0",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__27__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__28__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__28__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 1U, __Vtask_tb_market_noise_gen__DOT__check_decomp__27__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__27__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]);
            __Vtask_tb_market_noise_gen__DOT__check__28__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__27__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__28__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym1",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__27__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__28__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__28__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 2U, __Vtask_tb_market_noise_gen__DOT__check_decomp__27__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__27__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]);
            __Vtask_tb_market_noise_gen__DOT__check__28__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__27__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__28__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym2",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__27__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__28__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__28__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 3U, __Vtask_tb_market_noise_gen__DOT__check_decomp__27__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__27__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]);
            __Vtask_tb_market_noise_gen__DOT__check__28__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__27__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__28__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym3",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__27__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__28__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__28__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_h546553af__0 
            = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U];
        if (VL_LIKELY(((2U >= (3U & tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk8__DOT__k))))) {
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[0U][(3U 
                                                                                & tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk8__DOT__k)] 
                = vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_h546553af__0;
            vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_h546553af__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U];
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[1U][(3U 
                                                                                & tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk8__DOT__k)] 
                = vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_h546553af__0;
            vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_h546553af__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U];
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[2U][(3U 
                                                                                & tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk8__DOT__k)] 
                = vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_h546553af__0;
            vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_h546553af__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U];
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[3U][(3U 
                                                                                & tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk8__DOT__k)] 
                = vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_h546553af__0;
        } else {
            vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_h546553af__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U];
            vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_h546553af__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U];
            vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_h546553af__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U];
        }
        tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk8__DOT__k 
            = ((IData)(1U) + tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk8__DOT__k);
    }
    vlSelfRef.tb_market_noise_gen__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000009c40ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                         187);
    vlSelfRef.tb_market_noise_gen__DOT__rst_n = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         189);
    vlSelfRef.tb_market_noise_gen__DOT__enable = 1U;
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         98);
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 0U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         100);
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0x0000000aU;
    while (VL_LTS_III(32, 0U, tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
        __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__30__n_act = 4U;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__30__tag = "warm2"s;
        vlSelfRef.tb_market_noise_gen__DOT__tick = 1U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             86);
        vlSelfRef.tb_market_noise_gen__DOT__tick = 0U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             88);
        __Vtask_tb_market_noise_gen__DOT__check_decomp__32__n_act 
            = __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__30__n_act;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__32__tag 
            = vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__30__tag;
        __Vtask_tb_market_noise_gen__DOT__check_decomp__32__exp_step = 0;
        if (VL_LTS_III(32, 0U, __Vtask_tb_market_noise_gen__DOT__check_decomp__32__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__32__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]);
            __Vtask_tb_market_noise_gen__DOT__check__33__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__32__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__33__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym0",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__32__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__33__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__33__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 1U, __Vtask_tb_market_noise_gen__DOT__check_decomp__32__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__32__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]);
            __Vtask_tb_market_noise_gen__DOT__check__33__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__32__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__33__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym1",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__32__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__33__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__33__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 2U, __Vtask_tb_market_noise_gen__DOT__check_decomp__32__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__32__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]);
            __Vtask_tb_market_noise_gen__DOT__check__33__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__32__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__33__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym2",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__32__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__33__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__33__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 3U, __Vtask_tb_market_noise_gen__DOT__check_decomp__32__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__32__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]);
            __Vtask_tb_market_noise_gen__DOT__check__33__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__32__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__33__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym3",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__32__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__33__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__33__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk1_2__DOT____Vrepeat1 
            = (tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk1_2__DOT____Vrepeat1 
               - (IData)(1U));
    }
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         98);
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 0U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         100);
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk10__DOT__k = 0U;
    while (VL_GTS_III(32, 3U, tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk10__DOT__k)) {
        __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__35__n_act = 4U;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__35__tag 
            = VL_SFORMATF_N_NX("tail_y k%0d",0,32,tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk10__DOT__k) ;
        vlSelfRef.tb_market_noise_gen__DOT__tick = 1U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             86);
        vlSelfRef.tb_market_noise_gen__DOT__tick = 0U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             88);
        __Vtask_tb_market_noise_gen__DOT__check_decomp__37__n_act 
            = __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__35__n_act;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__37__tag 
            = vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__35__tag;
        __Vtask_tb_market_noise_gen__DOT__check_decomp__37__exp_step = 0;
        if (VL_LTS_III(32, 0U, __Vtask_tb_market_noise_gen__DOT__check_decomp__37__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__37__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]);
            __Vtask_tb_market_noise_gen__DOT__check__38__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__37__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__38__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym0",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__37__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__38__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__38__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 1U, __Vtask_tb_market_noise_gen__DOT__check_decomp__37__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__37__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]);
            __Vtask_tb_market_noise_gen__DOT__check__38__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__37__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__38__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym1",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__37__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__38__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__38__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 2U, __Vtask_tb_market_noise_gen__DOT__check_decomp__37__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__37__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]);
            __Vtask_tb_market_noise_gen__DOT__check__38__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__37__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__38__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym2",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__37__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__38__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__38__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 3U, __Vtask_tb_market_noise_gen__DOT__check_decomp__37__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__37__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]);
            __Vtask_tb_market_noise_gen__DOT__check__38__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__37__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__38__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym3",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__37__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__38__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__38__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0 
            = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U];
        if (VL_LIKELY(((2U >= (3U & tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk10__DOT__k))))) {
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[0U][(3U 
                                                                                & tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk10__DOT__k)] 
                = vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0;
            vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U];
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[1U][(3U 
                                                                                & tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk10__DOT__k)] 
                = vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0;
            vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U];
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[2U][(3U 
                                                                                & tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk10__DOT__k)] 
                = vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0;
            vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U];
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[3U][(3U 
                                                                                & tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk10__DOT__k)] 
                = vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0;
        } else {
            vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U];
            vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U];
            vlSelfRef.tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0 
                = vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U];
        }
        tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk10__DOT__k 
            = ((IData)(1U) + tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__unnamedblk10__DOT__k);
    }
    __Vtask_tb_market_noise_gen__DOT__check__39__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[0U][0U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[0U][0U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: lfsr_load tail sym0 t0\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__39__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[1U][0U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[1U][0U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: lfsr_load tail sym1 t0\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__39__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[2U][0U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[2U][0U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: lfsr_load tail sym2 t0\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__39__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[3U][0U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[3U][0U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: lfsr_load tail sym3 t0\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__39__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[0U][1U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[0U][1U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: lfsr_load tail sym0 t1\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__39__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[1U][1U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[1U][1U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: lfsr_load tail sym1 t1\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__39__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[2U][1U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[2U][1U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: lfsr_load tail sym2 t1\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__39__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[3U][1U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[3U][1U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: lfsr_load tail sym3 t1\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__39__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[0U][2U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[0U][2U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: lfsr_load tail sym0 t2\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__39__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[1U][2U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[1U][2U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: lfsr_load tail sym1 t2\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__39__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[2U][2U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[2U][2U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: lfsr_load tail sym2 t2\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__39__cond 
        = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[3U][2U] 
           == vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[3U][2U]);
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: lfsr_load tail sym3 t2\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         98);
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 0U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         100);
    vlSelfRef.tb_market_noise_gen__DOT__active_sym_count = 2U;
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_3__DOT____Vrepeat2 = 8U;
    while (VL_LTS_III(32, 0U, tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__41__n_act = 2U;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__41__tag = "active2"s;
        vlSelfRef.tb_market_noise_gen__DOT__tick = 1U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             86);
        vlSelfRef.tb_market_noise_gen__DOT__tick = 0U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             88);
        __Vtask_tb_market_noise_gen__DOT__check_decomp__43__n_act 
            = __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__41__n_act;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__43__tag 
            = vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__41__tag;
        __Vtask_tb_market_noise_gen__DOT__check_decomp__43__exp_step = 0;
        if (VL_LTS_III(32, 0U, __Vtask_tb_market_noise_gen__DOT__check_decomp__43__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__43__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]);
            __Vtask_tb_market_noise_gen__DOT__check__44__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__43__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__44__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym0",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__43__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__44__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__44__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 1U, __Vtask_tb_market_noise_gen__DOT__check_decomp__43__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__43__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]);
            __Vtask_tb_market_noise_gen__DOT__check__44__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__43__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__44__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym1",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__43__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__44__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__44__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 2U, __Vtask_tb_market_noise_gen__DOT__check_decomp__43__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__43__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]);
            __Vtask_tb_market_noise_gen__DOT__check__44__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__43__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__44__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym2",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__43__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__44__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__44__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 3U, __Vtask_tb_market_noise_gen__DOT__check_decomp__43__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__43__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]);
            __Vtask_tb_market_noise_gen__DOT__check__44__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__43__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__44__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym3",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__43__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__44__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__44__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        __Vtask_tb_market_noise_gen__DOT__check__45__cond 
            = (0U == vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U]);
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__45__msg = "active2 sym2 zero"s;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__45__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__45__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
            vlSelfRef.tb_market_noise_gen__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
        }
        __Vtask_tb_market_noise_gen__DOT__check__46__cond 
            = (0U == vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U]);
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__46__msg = "active2 sym3 zero"s;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__46__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__46__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
            vlSelfRef.tb_market_noise_gen__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
        }
        tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    vlSelfRef.tb_market_noise_gen__DOT__active_sym_count = 4U;
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         98);
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 0U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         100);
    vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U] = 1U;
    vlSelfRef.tb_market_noise_gen__DOT__active_sym_count = 4U;
    vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec0 = 0ULL;
    vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec1 = 0ULL;
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_4__DOT____Vrepeat3 = 0x000000a0U;
    while (VL_LTS_III(32, 0U, tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_4__DOT____Vrepeat3)) {
        __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__49__n_act = 4U;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__49__tag = "popscale"s;
        vlSelfRef.tb_market_noise_gen__DOT__tick = 1U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             86);
        vlSelfRef.tb_market_noise_gen__DOT__tick = 0U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             88);
        __Vtask_tb_market_noise_gen__DOT__check_decomp__51__n_act 
            = __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__49__n_act;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__51__tag 
            = vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__49__tag;
        __Vtask_tb_market_noise_gen__DOT__check_decomp__51__exp_step = 0;
        if (VL_LTS_III(32, 0U, __Vtask_tb_market_noise_gen__DOT__check_decomp__51__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__51__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]);
            __Vtask_tb_market_noise_gen__DOT__check__52__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__51__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__52__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym0",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__51__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__52__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__52__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 1U, __Vtask_tb_market_noise_gen__DOT__check_decomp__51__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__51__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]);
            __Vtask_tb_market_noise_gen__DOT__check__52__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__51__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__52__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym1",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__51__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__52__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__52__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 2U, __Vtask_tb_market_noise_gen__DOT__check_decomp__51__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__51__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]);
            __Vtask_tb_market_noise_gen__DOT__check__52__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__51__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__52__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym2",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__51__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__52__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__52__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 3U, __Vtask_tb_market_noise_gen__DOT__check_decomp__51__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__51__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]);
            __Vtask_tb_market_noise_gen__DOT__check__52__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__51__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__52__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym3",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__51__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__52__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__52__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec0 
            = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec0 
               + ([&]() {
                    __Vfunc_tb_market_noise_gen__DOT__abs32__53__v 
                        = vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[0U];
                    {
                        __Vfunc_tb_market_noise_gen__DOT__abs32__53__Vfuncout = 0ULL;
                        if (VL_GTS_III(32, 0U, __Vfunc_tb_market_noise_gen__DOT__abs32__53__v)) {
                            __Vfunc_tb_market_noise_gen__DOT__abs32__53__Vfuncout 
                                = (- VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__abs32__53__v));
                            goto __Vlabel0;
                        }
                        __Vfunc_tb_market_noise_gen__DOT__abs32__53__Vfuncout 
                            = VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__abs32__53__v);
                        __Vlabel0: ;
                    }
                }(), __Vfunc_tb_market_noise_gen__DOT__abs32__53__Vfuncout));
        vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec1 
            = (vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec1 
               + ([&]() {
                    __Vfunc_tb_market_noise_gen__DOT__abs32__54__v 
                        = vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[1U];
                    {
                        __Vfunc_tb_market_noise_gen__DOT__abs32__54__Vfuncout = 0ULL;
                        if (VL_GTS_III(32, 0U, __Vfunc_tb_market_noise_gen__DOT__abs32__54__v)) {
                            __Vfunc_tb_market_noise_gen__DOT__abs32__54__Vfuncout 
                                = (- VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__abs32__54__v));
                            goto __Vlabel1;
                        }
                        __Vfunc_tb_market_noise_gen__DOT__abs32__54__Vfuncout 
                            = VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__abs32__54__v);
                        __Vlabel1: ;
                    }
                }(), __Vfunc_tb_market_noise_gen__DOT__abs32__54__Vfuncout));
        tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_4__DOT____Vrepeat3 
            = (tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_4__DOT____Vrepeat3 
               - (IData)(1U));
    }
    __Vtask_tb_market_noise_gen__DOT__check__55__cond 
        = VL_GTS_IQQ(64, vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec0, vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec1);
    vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__55__msg = "popscale cumulative |sector0| > |sector1|"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__55__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__55__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         98);
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 0U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         100);
    vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U] = 1U;
    vlSelfRef.tb_market_noise_gen__DOT__active_sym_count = 4U;
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0x00000fa0U;
    while (VL_LTS_III(32, 0U, tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_5__DOT____Vrepeat4)) {
        __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__58__n_act = 4U;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__58__tag = "sat"s;
        vlSelfRef.tb_market_noise_gen__DOT__tick = 1U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             86);
        vlSelfRef.tb_market_noise_gen__DOT__tick = 0U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             88);
        __Vtask_tb_market_noise_gen__DOT__check_decomp__60__n_act 
            = __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__58__n_act;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__60__tag 
            = vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__58__tag;
        __Vtask_tb_market_noise_gen__DOT__check_decomp__60__exp_step = 0;
        if (VL_LTS_III(32, 0U, __Vtask_tb_market_noise_gen__DOT__check_decomp__60__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__60__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]);
            __Vtask_tb_market_noise_gen__DOT__check__61__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__60__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__61__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym0",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__60__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__61__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__61__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 1U, __Vtask_tb_market_noise_gen__DOT__check_decomp__60__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__60__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]);
            __Vtask_tb_market_noise_gen__DOT__check__61__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__60__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__61__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym1",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__60__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__61__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__61__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 2U, __Vtask_tb_market_noise_gen__DOT__check_decomp__60__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__60__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]);
            __Vtask_tb_market_noise_gen__DOT__check__61__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__60__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__61__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym2",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__60__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__61__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__61__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 3U, __Vtask_tb_market_noise_gen__DOT__check_decomp__60__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__60__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]);
            __Vtask_tb_market_noise_gen__DOT__check__61__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__60__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__61__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym3",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__60__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__61__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__61__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_5__DOT____Vrepeat4 
            = (tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_5__DOT____Vrepeat4 
               - (IData)(1U));
    }
    __Vtask_tb_market_noise_gen__DOT__check__62__cond 
        = (VL_GTES_III(32, 0x02000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[0U]) 
           & VL_LTES_III(32, 0xfe000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[0U]));
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__62__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: sat |sector_noise[0]| bound\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__62__cond 
        = (VL_GTES_III(32, 0x02000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[1U]) 
           & VL_LTES_III(32, 0xfe000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[1U]));
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__62__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: sat |sector_noise[1]| bound\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__62__cond 
        = (VL_GTES_III(32, 0x02000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[2U]) 
           & VL_LTES_III(32, 0xfe000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[2U]));
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__62__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: sat |sector_noise[2]| bound\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__62__cond 
        = (VL_GTES_III(32, 0x02000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[3U]) 
           & VL_LTES_III(32, 0xfe000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[3U]));
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__62__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: sat |sector_noise[3]| bound\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__62__cond 
        = (VL_GTES_III(32, 0x02000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[4U]) 
           & VL_LTES_III(32, 0xfe000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[4U]));
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__62__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: sat |sector_noise[4]| bound\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__62__cond 
        = (VL_GTES_III(32, 0x02000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[5U]) 
           & VL_LTES_III(32, 0xfe000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[5U]));
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__62__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: sat |sector_noise[5]| bound\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__62__cond 
        = (VL_GTES_III(32, 0x02000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[6U]) 
           & VL_LTES_III(32, 0xfe000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[6U]));
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__62__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: sat |sector_noise[6]| bound\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    __Vtask_tb_market_noise_gen__DOT__check__62__cond 
        = (VL_GTES_III(32, 0x02000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[7U]) 
           & VL_LTES_III(32, 0xfe000000U, vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[7U]));
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__62__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: sat |sector_noise[7]| bound\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    if ((0U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__active_sym_count))) {
        __Vtask_tb_market_noise_gen__DOT__check__63__cond 
            = (VL_GTES_III(32, 0x02000000U, vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]) 
               & VL_LTES_III(32, 0xfe000000U, vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]));
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__63__msg = "sat |company[0]| bound"s;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__63__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__63__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
            vlSelfRef.tb_market_noise_gen__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
        }
    }
    if ((1U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__active_sym_count))) {
        __Vtask_tb_market_noise_gen__DOT__check__63__cond 
            = (VL_GTES_III(32, 0x02000000U, vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]) 
               & VL_LTES_III(32, 0xfe000000U, vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]));
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__63__msg = "sat |company[1]| bound"s;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__63__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__63__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
            vlSelfRef.tb_market_noise_gen__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
        }
    }
    if ((2U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__active_sym_count))) {
        __Vtask_tb_market_noise_gen__DOT__check__63__cond 
            = (VL_GTES_III(32, 0x02000000U, vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]) 
               & VL_LTES_III(32, 0xfe000000U, vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]));
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__63__msg = "sat |company[2]| bound"s;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__63__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__63__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
            vlSelfRef.tb_market_noise_gen__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
        }
    }
    if ((3U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__active_sym_count))) {
        __Vtask_tb_market_noise_gen__DOT__check__63__cond 
            = (VL_GTES_III(32, 0x02000000U, vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]) 
               & VL_LTES_III(32, 0xfe000000U, vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]));
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__63__msg = "sat |company[3]| bound"s;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__63__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__63__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
            vlSelfRef.tb_market_noise_gen__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
        }
    }
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 1U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         98);
    vlSelfRef.tb_market_noise_gen__DOT__lfsr_load = 0U;
    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                               "@(posedge tb_market_noise_gen.clk)");
    co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_market_noise_gen.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                         100);
    vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__diff01 = 0U;
    tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0x00000018U;
    while (VL_LTS_III(32, 0U, tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_6__DOT____Vrepeat5)) {
        __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__65__n_act = 4U;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__65__tag = "diff"s;
        vlSelfRef.tb_market_noise_gen__DOT__tick = 1U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             86);
        vlSelfRef.tb_market_noise_gen__DOT__tick = 0U;
        Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(vlSelf, 
                                                                   "@(posedge tb_market_noise_gen.clk)");
        co_await vlSelfRef.__VtrigSched_h55fe2048__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_market_noise_gen.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                                             88);
        __Vtask_tb_market_noise_gen__DOT__check_decomp__67__n_act 
            = __Vtask_tb_market_noise_gen__DOT__do_tick_decomp__65__n_act;
        vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__67__tag 
            = vlSelfRef.__Vtask_tb_market_noise_gen__DOT__do_tick_decomp__65__tag;
        __Vtask_tb_market_noise_gen__DOT__check_decomp__67__exp_step = 0;
        if (VL_LTS_III(32, 0U, __Vtask_tb_market_noise_gen__DOT__check_decomp__67__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__67__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U]);
            __Vtask_tb_market_noise_gen__DOT__check__68__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__67__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__68__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym0",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__67__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__68__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__68__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 1U, __Vtask_tb_market_noise_gen__DOT__check_decomp__67__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__67__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U]);
            __Vtask_tb_market_noise_gen__DOT__check__68__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__67__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__68__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym1",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__67__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__68__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__68__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 2U, __Vtask_tb_market_noise_gen__DOT__check_decomp__67__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__67__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U]);
            __Vtask_tb_market_noise_gen__DOT__check__68__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__67__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__68__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym2",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__67__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__68__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__68__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if (VL_LTS_III(32, 3U, __Vtask_tb_market_noise_gen__DOT__check_decomp__67__n_act)) {
            __Vtask_tb_market_noise_gen__DOT__check_decomp__67__exp_step 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U]);
            __Vtask_tb_market_noise_gen__DOT__check__68__cond 
                = (vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
                   == __Vtask_tb_market_noise_gen__DOT__check_decomp__67__exp_step);
            vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__68__msg 
                = VL_SFORMATF_N_NX("%@ decomp sym3",0,
                                   -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check_decomp__67__tag)) ;
            if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__68__cond)))))) {
                VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),-1,
                             &(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__68__msg));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
                vlSelfRef.tb_market_noise_gen__DOT__err_count 
                    = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
            }
        }
        if ((vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
             != vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U])) {
            vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__diff01 = 1U;
        }
        tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_6__DOT____Vrepeat5 
            = (tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk1_6__DOT____Vrepeat5 
               - (IData)(1U));
    }
    __Vtask_tb_market_noise_gen__DOT__check__69__cond 
        = vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__diff01;
    vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__69__msg = "sym0 vs sym2 differ at least once"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_market_noise_gen__DOT__check__69__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_market_noise_gen.sv:40: Assertion failed in %Ntb_market_noise_gen.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_market_noise_gen__DOT__check__69__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 40, "");
        vlSelfRef.tb_market_noise_gen__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    if ((0U == vlSelfRef.tb_market_noise_gen__DOT__err_count)) {
        VL_WRITEF_NX("tb_market_noise_gen: PASS (all checks passed)\n",0);
    } else {
        VL_WRITEF_NX("tb_market_noise_gen: FAIL (%0d errors)\n",0,
                     32,vlSelfRef.tb_market_noise_gen__DOT__err_count);
    }
    VL_FINISH_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 265, "");
    co_return;
}

VlCoroutine Vtb_market_noise_gen___024root___eval_initial__TOP__Vtiming__2(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 
                                             58);
        vlSelfRef.tb_market_noise_gen__DOT__clk = (1U 
                                                   & (~ (IData)(vlSelfRef.tb_market_noise_gen__DOT__clk)));
    }
    co_return;
}

void Vtb_market_noise_gen___024root___eval_triggers_vec__act(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_triggers_vec__act\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((((IData)(vlSelfRef.tb_market_noise_gen__DOT__rst_n) 
                                                        != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__rst_n__0)) 
                                                       << 3U) 
                                                      | (vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                         << 2U)) 
                                                     | ((((~ (IData)(vlSelfRef.tb_market_noise_gen__DOT__rst_n)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__rst_n__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_market_noise_gen__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__clk__0 
        = vlSelfRef.tb_market_noise_gen__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__rst_n__0 
        = vlSelfRef.tb_market_noise_gen__DOT__rst_n;
}

bool Vtb_market_noise_gen___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___trigger_anySet__act\n"); );
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

void Vtb_market_noise_gen___024root___act_comb__TOP__0(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___act_comb__TOP__0\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable 
        = ((IData)(vlSelfRef.tb_market_noise_gen__DOT__enable) 
           & (IData)(vlSelfRef.tb_market_noise_gen__DOT__tick));
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff 
        = ((4U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__active_sym_count))
            ? 4U : (IData)(vlSelfRef.tb_market_noise_gen__DOT__active_sym_count));
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[0U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[1U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[2U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[3U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[4U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[5U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[6U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[7U] = 0U;
    if ((0U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                              [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]));
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U] 
            = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[0U];
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
               + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[0U]);
    } else {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] = 0U;
    }
    if ((1U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                              [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]));
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U] 
            = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[1U];
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
               + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[1U]);
    } else {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] = 0U;
    }
    if ((2U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                              [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]));
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U] 
            = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[2U];
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
               + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[2U]);
    } else {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] = 0U;
    }
    if ((3U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                              [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]));
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U] 
            = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[3U];
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
               + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[3U]);
    } else {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] = 0U;
    }
}

void Vtb_market_noise_gen___024root___eval_act(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_act\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((0x000000000000000dULL & vlSelfRef.__VactTriggered[0U])) {
        Vtb_market_noise_gen___024root___act_comb__TOP__0(vlSelf);
    }
}

void Vtb_market_noise_gen___024root___nba_sequent__TOP__0(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___nba_sequent__TOP__0\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__acc;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__acc = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__delta;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__delta = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos = 0;
    QData/*63:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__Vfuncout;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__r;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__r = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta = 0;
    QData/*63:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r = 0;
    CData/*7:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base = 0;
    QData/*63:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r;
    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v0;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v4;
    __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v4 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v4;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v4 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v5;
    __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v5 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v5;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v5 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v6;
    __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v6 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v6;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v6 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v7;
    __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v7 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v7;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v7 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v8;
    __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v8 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v8;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v8 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v9;
    __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v9 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v9;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v9 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v10;
    __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v10 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v10;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v10 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v11;
    __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v11 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v11;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v11 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v12;
    __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v12 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v12;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v12 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v13;
    __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v13 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v13;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v13 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v14;
    __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v14 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v14;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v14 = 0;
    IData/*31:0*/ __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v15;
    __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v15 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v15;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v15 = 0;
    CData/*0:0*/ __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v16;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v16 = 0;
    // Body
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v4 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v5 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v6 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v7 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v8 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v9 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v10 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v11 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v12 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v13 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v14 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v15 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v0 = 0U;
    __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v16 = 0U;
    if (vlSelfRef.tb_market_noise_gen__DOT__rst_n) {
        if (vlSelfRef.tb_market_noise_gen__DOT__lfsr_load) {
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg 
                = ((0U == (0xa11fe511U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0xa11fe511U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0xc13fa9a9U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0xc13fa9a9U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x5f772362U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0x5f772362U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0xfdae9d1bU ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0xfdae9d1bU ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x9be616d4U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0x9be616d4U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x3a1d908dU ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0x3a1d908dU ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0xd8550a46U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0xd8550a46U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x768c83ffU ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0x768c83ffU ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x14c3fdb8U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0x14c3fdb8U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x9e3779b9U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0x9e3779b9U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x3c6ef372U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0x3c6ef372U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0xdaa66d2bU ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0xdaa66d2bU ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
            __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x78dde6e4U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed))
                    ? 1U : (0x78dde6e4U ^ vlSelfRef.tb_market_noise_gen__DOT__base_seed));
        } else {
            if (vlSelfRef.tb_market_noise_gen__DOT__dut__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) {
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (0U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff)))) {
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (1U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff)))) {
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (2U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff)))) {
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (3U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff)))) {
                __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
        }
    } else {
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
    }
    if (vlSelfRef.tb_market_noise_gen__DOT__rst_n) {
        if (vlSelfRef.tb_market_noise_gen__DOT__lfsr_load) {
            __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v0 = 1U;
        } else if (((IData)(vlSelfRef.tb_market_noise_gen__DOT__enable) 
                    & (IData)(vlSelfRef.tb_market_noise_gen__DOT__tick))) {
            if ((0U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos = 0x02000000U;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg = 0xfe000000U;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__r 
                    = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_rand[0U];
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__delta 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__Vfuncout;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__acc 
                    = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[0U];
                {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout = 0;
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s = 0;
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos))) {
                        __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout 
                            = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos;
                        goto __Vlabel0;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg))) {
                        __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout 
                            = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg;
                        goto __Vlabel0;
                    }
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout 
                        = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s);
                    __Vlabel0: ;
                }
                __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v4 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout;
                __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v4 = 1U;
            }
            if ((1U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos = 0x02000000U;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg = 0xfe000000U;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__r 
                    = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_rand[1U];
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__delta 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__Vfuncout;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__acc 
                    = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[1U];
                {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout = 0;
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s = 0;
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos))) {
                        __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout 
                            = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos;
                        goto __Vlabel1;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg))) {
                        __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout 
                            = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg;
                        goto __Vlabel1;
                    }
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout 
                        = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s);
                    __Vlabel1: ;
                }
                __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v5 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout;
                __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v5 = 1U;
            }
            if ((2U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos = 0x02000000U;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg = 0xfe000000U;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__r 
                    = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_rand[2U];
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__delta 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__Vfuncout;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__acc 
                    = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[2U];
                {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout = 0;
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s = 0;
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos))) {
                        __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout 
                            = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos;
                        goto __Vlabel2;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg))) {
                        __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout 
                            = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg;
                        goto __Vlabel2;
                    }
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout 
                        = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s);
                    __Vlabel2: ;
                }
                __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v6 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout;
                __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v6 = 1U;
            }
            if ((3U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos = 0x02000000U;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg = 0xfe000000U;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__r 
                    = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_rand[3U];
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__delta 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__company_tick_delta__71__Vfuncout;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__acc 
                    = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[3U];
                {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout = 0;
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s = 0;
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos))) {
                        __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout 
                            = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_pos;
                        goto __Vlabel3;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg))) {
                        __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout 
                            = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__lim_neg;
                        goto __Vlabel3;
                    }
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout 
                        = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__s);
                    __Vlabel3: ;
                }
                __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v7 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__70__Vfuncout;
                __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v7 = 1U;
            }
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[0U];
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[0U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x7fffffffU;
                    goto __Vlabel4;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x80000000U;
                    goto __Vlabel4;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod);
                __Vlabel4: ;
            }
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[0U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0x02000000U;
                    goto __Vlabel5;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0xfe000000U;
                    goto __Vlabel5;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s);
                __Vlabel5: ;
            }
            __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v8 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout;
            __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v8 = 1U;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[1U];
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[1U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x7fffffffU;
                    goto __Vlabel6;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x80000000U;
                    goto __Vlabel6;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod);
                __Vlabel6: ;
            }
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[1U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0x02000000U;
                    goto __Vlabel7;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0xfe000000U;
                    goto __Vlabel7;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s);
                __Vlabel7: ;
            }
            __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v9 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout;
            __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v9 = 1U;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[2U];
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[2U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x7fffffffU;
                    goto __Vlabel8;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x80000000U;
                    goto __Vlabel8;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod);
                __Vlabel8: ;
            }
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[2U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0x02000000U;
                    goto __Vlabel9;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0xfe000000U;
                    goto __Vlabel9;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s);
                __Vlabel9: ;
            }
            __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v10 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout;
            __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v10 = 1U;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[3U];
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[3U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x7fffffffU;
                    goto __Vlabel10;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x80000000U;
                    goto __Vlabel10;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod);
                __Vlabel10: ;
            }
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[3U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0x02000000U;
                    goto __Vlabel11;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0xfe000000U;
                    goto __Vlabel11;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s);
                __Vlabel11: ;
            }
            __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v11 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout;
            __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v11 = 1U;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[4U];
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[4U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x7fffffffU;
                    goto __Vlabel12;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x80000000U;
                    goto __Vlabel12;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod);
                __Vlabel12: ;
            }
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[4U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0x02000000U;
                    goto __Vlabel13;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0xfe000000U;
                    goto __Vlabel13;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s);
                __Vlabel13: ;
            }
            __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v12 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout;
            __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v12 = 1U;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[5U];
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[5U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x7fffffffU;
                    goto __Vlabel14;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x80000000U;
                    goto __Vlabel14;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod);
                __Vlabel14: ;
            }
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[5U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0x02000000U;
                    goto __Vlabel15;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0xfe000000U;
                    goto __Vlabel15;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s);
                __Vlabel15: ;
            }
            __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v13 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout;
            __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v13 = 1U;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[6U];
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[6U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x7fffffffU;
                    goto __Vlabel16;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x80000000U;
                    goto __Vlabel16;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod);
                __Vlabel16: ;
            }
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[6U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0x02000000U;
                    goto __Vlabel17;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0xfe000000U;
                    goto __Vlabel17;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s);
                __Vlabel17: ;
            }
            __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v14 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout;
            __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v14 = 1U;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[7U];
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[7U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__r;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base 
                    = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_base_delta__74__Vfuncout;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x7fffffffU;
                    goto __Vlabel18;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout = 0x80000000U;
                    goto __Vlabel18;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__prod);
                __Vlabel18: ;
            }
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__sector_scaled_delta__73__Vfuncout;
            __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[7U];
            {
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s = 0;
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0x02000000U;
                    goto __Vlabel19;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s)) {
                    __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout = 0xfe000000U;
                    goto __Vlabel19;
                }
                __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout 
                    = (IData)(__Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__s);
                __Vlabel19: ;
            }
            __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v15 
                = __Vfunc_tb_market_noise_gen__DOT__dut__DOT__add_sat32__72__Vfuncout;
            __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v15 = 1U;
        }
    } else {
        __VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v16 = 1U;
    }
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v0) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[0U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[1U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[2U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[3U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[0U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[1U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[2U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[3U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[4U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[5U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[6U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[7U] = 0U;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v4) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[0U] 
            = __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v4;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v5) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[1U] 
            = __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v5;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v6) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[2U] 
            = __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v6;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v7) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[3U] 
            = __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16__v7;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v8) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[0U] 
            = __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v8;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v9) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[1U] 
            = __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v9;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v10) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[2U] 
            = __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v10;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v11) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[3U] 
            = __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v11;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v12) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[4U] 
            = __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v12;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v13) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[5U] 
            = __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v13;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v14) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[6U] 
            = __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v14;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v15) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[7U] 
            = __VdlyVal__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v15;
    }
    if (__VdlySet__tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16__v16) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[0U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[1U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[2U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[3U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[0U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[1U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[2U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[3U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[4U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[5U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[6U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[7U] = 0U;
    }
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[0U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[1U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[2U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[3U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[4U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[5U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[6U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[7U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_rand[0U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_rand[1U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_rand[2U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_rand[3U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[0U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[0U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[1U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[1U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[2U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[2U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[3U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[3U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[4U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[4U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[5U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[5U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[6U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[6U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[7U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[7U];
}

void Vtb_market_noise_gen___024root___nba_comb__TOP__0(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___nba_comb__TOP__0\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable 
        = ((IData)(vlSelfRef.tb_market_noise_gen__DOT__enable) 
           & (IData)(vlSelfRef.tb_market_noise_gen__DOT__tick));
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff 
        = ((4U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__active_sym_count))
            ? 4U : (IData)(vlSelfRef.tb_market_noise_gen__DOT__active_sym_count));
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[0U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[1U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[2U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[3U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[4U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[5U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[6U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[7U] = 0U;
    if ((0U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                              [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]));
    }
    if ((1U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                              [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]));
    }
    if ((2U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                              [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]));
    }
    if ((3U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                              [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]));
    }
}

void Vtb_market_noise_gen___024root___nba_comb__TOP__1(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___nba_comb__TOP__1\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((0U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U] 
            = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[0U];
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
               + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[0U]);
    } else {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] = 0U;
    }
    if ((1U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U] 
            = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[1U];
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
               + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[1U]);
    } else {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] = 0U;
    }
    if ((2U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U] 
            = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[2U];
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
               + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[2U]);
    } else {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] = 0U;
    }
    if ((3U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U] 
            = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[3U];
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
               + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[3U]);
    } else {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] = 0U;
    }
}

void Vtb_market_noise_gen___024root___eval_nba(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_nba\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_market_noise_gen___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((0x000000000000000dULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable 
            = ((IData)(vlSelfRef.tb_market_noise_gen__DOT__enable) 
               & (IData)(vlSelfRef.tb_market_noise_gen__DOT__tick));
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff 
            = ((4U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__active_sym_count))
                ? 4U : (IData)(vlSelfRef.tb_market_noise_gen__DOT__active_sym_count));
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[0U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[1U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[2U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[3U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[4U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[5U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[6U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[7U] = 0U;
        if ((0U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
            vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]] 
                = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                                  [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]));
        }
        if ((1U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
            vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]] 
                = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                                  [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]));
        }
        if ((2U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
            vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]] 
                = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                                  [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]));
        }
        if ((3U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
            vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]] 
                = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                                  [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]));
        }
    }
    if ((0x000000000000000fULL & vlSelfRef.__VnbaTriggered[0U])) {
        if ((0U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
            vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U] 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[0U];
            vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[0U]);
        } else {
            vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U] = 0U;
            vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] = 0U;
        }
        if ((1U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
            vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U] 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[1U];
            vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[1U]);
        } else {
            vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U] = 0U;
            vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] = 0U;
        }
        if ((2U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
            vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U] 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[2U];
            vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[2U]);
        } else {
            vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U] = 0U;
            vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] = 0U;
        }
        if ((3U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
            vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U] 
                = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[3U];
            vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
                = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                           (0x0000003fU 
                                                            & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                             - (IData)(0x00000020U)), 6U) 
                    + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                    [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
                   + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[3U]);
        } else {
            vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U] = 0U;
            vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] = 0U;
        }
    }
}

void Vtb_market_noise_gen___024root___timing_ready(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___timing_ready\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((8ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h04d2243f__0.ready("@( tb_market_noise_gen.rst_n)");
    }
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h55fe2048__0.ready("@(posedge tb_market_noise_gen.clk)");
    }
}

void Vtb_market_noise_gen___024root___timing_resume(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___timing_resume\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h04d2243f__0.moveToResumeQueue(
                                                          "@( tb_market_noise_gen.rst_n)");
    vlSelfRef.__VtrigSched_h55fe2048__0.moveToResumeQueue(
                                                          "@(posedge tb_market_noise_gen.clk)");
    vlSelfRef.__VtrigSched_h04d2243f__0.resume("@( tb_market_noise_gen.rst_n)");
    vlSelfRef.__VtrigSched_h55fe2048__0.resume("@(posedge tb_market_noise_gen.clk)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_market_noise_gen___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vtb_market_noise_gen___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_market_noise_gen___024root___eval_phase__act(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_phase__act\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_market_noise_gen___024root___eval_triggers_vec__act(vlSelf);
    Vtb_market_noise_gen___024root___timing_ready(vlSelf);
    Vtb_market_noise_gen___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_market_noise_gen___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_market_noise_gen___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_market_noise_gen___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_market_noise_gen___024root___timing_resume(vlSelf);
        Vtb_market_noise_gen___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_market_noise_gen___024root___eval_phase__inact(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_phase__inact\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 13, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_market_noise_gen___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_market_noise_gen___024root___eval_phase__nba(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_phase__nba\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_market_noise_gen___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_market_noise_gen___024root___eval_nba(vlSelf);
        Vtb_market_noise_gen___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_market_noise_gen___024root___eval(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_market_noise_gen___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 13, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 13, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_market_noise_gen___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 13, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_market_noise_gen___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_market_noise_gen___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_market_noise_gen___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_market_noise_gen___024root____VbeforeTrig_h04d2243f__0(Vtb_market_noise_gen___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root____VbeforeTrig_h04d2243f__0\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.tb_market_noise_gen__DOT__rst_n) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__rst_n__0)) 
                                  << 3U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__rst_n__0 
        = vlSelfRef.tb_market_noise_gen__DOT__rst_n;
    if ((8ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h04d2243f__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0(Vtb_market_noise_gen___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root____VbeforeTrig_h55fe2048__0\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_market_noise_gen__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__clk__0 
        = vlSelfRef.tb_market_noise_gen__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h55fe2048__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_market_noise_gen___024root___eval_debug_assertions(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_debug_assertions\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
