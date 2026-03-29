// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_sync_fifo.h for the primary calling header

#include "Vtb_sync_fifo__pch.h"

VlCoroutine Vtb_sync_fifo___024root___eval_initial__TOP__Vtiming__0(Vtb_sync_fifo___024root* vlSelf);
VlCoroutine Vtb_sync_fifo___024root___eval_initial__TOP__Vtiming__1(Vtb_sync_fifo___024root* vlSelf);
VlCoroutine Vtb_sync_fifo___024root___eval_initial__TOP__Vtiming__2(Vtb_sync_fifo___024root* vlSelf);

void Vtb_sync_fifo___024root___eval_initial(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_initial\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_sync_fifo__DOT__clk = 0U;
    Vtb_sync_fifo___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_sync_fifo___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_sync_fifo___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

VlCoroutine Vtb_sync_fifo___024root___eval_initial__TOP__Vtiming__0(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_sync_fifo__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000186a0ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                         31);
    vlSelfRef.tb_sync_fifo__DOT__rst_n = 1U;
    co_return;
}

void Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(Vtb_sync_fifo___024root* vlSelf, const char* __VeventDescription);
void Vtb_sync_fifo___024root____VbeforeTrig_hb2fb5223__0(Vtb_sync_fifo___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_sync_fifo___024root___eval_initial__TOP__Vtiming__1(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_sync_fifo__DOT__unnamedblk1__DOT__i;
    tb_sync_fifo__DOT__unnamedblk1__DOT__i = 0;
    IData/*31:0*/ tb_sync_fifo__DOT__unnamedblk2__DOT__i;
    tb_sync_fifo__DOT__unnamedblk2__DOT__i = 0;
    IData/*31:0*/ tb_sync_fifo__DOT__unnamedblk3__DOT__i;
    tb_sync_fifo__DOT__unnamedblk3__DOT__i = 0;
    IData/*31:0*/ tb_sync_fifo__DOT__unnamedblk4__DOT__j;
    tb_sync_fifo__DOT__unnamedblk4__DOT__j = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__0__cond;
    __Vtask_tb_sync_fifo__DOT__check__0__cond = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__1__cond;
    __Vtask_tb_sync_fifo__DOT__check__1__cond = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__2__cond;
    __Vtask_tb_sync_fifo__DOT__check__2__cond = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__3__cond;
    __Vtask_tb_sync_fifo__DOT__check__3__cond = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__4__cond;
    __Vtask_tb_sync_fifo__DOT__check__4__cond = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__5__cond;
    __Vtask_tb_sync_fifo__DOT__check__5__cond = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__6__cond;
    __Vtask_tb_sync_fifo__DOT__check__6__cond = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__7__cond;
    __Vtask_tb_sync_fifo__DOT__check__7__cond = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__8__cond;
    __Vtask_tb_sync_fifo__DOT__check__8__cond = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__9__cond;
    __Vtask_tb_sync_fifo__DOT__check__9__cond = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__10__cond;
    __Vtask_tb_sync_fifo__DOT__check__10__cond = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__11__cond;
    __Vtask_tb_sync_fifo__DOT__check__11__cond = 0;
    CData/*0:0*/ __Vtask_tb_sync_fifo__DOT__check__12__cond;
    __Vtask_tb_sync_fifo__DOT__check__12__cond = 0;
    VlWide<4>/*127:0*/ __Vtemp_1;
    VlWide<4>/*127:0*/ __Vtemp_2;
    VlWide<4>/*127:0*/ __Vtemp_3;
    VlWide<4>/*127:0*/ __Vtemp_4;
    VlWide<4>/*127:0*/ __Vtemp_5;
    // Body
    vlSelfRef.tb_sync_fifo__DOT__flush = 0U;
    vlSelfRef.tb_sync_fifo__DOT__wr_en = 0U;
    vlSelfRef.tb_sync_fifo__DOT__rd_en = 0U;
    vlSelfRef.tb_sync_fifo__DOT__wr_data[0U] = 0U;
    vlSelfRef.tb_sync_fifo__DOT__wr_data[1U] = 0U;
    vlSelfRef.tb_sync_fifo__DOT__wr_data[2U] = 0U;
    vlSelfRef.tb_sync_fifo__DOT__wr_data[3U] = 0U;
    Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                        "@(posedge tb_sync_fifo.clk)");
    co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_sync_fifo.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                         66);
    while ((1U & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__rst_n)))) {
        Vtb_sync_fifo___024root____VbeforeTrig_hb2fb5223__0(vlSelf, 
                                                            "@( tb_sync_fifo.rst_n)");
        co_await vlSelfRef.__VtrigSched_hb2fb5223__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_sync_fifo.rst_n)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                             67);
    }
    Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                        "@(posedge tb_sync_fifo.clk)");
    co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_sync_fifo.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                         68);
    __Vtask_tb_sync_fifo__DOT__check__0__cond = (IData)(
                                                        (0U 
                                                         == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r)));
    vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__0__msg = "empty after reset"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__0__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__0__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
        vlSelfRef.tb_sync_fifo__DOT__err_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    __Vtask_tb_sync_fifo__DOT__check__1__cond = (0x40U 
                                                 != (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
    vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__1__msg = "!full after reset"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__1__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__1__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
        vlSelfRef.tb_sync_fifo__DOT__err_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    tb_sync_fifo__DOT__unnamedblk1__DOT__i = 1U;
    while (VL_GTES_III(32, 5U, tb_sync_fifo__DOT__unnamedblk1__DOT__i)) {
        Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                            "@(posedge tb_sync_fifo.clk)");
        co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_sync_fifo.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                             75);
        __Vtemp_1[0U] = 0x10000001U;
        __Vtemp_1[1U] = 0U;
        __Vtemp_1[2U] = 0U;
        __Vtemp_1[3U] = 0U;
        __Vtemp_2[0U] = tb_sync_fifo__DOT__unnamedblk1__DOT__i;
        __Vtemp_2[1U] = 0U;
        __Vtemp_2[2U] = 0U;
        __Vtemp_2[3U] = 0U;
        VL_MUL_W(4, vlSelfRef.tb_sync_fifo__DOT__wr_data, __Vtemp_1, __Vtemp_2);
        vlSelfRef.tb_sync_fifo__DOT__wr_en = 1U;
        Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                            "@(posedge tb_sync_fifo.clk)");
        co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_sync_fifo.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                             78);
        vlSelfRef.tb_sync_fifo__DOT__wr_en = 0U;
        tb_sync_fifo__DOT__unnamedblk1__DOT__i = ((IData)(1U) 
                                                  + tb_sync_fifo__DOT__unnamedblk1__DOT__i);
    }
    __Vtask_tb_sync_fifo__DOT__check__2__cond = (5U 
                                                 == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
    vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__2__msg = "count==5"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__2__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__2__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
        vlSelfRef.tb_sync_fifo__DOT__err_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    __Vtask_tb_sync_fifo__DOT__check__3__cond = (0U 
                                                 != (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
    vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__3__msg = "!empty"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__3__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__3__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
        vlSelfRef.tb_sync_fifo__DOT__err_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    tb_sync_fifo__DOT__unnamedblk2__DOT__i = 1U;
    while (VL_GTES_III(32, 5U, tb_sync_fifo__DOT__unnamedblk2__DOT__i)) {
        Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                            "@(posedge tb_sync_fifo.clk)");
        co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_sync_fifo.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                             86);
        __Vtemp_3[0U] = 0x10000001U;
        __Vtemp_3[1U] = 0U;
        __Vtemp_3[2U] = 0U;
        __Vtemp_3[3U] = 0U;
        __Vtemp_4[0U] = tb_sync_fifo__DOT__unnamedblk2__DOT__i;
        __Vtemp_4[1U] = 0U;
        __Vtemp_4[2U] = 0U;
        __Vtemp_4[3U] = 0U;
        VL_MUL_W(4, __Vtemp_5, __Vtemp_3, __Vtemp_4);
        __Vtask_tb_sync_fifo__DOT__check__4__cond = 
            (0U == ((((vlSelfRef.tb_sync_fifo__DOT__dut__DOT__mem
                       [vlSelfRef.tb_sync_fifo__DOT__dut__DOT__rd_ptr][0U] 
                       ^ __Vtemp_5[0U]) | (vlSelfRef.tb_sync_fifo__DOT__dut__DOT__mem
                                           [vlSelfRef.tb_sync_fifo__DOT__dut__DOT__rd_ptr][1U] 
                                           ^ __Vtemp_5[1U])) 
                     | (vlSelfRef.tb_sync_fifo__DOT__dut__DOT__mem
                        [vlSelfRef.tb_sync_fifo__DOT__dut__DOT__rd_ptr][2U] 
                        ^ __Vtemp_5[2U])) | (vlSelfRef.tb_sync_fifo__DOT__dut__DOT__mem
                                             [vlSelfRef.tb_sync_fifo__DOT__dut__DOT__rd_ptr][3U] 
                                             ^ __Vtemp_5[3U])));
        vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__4__msg 
            = VL_SFORMATF_N_NX("rd_data %0d",0,32,tb_sync_fifo__DOT__unnamedblk2__DOT__i) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__4__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__4__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
            vlSelfRef.tb_sync_fifo__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_sync_fifo__DOT__err_count);
        }
        vlSelfRef.tb_sync_fifo__DOT__rd_en = 1U;
        Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                            "@(posedge tb_sync_fifo.clk)");
        co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_sync_fifo.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                             89);
        vlSelfRef.tb_sync_fifo__DOT__rd_en = 0U;
        tb_sync_fifo__DOT__unnamedblk2__DOT__i = ((IData)(1U) 
                                                  + tb_sync_fifo__DOT__unnamedblk2__DOT__i);
    }
    __Vtask_tb_sync_fifo__DOT__check__5__cond = (0U 
                                                 == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
    vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__5__msg = "empty after drain"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__5__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__5__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
        vlSelfRef.tb_sync_fifo__DOT__err_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    tb_sync_fifo__DOT__unnamedblk3__DOT__i = 0U;
    while (VL_GTS_III(32, 0x0000003cU, tb_sync_fifo__DOT__unnamedblk3__DOT__i)) {
        Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                            "@(posedge tb_sync_fifo.clk)");
        co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_sync_fifo.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                             96);
        VL_EXTENDS_WI(128,32, vlSelfRef.tb_sync_fifo__DOT__wr_data, tb_sync_fifo__DOT__unnamedblk3__DOT__i);
        vlSelfRef.tb_sync_fifo__DOT__wr_en = 1U;
        Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                            "@(posedge tb_sync_fifo.clk)");
        co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_sync_fifo.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                             99);
        vlSelfRef.tb_sync_fifo__DOT__wr_en = 0U;
        tb_sync_fifo__DOT__unnamedblk3__DOT__i = ((IData)(1U) 
                                                  + tb_sync_fifo__DOT__unnamedblk3__DOT__i);
    }
    __Vtask_tb_sync_fifo__DOT__check__6__cond = (0x3cU 
                                                 == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
    vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__6__msg = "count 60"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__6__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__6__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
        vlSelfRef.tb_sync_fifo__DOT__err_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    __Vtask_tb_sync_fifo__DOT__check__7__cond = (0x3cU 
                                                 <= (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
    vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__7__msg = "almost_full"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__7__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__7__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
        vlSelfRef.tb_sync_fifo__DOT__err_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    __Vtask_tb_sync_fifo__DOT__check__8__cond = (0x40U 
                                                 != (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
    vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__8__msg = "!full yet"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__8__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__8__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
        vlSelfRef.tb_sync_fifo__DOT__err_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    tb_sync_fifo__DOT__unnamedblk4__DOT__j = 0x0000003cU;
    while (VL_GTS_III(32, 0x00000040U, tb_sync_fifo__DOT__unnamedblk4__DOT__j)) {
        Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                            "@(posedge tb_sync_fifo.clk)");
        co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_sync_fifo.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                             107);
        VL_EXTENDS_WI(128,32, vlSelfRef.tb_sync_fifo__DOT__wr_data, tb_sync_fifo__DOT__unnamedblk4__DOT__j);
        vlSelfRef.tb_sync_fifo__DOT__wr_en = 1U;
        Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                            "@(posedge tb_sync_fifo.clk)");
        co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_sync_fifo.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                             110);
        vlSelfRef.tb_sync_fifo__DOT__wr_en = 0U;
        tb_sync_fifo__DOT__unnamedblk4__DOT__j = ((IData)(1U) 
                                                  + tb_sync_fifo__DOT__unnamedblk4__DOT__j);
    }
    Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                        "@(posedge tb_sync_fifo.clk)");
    co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_sync_fifo.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                         113);
    __Vtask_tb_sync_fifo__DOT__check__9__cond = (IData)(
                                                        (0x40U 
                                                         == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r)));
    vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__9__msg = "full at 64"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__9__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__9__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
        vlSelfRef.tb_sync_fifo__DOT__err_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                        "@(posedge tb_sync_fifo.clk)");
    co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_sync_fifo.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                         117);
    vlSelfRef.tb_sync_fifo__DOT__flush = 1U;
    Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                        "@(posedge tb_sync_fifo.clk)");
    co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_sync_fifo.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                         119);
    vlSelfRef.tb_sync_fifo__DOT__flush = 0U;
    Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                        "@(posedge tb_sync_fifo.clk)");
    co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_sync_fifo.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                         121);
    __Vtask_tb_sync_fifo__DOT__check__10__cond = (IData)(
                                                         (0U 
                                                          == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r)));
    vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__10__msg = "flush empty"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__10__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__10__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
        vlSelfRef.tb_sync_fifo__DOT__err_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                        "@(posedge tb_sync_fifo.clk)");
    co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_sync_fifo.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                         124);
    vlSelfRef.tb_sync_fifo__DOT__wr_data[0U] = 0xfeedfaceU;
    vlSelfRef.tb_sync_fifo__DOT__wr_data[1U] = 0U;
    vlSelfRef.tb_sync_fifo__DOT__wr_data[2U] = 0U;
    vlSelfRef.tb_sync_fifo__DOT__wr_data[3U] = 0U;
    vlSelfRef.tb_sync_fifo__DOT__wr_en = 1U;
    Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                        "@(posedge tb_sync_fifo.clk)");
    co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_sync_fifo.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                         127);
    vlSelfRef.tb_sync_fifo__DOT__wr_en = 0U;
    Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                        "@(posedge tb_sync_fifo.clk)");
    co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_sync_fifo.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                         129);
    __Vtask_tb_sync_fifo__DOT__check__11__cond = (0U 
                                                  == 
                                                  ((((0xfeedfaceU 
                                                      ^ vlSelfRef.tb_sync_fifo__DOT__dut__DOT__mem
                                                      [vlSelfRef.tb_sync_fifo__DOT__dut__DOT__rd_ptr][0U]) 
                                                     | vlSelfRef.tb_sync_fifo__DOT__dut__DOT__mem
                                                     [vlSelfRef.tb_sync_fifo__DOT__dut__DOT__rd_ptr][1U]) 
                                                    | vlSelfRef.tb_sync_fifo__DOT__dut__DOT__mem
                                                    [vlSelfRef.tb_sync_fifo__DOT__dut__DOT__rd_ptr][2U]) 
                                                   | vlSelfRef.tb_sync_fifo__DOT__dut__DOT__mem
                                                   [vlSelfRef.tb_sync_fifo__DOT__dut__DOT__rd_ptr][3U]));
    vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__11__msg = "peek before rd"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__11__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__11__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
        vlSelfRef.tb_sync_fifo__DOT__err_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    vlSelfRef.tb_sync_fifo__DOT__rd_en = 1U;
    Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                        "@(posedge tb_sync_fifo.clk)");
    co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_sync_fifo.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                         132);
    vlSelfRef.tb_sync_fifo__DOT__rd_en = 0U;
    Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(vlSelf, 
                                                        "@(posedge tb_sync_fifo.clk)");
    co_await vlSelfRef.__VtrigSched_h16468184__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_sync_fifo.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                                         134);
    __Vtask_tb_sync_fifo__DOT__check__12__cond = (0U 
                                                  == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
    vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__12__msg = "empty after single rd"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_sync_fifo__DOT__check__12__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_sync_fifo.sv:55: Assertion failed in %Ntb_sync_fifo.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_sync_fifo__DOT__check__12__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 55, "");
        vlSelfRef.tb_sync_fifo__DOT__err_count = ((IData)(1U) 
                                                  + vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    if ((0U == vlSelfRef.tb_sync_fifo__DOT__err_count)) {
        VL_WRITEF_NX("tb_sync_fifo: PASS (all checks passed)\n",0);
    } else {
        VL_WRITEF_NX("tb_sync_fifo: FAIL (%0d errors)\n",0,
                     32,vlSelfRef.tb_sync_fifo__DOT__err_count);
    }
    VL_FINISH_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 141, "");
    co_return;
}

