// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_system_top.h for the primary calling header

#include "Vtb_system_top__pch.h"

VL_ATTR_COLD void Vtb_system_top___024root___eval_static(Vtb_system_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___eval_static\n"); );
    Vtb_system_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next, __VscopeHash, 8527973246484880257ull);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_system_top__DOT__clk__0 
        = vlSelfRef.tb_system_top__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_system_top__DOT__rst_n__0 
        = vlSelfRef.tb_system_top__DOT__rst_n;
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_system_top___024root___eval_static__TOP(Vtb_system_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___eval_static__TOP\n"); );
    Vtb_system_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next, __VscopeHash, 8527973246484880257ull);
}

VL_ATTR_COLD void Vtb_system_top___024root___eval_initial__TOP(Vtb_system_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___eval_initial__TOP\n"); );
    Vtb_system_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_system_top__DOT__clk = 0U;
}

VL_ATTR_COLD void Vtb_system_top___024root___eval_final(Vtb_system_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___eval_final\n"); );
    Vtb_system_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_system_top___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_system_top___024root___eval_phase__stl(Vtb_system_top___024root* vlSelf);

VL_ATTR_COLD void Vtb_system_top___024root___eval_settle(Vtb_system_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___eval_settle\n"); );
    Vtb_system_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_system_top___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb\\tb_system_top.sv", 13, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_system_top___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_system_top___024root___eval_triggers_vec__stl(Vtb_system_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___eval_triggers_vec__stl\n"); );
    Vtb_system_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_system_top___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_system_top___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_system_top___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_system_top___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___trigger_anySet__stl\n"); );
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

extern const VlUnpacked<CData/*1:0*/, 32> Vtb_system_top__ConstPool__TABLE_hbfde2c6f_0;

