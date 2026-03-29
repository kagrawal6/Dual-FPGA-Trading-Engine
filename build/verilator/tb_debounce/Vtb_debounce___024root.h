// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_debounce.h for the primary calling header

#ifndef VERILATED_VTB_DEBOUNCE___024ROOT_H_
#define VERILATED_VTB_DEBOUNCE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_debounce__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_debounce___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_debounce__DOT__clk;
    CData/*0:0*/ tb_debounce__DOT__rst_n;
    CData/*0:0*/ tb_debounce__DOT__btn_in;
    CData/*0:0*/ tb_debounce__DOT__btn_out;
    CData/*0:0*/ tb_debounce__DOT__btn_pulse;
    CData/*4:0*/ tb_debounce__DOT__dut__DOT__counter;
    CData/*0:0*/ tb_debounce__DOT__dut__DOT__btn_out_prev;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_debounce__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_debounce__DOT__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ tb_debounce__DOT__err_count;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    std::string __Vtask_tb_debounce__DOT__check__1__msg;
    std::string __Vtask_tb_debounce__DOT__check__2__msg;
    std::string __Vtask_tb_debounce__DOT__check__3__msg;
    std::string __Vtask_tb_debounce__DOT__check__4__msg;
    std::string __Vtask_tb_debounce__DOT__check__5__msg;
    std::string __Vtask_tb_debounce__DOT__check__6__msg;
    std::string __Vtask_tb_debounce__DOT__check__7__msg;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h5a5a23e9__0;

    // INTERNAL VARIABLES
    Vtb_debounce__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_debounce___024root(Vtb_debounce__Syms* symsp, const char* namep);
    ~Vtb_debounce___024root();
    VL_UNCOPYABLE(Vtb_debounce___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
