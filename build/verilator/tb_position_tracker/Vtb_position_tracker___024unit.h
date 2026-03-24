// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_position_tracker.h for the primary calling header

#ifndef VERILATED_VTB_POSITION_TRACKER___024UNIT_H_
#define VERILATED_VTB_POSITION_TRACKER___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_position_tracker__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_position_tracker___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_position_tracker__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_position_tracker___024unit();
    ~Vtb_position_tracker___024unit();
    void ctor(Vtb_position_tracker__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_position_tracker___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
