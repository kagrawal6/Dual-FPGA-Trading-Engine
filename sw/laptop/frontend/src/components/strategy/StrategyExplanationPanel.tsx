import type { StrategyDecision } from "../../strategyDerived";
import { num } from "../../telemetryUtils";

type Props = {
  d: StrategyDecision;
  latest: Record<string, unknown>;
  selectedIdx: number;
};

export function StrategyExplanationPanel({ d, latest, selectedIdx }: Props) {
  const midArr = Array.isArray(latest.mid) ? latest.mid : [];
  const emaArr = Array.isArray(latest.ema) ? latest.ema : [];
  const sprArr = Array.isArray(latest.spread) ? latest.spread : [];
  const devArr = Array.isArray(latest.dev) ? latest.dev : [];
  const posArr = Array.isArray(latest.pos) ? latest.pos : [];
  const maxPos = Math.max(1, num(latest.max_position, 1));
  const thr = Math.max(0, num(latest.threshold, 0.2));

  const mid = num(midArr[selectedIdx], NaN);
  const ema = num(emaArr[selectedIdx], NaN);
  const spr = Math.max(0, num(sprArr[selectedIdx], NaN));
  const dev = num(devArr[selectedIdx], NaN);
  const pos = num(posArr[selectedIdx], 0);

  let msg = "";
  if (d.stale) {
    msg = `${d.symbol} decision is held because the stream is stale. Link/risk state may be delayed.`;
  } else if (!d.riskPass) {
    if (Math.abs(pos) >= 0.92 * maxPos) {
      msg = `${d.symbol} is blocked because position is near the configured max exposure. Signal is ${d.action}, but the risk gate prevented another order.`;
    } else if (spr > thr * 1.6 && Number.isFinite(spr) && thr > 0) {
      msg = `${d.symbol} is blocked because spread is wide vs threshold. Decision is held until spread normalizes.`;
    } else if (!Boolean(latest.link_up)) {
      msg = `${d.symbol} is blocked because the exchange link is down. Decisions are held until link recovers.`;
    } else if (Boolean(latest.kill_switch)) {
      msg = `${d.symbol} is blocked because the kill switch is enabled.`;
    } else {
      msg = `${d.symbol} is blocked by the risk gate (${d.riskReason || d.reason}).`;
    }
  } else if (d.action === "BUY") {
    if (Number.isFinite(mid) && Number.isFinite(ema) && mid > ema) msg = `${d.symbol} is BUY because mid is above EMA and momentum is positive.`;
    else if (Number.isFinite(dev) && dev > 0) msg = `${d.symbol} is BUY because EMA deviation is positive and above threshold pressure.`;
    else msg = `${d.symbol} is BUY based on feature signal alignment; risk gate passed.`;
  } else if (d.action === "SELL") {
    if (Number.isFinite(mid) && Number.isFinite(ema) && mid < ema) msg = `${d.symbol} is SELL because mid is below EMA and downside pressure is active.`;
    else if (Number.isFinite(dev) && dev < 0) msg = `${d.symbol} is SELL because EMA deviation is negative and above threshold pressure.`;
    else msg = `${d.symbol} is SELL based on feature signal alignment; risk gate passed.`;
  } else {
    if (Number.isFinite(spr) && thr > 0 && spr > thr * 1.6) msg = `${d.symbol} is HOLD because spread is wide; guard held orders.`;
    else msg = `${d.symbol} is HOLD because features are within guard bands and no order intent is asserted.`;
  }

  return (
    <section className="tm-se-why">
      <div className="tm-se-panel-head">
        <div className="tm-se-panel-title">WHY THIS DECISION</div>
        <div className="tm-se-panel-sub mono">{d.reasonSynthetic ? "demo-derived" : "streamed"} · {d.reason || "—"}</div>
      </div>
      <div className="tm-se-why-body mono">{msg}</div>
    </section>
  );
}

