"""
train_nn.py — Train a tiny PyTorch trading classifier from the golden model.

Purpose
-------
This script trains a *small* neural network that imitates Board B's current
mean-reversion strategy. It does not replace risk management, order packing,
or fill handling. It only learns the strategy decision:

    HOLD / BUY / SELL

Data generation uses the existing golden model pieces:
  - BoardA produces deterministic QuoteFrames
  - FeatureEngine computes EMA / deviation
  - Strategy.evaluate(...) is the teacher that supplies labels

Why this design?
----------------
It matches the hardware architecture cleanly:
  QuoteBook -> FeatureEngine -> Strategy -> RiskManager -> OrderBuilder

The NN can later replace or sit beside the Strategy block while keeping the
rest of Board B unchanged.

Usage examples
--------------
# Train on all 4 regimes, save checkpoint + metadata
python train_nn.py

# Short smoke test
python train_nn.py --cycles-per-regime 2000 --epochs 20 --output-dir nn_out

# Linear model only (no hidden layer)
python train_nn.py --hidden-dim 0
"""

from __future__ import annotations

import argparse
import csv
import json
import random
import sys
from collections import Counter
from dataclasses import dataclass
from pathlib import Path

THIS_DIR = Path(__file__).resolve().parent
if str(THIS_DIR) not in sys.path:
    sys.path.insert(0, str(THIS_DIR))

import numpy as np
import torch
import torch.nn as nn

from common import (
    MASK_32,
    Regime,
    SIDE_BUY,
    SIDE_SELL,
    QuoteFrame,
    default_init_mids,
    default_init_spreads,
    default_sector_ids,
    from_q16,
    q16,
    sext32,
)
from board_a import BoardA
from board_b import FeatureEngine, Strategy


LABEL_HOLD = 0
LABEL_BUY = 1
LABEL_SELL = 2
LABEL_NAMES = ["HOLD", "BUY", "SELL"]
FEATURE_NAMES = ["deviation", "spread", "mid_delta", "ema_delta"]


def set_seed(seed: int) -> None:
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)


@dataclass
class Sample:
    """One supervised training example."""

    features: list[float]
    label: int
    regime: int
    symbol: int
    cycle: int
    deviation_dollars: float
    spread_dollars: float
    mid_delta_dollars: float
    ema_delta_dollars: float


class TinyTraderNet(nn.Module):
    """Very small classifier for eventual RTL-friendly inference.

    hidden_dim == 0 gives a single linear layer (logistic-regression style).
    hidden_dim > 0 gives a 1-hidden-layer MLP with ReLU.
    """

    def __init__(self, in_dim: int = 4, hidden_dim: int = 4, out_dim: int = 3):
        super().__init__()
        if hidden_dim > 0:
            self.net = nn.Sequential(
                nn.Linear(in_dim, hidden_dim),
                nn.ReLU(),
                nn.Linear(hidden_dim, out_dim),
            )
        else:
            self.net = nn.Sequential(nn.Linear(in_dim, out_dim))

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.net(x)


