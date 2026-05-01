import type { StrategyDecision } from "../../strategyDerived";

type Props = {
  d: StrategyDecision;
};

export function OrderIntentOutcome({ d }: Props) {
  const intent = d.orderSide === "NONE" ? "NONE" : `${d.orderSide} ${d.orderSize ?? "—"}`;
  const intentPx = d.orderSide === "NONE" ? "—" : d.orderPrice != null ? d.orderPrice.toFixed(2) : "—";
  const out = d.outcome;
  const outReason = d.outcomeReason ?? (out === "REJECTED" || out === "BLOCKED" ? d.riskReason || d.reason : null);

  return (
    <section className="tm-se-io">
      <div className="tm-se-panel-head">
        <div className="tm-se-panel-title">INTENT VS OUTCOME</div>
        <div className="tm-se-panel-sub mono">{d.orderRoute ? `route ${d.orderRoute}` : "order surface"}</div>
      </div>
      <div className="tm-se-io-grid mono">
        <div className="h">INTENT</div>
        <div className="h">OUTCOME</div>
        <div className="a">{intent}</div>
        <div className={`b ${out === "FILLED" ? "good" : out === "REJECTED" || out === "BLOCKED" ? "bad" : out === "PENDING" ? "warn" : ""}`}>{out}</div>
        <div className="a sub">@ {intentPx}</div>
        <div className="b sub">{outReason ? outReason : out === "NO_ORDER" ? "NO_ORDER" : "—"}</div>
      </div>
      <div className="tm-se-mini-flow mono">
        <div className="n">STRATEGY</div>
        <div className="arrow">→</div>
        <div className="n">RISK</div>
        <div className="arrow">→</div>
        <div className="n">ORDER</div>
        <div className="arrow">→</div>
        <div className="n">EXCHANGE</div>
        <div className="v">{d.action}</div>
        <div />
        <div className={`v ${d.riskPass ? "good" : "bad"}`}>{d.riskPass ? "PASS" : "BLOCK"}</div>
        <div />
        <div className="v">{d.orderSide === "NONE" ? "NONE" : d.orderSide}</div>
        <div />
        <div className="v">{d.outcome}</div>
      </div>
    </section>
  );
}

