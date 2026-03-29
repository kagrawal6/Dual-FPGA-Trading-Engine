// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_lfsr32.h for the primary calling header

#include "Vtb_lfsr32__pch.h"

VlCoroutine Vtb_lfsr32___024root___eval_initial__TOP__Vtiming__0(Vtb_lfsr32___024root* vlSelf);
VlCoroutine Vtb_lfsr32___024root___eval_initial__TOP__Vtiming__1(Vtb_lfsr32___024root* vlSelf);

void Vtb_lfsr32___024root___eval_initial(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_initial\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_lfsr32__DOT__clk = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_lfsr32.vcd"s);
    VL_PRINTF_MT("-Info: C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv:65: $dumpvar ignored, as Verilated without --trace\n");
    Vtb_lfsr32___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_lfsr32___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

void Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(Vtb_lfsr32___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_lfsr32___024root___eval_initial__TOP__Vtiming__0(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vtask_tb_lfsr32__DOT__wait_reset__0__tb_lfsr32__DOT__unnamedblk1_1__DOT____Vrepeat0;
    __Vtask_tb_lfsr32__DOT__wait_reset__0__tb_lfsr32__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    CData/*0:0*/ __Vtask_tb_lfsr32__DOT__check__2__pass;
    __Vtask_tb_lfsr32__DOT__check__2__pass = 0;
    IData/*31:0*/ __Vtask_tb_lfsr32__DOT__run_load_hold_check__3__tb_lfsr32__DOT__unnamedblk1_2__DOT____Vrepeat1;
    __Vtask_tb_lfsr32__DOT__run_load_hold_check__3__tb_lfsr32__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0;
    CData/*0:0*/ __Vtask_tb_lfsr32__DOT__check__4__pass;
    __Vtask_tb_lfsr32__DOT__check__4__pass = 0;
    CData/*0:0*/ __Vtask_tb_lfsr32__DOT__check__5__pass;
    __Vtask_tb_lfsr32__DOT__check__5__pass = 0;
    IData/*31:0*/ __Vtask_tb_lfsr32__DOT__run_golden_check__6__k;
    __Vtask_tb_lfsr32__DOT__run_golden_check__6__k = 0;
    CData/*0:0*/ __Vtask_tb_lfsr32__DOT__check__7__pass;
    __Vtask_tb_lfsr32__DOT__check__7__pass = 0;
    IData/*31:0*/ __Vtask_tb_lfsr32__DOT__run_never_zero_stress__8__i;
    __Vtask_tb_lfsr32__DOT__run_never_zero_stress__8__i = 0;
    CData/*0:0*/ __Vtask_tb_lfsr32__DOT__check__9__pass;
    __Vtask_tb_lfsr32__DOT__check__9__pass = 0;
    CData/*0:0*/ __Vtask_tb_lfsr32__DOT__check__11__pass;
    __Vtask_tb_lfsr32__DOT__check__11__pass = 0;
    IData/*31:0*/ __Vtask_tb_lfsr32__DOT__run_determinism_check__12____Vlvbound_hacef8f96__0;
    __Vtask_tb_lfsr32__DOT__run_determinism_check__12____Vlvbound_hacef8f96__0 = 0;
    VlUnpacked<IData/*31:0*/, 10> __Vtask_tb_lfsr32__DOT__run_determinism_check__12__seq;
    for (int __Vi0 = 0; __Vi0 < 10; ++__Vi0) {
        __Vtask_tb_lfsr32__DOT__run_determinism_check__12__seq[__Vi0] = 0;
    }
    IData/*31:0*/ __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i;
    __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i = 0;
    CData/*0:0*/ __Vtask_tb_lfsr32__DOT__check__13__pass;
    __Vtask_tb_lfsr32__DOT__check__13__pass = 0;
    // Body
    vlSelfRef.tb_lfsr32__DOT__rst_n = 0U;
    vlSelfRef.tb_lfsr32__DOT__enable = 0U;
    vlSelfRef.tb_lfsr32__DOT__load = 0U;
    vlSelfRef.tb_lfsr32__DOT__seed_in = 0U;
    __Vtask_tb_lfsr32__DOT__wait_reset__0__tb_lfsr32__DOT__unnamedblk1_1__DOT____Vrepeat0 = 4U;
    while (VL_LTS_III(32, 0U, __Vtask_tb_lfsr32__DOT__wait_reset__0__tb_lfsr32__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                         "@(posedge tb_lfsr32.clk)");
        co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_lfsr32.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                             73);
        __Vtask_tb_lfsr32__DOT__wait_reset__0__tb_lfsr32__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (__Vtask_tb_lfsr32__DOT__wait_reset__0__tb_lfsr32__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.tb_lfsr32__DOT__rst_n = 1U;
    Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                     "@(posedge tb_lfsr32.clk)");
    co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_lfsr32.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                         75);
    __Vtask_tb_lfsr32__DOT__check__2__pass = (1U == vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg);
    vlSelfRef.__Vtask_tb_lfsr32__DOT__check__2__msg = "After async reset, state must be 1"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_lfsr32__DOT__check__2__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_lfsr32.sv:57: Assertion failed in %Ntb_lfsr32.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_lfsr32__DOT__check__2__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 57, "");
        vlSelfRef.tb_lfsr32__DOT__err_count = ((IData)(1U) 
                                               + vlSelfRef.tb_lfsr32__DOT__err_count);
    }
    __Vtask_tb_lfsr32__DOT__run_load_hold_check__3__tb_lfsr32__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0;
    vlSelfRef.tb_lfsr32__DOT__seed_in = 0xcafebabeU;
    vlSelfRef.tb_lfsr32__DOT__load = 1U;
    Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                     "@(posedge tb_lfsr32.clk)");
    co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_lfsr32.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                         86);
    vlSelfRef.tb_lfsr32__DOT__load = 0U;
    Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                     "@(posedge tb_lfsr32.clk)");
    co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_lfsr32.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                         88);
    __Vtask_tb_lfsr32__DOT__check__4__pass = (0xcafebabeU 
                                              == vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg);
    vlSelfRef.__Vtask_tb_lfsr32__DOT__check__4__msg = "After load, rand_out must match seed"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_lfsr32__DOT__check__4__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_lfsr32.sv:57: Assertion failed in %Ntb_lfsr32.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_lfsr32__DOT__check__4__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 57, "");
        vlSelfRef.tb_lfsr32__DOT__err_count = ((IData)(1U) 
                                               + vlSelfRef.tb_lfsr32__DOT__err_count);
    }
    __Vtask_tb_lfsr32__DOT__run_load_hold_check__3__tb_lfsr32__DOT__unnamedblk1_2__DOT____Vrepeat1 = 3U;
    while (VL_LTS_III(32, 0U, __Vtask_tb_lfsr32__DOT__run_load_hold_check__3__tb_lfsr32__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
        Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                         "@(posedge tb_lfsr32.clk)");
        co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_lfsr32.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                             91);
        __Vtask_tb_lfsr32__DOT__run_load_hold_check__3__tb_lfsr32__DOT__unnamedblk1_2__DOT____Vrepeat1 
            = (__Vtask_tb_lfsr32__DOT__run_load_hold_check__3__tb_lfsr32__DOT__unnamedblk1_2__DOT____Vrepeat1 
               - (IData)(1U));
    }
    __Vtask_tb_lfsr32__DOT__check__5__pass = (0xcafebabeU 
                                              == vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg);
    vlSelfRef.__Vtask_tb_lfsr32__DOT__check__5__msg = "With enable low, state must hold"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_lfsr32__DOT__check__5__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_lfsr32.sv:57: Assertion failed in %Ntb_lfsr32.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_lfsr32__DOT__check__5__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 57, "");
        vlSelfRef.tb_lfsr32__DOT__err_count = ((IData)(1U) 
                                               + vlSelfRef.tb_lfsr32__DOT__err_count);
    }
    __Vtask_tb_lfsr32__DOT__run_golden_check__6__k = 0U;
    vlSelfRef.tb_lfsr32__DOT__enable = 0U;
    vlSelfRef.tb_lfsr32__DOT__seed_in = 1U;
    vlSelfRef.tb_lfsr32__DOT__load = 1U;
    Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                     "@(posedge tb_lfsr32.clk)");
    co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_lfsr32.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                         100);
    vlSelfRef.tb_lfsr32__DOT__load = 0U;
    Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                     "@(posedge tb_lfsr32.clk)");
    co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_lfsr32.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                         102);
    __Vtask_tb_lfsr32__DOT__run_golden_check__6__k = 0U;
    while (VL_GTS_III(32, 8U, __Vtask_tb_lfsr32__DOT__run_golden_check__6__k)) {
        __Vtask_tb_lfsr32__DOT__check__7__pass = (vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg 
                                                  == vlSelfRef.tb_lfsr32__DOT__GOLDEN_AFTER_SEED1
                                                  [
                                                  (7U 
                                                   & __Vtask_tb_lfsr32__DOT__run_golden_check__6__k)]);
        vlSelfRef.__Vtask_tb_lfsr32__DOT__check__7__msg 
            = VL_SFORMATF_N_NX("Golden vector %0d: exp %08x got %08x",0,
                               32,__Vtask_tb_lfsr32__DOT__run_golden_check__6__k,
                               32,vlSelfRef.tb_lfsr32__DOT__GOLDEN_AFTER_SEED1
                               [(7U & __Vtask_tb_lfsr32__DOT__run_golden_check__6__k)],
                               32,vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_lfsr32__DOT__check__7__pass)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_lfsr32.sv:57: Assertion failed in %Ntb_lfsr32.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_lfsr32__DOT__check__7__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 57, "");
            vlSelfRef.tb_lfsr32__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_lfsr32__DOT__err_count);
        }
        if ((7U != __Vtask_tb_lfsr32__DOT__run_golden_check__6__k)) {
            vlSelfRef.tb_lfsr32__DOT__enable = 1U;
            Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                             "@(posedge tb_lfsr32.clk)");
            co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_lfsr32.clk)", 
                                                                 "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                                 110);
        }
        __Vtask_tb_lfsr32__DOT__run_golden_check__6__k 
            = ((IData)(1U) + __Vtask_tb_lfsr32__DOT__run_golden_check__6__k);
    }
    vlSelfRef.tb_lfsr32__DOT__enable = 0U;
    __Vtask_tb_lfsr32__DOT__run_never_zero_stress__8__i = 0U;
    vlSelfRef.tb_lfsr32__DOT__seed_in = 0xdeadbeefU;
    vlSelfRef.tb_lfsr32__DOT__load = 1U;
    Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                     "@(posedge tb_lfsr32.clk)");
    co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_lfsr32.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                         120);
    vlSelfRef.tb_lfsr32__DOT__load = 0U;
    vlSelfRef.tb_lfsr32__DOT__enable = 1U;
    __Vtask_tb_lfsr32__DOT__run_never_zero_stress__8__i = 0U;
    while (VL_GTS_III(32, 0x000001f4U, __Vtask_tb_lfsr32__DOT__run_never_zero_stress__8__i)) {
        Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                         "@(posedge tb_lfsr32.clk)");
        co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_lfsr32.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                             124);
        __Vtask_tb_lfsr32__DOT__check__9__pass = (0U 
                                                  != vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg);
        vlSelfRef.__Vtask_tb_lfsr32__DOT__check__9__msg 
            = VL_SFORMATF_N_NX("Stress cycle %0d: output non-zero",0,
                               32,__Vtask_tb_lfsr32__DOT__run_never_zero_stress__8__i) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_lfsr32__DOT__check__9__pass)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_lfsr32.sv:57: Assertion failed in %Ntb_lfsr32.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_lfsr32__DOT__check__9__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 57, "");
            vlSelfRef.tb_lfsr32__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_lfsr32__DOT__err_count);
        }
        __Vtask_tb_lfsr32__DOT__run_never_zero_stress__8__i 
            = ((IData)(1U) + __Vtask_tb_lfsr32__DOT__run_never_zero_stress__8__i);
    }
    vlSelfRef.tb_lfsr32__DOT__enable = 0U;
    vlSelfRef.tb_lfsr32__DOT__seed_in = 0U;
    vlSelfRef.tb_lfsr32__DOT__load = 1U;
    Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                     "@(posedge tb_lfsr32.clk)");
    co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_lfsr32.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                         133);
    vlSelfRef.tb_lfsr32__DOT__load = 0U;
    Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                     "@(posedge tb_lfsr32.clk)");
    co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_lfsr32.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                         135);
    __Vtask_tb_lfsr32__DOT__check__11__pass = (1U == vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg);
    vlSelfRef.__Vtask_tb_lfsr32__DOT__check__11__msg = "Zero seed remapped to 1"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_lfsr32__DOT__check__11__pass)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_lfsr32.sv:57: Assertion failed in %Ntb_lfsr32.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_lfsr32__DOT__check__11__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 57, "");
        vlSelfRef.tb_lfsr32__DOT__err_count = ((IData)(1U) 
                                               + vlSelfRef.tb_lfsr32__DOT__err_count);
    }
    __Vtask_tb_lfsr32__DOT__run_determinism_check__12____Vlvbound_hacef8f96__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 10; ++__Vi0) {
        __Vtask_tb_lfsr32__DOT__run_determinism_check__12__seq[__Vi0] = 0;
    }
    __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i = 0U;
    vlSelfRef.tb_lfsr32__DOT__seed_in = 0xa5a55a5aU;
    vlSelfRef.tb_lfsr32__DOT__load = 1U;
    Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                     "@(posedge tb_lfsr32.clk)");
    co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_lfsr32.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                         144);
    vlSelfRef.tb_lfsr32__DOT__load = 0U;
    vlSelfRef.tb_lfsr32__DOT__enable = 1U;
    __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i = 0U;
    while (VL_GTS_III(32, 0x0000000aU, __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i)) {
        Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                         "@(posedge tb_lfsr32.clk)");
        co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_lfsr32.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                             148);
        __Vtask_tb_lfsr32__DOT__run_determinism_check__12____Vlvbound_hacef8f96__0 
            = vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg;
        if (VL_LIKELY(((9U >= (0x0000000fU & __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i))))) {
            __Vtask_tb_lfsr32__DOT__run_determinism_check__12__seq[(0x0000000fU 
                                                                    & __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i)] 
                = __Vtask_tb_lfsr32__DOT__run_determinism_check__12____Vlvbound_hacef8f96__0;
        }
        __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i 
            = ((IData)(1U) + __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i);
    }
    vlSelfRef.tb_lfsr32__DOT__enable = 0U;
    vlSelfRef.tb_lfsr32__DOT__seed_in = 0xa5a55a5aU;
    vlSelfRef.tb_lfsr32__DOT__load = 1U;
    Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                     "@(posedge tb_lfsr32.clk)");
    co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_lfsr32.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                         155);
    vlSelfRef.tb_lfsr32__DOT__load = 0U;
    vlSelfRef.tb_lfsr32__DOT__enable = 1U;
    __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i = 0U;
    while (VL_GTS_III(32, 0x0000000aU, __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i)) {
        Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(vlSelf, 
                                                         "@(posedge tb_lfsr32.clk)");
        co_await vlSelfRef.__VtrigSched_hb706121e__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_lfsr32.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                                             159);
        __Vtask_tb_lfsr32__DOT__check__13__pass = (vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg 
                                                   == 
                                                   ((9U 
                                                     >= 
                                                     (0x0000000fU 
                                                      & __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i))
                                                     ? __Vtask_tb_lfsr32__DOT__run_determinism_check__12__seq
                                                    [
                                                    (0x0000000fU 
                                                     & __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i)]
                                                     : 0U));
        vlSelfRef.__Vtask_tb_lfsr32__DOT__check__13__msg 
            = VL_SFORMATF_N_NX("Determinism idx %0d",0,
                               32,__Vtask_tb_lfsr32__DOT__run_determinism_check__12__i) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_lfsr32__DOT__check__13__pass)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_lfsr32.sv:57: Assertion failed in %Ntb_lfsr32.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_lfsr32__DOT__check__13__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 57, "");
            vlSelfRef.tb_lfsr32__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_lfsr32__DOT__err_count);
        }
        __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i 
            = ((IData)(1U) + __Vtask_tb_lfsr32__DOT__run_determinism_check__12__i);
    }
    vlSelfRef.tb_lfsr32__DOT__enable = 0U;
    if ((0U == vlSelfRef.tb_lfsr32__DOT__err_count)) {
        VL_WRITEF_NX("tb_lfsr32: PASS (all checks passed, VCD: tb_lfsr32.vcd)\n",0);
    } else {
        VL_WRITEF_NX("tb_lfsr32: FAIL (%0d errors)\n",0,
                     32,vlSelfRef.tb_lfsr32__DOT__err_count);
    }
    VL_FINISH_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 180, "");
    co_return;
}

