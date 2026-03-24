// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_quote_book.h for the primary calling header

#include "Vtb_quote_book__pch.h"

void Vtb_quote_book___024root___ctor_var_reset(Vtb_quote_book___024root* vlSelf);

Vtb_quote_book___024root::Vtb_quote_book___024root(Vtb_quote_book__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_quote_book___024root___ctor_var_reset(this);
}

void Vtb_quote_book___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_quote_book___024root::~Vtb_quote_book___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
