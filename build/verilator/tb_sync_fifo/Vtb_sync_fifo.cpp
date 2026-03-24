// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_sync_fifo__pch.h"

//============================================================
// Constructors

Vtb_sync_fifo::Vtb_sync_fifo(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_sync_fifo__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_sync_fifo::Vtb_sync_fifo(const char* _vcname__)
    : Vtb_sync_fifo(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_sync_fifo::~Vtb_sync_fifo() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_sync_fifo___024root___eval_debug_assertions(Vtb_sync_fifo___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_sync_fifo___024root___eval_static(Vtb_sync_fifo___024root* vlSelf);
void Vtb_sync_fifo___024root___eval_initial(Vtb_sync_fifo___024root* vlSelf);
void Vtb_sync_fifo___024root___eval_settle(Vtb_sync_fifo___024root* vlSelf);
void Vtb_sync_fifo___024root___eval(Vtb_sync_fifo___024root* vlSelf);

void Vtb_sync_fifo::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_sync_fifo::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_sync_fifo___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_sync_fifo___024root___eval_static(&(vlSymsp->TOP));
        Vtb_sync_fifo___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_sync_fifo___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_sync_fifo___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_sync_fifo::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_sync_fifo::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_sync_fifo::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_sync_fifo___024root___eval_final(Vtb_sync_fifo___024root* vlSelf);

VL_ATTR_COLD void Vtb_sync_fifo::final() {
    Vtb_sync_fifo___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_sync_fifo::hierName() const { return vlSymsp->name(); }
const char* Vtb_sync_fifo::modelName() const { return "Vtb_sync_fifo"; }
unsigned Vtb_sync_fifo::threads() const { return 1; }
void Vtb_sync_fifo::prepareClone() const { contextp()->prepareClone(); }
void Vtb_sync_fifo::atClone() const {
    contextp()->threadPoolpOnClone();
}
