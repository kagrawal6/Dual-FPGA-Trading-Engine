// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_link_rx.h for the primary calling header

#include "Vtb_link_rx__pch.h"

VlCoroutine Vtb_link_rx___024root___eval_initial__TOP__Vtiming__0(Vtb_link_rx___024root* vlSelf);
VlCoroutine Vtb_link_rx___024root___eval_initial__TOP__Vtiming__1(Vtb_link_rx___024root* vlSelf);
VlCoroutine Vtb_link_rx___024root___eval_initial__TOP__Vtiming__2(Vtb_link_rx___024root* vlSelf);

void Vtb_link_rx___024root___eval_initial(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_initial\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_link_rx__DOT__clk = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_link_rx.vcd"s);
    VL_PRINTF_MT("-Info: C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv:130: $dumpvar ignored, as Verilated without --trace\n");
    Vtb_link_rx___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_link_rx___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_link_rx___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

VlCoroutine Vtb_link_rx___024root___eval_initial__TOP__Vtiming__0(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_link_rx__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000186a0ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                         30);
    vlSelfRef.tb_link_rx__DOT__rst_n = 1U;
    co_return;
}

void Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(Vtb_link_rx___024root* vlSelf, const char* __VeventDescription);
void Vtb_link_rx___024root____VbeforeTrig_h6bc084dd__0(Vtb_link_rx___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_link_rx___024root___eval_initial__TOP__Vtiming__1(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__0__cycles;
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__0__cycles = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__0__unnamedblk1__DOT__k;
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__0__unnamedblk1__DOT__k = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__1__cond;
    __Vtask_tb_link_rx__DOT__check__1__cond = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__2__cond;
    __Vtask_tb_link_rx__DOT__check__2__cond = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__3__cond;
    __Vtask_tb_link_rx__DOT__check__3__cond = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_link_rx__DOT__send_frame__4__frame;
    VL_ZERO_W(128, __Vtask_tb_link_rx__DOT__send_frame__4__frame);
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__send_frame__4__beats_to_send;
    __Vtask_tb_link_rx__DOT__send_frame__4__beats_to_send = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__send_frame__4__pad_cycles_after_last_beat;
    __Vtask_tb_link_rx__DOT__send_frame__4__pad_cycles_after_last_beat = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__send_frame__4__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0;
    __Vtask_tb_link_rx__DOT__send_frame__4__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__send_frame__4__i;
    __Vtask_tb_link_rx__DOT__send_frame__4__i = 0;
    CData/*3:0*/ __Vfunc_tb_link_rx__DOT__nibble_at__5__Vfuncout;
    __Vfunc_tb_link_rx__DOT__nibble_at__5__Vfuncout = 0;
    VlWide<4>/*127:0*/ __Vfunc_tb_link_rx__DOT__nibble_at__5__frame;
    VL_ZERO_W(128, __Vfunc_tb_link_rx__DOT__nibble_at__5__frame);
    IData/*31:0*/ __Vfunc_tb_link_rx__DOT__nibble_at__5__i;
    __Vfunc_tb_link_rx__DOT__nibble_at__5__i = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__6__cycles;
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__6__cycles = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__6__unnamedblk1__DOT__k;
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__6__unnamedblk1__DOT__k = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__7__cond;
    __Vtask_tb_link_rx__DOT__check__7__cond = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__8__cond;
    __Vtask_tb_link_rx__DOT__check__8__cond = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__9__cond;
    __Vtask_tb_link_rx__DOT__check__9__cond = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_link_rx__DOT__send_frame__10__frame;
    VL_ZERO_W(128, __Vtask_tb_link_rx__DOT__send_frame__10__frame);
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__send_frame__10__beats_to_send;
    __Vtask_tb_link_rx__DOT__send_frame__10__beats_to_send = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__send_frame__10__pad_cycles_after_last_beat;
    __Vtask_tb_link_rx__DOT__send_frame__10__pad_cycles_after_last_beat = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__send_frame__10__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0;
    __Vtask_tb_link_rx__DOT__send_frame__10__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__send_frame__10__i;
    __Vtask_tb_link_rx__DOT__send_frame__10__i = 0;
    CData/*3:0*/ __Vfunc_tb_link_rx__DOT__nibble_at__11__Vfuncout;
    __Vfunc_tb_link_rx__DOT__nibble_at__11__Vfuncout = 0;
    VlWide<4>/*127:0*/ __Vfunc_tb_link_rx__DOT__nibble_at__11__frame;
    VL_ZERO_W(128, __Vfunc_tb_link_rx__DOT__nibble_at__11__frame);
    IData/*31:0*/ __Vfunc_tb_link_rx__DOT__nibble_at__11__i;
    __Vfunc_tb_link_rx__DOT__nibble_at__11__i = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__12__cond;
    __Vtask_tb_link_rx__DOT__check__12__cond = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__13__cond;
    __Vtask_tb_link_rx__DOT__check__13__cond = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__14__cond;
    __Vtask_tb_link_rx__DOT__check__14__cond = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__15__cond;
    __Vtask_tb_link_rx__DOT__check__15__cond = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_link_rx__DOT__send_frame__16__frame;
    VL_ZERO_W(128, __Vtask_tb_link_rx__DOT__send_frame__16__frame);
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__send_frame__16__beats_to_send;
    __Vtask_tb_link_rx__DOT__send_frame__16__beats_to_send = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__send_frame__16__pad_cycles_after_last_beat;
    __Vtask_tb_link_rx__DOT__send_frame__16__pad_cycles_after_last_beat = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__send_frame__16__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0;
    __Vtask_tb_link_rx__DOT__send_frame__16__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__send_frame__16__i;
    __Vtask_tb_link_rx__DOT__send_frame__16__i = 0;
    CData/*3:0*/ __Vfunc_tb_link_rx__DOT__nibble_at__17__Vfuncout;
    __Vfunc_tb_link_rx__DOT__nibble_at__17__Vfuncout = 0;
    VlWide<4>/*127:0*/ __Vfunc_tb_link_rx__DOT__nibble_at__17__frame;
    VL_ZERO_W(128, __Vfunc_tb_link_rx__DOT__nibble_at__17__frame);
    IData/*31:0*/ __Vfunc_tb_link_rx__DOT__nibble_at__17__i;
    __Vfunc_tb_link_rx__DOT__nibble_at__17__i = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__18__cycles;
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__18__cycles = 0;
    IData/*31:0*/ __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__18__unnamedblk1__DOT__k;
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__18__unnamedblk1__DOT__k = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__19__cond;
    __Vtask_tb_link_rx__DOT__check__19__cond = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__20__cond;
    __Vtask_tb_link_rx__DOT__check__20__cond = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__21__cond;
    __Vtask_tb_link_rx__DOT__check__21__cond = 0;
    CData/*0:0*/ __Vtask_tb_link_rx__DOT__check__22__cond;
    __Vtask_tb_link_rx__DOT__check__22__cond = 0;
    // Body
    vlSelfRef.tb_link_rx__DOT__pmod_data = 0U;
    vlSelfRef.tb_link_rx__DOT__pmod_valid = 0U;
    vlSelfRef.tb_link_rx__DOT__frames_seen = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[0U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[1U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[2U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[3U] = 0U;
    vlSelfRef.tb_link_rx__DOT__err_count_scratch = 0U;
    Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                      "@(posedge tb_link_rx.clk)");
    co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_rx.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                         151);
    while ((1U & (~ (IData)(vlSelfRef.tb_link_rx__DOT__rst_n)))) {
        Vtb_link_rx___024root____VbeforeTrig_h6bc084dd__0(vlSelf, 
                                                          "@( tb_link_rx.rst_n)");
        co_await vlSelfRef.__VtrigSched_h6bc084dd__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_link_rx.rst_n)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                             152);
    }
    Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                      "@(posedge tb_link_rx.clk)");
    co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_rx.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                         153);
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__0__cycles = 0x0000001eU;
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__0__unnamedblk1__DOT__k = 0U;
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__0__unnamedblk1__DOT__k = 0U;
    while (VL_LTS_III(32, __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__0__unnamedblk1__DOT__k, __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__0__cycles)) {
        Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                          "@(posedge tb_link_rx.clk)");
        co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_link_rx.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                             118);
        __Vtask_tb_link_rx__DOT__check__1__cond = (1U 
                                                   & (~ (IData)(vlSelfRef.tb_link_rx__DOT__frame_out_valid)));
        vlSelfRef.__Vtask_tb_link_rx__DOT__check__1__msg 
            = VL_SFORMATF_N_NX("Unexpected frame_out_valid pulse at cycle %0d",0,
                               32,__Vtask_tb_link_rx__DOT__wait_cycles_no_frame__0__unnamedblk1__DOT__k) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__1__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__1__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
            vlSelfRef.tb_link_rx__DOT__err_count_scratch 
                = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
        }
        __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__0__unnamedblk1__DOT__k 
            = ((IData)(1U) + __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__0__unnamedblk1__DOT__k);
    }
    __Vtask_tb_link_rx__DOT__check__2__cond = (0U == vlSelfRef.tb_link_rx__DOT__frames_seen);
    vlSelfRef.__Vtask_tb_link_rx__DOT__check__2__msg = "No frames should be seen in idle period"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__2__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__2__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
        vlSelfRef.tb_link_rx__DOT__err_count_scratch 
            = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
    }
    __Vtask_tb_link_rx__DOT__check__3__cond = (1U & 
                                               (~ (IData)(vlSelfRef.tb_link_rx__DOT__link_up)));
    vlSelfRef.__Vtask_tb_link_rx__DOT__check__3__msg = "link_up should remain 0 before first valid frame"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__3__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__3__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
        vlSelfRef.tb_link_rx__DOT__err_count_scratch 
            = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
    }
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__err0 
        = vlSelfRef.tb_link_rx__DOT__error_count;
    __Vtask_tb_link_rx__DOT__send_frame__4__pad_cycles_after_last_beat = 0U;
    __Vtask_tb_link_rx__DOT__send_frame__4__beats_to_send = 5U;
    __Vtask_tb_link_rx__DOT__send_frame__4__frame[0U] = 0xdef00001U;
    __Vtask_tb_link_rx__DOT__send_frame__4__frame[1U] = 0x56789abcU;
    __Vtask_tb_link_rx__DOT__send_frame__4__frame[2U] = 0xf00d1234U;
    __Vtask_tb_link_rx__DOT__send_frame__4__frame[3U] = 0xdeadbeefU;
    __Vtask_tb_link_rx__DOT__send_frame__4__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    __Vtask_tb_link_rx__DOT__send_frame__4__i = 0U;
    vlSelfRef.tb_link_rx__DOT__pmod_valid = 0U;
    vlSelfRef.tb_link_rx__DOT__pmod_data = 0U;
    Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                      "@(posedge tb_link_rx.clk)");
    co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_rx.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                         91);
    __Vtask_tb_link_rx__DOT__send_frame__4__i = 0U;
    while (VL_LTS_III(32, __Vtask_tb_link_rx__DOT__send_frame__4__i, __Vtask_tb_link_rx__DOT__send_frame__4__beats_to_send)) {
        __Vfunc_tb_link_rx__DOT__nibble_at__5__i = __Vtask_tb_link_rx__DOT__send_frame__4__i;
        __Vfunc_tb_link_rx__DOT__nibble_at__5__frame[0U] 
            = __Vtask_tb_link_rx__DOT__send_frame__4__frame[0U];
        __Vfunc_tb_link_rx__DOT__nibble_at__5__frame[1U] 
            = __Vtask_tb_link_rx__DOT__send_frame__4__frame[1U];
        __Vfunc_tb_link_rx__DOT__nibble_at__5__frame[2U] 
            = __Vtask_tb_link_rx__DOT__send_frame__4__frame[2U];
        __Vfunc_tb_link_rx__DOT__nibble_at__5__frame[3U] 
            = __Vtask_tb_link_rx__DOT__send_frame__4__frame[3U];
        __Vfunc_tb_link_rx__DOT__nibble_at__5__Vfuncout = 0;
        __Vfunc_tb_link_rx__DOT__nibble_at__5__Vfuncout 
            = (0x0000000fU & (((0U == (0x0000001fU 
                                       & (((IData)(0x7fU) 
                                           - VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__5__i, 2U)) 
                                          - (IData)(3U))))
                                ? 0U : (__Vfunc_tb_link_rx__DOT__nibble_at__5__frame
                                        [(((IData)(3U) 
                                           + (0x0000007fU 
                                              & (((IData)(0x7fU) 
                                                  - 
                                                  VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__5__i, 2U)) 
                                                 - (IData)(3U)))) 
                                          >> 5U)] << 
                                        ((IData)(0x00000020U) 
                                         - (0x0000001fU 
                                            & (((IData)(0x7fU) 
                                                - VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__5__i, 2U)) 
                                               - (IData)(3U)))))) 
                              | (__Vfunc_tb_link_rx__DOT__nibble_at__5__frame
                                 [(3U & ((((IData)(0x7fU) 
                                           - VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__5__i, 2U)) 
                                          - (IData)(3U)) 
                                         >> 5U))] >> 
                                 (0x0000001fU & (((IData)(0x7fU) 
                                                  - 
                                                  VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__5__i, 2U)) 
                                                 - (IData)(3U))))));
        vlSelfRef.tb_link_rx__DOT__pmod_data = __Vfunc_tb_link_rx__DOT__nibble_at__5__Vfuncout;
        vlSelfRef.tb_link_rx__DOT__pmod_valid = 1U;
        Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                          "@(posedge tb_link_rx.clk)");
        co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_link_rx.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                             96);
        Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                          "@(posedge tb_link_rx.clk)");
        co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_link_rx.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                             97);
        __Vtask_tb_link_rx__DOT__send_frame__4__i = 
            ((IData)(1U) + __Vtask_tb_link_rx__DOT__send_frame__4__i);
    }
    if (VL_LTS_III(32, 0U, __Vtask_tb_link_rx__DOT__send_frame__4__pad_cycles_after_last_beat)) {
        __Vtask_tb_link_rx__DOT__send_frame__4__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = __Vtask_tb_link_rx__DOT__send_frame__4__pad_cycles_after_last_beat;
        while (VL_LTS_III(32, 0U, __Vtask_tb_link_rx__DOT__send_frame__4__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
            Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                              "@(posedge tb_link_rx.clk)");
            co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_link_rx.clk)", 
                                                                 "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                                 104);
            __Vtask_tb_link_rx__DOT__send_frame__4__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 
                = (__Vtask_tb_link_rx__DOT__send_frame__4__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 
                   - (IData)(1U));
        }
    }
    vlSelfRef.tb_link_rx__DOT__pmod_valid = 0U;
    vlSelfRef.tb_link_rx__DOT__pmod_data = 0U;
    Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                      "@(posedge tb_link_rx.clk)");
    co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_rx.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                         110);
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__6__cycles = 0x00000050U;
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__6__unnamedblk1__DOT__k = 0U;
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__6__unnamedblk1__DOT__k = 0U;
    while (VL_LTS_III(32, __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__6__unnamedblk1__DOT__k, __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__6__cycles)) {
        Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                          "@(posedge tb_link_rx.clk)");
        co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_link_rx.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                             118);
        __Vtask_tb_link_rx__DOT__check__7__cond = (1U 
                                                   & (~ (IData)(vlSelfRef.tb_link_rx__DOT__frame_out_valid)));
        vlSelfRef.__Vtask_tb_link_rx__DOT__check__7__msg 
            = VL_SFORMATF_N_NX("Unexpected frame_out_valid pulse at cycle %0d",0,
                               32,__Vtask_tb_link_rx__DOT__wait_cycles_no_frame__6__unnamedblk1__DOT__k) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__7__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__7__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
            vlSelfRef.tb_link_rx__DOT__err_count_scratch 
                = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
        }
        __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__6__unnamedblk1__DOT__k 
            = ((IData)(1U) + __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__6__unnamedblk1__DOT__k);
    }
    __Vtask_tb_link_rx__DOT__check__8__cond = (0U == vlSelfRef.tb_link_rx__DOT__frames_seen);
    vlSelfRef.__Vtask_tb_link_rx__DOT__check__8__msg = "Truncated frame must not produce frame_out_valid"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__8__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__8__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
        vlSelfRef.tb_link_rx__DOT__err_count_scratch 
            = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
    }
    __Vtask_tb_link_rx__DOT__check__9__cond = (vlSelfRef.tb_link_rx__DOT__error_count 
                                               > vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__err0);
    vlSelfRef.__Vtask_tb_link_rx__DOT__check__9__msg = "error_count should increment after truncation"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__9__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__9__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
        vlSelfRef.tb_link_rx__DOT__err_count_scratch 
            = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
    }
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__err1 
        = vlSelfRef.tb_link_rx__DOT__error_count;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__good_frame[0U] = 0x98765432U;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__good_frame[1U] = 0x00fedcbaU;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__good_frame[2U] = 0x89abcdefU;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__good_frame[3U] = 0x11234567U;
    vlSelfRef.tb_link_rx__DOT__frames_seen = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[0U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[1U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[2U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[3U] = 0U;
    __Vtask_tb_link_rx__DOT__send_frame__10__pad_cycles_after_last_beat = 0x0000000aU;
    __Vtask_tb_link_rx__DOT__send_frame__10__beats_to_send = 0x00000020U;
    __Vtask_tb_link_rx__DOT__send_frame__10__frame[0U] 
        = vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__good_frame[0U];
    __Vtask_tb_link_rx__DOT__send_frame__10__frame[1U] 
        = vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__good_frame[1U];
    __Vtask_tb_link_rx__DOT__send_frame__10__frame[2U] 
        = vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__good_frame[2U];
    __Vtask_tb_link_rx__DOT__send_frame__10__frame[3U] 
        = vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__good_frame[3U];
    __Vtask_tb_link_rx__DOT__send_frame__10__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    __Vtask_tb_link_rx__DOT__send_frame__10__i = 0U;
    vlSelfRef.tb_link_rx__DOT__pmod_valid = 0U;
    vlSelfRef.tb_link_rx__DOT__pmod_data = 0U;
    Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                      "@(posedge tb_link_rx.clk)");
    co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_rx.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                         91);
    __Vtask_tb_link_rx__DOT__send_frame__10__i = 0U;
    while (VL_LTS_III(32, __Vtask_tb_link_rx__DOT__send_frame__10__i, __Vtask_tb_link_rx__DOT__send_frame__10__beats_to_send)) {
        __Vfunc_tb_link_rx__DOT__nibble_at__11__i = __Vtask_tb_link_rx__DOT__send_frame__10__i;
        __Vfunc_tb_link_rx__DOT__nibble_at__11__frame[0U] 
            = __Vtask_tb_link_rx__DOT__send_frame__10__frame[0U];
        __Vfunc_tb_link_rx__DOT__nibble_at__11__frame[1U] 
            = __Vtask_tb_link_rx__DOT__send_frame__10__frame[1U];
        __Vfunc_tb_link_rx__DOT__nibble_at__11__frame[2U] 
            = __Vtask_tb_link_rx__DOT__send_frame__10__frame[2U];
        __Vfunc_tb_link_rx__DOT__nibble_at__11__frame[3U] 
            = __Vtask_tb_link_rx__DOT__send_frame__10__frame[3U];
        __Vfunc_tb_link_rx__DOT__nibble_at__11__Vfuncout = 0;
        __Vfunc_tb_link_rx__DOT__nibble_at__11__Vfuncout 
            = (0x0000000fU & (((0U == (0x0000001fU 
                                       & (((IData)(0x7fU) 
                                           - VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__11__i, 2U)) 
                                          - (IData)(3U))))
                                ? 0U : (__Vfunc_tb_link_rx__DOT__nibble_at__11__frame
                                        [(((IData)(3U) 
                                           + (0x0000007fU 
                                              & (((IData)(0x7fU) 
                                                  - 
                                                  VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__11__i, 2U)) 
                                                 - (IData)(3U)))) 
                                          >> 5U)] << 
                                        ((IData)(0x00000020U) 
                                         - (0x0000001fU 
                                            & (((IData)(0x7fU) 
                                                - VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__11__i, 2U)) 
                                               - (IData)(3U)))))) 
                              | (__Vfunc_tb_link_rx__DOT__nibble_at__11__frame
                                 [(3U & ((((IData)(0x7fU) 
                                           - VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__11__i, 2U)) 
                                          - (IData)(3U)) 
                                         >> 5U))] >> 
                                 (0x0000001fU & (((IData)(0x7fU) 
                                                  - 
                                                  VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__11__i, 2U)) 
                                                 - (IData)(3U))))));
        vlSelfRef.tb_link_rx__DOT__pmod_data = __Vfunc_tb_link_rx__DOT__nibble_at__11__Vfuncout;
        vlSelfRef.tb_link_rx__DOT__pmod_valid = 1U;
        Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                          "@(posedge tb_link_rx.clk)");
        co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_link_rx.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                             96);
        Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                          "@(posedge tb_link_rx.clk)");
        co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_link_rx.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                             97);
        __Vtask_tb_link_rx__DOT__send_frame__10__i 
            = ((IData)(1U) + __Vtask_tb_link_rx__DOT__send_frame__10__i);
    }
    if (VL_LTS_III(32, 0U, __Vtask_tb_link_rx__DOT__send_frame__10__pad_cycles_after_last_beat)) {
        __Vtask_tb_link_rx__DOT__send_frame__10__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = __Vtask_tb_link_rx__DOT__send_frame__10__pad_cycles_after_last_beat;
        while (VL_LTS_III(32, 0U, __Vtask_tb_link_rx__DOT__send_frame__10__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
            Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                              "@(posedge tb_link_rx.clk)");
            co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_link_rx.clk)", 
                                                                 "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                                 104);
            __Vtask_tb_link_rx__DOT__send_frame__10__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 
                = (__Vtask_tb_link_rx__DOT__send_frame__10__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 
                   - (IData)(1U));
        }
    }
    vlSelfRef.tb_link_rx__DOT__pmod_valid = 0U;
    vlSelfRef.tb_link_rx__DOT__pmod_data = 0U;
    Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                      "@(posedge tb_link_rx.clk)");
    co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_rx.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                         110);
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__wait_p = 0U;
    while (((0U == vlSelfRef.tb_link_rx__DOT__frames_seen) 
            & VL_GTS_III(32, 0x00000078U, vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__wait_p))) {
        Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                          "@(posedge tb_link_rx.clk)");
        co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_link_rx.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                             190);
        vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__wait_p 
            = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__wait_p);
    }
    __Vtask_tb_link_rx__DOT__check__12__cond = (1U 
                                                == vlSelfRef.tb_link_rx__DOT__frames_seen);
    vlSelfRef.__Vtask_tb_link_rx__DOT__check__12__msg = "Full valid frame must produce at least one frame_out_valid pulse"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__12__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__12__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
        vlSelfRef.tb_link_rx__DOT__err_count_scratch 
            = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
    }
    __Vtask_tb_link_rx__DOT__check__13__cond = (0U 
                                                == 
                                                ((((vlSelfRef.tb_link_rx__DOT__last_frame[0U] 
                                                    ^ vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__good_frame[0U]) 
                                                   | (vlSelfRef.tb_link_rx__DOT__last_frame[1U] 
                                                      ^ vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__good_frame[1U])) 
                                                  | (vlSelfRef.tb_link_rx__DOT__last_frame[2U] 
                                                     ^ vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__good_frame[2U])) 
                                                 | (vlSelfRef.tb_link_rx__DOT__last_frame[3U] 
                                                    ^ vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__good_frame[3U])));
    vlSelfRef.__Vtask_tb_link_rx__DOT__check__13__msg = "Assembled frame_out must match the transmitted frame"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__13__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__13__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
        vlSelfRef.tb_link_rx__DOT__err_count_scratch 
            = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
    }
    __Vtask_tb_link_rx__DOT__check__14__cond = vlSelfRef.tb_link_rx__DOT__link_up;
    vlSelfRef.__Vtask_tb_link_rx__DOT__check__14__msg = "link_up must assert after first successful frame"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__14__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__14__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
        vlSelfRef.tb_link_rx__DOT__err_count_scratch 
            = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
    }
    __Vtask_tb_link_rx__DOT__check__15__cond = (vlSelfRef.tb_link_rx__DOT__error_count 
                                                == vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__err1);
    vlSelfRef.__Vtask_tb_link_rx__DOT__check__15__msg = "No new errors expected for a valid complete frame"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__15__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__15__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
        vlSelfRef.tb_link_rx__DOT__err_count_scratch 
            = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
    }
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__bad_msg_frame[0U] = 0U;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__bad_msg_frame[1U] = 0U;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__bad_msg_frame[2U] = 0U;
    vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__bad_msg_frame[3U] = 0xf0000000U;
    vlSelfRef.tb_link_rx__DOT__frames_seen = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[0U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[1U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[2U] = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[3U] = 0U;
    __Vtask_tb_link_rx__DOT__send_frame__16__pad_cycles_after_last_beat = 0x0000000aU;
    __Vtask_tb_link_rx__DOT__send_frame__16__beats_to_send = 0x00000020U;
    __Vtask_tb_link_rx__DOT__send_frame__16__frame[0U] 
        = vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__bad_msg_frame[0U];
    __Vtask_tb_link_rx__DOT__send_frame__16__frame[1U] 
        = vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__bad_msg_frame[1U];
    __Vtask_tb_link_rx__DOT__send_frame__16__frame[2U] 
        = vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__bad_msg_frame[2U];
    __Vtask_tb_link_rx__DOT__send_frame__16__frame[3U] 
        = vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__bad_msg_frame[3U];
    __Vtask_tb_link_rx__DOT__send_frame__16__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    __Vtask_tb_link_rx__DOT__send_frame__16__i = 0U;
    vlSelfRef.tb_link_rx__DOT__pmod_valid = 0U;
    vlSelfRef.tb_link_rx__DOT__pmod_data = 0U;
    Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                      "@(posedge tb_link_rx.clk)");
    co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_rx.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                         91);
    __Vtask_tb_link_rx__DOT__send_frame__16__i = 0U;
    while (VL_LTS_III(32, __Vtask_tb_link_rx__DOT__send_frame__16__i, __Vtask_tb_link_rx__DOT__send_frame__16__beats_to_send)) {
        __Vfunc_tb_link_rx__DOT__nibble_at__17__i = __Vtask_tb_link_rx__DOT__send_frame__16__i;
        __Vfunc_tb_link_rx__DOT__nibble_at__17__frame[0U] 
            = __Vtask_tb_link_rx__DOT__send_frame__16__frame[0U];
        __Vfunc_tb_link_rx__DOT__nibble_at__17__frame[1U] 
            = __Vtask_tb_link_rx__DOT__send_frame__16__frame[1U];
        __Vfunc_tb_link_rx__DOT__nibble_at__17__frame[2U] 
            = __Vtask_tb_link_rx__DOT__send_frame__16__frame[2U];
        __Vfunc_tb_link_rx__DOT__nibble_at__17__frame[3U] 
            = __Vtask_tb_link_rx__DOT__send_frame__16__frame[3U];
        __Vfunc_tb_link_rx__DOT__nibble_at__17__Vfuncout = 0;
        __Vfunc_tb_link_rx__DOT__nibble_at__17__Vfuncout 
            = (0x0000000fU & (((0U == (0x0000001fU 
                                       & (((IData)(0x7fU) 
                                           - VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__17__i, 2U)) 
                                          - (IData)(3U))))
                                ? 0U : (__Vfunc_tb_link_rx__DOT__nibble_at__17__frame
                                        [(((IData)(3U) 
                                           + (0x0000007fU 
                                              & (((IData)(0x7fU) 
                                                  - 
                                                  VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__17__i, 2U)) 
                                                 - (IData)(3U)))) 
                                          >> 5U)] << 
                                        ((IData)(0x00000020U) 
                                         - (0x0000001fU 
                                            & (((IData)(0x7fU) 
                                                - VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__17__i, 2U)) 
                                               - (IData)(3U)))))) 
                              | (__Vfunc_tb_link_rx__DOT__nibble_at__17__frame
                                 [(3U & ((((IData)(0x7fU) 
                                           - VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__17__i, 2U)) 
                                          - (IData)(3U)) 
                                         >> 5U))] >> 
                                 (0x0000001fU & (((IData)(0x7fU) 
                                                  - 
                                                  VL_SHIFTL_III(7,32,32, __Vfunc_tb_link_rx__DOT__nibble_at__17__i, 2U)) 
                                                 - (IData)(3U))))));
        vlSelfRef.tb_link_rx__DOT__pmod_data = __Vfunc_tb_link_rx__DOT__nibble_at__17__Vfuncout;
        vlSelfRef.tb_link_rx__DOT__pmod_valid = 1U;
        Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                          "@(posedge tb_link_rx.clk)");
        co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_link_rx.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                             96);
        Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                          "@(posedge tb_link_rx.clk)");
        co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_link_rx.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                             97);
        __Vtask_tb_link_rx__DOT__send_frame__16__i 
            = ((IData)(1U) + __Vtask_tb_link_rx__DOT__send_frame__16__i);
    }
    if (VL_LTS_III(32, 0U, __Vtask_tb_link_rx__DOT__send_frame__16__pad_cycles_after_last_beat)) {
        __Vtask_tb_link_rx__DOT__send_frame__16__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = __Vtask_tb_link_rx__DOT__send_frame__16__pad_cycles_after_last_beat;
        while (VL_LTS_III(32, 0U, __Vtask_tb_link_rx__DOT__send_frame__16__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
            Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                              "@(posedge tb_link_rx.clk)");
            co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_link_rx.clk)", 
                                                                 "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                                 104);
            __Vtask_tb_link_rx__DOT__send_frame__16__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 
                = (__Vtask_tb_link_rx__DOT__send_frame__16__tb_link_rx__DOT__unnamedblk1_1__DOT____Vrepeat0 
                   - (IData)(1U));
        }
    }
    vlSelfRef.tb_link_rx__DOT__pmod_valid = 0U;
    vlSelfRef.tb_link_rx__DOT__pmod_data = 0U;
    Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                      "@(posedge tb_link_rx.clk)");
    co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_link_rx.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                         110);
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__18__cycles = 0x0000005aU;
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__18__unnamedblk1__DOT__k = 0U;
    __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__18__unnamedblk1__DOT__k = 0U;
    while (VL_LTS_III(32, __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__18__unnamedblk1__DOT__k, __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__18__cycles)) {
        Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(vlSelf, 
                                                          "@(posedge tb_link_rx.clk)");
        co_await vlSelfRef.__VtrigSched_ha334240d__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_link_rx.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                                             118);
        __Vtask_tb_link_rx__DOT__check__19__cond = 
            (1U & (~ (IData)(vlSelfRef.tb_link_rx__DOT__frame_out_valid)));
        vlSelfRef.__Vtask_tb_link_rx__DOT__check__19__msg 
            = VL_SFORMATF_N_NX("Unexpected frame_out_valid pulse at cycle %0d",0,
                               32,__Vtask_tb_link_rx__DOT__wait_cycles_no_frame__18__unnamedblk1__DOT__k) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__19__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__19__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
            vlSelfRef.tb_link_rx__DOT__err_count_scratch 
                = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
        }
        __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__18__unnamedblk1__DOT__k 
            = ((IData)(1U) + __Vtask_tb_link_rx__DOT__wait_cycles_no_frame__18__unnamedblk1__DOT__k);
    }
    __Vtask_tb_link_rx__DOT__check__20__cond = (0U 
                                                == vlSelfRef.tb_link_rx__DOT__frames_seen);
    vlSelfRef.__Vtask_tb_link_rx__DOT__check__20__msg = "Invalid msg_type must not output frame_out_valid"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__20__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__20__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
        vlSelfRef.tb_link_rx__DOT__err_count_scratch 
            = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
    }
    __Vtask_tb_link_rx__DOT__check__21__cond = (vlSelfRef.tb_link_rx__DOT__error_count 
                                                > vlSelfRef.tb_link_rx__DOT__unnamedblk2__DOT__err1);
    vlSelfRef.__Vtask_tb_link_rx__DOT__check__21__msg = "error_count should increment on invalid msg_type"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__21__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__21__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
        vlSelfRef.tb_link_rx__DOT__err_count_scratch 
            = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
    }
    __Vtask_tb_link_rx__DOT__check__22__cond = vlSelfRef.tb_link_rx__DOT__link_up;
    vlSelfRef.__Vtask_tb_link_rx__DOT__check__22__msg = "link_up should remain asserted once link is up"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_link_rx__DOT__check__22__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_link_rx.sv:66: Assertion failed in %Ntb_link_rx.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_link_rx__DOT__check__22__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 66, "");
        vlSelfRef.tb_link_rx__DOT__err_count_scratch 
            = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__err_count_scratch);
    }
    if ((0U == vlSelfRef.tb_link_rx__DOT__err_count_scratch)) {
        VL_WRITEF_NX("tb_link_rx: PASS (all tests passed)\n",0);
    } else {
        VL_WRITEF_NX("tb_link_rx: FAIL (%0d errors)\n",0,
                     32,vlSelfRef.tb_link_rx__DOT__err_count_scratch);
    }
    VL_FINISH_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 220, "");
    co_return;
}