VL_ATTR_COLD void Vtb_system_top___024root___stl_sequent__TOP__0(Vtb_system_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___stl_sequent__TOP__0\n"); );
    Vtb_system_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__step_size_q16_16;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__step_size_q16_16 = 0;
    IData/*31:0*/ tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__base_spread_q16_16;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__base_spread_q16_16 = 0;
    QData/*63:0*/ tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__delta_mul_c;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__delta_mul_c = 0;
    IData/*31:0*/ tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__delta_scaled_c;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__delta_scaled_c = 0;
    IData/*31:0*/ tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__mid_s_c;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__mid_s_c = 0;
    IData/*31:0*/ tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_mid_s_c;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_mid_s_c = 0;
    IData/*31:0*/ tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__spr_h_s_c;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__spr_h_s_c = 0;
    IData/*31:0*/ tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_s2_c;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_s2_c = 0;
    IData/*31:0*/ tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_s2_c;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_s2_c = 0;
    CData/*4:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__tx_ready 
        = (1U & (~ (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_link_tx__DOT__st)));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__quote_fifo_full 
        = (0x40U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_quote_fifo__DOT__count_r));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__quote_fifo_empty 
        = (0U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_quote_fifo__DOT__count_r));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_axi_regs__DOT__read_fire 
        = ((~ (IData)(vlSelfRef.tb_system_top__DOT__s_axi_rvalid_a)) 
           & (IData)(vlSelfRef.tb_system_top__DOT__s_axi_arvalid_a));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__quote_fifo_wr_en 
        = ((0x40U != (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_quote_fifo__DOT__count_r)) 
           & (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__quote_valid_ms));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_axi_regs__DOT__write_fire 
        = ((IData)(vlSelfRef.tb_system_top__DOT__s_axi_awvalid_a) 
           & ((~ (IData)(vlSelfRef.tb_system_top__DOT__s_axi_bvalid_a)) 
              & (IData)(vlSelfRef.tb_system_top__DOT__s_axi_wvalid_a)));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__quote_fifo_rd_en 
        = ((0U != (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_quote_fifo__DOT__count_r)) 
           & ((~ (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_tx_arb__DOT__tx_buf_valid)) 
              & (~ (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__fill_valid))));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[0U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[1U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[2U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[3U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[4U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[5U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[6U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[7U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vtableidx1 = (((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__p1) 
                     << 4U) | ((((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__axi_start_pulse) 
                                 | (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__p0)) 
                                << 3U) | ((((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__axi_reset_pulse) 
                                            | (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__p2)) 
                                           << 2U) | (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__fsm_state))));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__fsm_next 
        = Vtb_system_top__ConstPool__TABLE_hbfde2c6f_0
        [__Vtableidx1];
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__is_filled 
        = ((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_sym_in_range) 
           & ((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_side)
               ? (vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_limit_price 
                  <= vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_cur_bid)
               : (vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_limit_price 
                  >= vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_cur_ask)));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[0U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[1U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[2U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[3U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[4U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[5U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[6U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[7U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[8U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[9U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[10U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[11U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[12U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[13U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[14U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[15U] 
        = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__tick_raw 
        = ((2U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__fsm_state)) 
           & ((0U == vlSelfRef.tb_system_top__DOT__u_board_a__DOT__quote_interval) 
              | (vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_ctr 
                 == (vlSelfRef.tb_system_top__DOT__u_board_a__DOT__quote_interval 
                     - (IData)(1U)))));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__active_count_eff 
        = ((0U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_sym_count))
            ? 1U : ((0x10U < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_sym_count))
                     ? 0x10U : (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_sym_count)));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_regime 
        = (3U & ((4U & (IData)(vlSelfRef.tb_system_top__DOT__sw_a))
                  ? (IData)(vlSelfRef.tb_system_top__DOT__sw_a)
                  : (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__regime_from_ps)));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__lfsr_load 
        = ((1U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__fsm_state)) 
           & (2U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__fsm_next)));
    if (vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__is_filled) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__fill_qty_val 
            = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_qty;
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__fill_price_val 
            = ((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_side)
                ? vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_cur_bid
                : vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_cur_ask);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__fill_qty_val = 0U;
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__fill_price_val = 0U;
    }
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__do_quote 
        = ((0x40U != (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_quote_fifo__DOT__count_r)) 
           & (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__tick_raw));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff 
        = ((0x10U < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__active_count_eff))
            ? 0x10U : (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__active_count_eff));
    if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_regime)) 
                               << 2U) | (((1U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_regime)) 
                                          << 1U) | 
                                         (0U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_regime)))))))) {
        if ((0U != (((2U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_regime)) 
                     << 2U) | (((1U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_regime)) 
                                << 1U) | (0U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_regime)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: market_sim.sv:72: Assertion failed in %Ntb_system_top.u_board_a.u_market_sim: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_regime));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/rtl/board_a\\market_sim.sv", 72, "");
            }
        }
    }
    if ((0U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_regime))) {
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00000100U;
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00002000U;
    } else if ((1U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_regime))) {
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00001000U;
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00008000U;
    } else if ((2U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_regime))) {
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00000100U;
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00002000U;
    } else {
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00004000U;
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00010000U;
    }
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable 
        = ((2U == (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__fsm_state)) 
           & (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__do_quote));
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[0U] = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[1U] = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[2U] = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[3U] = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[4U] = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[5U] = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[6U] = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[7U] = 0U;
    if ((0U < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[0U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[0U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[0U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[0U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[0U] = 0U;
    }
    if ((1U < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[1U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[1U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[1U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[1U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[1U] = 0U;
    }
    if ((2U < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[2U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[2U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[2U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[2U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[2U] = 0U;
    }
    if ((3U < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[3U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[3U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[3U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[3U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[3U] = 0U;
    }
    if ((4U < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[4U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[4U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[4U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[4U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[4U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[4U] = 0U;
    }
    if ((5U < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[5U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[5U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[5U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[5U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[5U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[5U] = 0U;
    }
    if ((6U < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[6U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[6U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[6U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[6U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[6U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[6U] = 0U;
    }
    if ((7U < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[7U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[7U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[7U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[7U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[7U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[7U] = 0U;
    }
    if ((8U < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[8U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[8U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[8U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[8U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[8U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[8U] = 0U;
    }
    if ((9U < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[9U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[9U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[9U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[9U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[9U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[9U] = 0U;
    }
    if ((0x0aU < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[10U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[10U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[10U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[10U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[10U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[10U] = 0U;
    }
    if ((0x0bU < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[11U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[11U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[11U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[11U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[11U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[11U] = 0U;
    }
    if ((0x0cU < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[12U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[12U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[12U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[12U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[12U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[12U] = 0U;
    }
    if ((0x0dU < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[13U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[13U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[13U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[13U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[13U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[13U] = 0U;
    }
    if ((0x0eU < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[14U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[14U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[14U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[14U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[14U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[14U] = 0U;
    }
    if ((0x0fU < (IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[15U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[15U]]));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[15U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__sym_sector_id[15U]]) 
               + vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[15U]);
    } else {
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[15U] = 0U;
    }
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__delta_mul_c = 0ULL;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__delta_scaled_c = 0U;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__mid_s_c = 0U;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_mid_s_c = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_mid_u_c = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_spread_q_c = 0U;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__spr_h_s_c = 0U;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_s2_c = 0U;
    tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_s2_c = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_calc_c = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_calc_c = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_next_c[0U] = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_next_c[1U] = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_next_c[2U] = 0U;
    vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_next_c[3U] = 0U;
    if (vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__do_quote) {
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__delta_mul_c 
            = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out
                                            [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__sym_ptr]), 
                          VL_EXTENDS_QI(64,32, tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__step_size_q16_16));
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__delta_scaled_c 
            = (IData)(VL_SHIFTRS_QQI(64,64,32, tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__delta_mul_c, 0x00000010U));
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__mid_s_c 
            = vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__mid_price
            [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__sym_ptr];
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_mid_s_c 
            = (tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__mid_s_c 
               + tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__delta_scaled_c);
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_mid_u_c 
            = (VL_GTS_III(32, 0x00010000U, tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_mid_s_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_mid_s_c)
                                  ? 0x27100000U : tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_mid_s_c));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_spread_q_c 
            = tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__base_spread_q16_16;
        if ((0U == vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_spread_q_c)) {
            vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_spread_q_c = 1U;
        }
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__spr_h_s_c 
            = VL_SHIFTRS_III(32,32,32, vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_spread_q_c, 1U);
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_s2_c 
            = (vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_mid_u_c 
               - tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__spr_h_s_c);
        tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_s2_c 
            = (vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_mid_u_c 
               + tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__spr_h_s_c);
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_s2_c)
                                  ? 0x27100000U : tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_s2_c));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_s2_c)
                                  ? 0x27100000U : tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_s2_c));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_next_c[3U] 
            = ((0x0003ffffU & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_next_c[3U]) 
               | (0xfffc0000U & (0x10000000U | (((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__sym_ptr) 
                                                 << 0x00000014U) 
                                                | ((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__active_regime) 
                                                   << 0x00000012U)))));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_next_c[0U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                << 0x00000010U) | vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__seq_num
               [vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__sym_ptr]);
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_next_c[1U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                >> 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   << 0x00000010U));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_next_c[2U] 
            = (((IData)((QData)((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_calc_c))) 
                << 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   >> 0x00000010U));
        vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_next_c[3U] 
            = ((0xfffc0000U & vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_next_c[3U]) 
               | (((IData)((QData)((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_calc_c))) 
                   >> 0x00000010U) | ((IData)(((QData)((IData)(vlSelfRef.tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_calc_c)) 
                                               >> 0x00000020U)) 
                                      << 0x00000010U)));
    }
}

VL_ATTR_COLD void Vtb_system_top___024root___eval_stl(Vtb_system_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___eval_stl\n"); );
    Vtb_system_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtb_system_top___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtb_system_top___024root___eval_phase__stl(Vtb_system_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___eval_phase__stl\n"); );
    Vtb_system_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_system_top___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_system_top___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_system_top___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_system_top___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_system_top___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_system_top___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_system_top___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_system_top.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_system_top.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_system_top___024root___ctor_var_reset(Vtb_system_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_system_top___024root___ctor_var_reset\n"); );
    Vtb_system_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_system_top__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4864210923439232746ull);
    vlSelf->tb_system_top__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10382958516508520471ull);
    vlSelf->tb_system_top__DOT__btn_a = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 11735787140398162384ull);
    vlSelf->tb_system_top__DOT__sw_a = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8414367882830836526ull);
    vlSelf->tb_system_top__DOT__s_axi_awaddr_a = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14642167778726424947ull);
    vlSelf->tb_system_top__DOT__s_axi_awvalid_a = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2115806100298847143ull);
    vlSelf->tb_system_top__DOT__s_axi_wdata_a = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1106600513299211641ull);
    vlSelf->tb_system_top__DOT__s_axi_wvalid_a = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9465157990945912367ull);
    vlSelf->tb_system_top__DOT__s_axi_bvalid_a = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14607422319333015404ull);
    vlSelf->tb_system_top__DOT__s_axi_bready_a = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4184704072958394410ull);
    vlSelf->tb_system_top__DOT__s_axi_araddr_a = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14777954695996906638ull);
    vlSelf->tb_system_top__DOT__s_axi_arvalid_a = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18126822459058448596ull);
    vlSelf->tb_system_top__DOT__s_axi_rvalid_a = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7477131684299642600ull);
    vlSelf->tb_system_top__DOT__s_axi_rready_a = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18397615221228057889ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__fsm_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8918913862020363704ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__fsm_next = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7572878326489485631ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__lfsr_load = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1163117909110037997ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__axi_start_pulse = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3901498166317218372ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__axi_reset_pulse = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 131648512887381885ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__regime_from_ps = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3158689056167792059ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__quote_interval = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15831729940463177387ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__lfsr_seed = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5953429147509243451ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__sym_init_mid[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3798994478841471120ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__sym_init_spread[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8464754874492030847ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__sym_sector_id[__Vi0] = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 14915997954349329860ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__sym_company_token[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 9733458852279995081ull);
    }
    vlSelf->tb_system_top__DOT__u_board_a__DOT__active_sym_count = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17023091283179992332ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__active_regime = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12602451959017151374ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_system_top__DOT__u_board_a__DOT__fill_frame, __VscopeHash, 2612997472593519076ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__quote_valid_ms = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10262701231465472351ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__fill_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17541192637778761281ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__tx_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6737310889120685273ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__quotes_generated = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3244234930796595547ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__orders_rcvd = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7416447905061083131ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__fills_sent = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6574107356275313362ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__rejects_sent = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5546085746351423576ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__link_up = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12570600333752298959ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__best_bid[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1780536916282613405ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__best_ask[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6682543720625003156ull);
    }
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_system_top__DOT__u_board_a__DOT__frame_out, __VscopeHash, 4460919278891673549ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__frame_out_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 144868399964768933ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__quote_fifo_wr_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3397807244722287821ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__quote_fifo_rd_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9463499868395050506ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__quote_fifo_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14990274732349811061ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__quote_fifo_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8564784786959668895ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__rx_error_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6568940763755412126ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_axi_regs__DOT__write_fire = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2133205378624867661ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_axi_regs__DOT__read_fire = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13299299972944816622ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_axi_regs__DOT__idx = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 675492501704169428ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_axi_regs__DOT__tok_idx = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10789678193134191518ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__db0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16020805306613427882ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__db1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10869124261799697606ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__db2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4693868760024107777ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__p0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17248621989621694099ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__p1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13398730413661069081ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__p2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12868078662394184172ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__u_db0__DOT__counter = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 2741855800568549204ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__u_db0__DOT__btn_out_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1084376699809858421ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__u_db1__DOT__counter = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 13726847280852863483ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__u_db1__DOT__btn_out_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2588235603699832001ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__u_db2__DOT__counter = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 18377231455378924010ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_ctrl__DOT__u_db2__DOT__btn_out_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12662461336855015781ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__active_count_eff = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16825698541978468391ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__mid_price[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1639841155786507228ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__seq_num[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 298790609539504210ull);
    }
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__sym_ptr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 13543436510644362951ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_ctr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2268096002125987759ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__tick_raw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7489481321924265516ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__do_quote = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12640293260388212679ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__n_step_out[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16452485660621284482ull);
    }
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_hold, __VscopeHash, 4767505723393550606ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_mid_u_c = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18371553280764506158ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__new_spread_q_c = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6692014028902888997ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__bid_calc_c = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8827626007803738489ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__ask_calc_c = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17910924435522577531ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__quote_frame_next_c, __VscopeHash, 9786706890287349223ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7232105094251800972ull);
    }
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14440062749702398450ull);
    }
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14112357769868464673ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1442672107502604918ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12958229207606359412ull);
    }
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9202799085892242234ull);
    }
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable = 0;
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18132817162731931753ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11235047830471983707ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6549840238697532397ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7080315025011258372ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2880963426461905237ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11440712278316334757ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17376769174183923956ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13368953492871477748ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9374580923637564496ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4827452069316751536ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9544546905674429782ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14682090660048491721ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1453419219606651286ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12227170437145205131ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1435736419413608939ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15999499090604772647ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 308467028390749083ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3331869567427141076ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2576121490370661005ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16540494664166129269ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9319779409298522908ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 934051675001257336ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16129485863087343623ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13085796159713834011ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3598148213045984260ull);
    for (int __Vi0 = 0; __Vi0 < 64; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_system_top__DOT__u_board_a__DOT__u_quote_fifo__DOT__mem[__Vi0], __VscopeHash, 9546893091767747472ull);
    }
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_quote_fifo__DOT__wr_ptr = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 13431379988924945796ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_quote_fifo__DOT__rd_ptr = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 3654044484981760928ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_quote_fifo__DOT__count_r = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 4209949192708181964ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1700911353149498238ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_sym_in_range = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13075174467125220224ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_symbol = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9141164479576337891ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_side = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2829451629599462201ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_limit_price = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12607926965327890412ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_qty = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4634898247688465986ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_order_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1145238680582830464ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_timestamp = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 9165454049497851126ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_cur_bid = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11675592452570507670ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__p1_cur_ask = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3943747373350514489ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__is_filled = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6961759920010729823ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__fill_price_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13925533318793838851ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_exchange_lite__DOT__fill_qty_val = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 9173403360648129939ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_system_top__DOT__u_board_a__DOT__u_tx_arb__DOT__tx_frame_buf, __VscopeHash, 16172427190733942582ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_tx_arb__DOT__tx_buf_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12055207502131526974ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_tx__DOT__st = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12260274348521396066ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_tx__DOT__shifter, __VscopeHash, 6354157764492710071ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_tx__DOT__beat = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 7379314519733082115ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_tx__DOT__half_nibble = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13666057211617851526ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_rx__DOT__valid_s1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17001860630576583378ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_rx__DOT__valid_sync = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15254240863377311041ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_rx__DOT__data_s1 = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 13503586951021390315ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_rx__DOT__data_sync = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 5645110565919646620ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_rx__DOT__valid_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13235369327548433179ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_rx__DOT__state = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7069594894209513430ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_rx__DOT__assemble_reg, __VscopeHash, 13900632772675581492ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_rx__DOT__beat_count = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4432137421316497744ull);
    vlSelf->tb_system_top__DOT__u_board_a__DOT__u_link_rx__DOT__phase = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13137403768557411995ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_system_top__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_system_top__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
