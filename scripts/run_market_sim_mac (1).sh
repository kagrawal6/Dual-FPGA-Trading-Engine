#!/usr/bin/env bash
# ==============================================================================
# Run tb_market_sim on macOS using Verilator.
#
# Usage:
#   ./scripts/run_market_sim_mac.sh
#   ./scripts/run_market_sim_mac.sh --open   # open VCD in Surfer (preferred)
# ==============================================================================

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IMPL_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
OUT_DIR="$IMPL_DIR/sim_work/verilator_market_sim"

# Prefer Homebrew Verilator on Apple Silicon / Intel Macs
for CAND in verilator /opt/homebrew/bin/verilator /usr/local/bin/verilator; do
  if command -v "$CAND" &>/dev/null; then
    VERILATOR="$CAND"
    break
  fi
done

if [[ -z "${VERILATOR:-}" ]]; then
  echo "Verilator not found. Install with: brew install verilator"
  exit 1
fi

mkdir -p "$OUT_DIR"
cd "$OUT_DIR"

echo "Using: $($VERILATOR --version | head -1)"
echo "Build dir: $OUT_DIR"

"$VERILATOR" --binary --timing --trace-vcd -Wall -Wno-fatal \
  --Mdir "$OUT_DIR/obj_dir" \
  --top-module tb_market_sim \
  -o Vtb_market_sim \
  "$IMPL_DIR/rtl/shared/hft_pkg.sv" \
  "$IMPL_DIR/rtl/shared/lfsr32.sv" \
  "$IMPL_DIR/rtl/board_a/market_sim.sv" \
  "$IMPL_DIR/tb/board_a/tb_market_sim.sv"

if [[ -x ./Vtb_market_sim ]]; then
  ./Vtb_market_sim
elif [[ -x ./obj_dir/Vtb_market_sim ]]; then
  ./obj_dir/Vtb_market_sim
else
  echo "Sim executable not found (expected ./Vtb_market_sim or ./obj_dir/Vtb_market_sim)"
  exit 1
fi

VCD="$OUT_DIR/tb_market_sim.vcd"
echo ""
echo "Done. VCD: $VCD"

if [[ "${1:-}" == "--open" ]]; then
  SURFER=""
  command -v surfer &>/dev/null && SURFER="$(command -v surfer)"
  [[ -z "$SURFER" && -x /opt/homebrew/bin/surfer ]] && SURFER=/opt/homebrew/bin/surfer
  [[ -z "$SURFER" && -x /usr/local/bin/surfer ]] && SURFER=/usr/local/bin/surfer

  if [[ -n "$SURFER" ]]; then
    echo "Opening VCD with Surfer..."
    nohup "$SURFER" "$VCD" >/tmp/surfer_market_sim.log 2>&1 &
    disown 2>/dev/null || true
    echo "Surfer launched in background. Log: /tmp/surfer_market_sim.log"
  else
    echo "Surfer not found. Install with: brew install surfer"
    echo "Then open:"
    echo "  surfer \"$VCD\""
  fi
fi

