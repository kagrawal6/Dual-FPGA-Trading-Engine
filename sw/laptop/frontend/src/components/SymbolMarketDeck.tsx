import { useEffect } from "react";
import { arrNum, arrSignal, num, normalizeSignal, signalColor } from "../telemetryUtils";

type Props = {
  symbols: string[];
  latest: Record<string, unknown>;
  selectedIdx: number;
  onSelect: (i: number) => void;
};

const NS_PER_CYCLE = 10;

function fmtSigned(n: number, digits: number): string {
  if (!Number.isFinite(n)) return "—";
  if (n > 0) return `+${n.toFixed(digits)}`;
  return n.toFixed(digits);
}

function fmtPrice(n: number, digits: number): string {
  return Number.isFinite(n) ? n.toFixed(digits) : "—";
}

function LatencyStrip({ latest }: { latest: Record<string, unknown> }) {
  const cmin = num(latest.lat_min);
  const cmax = num(latest.lat_max);
  const lsum = num(latest.lat_sum);
  const lcnt = Math.max(1, num(latest.lat_cnt, 1));
  const last = num(latest.last_latency);
  const avgCy = lsum / lcnt;

  return (
    <div className="tm-latency-strip mono">
      <div className="tm-latency-strip-title">LATENCY</div>
      <dl className="tm-latency-strip-grid">
        <dt>min</dt>
        <dd>
          {Math.round(cmin)} cy <span className="tm-muted">({fmtPrice(cmin * NS_PER_CYCLE, 0)} ns)</span>
        </dd>
        <dt>max</dt>
        <dd>
          {Math.round(cmax)} cy <span className="tm-muted">({fmtPrice(cmax * NS_PER_CYCLE, 0)} ns)</span>
        </dd>
        <dt>sum</dt>
        <dd>{Number.isFinite(lsum) ? Math.round(lsum).toLocaleString() : "—"}</dd>
        <dt>count</dt>
        <dd>{Math.round(lcnt).toLocaleString()}</dd>
        <dt>avg</dt>
        <dd>
          {avgCy.toFixed(2)} cy <span className="tm-muted">({fmtPrice(avgCy * NS_PER_CYCLE, 1)} ns)</span>
        </dd>
        <dt>last</dt>
        <dd>
          {Math.round(last)} cy <span className="tm-muted">({fmtPrice(last * NS_PER_CYCLE, 0)} ns)</span>
        </dd>
      </dl>
      <p className="tm-latency-strip-note">B3: most recent single fill_processed sample (last).</p>
    </div>
  );
}

