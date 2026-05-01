/** Helpers for Board B NDJSON `latest` object (matches board_b_dashboard / telemetry_server). */

export function num(v: unknown, d = 0): number {
  const x = Number(v);
  return Number.isFinite(x) ? x : d;
}

export function str(v: unknown): string {
  if (v == null) return "—";
  return String(v);
}

export function arrNum(v: unknown, len: number, fill = 0): number[] {
  if (!Array.isArray(v)) return Array(len).fill(fill);
  return Array.from({ length: len }, (_, i) => num(v[i], fill));
}

export function arrStr(v: unknown, len: number, fill = "—"): string[] {
  if (!Array.isArray(v)) return Array(len).fill(fill);
  return Array.from({ length: len }, (_, i) => str(v[i] ?? fill));
}

/** RTL / NDJSON: 0=NONE, 1=BUY, 2=SELL, 3=RISK_BLOCKED (packed per symbol). */
const SIGNAL_ENUM = ["NONE", "BUY", "SELL", "RISK_BLOCKED"] as const;

export function normalizeSignal(v: unknown): string {
  if (typeof v === "number" && Number.isFinite(v)) {
    const k = Math.max(0, Math.min(3, Math.floor(v)));
    return SIGNAL_ENUM[k] ?? "NONE";
  }
  const s = String(v ?? "NONE")
    .trim()
    .toUpperCase();
  if (s === "" || s === "—") return "NONE";
  if (s === "RISK_BLOCK") return "RISK_BLOCKED";
  if (/^-?\d+$/.test(s)) {
    const k = Math.max(0, Math.min(3, parseInt(s, 10)));
    return SIGNAL_ENUM[k] ?? "NONE";
  }
  return s;
}

export function arrSignal(v: unknown, len: number): string[] {
  if (!Array.isArray(v)) return Array(len).fill("NONE");
  return Array.from({ length: len }, (_, i) => normalizeSignal(v[i]));
}

export function riskLabel(latest: Record<string, unknown>): { text: string; tone: "ok" | "warn" | "bad" } {
  if (Boolean(latest.risk_halt)) return { text: "HALTED", tone: "bad" };
  const rej = num(latest.rej);
  if (rej > 0) return { text: "REJECTING", tone: "warn" };
  return { text: "OK", tone: "ok" };
}

export function signalColor(sig: string): string {
  const s = normalizeSignal(sig);
  if (s === "BUY") return "#089981";
  if (s === "SELL") return "#f23645";
  if (s === "RISK_BLOCKED" || s === "REJECT") return "#f7931a";
  return "#787b86";
}
