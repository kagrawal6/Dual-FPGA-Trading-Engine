import type { DecisionEvent } from "../../strategyDerived";
import { num } from "../../telemetryUtils";

type Props = {
  latest: Record<string, unknown>;
  events: DecisionEvent[];
};

export function LastWindowSummary({ latest, events }: Props) {
  const now = Date.now();
  const recent = events.filter((e) => now - e.ts < 10_000);
  const fills = recent.filter((e) => e.outcome === "FILLED").length;
  const rejects = recent.filter((e) => e.outcome === "REJECTED" || e.outcome === "BLOCKED").length;
  const blocks = recent.filter((e) => e.risk === "BLOCK").length;
  const total = recent.length || 1;
  const fillRatio = fills / total;

  const rejRaw = num(latest.rej, NaN);
  const rejTag = Number.isFinite(rejRaw) ? "REAL" : "DERIVED";

  return (
    <section className="tm-rt-window mono">
      <div className="tm-rt-window-head">
        <div className="t">LAST WINDOW</div>
        <div className="sub">{recent.length ? "10s derived" : "not streamed"}</div>
      </div>
      <div className="tm-rt-window-grid">
        <div>
          <span className="k">Fills</span>
          <span className="v">{fills.toFixed(0)}</span>
        </div>
        <div>
          <span className="k">Rejects</span>
          <span className="v">{rejects.toFixed(0)}</span>
        </div>
        <div>
          <span className="k">Blocks</span>
          <span className="v">{blocks.toFixed(0)}</span>
        </div>
        <div>
          <span className="k">Fill ratio</span>
          <span className="v">{Number.isFinite(fillRatio) ? `${(fillRatio * 100).toFixed(1)}%` : "—"}</span>
        </div>
      </div>
      <div className="tm-rt-window-foot">
        <span className="mono">rej counter</span> <span className="tag">{rejTag}</span>
      </div>
    </section>
  );
}

