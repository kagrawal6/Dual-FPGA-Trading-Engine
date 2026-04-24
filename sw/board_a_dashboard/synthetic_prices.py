"""
Software-side synthetic price motion for the dashboard (v1).

Decision: we do NOT mirror exact RTL best_bid/best_ask (those are not on AXI).
Instead we animate display prices that:
  - anchor to configured init mids / spreads,
  - scale motion with active_regime and delta(QUOTES_SENT),
  - mean-revert slightly toward anchors each tick.

This keeps the UI lively and correlated with real FPGA activity without RTL changes.
"""

from __future__ import annotations

import math
from dataclasses import dataclass, field
from typing import List


def _regime_amp(regime: int) -> float:
    return {0: 0.35, 1: 0.75, 2: 1.25, 3: 2.0}.get(regime & 3, 0.5)


@dataclass
class SyntheticTracker:
    """Tracks display prices + a simple synthetic index."""

    anchors: List[float]
    spreads: List[float]
    prices: List[float] = field(default_factory=list)
    last_quotes: int = -1
    history_index: List[float] = field(default_factory=list)

    def __post_init__(self) -> None:
        n = len(self.anchors)
        if len(self.spreads) != n:
            raise ValueError("anchors and spreads length mismatch")
        if not self.prices:
            self.prices = list(self.anchors)
        self.history_index = [float(self.index_value())]

    def index_value(self) -> float:
        return sum(self.prices) / max(1, len(self.prices))

    def step(self, quotes_sent: int, regime: int) -> None:
        dq = 0
        if self.last_quotes >= 0:
            dq = max(0, quotes_sent - self.last_quotes)
        self.last_quotes = quotes_sent

        amp = _regime_amp(regime)
        t = quotes_sent * 0.07

        for i in range(len(self.prices)):
            anchor = self.anchors[i]
            spr = max(self.spreads[i], 0.01)
            # pseudo-random but smooth phase per symbol
            wobble = math.sin(t + i * 1.7) + 0.35 * math.sin(2.3 * t + i * 0.9)
            impulse = (1.0 + 0.45 * dq) * spr * amp * 0.0009 * wobble
            # mean-revert toward anchor
            self.prices[i] = 0.94 * self.prices[i] + 0.06 * anchor + impulse
            self.prices[i] = max(0.01, self.prices[i])

        self.history_index.append(self.index_value())
        if len(self.history_index) > 300:
            self.history_index = self.history_index[-300:]
