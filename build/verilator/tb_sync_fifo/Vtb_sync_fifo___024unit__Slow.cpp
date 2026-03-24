// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_sync_fifo.h for the primary calling header

#include "Vtb_sync_fifo__pch.h"

void Vtb_sync_fifo___024unit___ctor_var_reset(Vtb_sync_fifo___024unit* vlSelf);

Vtb_sync_fifo___024unit::Vtb_sync_fifo___024unit() = default;
Vtb_sync_fifo___024unit::~Vtb_sync_fifo___024unit() = default;

void Vtb_sync_fifo___024unit::ctor(Vtb_sync_fifo__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vtb_sync_fifo___024unit___ctor_var_reset(this);
}

void Vtb_sync_fifo___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vtb_sync_fifo___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