VlCoroutine Vtb_link_rx___024root___eval_initial__TOP__Vtiming__2(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 
                                             25);
        vlSelfRef.tb_link_rx__DOT__clk = (1U & (~ (IData)(vlSelfRef.tb_link_rx__DOT__clk)));
    }
    co_return;
}

void Vtb_link_rx___024root___eval_triggers_vec__act(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_triggers_vec__act\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((((IData)(vlSelfRef.tb_link_rx__DOT__rst_n) 
                                                        != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_link_rx__DOT__rst_n__0)) 
                                                       << 3U) 
                                                      | (vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                         << 2U)) 
                                                     | ((((~ (IData)(vlSelfRef.tb_link_rx__DOT__rst_n)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_link_rx__DOT__rst_n__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_link_rx__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_link_rx__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_rx__DOT__clk__0 
        = vlSelfRef.tb_link_rx__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_rx__DOT__rst_n__0 
        = vlSelfRef.tb_link_rx__DOT__rst_n;
}

bool Vtb_link_rx___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___trigger_anySet__act\n"); );
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

void Vtb_link_rx___024root___nba_sequent__TOP__0(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___nba_sequent__TOP__0\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vdly__tb_link_rx__DOT__error_count 
        = vlSelfRef.tb_link_rx__DOT__error_count;
    vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__beat_count 
        = vlSelfRef.tb_link_rx__DOT__dut__DOT__beat_count;
    vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__phase 
        = vlSelfRef.tb_link_rx__DOT__dut__DOT__phase;
}

void Vtb_link_rx___024root___nba_sequent__TOP__1(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___nba_sequent__TOP__1\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vdly__tb_link_rx__DOT__frames_seen;
    __Vdly__tb_link_rx__DOT__frames_seen = 0;
    IData/*31:0*/ __VdlyMask__tb_link_rx__DOT__frames_seen;
    __VdlyMask__tb_link_rx__DOT__frames_seen = 0;
    VlWide<4>/*127:0*/ __Vdly__tb_link_rx__DOT__last_frame;
    VL_ZERO_W(128, __Vdly__tb_link_rx__DOT__last_frame);
    VlWide<4>/*127:0*/ __VdlyMask__tb_link_rx__DOT__last_frame;
    VL_ZERO_W(128, __VdlyMask__tb_link_rx__DOT__last_frame);
    // Body
    if (vlSelfRef.tb_link_rx__DOT__frame_out_valid) {
        __Vdly__tb_link_rx__DOT__frames_seen = ((IData)(1U) 
                                                + vlSelfRef.tb_link_rx__DOT__frames_seen);
        __VdlyMask__tb_link_rx__DOT__frames_seen = 0xffffffffU;
        __Vdly__tb_link_rx__DOT__last_frame[0U] = vlSelfRef.tb_link_rx__DOT__frame_out[0U];
        __Vdly__tb_link_rx__DOT__last_frame[1U] = vlSelfRef.tb_link_rx__DOT__frame_out[1U];
        __Vdly__tb_link_rx__DOT__last_frame[2U] = vlSelfRef.tb_link_rx__DOT__frame_out[2U];
        __Vdly__tb_link_rx__DOT__last_frame[3U] = vlSelfRef.tb_link_rx__DOT__frame_out[3U];
        __VdlyMask__tb_link_rx__DOT__last_frame[0U] = 0xffffffffU;
        __VdlyMask__tb_link_rx__DOT__last_frame[1U] = 0xffffffffU;
        __VdlyMask__tb_link_rx__DOT__last_frame[2U] = 0xffffffffU;
        __VdlyMask__tb_link_rx__DOT__last_frame[3U] = 0xffffffffU;
    }
    vlSelfRef.tb_link_rx__DOT__frames_seen = ((__Vdly__tb_link_rx__DOT__frames_seen 
                                               & __VdlyMask__tb_link_rx__DOT__frames_seen) 
                                              | (vlSelfRef.tb_link_rx__DOT__frames_seen 
                                                 & (~ __VdlyMask__tb_link_rx__DOT__frames_seen)));
    __VdlyMask__tb_link_rx__DOT__frames_seen = 0U;
    vlSelfRef.tb_link_rx__DOT__last_frame[0U] = ((__Vdly__tb_link_rx__DOT__last_frame[0U] 
                                                  & __VdlyMask__tb_link_rx__DOT__last_frame[0U]) 
                                                 | (vlSelfRef.tb_link_rx__DOT__last_frame[0U] 
                                                    & (~ __VdlyMask__tb_link_rx__DOT__last_frame[0U])));
    vlSelfRef.tb_link_rx__DOT__last_frame[1U] = ((__Vdly__tb_link_rx__DOT__last_frame[1U] 
                                                  & __VdlyMask__tb_link_rx__DOT__last_frame[1U]) 
                                                 | (vlSelfRef.tb_link_rx__DOT__last_frame[1U] 
                                                    & (~ __VdlyMask__tb_link_rx__DOT__last_frame[1U])));
    vlSelfRef.tb_link_rx__DOT__last_frame[2U] = ((__Vdly__tb_link_rx__DOT__last_frame[2U] 
                                                  & __VdlyMask__tb_link_rx__DOT__last_frame[2U]) 
                                                 | (vlSelfRef.tb_link_rx__DOT__last_frame[2U] 
                                                    & (~ __VdlyMask__tb_link_rx__DOT__last_frame[2U])));
    vlSelfRef.tb_link_rx__DOT__last_frame[3U] = ((__Vdly__tb_link_rx__DOT__last_frame[3U] 
                                                  & __VdlyMask__tb_link_rx__DOT__last_frame[3U]) 
                                                 | (vlSelfRef.tb_link_rx__DOT__last_frame[3U] 
                                                    & (~ __VdlyMask__tb_link_rx__DOT__last_frame[3U])));
    __VdlyMask__tb_link_rx__DOT__last_frame[0U] = 0U;
    __VdlyMask__tb_link_rx__DOT__last_frame[1U] = 0U;
    __VdlyMask__tb_link_rx__DOT__last_frame[2U] = 0U;
    __VdlyMask__tb_link_rx__DOT__last_frame[3U] = 0U;
}

void Vtb_link_rx___024root___nba_sequent__TOP__2(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___nba_sequent__TOP__2\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.tb_link_rx__DOT__rst_n) {
        vlSelfRef.tb_link_rx__DOT__frame_out_valid = 0U;
        if (vlSelfRef.tb_link_rx__DOT__dut__DOT__state) {
            if ((1U & (~ (IData)(vlSelfRef.tb_link_rx__DOT__dut__DOT__phase)))) {
                if (vlSelfRef.tb_link_rx__DOT__dut__DOT__valid_sync) {
                    vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[0U] 
                        = ((vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[0U] 
                            << 4U) | (IData)(vlSelfRef.tb_link_rx__DOT__dut__DOT__data_sync));
                    vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[1U] 
                        = ((vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[0U] 
                            >> 0x0000001cU) | (vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[1U] 
                                               << 4U));
                    vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[2U] 
                        = ((vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[1U] 
                            >> 0x0000001cU) | (vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[2U] 
                                               << 4U));
                    vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U] 
                        = ((vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[2U] 
                            >> 0x0000001cU) | (vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[3U] 
                                               << 4U));
                    if ((0x1fU == (IData)(vlSelfRef.tb_link_rx__DOT__dut__DOT__beat_count))) {
                        if ((((1U == (vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                      >> 0x0000001cU)) 
                              || (2U == (vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                         >> 0x0000001cU))) 
                             || (3U == (vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                        >> 0x0000001cU)))) {
                            vlSelfRef.tb_link_rx__DOT__frame_out[0U] 
                                = vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[0U];
                            vlSelfRef.tb_link_rx__DOT__frame_out[1U] 
                                = vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[1U];
                            vlSelfRef.tb_link_rx__DOT__frame_out[2U] 
                                = vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[2U];
                            vlSelfRef.tb_link_rx__DOT__frame_out[3U] 
                                = vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U];
                            vlSelfRef.tb_link_rx__DOT__frame_out_valid = 1U;
                            vlSelfRef.tb_link_rx__DOT__link_up = 1U;
                        } else {
                            vlSelfRef.__Vdly__tb_link_rx__DOT__error_count 
                                = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__error_count);
                        }
                        vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[0U] = 0U;
                        vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[1U] = 0U;
                        vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[2U] = 0U;
                        vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[3U] = 0U;
                        vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__beat_count = 0U;
                        vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__phase = 0U;
                        vlSelfRef.tb_link_rx__DOT__dut__DOT__state = 0U;
                        if ((1U & (~ ((3U == (vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                              >> 0x0000001cU)) 
                                      | ((2U == (vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                                 >> 0x0000001cU)) 
                                         | (1U == (vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                                   >> 0x0000001cU))))))) {
                            if (((3U == (vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                         >> 0x0000001cU)) 
                                 | ((2U == (vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                            >> 0x0000001cU)) 
                                    | (1U == (vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                              >> 0x0000001cU))))) {
                                if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                                    VL_WRITEF_NX("[%0t] %%Error: link_rx.sv:128: Assertion failed in %Ntb_link_rx.dut.unnamedblk1: unique case, but multiple matches found for '4'h%x'\n",0,
                                                 64,
                                                 VL_TIME_UNITED_Q(1000),
                                                 -9,
                                                 vlSymsp->name(),
                                                 4,
                                                 (vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U] 
                                                  >> 0x0000001cU));
                                    VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/rtl/link\\link_rx.sv", 128, "");
                                }
                            }
                        }
                    } else {
                        vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__beat_count 
                            = (0x0000001fU & ((IData)(1U) 
                                              + (IData)(vlSelfRef.tb_link_rx__DOT__dut__DOT__beat_count)));
                        vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[0U] 
                            = vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[0U];
                        vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[1U] 
                            = vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[1U];
                        vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[2U] 
                            = vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[2U];
                        vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[3U] 
                            = vlSelfRef.tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next[3U];
                    }
                } else {
                    vlSelfRef.__Vdly__tb_link_rx__DOT__error_count 
                        = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__error_count);
                    vlSelfRef.tb_link_rx__DOT__dut__DOT__state = 0U;
                }
            }
            vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__phase 
                = (1U & (~ (IData)(vlSelfRef.tb_link_rx__DOT__dut__DOT__phase)));
        } else if (((~ (IData)(vlSelfRef.tb_link_rx__DOT__dut__DOT__valid_prev)) 
                    & (IData)(vlSelfRef.tb_link_rx__DOT__dut__DOT__valid_sync))) {
            vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[0U] = 0U;
            vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[1U] = 0U;
            vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[2U] = 0U;
            vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[3U] = 0U;
            vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__beat_count = 0U;
            vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__phase = 0U;
            vlSelfRef.tb_link_rx__DOT__dut__DOT__state = 1U;
        }
    } else {
        vlSelfRef.__Vdly__tb_link_rx__DOT__error_count = 0U;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__state = 0U;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[0U] = 0U;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[1U] = 0U;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[2U] = 0U;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__assemble_reg[3U] = 0U;
        vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__beat_count = 0U;
        vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__phase = 0U;
        vlSelfRef.tb_link_rx__DOT__frame_out[0U] = 0U;
        vlSelfRef.tb_link_rx__DOT__frame_out[1U] = 0U;
        vlSelfRef.tb_link_rx__DOT__frame_out[2U] = 0U;
        vlSelfRef.tb_link_rx__DOT__frame_out[3U] = 0U;
        vlSelfRef.tb_link_rx__DOT__frame_out_valid = 0U;
        vlSelfRef.tb_link_rx__DOT__link_up = 0U;
    }
    if (vlSelfRef.tb_link_rx__DOT__rst_n) {
        vlSelfRef.tb_link_rx__DOT__dut__DOT__data_sync 
            = vlSelfRef.tb_link_rx__DOT__dut__DOT__data_s1;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__data_s1 
            = vlSelfRef.tb_link_rx__DOT__pmod_data;
        vlSelfRef.tb_link_rx__DOT__error_count = vlSelfRef.__Vdly__tb_link_rx__DOT__error_count;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__beat_count 
            = vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__beat_count;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__phase 
            = vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__phase;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__valid_prev 
            = vlSelfRef.tb_link_rx__DOT__dut__DOT__valid_sync;
    } else {
        vlSelfRef.tb_link_rx__DOT__dut__DOT__data_sync = 0U;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__data_s1 = 0U;
        vlSelfRef.tb_link_rx__DOT__error_count = vlSelfRef.__Vdly__tb_link_rx__DOT__error_count;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__beat_count 
            = vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__beat_count;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__phase 
            = vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__phase;
        vlSelfRef.tb_link_rx__DOT__dut__DOT__valid_prev = 0U;
    }
    vlSelfRef.tb_link_rx__DOT__dut__DOT__valid_sync 
        = ((IData)(vlSelfRef.tb_link_rx__DOT__rst_n) 
           && (IData)(vlSelfRef.tb_link_rx__DOT__dut__DOT__valid_s1));
    vlSelfRef.tb_link_rx__DOT__dut__DOT__valid_s1 = 
        ((IData)(vlSelfRef.tb_link_rx__DOT__rst_n) 
         && (IData)(vlSelfRef.tb_link_rx__DOT__pmod_valid));
}

