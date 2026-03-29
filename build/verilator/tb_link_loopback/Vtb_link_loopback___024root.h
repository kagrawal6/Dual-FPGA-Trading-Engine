// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_link_loopback.h for the primary calling header

#ifndef VERILATED_VTB_LINK_LOOPBACK___024ROOT_H_
#define VERILATED_VTB_LINK_LOOPBACK___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_link_loopback__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_link_loopback___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_link_loopback__DOT__clk;
    CData/*0:0*/ tb_link_loopback__DOT__rst_n;
    CData/*0:0*/ tb_link_loopback__DOT__frame_in_valid;
    CData/*0:0*/ tb_link_loopback__DOT__frame_in_ready;
    CData/*0:0*/ tb_link_loopback__DOT__frame_out_valid;
    CData/*0:0*/ tb_link_loopback__DOT__link_up;
    CData/*0:0*/ tb_link_loopback__DOT__pmod_valid;
    CData/*0:0*/ tb_link_loopback__DOT__u_link_tx__DOT__st;
    CData/*4:0*/ tb_link_loopback__DOT__u_link_tx__DOT__beat;
    CData/*0:0*/ tb_link_loopback__DOT__u_link_tx__DOT__half_nibble;
    CData/*0:0*/ tb_link_loopback__DOT__u_link_rx__DOT__valid_s1;
    CData/*0:0*/ tb_link_loopback__DOT__u_link_rx__DOT__valid_sync;
    CData/*3:0*/ tb_link_loopback__DOT__u_link_rx__DOT__data_s1;
    CData/*3:0*/ tb_link_loopback__DOT__u_link_rx__DOT__data_sync;
    CData/*0:0*/ tb_link_loopback__DOT__u_link_rx__DOT__valid_prev;
    CData/*0:0*/ tb_link_loopback__DOT__u_link_rx__DOT__state;
    CData/*4:0*/ tb_link_loopback__DOT__u_link_rx__DOT__beat_count;
    CData/*0:0*/ tb_link_loopback__DOT__u_link_rx__DOT__phase;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_link_loopback__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_link_loopback__DOT__rst_n__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_link_loopback__DOT__frame_out_valid__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    VlWide<4>/*127:0*/ tb_link_loopback__DOT__frame_in;
    VlWide<4>/*127:0*/ tb_link_loopback__DOT__frame_out;
    IData/*31:0*/ tb_link_loopback__DOT__error_count;
    IData/*31:0*/ tb_link_loopback__DOT__err_count;
    VlWide<4>/*127:0*/ tb_link_loopback__DOT__unnamedblk1__DOT__payload;
    VlWide<4>/*127:0*/ tb_link_loopback__DOT__u_link_tx__DOT__shifter;
    VlWide<4>/*127:0*/ tb_link_loopback__DOT__u_link_rx__DOT__assemble_reg;
    VlWide<4>/*127:0*/ tb_link_loopback__DOT__u_link_rx__DOT__unnamedblk1__DOT__assembled_next;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    std::string __Vtask_tb_link_loopback__DOT__check__0__msg;
    std::string __Vtask_tb_link_loopback__DOT__check__1__msg;
    std::string __Vtask_tb_link_loopback__DOT__check__2__msg;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_hd6195f49__0;
    VlTriggerScheduler __VtrigSched_hfce81947__0;
    VlTriggerScheduler __VtrigSched_h91136b0c__0;

    // INTERNAL VARIABLES
    Vtb_link_loopback__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_link_loopback___024root(Vtb_link_loopback__Syms* symsp, const char* namep);
    ~Vtb_link_loopback___024root();
    VL_UNCOPYABLE(Vtb_link_loopback___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
