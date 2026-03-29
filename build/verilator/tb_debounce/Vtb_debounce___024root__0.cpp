// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_debounce.h for the primary calling header

#include "Vtb_debounce__pch.h"

VlCoroutine Vtb_debounce___024root___eval_initial__TOP__Vtiming__0(Vtb_debounce___024root* vlSelf);
VlCoroutine Vtb_debounce___024root___eval_initial__TOP__Vtiming__1(Vtb_debounce___024root* vlSelf);

void Vtb_debounce___024root___eval_initial(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_initial\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_debounce__DOT__clk = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_debounce.vcd"s);
    VL_PRINTF_MT("-Info: C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv:42: $dumpvar ignored, as Verilated without --trace\n");
    Vtb_debounce___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_debounce___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

void Vtb_debounce___024root____VbeforeTrig_h5a5a23e9__0(Vtb_debounce___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_debounce___024root___eval_initial__TOP__Vtiming__0(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_debounce__DOT__unnamedblk1__DOT__g;
    tb_debounce__DOT__unnamedblk1__DOT__g = 0;
    IData/*31:0*/ tb_debounce__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1;
    tb_debounce__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0;
    IData/*31:0*/ tb_debounce__DOT__unnamedblk1__DOT__unnamedblk1_3__DOT____Vrepeat2;
    tb_debounce__DOT__unnamedblk1__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ tb_debounce__DOT__unnamedblk1_4__DOT____Vrepeat3;
    tb_debounce__DOT__unnamedblk1_4__DOT____Vrepeat3 = 0;
    IData/*31:0*/ tb_debounce__DOT__unnamedblk1_5__DOT____Vrepeat4;
    tb_debounce__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0;
    IData/*31:0*/ tb_debounce__DOT__unnamedblk2__DOT__pulses;
    tb_debounce__DOT__unnamedblk2__DOT__pulses = 0;
    IData/*31:0*/ tb_debounce__DOT__unnamedblk2__DOT__unnamedblk3__DOT__i;
    tb_debounce__DOT__unnamedblk2__DOT__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ tb_debounce__DOT__unnamedblk4__DOT__pulses;
    tb_debounce__DOT__unnamedblk4__DOT__pulses = 0;
    IData/*31:0*/ tb_debounce__DOT__unnamedblk4__DOT__unnamedblk1_6__DOT____Vrepeat5;
    tb_debounce__DOT__unnamedblk4__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0;
    IData/*31:0*/ __Vtask_tb_debounce__DOT__wait_reset__0__tb_debounce__DOT__unnamedblk1_1__DOT____Vrepeat0;
    __Vtask_tb_debounce__DOT__wait_reset__0__tb_debounce__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    CData/*0:0*/ __Vtask_tb_debounce__DOT__check__1__pass;
    __Vtask_tb_debounce__DOT__check__1__pass = 0;
    CData/*0:0*/ __Vtask_tb_debounce__DOT__check__2__pass;
    __Vtask_tb_debounce__DOT__check__2__pass = 0;
    CData/*0:0*/ __Vtask_tb_debounce__DOT__check__3__pass;
    __Vtask_tb_debounce__DOT__check__3__pass = 0;
    CData/*0:0*/ __Vtask_tb_debounce__DOT__check__4__pass;
    __Vtask_tb_debounce__DOT__check__4__pass = 0;
    CData/*0:0*/ __Vtask_tb_debounce__DOT__check__5__pass;
    __Vtask_tb_debounce__DOT__check__5__pass = 0;
    CData/*0:0*/ __Vtask_tb_debounce__DOT__check__6__pass;
    __Vtask_tb_debounce__DOT__check__6__pass = 0;
    CData/*0:0*/ __Vtask_tb_debounce__DOT__check__7__pass;
    __Vtask_tb_debounce__DOT__check__7__pass = 0;
    // Body
    vlSelfRef.tb_debounce__DOT__rst_n = 0U;
    vlSelfRef.tb_debounce__DOT__btn_in = 0U;
    __Vtask_tb_debounce__DOT__wait_reset__0__tb_debounce__DOT__unnamedblk1_1__DOT____Vrepeat0 = 4U;
    while (VL_LTS_III(32, 0U, __Vtask_tb_debounce__DOT__wait_reset__0__tb_debounce__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vtb_debounce___024root____VbeforeTrig_h5a5a23e9__0(vlSelf, 
                                                           "@(posedge tb_debounce.clk)");
        co_await vlSelfRef.__VtrigSched_h5a5a23e9__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_debounce.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 
                                                             48);
        __Vtask_tb_debounce__DOT__wait_reset__0__tb_debounce__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (__Vtask_tb_debounce__DOT__wait_reset__0__tb_debounce__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.tb_debounce__DOT__rst_n = 1U;
    Vtb_debounce___024root____VbeforeTrig_h5a5a23e9__0(vlSelf, 
                                                       "@(posedge tb_debounce.clk)");
    co_await vlSelfRef.__VtrigSched_h5a5a23e9__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_debounce.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 
                                                         50);
    __Vtask_tb_debounce__DOT__check__1__pass = (1U 
                                                & (~ (IData)(vlSelfRef.tb_debounce__DOT__btn_out)));
    vlSelfRef.__Vtask_tb_debounce__DOT__check__1__msg = "After reset, btn_out=0"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_debounce__DOT__check__1__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_debounce.sv:35: Assertion failed in %Ntb_debounce.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_debounce__DOT__check__1__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 35, "");
        vlSelfRef.tb_debounce__DOT__err_count = ((IData)(1U) 
                                                 + vlSelfRef.tb_debounce__DOT__err_count);
    }
    __Vtask_tb_debounce__DOT__check__2__pass = (1U 
                                                & (~ (IData)(vlSelfRef.tb_debounce__DOT__btn_pulse)));
    vlSelfRef.__Vtask_tb_debounce__DOT__check__2__msg = "After reset, btn_pulse=0"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_debounce__DOT__check__2__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_debounce.sv:35: Assertion failed in %Ntb_debounce.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_debounce__DOT__check__2__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 35, "");
        vlSelfRef.tb_debounce__DOT__err_count = ((IData)(1U) 
                                                 + vlSelfRef.tb_debounce__DOT__err_count);
    }
    tb_debounce__DOT__unnamedblk1__DOT__g = 0U;
    while (VL_GTS_III(32, 0x0000000cU, tb_debounce__DOT__unnamedblk1__DOT__g)) {
        vlSelfRef.tb_debounce__DOT__btn_in = 1U;
        tb_debounce__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1 = 3U;
        while (VL_LTS_III(32, 0U, tb_debounce__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
            Vtb_debounce___024root____VbeforeTrig_h5a5a23e9__0(vlSelf, 
                                                               "@(posedge tb_debounce.clk)");
            co_await vlSelfRef.__VtrigSched_h5a5a23e9__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_debounce.clk)", 
                                                                 "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 
                                                                 61);
            tb_debounce__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1 
                = (tb_debounce__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1 
                   - (IData)(1U));
        }
        vlSelfRef.tb_debounce__DOT__btn_in = 0U;
        tb_debounce__DOT__unnamedblk1__DOT__unnamedblk1_3__DOT____Vrepeat2 = 3U;
        while (VL_LTS_III(32, 0U, tb_debounce__DOT__unnamedblk1__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
            Vtb_debounce___024root____VbeforeTrig_h5a5a23e9__0(vlSelf, 
                                                               "@(posedge tb_debounce.clk)");
            co_await vlSelfRef.__VtrigSched_h5a5a23e9__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_debounce.clk)", 
                                                                 "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 
                                                                 63);
            tb_debounce__DOT__unnamedblk1__DOT__unnamedblk1_3__DOT____Vrepeat2 
                = (tb_debounce__DOT__unnamedblk1__DOT__unnamedblk1_3__DOT____Vrepeat2 
                   - (IData)(1U));
        }
        tb_debounce__DOT__unnamedblk1__DOT__g = ((IData)(1U) 
                                                 + tb_debounce__DOT__unnamedblk1__DOT__g);
    }
    __Vtask_tb_debounce__DOT__check__3__pass = (1U 
                                                & (~ (IData)(vlSelfRef.tb_debounce__DOT__btn_out)));
    vlSelfRef.__Vtask_tb_debounce__DOT__check__3__msg = "After glitches, btn_out still 0"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_debounce__DOT__check__3__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_debounce.sv:35: Assertion failed in %Ntb_debounce.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_debounce__DOT__check__3__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 35, "");
        vlSelfRef.tb_debounce__DOT__err_count = ((IData)(1U) 
                                                 + vlSelfRef.tb_debounce__DOT__err_count);
    }
    vlSelfRef.tb_debounce__DOT__btn_in = 1U;
    tb_debounce__DOT__unnamedblk1_4__DOT____Vrepeat3 = 0x00000012U;
    while (VL_LTS_III(32, 0U, tb_debounce__DOT__unnamedblk1_4__DOT____Vrepeat3)) {
        Vtb_debounce___024root____VbeforeTrig_h5a5a23e9__0(vlSelf, 
                                                           "@(posedge tb_debounce.clk)");
        co_await vlSelfRef.__VtrigSched_h5a5a23e9__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_debounce.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 
                                                             69);
        tb_debounce__DOT__unnamedblk1_4__DOT____Vrepeat3 
            = (tb_debounce__DOT__unnamedblk1_4__DOT____Vrepeat3 
               - (IData)(1U));
    }
    __Vtask_tb_debounce__DOT__check__4__pass = vlSelfRef.tb_debounce__DOT__btn_out;
    vlSelfRef.__Vtask_tb_debounce__DOT__check__4__msg = "Stable high: btn_out should be 1"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_debounce__DOT__check__4__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_debounce.sv:35: Assertion failed in %Ntb_debounce.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_debounce__DOT__check__4__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 35, "");
        vlSelfRef.tb_debounce__DOT__err_count = ((IData)(1U) 
                                                 + vlSelfRef.tb_debounce__DOT__err_count);
    }
    vlSelfRef.tb_debounce__DOT__btn_in = 0U;
    tb_debounce__DOT__unnamedblk1_5__DOT____Vrepeat4 = 0x00000012U;
    while (VL_LTS_III(32, 0U, tb_debounce__DOT__unnamedblk1_5__DOT____Vrepeat4)) {
        Vtb_debounce___024root____VbeforeTrig_h5a5a23e9__0(vlSelf, 
                                                           "@(posedge tb_debounce.clk)");
        co_await vlSelfRef.__VtrigSched_h5a5a23e9__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_debounce.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 
                                                             74);
        tb_debounce__DOT__unnamedblk1_5__DOT____Vrepeat4 
            = (tb_debounce__DOT__unnamedblk1_5__DOT____Vrepeat4 
               - (IData)(1U));
    }
    __Vtask_tb_debounce__DOT__check__5__pass = (1U 
                                                & (~ (IData)(vlSelfRef.tb_debounce__DOT__btn_out)));
    vlSelfRef.__Vtask_tb_debounce__DOT__check__5__msg = "Stable low: btn_out should be 0"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_debounce__DOT__check__5__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_debounce.sv:35: Assertion failed in %Ntb_debounce.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_debounce__DOT__check__5__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 35, "");
        vlSelfRef.tb_debounce__DOT__err_count = ((IData)(1U) 
                                                 + vlSelfRef.tb_debounce__DOT__err_count);
    }
    tb_debounce__DOT__unnamedblk2__DOT__pulses = 0U;
    vlSelfRef.tb_debounce__DOT__btn_in = 1U;
    tb_debounce__DOT__unnamedblk2__DOT__unnamedblk3__DOT__i = 0U;
    while (VL_GTS_III(32, 0x0000001aU, tb_debounce__DOT__unnamedblk2__DOT__unnamedblk3__DOT__i)) {
        Vtb_debounce___024root____VbeforeTrig_h5a5a23e9__0(vlSelf, 
                                                           "@(posedge tb_debounce.clk)");
        co_await vlSelfRef.__VtrigSched_h5a5a23e9__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_debounce.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 
                                                             82);
        if (vlSelfRef.tb_debounce__DOT__btn_pulse) {
            tb_debounce__DOT__unnamedblk2__DOT__pulses 
                = ((IData)(1U) + tb_debounce__DOT__unnamedblk2__DOT__pulses);
        }
        tb_debounce__DOT__unnamedblk2__DOT__unnamedblk3__DOT__i 
            = ((IData)(1U) + tb_debounce__DOT__unnamedblk2__DOT__unnamedblk3__DOT__i);
    }
    __Vtask_tb_debounce__DOT__check__6__pass = (1U 
                                                == tb_debounce__DOT__unnamedblk2__DOT__pulses);
    vlSelfRef.__Vtask_tb_debounce__DOT__check__6__msg = "Rising debounce: exactly one btn_pulse"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_debounce__DOT__check__6__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_debounce.sv:35: Assertion failed in %Ntb_debounce.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_debounce__DOT__check__6__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 35, "");
        vlSelfRef.tb_debounce__DOT__err_count = ((IData)(1U) 
                                                 + vlSelfRef.tb_debounce__DOT__err_count);
    }
    tb_debounce__DOT__unnamedblk4__DOT__pulses = 0U;
    tb_debounce__DOT__unnamedblk4__DOT__unnamedblk1_6__DOT____Vrepeat5 = 0x00000028U;
    while (VL_LTS_III(32, 0U, tb_debounce__DOT__unnamedblk4__DOT__unnamedblk1_6__DOT____Vrepeat5)) {
        Vtb_debounce___024root____VbeforeTrig_h5a5a23e9__0(vlSelf, 
                                                           "@(posedge tb_debounce.clk)");
        co_await vlSelfRef.__VtrigSched_h5a5a23e9__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_debounce.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 
                                                             92);
        if (vlSelfRef.tb_debounce__DOT__btn_pulse) {
            tb_debounce__DOT__unnamedblk4__DOT__pulses 
                = ((IData)(1U) + tb_debounce__DOT__unnamedblk4__DOT__pulses);
        }
        tb_debounce__DOT__unnamedblk4__DOT__unnamedblk1_6__DOT____Vrepeat5 
            = (tb_debounce__DOT__unnamedblk4__DOT__unnamedblk1_6__DOT____Vrepeat5 
               - (IData)(1U));
    }
    __Vtask_tb_debounce__DOT__check__7__pass = (0U 
                                                == tb_debounce__DOT__unnamedblk4__DOT__pulses);
    vlSelfRef.__Vtask_tb_debounce__DOT__check__7__msg = "Held high: no extra pulses"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_debounce__DOT__check__7__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_debounce.sv:35: Assertion failed in %Ntb_debounce.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_debounce__DOT__check__7__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 35, "");
        vlSelfRef.tb_debounce__DOT__err_count = ((IData)(1U) 
                                                 + vlSelfRef.tb_debounce__DOT__err_count);
    }
    if ((0U == vlSelfRef.tb_debounce__DOT__err_count)) {
        VL_WRITEF_NX("tb_debounce: PASS (all checks passed, VCD: tb_debounce.vcd)\n",0);
    } else {
        VL_WRITEF_NX("tb_debounce: FAIL (%0d errors)\n",0,
                     32,vlSelfRef.tb_debounce__DOT__err_count);
    }
    VL_FINISH_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 103, "");
    co_return;
}