void Vtb_link_rx___024root___eval_nba(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_nba\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__frames_seen;
    __Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__frames_seen = 0;
    IData/*31:0*/ __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__frames_seen;
    __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__frames_seen = 0;
    VlWide<4>/*127:0*/ __Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__last_frame;
    VL_ZERO_W(128, __Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__last_frame);
    VlWide<4>/*127:0*/ __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame;
    VL_ZERO_W(128, __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame);
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.__Vdly__tb_link_rx__DOT__error_count 
            = vlSelfRef.tb_link_rx__DOT__error_count;
        vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__beat_count 
            = vlSelfRef.tb_link_rx__DOT__dut__DOT__beat_count;
        vlSelfRef.__Vdly__tb_link_rx__DOT__dut__DOT__phase 
            = vlSelfRef.tb_link_rx__DOT__dut__DOT__phase;
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        if (vlSelfRef.tb_link_rx__DOT__frame_out_valid) {
            __Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__frames_seen 
                = ((IData)(1U) + vlSelfRef.tb_link_rx__DOT__frames_seen);
            __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__frames_seen = 0xffffffffU;
            __Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__last_frame[0U] 
                = vlSelfRef.tb_link_rx__DOT__frame_out[0U];
            __Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__last_frame[1U] 
                = vlSelfRef.tb_link_rx__DOT__frame_out[1U];
            __Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__last_frame[2U] 
                = vlSelfRef.tb_link_rx__DOT__frame_out[2U];
            __Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__last_frame[3U] 
                = vlSelfRef.tb_link_rx__DOT__frame_out[3U];
            __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[0U] = 0xffffffffU;
            __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[1U] = 0xffffffffU;
            __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[2U] = 0xffffffffU;
            __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[3U] = 0xffffffffU;
        }
        vlSelfRef.tb_link_rx__DOT__frames_seen = ((__Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__frames_seen 
                                                   & __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__frames_seen) 
                                                  | (vlSelfRef.tb_link_rx__DOT__frames_seen 
                                                     & (~ __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__frames_seen)));
        __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__frames_seen = 0U;
        vlSelfRef.tb_link_rx__DOT__last_frame[0U] = 
            ((__Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__last_frame[0U] 
              & __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[0U]) 
             | (vlSelfRef.tb_link_rx__DOT__last_frame[0U] 
                & (~ __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[0U])));
        vlSelfRef.tb_link_rx__DOT__last_frame[1U] = 
            ((__Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__last_frame[1U] 
              & __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[1U]) 
             | (vlSelfRef.tb_link_rx__DOT__last_frame[1U] 
                & (~ __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[1U])));
        vlSelfRef.tb_link_rx__DOT__last_frame[2U] = 
            ((__Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__last_frame[2U] 
              & __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[2U]) 
             | (vlSelfRef.tb_link_rx__DOT__last_frame[2U] 
                & (~ __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[2U])));
        vlSelfRef.tb_link_rx__DOT__last_frame[3U] = 
            ((__Vinline__nba_sequent__TOP__1___Vdly__tb_link_rx__DOT__last_frame[3U] 
              & __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[3U]) 
             | (vlSelfRef.tb_link_rx__DOT__last_frame[3U] 
                & (~ __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[3U])));
        __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[0U] = 0U;
        __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[1U] = 0U;
        __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[2U] = 0U;
        __Vinline__nba_sequent__TOP__1___VdlyMask__tb_link_rx__DOT__last_frame[3U] = 0U;
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_link_rx___024root___nba_sequent__TOP__2(vlSelf);
    }
}

