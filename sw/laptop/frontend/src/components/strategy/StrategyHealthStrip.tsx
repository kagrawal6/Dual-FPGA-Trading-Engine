import { num } from "../../telemetryUtils";
import type { DecisionEvent } from "../../strategyDerived";

type Props = {
  rates: Record<string, number> | null | undefined;
  events: DecisionEvent[];
  packetAgeMs: number | null;
  connected: boolean;
};

function tone(v: number, warn: number, bad: number): "good" | "warn" | "bad" | "muted" {
  if (!Number.isFinite(v)) return "muted";
  if (v >= bad) return "bad";
  if (v >= warn) return "warn";
  return "good";
}

export function StrategyHealthStrip({ rates, events, packetAgeMs, connected }: Props) {
  const qps = rates ? num(rates.quotes, NaN) : NaN;
  const ops = rates ? num(rates.orders, NaN) : NaN;
  const fps = rates ? num(rates.fills, NaN) : NaN;
  const rps = rates ? num(rates.rejects, NaN) : NaN;

  const now = Date.now();
  const recent = events.filter((e) => now - e.ts < 10_000);
  const blocks = recent.filter((e) => e.risk === "BLOCK").length;
  const total = recent.length || 1;
  const blockRate = blocks / total;

  const stale = !connected || (packetAgeMs != null && packetAgeMs > 1500);

  const items: { k: string; v: string; tone?: string }[] = [
    { k: "decision/s", v: `${(recent.length / 10).toFixed(1)}` },
    { k: "order/s", v: Number.isFinite(ops) ? ops.toFixed(0) : "—" },
    { k: "fill/s", v: Number.isFinite(fps) ? fps.toFixed(0) : "—" },
    { k: "rej/s", v: Number.isFinite(rps) ? rps.toFixed(0) : "—", tone: tone(rps, 0.5, 2) },
    { k: "block", v: `${(blockRate * 100).toFixed(0)}%`, tone: blockRate > 0.35 ? "warn" : undefined },
    { k: "age", v: packetAgeMs != null ? `${packetAgeMs.toFixed(0)} ms` : "—", tone: stale ? "warn" : undefined },
  ];

  return (
    <div className={`tm-se-health mono ${stale ? "tm-se-health--stale" : ""}`}>
      <div className="tm-se-health-left">
        <span className="tm-se-health-title">STRATEGY HEALTH</span>
        {stale && <span className="tm-se-stale">STREAM STALE — decisions held</span>}
      </div>
      <div className="tm-se-health-items">
        {items.map((it) => (
          <span key={it.k} className={`tm-se-health-item ${it.tone ? `is-${it.tone}` : ""}`}>
            <span className="k">{it.k}</span>
            <span className="v">{it.v}</span>
          </span>
        ))}
      </div>
    </div>
  );
}

