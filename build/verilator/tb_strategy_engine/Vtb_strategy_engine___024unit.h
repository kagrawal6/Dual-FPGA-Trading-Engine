// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_strategy_engine.h for the primary calling header

#ifndef VERILATED_VTB_STRATEGY_ENGINE___024UNIT_H_
#define VERILATED_VTB_STRATEGY_ENGINE___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_strategy_engine__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_strategy_engine___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_strategy_engine__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_strategy_engine___024unit();
    ~Vtb_strategy_engine___024unit();
    void ctor(Vtb_strategy_engine__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_strategy_engine___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
