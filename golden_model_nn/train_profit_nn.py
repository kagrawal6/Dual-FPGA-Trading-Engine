"""
train_profit_nn.py

Stronger reward-driven policy training for the Dual-FPGA Trading Engine golden model.

What changed versus the first version:
  * larger policy network defaults
  * episode batching before each optimizer step (many full sims per update)
  * adversarial-oversampled regime sampling during training
  * temperature-controlled sampling + entropy regularization
  * small hold penalty to reduce collapse to "always HOLD"
  * evaluation against HOLD and mean-reversion baselines
  * extra diagnostics for action mix and excess PnL over baselines

The policy still learns only HOLD / BUY / SELL. It does NOT replace risk,
fills, or position accounting.
"""

from __future__ import annotations

import argparse
import json
import math
import os
import random
from dataclasses import dataclass
from typing import Optional

import torch
import torch.nn as nn
import torch.optim as optim
from torch.distributions import Categorical

from common import (
    NUM_SYMBOLS,
    NUM_SECTORS,
    MASK_16,
    SIDE_BUY,
    SIDE_SELL,
    Regime,
    MsgType,
    QuoteFrame,
    OrderFrame,
    FillFrame,
    LinkLayer,
    frame_type,
    sext32,
    sext48,
    default_init_mids,
    default_init_spreads,
    default_sector_ids,
)
from board_a import BoardA
from board_b import QuoteBook, FeatureEngine, RiskManager, PositionTracker, BoardB


ACTION_HOLD = 0
ACTION_BUY = 1
ACTION_SELL = 2
ACTION_NAMES = {ACTION_HOLD: "HOLD", ACTION_BUY: "BUY", ACTION_SELL: "SELL"}
REGIME_NAMES = {0: "CALM", 1: "VOLATILE", 2: "BURST", 3: "ADVERSARIAL"}


@dataclass
class Decision:
    order_bits: Optional[int] = None
    log_prob: Optional[torch.Tensor] = None
    entropy: Optional[torch.Tensor] = None
    action: int = ACTION_HOLD
    symbol: Optional[int] = None
    trade_penalty: float = 0.0
    reject_penalty: float = 0.0
    blocked_penalty: float = 0.0
    hold_penalty: float = 0.0
    obs: Optional[torch.Tensor] = None   # feature vector — stored for PPO replay


class ProfitPolicyNet(nn.Module):
    """Moderately larger MLP policy: 9 -> hidden -> hidden -> hidden -> 3 logits."""

    def __init__(self, input_dim: int = 9, hidden_dim: int = 128, hidden_dim2: int = 64, out_dim: int = 3):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, hidden_dim2),
            nn.ReLU(),
            nn.Linear(hidden_dim2, out_dim),
        )

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.net(x)


