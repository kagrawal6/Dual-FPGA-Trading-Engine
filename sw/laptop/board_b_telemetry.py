#!/usr/bin/env python3
"""
Board B telemetry readers (no Dash dependency)
============================================

This module exists so the React FastAPI server can reuse the exact same UART/demo
ingest logic as the Dash dashboard, without requiring `dash` / `plotly` to be
installed in the Python environment.

Exports:
- SerialTelemetryReader
- DemoTelemetryReader
- constants used by the frontend meta API (symbols, histogram sizing, timing)
"""

from __future__ import annotations

import json
import math
import threading
import time
from collections import deque
from typing import Any, Deque, Dict, List, Optional, Tuple

try:
    import serial  # type: ignore
except ImportError:  # pragma: no cover
    serial = None  # type: ignore

NUM_SYMBOLS = 16
NUM_HIST_BINS = 16
HIST_BIN_CYCLES = 32
NS_PER_CYCLE = 10
DEFAULT_HISTORY_SEC = 120.0

SYMBOL_NAMES: List[str] = [
    "AAPL",
    "MSFT",
    "GOOG",
    "META",
    "NVDA",
    "AMD",
    "INTC",
    "AVGO",
    "AMZN",
    "TSLA",
    "JPM",
    "GS",
    "JNJ",
    "PFE",
    "XOM",
    "CVX",
]

REGIME_LABELS = ("CALM", "VOLATILE", "BURST", "ADVERSARIAL")


def dollars_to_cash_regs(dollars: float) -> Tuple[int, int]:
    """Return (lo, hi) for signed Q32.16 cash."""
    x = int(round(float(dollars) * (1 << 16)))
    x &= (1 << 48) - 1
    lo = x & 0xFFFFFFFF
    hi = (x >> 32) & 0xFFFFFFFF
    return lo, hi


