// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_board_a_top.h for the primary calling header

#include "Vtb_board_a_top__pch.h"

void Vtb_board_a_top___024root___timing_ready(Vtb_board_a_top___024root* vlSelf);

VL_ATTR_COLD void Vtb_board_a_top___024root___eval_static(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_static\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_board_a_top__DOT__err_count = 0U;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_board_a_top__DOT__unnamedblk1__DOT__q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5465281616504101535ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next, __VscopeHash, 9322361080270760262ull);
    vlSelfRef.__VactTriggered[0U] = (8ULL | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000000000000010ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000000000000020ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000000000000040ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000000000000080ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__clk__0 
        = vlSelfRef.tb_board_a_top__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__rst_n__0 
        = vlSelfRef.tb_board_a_top__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr_h02f108bd__1 = (1U & 
                                              (~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_bvalid__0 
        = vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid;
    vlSelfRef.__Vtrigprevexpr_h28d73e28__1 = (1U & 
                                              (~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_rvalid__0 
        = vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid;
    Vtb_board_a_top___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_board_a_top___024root___eval_static__TOP(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_static__TOP\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_board_a_top__DOT__err_count = 0U;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_board_a_top__DOT__unnamedblk1__DOT__q = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5465281616504101535ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next, __VscopeHash, 9322361080270760262ull);
}

VL_ATTR_COLD void Vtb_board_a_top___024root___eval_initial__TOP(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_initial__TOP\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_board_a_top__DOT__clk = 0U;
}

VL_ATTR_COLD void Vtb_board_a_top___024root___eval_final(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_final\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_board_a_top___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_board_a_top___024root___eval_phase__stl(Vtb_board_a_top___024root* vlSelf);

VL_ATTR_COLD void Vtb_board_a_top___024root___eval_settle(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_settle\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_board_a_top___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_board_a_top.sv", 10, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_board_a_top___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_board_a_top___024root___eval_triggers_vec__stl(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_triggers_vec__stl\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_board_a_top___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_board_a_top___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_board_a_top___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_board_a_top___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___trigger_anySet__stl\n"); );
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

extern const VlUnpacked<CData/*1:0*/, 32> Vtb_board_a_top__ConstPool__TABLE_hbfde2c6f_0;

VL_ATTR_COLD void Vtb_board_a_top___024root___stl_sequent__TOP__0(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___stl_sequent__TOP__0\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0;
    QData/*63:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c = 0;
    IData/*31:0*/ tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c = 0;
    CData/*4:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_full 
        = (0x40U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_empty 
        = (0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_wr_en 
        = ((0x40U != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r)) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_valid_ms));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__tx_ready 
        = ((~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st)) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__pmod_ja_ready));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__read_fire 
        = ((~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_rvalid)) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_arvalid));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_fifo_rd_en 
        = ((0U != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r)) 
           & ((~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid)) 
              & (~ (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fill_valid))));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__write_fire 
        = ((IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_awvalid) 
           & ((~ (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_bvalid)) 
              & (IData)(vlSelfRef.tb_board_a_top__DOT__s_axi_wvalid)));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[0U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[1U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[2U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[3U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[4U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[5U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[6U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[7U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg;
    __Vtableidx1 = (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p1) 
                     << 4U) | ((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__axi_start_pulse) 
                                 | (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p0)) 
                                << 3U) | ((((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__axi_reset_pulse) 
                                            | (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p2)) 
                                           << 2U) | (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state))));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_next 
        = Vtb_board_a_top__ConstPool__TABLE_hbfde2c6f_0
        [__Vtableidx1];
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__is_filled 
        = ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_sym_in_range) 
           & ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side)
               ? (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_limit_price 
                  <= vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_bid)
               : (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_limit_price 
                  >= vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_ask)));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[0U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[1U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[2U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[3U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[4U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[5U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[6U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[7U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[8U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[9U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[10U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[11U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[12U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[13U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[14U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[15U] 
        = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__tick_raw 
        = ((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state)) 
           & ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_interval) 
              | (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_ctr 
                 == (vlSelfRef.tb_board_a_top__DOT__dut__DOT__quote_interval 
                     - (IData)(1U)))));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__active_count_eff 
        = ((0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_sym_count))
            ? 1U : ((0x10U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_sym_count))
                     ? 0x10U : (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_sym_count)));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime 
        = (3U & ((4U & (IData)(vlSelfRef.tb_board_a_top__DOT__sw))
                  ? (IData)(vlSelfRef.tb_board_a_top__DOT__sw)
                  : (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__regime_from_ps)));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__lfsr_load 
        = ((1U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state)) 
           & (2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_next)));
    if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__is_filled) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_qty_val 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_qty;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_price_val 
            = ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side)
                ? vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_bid
                : vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_ask);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_qty_val = 0U;
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_price_val = 0U;
    }
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote 
        = ((0x40U != (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r)) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__tick_raw));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff 
        = ((0x10U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__active_count_eff))
            ? 0x10U : (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__active_count_eff));
    if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)) 
                               << 2U) | (((1U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)) 
                                          << 1U) | 
                                         (0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)))))))) {
        if ((0U != (((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)) 
                     << 2U) | (((1U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)) 
                                << 1U) | (0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: market_sim.sv:72: Assertion failed in %Ntb_board_a_top.dut.u_market_sim: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime));
                VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/rtl/board_a\\market_sim.sv", 72, "");
            }
        }
    }
    if ((0U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime))) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00000100U;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00002000U;
    } else if ((1U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime))) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00001000U;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00008000U;
    } else if ((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime))) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00000100U;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00002000U;
    } else {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16 = 0x00004000U;
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16 = 0x00010000U;
    }
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable 
        = ((2U == (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__fsm_state)) 
           & (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote));
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[0U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[1U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[2U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[3U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[4U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[5U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[6U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[7U] = 0U;
    if ((0U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[0U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[0U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[0U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[0U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[0U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[0U] = 0U;
    }
    if ((1U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[1U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[1U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[1U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[1U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[1U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[1U] = 0U;
    }
    if ((2U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[2U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[2U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[2U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[2U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[2U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[2U] = 0U;
    }
    if ((3U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[3U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[3U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[3U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[3U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[3U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[3U] = 0U;
    }
    if ((4U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[4U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[4U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[4U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[4U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[4U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[4U] = 0U;
    }
    if ((5U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[5U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[5U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[5U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[5U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[5U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[5U] = 0U;
    }
    if ((6U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[6U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[6U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[6U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[6U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[6U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[6U] = 0U;
    }
    if ((7U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[7U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[7U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[7U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[7U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[7U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[7U] = 0U;
    }
    if ((8U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[8U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[8U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[8U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[8U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[8U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[8U] = 0U;
    }
    if ((9U < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[9U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[9U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[9U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[9U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[9U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[9U] = 0U;
    }
    if ((0x0aU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[10U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[10U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[10U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[10U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[10U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[10U] = 0U;
    }
    if ((0x0bU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[11U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[11U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[11U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[11U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[11U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[11U] = 0U;
    }
    if ((0x0cU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[12U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[12U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[12U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[12U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[12U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[12U] = 0U;
    }
    if ((0x0dU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[13U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[13U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[13U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[13U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[13U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[13U] = 0U;
    }
    if ((0x0eU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[14U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[14U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[14U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[14U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[14U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[14U] = 0U;
    }
    if ((0x0fU < (IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff))) {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[15U]] 
            = (0x000000ffU & ((IData)(1U) + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop
                              [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[15U]]));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[15U] 
            = ((VL_SHIFTL_III(32,32,32, (VL_EXTENDS_II(32,7, 
                                                       (0x0000003fU 
                                                        & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg)) 
                                         - (IData)(0x00000020U)), 6U) 
                + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16
                [vlSelfRef.tb_board_a_top__DOT__dut__DOT__sym_sector_id[15U]]) 
               + vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[15U]);
    } else {
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[15U] = 0U;
    }
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c = 0ULL;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c = 0U;
    tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[0U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[1U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[2U] = 0U;
    vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U] = 0U;
    if (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote) {
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c 
            = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out
                                            [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr]), 
                          VL_EXTENDS_QI(64,32, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__step_size_q16_16));
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c 
            = (IData)(VL_SHIFTRS_QQI(64,64,32, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_mul_c, 0x00000010U));
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c 
            = vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price
            [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr];
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c 
            = (tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_s_c 
               + tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__delta_scaled_c);
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c 
            = (VL_GTS_III(32, 0x00010000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c)
                                  ? 0x27100000U : tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_s_c));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c 
            = tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__base_spread_q16_16;
        if ((0U == vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c)) {
            vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c = 1U;
        }
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c 
            = VL_SHIFTRS_III(32,32,32, vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c, 1U);
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c 
            = (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c 
               - tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c);
        tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c 
            = (vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c 
               + tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__spr_h_s_c);
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c)
                                  ? 0x27100000U : tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_s2_c));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c 
            = (VL_GTS_III(32, 0x00010000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c)
                ? 0x00010000U : (VL_LTS_III(32, 0x27100000U, tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c)
                                  ? 0x27100000U : tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_s2_c));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U] 
            = ((0x0003ffffU & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U]) 
               | (0xfffc0000U & (0x10000000U | (((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr) 
                                                 << 0x00000014U) 
                                                | ((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__active_regime) 
                                                   << 0x00000012U)))));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[0U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                << 0x00000010U) | vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num
               [vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr]);
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[1U] 
            = (((IData)((0x0000000003e803e8ULL | ((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                  << 0x00000020U))) 
                >> 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   << 0x00000010U));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[2U] 
            = (((IData)((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c))) 
                << 0x00000010U) | ((IData)(((0x0000000003e803e8ULL 
                                             | ((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c)) 
                                                << 0x00000020U)) 
                                            >> 0x00000020U)) 
                                   >> 0x00000010U));
        vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U] 
            = ((0xfffc0000U & vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c[3U]) 
               | (((IData)((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c))) 
                   >> 0x00000010U) | ((IData)(((QData)((IData)(vlSelfRef.tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c)) 
                                               >> 0x00000020U)) 
                                      << 0x00000010U)));
    }
}

VL_ATTR_COLD void Vtb_board_a_top___024root___eval_stl(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_stl\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtb_board_a_top___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtb_board_a_top___024root___eval_phase__stl(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___eval_phase__stl\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_board_a_top___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_board_a_top___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_board_a_top___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_board_a_top___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_board_a_top___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_board_a_top___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_board_a_top___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_board_a_top.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_board_a_top.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( tb_board_a_top.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 4 is active: @( (~ tb_board_a_top.s_axi_bvalid))\n");
    }
    if ((1U & (IData)((triggers[0U] >> 5U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 5 is active: @( tb_board_a_top.s_axi_bvalid)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 6U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 6 is active: @( (~ tb_board_a_top.s_axi_rvalid))\n");
    }
    if ((1U & (IData)((triggers[0U] >> 7U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 7 is active: @( tb_board_a_top.s_axi_rvalid)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_board_a_top___024root___ctor_var_reset(Vtb_board_a_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_board_a_top___024root___ctor_var_reset\n"); );
    Vtb_board_a_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_board_a_top__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4289783609395386788ull);
    vlSelf->tb_board_a_top__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12646153050136009960ull);
    vlSelf->tb_board_a_top__DOT__btn = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 9088532871188460274ull);
    vlSelf->tb_board_a_top__DOT__sw = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3452699672462163492ull);
    vlSelf->tb_board_a_top__DOT__pmod_ja_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3993333179932750767ull);
    vlSelf->tb_board_a_top__DOT__pmod_jb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 4425137145725900809ull);
    vlSelf->tb_board_a_top__DOT__pmod_jb_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8209125434540545153ull);
    vlSelf->tb_board_a_top__DOT__s_axi_awaddr = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8834016334547752161ull);
    vlSelf->tb_board_a_top__DOT__s_axi_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8557323285237677205ull);
    vlSelf->tb_board_a_top__DOT__s_axi_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11313925567710792675ull);
    vlSelf->tb_board_a_top__DOT__s_axi_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8322526601413076617ull);
    vlSelf->tb_board_a_top__DOT__s_axi_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16107151188024937167ull);
    vlSelf->tb_board_a_top__DOT__s_axi_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14386116398009912047ull);
    vlSelf->tb_board_a_top__DOT__s_axi_araddr = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3231841704961292795ull);
    vlSelf->tb_board_a_top__DOT__s_axi_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12142503909545571450ull);
    vlSelf->tb_board_a_top__DOT__s_axi_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17806515018252547997ull);
    vlSelf->tb_board_a_top__DOT__s_axi_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12777108214716395097ull);
    vlSelf->tb_board_a_top__DOT__s_axi_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1256204862534869471ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__fsm_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9634678114755462603ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__fsm_next = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10364498387243019576ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__lfsr_load = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2088259484075498899ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__axi_start_pulse = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 707390378787992214ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__axi_reset_pulse = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2770576716664939892ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__regime_from_ps = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14189537262881515323ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__quote_interval = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14023035555030891595ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__lfsr_seed = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8164221005908300143ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__sym_init_mid[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18025560635953930660ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__sym_init_spread[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8843740653618493675ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__sym_sector_id[__Vi0] = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11810577422244737559ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__sym_company_token[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 2366157601149723889ull);
    }
    vlSelf->tb_board_a_top__DOT__dut__DOT__active_sym_count = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10317825213682259966ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__active_regime = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16766362731121683768ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_board_a_top__DOT__dut__DOT__fill_frame, __VscopeHash, 4207265004324883398ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__quote_valid_ms = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6804383839968230166ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__fill_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9219604572461129068ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__tx_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10602050672425351233ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__quotes_generated = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16679089782132113326ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__orders_rcvd = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 340294031727507925ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__fills_sent = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7053920788782417465ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__rejects_sent = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11486886672813589611ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__link_up = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2413264743798851308ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__best_bid[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3133449016402967126ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__best_ask[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1033213100773428826ull);
    }
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_board_a_top__DOT__dut__DOT__frame_out, __VscopeHash, 13570512877244936725ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__frame_out_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13093156808606830206ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__quote_fifo_wr_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12660193050031398631ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__quote_fifo_rd_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16109332694871667390ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__quote_fifo_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18272405557396264322ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__quote_fifo_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 180034253884780791ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__rx_error_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4640342619059879818ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__write_fire = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11917844374230572317ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__read_fire = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12205320863636590148ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__idx = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7857297833151167781ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_axi_regs__DOT__tok_idx = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12330731298779859068ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4365232707407075527ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10950299352843669941ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__db2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 477770912555133312ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13579242879279653816ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15549580658042089552ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__p2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 680100345607669669ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__blink_ctr = VL_SCOPED_RAND_RESET_I(25, __VscopeHash, 16520663174712120030ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__counter = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 13032664218746951998ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db0__DOT__btn_out_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13294622444425549795ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__counter = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 1902200070597452746ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db1__DOT__btn_out_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7293446948729344424ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__counter = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 17732641621909898935ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_ctrl__DOT__u_db2__DOT__btn_out_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13787905809146286969ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__active_count_eff = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2050107219128479669ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__mid_price[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13081826148642862152ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__seq_num[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16064226981719850401ull);
    }
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__sym_ptr = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 8874726325665926263ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_ctr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10760286697864830943ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__tick_raw = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5858560523909067774ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__do_quote = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3029408384611152146ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__n_step_out[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2387631860628337692ull);
    }
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_hold, __VscopeHash, 654641082875038522ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_mid_u_c = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5141570414986344892ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__new_spread_q_c = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6790063550121062067ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__bid_calc_c = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16363352182718229097ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__ask_calc_c = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16967315092818878590ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__quote_frame_next_c, __VscopeHash, 3059775250703620148ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_rand[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1512249847556301265ull);
    }
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_rand[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5548033794489672014ull);
    }
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__active_count_eff = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15450409513092301666ull);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sector_pop[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 762261364019862384ull);
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sym_drift_q16_16[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1839254743737944184ull);
    }
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__sec_drift_q16_16[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3179246134106590695ull);
    }
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT____Vcellinp__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__enable = 0;
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__u_global_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1891764507618532184ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__0__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6032595844649892975ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__1__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4879488570001051306ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__2__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3884307717073322945ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__3__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 782623987849252802ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__4__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17622040589536968527ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__5__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16595492275121222771ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__6__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12211667231972263086ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__7__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2002898381446086343ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__8__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13207850433658417522ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__9__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17417961224395726713ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__10__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18088653677355916222ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__11__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12283678573969130143ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__12__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 859564942579082583ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__13__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8276005650114198181ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__14__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6521465482295845598ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sym_rng__BRA__15__KET____DOT__u_sym_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15975234051152068356ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__0__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13118275037767788732ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__1__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14794057042702645717ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__2__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7870262058214869279ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__3__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6508109463770380127ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__4__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9176240349694791785ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__5__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2901930350142357443ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__6__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5958988930314050312ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_market_sim__DOT__u_market_noise_gen__DOT__g_sec_rng__BRA__7__KET____DOT__u_sec_lfsr__DOT__lfsr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13851774385005787464ull);
    for (int __Vi0 = 0; __Vi0 < 64; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__mem[__Vi0], __VscopeHash, 9728925897683915284ull);
    }
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__wr_ptr = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 15537985201179129802ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__rd_ptr = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 6350953630817008704ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_quote_fifo__DOT__count_r = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 13337549363861547750ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13795048818291417129ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_sym_in_range = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18300527392229257302ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_symbol = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12487662195427426522ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_side = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6571341412816480867ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_limit_price = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7778335877276168387ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_qty = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4140858237253526349ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_order_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11131774548672329383ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_timestamp = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4116560072632223055ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_bid = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11004805072630565510ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__p1_cur_ask = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6469786731099776992ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__is_filled = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18046872229782490617ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_price_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11541597054750075272ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_exchange_lite__DOT__fill_qty_val = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17216432892326173885ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_frame_buf, __VscopeHash, 18052105953627416305ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_tx_arb__DOT__tx_buf_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1839771061925918592ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__st = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16416919381134931911ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__shifter, __VscopeHash, 9520519849373902024ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__beat = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 7402502274841571694ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_tx__DOT__half_nibble = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5364265840859934027ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_s1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8034659366391768931ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_sync = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17863604535850855890ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__data_s1 = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 16867045944140937699ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__data_sync = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 7955518644164846095ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__valid_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7570924057528613449ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__state = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10487153746169355609ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__assemble_reg, __VscopeHash, 15865331549603059065ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__beat_count = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 6815805591906318381ull);
    vlSelf->tb_board_a_top__DOT__dut__DOT__u_link_rx__DOT__phase = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7302273675295435221ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_board_a_top__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_board_a_top__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr_h02f108bd__1 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_bvalid__0 = 0;
    vlSelf->__Vtrigprevexpr_h28d73e28__1 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_board_a_top__DOT__s_axi_rvalid__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
