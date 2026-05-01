import { arrNum, arrSignal, normalizeSignal, num, str } from "./telemetryUtils";

export type DecisionAction = "BUY" | "SELL" | "HOLD" | "RISK_BLOCKED";

export type StrategyDecision = {
  symbol: string;
  action: DecisionAction;
  confidence: number | null;
  confidenceSynthetic: boolean;
  decisionAgeMs: number | null;
  mode: string;
  reason: string;
  reasonSynthetic: boolean;
  riskPass: boolean;
  riskReason: string;
  orderSide: "BUY" | "SELL" | "NONE";
  orderSize: number | null;
  orderPrice: number | null;
  orderRoute: string | null;
  outcome: "NO_ORDER" | "HELD" | "PENDING" | "FILLED" | "REJECTED" | "BLOCKED";
  outcomeReason: string | null;
  stale: boolean;
};

function clamp01(x: number): number {
  if (!Number.isFinite(x)) return 0;
  return Math.max(0, Math.min(1, x));
}

function actionFromLatest(latest: Record<string, unknown>, idx: number): { action: DecisionAction; synthetic: boolean } {
  const actArr = latest.decision_action;
  if (Array.isArray(actArr)) {
    const raw = String(actArr[idx] ?? "").trim().toUpperCase();
    if (raw === "BUY" || raw === "SELL" || raw === "HOLD" || raw === "RISK_BLOCKED") return { action: raw, synthetic: false };
    if (raw === "RISK_BLOCK") return { action: "RISK_BLOCKED", synthetic: false };
  }
  const sig = arrSignal(latest.signal, idx + 1)[idx] ?? "NONE";
  const s = normalizeSignal(sig);
  if (s === "BUY" || s === "SELL" || s === "RISK_BLOCKED") return { action: s, synthetic: true };
  return { action: "HOLD", synthetic: true };
}

function confidenceFromLatest(latest: Record<string, unknown>, idx: number): { conf: number | null; synthetic: boolean } {
  const confArr = latest.decision_confidence;
  if (Array.isArray(confArr)) {
    const c = num(confArr[idx], NaN);
    if (Number.isFinite(c)) return { conf: clamp01(c), synthetic: false };
  }
  // safe synthetic: function of |dev| + inverse spread, bounded and clearly marked synthetic
  const dev = arrNum(latest.dev, idx + 1, 0)[idx] ?? 0;
  const spr = Math.max(0, arrNum(latest.spread, idx + 1, 0)[idx] ?? 0);
  const devScore = clamp01(Math.abs(dev) / 0.35);
  const sprScore = clamp01(1 - spr / 0.35);
  const c = 0.18 + 0.62 * devScore + 0.20 * sprScore;
  return { conf: clamp01(c), synthetic: true };
}

function reasonFromLatest(latest: Record<string, unknown>, idx: number, action: DecisionAction): { reason: string; synthetic: boolean } {
  const rr = latest.decision_reason;
  if (Array.isArray(rr)) {
    const raw = String(rr[idx] ?? "").trim().toUpperCase();
    if (raw && raw !== "—") return { reason: raw, synthetic: false };
  }

  // derived reasons (conservative, ops-style)
  const dev = arrNum(latest.dev, idx + 1, 0)[idx] ?? 0;
  const spr = Math.max(0, arrNum(latest.spread, idx + 1, 0)[idx] ?? 0);
  const pos = arrNum(latest.pos, idx + 1, 0)[idx] ?? 0;
  const maxPos = Math.max(1, num(latest.max_position, 1));
  const rej = num(latest.rej, 0);
  const linkUp = Boolean(latest.link_up);
  const kill = Boolean(latest.kill_switch);
  const threshold = Math.max(0, num(latest.threshold, 0.2));

  if (!linkUp) return { reason: "LINK_DOWN", synthetic: true };
  if (kill) return { reason: "KILL_SWITCH", synthetic: true };
  if (rej > 0 && action === "RISK_BLOCKED") return { reason: "RISK_REJECT", synthetic: true };
  if (Math.abs(pos) >= 0.92 * maxPos && action === "RISK_BLOCKED") return { reason: "POSITION_LIMIT", synthetic: true };
  if (spr >= 1.6 * threshold && (action === "HOLD" || action === "RISK_BLOCKED")) return { reason: "SPREAD_TOO_WIDE", synthetic: true };
  if (Math.abs(dev) >= threshold) return { reason: "EMA_DEV_THRESHOLD", synthetic: true };
  return { reason: "UNKNOWN_REASON", synthetic: true };
}

function riskFromLatest(latest: Record<string, unknown>, idx: number, action: DecisionAction, reason: string): { pass: boolean; reason: string } {
  const rs = latest.risk_status;
  if (Array.isArray(rs)) {
    const raw = String(rs[idx] ?? "").trim().toUpperCase();
    if (raw === "PASS") return { pass: true, reason: "PASS" };
    if (raw === "BLOCK" || raw === "BLOCKED") {
      const rr = latest.risk_reason;
      if (Array.isArray(rr)) {
        const rraw = String(rr[idx] ?? "").trim().toUpperCase();
        return { pass: false, reason: rraw || "BLOCKED" };
      }
      return { pass: false, reason: "BLOCKED" };
    }
  }
  if (Boolean(latest.risk_halt)) return { pass: false, reason: "HALTED" };
  if (!Boolean(latest.link_up)) return { pass: false, reason: "LINK_DOWN" };
  if (Boolean(latest.kill_switch)) return { pass: false, reason: "KILL_SWITCH" };
  if (action === "RISK_BLOCKED") return { pass: false, reason: reason || "BLOCKED" };
  return { pass: true, reason: "PASS" };
}

