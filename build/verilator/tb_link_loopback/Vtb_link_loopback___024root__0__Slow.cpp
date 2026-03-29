// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_link_loopback.h for the primary calling header

#include "Vtb_link_loopback__pch.h"

void Vtb_link_loopback___024root___timing_ready(Vtb_link_loopback___024root* vlSelf);

VL_ATTR_COLD void Vtb_link_loopback___024root___eval_static(Vtb_link_loopback___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___eval_static\n"); );
    Vtb_link_loopback__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_link_loopback__DOT__err_count = 0U;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_loopback__DOT__unnamedblk1__DOT__payload, __VscopeHash, 12766095908399591860ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_loopback__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next, __VscopeHash, 5494979706734083344ull);
    vlSelfRef.__VactTriggered[0U] = (8ULL | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__VactTriggered[0U] = (0x0000000000000010ULL 
                                     | vlSelfRef.__VactTriggered[0U]);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_loopback__DOT__clk__0 
        = vlSelfRef.tb_link_loopback__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_loopback__DOT__rst_n__0 
        = vlSelfRef.tb_link_loopback__DOT__rst_n;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_loopback__DOT__frame_out_valid__0 
        = vlSelfRef.tb_link_loopback__DOT__frame_out_valid;
    Vtb_link_loopback___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vtb_link_loopback___024root___eval_static__TOP(Vtb_link_loopback___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___eval_static__TOP\n"); );
    Vtb_link_loopback__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_link_loopback__DOT__err_count = 0U;
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_loopback__DOT__unnamedblk1__DOT__payload, __VscopeHash, 12766095908399591860ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_loopback__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next, __VscopeHash, 5494979706734083344ull);
}

VL_ATTR_COLD void Vtb_link_loopback___024root___eval_initial__TOP(Vtb_link_loopback___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___eval_initial__TOP\n"); );
    Vtb_link_loopback__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_link_loopback__DOT__clk = 0U;
}

VL_ATTR_COLD void Vtb_link_loopback___024root___eval_final(Vtb_link_loopback___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___eval_final\n"); );
    Vtb_link_loopback__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_link_loopback___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtb_link_loopback___024root___eval_phase__stl(Vtb_link_loopback___024root* vlSelf);

VL_ATTR_COLD void Vtb_link_loopback___024root___eval_settle(Vtb_link_loopback___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___eval_settle\n"); );
    Vtb_link_loopback__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtb_link_loopback___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_loopback.sv", 10, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtb_link_loopback___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtb_link_loopback___024root___eval_triggers_vec__stl(Vtb_link_loopback___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___eval_triggers_vec__stl\n"); );
    Vtb_link_loopback__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtb_link_loopback___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_link_loopback___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_link_loopback___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtb_link_loopback___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vtb_link_loopback___024root___stl_sequent__TOP__0(Vtb_link_loopback___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___stl_sequent__TOP__0\n"); );
    Vtb_link_loopback__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_link_loopback__DOT__frame_in_ready 
        = (1U & ((~ (IData)(vlSelfRef.tb_link_loopback__DOT__u_link_tx__DOT__st)) 
                 & (~ (IData)(vlSelfRef.tb_link_loopback__DOT__u_link_rx__DOT__state))));
}

VL_ATTR_COLD void Vtb_link_loopback___024root___eval_stl(Vtb_link_loopback___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___eval_stl\n"); );
    Vtb_link_loopback__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        vlSelfRef.tb_link_loopback__DOT__frame_in_ready 
            = (1U & ((~ (IData)(vlSelfRef.tb_link_loopback__DOT__u_link_tx__DOT__st)) 
                     & (~ (IData)(vlSelfRef.tb_link_loopback__DOT__u_link_rx__DOT__state))));
    }
}

VL_ATTR_COLD bool Vtb_link_loopback___024root___eval_phase__stl(Vtb_link_loopback___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___eval_phase__stl\n"); );
    Vtb_link_loopback__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtb_link_loopback___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_link_loopback___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtb_link_loopback___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtb_link_loopback___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtb_link_loopback___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_link_loopback___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_link_loopback___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_link_loopback.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_link_loopback.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( tb_link_loopback.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 4 is active: @( tb_link_loopback.frame_out_valid)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_link_loopback___024root___ctor_var_reset(Vtb_link_loopback___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_loopback___024root___ctor_var_reset\n"); );
    Vtb_link_loopback__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_link_loopback__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3130968215202141268ull);
    vlSelf->tb_link_loopback__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9575846169575880660ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_loopback__DOT__frame_in, __VscopeHash, 1359988546493854391ull);
    vlSelf->tb_link_loopback__DOT__frame_in_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1087969981657590151ull);
    vlSelf->tb_link_loopback__DOT__frame_in_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14939371429183293511ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_loopback__DOT__frame_out, __VscopeHash, 17287128963458943206ull);
    vlSelf->tb_link_loopback__DOT__frame_out_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6440071720142145738ull);
    vlSelf->tb_link_loopback__DOT__link_up = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13411567191452926616ull);
    vlSelf->tb_link_loopback__DOT__error_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15237766184934529279ull);
    vlSelf->tb_link_loopback__DOT__pmod_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6619930031024633087ull);
    vlSelf->tb_link_loopback__DOT__u_link_tx__DOT__st = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7420796323014413332ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_loopback__DOT__u_link_tx__DOT__shifter, __VscopeHash, 7349506170132219584ull);
    vlSelf->tb_link_loopback__DOT__u_link_tx__DOT__beat = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 11659250319279966063ull);
    vlSelf->tb_link_loopback__DOT__u_link_tx__DOT__half_nibble = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12973482065959972188ull);
    vlSelf->tb_link_loopback__DOT__u_link_rx__DOT__valid_s1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5573967633518085330ull);
    vlSelf->tb_link_loopback__DOT__u_link_rx__DOT__valid_sync = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4092377473025010311ull);
    vlSelf->tb_link_loopback__DOT__u_link_rx__DOT__data_s1 = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 4585125849160338519ull);
    vlSelf->tb_link_loopback__DOT__u_link_rx__DOT__data_sync = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 16039758083601284766ull);
    vlSelf->tb_link_loopback__DOT__u_link_rx__DOT__valid_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3050692416065366748ull);
    vlSelf->tb_link_loopback__DOT__u_link_rx__DOT__state = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 35050357421897575ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_link_loopback__DOT__u_link_rx__DOT__assemble_reg, __VscopeHash, 6664031357185603278ull);
    vlSelf->tb_link_loopback__DOT__u_link_rx__DOT__beat_count = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 12373703332202606942ull);
    vlSelf->tb_link_loopback__DOT__u_link_rx__DOT__phase = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6268814132727275439ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_link_loopback__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_link_loopback__DOT__rst_n__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_link_loopback__DOT__frame_out_valid__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
