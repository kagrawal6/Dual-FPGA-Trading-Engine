// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_board_a_ctrl.h for the primary calling header

#include "Vtb_board_a_ctrl__pch.h"

VlCoroutine Vtb_board_a_ctrl___024root___eval_initial__TOP__Vtiming__0(Vtb_board_a_ctrl___024root* vlSelf);
VlCoroutine Vtb_board_a_ctrl___024root___eval_initial__TOP__Vtiming__1(Vtb_board_a_ctrl___024root* vlSelf);
VlCoroutine Vtb_board_a_ctrl___024root___eval_initial__TOP__Vtiming__2(Vtb_board_a_ctrl___024root* vlSelf);

void Vtb_board_a_ctrl___024root___eval_initial(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_initial\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_board_a_ctrl__DOT__clk = 0U;
    Vtb_board_a_ctrl___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_board_a_ctrl___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_board_a_ctrl___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

VlCoroutine Vtb_board_a_ctrl___024root___eval_initial__TOP__Vtiming__0(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_board_a_ctrl__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000186a0ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 
                                         39);
    vlSelfRef.tb_board_a_ctrl__DOT__rst_n = 1U;
    co_return;
}

void Vtb_board_a_ctrl___024root____VbeforeTrig_h5841218e__0(Vtb_board_a_ctrl___024root* vlSelf, const char* __VeventDescription);
void Vtb_board_a_ctrl___024root____VbeforeTrig_h5c2f6120__0(Vtb_board_a_ctrl___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_board_a_ctrl___024root___eval_initial__TOP__Vtiming__1(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_board_a_ctrl__DOT__unnamedblk1_1__DOT____Vrepeat0;
    tb_board_a_ctrl__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ tb_board_a_ctrl__DOT__unnamedblk1__DOT__p;
    tb_board_a_ctrl__DOT__unnamedblk1__DOT__p = 0;
    IData/*31:0*/ tb_board_a_ctrl__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1;
    tb_board_a_ctrl__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0;
    CData/*0:0*/ __Vtask_tb_board_a_ctrl__DOT__check__0__pass;
    __Vtask_tb_board_a_ctrl__DOT__check__0__pass = 0;
    CData/*0:0*/ __Vtask_tb_board_a_ctrl__DOT__check__1__pass;
    __Vtask_tb_board_a_ctrl__DOT__check__1__pass = 0;
    CData/*0:0*/ __Vtask_tb_board_a_ctrl__DOT__check__2__pass;
    __Vtask_tb_board_a_ctrl__DOT__check__2__pass = 0;
    CData/*0:0*/ __Vtask_tb_board_a_ctrl__DOT__check__3__pass;
    __Vtask_tb_board_a_ctrl__DOT__check__3__pass = 0;
    CData/*0:0*/ __Vtask_tb_board_a_ctrl__DOT__check__4__pass;
    __Vtask_tb_board_a_ctrl__DOT__check__4__pass = 0;
    CData/*0:0*/ __Vtask_tb_board_a_ctrl__DOT__check__5__pass;
    __Vtask_tb_board_a_ctrl__DOT__check__5__pass = 0;
    CData/*0:0*/ __Vtask_tb_board_a_ctrl__DOT__check__6__pass;
    __Vtask_tb_board_a_ctrl__DOT__check__6__pass = 0;
    CData/*0:0*/ __Vtask_tb_board_a_ctrl__DOT__check__7__pass;
    __Vtask_tb_board_a_ctrl__DOT__check__7__pass = 0;
    CData/*0:0*/ __Vtask_tb_board_a_ctrl__DOT__check__8__pass;
    __Vtask_tb_board_a_ctrl__DOT__check__8__pass = 0;
    CData/*0:0*/ __Vtask_tb_board_a_ctrl__DOT__check__9__pass;
    __Vtask_tb_board_a_ctrl__DOT__check__9__pass = 0;
    // Body
    vlSelfRef.tb_board_a_ctrl__DOT__btn = 0U;
    vlSelfRef.tb_board_a_ctrl__DOT__sw = 0U;
    vlSelfRef.tb_board_a_ctrl__DOT__running = 0U;
    vlSelfRef.tb_board_a_ctrl__DOT__active_regime = 0U;
    vlSelfRef.tb_board_a_ctrl__DOT__link_up = 0U;
    vlSelfRef.tb_board_a_ctrl__DOT__link_error = 0U;
    Vtb_board_a_ctrl___024root____VbeforeTrig_h5841218e__0(vlSelf, 
                                                           "@(posedge tb_board_a_ctrl.clk)");
    co_await vlSelfRef.__VtrigSched_h5841218e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_ctrl.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 
                                                         79);
    while ((1U & (~ (IData)(vlSelfRef.tb_board_a_ctrl__DOT__rst_n)))) {
        Vtb_board_a_ctrl___024root____VbeforeTrig_h5c2f6120__0(vlSelf, 
                                                               "@( tb_board_a_ctrl.rst_n)");
        co_await vlSelfRef.__VtrigSched_h5c2f6120__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_board_a_ctrl.rst_n)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 
                                                             80);
    }
    Vtb_board_a_ctrl___024root____VbeforeTrig_h5841218e__0(vlSelf, 
                                                           "@(posedge tb_board_a_ctrl.clk)");
    co_await vlSelfRef.__VtrigSched_h5841218e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_ctrl.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 
                                                         81);
    __Vtask_tb_board_a_ctrl__DOT__check__0__pass = 
        (0U == (IData)(vlSelfRef.tb_board_a_ctrl__DOT__regime_sw));
    vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__0__msg = "regime_sw from sw[1:0]"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_board_a_ctrl__DOT__check__0__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_board_a_ctrl.sv:66: Assertion failed in %Ntb_board_a_ctrl.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__0__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 66, "");
        vlSelfRef.tb_board_a_ctrl__DOT__err_count = 
            ((IData)(1U) + vlSelfRef.tb_board_a_ctrl__DOT__err_count);
    }
    vlSelfRef.tb_board_a_ctrl__DOT__sw = 1U;
    Vtb_board_a_ctrl___024root____VbeforeTrig_h5841218e__0(vlSelf, 
                                                           "@(posedge tb_board_a_ctrl.clk)");
    co_await vlSelfRef.__VtrigSched_h5841218e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_ctrl.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 
                                                         85);
    __Vtask_tb_board_a_ctrl__DOT__check__1__pass = 
        (1U == (IData)(vlSelfRef.tb_board_a_ctrl__DOT__regime_sw));
    vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__1__msg = "regime_sw VOLATILE"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_board_a_ctrl__DOT__check__1__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_board_a_ctrl.sv:66: Assertion failed in %Ntb_board_a_ctrl.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__1__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 66, "");
        vlSelfRef.tb_board_a_ctrl__DOT__err_count = 
            ((IData)(1U) + vlSelfRef.tb_board_a_ctrl__DOT__err_count);
    }
    vlSelfRef.tb_board_a_ctrl__DOT__sw = 4U;
    Vtb_board_a_ctrl___024root____VbeforeTrig_h5841218e__0(vlSelf, 
                                                           "@(posedge tb_board_a_ctrl.clk)");
    co_await vlSelfRef.__VtrigSched_h5841218e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_ctrl.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 
                                                         88);
    __Vtask_tb_board_a_ctrl__DOT__check__2__pass = vlSelfRef.tb_board_a_ctrl__DOT__sw_override;
    vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__2__msg = "sw_override"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_board_a_ctrl__DOT__check__2__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_board_a_ctrl.sv:66: Assertion failed in %Ntb_board_a_ctrl.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__2__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 66, "");
        vlSelfRef.tb_board_a_ctrl__DOT__err_count = 
            ((IData)(1U) + vlSelfRef.tb_board_a_ctrl__DOT__err_count);
    }
    vlSelfRef.tb_board_a_ctrl__DOT__sw = 0U;
    vlSelfRef.tb_board_a_ctrl__DOT__running = 1U;
    vlSelfRef.tb_board_a_ctrl__DOT__active_regime = 2U;
    vlSelfRef.tb_board_a_ctrl__DOT__link_up = 1U;
    vlSelfRef.tb_board_a_ctrl__DOT__link_error = 0U;
    Vtb_board_a_ctrl___024root____VbeforeTrig_h5841218e__0(vlSelf, 
                                                           "@(posedge tb_board_a_ctrl.clk)");
    co_await vlSelfRef.__VtrigSched_h5841218e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_ctrl.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 
                                                         96);
    __Vtask_tb_board_a_ctrl__DOT__check__3__pass = 
        (1U & ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__led) 
               >> 2U));
    vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__3__msg = "led[2] running"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_board_a_ctrl__DOT__check__3__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_board_a_ctrl.sv:66: Assertion failed in %Ntb_board_a_ctrl.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__3__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 66, "");
        vlSelfRef.tb_board_a_ctrl__DOT__err_count = 
            ((IData)(1U) + vlSelfRef.tb_board_a_ctrl__DOT__err_count);
    }
    __Vtask_tb_board_a_ctrl__DOT__check__4__pass = 
        (1U & ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__led) 
               >> 4U));
    vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__4__msg = "led[4] link_up"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_board_a_ctrl__DOT__check__4__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_board_a_ctrl.sv:66: Assertion failed in %Ntb_board_a_ctrl.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__4__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 66, "");
        vlSelfRef.tb_board_a_ctrl__DOT__err_count = 
            ((IData)(1U) + vlSelfRef.tb_board_a_ctrl__DOT__err_count);
    }
    __Vtask_tb_board_a_ctrl__DOT__check__5__pass = 
        (4U == (IData)(vlSelfRef.tb_board_a_ctrl__DOT__rgb0));
    vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__5__msg = "rgb0 BURST red"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_board_a_ctrl__DOT__check__5__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_board_a_ctrl.sv:66: Assertion failed in %Ntb_board_a_ctrl.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__5__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 66, "");
        vlSelfRef.tb_board_a_ctrl__DOT__err_count = 
            ((IData)(1U) + vlSelfRef.tb_board_a_ctrl__DOT__err_count);
    }
    __Vtask_tb_board_a_ctrl__DOT__check__6__pass = 
        (2U == (IData)(vlSelfRef.tb_board_a_ctrl__DOT__rgb1));
    vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__6__msg = "rgb1 ok green"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_board_a_ctrl__DOT__check__6__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_board_a_ctrl.sv:66: Assertion failed in %Ntb_board_a_ctrl.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__6__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 66, "");
        vlSelfRef.tb_board_a_ctrl__DOT__err_count = 
            ((IData)(1U) + vlSelfRef.tb_board_a_ctrl__DOT__err_count);
    }
    vlSelfRef.tb_board_a_ctrl__DOT__link_error = 1U;
    Vtb_board_a_ctrl___024root____VbeforeTrig_h5841218e__0(vlSelf, 
                                                           "@(posedge tb_board_a_ctrl.clk)");
    co_await vlSelfRef.__VtrigSched_h5841218e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_ctrl.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 
                                                         103);
    __Vtask_tb_board_a_ctrl__DOT__check__7__pass = 
        (6U == (IData)(vlSelfRef.tb_board_a_ctrl__DOT__rgb1));
    vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__7__msg = "rgb1 error yellow"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_board_a_ctrl__DOT__check__7__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_board_a_ctrl.sv:66: Assertion failed in %Ntb_board_a_ctrl.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__7__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 66, "");
        vlSelfRef.tb_board_a_ctrl__DOT__err_count = 
            ((IData)(1U) + vlSelfRef.tb_board_a_ctrl__DOT__err_count);
    }
    vlSelfRef.tb_board_a_ctrl__DOT__link_error = 0U;
    vlSelfRef.tb_board_a_ctrl__DOT__link_up = 0U;
    Vtb_board_a_ctrl___024root____VbeforeTrig_h5841218e__0(vlSelf, 
                                                           "@(posedge tb_board_a_ctrl.clk)");
    co_await vlSelfRef.__VtrigSched_h5841218e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_ctrl.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 
                                                         108);
    __Vtask_tb_board_a_ctrl__DOT__check__8__pass = 
        (4U == (IData)(vlSelfRef.tb_board_a_ctrl__DOT__rgb1));
    vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__8__msg = "rgb1 down red"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_board_a_ctrl__DOT__check__8__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_board_a_ctrl.sv:66: Assertion failed in %Ntb_board_a_ctrl.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__8__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 66, "");
        vlSelfRef.tb_board_a_ctrl__DOT__err_count = 
            ((IData)(1U) + vlSelfRef.tb_board_a_ctrl__DOT__err_count);
    }
    vlSelfRef.tb_board_a_ctrl__DOT__btn = 0U;
    tb_board_a_ctrl__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0x00000022U;
    while (VL_LTS_III(32, 0U, tb_board_a_ctrl__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vtb_board_a_ctrl___024root____VbeforeTrig_h5841218e__0(vlSelf, 
                                                               "@(posedge tb_board_a_ctrl.clk)");
        co_await vlSelfRef.__VtrigSched_h5841218e__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_board_a_ctrl.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 
                                                             113);
        tb_board_a_ctrl__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (tb_board_a_ctrl__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.tb_board_a_ctrl__DOT__btn = (1U | (IData)(vlSelfRef.tb_board_a_ctrl__DOT__btn));
    tb_board_a_ctrl__DOT__unnamedblk1__DOT__p = 0U;
    tb_board_a_ctrl__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0x0000002aU;
    while (VL_LTS_III(32, 0U, tb_board_a_ctrl__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
        Vtb_board_a_ctrl___024root____VbeforeTrig_h5841218e__0(vlSelf, 
                                                               "@(posedge tb_board_a_ctrl.clk)");
        co_await vlSelfRef.__VtrigSched_h5841218e__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_board_a_ctrl.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 
                                                             118);
        if (vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__p0) {
            tb_board_a_ctrl__DOT__unnamedblk1__DOT__p 
                = ((IData)(1U) + tb_board_a_ctrl__DOT__unnamedblk1__DOT__p);
        }
        tb_board_a_ctrl__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1 
            = (tb_board_a_ctrl__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1 
               - (IData)(1U));
    }
    __Vtask_tb_board_a_ctrl__DOT__check__9__pass = 
        (1U == tb_board_a_ctrl__DOT__unnamedblk1__DOT__p);
    vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__9__msg = "one start pulse"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_board_a_ctrl__DOT__check__9__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_board_a_ctrl.sv:66: Assertion failed in %Ntb_board_a_ctrl.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_board_a_ctrl__DOT__check__9__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 66, "");
        vlSelfRef.tb_board_a_ctrl__DOT__err_count = 
            ((IData)(1U) + vlSelfRef.tb_board_a_ctrl__DOT__err_count);
    }
    if ((0U == vlSelfRef.tb_board_a_ctrl__DOT__err_count)) {
        VL_WRITEF_NX("tb_board_a_ctrl: PASS (all checks passed)\n",0);
    } else {
        VL_WRITEF_NX("tb_board_a_ctrl: FAIL (%0d errors)\n",0,
                     32,vlSelfRef.tb_board_a_ctrl__DOT__err_count);
    }
    VL_FINISH_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 128, "");
    co_return;
}