class FixedFeatureScaler:
    """Simple deterministic feature scaling that will be easy to reproduce later.

    We avoid dataset-dependent normalization (mean/std) so the exact scaling can
    be mirrored in Verilog with a few constants.
    """

    def __init__(
        self,
        deviation_scale: float,
        spread_scale: float,
        delta_scale: float,
        clip_value: float,
    ):
        self.deviation_scale = max(float(deviation_scale), 1e-9)
        self.spread_scale = max(float(spread_scale), 1e-9)
        self.delta_scale = max(float(delta_scale), 1e-9)
        self.clip_value = max(float(clip_value), 1e-9)

    def transform(
        self,
        deviation_dollars: float,
        spread_dollars: float,
        mid_delta_dollars: float,
        ema_delta_dollars: float,
    ) -> list[float]:
        def squash(v: float, scale: float, lo: float = -1.0, hi: float = 1.0) -> float:
            scaled = v / scale
            clipped = max(-self.clip_value, min(self.clip_value, scaled))
            # Keep spread non-negative if caller wants that by passing lo=0
            clipped = max(lo * self.clip_value, min(hi * self.clip_value, clipped))
            return clipped / self.clip_value

        return [
            squash(deviation_dollars, self.deviation_scale, -1.0, 1.0),
            squash(spread_dollars, self.spread_scale, 0.0, 1.0),
            squash(mid_delta_dollars, self.delta_scale, -1.0, 1.0),
            squash(ema_delta_dollars, self.delta_scale, -1.0, 1.0),
        ]

    def to_dict(self) -> dict:
        return {
            "feature_names": FEATURE_NAMES,
            "deviation_scale": self.deviation_scale,
            "spread_scale": self.spread_scale,
            "delta_scale": self.delta_scale,
            "clip_value": self.clip_value,
            "output_range": [-1.0, 1.0],
        }


def q16_delta_to_dollars(curr: int, prev: int | None) -> float:
    if prev is None:
        return 0.0
    return sext32((curr - prev) & MASK_32) / 65536.0


def teacher_label(signal) -> int:
    if signal is None:
        return LABEL_HOLD
    return LABEL_BUY if signal.side == SIDE_BUY else LABEL_SELL


def build_scaler(args: argparse.Namespace) -> FixedFeatureScaler:
    # The defaults are chosen to be easy to reason about and easy to reproduce
    # later in fixed-point hardware.
    deviation_scale = args.deviation_scale or max(args.threshold, 0.10)
    spread_scale = args.spread_scale or 0.50
    delta_scale = args.delta_scale or max(args.threshold, 0.10)
    return FixedFeatureScaler(
        deviation_scale=deviation_scale,
        spread_scale=spread_scale,
        delta_scale=delta_scale,
        clip_value=args.clip_value,
    )


def build_dataset(args: argparse.Namespace, scaler: FixedFeatureScaler) -> list[Sample]:
    samples: list[Sample] = []
    init_mid = default_init_mids()[: args.num_sym]
    init_spread = default_init_spreads()[: args.num_sym]
    sector_ids = default_sector_ids()[: args.num_sym]
    alpha_q16 = int(args.ema_alpha_q16)
    threshold_q16 = q16(args.threshold)

    for regime in [Regime.CALM, Regime.VOLATILE, Regime.BURST, Regime.ADVERSARIAL]:
        board_a = BoardA(num_sym=args.num_sym)
        board_a.configure(
            regime=int(regime),
            quote_interval=0,
            seed=(args.seed ^ (0x9E3779B9 * (int(regime) + 1))) & 0xFFFF_FFFF,
            init_mid=init_mid,
            init_spread=init_spread,
            sector_ids=sector_ids,
            active_count=args.num_sym,
        )
        board_a.start()

        features = FeatureEngine(num_sym=args.num_sym)
        prev_mid: list[int | None] = [None] * args.num_sym
        prev_ema: list[int | None] = [None] * args.num_sym

        for cycle in range(args.cycles_per_regime):
            bits = board_a.step(cycle)
            if bits is None:
                continue

            quote = QuoteFrame.from_bits(bits)
            symbol = quote.symbol
            mid = quote.mid
            spread_dollars = from_q16(quote.spread)

            deviation = features.compute(symbol, mid, alpha_q16)
            ema_now = features.ema[symbol]

            deviation_dollars = sext32(deviation) / 65536.0
            mid_delta_dollars = q16_delta_to_dollars(mid, prev_mid[symbol])
            ema_delta_dollars = q16_delta_to_dollars(ema_now, prev_ema[symbol])

            signal = Strategy.evaluate(
                deviation=deviation,
                bid=quote.bid,
                ask=quote.ask,
                threshold=threshold_q16,
                qty=args.base_qty,
            )
            label = teacher_label(signal)

            scaled_features = scaler.transform(
                deviation_dollars=deviation_dollars,
                spread_dollars=spread_dollars,
                mid_delta_dollars=mid_delta_dollars,
                ema_delta_dollars=ema_delta_dollars,
            )

            samples.append(
                Sample(
                    features=scaled_features,
                    label=label,
                    regime=int(regime),
                    symbol=symbol,
                    cycle=cycle,
                    deviation_dollars=deviation_dollars,
                    spread_dollars=spread_dollars,
                    mid_delta_dollars=mid_delta_dollars,
                    ema_delta_dollars=ema_delta_dollars,
                )
            )

            prev_mid[symbol] = mid
            prev_ema[symbol] = ema_now

    return samples


