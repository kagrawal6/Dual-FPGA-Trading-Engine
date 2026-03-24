// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_lfsr32__pch.h"

//============================================================
// Constructors

Vtb_lfsr32::Vtb_lfsr32(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_lfsr32__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_lfsr32::Vtb_lfsr32(const char* _vcname__)
    : Vtb_lfsr32(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_lfsr32::~Vtb_lfsr32() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_lfsr32___024root___eval_debug_assertions(Vtb_lfsr32___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_lfsr32___024root___eval_static(Vtb_lfsr32___024root* vlSelf);
void Vtb_lfsr32___024root___eval_initial(Vtb_lfsr32___024root* vlSelf);
void Vtb_lfsr32___024root___eval_settle(Vtb_lfsr32___024root* vlSelf);
void Vtb_lfsr32___024root___eval(Vtb_lfsr32___024root* vlSelf);

void Vtb_lfsr32::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_lfsr32::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_lfsr32___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_lfsr32___024root___eval_static(&(vlSymsp->TOP));
        Vtb_lfsr32___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_lfsr32___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_lfsr32___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_lfsr32::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_lfsr32::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_lfsr32::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_lfsr32___024root___eval_final(Vtb_lfsr32___024root* vlSelf);

VL_ATTR_COLD void Vtb_lfsr32::final() {
    Vtb_lfsr32___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_lfsr32::hierName() const { return vlSymsp->name(); }
const char* Vtb_lfsr32::modelName() const { return "Vtb_lfsr32"; }
unsigned Vtb_lfsr32::threads() const { return 1; }
void Vtb_lfsr32::prepareClone() const { contextp()->prepareClone(); }
void Vtb_lfsr32::atClone() const {
    contextp()->threadPoolpOnClone();
}
