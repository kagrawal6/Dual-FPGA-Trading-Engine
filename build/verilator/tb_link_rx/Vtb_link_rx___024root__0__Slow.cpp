// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_link_rx.h for the primary calling header

#include "Vtb_link_rx__pch.h"

void Vtb_link_rx___024root___timing_ready(Vtb_link_rx___024root* vlSelf);

VL_ATTR_COLD void Vtb_link_rx___024root___eval_static(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_static\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_link_rx__DOT__err_count_scratch = 0U;
    vlSelfRef.tb_link_rx__DOT__frames_seen = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[0U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[1U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[2U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[3U] = 0U;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__err0 = 0U;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__err1 = 0U;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__wait_p = 0U;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_rx__DOT__unnamedblk2__DOT__good_frame, __VscopeHash, 4300033435177953439ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_rx__DOT__unnamedblk2__DOT__bad_msg_frame, __VscopeHash, 1058054332176233286ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next, __VscopeHash, 5694688350888959863ull);
    vlSelfRef.__VactTriggered[0U] = (8ULL | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_rx__DOT__clk__0 
        = vlSelfRef.tb_link_rx__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_rx__DOT__rst_n__0 
        = vlSelfRef.tb_link_rx__DOT__rst_n;
    Vtb_link_rx___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_link_rx___024root___eval_static__TOP(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_static__TOP\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_link_rx__DOT__err_count_scratch = 0U;
    vlSelfRef.tb_link_rx__DOT__frames_seen = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[0U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[1U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[2U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[3U] = 0U;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__err0 = 0U;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__err1 = 0U;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__wait_p = 0U;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_rx__DOT__unnamedblk2__DOT__good_frame, __VscopeHash, 4300033435177953439ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_rx__DOT__unnamedblk2__DOT__bad_msg_frame, __VscopeHash, 1058054332176233286ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next, __VscopeHash, 5694688350888959863ull);
}

VL_ATTR_COLD void Vtb_link_rx___024root___eval_initial__TOP(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_initial__TOP\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_link_rx__DOT__clk = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_link_rx.vcd"s);
    VL_PRINTF_MT("-Info: C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv:130: $dumpvar ignored, as Verilated without --trace\n");
}

VL_ATTR_COLD void Vtb_link_rx___024root___eval_final(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_final\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtb_link_rx___024root___eval_settle(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_settle\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vtb_link_rx___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_link_rx___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_link_rx___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_link_rx.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_link_rx.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( tb_link_rx.rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_link_rx___024root___ctor_var_reset(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___ctor_var_reset\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_link_rx__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3646768123625012935ull);
    vlSelf->tb_link_rx__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8173047048151998679ull);
    vlSelf->tb_link_rx__DOT__pmod_data = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 13257978551378962233ull);
    vlSelf->tb_link_rx__DOT__pmod_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16649684949487121147ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_rx__DOT__frame_out, __VscopeHash, 5946226791402418996ull);
    vlSelf->tb_link_rx__DOT__frame_out_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17207349473138686393ull);
    vlSelf->tb_link_rx__DOT__link_up = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13576715310268496476ull);
    vlSelf->tb_link_rx__DOT__error_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8399688454624114556ull);
    vlSelf->tb_link_rx__DOT__dut__DOT__valid_s1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10213663903366443071ull);
    vlSelf->tb_link_rx__DOT__dut__DOT__valid_sync = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4159009496653836637ull);
    vlSelf->tb_link_rx__DOT__dut__DOT__data_s1 = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10956772856791907332ull);
    vlSelf->tb_link_rx__DOT__dut__DOT__data_sync = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 13148403798166627436ull);
    vlSelf->tb_link_rx__DOT__dut__DOT__valid_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13396899442205182755ull);
    vlSelf->tb_link_rx__DOT__dut__DOT__state = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5651321852680693177ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_rx__DOT__dut__DOT__assemble_reg, __VscopeHash, 5969076147415406476ull);
    vlSelf->tb_link_rx__DOT__dut__DOT__beat_count = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 2370948744605171683ull);
    vlSelf->tb_link_rx__DOT__dut__DOT__phase = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15525752155711516674ull);
    vlSelf->__Vdly__tb_link_rx__DOT__error_count = 0;
    vlSelf->__Vdly__tb_link_rx__DOT__dut__DOT__beat_count = 0;
    vlSelf->__Vdly__tb_link_rx__DOT__dut__DOT__phase = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_link_rx__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_link_rx__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
