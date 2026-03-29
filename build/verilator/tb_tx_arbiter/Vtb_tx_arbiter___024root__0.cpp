// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_tx_arbiter.h for the primary calling header

#include "Vtb_tx_arbiter__pch.h"

VlCoroutine Vtb_tx_arbiter___024root___eval_initial__TOP__Vtiming__0(Vtb_tx_arbiter___024root* vlSelf);
VlCoroutine Vtb_tx_arbiter___024root___eval_initial__TOP__Vtiming__1(Vtb_tx_arbiter___024root* vlSelf);
VlCoroutine Vtb_tx_arbiter___024root___eval_initial__TOP__Vtiming__2(Vtb_tx_arbiter___024root* vlSelf);

void Vtb_tx_arbiter___024root___eval_initial(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_initial\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_tx_arbiter__DOT__clk = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_tx_arbiter.vcd"s);
    VL_PRINTF_MT("-Info: C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv:108: $dumpvar ignored, as Verilated without --trace\n");
    Vtb_tx_arbiter___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_tx_arbiter___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_tx_arbiter___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

VlCoroutine Vtb_tx_arbiter___024root___eval_initial__TOP__Vtiming__0(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_tx_arbiter__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000186a0ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                         88);
    vlSelfRef.tb_tx_arbiter__DOT__rst_n = 1U;
    co_return;
}

