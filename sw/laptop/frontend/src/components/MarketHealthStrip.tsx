import { num, str } from "../telemetryUtils";

type Props = {
  latest: Record<string, unknown>;
  wsOpen: boolean;
  ageMs: number | null;
  parseErrors: number | null;
  qps: number | null;
  ops: number | null;
  fps: number | null;
  linkUp: boolean;
};

function toneForHeartbeat(ageMs: number | null, wsOpen: boolean): "good" | "warn" | "bad" {
  if (!wsOpen) return "bad";
  if (ageMs == null) return "warn";
  if (ageMs > 1800) return "bad";
  if (ageMs > 650) return "warn";
  return "good";
}

function toneForParse(parseErrors: number | null): "good" | "warn" | "bad" {
  if (parseErrors == null) return "warn";
  if (parseErrors >= 50) return "bad";
  if (parseErrors >= 5) return "warn";
  return "good";
}

function Tile({ k, v, tone }: { k: string; v: string; tone: "good" | "warn" | "bad" | "accent" }) {
  return (
    <div className={`tm-mi-health-tile tm-mi-health-tile--${tone}`}>
      <div className="tm-mi-health-k">{k}</div>
      <div className="tm-mi-health-v mono">{v}</div>
    </div>
  );
}

export function MarketHealthStrip({ latest, wsOpen, ageMs, parseErrors, qps, ops, fps, linkUp }: Props) {
  const dropRate = num(latest.drop_rate, NaN);
  const wsLatency = num(latest.ws_latency_ms, NaN);
  const hbTone = toneForHeartbeat(ageMs, wsOpen);
  const peTone = toneForParse(parseErrors);

  const dropTone: "good" | "warn" | "bad" =
    Number.isFinite(dropRate) ? (dropRate > 0.02 ? "bad" : dropRate > 0.005 ? "warn" : "good") : "warn";

  const linkTone: "good" | "bad" = linkUp ? "good" : "bad";

  const linkState = linkUp ? "UP" : "DOWN";
  const conn = wsOpen ? "OPEN" : "CLOSED";
  const stall = Boolean(latest.hardware_stalled);
  const stallTone: "good" | "bad" = stall ? "bad" : "good";

  const fmtRate = (x: number | null) => (x != null && Number.isFinite(x) ? `${x.toFixed(2)}/s` : "--");
  const fmtMs = (x: number | null) => (x != null && Number.isFinite(x) ? `${Math.round(x)} ms` : "--");
  const fmtPct = (x: number) => `${(x * 100).toFixed(2)}%`;

  return (
    <div className="tm-mi-health mono" aria-label="Market data health">
      <div className="tm-mi-panel-head">
        <div className="tm-mi-panel-title">MARKET DATA HEALTH</div>
        <div className="tm-mi-panel-sub">{str(latest.state).replace(/^B_/, "") || "—"} · WS {conn}</div>
      </div>
      <div className="tm-mi-health-grid">
        <Tile k="QPS" v={fmtRate(qps)} tone="accent" />
        <Tile k="OPS" v={fmtRate(ops)} tone="accent" />
        <Tile k="FPS" v={fmtRate(fps)} tone="accent" />
        <Tile k="DROP RATE" v={Number.isFinite(dropRate) ? fmtPct(dropRate) : "--"} tone={dropTone} />
        <Tile k="PARSE ERR" v={parseErrors != null ? Math.round(parseErrors).toLocaleString() : "--"} tone={peTone} />
        <Tile k="HEARTBEAT AGE" v={fmtMs(ageMs)} tone={hbTone} />
        <Tile k="WS LATENCY" v={Number.isFinite(wsLatency) ? `${wsLatency.toFixed(0)} ms` : "--"} tone="warn" />
        <Tile k="LINK STATE" v={linkState} tone={linkTone} />
        <Tile k="HW STALL" v={stall ? "YES" : "NO"} tone={stallTone} />
      </div>
    </div>
  );
}

