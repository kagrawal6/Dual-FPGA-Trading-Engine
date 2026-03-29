// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_sync_fifo.h for the primary calling header

#ifndef VERILATED_VTB_SYNC_FIFO___024ROOT_H_
#define VERILATED_VTB_SYNC_FIFO___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_sync_fifo__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_sync_fifo___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_sync_fifo__DOT__clk;
    CData/*0:0*/ tb_sync_fifo__DOT__rst_n;
    CData/*0:0*/ tb_sync_fifo__DOT__flush;
    CData/*0:0*/ tb_sync_fifo__DOT__wr_en;
    CData/*0:0*/ tb_sync_fifo__DOT__full;
    CData/*0:0*/ tb_sync_fifo__DOT__rd_en;
    CData/*0:0*/ tb_sync_fifo__DOT__empty;
    CData/*5:0*/ tb_sync_fifo__DOT__dut__DOT__wr_ptr;
    CData/*5:0*/ tb_sync_fifo__DOT__dut__DOT__rd_ptr;
    CData/*6:0*/ tb_sync_fifo__DOT__dut__DOT__count_r;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_sync_fifo__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_sync_fifo__DOT__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    VlWide<4>/*127:0*/ tb_sync_fifo__DOT__wr_data;
    IData/*31:0*/ tb_sync_fifo__DOT__err_count;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<VlWide<4>/*127:0*/, 64> tb_sync_fifo__DOT__dut__DOT__mem;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    std::string __Vtask_tb_sync_fifo__DOT__check__0__msg;
    std::string __Vtask_tb_sync_fifo__DOT__check__1__msg;
    std::string __Vtask_tb_sync_fifo__DOT__check__2__msg;
    std::string __Vtask_tb_sync_fifo__DOT__check__3__msg;
    std::string __Vtask_tb_sync_fifo__DOT__check__4__msg;
    std::string __Vtask_tb_sync_fifo__DOT__check__5__msg;
    std::string __Vtask_tb_sync_fifo__DOT__check__6__msg;
    std::string __Vtask_tb_sync_fifo__DOT__check__7__msg;
    std::string __Vtask_tb_sync_fifo__DOT__check__8__msg;
    std::string __Vtask_tb_sync_fifo__DOT__check__9__msg;
    std::string __Vtask_tb_sync_fifo__DOT__check__10__msg;
    std::string __Vtask_tb_sync_fifo__DOT__check__11__msg;
    std::string __Vtask_tb_sync_fifo__DOT__check__12__msg;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h16468184__0;
    VlTriggerScheduler __VtrigSched_hb2fb5223__0;

    // INTERNAL VARIABLES
    Vtb_sync_fifo__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_sync_fifo___024root(Vtb_sync_fifo__Syms* symsp, const char* namep);
    ~Vtb_sync_fifo___024root();
    VL_UNCOPYABLE(Vtb_sync_fifo___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
