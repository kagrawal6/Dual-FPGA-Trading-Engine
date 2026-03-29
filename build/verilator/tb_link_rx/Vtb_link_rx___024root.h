// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_link_rx.h for the primary calling header

#ifndef VERILATED_VTB_LINK_RX___024ROOT_H_
#define VERILATED_VTB_LINK_RX___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_link_rx__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_link_rx___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_link_rx__DOT__clk;
    CData/*0:0*/ tb_link_rx__DOT__rst_n;
    CData/*3:0*/ tb_link_rx__DOT__pmod_data;
    CData/*0:0*/ tb_link_rx__DOT__pmod_valid;
    CData/*0:0*/ tb_link_rx__DOT__frame_out_valid;
    CData/*0:0*/ tb_link_rx__DOT__link_up;
    CData/*0:0*/ tb_link_rx__DOT__dut__DOT__valid_s1;
    CData/*0:0*/ tb_link_rx__DOT__dut__DOT__valid_sync;
    CData/*3:0*/ tb_link_rx__DOT__dut__DOT__data_s1;
    CData/*3:0*/ tb_link_rx__DOT__dut__DOT__data_sync;
    CData/*0:0*/ tb_link_rx__DOT__dut__DOT__valid_prev;
    CData/*0:0*/ tb_link_rx__DOT__dut__DOT__state;
    CData/*4:0*/ tb_link_rx__DOT__dut__DOT__beat_count;
    CData/*0:0*/ tb_link_rx__DOT__dut__DOT__phase;
    CData/*4:0*/ __Vdly__tb_link_rx__DOT__dut__DOT__beat_count;
    CData/*0:0*/ __Vdly__tb_link_rx__DOT__dut__DOT__phase;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_link_rx__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_link_rx__DOT__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    VlWide<4>/*127:0*/ tb_link_rx__DOT__frame_out;
    IData/*31:0*/ tb_link_rx__DOT__error_count;
    IData/*31:0*/ tb_link_rx__DOT__err_count_scratch;
    IData/*31:0*/ tb_link_rx__DOT__frames_seen;
    VlWide<4>/*127:0*/ tb_link_rx__DOT__last_frame;
    IData/*31:0*/ tb_link_rx__DOT__unnamedblk2__DOT__err0;
    IData/*31:0*/ tb_link_rx__DOT__unnamedblk2__DOT__err1;
    IData/*31:0*/ tb_link_rx__DOT__unnamedblk2__DOT__wait_p;
    VlWide<4>/*127:0*/ tb_link_rx__DOT__unnamedblk2__DOT__good_frame;
    VlWide<4>/*127:0*/ tb_link_rx__DOT__unnamedblk2__DOT__bad_msg_frame;
    VlWide<4>/*127:0*/ tb_link_rx__DOT__dut__DOT__assemble_reg;
    VlWide<4>/*127:0*/ tb_link_rx__DOT__dut__DOT__unnamedblk1__DOT__assembled_next;
    IData/*31:0*/ __Vdly__tb_link_rx__DOT__error_count;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    std::string __Vtask_tb_link_rx__DOT__check__1__msg;
    std::string __Vtask_tb_link_rx__DOT__check__2__msg;
    std::string __Vtask_tb_link_rx__DOT__check__3__msg;
    std::string __Vtask_tb_link_rx__DOT__check__7__msg;
    std::string __Vtask_tb_link_rx__DOT__check__8__msg;
    std::string __Vtask_tb_link_rx__DOT__check__9__msg;
    std::string __Vtask_tb_link_rx__DOT__check__12__msg;
    std::string __Vtask_tb_link_rx__DOT__check__13__msg;
    std::string __Vtask_tb_link_rx__DOT__check__14__msg;
    std::string __Vtask_tb_link_rx__DOT__check__15__msg;
    std::string __Vtask_tb_link_rx__DOT__check__19__msg;
    std::string __Vtask_tb_link_rx__DOT__check__20__msg;
    std::string __Vtask_tb_link_rx__DOT__check__21__msg;
    std::string __Vtask_tb_link_rx__DOT__check__22__msg;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_ha334240d__0;
    VlTriggerScheduler __VtrigSched_h6bc084dd__0;

    // INTERNAL VARIABLES
    Vtb_link_rx__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_link_rx___024root(Vtb_link_rx__Syms* symsp, const char* namep);
    ~Vtb_link_rx___024root();
    VL_UNCOPYABLE(Vtb_link_rx___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
