// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_exchange_lite.h for the primary calling header

#include "Vtb_exchange_lite__pch.h"

VlCoroutine Vtb_exchange_lite___024root___eval_initial__TOP__Vtiming__0(Vtb_exchange_lite___024root* vlSelf);
VlCoroutine Vtb_exchange_lite___024root___eval_initial__TOP__Vtiming__1(Vtb_exchange_lite___024root* vlSelf);
VlCoroutine Vtb_exchange_lite___024root___eval_initial__TOP__Vtiming__2(Vtb_exchange_lite___024root* vlSelf);

void Vtb_exchange_lite___024root___eval_initial(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_initial\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_exchange_lite__DOT__clk = 0U;
    vlSymsp->_vm_contextp__->dumpfile("tb_exchange_lite.vcd"s);
    VL_PRINTF_MT("-Info: C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv:120: $dumpvar ignored, as Verilated without --trace\n");
    Vtb_exchange_lite___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_exchange_lite___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vtb_exchange_lite___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

VlCoroutine Vtb_exchange_lite___024root___eval_initial__TOP__Vtiming__0(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_exchange_lite__DOT__rst_n = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000186a0ULL, 
                                         nullptr, "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                         36);
    vlSelfRef.tb_exchange_lite__DOT__rst_n = 1U;
    co_return;
}

void Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(Vtb_exchange_lite___024root* vlSelf, const char* __VeventDescription);
void Vtb_exchange_lite___024root____VbeforeTrig_h059def81__0(Vtb_exchange_lite___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vtb_exchange_lite___024root___eval_initial__TOP__Vtiming__1(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_exchange_lite__DOT__unnamedblk1_1__DOT____Vrepeat0;
    tb_exchange_lite__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_exchange_lite__DOT__send_order__0__frame;
    VL_ZERO_W(128, __Vtask_tb_exchange_lite__DOT__send_order__0__frame);
    VlWide<4>/*127:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout);
    CData/*7:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__1__sym;
    __Vfunc_tb_exchange_lite__DOT__build_order__1__sym = 0;
    CData/*0:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__1__side;
    __Vfunc_tb_exchange_lite__DOT__build_order__1__side = 0;
    IData/*31:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__1__limit_price;
    __Vfunc_tb_exchange_lite__DOT__build_order__1__limit_price = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__1__qty;
    __Vfunc_tb_exchange_lite__DOT__build_order__1__qty = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__1__oid;
    __Vfunc_tb_exchange_lite__DOT__build_order__1__oid = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__1__ts;
    __Vfunc_tb_exchange_lite__DOT__build_order__1__ts = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__2__timeout_cycles;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__2__timeout_cycles = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__2__i;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__2__i = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__3__cond;
    __Vtask_tb_exchange_lite__DOT__check__3__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__4__cond;
    __Vtask_tb_exchange_lite__DOT__check__4__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__5__cond;
    __Vtask_tb_exchange_lite__DOT__check__5__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__6__cond;
    __Vtask_tb_exchange_lite__DOT__check__6__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__7__cond;
    __Vtask_tb_exchange_lite__DOT__check__7__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__8__cond;
    __Vtask_tb_exchange_lite__DOT__check__8__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__9__cond;
    __Vtask_tb_exchange_lite__DOT__check__9__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__10__cond;
    __Vtask_tb_exchange_lite__DOT__check__10__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__11__cond;
    __Vtask_tb_exchange_lite__DOT__check__11__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__12__cond;
    __Vtask_tb_exchange_lite__DOT__check__12__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__13__cond;
    __Vtask_tb_exchange_lite__DOT__check__13__cond = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_exchange_lite__DOT__send_order__14__frame;
    VL_ZERO_W(128, __Vtask_tb_exchange_lite__DOT__send_order__14__frame);
    VlWide<4>/*127:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout);
    CData/*7:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__15__sym;
    __Vfunc_tb_exchange_lite__DOT__build_order__15__sym = 0;
    CData/*0:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__15__side;
    __Vfunc_tb_exchange_lite__DOT__build_order__15__side = 0;
    IData/*31:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__15__limit_price;
    __Vfunc_tb_exchange_lite__DOT__build_order__15__limit_price = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__15__qty;
    __Vfunc_tb_exchange_lite__DOT__build_order__15__qty = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__15__oid;
    __Vfunc_tb_exchange_lite__DOT__build_order__15__oid = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__15__ts;
    __Vfunc_tb_exchange_lite__DOT__build_order__15__ts = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__16__timeout_cycles;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__16__timeout_cycles = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__16__i;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__16__i = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__17__cond;
    __Vtask_tb_exchange_lite__DOT__check__17__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__18__cond;
    __Vtask_tb_exchange_lite__DOT__check__18__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__19__cond;
    __Vtask_tb_exchange_lite__DOT__check__19__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__20__cond;
    __Vtask_tb_exchange_lite__DOT__check__20__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__21__cond;
    __Vtask_tb_exchange_lite__DOT__check__21__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__22__cond;
    __Vtask_tb_exchange_lite__DOT__check__22__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__23__cond;
    __Vtask_tb_exchange_lite__DOT__check__23__cond = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_exchange_lite__DOT__send_order__24__frame;
    VL_ZERO_W(128, __Vtask_tb_exchange_lite__DOT__send_order__24__frame);
    VlWide<4>/*127:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout);
    CData/*7:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__25__sym;
    __Vfunc_tb_exchange_lite__DOT__build_order__25__sym = 0;
    CData/*0:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__25__side;
    __Vfunc_tb_exchange_lite__DOT__build_order__25__side = 0;
    IData/*31:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__25__limit_price;
    __Vfunc_tb_exchange_lite__DOT__build_order__25__limit_price = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__25__qty;
    __Vfunc_tb_exchange_lite__DOT__build_order__25__qty = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__25__oid;
    __Vfunc_tb_exchange_lite__DOT__build_order__25__oid = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__25__ts;
    __Vfunc_tb_exchange_lite__DOT__build_order__25__ts = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__26__timeout_cycles;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__26__timeout_cycles = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__26__i;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__26__i = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__27__cond;
    __Vtask_tb_exchange_lite__DOT__check__27__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__28__cond;
    __Vtask_tb_exchange_lite__DOT__check__28__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__29__cond;
    __Vtask_tb_exchange_lite__DOT__check__29__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__30__cond;
    __Vtask_tb_exchange_lite__DOT__check__30__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__31__cond;
    __Vtask_tb_exchange_lite__DOT__check__31__cond = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_exchange_lite__DOT__send_order__32__frame;
    VL_ZERO_W(128, __Vtask_tb_exchange_lite__DOT__send_order__32__frame);
    VlWide<4>/*127:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout);
    CData/*7:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__33__sym;
    __Vfunc_tb_exchange_lite__DOT__build_order__33__sym = 0;
    CData/*0:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__33__side;
    __Vfunc_tb_exchange_lite__DOT__build_order__33__side = 0;
    IData/*31:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__33__limit_price;
    __Vfunc_tb_exchange_lite__DOT__build_order__33__limit_price = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__33__qty;
    __Vfunc_tb_exchange_lite__DOT__build_order__33__qty = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__33__oid;
    __Vfunc_tb_exchange_lite__DOT__build_order__33__oid = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__33__ts;
    __Vfunc_tb_exchange_lite__DOT__build_order__33__ts = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__34__timeout_cycles;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__34__timeout_cycles = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__34__i;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__34__i = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__35__cond;
    __Vtask_tb_exchange_lite__DOT__check__35__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__36__cond;
    __Vtask_tb_exchange_lite__DOT__check__36__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__37__cond;
    __Vtask_tb_exchange_lite__DOT__check__37__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__38__cond;
    __Vtask_tb_exchange_lite__DOT__check__38__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__39__cond;
    __Vtask_tb_exchange_lite__DOT__check__39__cond = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_exchange_lite__DOT__send_order__40__frame;
    VL_ZERO_W(128, __Vtask_tb_exchange_lite__DOT__send_order__40__frame);
    VlWide<4>/*127:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout);
    CData/*7:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__41__sym;
    __Vfunc_tb_exchange_lite__DOT__build_order__41__sym = 0;
    CData/*0:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__41__side;
    __Vfunc_tb_exchange_lite__DOT__build_order__41__side = 0;
    IData/*31:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__41__limit_price;
    __Vfunc_tb_exchange_lite__DOT__build_order__41__limit_price = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__41__qty;
    __Vfunc_tb_exchange_lite__DOT__build_order__41__qty = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__41__oid;
    __Vfunc_tb_exchange_lite__DOT__build_order__41__oid = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__41__ts;
    __Vfunc_tb_exchange_lite__DOT__build_order__41__ts = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__42__timeout_cycles;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__42__timeout_cycles = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__42__i;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__42__i = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__43__cond;
    __Vtask_tb_exchange_lite__DOT__check__43__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__44__cond;
    __Vtask_tb_exchange_lite__DOT__check__44__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__45__cond;
    __Vtask_tb_exchange_lite__DOT__check__45__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__46__cond;
    __Vtask_tb_exchange_lite__DOT__check__46__cond = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_exchange_lite__DOT__send_order__47__frame;
    VL_ZERO_W(128, __Vtask_tb_exchange_lite__DOT__send_order__47__frame);
    VlWide<4>/*127:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout);
    CData/*7:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__48__sym;
    __Vfunc_tb_exchange_lite__DOT__build_order__48__sym = 0;
    CData/*0:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__48__side;
    __Vfunc_tb_exchange_lite__DOT__build_order__48__side = 0;
    IData/*31:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__48__limit_price;
    __Vfunc_tb_exchange_lite__DOT__build_order__48__limit_price = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__48__qty;
    __Vfunc_tb_exchange_lite__DOT__build_order__48__qty = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__48__oid;
    __Vfunc_tb_exchange_lite__DOT__build_order__48__oid = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__48__ts;
    __Vfunc_tb_exchange_lite__DOT__build_order__48__ts = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__49__timeout_cycles;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__49__timeout_cycles = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__49__i;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__49__i = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__50__cond;
    __Vtask_tb_exchange_lite__DOT__check__50__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__51__cond;
    __Vtask_tb_exchange_lite__DOT__check__51__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__52__cond;
    __Vtask_tb_exchange_lite__DOT__check__52__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__53__cond;
    __Vtask_tb_exchange_lite__DOT__check__53__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__54__cond;
    __Vtask_tb_exchange_lite__DOT__check__54__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__55__cond;
    __Vtask_tb_exchange_lite__DOT__check__55__cond = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_exchange_lite__DOT__send_order__56__frame;
    VL_ZERO_W(128, __Vtask_tb_exchange_lite__DOT__send_order__56__frame);
    VlWide<4>/*127:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout);
    CData/*7:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__57__sym;
    __Vfunc_tb_exchange_lite__DOT__build_order__57__sym = 0;
    CData/*0:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__57__side;
    __Vfunc_tb_exchange_lite__DOT__build_order__57__side = 0;
    IData/*31:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__57__limit_price;
    __Vfunc_tb_exchange_lite__DOT__build_order__57__limit_price = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__57__qty;
    __Vfunc_tb_exchange_lite__DOT__build_order__57__qty = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__57__oid;
    __Vfunc_tb_exchange_lite__DOT__build_order__57__oid = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__57__ts;
    __Vfunc_tb_exchange_lite__DOT__build_order__57__ts = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__cycles;
    __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__cycles = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__unnamedblk1__DOT__i;
    __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__unnamedblk1__DOT__i = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__59__cond;
    __Vtask_tb_exchange_lite__DOT__check__59__cond = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__cycles;
    __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__cycles = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__unnamedblk1__DOT__i;
    __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__unnamedblk1__DOT__i = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__61__cond;
    __Vtask_tb_exchange_lite__DOT__check__61__cond = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_exchange_lite__DOT__send_order__62__frame;
    VL_ZERO_W(128, __Vtask_tb_exchange_lite__DOT__send_order__62__frame);
    VlWide<4>/*127:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout);
    CData/*7:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__63__sym;
    __Vfunc_tb_exchange_lite__DOT__build_order__63__sym = 0;
    CData/*0:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__63__side;
    __Vfunc_tb_exchange_lite__DOT__build_order__63__side = 0;
    IData/*31:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__63__limit_price;
    __Vfunc_tb_exchange_lite__DOT__build_order__63__limit_price = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__63__qty;
    __Vfunc_tb_exchange_lite__DOT__build_order__63__qty = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__63__oid;
    __Vfunc_tb_exchange_lite__DOT__build_order__63__oid = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__63__ts;
    __Vfunc_tb_exchange_lite__DOT__build_order__63__ts = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__64__timeout_cycles;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__64__timeout_cycles = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__64__i;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__64__i = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__65__cond;
    __Vtask_tb_exchange_lite__DOT__check__65__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__66__cond;
    __Vtask_tb_exchange_lite__DOT__check__66__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__67__cond;
    __Vtask_tb_exchange_lite__DOT__check__67__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__68__cond;
    __Vtask_tb_exchange_lite__DOT__check__68__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__69__cond;
    __Vtask_tb_exchange_lite__DOT__check__69__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__70__cond;
    __Vtask_tb_exchange_lite__DOT__check__70__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__71__cond;
    __Vtask_tb_exchange_lite__DOT__check__71__cond = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_exchange_lite__DOT__send_order__72__frame;
    VL_ZERO_W(128, __Vtask_tb_exchange_lite__DOT__send_order__72__frame);
    VlWide<4>/*127:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout);
    CData/*7:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__73__sym;
    __Vfunc_tb_exchange_lite__DOT__build_order__73__sym = 0;
    CData/*0:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__73__side;
    __Vfunc_tb_exchange_lite__DOT__build_order__73__side = 0;
    IData/*31:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__73__limit_price;
    __Vfunc_tb_exchange_lite__DOT__build_order__73__limit_price = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__73__qty;
    __Vfunc_tb_exchange_lite__DOT__build_order__73__qty = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__73__oid;
    __Vfunc_tb_exchange_lite__DOT__build_order__73__oid = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__73__ts;
    __Vfunc_tb_exchange_lite__DOT__build_order__73__ts = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__74__timeout_cycles;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__74__timeout_cycles = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__74__i;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__74__i = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__75__cond;
    __Vtask_tb_exchange_lite__DOT__check__75__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__76__cond;
    __Vtask_tb_exchange_lite__DOT__check__76__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__77__cond;
    __Vtask_tb_exchange_lite__DOT__check__77__cond = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_exchange_lite__DOT__send_order__78__frame;
    VL_ZERO_W(128, __Vtask_tb_exchange_lite__DOT__send_order__78__frame);
    VlWide<4>/*127:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout);
    CData/*7:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__79__sym;
    __Vfunc_tb_exchange_lite__DOT__build_order__79__sym = 0;
    CData/*0:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__79__side;
    __Vfunc_tb_exchange_lite__DOT__build_order__79__side = 0;
    IData/*31:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__79__limit_price;
    __Vfunc_tb_exchange_lite__DOT__build_order__79__limit_price = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__79__qty;
    __Vfunc_tb_exchange_lite__DOT__build_order__79__qty = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__79__oid;
    __Vfunc_tb_exchange_lite__DOT__build_order__79__oid = 0;
    SData/*15:0*/ __Vfunc_tb_exchange_lite__DOT__build_order__79__ts;
    __Vfunc_tb_exchange_lite__DOT__build_order__79__ts = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__80__timeout_cycles;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__80__timeout_cycles = 0;
    IData/*31:0*/ __Vtask_tb_exchange_lite__DOT__wait_for_fill__80__i;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__80__i = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__81__cond;
    __Vtask_tb_exchange_lite__DOT__check__81__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__82__cond;
    __Vtask_tb_exchange_lite__DOT__check__82__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__83__cond;
    __Vtask_tb_exchange_lite__DOT__check__83__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__84__cond;
    __Vtask_tb_exchange_lite__DOT__check__84__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__85__cond;
    __Vtask_tb_exchange_lite__DOT__check__85__cond = 0;
    CData/*0:0*/ __Vtask_tb_exchange_lite__DOT__check__86__cond;
    __Vtask_tb_exchange_lite__DOT__check__86__cond = 0;
    // Body
    vlSelfRef.tb_exchange_lite__DOT__enable = 0U;
    vlSelfRef.tb_exchange_lite__DOT__order_frame[0U] = 0U;
    vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] = 0U;
    vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] = 0U;
    vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] = 0U;
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 0U;
    vlSelfRef.tb_exchange_lite__DOT__fill_ready = 1U;
    vlSelfRef.tb_exchange_lite__DOT__best_bid[0U] = 0x00640000U;
    vlSelfRef.tb_exchange_lite__DOT__best_ask[0U] = 0x00650000U;
    vlSelfRef.tb_exchange_lite__DOT__best_bid[1U] = 0x00640000U;
    vlSelfRef.tb_exchange_lite__DOT__best_ask[1U] = 0x00650000U;
    vlSelfRef.tb_exchange_lite__DOT__best_bid[2U] = 0x00640000U;
    vlSelfRef.tb_exchange_lite__DOT__best_ask[2U] = 0x00650000U;
    vlSelfRef.tb_exchange_lite__DOT__best_bid[3U] = 0x00640000U;
    vlSelfRef.tb_exchange_lite__DOT__best_ask[3U] = 0x00650000U;
    vlSelfRef.tb_exchange_lite__DOT__best_bid[1U] = 0x00320000U;
    vlSelfRef.tb_exchange_lite__DOT__best_ask[1U] = 0x00330000U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         140);
    while ((1U & (~ (IData)(vlSelfRef.tb_exchange_lite__DOT__rst_n)))) {
        Vtb_exchange_lite___024root____VbeforeTrig_h059def81__0(vlSelf, 
                                                                "@( tb_exchange_lite.rst_n)");
        co_await vlSelfRef.__VtrigSched_h059def81__0.trigger(1U, 
                                                             nullptr, 
                                                             "@( tb_exchange_lite.rst_n)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             141);
    }
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         142);
    vlSelfRef.tb_exchange_lite__DOT__enable = 1U;
    __Vfunc_tb_exchange_lite__DOT__build_order__1__ts = 0xaaaaU;
    __Vfunc_tb_exchange_lite__DOT__build_order__1__oid = 1U;
    __Vfunc_tb_exchange_lite__DOT__build_order__1__qty = 0x0032U;
    __Vfunc_tb_exchange_lite__DOT__build_order__1__limit_price = 0x00650000U;
    __Vfunc_tb_exchange_lite__DOT__build_order__1__side = 0U;
    __Vfunc_tb_exchange_lite__DOT__build_order__1__sym = 0U;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout);
    __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout[0U] 
        = (IData)(((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__1__oid) 
                                     << 0x00000010U) 
                                    | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__1__ts)))) 
                   << 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout[1U] 
        = (IData)((((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__1__oid) 
                                      << 0x00000010U) 
                                     | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__1__ts)))) 
                    << 0x00000020U) >> 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout[2U] 
        = (IData)((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__1__limit_price)) 
                    << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__1__qty))));
    __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout[3U] 
        = ((0xfff80000U & __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout[3U]) 
           | (IData)(((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__1__limit_price)) 
                        << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__1__qty))) 
                      >> 0x00000020U)));
    __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout[3U] 
        = ((0x0007ffffU & __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout[3U]) 
           | (0xfff80000U & (0x20000000U | (((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__1__sym) 
                                             << 0x00000014U) 
                                            | ((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__1__side) 
                                               << 0x00000013U)))));
    __Vtask_tb_exchange_lite__DOT__send_order__0__frame[0U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout[0U];
    __Vtask_tb_exchange_lite__DOT__send_order__0__frame[1U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout[1U];
    __Vtask_tb_exchange_lite__DOT__send_order__0__frame[2U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout[2U];
    __Vtask_tb_exchange_lite__DOT__send_order__0__frame[3U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__1__Vfuncout[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[0U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__0__frame[0U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__0__frame[1U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__0__frame[2U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__0__frame[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 1U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         90);
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 0U;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__2__why = "BUY at ask"s;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__2__timeout_cycles = 4U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__2__i = 0U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__2__i = 0U;
    while (((~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)) 
            & VL_LTS_III(32, __Vtask_tb_exchange_lite__DOT__wait_for_fill__2__i, __Vtask_tb_exchange_lite__DOT__wait_for_fill__2__timeout_cycles))) {
        Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                                "@(posedge tb_exchange_lite.clk)");
        co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_exchange_lite.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             100);
        __Vtask_tb_exchange_lite__DOT__wait_for_fill__2__i 
            = ((IData)(1U) + __Vtask_tb_exchange_lite__DOT__wait_for_fill__2__i);
    }
    __Vtask_tb_exchange_lite__DOT__check__3__cond = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__3__msg 
        = VL_SFORMATF_N_NX("%@: fill_valid should assert within %0d cycles",0,
                           -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__2__why),
                           32,__Vtask_tb_exchange_lite__DOT__wait_for_fill__2__timeout_cycles) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__3__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__3__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__4__cond = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__4__msg = "BUY at ask: fill_valid"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__4__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__4__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__5__cond = 
        (3U == (vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                >> 0x0000001cU));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__5__msg = "BUY at ask: msg_type=FILL"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__5__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__5__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__6__cond = 
        (0U == (0x000000ffU & (vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                               >> 0x00000014U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__6__msg = "BUY at ask: symbol echoed"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__6__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__6__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__7__cond = 
        (1U & (~ (vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                  >> 0x00000013U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__7__msg = "BUY at ask: side echoed"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__7__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__7__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__8__cond = 
        (0U == (7U & (vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                      >> 0x00000010U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__8__msg = "BUY at ask: status=FILLED"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__8__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__8__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__9__cond = 
        (0x00650000U == ((vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                          << 0x00000010U) | (vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U] 
                                             >> 0x00000010U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__9__msg = "BUY at ask: fill_price=ask"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__9__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__9__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__10__cond 
        = (0x0032U == (0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U]));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__10__msg = "BUY at ask: fill_qty=order qty"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__10__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__10__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__11__cond 
        = (1U == (vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U] 
                  >> 0x00000010U));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__11__msg = "BUY at ask: order_id echoed"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__11__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__11__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__12__cond 
        = (0xaaaaU == (0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U]));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__12__msg = "BUY at ask: ts_echo echoed"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__12__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__12__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__13__cond 
        = (0U == vlSelfRef.tb_exchange_lite__DOT__fill_frame[0U]);
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__13__msg = "BUY at ask: reserved low bits zero"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__13__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__13__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         160);
    __Vfunc_tb_exchange_lite__DOT__build_order__15__ts = 0xbbbbU;
    __Vfunc_tb_exchange_lite__DOT__build_order__15__oid = 2U;
    __Vfunc_tb_exchange_lite__DOT__build_order__15__qty = 0x0019U;
    __Vfunc_tb_exchange_lite__DOT__build_order__15__limit_price = 0x00630000U;
    __Vfunc_tb_exchange_lite__DOT__build_order__15__side = 0U;
    __Vfunc_tb_exchange_lite__DOT__build_order__15__sym = 0U;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout);
    __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout[0U] 
        = (IData)(((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__15__oid) 
                                     << 0x00000010U) 
                                    | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__15__ts)))) 
                   << 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout[1U] 
        = (IData)((((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__15__oid) 
                                      << 0x00000010U) 
                                     | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__15__ts)))) 
                    << 0x00000020U) >> 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout[2U] 
        = (IData)((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__15__limit_price)) 
                    << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__15__qty))));
    __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout[3U] 
        = ((0xfff80000U & __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout[3U]) 
           | (IData)(((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__15__limit_price)) 
                        << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__15__qty))) 
                      >> 0x00000020U)));
    __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout[3U] 
        = ((0x0007ffffU & __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout[3U]) 
           | (0xfff80000U & (0x20000000U | (((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__15__sym) 
                                             << 0x00000014U) 
                                            | ((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__15__side) 
                                               << 0x00000013U)))));
    __Vtask_tb_exchange_lite__DOT__send_order__14__frame[0U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout[0U];
    __Vtask_tb_exchange_lite__DOT__send_order__14__frame[1U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout[1U];
    __Vtask_tb_exchange_lite__DOT__send_order__14__frame[2U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout[2U];
    __Vtask_tb_exchange_lite__DOT__send_order__14__frame[3U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__15__Vfuncout[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[0U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__14__frame[0U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__14__frame[1U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__14__frame[2U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__14__frame[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 1U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         90);
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 0U;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__16__why = "BUY below ask"s;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__16__timeout_cycles = 4U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__16__i = 0U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__16__i = 0U;
    while (((~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)) 
            & VL_LTS_III(32, __Vtask_tb_exchange_lite__DOT__wait_for_fill__16__i, __Vtask_tb_exchange_lite__DOT__wait_for_fill__16__timeout_cycles))) {
        Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                                "@(posedge tb_exchange_lite.clk)");
        co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_exchange_lite.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             100);
        __Vtask_tb_exchange_lite__DOT__wait_for_fill__16__i 
            = ((IData)(1U) + __Vtask_tb_exchange_lite__DOT__wait_for_fill__16__i);
    }
    __Vtask_tb_exchange_lite__DOT__check__17__cond 
        = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__17__msg 
        = VL_SFORMATF_N_NX("%@: fill_valid should assert within %0d cycles",0,
                           -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__16__why),
                           32,__Vtask_tb_exchange_lite__DOT__wait_for_fill__16__timeout_cycles) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__17__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__17__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__18__cond 
        = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__18__msg = "BUY below ask: fill_valid"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__18__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__18__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__19__cond 
        = (1U == (7U & (vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                        >> 0x00000010U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__19__msg = "BUY below ask: status=REJECTED"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__19__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__19__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__20__cond 
        = (0U == ((vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                   << 0x00000010U) | (vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U] 
                                      >> 0x00000010U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__20__msg = "BUY below ask: fill_price=0"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__20__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__20__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__21__cond 
        = (0U == (0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U]));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__21__msg = "BUY below ask: fill_qty=0"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__21__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__21__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__22__cond 
        = (2U == (vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U] 
                  >> 0x00000010U));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__22__msg = "BUY below ask: order_id echoed"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__22__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__22__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__23__cond 
        = (0xbbbbU == (0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U]));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__23__msg = "BUY below ask: ts_echo echoed"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__23__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__23__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         173);
    __Vfunc_tb_exchange_lite__DOT__build_order__25__ts = 0xccccU;
    __Vfunc_tb_exchange_lite__DOT__build_order__25__oid = 3U;
    __Vfunc_tb_exchange_lite__DOT__build_order__25__qty = 0x001eU;
    __Vfunc_tb_exchange_lite__DOT__build_order__25__limit_price = 0x00640000U;
    __Vfunc_tb_exchange_lite__DOT__build_order__25__side = 1U;
    __Vfunc_tb_exchange_lite__DOT__build_order__25__sym = 0U;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout);
    __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout[0U] 
        = (IData)(((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__25__oid) 
                                     << 0x00000010U) 
                                    | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__25__ts)))) 
                   << 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout[1U] 
        = (IData)((((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__25__oid) 
                                      << 0x00000010U) 
                                     | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__25__ts)))) 
                    << 0x00000020U) >> 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout[2U] 
        = (IData)((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__25__limit_price)) 
                    << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__25__qty))));
    __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout[3U] 
        = ((0xfff80000U & __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout[3U]) 
           | (IData)(((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__25__limit_price)) 
                        << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__25__qty))) 
                      >> 0x00000020U)));
    __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout[3U] 
        = ((0x0007ffffU & __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout[3U]) 
           | (0xfff80000U & (0x20000000U | (((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__25__sym) 
                                             << 0x00000014U) 
                                            | ((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__25__side) 
                                               << 0x00000013U)))));
    __Vtask_tb_exchange_lite__DOT__send_order__24__frame[0U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout[0U];
    __Vtask_tb_exchange_lite__DOT__send_order__24__frame[1U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout[1U];
    __Vtask_tb_exchange_lite__DOT__send_order__24__frame[2U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout[2U];
    __Vtask_tb_exchange_lite__DOT__send_order__24__frame[3U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__25__Vfuncout[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[0U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__24__frame[0U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__24__frame[1U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__24__frame[2U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__24__frame[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 1U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         90);
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 0U;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__26__why = "SELL at bid"s;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__26__timeout_cycles = 4U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__26__i = 0U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__26__i = 0U;
    while (((~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)) 
            & VL_LTS_III(32, __Vtask_tb_exchange_lite__DOT__wait_for_fill__26__i, __Vtask_tb_exchange_lite__DOT__wait_for_fill__26__timeout_cycles))) {
        Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                                "@(posedge tb_exchange_lite.clk)");
        co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_exchange_lite.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             100);
        __Vtask_tb_exchange_lite__DOT__wait_for_fill__26__i 
            = ((IData)(1U) + __Vtask_tb_exchange_lite__DOT__wait_for_fill__26__i);
    }
    __Vtask_tb_exchange_lite__DOT__check__27__cond 
        = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__27__msg 
        = VL_SFORMATF_N_NX("%@: fill_valid should assert within %0d cycles",0,
                           -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__26__why),
                           32,__Vtask_tb_exchange_lite__DOT__wait_for_fill__26__timeout_cycles) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__27__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__27__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__28__cond 
        = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__28__msg = "SELL at bid: fill_valid"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__28__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__28__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__29__cond 
        = (0U == (7U & (vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                        >> 0x00000010U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__29__msg = "SELL at bid: status=FILLED"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__29__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__29__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__30__cond 
        = (0x00640000U == ((vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                            << 0x00000010U) | (vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U] 
                                               >> 0x00000010U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__30__msg = "SELL at bid: fill_price=bid"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__30__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__30__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__31__cond 
        = (0x001eU == (0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U]));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__31__msg = "SELL at bid: fill_qty=order qty"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__31__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__31__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         184);
    __Vfunc_tb_exchange_lite__DOT__build_order__33__ts = 0xddddU;
    __Vfunc_tb_exchange_lite__DOT__build_order__33__oid = 4U;
    __Vfunc_tb_exchange_lite__DOT__build_order__33__qty = 0x001eU;
    __Vfunc_tb_exchange_lite__DOT__build_order__33__limit_price = 0x00660000U;
    __Vfunc_tb_exchange_lite__DOT__build_order__33__side = 1U;
    __Vfunc_tb_exchange_lite__DOT__build_order__33__sym = 0U;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout);
    __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout[0U] 
        = (IData)(((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__33__oid) 
                                     << 0x00000010U) 
                                    | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__33__ts)))) 
                   << 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout[1U] 
        = (IData)((((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__33__oid) 
                                      << 0x00000010U) 
                                     | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__33__ts)))) 
                    << 0x00000020U) >> 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout[2U] 
        = (IData)((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__33__limit_price)) 
                    << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__33__qty))));
    __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout[3U] 
        = ((0xfff80000U & __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout[3U]) 
           | (IData)(((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__33__limit_price)) 
                        << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__33__qty))) 
                      >> 0x00000020U)));
    __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout[3U] 
        = ((0x0007ffffU & __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout[3U]) 
           | (0xfff80000U & (0x20000000U | (((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__33__sym) 
                                             << 0x00000014U) 
                                            | ((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__33__side) 
                                               << 0x00000013U)))));
    __Vtask_tb_exchange_lite__DOT__send_order__32__frame[0U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout[0U];
    __Vtask_tb_exchange_lite__DOT__send_order__32__frame[1U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout[1U];
    __Vtask_tb_exchange_lite__DOT__send_order__32__frame[2U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout[2U];
    __Vtask_tb_exchange_lite__DOT__send_order__32__frame[3U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__33__Vfuncout[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[0U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__32__frame[0U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__32__frame[1U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__32__frame[2U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__32__frame[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 1U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         90);
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 0U;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__34__why = "SELL above bid"s;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__34__timeout_cycles = 4U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__34__i = 0U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__34__i = 0U;
    while (((~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)) 
            & VL_LTS_III(32, __Vtask_tb_exchange_lite__DOT__wait_for_fill__34__i, __Vtask_tb_exchange_lite__DOT__wait_for_fill__34__timeout_cycles))) {
        Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                                "@(posedge tb_exchange_lite.clk)");
        co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_exchange_lite.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             100);
        __Vtask_tb_exchange_lite__DOT__wait_for_fill__34__i 
            = ((IData)(1U) + __Vtask_tb_exchange_lite__DOT__wait_for_fill__34__i);
    }
    __Vtask_tb_exchange_lite__DOT__check__35__cond 
        = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__35__msg 
        = VL_SFORMATF_N_NX("%@: fill_valid should assert within %0d cycles",0,
                           -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__34__why),
                           32,__Vtask_tb_exchange_lite__DOT__wait_for_fill__34__timeout_cycles) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__35__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__35__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__36__cond 
        = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__36__msg = "SELL above bid: fill_valid"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__36__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__36__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__37__cond 
        = (1U == (7U & (vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                        >> 0x00000010U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__37__msg = "SELL above bid: status=REJECTED"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__37__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__37__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__38__cond 
        = (0U == ((vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                   << 0x00000010U) | (vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U] 
                                      >> 0x00000010U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__38__msg = "SELL above bid: fill_price=0"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__38__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__38__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__39__cond 
        = (0U == (0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U]));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__39__msg = "SELL above bid: fill_qty=0"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__39__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__39__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         195);
    __Vfunc_tb_exchange_lite__DOT__build_order__41__ts = 0xeeeeU;
    __Vfunc_tb_exchange_lite__DOT__build_order__41__oid = 5U;
    __Vfunc_tb_exchange_lite__DOT__build_order__41__qty = 0x000aU;
    __Vfunc_tb_exchange_lite__DOT__build_order__41__limit_price = 0x00330000U;
    __Vfunc_tb_exchange_lite__DOT__build_order__41__side = 0U;
    __Vfunc_tb_exchange_lite__DOT__build_order__41__sym = 1U;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout);
    __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout[0U] 
        = (IData)(((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__41__oid) 
                                     << 0x00000010U) 
                                    | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__41__ts)))) 
                   << 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout[1U] 
        = (IData)((((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__41__oid) 
                                      << 0x00000010U) 
                                     | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__41__ts)))) 
                    << 0x00000020U) >> 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout[2U] 
        = (IData)((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__41__limit_price)) 
                    << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__41__qty))));
    __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout[3U] 
        = ((0xfff80000U & __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout[3U]) 
           | (IData)(((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__41__limit_price)) 
                        << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__41__qty))) 
                      >> 0x00000020U)));
    __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout[3U] 
        = ((0x0007ffffU & __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout[3U]) 
           | (0xfff80000U & (0x20000000U | (((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__41__sym) 
                                             << 0x00000014U) 
                                            | ((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__41__side) 
                                               << 0x00000013U)))));
    __Vtask_tb_exchange_lite__DOT__send_order__40__frame[0U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout[0U];
    __Vtask_tb_exchange_lite__DOT__send_order__40__frame[1U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout[1U];
    __Vtask_tb_exchange_lite__DOT__send_order__40__frame[2U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout[2U];
    __Vtask_tb_exchange_lite__DOT__send_order__40__frame[3U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__41__Vfuncout[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[0U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__40__frame[0U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__40__frame[1U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__40__frame[2U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__40__frame[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 1U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         90);
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 0U;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__42__why = "Symbol1 BUY at ask"s;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__42__timeout_cycles = 4U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__42__i = 0U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__42__i = 0U;
    while (((~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)) 
            & VL_LTS_III(32, __Vtask_tb_exchange_lite__DOT__wait_for_fill__42__i, __Vtask_tb_exchange_lite__DOT__wait_for_fill__42__timeout_cycles))) {
        Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                                "@(posedge tb_exchange_lite.clk)");
        co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_exchange_lite.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             100);
        __Vtask_tb_exchange_lite__DOT__wait_for_fill__42__i 
            = ((IData)(1U) + __Vtask_tb_exchange_lite__DOT__wait_for_fill__42__i);
    }
    __Vtask_tb_exchange_lite__DOT__check__43__cond 
        = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__43__msg 
        = VL_SFORMATF_N_NX("%@: fill_valid should assert within %0d cycles",0,
                           -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__42__why),
                           32,__Vtask_tb_exchange_lite__DOT__wait_for_fill__42__timeout_cycles) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__43__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__43__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__44__cond 
        = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__44__msg = "Symbol1 BUY at ask: fill_valid"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__44__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__44__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__45__cond 
        = (1U == (0x000000ffU & (vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                                 >> 0x00000014U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__45__msg = "Symbol1 BUY at ask: symbol echoed"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__45__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__45__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__46__cond 
        = (0x00330000U == ((vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                            << 0x00000010U) | (vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U] 
                                               >> 0x00000010U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__46__msg = "Symbol1 BUY at ask: fill_price uses symbol1 ask"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__46__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__46__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         205);
    vlSelfRef.tb_exchange_lite__DOT__fill_ready = 0U;
    __Vfunc_tb_exchange_lite__DOT__build_order__48__ts = 0x1234U;
    __Vfunc_tb_exchange_lite__DOT__build_order__48__oid = 6U;
    __Vfunc_tb_exchange_lite__DOT__build_order__48__qty = 0x000bU;
    __Vfunc_tb_exchange_lite__DOT__build_order__48__limit_price = 0x00650000U;
    __Vfunc_tb_exchange_lite__DOT__build_order__48__side = 0U;
    __Vfunc_tb_exchange_lite__DOT__build_order__48__sym = 0U;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout);
    __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout[0U] 
        = (IData)(((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__48__oid) 
                                     << 0x00000010U) 
                                    | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__48__ts)))) 
                   << 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout[1U] 
        = (IData)((((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__48__oid) 
                                      << 0x00000010U) 
                                     | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__48__ts)))) 
                    << 0x00000020U) >> 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout[2U] 
        = (IData)((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__48__limit_price)) 
                    << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__48__qty))));
    __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout[3U] 
        = ((0xfff80000U & __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout[3U]) 
           | (IData)(((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__48__limit_price)) 
                        << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__48__qty))) 
                      >> 0x00000020U)));
    __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout[3U] 
        = ((0x0007ffffU & __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout[3U]) 
           | (0xfff80000U & (0x20000000U | (((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__48__sym) 
                                             << 0x00000014U) 
                                            | ((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__48__side) 
                                               << 0x00000013U)))));
    __Vtask_tb_exchange_lite__DOT__send_order__47__frame[0U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout[0U];
    __Vtask_tb_exchange_lite__DOT__send_order__47__frame[1U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout[1U];
    __Vtask_tb_exchange_lite__DOT__send_order__47__frame[2U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout[2U];
    __Vtask_tb_exchange_lite__DOT__send_order__47__frame[3U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__48__Vfuncout[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[0U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__47__frame[0U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__47__frame[1U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__47__frame[2U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__47__frame[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 1U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         90);
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 0U;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__49__why = "fill_ready low"s;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__49__timeout_cycles = 4U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__49__i = 0U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__49__i = 0U;
    while (((~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)) 
            & VL_LTS_III(32, __Vtask_tb_exchange_lite__DOT__wait_for_fill__49__i, __Vtask_tb_exchange_lite__DOT__wait_for_fill__49__timeout_cycles))) {
        Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                                "@(posedge tb_exchange_lite.clk)");
        co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_exchange_lite.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             100);
        __Vtask_tb_exchange_lite__DOT__wait_for_fill__49__i 
            = ((IData)(1U) + __Vtask_tb_exchange_lite__DOT__wait_for_fill__49__i);
    }
    __Vtask_tb_exchange_lite__DOT__check__50__cond 
        = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__50__msg 
        = VL_SFORMATF_N_NX("%@: fill_valid should assert within %0d cycles",0,
                           -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__49__why),
                           32,__Vtask_tb_exchange_lite__DOT__wait_for_fill__49__timeout_cycles) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__50__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__50__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__51__cond 
        = (6U == (vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U] 
                  >> 0x00000010U));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__51__msg = "fill_ready low: held order_id"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__51__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__51__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__52__cond 
        = (0x1234U == (0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U]));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__52__msg = "fill_ready low: held ts_echo"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__52__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__52__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    tb_exchange_lite__DOT__unnamedblk1_1__DOT____Vrepeat0 = 4U;
    while (VL_LTS_III(32, 0U, tb_exchange_lite__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                                "@(posedge tb_exchange_lite.clk)");
        co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_exchange_lite.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             216);
        __Vtask_tb_exchange_lite__DOT__check__53__cond 
            = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
        vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__53__msg = "fill_ready low: fill_valid stays asserted"s;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__53__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__53__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
            vlSelfRef.tb_exchange_lite__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
        }
        __Vtask_tb_exchange_lite__DOT__check__54__cond 
            = (6U == (vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U] 
                      >> 0x00000010U));
        vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__54__msg = "fill_ready low: frame stable"s;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__54__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__54__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
            vlSelfRef.tb_exchange_lite__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
        }
        tb_exchange_lite__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (tb_exchange_lite__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.tb_exchange_lite__DOT__fill_ready = 1U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         221);
    __Vtask_tb_exchange_lite__DOT__check__55__cond 
        = (1U & (~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__55__msg = "held fill consumed when ready returns"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__55__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__55__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         223);
    vlSelfRef.tb_exchange_lite__DOT__enable = 0U;
    __Vfunc_tb_exchange_lite__DOT__build_order__57__ts = 0x5678U;
    __Vfunc_tb_exchange_lite__DOT__build_order__57__oid = 7U;
    __Vfunc_tb_exchange_lite__DOT__build_order__57__qty = 0x000cU;
    __Vfunc_tb_exchange_lite__DOT__build_order__57__limit_price = 0x00650000U;
    __Vfunc_tb_exchange_lite__DOT__build_order__57__side = 0U;
    __Vfunc_tb_exchange_lite__DOT__build_order__57__sym = 0U;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout);
    __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout[0U] 
        = (IData)(((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__57__oid) 
                                     << 0x00000010U) 
                                    | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__57__ts)))) 
                   << 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout[1U] 
        = (IData)((((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__57__oid) 
                                      << 0x00000010U) 
                                     | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__57__ts)))) 
                    << 0x00000020U) >> 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout[2U] 
        = (IData)((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__57__limit_price)) 
                    << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__57__qty))));
    __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout[3U] 
        = ((0xfff80000U & __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout[3U]) 
           | (IData)(((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__57__limit_price)) 
                        << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__57__qty))) 
                      >> 0x00000020U)));
    __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout[3U] 
        = ((0x0007ffffU & __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout[3U]) 
           | (0xfff80000U & (0x20000000U | (((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__57__sym) 
                                             << 0x00000014U) 
                                            | ((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__57__side) 
                                               << 0x00000013U)))));
    __Vtask_tb_exchange_lite__DOT__send_order__56__frame[0U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout[0U];
    __Vtask_tb_exchange_lite__DOT__send_order__56__frame[1U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout[1U];
    __Vtask_tb_exchange_lite__DOT__send_order__56__frame[2U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout[2U];
    __Vtask_tb_exchange_lite__DOT__send_order__56__frame[3U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__57__Vfuncout[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[0U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__56__frame[0U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__56__frame[1U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__56__frame[2U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__56__frame[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 1U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         90);
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 0U;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__why = "enable low"s;
    __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__cycles = 4U;
    __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__unnamedblk1__DOT__i = 0U;
    __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__unnamedblk1__DOT__i = 0U;
    while (VL_LTS_III(32, __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__unnamedblk1__DOT__i, __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__cycles)) {
        Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                                "@(posedge tb_exchange_lite.clk)");
        co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_exchange_lite.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             111);
        __Vtask_tb_exchange_lite__DOT__check__59__cond 
            = (1U & (~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)));
        vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__59__msg 
            = VL_SFORMATF_N_NX("%@ (cycle %0d): no fill_valid expected",0,
                               -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__why),
                               32,__Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__unnamedblk1__DOT__i) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__59__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__59__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
            vlSelfRef.tb_exchange_lite__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
        }
        __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__unnamedblk1__DOT__i 
            = ((IData)(1U) + __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__unnamedblk1__DOT__i);
    }
    vlSelfRef.tb_exchange_lite__DOT__enable = 1U;
    vlSelfRef.tb_exchange_lite__DOT__order_frame[0U] = 0U;
    vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] = 0U;
    vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] = 0U;
    vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] = 0xf0000000U;
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 1U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         238);
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 0U;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__why = "invalid msg_type"s;
    __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__cycles = 3U;
    __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__unnamedblk1__DOT__i = 0U;
    __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__unnamedblk1__DOT__i = 0U;
    while (VL_LTS_III(32, __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__unnamedblk1__DOT__i, __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__cycles)) {
        Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                                "@(posedge tb_exchange_lite.clk)");
        co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_exchange_lite.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             111);
        __Vtask_tb_exchange_lite__DOT__check__61__cond 
            = (1U & (~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)));
        vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__61__msg 
            = VL_SFORMATF_N_NX("%@ (cycle %0d): no fill_valid expected",0,
                               -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__why),
                               32,__Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__unnamedblk1__DOT__i) ;
        if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__61__cond)))))) {
            VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                         64,VL_TIME_UNITED_Q(1000),
                         -9,vlSymsp->name(),-1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__61__msg));
            VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
            vlSelfRef.tb_exchange_lite__DOT__err_count 
                = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
        }
        __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__unnamedblk1__DOT__i 
            = ((IData)(1U) + __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__unnamedblk1__DOT__i);
    }
    __Vfunc_tb_exchange_lite__DOT__build_order__63__ts = 0x9abcU;
    __Vfunc_tb_exchange_lite__DOT__build_order__63__oid = 8U;
    __Vfunc_tb_exchange_lite__DOT__build_order__63__qty = 7U;
    __Vfunc_tb_exchange_lite__DOT__build_order__63__limit_price = 0x00650000U;
    __Vfunc_tb_exchange_lite__DOT__build_order__63__side = 0U;
    __Vfunc_tb_exchange_lite__DOT__build_order__63__sym = 0x63U;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout);
    __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout[0U] 
        = (IData)(((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__63__oid) 
                                     << 0x00000010U) 
                                    | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__63__ts)))) 
                   << 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout[1U] 
        = (IData)((((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__63__oid) 
                                      << 0x00000010U) 
                                     | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__63__ts)))) 
                    << 0x00000020U) >> 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout[2U] 
        = (IData)((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__63__limit_price)) 
                    << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__63__qty))));
    __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout[3U] 
        = ((0xfff80000U & __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout[3U]) 
           | (IData)(((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__63__limit_price)) 
                        << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__63__qty))) 
                      >> 0x00000020U)));
    __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout[3U] 
        = ((0x0007ffffU & __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout[3U]) 
           | (0xfff80000U & (0x20000000U | (((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__63__sym) 
                                             << 0x00000014U) 
                                            | ((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__63__side) 
                                               << 0x00000013U)))));
    __Vtask_tb_exchange_lite__DOT__send_order__62__frame[0U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout[0U];
    __Vtask_tb_exchange_lite__DOT__send_order__62__frame[1U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout[1U];
    __Vtask_tb_exchange_lite__DOT__send_order__62__frame[2U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout[2U];
    __Vtask_tb_exchange_lite__DOT__send_order__62__frame[3U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__63__Vfuncout[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[0U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__62__frame[0U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__62__frame[1U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__62__frame[2U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__62__frame[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 1U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         90);
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 0U;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__64__why = "out-of-range symbol"s;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__64__timeout_cycles = 4U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__64__i = 0U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__64__i = 0U;
    while (((~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)) 
            & VL_LTS_III(32, __Vtask_tb_exchange_lite__DOT__wait_for_fill__64__i, __Vtask_tb_exchange_lite__DOT__wait_for_fill__64__timeout_cycles))) {
        Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                                "@(posedge tb_exchange_lite.clk)");
        co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_exchange_lite.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             100);
        __Vtask_tb_exchange_lite__DOT__wait_for_fill__64__i 
            = ((IData)(1U) + __Vtask_tb_exchange_lite__DOT__wait_for_fill__64__i);
    }
    __Vtask_tb_exchange_lite__DOT__check__65__cond 
        = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__65__msg 
        = VL_SFORMATF_N_NX("%@: fill_valid should assert within %0d cycles",0,
                           -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__64__why),
                           32,__Vtask_tb_exchange_lite__DOT__wait_for_fill__64__timeout_cycles) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__65__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__65__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__66__cond 
        = (0x63U == (0x000000ffU & (vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                                    >> 0x00000014U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__66__msg = "out-of-range: symbol echoed"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__66__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__66__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__67__cond 
        = (1U == (7U & (vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                        >> 0x00000010U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__67__msg = "out-of-range: status=REJECTED"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__67__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__67__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__68__cond 
        = (0U == ((vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                   << 0x00000010U) | (vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U] 
                                      >> 0x00000010U)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__68__msg = "out-of-range: fill_price=0"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__68__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__68__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__69__cond 
        = (0U == (0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U]));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__69__msg = "out-of-range: fill_qty=0"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__69__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__69__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__70__cond 
        = (8U == (vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U] 
                  >> 0x00000010U));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__70__msg = "out-of-range: order_id echoed"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__70__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__70__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__71__cond 
        = (0x9abcU == (0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U]));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__71__msg = "out-of-range: ts_echo echoed"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__71__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__71__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         253);
    __Vfunc_tb_exchange_lite__DOT__build_order__73__ts = 0x1111U;
    __Vfunc_tb_exchange_lite__DOT__build_order__73__oid = 9U;
    __Vfunc_tb_exchange_lite__DOT__build_order__73__qty = 0x0015U;
    __Vfunc_tb_exchange_lite__DOT__build_order__73__limit_price = 0x00650000U;
    __Vfunc_tb_exchange_lite__DOT__build_order__73__side = 0U;
    __Vfunc_tb_exchange_lite__DOT__build_order__73__sym = 0U;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout);
    __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout[0U] 
        = (IData)(((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__73__oid) 
                                     << 0x00000010U) 
                                    | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__73__ts)))) 
                   << 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout[1U] 
        = (IData)((((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__73__oid) 
                                      << 0x00000010U) 
                                     | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__73__ts)))) 
                    << 0x00000020U) >> 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout[2U] 
        = (IData)((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__73__limit_price)) 
                    << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__73__qty))));
    __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout[3U] 
        = ((0xfff80000U & __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout[3U]) 
           | (IData)(((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__73__limit_price)) 
                        << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__73__qty))) 
                      >> 0x00000020U)));
    __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout[3U] 
        = ((0x0007ffffU & __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout[3U]) 
           | (0xfff80000U & (0x20000000U | (((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__73__sym) 
                                             << 0x00000014U) 
                                            | ((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__73__side) 
                                               << 0x00000013U)))));
    __Vtask_tb_exchange_lite__DOT__send_order__72__frame[0U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout[0U];
    __Vtask_tb_exchange_lite__DOT__send_order__72__frame[1U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout[1U];
    __Vtask_tb_exchange_lite__DOT__send_order__72__frame[2U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout[2U];
    __Vtask_tb_exchange_lite__DOT__send_order__72__frame[3U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__73__Vfuncout[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[0U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__72__frame[0U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__72__frame[1U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__72__frame[2U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__72__frame[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 1U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         90);
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 0U;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__74__why = "bubble prefill"s;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__74__timeout_cycles = 4U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__74__i = 0U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__74__i = 0U;
    while (((~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)) 
            & VL_LTS_III(32, __Vtask_tb_exchange_lite__DOT__wait_for_fill__74__i, __Vtask_tb_exchange_lite__DOT__wait_for_fill__74__timeout_cycles))) {
        Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                                "@(posedge tb_exchange_lite.clk)");
        co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_exchange_lite.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             100);
        __Vtask_tb_exchange_lite__DOT__wait_for_fill__74__i 
            = ((IData)(1U) + __Vtask_tb_exchange_lite__DOT__wait_for_fill__74__i);
    }
    __Vtask_tb_exchange_lite__DOT__check__75__cond 
        = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__75__msg 
        = VL_SFORMATF_N_NX("%@: fill_valid should assert within %0d cycles",0,
                           -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__74__why),
                           32,__Vtask_tb_exchange_lite__DOT__wait_for_fill__74__timeout_cycles) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__75__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__75__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__76__cond 
        = (9U == (vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U] 
                  >> 0x00000010U));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__76__msg = "bubble prefill: order_id=9"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__76__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__76__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         263);
    __Vtask_tb_exchange_lite__DOT__check__77__cond 
        = (1U & (~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__77__msg = "bubble: no same-cycle replacement after consume"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__77__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__77__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vfunc_tb_exchange_lite__DOT__build_order__79__ts = 0x2222U;
    __Vfunc_tb_exchange_lite__DOT__build_order__79__oid = 0x000aU;
    __Vfunc_tb_exchange_lite__DOT__build_order__79__qty = 0x0016U;
    __Vfunc_tb_exchange_lite__DOT__build_order__79__limit_price = 0x00650000U;
    __Vfunc_tb_exchange_lite__DOT__build_order__79__side = 0U;
    __Vfunc_tb_exchange_lite__DOT__build_order__79__sym = 0U;
    VL_ZERO_W(128, __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout);
    __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout[0U] 
        = (IData)(((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__79__oid) 
                                     << 0x00000010U) 
                                    | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__79__ts)))) 
                   << 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout[1U] 
        = (IData)((((QData)((IData)((((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__79__oid) 
                                      << 0x00000010U) 
                                     | (IData)(__Vfunc_tb_exchange_lite__DOT__build_order__79__ts)))) 
                    << 0x00000020U) >> 0x00000020U));
    __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout[2U] 
        = (IData)((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__79__limit_price)) 
                    << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__79__qty))));
    __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout[3U] 
        = ((0xfff80000U & __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout[3U]) 
           | (IData)(((((QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__79__limit_price)) 
                        << 0x00000010U) | (QData)((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__79__qty))) 
                      >> 0x00000020U)));
    __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout[3U] 
        = ((0x0007ffffU & __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout[3U]) 
           | (0xfff80000U & (0x20000000U | (((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__79__sym) 
                                             << 0x00000014U) 
                                            | ((IData)(__Vfunc_tb_exchange_lite__DOT__build_order__79__side) 
                                               << 0x00000013U)))));
    __Vtask_tb_exchange_lite__DOT__send_order__78__frame[0U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout[0U];
    __Vtask_tb_exchange_lite__DOT__send_order__78__frame[1U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout[1U];
    __Vtask_tb_exchange_lite__DOT__send_order__78__frame[2U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout[2U];
    __Vtask_tb_exchange_lite__DOT__send_order__78__frame[3U] 
        = __Vfunc_tb_exchange_lite__DOT__build_order__79__Vfuncout[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[0U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__78__frame[0U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__78__frame[1U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__78__frame[2U];
    vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
        = __Vtask_tb_exchange_lite__DOT__send_order__78__frame[3U];
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 1U;
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         90);
    vlSelfRef.tb_exchange_lite__DOT__order_valid = 0U;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__80__why = "bubble second response"s;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__80__timeout_cycles = 4U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__80__i = 0U;
    __Vtask_tb_exchange_lite__DOT__wait_for_fill__80__i = 0U;
    while (((~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)) 
            & VL_LTS_III(32, __Vtask_tb_exchange_lite__DOT__wait_for_fill__80__i, __Vtask_tb_exchange_lite__DOT__wait_for_fill__80__timeout_cycles))) {
        Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                                "@(posedge tb_exchange_lite.clk)");
        co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_exchange_lite.clk)", 
                                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                             100);
        __Vtask_tb_exchange_lite__DOT__wait_for_fill__80__i 
            = ((IData)(1U) + __Vtask_tb_exchange_lite__DOT__wait_for_fill__80__i);
    }
    __Vtask_tb_exchange_lite__DOT__check__81__cond 
        = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__81__msg 
        = VL_SFORMATF_N_NX("%@: fill_valid should assert within %0d cycles",0,
                           -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__wait_for_fill__80__why),
                           32,__Vtask_tb_exchange_lite__DOT__wait_for_fill__80__timeout_cycles) ;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__81__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__81__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__82__cond 
        = (0x000aU == (vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U] 
                       >> 0x00000010U));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__82__msg = "bubble second response: order_id=10"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__82__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__82__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__83__cond 
        = (0x2222U == (0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U]));
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__83__msg = "bubble second response: ts_echo"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__83__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__83__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(vlSelf, 
                                                            "@(posedge tb_exchange_lite.clk)");
    co_await vlSelfRef.__VtrigSched_h89ac9348__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_exchange_lite.clk)", 
                                                         "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                                         270);
    __Vtask_tb_exchange_lite__DOT__check__84__cond 
        = (9U == vlSelfRef.tb_exchange_lite__DOT__orders_rcvd);
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__84__msg = "orders_rcvd count"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__84__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__84__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__85__cond 
        = (6U == vlSelfRef.tb_exchange_lite__DOT__fills_sent);
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__85__msg = "fills_sent count"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__85__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__85__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    __Vtask_tb_exchange_lite__DOT__check__86__cond 
        = (3U == vlSelfRef.tb_exchange_lite__DOT__rejects_sent);
    vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__86__msg = "rejects_sent count"s;
    if (VL_UNLIKELY(((1U & (~ (IData)(__Vtask_tb_exchange_lite__DOT__check__86__cond)))))) {
        VL_WRITEF_NX("[%0t] %%Error: tb_exchange_lite.sv:63: Assertion failed in %Ntb_exchange_lite.check: FAIL: %@\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name(),
                     -1,&(vlSelfRef.__Vtask_tb_exchange_lite__DOT__check__86__msg));
        VL_STOP_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 63, "");
        vlSelfRef.tb_exchange_lite__DOT__err_count 
            = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    if ((0U == vlSelfRef.tb_exchange_lite__DOT__err_count)) {
        VL_WRITEF_NX("tb_exchange_lite: PASS (all checks passed, VCD: tb_exchange_lite.vcd)\n",0);
    } else {
        VL_WRITEF_NX("tb_exchange_lite: FAIL (%0d errors)\n",0,
                     32,vlSelfRef.tb_exchange_lite__DOT__err_count);
    }
    VL_FINISH_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 286, "");
    co_return;
}

