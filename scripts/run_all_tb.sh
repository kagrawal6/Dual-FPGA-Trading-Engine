#!/usr/bin/env bash
# Build and run all Verilator testbenches. hft_pkg.sv must be first in compile order.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

FAIL=0
PASS=0

rtl_files() {
  echo "$ROOT/rtl/shared/hft_pkg.sv"
  find "$ROOT/rtl" -name '*.sv' ! -name 'hft_pkg.sv' | sort
}

run_one() {
  local top="$1"
  local tb_file="$2"
  local extra="${3:-}"
  local dir="$ROOT/build/verilator/$top"
  mkdir -p "$dir"

  local -a files=()
  while IFS= read -r f; do files+=("$f"); done < <(rtl_files)
  [[ -n "$extra" ]] && files+=("$extra")
  files+=("$tb_file")

  echo "======================================== $top"
  if ! verilator --binary --timing --Wno-fatal -j 0 -Mdir "$dir" --top-module "$top" "${files[@]}" \
      >"$dir/build.log" 2>&1; then
    echo "BUILD FAIL $top"
    tail -25 "$dir/build.log"
    FAIL=$((FAIL + 1))
    return 0
  fi
  if ! "$dir/V$top" >"$dir/run.log" 2>&1; then
    echo "RUN FAIL $top (non-zero exit)"
    tail -30 "$dir/run.log"
    FAIL=$((FAIL + 1))
    return 0
  fi
  if grep -q "FAIL (" "$dir/run.log" || grep -qE '%Error|^\s*FAIL:' "$dir/run.log"; then
    echo "SIM FAIL $top"
    tail -20 "$dir/run.log"
    FAIL=$((FAIL + 1))
    return 0
  fi
  tail -4 "$dir/run.log"
  PASS=$((PASS + 1))
}

run_one tb_market_sim           "$ROOT/tb/board_a/tb_market_sim.sv"
run_one tb_exchange_lite        "$ROOT/tb/board_a/tb_exchange_lite.sv"
run_one tb_tx_arbiter           "$ROOT/tb/board_a/tb_tx_arbiter.sv"
run_one tb_link_rx              "$ROOT/tb/link/tb_link_rx.sv"
run_one tb_link_tx              "$ROOT/tb/link/tb_link_tx.sv"
run_one tb_sync_fifo            "$ROOT/tb/shared/tb_sync_fifo.sv"
run_one tb_link_loopback        "$ROOT/tb/link/tb_link_loopback.sv"
run_one tb_debounce             "$ROOT/tb/shared/tb_debounce.sv"
run_one tb_lfsr32               "$ROOT/tb/shared/tb_lfsr32.sv"
run_one tb_board_a_ctrl         "$ROOT/tb/board_a/tb_board_a_ctrl.sv"
run_one tb_board_a_top          "$ROOT/tb/board_a/tb_board_a_top.sv"
run_one tb_market_noise_gen     "$ROOT/tb/board_a/tb_market_noise_gen.sv"
run_one tb_system_top           "$ROOT/tb/tb_system_top.sv" "$ROOT/tb/stubs/board_b_top_stub.sv"

run_one tb_quote_book           "$ROOT/tb/board_b/tb_quote_book.sv"
run_one tb_msg_demux            "$ROOT/tb/board_b/tb_msg_demux.sv"
run_one tb_board_b_ctrl         "$ROOT/tb/board_b/tb_board_b_ctrl.sv"
run_one tb_board_b_pipeline     "$ROOT/tb/board_b/tb_board_b_pipeline.sv"
run_one tb_board_b_top          "$ROOT/tb/board_b/tb_board_b_top.sv"
run_one tb_feature_compute      "$ROOT/tb/board_b/tb_feature_compute.sv"
run_one tb_strategy_engine      "$ROOT/tb/board_b/tb_strategy_engine.sv"
run_one tb_risk_manager         "$ROOT/tb/board_b/tb_risk_manager.sv"
run_one tb_order_manager        "$ROOT/tb/board_b/tb_order_manager.sv"
run_one tb_position_tracker     "$ROOT/tb/board_b/tb_position_tracker.sv"
run_one tb_latency_histogram    "$ROOT/tb/board_b/tb_latency_histogram.sv"

echo "========================================"
echo "Done: PASS=$PASS FAIL=$FAIL"
[[ $FAIL -eq 0 ]]
