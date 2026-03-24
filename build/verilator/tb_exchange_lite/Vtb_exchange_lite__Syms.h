// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_EXCHANGE_LITE__SYMS_H_
#define VERILATED_VTB_EXCHANGE_LITE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_exchange_lite.h"

// INCLUDE MODULE CLASSES
#include "Vtb_exchange_lite___024root.h"
#include "Vtb_exchange_lite___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_exchange_lite__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_exchange_lite* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_exchange_lite___024root    TOP;

    // CONSTRUCTORS
    Vtb_exchange_lite__Syms(VerilatedContext* contextp, const char* namep, Vtb_exchange_lite* modelp);
    ~Vtb_exchange_lite__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