void Vtb_link_rx___024root___timing_ready(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___timing_ready\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_ha334240d__0.ready("@(posedge tb_link_rx.clk)");
    }
    if ((8ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h6bc084dd__0.ready("@( tb_link_rx.rst_n)");
    }
}

void Vtb_link_rx___024root___timing_resume(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___timing_resume\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_ha334240d__0.moveToResumeQueue(
                                                          "@(posedge tb_link_rx.clk)");
    vlSelfRef.__VtrigSched_h6bc084dd__0.moveToResumeQueue(
                                                          "@( tb_link_rx.rst_n)");
    vlSelfRef.__VtrigSched_ha334240d__0.resume("@(posedge tb_link_rx.clk)");
    vlSelfRef.__VtrigSched_h6bc084dd__0.resume("@( tb_link_rx.rst_n)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_link_rx___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vtb_link_rx___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_link_rx___024root___eval_phase__act(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_phase__act\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_link_rx___024root___eval_triggers_vec__act(vlSelf);
    Vtb_link_rx___024root___timing_ready(vlSelf);
    Vtb_link_rx___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_link_rx___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_link_rx___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_link_rx___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_link_rx___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_link_rx___024root___eval_phase__inact(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_phase__inact\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 11, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_link_rx___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_link_rx___024root___eval_phase__nba(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_phase__nba\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_link_rx___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_link_rx___024root___eval_nba(vlSelf);
        Vtb_link_rx___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_link_rx___024root___eval(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_link_rx___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 11, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 11, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_link_rx___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/link\\tb_link_rx.sv", 11, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_link_rx___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_link_rx___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_link_rx___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_link_rx___024root____VbeforeTrig_ha334240d__0(Vtb_link_rx___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root____VbeforeTrig_ha334240d__0\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_link_rx__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_link_rx__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_rx__DOT__clk__0 
        = vlSelfRef.tb_link_rx__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_ha334240d__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_link_rx___024root____VbeforeTrig_h6bc084dd__0(Vtb_link_rx___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root____VbeforeTrig_h6bc084dd__0\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.tb_link_rx__DOT__rst_n) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_link_rx__DOT__rst_n__0)) 
                                  << 3U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_link_rx__DOT__rst_n__0 
        = vlSelfRef.tb_link_rx__DOT__rst_n;
    if ((8ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h6bc084dd__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_link_rx___024root___eval_debug_assertions(Vtb_link_rx___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_link_rx___024root___eval_debug_assertions\n"); );
    Vtb_link_rx__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