class ProfitDrivenBoardB:
    """Board B-like wrapper with existing feature / risk / accounting blocks."""

    def __init__(
        self,
        num_sym: int = NUM_SYMBOLS,
        ema_alpha: int = 6554,
        base_qty: int = 100,
        max_position: int = 500,
        max_order_rate: int = 100000,
        max_loss: int = 100000,
        trade_penalty: float = 0.005,
        reject_penalty: float = 0.02,
        blocked_penalty: float = 0.01,
        hold_penalty: float = 0.0002,
        inventory_penalty: float = 0.0005,
    ):
        self.num_sym = num_sym
        self.book = QuoteBook(num_sym)
        self.features = FeatureEngine(num_sym)
        self.risk = RiskManager(num_sym)
        self.positions = PositionTracker(num_sym)

        self.ema_alpha = ema_alpha
        self.base_qty = base_qty
        self.max_position = max_position
        self.max_order_rate = max_order_rate
        self.max_loss = max_loss

        self.trade_penalty = trade_penalty
        self.reject_penalty = reject_penalty
        self.blocked_penalty = blocked_penalty
        self.hold_penalty = hold_penalty
        self.inventory_penalty = inventory_penalty

        self._cycle = 0
        self._next_order_id = 0
        self.last_mid = [None] * num_sym
        self.last_ema = [0] * num_sym
        self.last_quote_regime = [0] * num_sym
        self.last_feature_vec = [[0.0] * 9 for _ in range(num_sym)]
        self.trading = True

        # position tracking for new features
        self.entry_mid = [0] * num_sym          # mid price when position was opened (Q16.16)
        self.quotes_since_entry = [0] * num_sym  # how many quotes arrived while holding

        self.quotes_rcvd = 0
        self.orders_sent = 0
        self.order_blocked = 0
        self.action_counts = {ACTION_HOLD: 0, ACTION_BUY: 0, ACTION_SELL: 0}
        self.init_mid = default_init_mids()[:num_sym]

    def reset(self):
        self.book = QuoteBook(self.num_sym)
        self.features.reset()
        self.risk.reset()
        self.positions.reset()
        self._cycle = 0
        self._next_order_id = 0
        self.last_mid = [None] * self.num_sym
        self.last_ema = [0] * self.num_sym
        self.last_quote_regime = [0] * self.num_sym
        self.last_feature_vec = [[0.0] * 9 for _ in range(self.num_sym)]
        self.entry_mid = [0] * self.num_sym
        self.quotes_since_entry = [0] * self.num_sym
        self.quotes_rcvd = 0
        self.orders_sent = 0
        self.order_blocked = 0
        self.action_counts = {ACTION_HOLD: 0, ACTION_BUY: 0, ACTION_SELL: 0}
        self.trading = True

    def current_mtm(self) -> float:
        cash_dollars = sext48(self.positions.cash) / 65536.0
        unrealized = 0.0
        for i in range(self.num_sym):
            pos = sext32(self.positions.position[i])
            if self.book.bid[i] == 0 and self.book.ask[i] == 0:
                mid = self.init_mid[i]
            else:
                mid = (self.book.bid[i] + self.book.ask[i]) >> 1
            unrealized += pos * (mid / 65536.0)
        return cash_dollars + unrealized

    def _scale_q16(self, val: int, dollars: float, clip: float = 4.0) -> float:
        denom = max(dollars, 1e-6) * 65536.0
        x = sext32(val) / denom
        return max(-clip, min(clip, float(x)))

    def _regime_norm(self, regime: int) -> float:
        return (float(regime) - 1.5) / 1.5

    def _extract_features(self, q: QuoteFrame) -> torch.Tensor:
        sym = q.symbol
        prev_mid = self.last_mid[sym]
        prev_ema = self.features.ema[sym]
        prev_initialized = self.features.initialized[sym]

        self.book.update(q)
        mid = q.mid
        deviation = self.features.compute(sym, mid, self.ema_alpha)
        ema_now = self.features.ema[sym]

        mid_delta = 0 if prev_mid is None else ((mid - prev_mid) & 0xFFFF_FFFF)
        ema_delta = 0 if not prev_initialized else ((ema_now - prev_ema) & 0xFFFF_FFFF)
        if self.max_position > 0:
            position_norm = sext32(self.positions.position[sym]) / float(self.max_position)
        else:
            position_norm = 0.0
        position_norm = max(-4.0, min(4.0, position_norm))

        # feature 7: deviation / spread ratio — how many spreads is the deviation?
        spread_q16 = max(q.spread, 1)
        dev_signed = sext32(deviation)
        dev_spread_ratio = max(-4.0, min(4.0, dev_signed / float(spread_q16)))

        # feature 8: entry price delta — (current mid - entry mid) in spread units
        # positive = position is winning, negative = losing
        pos = sext32(self.positions.position[sym])
        if pos != 0 and self.entry_mid[sym] != 0:
            entry_delta_q16 = (mid - self.entry_mid[sym]) & 0xFFFF_FFFF
            entry_delta_signed = sext32(entry_delta_q16)
            # flip sign for short positions so positive always means winning
            if pos < 0:
                entry_delta_signed = -entry_delta_signed
            entry_price_delta = max(-4.0, min(4.0, entry_delta_signed / float(spread_q16)))
        else:
            entry_price_delta = 0.0

        # feature 9: holding time — quotes received since entry, normalized
        holding_time_norm = min(4.0, self.quotes_since_entry[sym] / 20.0)

        # update holding time counter
        if pos != 0:
            self.quotes_since_entry[sym] += 1
        else:
            self.quotes_since_entry[sym] = 0

        feat = [
            self._scale_q16(deviation, dollars=2.0),
            self._scale_q16(q.spread, dollars=0.50),
            self._scale_q16(mid_delta, dollars=1.00),
            self._scale_q16(ema_delta, dollars=0.50),
            position_norm,
            self._regime_norm(q.regime),
            dev_spread_ratio,
            entry_price_delta,
            holding_time_norm,
        ]

        self.last_mid[sym] = mid
        self.last_ema[sym] = ema_now
        self.last_quote_regime[sym] = q.regime
        self.last_feature_vec[sym] = feat

        return torch.tensor(feat, dtype=torch.float32)

    def _build_order(self, action: int, q: QuoteFrame) -> Optional[OrderFrame]:
        if action == ACTION_BUY:
            return OrderFrame(symbol=q.symbol, side=SIDE_BUY, price=q.ask, qty=self.base_qty)
        if action == ACTION_SELL:
            return OrderFrame(symbol=q.symbol, side=SIDE_SELL, price=q.bid, qty=self.base_qty)
        return None

    def process_frame(
        self,
        cycle: int,
        frame_bits: Optional[int],
        policy: ProfitPolicyNet,
        device: torch.device,
        sample_action: bool,
        temperature: float = 1.0,
    ) -> Decision:
        self._cycle = cycle
        decision = Decision()

        if frame_bits is None:
            return decision

        msg = frame_type(frame_bits)
        if msg == MsgType.FILL:
            fill = FillFrame.from_bits(frame_bits)
            self.positions.process_fill(fill)
            clear_qty = fill.fill_qty if fill.is_filled else self.base_qty
            self.risk.on_fill(fill.symbol, fill.side, clear_qty)
            return decision

        if msg != MsgType.QUOTE:
            return decision

        q = QuoteFrame.from_bits(frame_bits)
        self.quotes_rcvd += 1
        feat = self._extract_features(q).to(device)

        if not self.trading:
            self.action_counts[ACTION_HOLD] += 1
            return decision

        logits = policy(feat.unsqueeze(0)).squeeze(0)
        if sample_action:
            logits = logits / max(float(temperature), 1e-6)
            dist = Categorical(logits=logits)
            action = int(dist.sample().item())
        else:
            eval_logits = logits / max(float(temperature), 1e-6)
            dist = Categorical(logits=eval_logits)
            action = int(dist.sample().item())

        decision.action = action
        decision.symbol = q.symbol
        decision.obs = feat.detach()
        decision.log_prob = dist.log_prob(torch.tensor(action, device=device))
        decision.entropy = dist.entropy()
        self.action_counts[action] += 1

        if action == ACTION_HOLD:
            # only penalise HOLD when flat — don't punish patience while holding
            pos = sext32(self.positions.position[q.symbol])
            if pos == 0:
                decision.hold_penalty += self.hold_penalty
            return decision

        order = self._build_order(action, q)
        if order is None:
            return decision

        approved = self.risk.check(
            order.symbol,
            order.side,
            order.qty,
            self.positions.position,
            self.positions.total_pnl,
            self.max_position,
            self.max_order_rate,
            self.max_loss,
            order_enable=True,
        )
        if not approved:
            decision.reject_penalty += self.reject_penalty
            return decision

        # record entry price when opening or adding to a position
        sym = order.symbol
        prev_pos = sext32(self.positions.position[sym])
        if prev_pos == 0:
            self.entry_mid[sym] = q.mid
            self.quotes_since_entry[sym] = 0

        order.order_id = self._next_order_id & MASK_16
        order.timestamp = self._cycle & MASK_16
        self._next_order_id = (self._next_order_id + 1) & MASK_16
        self.orders_sent += 1
        decision.order_bits = order.to_bits()
        decision.trade_penalty += self.trade_penalty
        return decision


