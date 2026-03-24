// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_strategy_engine__pch.h"

//============================================================
// Constructors

Vtb_strategy_engine::Vtb_strategy_engine(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_strategy_engine__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_strategy_engine::Vtb_strategy_engine(const char* _vcname__)
    : Vtb_strategy_engine(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_strategy_engine::~Vtb_strategy_engine() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_strategy_engine___024root___eval_debug_assertions(Vtb_strategy_engine___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_strategy_engine___024root___eval_static(Vtb_strategy_engine___024root* vlSelf);
void Vtb_strategy_engine___024root___eval_initial(Vtb_strategy_engine___024root* vlSelf);
void Vtb_strategy_engine___024root___eval_settle(Vtb_strategy_engine___024root* vlSelf);
void Vtb_strategy_engine___024root___eval(Vtb_strategy_engine___024root* vlSelf);

void Vtb_strategy_engine::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_strategy_engine::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_strategy_engine___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_strategy_engine___024root___eval_static(&(vlSymsp->TOP));
        Vtb_strategy_engine___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_strategy_engine___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_strategy_engine___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_strategy_engine::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_strategy_engine::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_strategy_engine::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_strategy_engine___024root___eval_final(Vtb_strategy_engine___024root* vlSelf);

VL_ATTR_COLD void Vtb_strategy_engine::final() {
    Vtb_strategy_engine___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_strategy_engine::hierName() const { return vlSymsp->name(); }
const char* Vtb_strategy_engine::modelName() const { return "Vtb_strategy_engine"; }
unsigned Vtb_strategy_engine::threads() const { return 1; }
void Vtb_strategy_engine::prepareClone() const { contextp()->prepareClone(); }
void Vtb_strategy_engine::atClone() const {
    contextp()->threadPoolpOnClone();
}
