// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_LINK_TX__SYMS_H_
#define VERILATED_VTB_LINK_TX__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_link_tx.h"

// INCLUDE MODULE CLASSES
#include "Vtb_link_tx___024root.h"
#include "Vtb_link_tx___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_link_tx__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_link_tx* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_link_tx___024root          TOP;

    // CONSTRUCTORS
    Vtb_link_tx__Syms(VerilatedContext* contextp, const char* namep, Vtb_link_tx* modelp);
    ~Vtb_link_tx__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
