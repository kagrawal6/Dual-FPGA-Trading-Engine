// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_link_tx.h for the primary calling header

#include "Vtb_link_tx__pch.h"

VlCoroutine Vtb_link_tx___024root___eval_initial__TOP__Vtiming__0(Vtb_link_tx___024root* vlSelf);
VlCoroutine Vtb_link_tx___024root___eval_initial__TOP__Vtiming__1(Vtb_link_tx___024root* vlSelf);
VlCoroutine Vtb_link_tx___024root___eval_initial__TOP__Vtiming__2(Vtb_link_tx___024root* vlSelf);

void Vtb_link_tx___024root___eval_initial(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___eval_initial\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_link_tx__DOT__clk = 0U;
    Vtb_link_tx___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_link_tx___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_link_tx___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

VlCoroutine Vtb_link_tx___024root___eval_initial__TOP__Vtiming__0(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_link_tx__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000186a0ULL, 
                                         nullptr, "tb/link/tb_link_tx.sv", 
                                         33);
    vlSelfRef.tb_link_tx__DOT__rst_n = 1U;
    co_return;
}

void Vtb_link_tx___024root____VbeforeTrig_h9028e335__0(Vtb_link_tx___024root* vlSelf, const char* __VeventDescription);
void Vtb_link_tx___024root____VbeforeTrig_h38e3431a__0(Vtb_link_tx___024root* vlSelf, const char* __VeventDescription);
void Vtb_link_tx___024root____VbeforeTrig_h1699be42__0(Vtb_link_tx___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_link_tx___024root___eval_initial__TOP__Vtiming__1(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vtask_tb_link_tx__DOT__check__0__cond;
    __Vtask_tb_link_tx__DOT__check__0__cond = 0;
    CData/*0:0*/ __Vtask_tb_link_tx__DOT__check__1__cond;
    __Vtask_tb_link_tx__DOT__check__1__cond = 0;
    CData/*0:0*/ __Vtask_tb_link_tx__DOT__check__2__cond;
    __Vtask_tb_link_tx__DOT__check__2__cond = 0;
    // Body
    vlSelfRef.tb_link_tx__DOT__frame_in[0U] = 0U;
    vlSelfRef.tb_link_tx__DOT__frame_in[1U] = 0U;
    vlSelfRef.tb_link_tx__DOT__frame_in[2U] = 0U;
    vlSelfRef.tb_link_tx__DOT__frame_in[3U] = 0U;
    vlSelfRef.tb_link_tx__DOT__frame_in_valid = 0U;
    Vtb_link_tx___024root____VbeforeTrig_h9028e335__0(vlSelf, 
                                                      "@(posedge tb_link_tx.clk)");
    co_await vlSelfRef.__VtrigSched_h9028e335__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_tx.clk)", 
                                                         "tb/link/tb_link_tx.sv", 
                                                         79);
    while ((1U & (~ (IData)(vlSelfRef.tb_link_tx__DOT__rst_n)))) {
        Vtb_link_tx___024root____VbeforeTrig_h38e3431a__0(vlSelf, 
                                                          "@( tb_link_tx.rst_n)");
        co_await vlSelfRef.__VtrigSched_h38e3431a__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_link_tx.rst_n)", 
                                                             "tb/link/tb_link_tx.sv", 
                                                             80);
    }
    Vtb_link_tx___024root____VbeforeTrig_h9028e335__0(vlSelf, 
                                                      "@(posedge tb_link_tx.clk)");
    co_await vlSelfRef.__VtrigSched_h9028e335__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_tx.clk)", 
                                                         "tb/link/tb_link_tx.sv", 
                                                         81);
    vlSelfRef.tb_link_tx__DOT__unnamedblk1__DOT__exp_frame[0U] = 0U;
    vlSelfRef.tb_link_tx__DOT__unnamedblk1__DOT__exp_frame[1U] = 0xcafe0000U;
    vlSelfRef.tb_link_tx__DOT__unnamedblk1__DOT__exp_frame[2U] = 0xdeadbeefU;
    vlSelfRef.tb_link_tx__DOT__unnamedblk1__DOT__exp_frame[3U] = 0x23000005U;
    Vtb_link_tx___024root____VbeforeTrig_h9028e335__0(vlSelf, 
                                                      "@(posedge tb_link_tx.clk)");
    co_await vlSelfRef.__VtrigSched_h9028e335__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_tx.clk)", 
                                                         "tb/link/tb_link_tx.sv", 
                                                         84);
    vlSelfRef.tb_link_tx__DOT__frame_in[0U] = vlSelfRef.tb_link_tx__DOT__unnamedblk1__DOT__exp_frame[0U];
    vlSelfRef.tb_link_tx__DOT__frame_in[1U] = vlSelfRef.tb_link_tx__DOT__unnamedblk1__DOT__exp_frame[1U];
    vlSelfRef.tb_link_tx__DOT__frame_in[2U] = vlSelfRef.tb_link_tx__DOT__unnamedblk1__DOT__exp_frame[2U];
    vlSelfRef.tb_link_tx__DOT__frame_in[3U] = vlSelfRef.tb_link_tx__DOT__unnamedblk1__DOT__exp_frame[3U];
    vlSelfRef.tb_link_tx__DOT__frame_in_valid = 1U;
    do {
        Vtb_link_tx___024root____VbeforeTrig_h9028e335__0(vlSelf, 
                                                          "@(posedge tb_link_tx.clk)");
        co_await vlSelfRef.__VtrigSched_h9028e335__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_link_tx.clk)", 
                                                             "tb/link/tb_link_tx.sv", 
                                                             88);
    } while ((1U & (~ (((~ (IData)(vlSelfRef.tb_link_tx__DOT__dut__DOT__st)) 
                        & (~ (IData)(vlSelfRef.tb_link_tx__DOT__u_mon__DOT__state))) 
                       & (IData)(vlSelfRef.tb_link_tx__DOT__frame_in_valid)))));
    Vtb_link_tx___024root____VbeforeTrig_h9028e335__0(vlSelf, 
                                                      "@(posedge tb_link_tx.clk)");
    co_await vlSelfRef.__VtrigSched_h9028e335__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_tx.clk)", 
                                                         "tb/link/tb_link_tx.sv", 
                                                         90);
    vlSelfRef.tb_link_tx__DOT__frame_in_valid = 0U;
    while ((1U & (~ (IData)(vlSelfRef.tb_link_tx__DOT__frame_out_valid)))) {
        Vtb_link_tx___024root____VbeforeTrig_h1699be42__0(vlSelf, 
                                                          "@( tb_link_tx.frame_out_valid)");
        co_await vlSelfRef.__VtrigSched_h1699be42__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_link_tx.frame_out_valid)", 
                                                             "tb/link/tb_link_tx.sv", 
                                                             93);
    }
    Vtb_link_tx___024root____VbeforeTrig_h9028e335__0(vlSelf, 
                                                      "@(posedge tb_link_tx.clk)");
    co_await vlSelfRef.__VtrigSched_h9028e335__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_tx.clk)", 
                                                         "tb/link/tb_link_tx.sv", 
                                                         94);
    __Vtask_tb_link_tx__DOT__check__0__cond = (0U == 
                                               ((((vlSelfRef.tb_link_tx__DOT__frame_out[0U] 
                                                   ^ vlSelfRef.tb_link_tx__DOT__unnamedblk1__DOT__exp_frame[0U]) 
                                                  | (vlSelfRef.tb_link_tx__DOT__frame_out[1U] 
                                                     ^ vlSelfRef.tb_link_tx__DOT__unnamedblk1__DOT__exp_frame[1U])) 
                                                 | (vlSelfRef.tb_link_tx__DOT__frame_out[2U] 
                                                    ^ vlSelfRef.tb_link_tx__DOT__unnamedblk1__DOT__exp_frame[2U])) 
                                                | (vlSelfRef.tb_link_tx__DOT__frame_out[3U] 
                                                   ^ vlSelfRef.tb_link_tx__DOT__unnamedblk1__DOT__exp_frame[3U])));
    vlSelfRef.__Vtask_tb_link_tx__DOT__check__0__msg = "assembled frame"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_tx__DOT__check__0__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_tx.sv:69: Assertion failed in %Ntb_link_tx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_tx__DOT__check__0__msg));
        VL_STOP_MT("tb/link/tb_link_tx.sv", 69, "");
        vlSelfRef.tb_link_tx__DOT__err_count = ((IData)(1U) 
                                                + vlSelfRef.tb_link_tx__DOT__err_count);
    }
    __Vtask_tb_link_tx__DOT__check__1__cond = vlSelfRef.tb_link_tx__DOT__link_up;
    vlSelfRef.__Vtask_tb_link_tx__DOT__check__1__msg = "link_up"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_tx__DOT__check__1__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_tx.sv:69: Assertion failed in %Ntb_link_tx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_tx__DOT__check__1__msg));
        VL_STOP_MT("tb/link/tb_link_tx.sv", 69, "");
        vlSelfRef.tb_link_tx__DOT__err_count = ((IData)(1U) 
                                                + vlSelfRef.tb_link_tx__DOT__err_count);
    }
    __Vtask_tb_link_tx__DOT__check__2__cond = (0U == vlSelfRef.tb_link_tx__DOT__error_count);
    vlSelfRef.__Vtask_tb_link_tx__DOT__check__2__msg = "rx errors"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_tx__DOT__check__2__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_tx.sv:69: Assertion failed in %Ntb_link_tx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_tx__DOT__check__2__msg));
        VL_STOP_MT("tb/link/tb_link_tx.sv", 69, "");
        vlSelfRef.tb_link_tx__DOT__err_count = ((IData)(1U) 
                                                + vlSelfRef.tb_link_tx__DOT__err_count);
    }
    if ((0U == vlSelfRef.tb_link_tx__DOT__err_count)) {
        VL_WRITEF_NX("tb_link_tx: PASS (all checks passed)\n",0);
    } else {
        VL_WRITEF_NX("tb_link_tx: FAIL (%0d errors)\n",0,
                     32,vlSelfRef.tb_link_tx__DOT__err_count);
    }
    VL_FINISH_MT("tb/link/tb_link_tx.sv", 103, "");
    co_return;
}

