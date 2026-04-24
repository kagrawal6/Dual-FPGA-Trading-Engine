"""
Interactive Board A dashboard (Jupyter / Voilà).

Layout: ~3/4 main (synthetic index + sector lanes + tiles), ~1/4 sidebar
(regime, quote interval, apply / reset, polling).

Price model: software synthetic (see synthetic_prices.py); motion tracks
AXI QUOTES_SENT + regime + configured anchors — not RTL best_bid/best_ask.
"""

from __future__ import annotations

import random
import sys
import threading
import time
from pathlib import Path
from typing import Any, Dict, List, Optional

# ---------------------------------------------------------------------------
# Import Board A symbol helpers (same repo layout: sw/board_a/)
# ---------------------------------------------------------------------------
_BOARD_A = Path(__file__).resolve().parent.parent / "board_a"
if _BOARD_A.is_dir() and str(_BOARD_A) not in sys.path:
    sys.path.insert(0, str(_BOARD_A))

from config_symbols import (  # type: ignore  # noqa: E402
    parse_sector_mix_compact,
    prepare_loaded_symbols,
    sample_tickers_from_sector_allocation,
    validate_sector_allocation,
    write_mmio_board_config,
)
from symbol_universe import ordered_sector_names, tickers_grouped_by_sector  # type: ignore  # noqa: E402

from . import registers as R
from .axi_client import (
    DemoMMIO,
    pulse_reset,
    read_board_snapshot,
    read_init_mids,
    read_init_spreads,
    read_sector_ids,
)
from .synthetic_prices import SyntheticTracker

try:
    import ipywidgets as W
    from IPython.display import display
except ImportError as e:  # pragma: no cover
    W = None  # type: ignore
    display = None  # type: ignore
    _IPY_ERR = str(e)
else:
    _IPY_ERR = ""

try:
    import plotly.graph_objects as go
except ImportError as e:  # pragma: no cover
    go = None  # type: ignore
    _PLOTLY_ERR = str(e)
else:
    _PLOTLY_ERR = ""


# Robinhood-ish dark palette + distinct sector accents (left border)
ACCENT = ("#60a5fa", "#fbbf24", "#34d399", "#f472b6", "#a78bfa", "#94a3b8", "#f87171", "#38bdf8")
BG = "#020617"
CARD = "#0f172a"
TEXT = "#e2e8f0"
MUTED = "#94a3b8"

# Short labels for dropdowns (canonical GICS name -> display)
SECTOR_DISPLAY: Dict[str, str] = {
    "Information Technology": "Tech",
    "Energy": "Energy",
    "Health Care": "Health",
    "Consumer Discretionary": "Cons. Disc.",
    "Financials": "Financials",
    "Industrials": "Industrials",
    "Consumer Staples": "Staples",
    "Communication Services": "Comms",
}


def _sector_dropdown_options() -> List[tuple[str, str]]:
    """(label, canonical_sector_name) for ipywidgets.Dropdown."""
    groups = tickers_grouped_by_sector()
    opts: List[tuple[str, str]] = []
    for nm in ordered_sector_names():
        short = SECTOR_DISPLAY.get(nm, nm[:14])
        n = len(groups[nm])
        opts.append((f"{short} ({n} in pool)", nm))
    return opts


def _sector_label(sid: int) -> str:
    sid = int(sid) & 7
    return R.SECTOR_LABELS[sid] if sid < len(R.SECTOR_LABELS) else f"sector_{sid}"


