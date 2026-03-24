// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_exchange_lite.h for the primary calling header

#ifndef VERILATED_VTB_EXCHANGE_LITE___024UNIT_H_
#define VERILATED_VTB_EXCHANGE_LITE___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_exchange_lite__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_exchange_lite___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_exchange_lite__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_exchange_lite___024unit();
    ~Vtb_exchange_lite___024unit();
    void ctor(Vtb_exchange_lite__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_exchange_lite___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
