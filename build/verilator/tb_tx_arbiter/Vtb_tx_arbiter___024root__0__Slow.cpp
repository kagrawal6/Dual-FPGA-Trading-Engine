// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_tx_arbiter.h for the primary calling header

#include "Vtb_tx_arbiter__pch.h"

void Vtb_tx_arbiter___024root___timing_ready(Vtb_tx_arbiter___024root* vlSelf);

VL_ATTR_COLD void Vtb_tx_arbiter___024root___eval_static(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_static\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_tx_arbiter__DOT__err_count = 0U;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_tx_arbiter__DOT__unnamedblk1__DOT__F1, __VscopeHash, 5130783743092574302ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_tx_arbiter__DOT__unnamedblk1__DOT__F2, __VscopeHash, 13277483223607101384ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1, __VscopeHash, 10857121464124380625ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2, __VscopeHash, 10797132074699032271ull);
    vlSelfRef.__VactTriggered[0U] = (8ULL | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__clk__0 
        = vlSelfRef.tb_tx_arbiter__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__rst_n__0 
        = vlSelfRef.tb_tx_arbiter__DOT__rst_n;
    Vtb_tx_arbiter___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_tx_arbiter___024root___eval_static__TOP(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_static__TOP\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_tx_arbiter__DOT__err_count = 0U;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_tx_arbiter__DOT__unnamedblk1__DOT__F1, __VscopeHash, 5130783743092574302ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_tx_arbiter__DOT__unnamedblk1__DOT__F2, __VscopeHash, 13277483223607101384ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1, __VscopeHash, 10857121464124380625ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2, __VscopeHash, 10797132074699032271ull);
}

VL_ATTR_COLD void Vtb_tx_arbiter___024root___eval_initial__TOP(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_initial__TOP\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_tx_arbiter__DOT__clk = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_tx_arbiter.vcd"s);
    VL_PRINTF_MT("-Info: C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv:108: $dumpvar ignored, as Verilated without --trace\n");
}

VL_ATTR_COLD void Vtb_tx_arbiter___024root___eval_final(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_final\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_tx_arbiter___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_tx_arbiter___024root___eval_phase__stl(Vtb_tx_arbiter___024root* vlSelf);

VL_ATTR_COLD void Vtb_tx_arbiter___024root___eval_settle(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_settle\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_tx_arbiter___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_tx_arbiter.sv", 61, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_tx_arbiter___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_tx_arbiter___024root___eval_triggers_vec__stl(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_triggers_vec__stl\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_tx_arbiter___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_tx_arbiter___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_tx_arbiter___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_tx_arbiter___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtb_tx_arbiter___024root___eval_stl(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_stl\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        vlSelfRef.tb_tx_arbiter__DOT__quote_ready = 
            (1U & ((~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid)) 
                   & (~ (IData)(vlSelfRef.tb_tx_arbiter__DOT__fill_valid))));
    }
}

VL_ATTR_COLD bool Vtb_tx_arbiter___024root___eval_phase__stl(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___eval_phase__stl\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_tx_arbiter___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_tx_arbiter___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_tx_arbiter___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_tx_arbiter___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_tx_arbiter___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_tx_arbiter___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_tx_arbiter___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_tx_arbiter.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_tx_arbiter.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( tb_tx_arbiter.rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_tx_arbiter___024root___ctor_var_reset(Vtb_tx_arbiter___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_tx_arbiter___024root___ctor_var_reset\n"); );
    Vtb_tx_arbiter__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_tx_arbiter__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13158843472327532078ull);
    vlSelf->tb_tx_arbiter__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6896301483549995370ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_tx_arbiter__DOT__fill_frame, __VscopeHash, 12616430352547461715ull);
    vlSelf->tb_tx_arbiter__DOT__fill_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6968678354114295513ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_tx_arbiter__DOT__quote_frame, __VscopeHash, 499475150656335046ull);
    vlSelf->tb_tx_arbiter__DOT__quote_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14887605992113069391ull);
    vlSelf->tb_tx_arbiter__DOT__quote_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15630719892027535093ull);
    vlSelf->tb_tx_arbiter__DOT__tx_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13759358479559408772ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf, __VscopeHash, 8142042445502037603ull);
    vlSelf->tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4983914668950291093ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
