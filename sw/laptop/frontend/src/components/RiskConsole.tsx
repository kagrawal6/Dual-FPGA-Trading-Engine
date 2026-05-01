import { useState } from "react";
import { num } from "../telemetryUtils";

type Props = {
  latest: Record<string, unknown>;
  demoMode: boolean;
};

function stratIdxFromLatest(latest: Record<string, unknown>): number {
  const s = String(latest.strategy ?? "");
  return s === "NN" || s === "ML" ? 2 : 0;
}

export function RiskConsole({ latest, demoMode }: Props) {
  const [armed, setArmed] = useState(false);
  const [threshold, setThreshold] = useState(() => num(latest.threshold, 1));
  const [maxPos, setMaxPos] = useState(() => num(latest.max_position, 500));
  const [maxRate, setMaxRate] = useState(() => num(latest.max_order_rate, 1000));
  const [maxLoss, setMaxLoss] = useState(() => num(latest.max_loss, 100));
  const [strategy, setStrategy] = useState(() => stratIdxFromLatest(latest));
  const [msg, setMsg] = useState("");

  const apply = async () => {
    if (!armed) {
      setMsg("Arm edits to apply risk changes.");
      return;
    }
    if (!demoMode) {
      setMsg("UART: change risk on PYNQ / telemetry_server (laptop JSON is read-only).");
      return;
    }
    const r = await fetch("/api/demo-risk", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        threshold,
        max_position: maxPos,
        max_order_rate: maxRate,
        max_loss: maxLoss,
        strategy,
      }),
    });
    const j = (await r.json()) as { msg: string };
    setMsg(j.msg ?? "ok");
    setArmed(false);
  };

  return (
    <section className="tm-risk-console">
      <div className="tm-risk-title">Risk & strategy</div>
      <div className="tm-risk-top">
        <button type="button" className={`tm-btn ${armed ? "tm-btn--danger" : ""}`} onClick={() => setArmed((v) => !v)}>
          {armed ? "Edits armed" : "Edit risk limits"}
        </button>
        <span className="tm-risk-top-hint mono">{demoMode ? "demo writes enabled" : "read-only (hardware)"}</span>
      </div>
      <div className="tm-risk-grid">
        <label className="tm-risk-field">
          <span>threshold ($)</span>
          <input disabled={!armed} type="number" step={0.05} value={threshold} onChange={(e) => setThreshold(Number(e.target.value))} />
        </label>
        <label className="tm-risk-field">
          <span>max_position</span>
          <input disabled={!armed} type="number" step={10} value={maxPos} onChange={(e) => setMaxPos(Number(e.target.value))} />
        </label>
        <label className="tm-risk-field">
          <span>max_order_rate</span>
          <input disabled={!armed} type="number" step={50} value={maxRate} onChange={(e) => setMaxRate(Number(e.target.value))} />
        </label>
        <label className="tm-risk-field">
          <span>max_loss ($)</span>
          <input disabled={!armed} type="number" step={5} value={maxLoss} onChange={(e) => setMaxLoss(Number(e.target.value))} />
        </label>
        <label className="tm-risk-field tm-risk-field--wide">
          <span>strategy</span>
          <select disabled={!armed} value={strategy} onChange={(e) => setStrategy(Number(e.target.value))}>
            <option value={0}>Mean reversion (0)</option>
            <option value={2}>Neural net (2)</option>
          </select>
        </label>
      </div>
      <div className="tm-risk-actions">
        <button type="button" className="tm-btn tm-btn--primary" disabled={!armed} onClick={apply}>
          Apply
        </button>
        {msg && <span className="tm-risk-msg mono">{msg}</span>}
      </div>
    </section>
  );
}
