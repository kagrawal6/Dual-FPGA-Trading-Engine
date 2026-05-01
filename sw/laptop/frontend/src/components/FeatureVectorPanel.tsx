import { useMemo } from "react";
import { normalizeSignal, signalColor } from "../telemetryUtils";
import { percentile, rollingStd, zScore } from "../marketDerivedMetrics";

type SymSeries = {
  t: number[];
  mid: number[];
  ema: number[];
  spread: number[];
  dev: number[];
  trades: number[];
};

type Props = {
  sym: string;
  latest: Record<string, unknown>;
  selectedIdx: number;
  series: SymSeries;
};

function fmtSigned(n: number | null, digits = 3): string {
  if (n == null || !Number.isFinite(n)) return "--";
  return n > 0 ? `+${n.toFixed(digits)}` : n.toFixed(digits);
}

function fmtNum(n: number | null, digits = 3): string {
  if (n == null || !Number.isFinite(n)) return "--";
  return n.toFixed(digits);
}

function Row({ k, v, tone }: { k: string; v: string; tone?: string }) {
  return (
    <div className="tm-mi-fv-row">
      <div className="tm-mi-fv-k">{k}</div>
      <div className="tm-mi-fv-v mono" style={tone ? { color: tone } : undefined}>
        {v}
      </div>
    </div>
  );
}

export function FeatureVectorPanel({ sym, latest, selectedIdx, series }: Props) {
  const sig = normalizeSignal(Array.isArray(latest.signal) ? latest.signal[selectedIdx] : undefined) || "—";

  const derived = useMemo(() => {
    const n = series.t.length;
    const win = Math.min(140, n);
    const midWin = series.mid.slice(-win);
    const devWin = series.dev.slice(-win);
    const sprWin = series.spread.slice(-win);

    const curDev = Number.isFinite(series.dev[n - 1]) ? series.dev[n - 1] : null;
    const z = zScore(curDev, devWin);
    const sprCur = Number.isFinite(series.spread[n - 1]) ? series.spread[n - 1] : null;
    const sprP = percentile(sprCur, sprWin);

    const vol = rollingStd(midWin);

    // trades delta as a proxy for last fill delta
    const tr = series.trades;
    const trCur = Number.isFinite(tr[n - 1]) ? tr[n - 1] : null;
    const trPrev = n >= 2 && Number.isFinite(tr[n - 2]) ? tr[n - 2] : null;
    const trD = trCur != null && trPrev != null ? trCur - trPrev : null;

    return { curDev, z, sprP, vol, trD };
  }, [series]);

  const sigTone = signalColor(sig);
  const zTone = derived.z != null ? (Math.abs(derived.z) >= 2 ? "#f7931a" : "#787b86") : undefined;

  return (
    <div className="tm-mi-fv" aria-label="Feature vector panel">
      <div className="tm-mi-panel-head">
        <div className="tm-mi-panel-title">FEATURE VECTOR</div>
        <div className="tm-mi-panel-sub mono">SELECTED · {sym || "—"}</div>
      </div>
      <div className="tm-mi-fv-grid">
        <Row k="EMA DEV" v={fmtSigned(derived.curDev, 4)} tone={derived.curDev != null ? (derived.curDev >= 0 ? "#089981" : "#f23645") : undefined} />
        <Row k="Z-SCORE" v={fmtSigned(derived.z, 2)} tone={zTone} />
        <Row k="SPREAD PCTL" v={derived.sprP != null ? `${Math.round(derived.sprP)}%` : "--"} />
        <Row k="VOL PROXY" v={fmtNum(derived.vol, 4)} />
        <Row k="LAST FILL Δ" v={derived.trD != null ? fmtSigned(derived.trD, 0) : "--"} tone={derived.trD != null && derived.trD > 0 ? "#5AC8FA" : undefined} />
        <Row k="SIGNAL" v={sig} tone={sigTone} />
      </div>
    </div>
  );
}

