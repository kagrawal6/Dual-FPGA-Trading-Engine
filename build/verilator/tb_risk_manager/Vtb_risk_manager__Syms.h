// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_RISK_MANAGER__SYMS_H_
#define VERILATED_VTB_RISK_MANAGER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_risk_manager.h"

// INCLUDE MODULE CLASSES
#include "Vtb_risk_manager___024root.h"
#include "Vtb_risk_manager___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_risk_manager__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_risk_manager* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_risk_manager___024root     TOP;

    // CONSTRUCTORS
    Vtb_risk_manager__Syms(VerilatedContext* contextp, const char* namep, Vtb_risk_manager* modelp);
    ~Vtb_risk_manager__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
