// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_exchange_lite.h for the primary calling header

#include "Vtb_exchange_lite__pch.h"

void Vtb_exchange_lite___024unit___ctor_var_reset(Vtb_exchange_lite___024unit* vlSelf);

Vtb_exchange_lite___024unit::Vtb_exchange_lite___024unit() = default;
Vtb_exchange_lite___024unit::~Vtb_exchange_lite___024unit() = default;

void Vtb_exchange_lite___024unit::ctor(Vtb_exchange_lite__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_exchange_lite___024unit___ctor_var_reset(this);
}

void Vtb_exchange_lite___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_exchange_lite___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
