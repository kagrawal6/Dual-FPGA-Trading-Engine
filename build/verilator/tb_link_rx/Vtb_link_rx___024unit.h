// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_link_rx.h for the primary calling header

#ifndef VERILATED_VTB_LINK_RX___024UNIT_H_
#define VERILATED_VTB_LINK_RX___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_link_rx__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_link_rx___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_link_rx__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_link_rx___024unit();
    ~Vtb_link_rx___024unit();
    void ctor(Vtb_link_rx__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_link_rx___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
