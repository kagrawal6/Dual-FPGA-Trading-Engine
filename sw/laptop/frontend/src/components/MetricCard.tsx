import Plot from "react-plotly.js";
import type { Data, Layout } from "plotly.js";

type Props = {
  label: string;
  value: string;
  tone?: "good" | "bad" | "warn" | "accent";
  subtitle?: string;
  spark?: { x: number[]; y: number[]; color: string } | null;
  onExpand?: () => void;
};

const toneColor: Record<NonNullable<Props["tone"]>, string> = {
  good: "#089981",
  bad: "#f23645",
  warn: "#f7931a",
  accent: "#2962ff",
};

function sparkLayout(): Partial<Layout> {
  return {
    paper_bgcolor: "rgba(0,0,0,0)",
    plot_bgcolor: "rgba(0,0,0,0)",
    margin: { l: 0, r: 0, t: 0, b: 0 },
    height: 44,
    autosize: true,
    showlegend: false,
    xaxis: { visible: false, fixedrange: true },
    yaxis: { visible: false, fixedrange: true },
  };
}

export function MetricCard({ label, value, tone, subtitle, spark, onExpand }: Props) {
  const clickable = Boolean(onExpand);
  const color = tone ? toneColor[tone] : undefined;

  const sparkData: Data[] =
    spark && spark.x.length > 1
      ? [
          {
            type: "scatter",
            mode: "lines",
            x: spark.x,
            y: spark.y,
            line: { color: spark.color, width: 2 },
            hoverinfo: "skip",
          },
        ]
      : [];

  const body = (
    <>
      <label>{label}</label>
      <div className="v" style={color ? { color } : undefined}>
        {value}
      </div>
      {subtitle && <div className="tm-metric-sub mono">{subtitle}</div>}
      {sparkData.length > 0 && (
        <div className="tm-metric-spark" aria-hidden="true">
          <Plot data={sparkData} layout={sparkLayout()} config={{ displayModeBar: false, responsive: true }} style={{ width: "100%", height: "100%" }} />
        </div>
      )}
    </>
  );

  if (!clickable) {
    return (
      <div className="tm-metric mono" data-clickable="false">
        {body}
      </div>
    );
  }

  return (
    <button type="button" className="tm-metric mono" onClick={onExpand}>
      {body}
    </button>
  );
}

