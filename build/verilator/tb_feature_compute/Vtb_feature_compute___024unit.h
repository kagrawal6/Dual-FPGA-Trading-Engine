// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_feature_compute.h for the primary calling header

#ifndef VERILATED_VTB_FEATURE_COMPUTE___024UNIT_H_
#define VERILATED_VTB_FEATURE_COMPUTE___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_feature_compute__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_feature_compute___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_feature_compute__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_feature_compute___024unit();
    ~Vtb_feature_compute___024unit();
    void ctor(Vtb_feature_compute__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_feature_compute___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
