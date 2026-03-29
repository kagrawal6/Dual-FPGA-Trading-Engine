// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_board_a_ctrl.h for the primary calling header

#ifndef VERILATED_VTB_BOARD_A_CTRL___024ROOT_H_
#define VERILATED_VTB_BOARD_A_CTRL___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_board_a_ctrl__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_board_a_ctrl___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_board_a_ctrl__DOT__clk;
    CData/*0:0*/ tb_board_a_ctrl__DOT__rst_n;
    CData/*3:0*/ tb_board_a_ctrl__DOT__btn;
    CData/*7:0*/ tb_board_a_ctrl__DOT__sw;
    CData/*1:0*/ tb_board_a_ctrl__DOT__regime_sw;
    CData/*0:0*/ tb_board_a_ctrl__DOT__sw_override;
    CData/*0:0*/ tb_board_a_ctrl__DOT__running;
    CData/*1:0*/ tb_board_a_ctrl__DOT__active_regime;
    CData/*0:0*/ tb_board_a_ctrl__DOT__link_up;
    CData/*0:0*/ tb_board_a_ctrl__DOT__link_error;
    CData/*7:0*/ tb_board_a_ctrl__DOT__led;
    CData/*2:0*/ tb_board_a_ctrl__DOT__rgb0;
    CData/*2:0*/ tb_board_a_ctrl__DOT__rgb1;
    CData/*0:0*/ tb_board_a_ctrl__DOT__dut__DOT__db0;
    CData/*0:0*/ tb_board_a_ctrl__DOT__dut__DOT__p0;
    CData/*5:0*/ tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__counter;
    CData/*0:0*/ tb_board_a_ctrl__DOT__dut__DOT__u_db0__DOT__btn_out_prev;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_board_a_ctrl__DOT__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ tb_board_a_ctrl__DOT__err_count;
    IData/*24:0*/ tb_board_a_ctrl__DOT__dut__DOT__blink_ctr;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    std::string __Vtask_tb_board_a_ctrl__DOT__check__0__msg;
    std::string __Vtask_tb_board_a_ctrl__DOT__check__1__msg;
    std::string __Vtask_tb_board_a_ctrl__DOT__check__2__msg;
    std::string __Vtask_tb_board_a_ctrl__DOT__check__3__msg;
    std::string __Vtask_tb_board_a_ctrl__DOT__check__4__msg;
    std::string __Vtask_tb_board_a_ctrl__DOT__check__5__msg;
    std::string __Vtask_tb_board_a_ctrl__DOT__check__6__msg;
    std::string __Vtask_tb_board_a_ctrl__DOT__check__7__msg;
    std::string __Vtask_tb_board_a_ctrl__DOT__check__8__msg;
    std::string __Vtask_tb_board_a_ctrl__DOT__check__9__msg;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h5841218e__0;
    VlTriggerScheduler __VtrigSched_h5c2f6120__0;

    // INTERNAL VARIABLES
    Vtb_board_a_ctrl__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_board_a_ctrl___024root(Vtb_board_a_ctrl__Syms* symsp, const char* namep);
    ~Vtb_board_a_ctrl___024root();
    VL_UNCOPYABLE(Vtb_board_a_ctrl___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
