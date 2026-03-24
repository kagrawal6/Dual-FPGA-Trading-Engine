// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_feature_compute.h for the primary calling header

#include "Vtb_feature_compute__pch.h"

void Vtb_feature_compute___024root___ctor_var_reset(Vtb_feature_compute___024root* vlSelf);

Vtb_feature_compute___024root::Vtb_feature_compute___024root(Vtb_feature_compute__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_feature_compute___024root___ctor_var_reset(this);
}

void Vtb_feature_compute___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_feature_compute___024root::~Vtb_feature_compute___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
