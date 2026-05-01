import { num } from "../../telemetryUtils";

type Row = { k: string; value: string; limit: string; status: "PASS" | "BLOCK"; note?: string };

type Props = {
  latest: Record<string, unknown>;
  selectedIdx: number;
  blockingHint?: string | null;
};

function pass(v: boolean): "PASS" | "BLOCK" {
  return v ? "PASS" : "BLOCK";
}

export function RiskGateMatrix({ latest, selectedIdx, blockingHint }: Props) {
  const posArr = Array.isArray(latest.pos) ? latest.pos : [];
  const pos = num(posArr[selectedIdx], 0);
  const maxPos = Math.max(1, num(latest.max_position, 1));

  const pnlArr = Array.isArray(latest.pnl_mtm) ? latest.pnl_mtm : [];
  const pnl = num(pnlArr[selectedIdx], 0);
  const maxLoss = Math.max(0, num(latest.max_loss, 0));

  const sprArr = Array.isArray(latest.spread) ? latest.spread : [];
  const spr = Math.max(0, num(sprArr[selectedIdx], 0));
  const thr = Math.max(0, num(latest.threshold, 0));

  const ops = Math.max(0, num(latest.ops, 0));
  const maxRate = Math.max(1, num(latest.max_order_rate, 1));

  const ageMs = Math.max(0, num(latest.heartbeat_age_ms, num(latest.age_ms, NaN)));
  const hbLimit = 1500;

  const linkUp = Boolean(latest.link_up);
  const kill = Boolean(latest.kill_switch);
  const throttle = String(latest.throttle_state ?? "—");
  const rej = Math.max(0, num(latest.rej, 0));

  const rows: Row[] = [
    { k: "Position", value: `${pos.toFixed(0)}`, limit: `±${maxPos.toFixed(0)}`, status: pass(Math.abs(pos) <= maxPos), note: Math.abs(pos) >= 0.92 * maxPos ? "near limit" : undefined },
    { k: "Loss", value: `${pnl.toFixed(2)}`, limit: `≥ -${maxLoss.toFixed(2)}`, status: pass(maxLoss <= 0 || pnl >= -maxLoss), note: maxLoss > 0 && pnl < -maxLoss ? "loss limit" : undefined },
    { k: "Spread", value: `${spr.toFixed(4)}`, limit: `≤ ${(thr * 1.6).toFixed(4)}`, status: pass(thr <= 0 || spr <= thr * 1.6), note: thr > 0 && spr > thr * 1.6 ? "wide" : undefined },
    { k: "Rate", value: `${ops.toFixed(0)}`, limit: `≤ ${maxRate.toFixed(0)}`, status: pass(ops <= maxRate), note: ops > maxRate ? "throttle" : undefined },
    { k: "Link", value: linkUp ? "UP" : "DOWN", limit: "UP", status: pass(linkUp) },
    { k: "Heartbeat", value: Number.isFinite(ageMs) ? `${ageMs.toFixed(0)} ms` : "—", limit: `${hbLimit} ms`, status: pass(!Number.isFinite(ageMs) || ageMs <= hbLimit), note: Number.isFinite(ageMs) && ageMs > hbLimit ? "stale" : undefined },
    { k: "Kill switch", value: kill ? "ON" : "OFF", limit: "OFF", status: pass(!kill) },
    { k: "Rejects", value: `${rej.toFixed(0)}`, limit: "0", status: pass(rej === 0), note: rej > 0 ? "rejecting" : undefined },
    { k: "Throttle", value: throttle, limit: "—", status: pass(true) },
  ];

  const hint = (blockingHint ?? "").toUpperCase();

  return (
    <section className="tm-se-matrix">
      <div className="tm-se-panel-head">
        <div className="tm-se-panel-title">RISK GATE</div>
        {hint ? <div className="tm-se-panel-sub mono">blocking: {hint}</div> : <div className="tm-se-panel-sub mono">checks: position · loss · spread · rate · link</div>}
      </div>
      <div className="tm-se-table mono">
        <div className="tm-se-tr tm-se-tr--head">
          <div>check</div>
          <div style={{ textAlign: "right" }}>value</div>
          <div style={{ textAlign: "right" }}>limit</div>
          <div style={{ textAlign: "right" }}>status</div>
        </div>
        {rows.map((r) => {
          const hot = hint && (r.k.toUpperCase().includes(hint) || (r.note ? r.note.toUpperCase().includes(hint) : false));
          return (
            <div key={r.k} className={`tm-se-tr ${r.status === "PASS" ? "is-pass" : "is-block"} ${hot ? "is-hot" : ""}`}>
              <div className="k">
                {r.k}
                {r.note ? <span className="note"> {r.note}</span> : null}
              </div>
              <div style={{ textAlign: "right" }}>{r.value}</div>
              <div style={{ textAlign: "right" }}>{r.limit}</div>
              <div style={{ textAlign: "right" }} className="st">
                {r.status}
              </div>
            </div>
          );
        })}
      </div>
    </section>
  );
}

