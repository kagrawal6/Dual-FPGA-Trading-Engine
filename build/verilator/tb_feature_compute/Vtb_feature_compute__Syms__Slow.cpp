// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtb_feature_compute__pch.h"

Vtb_feature_compute__Syms::Vtb_feature_compute__Syms(VerilatedContext* contextp, const char* namep, Vtb_feature_compute* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup top module instance
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(194);
    // Setup sub module instances
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
}

Vtb_feature_compute__Syms::~Vtb_feature_compute__Syms() {
    // Tear down scopes
    // Tear down sub module instances
}
