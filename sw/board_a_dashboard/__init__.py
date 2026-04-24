"""Board A interactive Jupyter / Voilà dashboard (synthetic price UX + AXI)."""

from .dashboard_app import (
    BoardADashboard,
    create_demo_dashboard,
    open_mmio_from_overlay,
    sector_mix_cheat_sheet,
    show,
)

__all__ = [
    "BoardADashboard",
    "create_demo_dashboard",
    "open_mmio_from_overlay",
    "sector_mix_cheat_sheet",
    "show",
]
