import type { Data, Layout } from "plotly.js";
import Plot from "react-plotly.js";
import { num } from "../telemetryUtils";

type Props = {
  latest: Record<string, unknown>;
  histXNs: number[];
  histY: number[];
  latT?: number[];
  latLastCy?: number[];
};

const NS = 10;

export function LatencyTelemetry({ latest, histXNs, histY, latT, latLastCy }: Props) {
  const latMin = num(latest.lat_min);
  const latMax = num(latest.lat_max);
  const latSum = num(latest.lat_sum);
  const latCnt = Math.max(1, num(latest.lat_cnt, 1));
  const last = num(latest.last_latency);
  const avg = latSum / latCnt;

  const bars: Data[] =
    histY.length > 0
      ? [{ type: "bar", x: histXNs, y: histY, marker: { color: "#2962ff" }, name: "fills" }]
      : [];

  const layout: Partial<Layout> = {
    title: { text: "Latency histogram (ns bin centers)", font: { size: 11, color: "#d1d4dc" } },
    paper_bgcolor: "#131722",
    plot_bgcolor: "#131722",
    font: { color: "#787b86", size: 9 },
    margin: { l: 40, r: 6, t: 28, b: 22 },
    height: undefined,
    autosize: true,
    xaxis: { gridcolor: "#2a2e39", color: "#787b86" },
    yaxis: { gridcolor: "#2a2e39", color: "#787b86" },
  };

  const latLine: Data[] =
    latT && latLastCy && latT.length > 1 && latLastCy.length > 1
      ? [
          {
            type: "scatter",
            mode: "lines",
            x: latT,
            y: latLastCy,
            line: { color: "#5AC8FA", width: 2 },
            name: "last_latency (cy)",
          },
        ]
      : [];

  const lineLayout: Partial<Layout> = {
    title: { text: "Last latency trend (cycles)", font: { size: 11, color: "#d1d4dc" } },
    paper_bgcolor: "#131722",
    plot_bgcolor: "#131722",
    font: { color: "#787b86", size: 9 },
    margin: { l: 40, r: 6, t: 28, b: 22 },
    height: undefined,
    autosize: true,
    xaxis: { gridcolor: "#2a2e39", color: "#787b86" },
    yaxis: { gridcolor: "#2a2e39", color: "#787b86" },
  };

  return (
    <div className="tm-latency-stack">
      <div className="tm-latency-card mono">
        <div className="tm-latency-card-title">Latency engine</div>
        <div className="tm-latency-grid">
          <div>
            <span className="tm-lat-lbl">min</span>
            <span className="tm-lat-val">
              {latMin} cy <span className="tm-lat-sub">/ {(latMin * NS).toFixed(0)} ns</span>
            </span>
          </div>
          <div>
            <span className="tm-lat-lbl">avg</span>
            <span className="tm-lat-val">
              {avg.toFixed(0)} cy <span className="tm-lat-sub">/ {(avg * NS).toFixed(2)} µs</span>
            </span>
          </div>
          <div>
            <span className="tm-lat-lbl">max</span>
            <span className="tm-lat-val">
              {latMax} cy <span className="tm-lat-sub">/ {(latMax * NS).toFixed(2)} µs</span>
            </span>
          </div>
          <div>
            <span className="tm-lat-lbl">last</span>
            <span className="tm-lat-val">
              {last} cy <span className="tm-lat-sub">/ {(last * NS).toFixed(2)} ns</span>
            </span>
          </div>
        </div>
        <div className="tm-latency-hint">10 ns / cycle @ 50 MHz link timing context</div>
      </div>
      <div className="tm-plot tm-plot--compact">
        {bars.length > 0 ? (
          <Plot data={bars} layout={layout} config={{ displayModeBar: false, responsive: true }} style={{ width: "100%", height: "100%" }} />
        ) : (
          <div className="tm-plot-empty mono">No histogram yet</div>
        )}
      </div>
      <div className="tm-plot tm-plot--compact">
        {latLine.length > 0 ? (
          <Plot data={latLine} layout={lineLayout} config={{ displayModeBar: false, responsive: true }} style={{ width: "100%", height: "100%" }} />
        ) : (
          <div className="tm-plot-empty mono">No latency trend yet</div>
        )}
      </div>
    </div>
  );
}
