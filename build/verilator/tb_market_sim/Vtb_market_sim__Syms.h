// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_MARKET_SIM__SYMS_H_
#define VERILATED_VTB_MARKET_SIM__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_market_sim.h"

// INCLUDE MODULE CLASSES
#include "Vtb_market_sim___024root.h"
#include "Vtb_market_sim___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_market_sim__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_market_sim* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_market_sim___024root       TOP;

    // CONSTRUCTORS
    Vtb_market_sim__Syms(VerilatedContext* contextp, const char* namep, Vtb_market_sim* modelp);
    ~Vtb_market_sim__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
