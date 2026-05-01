import { normalizeSignal, num, riskLabel, signalColor, str } from "../telemetryUtils";

type Props = {
  latest: Record<string, unknown>;
  selectedIdx: number;
};

export function StatusPills({ latest, selectedIdx }: Props) {
  const rk = riskLabel(latest);
  const qps = num(latest.qps);
  const ops = num(latest.ops);
  const fps = num(latest.fps);
  const rej = num(latest.rej);
  const le = num(latest.link_err);
  const fillRate = fps / Math.max(ops, 1);
  const rejRate = rej / Math.max(ops, 1);
  const sigs = Array.isArray(latest.signal) ? latest.signal : [];
  const sig = normalizeSignal(sigs[selectedIdx]);

  const pills: { k: string; v: string; tone?: "good" | "warn" | "bad" | "accent" }[] = [
    { k: "fsm", v: str(latest.state).replace(/^B_/, ""), tone: "accent" },
    { k: "link", v: latest.link_up ? "UP" : "DOWN", tone: latest.link_up ? "good" : "bad" },
    { k: "risk", v: rk.text, tone: rk.tone === "ok" ? "good" : rk.tone === "warn" ? "warn" : "bad" },
    { k: "qps", v: `${qps.toLocaleString()}`, tone: "good" },
    { k: "ops", v: `${ops.toLocaleString()}` },
    { k: "fps", v: `${fps.toLocaleString()}`, tone: fps ? "good" : undefined },
    { k: "rej", v: `${rej.toLocaleString()}`, tone: rej ? "warn" : undefined },
    { k: "link_err", v: `${le}`, tone: le ? "bad" : undefined },
    { k: "fill÷order", v: fillRate.toFixed(3) },
    { k: "rej÷order", v: rejRate.toFixed(3), tone: rejRate > 0 ? "warn" : undefined },
    { k: "signal", v: sig, tone: sig === "BUY" ? "good" : sig === "SELL" ? "bad" : sig === "RISK_BLOCKED" ? "warn" : undefined },
  ];

  return (
    <div className="tm-status-strip">
      {pills.map((p) => (
        <span
          key={p.k}
          className={`tm-pill mono ${p.tone ? `tm-pill--${p.tone}` : ""}`}
          style={p.k === "signal" ? { color: signalColor(sig), borderColor: signalColor(sig) } : undefined}
        >
          <span className="tm-pill-k">{p.k}</span>
          <span className="tm-pill-v">{p.v}</span>
        </span>
      ))}
    </div>
  );
}