@dataclass
class EpisodeStats:
    regime: int
    seed: int
    final_mtm: float
    avg_reward: float
    orders_sent: int
    fills_rcvd: int
    risk_rejects: int
    blocked: int
    action_counts: dict


class EpisodeTrace:
    def __init__(self):
        self.cycle_rewards: list[float] = []
        self.log_probs: list[torch.Tensor] = []
        self.entropies: list[torch.Tensor] = []
        self.action_time_idxs: list[int] = []
        # PPO extras — stored per action step
        self.obs: list[torch.Tensor] = []        # feature vector at decision time
        self.actions: list[int] = []             # action taken


def set_seed(seed: int):
    random.seed(seed)
    torch.manual_seed(seed)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(seed)


def save_checkpoint(state, is_best, file_folder="./profit_nn_out", filename="checkpoint.pth.tar"):
    os.makedirs(os.path.expanduser(file_folder), exist_ok=True)
    ckpt_path = os.path.join(file_folder, filename)
    torch.save(state, ckpt_path)
    if is_best:
        best_state = dict(state)
        best_state.pop("optimizer", None)
        torch.save(best_state, os.path.join(file_folder, "model_best.pth.tar"))


def build_board_a(num_sym: int, regime: Regime, seed: int) -> BoardA:
    board_a = BoardA(num_sym=num_sym, num_sectors=NUM_SECTORS)
    board_a.configure(
        regime=int(regime),
        quote_interval=0,
        seed=seed,
        init_mid=default_init_mids()[:num_sym],
        init_spread=default_init_spreads()[:num_sym],
        sector_ids=default_sector_ids()[:num_sym],
        active_count=num_sym,
    )
    board_a.start()
    return board_a


def compute_mtm_from_book(bid, ask, positions, cash, init_mid) -> float:
    cash_dollars = sext48(cash) / 65536.0
    unrealized = 0.0
    for i in range(len(init_mid)):
        pos = sext32(positions[i])
        if bid[i] == 0 and ask[i] == 0:
            mid = init_mid[i]
        else:
            mid = (bid[i] + ask[i]) >> 1
        unrealized += pos * (mid / 65536.0)
    return cash_dollars + unrealized