VlCoroutine Vtb_board_a_ctrl___024root___eval_initial__TOP__Vtiming__2(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 
                                             35);
        vlSelfRef.tb_board_a_ctrl__DOT__clk = (1U & 
                                               (~ (IData)(vlSelfRef.tb_board_a_ctrl__DOT__clk)));
    }
    co_return;
}

void Vtb_board_a_ctrl___024root___eval_triggers_vec__act(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_triggers_vec__act\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((((IData)(vlSelfRef.tb_board_a_ctrl__DOT__rst_n) 
                                                        != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__rst_n__0)) 
                                                       << 3U) 
                                                      | (vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                         << 2U)) 
                                                     | ((((~ (IData)(vlSelfRef.tb_board_a_ctrl__DOT__rst_n)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__rst_n__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__clk__0 
        = vlSelfRef.tb_board_a_ctrl__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__rst_n__0 
        = vlSelfRef.tb_board_a_ctrl__DOT__rst_n;
}

bool Vtb_board_a_ctrl___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___trigger_anySet__act\n"); );
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

extern const VlUnpacked<CData/*2:0*/, 4> Vtb_board_a_ctrl__ConstPool__TABLE_h608c3c40_0;

void Vtb_board_a_ctrl___024root___act_comb__TOP__0(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___act_comb__TOP__0\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    vlSelfRef.tb_board_a_ctrl__DOT__regime_sw = (3U 
                                                 & (IData)(vlSelfRef.tb_board_a_ctrl__DOT__sw));
    vlSelfRef.tb_board_a_ctrl__DOT__sw_override = (1U 
                                                   & ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__sw) 
                                                      >> 2U));
    vlSelfRef.tb_board_a_ctrl__DOT__rgb1 = ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_up)
                                             ? ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_error)
                                                 ? 6U
                                                 : 2U)
                                             : 4U);
    __Vtableidx1 = vlSelfRef.tb_board_a_ctrl__DOT__active_regime;
    vlSelfRef.tb_board_a_ctrl__DOT__rgb0 = Vtb_board_a_ctrl__ConstPool__TABLE_h608c3c40_0
        [__Vtableidx1];
    vlSelfRef.tb_board_a_ctrl__DOT__led = ((((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_error) 
                                             << 5U) 
                                            | (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_up) 
                                                << 4U) 
                                               | (0x000007f8U 
                                                  & (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__running) 
                                                      << 3U) 
                                                     & (vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__blink_ctr 
                                                        >> 0x00000015U))))) 
                                           | (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__running) 
                                               << 2U) 
                                              | (IData)(vlSelfRef.tb_board_a_ctrl__DOT__active_regime)));
}

