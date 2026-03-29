// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_lfsr32.h for the primary calling header

#ifndef VERILATED_VTB_LFSR32___024ROOT_H_
#define VERILATED_VTB_LFSR32___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_lfsr32__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_lfsr32___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_lfsr32__DOT__clk;
    CData/*0:0*/ tb_lfsr32__DOT__rst_n;
    CData/*0:0*/ tb_lfsr32__DOT__enable;
    CData/*0:0*/ tb_lfsr32__DOT__load;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_lfsr32__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_lfsr32__DOT__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ tb_lfsr32__DOT__seed_in;
    IData/*31:0*/ tb_lfsr32__DOT__err_count;
    IData/*31:0*/ tb_lfsr32__DOT__dut__DOT__lfsr_reg;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    std::string __Vtask_tb_lfsr32__DOT__check__2__msg;
    std::string __Vtask_tb_lfsr32__DOT__check__4__msg;
    std::string __Vtask_tb_lfsr32__DOT__check__5__msg;
    std::string __Vtask_tb_lfsr32__DOT__check__7__msg;
    std::string __Vtask_tb_lfsr32__DOT__check__9__msg;
    std::string __Vtask_tb_lfsr32__DOT__check__11__msg;
    std::string __Vtask_tb_lfsr32__DOT__check__13__msg;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_hb706121e__0;

    // INTERNAL VARIABLES
    Vtb_lfsr32__Syms* vlSymsp;
    const char* vlNamep;

    // PARAMETERS
    static constexpr VlUnpacked<IData/*31:0*/, 8> tb_lfsr32__DOT__GOLDEN_AFTER_SEED1 = {{
        1U, 0x00400007U, 0x00600004U, 0x00300002U,
        0x00180001U, 0x004c0007U, 0x00660004U, 0x00330002U
    }};

    // CONSTRUCTORS
    Vtb_lfsr32___024root(Vtb_lfsr32__Syms* symsp, const char* namep);
    ~Vtb_lfsr32___024root();
    VL_UNCOPYABLE(Vtb_lfsr32___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
