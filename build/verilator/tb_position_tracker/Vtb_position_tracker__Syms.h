// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_POSITION_TRACKER__SYMS_H_
#define VERILATED_VTB_POSITION_TRACKER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_position_tracker.h"

// INCLUDE MODULE CLASSES
#include "Vtb_position_tracker___024root.h"
#include "Vtb_position_tracker___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_position_tracker__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_position_tracker* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_position_tracker___024root TOP;

    // CONSTRUCTORS
    Vtb_position_tracker__Syms(VerilatedContext* contextp, const char* namep, Vtb_position_tracker* modelp);
    ~Vtb_position_tracker__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