def run_mean_reversion_baseline(args, regime: Regime, seed: int) -> dict:
    board_a = build_board_a(args.num_sym, regime, seed)
    board_b = BoardB(num_sym=args.num_sym)
    board_b.ema_alpha = args.ema_alpha
    board_b.threshold = args.mean_reversion_threshold_q16
    board_b.base_qty = args.base_qty
    board_b.max_position = args.max_position
    board_b.max_order_rate = args.max_order_rate
    board_b.max_loss = args.max_loss
    board_b.start()

    link_ab = LinkLayer(delay=args.link_delay)
    link_ba = LinkLayer(delay=args.link_delay)

    for cycle in range(args.cycles):
        ab_frame = link_ab.receive(cycle)
        ba_frame = link_ba.receive(cycle)

        order_in = None
        if ba_frame is not None and frame_type(ba_frame) == MsgType.ORDER:
            order_in = OrderFrame.from_bits(ba_frame)

        if link_ab.can_send(cycle):
            a_out = board_a.step(cycle, order_in=order_in)
            if a_out is not None:
                link_ab.send(a_out, cycle)
        elif order_in is not None:
            board_a.step(cycle, order_in=order_in)

        b_out = board_b.step(cycle, frame_bits=ab_frame)
        if b_out is not None and link_ba.can_send(cycle):
            link_ba.send(b_out, cycle)

    mtm = compute_mtm_from_book(
        board_b.book.bid,
        board_b.book.ask,
        board_b.positions.position,
        board_b.positions.cash,
        default_init_mids()[: args.num_sym],
    )
    return {
        "final_mtm": mtm,
        "orders": board_b.orders_sent,
        "fills": board_b.positions.fills_rcvd,
        "risk_rejects": board_b.risk.risk_rejects,
    }


def run_episode(
    policy: ProfitPolicyNet,
    device: torch.device,
    args,
    regime: Regime,
    seed: int,
    sample_action: bool,
    temperature: float,
) -> tuple[EpisodeTrace, EpisodeStats]:
    board_a = build_board_a(args.num_sym, regime, seed)
    board_b = ProfitDrivenBoardB(
        num_sym=args.num_sym,
        ema_alpha=args.ema_alpha,
        base_qty=args.base_qty,
        max_position=args.max_position,
        max_order_rate=args.max_order_rate,
        max_loss=args.max_loss,
        trade_penalty=args.trade_penalty,
        reject_penalty=args.reject_penalty,
        blocked_penalty=args.blocked_penalty,
        hold_penalty=args.hold_penalty,
        inventory_penalty=args.inventory_penalty,
    )
    board_b.reset()

    link_ab = LinkLayer(delay=args.link_delay)
    link_ba = LinkLayer(delay=args.link_delay)

    trace = EpisodeTrace()
    prev_mtm = board_b.current_mtm()
    prev_positions = list(board_b.positions.position)  # snapshot for close detection

    for cycle in range(args.cycles):
        ab_frame = link_ab.receive(cycle)
        ba_frame = link_ba.receive(cycle)

        order_in = None
        if ba_frame is not None and frame_type(ba_frame) == MsgType.ORDER:
            order_in = OrderFrame.from_bits(ba_frame)

        if link_ab.can_send(cycle):
            a_out = board_a.step(cycle, order_in=order_in)
            if a_out is not None:
                link_ab.send(a_out, cycle)
        elif order_in is not None:
            board_a.step(cycle, order_in=order_in)

        decision = board_b.process_frame(
            cycle,
            ab_frame,
            policy,
            device,
            sample_action=sample_action,
            temperature=temperature,
        )
        if decision.order_bits is not None:
            if link_ba.can_send(cycle):
                link_ba.send(decision.order_bits, cycle)
            else:
                board_b.order_blocked += 1
                decision.blocked_penalty += board_b.blocked_penalty

        mtm = board_b.current_mtm()

        # compute position-close reward: fire a bonus when a position goes flat
        close_reward = 0.0
        if decision.symbol is not None:
            sym = decision.symbol
            prev_pos = sext32(prev_positions[sym])
            curr_pos = sext32(board_b.positions.position[sym])
            if prev_pos != 0 and curr_pos == 0:
                # position just closed — reward is the actual PnL of that round trip
                # entry_mid was recorded when we opened; current mid is the exit reference
                if board_b.book.bid[sym] != 0 and board_b.book.ask[sym] != 0:
                    exit_mid = (board_b.book.bid[sym] + board_b.book.ask[sym]) >> 1
                else:
                    exit_mid = board_b.init_mid[sym]
                entry_mid = board_b.entry_mid[sym]
                pnl_q16 = (exit_mid - entry_mid) * prev_pos  # Q16.16 * shares
                close_reward = (pnl_q16 / 65536.0) * 0.01   # scale to reward units

        # patience bonus: small reward each quote while holding a winning position
        patience_bonus = 0.0
        for s in range(board_b.num_sym):
            pos = sext32(board_b.positions.position[s])
            if pos != 0 and board_b.entry_mid[s] != 0:
                if board_b.book.bid[s] != 0 and board_b.book.ask[s] != 0:
                    cur_mid = (board_b.book.bid[s] + board_b.book.ask[s]) >> 1
                else:
                    cur_mid = board_b.init_mid[s]
                pnl = (cur_mid - board_b.entry_mid[s]) * pos / 65536.0
                if pnl > 0:
                    patience_bonus += 0.0001  # tiny nudge to stay in winning trades

        # update prev_positions snapshot
        for s in range(board_b.num_sym):
            prev_positions[s] = board_b.positions.position[s]

        if board_b.max_position > 0:
            avg_abs_pos = 0.0
            for s in range(board_b.num_sym):
                avg_abs_pos += abs(sext32(board_b.positions.position[s])) / float(board_b.max_position)
            avg_abs_pos /= max(board_b.num_sym, 1)
        else:
            avg_abs_pos = 0.0
        pos_penalty = board_b.inventory_penalty * avg_abs_pos

        reward = (
            (mtm - prev_mtm)
            + close_reward
            + patience_bonus
            - decision.trade_penalty
            - decision.reject_penalty
            - decision.blocked_penalty
            - decision.hold_penalty
            - pos_penalty
        )
        trace.cycle_rewards.append(float(reward))
        if decision.log_prob is not None:
            trace.log_probs.append(decision.log_prob)
            trace.entropies.append(decision.entropy if decision.entropy is not None else torch.tensor(0.0, device=device))
            trace.action_time_idxs.append(len(trace.cycle_rewards) - 1)
            trace.obs.append(decision.obs)
            trace.actions.append(decision.action)
        prev_mtm = mtm

    avg_reward = sum(trace.cycle_rewards) / max(len(trace.cycle_rewards), 1)
    stats = EpisodeStats(
        regime=int(regime),
        seed=seed,
        final_mtm=board_b.current_mtm(),
        avg_reward=avg_reward,
        orders_sent=board_b.orders_sent,
        fills_rcvd=board_b.positions.fills_rcvd,
        risk_rejects=board_b.risk.risk_rejects,
        blocked=board_b.order_blocked,
        action_counts=dict(board_b.action_counts),
    )
    return trace, stats


