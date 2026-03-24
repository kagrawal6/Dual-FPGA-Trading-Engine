// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_market_noise_gen.h for the primary calling header

#ifndef VERILATED_VTB_MARKET_NOISE_GEN___024UNIT_H_
#define VERILATED_VTB_MARKET_NOISE_GEN___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_market_noise_gen__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_market_noise_gen___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_market_noise_gen__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_market_noise_gen___024unit();
    ~Vtb_market_noise_gen___024unit();
    void ctor(Vtb_market_noise_gen__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_market_noise_gen___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
