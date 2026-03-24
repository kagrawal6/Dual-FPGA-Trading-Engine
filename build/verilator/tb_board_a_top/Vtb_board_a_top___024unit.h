// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_board_a_top.h for the primary calling header

#ifndef VERILATED_VTB_BOARD_A_TOP___024UNIT_H_
#define VERILATED_VTB_BOARD_A_TOP___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_board_a_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_board_a_top___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_board_a_top__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_board_a_top___024unit();
    ~Vtb_board_a_top___024unit();
    void ctor(Vtb_board_a_top__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_board_a_top___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