def split_dataset(
    X: np.ndarray, y: np.ndarray, val_frac: float, seed: int
) -> tuple[np.ndarray, np.ndarray, np.ndarray, np.ndarray]:
    n = len(X)
    idx = np.arange(n)
    rng = np.random.default_rng(seed)
    rng.shuffle(idx)

    val_size = max(1, int(round(n * val_frac)))
    val_idx = idx[:val_size]
    train_idx = idx[val_size:]
    if len(train_idx) == 0:
        raise ValueError("Validation split left no training data. Reduce --val-frac.")

    return X[train_idx], y[train_idx], X[val_idx], y[val_idx]


@torch.no_grad()
def evaluate(model: nn.Module, X: torch.Tensor, y: torch.Tensor) -> dict:
    model.eval()
    logits = model(X)
    pred = torch.argmax(logits, dim=1)
    acc = (pred == y).float().mean().item()

    confusion = torch.zeros((3, 3), dtype=torch.int64)
    for t, p in zip(y, pred):
        confusion[int(t), int(p)] += 1

    per_class_acc = {}
    for cls_idx, cls_name in enumerate(LABEL_NAMES):
        denom = confusion[cls_idx].sum().item()
        per_class_acc[cls_name] = (
            confusion[cls_idx, cls_idx].item() / denom if denom > 0 else None
        )

    return {
        "accuracy": acc,
        "confusion_matrix": confusion.tolist(),
        "per_class_accuracy": per_class_acc,
        "pred_counts": Counter(pred.tolist()),
    }


def class_weights_from_labels(y: np.ndarray) -> torch.Tensor:
    counts = Counter(int(v) for v in y.tolist())
    total = float(len(y))
    weights = []
    for cls in range(3):
        count = max(counts.get(cls, 0), 1)
        weights.append(total / (3.0 * count))
    return torch.tensor(weights, dtype=torch.float32)