VlCoroutine Vtb_link_tx___024root___eval_initial__TOP__Vtiming__2(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "tb/link/tb_link_tx.sv", 
                                             29);
        vlSelfRef.tb_link_tx__DOT__clk = (1U & (~ (IData)(vlSelfRef.tb_link_tx__DOT__clk)));
    }
    co_return;
}

void Vtb_link_tx___024root___eval_triggers_vec__act(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___eval_triggers_vec__act\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((IData)(vlSelfRef.tb_link_tx__DOT__frame_out_valid) 
                                                       != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__frame_out_valid__0)) 
                                                      << 4U) 
                                                     | (((((IData)(vlSelfRef.tb_link_tx__DOT__rst_n) 
                                                           != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__rst_n__0)) 
                                                          << 3U) 
                                                         | (vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                            << 2U)) 
                                                        | ((((~ (IData)(vlSelfRef.tb_link_tx__DOT__rst_n)) 
                                                             & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__rst_n__0)) 
                                                            << 1U) 
                                                           | ((IData)(vlSelfRef.tb_link_tx__DOT__clk) 
                                                              & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__clk__0))))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__clk__0 
        = vlSelfRef.tb_link_tx__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__rst_n__0 
        = vlSelfRef.tb_link_tx__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__frame_out_valid__0 
        = vlSelfRef.tb_link_tx__DOT__frame_out_valid;
}

