// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_strategy_engine.h for the primary calling header

#include "Vtb_strategy_engine__pch.h"

void Vtb_strategy_engine___024unit___ctor_var_reset(Vtb_strategy_engine___024unit* vlSelf);

Vtb_strategy_engine___024unit::Vtb_strategy_engine___024unit() = default;
Vtb_strategy_engine___024unit::~Vtb_strategy_engine___024unit() = default;

void Vtb_strategy_engine___024unit::ctor(Vtb_strategy_engine__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_strategy_engine___024unit___ctor_var_reset(this);
}

void Vtb_strategy_engine___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_strategy_engine___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
