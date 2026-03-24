// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_board_b_pipeline.h for the primary calling header

#include "Vtb_board_b_pipeline__pch.h"

void Vtb_board_b_pipeline___024unit___ctor_var_reset(Vtb_board_b_pipeline___024unit* vlSelf);

Vtb_board_b_pipeline___024unit::Vtb_board_b_pipeline___024unit() = default;
Vtb_board_b_pipeline___024unit::~Vtb_board_b_pipeline___024unit() = default;

void Vtb_board_b_pipeline___024unit::ctor(Vtb_board_b_pipeline__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_board_b_pipeline___024unit___ctor_var_reset(this);
}

void Vtb_board_b_pipeline___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_board_b_pipeline___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
