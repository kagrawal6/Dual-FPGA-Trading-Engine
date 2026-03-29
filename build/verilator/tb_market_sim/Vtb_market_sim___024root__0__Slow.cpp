// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_market_sim.h for the primary calling header

#include "Vtb_market_sim__pch.h"

void Vtb_market_sim___024root___timing_ready(Vtb_market_sim___024root* vlSelf);

VL_ATTR_COLD void Vtb_market_sim___024root___eval_static(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_static\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_sim__DOT__err_count = 0U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym = 0U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap = 0U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__q = 0U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__seen_volatile = 0U;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_market_sim__DOT__unnamedblk2__DOT__qg_before_block = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18300914376543472423ull);
    vlSelfRef.__VactTriggered[0U] = (8ULL | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_market_sim__DOT__clk__0 
        = vlSelfRef.tb_market_sim__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_market_sim__DOT__rst_n__0 
        = vlSelfRef.tb_market_sim__DOT__rst_n;
    Vtb_market_sim___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_market_sim___024root___eval_static__TOP(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_static__TOP\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_sim__DOT__err_count = 0U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__exp_sym = 0U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__sym_wrap = 0U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__q = 0U;
    vlSelfRef.tb_market_sim__DOT__unnamedblk2__DOT__seen_volatile = 0U;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_market_sim__DOT__unnamedblk2__DOT__qg_before_block = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18300914376543472423ull);
}

VL_ATTR_COLD void Vtb_market_sim___024root___eval_initial__TOP(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_initial__TOP\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_market_sim__DOT__clk = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_market_sim.vcd"s);
    VL_PRINTF_MT("-Info: C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv:78: $dumpvar ignored, as Verilated without --trace\n");
}

