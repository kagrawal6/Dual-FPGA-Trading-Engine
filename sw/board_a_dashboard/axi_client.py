"""Thin Board A AXI helpers + optional demo MMIO (no hardware)."""

from __future__ import annotations

import time
from typing import Any, Dict

from . import registers as R


def q16_16(val: float) -> int:
    return int(val * 65536) & 0xFFFFFFFF


def from_q16_16(raw: int) -> float:
    return (raw & 0xFFFFFFFF) / 65536.0


def decode_status(raw: int) -> Dict[str, Any]:
    return {
        "running": bool(raw & 0x01),
        "link_up": bool(raw & 0x02),
        "regime": (raw >> 2) & 0x03,
        "regime_name": R.REGIME_NAMES.get((raw >> 2) & 0x03, "?"),
        "fifo_fill": (raw >> 9) & 0x7F,
    }


class DemoMMIO:
    """In-memory registers for UI development without an overlay."""

    def __init__(self) -> None:
        self._mem: Dict[int, int] = {
            R.CTRL: 0,
            R.QUOTE_INTERVAL: 1000,
            R.LFSR_SEED: 0xDEADBEEF,
            R.REGIME: 0,
            R.ACTIVE_SYM_COUNT: R.NUM_SYM,
            R.STATUS: 0,
            R.QUOTES_SENT: 0,
            R.ORDERS_RCVD: 0,
        }
        for i in range(R.NUM_SYM):
            self._mem[R.INIT_MID_BASE + 4 * i] = q16_16(100.0 + i)
            self._mem[R.INIT_SPREAD_BASE + 4 * i] = q16_16(0.1)
            self._mem[R.SECTOR_ID_BASE + 4 * i] = i % 8
        for j in range(R.NUM_SYM // 2):
            self._mem[R.TOKEN_BASE + 4 * j] = (0x1000 + 2 * j + 1) << 16 | (0x1000 + 2 * j)

    def read(self, addr: int) -> int:
        if addr == R.STATUS:
            running = 1 if (self._mem.get(R.STATUS, 0) & 1) else 0
            link_up = 1
            reg = self._mem.get(R.REGIME, 0) & 0x03
            fifo = 0x0A
            return (fifo << 9) | (reg << 2) | (link_up << 1) | running
        return int(self._mem.get(addr, 0))

    def write(self, addr: int, val: int) -> None:
        self._mem[addr] = int(val) & 0xFFFFFFFF
        if addr == R.CTRL:
            st = self._mem.get(R.STATUS, 0)
            if val & 0x01:
                st |= 1
            if val & 0x02:
                st &= ~1
                self._mem[R.QUOTES_SENT] = 0
            self._mem[R.STATUS] = st & 0xFFFFFFFF

    def bump_activity(self) -> None:
        """Advance fake quote counter while 'running' (for demo mode polling)."""
        import random

        if self._mem.get(R.STATUS, 0) & 1:
            self._mem[R.QUOTES_SENT] = min(
                0xFFFF_FFFF, self._mem.get(R.QUOTES_SENT, 0) + random.randint(0, 4)
            )


def read_board_snapshot(mmio: Any) -> Dict[str, Any]:
    raw = mmio.read(R.STATUS)
    st = decode_status(raw)
    st["quotes_sent"] = mmio.read(R.QUOTES_SENT)
    st["orders_rcvd"] = mmio.read(R.ORDERS_RCVD)
    st["raw_status"] = raw
    return st


def read_init_mids(mmio: Any, n: int) -> list[float]:
    out = []
    for i in range(n):
        out.append(from_q16_16(mmio.read(R.INIT_MID_BASE + 4 * i)))
    return out


def read_init_spreads(mmio: Any, n: int) -> list[float]:
    out = []
    for i in range(n):
        raw = mmio.read(R.INIT_SPREAD_BASE + 4 * i)
        out.append(max(from_q16_16(raw), 0.01))
    return out


def read_sector_ids(mmio: Any, n: int) -> list[int]:
    return [mmio.read(R.SECTOR_ID_BASE + 4 * i) & 0x7 for i in range(n)]


def pulse_reset(mmio: Any) -> None:
    mmio.write(R.CTRL, 0x02)
    time.sleep(0.05)


def pulse_start(mmio: Any) -> None:
    mmio.write(R.CTRL, 0x01)
    time.sleep(0.05)
