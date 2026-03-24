// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_feature_compute.h for the primary calling header

#include "Vtb_feature_compute__pch.h"

void Vtb_feature_compute___024unit___ctor_var_reset(Vtb_feature_compute___024unit* vlSelf);

Vtb_feature_compute___024unit::Vtb_feature_compute___024unit() = default;
Vtb_feature_compute___024unit::~Vtb_feature_compute___024unit() = default;

void Vtb_feature_compute___024unit::ctor(Vtb_feature_compute__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_feature_compute___024unit___ctor_var_reset(this);
}

void Vtb_feature_compute___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_feature_compute___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