def _tiles_html(
    loaded: List[dict[str, Any]],
    prices: List[float],
    prev: List[float],
    sectors: List[int],
) -> str:
    lanes: dict[int, list[tuple[int, dict, float, float]]] = {}
    for i, row in enumerate(loaded):
        if i >= len(prices):
            break
        sid = int(sectors[i]) & 7
        lanes.setdefault(sid, []).append((i, row, prices[i], prev[i]))

    parts = [
        f'<div style="background:{BG};color:{TEXT};font-family:system-ui,Segoe UI,sans-serif;padding:4px;">',
        f'<p style="color:{MUTED};font-size:0.8rem;margin:4px 0 8px 0;">'
        "Tiles use a <b>software synthetic</b> price model tied to AXI activity (not exact FPGA quotes).</p>",
    ]
    for sid in sorted(lanes.keys()):
        accent = ACCENT[sid % len(ACCENT)]
        label = _sector_label(sid)
        parts.append(
            f'<div style="margin-bottom:14px;border-radius:10px;padding:8px;background:#0b1224;border:1px solid #1e293b;">'
            f'<div style="font-size:0.85rem;font-weight:600;margin-bottom:6px;border-left:4px solid {accent};padding-left:8px;">{label}</div>'
            f'<div style="display:flex;flex-wrap:wrap;gap:6px;align-items:stretch;">'
        )
        for i, row, p, pr in lanes[sid]:
            d = p - pr
            dc = "#34d399" if d >= 0 else "#f87171"
            tk = row.get("ticker", "?")
            tt = f"{tk} | slot {i} | {_sector_label(sid)}"
            st = (
                f"flex:1 1 120px;min-width:108px;max-width:160px;border-left:4px solid {accent};"
                f"background:{CARD};border-radius:12px;padding:10px 10px 8px 10px;"
                f"box-shadow:0 1px 2px rgba(0,0,0,0.4);"
            )
            parts.append(
                f"<div title='{tt}' style='{st}'>"
                f"<div style='font-size:0.72rem;color:{MUTED};letter-spacing:0.02em;'>{tk}</div>"
                f"<div style='font-size:1.15rem;font-weight:700;margin-top:4px;'>{p:,.2f}</div>"
                f"<div style='font-size:0.82rem;color:{dc};margin-top:2px;'>{d:+.2f}</div>"
                f"<div style='font-size:0.68rem;color:{MUTED};margin-top:6px;'>slot {i}</div></div>"
            )
        parts.append("</div></div>")
    parts.append("</div>")
    return "".join(parts)


