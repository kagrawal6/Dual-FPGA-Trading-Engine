import { num } from "../../telemetryUtils";
import type { DecisionEvent } from "../../strategyDerived";

type Props = {
  latest: Record<string, unknown>;
  rates: Record<string, number> | null | undefined;
  events: DecisionEvent[];
  connected: boolean;
  packetAgeMs: number | null;
};

function fmtRate(v: number): string {
  if (!Number.isFinite(v)) return "—";
  if (v >= 1000) return `${(v / 1000).toFixed(1)}k/s`;
  return `${v.toFixed(1)}/s`;
}

function cellTone(kind: "good" | "warn" | "bad" | "muted"): string {
  return `tone-${kind}`;
}

export function ExecutionHealthRow({ latest, rates, events, connected, packetAgeMs }: Props) {
  const now = Date.now();
  const recent = events.filter((e) => now - e.ts < 10_000);
  const decisionRate = recent.length / 10;
  const blocks = recent.filter((e) => e.risk === "BLOCK").length;
  const blockPct = recent.length ? (blocks / recent.length) * 100 : NaN;

  const orderRate = Number.isFinite(num(latest.order_rate, NaN)) ? num(latest.order_rate) : rates ? num(rates.orders, NaN) : NaN;
  const fillRate = Number.isFinite(num(latest.fill_rate, NaN)) ? num(latest.fill_rate) : rates ? num(rates.fills, NaN) : NaN;
  const rejectRate = Number.isFinite(num(latest.reject_rate, NaN)) ? num(latest.reject_rate) : rates ? num(rates.rejects, NaN) : NaN;

  const linkUp = Boolean(latest.link_up);
  const hbAge = Number.isFinite(num(latest.heartbeat_age_ms, NaN)) ? num(latest.heartbeat_age_ms) : packetAgeMs;
  const stale = !connected || (hbAge != null && hbAge > 1500);

  const cells: { k: string; v: string; tone: "good" | "warn" | "bad" | "muted"; tag?: string }[] = [
    { k: "DECISION RATE", v: fmtRate(decisionRate), tone: stale ? "warn" : "good", tag: "DERIVED" },
    { k: "ORDER RATE", v: fmtRate(orderRate), tone: Number.isFinite(orderRate) ? "good" : "muted", tag: Number.isFinite(num(latest.order_rate, NaN)) ? "REAL" : "DERIVED" },
    { k: "FILL RATE", v: fmtRate(fillRate), tone: Number.isFinite(fillRate) && fillRate > 0 ? "good" : "muted", tag: Number.isFinite(num(latest.fill_rate, NaN)) ? "REAL" : "DERIVED" },
    { k: "REJECT RATE", v: fmtRate(rejectRate), tone: Number.isFinite(rejectRate) && rejectRate > 0.5 ? "warn" : Number.isFinite(rejectRate) ? "good" : "muted", tag: Number.isFinite(num(latest.reject_rate, NaN)) ? "REAL" : "DERIVED" },
    { k: "BLOCK %", v: Number.isFinite(blockPct) ? `${blockPct.toFixed(1)}%` : "—", tone: Number.isFinite(blockPct) && blockPct > 25 ? "warn" : Number.isFinite(blockPct) ? "good" : "muted", tag: "DERIVED" },
    { k: "STREAM AGE", v: hbAge != null && Number.isFinite(hbAge) ? `${hbAge.toFixed(0)} ms` : "—", tone: stale ? "warn" : "good", tag: "DERIVED" },
    { k: "LINK", v: linkUp ? "UP" : "DOWN", tone: linkUp ? "good" : "bad", tag: "REAL" },
    { k: "HEARTBEAT", v: stale ? "STALE" : "OK", tone: stale ? "warn" : "good", tag: "DERIVED" },
  ];

  return (
    <div className="tm-rt-exec-row mono">
      {cells.map((c) => (
        <div key={c.k} className={`tm-rt-exec-cell ${cellTone(c.tone)}`}>
          <div className="k">{c.k}</div>
          <div className="v">{c.v}</div>
          <div className="t">{c.tag ?? ""}</div>
        </div>
      ))}
    </div>
  );
}