VlCoroutine Vtb_exchange_lite___024root___eval_initial__TOP__Vtiming__2(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 
                                             31);
        vlSelfRef.tb_exchange_lite__DOT__clk = (1U 
                                                & (~ (IData)(vlSelfRef.tb_exchange_lite__DOT__clk)));
    }
    co_return;
}

void Vtb_exchange_lite___024root___eval_triggers_vec__act(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_triggers_vec__act\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((((IData)(vlSelfRef.tb_exchange_lite__DOT__rst_n) 
                                                        != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__rst_n__0)) 
                                                       << 3U) 
                                                      | (vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                         << 2U)) 
                                                     | ((((~ (IData)(vlSelfRef.tb_exchange_lite__DOT__rst_n)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__rst_n__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_exchange_lite__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__clk__0 
        = vlSelfRef.tb_exchange_lite__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__rst_n__0 
        = vlSelfRef.tb_exchange_lite__DOT__rst_n;
}

bool Vtb_exchange_lite___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___trigger_anySet__act\n"); );
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

void Vtb_exchange_lite___024root___nba_sequent__TOP__0(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___nba_sequent__TOP__0\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __Vdly__tb_exchange_lite__DOT__fill_valid;
    __Vdly__tb_exchange_lite__DOT__fill_valid = 0;
    CData/*0:0*/ __Vdly__tb_exchange_lite__DOT__dut__DOT__p1_valid;
    __Vdly__tb_exchange_lite__DOT__dut__DOT__p1_valid = 0;
    // Body
    __Vdly__tb_exchange_lite__DOT__fill_valid = vlSelfRef.tb_exchange_lite__DOT__fill_valid;
    __Vdly__tb_exchange_lite__DOT__dut__DOT__p1_valid 
        = vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_valid;
    if (vlSelfRef.tb_exchange_lite__DOT__rst_n) {
        if (((IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid) 
             & (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_ready))) {
            __Vdly__tb_exchange_lite__DOT__fill_valid = 0U;
        }
        if ((((IData)(vlSelfRef.tb_exchange_lite__DOT__enable) 
              & (IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_valid)) 
             & (~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid)))) {
            if (vlSelfRef.tb_exchange_lite__DOT__dut__DOT__is_filled) {
                vlSelfRef.tb_exchange_lite__DOT__fills_sent 
                    = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__fills_sent);
            } else {
                vlSelfRef.tb_exchange_lite__DOT__rejects_sent 
                    = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__rejects_sent);
            }
            vlSelfRef.tb_exchange_lite__DOT__fill_frame[0U] 
                = (IData)(((QData)((IData)((((IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_order_id) 
                                             << 0x00000010U) 
                                            | (IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_timestamp)))) 
                           << 0x00000020U));
            vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U] 
                = (IData)((((QData)((IData)((((IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_order_id) 
                                              << 0x00000010U) 
                                             | (IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_timestamp)))) 
                            << 0x00000020U) >> 0x00000020U));
            vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U] 
                = ((0xffff0000U & vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U]) 
                   | (IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__fill_qty_val));
            vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U] 
                = ((0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U]) 
                   | (vlSelfRef.tb_exchange_lite__DOT__dut__DOT__fill_price_val 
                      << 0x00000010U));
            vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                = ((0xffff0000U & vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U]) 
                   | (vlSelfRef.tb_exchange_lite__DOT__dut__DOT__fill_price_val 
                      >> 0x00000010U));
            vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] 
                = ((0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U]) 
                   | (0xffff0000U & (0x30000000U | 
                                     (((IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_symbol) 
                                       << 0x00000014U) 
                                      | (((IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_side) 
                                          << 0x00000013U) 
                                         | (((IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__is_filled)
                                              ? 0U : 1U) 
                                            << 0x00000010U))))));
            __Vdly__tb_exchange_lite__DOT__fill_valid = 1U;
            __Vdly__tb_exchange_lite__DOT__dut__DOT__p1_valid = 0U;
        }
        if ((((((IData)(vlSelfRef.tb_exchange_lite__DOT__enable) 
                & (~ (IData)(vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_valid))) 
               & (~ (IData)(vlSelfRef.tb_exchange_lite__DOT__fill_valid))) 
              & (IData)(vlSelfRef.tb_exchange_lite__DOT__order_valid)) 
             & (2U == (vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
                       >> 0x0000001cU)))) {
            vlSelfRef.tb_exchange_lite__DOT__orders_rcvd 
                = ((IData)(1U) + vlSelfRef.tb_exchange_lite__DOT__orders_rcvd);
            vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_symbol 
                = (0x000000ffU & (vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
                                  >> 0x00000014U));
            vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_side 
                = (1U & (vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
                         >> 0x00000013U));
            vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_limit_price 
                = ((vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
                    << 0x00000010U) | (vlSelfRef.tb_exchange_lite__DOT__order_frame[2U] 
                                       >> 0x00000010U));
            vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_qty 
                = (0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__order_frame[2U]);
            vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_order_id 
                = (vlSelfRef.tb_exchange_lite__DOT__order_frame[1U] 
                   >> 0x00000010U);
            vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_timestamp 
                = (0x0000ffffU & vlSelfRef.tb_exchange_lite__DOT__order_frame[1U]);
            if ((4U > (0x000000ffU & (vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
                                      >> 0x00000014U)))) {
                vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_sym_in_range = 1U;
                vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_bid 
                    = vlSelfRef.tb_exchange_lite__DOT__best_bid
                    [(3U & (vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
                            >> 0x00000014U))];
                vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_ask 
                    = vlSelfRef.tb_exchange_lite__DOT__best_ask
                    [(3U & (vlSelfRef.tb_exchange_lite__DOT__order_frame[3U] 
                            >> 0x00000014U))];
            } else {
                vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_sym_in_range = 0U;
                vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_bid = 0U;
                vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_ask = 0U;
            }
            __Vdly__tb_exchange_lite__DOT__dut__DOT__p1_valid = 1U;
        }
    } else {
        vlSelfRef.tb_exchange_lite__DOT__orders_rcvd = 0U;
        __Vdly__tb_exchange_lite__DOT__dut__DOT__p1_valid = 0U;
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_sym_in_range = 0U;
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_symbol = 0U;
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_side = 0U;
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_limit_price = 0U;
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_qty = 0U;
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_order_id = 0U;
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_timestamp = 0U;
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_bid = 0U;
        vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_cur_ask = 0U;
        vlSelfRef.tb_exchange_lite__DOT__fill_frame[0U] = 0U;
        vlSelfRef.tb_exchange_lite__DOT__fill_frame[1U] = 0U;
        vlSelfRef.tb_exchange_lite__DOT__fill_frame[2U] = 0U;
        vlSelfRef.tb_exchange_lite__DOT__fill_frame[3U] = 0U;
        __Vdly__tb_exchange_lite__DOT__fill_valid = 0U;
        vlSelfRef.tb_exchange_lite__DOT__fills_sent = 0U;
        vlSelfRef.tb_exchange_lite__DOT__rejects_sent = 0U;
    }
    vlSelfRef.tb_exchange_lite__DOT__fill_valid = __Vdly__tb_exchange_lite__DOT__fill_valid;
    vlSelfRef.tb_exchange_lite__DOT__dut__DOT__p1_valid 
        = __Vdly__tb_exchange_lite__DOT__dut__DOT__p1_valid;
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

