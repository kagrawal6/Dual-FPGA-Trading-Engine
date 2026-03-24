// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_board_a_top__pch.h"

//============================================================
// Constructors

Vtb_board_a_top::Vtb_board_a_top(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_board_a_top__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_board_a_top::Vtb_board_a_top(const char* _vcname__)
    : Vtb_board_a_top(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_board_a_top::~Vtb_board_a_top() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_board_a_top___024root___eval_debug_assertions(Vtb_board_a_top___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_board_a_top___024root___eval_static(Vtb_board_a_top___024root* vlSelf);
void Vtb_board_a_top___024root___eval_initial(Vtb_board_a_top___024root* vlSelf);
void Vtb_board_a_top___024root___eval_settle(Vtb_board_a_top___024root* vlSelf);
void Vtb_board_a_top___024root___eval(Vtb_board_a_top___024root* vlSelf);

void Vtb_board_a_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_board_a_top::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_board_a_top___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_board_a_top___024root___eval_static(&(vlSymsp->TOP));
        Vtb_board_a_top___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_board_a_top___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_board_a_top___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_board_a_top::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_board_a_top::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_board_a_top::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_board_a_top___024root___eval_final(Vtb_board_a_top___024root* vlSelf);

VL_ATTR_COLD void Vtb_board_a_top::final() {
    Vtb_board_a_top___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_board_a_top::hierName() const { return vlSymsp->name(); }
const char* Vtb_board_a_top::modelName() const { return "Vtb_board_a_top"; }
unsigned Vtb_board_a_top::threads() const { return 1; }
void Vtb_board_a_top::prepareClone() const { contextp()->prepareClone(); }
void Vtb_board_a_top::atClone() const {
    contextp()->threadPoolpOnClone();
}
