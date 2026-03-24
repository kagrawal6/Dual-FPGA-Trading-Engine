// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_link_rx.h for the primary calling header

#include "Vtb_link_rx__pch.h"

void Vtb_link_rx___024root___ctor_var_reset(Vtb_link_rx___024root* vlSelf);

Vtb_link_rx___024root::Vtb_link_rx___024root(Vtb_link_rx__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_link_rx___024root___ctor_var_reset(this);
}

void Vtb_link_rx___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_link_rx___024root::~Vtb_link_rx___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
