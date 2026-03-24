// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_strategy_engine.h for the primary calling header

#ifndef VERILATED_VTB_STRATEGY_ENGINE___024ROOT_H_
#define VERILATED_VTB_STRATEGY_ENGINE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_strategy_engine__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_strategy_engine___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_strategy_engine__DOT__clk;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlDelayScheduler __VdlySched;

    // INTERNAL VARIABLES
    Vtb_strategy_engine__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_strategy_engine___024root(Vtb_strategy_engine__Syms* symsp, const char* namep);
    ~Vtb_strategy_engine___024root();
    VL_UNCOPYABLE(Vtb_strategy_engine___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