def discounted_returns(cycle_rewards: list[float], action_time_idxs: list[int], gamma: float) -> list[float]:
    if not action_time_idxs:
        return []
    returns_from_cycle = [0.0] * len(cycle_rewards)
    running = 0.0
    for t in reversed(range(len(cycle_rewards))):
        running = cycle_rewards[t] + gamma * running
        returns_from_cycle[t] = running
    return [returns_from_cycle[t] for t in action_time_idxs]


def choose_training_regime(rng: random.Random, args) -> Regime:
    weights = [args.train_calm_weight, args.train_volatile_weight, args.train_burst_weight, args.train_adversarial_weight]
    idx = rng.choices([0, 1, 2, 3], weights=weights, k=1)[0]
    return Regime(idx)


@torch.no_grad()
def evaluate_policy(policy: ProfitPolicyNet, device: torch.device, args) -> dict:
    policy.eval()
    per_regime = {}
    all_policy_mtm = []
    all_mr_mtm = []
    all_orders = 0
    all_fills = 0
    all_rejects = 0
    all_blocked = 0
    total_actions = {ACTION_HOLD: 0, ACTION_BUY: 0, ACTION_SELL: 0}

    for regime_int in range(4):
        regime = Regime(regime_int)
        policy_mtms = []
        mr_mtms = []
        orders = fills = rejects = blocked = 0
        action_counts = {ACTION_HOLD: 0, ACTION_BUY: 0, ACTION_SELL: 0}
        for k in range(args.eval_episodes_per_regime):
            seed = args.eval_seed_base + regime_int * 10000 + k
            _, stats = run_episode(policy, device, args, regime, seed, sample_action=False, temperature=args.eval_temperature)
            mr = run_mean_reversion_baseline(args, regime, seed)
            if k == 0:
                print(f"  [baseline debug] regime={regime.name} seed={seed} orders={mr['orders']} fills={mr['fills']} mtm={mr['final_mtm']:+.2f}")

            policy_mtms.append(stats.final_mtm)
            mr_mtms.append(mr["final_mtm"])
            orders += stats.orders_sent
            fills += stats.fills_rcvd
            rejects += stats.risk_rejects
            blocked += stats.blocked
            all_policy_mtm.append(stats.final_mtm)
            all_mr_mtm.append(mr["final_mtm"])
            all_orders += stats.orders_sent
            all_fills += stats.fills_rcvd
            all_rejects += stats.risk_rejects
            all_blocked += stats.blocked
            for a in action_counts:
                action_counts[a] += stats.action_counts.get(a, 0)
                total_actions[a] += stats.action_counts.get(a, 0)

        hold_mtm = 0.0
        per_regime[regime.name] = {
            "avg_mtm": sum(policy_mtms) / max(len(policy_mtms), 1),
            "min_mtm": min(policy_mtms) if policy_mtms else 0.0,
            "max_mtm": max(policy_mtms) if policy_mtms else 0.0,
            "avg_hold_mtm": hold_mtm,
            "avg_mean_reversion_mtm": sum(mr_mtms) / max(len(mr_mtms), 1),
            "avg_excess_vs_hold": (sum(policy_mtms) / max(len(policy_mtms), 1)) - hold_mtm,
            "avg_excess_vs_mean_reversion": (sum(policy_mtms) / max(len(policy_mtms), 1)) - (sum(mr_mtms) / max(len(mr_mtms), 1)),
            "orders": orders,
            "fills": fills,
            "risk_rejects": rejects,
            "blocked": blocked,
            "action_counts": action_counts,
        }

    action_total = sum(total_actions.values())
    if action_total > 0:
        action_mix = {ACTION_NAMES[a]: total_actions[a] / action_total for a in total_actions}
    else:
        action_mix = {ACTION_NAMES[a]: 0.0 for a in total_actions}

    avg_policy = sum(all_policy_mtm) / max(len(all_policy_mtm), 1)
    avg_mr = sum(all_mr_mtm) / max(len(all_mr_mtm), 1)
    return {
        "avg_mtm": avg_policy,
        "min_mtm": min(all_policy_mtm) if all_policy_mtm else 0.0,
        "max_mtm": max(all_policy_mtm) if all_policy_mtm else 0.0,
        "avg_hold_mtm": 0.0,
        "avg_mean_reversion_mtm": avg_mr,
        "avg_excess_vs_hold": avg_policy,
        "avg_excess_vs_mean_reversion": avg_policy - avg_mr,
        "orders": all_orders,
        "fills": all_fills,
        "risk_rejects": all_rejects,
        "blocked": all_blocked,
        "action_mix": action_mix,
        "per_regime": per_regime,
    }


