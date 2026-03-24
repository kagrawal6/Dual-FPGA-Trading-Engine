// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_MSG_DEMUX__SYMS_H_
#define VERILATED_VTB_MSG_DEMUX__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_msg_demux.h"

// INCLUDE MODULE CLASSES
#include "Vtb_msg_demux___024root.h"
#include "Vtb_msg_demux___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_msg_demux__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_msg_demux* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_msg_demux___024root        TOP;

    // CONSTRUCTORS
    Vtb_msg_demux__Syms(VerilatedContext* contextp, const char* namep, Vtb_msg_demux* modelp);
    ~Vtb_msg_demux__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
