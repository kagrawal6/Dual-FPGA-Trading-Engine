export type SpreadRegime = "TIGHT" | "NORMAL" | "WIDE" | "ABNORMAL" | "UNKNOWN";

export function clamp(x: number, lo: number, hi: number) {
  return Math.min(hi, Math.max(lo, x));
}

export function finiteOrNull(x: unknown): number | null {
  const n = typeof x === "number" ? x : Number(x);
  return Number.isFinite(n) ? n : null;
}

export function rollingMean(xs: number[]): number | null {
  let s = 0;
  let c = 0;
  for (const v of xs) {
    if (!Number.isFinite(v)) continue;
    s += v;
    c += 1;
  }
  return c ? s / c : null;
}

export function rollingStd(xs: number[]): number | null {
  const m = rollingMean(xs);
  if (m == null) return null;
  let s2 = 0;
  let c = 0;
  for (const v of xs) {
    if (!Number.isFinite(v)) continue;
    const d = v - m;
    s2 += d * d;
    c += 1;
  }
  if (!c) return null;
  return Math.sqrt(s2 / c);
}

export function zScore(cur: number | null, xs: number[]): number | null {
  if (cur == null || !Number.isFinite(cur)) return null;
  const m = rollingMean(xs);
  const sd = rollingStd(xs);
  if (m == null || sd == null || sd === 0) return null;
  return (cur - m) / sd;
}

export function percentile(cur: number | null, xs: number[]): number | null {
  if (cur == null || !Number.isFinite(cur)) return null;
  const vals = xs.filter((v) => Number.isFinite(v)).slice().sort((a, b) => a - b);
  if (!vals.length) return null;
  // inclusive percentile: share of historical values <= current
  let lo = 0;
  let hi = vals.length;
  while (lo < hi) {
    const mid = (lo + hi) >> 1;
    if (vals[mid] <= cur) lo = mid + 1;
    else hi = mid;
  }
  return (lo / vals.length) * 100;
}

export function spreadRegime(cur: number | null, spreadHist: number[]): SpreadRegime {
  if (cur == null || !Number.isFinite(cur)) return "UNKNOWN";
  const vals = spreadHist.filter((v) => Number.isFinite(v));
  if (vals.length < 8) {
    if (cur < 0.02) return "TIGHT";
    if (cur < 0.08) return "NORMAL";
    if (cur < 0.18) return "WIDE";
    return "ABNORMAL";
  }
  const m = rollingMean(vals);
  const sd = rollingStd(vals);
  const p = percentile(cur, vals);
  if (m != null && sd != null && cur > m + 2 * sd) return "ABNORMAL";
  if (p == null) return "UNKNOWN";
  if (p < 25) return "TIGHT";
  if (p <= 75) return "NORMAL";
  return "WIDE";
}

export function microprice(
  bid: number | null,
  ask: number | null,
  bidSize: number | null,
  askSize: number | null
): number | null {
  if (bid == null || ask == null || bidSize == null || askSize == null) return null;
  const den = bidSize + askSize;
  if (!Number.isFinite(den) || den <= 0) return null;
  return (ask * bidSize + bid * askSize) / den;
}

export function imbalance(bidSize: number | null, askSize: number | null): number | null {
  if (bidSize == null || askSize == null) return null;
  const den = bidSize + askSize;
  if (!Number.isFinite(den) || den <= 0) return null;
  return (bidSize - askSize) / den;
}

export type LadderRow = {
  side: "ASK" | "BID" | "MID";
  level: number; // 0 for top-level, +/-1 etc; MID uses 0
  price: number;
  size: number | null;
};

export function syntheticTopSizes(symIdx: number, spread: number | null, mid: number | null): { bidSize: number; askSize: number } {
  const s = spread != null && Number.isFinite(spread) ? spread : 0.05;
  const m = mid != null && Number.isFinite(mid) ? mid : 100;
  const base = 40 + ((symIdx * 17) % 60);
  const volBump = clamp(Math.round((Math.abs(s) * 800) % 40), 0, 40);
  const pxBump = clamp(Math.round((Math.abs(m) * 10) % 30), 0, 30);
  const bidSize = clamp(base + volBump + (pxBump % 15), 20, 140);
  const askSize = clamp(base + (40 - volBump) + ((pxBump + 7) % 15), 20, 140);
  return { bidSize, askSize };
}

export function syntheticLadder(
  bid: number | null,
  ask: number | null,
  mid: number | null,
  spread: number | null,
  symIdx: number,
  depth = 3
): LadderRow[] {
  if (bid == null || ask == null || mid == null) return [];
  const spr = spread != null && Number.isFinite(spread) ? spread : Math.max(0.01, ask - bid);
  const tick = clamp(spr / 3, 0.01, Math.max(0.01, spr));
  const { bidSize, askSize } = syntheticTopSizes(symIdx, spr, mid);

  const rows: LadderRow[] = [];
  for (let i = depth; i >= 1; i--) {
    const px = ask + tick * i;
    const size = clamp(Math.round(askSize * (0.55 ** i)), 8, 180);
    rows.push({ side: "ASK", level: i, price: px, size });
  }
  rows.push({ side: "ASK", level: 0, price: ask, size: askSize });
  rows.push({ side: "MID", level: 0, price: mid, size: null });
  rows.push({ side: "BID", level: 0, price: bid, size: bidSize });
  for (let i = 1; i <= depth; i++) {
    const px = bid - tick * i;
    const size = clamp(Math.round(bidSize * (0.55 ** i)), 8, 180);
    rows.push({ side: "BID", level: -i, price: px, size });
  }
  return rows;
}