def format_eval_summary(summary: dict) -> str:
    lines = []
    mix = summary.get("action_mix", {})
    lines.append(
        f"eval policy avg_mtm={summary['avg_mtm']:+.2f} | hold={summary['avg_hold_mtm']:+.2f} | "
        f"mean_rev={summary['avg_mean_reversion_mtm']:+.2f} | excess_vs_mr={summary['avg_excess_vs_mean_reversion']:+.2f} | "
        f"orders={summary['orders']} | fills={summary['fills']} | risk_rejects={summary['risk_rejects']} | blocked={summary['blocked']}"
    )
    lines.append(
        f"  action_mix HOLD={mix.get('HOLD', 0.0):.3f} BUY={mix.get('BUY', 0.0):.3f} SELL={mix.get('SELL', 0.0):.3f}"
    )
    for regime_name, reg in summary["per_regime"].items():
        amix = reg.get("action_counts", {})
        atot = max(sum(amix.values()), 1)
        lines.append(
            f"  {regime_name:11s} policy={reg['avg_mtm']:+.2f} hold={reg['avg_hold_mtm']:+.2f} mr={reg['avg_mean_reversion_mtm']:+.2f} "
            f"excess_vs_mr={reg['avg_excess_vs_mean_reversion']:+.2f} orders={reg['orders']} fills={reg['fills']} rejects={reg['risk_rejects']} blocked={reg['blocked']} "
            f"mix(H/B/S)=({amix.get(ACTION_HOLD,0)/atot:.2f}/{amix.get(ACTION_BUY,0)/atot:.2f}/{amix.get(ACTION_SELL,0)/atot:.2f})"
        )
    return "\n".join(lines)


