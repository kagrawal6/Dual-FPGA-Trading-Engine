// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtb_tx_arbiter__pch.h"

Vtb_tx_arbiter__Syms::Vtb_tx_arbiter__Syms(VerilatedContext* contextp, const char* namep, Vtb_tx_arbiter* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup top module instance
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(375);
    // Setup sub module instances
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
}

Vtb_tx_arbiter__Syms::~Vtb_tx_arbiter__Syms() {
    // Tear down scopes
    // Tear down sub module instances
}
