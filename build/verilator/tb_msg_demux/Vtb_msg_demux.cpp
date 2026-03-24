// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_msg_demux__pch.h"

//============================================================
// Constructors

Vtb_msg_demux::Vtb_msg_demux(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_msg_demux__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_msg_demux::Vtb_msg_demux(const char* _vcname__)
    : Vtb_msg_demux(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_msg_demux::~Vtb_msg_demux() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_msg_demux___024root___eval_debug_assertions(Vtb_msg_demux___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_msg_demux___024root___eval_static(Vtb_msg_demux___024root* vlSelf);
void Vtb_msg_demux___024root___eval_initial(Vtb_msg_demux___024root* vlSelf);
void Vtb_msg_demux___024root___eval_settle(Vtb_msg_demux___024root* vlSelf);
void Vtb_msg_demux___024root___eval(Vtb_msg_demux___024root* vlSelf);

void Vtb_msg_demux::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_msg_demux::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_msg_demux___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_msg_demux___024root___eval_static(&(vlSymsp->TOP));
        Vtb_msg_demux___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_msg_demux___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_msg_demux___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_msg_demux::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vtb_msg_demux::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_msg_demux::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_msg_demux___024root___eval_final(Vtb_msg_demux___024root* vlSelf);

VL_ATTR_COLD void Vtb_msg_demux::final() {
    Vtb_msg_demux___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_msg_demux::hierName() const { return vlSymsp->name(); }
const char* Vtb_msg_demux::modelName() const { return "Vtb_msg_demux"; }
unsigned Vtb_msg_demux::threads() const { return 1; }
void Vtb_msg_demux::prepareClone() const { contextp()->prepareClone(); }
void Vtb_msg_demux::atClone() const {
    contextp()->threadPoolpOnClone();
}
