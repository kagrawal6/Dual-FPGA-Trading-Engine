// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_board_a_top.h for the primary calling header

#include "Vtb_board_a_top__pch.h"

VlCoroutine Vtb_board_a_top___024root___eval_initial__TOP__Vtiming__0(Vtb_board_a_top___024root* vlSelf);
VlCoroutine Vtb_board_a_top___024root___eval_initial__TOP__Vtiming__1(Vtb_board_a_top___024root* vlSelf);
VlCoroutine Vtb_board_a_top___024root___eval_initial__TOP__Vtiming__2(Vtb_board_a_top___024root* vlSelf);

void Vtb_board_a_top___024root___eval_initial(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_initial\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_board_a_top__DOT__clk = 0U;
    Vtb_board_a_top___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_board_a_top___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_board_a_top___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

VlCoroutine Vtb_board_a_top___024root___eval_initial__TOP__Vtiming__0(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_board_a_top__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000186a0ULL, 
                                         nullptr, "tb/board_a/tb_board_a_top.sv", 
                                         60);
    vlSelfRef.tb_board_a_top__DOT__rst_n = 1U;
    co_return;
}

void Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(Vtb_board_a_top___024root* vlSelf, const char* __VeventDescription);
void Vtb_board_a_top___024root____VbeforeTrig_h68e7d246__0(Vtb_board_a_top___024root* vlSelf, const char* __VeventDescription);
void Vtb_board_a_top___024root____VbeforeTrig_h0f1c9fb4__0(Vtb_board_a_top___024root* vlSelf, const char* __VeventDescription);
void Vtb_board_a_top___024root____VbeforeTrig_h43444ce6__0(Vtb_board_a_top___024root* vlSelf, const char* __VeventDescription);
void Vtb_board_a_top___024root____VbeforeTrig_h950459ef__0(Vtb_board_a_top___024root* vlSelf, const char* __VeventDescription);
void Vtb_board_a_top___024root____VbeforeTrig_hc95c02d3__0(Vtb_board_a_top___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_board_a_top___024root___eval_initial__TOP__Vtiming__1(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_board_a_top__DOT__unnamedblk1__DOT__unnamedblk1_1__DOT____Vrepeat0;
    tb_board_a_top__DOT__unnamedblk1__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ tb_board_a_top__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1;
    tb_board_a_top__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0;
    CData/*7:0*/ __Vtask_tb_board_a_top__DOT__axi_write__0__addr;
    __Vtask_tb_board_a_top__DOT__axi_write__0__addr = 0;
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__axi_write__0__data;
    __Vtask_tb_board_a_top__DOT__axi_write__0__data = 0;
    CData/*7:0*/ __Vtask_tb_board_a_top__DOT__axi_write__1__addr;
    __Vtask_tb_board_a_top__DOT__axi_write__1__addr = 0;
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__axi_write__1__data;
    __Vtask_tb_board_a_top__DOT__axi_write__1__data = 0;
    CData/*7:0*/ __Vtask_tb_board_a_top__DOT__axi_read__2__addr;
    __Vtask_tb_board_a_top__DOT__axi_read__2__addr = 0;
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__axi_read__2__data;
    __Vtask_tb_board_a_top__DOT__axi_read__2__data = 0;
    CData/*0:0*/ __Vtask_tb_board_a_top__DOT__check__3__cond;
    __Vtask_tb_board_a_top__DOT__check__3__cond = 0;
    CData/*0:0*/ __Vtask_tb_board_a_top__DOT__check__4__cond;
    __Vtask_tb_board_a_top__DOT__check__4__cond = 0;
    // Body
    vlSelfRef.tb_board_a_top__DOT__btn = 0U;
    vlSelfRef.tb_board_a_top__DOT__sw = 0U;
    vlSelfRef.tb_board_a_top__DOT__pmod_ja_ready = 1U;
    vlSelfRef.tb_board_a_top__DOT__pmod_jb = 0U;
    vlSelfRef.tb_board_a_top__DOT__pmod_jb_valid = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_awvalid = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_wdata = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_wvalid = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_bready = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_araddr = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_arvalid = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_rready = 0U;
    Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(vlSelf, 
                                                          "@(posedge tb_board_a_top.clk)");
    co_await vlSelfRef.__VtrigSched_h6fd192e6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_top.clk)", 
                                                         "tb/board_a/tb_board_a_top.sv", 
                                                         156);
    while ((1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__rst_n)))) {
        Vtb_board_a_top___024root____VbeforeTrig_h68e7d246__0(vlSelf, 
                                                              "@( tb_board_a_top.rst_n)");
        co_await vlSelfRef.__VtrigSched_h68e7d246__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_board_a_top.rst_n)", 
                                                             "tb/board_a/tb_board_a_top.sv", 
                                                             157);
    }
    tb_board_a_top__DOT__unnamedblk1__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0x00000014U;
    while (VL_LTS_III(32, 0U, tb_board_a_top__DOT__unnamedblk1__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(vlSelf, 
                                                              "@(posedge tb_board_a_top.clk)");
        co_await vlSelfRef.__VtrigSched_h6fd192e6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_board_a_top.clk)", 
                                                             "tb/board_a/tb_board_a_top.sv", 
                                                             158);
        tb_board_a_top__DOT__unnamedblk1__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (tb_board_a_top__DOT__unnamedblk1__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    __Vtask_tb_board_a_top__DOT__axi_write__0__data = 0U;
    __Vtask_tb_board_a_top__DOT__axi_write__0__addr = 4U;
    Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(vlSelf, 
                                                          "@(posedge tb_board_a_top.clk)");
    co_await vlSelfRef.__VtrigSched_h6fd192e6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_top.clk)", 
                                                         "tb/board_a/tb_board_a_top.sv", 
                                                         107);
    vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr = __Vtask_tb_board_a_top__DOT__axi_write__0__addr;
    vlSelfRef.tb_board_a_top__DOT__s_axi_awvalid = 1U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_wdata = __Vtask_tb_board_a_top__DOT__axi_write__0__data;
    vlSelfRef.tb_board_a_top__DOT__s_axi_wvalid = 1U;
    while (vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid) {
        Vtb_board_a_top___024root____VbeforeTrig_h0f1c9fb4__0(vlSelf, 
                                                              "@( (~ tb_board_a_top.s_axi_bvalid))");
        co_await vlSelfRef.__VtrigSched_h0f1c9fb4__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( (~ tb_board_a_top.s_axi_bvalid))", 
                                                             "tb/board_a/tb_board_a_top.sv", 
                                                             113);
    }
    Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(vlSelf, 
                                                          "@(posedge tb_board_a_top.clk)");
    co_await vlSelfRef.__VtrigSched_h6fd192e6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_top.clk)", 
                                                         "tb/board_a/tb_board_a_top.sv", 
                                                         114);
    vlSelfRef.tb_board_a_top__DOT__s_axi_awvalid = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_wvalid = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_bready = 1U;
    while ((1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid)))) {
        Vtb_board_a_top___024root____VbeforeTrig_h43444ce6__0(vlSelf, 
                                                              "@( tb_board_a_top.s_axi_bvalid)");
        co_await vlSelfRef.__VtrigSched_h43444ce6__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_board_a_top.s_axi_bvalid)", 
                                                             "tb/board_a/tb_board_a_top.sv", 
                                                             118);
    }
    Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(vlSelf, 
                                                          "@(posedge tb_board_a_top.clk)");
    co_await vlSelfRef.__VtrigSched_h6fd192e6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_top.clk)", 
                                                         "tb/board_a/tb_board_a_top.sv", 
                                                         119);
    vlSelfRef.tb_board_a_top__DOT__s_axi_bready = 0U;
    __Vtask_tb_board_a_top__DOT__axi_write__1__data = 1U;
    __Vtask_tb_board_a_top__DOT__axi_write__1__addr = 0U;
    Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(vlSelf, 
                                                          "@(posedge tb_board_a_top.clk)");
    co_await vlSelfRef.__VtrigSched_h6fd192e6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_top.clk)", 
                                                         "tb/board_a/tb_board_a_top.sv", 
                                                         107);
    vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr = __Vtask_tb_board_a_top__DOT__axi_write__1__addr;
    vlSelfRef.tb_board_a_top__DOT__s_axi_awvalid = 1U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_wdata = __Vtask_tb_board_a_top__DOT__axi_write__1__data;
    vlSelfRef.tb_board_a_top__DOT__s_axi_wvalid = 1U;
    while (vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid) {
        Vtb_board_a_top___024root____VbeforeTrig_h0f1c9fb4__0(vlSelf, 
                                                              "@( (~ tb_board_a_top.s_axi_bvalid))");
        co_await vlSelfRef.__VtrigSched_h0f1c9fb4__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( (~ tb_board_a_top.s_axi_bvalid))", 
                                                             "tb/board_a/tb_board_a_top.sv", 
                                                             113);
    }
    Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(vlSelf, 
                                                          "@(posedge tb_board_a_top.clk)");
    co_await vlSelfRef.__VtrigSched_h6fd192e6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_top.clk)", 
                                                         "tb/board_a/tb_board_a_top.sv", 
                                                         114);
    vlSelfRef.tb_board_a_top__DOT__s_axi_awvalid = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_wvalid = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_bready = 1U;
    while ((1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid)))) {
        Vtb_board_a_top___024root____VbeforeTrig_h43444ce6__0(vlSelf, 
                                                              "@( tb_board_a_top.s_axi_bvalid)");
        co_await vlSelfRef.__VtrigSched_h43444ce6__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_board_a_top.s_axi_bvalid)", 
                                                             "tb/board_a/tb_board_a_top.sv", 
                                                             118);
    }
    Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(vlSelf, 
                                                          "@(posedge tb_board_a_top.clk)");
    co_await vlSelfRef.__VtrigSched_h6fd192e6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_top.clk)", 
                                                         "tb/board_a/tb_board_a_top.sv", 
                                                         119);
    vlSelfRef.tb_board_a_top__DOT__s_axi_bready = 0U;
    tb_board_a_top__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0x00013880U;
    while (VL_LTS_III(32, 0U, tb_board_a_top__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
        Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(vlSelf, 
                                                              "@(posedge tb_board_a_top.clk)");
        co_await vlSelfRef.__VtrigSched_h6fd192e6__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_board_a_top.clk)", 
                                                             "tb/board_a/tb_board_a_top.sv", 
                                                             163);
        tb_board_a_top__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1 
            = (tb_board_a_top__DOT__unnamedblk1__DOT__unnamedblk1_2__DOT____Vrepeat1 
               - (IData)(1U));
    }
    __Vtask_tb_board_a_top__DOT__axi_read__2__addr = 0xf8U;
    __Vtask_tb_board_a_top__DOT__axi_read__2__data = 0;
    Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(vlSelf, 
                                                          "@(posedge tb_board_a_top.clk)");
    co_await vlSelfRef.__VtrigSched_h6fd192e6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_top.clk)", 
                                                         "tb/board_a/tb_board_a_top.sv", 
                                                         124);
    vlSelfRef.tb_board_a_top__DOT__s_axi_araddr = __Vtask_tb_board_a_top__DOT__axi_read__2__addr;
    vlSelfRef.tb_board_a_top__DOT__s_axi_arvalid = 1U;
    while (vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid) {
        Vtb_board_a_top___024root____VbeforeTrig_h950459ef__0(vlSelf, 
                                                              "@( (~ tb_board_a_top.s_axi_rvalid))");
        co_await vlSelfRef.__VtrigSched_h950459ef__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( (~ tb_board_a_top.s_axi_rvalid))", 
                                                             "tb/board_a/tb_board_a_top.sv", 
                                                             127);
    }
    Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(vlSelf, 
                                                          "@(posedge tb_board_a_top.clk)");
    co_await vlSelfRef.__VtrigSched_h6fd192e6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_top.clk)", 
                                                         "tb/board_a/tb_board_a_top.sv", 
                                                         128);
    vlSelfRef.tb_board_a_top__DOT__s_axi_arvalid = 0U;
    vlSelfRef.tb_board_a_top__DOT__s_axi_rready = 1U;
    while ((1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid)))) {
        Vtb_board_a_top___024root____VbeforeTrig_hc95c02d3__0(vlSelf, 
                                                              "@( tb_board_a_top.s_axi_rvalid)");
        co_await vlSelfRef.__VtrigSched_hc95c02d3__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_board_a_top.s_axi_rvalid)", 
                                                             "tb/board_a/tb_board_a_top.sv", 
                                                             131);
    }
    __Vtask_tb_board_a_top__DOT__axi_read__2__data 
        = vlSelfRef.tb_board_a_top__DOT__s_axi_rdata;
    Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(vlSelf, 
                                                          "@(posedge tb_board_a_top.clk)");
    co_await vlSelfRef.__VtrigSched_h6fd192e6__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_board_a_top.clk)", 
                                                         "tb/board_a/tb_board_a_top.sv", 
                                                         133);
    vlSelfRef.tb_board_a_top__DOT__s_axi_rready = 0U;
    vlSelfRef.tb_board_a_top__DOT__unnamedblk1__DOT__q 
        = __Vtask_tb_board_a_top__DOT__axi_read__2__data;
    __Vtask_tb_board_a_top__DOT__check__3__cond = (0U 
                                                   < vlSelfRef.tb_board_a_top__DOT__unnamedblk1__DOT__q);
    vlSelfRef.__Vtask_tb_board_a_top__DOT__check__3__msg = "quotes_sent non-zero"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_board_a_top__DOT__check__3__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_board_a_top.sv:101: Assertion failed in %Ntb_board_a_top.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_board_a_top__DOT__check__3__msg));
        VL_STOP_MT("tb/board_a/tb_board_a_top.sv", 101, "");
        vlSelfRef.tb_board_a_top__DOT__err_count = 
            ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__err_count);
    }
    __Vtask_tb_board_a_top__DOT__check__4__cond = (1U 
                                                   & (((((0U 
                                                          != vlSelfRef.tb_board_a_top__DOT__dut__DOT__rx_error_count) 
                                                         << 5U) 
                                                        | (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__link_up) 
                                                            << 4U) 
                                                           | (((2U 
                                                                == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state)) 
                                                               & (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__blink_ctr 
                                                                  >> 0x00000018U)) 
                                                              << 3U))) 
                                                       | (((2U 
                                                            == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state)) 
                                                           << 2U) 
                                                          | (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime))) 
                                                      >> 2U));
    vlSelfRef.__Vtask_tb_board_a_top__DOT__check__4__msg = "running LED"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_board_a_top__DOT__check__4__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_board_a_top.sv:101: Assertion failed in %Ntb_board_a_top.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_board_a_top__DOT__check__4__msg));
        VL_STOP_MT("tb/board_a/tb_board_a_top.sv", 101, "");
        vlSelfRef.tb_board_a_top__DOT__err_count = 
            ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__err_count);
    }
    if ((0U == vlSelfRef.tb_board_a_top__DOT__err_count)) {
        VL_WRITEF_NX("tb_board_a_top: PASS (quotes_sent=%0#)\n",0,
                     32,vlSelfRef.tb_board_a_top__DOT__unnamedblk1__DOT__q);
    } else {
        VL_WRITEF_NX("tb_board_a_top: FAIL (%0d errors)\n",0,
                     32,vlSelfRef.tb_board_a_top__DOT__err_count);
    }
    VL_FINISH_MT("tb/board_a/tb_board_a_top.sv", 173, "");
    co_return;
}

