"""
Jupyter / ipywidgets UI for Board A symbol loading (PYNQ-friendly demo path).

Uses the same validation and MMIO path as config_symbols.py.

Usage (on the board, Jupyter in a browser):

    from symbol_config_panel import show_symbol_config_panel
    show_symbol_config_panel()

Requires: ipywidgets (preinstalled on typical PYNQ images).
"""

from __future__ import annotations

import random
from typing import Any, List

from pynq import MMIO, Overlay

from config_symbols import (
    DEFAULT_HW_SLOTS,
    parse_company_picks,
    parse_sector_mix_lines,
    prepare_loaded_symbols,
    print_configuration_summary,
    sample_tickers_from_sector_allocation,
    write_mmio_board_config,
)
from symbol_universe import SYMBOL_DB


def _random_sample_full_universe(count: int, seed_text: str) -> List[str]:
    universe = sorted(SYMBOL_DB.keys())
    if count > len(universe):
        raise ValueError(f"Count {count} exceeds universe size {len(universe)}.")
    st = seed_text.strip()
    seed: int | None = int(st) if st else None
    rng = random.Random(seed)
    return rng.sample(universe, count)


def show_symbol_config_panel(
    overlay_path: str = "overlays/board_a.bit",
    ip_block: str = "board_a_top_0",
    mmio_length: int = 256,
) -> Any:
    """
    Display an interactive panel. Returns the top-level widget container.
    """
    try:
        import ipywidgets as w
        from IPython.display import display
    except ImportError as e:
        raise ImportError(
            "symbol_config_panel needs Jupyter + ipywidgets. "
            "Install with: pip install ipywidgets  (and jupyter if missing)"
        ) from e

    title = w.HTML("<h3>Board A — symbol load</h3>")
    subtitle = w.HTML(
        f"<p>Universe: <b>{len(SYMBOL_DB)}</b> tickers. "
        f"Default mode: sector mix totaling <b>HW slots</b> (usually 16).</p>"
    )

    mode = w.ToggleButtons(
        options=[
            ("Sector mix", "sector"),
            ("Paste tickers / #rows", "manual"),
            ("Random (full universe)", "random"),
        ],
        description="Mode",
        style={"description_width": "initial"},
    )

    sector_ta = w.Textarea(
        value="Energy 6\nInformation Technology 10",
        placeholder="One line per sector: 'Name count' or 'Name:count'; sum = HW slots",
        description="Sector lines",
        layout=w.Layout(width="100%", height="100px"),
    )
    sector_seed = w.Text(value="", placeholder="optional", description="Seed", layout=w.Layout(width="140px"))
    sector_mix_area = w.VBox(
        [
            w.HTML(
                "<i>Counts must sum to <b>HW slots</b>. Companies are drawn randomly within each sector.</i>"
            ),
            sector_ta,
            sector_seed,
        ]
    )

    manual = w.Textarea(
        value="AAPL MSFT NVDA GOOGL JPM XOM",
        placeholder="Tickers (AAPL) or catalog rows (42 or #42)",
        description="Picks",
        layout=w.Layout(width="100%", height="88px"),
    )

    rnd_seed = w.Text(value="", placeholder="optional", description="Seed", layout=w.Layout(width="200px"))
    random_inner = w.VBox(
        [
            w.HTML(f"<i>Uniform random sample of <b>HW slots</b> companies from all ~{len(SYMBOL_DB)} tickers.</i>"),
            rnd_seed,
        ]
    )

    hw_slots = w.BoundedIntText(
        value=DEFAULT_HW_SLOTS,
        min=1,
        max=32,
        description="HW slots",
    )

    w_quote_interval = w.BoundedIntText(
        value=1000, min=0, max=1_000_000,
        description="Quote interval", style={"description_width": "initial"},
    )
    w_lfsr_seed = w.Text(
        value="0xDEADBEEF", description="LFSR seed",
        style={"description_width": "initial"}, layout=w.Layout(width="200px"),
    )
    w_regime = w.Dropdown(
        options=[("CALM", 0), ("VOLATILE", 1), ("BURST", 2), ("ADVERSARIAL", 3)],
        value=0, description="Regime", style={"description_width": "initial"},
    )

    chk_sector = w.Checkbox(value=True, description="Write sector IDs")
    chk_token = w.Checkbox(value=True, description="Write token IDs")
    chk_start = w.Checkbox(value=True, description="Pulse start (CTRL)")
    chk_truncate = w.Checkbox(value=False, description="Allow truncate if too many tickers")

    apply_btn = w.Button(description="Apply to FPGA", button_style="success", icon="check")
    out = w.Output(layout=w.Layout(border="1px solid #ccc", padding="8px", min_height="120px"))

    def _on_mode_change(change: dict[str, Any]) -> None:
        v = change["new"]
        sector_mix_area.layout.display = None if v == "sector" else "none"
        manual.layout.display = None if v == "manual" else "none"
        random_inner.layout.display = None if v == "random" else "none"

    mode.observe(_on_mode_change, names="value")
    _on_mode_change({"new": mode.value})

    def on_apply(_: Any) -> None:
        with out:
            out.clear_output(wait=True)
            try:
                slots = int(hw_slots.value)
                if mode.value == "sector":
                    alloc = parse_sector_mix_lines(sector_ta.value, slots)
                    st = sector_seed.value.strip()
                    seed: int | None = int(st) if st else None
                    rng = random.Random(seed)
                    selected = sample_tickers_from_sector_allocation(alloc, rng)
                    print("Sector allocation:", dict(sorted(alloc.items())))
                elif mode.value == "manual":
                    selected = parse_company_picks(manual.value)
                else:
                    selected = _random_sample_full_universe(slots, rnd_seed.value)

                loaded = prepare_loaded_symbols(
                    selected,
                    slots,
                    bool(chk_truncate.value),
                    0.125,
                )
                print_configuration_summary(loaded, slots)

                ol = Overlay(overlay_path)
                mmio = MMIO(ol.ip_dict[ip_block]["phys_addr"], mmio_length)
                lfsr_val = int(w_lfsr_seed.value.strip(), 0)
                write_mmio_board_config(
                    mmio,
                    loaded,
                    slots,
                    write_sector_id=bool(chk_sector.value),
                    write_token_id=bool(chk_token.value),
                    init_spread_default=0.125,
                    pulse_start=bool(chk_start.value),
                    quote_interval=int(w_quote_interval.value),
                    lfsr_seed=lfsr_val,
                    regime=int(w_regime.value),
                )
                if chk_start.value:
                    print("Board A started (CTRL pulsed).")
                else:
                    print("Registers written (start not pulsed).")
            except Exception as ex:
                print(f"Error: {ex}")

    apply_btn.on_click(on_apply)

    ui = w.VBox(
        [
            title,
            subtitle,
            mode,
            sector_mix_area,
            manual,
            random_inner,
            hw_slots,
            w.HBox([w_quote_interval, w_lfsr_seed, w_regime]),
            w.HBox([chk_sector, chk_token, chk_start]),
            chk_truncate,
            apply_btn,
            out,
        ]
    )
    display(ui)
    return ui