VlCoroutine Vtb_lfsr32___024root___eval_initial__TOP__Vtiming__1(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 
                                             29);
        vlSelfRef.tb_lfsr32__DOT__clk = (1U & (~ (IData)(vlSelfRef.tb_lfsr32__DOT__clk)));
    }
    co_return;
}

void Vtb_lfsr32___024root___eval_triggers_vec__act(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_triggers_vec__act\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 2U) 
                                                     | ((((~ (IData)(vlSelfRef.tb_lfsr32__DOT__rst_n)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_lfsr32__DOT__rst_n__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_lfsr32__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_lfsr32__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_lfsr32__DOT__clk__0 
        = vlSelfRef.tb_lfsr32__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_lfsr32__DOT__rst_n__0 
        = vlSelfRef.tb_lfsr32__DOT__rst_n;
}

bool Vtb_lfsr32___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___trigger_anySet__act\n"); );
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

void Vtb_lfsr32___024root___nba_sequent__TOP__0(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___nba_sequent__TOP__0\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg;
    __Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg = 0;
    // Body
    __Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg = vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg;
    if (vlSelfRef.tb_lfsr32__DOT__rst_n) {
        if (vlSelfRef.tb_lfsr32__DOT__load) {
            __Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg 
                = ((0U == vlSelfRef.tb_lfsr32__DOT__seed_in)
                    ? 1U : vlSelfRef.tb_lfsr32__DOT__seed_in);
        } else if (vlSelfRef.tb_lfsr32__DOT__enable) {
            __Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg 
                = ((1U & vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg)
                    ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg, 1U))
                    : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg, 1U));
        }
    } else {
        __Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg = 1U;
    }
    vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg = __Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg;
}