void Vtb_board_a_ctrl___024root___eval_act(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_act\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vinline__act_comb__TOP__0___Vtableidx1;
    __Vinline__act_comb__TOP__0___Vtableidx1 = 0;
    // Body
    if ((9ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.tb_board_a_ctrl__DOT__regime_sw = 
            (3U & (IData)(vlSelfRef.tb_board_a_ctrl__DOT__sw));
        vlSelfRef.tb_board_a_ctrl__DOT__sw_override 
            = (1U & ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__sw) 
                     >> 2U));
        vlSelfRef.tb_board_a_ctrl__DOT__rgb1 = ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_up)
                                                 ? 
                                                ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_error)
                                                  ? 6U
                                                  : 2U)
                                                 : 4U);
        __Vinline__act_comb__TOP__0___Vtableidx1 = vlSelfRef.tb_board_a_ctrl__DOT__active_regime;
        vlSelfRef.tb_board_a_ctrl__DOT__rgb0 = Vtb_board_a_ctrl__ConstPool__TABLE_h608c3c40_0
            [__Vinline__act_comb__TOP__0___Vtableidx1];
        vlSelfRef.tb_board_a_ctrl__DOT__led = ((((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_error) 
                                                 << 5U) 
                                                | (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_up) 
                                                    << 4U) 
                                                   | (0x000007f8U 
                                                      & (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__running) 
                                                          << 3U) 
                                                         & (vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__blink_ctr 
                                                            >> 0x00000015U))))) 
                                               | (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__running) 
                                                   << 2U) 
                                                  | (IData)(vlSelfRef.tb_board_a_ctrl__DOT__active_regime)));
    }
}

