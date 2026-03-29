// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_tx_arbiter.h for the primary calling header

#ifndef VERILATED_VTB_TX_ARBITER___024ROOT_H_
#define VERILATED_VTB_TX_ARBITER___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_tx_arbiter__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_tx_arbiter___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_tx_arbiter__DOT__clk;
    CData/*0:0*/ tb_tx_arbiter__DOT__rst_n;
    CData/*0:0*/ tb_tx_arbiter__DOT__fill_valid;
    CData/*0:0*/ tb_tx_arbiter__DOT__quote_valid;
    CData/*0:0*/ tb_tx_arbiter__DOT__quote_ready;
    CData/*0:0*/ tb_tx_arbiter__DOT__tx_ready;
    CData/*0:0*/ tb_tx_arbiter__DOT__dut__DOT__tx_buf_valid;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_tx_arbiter__DOT__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    VlWide<4>/*127:0*/ tb_tx_arbiter__DOT__fill_frame;
    VlWide<4>/*127:0*/ tb_tx_arbiter__DOT__quote_frame;
    IData/*31:0*/ tb_tx_arbiter__DOT__err_count;
    VlWide<4>/*127:0*/ tb_tx_arbiter__DOT__unnamedblk1__DOT__F1;
    VlWide<4>/*127:0*/ tb_tx_arbiter__DOT__unnamedblk1__DOT__F2;
    VlWide<4>/*127:0*/ tb_tx_arbiter__DOT__unnamedblk1__DOT__Q1;
    VlWide<4>/*127:0*/ tb_tx_arbiter__DOT__unnamedblk1__DOT__Q2;
    VlWide<4>/*127:0*/ tb_tx_arbiter__DOT__dut__DOT__tx_frame_buf;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    std::string __Vtask_tb_tx_arbiter__DOT__check__0__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__1__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__2__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__3__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__4__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__5__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__6__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__7__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__8__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__9__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__10__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__11__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__12__msg;
    std::string __Vtask_tb_tx_arbiter__DOT__check__13__msg;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h4d3b64c4__0;
    VlTriggerScheduler __VtrigSched_h320c008b__0;

    // INTERNAL VARIABLES
    Vtb_tx_arbiter__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_tx_arbiter___024root(Vtb_tx_arbiter__Syms* symsp, const char* namep);
    ~Vtb_tx_arbiter___024root();
    VL_UNCOPYABLE(Vtb_tx_arbiter___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