void Vtb_lfsr32___024root___eval_nba(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_nba\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vinline__nba_sequent__TOP__0___Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg;
    __Vinline__nba_sequent__TOP__0___Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg = 0;
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_sequent__TOP__0___Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg 
            = vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg;
        if (vlSelfRef.tb_lfsr32__DOT__rst_n) {
            if (vlSelfRef.tb_lfsr32__DOT__load) {
                __Vinline__nba_sequent__TOP__0___Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg 
                    = ((0U == vlSelfRef.tb_lfsr32__DOT__seed_in)
                        ? 1U : vlSelfRef.tb_lfsr32__DOT__seed_in);
            } else if (vlSelfRef.tb_lfsr32__DOT__enable) {
                __Vinline__nba_sequent__TOP__0___Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg, 1U));
            }
        } else {
            __Vinline__nba_sequent__TOP__0___Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg = 1U;
        }
        vlSelfRef.tb_lfsr32__DOT__dut__DOT__lfsr_reg 
            = __Vinline__nba_sequent__TOP__0___Vdly__tb_lfsr32__DOT__dut__DOT__lfsr_reg;
    }
}

void Vtb_lfsr32___024root___timing_ready(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___timing_ready\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_hb706121e__0.ready("@(posedge tb_lfsr32.clk)");
    }
}

