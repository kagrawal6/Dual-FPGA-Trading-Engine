import { useMemo } from "react";

export type MiEvent = {
  ts: number; // seconds
  severity: "INFO" | "WARN" | "ERROR";
  sym: string; // symbol or ALL
  msg: string;
};

type Props = {
  events: MiEvent[];
};

function sevColor(s: MiEvent["severity"]): string {
  if (s === "ERROR") return "#f23645";
  if (s === "WARN") return "#f7931a";
  return "#787b86";
}

function fmtTs(ts: number): string {
  const d = new Date(ts * 1000);
  const hh = String(d.getHours()).padStart(2, "0");
  const mm = String(d.getMinutes()).padStart(2, "0");
  const ss = String(d.getSeconds()).padStart(2, "0");
  return `${hh}:${mm}:${ss}`;
}

export function MarketEventFeed({ events }: Props) {
  const rows = useMemo(() => events.slice(0, 40), [events]);

  return (
    <div className="tm-mi-event-feed" aria-label="Market event feed">
      <div className="tm-mi-panel-head">
        <div className="tm-mi-panel-title">MARKET EVENT FEED</div>
        <div className="tm-mi-panel-sub mono">{rows.length ? `${rows.length} recent` : "—"}</div>
      </div>
      <div className="tm-mi-event-list mono">
        {rows.length ? (
          rows.map((e) => (
            <div key={`${e.ts}-${e.severity}-${e.sym}-${e.msg}`} className="tm-mi-event-row">
              <span className="t">{fmtTs(e.ts)}</span>
              <span className="s" style={{ color: sevColor(e.severity) }}>
                {e.severity}
              </span>
              <span className="y">{e.sym}</span>
              <span className="m">{e.msg}</span>
            </div>
          ))
        ) : (
          <div className="tm-mi-empty">Waiting for telemetry stream…</div>
        )}
      </div>
    </div>
  );
}