VlCoroutine Vtb_debounce___024root___eval_initial__TOP__Vtiming__1(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 
                                             23);
        vlSelfRef.tb_debounce__DOT__clk = (1U & (~ (IData)(vlSelfRef.tb_debounce__DOT__clk)));
    }
    co_return;
}

void Vtb_debounce___024root___eval_triggers_vec__act(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_triggers_vec__act\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 2U) 
                                                     | ((((~ (IData)(vlSelfRef.tb_debounce__DOT__rst_n)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_debounce__DOT__rst_n__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_debounce__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_debounce__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_debounce__DOT__clk__0 
        = vlSelfRef.tb_debounce__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_debounce__DOT__rst_n__0 
        = vlSelfRef.tb_debounce__DOT__rst_n;
}

bool Vtb_debounce___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___trigger_anySet__act\n"); );
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

void Vtb_debounce___024root___nba_sequent__TOP__0(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___nba_sequent__TOP__0\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vdly__tb_debounce__DOT__btn_out;
    __Vdly__tb_debounce__DOT__btn_out = 0;
    CData/*4:0*/ __Vdly__tb_debounce__DOT__dut__DOT__counter;
    __Vdly__tb_debounce__DOT__dut__DOT__counter = 0;
    CData/*0:0*/ __Vdly__tb_debounce__DOT__dut__DOT__btn_out_prev;
    __Vdly__tb_debounce__DOT__dut__DOT__btn_out_prev = 0;
    // Body
    __Vdly__tb_debounce__DOT__btn_out = vlSelfRef.tb_debounce__DOT__btn_out;
    __Vdly__tb_debounce__DOT__dut__DOT__counter = vlSelfRef.tb_debounce__DOT__dut__DOT__counter;
    __Vdly__tb_debounce__DOT__dut__DOT__btn_out_prev 
        = vlSelfRef.tb_debounce__DOT__dut__DOT__btn_out_prev;
    if (vlSelfRef.tb_debounce__DOT__rst_n) {
        if (((IData)(vlSelfRef.tb_debounce__DOT__btn_in) 
             != (IData)(vlSelfRef.tb_debounce__DOT__btn_out))) {
            if ((0x10U == (IData)(vlSelfRef.tb_debounce__DOT__dut__DOT__counter))) {
                __Vdly__tb_debounce__DOT__btn_out = vlSelfRef.tb_debounce__DOT__btn_in;
                __Vdly__tb_debounce__DOT__dut__DOT__counter = 0U;
            } else {
                __Vdly__tb_debounce__DOT__dut__DOT__counter 
                    = (0x0000001fU & ((IData)(1U) + (IData)(vlSelfRef.tb_debounce__DOT__dut__DOT__counter)));
            }
        } else {
            __Vdly__tb_debounce__DOT__dut__DOT__counter = 0U;
        }
        __Vdly__tb_debounce__DOT__dut__DOT__btn_out_prev 
            = vlSelfRef.tb_debounce__DOT__btn_out;
        vlSelfRef.tb_debounce__DOT__btn_pulse = ((IData)(vlSelfRef.tb_debounce__DOT__btn_out) 
                                                 & (~ (IData)(vlSelfRef.tb_debounce__DOT__dut__DOT__btn_out_prev)));
    } else {
        __Vdly__tb_debounce__DOT__dut__DOT__counter = 0U;
        __Vdly__tb_debounce__DOT__btn_out = 0U;
        __Vdly__tb_debounce__DOT__dut__DOT__btn_out_prev = 0U;
        vlSelfRef.tb_debounce__DOT__btn_pulse = 0U;
    }
    vlSelfRef.tb_debounce__DOT__btn_out = __Vdly__tb_debounce__DOT__btn_out;
    vlSelfRef.tb_debounce__DOT__dut__DOT__counter = __Vdly__tb_debounce__DOT__dut__DOT__counter;
    vlSelfRef.tb_debounce__DOT__dut__DOT__btn_out_prev 
        = __Vdly__tb_debounce__DOT__dut__DOT__btn_out_prev;
}

void Vtb_debounce___024root___eval_nba(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_nba\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__btn_out;
    __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__btn_out = 0;
    CData/*4:0*/ __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__counter;
    __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__counter = 0;
    CData/*0:0*/ __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__btn_out_prev;
    __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__btn_out_prev = 0;
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__btn_out 
            = vlSelfRef.tb_debounce__DOT__btn_out;
        __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__counter 
            = vlSelfRef.tb_debounce__DOT__dut__DOT__counter;
        __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__btn_out_prev 
            = vlSelfRef.tb_debounce__DOT__dut__DOT__btn_out_prev;
        if (vlSelfRef.tb_debounce__DOT__rst_n) {
            if (((IData)(vlSelfRef.tb_debounce__DOT__btn_in) 
                 != (IData)(vlSelfRef.tb_debounce__DOT__btn_out))) {
                if ((0x10U == (IData)(vlSelfRef.tb_debounce__DOT__dut__DOT__counter))) {
                    __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__btn_out 
                        = vlSelfRef.tb_debounce__DOT__btn_in;
                    __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__counter = 0U;
                } else {
                    __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__counter 
                        = (0x0000001fU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.tb_debounce__DOT__dut__DOT__counter)));
                }
            } else {
                __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__counter = 0U;
            }
            __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__btn_out_prev 
                = vlSelfRef.tb_debounce__DOT__btn_out;
            vlSelfRef.tb_debounce__DOT__btn_pulse = 
                ((IData)(vlSelfRef.tb_debounce__DOT__btn_out) 
                 & (~ (IData)(vlSelfRef.tb_debounce__DOT__dut__DOT__btn_out_prev)));
        } else {
            __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__counter = 0U;
            __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__btn_out = 0U;
            __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__btn_out_prev = 0U;
            vlSelfRef.tb_debounce__DOT__btn_pulse = 0U;
        }
        vlSelfRef.tb_debounce__DOT__btn_out = __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__btn_out;
        vlSelfRef.tb_debounce__DOT__dut__DOT__counter 
            = __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__counter;
        vlSelfRef.tb_debounce__DOT__dut__DOT__btn_out_prev 
            = __Vinline__nba_sequent__TOP__0___Vdly__tb_debounce__DOT__dut__DOT__btn_out_prev;
    }
}

