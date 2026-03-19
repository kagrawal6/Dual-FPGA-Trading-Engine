#!/bin/bash
# ==============================================================================
# HFT Capstone — Regression Test Runner
# Runs all testbenches via Vivado XSIM and reports pass/fail.
# Usage: bash run_regression.sh [--gui] [test_name]
# ==============================================================================

set -e

PROJ_DIR="$(cd "$(dirname "$0")/.." && pwd)"
RTL_DIR="$PROJ_DIR/rtl"
TB_DIR="$PROJ_DIR/tb"
WORK_DIR="$PROJ_DIR/sim_work"

mkdir -p "$WORK_DIR"

# Collect all source files
PKG="$RTL_DIR/shared/hft_pkg.sv"
RTL_FILES=$(find "$RTL_DIR" -name "*.sv" ! -name "hft_pkg.sv" | sort)

# All testbenches
TB_FILES=$(find "$TB_DIR" -name "tb_*.sv" | sort)

PASS=0
FAIL=0
SKIP=0

for TB in $TB_FILES; do
    TB_NAME=$(basename "$TB" .sv)
    echo "──────────────────────────────────────────"
    echo "Running: $TB_NAME"
    echo "──────────────────────────────────────────"

    # Compile
    if xvlog -sv "$PKG" $RTL_FILES "$TB" -work "$WORK_DIR" > /dev/null 2>&1; then
        # Elaborate
        if xelab -debug typical "$TB_NAME" -s "${TB_NAME}_sim" -work "$WORK_DIR" > /dev/null 2>&1; then
            # Simulate
            if xsim "${TB_NAME}_sim" -runall -work "$WORK_DIR" 2>&1 | grep -q "TEST PASSED"; then
                echo "  PASSED"
                ((PASS++))
            else
                echo "  FAILED (simulation)"
                ((FAIL++))
            fi
        else
            echo "  FAILED (elaboration)"
            ((FAIL++))
        fi
    else
        echo "  FAILED (compilation)"
        ((FAIL++))
    fi
done

echo ""
echo "══════════════════════════════════════════"
echo "Results: $PASS passed, $FAIL failed, $SKIP skipped"
echo "══════════════════════════════════════════"

exit $FAIL
