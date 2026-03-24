// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_position_tracker.h for the primary calling header

#include "Vtb_position_tracker__pch.h"

void Vtb_position_tracker___024root___ctor_var_reset(Vtb_position_tracker___024root* vlSelf);

Vtb_position_tracker___024root::Vtb_position_tracker___024root(Vtb_position_tracker__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_position_tracker___024root___ctor_var_reset(this);
}

void Vtb_position_tracker___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_position_tracker___024root::~Vtb_position_tracker___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
