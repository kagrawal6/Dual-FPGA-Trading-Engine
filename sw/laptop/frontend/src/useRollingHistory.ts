import { useEffect, useMemo, useRef, useState } from "react";
import { arrNum } from "./telemetryUtils";

type SymSeries = {
  t: number[];
  mid: number[];
  ema: number[];
  spread: number[];
  dev: number[];
  pos: number[];
  pnl: number[];
  trades: number[];
};

function makeEmpty(): SymSeries {
  return { t: [], mid: [], ema: [], spread: [], dev: [], pos: [], pnl: [], trades: [] };
}

export function useRollingHistory(
  latest: Record<string, unknown>,
  symCount: number,
  tsSec: number | null | undefined,
  maxLen = 900
) {
  const storeRef = useRef<SymSeries[]>([]);
  const t0Ref = useRef<number | null>(null);
  const [, bump] = useState(0);

  useEffect(() => {
    if (symCount <= 0) return;
    if (storeRef.current.length !== symCount) {
      storeRef.current = Array.from({ length: symCount }, () => makeEmpty());
      t0Ref.current = null;
    }
  }, [symCount]);

  useEffect(() => {
    if (!symCount) return;
    const tAbs = typeof tsSec === "number" && Number.isFinite(tsSec) ? tsSec : Date.now() / 1000;
    if (t0Ref.current == null) t0Ref.current = tAbs;
    const t = tAbs - (t0Ref.current ?? tAbs);

    const mid = arrNum(latest.mid, symCount, NaN);
    const ema = arrNum(latest.ema, symCount, NaN);
    const spr = arrNum(latest.spread, symCount, NaN);
    const pos = arrNum(latest.pos, symCount, NaN);
    const pnl = arrNum(latest.pnl_mtm, symCount, NaN);
    const trd = arrNum(latest.trades, symCount, NaN);

    const st = storeRef.current;
    for (let i = 0; i < symCount; i++) {
      const s = st[i] ?? (st[i] = makeEmpty());
      s.t.push(t);
      s.mid.push(mid[i]);
      s.ema.push(ema[i]);
      s.spread.push(spr[i]);
      s.pos.push(pos[i]);
      s.pnl.push(pnl[i]);
      s.trades.push(trd[i]);
      s.dev.push(Number.isFinite(mid[i]) && Number.isFinite(ema[i]) ? mid[i] - ema[i] : NaN);

      if (s.t.length > maxLen) {
        const k = s.t.length - maxLen;
        s.t.splice(0, k);
        s.mid.splice(0, k);
        s.ema.splice(0, k);
        s.spread.splice(0, k);
        s.pos.splice(0, k);
        s.pnl.splice(0, k);
        s.trades.splice(0, k);
        s.dev.splice(0, k);
      }
    }
    bump((x) => (x + 1) % 1_000_000);
  }, [latest, symCount, tsSec, maxLen]);

  const get = useMemo(() => {
    return (i: number): SymSeries => storeRef.current[i] ?? makeEmpty();
  }, []);

  return { get };
}

