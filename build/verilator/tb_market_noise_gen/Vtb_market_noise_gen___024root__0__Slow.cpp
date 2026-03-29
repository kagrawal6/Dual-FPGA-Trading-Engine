// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_market_noise_gen.h for the primary calling header

#include "Vtb_market_noise_gen__pch.h"

void Vtb_market_noise_gen___024root___timing_ready(Vtb_market_noise_gen___024root* vlSelf);

VL_ATTR_COLD void Vtb_market_noise_gen___024root___eval_static(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_static\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_noise_gen__DOT__err_count = 0U;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 24; ++__Vi1) {
            vlSelf->tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[__Vi0][__Vi1] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3343816890071919622ull);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 24; ++__Vi1) {
            vlSelf->tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[__Vi0][__Vi1] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9560369444407943615ull);
        }
    }
    vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__diff01 = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec0 = 0ULL;
    vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec1 = 0ULL;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 3; ++__Vi1) {
            vlSelf->tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[__Vi0][__Vi1] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6335950089985076547ull);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 3; ++__Vi1) {
            vlSelf->tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[__Vi0][__Vi1] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3030194450002036711ull);
        }
    }
    vlSelfRef.__VactTriggered[0U] = (8ULL | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__clk__0 
        = vlSelfRef.tb_market_noise_gen__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__rst_n__0 
        = vlSelfRef.tb_market_noise_gen__DOT__rst_n;
    Vtb_market_noise_gen___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_market_noise_gen___024root___eval_static__TOP(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_static__TOP\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_noise_gen__DOT__err_count = 0U;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 24; ++__Vi1) {
            vlSelf->tb_market_noise_gen__DOT__unnamedblk4__DOT__run_a[__Vi0][__Vi1] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3343816890071919622ull);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 24; ++__Vi1) {
            vlSelf->tb_market_noise_gen__DOT__unnamedblk4__DOT__run_b[__Vi0][__Vi1] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9560369444407943615ull);
        }
    }
    vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__diff01 = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec0 = 0ULL;
    vlSelfRef.tb_market_noise_gen__DOT__unnamedblk4__DOT__cum_abs_sec1 = 0ULL;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 3; ++__Vi1) {
            vlSelf->tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_x[__Vi0][__Vi1] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6335950089985076547ull);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 3; ++__Vi1) {
            vlSelf->tb_market_noise_gen__DOT__unnamedblk4__DOT__unnamedblk7__DOT__tail_y[__Vi0][__Vi1] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3030194450002036711ull);
        }
    }
}

VL_ATTR_COLD void Vtb_market_noise_gen___024root___eval_initial__TOP(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_initial__TOP\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_noise_gen__DOT__clk = 0U;
}

