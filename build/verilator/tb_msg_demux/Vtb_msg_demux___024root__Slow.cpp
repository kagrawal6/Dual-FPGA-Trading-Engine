// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_msg_demux.h for the primary calling header

#include "Vtb_msg_demux__pch.h"

void Vtb_msg_demux___024root___ctor_var_reset(Vtb_msg_demux___024root* vlSelf);

Vtb_msg_demux___024root::Vtb_msg_demux___024root(Vtb_msg_demux__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_msg_demux___024root___ctor_var_reset(this);
}

void Vtb_msg_demux___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_msg_demux___024root::~Vtb_msg_demux___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