void Vtb_lfsr32___024root___timing_resume(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___timing_resume\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_hb706121e__0.moveToResumeQueue(
                                                          "@(posedge tb_lfsr32.clk)");
    vlSelfRef.__VtrigSched_hb706121e__0.resume("@(posedge tb_lfsr32.clk)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_lfsr32___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vtb_lfsr32___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_lfsr32___024root___eval_phase__act(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_phase__act\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_lfsr32___024root___eval_triggers_vec__act(vlSelf);
    Vtb_lfsr32___024root___timing_ready(vlSelf);
    Vtb_lfsr32___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_lfsr32___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_lfsr32___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_lfsr32___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_lfsr32___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_lfsr32___024root___eval_phase__inact(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_phase__inact\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 16, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_lfsr32___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_lfsr32___024root___eval_phase__nba(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_phase__nba\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_lfsr32___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_lfsr32___024root___eval_nba(vlSelf);
        Vtb_lfsr32___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_lfsr32___024root___eval(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_lfsr32___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 16, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 16, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_lfsr32___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv", 16, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_lfsr32___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_lfsr32___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_lfsr32___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0(Vtb_lfsr32___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root____VbeforeTrig_hb706121e__0\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_lfsr32__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_lfsr32__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_lfsr32__DOT__clk__0 
        = vlSelfRef.tb_lfsr32__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hb706121e__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_lfsr32___024root___eval_debug_assertions(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_debug_assertions\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