VlCoroutine Vtb_board_a_top___024root___eval_initial__TOP__Vtiming__2(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "tb/board_a/tb_board_a_top.sv", 
                                             56);
        vlSelfRef.tb_board_a_top__DOT__clk = (1U & 
                                              (~ (IData)(vlSelfRef.tb_board_a_top__DOT__clk)));
    }
    co_return;
}

void Vtb_board_a_top___024root___eval_triggers_vec__act(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_triggers_vec__act\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vtrigprevexpr_h972aab23__0;
    __Vtrigprevexpr_h972aab23__0 = 0;
    CData/*0:0*/ __Vtrigprevexpr_h113370fe__0;
    __Vtrigprevexpr_h113370fe__0 = 0;
    // Body
    __Vtrigprevexpr_h972aab23__0 = (1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid)));
    __Vtrigprevexpr_h113370fe__0 = (1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid)));
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((((((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid) 
                                                          != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_rvalid__0)) 
                                                         << 3U) 
                                                        | (((IData)(__Vtrigprevexpr_h113370fe__0) 
                                                            != (IData)(vlSelfRef.__Vtrigprevexpr_h113370fe__1)) 
                                                           << 2U)) 
                                                       | ((((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid) 
                                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_bvalid__0)) 
                                                           << 1U) 
                                                          | ((IData)(__Vtrigprevexpr_h972aab23__0) 
                                                             != (IData)(vlSelfRef.__Vtrigprevexpr_h972aab23__1)))) 
                                                      << 4U) 
                                                     | (((((IData)(vlSelfRef.tb_board_a_top__DOT__rst_n) 
                                                           != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__rst_n__0)) 
                                                          << 3U) 
                                                         | (vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                            << 2U)) 
                                                        | ((((~ (IData)(vlSelfRef.tb_board_a_top__DOT__rst_n)) 
                                                             & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__rst_n__0)) 
                                                            << 1U) 
                                                           | ((IData)(vlSelfRef.tb_board_a_top__DOT__clk) 
                                                              & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__clk__0))))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__clk__0 
        = vlSelfRef.tb_board_a_top__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__rst_n__0 
        = vlSelfRef.tb_board_a_top__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr_h972aab23__1 = __Vtrigprevexpr_h972aab23__0;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_bvalid__0 
        = vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid;
    vlSelfRef.__Vtrigprevexpr_h113370fe__1 = __Vtrigprevexpr_h113370fe__0;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_rvalid__0 
        = vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid;
}

bool Vtb_board_a_top___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___trigger_anySet__act\n"); );
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

