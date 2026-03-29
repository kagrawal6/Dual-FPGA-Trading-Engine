// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_exchange_lite.h for the primary calling header

#include "Vtb_exchange_lite__pch.h"

void Vtb_exchange_lite___024root___timing_ready(Vtb_exchange_lite___024root* vlSelf);

VL_ATTR_COLD void Vtb_exchange_lite___024root___eval_static(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_static\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_exchange_lite__DOT__err_count = 0U;
    vlSelfRef.__VactTriggered[0U] = (8ULL | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__clk__0 
        = vlSelfRef.tb_exchange_lite__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__rst_n__0 
        = vlSelfRef.tb_exchange_lite__DOT__rst_n;
    Vtb_exchange_lite___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_exchange_lite___024root___eval_static__TOP(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_static__TOP\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_exchange_lite__DOT__err_count = 0U;
}

VL_ATTR_COLD void Vtb_exchange_lite___024root___eval_initial__TOP(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_initial__TOP\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_exchange_lite__DOT__clk = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_exchange_lite.vcd"s);
    VL_PRINTF_MT("-Info: C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv:120: $dumpvar ignored, as Verilated without --trace\n");
}

VL_ATTR_COLD void Vtb_exchange_lite___024root___eval_final(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_final\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_exchange_lite___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_exchange_lite___024root___eval_phase__stl(Vtb_exchange_lite___024root* vlSelf);

VL_ATTR_COLD void Vtb_exchange_lite___024root___eval_settle(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_settle\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_exchange_lite___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 12, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_exchange_lite___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_exchange_lite___024root___eval_triggers_vec__stl(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_triggers_vec__stl\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_exchange_lite___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_exchange_lite___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_exchange_lite___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_exchange_lite___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtb_exchange_lite___024root___stl_sequent__TOP__0(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___stl_sequent__TOP__0\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_exchange_lite__DOT__dut__DOT__is_filled 
        = ((IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_sym_in_range) 
           & ((IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_side)
               ? (vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_limit_price 
                  <= vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_bid)
               : (vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_limit_price 
                  >= vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_ask)));
    if (vlSelfRef.tb_exchange_lite__DOT__dut__DOT__is_filled) {
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__fill_qty_val 
            = vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_qty;
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__fill_price_val 
            = ((IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_side)
                ? vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_bid
                : vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_ask);
    } else {
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__fill_qty_val = 0U;
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__fill_price_val = 0U;
    }
}

VL_ATTR_COLD void Vtb_exchange_lite___024root___eval_stl(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_stl\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__is_filled 
            = ((IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_sym_in_range) 
               & ((IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_side)
                   ? (vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_limit_price 
                      <= vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_bid)
                   : (vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_limit_price 
                      >= vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_ask)));
        if (vlSelfRef.tb_exchange_lite__DOT__dut__DOT__is_filled) {
            vlSelfRef.tb_exchange_lite__DOT__dut__DOT__fill_qty_val 
                = vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_qty;
            vlSelfRef.tb_exchange_lite__DOT__dut__DOT__fill_price_val 
                = ((IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_side)
                    ? vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_bid
                    : vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_ask);
        } else {
            vlSelfRef.tb_exchange_lite__DOT__dut__DOT__fill_qty_val = 0U;
            vlSelfRef.tb_exchange_lite__DOT__dut__DOT__fill_price_val = 0U;
        }
    }
}

VL_ATTR_COLD bool Vtb_exchange_lite___024root___eval_phase__stl(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_phase__stl\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_exchange_lite___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_exchange_lite___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_exchange_lite___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_exchange_lite___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_exchange_lite___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_exchange_lite___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_exchange_lite___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_exchange_lite.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_exchange_lite.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( tb_exchange_lite.rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_exchange_lite___024root___ctor_var_reset(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___ctor_var_reset\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_exchange_lite__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11572946785071822191ull);
    vlSelf->tb_exchange_lite__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8506591930296294226ull);
    vlSelf->tb_exchange_lite__DOT__enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13059876873768435050ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_exchange_lite__DOT__best_bid[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15486508139886358470ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_exchange_lite__DOT__best_ask[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3948897122557227111ull);
    }
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_exchange_lite__DOT__order_frame, __VscopeHash, 8559679090569124388ull);
    vlSelf->tb_exchange_lite__DOT__order_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6394559810392571693ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_exchange_lite__DOT__fill_frame, __VscopeHash, 2616268503276043704ull);
    vlSelf->tb_exchange_lite__DOT__fill_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2906836942788799854ull);
    vlSelf->tb_exchange_lite__DOT__fill_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14108917754307057197ull);
    vlSelf->tb_exchange_lite__DOT__orders_rcvd = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7467031114154082753ull);
    vlSelf->tb_exchange_lite__DOT__fills_sent = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13188656903974058002ull);
    vlSelf->tb_exchange_lite__DOT__rejects_sent = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6838503487513554540ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__p1_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13359851405469079555ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__p1_sym_in_range = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9422387293068876428ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__p1_symbol = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2767520815105467217ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__p1_side = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4425537727215097497ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__p1_limit_price = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14901341298377183521ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__p1_qty = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6114883703802420990ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__p1_order_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 336069134838257158ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__p1_timestamp = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1751403021067642573ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__p1_cur_bid = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8751123208472258535ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__p1_cur_ask = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11267900326357748433ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__is_filled = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3547691322638026526ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__fill_price_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13472456558406889432ull);
    vlSelf->tb_exchange_lite__DOT__dut__DOT__fill_qty_val = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 5007445316773452607ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
