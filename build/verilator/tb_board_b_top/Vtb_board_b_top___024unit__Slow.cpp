// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_board_b_top.h for the primary calling header

#include "Vtb_board_b_top__pch.h"

void Vtb_board_b_top___024unit___ctor_var_reset(Vtb_board_b_top___024unit* vlSelf);

Vtb_board_b_top___024unit::Vtb_board_b_top___024unit() = default;
Vtb_board_b_top___024unit::~Vtb_board_b_top___024unit() = default;

void Vtb_board_b_top___024unit::ctor(Vtb_board_b_top__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_board_b_top___024unit___ctor_var_reset(this);
}

void Vtb_board_b_top___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_board_b_top___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
