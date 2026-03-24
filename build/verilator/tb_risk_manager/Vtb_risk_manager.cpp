// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_risk_manager__pch.h"

//============================================================
// Constructors

Vtb_risk_manager::Vtb_risk_manager(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_risk_manager__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_risk_manager::Vtb_risk_manager(const char* _vcname__)
    : Vtb_risk_manager(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_risk_manager::~Vtb_risk_manager() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_risk_manager___024root___eval_debug_assertions(Vtb_risk_manager___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_risk_manager___024root___eval_static(Vtb_risk_manager___024root* vlSelf);
void Vtb_risk_manager___024root___eval_initial(Vtb_risk_manager___024root* vlSelf);
void Vtb_risk_manager___024root___eval_settle(Vtb_risk_manager___024root* vlSelf);
void Vtb_risk_manager___024root___eval(Vtb_risk_manager___024root* vlSelf);

void Vtb_risk_manager::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_risk_manager::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_risk_manager___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_risk_manager___024root___eval_static(&(vlSymsp->TOP));
        Vtb_risk_manager___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_risk_manager___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_risk_manager___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_risk_manager::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_risk_manager::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_risk_manager::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_risk_manager___024root___eval_final(Vtb_risk_manager___024root* vlSelf);

VL_ATTR_COLD void Vtb_risk_manager::final() {
    Vtb_risk_manager___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_risk_manager::hierName() const { return vlSymsp->name(); }
const char* Vtb_risk_manager::modelName() const { return "Vtb_risk_manager"; }
unsigned Vtb_risk_manager::threads() const { return 1; }
void Vtb_risk_manager::prepareClone() const { contextp()->prepareClone(); }
void Vtb_risk_manager::atClone() const {
    contextp()->threadPoolpOnClone();
}