void Vtb_board_a_ctrl___024root___nba_sequent__TOP__0(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___nba_sequent__TOP__0\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vdly__tb_board_a_ctrl__DOT__dut__DOT__db0;
    __Vdly__tb_board_a_ctrl__DOT__dut__DOT__db0 = 0;
    CData/*5:0*/ __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter;
    __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter = 0;
    CData/*0:0*/ __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev;
    __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev = 0;
    // Body
    __Vdly__tb_board_a_ctrl__DOT__dut__DOT__db0 = vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__db0;
    __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter 
        = vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter;
    __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev 
        = vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev;
    if (vlSelfRef.tb_board_a_ctrl__DOT__rst_n) {
        vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__blink_ctr 
            = (0x01ffffffU & ((IData)(1U) + vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__blink_ctr));
        if (((1U & (IData)(vlSelfRef.tb_board_a_ctrl__DOT__btn)) 
             != (IData)(vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__db0))) {
            if ((0x20U == (IData)(vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter))) {
                __Vdly__tb_board_a_ctrl__DOT__dut__DOT__db0 
                    = (1U & (IData)(vlSelfRef.tb_board_a_ctrl__DOT__btn));
                __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter = 0U;
            } else {
                __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter 
                    = (0x0000003fU & ((IData)(1U) + (IData)(vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter)));
            }
        } else {
            __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter = 0U;
        }
        __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev 
            = vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__db0;
        vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__p0 
            = ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__db0) 
               & (~ (IData)(vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev)));
    } else {
        vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__blink_ctr = 0U;
        __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter = 0U;
        __Vdly__tb_board_a_ctrl__DOT__dut__DOT__db0 = 0U;
        __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev = 0U;
        vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__p0 = 0U;
    }
    vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__db0 = __Vdly__tb_board_a_ctrl__DOT__dut__DOT__db0;
    vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter 
        = __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter;
    vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev 
        = __Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev;
}

