import type { StrategyDecision } from "../../strategyDerived";

type Props = {
  d: StrategyDecision;
};

function toneForAction(a: StrategyDecision["action"]): "buy" | "sell" | "hold" | "blocked" {
  if (a === "BUY") return "buy";
  if (a === "SELL") return "sell";
  if (a === "RISK_BLOCKED") return "blocked";
  return "hold";
}

export function StrategyDecisionStack({ d }: Props) {
  const t = toneForAction(d.action);
  return (
    <section className="tm-se-deck">
      <div className={`tm-se-card tm-se-card--decision tone-${t}`}>
        <div className="tm-se-card-k">DECISION</div>
        <div className="tm-se-card-main mono">
          <span className="sym">{d.symbol}</span> · <span className="act">{d.action}</span>
        </div>
        <div className="tm-se-card-sub mono">
          <span>
            confidence {d.confidence != null ? d.confidence.toFixed(2) : "—"}
            {d.confidenceSynthetic ? " (synthetic)" : ""}
          </span>
          <span className="sep">·</span>
          <span>age {d.decisionAgeMs != null ? `${Math.max(0, d.decisionAgeMs).toFixed(0)} ms` : "—"}</span>
          <span className="sep">·</span>
          <span>mode {d.mode || "—"}</span>
          {d.stale && (
            <>
              <span className="sep">·</span>
              <span className="stale">STALE</span>
            </>
          )}
        </div>
      </div>

      <div className="tm-se-card">
        <div className="tm-se-card-k">REASON</div>
        <div className="tm-se-card-main mono">{d.reason || "—"}</div>
        <div className="tm-se-card-sub mono">{d.reasonSynthetic ? "demo-derived" : "streamed"}</div>
      </div>

      <div className={`tm-se-card ${d.riskPass ? "tone-pass" : "tone-block"}`}>
        <div className="tm-se-card-k">RISK GATE</div>
        <div className="tm-se-card-main mono">{d.riskPass ? "PASS" : "BLOCKED"}</div>
        <div className="tm-se-card-sub mono">{d.riskReason || "—"}</div>
      </div>

      <div className="tm-se-card">
        <div className="tm-se-card-k">ORDER INTENT</div>
        <div className="tm-se-card-main mono">
          {d.orderSide === "NONE" ? "NONE" : `${d.orderSide} ${d.orderSize ?? "—"} @ ${d.orderPrice != null ? d.orderPrice.toFixed(2) : "—"}`}
        </div>
        <div className="tm-se-card-sub mono">
          <span>route {d.orderRoute ?? "—"}</span>
          <span className="sep">·</span>
          <span>
            outcome {d.outcome}
            {d.outcomeReason ? ` (${d.outcomeReason})` : ""}
          </span>
        </div>
      </div>
    </section>
  );
}

