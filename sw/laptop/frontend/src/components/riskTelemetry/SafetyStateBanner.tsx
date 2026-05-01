import { num } from "../../telemetryUtils";

type Props = {
  latest: Record<string, unknown>;
  connected: boolean;
  packetAgeMs: number | null;
};

type Safety = { label: string; tone: "good" | "warn" | "bad" | "muted"; detail?: string; source?: "REAL" | "DERIVED" };

export function SafetyStateBanner({ latest, connected, packetAgeMs }: Props) {
  const linkUp = Boolean(latest.link_up);
  const kill = Boolean(latest.kill_switch);
  const riskHalt = Boolean(latest.risk_halt);
  const rej = Math.max(0, num(latest.rej, 0));
  const throttle = Boolean(latest.throttle_active) || String(latest.throttle_state ?? "").toUpperCase().includes("ON");
  const age = packetAgeMs != null ? packetAgeMs : Number.isFinite(num(latest.stream_age_ms, NaN)) ? num(latest.stream_age_ms) : null;
  const stale = !connected || (age != null && age > 1500);

  const s: Safety = (() => {
    if (kill) return { label: "KILL SWITCH ACTIVE", tone: "bad", detail: "trading disabled", source: "REAL" };
    if (!linkUp) return { label: "LINK DOWN", tone: "bad", detail: "execution not trustworthy", source: "REAL" };
    if (stale) return { label: "STREAM STALE", tone: "warn", detail: "telemetry may be outdated", source: "DERIVED" };
    if (riskHalt) return { label: "RISK BLOCKING", tone: "warn", detail: "risk halt asserted", source: "REAL" };
    if (rej >= 3) return { label: "REJECT SPIKE", tone: "warn", detail: `rej=${rej}`, source: "REAL" };
    if (throttle) return { label: "THROTTLED", tone: "warn", detail: "rate limit active", source: "REAL" };
    return { label: "TRADING ENABLED", tone: "good", detail: "stream live, link up", source: "DERIVED" };
  })();

  return (
    <div className={`tm-rt-safety mono tone-${s.tone}`}>
      <div className="tm-rt-safety-left">
        <span className="k">SAFETY STATE</span>
        <span className="v">{s.label}</span>
      </div>
      <div className="tm-rt-safety-right">
        <span className="d">{s.detail ?? "—"}</span>
        <span className="tag">{s.source ?? "—"}</span>
      </div>
    </div>
  );
}