void Vtb_board_a_ctrl___024root___nba_comb__TOP__0(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___nba_comb__TOP__0\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    vlSelfRef.tb_board_a_ctrl__DOT__regime_sw = (3U 
                                                 & (IData)(vlSelfRef.tb_board_a_ctrl__DOT__sw));
    vlSelfRef.tb_board_a_ctrl__DOT__sw_override = (1U 
                                                   & ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__sw) 
                                                      >> 2U));
    vlSelfRef.tb_board_a_ctrl__DOT__rgb1 = ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_up)
                                             ? ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_error)
                                                 ? 6U
                                                 : 2U)
                                             : 4U);
    __Vtableidx1 = vlSelfRef.tb_board_a_ctrl__DOT__active_regime;
    vlSelfRef.tb_board_a_ctrl__DOT__rgb0 = Vtb_board_a_ctrl__ConstPool__TABLE_h608c3c40_0
        [__Vtableidx1];
}

void Vtb_board_a_ctrl___024root___nba_comb__TOP__1(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___nba_comb__TOP__1\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_board_a_ctrl__DOT__led = ((((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_error) 
                                             << 5U) 
                                            | (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_up) 
                                                << 4U) 
                                               | (0x000007f8U 
                                                  & (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__running) 
                                                      << 3U) 
                                                     & (vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__blink_ctr 
                                                        >> 0x00000015U))))) 
                                           | (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__running) 
                                               << 2U) 
                                              | (IData)(vlSelfRef.tb_board_a_ctrl__DOT__active_regime)));
}

