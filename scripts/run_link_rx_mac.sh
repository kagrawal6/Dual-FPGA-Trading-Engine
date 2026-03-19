#!/usr/bin/env bash
# ==============================================================================
# Run tb_link_rx on macOS using Verilator (PMOD link receiver unit test).
#
# Usage:
#   ./scripts/run_link_rx_mac.sh
#   ./scripts/run_link_rx_mac.sh --open   # open VCD in Surfer
# ==============================================================================

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IMPL_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
OUT_DIR="$IMPL_DIR/sim_work/verilator_link_rx"

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
  --top-module tb_link_rx \
  -o Vtb_link_rx \
  "$IMPL_DIR/rtl/shared/hft_pkg.sv" \
  "$IMPL_DIR/rtl/link/link_rx.sv" \
  "$IMPL_DIR/tb/link/tb_link_rx.sv"

if [[ -x ./Vtb_link_rx ]]; then
  ./Vtb_link_rx
elif [[ -x ./obj_dir/Vtb_link_rx ]]; then
  ./obj_dir/Vtb_link_rx
else
  echo "Sim executable not found (expected ./Vtb_link_rx or ./obj_dir/Vtb_link_rx)"
  exit 1
fi

VCD="$OUT_DIR/tb_link_rx.vcd"
echo ""
echo "Done. VCD: $VCD"

if [[ "${1:-}" == "--open" ]]; then
  SURFER=""
  command -v surfer &>/dev/null && SURFER="$(command -v surfer)"
  [[ -z "$SURFER" && -x /opt/homebrew/bin/surfer ]] && SURFER=/opt/homebrew/bin/surfer
  [[ -z "$SURFER" && -x /usr/local/bin/surfer ]] && SURFER=/usr/local/bin/surfer

  if [[ -n "$SURFER" ]]; then
    echo "Opening VCD with Surfer..."
    nohup "$SURFER" "$VCD" >/tmp/surfer_link_rx.log 2>&1 &
    disown 2>/dev/null || true
    echo "Surfer launched in background. Log: /tmp/surfer_link_rx.log"
  else
    echo "Surfer not found. Install with: brew install surfer"
    echo "Then open:"
    echo "  surfer \"$VCD\""
  fi
fi

