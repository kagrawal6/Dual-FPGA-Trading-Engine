// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_risk_manager.h for the primary calling header

#ifndef VERILATED_VTB_RISK_MANAGER___024ROOT_H_
#define VERILATED_VTB_RISK_MANAGER___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_risk_manager__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_risk_manager___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_risk_manager__DOT__clk;
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
    Vtb_risk_manager__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_risk_manager___024root(Vtb_risk_manager__Syms* symsp, const char* namep);
    ~Vtb_risk_manager___024root();
    VL_UNCOPYABLE(Vtb_risk_manager___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