void Vtb_board_a_ctrl___024root___eval_nba(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_nba\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__db0;
    __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__db0 = 0;
    CData/*5:0*/ __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter;
    __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter = 0;
    CData/*0:0*/ __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev;
    __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev = 0;
    CData/*1:0*/ __Vinline__nba_comb__TOP__0___Vtableidx1;
    __Vinline__nba_comb__TOP__0___Vtableidx1 = 0;
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__db0 
            = vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__db0;
        __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter 
            = vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter;
        __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev 
            = vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev;
        if (vlSelfRef.tb_board_a_ctrl__DOT__rst_n) {
            vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__blink_ctr 
                = (0x01ffffffU & ((IData)(1U) + vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__blink_ctr));
            if (((1U & (IData)(vlSelfRef.tb_board_a_ctrl__DOT__btn)) 
                 != (IData)(vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__db0))) {
                if ((0x20U == (IData)(vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter))) {
                    __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__db0 
                        = (1U & (IData)(vlSelfRef.tb_board_a_ctrl__DOT__btn));
                    __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter = 0U;
                } else {
                    __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter 
                        = (0x0000003fU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter)));
                }
            } else {
                __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter = 0U;
            }
            __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev 
                = vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__db0;
            vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__p0 
                = ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__db0) 
                   & (~ (IData)(vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev)));
        } else {
            vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__blink_ctr = 0U;
            __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter = 0U;
            __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__db0 = 0U;
            __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev = 0U;
            vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__p0 = 0U;
        }
        vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__db0 
            = __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__db0;
        vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter 
            = __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter;
        vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev 
            = __Vinline__nba_sequent__TOP__0___Vdly__tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev;
    }
    if ((9ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.tb_board_a_ctrl__DOT__regime_sw = 
            (3U & (IData)(vlSelfRef.tb_board_a_ctrl__DOT__sw));
        vlSelfRef.tb_board_a_ctrl__DOT__sw_override 
            = (1U & ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__sw) 
                     >> 2U));
        vlSelfRef.tb_board_a_ctrl__DOT__rgb1 = ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_up)
                                                 ? 
                                                ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_error)
                                                  ? 6U
                                                  : 2U)
                                                 : 4U);
        __Vinline__nba_comb__TOP__0___Vtableidx1 = vlSelfRef.tb_board_a_ctrl__DOT__active_regime;
        vlSelfRef.tb_board_a_ctrl__DOT__rgb0 = Vtb_board_a_ctrl__ConstPool__TABLE_h608c3c40_0
            [__Vinline__nba_comb__TOP__0___Vtableidx1];
    }
    if ((0x000000000000000bULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.tb_board_a_ctrl__DOT__led = ((((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_error) 
                                                 << 5U) 
                                                | (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_up) 
                                                    << 4U) 
                                                   | (0x000007f8U 
                                                      & (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__running) 
                                                          << 3U) 
                                                         & (vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__blink_ctr 
                                                            >> 0x00000015U))))) 
                                               | (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__running) 
                                                   << 2U) 
                                                  | (IData)(vlSelfRef.tb_board_a_ctrl__DOT__active_regime)));
    }
}

