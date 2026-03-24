// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_market_noise_gen.h for the primary calling header

#include "Vtb_market_noise_gen__pch.h"

void Vtb_market_noise_gen___024unit___ctor_var_reset(Vtb_market_noise_gen___024unit* vlSelf);

Vtb_market_noise_gen___024unit::Vtb_market_noise_gen___024unit() = default;
Vtb_market_noise_gen___024unit::~Vtb_market_noise_gen___024unit() = default;

void Vtb_market_noise_gen___024unit::ctor(Vtb_market_noise_gen__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_market_noise_gen___024unit___ctor_var_reset(this);
}

void Vtb_market_noise_gen___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_market_noise_gen___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