bool Vtb_link_tx___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___trigger_anySet__act\n"); );
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

void Vtb_link_tx___024root___nba_sequent__TOP__0(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___nba_sequent__TOP__0\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vdly__tb_link_tx__DOT__dut__DOT__st;
    __Vdly__tb_link_tx__DOT__dut__DOT__st = 0;
    IData/*31:0*/ __Vdly__tb_link_tx__DOT__error_count;
    __Vdly__tb_link_tx__DOT__error_count = 0;
    CData/*4:0*/ __Vdly__tb_link_tx__DOT__u_mon__DOT__beat_count;
    __Vdly__tb_link_tx__DOT__u_mon__DOT__beat_count = 0;
    CData/*0:0*/ __Vdly__tb_link_tx__DOT__u_mon__DOT__phase;
    __Vdly__tb_link_tx__DOT__u_mon__DOT__phase = 0;
    VlWide<4>/*127:0*/ __Vtemp_4;
    // Body
    __Vdly__tb_link_tx__DOT__dut__DOT__st = vlSelfRef.tb_link_tx__DOT__dut__DOT__st;
    __Vdly__tb_link_tx__DOT__error_count = vlSelfRef.tb_link_tx__DOT__error_count;
    __Vdly__tb_link_tx__DOT__u_mon__DOT__beat_count 
        = vlSelfRef.tb_link_tx__DOT__u_mon__DOT__beat_count;
    __Vdly__tb_link_tx__DOT__u_mon__DOT__phase = vlSelfRef.tb_link_tx__DOT__u_mon__DOT__phase;
    if (vlSelfRef.tb_link_tx__DOT__rst_n) {
        vlSelfRef.tb_link_tx__DOT__frame_out_valid = 0U;
        if (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__state) {
            if ((1U & (~ (IData)(vlSelfRef.tb_link_tx__DOT__u_mon__DOT__phase)))) {
                if (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__valid_sync) {
                    vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[0U] 
                        = ((vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[0U] 
                            << 4U) | (IData)(vlSelfRef.tb_link_tx__DOT__u_mon__DOT__data_sync));
                    vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[1U] 
                        = ((vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[0U] 
                            >> 0x0000001cU) | (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[1U] 
                                               << 4U));
                    vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[2U] 
                        = ((vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[1U] 
                            >> 0x0000001cU) | (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[2U] 
                                               << 4U));
                    vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U] 
                        = ((vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[2U] 
                            >> 0x0000001cU) | (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[3U] 
                                               << 4U));
                    if ((0x1fU == (IData)(vlSelfRef.tb_link_tx__DOT__u_mon__DOT__beat_count))) {
                        if ((((1U == (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                      >> 0x0000001cU)) 
                              || (2U == (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                         >> 0x0000001cU))) 
                             || (3U == (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                        >> 0x0000001cU)))) {
                            vlSelfRef.tb_link_tx__DOT__frame_out[0U] 
                                = vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[0U];
                            vlSelfRef.tb_link_tx__DOT__frame_out[1U] 
                                = vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[1U];
                            vlSelfRef.tb_link_tx__DOT__frame_out[2U] 
                                = vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[2U];
                            vlSelfRef.tb_link_tx__DOT__frame_out[3U] 
                                = vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U];
                            vlSelfRef.tb_link_tx__DOT__frame_out_valid = 1U;
                            vlSelfRef.tb_link_tx__DOT__link_up = 1U;
                        } else {
                            __Vdly__tb_link_tx__DOT__error_count 
                                = ((IData)(1U) + vlSelfRef.tb_link_tx__DOT__error_count);
                        }
                        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[0U] = 0U;
                        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[1U] = 0U;
                        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[2U] = 0U;
                        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[3U] = 0U;
                        __Vdly__tb_link_tx__DOT__u_mon__DOT__beat_count = 0U;
                        __Vdly__tb_link_tx__DOT__u_mon__DOT__phase = 0U;
                        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__state = 0U;
                        if ((1U & (~ ((3U == (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                              >> 0x0000001cU)) 
                                      | ((2U == (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                                 >> 0x0000001cU)) 
                                         | (1U == (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                                   >> 0x0000001cU))))))) {
                            if (((3U == (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                         >> 0x0000001cU)) 
                                 | ((2U == (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                            >> 0x0000001cU)) 
                                    | (1U == (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                              >> 0x0000001cU))))) {
                                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                                    VL_WRITEF_NX("[%0t] %%Error: link_rx.sv:128: Assertion failed in %Ntb_link_tx.u_mon.unnamedblk1: unique case, but multiple matches found for '4'h%x'\n",0,
                                                 64,
                                                 VL_TIME_UNITED_Q(1000),
                                                 -9,
                                                 vlSymsp->name(),
                                                 4,
                                                 (vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                                  >> 0x0000001cU));
                                    VL_STOP_MT("rtl/link/link_rx.sv", 128, "");
                                }
                            }
                        }
                    } else {
                        __Vdly__tb_link_tx__DOT__u_mon__DOT__beat_count 
                            = (0x0000001fU & ((IData)(1U) 
                                              + (IData)(vlSelfRef.tb_link_tx__DOT__u_mon__DOT__beat_count)));
                        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[0U] 
                            = vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[0U];
                        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[1U] 
                            = vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[1U];
                        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[2U] 
                            = vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[2U];
                        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[3U] 
                            = vlSelfRef.tb_link_tx__DOT__u_mon__DOT__unnamedblk1__DOT__assembled_next[3U];
                    }
                } else {
                    __Vdly__tb_link_tx__DOT__error_count 
                        = ((IData)(1U) + vlSelfRef.tb_link_tx__DOT__error_count);
                    vlSelfRef.tb_link_tx__DOT__u_mon__DOT__state = 0U;
                }
            }
            __Vdly__tb_link_tx__DOT__u_mon__DOT__phase 
                = (1U & (~ (IData)(vlSelfRef.tb_link_tx__DOT__u_mon__DOT__phase)));
        } else if (((~ (IData)(vlSelfRef.tb_link_tx__DOT__u_mon__DOT__valid_prev)) 
                    & (IData)(vlSelfRef.tb_link_tx__DOT__u_mon__DOT__valid_sync))) {
            vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[0U] = 0U;
            vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[1U] = 0U;
            vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[2U] = 0U;
            vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[3U] = 0U;
            __Vdly__tb_link_tx__DOT__u_mon__DOT__beat_count = 0U;
            __Vdly__tb_link_tx__DOT__u_mon__DOT__phase = 0U;
            vlSelfRef.tb_link_tx__DOT__u_mon__DOT__state = 1U;
        }
    } else {
        __Vdly__tb_link_tx__DOT__error_count = 0U;
        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__state = 0U;
        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[0U] = 0U;
        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[1U] = 0U;
        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[2U] = 0U;
        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__assemble_reg[3U] = 0U;
        __Vdly__tb_link_tx__DOT__u_mon__DOT__beat_count = 0U;
        __Vdly__tb_link_tx__DOT__u_mon__DOT__phase = 0U;
        vlSelfRef.tb_link_tx__DOT__frame_out[0U] = 0U;
        vlSelfRef.tb_link_tx__DOT__frame_out[1U] = 0U;
        vlSelfRef.tb_link_tx__DOT__frame_out[2U] = 0U;
        vlSelfRef.tb_link_tx__DOT__frame_out[3U] = 0U;
        vlSelfRef.tb_link_tx__DOT__frame_out_valid = 0U;
        vlSelfRef.tb_link_tx__DOT__link_up = 0U;
    }
    vlSelfRef.tb_link_tx__DOT__error_count = __Vdly__tb_link_tx__DOT__error_count;
    vlSelfRef.tb_link_tx__DOT__u_mon__DOT__beat_count 
        = __Vdly__tb_link_tx__DOT__u_mon__DOT__beat_count;
    vlSelfRef.tb_link_tx__DOT__u_mon__DOT__phase = __Vdly__tb_link_tx__DOT__u_mon__DOT__phase;
    vlSelfRef.tb_link_tx__DOT__u_mon__DOT__valid_prev 
        = ((IData)(vlSelfRef.tb_link_tx__DOT__rst_n) 
           & (IData)(vlSelfRef.tb_link_tx__DOT__u_mon__DOT__valid_sync));
    vlSelfRef.tb_link_tx__DOT__u_mon__DOT__valid_sync 
        = ((IData)(vlSelfRef.tb_link_tx__DOT__rst_n) 
           && (IData)(vlSelfRef.tb_link_tx__DOT__u_mon__DOT__valid_s1));
    vlSelfRef.tb_link_tx__DOT__u_mon__DOT__valid_s1 
        = ((IData)(vlSelfRef.tb_link_tx__DOT__rst_n) 
           && (IData)(vlSelfRef.tb_link_tx__DOT__pmod_valid));
    if (vlSelfRef.tb_link_tx__DOT__rst_n) {
        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__data_sync 
            = vlSelfRef.tb_link_tx__DOT__u_mon__DOT__data_s1;
        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__data_s1 
            = (vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[3U] 
               >> 0x0000001cU);
    } else {
        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__data_sync = 0U;
        vlSelfRef.tb_link_tx__DOT__u_mon__DOT__data_s1 = 0U;
    }
    if (vlSelfRef.tb_link_tx__DOT__rst_n) {
        if (vlSelfRef.tb_link_tx__DOT__dut__DOT__st) {
            vlSelfRef.tb_link_tx__DOT__pmod_valid = 1U;
            if (vlSelfRef.tb_link_tx__DOT__dut__DOT__half_nibble) {
                vlSelfRef.tb_link_tx__DOT__dut__DOT__half_nibble = 0U;
                if ((0x1fU == (IData)(vlSelfRef.tb_link_tx__DOT__dut__DOT__beat))) {
                    __Vdly__tb_link_tx__DOT__dut__DOT__st = 0U;
                    vlSelfRef.tb_link_tx__DOT__pmod_valid = 0U;
                } else {
                    __Vtemp_4[1U] = ((vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[0U] 
                                      >> 0x0000001cU) 
                                     | (vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[1U] 
                                        << 4U));
                    __Vtemp_4[2U] = ((vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[1U] 
                                      >> 0x0000001cU) 
                                     | (vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[2U] 
                                        << 4U));
                    __Vtemp_4[3U] = ((vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[2U] 
                                      >> 0x0000001cU) 
                                     | (vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[3U] 
                                        << 4U));
                    vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[0U] 
                        = (vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[0U] 
                           << 4U);
                    vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[1U] 
                        = __Vtemp_4[1U];
                    vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[2U] 
                        = __Vtemp_4[2U];
                    vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[3U] 
                        = __Vtemp_4[3U];
                    vlSelfRef.tb_link_tx__DOT__dut__DOT__beat 
                        = (0x0000001fU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.tb_link_tx__DOT__dut__DOT__beat)));
                }
            } else {
                vlSelfRef.tb_link_tx__DOT__dut__DOT__half_nibble = 1U;
            }
        } else {
            vlSelfRef.tb_link_tx__DOT__pmod_valid = 0U;
            if (((IData)(vlSelfRef.tb_link_tx__DOT__frame_in_valid) 
                 & (IData)(vlSelfRef.tb_link_tx__DOT__frame_in_ready))) {
                vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[0U] 
                    = vlSelfRef.tb_link_tx__DOT__frame_in[0U];
                vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[1U] 
                    = vlSelfRef.tb_link_tx__DOT__frame_in[1U];
                vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[2U] 
                    = vlSelfRef.tb_link_tx__DOT__frame_in[2U];
                vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[3U] 
                    = vlSelfRef.tb_link_tx__DOT__frame_in[3U];
                vlSelfRef.tb_link_tx__DOT__dut__DOT__beat = 0U;
                vlSelfRef.tb_link_tx__DOT__dut__DOT__half_nibble = 0U;
                __Vdly__tb_link_tx__DOT__dut__DOT__st = 1U;
                vlSelfRef.tb_link_tx__DOT__pmod_valid = 1U;
            }
        }
        if ((1U & (~ VL_ONEHOT_I((((IData)(vlSelfRef.tb_link_tx__DOT__dut__DOT__st) 
                                   << 1U) | (1U & (~ (IData)(vlSelfRef.tb_link_tx__DOT__dut__DOT__st)))))))) {
            if ((0U != (((IData)(vlSelfRef.tb_link_tx__DOT__dut__DOT__st) 
                         << 1U) | (1U & (~ (IData)(vlSelfRef.tb_link_tx__DOT__dut__DOT__st)))))) {
                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                    VL_WRITEF_NX("[%0t] %%Error: link_tx.sv:49: Assertion failed in %Ntb_link_tx.dut: unique case, but multiple matches found for '1'h%x'\n",0,
                                 64,VL_TIME_UNITED_Q(1000),
                                 -9,vlSymsp->name(),
                                 1,(IData)(vlSelfRef.tb_link_tx__DOT__dut__DOT__st));
                    VL_STOP_MT("rtl/link/link_tx.sv", 49, "");
                }
            }
        }
    } else {
        vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[0U] = 0U;
        vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[1U] = 0U;
        vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[2U] = 0U;
        vlSelfRef.tb_link_tx__DOT__dut__DOT__shifter[3U] = 0U;
        vlSelfRef.tb_link_tx__DOT__dut__DOT__beat = 0U;
        vlSelfRef.tb_link_tx__DOT__dut__DOT__half_nibble = 0U;
        __Vdly__tb_link_tx__DOT__dut__DOT__st = 0U;
        vlSelfRef.tb_link_tx__DOT__pmod_valid = 0U;
    }
    vlSelfRef.tb_link_tx__DOT__dut__DOT__st = __Vdly__tb_link_tx__DOT__dut__DOT__st;
    vlSelfRef.tb_link_tx__DOT__frame_in_ready = (1U 
                                                 & ((~ (IData)(vlSelfRef.tb_link_tx__DOT__dut__DOT__st)) 
                                                    & (~ (IData)(vlSelfRef.tb_link_tx__DOT__u_mon__DOT__state))));
}