VL_ATTR_COLD void Vtb_market_sim___024root___eval_final(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_final\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_market_sim___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_market_sim___024root___eval_phase__stl(Vtb_market_sim___024root* vlSelf);

VL_ATTR_COLD void Vtb_market_sim___024root___eval_settle(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_settle\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_market_sim___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_market_sim.sv", 16, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_market_sim___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_market_sim___024root___eval_triggers_vec__stl(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_triggers_vec__stl\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_market_sim___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_market_sim___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_market_sim___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_market_sim___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtb_market_sim___024root___stl_sequent__TOP__0(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___stl_sequent__TOP__0\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    QData/*63:0*/ tb_market_sim__DOT__dut__DOT__delta_mul_c;
    tb_market_sim__DOT__dut__DOT__delta_mul_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__delta_scaled_c;
    tb_market_sim__DOT__dut__DOT__delta_scaled_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__mid_s_c;
    tb_market_sim__DOT__dut__DOT__mid_s_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__new_mid_s_c;
    tb_market_sim__DOT__dut__DOT__new_mid_s_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__spr_h_s_c;
    tb_market_sim__DOT__dut__DOT__spr_h_s_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__bid_s2_c;
    tb_market_sim__DOT__dut__DOT__bid_s2_c = 0;
    IData/*31:0*/ tb_market_sim__DOT__dut__DOT__ask_s2_c;
    tb_market_sim__DOT__dut__DOT__ask_s2_c = 0;
    // Body
    if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)) 
                               << 2U) | (((1U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)) 
                                          << 1U) | 
                                         (0U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)))))))) {
        if ((0U != (((2U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)) 
                     << 2U) | (((1U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)) 
                                << 1U) | (0U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: market_sim.sv:72: Assertion failed in %Ntb_market_sim.dut: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(vlSelfRef.tb_market_sim__DOT__active_regime));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/rtl/board_a\\market_sim.sv", 72, "");
            }
        }
    }
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[0U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[1U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[2U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[3U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[0U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[1U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[2U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[3U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[4U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[5U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[6U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[7U] 
        = vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    if ((0U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16 = 0x00000100U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = 0x00002000U;
    } else if ((1U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16 = 0x00001000U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = 0x00008000U;
    } else if ((2U == (IData)(vlSelfRef.tb_market_sim__DOT__active_regime))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16 = 0x00000100U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = 0x00002000U;
    } else {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16 = 0x00004000U;
        vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = 0x00010000U;
    }
    vlSelfRef.tb_market_sim__DOT__dut__DOT__tick_raw 
        = ((IData)(vlSelfRef.tb_market_sim__DOT__enable) 
           & ((0U == vlSelfRef.tb_market_sim__DOT__quote_interval) 
              | (vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_ctr 
                 == (vlSelfRef.tb_market_sim__DOT__quote_interval 
                     - (IData)(1U)))));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__active_count_eff 
        = ((0U == (IData)(vlSelfRef.tb_market_sim__DOT__active_sym_count))
            ? 1U : ((4U < (IData)(vlSelfRef.tb_market_sim__DOT__active_sym_count))
                     ? 4U : (IData)(vlSelfRef.tb_market_sim__DOT__active_sym_count)));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__do_quote 
        = ((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__tick_raw) 
           & (IData)(vlSelfRef.tb_market_sim__DOT__quote_ready));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff 
        = ((4U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__active_count_eff))
            ? 4U : (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__active_count_eff));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable 
        = ((IData)(vlSelfRef.tb_market_sim__DOT__enable) 
           & (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__do_quote));
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[3U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[4U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[5U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[6U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[7U] = 0U;
    if ((0U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_market_sim__DOT__sector_id[0U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_market_sim__DOT__sector_id[0U]]));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[0U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_sim__DOT__sector_id[0U]]) 
               + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U]);
    } else {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[0U] = 0U;
    }
    if ((1U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_market_sim__DOT__sector_id[1U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_market_sim__DOT__sector_id[1U]]));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[1U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_sim__DOT__sector_id[1U]]) 
               + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U]);
    } else {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[1U] = 0U;
    }
    if ((2U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_market_sim__DOT__sector_id[2U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_market_sim__DOT__sector_id[2U]]));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[2U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_sim__DOT__sector_id[2U]]) 
               + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U]);
    } else {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[2U] = 0U;
    }
    if ((3U < (IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_market_sim__DOT__sector_id[3U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_market_sim__DOT__sector_id[3U]]));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[3U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_market_sim__DOT__sector_id[3U]]) 
               + vlSelfRef.tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U]);
    } else {
        vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out[3U] = 0U;
    }
    tb_market_sim__DOT__dut__DOT__delta_mul_c = 0ULL;
    tb_market_sim__DOT__dut__DOT__delta_scaled_c = 0U;
    tb_market_sim__DOT__dut__DOT__mid_s_c = 0U;
    tb_market_sim__DOT__dut__DOT__new_mid_s_c = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c = 0U;
    tb_market_sim__DOT__dut__DOT__spr_h_s_c = 0U;
    tb_market_sim__DOT__dut__DOT__bid_s2_c = 0U;
    tb_market_sim__DOT__dut__DOT__ask_s2_c = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[0U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[1U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[2U] = 0U;
    vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U] = 0U;
    if (vlSelfRef.tb_market_sim__DOT__dut__DOT__do_quote) {
        tb_market_sim__DOT__dut__DOT__delta_mul_c = 
            VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__n_step_out
                                          [vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr]), 
                        VL_EXTENDS_QI(64,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__step_size_q16_16));
        tb_market_sim__DOT__dut__DOT__delta_scaled_c 
            = (IData)(VL_SHIFTRS_QQI(64,64,32, tb_market_sim__DOT__dut__DOT__delta_mul_c, 0x00000010U));
        tb_market_sim__DOT__dut__DOT__mid_s_c = vlSelfRef.tb_market_sim__DOT__dut__DOT__mid_price
            [vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr];
        tb_market_sim__DOT__dut__DOT__new_mid_s_c = 
            (tb_market_sim__DOT__dut__DOT__mid_s_c 
             + tb_market_sim__DOT__dut__DOT__delta_scaled_c);
        vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c 
            = (VL_GTS_III(32, 0x00010000U, tb_market_sim__DOT__dut__DOT__new_mid_s_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_market_sim__DOT__dut__DOT__new_mid_s_c)
                                  ? 0x27100000U : tb_market_sim__DOT__dut__DOT__new_mid_s_c));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c 
            = vlSelfRef.tb_market_sim__DOT__dut__DOT__base_spread_q16_16;
        if ((0U == vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c)) {
            vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c = 1U;
        }
        tb_market_sim__DOT__dut__DOT__spr_h_s_c = VL_SHIFTRS_III(32,32,32, vlSelfRef.tb_market_sim__DOT__dut__DOT__new_spread_q_c, 1U);
        tb_market_sim__DOT__dut__DOT__bid_s2_c = (vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c 
                                                  - tb_market_sim__DOT__dut__DOT__spr_h_s_c);
        tb_market_sim__DOT__dut__DOT__ask_s2_c = (vlSelfRef.tb_market_sim__DOT__dut__DOT__new_mid_u_c 
                                                  + tb_market_sim__DOT__dut__DOT__spr_h_s_c);
        vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_market_sim__DOT__dut__DOT__bid_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_market_sim__DOT__dut__DOT__bid_s2_c)
                                  ? 0x27100000U : tb_market_sim__DOT__dut__DOT__bid_s2_c));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_market_sim__DOT__dut__DOT__ask_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_market_sim__DOT__dut__DOT__ask_s2_c)
                                  ? 0x27100000U : tb_market_sim__DOT__dut__DOT__ask_s2_c));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U] 
            = ((0x0003ffffU & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U]) 
               | (0xfffc0000U & (0x10000000U | (((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr) 
                                                 << 0x00000014U) 
                                                | ((IData)(vlSelfRef.tb_market_sim__DOT__active_regime) 
                                                   << 0x00000012U)))));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[0U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                << 0x00000010U) | vlSelfRef.tb_market_sim__DOT__dut__DOT__seq_num
               [vlSelfRef.tb_market_sim__DOT__dut__DOT__sym_ptr]);
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[1U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                >> 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   << 0x00000010U));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[2U] 
            = (((IData)((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c))) 
                << 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   >> 0x00000010U));
        vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U] 
            = ((0xfffc0000U & vlSelfRef.tb_market_sim__DOT__dut__DOT__quote_frame_next_c[3U]) 
               | (((IData)((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c))) 
                   >> 0x00000010U) | ((IData)(((QData)((IData)(vlSelfRef.tb_market_sim__DOT__dut__DOT__bid_calc_c)) 
                                               >> 0x00000020U)) 
                                      << 0x00000010U)));
    }
}

