import type { DecisionEvent } from "../../strategyDerived";

type Props = {
  events: DecisionEvent[];
  onSelectSymbol?: (sym: string) => void;
};

function tone(e: DecisionEvent): string {
  if (e.action === "BUY") return "buy";
  if (e.action === "SELL") return "sell";
  if (e.action === "RISK_BLOCKED" || e.risk === "BLOCK") return "blocked";
  return "hold";
}

export function DecisionTimeline({ events, onSelectSymbol }: Props) {
  const items = events.slice(-20);
  return (
    <section className="tm-se-timeline">
      <div className="tm-se-panel-head">
        <div className="tm-se-panel-title">LAST 20 DECISIONS</div>
        <div className="tm-se-panel-sub mono">newest →</div>
      </div>
      <div className="tm-se-timeline-row mono">
        {items.map((e) => {
          const t = tone(e);
          const tip =
            `${new Date(e.ts).toLocaleTimeString()} ` +
            `${e.symbol} ${e.action} conf=${e.confidence != null ? e.confidence.toFixed(2) : "—"} ` +
            `risk=${e.risk} reason=${e.reason} outcome=${e.outcome}${e.outcomeReason ? ` (${e.outcomeReason})` : ""}`;
          return (
            <button
              key={`${e.ts}-${e.symbol}`}
              type="button"
              className={`tm-se-timeline-item tone-${t}`}
              title={tip}
              onClick={() => onSelectSymbol?.(e.symbol)}
            >
              <span className="sym">{e.symbol}</span>
              <span className="act">{e.action}</span>
              <span className={`rk ${e.risk === "PASS" ? "pass" : "block"}`}>{e.risk}</span>
            </button>
          );
        })}
      </div>
    </section>
  );
}

