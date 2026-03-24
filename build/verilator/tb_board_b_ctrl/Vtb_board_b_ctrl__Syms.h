// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_BOARD_B_CTRL__SYMS_H_
#define VERILATED_VTB_BOARD_B_CTRL__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_board_b_ctrl.h"

// INCLUDE MODULE CLASSES
#include "Vtb_board_b_ctrl___024root.h"
#include "Vtb_board_b_ctrl___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_board_b_ctrl__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_board_b_ctrl* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_board_b_ctrl___024root     TOP;

    // CONSTRUCTORS
    Vtb_board_b_ctrl__Syms(VerilatedContext* contextp, const char* namep, Vtb_board_b_ctrl* modelp);
    ~Vtb_board_b_ctrl__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
