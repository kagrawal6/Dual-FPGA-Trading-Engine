// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_link_loopback.h for the primary calling header

#include "Vtb_link_loopback__pch.h"

void Vtb_link_loopback___024unit___ctor_var_reset(Vtb_link_loopback___024unit* vlSelf);

Vtb_link_loopback___024unit::Vtb_link_loopback___024unit() = default;
Vtb_link_loopback___024unit::~Vtb_link_loopback___024unit() = default;

void Vtb_link_loopback___024unit::ctor(Vtb_link_loopback__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_link_loopback___024unit___ctor_var_reset(this);
}

void Vtb_link_loopback___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_link_loopback___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
