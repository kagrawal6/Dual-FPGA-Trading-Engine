#!/bin/bash
# Wrapper for live_monitor_term.py on PYNQ 3.x.
#
# Handles the three-headed annoyance:
#   1. /dev/xrt-region* needs root             (so we sudo)
#   2. pynq lives in /usr/local/share/pynq-venv (so we use its python)
#   3. XRT env vars are set in /etc/profile.d  (so we re-source them inside sudo)
#
# Usage:   ./monitor.sh [args forwarded to live_monitor_term.py]
# Example: ./monitor.sh --regime VOLATILE --poll-hz 10
#          ./monitor.sh --no-arm --duration 10

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TARGET="$SCRIPT_DIR/live_monitor_term.py"
PY="/usr/local/share/pynq-venv/bin/python3"

if [ ! -f "$TARGET" ]; then
    echo "ERROR: $TARGET not found" >&2
    exit 1
fi
if [ ! -x "$PY" ]; then
    echo "ERROR: pynq venv python not found at $PY" >&2
    exit 1
fi

# Re-source the PYNQ + XRT env inside sudo, then exec the target.
# Any *.sh under /etc/profile.d that's relevant (pynq_venv.sh, xrt_setup.sh,
# boardname.sh, ...) will be picked up.
exec sudo -H bash -lc '
    for f in /etc/profile.d/pynq_venv.sh /etc/profile.d/xrt_setup.sh /etc/profile.d/*pynq*.sh /etc/profile.d/*xrt*.sh; do
        [ -r "$f" ] && source "$f"
    done
    exec "'"$PY"'" "'"$TARGET"'" "$@"
' _ "$@"