VL_ATTR_COLD void Vtb_market_sim___024root___eval_stl(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_stl\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtb_market_sim___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtb_market_sim___024root___eval_phase__stl(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___eval_phase__stl\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_market_sim___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_market_sim___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_market_sim___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_market_sim___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_market_sim___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_market_sim___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_market_sim___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_market_sim.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_market_sim.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( tb_market_sim.rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_market_sim___024root___ctor_var_reset(Vtb_market_sim___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_market_sim___024root___ctor_var_reset\n"); );
    Vtb_market_sim__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_market_sim__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8132765567025290501ull);
    vlSelf->tb_market_sim__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10583968096120321141ull);
    vlSelf->tb_market_sim__DOT__enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2253490100245568515ull);
    vlSelf->tb_market_sim__DOT__lfsr_load = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15943313910375163633ull);
    vlSelf->tb_market_sim__DOT__lfsr_seed = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13623231592610804321ull);
    vlSelf->tb_market_sim__DOT__active_regime = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14553339385405398746ull);
    vlSelf->tb_market_sim__DOT__quote_interval = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11755313395359958582ull);
    vlSelf->tb_market_sim__DOT__active_sym_count = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1617345270565894589ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__sector_id[__Vi0] = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 8255221696738179770ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__init_mid[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10739024249117547720ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__init_spread[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11109947071664687057ull);
    }
    vlSelf->tb_market_sim__DOT__quote_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15501489446552854618ull);
    vlSelf->tb_market_sim__DOT__quote_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11132262869415322291ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__best_bid[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 910649376816351371ull);
    }
    vlSelf->tb_market_sim__DOT__quotes_generated = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6269319993005751297ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__seq_expect[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 8139929648659965258ull);
    }
    vlSelf->tb_market_sim__DOT__sym_id_u8 = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10968554413982396383ull);
    vlSelf->tb_market_sim__DOT__regime_in_frame = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 18337218171515968448ull);
    vlSelf->tb_market_sim__DOT__seq_in_frame = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11544409128746937389ull);
    vlSelf->tb_market_sim__DOT__bid_u = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13899469003108916046ull);
    vlSelf->tb_market_sim__DOT__ask_u = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18230947058202847230ull);
    vlSelf->tb_market_sim__DOT__spread_b = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4897201036618534565ull);
    vlSelf->tb_market_sim__DOT__spread_meas = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15296525335328851127ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__step_size_q16_16 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17258405821982472448ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__base_spread_q16_16 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5864269990527198597ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__active_count_eff = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10444366558767003613ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__dut__DOT__mid_price[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3954561410077672709ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__dut__DOT__seq_num[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4431070267311116080ull);
    }
    vlSelf->tb_market_sim__DOT__dut__DOT__sym_ptr = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16643362536760108434ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__quote_ctr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 276191864953905536ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__tick_raw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 888031060424074369ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__do_quote = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14237279916856997408ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__dut__DOT__n_step_out[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15372525185648806165ull);
    }
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_market_sim__DOT__dut__DOT__quote_frame_hold, __VscopeHash, 14985109123317768661ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__new_mid_u_c = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17938093980613057353ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__new_spread_q_c = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13075153848628021547ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__bid_calc_c = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5738162036500988033ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__ask_calc_c = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 980029346494447437ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_market_sim__DOT__dut__DOT__quote_frame_next_c, __VscopeHash, 15873539272670179458ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_rand[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3032924436038353531ull);
    }
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_rand[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14359565165563579331ull);
    }
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__active_count_eff = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15606536099966796321ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sector_pop[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5104481351683266590ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16193159433754936794ull);
    }
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18274320021258096129ull);
    }
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable = 0;
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3726738206327367922ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8438489581527623339ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17375488170634895570ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18379907035348048801ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9060499414842612206ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6892918809303340334ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5871583115608531893ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15203190982458389144ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10594411634045255723ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10219298864327872976ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2185620912469683629ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12274756509055055160ull);
    vlSelf->tb_market_sim__DOT__dut__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12936413587078326633ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_market_sim__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_market_sim__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
