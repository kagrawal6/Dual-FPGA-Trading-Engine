// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_latency_histogram__pch.h"

//============================================================
// Constructors

Vtb_latency_histogram::Vtb_latency_histogram(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_latency_histogram__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_latency_histogram::Vtb_latency_histogram(const char* _vcname__)
    : Vtb_latency_histogram(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_latency_histogram::~Vtb_latency_histogram() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_latency_histogram___024root___eval_debug_assertions(Vtb_latency_histogram___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_latency_histogram___024root___eval_static(Vtb_latency_histogram___024root* vlSelf);
void Vtb_latency_histogram___024root___eval_initial(Vtb_latency_histogram___024root* vlSelf);
void Vtb_latency_histogram___024root___eval_settle(Vtb_latency_histogram___024root* vlSelf);
void Vtb_latency_histogram___024root___eval(Vtb_latency_histogram___024root* vlSelf);

void Vtb_latency_histogram::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_latency_histogram::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_latency_histogram___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_latency_histogram___024root___eval_static(&(vlSymsp->TOP));
        Vtb_latency_histogram___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_latency_histogram___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_latency_histogram___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_latency_histogram::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_latency_histogram::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_latency_histogram::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_latency_histogram___024root___eval_final(Vtb_latency_histogram___024root* vlSelf);

VL_ATTR_COLD void Vtb_latency_histogram::final() {
    Vtb_latency_histogram___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_latency_histogram::hierName() const { return vlSymsp->name(); }
const char* Vtb_latency_histogram::modelName() const { return "Vtb_latency_histogram"; }
unsigned Vtb_latency_histogram::threads() const { return 1; }
void Vtb_latency_histogram::prepareClone() const { contextp()->prepareClone(); }
void Vtb_latency_histogram::atClone() const {
    contextp()->threadPoolpOnClone();
}