function orderFromLatest(latest: Record<string, unknown>, idx: number): { side: "BUY" | "SELL" | "NONE"; size: number | null; price: number | null; route: string | null } {
  const sideArr = latest.order_side;
  const sizeArr = latest.order_size;
  const priceArr = latest.order_price;
  const routeArr = latest.order_route;
  if (Array.isArray(sideArr) || Array.isArray(sizeArr) || Array.isArray(priceArr) || Array.isArray(routeArr)) {
    const s = Array.isArray(sideArr) ? String(sideArr[idx] ?? "").trim().toUpperCase() : "";
    const side = s === "BUY" || s === "SELL" ? (s as "BUY" | "SELL") : "NONE";
    const size = Array.isArray(sizeArr) ? num(sizeArr[idx], NaN) : NaN;
    const price = Array.isArray(priceArr) ? num(priceArr[idx], NaN) : NaN;
    const route = Array.isArray(routeArr) ? String(routeArr[idx] ?? "").trim() : "";
    return {
      side,
      size: Number.isFinite(size) ? Math.max(0, Math.floor(size)) : null,
      price: Number.isFinite(price) ? price : null,
      route: route ? route : null,
    };
  }
  return { side: "NONE", size: null, price: null, route: null };
}

function synthOrder(latest: Record<string, unknown>, idx: number, action: DecisionAction, conf: number | null, riskPass: boolean): { side: "BUY" | "SELL" | "NONE"; size: number | null; price: number | null; route: string | null } {
  if (!riskPass || action === "HOLD" || action === "RISK_BLOCKED") return { side: "NONE", size: null, price: null, route: "SIM_EXCHANGE" };
  const bid = arrNum(latest.bid, idx + 1, NaN)[idx];
  const ask = arrNum(latest.ask, idx + 1, NaN)[idx];
  const mid = arrNum(latest.mid, idx + 1, NaN)[idx];
  const px = Number.isFinite(mid) ? mid : Number.isFinite(ask) ? ask : Number.isFinite(bid) ? bid : null;
  const c = conf ?? 0.5;
  const base = 25 + Math.floor(175 * clamp01(c));
  return {
    side: action === "BUY" ? "BUY" : action === "SELL" ? "SELL" : "NONE",
    size: action === "BUY" || action === "SELL" ? base : null,
    price: px,
    route: "SIM_EXCHANGE",
  };
}

function outcomeFromLatest(latest: Record<string, unknown>, idx: number): { outcome: StrategyDecision["outcome"]; reason: string | null } {
  const outArr = latest.order_outcome;
  const rejArr = latest.order_reject_reason;
  if (Array.isArray(outArr)) {
    const raw = String(outArr[idx] ?? "").trim().toUpperCase();
    const o =
      raw === "FILLED" || raw === "REJECTED" || raw === "PENDING" || raw === "HELD" || raw === "NO_ORDER" || raw === "BLOCKED"
        ? (raw as StrategyDecision["outcome"])
        : null;
    if (o) {
      const rr = Array.isArray(rejArr) ? String(rejArr[idx] ?? "").trim().toUpperCase() : "";
      return { outcome: o, reason: rr || null };
    }
  }
  return { outcome: "NO_ORDER", reason: null };
}

export function deriveStrategyDecision(args: {
  latest: Record<string, unknown>;
  symbols: string[];
  selectedIdx: number;
  packetAgeMs?: number;
  connected?: boolean;
}): StrategyDecision {
  const { latest, symbols, selectedIdx } = args;
  const symbol = symbols[selectedIdx] ?? `SYM${selectedIdx}`;

  const { action } = actionFromLatest(latest, selectedIdx);
  const { conf, synthetic: confSynthetic } = confidenceFromLatest(latest, selectedIdx);
  const { reason, synthetic: reasonSynthetic } = reasonFromLatest(latest, selectedIdx, action);
  const { pass: riskPass, reason: riskReason } = riskFromLatest(latest, selectedIdx, action, reason);

  const ageMs = num((latest.decision_age_ms as unknown) ?? (latest.age_ms as unknown), NaN);
  const decisionAgeMs = Number.isFinite(ageMs) ? ageMs : args.packetAgeMs ?? null;

  const mode = str(latest.strategy).replace(/^B_/, "");

  const o1 = orderFromLatest(latest, selectedIdx);
  const order = o1.side !== "NONE" || o1.size != null || o1.price != null ? o1 : synthOrder(latest, selectedIdx, action, conf, riskPass);

  const out = outcomeFromLatest(latest, selectedIdx);
  let outcome = out.outcome;
  let outcomeReason = out.reason;
  if (outcome === "NO_ORDER") {
    if (!riskPass || action === "RISK_BLOCKED") {
      outcome = "REJECTED";
      outcomeReason = riskReason || reason;
    } else if (order.side === "NONE") {
      outcome = "NO_ORDER";
    } else {
      outcome = "PENDING";
    }
  }

  const stale = (args.connected === false) || (typeof args.packetAgeMs === "number" && args.packetAgeMs > 1500) || false;

  return {
    symbol,
    action,
    confidence: conf,
    confidenceSynthetic: confSynthetic,
    decisionAgeMs,
    mode,
    reason,
    reasonSynthetic,
    riskPass,
    riskReason,
    orderSide: order.side,
    orderSize: order.size,
    orderPrice: order.price,
    orderRoute: order.route,
    outcome,
    outcomeReason,
    stale,
  };
}

export type DecisionEvent = {
  ts: number; // epoch ms
  symbol: string;
  action: DecisionAction;
  confidence: number | null;
  risk: "PASS" | "BLOCK";
  reason: string;
  outcome: StrategyDecision["outcome"];
  outcomeReason: string | null;
};

