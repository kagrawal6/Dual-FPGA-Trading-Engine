#!/usr/bin/env bash
# ==============================================================================
# Run tb_lfsr32 on macOS using Verilator (no ModelSim license needed).
#
# Prereq:  brew install verilator
#
# Produces:  tb_lfsr32.vcd  in the build directory (open with a wave viewer).
#
# Usage:
#   ./scripts/run_lfsr32_mac.sh
#   ./scripts/run_lfsr32_mac.sh --open    # open VCD (Surfer on macOS 14+; GTKWave if old Mac)
# ==============================================================================

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
IMPL_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
OUT_DIR="$IMPL_DIR/sim_work/verilator_lfsr32"

# Prefer Homebrew Verilator on Apple Silicon / Intel Macs
for CAND in verilator /opt/homebrew/bin/verilator /usr/local/bin/verilator; do
  if command -v "$CAND" &>/dev/null; then
    VERILATOR="$CAND"
    break
  fi
done

if [[ -z "${VERILATOR:-}" ]]; then
  echo "Verilator not found. Install with:"
  echo "  brew install verilator"
  exit 1
fi

mkdir -p "$OUT_DIR"
cd "$OUT_DIR"

echo "Using: $($VERILATOR --version | head -1)"
echo "Build dir: $OUT_DIR"

"$VERILATOR" --binary --timing --trace-vcd -Wall -Wno-fatal \
  --Mdir "$OUT_DIR/obj_dir" \
  --top-module tb_lfsr32 \
  -o Vtb_lfsr32 \
  "$IMPL_DIR/rtl/shared/hft_pkg.sv" \
  "$IMPL_DIR/rtl/shared/lfsr32.sv" \
  "$IMPL_DIR/tb/shared/tb_lfsr32.sv"

if [[ -x ./Vtb_lfsr32 ]]; then
  ./Vtb_lfsr32
elif [[ -x ./obj_dir/Vtb_lfsr32 ]]; then
  ./obj_dir/Vtb_lfsr32
else
  echo "Sim executable not found (expected ./Vtb_lfsr32 or ./obj_dir/Vtb_lfsr32)"
  exit 1
fi

VCD="$OUT_DIR/tb_lfsr32.vcd"
echo ""
echo "Done. VCD (waveforms): $VCD"

if [[ "${1:-}" == "--open" ]]; then
  # macOS 14+: Homebrew's gtkwave.app is an old binary; Apple blocks it ("not compatible").
  # Use Surfer instead:  brew install surfer
  SURFER=""
  command -v surfer &>/dev/null && SURFER="$(command -v surfer)"
  [[ -z "$SURFER" && -x /opt/homebrew/bin/surfer ]] && SURFER=/opt/homebrew/bin/surfer
  [[ -z "$SURFER" && -x /usr/local/bin/surfer ]] && SURFER=/usr/local/bin/surfer

  if [[ -n "$SURFER" ]]; then
    echo "Opening VCD with Surfer (macOS 14+ friendly)..."
    nohup "$SURFER" "$VCD" >/tmp/surfer_lfsr32.log 2>&1 &
    disown 2>/dev/null || true
    echo "Surfer launched in background. Log: /tmp/surfer_lfsr32.log"
  elif [[ -d "/Applications/gtkwave.app" ]]; then
    echo "Trying gtkwave.app (may fail on macOS 14+ — prefer: brew install surfer)..."
    open -na gtkwave --args "$VCD" || true
  elif command -v gtkwave &>/dev/null; then
    nohup gtkwave "$VCD" >/tmp/gtkwave_lfsr32.log 2>&1 &
    disown 2>/dev/null || true
    echo "Launched gtkwave in background; log: /tmp/gtkwave_lfsr32.log"
  else
    echo "No wave viewer found. On macOS 14+ install Surfer:"
    echo "  brew install surfer"
    echo "Then:  surfer \"$VCD\""
  fi
fi
