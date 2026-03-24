// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_risk_manager.h for the primary calling header

#ifndef VERILATED_VTB_RISK_MANAGER___024UNIT_H_
#define VERILATED_VTB_RISK_MANAGER___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_risk_manager__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_risk_manager___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_risk_manager__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_risk_manager___024unit();
    ~Vtb_risk_manager___024unit();
    void ctor(Vtb_risk_manager__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_risk_manager___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
