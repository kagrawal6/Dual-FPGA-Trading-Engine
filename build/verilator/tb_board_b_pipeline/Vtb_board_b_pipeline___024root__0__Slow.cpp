// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_board_b_pipeline.h for the primary calling header

#include "Vtb_board_b_pipeline__pch.h"

VL_ATTR_COLD void Vtb_board_b_pipeline___024root___eval_static(Vtb_board_b_pipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_b_pipeline___024root___eval_static\n"); );
    Vtb_board_b_pipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_board_b_pipeline___024root___eval_initial__TOP(Vtb_board_b_pipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_b_pipeline___024root___eval_initial__TOP\n"); );
    Vtb_board_b_pipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_board_b_pipeline__DOT__clk = 0U;
}

VL_ATTR_COLD void Vtb_board_b_pipeline___024root___eval_final(Vtb_board_b_pipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_b_pipeline___024root___eval_final\n"); );
    Vtb_board_b_pipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtb_board_b_pipeline___024root___eval_settle(Vtb_board_b_pipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_b_pipeline___024root___eval_settle\n"); );
    Vtb_board_b_pipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vtb_board_b_pipeline___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_board_b_pipeline___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_b_pipeline___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_board_b_pipeline___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_board_b_pipeline___024root___ctor_var_reset(Vtb_board_b_pipeline___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_b_pipeline___024root___ctor_var_reset\n"); );
    Vtb_board_b_pipeline__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_board_b_pipeline__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2043979779778657300ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
