// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_lfsr32.h for the primary calling header

#include "Vtb_lfsr32__pch.h"

// Parameter definitions for Vtb_lfsr32___024root
constexpr VlUnpacked<IData/*31:0*/, 8> Vtb_lfsr32___024root::tb_lfsr32__DOT__GOLDEN_AFTER_SEED1;


void Vtb_lfsr32___024root___ctor_var_reset(Vtb_lfsr32___024root* vlSelf);

Vtb_lfsr32___024root::Vtb_lfsr32___024root(Vtb_lfsr32__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_lfsr32___024root___ctor_var_reset(this);
}

void Vtb_lfsr32___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_lfsr32___024root::~Vtb_lfsr32___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
