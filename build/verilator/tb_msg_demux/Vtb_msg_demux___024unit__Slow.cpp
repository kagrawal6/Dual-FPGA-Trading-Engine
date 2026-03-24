// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_msg_demux.h for the primary calling header

#include "Vtb_msg_demux__pch.h"

void Vtb_msg_demux___024unit___ctor_var_reset(Vtb_msg_demux___024unit* vlSelf);

Vtb_msg_demux___024unit::Vtb_msg_demux___024unit() = default;
Vtb_msg_demux___024unit::~Vtb_msg_demux___024unit() = default;

void Vtb_msg_demux___024unit::ctor(Vtb_msg_demux__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_msg_demux___024unit___ctor_var_reset(this);
}

void Vtb_msg_demux___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_msg_demux___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
