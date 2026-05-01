import { num } from "../../telemetryUtils";

type Props = {
  latest: Record<string, unknown>;
  connected: boolean;
  packetAgeMs: number | null;
  hardwareStalled: boolean;
  parseErrors: number;
};

export function StreamDiagnosticsBanner({ latest, connected, packetAgeMs, hardwareStalled, parseErrors }: Props) {
  const linkUp = Boolean(latest.link_up);
  const age = packetAgeMs != null ? packetAgeMs : Number.isFinite(num(latest.stream_age_ms, NaN)) ? num(latest.stream_age_ms) : null;
  const stale = !connected || (age != null && age > 1500);

  const state = !linkUp ? "LINK DOWN" : stale ? "STREAM: STALE" : "STREAM: LIVE";
  const tone = !linkUp ? "bad" : stale ? "warn" : "good";

  const dropped = Number.isFinite(num(latest.dropped_frames, NaN)) ? num(latest.dropped_frames) : null;

  return (
    <section className={`tm-rt-stream mono tone-${tone}`}>
      <div className="tm-rt-stream-top">
        <div className="s">{state}</div>
        <div className="age">{age != null && Number.isFinite(age) ? `Last packet: ${age.toFixed(0)} ms ago` : "Last packet: —"}</div>
      </div>
      <div className="tm-rt-stream-grid">
        <div>
          <span className="k">Heartbeat</span>
          <span className="v">{stale ? "STALE" : "OK"}</span>
        </div>
        <div>
          <span className="k">Dropped</span>
          <span className="v">{dropped != null ? dropped.toFixed(0) : "not streamed"}</span>
        </div>
        <div>
          <span className="k">Parse errors</span>
          <span className="v">{Number.isFinite(parseErrors) ? parseErrors.toFixed(0) : "—"}</span>
        </div>
        <div>
          <span className="k">HW stall</span>
          <span className="v">{hardwareStalled ? "YES" : "no"}</span>
        </div>
      </div>
      {!linkUp && <div className="tm-rt-stream-warn">Execution data is not trustworthy.</div>}
      {stale && linkUp && <div className="tm-rt-stream-warn">Telemetry may be outdated.</div>}
    </section>
  );
}