void Vtb_tx_arbiter___024root____VbeforeTrig_h4d3b64c4__0(Vtb_tx_arbiter___024root* vlSelf, const char* __VeventDescription);
void Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0(Vtb_tx_arbiter___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_tx_arbiter___024root___eval_initial__TOP__Vtiming__1(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_tx_arbiter__DOT__unnamedblk1__DOT__unnamedblk1_1__DOT____Vrepeat0;
    tb_tx_arbiter__DOT__unnamedblk1__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__0__cond;
    __Vtask_tb_tx_arbiter__DOT__check__0__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__1__cond;
    __Vtask_tb_tx_arbiter__DOT__check__1__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__2__cond;
    __Vtask_tb_tx_arbiter__DOT__check__2__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__3__cond;
    __Vtask_tb_tx_arbiter__DOT__check__3__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__4__cond;
    __Vtask_tb_tx_arbiter__DOT__check__4__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__5__cond;
    __Vtask_tb_tx_arbiter__DOT__check__5__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__6__cond;
    __Vtask_tb_tx_arbiter__DOT__check__6__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__7__cond;
    __Vtask_tb_tx_arbiter__DOT__check__7__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__8__cond;
    __Vtask_tb_tx_arbiter__DOT__check__8__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__9__cond;
    __Vtask_tb_tx_arbiter__DOT__check__9__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__10__cond;
    __Vtask_tb_tx_arbiter__DOT__check__10__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__11__cond;
    __Vtask_tb_tx_arbiter__DOT__check__11__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__12__cond;
    __Vtask_tb_tx_arbiter__DOT__check__12__cond = 0;
    CData/*0:0*/ __Vtask_tb_tx_arbiter__DOT__check__13__cond;
    __Vtask_tb_tx_arbiter__DOT__check__13__cond = 0;
    // Body
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[0U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[1U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[2U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[3U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__fill_valid = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[0U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[1U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[2U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[3U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__quote_valid = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__tx_ready = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[0U] = 1U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[1U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[2U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[3U] = 0x30000000U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[0U] = 2U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[1U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[2U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[3U] = 0x30000000U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[0U] = 0x00000011U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[1U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[2U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[3U] = 0x10000000U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2[0U] = 0x00000022U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2[1U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2[2U] = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2[3U] = 0x10000000U;
    while ((1U & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__rst_n)))) {
        Vtb_tx_arbiter___024root____VbeforeTrig_h4d3b64c4__0(vlSelf, 
                                                             "@( tb_tx_arbiter.rst_n)");
        co_await vlSelfRef.__VtrigSched_h4d3b64c4__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_tx_arbiter.rst_n)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                                             125);
    }
    Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0(vlSelf, 
                                                         "@(posedge tb_tx_arbiter.clk)");
    co_await vlSelfRef.__VtrigSched_h320c008b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_tx_arbiter.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                                         126);
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[0U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[0U];
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[1U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[1U];
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[2U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[2U];
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[3U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[3U];
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[0U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[0U];
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[1U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[1U];
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[2U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[2U];
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[3U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[3U];
    vlSelfRef.tb_tx_arbiter__DOT__fill_valid = 1U;
    vlSelfRef.tb_tx_arbiter__DOT__quote_valid = 1U;
    vlSelfRef.tb_tx_arbiter__DOT__tx_ready = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                         134);
    __Vtask_tb_tx_arbiter__DOT__check__0__cond = (1U 
                                                  & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__quote_ready)));
    vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__0__msg = "both valid -> quote_ready low (strict priority)"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__0__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__0__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
        vlSelfRef.tb_tx_arbiter__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    __Vtask_tb_tx_arbiter__DOT__check__1__cond = (1U 
                                                  & (~ 
                                                     ((~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid)) 
                                                      & (IData)(vlSelfRef.tb_tx_arbiter__DOT__quote_ready))));
    vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__1__msg = "both valid -> not both ready high"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__1__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__1__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
        vlSelfRef.tb_tx_arbiter__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0(vlSelf, 
                                                         "@(posedge tb_tx_arbiter.clk)");
    co_await vlSelfRef.__VtrigSched_h320c008b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_tx_arbiter.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                                         137);
    __Vtask_tb_tx_arbiter__DOT__check__2__cond = ((IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid) 
                                                  & (0U 
                                                     == 
                                                     ((((vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[0U] 
                                                         ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[0U]) 
                                                        | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[1U] 
                                                           ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[1U])) 
                                                       | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[2U] 
                                                          ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[2U])) 
                                                      | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[3U] 
                                                         ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[3U]))));
    vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__2__msg = "selected frame is fill"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__2__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__2__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
        vlSelfRef.tb_tx_arbiter__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[0U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[0U];
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[1U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[1U];
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[2U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[2U];
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[3U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[3U];
    Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0(vlSelf, 
                                                         "@(posedge tb_tx_arbiter.clk)");
    co_await vlSelfRef.__VtrigSched_h320c008b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_tx_arbiter.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                                         142);
    __Vtask_tb_tx_arbiter__DOT__check__3__cond = vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid;
    vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__3__msg = "while stalled, fill_ready low"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__3__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__3__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
        vlSelfRef.tb_tx_arbiter__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    __Vtask_tb_tx_arbiter__DOT__check__4__cond = (1U 
                                                  & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__quote_ready)));
    vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__4__msg = "while stalled, quote_ready low"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__4__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__4__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
        vlSelfRef.tb_tx_arbiter__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    __Vtask_tb_tx_arbiter__DOT__check__5__cond = ((IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid) 
                                                  & (0U 
                                                     == 
                                                     ((((vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[0U] 
                                                         ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[0U]) 
                                                        | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[1U] 
                                                           ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[1U])) 
                                                       | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[2U] 
                                                          ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[2U])) 
                                                      | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[3U] 
                                                         ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F1[3U]))));
    vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__5__msg = "stalled output remains stable"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__5__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__5__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
        vlSelfRef.tb_tx_arbiter__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    vlSelfRef.tb_tx_arbiter__DOT__tx_ready = 1U;
    Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0(vlSelf, 
                                                         "@(posedge tb_tx_arbiter.clk)");
    co_await vlSelfRef.__VtrigSched_h320c008b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_tx_arbiter.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                                         149);
    __Vtask_tb_tx_arbiter__DOT__check__6__cond = (1U 
                                                  & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid)));
    vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__6__msg = "consumed frame deasserts tx_valid"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__6__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__6__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
        vlSelfRef.tb_tx_arbiter__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    vlSelfRef.tb_tx_arbiter__DOT__fill_valid = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__quote_valid = 1U;
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[0U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2[0U];
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[1U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2[1U];
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[2U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2[2U];
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[3U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2[3U];
    vlSelfRef.tb_tx_arbiter__DOT__tx_ready = 1U;
    Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0(vlSelf, 
                                                         "@(posedge tb_tx_arbiter.clk)");
    co_await vlSelfRef.__VtrigSched_h320c008b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_tx_arbiter.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                                         157);
    __Vtask_tb_tx_arbiter__DOT__check__7__cond = ((IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid) 
                                                  & (0U 
                                                     == 
                                                     ((((vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[0U] 
                                                         ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2[0U]) 
                                                        | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[1U] 
                                                           ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2[1U])) 
                                                       | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[2U] 
                                                          ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2[2U])) 
                                                      | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[3U] 
                                                         ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2[3U]))));
    vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__7__msg = "quote accepted when no fill"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__7__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__7__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
        vlSelfRef.tb_tx_arbiter__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0(vlSelf, 
                                                         "@(posedge tb_tx_arbiter.clk)");
    co_await vlSelfRef.__VtrigSched_h320c008b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_tx_arbiter.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                                         159);
    __Vtask_tb_tx_arbiter__DOT__check__8__cond = (1U 
                                                  & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid)));
    vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__8__msg = "quote consumed"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__8__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__8__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
        vlSelfRef.tb_tx_arbiter__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    vlSelfRef.tb_tx_arbiter__DOT__tx_ready = 0U;
    vlSelfRef.tb_tx_arbiter__DOT__quote_valid = 1U;
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[0U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[0U];
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[1U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[1U];
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[2U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[2U];
    vlSelfRef.tb_tx_arbiter__DOT__quote_frame[3U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[3U];
    vlSelfRef.tb_tx_arbiter__DOT__fill_valid = 0U;
    Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0(vlSelf, 
                                                         "@(posedge tb_tx_arbiter.clk)");
    co_await vlSelfRef.__VtrigSched_h320c008b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_tx_arbiter.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                                         168);
    __Vtask_tb_tx_arbiter__DOT__check__9__cond = ((IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid) 
                                                  & (0U 
                                                     == 
                                                     ((((vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[0U] 
                                                         ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[0U]) 
                                                        | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[1U] 
                                                           ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[1U])) 
                                                       | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[2U] 
                                                          ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[2U])) 
                                                      | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[3U] 
                                                         ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[3U]))));
    vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__9__msg = "quote buffered with tx stall"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__9__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__9__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
        vlSelfRef.tb_tx_arbiter__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    vlSelfRef.tb_tx_arbiter__DOT__fill_valid = 1U;
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[0U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[0U];
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[1U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[1U];
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[2U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[2U];
    vlSelfRef.tb_tx_arbiter__DOT__fill_frame[3U] = vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[3U];
    tb_tx_arbiter__DOT__unnamedblk1__DOT__unnamedblk1_1__DOT____Vrepeat0 = 3U;
    while (VL_LTS_III(32, 0U, tb_tx_arbiter__DOT__unnamedblk1__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0(vlSelf, 
                                                             "@(posedge tb_tx_arbiter.clk)");
        co_await vlSelfRef.__VtrigSched_h320c008b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_tx_arbiter.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                                             174);
        __Vtask_tb_tx_arbiter__DOT__check__10__cond 
            = ((IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid) 
               & (0U == ((((vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[0U] 
                            ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[0U]) 
                           | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[1U] 
                              ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[1U])) 
                          | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[2U] 
                             ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[2U])) 
                         | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[3U] 
                            ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1[3U]))));
        vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__10__msg = "held frame remains quote (no preempt mid-hold)"s;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__10__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__10__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
            vlSelfRef.tb_tx_arbiter__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_tx_arbiter__DOT__err_count);
        }
        __Vtask_tb_tx_arbiter__DOT__check__11__cond 
            = (1U & (~ ((~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid)) 
                        & (IData)(vlSelfRef.tb_tx_arbiter__DOT__quote_ready))));
        vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__11__msg = "no dual ready while full"s;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__11__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__11__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
            vlSelfRef.tb_tx_arbiter__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_tx_arbiter__DOT__err_count);
        }
        tb_tx_arbiter__DOT__unnamedblk1__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (tb_tx_arbiter__DOT__unnamedblk1__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.tb_tx_arbiter__DOT__tx_ready = 1U;
    Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0(vlSelf, 
                                                         "@(posedge tb_tx_arbiter.clk)");
    co_await vlSelfRef.__VtrigSched_h320c008b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_tx_arbiter.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                                         179);
    __Vtask_tb_tx_arbiter__DOT__check__12__cond = (1U 
                                                   & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid)));
    vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__12__msg = "held quote consumed first"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__12__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__12__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
        vlSelfRef.tb_tx_arbiter__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0(vlSelf, 
                                                         "@(posedge tb_tx_arbiter.clk)");
    co_await vlSelfRef.__VtrigSched_h320c008b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_tx_arbiter.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                                         183);
    __Vtask_tb_tx_arbiter__DOT__check__13__cond = ((IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid) 
                                                   & (0U 
                                                      == 
                                                      ((((vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[0U] 
                                                          ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[0U]) 
                                                         | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[1U] 
                                                            ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[1U])) 
                                                        | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[2U] 
                                                           ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[2U])) 
                                                       | (vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[3U] 
                                                          ^ vlSelfRef.tb_tx_arbiter__DOT__unnamedblk1__DOT__F2[3U]))));
    vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__13__msg = "fill accepted after buffer frees"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_tx_arbiter__DOT__check__13__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_tx_arbiter.sv:78: Assertion failed in %Ntb_tx_arbiter.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_tx_arbiter__DOT__check__13__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 78, "");
        vlSelfRef.tb_tx_arbiter__DOT__err_count = ((IData)(1U) 
                                                   + vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    if ((0U == vlSelfRef.tb_tx_arbiter__DOT__err_count)) {
        VL_WRITEF_NX("tb_tx_arbiter: PASS (all checks passed)\n",0);
    } else {
        VL_WRITEF_NX("tb_tx_arbiter: FAIL (%0d errors)\n",0,
                     32,vlSelfRef.tb_tx_arbiter__DOT__err_count);
    }
    VL_FINISH_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 191, "");
    co_return;
}

