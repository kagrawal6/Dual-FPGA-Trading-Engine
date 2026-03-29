// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_board_a_ctrl.h for the primary calling header

#include "Vtb_board_a_ctrl__pch.h"

void Vtb_board_a_ctrl___024root___timing_ready(Vtb_board_a_ctrl___024root* vlSelf);

VL_ATTR_COLD void Vtb_board_a_ctrl___024root___eval_static(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_static\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_board_a_ctrl__DOT__err_count = 0U;
    vlSelfRef.__VactTriggered[0U] = (8ULL | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__clk__0 
        = vlSelfRef.tb_board_a_ctrl__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__rst_n__0 
        = vlSelfRef.tb_board_a_ctrl__DOT__rst_n;
    Vtb_board_a_ctrl___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_board_a_ctrl___024root___eval_static__TOP(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_static__TOP\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_board_a_ctrl__DOT__err_count = 0U;
}

VL_ATTR_COLD void Vtb_board_a_ctrl___024root___eval_initial__TOP(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_initial__TOP\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_board_a_ctrl__DOT__clk = 0U;
}

VL_ATTR_COLD void Vtb_board_a_ctrl___024root___eval_final(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_final\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_board_a_ctrl___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_board_a_ctrl___024root___eval_phase__stl(Vtb_board_a_ctrl___024root* vlSelf);

VL_ATTR_COLD void Vtb_board_a_ctrl___024root___eval_settle(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_settle\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_board_a_ctrl___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_ctrl.sv", 10, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_board_a_ctrl___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_board_a_ctrl___024root___eval_triggers_vec__stl(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_triggers_vec__stl\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_board_a_ctrl___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_board_a_ctrl___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_board_a_ctrl___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_board_a_ctrl___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___trigger_anySet__stl\n"); );
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

extern const VlUnpacked<CData/*2:0*/, 4> Vtb_board_a_ctrl__ConstPool__TABLE_h608c3c40_0;

VL_ATTR_COLD void Vtb_board_a_ctrl___024root___eval_stl(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_stl\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vinline__act_comb__TOP__0___Vtableidx1;
    __Vinline__act_comb__TOP__0___Vtableidx1 = 0;
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        vlSelfRef.tb_board_a_ctrl__DOT__regime_sw = 
            (3U & (IData)(vlSelfRef.tb_board_a_ctrl__DOT__sw));
        vlSelfRef.tb_board_a_ctrl__DOT__sw_override 
            = (1U & ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__sw) 
                     >> 2U));
        vlSelfRef.tb_board_a_ctrl__DOT__rgb1 = ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_up)
                                                 ? 
                                                ((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_error)
                                                  ? 6U
                                                  : 2U)
                                                 : 4U);
        __Vinline__act_comb__TOP__0___Vtableidx1 = vlSelfRef.tb_board_a_ctrl__DOT__active_regime;
        vlSelfRef.tb_board_a_ctrl__DOT__rgb0 = Vtb_board_a_ctrl__ConstPool__TABLE_h608c3c40_0
            [__Vinline__act_comb__TOP__0___Vtableidx1];
        vlSelfRef.tb_board_a_ctrl__DOT__led = ((((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_error) 
                                                 << 5U) 
                                                | (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__link_up) 
                                                    << 4U) 
                                                   | (0x000007f8U 
                                                      & (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__running) 
                                                          << 3U) 
                                                         & (vlSelfRef.tb_board_a_ctrl__DOT__dut__DOT__blink_ctr 
                                                            >> 0x00000015U))))) 
                                               | (((IData)(vlSelfRef.tb_board_a_ctrl__DOT__running) 
                                                   << 2U) 
                                                  | (IData)(vlSelfRef.tb_board_a_ctrl__DOT__active_regime)));
    }
}

VL_ATTR_COLD bool Vtb_board_a_ctrl___024root___eval_phase__stl(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___eval_phase__stl\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_board_a_ctrl___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_board_a_ctrl___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_board_a_ctrl___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_board_a_ctrl___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_board_a_ctrl___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_board_a_ctrl___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_board_a_ctrl___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_board_a_ctrl.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_board_a_ctrl.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( tb_board_a_ctrl.rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_board_a_ctrl___024root___ctor_var_reset(Vtb_board_a_ctrl___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_ctrl___024root___ctor_var_reset\n"); );
    Vtb_board_a_ctrl__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_board_a_ctrl__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5312820541768211995ull);
    vlSelf->tb_board_a_ctrl__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2588981789798161236ull);
    vlSelf->tb_board_a_ctrl__DOT__btn = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 8544227800947818861ull);
    vlSelf->tb_board_a_ctrl__DOT__sw = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17333347756364331060ull);
    vlSelf->tb_board_a_ctrl__DOT__regime_sw = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 655342195356925958ull);
    vlSelf->tb_board_a_ctrl__DOT__sw_override = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6527491016063530340ull);
    vlSelf->tb_board_a_ctrl__DOT__running = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 636685142482366150ull);
    vlSelf->tb_board_a_ctrl__DOT__active_regime = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9246971089622380071ull);
    vlSelf->tb_board_a_ctrl__DOT__link_up = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13024167362685470679ull);
    vlSelf->tb_board_a_ctrl__DOT__link_error = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5975463264304499617ull);
    vlSelf->tb_board_a_ctrl__DOT__led = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17918629788911715652ull);
    vlSelf->tb_board_a_ctrl__DOT__rgb0 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 3518283048157294975ull);
    vlSelf->tb_board_a_ctrl__DOT__rgb1 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 13960851980631588385ull);
    vlSelf->tb_board_a_ctrl__DOT__dut__DOT__db0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5240171698045601672ull);
    vlSelf->tb_board_a_ctrl__DOT__dut__DOT__p0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7669009079489805143ull);
    vlSelf->tb_board_a_ctrl__DOT__dut__DOT__blink_ctr = VL_SCOPED_RAND_RESET_I(25, __VscopeHash, 16826553863837991826ull);
    vlSelf->tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 12939167064034101516ull);
    vlSelf->tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7536778006252587235ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
