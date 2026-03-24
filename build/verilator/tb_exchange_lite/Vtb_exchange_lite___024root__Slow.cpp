// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_exchange_lite.h for the primary calling header

#include "Vtb_exchange_lite__pch.h"

void Vtb_exchange_lite___024root___ctor_var_reset(Vtb_exchange_lite___024root* vlSelf);

Vtb_exchange_lite___024root::Vtb_exchange_lite___024root(Vtb_exchange_lite__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_exchange_lite___024root___ctor_var_reset(this);
}

void Vtb_exchange_lite___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_exchange_lite___024root::~Vtb_exchange_lite___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