VlCoroutine Vtb_tx_arbiter___024root___eval_initial__TOP__Vtiming__2(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 
                                             84);
        vlSelfRef.tb_tx_arbiter__DOT__clk = (1U & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__clk)));
    }
    co_return;
}

void Vtb_tx_arbiter___024root___eval_triggers_vec__act(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_triggers_vec__act\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((((IData)(vlSelfRef.tb_tx_arbiter__DOT__rst_n) 
                                                        != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__rst_n__0)) 
                                                       << 3U) 
                                                      | (vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                         << 2U)) 
                                                     | ((((~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__rst_n)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__rst_n__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_tx_arbiter__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__clk__0 
        = vlSelfRef.tb_tx_arbiter__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__rst_n__0 
        = vlSelfRef.tb_tx_arbiter__DOT__rst_n;
}

bool Vtb_tx_arbiter___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___trigger_anySet__act\n"); );
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

void Vtb_tx_arbiter___024root___act_comb__TOP__0(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___act_comb__TOP__0\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_tx_arbiter__DOT__quote_ready = (1U 
                                                 & ((~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid)) 
                                                    & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__fill_valid))));
}

void Vtb_tx_arbiter___024root___eval_act(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_act\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((0x000000000000000dULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.tb_tx_arbiter__DOT__quote_ready = 
            (1U & ((~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid)) 
                   & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__fill_valid))));
    }
}

