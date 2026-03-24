// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_FEATURE_COMPUTE__SYMS_H_
#define VERILATED_VTB_FEATURE_COMPUTE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_feature_compute.h"

// INCLUDE MODULE CLASSES
#include "Vtb_feature_compute___024root.h"
#include "Vtb_feature_compute___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_feature_compute__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_feature_compute* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_feature_compute___024root  TOP;

    // CONSTRUCTORS
    Vtb_feature_compute__Syms(VerilatedContext* contextp, const char* namep, Vtb_feature_compute* modelp);
    ~Vtb_feature_compute__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
