// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_risk_manager.h for the primary calling header

#include "Vtb_risk_manager__pch.h"

void Vtb_risk_manager___024root___ctor_var_reset(Vtb_risk_manager___024root* vlSelf);

Vtb_risk_manager___024root::Vtb_risk_manager___024root(Vtb_risk_manager__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_risk_manager___024root___ctor_var_reset(this);
}

void Vtb_risk_manager___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_risk_manager___024root::~Vtb_risk_manager___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