void Vtb_exchange_lite___024root___eval_nba(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_nba\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_exchange_lite___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vtb_exchange_lite___024root___timing_ready(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___timing_ready\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h89ac9348__0.ready("@(posedge tb_exchange_lite.clk)");
    }
    if ((8ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h059def81__0.ready("@( tb_exchange_lite.rst_n)");
    }
}

void Vtb_exchange_lite___024root___timing_resume(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___timing_resume\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h89ac9348__0.moveToResumeQueue(
                                                          "@(posedge tb_exchange_lite.clk)");
    vlSelfRef.__VtrigSched_h059def81__0.moveToResumeQueue(
                                                          "@( tb_exchange_lite.rst_n)");
    vlSelfRef.__VtrigSched_h89ac9348__0.resume("@(posedge tb_exchange_lite.clk)");
    vlSelfRef.__VtrigSched_h059def81__0.resume("@( tb_exchange_lite.rst_n)");
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_exchange_lite___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vtb_exchange_lite___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtb_exchange_lite___024root___eval_phase__act(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_phase__act\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_exchange_lite___024root___eval_triggers_vec__act(vlSelf);
    Vtb_exchange_lite___024root___timing_ready(vlSelf);
    Vtb_exchange_lite___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_exchange_lite___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtb_exchange_lite___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_exchange_lite___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vtb_exchange_lite___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vtb_exchange_lite___024root___eval_phase__inact(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_phase__inact\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 12, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vtb_exchange_lite___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_exchange_lite___024root___eval_phase__nba(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_phase__nba\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_exchange_lite___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_exchange_lite___024root___eval_nba(vlSelf);
        Vtb_exchange_lite___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_exchange_lite___024root___eval(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_exchange_lite___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 12, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 12, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vtb_exchange_lite___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("C:/Users/blazi/Downloads/Dual-FPGA-Trading-Engine/tb/board_a\\tb_exchange_lite.sv", 12, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vtb_exchange_lite___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vtb_exchange_lite___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtb_exchange_lite___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0(Vtb_exchange_lite___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root____VbeforeTrig_h89ac9348__0\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_exchange_lite__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__clk__0 
        = vlSelfRef.tb_exchange_lite__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h89ac9348__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vtb_exchange_lite___024root____VbeforeTrig_h059def81__0(Vtb_exchange_lite___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root____VbeforeTrig_h059def81__0\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)((((IData)(vlSelfRef.tb_exchange_lite__DOT__rst_n) 
                                   != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__rst_n__0)) 
                                  << 3U)));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_exchange_lite__DOT__rst_n__0 
        = vlSelfRef.tb_exchange_lite__DOT__rst_n;
    if ((8ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h059def81__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vtb_exchange_lite___024root___eval_debug_assertions(Vtb_exchange_lite___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_exchange_lite___024root___eval_debug_assertions\n"); );
    Vtb_exchange_lite__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
