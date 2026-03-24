// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_order_manager.h for the primary calling header

#ifndef VERILATED_VTB_ORDER_MANAGER___024UNIT_H_
#define VERILATED_VTB_ORDER_MANAGER___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_order_manager__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_order_manager___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_order_manager__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_order_manager___024unit();
    ~Vtb_order_manager___024unit();
    void ctor(Vtb_order_manager__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_order_manager___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
