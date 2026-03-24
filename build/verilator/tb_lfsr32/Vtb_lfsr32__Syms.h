// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_LFSR32__SYMS_H_
#define VERILATED_VTB_LFSR32__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_lfsr32.h"

// INCLUDE MODULE CLASSES
#include "Vtb_lfsr32___024root.h"
#include "Vtb_lfsr32___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_lfsr32__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_lfsr32* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_lfsr32___024root           TOP;

    // CONSTRUCTORS
    Vtb_lfsr32__Syms(VerilatedContext* contextp, const char* namep, Vtb_lfsr32* modelp);
    ~Vtb_lfsr32__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