class BoardADashboard:
    def __init__(self, mmio: Any, *, hw_slots: int = R.NUM_SYM, poll_hz: float = 5.0) -> None:
        self.mmio = mmio
        self.hw_slots = hw_slots
        self.poll_s = 1.0 / max(0.5, poll_hz)
        self.loaded: List[dict[str, Any]] = []
        self._sectors: List[int] = [0] * hw_slots
        self._prev_prices: List[float] = []
        self.tracker: Optional[SyntheticTracker] = None
        self._poll_thread: Optional[threading.Thread] = None
        self._stop = threading.Event()
        self._fig: Any = None
        self._tiles = None
        self._status = None
        self._index_note = None
        self._sidebar_note = None
        self._num_sectors_dd: Any = None
        self._sector_ui_box: Any = None
        self._sector_rows: List[Dict[str, Any]] = []
        self._adv_mix: Any = None

    def _on_regime_write(self, change: dict) -> None:
        try:
            v = int(change.get("new", 0)) & 0x03
            self.mmio.write(R.REGIME, v)
        except Exception:
            pass

    def _on_qi_write(self, change: dict) -> None:
        try:
            self.mmio.write(R.QUOTE_INTERVAL, int(change.get("new", 1000)) & 0xFFFFFFFF)
        except Exception:
            pass

    def _max_num_sectors(self) -> int:
        return max(1, len(ordered_sector_names()))

    def _rebuild_sector_rows(self, _change: Any = None) -> None:
        if self._sector_ui_box is None or self._num_sectors_dd is None:
            return
        k = int(self._num_sectors_dd.value)
        k = max(1, min(k, self._max_num_sectors()))
        opts = _sector_dropdown_options()
        names = ordered_sector_names()
        rows: List[Dict[str, Any]] = []
        children: List[Any] = []

        if k == 1:
            dd = W.Dropdown(
                options=opts,
                value=names[0],
                layout=W.Layout(flex="2"),
                description="Sector",
            )
            hint = W.HTML(
                "<span style='color:#94a3b8;font-size:0.85rem;'>Uses all <b>16</b> slots in this sector.</span>"
            )
            children.append(W.HBox([dd, hint], layout=W.Layout(width="100%")))
            rows.append({"sector": dd, "count": None, "auto_html": hint, "mode": "single"})
            dd.observe(self._sync_auto_count, "value")
        else:
            for i in range(k - 1):
                dd = W.Dropdown(
                    options=opts,
                    value=names[i % len(names)],
                    layout=W.Layout(flex="2"),
                    description=f"S{i+1}",
                )
                cnt = W.BoundedIntText(
                    min=0,
                    max=16,
                    value=1,
                    layout=W.Layout(width="76px"),
                    description="#",
                )

                def _mk_sync(_c: Any = None, _d: Any = None) -> None:
                    self._sync_auto_count()

                dd.observe(_mk_sync, "value")
                cnt.observe(_mk_sync, "value")
                children.append(W.HBox([dd, cnt], layout=W.Layout(width="100%")))
                rows.append({"sector": dd, "count": cnt, "mode": "manual"})

            dd_last = W.Dropdown(
                options=opts,
                value=names[(k - 1) % len(names)],
                layout=W.Layout(flex="2"),
                description=f"S{k}",
            )
            auto_html = W.HTML("")
            children.append(W.HBox([dd_last, auto_html], layout=W.Layout(width="100%")))
            rows.append({"sector": dd_last, "count": None, "auto_html": auto_html, "mode": "last"})
            dd_last.observe(self._sync_auto_count, "value")

        self._sector_rows = rows
        self._sector_ui_box.children = tuple(children)
        self._sync_auto_count()

    def _sync_auto_count(self, *_args: Any) -> None:
        if not self._sector_rows or self._num_sectors_dd is None:
            return
        k = int(self._num_sectors_dd.value)
        if k == 1:
            return
        groups = tickers_grouped_by_sector()
        manual = 0
        for r in self._sector_rows:
            if r.get("mode") == "manual" and r.get("count") is not None:
                manual += int(r["count"].value)
        auto = self.hw_slots - manual
        last = self._sector_rows[-1]
        ah = last.get("auto_html")
        if ah is None:
            return
        sec = last["sector"].value
        cap = len(groups.get(sec, []))
        ok = auto >= 0 and auto <= cap
        dup = self._duplicate_sector_error()
        color = "#94a3b8"
        if auto < 0 or not ok:
            color = "#f43f5e"
        elif dup:
            color = "#f97316"
        elif ok:
            color = "#4ade80"
        extra = f" &nbsp; <span style='color:#f97316;'>{dup}</span>" if dup else ""
        ah.value = (
            f"<span style='color:{color};font-size:0.82rem;'><b>Last sector count (auto):</b> {auto} "
            f"&nbsp; (pool max: {cap})</span>{extra}"
        )

    def _duplicate_sector_error(self) -> str:
        seen: set[str] = set()
        for r in self._sector_rows:
            s = r["sector"].value
            if s in seen:
                return f"Duplicate sector pick: {SECTOR_DISPLAY.get(s, s)}"
            seen.add(s)
        return ""

    def _allocation_from_widgets(self) -> Dict[str, int]:
        """Build sector_name -> count dict; validates pool sizes and sum == hw_slots."""
        groups = tickers_grouped_by_sector()
        k = int(self._num_sectors_dd.value)
        k = max(1, min(k, self._max_num_sectors()))

        if self._adv_mix is not None and str(self._adv_mix.value).strip():
            return parse_sector_mix_compact(str(self._adv_mix.value).strip(), self.hw_slots)

        if k == 1:
            r0 = self._sector_rows[0]
            alloc = {r0["sector"].value: self.hw_slots}
            validate_sector_allocation(alloc, self.hw_slots, groups)
            return alloc

        alloc: Dict[str, int] = {}
        for r in self._sector_rows[:-1]:
            sec = r["sector"].value
            n = int(r["count"].value)
            if sec in alloc:
                raise ValueError(f"Duplicate sector in rows: {sec}")
            alloc[sec] = n

        last_r = self._sector_rows[-1]
        sec_last = last_r["sector"].value
        auto = self.hw_slots - sum(alloc.values())
        if sec_last in alloc:
            raise ValueError("Last sector matches an earlier row — pick a different sector.")
        if auto < 0:
            raise ValueError(f"Counts too large: need sum of first {k-1} rows ≤ {self.hw_slots} (last would be {auto}).")
        cap = len(groups[sec_last])
        if auto > cap:
            raise ValueError(
                f"Last sector auto count is {auto} but '{sec_last}' only has {cap} symbol(s) in the universe. "
                "Lower earlier counts or change the last sector."
            )
        alloc[sec_last] = auto
        validate_sector_allocation(alloc, self.hw_slots, groups)
        return alloc

    # --- widget tree ---
    def build(self) -> Any:
        if W is None or go is None:
            missing = []
            if W is None:
                missing.append(f"ipywidgets ({_IPY_ERR})")
            if go is None:
                missing.append(f"plotly ({_PLOTLY_ERR})")
            raise ImportError(" + ".join(missing))

        max_sec = self._max_num_sectors()
        low = 2 if max_sec >= 2 else 1
        self._sector_help = W.HTML(
            value="<p style='font-size:0.82rem;color:#94a3b8;margin:0 0 6px 0;'>"
            "<b>1)</b> Pick how many sectors. <b>2)</b> For each row except the last, choose a sector (short name) and a count. "
            f"<b>3)</b> The <b>last</b> row: pick the final sector — its count is computed so the total is <b>{self.hw_slots}</b>. "
            "Green = OK; red/orange = fix counts or change sectors.</p>"
        )
        _ns_opts = [(f"{i} sectors", i) for i in range(low, max_sec + 1)]
        _ns_val = min(3, max_sec) if max_sec >= 3 else max_sec
        if _ns_val < low:
            _ns_val = low
        self._num_sectors_dd = W.Dropdown(
            options=_ns_opts,
            value=_ns_val,
            description="How many",
            layout=W.Layout(width="100%"),
        )
        self._sector_ui_box = W.VBox([], layout=W.Layout(width="100%"))
        self._num_sectors_dd.observe(self._rebuild_sector_rows, "value")

        self._adv_mix = W.Textarea(
            value="",
            layout=W.Layout(width="100%", height="72px"),
            placeholder="Expert only: paste mix, e.g. Tech:8,Energy:2,... (overrides dropdowns if non-empty)",
        )
        _adv_acc = W.Accordion(children=[self._adv_mix])
        _adv_acc.set_title(0, "Advanced: paste sector mix string")

        self._parse_btn = W.Button(description="Parse & pick companies", button_style="info")
        self._preview = W.HTML(value="<i>No allocation yet.</i>")
        self._apply_btn = W.Button(description="Reset + write FPGA + start", button_style="success")
        self._seed = W.IntText(value=42, description="RNG seed")

        self._regime = W.Dropdown(
            options=[(R.REGIME_NAMES[i], i) for i in range(4)],
            value=0,
            description="Regime",
        )
        self._qi = W.IntSlider(value=1000, min=50, max=5000, step=50, description="Quote int.")
        self._poll_toggle = W.ToggleButton(value=False, description="Live poll (5 Hz)", icon="play")
        self._sidebar_note = W.HTML(
            value=f"<p style='font-size:0.78rem;color:#64748b;'>MMIO: "
            f"<code>{type(self.mmio).__name__}</code></p>"
        )

        self._fig = go.FigureWidget(
            data=[
                go.Scatter(
                    y=[],
                    mode="lines",
                    line=dict(color="#38bdf8", width=2),
                    fill="tozeroy",
                    fillcolor="rgba(56,189,248,0.12)",
                )
            ],
            layout=go.Layout(
                paper_bgcolor=BG,
                plot_bgcolor="#0b1224",
                font=dict(color=TEXT, size=11),
                margin=dict(l=36, r=12, t=28, b=28),
                height=220,
                title=dict(text="Synthetic index (mean of display prices)", font=dict(size=13)),
                xaxis=dict(showgrid=False, zeroline=False, showticklabels=False),
                yaxis=dict(showgrid=True, gridcolor="#1e293b", zeroline=False),
            ),
        )

        self._index_note = W.HTML(
            value="<span style='color:#64748b;font-size:0.8rem;'>Correlated with "
            "<b>QUOTES_SENT</b> deltas + regime; anchors from configured mids.</span>"
        )
        self._tiles = W.HTML(value=_tiles_html([], [100.0] * 16, [100.0] * 16, [0] * 16))
        self._status = W.HTML(value="<i>Idle</i>")

        self._parse_btn.on_click(self._on_parse)
        self._apply_btn.on_click(self._on_apply)
        self._poll_toggle.observe(self._on_poll_toggle, "value")
        self._regime.observe(self._on_regime_write, "value")
        self._qi.observe(self._on_qi_write, "value")

        left = W.VBox(
            [
                W.HTML("<h2 style='margin:4px 0;color:#f8fafc;'>Board A — market view</h2>"),
                self._index_note,
                self._fig,
                W.HTML("<h3 style='margin:10px 0 4px 0;color:#cbd5e1;'>Sector lanes</h3>"),
                self._tiles,
                self._status,
            ],
            layout=W.Layout(flex="3", min_width="320px"),
        )

        right = W.VBox(
            [
                W.HTML("<h3 style='margin:4px 0;color:#cbd5e1;'>Configure</h3>"),
                self._sector_help,
                self._num_sectors_dd,
                self._sector_ui_box,
                _adv_acc,
                self._seed,
                self._parse_btn,
                self._preview,
                self._regime,
                self._qi,
                self._apply_btn,
                W.HTML("<hr style='border:0;border-top:1px solid #334155;margin:12px 0;'/>"),
                self._poll_toggle,
                self._sidebar_note,
            ],
            layout=W.Layout(flex="1", min_width="240px", max_width="420px"),
        )

        self._rebuild_sector_rows()

        root = W.HBox(
            [left, right],
            layout=W.Layout(width="100%", align_items="flex-start"),
        )
        return root

    def _on_parse(self, _btn: Any = None) -> None:
        try:
            alloc = self._allocation_from_widgets()
            picks = sample_tickers_from_sector_allocation(alloc, random.Random(int(self._seed.value)))
            loaded = prepare_loaded_symbols(picks, self.hw_slots, allow_truncate=True, init_spread_default=0.1)
            self.loaded = loaded
            self._sectors = [int(x["sector_id"]) for x in loaded]
            lines = [f"<b>{x['ticker']}</b> — {x['sector']} (id {x['sector_id']}) @ {x['init_price']:.2f}" for x in loaded]
            self._preview.value = "<br/>".join(lines[:20]) + (f"<br/><i>… {len(lines)} total</i>" if len(lines) > 20 else "")
        except Exception as e:  # pragma: no cover
            self._preview.value = f"<span style='color:#f43f5e'>{type(e).__name__}: {e}</span>"

    def _on_apply(self, _btn: Any = None) -> None:
        if not self.loaded:
            self._preview.value = "<span style='color:#f97316'>Parse first.</span>"
            return
        try:
            pulse_reset(self.mmio)
            write_mmio_board_config(
                self.mmio,
                self.loaded,
                self.hw_slots,
                write_sector_id=True,
                write_token_id=True,
                init_spread_default=0.1,
                pulse_start=True,
                quote_interval=int(self._qi.value),
                lfsr_seed=0xDEADBEEF,
                regime=int(self._regime.value),
            )
            anchors = [float(x["init_price"]) for x in self.loaded]
            spreads = [float(x["init_spread"]) for x in self.loaded]
            while len(anchors) < self.hw_slots:
                anchors.append(100.0)
                spreads.append(0.1)
            self.tracker = SyntheticTracker(anchors=anchors[: self.hw_slots], spreads=spreads[: self.hw_slots])
            self._prev_prices = []
            self._status.value = "<span style='color:#4ade80'>Applied + started.</span>"
        except Exception as e:  # pragma: no cover
            self._status.value = f"<span style='color:#f43f5e'>{type(e).__name__}: {e}</span>"

    def _on_poll_toggle(self, change: dict) -> None:
        if change.get("new"):
            self._stop.clear()
            self._poll_thread = threading.Thread(target=self._poll_loop, daemon=True)
            self._poll_thread.start()
        else:
            self._stop.set()

    def _poll_loop(self) -> None:
        while not self._stop.is_set():
            try:
                self._tick_once()
            except Exception as e:  # pragma: no cover
                self._status.value = f"<span style='color:#f43f5e'>poll: {e}</span>"
            time.sleep(self.poll_s)

    def _tick_once(self) -> None:
        if isinstance(self.mmio, DemoMMIO):
            self.mmio.bump_activity()
        snap = read_board_snapshot(self.mmio)
        if self.tracker is None:
            n = int(self.mmio.read(R.ACTIVE_SYM_COUNT)) & 0xFF
            n = max(1, min(self.hw_slots, n))
            mids = read_init_mids(self.mmio, n)
            spr = read_init_spreads(self.mmio, n)
            self.tracker = SyntheticTracker(anchors=mids, spreads=spr)
            self._prev_prices = list(self.tracker.prices)

        self.tracker.step(int(snap["quotes_sent"]), int(snap["regime"]))
        prices = self.tracker.prices
        if len(self._prev_prices) != len(prices):
            self._prev_prices = list(prices)
        hist = self.tracker.history_index

        self._fig.data[0].y = list(hist)
        self._fig.data[0].x = list(range(len(hist)))

        if self.loaded:
            self._tiles.value = _tiles_html(self.loaded, prices, self._prev_prices, self._sectors)
        else:
            n = max(1, min(self.hw_slots, int(self.mmio.read(R.ACTIVE_SYM_COUNT)) & 0xFF))
            sectors = read_sector_ids(self.mmio, n)
            pseudo = [{"ticker": f"slot{i}"} for i in range(n)]
            self._tiles.value = _tiles_html(pseudo, prices[:n], self._prev_prices[:n], sectors)

        self._prev_prices = list(prices)

        rs = "RUN" if snap["running"] else "STOP"
        self._status.value = (
            f"<span style='color:#94a3b8;font-size:0.85rem;'>"
            f"{rs} | regime <b>{snap['regime_name']}</b> | quotes <b>{snap['quotes_sent']}</b> | "
            f"orders <b>{snap['orders_rcvd']}</b> | fifo <b>{snap['fifo_fill']}</b>"
            f"</span>"
        )


def open_mmio_from_overlay(ol: Any, ip_name: str = "hft_core") -> Any:
    base = ol.ip_dict[ip_name]["phys_addr"]
    span = ol.ip_dict[ip_name]["addr_range"]
    from pynq import MMIO  # type: ignore

    return MMIO(base, span)


def create_demo_dashboard(**kwargs: Any) -> BoardADashboard:
    return BoardADashboard(DemoMMIO(), **kwargs)


def show(dashboard: BoardADashboard) -> None:
    if display is None:
        raise RuntimeError("IPython display not available")
    display(dashboard.build())


def sector_mix_cheat_sheet() -> str:
    names = ordered_sector_names()
    groups = tickers_grouped_by_sector()
    lines = ["<ul style='font-size:0.85rem;color:#94a3b8;'>"]
    for nm in names:
        lines.append(f"<li><b>{nm}</b> — {len(groups[nm])} symbols</li>")
    lines.append("</ul>")
    return "".join(lines)
