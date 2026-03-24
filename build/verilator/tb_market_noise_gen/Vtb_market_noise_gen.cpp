// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_market_noise_gen__pch.h"

//============================================================
// Constructors

Vtb_market_noise_gen::Vtb_market_noise_gen(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_market_noise_gen__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_market_noise_gen::Vtb_market_noise_gen(const char* _vcname__)
    : Vtb_market_noise_gen(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_market_noise_gen::~Vtb_market_noise_gen() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_market_noise_gen___024root___eval_debug_assertions(Vtb_market_noise_gen___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_market_noise_gen___024root___eval_static(Vtb_market_noise_gen___024root* vlSelf);
void Vtb_market_noise_gen___024root___eval_initial(Vtb_market_noise_gen___024root* vlSelf);
void Vtb_market_noise_gen___024root___eval_settle(Vtb_market_noise_gen___024root* vlSelf);
void Vtb_market_noise_gen___024root___eval(Vtb_market_noise_gen___024root* vlSelf);

void Vtb_market_noise_gen::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_market_noise_gen::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_market_noise_gen___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_market_noise_gen___024root___eval_static(&(vlSymsp->TOP));
        Vtb_market_noise_gen___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_market_noise_gen___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_market_noise_gen___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_market_noise_gen::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_market_noise_gen::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_market_noise_gen::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_market_noise_gen___024root___eval_final(Vtb_market_noise_gen___024root* vlSelf);

VL_ATTR_COLD void Vtb_market_noise_gen::final() {
    Vtb_market_noise_gen___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_market_noise_gen::hierName() const { return vlSymsp->name(); }
const char* Vtb_market_noise_gen::modelName() const { return "Vtb_market_noise_gen"; }
unsigned Vtb_market_noise_gen::threads() const { return 1; }
void Vtb_market_noise_gen::prepareClone() const { contextp()->prepareClone(); }
void Vtb_market_noise_gen::atClone() const {
    contextp()->threadPoolpOnClone();
}
