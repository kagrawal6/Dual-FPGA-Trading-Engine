// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_latency_histogram.h for the primary calling header

#include "Vtb_latency_histogram__pch.h"

VlCoroutine Vtb_latency_histogram___024root___eval_initial__TOP__Vtiming__0(Vtb_latency_histogram___024root* vlSelf);
VlCoroutine Vtb_latency_histogram___024root___eval_initial__TOP__Vtiming__1(Vtb_latency_histogram___024root* vlSelf);
VlCoroutine Vtb_latency_histogram___024root___eval_initial__TOP__Vtiming__2(Vtb_latency_histogram___024root* vlSelf);

void Vtb_latency_histogram___024root___eval_initial(Vtb_latency_histogram___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___eval_initial\n"); );
    Vtb_latency_histogram__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_latency_histogram__DOT__clk = 0U;
    Vtb_latency_histogram___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_latency_histogram___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_latency_histogram___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

VlCoroutine Vtb_latency_histogram___024root___eval_initial__TOP__Vtiming__0(Vtb_latency_histogram___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_latency_histogram__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0x00000000000186a0ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_b\\tb_latency_histogram.sv", 
                                         33);
    co_return;
}

VlCoroutine Vtb_latency_histogram___024root___eval_initial__TOP__Vtiming__1(Vtb_latency_histogram___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_latency_histogram__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0x00000000000f4240ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_b\\tb_latency_histogram.sv", 
                                         53);
    VL_FINISH_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_b\\tb_latency_histogram.sv", 54, "");
    co_return;
}

VlCoroutine Vtb_latency_histogram___024root___eval_initial__TOP__Vtiming__2(Vtb_latency_histogram___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_latency_histogram__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_b\\tb_latency_histogram.sv", 
                                             28);
        vlSelfRef.tb_latency_histogram__DOT__clk = 
            (1U & (~ (IData)(vlSelfRef.tb_latency_histogram__DOT__clk)));
    }
    co_return;
}

void Vtb_latency_histogram___024root___eval_triggers_vec__act(Vtb_latency_histogram___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___eval_triggers_vec__act\n"); );
    Vtb_latency_histogram__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(vlSelfRef.__VdlySched.awaitingCurrentTime()));
}

bool Vtb_latency_histogram___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___trigger_anySet__act\n"); );
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

void Vtb_latency_histogram___024root___timing_resume(Vtb_latency_histogram___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___timing_resume\n"); );
    Vtb_latency_histogram__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_latency_histogram___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_latency_histogram___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_latency_histogram___024root___eval_phase__act(Vtb_latency_histogram___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___eval_phase__act\n"); );
    Vtb_latency_histogram__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_latency_histogram___024root___eval_triggers_vec__act(vlSelf);
    Vtb_latency_histogram___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_latency_histogram___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_latency_histogram___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_latency_histogram___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_latency_histogram___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_latency_histogram___024root___eval_phase__inact(Vtb_latency_histogram___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___eval_phase__inact\n"); );
    Vtb_latency_histogram__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_b\\tb_latency_histogram.sv", 12, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_latency_histogram___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_latency_histogram___024root___eval_phase__nba(Vtb_latency_histogram___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___eval_phase__nba\n"); );
    Vtb_latency_histogram__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_latency_histogram___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_latency_histogram___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_latency_histogram___024root___eval(Vtb_latency_histogram___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___eval\n"); );
    Vtb_latency_histogram__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_latency_histogram___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_b\\tb_latency_histogram.sv", 12, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_b\\tb_latency_histogram.sv", 12, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_latency_histogram___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_b\\tb_latency_histogram.sv", 12, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_latency_histogram___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_latency_histogram___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_latency_histogram___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vtb_latency_histogram___024root___eval_debug_assertions(Vtb_latency_histogram___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_latency_histogram___024root___eval_debug_assertions\n"); );
    Vtb_latency_histogram__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