class SerialTelemetryReader(threading.Thread):
    def __init__(self, port: str, baud: int):
        super().__init__(daemon=True)
        self._port = port
        self._baud = baud
        self._lock = threading.Lock()
        self._ser: Optional[serial.Serial] = None
        self._stop = threading.Event()

        self.connected = False
        self.parse_errors = 0
        self.last_mono: float = 0.0
        self.latest: Dict[str, Any] = {}
        self.rates = {"q": 0.0, "o": 0.0, "f": 0.0, "rej": 0.0}
        self.heartbeat: int = 0

        self._events: Deque[Dict[str, Any]] = deque(maxlen=120)
        self._last_regime_name: str = ""
        self._last_regime_id: int = -1
        self._last_regime_changes: Optional[int] = None
        self._regime_edge_pending: bool = False

        self._last_snapshot_hb: int = 0
        self._stall_snapshot_count: int = 0
        self.hardware_stalled: bool = False

        self._prev_mono: float = 0.0
        self._prev: Dict[str, int] = {}

        self.history_t: Deque[float] = deque(maxlen=8000)
        self.history_cash: Deque[float] = deque(maxlen=8000)
        self.history_pnl: Deque[float] = deque(maxlen=8000)
        self.history_port: Deque[float] = deque(maxlen=8000)
        self.history_rej: Deque[float] = deque(maxlen=8000)

        self.history_rate_q: Deque[float] = deque(maxlen=8000)
        self.history_rate_o: Deque[float] = deque(maxlen=8000)
        self.history_rate_f: Deque[float] = deque(maxlen=8000)
        self.history_rate_rej: Deque[float] = deque(maxlen=8000)
        self.history_lat_last: Deque[float] = deque(maxlen=8000)

        self.sym_history_t: Deque[float] = deque(maxlen=1200)
        self.sym_history_mid: List[Deque[float]] = [deque(maxlen=1200) for _ in range(NUM_SYMBOLS)]
        self.sym_history_ema: List[Deque[float]] = [deque(maxlen=1200) for _ in range(NUM_SYMBOLS)]

    def stop(self) -> None:
        self._stop.set()
        if self._ser and self._ser.is_open:
            try:
                self._ser.close()
            except Exception:
                pass

    def open_serial(self) -> bool:
        if serial is None:  # pragma: no cover
            with self._lock:
                self._ser = None
                self.connected = False
            return False
        with self._lock:
            if self._ser and self._ser.is_open:
                try:
                    self._ser.close()
                except Exception:
                    pass
            self._ser = None
            self.connected = False
        try:
            ser = serial.Serial(self._port, self._baud, timeout=0.5)
            with self._lock:
                self._ser = ser
                self.connected = True
            return True
        except Exception:
            with self._lock:
                self._ser = None
                self.connected = False
            return False

    def ingest(self, data: Dict[str, Any]) -> bool:
        """
        Ingest one JSON-like telemetry dict from a non-serial source (e.g. notebook / HTTP).

        Returns True if accepted.
        """
        if not isinstance(data, dict):
            return False
        # Treat external ingest as "connected" so the UI doesn't show a stale disconnect.
        with self._lock:
            self.connected = True
        try:
            self._ingest(data)
            return True
        except Exception:
            with self._lock:
                self.parse_errors += 1
            return False

    def pop_regime_edge(self) -> bool:
        with self._lock:
            e = self._regime_edge_pending
            self._regime_edge_pending = False
            return e

    def snapshot(self) -> Tuple[Dict[str, Any], Dict[str, float], float, bool, int]:
        with self._lock:
            age_ms = (time.monotonic() - self.last_mono) * 1000 if self.last_mono else 1e9
            if self.connected and self.last_mono:
                if self.heartbeat == self._last_snapshot_hb and self.heartbeat != 0:
                    self._stall_snapshot_count += 1
                else:
                    self._stall_snapshot_count = 0
                self._last_snapshot_hb = self.heartbeat
                self.hardware_stalled = self._stall_snapshot_count >= 3
            else:
                self.hardware_stalled = False

            return dict(self.latest), dict(self.rates), age_ms, self.connected, self.heartbeat

    def events_snapshot(self) -> List[Dict[str, Any]]:
        with self._lock:
            return list(self._events)

    def symbol_series(self, sym_idx: int) -> Tuple[List[float], List[float], List[float]]:
        with self._lock:
            t = list(self.sym_history_t)
            mid = list(self.sym_history_mid[sym_idx])
            ema = list(self.sym_history_ema[sym_idx])
        n = min(len(t), len(mid), len(ema))
        return t[-n:], mid[-n:], ema[-n:]

    def history_arrays(self, window_sec: float) -> Tuple[List[float], List[float], List[float]]:
        cutoff = time.monotonic() - window_sec
        t_list: List[float] = []
        c_list: List[float] = []
        r_list: List[float] = []
        with self._lock:
            for t, c, rr in zip(self.history_t, self.history_cash, self.history_rej):
                if t >= cutoff:
                    t_list.append(t)
                    c_list.append(c)
                    r_list.append(rr)
        if t_list:
            t0 = t_list[0]
            t_rel = [x - t0 for x in t_list]
        else:
            t_rel = []
        return t_rel, c_list, r_list

    def history_profit_arrays(self, window_sec: float) -> Tuple[List[float], List[float], List[float], List[float]]:
        cutoff = time.monotonic() - window_sec
        t_list: List[float] = []
        cash_list: List[float] = []
        pnl_list: List[float] = []
        port_list: List[float] = []
        with self._lock:
            for t, cash, pnl, port in zip(self.history_t, self.history_cash, self.history_pnl, self.history_port):
                if t >= cutoff:
                    t_list.append(t)
                    cash_list.append(cash)
                    pnl_list.append(pnl)
                    port_list.append(port)
        if t_list:
            t0 = t_list[0]
            t_rel = [x - t0 for x in t_list]
        else:
            t_rel = []
        return t_rel, cash_list, pnl_list, port_list

    def history_activity_arrays(self, window_sec: float) -> Tuple[List[float], List[float], List[float], List[float], List[float]]:
        cutoff = time.monotonic() - window_sec
        t_list: List[float] = []
        q_list: List[float] = []
        o_list: List[float] = []
        f_list: List[float] = []
        r_list: List[float] = []
        with self._lock:
            for t, q, o, f, r in zip(
                self.history_t,
                self.history_rate_q,
                self.history_rate_o,
                self.history_rate_f,
                self.history_rate_rej,
            ):
                if t >= cutoff:
                    t_list.append(t)
                    q_list.append(q)
                    o_list.append(o)
                    f_list.append(f)
                    r_list.append(r)
        if t_list:
            t0 = t_list[0]
            t_rel = [x - t0 for x in t_list]
        else:
            t_rel = []
        return t_rel, q_list, o_list, f_list, r_list

    def apply_demo_risk_overrides(self, d: Dict[str, Any]) -> str:
        _ = d
        return (
            "Read-only from the laptop: JSON is one-way over serial. "
            "Change risk/strategy on the PYNQ host, then reconnect."
        )

    def _rate(self, key: str, now: int, dt: float) -> float:
        prev = self._prev.get(key)
        self._prev[key] = now
        if prev is None or dt <= 1e-6:
            return 0.0
        return max(0.0, float(now - prev) / dt)

    def _ingest(self, data: Dict[str, Any]) -> None:
        now_mono = time.monotonic()
        dt = now_mono - self._prev_mono if self._prev_mono else 0.0
        self._prev_mono = now_mono

        # Optional: allow the upstream telemetry source to override symbol names.
        # If Board A (or any upstream) streams a symbol list, the React UI can follow along.
        sym_names = data.get("symbol_names") or data.get("symbols")
        if isinstance(sym_names, list):
            cleaned: List[str] = []
            for x in sym_names[:NUM_SYMBOLS]:
                s = str(x).strip().upper()
                if not s or s == "NONE" or s == "?":
                    s = "—"
                cleaned.append(s)
            if len(cleaned) == NUM_SYMBOLS and all(isinstance(x, str) for x in cleaned):
                with self._lock:
                    SYMBOL_NAMES[:] = cleaned

        # Prefer explicit rates if present; else derive from cumulative counters.
        qps = data.get("qps")
        ops = data.get("ops")
        fps = data.get("fps")
        rej = data.get("rej")

        if qps is None:
            qps = self._rate("q", int(data.get("q", 0) or 0), dt)
        if ops is None:
            ops = self._rate("o", int(data.get("o", 0) or 0), dt)
        if fps is None:
            fps = self._rate("f", int(data.get("f", 0) or 0), dt)
        if rej is None:
            rej = self._rate("rej", int(data.get("rej", 0) or 0), dt)

        cash = float(data.get("cash", 0.0) or 0.0)
        port = float(data.get("port_value", 0.0) or 0.0)
        pnl = float(data.get("total_pnl", 0.0) or 0.0)
        last_lat = float(data.get("last_latency", 0.0) or 0.0)

        # Regime edge detection (id/name or monotonic counter).
        nm = str(data.get("regime_name", "") or "").strip()
        try:
            rid_i = int(data.get("regime", -1))
        except (TypeError, ValueError):
            rid_i = -1
        rc_raw = data.get("regime_changes")
        use_rc = "regime_changes" in data and rc_raw is not None
        if use_rc:
            try:
                rc = int(rc_raw)
                if self._last_regime_changes is not None and rc != self._last_regime_changes:
                    self._regime_edge_pending = True
                self._last_regime_changes = rc
            except (TypeError, ValueError):
                use_rc = False
        if not use_rc:
            if self._last_regime_id >= 0 and rid_i >= 0 and rid_i != self._last_regime_id:
                self._regime_edge_pending = True
            elif self._last_regime_name and nm and nm != self._last_regime_name:
                self._regime_edge_pending = True
        if nm:
            self._last_regime_name = nm
        if rid_i >= 0:
            self._last_regime_id = rid_i

        mid_arr = data.get("mid")
        ema_arr = data.get("ema")
        if isinstance(mid_arr, list) and isinstance(ema_arr, list) and len(mid_arr) >= NUM_SYMBOLS and len(ema_arr) >= NUM_SYMBOLS:
            self.sym_history_t.append(now_mono)
            for i in range(NUM_SYMBOLS):
                try:
                    self.sym_history_mid[i].append(float(mid_arr[i]))
                    self.sym_history_ema[i].append(float(ema_arr[i]))
                except Exception:
                    self.sym_history_mid[i].append(float("nan"))
                    self.sym_history_ema[i].append(float("nan"))

        with self._lock:
            self.last_mono = now_mono
            self.latest = dict(data)
            self.latest["qps"] = float(qps)
            self.latest["ops"] = float(ops)
            self.latest["fps"] = float(fps)
            self.latest["rej"] = float(rej)
            self.rates = {"q": float(qps), "o": float(ops), "f": float(fps), "rej": float(rej)}

            self.heartbeat += 1
            self.history_t.append(now_mono)
            self.history_cash.append(cash)
            self.history_port.append(port)
            self.history_pnl.append(pnl)
            self.history_rej.append(float(rej))
            self.history_rate_q.append(float(qps))
            self.history_rate_o.append(float(ops))
            self.history_rate_f.append(float(fps))
            self.history_rate_rej.append(float(rej))
            self.history_lat_last.append(last_lat)

    def run(self) -> None:
        while not self._stop.is_set():
            ser = None
            with self._lock:
                ser = self._ser
            if not ser or not ser.is_open:
                time.sleep(0.1)
                continue
            try:
                line = ser.readline()
                if not line:
                    continue
                try:
                    s = line.decode("utf-8", errors="ignore").strip()
                    if not s:
                        continue
                    data = json.loads(s)
                    if isinstance(data, dict):
                        self._ingest(data)
                except Exception:
                    with self._lock:
                        self.parse_errors += 1
            except Exception:
                with self._lock:
                    self.connected = False
                time.sleep(0.2)


