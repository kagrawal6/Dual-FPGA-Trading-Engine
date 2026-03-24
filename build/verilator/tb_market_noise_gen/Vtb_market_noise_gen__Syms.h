// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTB_MARKET_NOISE_GEN__SYMS_H_
#define VERILATED_VTB_MARKET_NOISE_GEN__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vtb_market_noise_gen.h"

// INCLUDE MODULE CLASSES
#include "Vtb_market_noise_gen___024root.h"
#include "Vtb_market_noise_gen___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vtb_market_noise_gen__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vtb_market_noise_gen* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vtb_market_noise_gen___024root TOP;

    // CONSTRUCTORS
    Vtb_market_noise_gen__Syms(VerilatedContext* contextp, const char* namep, Vtb_market_noise_gen* modelp);
    ~Vtb_market_noise_gen__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