void Vtb_tx_arbiter___024root___nba_sequent__TOP__0(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___nba_sequent__TOP__0\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid;
    __Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid = 0;
    // Body
    __Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid 
        = vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid;
    if (vlSelfRef.tb_tx_arbiter__DOT__rst_n) {
        if (((IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid) 
             & (IData)(vlSelfRef.tb_tx_arbiter__DOT__tx_ready))) {
            __Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid = 0U;
        }
        if ((1U & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid)))) {
            if (vlSelfRef.tb_tx_arbiter__DOT__fill_valid) {
                vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[0U] 
                    = vlSelfRef.tb_tx_arbiter__DOT__fill_frame[0U];
                vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[1U] 
                    = vlSelfRef.tb_tx_arbiter__DOT__fill_frame[1U];
                vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[2U] 
                    = vlSelfRef.tb_tx_arbiter__DOT__fill_frame[2U];
                vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[3U] 
                    = vlSelfRef.tb_tx_arbiter__DOT__fill_frame[3U];
                __Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid = 1U;
            } else if (vlSelfRef.tb_tx_arbiter__DOT__quote_valid) {
                vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[0U] 
                    = vlSelfRef.tb_tx_arbiter__DOT__quote_frame[0U];
                vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[1U] 
                    = vlSelfRef.tb_tx_arbiter__DOT__quote_frame[1U];
                vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[2U] 
                    = vlSelfRef.tb_tx_arbiter__DOT__quote_frame[2U];
                vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[3U] 
                    = vlSelfRef.tb_tx_arbiter__DOT__quote_frame[3U];
                __Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid = 1U;
            }
        }
    } else {
        vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[0U] = 0U;
        vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[1U] = 0U;
        vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[2U] = 0U;
        vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[3U] = 0U;
        __Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid = 0U;
    }
    vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid 
        = __Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid;
}

