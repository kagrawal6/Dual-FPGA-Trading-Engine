// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_position_tracker.h for the primary calling header

#include "Vtb_position_tracker__pch.h"

void Vtb_position_tracker___024unit___ctor_var_reset(Vtb_position_tracker___024unit* vlSelf);

Vtb_position_tracker___024unit::Vtb_position_tracker___024unit() = default;
Vtb_position_tracker___024unit::~Vtb_position_tracker___024unit() = default;

void Vtb_position_tracker___024unit::ctor(Vtb_position_tracker__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_position_tracker___024unit___ctor_var_reset(this);
}

void Vtb_position_tracker___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_position_tracker___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