VlCoroutine Vtb_sync_fifo___024root___eval_initial__TOP__Vtiming__2(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 
                                             27);
        vlSelfRef.tb_sync_fifo__DOT__clk = (1U & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__clk)));
    }
    co_return;
}

void Vtb_sync_fifo___024root___eval_triggers_vec__act(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_triggers_vec__act\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((((IData)(vlSelfRef.tb_sync_fifo__DOT__rst_n) 
                                                        != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__rst_n__0)) 
                                                       << 3U) 
                                                      | (vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                         << 2U)) 
                                                     | ((((~ (IData)(vlSelfRef.tb_sync_fifo__DOT__rst_n)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__rst_n__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_sync_fifo__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__clk__0 
        = vlSelfRef.tb_sync_fifo__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__rst_n__0 
        = vlSelfRef.tb_sync_fifo__DOT__rst_n;
}

bool Vtb_sync_fifo___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___trigger_anySet__act\n"); );
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

void Vtb_sync_fifo___024root___nba_sequent__TOP__0(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___nba_sequent__TOP__0\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*5:0*/ __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__13__Vfuncout;
    __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__13__Vfuncout = 0;
    CData/*5:0*/ __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__13__p;
    __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__13__p = 0;
    CData/*5:0*/ __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__14__Vfuncout;
    __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__14__Vfuncout = 0;
    CData/*5:0*/ __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__14__p;
    __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__14__p = 0;
    CData/*5:0*/ __Vdly__tb_sync_fifo__DOT__dut__DOT__wr_ptr;
    __Vdly__tb_sync_fifo__DOT__dut__DOT__wr_ptr = 0;
    CData/*5:0*/ __Vdly__tb_sync_fifo__DOT__dut__DOT__rd_ptr;
    __Vdly__tb_sync_fifo__DOT__dut__DOT__rd_ptr = 0;
    CData/*6:0*/ __Vdly__tb_sync_fifo__DOT__dut__DOT__count_r;
    __Vdly__tb_sync_fifo__DOT__dut__DOT__count_r = 0;
    VlWide<4>/*127:0*/ __VdlyVal__tb_sync_fifo__DOT__dut__DOT__mem__v0;
    VL_ZERO_W(128, __VdlyVal__tb_sync_fifo__DOT__dut__DOT__mem__v0);
    CData/*5:0*/ __VdlyDim0__tb_sync_fifo__DOT__dut__DOT__mem__v0;
    __VdlyDim0__tb_sync_fifo__DOT__dut__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_sync_fifo__DOT__dut__DOT__mem__v0;
    __VdlySet__tb_sync_fifo__DOT__dut__DOT__mem__v0 = 0;
    // Body
    __Vdly__tb_sync_fifo__DOT__dut__DOT__wr_ptr = vlSelfRef.tb_sync_fifo__DOT__dut__DOT__wr_ptr;
    __Vdly__tb_sync_fifo__DOT__dut__DOT__rd_ptr = vlSelfRef.tb_sync_fifo__DOT__dut__DOT__rd_ptr;
    __VdlySet__tb_sync_fifo__DOT__dut__DOT__mem__v0 = 0U;
    __Vdly__tb_sync_fifo__DOT__dut__DOT__count_r = vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r;
    if (vlSelfRef.tb_sync_fifo__DOT__rst_n) {
        if (vlSelfRef.tb_sync_fifo__DOT__flush) {
            __Vdly__tb_sync_fifo__DOT__dut__DOT__wr_ptr = 0U;
            __Vdly__tb_sync_fifo__DOT__dut__DOT__rd_ptr = 0U;
            __Vdly__tb_sync_fifo__DOT__dut__DOT__count_r = 0U;
        } else {
            if ((2U == ((((IData)(vlSelfRef.tb_sync_fifo__DOT__wr_en) 
                          & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__full))) 
                         << 1U) | ((IData)(vlSelfRef.tb_sync_fifo__DOT__rd_en) 
                                   & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__empty)))))) {
                __Vdly__tb_sync_fifo__DOT__dut__DOT__count_r 
                    = (0x0000007fU & ((IData)(1U) + (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r)));
            } else if ((1U == ((((IData)(vlSelfRef.tb_sync_fifo__DOT__wr_en) 
                                 & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__full))) 
                                << 1U) | ((IData)(vlSelfRef.tb_sync_fifo__DOT__rd_en) 
                                          & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__empty)))))) {
                __Vdly__tb_sync_fifo__DOT__dut__DOT__count_r 
                    = (0x0000007fU & ((IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r) 
                                      - (IData)(1U)));
            }
            if (((IData)(vlSelfRef.tb_sync_fifo__DOT__rd_en) 
                 & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__empty)))) {
                __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__14__p 
                    = vlSelfRef.tb_sync_fifo__DOT__dut__DOT__rd_ptr;
                __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__14__Vfuncout 
                    = ((0x3fU == (IData)(__Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__14__p))
                        ? 0U : (0x0000003fU & ((IData)(1U) 
                                               + (IData)(__Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__14__p))));
                __Vdly__tb_sync_fifo__DOT__dut__DOT__rd_ptr 
                    = __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__14__Vfuncout;
            }
            if ((1U & (~ VL_ONEHOT_I((((1U == ((((IData)(vlSelfRef.tb_sync_fifo__DOT__wr_en) 
                                                 & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__full))) 
                                                << 1U) 
                                               | ((IData)(vlSelfRef.tb_sync_fifo__DOT__rd_en) 
                                                  & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__empty))))) 
                                       << 1U) | (2U 
                                                 == 
                                                 ((((IData)(vlSelfRef.tb_sync_fifo__DOT__wr_en) 
                                                    & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__full))) 
                                                   << 1U) 
                                                  | ((IData)(vlSelfRef.tb_sync_fifo__DOT__rd_en) 
                                                     & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__empty)))))))))) {
                if ((0U != (((1U == ((((IData)(vlSelfRef.tb_sync_fifo__DOT__wr_en) 
                                       & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__full))) 
                                      << 1U) | ((IData)(vlSelfRef.tb_sync_fifo__DOT__rd_en) 
                                                & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__empty))))) 
                             << 1U) | (2U == ((((IData)(vlSelfRef.tb_sync_fifo__DOT__wr_en) 
                                                & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__full))) 
                                               << 1U) 
                                              | ((IData)(vlSelfRef.tb_sync_fifo__DOT__rd_en) 
                                                 & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__empty)))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: sync_fifo.sv:61: Assertion failed in %Ntb_sync_fifo.dut: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,((((IData)(vlSelfRef.tb_sync_fifo__DOT__wr_en) 
                                          & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__full))) 
                                         << 1U) | ((IData)(vlSelfRef.tb_sync_fifo__DOT__rd_en) 
                                                   & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__empty)))));
                        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/rtl/shared\\sync_fifo.sv", 61, "");
                    }
                }
            }
            if (((IData)(vlSelfRef.tb_sync_fifo__DOT__wr_en) 
                 & (~ (IData)(vlSelfRef.tb_sync_fifo__DOT__full)))) {
                __VdlyVal__tb_sync_fifo__DOT__dut__DOT__mem__v0[0U] 
                    = vlSelfRef.tb_sync_fifo__DOT__wr_data[0U];
                __VdlyVal__tb_sync_fifo__DOT__dut__DOT__mem__v0[1U] 
                    = vlSelfRef.tb_sync_fifo__DOT__wr_data[1U];
                __VdlyVal__tb_sync_fifo__DOT__dut__DOT__mem__v0[2U] 
                    = vlSelfRef.tb_sync_fifo__DOT__wr_data[2U];
                __VdlyVal__tb_sync_fifo__DOT__dut__DOT__mem__v0[3U] 
                    = vlSelfRef.tb_sync_fifo__DOT__wr_data[3U];
                __VdlyDim0__tb_sync_fifo__DOT__dut__DOT__mem__v0 
                    = vlSelfRef.tb_sync_fifo__DOT__dut__DOT__wr_ptr;
                __VdlySet__tb_sync_fifo__DOT__dut__DOT__mem__v0 = 1U;
                __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__13__p 
                    = vlSelfRef.tb_sync_fifo__DOT__dut__DOT__wr_ptr;
                __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__13__Vfuncout 
                    = ((0x3fU == (IData)(__Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__13__p))
                        ? 0U : (0x0000003fU & ((IData)(1U) 
                                               + (IData)(__Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__13__p))));
                __Vdly__tb_sync_fifo__DOT__dut__DOT__wr_ptr 
                    = __Vfunc_tb_sync_fifo__DOT__dut__DOT__ptr_next__13__Vfuncout;
            }
        }
    } else {
        __Vdly__tb_sync_fifo__DOT__dut__DOT__wr_ptr = 0U;
        __Vdly__tb_sync_fifo__DOT__dut__DOT__rd_ptr = 0U;
        __Vdly__tb_sync_fifo__DOT__dut__DOT__count_r = 0U;
    }
    vlSelfRef.tb_sync_fifo__DOT__dut__DOT__wr_ptr = __Vdly__tb_sync_fifo__DOT__dut__DOT__wr_ptr;
    vlSelfRef.tb_sync_fifo__DOT__dut__DOT__rd_ptr = __Vdly__tb_sync_fifo__DOT__dut__DOT__rd_ptr;
    if (__VdlySet__tb_sync_fifo__DOT__dut__DOT__mem__v0) {
        vlSelfRef.tb_sync_fifo__DOT__dut__DOT__mem[__VdlyDim0__tb_sync_fifo__DOT__dut__DOT__mem__v0][0U] 
            = __VdlyVal__tb_sync_fifo__DOT__dut__DOT__mem__v0[0U];
        vlSelfRef.tb_sync_fifo__DOT__dut__DOT__mem[__VdlyDim0__tb_sync_fifo__DOT__dut__DOT__mem__v0][1U] 
            = __VdlyVal__tb_sync_fifo__DOT__dut__DOT__mem__v0[1U];
        vlSelfRef.tb_sync_fifo__DOT__dut__DOT__mem[__VdlyDim0__tb_sync_fifo__DOT__dut__DOT__mem__v0][2U] 
            = __VdlyVal__tb_sync_fifo__DOT__dut__DOT__mem__v0[2U];
        vlSelfRef.tb_sync_fifo__DOT__dut__DOT__mem[__VdlyDim0__tb_sync_fifo__DOT__dut__DOT__mem__v0][3U] 
            = __VdlyVal__tb_sync_fifo__DOT__dut__DOT__mem__v0[3U];
    }
    vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r 
        = __Vdly__tb_sync_fifo__DOT__dut__DOT__count_r;
    vlSelfRef.tb_sync_fifo__DOT__full = (0x40U == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
    vlSelfRef.tb_sync_fifo__DOT__empty = (0U == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
}

void Vtb_sync_fifo___024root___eval_nba(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_nba\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_sync_fifo___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vtb_sync_fifo___024root___timing_ready(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___timing_ready\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h16468184__0.ready("@(posedge tb_sync_fifo.clk)");
    }
    if ((8ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_hb2fb5223__0.ready("@( tb_sync_fifo.rst_n)");
    }
}

void Vtb_sync_fifo___024root___timing_resume(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___timing_resume\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h16468184__0.moveToResumeQueue(
                                                          "@(posedge tb_sync_fifo.clk)");
    vlSelfRef.__VtrigSched_hb2fb5223__0.moveToResumeQueue(
                                                          "@( tb_sync_fifo.rst_n)");
    vlSelfRef.__VtrigSched_h16468184__0.resume("@(posedge tb_sync_fifo.clk)");
    vlSelfRef.__VtrigSched_hb2fb5223__0.resume("@( tb_sync_fifo.rst_n)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_sync_fifo___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vtb_sync_fifo___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_sync_fifo___024root___eval_phase__act(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_phase__act\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_sync_fifo___024root___eval_triggers_vec__act(vlSelf);
    Vtb_sync_fifo___024root___timing_ready(vlSelf);
    Vtb_sync_fifo___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_sync_fifo___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_sync_fifo___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_sync_fifo___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_sync_fifo___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_sync_fifo___024root___eval_phase__inact(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_phase__inact\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 10, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_sync_fifo___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_sync_fifo___024root___eval_phase__nba(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_phase__nba\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_sync_fifo___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_sync_fifo___024root___eval_nba(vlSelf);
        Vtb_sync_fifo___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_sync_fifo___024root___eval(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_sync_fifo___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 10, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 10, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_sync_fifo___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 10, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_sync_fifo___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_sync_fifo___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_sync_fifo___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0(Vtb_sync_fifo___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root____VbeforeTrig_h16468184__0\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_sync_fifo__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__clk__0 
        = vlSelfRef.tb_sync_fifo__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h16468184__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_sync_fifo___024root____VbeforeTrig_hb2fb5223__0(Vtb_sync_fifo___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root____VbeforeTrig_hb2fb5223__0\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.tb_sync_fifo__DOT__rst_n) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__rst_n__0)) 
                                  << 3U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__rst_n__0 
        = vlSelfRef.tb_sync_fifo__DOT__rst_n;
    if ((8ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_hb2fb5223__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_sync_fifo___024root___eval_debug_assertions(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_debug_assertions\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