VL_ATTR_COLD void Vtb_market_noise_gen___024root___eval_final(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_final\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_market_noise_gen___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_market_noise_gen___024root___eval_phase__stl(Vtb_market_noise_gen___024root* vlSelf);

VL_ATTR_COLD void Vtb_market_noise_gen___024root___eval_settle(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_settle\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_market_noise_gen___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_noise_gen.sv", 13, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_market_noise_gen___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_market_noise_gen___024root___eval_triggers_vec__stl(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_triggers_vec__stl\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_market_noise_gen___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_market_noise_gen___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_market_noise_gen___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_market_noise_gen___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtb_market_noise_gen___024root___stl_sequent__TOP__0(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___stl_sequent__TOP__0\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[0U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[0U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[1U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[1U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[2U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[2U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[3U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[3U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[4U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[4U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[5U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[5U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[6U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[6U];
    vlSelfRef.tb_market_noise_gen__DOT__sector_noise_q16_16[7U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[7U];
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable 
        = ((IData)(vlSelfRef.tb_market_noise_gen__DOT__enable) 
           & (IData)(vlSelfRef.tb_market_noise_gen__DOT__tick));
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_rand[0U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_rand[1U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_rand[2U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_rand[3U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[0U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[1U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[2U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[3U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[4U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[5U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[6U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_rand[7U] 
        = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff 
        = ((4U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__active_sym_count))
            ? 4U : (IData)(vlSelfRef.tb_market_noise_gen__DOT__active_sym_count));
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[0U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[1U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[2U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[3U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[4U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[5U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[6U] = 0U;
    vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[7U] = 0U;
    if ((0U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                              [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]));
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U] 
            = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[0U];
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_noise_gen__DOT__sector_id[0U]]) 
               + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[0U]);
    } else {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[0U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[0U] = 0U;
    }
    if ((1U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                              [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]));
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U] 
            = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[1U];
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_noise_gen__DOT__sector_id[1U]]) 
               + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[1U]);
    } else {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[1U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[1U] = 0U;
    }
    if ((2U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                              [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]));
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U] 
            = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[2U];
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_noise_gen__DOT__sector_id[2U]]) 
               + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[2U]);
    } else {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[2U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[2U] = 0U;
    }
    if ((3U < (IData)(vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__active_count_eff))) {
        vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop[vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sector_pop
                              [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]));
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U] 
            = vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[3U];
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_noise_gen__DOT__sector_id[3U]]) 
               + vlSelfRef.tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[3U]);
    } else {
        vlSelfRef.tb_market_noise_gen__DOT__company_noise_q16_16[3U] = 0U;
        vlSelfRef.tb_market_noise_gen__DOT__step_out_q16_16[3U] = 0U;
    }
}

VL_ATTR_COLD void Vtb_market_noise_gen___024root___eval_stl(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_stl\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtb_market_noise_gen___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtb_market_noise_gen___024root___eval_phase__stl(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___eval_phase__stl\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_market_noise_gen___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_market_noise_gen___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_market_noise_gen___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_market_noise_gen___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_market_noise_gen___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_market_noise_gen___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_market_noise_gen___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_market_noise_gen.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_market_noise_gen.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( tb_market_noise_gen.rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_market_noise_gen___024root___ctor_var_reset(Vtb_market_noise_gen___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_noise_gen___024root___ctor_var_reset\n"); );
    Vtb_market_noise_gen__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->tb_market_noise_gen__DOT____Vlvbound_hfe5e2d2f__0 = 0;
    vlSelf->tb_market_noise_gen__DOT____Vlvbound_h546553af__0 = 0;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_market_noise_gen__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5911782632311984704ull);
    vlSelf->tb_market_noise_gen__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5903399981987933972ull);
    vlSelf->tb_market_noise_gen__DOT__enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8480306588029937979ull);
    vlSelf->tb_market_noise_gen__DOT__lfsr_load = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8758860722770574241ull);
    vlSelf->tb_market_noise_gen__DOT__tick = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14109292141600416607ull);
    vlSelf->tb_market_noise_gen__DOT__base_seed = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14729542483752455324ull);
    vlSelf->tb_market_noise_gen__DOT__active_sym_count = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 867914126111068553ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_noise_gen__DOT__sector_id[__Vi0] = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 2525458018174067052ull);
    }
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_market_noise_gen__DOT__sector_noise_q16_16[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17722091157940498400ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_noise_gen__DOT__company_noise_q16_16[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15375426576159076004ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_noise_gen__DOT__step_out_q16_16[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17914092008713418857ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_noise_gen__DOT__dut__DOT__sym_rand[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15492835615826416560ull);
    }
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_market_noise_gen__DOT__dut__DOT__sector_rand[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15722781518157438461ull);
    }
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__active_count_eff = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3029573766070765519ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_market_noise_gen__DOT__dut__DOT__sector_pop[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2358962857681137518ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_noise_gen__DOT__dut__DOT__sym_drift_q16_16[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2581986095407279404ull);
    }
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_market_noise_gen__DOT__dut__DOT__sec_drift_q16_16[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3007739570067302314ull);
    }
    vlSelf->tb_market_noise_gen__DOT__dut__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable = 0;
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__u_global_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7984123890037400768ull);
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6152722278248265514ull);
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9562091973173335872ull);
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2886184839465110562ull);
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2003319377347739991ull);
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9779737372704626665ull);
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17445850362284643642ull);
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15849062057833319763ull);
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17350036021451364221ull);
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6880709213869111032ull);
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17782080744499487456ull);
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1177345786770711753ull);
    vlSelf->tb_market_noise_gen__DOT__dut__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10466630159405332444ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_market_noise_gen__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