def train_model(
    X_train: np.ndarray,
    y_train: np.ndarray,
    X_val: np.ndarray,
    y_val: np.ndarray,
    args: argparse.Namespace,
) -> tuple[nn.Module, dict]:
    device = torch.device("cpu")
    model = TinyTraderNet(in_dim=4, hidden_dim=args.hidden_dim, out_dim=3).to(device)

    X_train_t = torch.tensor(X_train, dtype=torch.float32, device=device)
    y_train_t = torch.tensor(y_train, dtype=torch.long, device=device)
    X_val_t = torch.tensor(X_val, dtype=torch.float32, device=device)
    y_val_t = torch.tensor(y_val, dtype=torch.long, device=device)

    loss_fn = nn.CrossEntropyLoss(weight=class_weights_from_labels(y_train).to(device))
    optimizer = torch.optim.Adam(model.parameters(), lr=args.lr)

    history = {
        "train_loss": [],
        "train_acc": [],
        "val_acc": [],
    }

    batch_size = min(args.batch_size, len(X_train_t))
    best_state = None
    best_val_acc = -1.0

    for epoch in range(1, args.epochs + 1):
        model.train()
        perm = torch.randperm(len(X_train_t), device=device)
        running_loss = 0.0
        seen = 0

        for start in range(0, len(X_train_t), batch_size):
            idx = perm[start : start + batch_size]
            xb = X_train_t[idx]
            yb = y_train_t[idx]

            optimizer.zero_grad()
            logits = model(xb)
            loss = loss_fn(logits, yb)
            loss.backward()
            optimizer.step()

            running_loss += loss.item() * len(xb)
            seen += len(xb)

        train_metrics = evaluate(model, X_train_t, y_train_t)
        val_metrics = evaluate(model, X_val_t, y_val_t)
        avg_loss = running_loss / max(seen, 1)

        history["train_loss"].append(avg_loss)
        history["train_acc"].append(train_metrics["accuracy"])
        history["val_acc"].append(val_metrics["accuracy"])

        if val_metrics["accuracy"] > best_val_acc:
            best_val_acc = val_metrics["accuracy"]
            best_state = {k: v.cpu().clone() for k, v in model.state_dict().items()}

        if epoch == 1 or epoch % max(1, args.print_every) == 0 or epoch == args.epochs:
            print(
                f"epoch {epoch:4d} | loss {avg_loss:.4f} | "
                f"train_acc {train_metrics['accuracy']:.4f} | "
                f"val_acc {val_metrics['accuracy']:.4f}"
            )

    if best_state is not None:
        model.load_state_dict(best_state)

    final_train = evaluate(model, X_train_t, y_train_t)
    final_val = evaluate(model, X_val_t, y_val_t)

    summary = {
        "history": history,
        "best_val_accuracy": best_val_acc,
        "final_train": {
            **final_train,
            "pred_counts": dict(final_train["pred_counts"]),
        },
        "final_val": {
            **final_val,
            "pred_counts": dict(final_val["pred_counts"]),
        },
    }
    return model, summary


def save_dataset_csv(samples: list[Sample], out_path: Path) -> None:
    with out_path.open("w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(
            [
                "cycle",
                "regime",
                "symbol",
                *FEATURE_NAMES,
                "label",
                "label_name",
                "deviation_dollars",
                "spread_dollars",
                "mid_delta_dollars",
                "ema_delta_dollars",
            ]
        )
        for s in samples:
            writer.writerow(
                [
                    s.cycle,
                    s.regime,
                    s.symbol,
                    *[f"{v:.8f}" for v in s.features],
                    s.label,
                    LABEL_NAMES[s.label],
                    f"{s.deviation_dollars:.8f}",
                    f"{s.spread_dollars:.8f}",
                    f"{s.mid_delta_dollars:.8f}",
                    f"{s.ema_delta_dollars:.8f}",
                ]
            )


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Train a tiny NN from the trading golden model.")
    p.add_argument("--num-sym", type=int, default=16, help="Number of symbols to simulate.")
    p.add_argument(
        "--cycles-per-regime",
        type=int,
        default=12000,
        help="Quote-generation cycles to simulate for each regime.",
    )
    p.add_argument("--threshold", type=float, default=0.30, help="Teacher strategy threshold in dollars.")
    p.add_argument(
        "--ema-alpha-q16",
        type=int,
        default=6554,
        help="EMA alpha in Q0.16 (6554 ≈ 0.10).",
    )
    p.add_argument("--base-qty", type=int, default=100, help="Teacher strategy order quantity.")
    p.add_argument("--hidden-dim", type=int, default=4, help="Hidden layer width; 0 => linear model.")
    p.add_argument("--epochs", type=int, default=80, help="Training epochs.")
    p.add_argument("--batch-size", type=int, default=256, help="Mini-batch size.")
    p.add_argument("--lr", type=float, default=1e-3, help="Adam learning rate.")
    p.add_argument("--val-frac", type=float, default=0.20, help="Validation fraction.")
    p.add_argument("--seed", type=int, default=1234, help="Random seed.")
    p.add_argument("--print-every", type=int, default=10, help="Epoch print interval.")
    p.add_argument(
        "--output-dir",
        type=Path,
        default=Path("nn_out"),
        help="Directory for checkpoint + metadata + optional CSV.",
    )
    p.add_argument(
        "--write-csv",
        action="store_true",
        help="Also write the generated supervised dataset as CSV.",
    )
    p.add_argument(
        "--deviation-scale",
        type=float,
        default=None,
        help="Manual scaling constant for deviation dollars before clipping.",
    )
    p.add_argument(
        "--spread-scale",
        type=float,
        default=None,
        help="Manual scaling constant for spread dollars before clipping.",
    )
    p.add_argument(
        "--delta-scale",
        type=float,
        default=None,
        help="Manual scaling constant for mid/ema deltas before clipping.",
    )
    p.add_argument(
        "--clip-value",
        type=float,
        default=4.0,
        help="Clip raw scaled features to [-clip, clip] before mapping to [-1,1].",
    )
    return p.parse_args()


