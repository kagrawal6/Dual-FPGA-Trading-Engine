// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_lfsr32.h for the primary calling header

#include "Vtb_lfsr32__pch.h"

void Vtb_lfsr32___024root___timing_ready(Vtb_lfsr32___024root* vlSelf);

VL_ATTR_COLD void Vtb_lfsr32___024root___eval_static(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_static\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_lfsr32__DOT__err_count = 0U;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_lfsr32__DOT__clk__0 
        = vlSelfRef.tb_lfsr32__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_lfsr32__DOT__rst_n__0 
        = vlSelfRef.tb_lfsr32__DOT__rst_n;
    Vtb_lfsr32___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_lfsr32___024root___eval_static__TOP(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_static__TOP\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_lfsr32__DOT__err_count = 0U;
}

VL_ATTR_COLD void Vtb_lfsr32___024root___eval_initial__TOP(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_initial__TOP\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_lfsr32__DOT__clk = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_lfsr32.vcd"s);
    VL_PRINTF_MT("-Info: C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_lfsr32.sv:65: $dumpvar ignored, as Verilated without --trace\n");
}

VL_ATTR_COLD void Vtb_lfsr32___024root___eval_final(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_final\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtb_lfsr32___024root___eval_settle(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___eval_settle\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vtb_lfsr32___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_lfsr32___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_lfsr32___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_lfsr32.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_lfsr32.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_lfsr32___024root___ctor_var_reset(Vtb_lfsr32___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_lfsr32___024root___ctor_var_reset\n"); );
    Vtb_lfsr32__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_lfsr32__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8758681832528618162ull);
    vlSelf->tb_lfsr32__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7457145905850739310ull);
    vlSelf->tb_lfsr32__DOT__enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4610249200297867045ull);
    vlSelf->tb_lfsr32__DOT__load = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5361664882626685996ull);
    vlSelf->tb_lfsr32__DOT__seed_in = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17881553511300964182ull);
    vlSelf->tb_lfsr32__DOT__dut__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11771838899230599528ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_lfsr32__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_lfsr32__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