void Vtb_debounce___024root___timing_ready(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___timing_ready\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h5a5a23e9__0.ready("@(posedge tb_debounce.clk)");
    }
}

void Vtb_debounce___024root___timing_resume(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___timing_resume\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h5a5a23e9__0.moveToResumeQueue(
                                                          "@(posedge tb_debounce.clk)");
    vlSelfRef.__VtrigSched_h5a5a23e9__0.resume("@(posedge tb_debounce.clk)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_debounce___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vtb_debounce___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_debounce___024root___eval_phase__act(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_phase__act\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_debounce___024root___eval_triggers_vec__act(vlSelf);
    Vtb_debounce___024root___timing_ready(vlSelf);
    Vtb_debounce___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_debounce___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_debounce___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_debounce___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_debounce___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_debounce___024root___eval_phase__inact(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_phase__inact\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 9, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_debounce___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_debounce___024root___eval_phase__nba(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_phase__nba\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_debounce___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_debounce___024root___eval_nba(vlSelf);
        Vtb_debounce___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_debounce___024root___eval(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_debounce___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 9, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 9, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_debounce___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv", 9, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_debounce___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_debounce___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_debounce___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_debounce___024root____VbeforeTrig_h5a5a23e9__0(Vtb_debounce___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root____VbeforeTrig_h5a5a23e9__0\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_debounce__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_debounce__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_debounce__DOT__clk__0 
        = vlSelfRef.tb_debounce__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h5a5a23e9__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5a5a23e9__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5a5a23e9__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5a5a23e9__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5a5a23e9__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5a5a23e9__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5a5a23e9__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5a5a23e9__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_debounce___024root___eval_debug_assertions(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_debug_assertions\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
