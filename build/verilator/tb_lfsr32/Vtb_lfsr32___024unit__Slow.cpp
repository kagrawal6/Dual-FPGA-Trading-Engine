// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_lfsr32.h for the primary calling header

#include "Vtb_lfsr32__pch.h"

void Vtb_lfsr32___024unit___ctor_var_reset(Vtb_lfsr32___024unit* vlSelf);

Vtb_lfsr32___024unit::Vtb_lfsr32___024unit() = default;
Vtb_lfsr32___024unit::~Vtb_lfsr32___024unit() = default;

void Vtb_lfsr32___024unit::ctor(Vtb_lfsr32__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_lfsr32___024unit___ctor_var_reset(this);
}

void Vtb_lfsr32___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_lfsr32___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
