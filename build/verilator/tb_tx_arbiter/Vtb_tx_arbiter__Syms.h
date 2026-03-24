// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_TX_ARBITER__SYMS_H_
#define VERILATED_VTB_TX_ARBITER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_tx_arbiter.h"

// INCLUDE MODULE CLASSES
#include "Vtb_tx_arbiter___024root.h"
#include "Vtb_tx_arbiter___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_tx_arbiter__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_tx_arbiter* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_tx_arbiter___024root       TOP;

    // CONSTRUCTORS
    Vtb_tx_arbiter__Syms(VerilatedContext* contextp, const char* namep, Vtb_tx_arbiter* modelp);
    ~Vtb_tx_arbiter__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
