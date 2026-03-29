// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_sync_fifo.h for the primary calling header

#include "Vtb_sync_fifo__pch.h"

void Vtb_sync_fifo___024root___timing_ready(Vtb_sync_fifo___024root* vlSelf);

VL_ATTR_COLD void Vtb_sync_fifo___024root___eval_static(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_static\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_sync_fifo__DOT__err_count = 0U;
    vlSelfRef.__VactTriggered[0U] = (8ULL | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__clk__0 
        = vlSelfRef.tb_sync_fifo__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__rst_n__0 
        = vlSelfRef.tb_sync_fifo__DOT__rst_n;
    Vtb_sync_fifo___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_sync_fifo___024root___eval_static__TOP(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_static__TOP\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_sync_fifo__DOT__err_count = 0U;
}

VL_ATTR_COLD void Vtb_sync_fifo___024root___eval_initial__TOP(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_initial__TOP\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_sync_fifo__DOT__clk = 0U;
}

VL_ATTR_COLD void Vtb_sync_fifo___024root___eval_final(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_final\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_sync_fifo___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_sync_fifo___024root___eval_phase__stl(Vtb_sync_fifo___024root* vlSelf);

VL_ATTR_COLD void Vtb_sync_fifo___024root___eval_settle(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_settle\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_sync_fifo___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/shared\\tb_sync_fifo.sv", 10, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_sync_fifo___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_sync_fifo___024root___eval_triggers_vec__stl(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_triggers_vec__stl\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_sync_fifo___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_sync_fifo___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_sync_fifo___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_sync_fifo___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtb_sync_fifo___024root___stl_sequent__TOP__0(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___stl_sequent__TOP__0\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_sync_fifo__DOT__full = (0x40U == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
    vlSelfRef.tb_sync_fifo__DOT__empty = (0U == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
}

VL_ATTR_COLD void Vtb_sync_fifo___024root___eval_stl(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_stl\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        vlSelfRef.tb_sync_fifo__DOT__full = (0x40U 
                                             == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
        vlSelfRef.tb_sync_fifo__DOT__empty = (0U == (IData)(vlSelfRef.tb_sync_fifo__DOT__dut__DOT__count_r));
    }
}

VL_ATTR_COLD bool Vtb_sync_fifo___024root___eval_phase__stl(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___eval_phase__stl\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_sync_fifo___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_sync_fifo___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_sync_fifo___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_sync_fifo___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_sync_fifo___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_sync_fifo___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_sync_fifo___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_sync_fifo.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_sync_fifo.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( tb_sync_fifo.rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_sync_fifo___024root___ctor_var_reset(Vtb_sync_fifo___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_sync_fifo___024root___ctor_var_reset\n"); );
    Vtb_sync_fifo__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_sync_fifo__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12272240386055350815ull);
    vlSelf->tb_sync_fifo__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12303410053635814759ull);
    vlSelf->tb_sync_fifo__DOT__flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12613978050087824876ull);
    vlSelf->tb_sync_fifo__DOT__wr_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18208166083735679274ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_sync_fifo__DOT__wr_data, __VscopeHash, 14926195919763549904ull);
    vlSelf->tb_sync_fifo__DOT__full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14523670734778672996ull);
    vlSelf->tb_sync_fifo__DOT__rd_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7548510650479290529ull);
    vlSelf->tb_sync_fifo__DOT__empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3986144286981295515ull);
    for (int __Vi0 = 0; __Vi0 < 64; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_sync_fifo__DOT__dut__DOT__mem[__Vi0], __VscopeHash, 5423066854902772731ull);
    }
    vlSelf->tb_sync_fifo__DOT__dut__DOT__wr_ptr = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 18000767823863864481ull);
    vlSelf->tb_sync_fifo__DOT__dut__DOT__rd_ptr = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 4469832321796821925ull);
    vlSelf->tb_sync_fifo__DOT__dut__DOT__count_r = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 6507947983365854561ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_sync_fifo__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
