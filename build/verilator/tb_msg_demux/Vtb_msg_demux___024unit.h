// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_msg_demux.h for the primary calling header

#ifndef VERILATED_VTB_MSG_DEMUX___024UNIT_H_
#define VERILATED_VTB_MSG_DEMUX___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_msg_demux__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_msg_demux___024unit final {
  public:

    // INTERNAL VARIABLES
    Vtb_msg_demux__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_msg_demux___024unit();
    ~Vtb_msg_demux___024unit();
    void ctor(Vtb_msg_demux__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vtb_msg_demux___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
