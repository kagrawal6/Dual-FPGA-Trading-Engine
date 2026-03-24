// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_feature_compute__pch.h"

//============================================================
// Constructors

Vtb_feature_compute::Vtb_feature_compute(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_feature_compute__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_feature_compute::Vtb_feature_compute(const char* _vcname__)
    : Vtb_feature_compute(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_feature_compute::~Vtb_feature_compute() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_feature_compute___024root___eval_debug_assertions(Vtb_feature_compute___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_feature_compute___024root___eval_static(Vtb_feature_compute___024root* vlSelf);
void Vtb_feature_compute___024root___eval_initial(Vtb_feature_compute___024root* vlSelf);
void Vtb_feature_compute___024root___eval_settle(Vtb_feature_compute___024root* vlSelf);
void Vtb_feature_compute___024root___eval(Vtb_feature_compute___024root* vlSelf);

void Vtb_feature_compute::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_feature_compute::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_feature_compute___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_feature_compute___024root___eval_static(&(vlSymsp->TOP));
        Vtb_feature_compute___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_feature_compute___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_feature_compute___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_feature_compute::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_feature_compute::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_feature_compute::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_feature_compute___024root___eval_final(Vtb_feature_compute___024root* vlSelf);

VL_ATTR_COLD void Vtb_feature_compute::final() {
    Vtb_feature_compute___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_feature_compute::hierName() const { return vlSymsp->name(); }
const char* Vtb_feature_compute::modelName() const { return "Vtb_feature_compute"; }
unsigned Vtb_feature_compute::threads() const { return 1; }
void Vtb_feature_compute::prepareClone() const { contextp()->prepareClone(); }
void Vtb_feature_compute::atClone() const {
    contextp()->threadPoolpOnClone();
}