class DemoTelemetryReader(SerialTelemetryReader):
    """Deterministic synthetic telemetry to exercise the full UI without hardware."""

    def __init__(self) -> None:
        super().__init__("DEMO", 115200)
        self._demo_t0 = time.monotonic()
        self._demo_risk: Dict[str, Any] = {}

    def apply_demo_risk_overrides(self, d: Dict[str, Any]) -> str:
        with self._lock:
            for k, v in d.items():
                if v is None:
                    continue
                self._demo_risk[k] = v
        return "Applied to demo stream only (synthetic telemetry; hardware unchanged)."

    def open_serial(self) -> bool:
        with self._lock:
            self.connected = True
        return True

    def run(self) -> None:
        sig_cycle = ("NONE", "BUY", "SELL", "RISK_BLOCKED")
        while not self._stop.is_set():
            t = time.monotonic() - self._demo_t0
            cash = 10000.0 + 85.0 * math.sin(t * 0.33)
            total_pnl = 420.0 * math.sin(t * 0.11)
            port_value = cash + total_pnl * 0.25

            qps = 8000 + int(t * 18.0) + int(40 * math.sin(t * 0.9))
            ops = 1200 + int(t * 2.4) + int(8 * math.sin(t * 1.1))
            fps = 1100 + int(t * 2.2) + int(7 * math.sin(t * 1.05))
            rej = int(max(0.0, 3.0 * math.sin(t * 0.17)))

            rid = int(t // 22.0) % 4
            rname = REGIME_LABELS[rid]
            regime_changes = int(t // 18.0)

            mid: List[float] = []
            ema: List[float] = []
            pos: List[int] = []
            bid: List[float] = []
            ask: List[float] = []
            spread: List[float] = []
            pnl_cash: List[float] = []
            pnl_mtm: List[float] = []
            last_fill: List[float] = []
            trades: List[int] = []
            signal: List[str] = []
            pos_value: List[float] = []

            for i in range(NUM_SYMBOLS):
                base = 60.0 + 12.0 * i
                m = base + 2.4 * math.sin(t * (0.26 + 0.01 * i))
                e = base + 2.4 * math.sin(t * (0.26 + 0.01 * i) - 0.9)
                p = int(10000 * math.sin(t * (0.05 + 0.008 * i)))
                sp = 0.06 + 0.004 * math.sin(t * 0.4 + i)
                b = m - sp / 2
                a = m + sp / 2

                pc = 250.0 * math.sin(t * (0.11 + 0.01 * i) + i * 0.3)
                pv = p * m / 65536.0

                mid.append(round(m, 4))
                ema.append(round(e, 4))
                pos.append(p)
                bid.append(round(b, 4))
                ask.append(round(a, 4))
                spread.append(round(sp, 4))
                pnl_cash.append(round(pc, 4))
                pnl_mtm.append(round(pc + pv, 4))
                last_fill.append(round(m, 4))
                trades.append(max(0, int(3 * t + i * 2) % 500))
                signal.append(sig_cycle[(i + int(t * 3)) % 4])
                pos_value.append(round(pv, 4))

            hist = [max(0, int(40 * math.exp(-((i - 4) ** 2) / 18.0) + 7 * math.sin(t * 0.7 + i))) for i in range(NUM_HIST_BINS)]
            lat_cnt = max(1, int(200 + t * 4))
            lat_sum = int(450000 * lat_cnt / 200)
            lat_min = 10
            lat_max = 180

            data: Dict[str, Any] = {
                "state": "B_TRADING",
                "link_up": True,
                "risk_halt": False,
                "strategy": "MEAN_REV",
                "threshold": float(self._demo_risk.get("threshold", 1.0)),
                "max_position": int(self._demo_risk.get("max_position", 10000)),
                "max_order_rate": int(self._demo_risk.get("max_order_rate", 1000)),
                "max_loss": float(self._demo_risk.get("max_loss", -1000)),
                "base_qty": int(self._demo_risk.get("base_qty", 100)),
                "qps": qps,
                "ops": ops,
                "fps": fps,
                "rej": rej,
                "link_err": 0,
                "cash": round(cash, 4),
                "total_pnl": round(total_pnl, 4),
                "port_value": round(port_value, 4),
                "pos": pos,
                "bid": bid,
                "ask": ask,
                "mid": mid,
                "spread": spread,
                "ema": ema,
                "signal": signal,
                "pnl_cash": pnl_cash,
                "pnl_mtm": pnl_mtm,
                "pos_value": pos_value,
                "last_fill": last_fill,
                "trades": trades,
                "hist": hist,
                "lat_min": lat_min,
                "lat_max": lat_max,
                "lat_sum": lat_sum,
                "lat_cnt": lat_cnt,
                "last_latency": int(40 + 35 * math.sin(t * 1.7)),
                "regime": rid,
                "regime_name": rname,
                "regime_changes": regime_changes,
            }
            self._ingest(data)
            time.sleep(0.22)


class HttpIngestTelemetryReader(SerialTelemetryReader):
    """
    Reader that receives telemetry via explicit `ingest()` calls (no UART).

    Intended for driving the React UI from a notebook or another process that can POST JSON.
    """

    def __init__(self) -> None:
        super().__init__("HTTP_INGEST", 0)

    def open_serial(self) -> bool:
        with self._lock:
            self.connected = True
        return True

    def run(self) -> None:
        # Nothing to read; the producer pushes via `ingest()`.
        while not self._stop.is_set():
            time.sleep(0.25)