def main() -> None:
    args = parse_args()
    set_seed(args.seed)
    args.output_dir.mkdir(parents=True, exist_ok=True)

    scaler = build_scaler(args)
    print("Building dataset...")
    samples = build_dataset(args, scaler)
    if not samples:
        raise RuntimeError("No samples were generated.")

    X = np.asarray([s.features for s in samples], dtype=np.float32)
    y = np.asarray([s.label for s in samples], dtype=np.int64)

    label_counts = Counter(int(v) for v in y.tolist())
    print(f"Total samples: {len(samples)}")
    print(
        "Label counts: "
        + ", ".join(f"{LABEL_NAMES[i]}={label_counts.get(i, 0)}" for i in range(3))
    )
    missing = [LABEL_NAMES[i] for i in range(3) if label_counts.get(i, 0) == 0]
    if missing:
        print(
            "Warning: missing classes in generated data -> "
            + ", ".join(missing)
            + ". Increase --cycles-per-regime or lower --threshold if needed."
        )

    X_train, y_train, X_val, y_val = split_dataset(X, y, args.val_frac, args.seed)
    model, training_summary = train_model(X_train, y_train, X_val, y_val, args)

    ckpt_path = args.output_dir / "tiny_trader_net.pt"
    torch.save(
        {
            "state_dict": model.state_dict(),
            "feature_names": FEATURE_NAMES,
            "label_names": LABEL_NAMES,
            "hidden_dim": args.hidden_dim,
            "scaler": scaler.to_dict(),
            "teacher_threshold_dollars": args.threshold,
            "ema_alpha_q16": args.ema_alpha_q16,
            "num_symbols": args.num_sym,
        },
        ckpt_path,
    )

    metadata = {
        "args": {
            k: (str(v) if isinstance(v, Path) else v)
            for k, v in vars(args).items()
        },
        "feature_names": FEATURE_NAMES,
        "label_names": LABEL_NAMES,
        "scaler": scaler.to_dict(),
        "dataset": {
            "num_samples": len(samples),
            "label_counts": {LABEL_NAMES[k]: label_counts.get(k, 0) for k in range(3)},
        },
        "training": training_summary,
    }

    meta_path = args.output_dir / "training_summary.json"
    meta_path.write_text(json.dumps(metadata, indent=2))

    if args.write_csv:
        csv_path = args.output_dir / "nn_dataset.csv"
        save_dataset_csv(samples, csv_path)
        print(f"Dataset CSV written to {csv_path}")

    print(f"Checkpoint written to {ckpt_path}")
    print(f"Summary written to {meta_path}")

    val_acc = training_summary["final_val"]["accuracy"]
    print(f"Final validation accuracy: {val_acc:.4f}")
    print("Validation confusion matrix [true][pred]:")
    for row_name, row in zip(LABEL_NAMES, training_summary["final_val"]["confusion_matrix"]):
        print(f"  {row_name:>4}: {row}")


if __name__ == "__main__":
    main()