void Vtb_board_a_ctrl___024root___timing_ready(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___timing_ready\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h5841218e__0.ready("@(posedge tb_board_a_ctrl.clk)");
    }
    if ((8ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h5c2f6120__0.ready("@( tb_board_a_ctrl.rst_n)");
    }
}

void Vtb_board_a_ctrl___024root___timing_resume(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___timing_resume\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h5841218e__0.moveToResumeQueue(
                                                          "@(posedge tb_board_a_ctrl.clk)");
    vlSelfRef.__VtrigSched_h5c2f6120__0.moveToResumeQueue(
                                                          "@( tb_board_a_ctrl.rst_n)");
    vlSelfRef.__VtrigSched_h5841218e__0.resume("@(posedge tb_board_a_ctrl.clk)");
    vlSelfRef.__VtrigSched_h5c2f6120__0.resume("@( tb_board_a_ctrl.rst_n)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_board_a_ctrl___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vtb_board_a_ctrl___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_board_a_ctrl___024root___eval_phase__act(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_phase__act\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_board_a_ctrl___024root___eval_triggers_vec__act(vlSelf);
    Vtb_board_a_ctrl___024root___timing_ready(vlSelf);
    Vtb_board_a_ctrl___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_board_a_ctrl___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_board_a_ctrl___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_board_a_ctrl___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_board_a_ctrl___024root___timing_resume(vlSelf);
        Vtb_board_a_ctrl___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_board_a_ctrl___024root___eval_phase__inact(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_phase__inact\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 10, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_board_a_ctrl___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_board_a_ctrl___024root___eval_phase__nba(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_phase__nba\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_board_a_ctrl___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_board_a_ctrl___024root___eval_nba(vlSelf);
        Vtb_board_a_ctrl___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_board_a_ctrl___024root___eval(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_board_a_ctrl___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 10, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 10, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_board_a_ctrl___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 10, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_board_a_ctrl___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_board_a_ctrl___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_board_a_ctrl___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_board_a_ctrl___024root____VbeforeTrig_h5841218e__0(Vtb_board_a_ctrl___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root____VbeforeTrig_h5841218e__0\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_board_a_ctrl__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__clk__0 
        = vlSelfRef.tb_board_a_ctrl__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h5841218e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5841218e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5841218e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5841218e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5841218e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5841218e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5841218e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5841218e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5841218e__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_board_a_ctrl___024root____VbeforeTrig_h5c2f6120__0(Vtb_board_a_ctrl___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root____VbeforeTrig_h5c2f6120__0\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.tb_board_a_ctrl__DOT__rst_n) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__rst_n__0)) 
                                  << 3U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__rst_n__0 
        = vlSelfRef.tb_board_a_ctrl__DOT__rst_n;
    if ((8ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h5c2f6120__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_board_a_ctrl___024root___eval_debug_assertions(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_debug_assertions\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
