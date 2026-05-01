import { num } from "../../telemetryUtils";

type Props = {
  latest: Record<string, unknown>;
  selectedIdx: number;
  confidence: number | null;
  confidenceSynthetic: boolean;
};

function clamp01(x: number): number {
  if (!Number.isFinite(x)) return 0;
  return Math.max(0, Math.min(1, x));
}

function bar(x: number): string {
  const n = Math.round(clamp01(x) * 10);
  return "█".repeat(n) + "░".repeat(10 - n);
}

export function FeaturePressureBars({ latest, selectedIdx, confidence, confidenceSynthetic }: Props) {
  const devArr = Array.isArray(latest.dev) ? latest.dev : [];
  const sprArr = Array.isArray(latest.spread) ? latest.spread : [];
  const posArr = Array.isArray(latest.pos) ? latest.pos : [];
  const pnlArr = Array.isArray(latest.pnl_mtm) ? latest.pnl_mtm : [];

  const dev = Math.abs(num(devArr[selectedIdx], 0));
  const spr = Math.max(0, num(sprArr[selectedIdx], 0));
  const pos = Math.abs(num(posArr[selectedIdx], 0));
  const pnl = num(pnlArr[selectedIdx], 0);

  const maxPos = Math.max(1, num(latest.max_position, 1));
  const maxLoss = Math.max(0, num(latest.max_loss, 0));
  const ageMs = num(latest.heartbeat_age_ms, num(latest.age_ms, NaN));

  const emaDev = clamp01(dev / 0.35);
  const spread = clamp01(spr / 0.35);
  const posUtil = clamp01(pos / maxPos);
  const pnlPress = maxLoss > 0 ? clamp01(Math.max(0, -pnl) / maxLoss) : 0;
  const latPress = Number.isFinite(ageMs) ? clamp01(ageMs / 1500) : 0;
  const conf = confidence != null ? clamp01(confidence) : 0;

  const rows: { k: string; v: number; label: string; tone?: "good" | "warn" | "bad" }[] = [
    { k: "EMA DEV", v: emaDev, label: dev.toFixed(3), tone: emaDev > 0.8 ? "warn" : undefined },
    { k: "SPREAD", v: spread, label: spr.toFixed(4), tone: spread > 0.8 ? "warn" : undefined },
    { k: "POSITION UTIL", v: posUtil, label: posUtil.toFixed(2), tone: posUtil > 0.92 ? "bad" : posUtil > 0.8 ? "warn" : undefined },
    { k: "PNL PRESSURE", v: pnlPress, label: pnlPress.toFixed(2), tone: pnlPress > 0.7 ? "warn" : undefined },
    { k: "LATENCY", v: latPress, label: latPress.toFixed(2), tone: latPress > 0.7 ? "warn" : undefined },
    { k: "CONFIDENCE", v: conf, label: `${conf.toFixed(2)}${confidenceSynthetic ? " s" : ""}`, tone: conf < 0.25 ? "warn" : undefined },
  ];

  return (
    <section className="tm-se-pressure">
      <div className="tm-se-panel-head">
        <div className="tm-se-panel-title">FEATURE PRESSURE</div>
        <div className="tm-se-panel-sub mono">selected symbol</div>
      </div>
      <div className="tm-se-pressure-body mono">
        {rows.map((r) => (
          <div key={r.k} className={`tm-se-pr ${r.tone ? `is-${r.tone}` : ""}`}>
            <div className="k">{r.k}</div>
            <div className="b">{bar(r.v)}</div>
            <div className="v">{r.label}</div>
          </div>
        ))}
      </div>
    </section>
  );
}