def train(args):
    set_seed(args.seed)
    device = torch.device("cuda" if torch.cuda.is_available() and not args.cpu else "cpu")
    rng = random.Random(args.seed)

    policy = ProfitPolicyNet(input_dim=args.input_dim, hidden_dim=args.hidden_dim, hidden_dim2=args.hidden_dim2, out_dim=3).to(device)
    optimizer = optim.Adam(policy.parameters(), lr=args.lr, weight_decay=args.weight_decay)

    best_avg_mtm = -float("inf")
    best_excess_vs_mr = -float("inf")
    episodes_since_improvement = 0
    start_episode = 0

    if args.resume:
        if not os.path.isfile(args.resume):
            raise FileNotFoundError(f"Checkpoint not found: {args.resume}")
        checkpoint = torch.load(args.resume, map_location=device)
        policy.load_state_dict(checkpoint["state_dict"])
        if "optimizer" in checkpoint and not args.eval_only:
            optimizer.load_state_dict(checkpoint["optimizer"])
        start_episode = int(checkpoint.get("episode", 0))
        best_avg_mtm = float(checkpoint.get("best_avg_mtm", best_avg_mtm))
        best_excess_vs_mr = float(checkpoint.get("best_excess_vs_mr", best_excess_vs_mr))
        print(f"Loaded checkpoint '{args.resume}' (episode {start_episode}, best_avg_mtm={best_avg_mtm:+.2f}, best_excess_vs_mr={best_excess_vs_mr:+.2f})")

    if args.eval_only:
        summary = evaluate_policy(policy, device, args)
        print(format_eval_summary(summary))
        return

    os.makedirs(args.output_dir, exist_ok=True)
    history = []
    print(f"Training on device: {device} | algorithm: PPO clip={args.ppo_clip} epochs={args.ppo_epochs}")

    temperature = args.train_temperature

    for episode in range(start_episode, args.episodes):
        regime = choose_training_regime(rng, args)
        seed = args.seed_base + rng.randrange(1_000_000_000)
        policy.train()
        trace, stats = run_episode(policy, device, args, regime, seed, sample_action=True, temperature=temperature)

        loss_value = float("nan")
        if trace.log_probs and trace.obs:
            returns = discounted_returns(trace.cycle_rewards, trace.action_time_idxs, args.gamma)
            returns_t = torch.tensor(returns, dtype=torch.float32, device=device)
            if args.normalize_returns and len(returns) > 1:
                std = returns_t.std(unbiased=False)
                if std.item() > 1e-8:
                    returns_t = (returns_t - returns_t.mean()) / (std + 1e-8)
                else:
                    returns_t = returns_t - returns_t.mean()

            # old log probs from rollout — detach so they are fixed reference
            old_log_probs_t = torch.stack(trace.log_probs).detach()
            obs_t = torch.stack(trace.obs)                          # (T, 9)
            actions_t = torch.tensor(trace.actions, dtype=torch.long, device=device)  # (T,)

            # PPO update: multiple epochs over the same rollout batch
            for ppo_epoch in range(args.ppo_epochs):
                # shuffle minibatches
                perm = torch.randperm(len(actions_t), device=device)
                batch_size = max(1, args.ppo_batch_size)
                epoch_losses = []
                for start in range(0, len(perm), batch_size):
                    idx = perm[start: start + batch_size]
                    obs_b = obs_t[idx]
                    act_b = actions_t[idx]
                    ret_b = returns_t[idx]
                    old_lp_b = old_log_probs_t[idx]

                    logits_b = policy(obs_b)
                    dist_b = Categorical(logits=logits_b)
                    new_lp_b = dist_b.log_prob(act_b)
                    entropy_b = dist_b.entropy().mean()

                    # PPO clipped objective
                    ratio = torch.exp(new_lp_b - old_lp_b)
                    surr1 = ratio * ret_b
                    surr2 = torch.clamp(ratio, 1.0 - args.ppo_clip, 1.0 + args.ppo_clip) * ret_b
                    policy_loss = -torch.min(surr1, surr2).mean()
                    loss = policy_loss - args.entropy_coef * entropy_b

                    optimizer.zero_grad()
                    loss.backward()
                    if args.grad_clip > 0:
                        torch.nn.utils.clip_grad_norm_(policy.parameters(), args.grad_clip)
                    optimizer.step()
                    epoch_losses.append(float(loss.item()))

            loss_value = sum(epoch_losses) / max(len(epoch_losses), 1)

        row = {
            "episode": episode + 1,
            "regime": regime.name,
            "seed": seed,
            "final_mtm": stats.final_mtm,
            "avg_reward": stats.avg_reward,
            "orders_sent": stats.orders_sent,
            "fills_rcvd": stats.fills_rcvd,
            "risk_rejects": stats.risk_rejects,
            "blocked": stats.blocked,
            "loss": loss_value,
            "action_counts": stats.action_counts,
        }
        history.append(row)

        if (episode + 1) % args.log_every == 0 or episode == start_episode:
            ac = stats.action_counts
            total_a = max(sum(ac.values()), 1)
            print(
                f"episode {episode + 1:5d} | regime {regime.name:11s} | loss {loss_value:+.4f} | "
                f"final_mtm {stats.final_mtm:+.2f} | avg_reward {stats.avg_reward:+.4f} | "
                f"orders {stats.orders_sent:4d} | fills {stats.fills_rcvd:4d} | rejects {stats.risk_rejects:4d} | blocked {stats.blocked:4d} | "
                f"mix(H/B/S)=({ac.get(ACTION_HOLD,0)/total_a:.2f}/{ac.get(ACTION_BUY,0)/total_a:.2f}/{ac.get(ACTION_SELL,0)/total_a:.2f}) | temp={temperature:.2f}"
            )

        if (episode + 1) % args.eval_every == 0 or episode == args.episodes - 1:
            summary = evaluate_policy(policy, device, args)
            print(format_eval_summary(summary))
            excess_vs_mr = summary["avg_excess_vs_mean_reversion"]
            is_best = excess_vs_mr > best_excess_vs_mr
            if is_best:
                best_excess_vs_mr = excess_vs_mr
                best_avg_mtm = summary["avg_mtm"]
                episodes_since_improvement = 0
                print(f"  *** new best excess_vs_mr={best_excess_vs_mr:+.2f} at episode {episode+1} ***")
            else:
                episodes_since_improvement += args.eval_every
            save_checkpoint(
                {
                    "episode": episode + 1,
                    "state_dict": policy.state_dict(),
                    "best_avg_mtm": best_avg_mtm,
                    "best_excess_vs_mr": best_excess_vs_mr,
                    "optimizer": optimizer.state_dict(),
                    "args": vars(args),
                    "eval_summary": summary,
                },
                is_best,
                file_folder=args.output_dir,
                filename="checkpoint.pth.tar",
            )
            with open(os.path.join(args.output_dir, "training_history.json"), "w", encoding="utf-8") as f:
                json.dump(history, f, indent=2)
            with open(os.path.join(args.output_dir, "latest_eval_summary.json"), "w", encoding="utf-8") as f:
                json.dump(summary, f, indent=2)
            if args.early_stop_patience > 0 and episodes_since_improvement >= args.early_stop_patience:
                print(f"Early stopping: no improvement in excess_vs_mr for {episodes_since_improvement} episodes.")
                break

        temperature = max(args.min_train_temperature, temperature * args.train_temperature_decay)

    print("Finished training.")
    print(f"Best avg_mtm: {best_avg_mtm:+.2f}")
    print(f"Best excess_vs_mr: {best_excess_vs_mr:+.2f}")


