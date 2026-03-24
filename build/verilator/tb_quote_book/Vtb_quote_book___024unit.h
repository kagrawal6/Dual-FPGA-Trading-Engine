// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_quote_book.h for the primary calling header

#ifndef VERILATED_VTB_QUOTE_BOOK___024UNIT_H_
#define VERILATED_VTB_QUOTE_BOOK___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_quote_book__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_quote_book___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_quote_book__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_quote_book___024unit();
    ~Vtb_quote_book___024unit();
    void ctor(Vtb_quote_book__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_quote_book___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
