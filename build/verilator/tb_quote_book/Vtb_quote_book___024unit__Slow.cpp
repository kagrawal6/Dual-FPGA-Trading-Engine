// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_quote_book.h for the primary calling header

#include "Vtb_quote_book__pch.h"

void Vtb_quote_book___024unit___ctor_var_reset(Vtb_quote_book___024unit* vlSelf);

Vtb_quote_book___024unit::Vtb_quote_book___024unit() = default;
Vtb_quote_book___024unit::~Vtb_quote_book___024unit() = default;

void Vtb_quote_book___024unit::ctor(Vtb_quote_book__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_quote_book___024unit___ctor_var_reset(this);
}

void Vtb_quote_book___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_quote_book___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
