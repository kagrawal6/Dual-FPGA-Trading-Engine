// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_latency_histogram.h for the primary calling header

#ifndef VERILATED_VTB_LATENCY_HISTOGRAM___024UNIT_H_
#define VERILATED_VTB_LATENCY_HISTOGRAM___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_latency_histogram__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_latency_histogram___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_latency_histogram__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_latency_histogram___024unit();
    ~Vtb_latency_histogram___024unit();
    void ctor(Vtb_latency_histogram__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_latency_histogram___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
