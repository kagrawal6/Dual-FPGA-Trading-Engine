// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_board_b_pipeline.h for the primary calling header

#include "Vtb_board_b_pipeline__pch.h"

void Vtb_board_b_pipeline___024root___ctor_var_reset(Vtb_board_b_pipeline___024root* vlSelf);

Vtb_board_b_pipeline___024root::Vtb_board_b_pipeline___024root(Vtb_board_b_pipeline__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_board_b_pipeline___024root___ctor_var_reset(this);
}

void Vtb_board_b_pipeline___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_board_b_pipeline___024root::~Vtb_board_b_pipeline___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
