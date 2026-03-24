// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_link_loopback__pch.h"

//============================================================
// Constructors

Vtb_link_loopback::Vtb_link_loopback(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_link_loopback__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_link_loopback::Vtb_link_loopback(const char* _vcname__)
    : Vtb_link_loopback(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_link_loopback::~Vtb_link_loopback() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_link_loopback___024root___eval_debug_assertions(Vtb_link_loopback___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_link_loopback___024root___eval_static(Vtb_link_loopback___024root* vlSelf);
void Vtb_link_loopback___024root___eval_initial(Vtb_link_loopback___024root* vlSelf);
void Vtb_link_loopback___024root___eval_settle(Vtb_link_loopback___024root* vlSelf);
void Vtb_link_loopback___024root___eval(Vtb_link_loopback___024root* vlSelf);

void Vtb_link_loopback::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_link_loopback::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_link_loopback___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_link_loopback___024root___eval_static(&(vlSymsp->TOP));
        Vtb_link_loopback___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_link_loopback___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_link_loopback___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_link_loopback::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_link_loopback::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_link_loopback::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_link_loopback___024root___eval_final(Vtb_link_loopback___024root* vlSelf);

VL_ATTR_COLD void Vtb_link_loopback::final() {
    Vtb_link_loopback___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_link_loopback::hierName() const { return vlSymsp->name(); }
const char* Vtb_link_loopback::modelName() const { return "Vtb_link_loopback"; }
unsigned Vtb_link_loopback::threads() const { return 1; }
void Vtb_link_loopback::prepareClone() const { contextp()->prepareClone(); }
void Vtb_link_loopback::atClone() const {
    contextp()->threadPoolpOnClone();
}
