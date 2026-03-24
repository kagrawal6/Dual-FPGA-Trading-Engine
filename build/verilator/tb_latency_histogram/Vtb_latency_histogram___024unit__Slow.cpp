// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_latency_histogram.h for the primary calling header

#include "Vtb_latency_histogram__pch.h"

void Vtb_latency_histogram___024unit___ctor_var_reset(Vtb_latency_histogram___024unit* vlSelf);

Vtb_latency_histogram___024unit::Vtb_latency_histogram___024unit() = default;
Vtb_latency_histogram___024unit::~Vtb_latency_histogram___024unit() = default;

void Vtb_latency_histogram___024unit::ctor(Vtb_latency_histogram__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_latency_histogram___024unit___ctor_var_reset(this);
}

void Vtb_latency_histogram___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_latency_histogram___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
