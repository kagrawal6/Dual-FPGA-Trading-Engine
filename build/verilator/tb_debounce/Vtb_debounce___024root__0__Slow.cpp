// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_debounce.h for the primary calling header

#include "Vtb_debounce__pch.h"

void Vtb_debounce___024root___timing_ready(Vtb_debounce___024root* vlSelf);

VL_ATTR_COLD void Vtb_debounce___024root___eval_static(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_static\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_debounce__DOT__err_count = 0U;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_debounce__DOT__clk__0 
        = vlSelfRef.tb_debounce__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_debounce__DOT__rst_n__0 
        = vlSelfRef.tb_debounce__DOT__rst_n;
    Vtb_debounce___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_debounce___024root___eval_static__TOP(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_static__TOP\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_debounce__DOT__err_count = 0U;
}

VL_ATTR_COLD void Vtb_debounce___024root___eval_initial__TOP(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_initial__TOP\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_debounce__DOT__clk = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_debounce.vcd"s);
    VL_PRINTF_MT("-Info: C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_debounce.sv:42: $dumpvar ignored, as Verilated without --trace\n");
}

VL_ATTR_COLD void Vtb_debounce___024root___eval_final(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_final\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtb_debounce___024root___eval_settle(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___eval_settle\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vtb_debounce___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_debounce___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_debounce___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_debounce.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_debounce.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_debounce___024root___ctor_var_reset(Vtb_debounce___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_debounce___024root___ctor_var_reset\n"); );
    Vtb_debounce__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_debounce__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11928988576667964780ull);
    vlSelf->tb_debounce__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9479675823699493802ull);
    vlSelf->tb_debounce__DOT__btn_in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2672397575614477497ull);
    vlSelf->tb_debounce__DOT__btn_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16927078754914176389ull);
    vlSelf->tb_debounce__DOT__btn_pulse = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12955424799508686980ull);
    vlSelf->tb_debounce__DOT__dut__DOT__counter = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 15453365429979949484ull);
    vlSelf->tb_debounce__DOT__dut__DOT__btn_out_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16623641983097312193ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_debounce__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_debounce__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