def build_argparser():
    parser = argparse.ArgumentParser(description="Stronger profit-driven policy training for the Dual-FPGA trading engine")
    parser.add_argument("--episodes", default=1000, type=int, help="number of training episodes")
    parser.add_argument("--cycles", default=20000, type=int, help="cycles per episode")
    parser.add_argument("--lr", default=3e-4, type=float, help="learning rate")
    parser.add_argument("--weight-decay", default=1e-5, type=float, help="Adam weight decay")
    parser.add_argument("--gamma", default=0.995, type=float, help="discount factor")
    parser.add_argument("--hidden-dim", default=128, type=int, help="first/second hidden width")
    parser.add_argument("--hidden-dim2", default=64, type=int, help="third hidden width")
    parser.add_argument("--input-dim", default=9, type=int, help="policy network input dimension")
    parser.add_argument("--entropy-coef", default=5e-3, type=float, help="entropy bonus coefficient")
    parser.add_argument("--grad-clip", default=1.0, type=float, help="gradient clip norm; <=0 disables clipping")
    parser.add_argument("--normalize-returns", action="store_true", help="normalize episode returns before policy update")
    parser.add_argument("--ppo-epochs", default=4, type=int, help="PPO update epochs per episode rollout")
    parser.add_argument("--ppo-clip", default=0.2, type=float, help="PPO clip ratio epsilon")
    parser.add_argument("--ppo-batch-size", default=64, type=int, help="minibatch size for PPO update")
    parser.add_argument("--eval-every", default=50, type=int, help="evaluate every N training episodes")
    parser.add_argument("--log-every", default=10, type=int, help="print training row every N episodes")
    parser.add_argument("--eval-episodes-per-regime", default=8, type=int, help="deterministic eval episodes per regime")
    parser.add_argument("--eval-only", action="store_true", help="skip training and only run evaluation")
    parser.add_argument("--early-stop-patience", default=400, type=int, help="stop training if excess_vs_mr has not improved for this many episodes (0 = disabled)")
    parser.add_argument("--resume", default="", type=str, help="checkpoint path")
    parser.add_argument("--output-dir", default="profit_nn_out", type=str, help="directory for checkpoints + json logs")
    parser.add_argument("--seed", default=0, type=int, help="global RNG seed")
    parser.add_argument("--seed-base", default=1000, type=int, help="base seed added to per-episode random draws")
    parser.add_argument("--eval-seed-base", default=50000, type=int, help="base seed for eval episodes")
    parser.add_argument("--cpu", action="store_true", help="force CPU even if CUDA is available")

    parser.add_argument("--num-sym", default=8, type=int, help="number of active symbols to simulate")
    parser.add_argument("--ema-alpha", default=6554, type=int, help="EMA alpha in Q0.16 (default ~10%%)")
    parser.add_argument("--base-qty", default=100, type=int, help="shares per order")
    parser.add_argument("--max-position", default=500, type=int, help="risk manager max position")
    parser.add_argument("--max-order-rate", default=100000, type=int, help="risk manager max order count per episode")
    parser.add_argument("--max-loss", default=100000, type=int, help="risk manager max realized loss in dollars")
    parser.add_argument("--link-delay", default=64, type=int, help="link delay in cycles")

    parser.add_argument("--trade-penalty", default=0.001, type=float, help="penalty per approved trade")
    parser.add_argument("--reject-penalty", default=0.02, type=float, help="penalty when risk rejects a trade")
    parser.add_argument("--blocked-penalty", default=0.01, type=float, help="penalty when outbound link is busy")
    parser.add_argument("--hold-penalty", default=0.0002, type=float, help="small penalty for HOLD to reduce zero-trade collapse")
    parser.add_argument("--inventory-penalty", default=0.0005, type=float, help="per-cycle inventory penalty weight")

    parser.add_argument("--train-temperature", default=1.50, type=float, help="initial action-sampling temperature during training")
    parser.add_argument("--min-train-temperature", default=1.20, type=float, help="floor for training temperature")
    parser.add_argument("--train-temperature-decay", default=0.9995, type=float, help="per-episode temperature decay")
    parser.add_argument("--eval-temperature", default=0.3, type=float, help="temperature for action sampling during eval (replaces hard argmax)")

    parser.add_argument("--train-calm-weight", default=0.5, type=float, help="sampling weight for CALM during training")
    parser.add_argument("--train-volatile-weight", default=1.0, type=float, help="sampling weight for VOLATILE during training")
    parser.add_argument("--train-burst-weight", default=0.5, type=float, help="sampling weight for BURST during training")
    parser.add_argument("--train-adversarial-weight", default=4.0, type=float, help="sampling weight for ADVERSARIAL during training")

    parser.add_argument("--mean-reversion-threshold-q16", default=0x00001999, type=lambda x: int(x, 0), help="baseline mean-reversion threshold in Q16.16 (default $0.10)")
    return parser


if __name__ == "__main__":
    parser = build_argparser()
    args = parser.parse_args()
    train(args)