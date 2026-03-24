// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_SYNC_FIFO__SYMS_H_
#define VERILATED_VTB_SYNC_FIFO__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_sync_fifo.h"

// INCLUDE MODULE CLASSES
#include "Vtb_sync_fifo___024root.h"
#include "Vtb_sync_fifo___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_sync_fifo__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_sync_fifo* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_sync_fifo___024root        TOP;

    // CONSTRUCTORS
    Vtb_sync_fifo__Syms(VerilatedContext* contextp, const char* namep, Vtb_sync_fifo* modelp);
    ~Vtb_sync_fifo__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