void Vtb_tx_arbiter___024root___eval_nba(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_nba\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vinline__nba_sequent__TOP__0___Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid;
    __Vinline__nba_sequent__TOP__0___Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid = 0;
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_sequent__TOP__0___Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid 
            = vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid;
        if (vlSelfRef.tb_tx_arbiter__DOT__rst_n) {
            if (((IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid) 
                 & (IData)(vlSelfRef.tb_tx_arbiter__DOT__tx_ready))) {
                __Vinline__nba_sequent__TOP__0___Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid = 0U;
            }
            if ((1U & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid)))) {
                if (vlSelfRef.tb_tx_arbiter__DOT__fill_valid) {
                    vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[0U] 
                        = vlSelfRef.tb_tx_arbiter__DOT__fill_frame[0U];
                    vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[1U] 
                        = vlSelfRef.tb_tx_arbiter__DOT__fill_frame[1U];
                    vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[2U] 
                        = vlSelfRef.tb_tx_arbiter__DOT__fill_frame[2U];
                    vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[3U] 
                        = vlSelfRef.tb_tx_arbiter__DOT__fill_frame[3U];
                    __Vinline__nba_sequent__TOP__0___Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid = 1U;
                } else if (vlSelfRef.tb_tx_arbiter__DOT__quote_valid) {
                    vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[0U] 
                        = vlSelfRef.tb_tx_arbiter__DOT__quote_frame[0U];
                    vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[1U] 
                        = vlSelfRef.tb_tx_arbiter__DOT__quote_frame[1U];
                    vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[2U] 
                        = vlSelfRef.tb_tx_arbiter__DOT__quote_frame[2U];
                    vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[3U] 
                        = vlSelfRef.tb_tx_arbiter__DOT__quote_frame[3U];
                    __Vinline__nba_sequent__TOP__0___Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid = 1U;
                }
            }
        } else {
            vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[0U] = 0U;
            vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[1U] = 0U;
            vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[2U] = 0U;
            vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf[3U] = 0U;
            __Vinline__nba_sequent__TOP__0___Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid = 0U;
        }
        vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid 
            = __Vinline__nba_sequent__TOP__0___Vdly__tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid;
    }
    if ((0x000000000000000fULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.tb_tx_arbiter__DOT__quote_ready = 
            (1U & ((~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid)) 
                   & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__fill_valid))));
    }
}

void Vtb_tx_arbiter___024root___timing_ready(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___timing_ready\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((8ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h4d3b64c4__0.ready("@( tb_tx_arbiter.rst_n)");
    }
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h320c008b__0.ready("@(posedge tb_tx_arbiter.clk)");
    }
}

void Vtb_tx_arbiter___024root___timing_resume(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___timing_resume\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h4d3b64c4__0.moveToResumeQueue(
                                                          "@( tb_tx_arbiter.rst_n)");
    vlSelfRef.__VtrigSched_h320c008b__0.moveToResumeQueue(
                                                          "@(posedge tb_tx_arbiter.clk)");
    vlSelfRef.__VtrigSched_h4d3b64c4__0.resume("@( tb_tx_arbiter.rst_n)");
    vlSelfRef.__VtrigSched_h320c008b__0.resume("@(posedge tb_tx_arbiter.clk)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_tx_arbiter___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vtb_tx_arbiter___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_tx_arbiter___024root___eval_phase__act(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_phase__act\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_tx_arbiter___024root___eval_triggers_vec__act(vlSelf);
    Vtb_tx_arbiter___024root___timing_ready(vlSelf);
    Vtb_tx_arbiter___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_tx_arbiter___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_tx_arbiter___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_tx_arbiter___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_tx_arbiter___024root___timing_resume(vlSelf);
        Vtb_tx_arbiter___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_tx_arbiter___024root___eval_phase__inact(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_phase__inact\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 61, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_tx_arbiter___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_tx_arbiter___024root___eval_phase__nba(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_phase__nba\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_tx_arbiter___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_tx_arbiter___024root___eval_nba(vlSelf);
        Vtb_tx_arbiter___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_tx_arbiter___024root___eval(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_tx_arbiter___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 61, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 61, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_tx_arbiter___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 61, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_tx_arbiter___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_tx_arbiter___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_tx_arbiter___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_tx_arbiter___024root____VbeforeTrig_h4d3b64c4__0(Vtb_tx_arbiter___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root____VbeforeTrig_h4d3b64c4__0\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.tb_tx_arbiter__DOT__rst_n) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__rst_n__0)) 
                                  << 3U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__rst_n__0 
        = vlSelfRef.tb_tx_arbiter__DOT__rst_n;
    if ((8ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h4d3b64c4__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0(Vtb_tx_arbiter___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root____VbeforeTrig_h320c008b__0\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_tx_arbiter__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__clk__0 
        = vlSelfRef.tb_tx_arbiter__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h320c008b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h320c008b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h320c008b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h320c008b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h320c008b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h320c008b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h320c008b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h320c008b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h320c008b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h320c008b__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_tx_arbiter___024root___eval_debug_assertions(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_debug_assertions\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
