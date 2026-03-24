// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_risk_manager.h for the primary calling header

#include "Vtb_risk_manager__pch.h"

void Vtb_risk_manager___024unit___ctor_var_reset(Vtb_risk_manager___024unit* vlSelf);

Vtb_risk_manager___024unit::Vtb_risk_manager___024unit() = default;
Vtb_risk_manager___024unit::~Vtb_risk_manager___024unit() = default;

void Vtb_risk_manager___024unit::ctor(Vtb_risk_manager__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_risk_manager___024unit___ctor_var_reset(this);
}

void Vtb_risk_manager___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_risk_manager___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
