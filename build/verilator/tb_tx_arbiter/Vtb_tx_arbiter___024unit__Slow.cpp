// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_tx_arbiter.h for the primary calling header

#include "Vtb_tx_arbiter__pch.h"

void Vtb_tx_arbiter___024unit___ctor_var_reset(Vtb_tx_arbiter___024unit* vlSelf);

Vtb_tx_arbiter___024unit::Vtb_tx_arbiter___024unit() = default;
Vtb_tx_arbiter___024unit::~Vtb_tx_arbiter___024unit() = default;

void Vtb_tx_arbiter___024unit::ctor(Vtb_tx_arbiter__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_tx_arbiter___024unit___ctor_var_reset(this);
}

void Vtb_tx_arbiter___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_tx_arbiter___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
