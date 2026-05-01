import { num, str } from "../../telemetryUtils";

type Props = {
  latest: Record<string, unknown>;
};

function synthRegime(latest: Record<string, unknown>): { regime: string; conf: number; source: "SYNTHETIC" | "STREAMED" } {
  const r = String(latest.cnn_regime ?? latest.regime ?? "").trim().toUpperCase();
  const rc = num(latest.cnn_confidence, num(latest.regime_confidence, NaN));
  if (r) return { regime: r, conf: Number.isFinite(rc) ? Math.max(0, Math.min(1, rc)) : 0.62, source: latest.cnn_regime || latest.regime ? "STREAMED" : "SYNTHETIC" };

  const edge = Boolean(latest.regime_edge);
  const rej = num(latest.rej, 0);
  const le = num(latest.link_err, 0);
  if (edge || rej > 0 || le > 0) return { regime: "BURST", conf: 0.74, source: "SYNTHETIC" };
  return { regime: "CALM", conf: 0.58, source: "SYNTHETIC" };
}

export function CnnAssistPanel({ latest }: Props) {
  const enabled = latest.cnn_enabled != null ? Boolean(latest.cnn_enabled) : null;
  const state = latest.cnn_state != null ? str(latest.cnn_state).toUpperCase() : enabled === false ? "DISABLED" : "SYNTHETIC";
  const used = latest.cnn_used != null ? Boolean(latest.cnn_used) : true;
  const hint = latest.cnn_strategy_hint != null ? str(latest.cnn_strategy_hint) : "momentum_guarded";
  const { regime, conf, source } = synthRegime(latest);

  return (
    <section className="tm-se-cnn">
      <div className="tm-se-panel-head">
        <div className="tm-se-panel-title">CNN ASSIST</div>
        <div className="tm-se-panel-sub mono">{source === "SYNTHETIC" ? "SYNTHETIC / demo-derived" : "streamed fields"}</div>
      </div>
      <div className="tm-se-cnn-body mono">
        <div className="r">
          <span className="k">state</span>
          <span className="v">{state}</span>
        </div>
        <div className="r">
          <span className="k">regime</span>
          <span className="v">{regime}</span>
        </div>
        <div className="r">
          <span className="k">confidence</span>
          <span className="v">{conf.toFixed(2)}</span>
        </div>
        <div className="r">
          <span className="k">suggested mode</span>
          <span className="v">{hint}</span>
        </div>
        <div className="r">
          <span className="k">used</span>
          <span className="v">{used ? "yes" : "no"}</span>
        </div>
        <div className="r">
          <span className="k">enabled</span>
          <span className="v">{enabled == null ? "—" : enabled ? "yes" : "no"}</span>
        </div>
      </div>
    </section>
  );
}

