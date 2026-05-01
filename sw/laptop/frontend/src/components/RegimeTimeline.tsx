import { useEffect, useMemo, useRef } from "react";

type Seg = { name: string; t0: number; t1: number; reason?: string };

type Props = {
  nowSec: number;
  regimeName: string;
  qps: number | null;
  ops: number | null;
  fps: number | null;
  rejDelta: number;
};

function colorFor(name: string): string {
  const m: Record<string, string> = {
    CALM: "rgba(8,153,129,0.70)",
    VOLATILE: "rgba(247,147,26,0.70)",
    BURST: "rgba(90,200,250,0.70)",
    ADVERSARIAL: "rgba(242,54,69,0.70)",
    UNKNOWN: "rgba(120,123,134,0.55)",
  };
  return m[name] ?? m.UNKNOWN;
}

function inferReason(next: string, qps: number | null, rejDelta: number): string | undefined {
  if (next === "BURST" && qps != null) return "Likely trigger: quote rate spike";
  if (next === "ADVERSARIAL" && rejDelta > 0) return "Likely trigger: rejects increased";
  if (next === "VOLATILE") return "Likely trigger: spread variance increased";
  if (next === "CALM") return "Likely trigger: quote rate normalized";
  return undefined;
}

export function RegimeTimeline({ nowSec, regimeName, qps, rejDelta }: Props) {
  const segsRef = useRef<Seg[]>([]);
  const lastRef = useRef<string>("UNKNOWN");

  useEffect(() => {
    const name = (regimeName || "UNKNOWN").toUpperCase();
    const prev = lastRef.current;
    lastRef.current = name;
    if (!segsRef.current.length) {
      segsRef.current = [{ name, t0: nowSec, t1: nowSec }];
      return;
    }
    const s = segsRef.current[segsRef.current.length - 1]!;
    s.t1 = nowSec;
    if (name !== prev) {
      const reason = inferReason(name, qps, rejDelta);
      segsRef.current.push({ name, t0: nowSec, t1: nowSec, reason });
      // cap by count; time window is applied at render
      if (segsRef.current.length > 50) segsRef.current.splice(0, segsRef.current.length - 50);
    }
  }, [nowSec, regimeName, qps, rejDelta]);

  const view = useMemo(() => {
    const horizon = 120;
    const tMin = nowSec - horizon;
    const segs = segsRef.current
      .map((s) => ({ ...s, t0: Math.max(s.t0, tMin), t1: Math.max(s.t1, tMin) }))
      .filter((s) => s.t1 >= tMin);
    const span = Math.max(1, nowSec - tMin);
    return { segs, tMin, span };
  }, [nowSec]);

  const latest = view.segs[view.segs.length - 1];

  return (
    <div className="tm-mi-regime-timeline" aria-label="Regime timeline">
      <div className="tm-mi-panel-head">
        <div className="tm-mi-panel-title">REGIME TIMELINE</div>
        <div className="tm-mi-panel-sub mono">
          {latest ? `${latest.name} · ${(latest.t1 - latest.t0).toFixed(0)}s` : "—"}
        </div>
      </div>
      <div className="tm-mi-regime-strip" role="img" aria-label="Recent regimes">
        {view.segs.map((s, i) => {
          const left = ((s.t0 - view.tMin) / view.span) * 100;
          const w = Math.max(0.6, ((s.t1 - s.t0) / view.span) * 100);
          return (
            <div
              key={`${s.name}-${i}-${s.t0}`}
              className="tm-mi-regime-seg mono"
              title={s.reason ? `${s.name}: ${s.reason}` : s.name}
              style={{ left: `${left}%`, width: `${w}%`, background: colorFor(s.name) }}
            >
              <span className="lbl">{s.name}</span>
            </div>
          );
        })}
      </div>
      {latest?.reason && <div className="tm-mi-regime-reason mono">{latest.reason}</div>}
    </div>
  );
}

