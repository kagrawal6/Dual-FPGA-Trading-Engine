// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_market_sim.h for the primary calling header

#include "Vtb_market_sim__pch.h"

void Vtb_market_sim___024root___ctor_var_reset(Vtb_market_sim___024root* vlSelf);

Vtb_market_sim___024root::Vtb_market_sim___024root(Vtb_market_sim__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_market_sim___024root___ctor_var_reset(this);
}

void Vtb_market_sim___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_market_sim___024root::~Vtb_market_sim___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
