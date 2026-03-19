#!/usr/bin/env bash
# ==============================================================================
# Run tb_debounce on macOS with Verilator (same pattern as run_lfsr32_mac.sh).
#
# Usage:
#   ./scripts/run_debounce_mac.sh
#   ./scripts/run_debounce_mac.sh --open   # Surfer on macOS 14+
# ==============================================================================

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IMPL_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
OUT_DIR="$IMPL_DIR/sim_work/verilator_debounce"

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
  --top-module tb_debounce \
  -o Vtb_debounce \
  "$IMPL_DIR/rtl/shared/debounce.sv" \
  "$IMPL_DIR/tb/shared/tb_debounce.sv"

if [[ -x ./Vtb_debounce ]]; then
  ./Vtb_debounce
elif [[ -x ./obj_dir/Vtb_debounce ]]; then
  ./obj_dir/Vtb_debounce
else
  echo "Sim executable not found (expected ./Vtb_debounce or ./obj_dir/Vtb_debounce)"
  exit 1
fi

VCD="$OUT_DIR/tb_debounce.vcd"
echo ""
echo "Done. VCD: $VCD"

if [[ "${1:-}" == "--open" ]]; then
  SURFER=""
  command -v surfer &>/dev/null && SURFER="$(command -v surfer)"
  [[ -z "$SURFER" && -x /opt/homebrew/bin/surfer ]] && SURFER=/opt/homebrew/bin/surfer
  if [[ -n "$SURFER" ]]; then
    echo "Opening VCD with Surfer..."
    nohup "$SURFER" "$VCD" >/tmp/surfer_debounce.log 2>&1 &
    disown 2>/dev/null || true
    echo "Log: /tmp/surfer_debounce.log"
  else
    echo "Install Surfer: brew install surfer"
    echo "Then: surfer \"$VCD\""
  fi
fi