void Vtb_board_a_top___024root___act_comb__TOP__0(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___act_comb__TOP__0\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0;
    QData/*63:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c = 0;
    // Body
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__tx_ready 
        = ((~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st)) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__pmod_ja_ready));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__read_fire 
        = ((~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid)) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_arvalid));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__write_fire 
        = ((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awvalid) 
           & ((~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid)) 
              & (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_wvalid)));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime 
        = (3U & ((4U & (IData)(vlSelfRef.tb_board_a_top__DOT__sw))
                  ? (IData)(vlSelfRef.tb_board_a_top__DOT__sw)
                  : (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__regime_from_ps)));
    if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)) 
                               << 2U) | (((1U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)) 
                                          << 1U) | 
                                         (0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)))))))) {
        if ((0U != (((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)) 
                     << 2U) | (((1U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)) 
                                << 1U) | (0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: market_sim.sv:72: Assertion failed in %Ntb_board_a_top.dut.u_market_sim: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime));
                VL_STOP_MT("rtl/board_a/market_sim.sv", 72, "");
            }
        }
    }
    if ((0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime))) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00000100U;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00002000U;
    } else if ((1U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime))) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00001000U;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00008000U;
    } else if ((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime))) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00000100U;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00002000U;
    } else {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00004000U;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00010000U;
    }
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c = 0ULL;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[0U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[1U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[2U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U] = 0U;
    if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c 
            = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out
                                            [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr]), 
                          VL_EXTENDS_QI(64,32, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16));
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c 
            = (IData)(VL_SHIFTRS_QQI(64,64,32, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c, 0x00000010U));
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price
            [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr];
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c 
            = (tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c 
               + tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c);
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c 
            = (VL_GTS_III(32, 0x00010000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c)
                                  ? 0x27100000U : tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c 
            = tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16;
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c)) {
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c = 1U;
        }
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c 
            = VL_SHIFTRS_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c, 1U);
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c 
            = (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c 
               - tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c);
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c 
            = (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c 
               + tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c);
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c)
                                  ? 0x27100000U : tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c)
                                  ? 0x27100000U : tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U] 
            = ((0x0003ffffU & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U]) 
               | (0xfffc0000U & (0x10000000U | (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr) 
                                                 << 0x00000014U) 
                                                | ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime) 
                                                   << 0x00000012U)))));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[0U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                << 0x00000010U) | vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num
               [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr]);
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[1U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                >> 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   << 0x00000010U));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[2U] 
            = (((IData)((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c))) 
                << 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   >> 0x00000010U));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U] 
            = ((0xfffc0000U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U]) 
               | (((IData)((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c))) 
                   >> 0x00000010U) | ((IData)(((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c)) 
                                               >> 0x00000020U)) 
                                      << 0x00000010U)));
    }
}

void Vtb_board_a_top___024root___eval_act(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_act\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((0x00000000000000f9ULL & vlSelfRef.__VactTriggered[0U])) {
        Vtb_board_a_top___024root___act_comb__TOP__0(vlSelf);
    }
}

extern const VlUnpacked<CData/*1:0*/, 32> Vtb_board_a_top__ConstPool__TABLE_hbfde2c6f_0;

void Vtb_board_a_top___024root___nba_sequent__TOP__0(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___nba_sequent__TOP__0\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<IData/*31:0*/, 16> tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread;
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[__Vi0] = 0;
    }
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv;
    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv = 0;
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv;
    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 0;
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv;
    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv = 0;
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv;
    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv = 0;
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv;
    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv = 0;
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv;
    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv = 0;
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv;
    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 0;
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv;
    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv = 0;
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv;
    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv = 0;
    IData/*31:0*/ __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv;
    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0;
    QData/*63:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta = 0;
    QData/*63:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r = 0;
    CData/*7:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base = 0;
    QData/*63:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r = 0;
    CData/*5:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__12__Vfuncout;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__12__Vfuncout = 0;
    CData/*5:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__12__p;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__12__p = 0;
    CData/*5:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__13__Vfuncout;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__13__Vfuncout = 0;
    CData/*5:0*/ __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__13__p;
    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__13__p = 0;
    CData/*4:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__s_axi_bvalid;
    __Vdly__tb_board_a_top__DOT__s_axi_bvalid = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__s_axi_rvalid;
    __Vdly__tb_board_a_top__DOT__s_axi_rvalid = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0 = 0;
    IData/*16:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__btn_out_prev;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__btn_out_prev = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1 = 0;
    IData/*16:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__btn_out_prev;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__btn_out_prev = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2 = 0;
    IData/*16:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__btn_out_prev;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__btn_out_prev = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__quotes_generated;
    __Vdly__tb_board_a_top__DOT__dut__DOT__quotes_generated = 0;
    CData/*3:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 0;
    CData/*5:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr = 0;
    CData/*5:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr = 0;
    CData/*6:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid = 0;
    CData/*7:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_symbol;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_symbol = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side = 0;
    SData/*15:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id = 0;
    SData/*15:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__orders_rcvd;
    __Vdly__tb_board_a_top__DOT__dut__DOT__orders_rcvd = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__fill_valid;
    __Vdly__tb_board_a_top__DOT__dut__DOT__fill_valid = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__fills_sent;
    __Vdly__tb_board_a_top__DOT__dut__DOT__fills_sent = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__rejects_sent;
    __Vdly__tb_board_a_top__DOT__dut__DOT__rejects_sent = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st = 0;
    IData/*31:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__rx_error_count;
    __Vdly__tb_board_a_top__DOT__dut__DOT__rx_error_count = 0;
    CData/*4:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count = 0;
    CData/*0:0*/ __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0 = 0;
    CData/*3:0*/ __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0;
    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0 = 0;
    CData/*3:0*/ __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0;
    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0 = 0;
    CData/*2:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0 = 0;
    CData/*3:0*/ __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0;
    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0 = 0;
    SData/*15:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0 = 0;
    CData/*3:0*/ __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0;
    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0 = 0;
    SData/*15:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1 = 0;
    CData/*3:0*/ __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1;
    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v1;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v0;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v0;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v0;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v1;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v1 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v1;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v1;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v2;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v2 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v2;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v2 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v2;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v2 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v3;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v3 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v3;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v3 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v3;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v3 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v0;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v4;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v4 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v4;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v4 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v0;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v5;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v5 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v5;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v5 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v6;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v6 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v6;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v6 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v6;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v6 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v7;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v7 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v7;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v7 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v7;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v7 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v8;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v8 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v8;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v8 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v8;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v8 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v9;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v9 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v9;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v9 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v9;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v9 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v10;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v10 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v10;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v10 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v10;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v10 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v1;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v11;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v11 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v11;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v11 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v1;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v1 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v12;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v12 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v12;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v12 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v13;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v13 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v13;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v13 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v13;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v13 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v14;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v14 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v14;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v14 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v14;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v14 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v15;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v15 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v15;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v15 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v15;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v15 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v2;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v2 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v2;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v2 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v2;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v2 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v3;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v3 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v3;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v3 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v3;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v3 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v4;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v4 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v4;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v4 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v4;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v4 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v5;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v5 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v5;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v5 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v5;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v5 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v6;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v6 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v6;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v6 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v6;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v6 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v7;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v7 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v7;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v7 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v7;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v7 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v8;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v8 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v8;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v8 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v8;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v8 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v9;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v9 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v9;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v9 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v9;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v9 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v10;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v10 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v10;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v10 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v10;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v10 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v11;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v11 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v11;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v11 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v11;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v11 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v12;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v12 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v12;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v12 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v12;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v12 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v13;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v13 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v13;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v13 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v13;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v13 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v14;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v14 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v14;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v14 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v14;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v14 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v15;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v15 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v15;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v15 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v15;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v15 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16 = 0;
    CData/*3:0*/ __VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16;
    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v16;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v16 = 0;
    CData/*3:0*/ __VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v16;
    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v16 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v16;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v16 = 0;
    CData/*3:0*/ __VdlyDim0__tb_board_a_top__DOT__dut__DOT__best_bid__v16;
    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__best_bid__v16 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v16;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v16 = 0;
    CData/*3:0*/ __VdlyDim0__tb_board_a_top__DOT__dut__DOT__best_ask__v16;
    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__best_ask__v16 = 0;
    SData/*15:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num__v16;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num__v16 = 0;
    CData/*3:0*/ __VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num__v16;
    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num__v16 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v17;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v17 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v17;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v17 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v17;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v17 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v18;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v18 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v18;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v18 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v18;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v18 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v19;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v19 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v19;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v19 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v19;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v19 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v20;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v20 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v20;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v20 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v20;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v20 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v17;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v17 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v21;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v21 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v21;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v21 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v17;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v17 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v22;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v22 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v22;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v22 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v23;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v23 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v23;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v23 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v23;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v23 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v24;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v24 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v24;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v24 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v24;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v24 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v25;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v25 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v25;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v25 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v25;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v25 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v26;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v26 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v26;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v26 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v26;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v26 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v27;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v27 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v27;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v27 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v27;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v27 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v18;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v18 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v28;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v28 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v28;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v28 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v18;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v18 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v29;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v29 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v29;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v29 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v30;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v30 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v30;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v30 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v30;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v30 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v31;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v31 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v31;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v31 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v31;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v31 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v32;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v32 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v32;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v32 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v32;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v32 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v19;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v19 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v19;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v19 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v19;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v19 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v20;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v20 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v20;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v20 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v20;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v20 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v21;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v21 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v21;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v21 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v21;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v21 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v22;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v22 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v22;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v22 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v22;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v22 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v23;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v23 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v23;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v23 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v23;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v23 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v24;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v24 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v24;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v24 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v24;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v24 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v25;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v25 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v25;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v25 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v25;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v25 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v26;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v26 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v26;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v26 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v26;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v26 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v27;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v27 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v27;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v27 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v27;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v27 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v28;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v28 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v28;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v28 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v28;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v28 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v29;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v29 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v29;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v29 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v29;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v29 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v30;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v30 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v30;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v30 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v30;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v30 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v31;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v31 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v31;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v31 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v31;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v31 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v32;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v32 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v32;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v32 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v32;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v32 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v0;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v0 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v16;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v16 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v16;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v16 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v17;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v17 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v17;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v17 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v18;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v18 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v18;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v18 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v19;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v19 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v19;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v19 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v20;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v20 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v20;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v20 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v21;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v21 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v21;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v21 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v22;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v22 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v22;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v22 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v23;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v23 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v23;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v23 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v24;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v24 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v24;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v24 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v25;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v25 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v25;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v25 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v26;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v26 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v26;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v26 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v27;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v27 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v27;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v27 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v28;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v28 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v28;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v28 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v29;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v29 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v29;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v29 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v30;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v30 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v30;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v30 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v31;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v31 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v31;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v31 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14 = 0;
    IData/*31:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15;
    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v16;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v16 = 0;
    VlWide<4>/*127:0*/ __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0;
    VL_ZERO_W(128, __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0);
    CData/*5:0*/ __VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0;
    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0 = 0;
    VlWide<4>/*127:0*/ __Vtemp_1;
    // Body
    __Vdly__tb_board_a_top__DOT__s_axi_rvalid = vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid;
    __Vdly__tb_board_a_top__DOT__s_axi_bvalid = vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__btn_out_prev 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__btn_out_prev;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__btn_out_prev 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__btn_out_prev;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__btn_out_prev 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__btn_out_prev;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    __Vdly__tb_board_a_top__DOT__dut__DOT__quotes_generated 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__quotes_generated;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0 = 0U;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r;
    __Vdly__tb_board_a_top__DOT__dut__DOT__rx_error_count 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__rx_error_count;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_symbol 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_symbol;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp;
    __Vdly__tb_board_a_top__DOT__dut__DOT__orders_rcvd 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__orders_rcvd;
    __Vdly__tb_board_a_top__DOT__dut__DOT__fills_sent 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__fills_sent;
    __Vdly__tb_board_a_top__DOT__dut__DOT__rejects_sent 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__rejects_sent;
    __Vdly__tb_board_a_top__DOT__dut__DOT__fill_valid 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_valid;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v1 = 0U;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v16 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v17 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v18 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v19 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v20 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v21 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v22 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v23 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v24 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v25 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v26 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v27 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v28 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v29 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v30 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v31 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v0 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v16 = 0U;
    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v2 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v3 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v4 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v5 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v6 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v7 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v8 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v9 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v10 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v11 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v12 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v13 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v14 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v15 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v19 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v20 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v21 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v22 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v23 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v24 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v25 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v26 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v27 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v28 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v29 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v30 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v31 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v32 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v0 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v1 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v2 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v6 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v7 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v8 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v9 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v13 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v14 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v15 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v17 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v18 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v19 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v23 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v24 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v25 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v26 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v30 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v31 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v32 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v3 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v10 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v20 = 0U;
    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v27 = 0U;
    if (vlSelfRef.tb_board_a_top__DOT__rst_n) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__blink_ctr 
            = (0x01ffffffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__blink_ctr));
        if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__read_fire) {
            __Vdly__tb_board_a_top__DOT__s_axi_rvalid = 1U;
        } else if (((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid) 
                    & (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_rready))) {
            __Vdly__tb_board_a_top__DOT__s_axi_rvalid = 0U;
        }
        if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__write_fire) {
            __Vdly__tb_board_a_top__DOT__s_axi_bvalid = 1U;
        } else if (((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid) 
                    & (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_bready))) {
            __Vdly__tb_board_a_top__DOT__s_axi_bvalid = 0U;
        }
        if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_load) {
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0xc13fa9a9U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0xc13fa9a9U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x5f772362U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x5f772362U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0xfdae9d1bU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0xfdae9d1bU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x9be616d4U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x9be616d4U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x3a1d908dU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x3a1d908dU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0xd8550a46U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0xd8550a46U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x768c83ffU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x768c83ffU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                = ((0U == (0x14c3fdb8U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x14c3fdb8U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg 
                = ((0U == (0xa11fe511U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0xa11fe511U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x9e3779b9U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x9e3779b9U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x3c6ef372U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x3c6ef372U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0xdaa66d2bU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0xdaa66d2bU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x78dde6e4U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x78dde6e4U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x1715609dU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x1715609dU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0xb54cda56U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0xb54cda56U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x5384540fU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x5384540fU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0xf1bbcdc8U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0xf1bbcdc8U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x8ff34781U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x8ff34781U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x2e2ac13aU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x2e2ac13aU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0xcc623af3U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0xcc623af3U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x6a99b4acU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x6a99b4acU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x08d12e65U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x08d12e65U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0xa708a81eU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0xa708a81eU ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0x454021d7U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0x454021d7U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                = ((0U == (0xe3779b90U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed))
                    ? 1U : (0xe3779b90U ^ vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed));
        } else {
            if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg, 1U));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (0U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (1U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (2U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (3U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (4U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (5U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (6U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (7U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (8U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (9U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (0x0aU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (0x0bU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (0x0cU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (0x0dU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (0x0eU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable) 
                 & (0x0fU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
                    = ((1U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg)
                        ? (0x00400007U ^ VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U))
                        : VL_SHIFTR_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg, 1U));
            }
        }
        if ((0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))) {
            __Vdly__tb_board_a_top__DOT__dut__DOT__quotes_generated = 0U;
        } else if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_load) {
            __Vdly__tb_board_a_top__DOT__dut__DOT__quotes_generated = 0U;
        } else if ((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))) {
            if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__quotes_generated 
                    = ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__quotes_generated);
            }
        }
        if ((0U != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))) {
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_ctr 
                = ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_load)
                    ? 0U : ((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))
                             ? ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__tick_raw)
                                 ? ((0x40U != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r))
                                     ? 0U : vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_ctr)
                                 : ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_ctr))
                             : 0U));
        }
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__blink_ctr = 0U;
        __Vdly__tb_board_a_top__DOT__s_axi_rvalid = 0U;
        __Vdly__tb_board_a_top__DOT__s_axi_bvalid = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = 1U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__quotes_generated = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_ctr = 0U;
    }
    if (vlSelfRef.tb_board_a_top__DOT__rst_n) {
        if ((0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))) {
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r = 0U;
        } else {
            if ((2U == ((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_wr_en) 
                          & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_full))) 
                         << 1U) | ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_rd_en) 
                                   & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_empty)))))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r 
                    = (0x0000007fU & ((IData)(1U) + (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r)));
            } else if ((1U == ((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_wr_en) 
                                 & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_full))) 
                                << 1U) | ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_rd_en) 
                                          & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_empty)))))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r 
                    = (0x0000007fU & ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r) 
                                      - (IData)(1U)));
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_rd_en) 
                 & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_empty)))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__13__p 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__13__Vfuncout 
                    = ((0x3fU == (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__13__p))
                        ? 0U : (0x0000003fU & ((IData)(1U) 
                                               + (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__13__p))));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__13__Vfuncout;
            }
            if ((1U & (~ VL_ONEHOT_I((((1U == ((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_wr_en) 
                                                 & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_full))) 
                                                << 1U) 
                                               | ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_rd_en) 
                                                  & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_empty))))) 
                                       << 1U) | (2U 
                                                 == 
                                                 ((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_wr_en) 
                                                    & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_full))) 
                                                   << 1U) 
                                                  | ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_rd_en) 
                                                     & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_empty)))))))))) {
                if ((0U != (((1U == ((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_wr_en) 
                                       & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_full))) 
                                      << 1U) | ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_rd_en) 
                                                & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_empty))))) 
                             << 1U) | (2U == ((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_wr_en) 
                                                & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_full))) 
                                               << 1U) 
                                              | ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_rd_en) 
                                                 & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_empty)))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: sync_fifo.sv:61: Assertion failed in %Ntb_board_a_top.dut.u_quote_fifo: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_wr_en) 
                                          & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_full))) 
                                         << 1U) | ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_rd_en) 
                                                   & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_empty)))));
                        VL_STOP_MT("rtl/shared/sync_fifo.sv", 61, "");
                    }
                }
            }
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_wr_en) 
                 & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_full)))) {
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0[0U] 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[0U];
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0[1U] 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[1U];
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0[2U] 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[2U];
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0[3U] 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[3U];
                __VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0 = 1U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__12__p 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__12__Vfuncout 
                    = ((0x3fU == (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__12__p))
                        ? 0U : (0x0000003fU & ((IData)(1U) 
                                               + (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__12__p))));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__ptr_next__12__Vfuncout;
            }
        }
    } else {
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r = 0U;
    }
    if (vlSelfRef.tb_board_a_top__DOT__rst_n) {
        if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st) {
            if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__half_nibble) {
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__half_nibble = 0U;
                if ((0x1fU == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__beat))) {
                    __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st = 0U;
                } else {
                    __Vtemp_1[1U] = ((vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[0U] 
                                      >> 0x0000001cU) 
                                     | (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[1U] 
                                        << 4U));
                    __Vtemp_1[2U] = ((vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[1U] 
                                      >> 0x0000001cU) 
                                     | (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[2U] 
                                        << 4U));
                    __Vtemp_1[3U] = ((vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[2U] 
                                      >> 0x0000001cU) 
                                     | (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[3U] 
                                        << 4U));
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[0U] 
                        = (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[0U] 
                           << 4U);
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[1U] 
                        = __Vtemp_1[1U];
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[2U] 
                        = __Vtemp_1[2U];
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[3U] 
                        = __Vtemp_1[3U];
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__beat 
                        = (0x0000001fU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__beat)));
                }
            } else {
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__half_nibble = 1U;
            }
        } else if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid) 
                    & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__tx_ready))) {
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[0U] 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[0U];
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[1U] 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[1U];
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[2U] 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[2U];
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[3U] 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[3U];
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__beat = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__half_nibble = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st = 1U;
        }
        if ((1U & (~ VL_ONEHOT_I((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st) 
                                   << 1U) | (1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st)))))))) {
            if ((0U != (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st) 
                         << 1U) | (1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st)))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: link_tx.sv:49: Assertion failed in %Ntb_board_a_top.dut.u_link_tx: unique case, but multiple matches found for '1'h%x'\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name(),
                                 1,(IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st));
                    VL_STOP_MT("rtl/link/link_tx.sv", 49, "");
                }
            }
        }
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter[3U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__beat = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__half_nibble = 0U;
    }
    if (vlSelfRef.tb_board_a_top__DOT__rst_n) {
        if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_load) {
            __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v0 = 1U;
        } else if (((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state)) 
                    & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote))) {
            if ((0U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[0U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel0;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel0;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel0: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v16 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v16 = 1U;
            }
            if ((1U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[1U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel1;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel1;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel1: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v17 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v17 = 1U;
            }
            if ((2U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[2U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel2;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel2;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel2: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v18 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v18 = 1U;
            }
            if ((3U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[3U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel3;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel3;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel3: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v19 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v19 = 1U;
            }
            if ((4U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[4U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[4U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel4;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel4;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel4: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v20 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v20 = 1U;
            }
            if ((5U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[5U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[5U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel5;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel5;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel5: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v21 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v21 = 1U;
            }
            if ((6U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[6U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[6U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel6;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel6;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel6: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v22 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v22 = 1U;
            }
            if ((7U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[7U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[7U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel7;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel7;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel7: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v23 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v23 = 1U;
            }
            if ((8U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[8U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[8U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel8;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel8;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel8: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v24 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v24 = 1U;
            }
            if ((9U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[9U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[9U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel9;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel9;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel9: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v25 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v25 = 1U;
            }
            if ((0x0aU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[10U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[10U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel10;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel10;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel10: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v26 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v26 = 1U;
            }
            if ((0x0bU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[11U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[11U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel11;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel11;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel11: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v27 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v27 = 1U;
            }
            if ((0x0cU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[12U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[12U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel12;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel12;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel12: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v28 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v28 = 1U;
            }
            if ((0x0dU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[13U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[13U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel13;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel13;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel13: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v29 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v29 = 1U;
            }
            if ((0x0eU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[14U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[14U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel14;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel14;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel14: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v30 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v30 = 1U;
            }
            if ((0x0fU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos = 0x02000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg = 0xfe000000U;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[15U];
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__r 
                                                                 >> 6U))) 
                                               - (IData)(0x00000020U)), 3U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__company_tick_delta__8__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[15U];
                {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s = 0;
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s 
                        = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__acc) 
                           + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__delta));
                    if (VL_GTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_pos;
                        goto __Vlabel15;
                    }
                    if (VL_LTS_IQQ(64, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s, 
                                   VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg))) {
                        __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                            = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__lim_neg;
                        goto __Vlabel15;
                    }
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout 
                        = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__s);
                    __Vlabel15: ;
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v31 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__7__Vfuncout;
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v31 = 1U;
            }
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[0U];
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[0U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x7fffffffU;
                    goto __Vlabel16;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x80000000U;
                    goto __Vlabel16;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod);
                __Vlabel16: ;
            }
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[0U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0x02000000U;
                    goto __Vlabel17;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0xfe000000U;
                    goto __Vlabel17;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s);
                __Vlabel17: ;
            }
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout;
            __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8 = 1U;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[1U];
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[1U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x7fffffffU;
                    goto __Vlabel18;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x80000000U;
                    goto __Vlabel18;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod);
                __Vlabel18: ;
            }
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[1U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0x02000000U;
                    goto __Vlabel19;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0xfe000000U;
                    goto __Vlabel19;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s);
                __Vlabel19: ;
            }
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout;
            __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9 = 1U;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[2U];
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[2U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x7fffffffU;
                    goto __Vlabel20;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x80000000U;
                    goto __Vlabel20;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod);
                __Vlabel20: ;
            }
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[2U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0x02000000U;
                    goto __Vlabel21;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0xfe000000U;
                    goto __Vlabel21;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s);
                __Vlabel21: ;
            }
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout;
            __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10 = 1U;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[3U];
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[3U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x7fffffffU;
                    goto __Vlabel22;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x80000000U;
                    goto __Vlabel22;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod);
                __Vlabel22: ;
            }
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[3U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0x02000000U;
                    goto __Vlabel23;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0xfe000000U;
                    goto __Vlabel23;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s);
                __Vlabel23: ;
            }
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout;
            __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11 = 1U;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[4U];
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[4U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x7fffffffU;
                    goto __Vlabel24;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x80000000U;
                    goto __Vlabel24;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod);
                __Vlabel24: ;
            }
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[4U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0x02000000U;
                    goto __Vlabel25;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0xfe000000U;
                    goto __Vlabel25;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s);
                __Vlabel25: ;
            }
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout;
            __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12 = 1U;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[5U];
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[5U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x7fffffffU;
                    goto __Vlabel26;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x80000000U;
                    goto __Vlabel26;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod);
                __Vlabel26: ;
            }
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[5U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0x02000000U;
                    goto __Vlabel27;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0xfe000000U;
                    goto __Vlabel27;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s);
                __Vlabel27: ;
            }
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout;
            __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13 = 1U;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[6U];
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[6U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x7fffffffU;
                    goto __Vlabel28;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x80000000U;
                    goto __Vlabel28;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod);
                __Vlabel28: ;
            }
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[6U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0x02000000U;
                    goto __Vlabel29;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0xfe000000U;
                    goto __Vlabel29;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s);
                __Vlabel29: ;
            }
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout;
            __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14 = 1U;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[7U];
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[7U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__r;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout 
                    = VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                             (0x0000003fU 
                                                              & (__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__r 
                                                                 >> 0x0cU))) 
                                               - (IData)(0x00000020U)), 2U);
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base 
                    = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_base_delta__11__Vfuncout;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod 
                    = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__base), 
                                  VL_EXTENDS_QI(64,32, (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__pop)));
                if (VL_LTS_IQQ(64, 0x000000007fffffffULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x7fffffffU;
                    goto __Vlabel30;
                }
                if (VL_GTS_IQQ(64, 0xffffffff80000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout = 0x80000000U;
                    goto __Vlabel30;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__prod);
                __Vlabel30: ;
            }
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_scaled_delta__10__Vfuncout;
            __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[7U];
            {
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s = 0;
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s 
                    = (VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__acc) 
                       + VL_EXTENDS_QI(64,32, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__delta));
                if (VL_LTS_IQQ(64, 0x0000000002000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0x02000000U;
                    goto __Vlabel31;
                }
                if (VL_GTS_IQQ(64, 0xfffffffffe000000ULL, __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s)) {
                    __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout = 0xfe000000U;
                    goto __Vlabel31;
                }
                __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout 
                    = (IData)(__Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__s);
                __Vlabel31: ;
            }
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15 
                = __Vfunc_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__add_sat32__9__Vfuncout;
            __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15 = 1U;
        }
    } else {
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v16 = 1U;
    }
    vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid = __Vdly__tb_board_a_top__DOT__s_axi_rvalid;
    vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid = __Vdly__tb_board_a_top__DOT__s_axi_bvalid;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st;
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v0) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[3U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[4U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[5U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[6U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[7U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[4U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[5U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[6U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[7U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[8U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[9U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[10U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[11U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[12U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[13U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[14U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[15U] = 0U;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[0U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v8;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[1U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v9;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[2U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v10;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[3U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v11;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[4U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v12;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[5U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v13;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[6U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v14;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[7U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v15;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v16) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v16;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v17) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v17;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v18) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v18;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v19) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v19;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v20) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[4U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v20;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v21) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[5U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v21;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v22) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[6U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v22;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v23) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[7U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v23;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v24) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[8U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v24;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v25) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[9U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v25;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v26) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[10U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v26;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v27) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[11U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v27;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v28) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[12U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v28;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v29) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[13U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v29;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v30) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[14U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v30;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v31) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[15U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16__v31;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16__v16) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[3U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[4U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[5U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[6U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[7U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[4U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[5U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[6U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[7U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[8U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[9U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[10U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[11U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[12U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[13U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[14U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[15U] = 0U;
    }
    if (vlSelfRef.tb_board_a_top__DOT__rst_n) {
        if ((0U != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))) {
            if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_load) {
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[0U];
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr = 0U;
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v0 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[0U];
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v0 = 1U;
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[0U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v0 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v0 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[0U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[0U];
                }
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v1 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[1U];
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v1 = 1U;
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[1U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v1 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v1 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[1U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[1U];
                }
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v2 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[2U];
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v2 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v3 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[3U];
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v3 = 1U;
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v4 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[4U];
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v5 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[5U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[1U];
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v6 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[6U];
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v6 = 1U;
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v7 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[7U];
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v7 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[2U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v2 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v2 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[2U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[2U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v8 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[8U];
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v8 = 1U;
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v0 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v9 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[9U];
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v9 = 1U;
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v0 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v10 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[10U];
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v10 = 1U;
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v11 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[11U];
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v12 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[12U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[2U];
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v13 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[13U];
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v13 = 1U;
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v14 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[14U];
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v14 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[3U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v3 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v3 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[3U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[3U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v15 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[15U];
                __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v15 = 1U;
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v1 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v1 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v2 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[3U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[4U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v4 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v4 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[4U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[4U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v2 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v2 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v3 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[4U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[5U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v5 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v5 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[5U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[5U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v3 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v3 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v4 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[5U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[6U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v6 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v6 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[6U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[6U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v4 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v4 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v5 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[6U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[7U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v7 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v7 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[7U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[7U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v5 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v5 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v6 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[7U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[8U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v8 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v8 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[8U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[8U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v6 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v6 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v7 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[8U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[9U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v9 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v9 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[9U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[9U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v7 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v7 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v8 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[9U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[10U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v10 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v10 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[10U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[10U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v8 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v8 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v9 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[10U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[11U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v11 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v11 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[11U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[11U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v9 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v9 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v10 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[11U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[12U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v12 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v12 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[12U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[12U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v10 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v10 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v11 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[12U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[13U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v13 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v13 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[13U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[13U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v11 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v11 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v12 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[13U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[14U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v14 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v14 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[14U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[14U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v12 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v12 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v13 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[14U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[15U])) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v15 = 1U;
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv = 1U;
                } else {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v15 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[15U];
                    __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[15U];
                }
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v13 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v13 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v14 = 1U;
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[15U];
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv 
                    = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_sv, 1U);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v14 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v15 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__bid_sv));
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v14 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv 
                    = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__mid_sv 
                       + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__spr_hv);
                __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v15 
                    = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                        ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv)
                                          ? 0x27100000U
                                          : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__5__ask_sv));
                __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v15 = 1U;
            } else if ((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))) {
                if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote) {
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c;
                    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr;
                    __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16 = 1U;
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v16 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c;
                    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v16 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr;
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v16 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c;
                    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__best_bid__v16 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr;
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v16 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c;
                    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__best_ask__v16 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr;
                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num__v16 
                        = (0x0000ffffU & ((IData)(1U) 
                                          + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num
                                          [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr]));
                    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num__v16 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr;
                    __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr 
                        = (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr) 
                            == (0x0000000fU & ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__active_count_eff) 
                                               - (IData)(1U))))
                            ? 0U : (0x0000000fU & ((IData)(1U) 
                                                   + (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr))));
                }
            }
        }
    } else {
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[0U];
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr = 0U;
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v17 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[0U];
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v17 = 1U;
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[0U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v17 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v17 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[0U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[0U];
        }
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v18 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[1U];
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v18 = 1U;
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[1U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v18 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v18 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[1U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[1U];
        }
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v19 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[2U];
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v19 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v20 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[3U];
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v20 = 1U;
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v21 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[4U];
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v22 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[5U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[1U];
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v23 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[6U];
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v23 = 1U;
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v24 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[7U];
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v24 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[2U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v19 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v19 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[2U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[2U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v25 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[8U];
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v25 = 1U;
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v17 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v26 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[9U];
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v26 = 1U;
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v17 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v27 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[10U];
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v27 = 1U;
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v28 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[11U];
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v29 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[12U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[2U];
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v30 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[13U];
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v30 = 1U;
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v31 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[14U];
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v31 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[3U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v20 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v20 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[3U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[3U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v32 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[15U];
        __VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v32 = 1U;
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v18 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v18 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v19 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[3U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[4U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v21 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v21 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[4U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[4U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v19 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v19 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v20 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[4U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[5U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v22 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v22 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[5U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[5U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v20 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v20 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v21 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[5U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[6U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v23 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v23 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[6U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[6U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v21 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v21 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v22 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[6U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[7U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v24 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v24 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[7U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[7U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v22 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v22 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v23 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[7U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[8U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v25 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v25 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[8U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[8U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v23 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v23 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v24 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[8U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[9U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v26 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v26 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[9U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[9U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v24 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v24 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v25 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[9U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[10U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v27 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v27 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[10U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[10U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v25 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v25 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v26 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[10U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[11U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v28 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v28 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[11U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[11U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v26 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v26 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v27 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[11U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[12U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v29 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v29 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[12U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[12U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v27 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v27 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v28 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[12U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[13U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v30 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v30 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[13U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[13U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v28 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v28 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v29 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[13U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[14U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v31 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v31 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[14U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[14U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v29 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v29 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v30 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[14U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[15U])) {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v32 = 1U;
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv = 1U;
        } else {
            __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v32 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[15U];
            __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv 
                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[15U];
        }
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v30 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v30 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v31 = 1U;
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[15U];
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv 
            = VL_SHIFTRS_III(32,32,32, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_sv, 1U);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v31 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               - __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v32 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__bid_sv));
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v31 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv 
            = (__Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__mid_sv 
               + __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__spr_hv);
        __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v32 
            = (VL_GTS_III(32, 0x00010000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv)
                                  ? 0x27100000U : __Vtask_tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__init_symbol_tables__6__ask_sv));
        __VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v32 = 1U;
    }
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr;
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v0) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[0U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v0;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[0U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v0;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v1) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[1U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v1;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[1U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v1;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v2) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[2U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v2;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[2U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v2;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v3) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[3U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v3;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[4U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v4;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[5U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v5;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[3U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[4U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[5U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[3U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v3;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[4U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v4;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[5U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v5;
    }
    if (vlSelfRef.tb_board_a_top__DOT__rst_n) {
        if (((1U & (IData)(vlSelfRef.tb_board_a_top__DOT__btn)) 
             != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0))) {
            if ((0x00010000U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter)) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0 
                    = (1U & (IData)(vlSelfRef.tb_board_a_top__DOT__btn));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter = 0U;
            } else {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter 
                    = (0x0001ffffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter));
            }
        } else {
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter = 0U;
        }
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__btn_out_prev 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p0 
            = ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0) 
               & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__btn_out_prev)));
        if (((1U & ((IData)(vlSelfRef.tb_board_a_top__DOT__btn) 
                    >> 1U)) != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1))) {
            if ((0x00010000U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter)) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1 
                    = (1U & ((IData)(vlSelfRef.tb_board_a_top__DOT__btn) 
                             >> 1U));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter = 0U;
            } else {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter 
                    = (0x0001ffffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter));
            }
        } else {
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter = 0U;
        }
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__btn_out_prev 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p1 
            = ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1) 
               & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__btn_out_prev)));
        if (((1U & ((IData)(vlSelfRef.tb_board_a_top__DOT__btn) 
                    >> 2U)) != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2))) {
            if ((0x00010000U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter)) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2 
                    = (1U & ((IData)(vlSelfRef.tb_board_a_top__DOT__btn) 
                             >> 2U));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter = 0U;
            } else {
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter 
                    = (0x0001ffffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter));
            }
        } else {
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter = 0U;
        }
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__btn_out_prev 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p2 
            = ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2) 
               & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__btn_out_prev)));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__axi_reset_pulse = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__axi_start_pulse = 0U;
        if ((0U != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))) {
            if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_load) {
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_valid_ms = 0U;
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[0U] = 0U;
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[1U] = 0U;
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[2U] = 0U;
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[3U] = 0U;
            } else {
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_valid_ms = 0U;
                if ((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))) {
                    if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote) {
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_valid_ms = 1U;
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[0U] 
                            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[0U];
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[1U] 
                            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[1U];
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[2U] 
                            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[2U];
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[3U] 
                            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U];
                    }
                }
            }
        }
        if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__write_fire) {
            if ((0U == (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__axi_reset_pulse 
                    = (1U & (vlSelfRef.tb_board_a_top__DOT__s_axi_wdata 
                             >> 1U));
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__axi_start_pulse 
                    = (1U & vlSelfRef.tb_board_a_top__DOT__s_axi_wdata);
            }
            if ((0U != (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                if ((4U != (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                    if ((8U != (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                        if ((0x0cU != (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                            if (((0x10U <= (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)) 
                                 & (0x50U > (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)))) {
                                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx 
                                    = VL_SHIFTR_III(32,32,32, 
                                                    ((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr) 
                                                     - (IData)(0x00000010U)), 2U);
                                if (VL_GTS_III(32, 0x00000010U, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx)) {
                                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0 
                                        = vlSelfRef.tb_board_a_top__DOT__s_axi_wdata;
                                    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0 
                                        = (0x0000000fU 
                                           & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx);
                                    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0 = 1U;
                                }
                            } else if (((0x50U <= (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)) 
                                        & (0x90U > (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)))) {
                                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx 
                                    = VL_SHIFTR_III(32,32,32, 
                                                    ((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr) 
                                                     - (IData)(0x00000050U)), 2U);
                                if (VL_GTS_III(32, 0x00000010U, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx)) {
                                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0 
                                        = ((0U == vlSelfRef.tb_board_a_top__DOT__s_axi_wdata)
                                            ? 1U : vlSelfRef.tb_board_a_top__DOT__s_axi_wdata);
                                    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0 
                                        = (0x0000000fU 
                                           & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx);
                                    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0 = 1U;
                                }
                            } else if (((0x90U <= (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)) 
                                        & (0xd0U > (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)))) {
                                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx 
                                    = VL_SHIFTR_III(32,32,32, 
                                                    ((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr) 
                                                     - (IData)(0x00000090U)), 2U);
                                if (VL_GTS_III(32, 0x00000010U, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx)) {
                                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0 
                                        = (7U & vlSelfRef.tb_board_a_top__DOT__s_axi_wdata);
                                    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0 
                                        = (0x0000000fU 
                                           & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx);
                                    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0 = 1U;
                                }
                            } else if (((0xd0U <= (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)) 
                                        & (0xf0U > (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)))) {
                                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__tok_idx 
                                    = (0x7ffffffeU 
                                       & VL_SHIFTR_III(32,32,32, 
                                                       ((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr) 
                                                        - (IData)(0x000000d0U)), 1U));
                                if (VL_GTS_III(32, 0x00000010U, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__tok_idx)) {
                                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0 
                                        = (0x0000ffffU 
                                           & vlSelfRef.tb_board_a_top__DOT__s_axi_wdata);
                                    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0 
                                        = (0x0000000fU 
                                           & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__tok_idx);
                                    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0 = 1U;
                                }
                                if (VL_GTS_III(32, 0x00000010U, 
                                               ((IData)(1U) 
                                                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__tok_idx))) {
                                    __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1 
                                        = (vlSelfRef.tb_board_a_top__DOT__s_axi_wdata 
                                           >> 0x10U);
                                    __VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1 
                                        = (0x0000000fU 
                                           & ((IData)(1U) 
                                              + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__tok_idx));
                                    __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1 = 1U;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__read_fire) {
            vlSelfRef.tb_board_a_top__DOT__s_axi_rdata = 0U;
            if ((4U == (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr))) {
                vlSelfRef.tb_board_a_top__DOT__s_axi_rdata 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_interval;
            } else if ((8U == (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr))) {
                vlSelfRef.tb_board_a_top__DOT__s_axi_rdata 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed;
            } else if ((0x0cU == (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr))) {
                vlSelfRef.tb_board_a_top__DOT__s_axi_rdata 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__regime_from_ps;
            } else if (((0x10U <= (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr)) 
                        & (0x50U > (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr)))) {
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx 
                    = VL_SHIFTR_III(32,32,32, ((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr) 
                                               - (IData)(0x00000010U)), 2U);
                if (VL_GTS_III(32, 0x00000010U, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx)) {
                    vlSelfRef.tb_board_a_top__DOT__s_axi_rdata 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid
                        [(0x0000000fU & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx)];
                }
            } else if (((0x50U <= (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr)) 
                        & (0x90U > (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr)))) {
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx 
                    = VL_SHIFTR_III(32,32,32, ((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr) 
                                               - (IData)(0x00000050U)), 2U);
                if (VL_GTS_III(32, 0x00000010U, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx)) {
                    vlSelfRef.tb_board_a_top__DOT__s_axi_rdata 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread
                        [(0x0000000fU & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx)];
                }
            } else if (((0x90U <= (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr)) 
                        & (0xd0U > (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr)))) {
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx 
                    = VL_SHIFTR_III(32,32,32, ((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr) 
                                               - (IData)(0x00000090U)), 2U);
                if (VL_GTS_III(32, 0x00000010U, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx)) {
                    vlSelfRef.tb_board_a_top__DOT__s_axi_rdata 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id
                        [(0x0000000fU & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx)];
                }
            } else if (((0xd0U <= (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr)) 
                        & (0xf0U > (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr)))) {
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__tok_idx 
                    = (0x7ffffffeU & VL_SHIFTR_III(32,32,32, 
                                                   ((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr) 
                                                    - (IData)(0x000000d0U)), 1U));
                vlSelfRef.tb_board_a_top__DOT__s_axi_rdata 
                    = ((0xffff0000U & vlSelfRef.tb_board_a_top__DOT__s_axi_rdata) 
                       | (VL_GTS_III(32, 0x00000010U, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__tok_idx)
                           ? vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token
                          [(0x0000000fU & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__tok_idx)]
                           : 0U));
                vlSelfRef.tb_board_a_top__DOT__s_axi_rdata 
                    = ((0x0000ffffU & vlSelfRef.tb_board_a_top__DOT__s_axi_rdata) 
                       | ((VL_GTS_III(32, 0x00000010U, 
                                      ((IData)(1U) 
                                       + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__tok_idx))
                            ? vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token
                           [(0x0000000fU & ((IData)(1U) 
                                            + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__tok_idx))]
                            : 0U) << 0x00000010U));
            } else if ((0xf0U == (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr))) {
                vlSelfRef.tb_board_a_top__DOT__s_axi_rdata 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_sym_count;
            } else if ((0xf4U == (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr))) {
                vlSelfRef.tb_board_a_top__DOT__s_axi_rdata 
                    = (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r) 
                        << 9U) | (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime) 
                                   << 2U) | (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__link_up) 
                                              << 1U) 
                                             | (2U 
                                                == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state)))));
            } else if ((0xf8U == (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr))) {
                vlSelfRef.tb_board_a_top__DOT__s_axi_rdata 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__quotes_generated;
            } else if ((0xfcU == (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_araddr))) {
                vlSelfRef.tb_board_a_top__DOT__s_axi_rdata 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__orders_rcvd;
            }
        }
        if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__write_fire) {
            if ((0U != (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                if ((4U != (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                    if ((8U == (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed 
                            = vlSelfRef.tb_board_a_top__DOT__s_axi_wdata;
                    }
                    if ((8U != (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                        if ((0x0cU != (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                            if ((1U & (~ ((0x10U <= (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)) 
                                          & (0x50U 
                                             > (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)))))) {
                                if ((1U & (~ ((0x50U 
                                               <= (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)) 
                                              & (0x90U 
                                                 > (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)))))) {
                                    if ((1U & (~ ((0x90U 
                                                   <= (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)) 
                                                  & (0xd0U 
                                                     > (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)))))) {
                                        if ((1U & (~ 
                                                   ((0xd0U 
                                                     <= (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)) 
                                                    & (0xf0U 
                                                       > (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr)))))) {
                                            if ((0xf0U 
                                                 == (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                                                vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_sym_count 
                                                    = 
                                                    ((0U 
                                                      == 
                                                      (0x000000ffU 
                                                       & vlSelfRef.tb_board_a_top__DOT__s_axi_wdata))
                                                      ? 1U
                                                      : 
                                                     ((0x10U 
                                                       < 
                                                       (0x000000ffU 
                                                        & vlSelfRef.tb_board_a_top__DOT__s_axi_wdata))
                                                       ? 0x00000010U
                                                       : 
                                                      (0x000000ffU 
                                                       & vlSelfRef.tb_board_a_top__DOT__s_axi_wdata)));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if ((0x0cU == (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                            vlSelfRef.tb_board_a_top__DOT__dut__DOT__regime_from_ps 
                                = (3U & vlSelfRef.tb_board_a_top__DOT__s_axi_wdata);
                        }
                    }
                }
                if ((4U == (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awaddr))) {
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_interval 
                        = vlSelfRef.tb_board_a_top__DOT__s_axi_wdata;
                }
            }
        }
        if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid) 
             & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__tx_ready))) {
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid = 0U;
        }
        if ((1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid)))) {
            if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_valid) {
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[0U] 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[0U];
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[1U] 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[1U];
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[2U] 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[2U];
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[3U] 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[3U];
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid = 1U;
            } else if ((0U != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r))) {
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[0U] 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem
                    [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr][0U];
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[1U] 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem
                    [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr][1U];
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[2U] 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem
                    [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr][2U];
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[3U] 
                    = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem
                    [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr][3U];
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid = 1U;
            }
        }
        if ((0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))) {
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_sym_in_range = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_symbol = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_limit_price = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_qty = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_bid = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_ask = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__orders_rcvd = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[0U] = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[1U] = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[2U] = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[3U] = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__fill_valid = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__fills_sent = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__rejects_sent = 0U;
        } else {
            if (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_valid) 
                 & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid)))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__fill_valid = 0U;
            }
            if ((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__exchange_enable) 
                  & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid)) 
                 & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_valid)))) {
                if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__is_filled) {
                    __Vdly__tb_board_a_top__DOT__dut__DOT__fills_sent 
                        = ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__fills_sent);
                } else {
                    __Vdly__tb_board_a_top__DOT__dut__DOT__rejects_sent 
                        = ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__rejects_sent);
                }
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[0U] 
                    = (IData)(((QData)((IData)((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id) 
                                                 << 0x00000010U) 
                                                | (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp)))) 
                               << 0x00000020U));
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[1U] 
                    = (IData)((((QData)((IData)((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id) 
                                                  << 0x00000010U) 
                                                 | (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp)))) 
                                << 0x00000020U) >> 0x00000020U));
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[2U] 
                    = ((0xffff0000U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[2U]) 
                       | (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_qty_val));
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[2U] 
                    = ((0x0000ffffU & vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[2U]) 
                       | (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_price_val 
                          << 0x00000010U));
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[3U] 
                    = ((0xffff0000U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[3U]) 
                       | (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_price_val 
                          >> 0x00000010U));
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[3U] 
                    = ((0x0000ffffU & vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[3U]) 
                       | (0xffff0000U & (0x30000000U 
                                         | (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_symbol) 
                                             << 0x00000014U) 
                                            | (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side) 
                                                << 0x00000013U) 
                                               | (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__is_filled)
                                                    ? 0U
                                                    : 1U) 
                                                  << 0x00000010U))))));
                __Vdly__tb_board_a_top__DOT__dut__DOT__fill_valid = 1U;
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid = 0U;
            }
            if ((((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__exchange_enable) 
                    & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid))) 
                   & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_valid))) 
                  & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out_valid)) 
                 & (0x20000000U == (0xf0000000U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[3U])))) {
                __Vdly__tb_board_a_top__DOT__dut__DOT__orders_rcvd 
                    = ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__orders_rcvd);
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_symbol 
                    = (0x000000ffU & (vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[3U] 
                                      >> 0x00000014U));
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side 
                    = (1U & (vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[3U] 
                             >> 0x00000013U));
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_limit_price 
                    = ((vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[3U] 
                        << 0x00000010U) | (vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[2U] 
                                           >> 0x00000010U));
                vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_qty 
                    = (0x0000ffffU & vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[2U]);
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id 
                    = (vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[1U] 
                       >> 0x00000010U);
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp 
                    = (0x0000ffffU & vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[1U]);
                if ((0x10U > (0x000000ffU & (vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[3U] 
                                             >> 0x00000014U)))) {
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_sym_in_range = 1U;
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_bid 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid
                        [(0x0000000fU & (vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[3U] 
                                         >> 0x00000014U))];
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_ask 
                        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask
                        [(0x0000000fU & (vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[3U] 
                                         >> 0x00000014U))];
                } else {
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_sym_in_range = 0U;
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_bid = 0U;
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_ask = 0U;
                }
                __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid = 1U;
            }
        }
    } else {
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0 = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__btn_out_prev = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p0 = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1 = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__btn_out_prev = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p1 = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2 = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__btn_out_prev = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p2 = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__axi_reset_pulse = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__axi_start_pulse = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_valid_ms = 0U;
        vlSelfRef.tb_board_a_top__DOT__s_axi_rdata = 0U;
        __VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v1 = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold[3U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf[3U] = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_seed = 0xdeadbeefU;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_interval = 0x000003e8U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_sym_count = 0x10U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__regime_from_ps = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_sym_in_range = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_symbol = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_limit_price = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_qty = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_bid = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_ask = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__orders_rcvd = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_frame[3U] = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__fill_valid = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__fills_sent = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__rejects_sent = 0U;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v3) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[0U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v0;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[0U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v0;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v6) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[6U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v6;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[6U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[6U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v6;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v7) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[7U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v7;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[7U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[7U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v7;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v8) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[8U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v8;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[8U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[8U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v8;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v9) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[9U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v9;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[9U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[9U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v9;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v10) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[10U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v10;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[11U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v11;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[12U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v12;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[10U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[11U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[12U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[10U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v10;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[11U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v11;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[12U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v12;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[1U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v1;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[1U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v1;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v13) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[13U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v13;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[13U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[13U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v13;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v14) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[14U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v14;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[14U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[14U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v14;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v15) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[15U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v15;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[15U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[15U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v15;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v16] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v16;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v17) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[0U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v17;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num__v16] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num__v16;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v17) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[0U] = 0U;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v17) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[0U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v17;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v18) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[1U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v18;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[1U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v18;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v19) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[2U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v19;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[2U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v19;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v20) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[3U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v20;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[4U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v21;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[5U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v22;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v23) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[6U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v23;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v20) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[3U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[4U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[5U] = 0U;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v23) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[6U] = 0U;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v20) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[3U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v20;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[4U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v21;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[5U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v22;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v23) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[6U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v23;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v24) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[7U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v24;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[7U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[7U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v24;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v25) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[8U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v25;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[8U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[8U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v25;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v26) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[9U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v26;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[9U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[9U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v26;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v27) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[10U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v27;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[11U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v28;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[12U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v29;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v30) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[13U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v30;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v27) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[10U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[11U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[12U] = 0U;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v30) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[13U] = 0U;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v27) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[10U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v27;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[11U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v28;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[12U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v29;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v30) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[13U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v30;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v31) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[14U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v31;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[14U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[14U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v31;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v32) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread[15U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spread__v32;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[15U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[15U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v32;
    }
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__btn_out_prev 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__btn_out_prev;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__btn_out_prev 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__btn_out_prev;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__btn_out_prev 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__btn_out_prev;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__quotes_generated 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__quotes_generated;
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v0;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_init_spread__v0;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_company_token__v0;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_company_token__v1;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__sym_sector_id__v0;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__sym_init_mid__v1) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[3U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[4U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[5U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[6U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[7U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[8U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[9U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[10U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[11U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[12U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[13U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[14U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_mid[15U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[0U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[1U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[2U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[3U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[4U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[5U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[6U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[7U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[8U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[9U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[10U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[11U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[12U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[13U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[14U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_init_spread[15U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[1U] = 1U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[2U] = 2U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[3U] = 3U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[4U] = 4U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[5U] = 5U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[6U] = 6U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[7U] = 7U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[8U] = 8U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[9U] = 9U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[10U] = 0x000aU;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[11U] = 0x000bU;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[12U] = 0x000cU;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[13U] = 0x000dU;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[14U] = 0x000eU;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_company_token[15U] = 0x000fU;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[3U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[4U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[5U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[6U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[7U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[8U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[9U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[10U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[11U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[12U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[13U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[14U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[15U] = 0U;
    }
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[0U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[1U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[2U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[3U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[4U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[5U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[6U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[7U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[0U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[1U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[2U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[3U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[4U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[5U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[6U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[7U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[8U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[9U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[10U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[11U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[12U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[13U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[14U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[15U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr;
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0][0U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0[0U];
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0][1U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0[1U];
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0][2U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0[2U];
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0][3U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem__v0[3U];
    }
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_full 
        = (0x40U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_empty 
        = (0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_wr_en 
        = ((0x40U != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r)) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_valid_ms));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__active_count_eff 
        = ((0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_sym_count))
            ? 1U : ((0x10U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_sym_count))
                     ? 0x10U : (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_sym_count)));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_symbol 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_symbol;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__fills_sent 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__fills_sent;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__rejects_sent 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__rejects_sent;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__orders_rcvd 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__orders_rcvd;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_valid 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__fill_valid;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side;
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v2) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[2U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v2;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[2U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v2;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v3) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[3U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v3;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[3U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v3;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v4) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[4U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v4;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[4U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v4;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v5) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[5U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v5;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[5U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v5;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v6) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[6U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v6;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[6U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v6;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v7) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[7U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v7;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[7U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v7;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v8) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[8U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v8;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[8U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v8;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v9) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[9U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v9;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[9U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v9;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v10) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[10U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v10;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[10U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v10;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v11) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[11U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v11;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[11U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v11;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v12) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[12U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v12;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[12U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v12;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v13) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[13U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v13;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[13U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v13;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v14) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[14U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v14;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[14U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v14;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v15) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[15U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v15;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[15U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v15;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v16) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__best_bid__v16] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v16;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[__VdlyDim0__tb_board_a_top__DOT__dut__DOT__best_ask__v16] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v16;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v20) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[0U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v17;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[0U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v17;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price__v27) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[1U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v18;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[1U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v18;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v19) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[2U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v19;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[2U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v19;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v20) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[3U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v20;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[3U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v20;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v21) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[4U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v21;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[4U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v21;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v22) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[5U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v22;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[5U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v22;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v23) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[6U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v23;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[6U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v23;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v24) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[7U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v24;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[7U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v24;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v25) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[8U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v25;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[8U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v25;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v26) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[9U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v26;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[9U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v26;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v27) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[10U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v27;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[10U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v27;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v28) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[11U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v28;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[11U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v28;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v29) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[12U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v29;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[12U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v29;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v30) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[13U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v30;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[13U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v30;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v31) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[14U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v31;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[14U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v31;
    }
    if (__VdlySet__tb_board_a_top__DOT__dut__DOT__best_bid__v32) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_bid[15U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_bid__v32;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__best_ask[15U] 
            = __VdlyVal__tb_board_a_top__DOT__dut__DOT__best_ask__v32;
    }
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff 
        = ((0x10U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__active_count_eff))
            ? 0x10U : (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__active_count_eff));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_rd_en 
        = ((0U != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r)) 
           & ((~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid)) 
              & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_valid))));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__is_filled 
        = ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_sym_in_range) 
           & ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side)
               ? (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_limit_price 
                  <= vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_bid)
               : (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_limit_price 
                  >= vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_ask)));
    if (vlSelfRef.tb_board_a_top__DOT__rst_n) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out_valid = 0U;
        if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__state) {
            if ((1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase)))) {
                if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_sync) {
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[0U] 
                        = ((vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[0U] 
                            << 4U) | (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__data_sync));
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[1U] 
                        = ((vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[0U] 
                            >> 0x0000001cU) | (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[1U] 
                                               << 4U));
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[2U] 
                        = ((vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[1U] 
                            >> 0x0000001cU) | (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[2U] 
                                               << 4U));
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U] 
                        = ((vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[2U] 
                            >> 0x0000001cU) | (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[3U] 
                                               << 4U));
                    if ((0x1fU == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count))) {
                        if ((((1U == (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                      >> 0x0000001cU)) 
                              || (2U == (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                         >> 0x0000001cU))) 
                             || (3U == (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                        >> 0x0000001cU)))) {
                            vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[0U] 
                                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[0U];
                            vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[1U] 
                                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[1U];
                            vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[2U] 
                                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[2U];
                            vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[3U] 
                                = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U];
                            vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out_valid = 1U;
                            vlSelfRef.tb_board_a_top__DOT__dut__DOT__link_up = 1U;
                        } else {
                            __Vdly__tb_board_a_top__DOT__dut__DOT__rx_error_count 
                                = ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__rx_error_count);
                        }
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[0U] = 0U;
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[1U] = 0U;
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[2U] = 0U;
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[3U] = 0U;
                        __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count = 0U;
                        __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase = 0U;
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__state = 0U;
                        if ((1U & (~ ((3U == (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                              >> 0x0000001cU)) 
                                      | ((2U == (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                                 >> 0x0000001cU)) 
                                         | (1U == (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                                   >> 0x0000001cU))))))) {
                            if (((3U == (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                         >> 0x0000001cU)) 
                                 | ((2U == (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                            >> 0x0000001cU)) 
                                    | (1U == (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                              >> 0x0000001cU))))) {
                                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                                    VL_WRITEF_NX("[%0t] %%Error: link_rx.sv:128: Assertion failed in %Ntb_board_a_top.dut.u_link_rx.unnamedblk1: unique case, but multiple matches found for '4'h%x'\n",0,
                                                 64,
                                                 VL_TIME_UNITED_Q(1000),
                                                 -9,
                                                 vlSymsp->name(),
                                                 4,
                                                 (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                                  >> 0x0000001cU));
                                    VL_STOP_MT("rtl/link/link_rx.sv", 128, "");
                                }
                            }
                        }
                    } else {
                        __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count 
                            = (0x0000001fU & ((IData)(1U) 
                                              + (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count)));
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[0U] 
                            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[0U];
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[1U] 
                            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[1U];
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[2U] 
                            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[2U];
                        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[3U] 
                            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next[3U];
                    }
                } else {
                    __Vdly__tb_board_a_top__DOT__dut__DOT__rx_error_count 
                        = ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__rx_error_count);
                    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__state = 0U;
                }
            }
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase 
                = (1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase)));
        } else if (((~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_prev)) 
                    & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_sync))) {
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[0U] = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[1U] = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[2U] = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[3U] = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count = 0U;
            __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase = 0U;
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__state = 1U;
        }
        if ((0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))) {
            __Vdly__tb_board_a_top__DOT__dut__DOT__rx_error_count = 0U;
        }
    } else {
        __Vdly__tb_board_a_top__DOT__dut__DOT__rx_error_count = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__state = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg[3U] = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count = 0U;
        __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[0U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[1U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[2U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out[3U] = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__frame_out_valid = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__link_up = 0U;
    }
    if (vlSelfRef.tb_board_a_top__DOT__rst_n) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__data_sync 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__data_s1;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_next;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__data_s1 
            = vlSelfRef.tb_board_a_top__DOT__pmod_jb;
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__data_sync = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__data_s1 = 0U;
    }
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[0U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[1U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[2U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[3U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[4U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[5U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[6U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[7U] = 0U;
    if ((0U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[0U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[0U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[0U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[0U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[0U] = 0U;
    }
    if ((1U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[1U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[1U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[1U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[1U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[1U] = 0U;
    }
    if ((2U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[2U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[2U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[2U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[2U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[2U] = 0U;
    }
    if ((3U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[3U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[3U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[3U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[3U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[3U] = 0U;
    }
    if ((4U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[4U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[4U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[4U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[4U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[4U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[4U] = 0U;
    }
    if ((5U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[5U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[5U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[5U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[5U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[5U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[5U] = 0U;
    }
    if ((6U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[6U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[6U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[6U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[6U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[6U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[6U] = 0U;
    }
    if ((7U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[7U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[7U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[7U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[7U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[7U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[7U] = 0U;
    }
    if ((8U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[8U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[8U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[8U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[8U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[8U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[8U] = 0U;
    }
    if ((9U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[9U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[9U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[9U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[9U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[9U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[9U] = 0U;
    }
    if ((0x0aU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[10U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[10U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[10U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[10U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[10U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[10U] = 0U;
    }
    if ((0x0bU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[11U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[11U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[11U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[11U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[11U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[11U] = 0U;
    }
    if ((0x0cU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[12U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[12U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[12U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[12U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[12U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[12U] = 0U;
    }
    if ((0x0dU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[13U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[13U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[13U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[13U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[13U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[13U] = 0U;
    }
    if ((0x0eU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[14U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[14U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[14U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[14U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[14U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[14U] = 0U;
    }
    if ((0x0fU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[15U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[15U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[15U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[15U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[15U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[15U] = 0U;
    }
    if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__is_filled) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_qty_val 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_qty;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_price_val 
            = ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side)
                ? vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_bid
                : vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_ask);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_qty_val = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_price_val = 0U;
    }
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__rx_error_count 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__rx_error_count;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase 
        = __Vdly__tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_prev 
        = ((IData)(vlSelfRef.tb_board_a_top__DOT__rst_n) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_sync));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__exchange_enable 
        = ((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state)) 
           | (3U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state)));
    __Vtableidx1 = (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p1) 
                     << 4U) | ((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__axi_start_pulse) 
                                 | (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p0)) 
                                << 3U) | ((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__axi_reset_pulse) 
                                            | (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p2)) 
                                           << 2U) | (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_next 
        = Vtb_board_a_top__ConstPool__TABLE_hbfde2c6f_0
        [__Vtableidx1];
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__tick_raw 
        = ((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state)) 
           & ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_interval) 
              | (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_ctr 
                 == (vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_interval 
                     - (IData)(1U)))));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_sync 
        = ((IData)(vlSelfRef.tb_board_a_top__DOT__rst_n) 
           && (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_s1));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_load 
        = ((1U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state)) 
           & (2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_next)));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote 
        = ((0x40U != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r)) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__tick_raw));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable 
        = ((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state)) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_s1 
        = ((IData)(vlSelfRef.tb_board_a_top__DOT__rst_n) 
           && (IData)(vlSelfRef.tb_board_a_top__DOT__pmod_jb_valid));
}

void Vtb_board_a_top___024root___nba_comb__TOP__0(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___nba_comb__TOP__0\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0;
    QData/*63:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c = 0;
    // Body
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__read_fire 
        = ((~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid)) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_arvalid));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__tx_ready 
        = ((~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st)) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__pmod_ja_ready));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__write_fire 
        = ((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awvalid) 
           & ((~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid)) 
              & (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_wvalid)));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime 
        = (3U & ((4U & (IData)(vlSelfRef.tb_board_a_top__DOT__sw))
                  ? (IData)(vlSelfRef.tb_board_a_top__DOT__sw)
                  : (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__regime_from_ps)));
    if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)) 
                               << 2U) | (((1U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)) 
                                          << 1U) | 
                                         (0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)))))))) {
        if ((0U != (((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)) 
                     << 2U) | (((1U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)) 
                                << 1U) | (0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: market_sim.sv:72: Assertion failed in %Ntb_board_a_top.dut.u_market_sim: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime));
                VL_STOP_MT("rtl/board_a/market_sim.sv", 72, "");
            }
        }
    }
    if ((0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime))) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00000100U;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00002000U;
    } else if ((1U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime))) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00001000U;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00008000U;
    } else if ((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime))) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00000100U;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00002000U;
    } else {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00004000U;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00010000U;
    }
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c = 0ULL;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[0U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[1U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[2U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U] = 0U;
    if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c 
            = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out
                                            [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr]), 
                          VL_EXTENDS_QI(64,32, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16));
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c 
            = (IData)(VL_SHIFTRS_QQI(64,64,32, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c, 0x00000010U));
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price
            [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr];
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c 
            = (tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c 
               + tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c);
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c 
            = (VL_GTS_III(32, 0x00010000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c)
                                  ? 0x27100000U : tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c 
            = tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16;
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c)) {
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c = 1U;
        }
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c 
            = VL_SHIFTRS_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c, 1U);
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c 
            = (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c 
               - tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c);
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c 
            = (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c 
               + tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c);
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c)
                                  ? 0x27100000U : tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c)
                                  ? 0x27100000U : tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U] 
            = ((0x0003ffffU & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U]) 
               | (0xfffc0000U & (0x10000000U | (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr) 
                                                 << 0x00000014U) 
                                                | ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime) 
                                                   << 0x00000012U)))));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[0U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                << 0x00000010U) | vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num
               [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr]);
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[1U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                >> 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   << 0x00000010U));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[2U] 
            = (((IData)((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c))) 
                << 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   >> 0x00000010U));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U] 
            = ((0xfffc0000U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U]) 
               | (((IData)((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c))) 
                   >> 0x00000010U) | ((IData)(((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c)) 
                                               >> 0x00000020U)) 
                                      << 0x00000010U)));
    }
}

void Vtb_board_a_top___024root___eval_nba(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_nba\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_board_a_top___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((0x00000000000000fbULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_board_a_top___024root___nba_comb__TOP__0(vlSelf);
    }
}

void Vtb_board_a_top___024root___timing_ready(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___timing_ready\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready("@(posedge tb_board_a_top.clk)");
    }
    if ((8ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h68e7d246__0.ready("@( tb_board_a_top.rst_n)");
    }
    if ((0x0000000000000010ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h0f1c9fb4__0.ready("@( (~ tb_board_a_top.s_axi_bvalid))");
    }
    if ((0x0000000000000020ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h43444ce6__0.ready("@( tb_board_a_top.s_axi_bvalid)");
    }
    if ((0x0000000000000040ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h950459ef__0.ready("@( (~ tb_board_a_top.s_axi_rvalid))");
    }
    if ((0x0000000000000080ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_hc95c02d3__0.ready("@( tb_board_a_top.s_axi_rvalid)");
    }
}

void Vtb_board_a_top___024root___timing_resume(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___timing_resume\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h6fd192e6__0.moveToResumeQueue(
                                                          "@(posedge tb_board_a_top.clk)");
    vlSelfRef.__VtrigSched_h68e7d246__0.moveToResumeQueue(
                                                          "@( tb_board_a_top.rst_n)");
    vlSelfRef.__VtrigSched_h0f1c9fb4__0.moveToResumeQueue(
                                                          "@( (~ tb_board_a_top.s_axi_bvalid))");
    vlSelfRef.__VtrigSched_h43444ce6__0.moveToResumeQueue(
                                                          "@( tb_board_a_top.s_axi_bvalid)");
    vlSelfRef.__VtrigSched_h950459ef__0.moveToResumeQueue(
                                                          "@( (~ tb_board_a_top.s_axi_rvalid))");
    vlSelfRef.__VtrigSched_hc95c02d3__0.moveToResumeQueue(
                                                          "@( tb_board_a_top.s_axi_rvalid)");
    vlSelfRef.__VtrigSched_h6fd192e6__0.resume("@(posedge tb_board_a_top.clk)");
    vlSelfRef.__VtrigSched_h68e7d246__0.resume("@( tb_board_a_top.rst_n)");
    vlSelfRef.__VtrigSched_h0f1c9fb4__0.resume("@( (~ tb_board_a_top.s_axi_bvalid))");
    vlSelfRef.__VtrigSched_h43444ce6__0.resume("@( tb_board_a_top.s_axi_bvalid)");
    vlSelfRef.__VtrigSched_h950459ef__0.resume("@( (~ tb_board_a_top.s_axi_rvalid))");
    vlSelfRef.__VtrigSched_hc95c02d3__0.resume("@( tb_board_a_top.s_axi_rvalid)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_board_a_top___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vtb_board_a_top___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_board_a_top___024root___eval_phase__act(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_phase__act\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_board_a_top___024root___eval_triggers_vec__act(vlSelf);
    Vtb_board_a_top___024root___timing_ready(vlSelf);
    Vtb_board_a_top___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_board_a_top___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_board_a_top___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_board_a_top___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_board_a_top___024root___timing_resume(vlSelf);
        Vtb_board_a_top___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_board_a_top___024root___eval_phase__inact(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_phase__inact\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("tb/board_a/tb_board_a_top.sv", 10, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_board_a_top___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_board_a_top___024root___eval_phase__nba(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_phase__nba\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_board_a_top___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_board_a_top___024root___eval_nba(vlSelf);
        Vtb_board_a_top___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_board_a_top___024root___eval(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_board_a_top___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("tb/board_a/tb_board_a_top.sv", 10, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("tb/board_a/tb_board_a_top.sv", 10, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_board_a_top___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("tb/board_a/tb_board_a_top.sv", 10, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_board_a_top___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_board_a_top___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_board_a_top___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0(Vtb_board_a_top___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root____VbeforeTrig_h6fd192e6__0\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_board_a_top__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__clk__0 
        = vlSelfRef.tb_board_a_top__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h6fd192e6__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_board_a_top___024root____VbeforeTrig_h68e7d246__0(Vtb_board_a_top___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root____VbeforeTrig_h68e7d246__0\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.tb_board_a_top__DOT__rst_n) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__rst_n__0)) 
                                  << 3U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__rst_n__0 
        = vlSelfRef.tb_board_a_top__DOT__rst_n;
    if ((8ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h68e7d246__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_board_a_top___024root____VbeforeTrig_h0f1c9fb4__0(Vtb_board_a_top___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root____VbeforeTrig_h0f1c9fb4__0\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    CData/*0:0*/ __Vtrigprevexpr_h972aab23__0;
    __Vtrigprevexpr_h972aab23__0 = 0;
    // Body
    __Vtrigprevexpr_h972aab23__0 = (1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid)));
    __VTmp[0U] = (QData)((IData)((((IData)(__Vtrigprevexpr_h972aab23__0) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr_h972aab23__1)) 
                                  << 4U)));
    vlSelfRef.__Vtrigprevexpr_h972aab23__1 = __Vtrigprevexpr_h972aab23__0;
    if ((0x0000000000000010ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h0f1c9fb4__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h0f1c9fb4__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_board_a_top___024root____VbeforeTrig_h43444ce6__0(Vtb_board_a_top___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root____VbeforeTrig_h43444ce6__0\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_bvalid__0)) 
                                  << 5U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_bvalid__0 
        = vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid;
    if ((0x0000000000000020ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h43444ce6__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h43444ce6__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_board_a_top___024root____VbeforeTrig_h950459ef__0(Vtb_board_a_top___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root____VbeforeTrig_h950459ef__0\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    CData/*0:0*/ __Vtrigprevexpr_h113370fe__0;
    __Vtrigprevexpr_h113370fe__0 = 0;
    // Body
    __Vtrigprevexpr_h113370fe__0 = (1U & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid)));
    __VTmp[0U] = (QData)((IData)((((IData)(__Vtrigprevexpr_h113370fe__0) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr_h113370fe__1)) 
                                  << 6U)));
    vlSelfRef.__Vtrigprevexpr_h113370fe__1 = __Vtrigprevexpr_h113370fe__0;
    if ((0x0000000000000040ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h950459ef__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_board_a_top___024root____VbeforeTrig_hc95c02d3__0(Vtb_board_a_top___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root____VbeforeTrig_hc95c02d3__0\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_rvalid__0)) 
                                  << 7U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_rvalid__0 
        = vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid;
    if ((0x0000000000000080ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_hc95c02d3__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_board_a_top___024root___eval_debug_assertions(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_debug_assertions\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
