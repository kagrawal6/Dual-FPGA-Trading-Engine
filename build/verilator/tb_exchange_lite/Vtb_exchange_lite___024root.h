// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_exchange_lite.h for the primary calling header

#ifndef VERILATED_VTB_EXCHANGE_LITE___024ROOT_H_
#define VERILATED_VTB_EXCHANGE_LITE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_exchange_lite__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_exchange_lite___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_exchange_lite__DOT__clk;
    CData/*0:0*/ tb_exchange_lite__DOT__rst_n;
    CData/*0:0*/ tb_exchange_lite__DOT__enable;
    CData/*0:0*/ tb_exchange_lite__DOT__order_valid;
    CData/*0:0*/ tb_exchange_lite__DOT__fill_valid;
    CData/*0:0*/ tb_exchange_lite__DOT__fill_ready;
    CData/*0:0*/ tb_exchange_lite__DOT__dut__DOT__p1_valid;
    CData/*0:0*/ tb_exchange_lite__DOT__dut__DOT__p1_sym_in_range;
    CData/*7:0*/ tb_exchange_lite__DOT__dut__DOT__p1_symbol;
    CData/*0:0*/ tb_exchange_lite__DOT__dut__DOT__p1_side;
    CData/*0:0*/ tb_exchange_lite__DOT__dut__DOT__is_filled;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_exchange_lite__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_exchange_lite__DOT__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    SData/*15:0*/ tb_exchange_lite__DOT__dut__DOT__p1_qty;
    SData/*15:0*/ tb_exchange_lite__DOT__dut__DOT__p1_order_id;
    SData/*15:0*/ tb_exchange_lite__DOT__dut__DOT__p1_timestamp;
    SData/*15:0*/ tb_exchange_lite__DOT__dut__DOT__fill_qty_val;
    VlWide<4>/*127:0*/ tb_exchange_lite__DOT__order_frame;
    VlWide<4>/*127:0*/ tb_exchange_lite__DOT__fill_frame;
    IData/*31:0*/ tb_exchange_lite__DOT__orders_rcvd;
    IData/*31:0*/ tb_exchange_lite__DOT__fills_sent;
    IData/*31:0*/ tb_exchange_lite__DOT__rejects_sent;
    IData/*31:0*/ tb_exchange_lite__DOT__err_count;
    IData/*31:0*/ tb_exchange_lite__DOT__dut__DOT__p1_limit_price;
    IData/*31:0*/ tb_exchange_lite__DOT__dut__DOT__p1_cur_bid;
    IData/*31:0*/ tb_exchange_lite__DOT__dut__DOT__p1_cur_ask;
    IData/*31:0*/ tb_exchange_lite__DOT__dut__DOT__fill_price_val;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<IData/*31:0*/, 4> tb_exchange_lite__DOT__best_bid;
    VlUnpacked<IData/*31:0*/, 4> tb_exchange_lite__DOT__best_ask;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    std::string __Vtask_tb_exchange_lite__DOT__wait_for_fill__2__why;
    std::string __Vtask_tb_exchange_lite__DOT__check__3__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__4__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__5__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__6__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__7__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__8__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__9__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__10__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__11__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__12__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__13__msg;
    std::string __Vtask_tb_exchange_lite__DOT__wait_for_fill__16__why;
    std::string __Vtask_tb_exchange_lite__DOT__check__17__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__18__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__19__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__20__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__21__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__22__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__23__msg;
    std::string __Vtask_tb_exchange_lite__DOT__wait_for_fill__26__why;
    std::string __Vtask_tb_exchange_lite__DOT__check__27__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__28__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__29__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__30__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__31__msg;
    std::string __Vtask_tb_exchange_lite__DOT__wait_for_fill__34__why;
    std::string __Vtask_tb_exchange_lite__DOT__check__35__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__36__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__37__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__38__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__39__msg;
    std::string __Vtask_tb_exchange_lite__DOT__wait_for_fill__42__why;
    std::string __Vtask_tb_exchange_lite__DOT__check__43__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__44__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__45__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__46__msg;
    std::string __Vtask_tb_exchange_lite__DOT__wait_for_fill__49__why;
    std::string __Vtask_tb_exchange_lite__DOT__check__50__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__51__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__52__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__53__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__54__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__55__msg;
    std::string __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__58__why;
    std::string __Vtask_tb_exchange_lite__DOT__check__59__msg;
    std::string __Vtask_tb_exchange_lite__DOT__expect_no_fill_for_cycles__60__why;
    std::string __Vtask_tb_exchange_lite__DOT__check__61__msg;
    std::string __Vtask_tb_exchange_lite__DOT__wait_for_fill__64__why;
    std::string __Vtask_tb_exchange_lite__DOT__check__65__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__66__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__67__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__68__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__69__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__70__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__71__msg;
    std::string __Vtask_tb_exchange_lite__DOT__wait_for_fill__74__why;
    std::string __Vtask_tb_exchange_lite__DOT__check__75__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__76__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__77__msg;
    std::string __Vtask_tb_exchange_lite__DOT__wait_for_fill__80__why;
    std::string __Vtask_tb_exchange_lite__DOT__check__81__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__82__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__83__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__84__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__85__msg;
    std::string __Vtask_tb_exchange_lite__DOT__check__86__msg;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h89ac9348__0;
    VlTriggerScheduler __VtrigSched_h059def81__0;

    // INTERNAL VARIABLES
    Vtb_exchange_lite__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_exchange_lite___024root(Vtb_exchange_lite__Syms* symsp, const char* namep);
    ~Vtb_exchange_lite___024root();
    VL_UNCOPYABLE(Vtb_exchange_lite___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
