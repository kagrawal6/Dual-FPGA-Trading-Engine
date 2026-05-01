import { useMemo } from "react";
import { syntheticLadder, syntheticTopSizes, microprice, imbalance, spreadRegime } from "../marketDerivedMetrics";

type Props = {
  sym: string;
  symIdx: number;
  bid: number | null;
  ask: number | null;
  mid: number | null;
  spread: number | null;
  spreadHist: number[];
};

function fmt(n: number | null, digits = 2): string {
  if (n == null || !Number.isFinite(n)) return "--";
  return n.toFixed(digits);
}

function fmtSigned(n: number | null, digits = 2): string {
  if (n == null || !Number.isFinite(n)) return "--";
  return n > 0 ? `+${n.toFixed(digits)}` : n.toFixed(digits);
}

export function MarketQuoteBook({ sym, symIdx, bid, ask, mid, spread, spreadHist }: Props) {
  const sizes = useMemo(() => syntheticTopSizes(symIdx, spread, mid), [symIdx, spread, mid]);
  const mp = useMemo(() => microprice(bid, ask, sizes.bidSize, sizes.askSize), [bid, ask, sizes]);
  const imb = useMemo(() => imbalance(sizes.bidSize, sizes.askSize), [sizes]);
  const sprReg = useMemo(() => spreadRegime(spread, spreadHist), [spread, spreadHist]);
  const ladder = useMemo(() => syntheticLadder(bid, ask, mid, spread, symIdx, 3), [bid, ask, mid, spread, symIdx]);

  return (
    <div className="tm-mi-quote-book" aria-label="Selected symbol quote book">
      <div className="tm-mi-panel-head">
        <div className="tm-mi-panel-title">SELECTED SYMBOL QUOTE BOOK</div>
        <div className="tm-mi-panel-sub mono">SYMBOL: {sym || "--"}</div>
      </div>

      <div className="tm-mi-qb-top mono">
        <div className="tm-mi-qb-kv">
          <span className="k">BID</span>
          <span className="v">{fmt(bid, 2)}</span>
          <span className="s">size {sizes.bidSize}</span>
        </div>
        <div className="tm-mi-qb-kv">
          <span className="k">ASK</span>
          <span className="v">{fmt(ask, 2)}</span>
          <span className="s">size {sizes.askSize}</span>
        </div>
        <div className="tm-mi-qb-kv">
          <span className="k">MID</span>
          <span className="v">{fmt(mid, 2)}</span>
          <span className="s">spr {fmt(spread, 3)}</span>
        </div>
        <div className="tm-mi-qb-kv">
          <span className="k">MICROPRICE</span>
          <span className="v">{fmt(mp, 2)}</span>
          <span className="s">IMB {fmtSigned(imb, 2)}</span>
        </div>
        <div className="tm-mi-qb-kv">
          <span className="k">SPREAD REGIME</span>
          <span className={`v tag tag--${sprReg.toLowerCase()}`}>{sprReg}</span>
          <span className="s">pctl {spreadHist.length ? "ok" : "--"}</span>
        </div>
      </div>

      <div className="tm-mi-qb-ladder mono" aria-label="Synthetic depth ladder">
        {ladder.length ? (
          ladder.map((r, i) => {
            const side = r.side;
            const cls =
              side === "ASK" ? "ask" : side === "BID" ? "bid" : "mid";
            const lab =
              side === "MID"
                ? "MID"
                : side === "ASK"
                  ? r.level === 0
                    ? "ASK"
                    : `ASK +${r.level}`
                  : r.level === 0
                    ? "BID"
                    : `BID ${r.level}`;
            return (
              <div key={`${side}-${i}`} className={`tm-mi-qb-row tm-mi-qb-row--${cls}`}>
                <span className="lvl">{lab}</span>
                <span className="px">{fmt(r.price, 2)}</span>
                <span className="sz">{r.size != null ? `size ${r.size}` : ""}</span>
              </div>
            );
          })
        ) : (
          <div className="tm-mi-empty">Waiting for telemetry stream…</div>
        )}
      </div>
    </div>
  );
}

