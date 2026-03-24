// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_sync_fifo.h for the primary calling header

#ifndef VERILATED_VTB_SYNC_FIFO___024UNIT_H_
#define VERILATED_VTB_SYNC_FIFO___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_sync_fifo__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_sync_fifo___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_sync_fifo__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_sync_fifo___024unit();
    ~Vtb_sync_fifo___024unit();
    void ctor(Vtb_sync_fifo__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_sync_fifo___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