export function SymbolMarketDeck({ symbols, latest, selectedIdx, onSelect }: Props) {
  const n = symbols.length || 16;
  const pos = arrNum(latest.pos, n);
  const bid = arrNum(latest.bid, n);
  const ask = arrNum(latest.ask, n);
  const mid = arrNum(latest.mid, n);
  const ema = arrNum(latest.ema, n);
  const spr = arrNum(latest.spread, n);
  const pnl = arrNum(latest.pnl_mtm, n);
  const lf = arrNum(latest.last_fill, n);
  const trades = arrNum(latest.trades, n);
  const sig = arrSignal(latest.signal, n);

  useEffect(() => {
    const onKey = (e: KeyboardEvent) => {
      if (e.target instanceof HTMLInputElement || e.target instanceof HTMLTextAreaElement || e.target instanceof HTMLSelectElement) return;
      if (e.key === "ArrowUp") {
        e.preventDefault();
        onSelect(Math.max(0, selectedIdx - 1));
      } else if (e.key === "ArrowDown") {
        e.preventDefault();
        onSelect(Math.min(n - 1, selectedIdx + 1));
      }
    };
    window.addEventListener("keydown", onKey);
    return () => window.removeEventListener("keydown", onKey);
  }, [n, onSelect, selectedIdx]);

  const dev = (i: number) => (Number.isFinite(mid[i]) && Number.isFinite(ema[i]) ? mid[i] - ema[i] : NaN);

  const sigSel = normalizeSignal(Array.isArray(latest.signal) ? latest.signal[selectedIdx] : undefined);
  const maxAbsDev = Math.max(1e-9, ...symbols.map((_, i) => Math.abs(dev(i) || 0)));
  const maxSpr = Math.max(1e-9, ...spr.map((v) => (Number.isFinite(v) ? v : 0)));

  return (
    <div className="tm-per-symbol-stack">
      <LatencyStrip latest={latest} />

      <div className="tm-rail-head">
        <div className="tm-rail-title">PER-SYMBOL</div>
        <div className="tm-rail-sub mono">16 symbols · ↑↓ select row</div>
      </div>
      <div className="tm-scroll tm-scroll--table">
        <table className="tm-sym tm-sym-wide mono">
          <thead>
            <tr>
              <th>sym</th>
              <th>pos</th>
              <th>bid</th>
              <th>ask</th>
              <th>mid</th>
              <th>spread</th>
              <th>ema</th>
              <th>dev</th>
              <th>last_fill</th>
              <th>pnl_mtm</th>
              <th>trd</th>
              <th>sig</th>
            </tr>
          </thead>
          <tbody>
            {symbols.map((sym, i) => {
              const s = sig[i];
              const d = dev(i);
              return (
                <tr
                  key={sym}
                  data-selected={i === selectedIdx}
                  className={i === selectedIdx ? "tm-sym-row tm-sym-row--sel" : "tm-sym-row"}
                  onClick={() => onSelect(i)}
                >
                  <td>{sym}</td>
                  <td style={{ color: pos[i] > 0 ? "#089981" : pos[i] < 0 ? "#f23645" : undefined }}>{fmtSigned(pos[i], 0)}</td>
                  <td>{fmtPrice(bid[i], 2)}</td>
                  <td>{fmtPrice(ask[i], 2)}</td>
                  <td>{fmtPrice(mid[i], 2)}</td>
                  <td>{Number.isFinite(spr[i]) ? spr[i].toFixed(3) : "—"}</td>
                  <td>{fmtPrice(ema[i], 2)}</td>
                  <td style={{ color: d > 0 ? "#089981" : d < 0 ? "#f23645" : "#787b86" }}>{Number.isFinite(d) ? fmtSigned(d, 3) : "—"}</td>
                  <td>{fmtPrice(lf[i], 2)}</td>
                  <td style={{ color: pnl[i] >= 0 ? "#089981" : "#f23645" }}>{Number.isFinite(pnl[i]) ? fmtSigned(pnl[i], 2) : "—"}</td>
                  <td>{Number.isFinite(trades[i]) ? Math.round(trades[i]).toLocaleString() : "—"}</td>
                  <td style={{ color: signalColor(s), fontWeight: 700 }}>{s}</td>
                </tr>
              );
            })}
          </tbody>
        </table>
      </div>

      <div className="tm-sym-micro tm-sym-micro--fill" aria-label="Per-symbol micro snapshot">
        <div className="tm-sym-micro-head">
          <div className="tm-sym-micro-title">MICRO SNAPSHOT</div>
          <div className="tm-sym-micro-sub">dev | spread</div>
        </div>
        <div className="tm-sym-micro-grid mono">
          {symbols.map((sym, i) => {
            const d = dev(i);
            const s = spr[i];
            const dNorm = Number.isFinite(d) ? Math.min(1, Math.abs(d) / maxAbsDev) : 0;
            const sNorm = Number.isFinite(s) ? Math.min(1, s / maxSpr) : 0;
            return (
              <div key={`micro-${sym}`} className={i === selectedIdx ? "tm-sym-micro-row sel" : "tm-sym-micro-row"}>
                <span className="sym">{sym}</span>
                <span
                  className="bar dev"
                  style={{
                    ["--w" as any]: `${Math.round(dNorm * 100)}%`,
                    ["--c" as any]: d >= 0 ? "rgba(8,153,129,0.70)" : "rgba(242,54,69,0.70)",
                  }}
                />
                <span className="bar spr" style={{ ["--w" as any]: `${Math.round(sNorm * 100)}%`, ["--c" as any]: "rgba(90,200,250,0.55)" }} />
              </div>
            );
          })}
        </div>
      </div>

      <details className="tm-per-symbol-key mono">
        <summary>KEY · register mapping</summary>
        <ul>
          <li>
            <code>pos[i]</code> signed position
          </li>
          <li>
            <code>bid/ask/mid/spread/ema</code> from telemetry (fixed-point scaled in RTL)
          </li>
          <li>
            <code>dev</code> = mid − ema (strategy input)
          </li>
          <li>
            <code>last_fill[i]</code> last trade price
          </li>
          <li>
            <code>pnl_mtm</code> realized + unrealized MTM
          </li>
          <li>
            <code>trd</code> = trades[i] (fill count)
          </li>
          <li>
            <code>sig</code> = signal[i] → NONE, BUY, SELL, RISK_BLOCKED
          </li>
        </ul>
      </details>

      <div className="tm-selected-panel mono">
        <div className="tm-selected-kicker">SELECTED · {symbols[selectedIdx] ?? "?"}</div>
        <div className="tm-selected-grid">
          <div>
            <span className="tm-sel-l">position</span>
            <span className="tm-sel-v" style={{ color: pos[selectedIdx] > 0 ? "#089981" : pos[selectedIdx] < 0 ? "#f23645" : undefined }}>
              {fmtSigned(pos[selectedIdx] ?? 0, 0)}
            </span>
          </div>
          <div>
            <span className="tm-sel-l">bid / ask</span>
            <span className="tm-sel-v">
              {fmtPrice(bid[selectedIdx], 2)} / {fmtPrice(ask[selectedIdx], 2)}
            </span>
          </div>
          <div>
            <span className="tm-sel-l">mid</span>
            <span className="tm-sel-v">{fmtPrice(mid[selectedIdx], 4)}</span>
          </div>
          <div>
            <span className="tm-sel-l">spread</span>
            <span className="tm-sel-v">{Number.isFinite(spr[selectedIdx]) ? spr[selectedIdx].toFixed(4) : "—"}</span>
          </div>
          <div>
            <span className="tm-sel-l">ema</span>
            <span className="tm-sel-v">{fmtPrice(ema[selectedIdx], 4)}</span>
          </div>
          <div>
            <span className="tm-sel-l">mid − ema</span>
            <span className="tm-sel-v" style={{ color: (dev(selectedIdx) ?? 0) >= 0 ? "#089981" : "#f23645" }}>
              {Number.isFinite(dev(selectedIdx)) ? fmtSigned(dev(selectedIdx), 4) : "—"}
            </span>
          </div>
          <div>
            <span className="tm-sel-l">last_fill</span>
            <span className="tm-sel-v">{fmtPrice(lf[selectedIdx], 4)}</span>
          </div>
          <div>
            <span className="tm-sel-l">pnl_mtm</span>
            <span className="tm-sel-v" style={{ color: (pnl[selectedIdx] ?? 0) >= 0 ? "#089981" : "#f23645" }}>
              {Number.isFinite(pnl[selectedIdx]) ? fmtSigned(pnl[selectedIdx], 2) : "—"}
            </span>
          </div>
          <div>
            <span className="tm-sel-l">trd</span>
            <span className="tm-sel-v">{Number.isFinite(trades[selectedIdx]) ? Math.round(trades[selectedIdx]).toLocaleString() : "—"}</span>
          </div>
          <div>
            <span className="tm-sel-l">sig</span>
            <span className="tm-sel-v" style={{ color: signalColor(sigSel) }}>
              {sigSel}
            </span>
          </div>
        </div>
      </div>
    </div>
  );
}