void Vtb_link_tx___024root___eval_nba(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___eval_nba\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_link_tx___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vtb_link_tx___024root___timing_ready(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___timing_ready\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h9028e335__0.ready("@(posedge tb_link_tx.clk)");
    }
    if ((8ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h38e3431a__0.ready("@( tb_link_tx.rst_n)");
    }
    if ((0x0000000000000010ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h1699be42__0.ready("@( tb_link_tx.frame_out_valid)");
    }
}

void Vtb_link_tx___024root___timing_resume(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___timing_resume\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h9028e335__0.moveToResumeQueue(
                                                          "@(posedge tb_link_tx.clk)");
    vlSelfRef.__VtrigSched_h38e3431a__0.moveToResumeQueue(
                                                          "@( tb_link_tx.rst_n)");
    vlSelfRef.__VtrigSched_h1699be42__0.moveToResumeQueue(
                                                          "@( tb_link_tx.frame_out_valid)");
    vlSelfRef.__VtrigSched_h9028e335__0.resume("@(posedge tb_link_tx.clk)");
    vlSelfRef.__VtrigSched_h38e3431a__0.resume("@( tb_link_tx.rst_n)");
    vlSelfRef.__VtrigSched_h1699be42__0.resume("@( tb_link_tx.frame_out_valid)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_link_tx___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vtb_link_tx___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_link_tx___024root___eval_phase__act(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___eval_phase__act\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_link_tx___024root___eval_triggers_vec__act(vlSelf);
    Vtb_link_tx___024root___timing_ready(vlSelf);
    Vtb_link_tx___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_link_tx___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_link_tx___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_link_tx___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_link_tx___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_link_tx___024root___eval_phase__inact(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___eval_phase__inact\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("tb/link/tb_link_tx.sv", 10, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_link_tx___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_link_tx___024root___eval_phase__nba(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___eval_phase__nba\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_link_tx___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_link_tx___024root___eval_nba(vlSelf);
        Vtb_link_tx___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_link_tx___024root___eval(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___eval\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_link_tx___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("tb/link/tb_link_tx.sv", 10, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("tb/link/tb_link_tx.sv", 10, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_link_tx___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("tb/link/tb_link_tx.sv", 10, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_link_tx___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_link_tx___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_link_tx___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_link_tx___024root____VbeforeTrig_h9028e335__0(Vtb_link_tx___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root____VbeforeTrig_h9028e335__0\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_link_tx__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__clk__0 
        = vlSelfRef.tb_link_tx__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h9028e335__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9028e335__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9028e335__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9028e335__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9028e335__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h9028e335__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_link_tx___024root____VbeforeTrig_h38e3431a__0(Vtb_link_tx___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root____VbeforeTrig_h38e3431a__0\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.tb_link_tx__DOT__rst_n) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__rst_n__0)) 
                                  << 3U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__rst_n__0 
        = vlSelfRef.tb_link_tx__DOT__rst_n;
    if ((8ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h38e3431a__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_link_tx___024root____VbeforeTrig_h1699be42__0(Vtb_link_tx___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root____VbeforeTrig_h1699be42__0\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.tb_link_tx__DOT__frame_out_valid) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__frame_out_valid__0)) 
                                  << 4U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_tx__DOT__frame_out_valid__0 
        = vlSelfRef.tb_link_tx__DOT__frame_out_valid;
    if ((0x0000000000000010ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h1699be42__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_link_tx___024root___eval_debug_assertions(Vtb_link_tx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_tx___024root___eval_debug_assertions\n"); );
    Vtb_link_tx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
