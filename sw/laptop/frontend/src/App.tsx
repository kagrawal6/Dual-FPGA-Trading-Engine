import { useEffect, useLayoutEffect, useMemo, useRef, useState } from "react";
import Plot from "react-plotly.js";
import type { Data, Layout } from "plotly.js";
import { LatencyTelemetry } from "./components/LatencyTelemetry";
import { GlobeGlRandomArcs } from "./components/GlobeGlRandomArcs";
import { MetricCard } from "./components/MetricCard";
import { MarketHealthStrip } from "./components/MarketHealthStrip";
import { FeatureVectorPanel } from "./components/FeatureVectorPanel";
import { MarketQuoteBook } from "./components/MarketQuoteBook";
import { RegimeTimeline } from "./components/RegimeTimeline";
import { MarketEventFeed, type MiEvent } from "./components/MarketEventFeed";
import { RiskConsole } from "./components/RiskConsole";
import { StatusPills } from "./components/StatusPills";
import { SymbolMarketDeck } from "./components/SymbolMarketDeck";
import { TradeMarkHeader } from "./components/TradeMarkHeader";
import { ExecutionHealthRow } from "./components/riskTelemetry/ExecutionHealthRow";
import { LastWindowSummary } from "./components/riskTelemetry/LastWindowSummary";
import { SafetyStateBanner } from "./components/riskTelemetry/SafetyStateBanner";
import { StreamDiagnosticsBanner } from "./components/riskTelemetry/StreamDiagnosticsBanner";
import { CnnAssistPanel } from "./components/strategy/CnnAssistPanel";
import { DecisionTimeline } from "./components/strategy/DecisionTimeline";
import { FeaturePressureBars } from "./components/strategy/FeaturePressureBars";
import { OrderIntentOutcome } from "./components/strategy/OrderIntentOutcome";
import { RiskGateMatrix } from "./components/strategy/RiskGateMatrix";
import { StrategyDecisionStack } from "./components/strategy/StrategyDecisionStack";
import { StrategyExplanationPanel } from "./components/strategy/StrategyExplanationPanel";
import { StrategyHealthStrip } from "./components/strategy/StrategyHealthStrip";
import { useRollingHistory } from "./useRollingHistory";
import { useTelemetry } from "./useTelemetry";
import { normalizeSignal, num, signalColor, str } from "./telemetryUtils";
import { deriveStrategyDecision, type DecisionEvent } from "./strategyDerived";

type ActiveSection = null | 0 | 1 | 2;

type Meta = {
  symbols: string[];
  demo_mode: boolean;
  default_history_sec: number;
  regime_labels: string[];
  num_hist_bins: number;
  hist_bin_cycles: number;
  ns_per_cycle: number;
};

const plotBase = (): Partial<Layout> => ({
  paper_bgcolor: "#131722",
  plot_bgcolor: "#131722",
  font: { color: "#d1d4dc", size: 10 },
  margin: { l: 44, r: 8, t: 32, b: 28 },
  autosize: true,
  showlegend: true,
  legend: { orientation: "h", y: 1.08, x: 0, font: { size: 9, color: "#787b86" } },
  xaxis: { gridcolor: "#2a2e39", zerolinecolor: "#2a2e39", color: "#787b86" },
  yaxis: { gridcolor: "#2a2e39", zerolinecolor: "#2a2e39", color: "#787b86" },
});

function plotLayout(title: string, h?: number): Partial<Layout> {
  return {
    ...plotBase(),
    title: { text: title, font: { size: 12, color: "#d1d4dc" } },
    ...(h != null ? { height: h } : {}),
  };
}

function tightRange(y: number[], padFrac = 0.12): [number, number] | undefined {
  const finite = y.filter((v) => Number.isFinite(v));
  if (finite.length < 2) return undefined;
  let mn = finite[0]!;
  let mx = finite[0]!;
  for (const v of finite) {
    mn = Math.min(mn, v);
    mx = Math.max(mx, v);
  }
  if (mn === mx) {
    const eps = Math.max(1e-6, Math.abs(mn) * 0.02);
    return [mn - eps, mx + eps];
  }
  const pad = (mx - mn) * padFrac;
  return [mn - pad, mx + pad];
}

export default function App() {
  const [meta, setMeta] = useState<Meta | null>(null);
  const [historySec, setHistorySec] = useState(120);
  const [emaSymbol, setEmaSymbol] = useState(0);
  const [tab, setTab] = useState<"events" | "diag">("events");
  const [symMetric, setSymMetric] = useState<"pos" | "pnl" | "spread" | "dev">("pos");
  const [activeSection, setActiveSection] = useState<ActiveSection>(null);
  const [hubTransition, setHubTransition] = useState<null | { target: Exclude<ActiveSection, null>; label: string }>(null);
  const [hubFocus, setHubFocus] = useState<{ region: "NY" | "LDN" | "TYO" | "SGP"; phase: "handoff" | "approach" | "zoom" | "execute" } | null>(null);
  const [hubHeroY, setHubHeroY] = useState<number | null>(null);
  const [port, setPort] = useState("");
  const [baud, setBaud] = useState(115200);
  const [connectMsg, setConnectMsg] = useState("");
  const [expanded, setExpanded] = useState<null | "portfolio" | "pnl" | "cash" | "account">(null);
  const [eventBadge, setEventBadge] = useState<{ text: string; color: string } | null>(null);
  const [eventMarker, setEventMarker] = useState<{ t: number; y: number; text: string; color: string } | null>(null);
  const prevSig = useRef<string>("");
  const prevTrd = useRef<number>(0);
  const prevRej = useRef<number>(0);
  const sePrevRef = useRef<{ action: string; reason: string; risk: string; outcome: string }>({ action: "", reason: "", risk: "", outcome: "" });
  const seEventsRef = useRef<DecisionEvent[]>([]);
  const latRef = useRef<{ t: number[]; v: number[]; t0: number | null }>({ t: [], v: [], t0: null });
  const hubRef = useRef<HTMLDivElement | null>(null);
  const hubCardsRef = useRef<HTMLDivElement | null>(null);

  const { data, wsState } = useTelemetry(historySec, emaSymbol);

  useEffect(() => {
    fetch("/api/meta")
      .then((r) => r.json())
      .then((m: Meta) => {
        setMeta(m);
        setHistorySec(m.default_history_sec ?? 120);
      })
      .catch(() => setMeta(null));
  }, []);

  useEffect(() => {
    const next = data?.meta?.symbols;
    if (!next || !Array.isArray(next) || next.length < 1) return;
    setMeta((m) => {
      if (!m) return m;
      const cur = m.symbols ?? [];
      if (cur.length === next.length && cur.every((s, i) => s === next[i])) return m;
      return { ...m, symbols: next };
    });
  }, [data?.meta?.symbols]);

  const latest = data?.latest ?? {};
  const series = data?.series;
  const symbols = meta?.symbols ?? [];
  const symHist = useRollingHistory(latest, symbols.length, data?.ts, Math.max(240, historySec * 5));

  const goBack = () => setActiveSection(null);
  const goNext = () => setActiveSection((s) => (s == null ? 0 : (((s + 1) % 3) as 0 | 1 | 2)));
  const goPrev = () => setActiveSection((s) => (s == null ? 2 : (((s + 2) % 3) as 0 | 1 | 2)));
  const goTo = (s: ActiveSection) => setActiveSection(s);

  useLayoutEffect(() => {
    if (activeSection !== null) return;
    const hubEl = hubRef.current;
    const cardsEl = hubCardsRef.current;
    if (!hubEl || !cardsEl) return;

    const measure = () => {
      const hr = hubEl.getBoundingClientRect();
      const cr = cardsEl.getBoundingClientRect();
      const cardsTop = Math.max(0, cr.top - hr.top);
      setHubHeroY(Math.round(cardsTop / 2));
    };

    measure();

    const ro = new ResizeObserver(() => measure());
    ro.observe(hubEl);
    ro.observe(cardsEl);
    window.addEventListener("resize", measure);
    return () => {
      ro.disconnect();
      window.removeEventListener("resize", measure);
    };
  }, [activeSection]);

  useEffect(() => {
    if (!hubTransition) return;
    const t = window.setTimeout(() => {
      setActiveSection(hubTransition.target);
      setHubTransition(null);
    }, 520);
    return () => window.clearTimeout(t);
  }, [hubTransition]);

  useEffect(() => {
    const onFocus = (ev: Event) => {
      const e = ev as CustomEvent<{ lat: number; lng: number; continent: string; phase: "handoff" | "approach" | "zoom" | "execute" }>;
      const d = e.detail;
      if (!d) return;
      // Map globe focus to the 4 market-clock regions.
      // Priority: Singapore when focusing Singapore; otherwise by longitude/continent buckets.
      const region = (() => {
        if (d.continent === "as" && d.lng > 95 && d.lng < 125 && d.lat > -5 && d.lat < 15) return "SGP";
        if (d.continent === "na" || d.continent === "sa") return "NY";
        if (d.continent === "eu" || d.continent === "af" || d.continent === "me") return "LDN";
        if (d.continent === "oc") return "TYO";
        if (d.continent === "as") return "TYO";
        return d.lng < -30 ? "NY" : d.lng < 60 ? "LDN" : d.lng < 120 ? "SGP" : "TYO";
      })();
      setHubFocus({ region, phase: d.phase });
    };
    window.addEventListener("tm:globeFocus", onFocus as EventListener);
    return () => window.removeEventListener("tm:globeFocus", onFocus as EventListener);
  }, []);

  const regimeName = useMemo(() => {
    const rn = str(latest.regime_name).toUpperCase();
    if (rn && rn !== "?" && rn !== "UNKNOWN" && rn !== "") return rn;
    const rid = num(latest.regime, -1);
    if (rid >= 0 && meta?.regime_labels) return meta.regime_labels[rid & 3] ?? "UNKNOWN";
    return "UNKNOWN";
  }, [latest, meta]);

  const regimeColor = useMemo(() => {
    const m: Record<string, string> = {
      CALM: "#00C805",
      VOLATILE: "#FFB020",
      BURST: "#5AC8FA",
      ADVERSARIAL: "#FF331F",
    };
    return m[regimeName] ?? "#787b86";
  }, [regimeName]);

  const histXNs = useMemo(() => {
    const hist = latest.hist;
    if (!Array.isArray(hist)) return [];
    const hc = meta?.hist_bin_cycles ?? 32;
    const ns = meta?.ns_per_cycle ?? 10;
    const bw = hc * ns;
    return hist.map((_, i) => (i + 0.5) * bw);
  }, [latest, meta]);

  const histY = useMemo(() => {
    const hist = latest.hist;
    if (!Array.isArray(hist)) return [];
    return hist.map((c) => num(c));
  }, [latest]);

  const latTrend = useMemo(() => {
    const last = num(latest.last_latency, NaN);
    const ts = typeof data?.ts === "number" && Number.isFinite(data.ts) ? data.ts : Date.now() / 1000;
    const s = latRef.current;
    if (s.t0 == null) s.t0 = ts;
    const tRel = ts - (s.t0 ?? ts);
    if (Number.isFinite(last)) {
      s.t.push(tRel);
      s.v.push(last);
      const maxLen = Math.max(120, historySec * 5);
      if (s.t.length > maxLen) {
        const k = s.t.length - maxLen;
        s.t.splice(0, k);
        s.v.splice(0, k);
      }
    }
    return { t: [...s.t], v: [...s.v] };
  }, [latest, data?.ts, historySec]);

  useEffect(() => {
    const sigs = latest.signal;
    if (!Array.isArray(sigs)) return;
    const s = normalizeSignal(sigs[emaSymbol]);
    if (prevSig.current && s && s !== prevSig.current) {
      setEventBadge({ text: s, color: signalColor(s) });
      const ss = symHist.get(emaSymbol);
      const k = ss.t.length - 1;
      if (k >= 0 && Number.isFinite(ss.mid[k])) {
        setEventMarker({ t: ss.t[k], y: ss.mid[k], text: s, color: signalColor(s) });
      }
      const t = window.setTimeout(() => setEventBadge(null), 2200);
      return () => clearTimeout(t);
    }
    prevSig.current = s || prevSig.current;
  }, [latest, emaSymbol, symHist]);

  useEffect(() => {
    const trdArr = Array.isArray(latest.trades) ? (latest.trades as unknown[]) : [];
    const trdNow = num(trdArr[emaSymbol], 0);
    if (trdNow > prevTrd.current) {
      setEventBadge({ text: "FILL", color: "#5AC8FA" });
      const ss = symHist.get(emaSymbol);
      const k = ss.t.length - 1;
      if (k >= 0 && Number.isFinite(ss.mid[k])) {
        setEventMarker({ t: ss.t[k], y: ss.mid[k], text: "FILL", color: "#5AC8FA" });
      }
      const t = window.setTimeout(() => setEventBadge(null), 1600);
      prevTrd.current = trdNow;
      return () => clearTimeout(t);
    }
    prevTrd.current = trdNow;
  }, [latest, emaSymbol, symHist]);

  useEffect(() => {
    const r = num(latest.rej, 0);
    if (r > prevRej.current) {
      setEventBadge({ text: "REJECTED", color: "#f7931a" });
      const t = window.setTimeout(() => setEventBadge(null), 1800);
      prevRej.current = r;
      return () => clearTimeout(t);
    }
    prevRej.current = r;
  }, [latest]);

  useEffect(() => {
    if (!eventMarker) return;
    const t = window.setTimeout(() => setEventMarker(null), 2200);
    return () => clearTimeout(t);
  }, [eventMarker]);

  const pnlTraces: Data[] = useMemo(() => {
    if (!series) return [];
    const tc = series.t_cash;
    const mode = tc.length > 1 ? "lines" : "markers";
    return [
      { type: "scatter", mode, x: tc, y: series.cash, name: "cash", line: { color: "#089981", width: 2 } },
      { type: "scatter", mode, x: tc, y: series.pnl, name: "total PnL", line: { color: "#2962ff", width: 2 } },
      { type: "scatter", mode, x: tc, y: series.port, name: "port value", line: { color: "#f7931a", width: 2 } },
    ];
  }, [series]);

  const overlayTraces: Data[] = useMemo(() => {
    if (!expanded || !series) return [];
    const tc = series.t_cash;
    const mode = tc.length > 1 ? "lines" : "markers";
    if (expanded === "cash") {
      return [{ type: "scatter", mode, x: tc, y: series.cash, name: "cash", line: { color: "#089981", width: 2 } }];
    }
    if (expanded === "pnl") {
      return [{ type: "scatter", mode, x: tc, y: series.pnl, name: "total PnL", line: { color: "#2962ff", width: 2 } }];
    }
    if (expanded === "account") {
      return [{ type: "scatter", mode, x: tc, y: series.port, name: "total account", line: { color: "#2962ff", width: 2 } }];
    }
    return [{ type: "scatter", mode, x: tc, y: series.port, name: "port value", line: { color: "#f7931a", width: 2 } }];
  }, [expanded, series]);

  const thrTraces: Data[] = useMemo(() => {
    if (!series) return [];
    const t = series.t_act;
    const mode = "lines";
    return [
      { type: "scatter", mode, x: t, y: series.quotes, name: "quotes/s", line: { color: "#787b86", shape: "hv" } },
      { type: "scatter", mode, x: t, y: series.orders, name: "orders/s", line: { color: "#2962ff", shape: "hv" } },
      { type: "scatter", mode, x: t, y: series.fills, name: "fills/s", line: { color: "#089981", shape: "hv" } },
      { type: "scatter", mode, x: t, y: series.rejects, name: "rejects/s", line: { color: "#f23645", shape: "hv" } },
    ];
  }, [series]);

  const emaTraces: Data[] = useMemo(() => {
    const s = symHist.get(emaSymbol);
    const base: Data[] = [
      { type: "scatter", mode: "lines", x: s.t, y: s.mid, name: "mid", line: { color: "#d1d4dc", width: 2 } },
      { type: "scatter", mode: "lines", x: s.t, y: s.ema, name: "ema", line: { color: "#2962ff", width: 2 } },
    ];
    if (eventMarker && Number.isFinite(eventMarker.t) && Number.isFinite(eventMarker.y)) {
      const txt = String(eventMarker.text ?? "").toUpperCase();
      const symbol =
        txt === "BUY"
          ? "triangle-up"
          : txt === "SELL"
            ? "triangle-down"
            : txt === "FILL"
              ? "diamond"
              : "hexagon";

      // Halo/glow (bigger translucent marker) + core marker with label.
      base.push({
        type: "scatter",
        mode: "markers",
        x: [eventMarker.t],
        y: [eventMarker.y],
        marker: { color: eventMarker.color, size: 26, opacity: 0.22, symbol, line: { color: eventMarker.color, width: 1 } },
        hoverinfo: "skip",
        showlegend: false,
        name: "event-glow",
      });
      base.push({
        type: "scatter",
        mode: "markers+text",
        x: [eventMarker.t],
        y: [eventMarker.y],
        marker: { color: eventMarker.color, size: 15, symbol, line: { color: "#0b0e14", width: 1 } },
        text: [txt],
        textposition: "top center",
        textfont: { color: eventMarker.color, size: 14, family: "Inter, system-ui", },
        hoverinfo: "skip",
        name: "event",
      });
    }
    return base;
  }, [symHist, emaSymbol, eventMarker]);

  const symMetricTrace: Data[] = useMemo(() => {
    const s = symHist.get(emaSymbol);
    const m =
      symMetric === "pos"
        ? s.pos
        : symMetric === "pnl"
          ? s.pnl
          : symMetric === "spread"
            ? s.spread
            : s.dev;
    const color =
      symMetric === "pos"
        ? "#5AC8FA"
        : symMetric === "pnl"
          ? "#f7931a"
          : symMetric === "spread"
            ? "#787b86"
            : "#c4b5fd";
    const shape = symMetric === "spread" || symMetric === "dev" ? "hv" : "linear";
    const width = symMetric === "spread" || symMetric === "dev" ? 3 : 2.5;
    return [
      {
        type: "scatter",
        mode: "lines",
        x: s.t,
        y: m,
        name: symMetric,
        line: { color, width, shape },
      },
    ];
  }, [symHist, emaSymbol, symMetric]);

  const posTrace: Data[] = useMemo(() => {
    const pos = latest.pos;
    if (!Array.isArray(pos) || !symbols.length) return [];
    const y = symbols.slice(0, pos.length);
    const x = pos.map((p) => num(p));
    return [{ type: "bar", orientation: "h", x, y, marker: { color: x.map((v) => (v >= 0 ? "#089981" : "#f23645")) } }];
  }, [latest, symbols]);

  const onConnect = async () => {
    setConnectMsg("");
    const r = await fetch("/api/connect", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ port, baud }),
    });
    const j = (await r.json()) as { ok: boolean; msg: string };
    setConnectMsg(j.msg || (j.ok ? "ok" : "failed"));
  };

  const cash = num(latest.cash);
  const totalPnl = num(latest.total_pnl);
  const portVal = num(latest.port_value);
  const inv = num(latest.inventory_mtm);
  const costBasis = portVal - totalPnl;
  const totalAccount = portVal;
  const strat = str(latest.strategy);
  const linkUp = Boolean(latest.link_up);

  const quoteRate = Math.max(0, num(data?.rates?.quotes ?? data?.rates?.qps ?? latest.qps, 0));
  const orderRate = Math.max(0, num(data?.rates?.orders ?? data?.rates?.ops ?? latest.ops, 0));
  const fillRate = Math.max(0, num(data?.rates?.fills ?? data?.rates?.fps ?? latest.fps, 0));
  const latencyNs = num(latest.last_latency, NaN);

  const miEventsRef = useRef<MiEvent[]>([]);
  const miPrevRef = useRef({
    qps: 0,
    rej: 0,
    linkUp: true,
    regime: "UNKNOWN",
    sig: "—",
    trades: 0,
    spread: NaN,
    lastEmitTs: 0,
  });

  // Market Intelligence event feed (debounced & thresholded)
  useEffect(() => {
    const ts = typeof data?.ts === "number" && Number.isFinite(data.ts) ? data.ts : Date.now() / 1000;
    const prev = miPrevRef.current;
    const push = (severity: MiEvent["severity"], sym: string, msg: string) => {
      // avoid spamming: at most 4 events / 2s unless ERROR
      if (severity !== "ERROR" && ts - prev.lastEmitTs < 0.5) return;
      prev.lastEmitTs = ts;
      miEventsRef.current = [{ ts, severity, sym, msg }, ...miEventsRef.current].slice(0, 50);
    };

    // quote spike
    if (quoteRate > 0 && prev.qps > 0) {
      const r = quoteRate / Math.max(1e-9, prev.qps);
      if (r >= 1.9 && quoteRate > 200) push("WARN", "ALL", `QUOTE_SPIKE: qps ${prev.qps.toFixed(0)} → ${quoteRate.toFixed(0)}`);
    }
    prev.qps = quoteRate;

    // regime flip
    if (regimeName && regimeName !== prev.regime) {
      push("INFO", "ALL", `REGIME_FLIP: ${prev.regime} → ${regimeName}`);
      prev.regime = regimeName;
    }

    // link changes
    if (linkUp !== prev.linkUp) {
      push(linkUp ? "INFO" : "ERROR", "ALL", linkUp ? "LINK_RESTORED: PMOD link UP" : "LINK_DOWN: PMOD link DOWN");
      prev.linkUp = linkUp;
    }

    // rejects
    const rj = num(latest.rej, 0);
    if (rj > prev.rej) {
      push(rj - prev.rej >= 2 ? "ERROR" : "WARN", "ALL", `REJECTED: +${rj - prev.rej} rejects`);
      prev.rej = rj;
    }

    // spread widen/normalize on selected symbol
    const s = symHist.get(emaSymbol);
    const sprCur = s.spread.length ? s.spread[s.spread.length - 1] : NaN;
    const sprPrev = prev.spread;
    if (Number.isFinite(sprCur) && Number.isFinite(sprPrev)) {
      if (sprCur > sprPrev * 1.6 && sprCur > 0.05) push("WARN", symbols[emaSymbol] ?? "ALL", `SPREAD_WIDEN: ${sprPrev.toFixed(3)} → ${sprCur.toFixed(3)}`);
      if (sprCur < sprPrev * 0.72 && sprPrev > 0.05) push("INFO", symbols[emaSymbol] ?? "ALL", `SPREAD_NORMALIZED: ${sprPrev.toFixed(3)} → ${sprCur.toFixed(3)}`);
    }
    prev.spread = sprCur;

    // signal changes (selected)
    const sigNow = normalizeSignal(Array.isArray(latest.signal) ? latest.signal[emaSymbol] : undefined) || "—";
    if (sigNow !== prev.sig && prev.sig !== "—") push("INFO", symbols[emaSymbol] ?? "ALL", `SIGNAL_CHANGE: ${prev.sig} → ${sigNow}`);
    prev.sig = sigNow;

    // fills (selected)
    const trdArr = Array.isArray(latest.trades) ? (latest.trades as unknown[]) : [];
    const trdNow = num(trdArr[emaSymbol], 0);
    if (trdNow > prev.trades) push("INFO", symbols[emaSymbol] ?? "ALL", `FILL: +${trdNow - prev.trades}`);
    prev.trades = trdNow;

    // heartbeat stale
    const ageMs = num(data?.age_ms, NaN);
    if (Number.isFinite(ageMs) && ageMs > 1200) push(ageMs > 2200 ? "ERROR" : "WARN", "ALL", `HEARTBEAT_STALE: age ${Math.round(ageMs)} ms`);
  }, [data?.ts, data?.age_ms, latest, quoteRate, linkUp, regimeName, emaSymbol, symHist, symbols]);

  const seDecision = useMemo(() => {
    return deriveStrategyDecision({
      latest,
      symbols,
      selectedIdx: emaSymbol,
      packetAgeMs: typeof data?.age_ms === "number" ? data.age_ms : null,
      connected: Boolean(data?.connected),
    });
  }, [latest, symbols, emaSymbol, data?.age_ms, data?.connected]);

  // Strategy Engine decision timeline (debounced & thresholded)
  useEffect(() => {
    if (!symbols.length) return;
    const d = seDecision;
    const prev = sePrevRef.current;
    const key = `${d.action}|${d.reason}|${d.riskPass ? "PASS" : "BLOCK"}|${d.outcome}`;
    const prevKey = `${prev.action}|${prev.reason}|${prev.risk}|${prev.outcome}`;

    const now = Date.now();
    const lastTs = seEventsRef.current.length ? seEventsRef.current[seEventsRef.current.length - 1]!.ts : 0;
    const tooSoon = now - lastTs < 170;

    if (key !== prevKey && !tooSoon) {
      const ev: DecisionEvent = {
        ts: now,
        symbol: d.symbol,
        action: d.action,
        confidence: d.confidence,
        risk: d.riskPass ? "PASS" : "BLOCK",
        reason: d.reason,
        outcome: d.outcome,
        outcomeReason: d.outcomeReason,
      };
      seEventsRef.current = [...seEventsRef.current, ev].slice(-80);
    }

    sePrevRef.current = { action: d.action, reason: d.reason, risk: d.riskPass ? "PASS" : "BLOCK", outcome: d.outcome };
  }, [seDecision, symbols.length]);

  const overlayTitle =
    expanded === "cash"
      ? "Cash — expanded"
      : expanded === "pnl"
        ? "Total PnL — expanded"
        : expanded === "account"
          ? "Total account — expanded"
          : "Portfolio value — expanded";

  return (
    <div className="tm-app">
      {activeSection !== null && (
        <>
          <TradeMarkHeader
            regimeName={regimeName}
            regimeColor={regimeColor}
            strategy={strat || "—"}
            linkUp={linkUp}
            demoMode={Boolean(meta?.demo_mode)}
          />

          <div className="tm-command">
            <h2>LIVE</h2>
            <span className="tm-ws mono">
              ws {wsState}
              {data ? ` · hb ${data.heartbeat} · ${data.age_ms.toFixed(0)} ms` : ""}
            </span>
            <label className="mono" style={{ color: "#787b86" }}>
              history
              <select
                value={historySec}
                onChange={(e) => setHistorySec(Number(e.target.value))}
                style={{ marginLeft: 6, background: "#0b0e14", color: "#d1d4dc", border: "1px solid #2a2e39", borderRadius: 4 }}
              >
                {[30, 120, 600].map((s) => (
                  <option key={s} value={s}>
                    {s}s
                  </option>
                ))}
              </select>
            </label>
            {!meta?.demo_mode && (
              <>
                <input
                  className="mono"
                  placeholder="/dev/cu.usbserial-…"
                  value={port}
                  onChange={(e) => setPort(e.target.value)}
                  style={{ width: 180, padding: 6, fontSize: 12, borderRadius: 4, border: "1px solid #2a2e39", background: "#0b0e14", color: "#d1d4dc" }}
                />
                <input
                  className="mono"
                  type="number"
                  value={baud}
                  onChange={(e) => setBaud(Number(e.target.value))}
                  style={{ width: 90, padding: 6, fontSize: 12, borderRadius: 4, border: "1px solid #2a2e39", background: "#0b0e14", color: "#d1d4dc" }}
                />
                <button type="button" className="tm-btn" onClick={onConnect}>
                  Connect UART
                </button>
                {connectMsg && <span className="mono" style={{ fontSize: 11, color: "#787b86" }}>{connectMsg}</span>}
              </>
            )}
            <a className="mono" href={`/api/export/csv?history_sec=${historySec}`} style={{ marginLeft: "auto", color: "#5ac8fa", fontSize: 12 }}>
              Export CSV
            </a>
          </div>
        </>
      )}

      {activeSection === null ? (
        <div className="tm-hub" ref={hubRef}>
          <div className="tm-hub-fx" aria-hidden="true">
            <div className="tm-hub-gridfx" />
            <div className="tm-hub-spark tm-hub-spark--1" />
            <div className="tm-hub-spark tm-hub-spark--2" />
            <div className="tm-hub-spark tm-hub-spark--3" />
            <GlobeGlRandomArcs />
          </div>

          <div className="tm-hub-topnav mono">
            <button type="button" className="tm-topnav-link on" aria-current="page">
              Overview
            </button>
            <button type="button" className="tm-topnav-link" onClick={() => setHubTransition({ target: 0, label: "Loading Market Intelligence…" })}>
              Metrics
            </button>
            <button type="button" className="tm-topnav-link" onClick={() => setHubTransition({ target: 1, label: "Loading Strategy Engine…" })}>
              Demo
            </button>
            <button type="button" className="tm-topnav-link" onClick={() => setHubTransition({ target: 2, label: "Loading Risk & Telemetry…" })}>
              Hardware
            </button>
          </div>

          <div
            className="tm-hub-hero"
            style={hubHeroY != null ? { top: hubHeroY } : undefined}
          >
            <div className="tm-hero-frame" aria-hidden="true" />
            <div className="tm-wordmark tm-wordmark--hero" aria-label="TradeMark">
              TradeMark
            </div>
            <div className="tm-hero-sub mono">
              Deterministic trading infrastructure for real-time market simulation.
            </div>

            <div className="tm-hero-chips mono" role="list" aria-label="Live system status">
              <div className="tm-chip" role="listitem">
                <span className="tm-chip-dot tm-chip-dot--good" aria-hidden="true" /> BOARD A ↔ BOARD B
              </div>
              <div className="tm-chip" role="listitem">
                <span className="tm-chip-dot tm-chip-dot--accent" aria-hidden="true" /> 50 MHz PL CLOCK
              </div>
              <div className="tm-chip" role="listitem">
                <span className={`tm-chip-dot ${linkUp ? "tm-chip-dot--good" : "tm-chip-dot--bad"}`} aria-hidden="true" /> PMOD LINK {linkUp ? "ACTIVE" : "DOWN"}
              </div>
              <div className="tm-chip" role="listitem">
                <span className="tm-chip-dot tm-chip-dot--good" aria-hidden="true" /> RISK GATE ENABLED
              </div>
            </div>

            <div className="tm-hero-cta">
              <button
                type="button"
                className="tm-btn tm-btn--primary tm-hero-cta-btn"
                onClick={() => setHubTransition({ target: 0, label: "Entering live system…" })}
              >
                Enter Live System
              </button>
              <div className="tm-hero-narr mono" aria-label="System narrative">
                QUOTE → DECISION → RISK CHECK → EXECUTE
              </div>
            </div>
          </div>

          <div className="tm-market-clock mono" aria-label="Global market clock">
            <div className="tm-clock-item">
              <span className={`tm-clock-dot ${hubFocus?.region === "NY" ? `tm-clock-dot--focus tm-clock-dot--${hubFocus.phase}` : "tm-clock-dot--good"}`} aria-hidden="true" /> NEW YORK <span className="tm-clock-state">{hubFocus?.region === "NY" ? (hubFocus.phase === "execute" ? "EXECUTING" : hubFocus.phase === "zoom" ? "LOCKING" : hubFocus.phase === "approach" ? "SYNCING" : "HANDOFF") : "OPEN"}</span>
            </div>
            <div className="tm-clock-item">
              <span className={`tm-clock-dot ${hubFocus?.region === "LDN" ? `tm-clock-dot--focus tm-clock-dot--${hubFocus.phase}` : "tm-clock-dot--warn"}`} aria-hidden="true" /> LONDON <span className="tm-clock-state">{hubFocus?.region === "LDN" ? (hubFocus.phase === "execute" ? "EXECUTING" : hubFocus.phase === "zoom" ? "LOCKING" : hubFocus.phase === "approach" ? "SYNCING" : "HANDOFF") : "CLOSED"}</span>
            </div>
            <div className="tm-clock-item">
              <span className={`tm-clock-dot ${hubFocus?.region === "TYO" ? `tm-clock-dot--focus tm-clock-dot--${hubFocus.phase}` : "tm-clock-dot--good"}`} aria-hidden="true" /> TOKYO <span className="tm-clock-state">{hubFocus?.region === "TYO" ? (hubFocus.phase === "execute" ? "EXECUTING" : hubFocus.phase === "zoom" ? "LOCKING" : hubFocus.phase === "approach" ? "SYNCING" : "HANDOFF") : "OPEN"}</span>
            </div>
            <div className="tm-clock-item">
              <span className={`tm-clock-dot ${hubFocus?.region === "SGP" ? `tm-clock-dot--focus tm-clock-dot--${hubFocus.phase}` : "tm-clock-dot--accent"}`} aria-hidden="true" /> SINGAPORE <span className="tm-clock-state">{hubFocus?.region === "SGP" ? (hubFocus.phase === "execute" ? "EXECUTING" : hubFocus.phase === "zoom" ? "LOCKING" : hubFocus.phase === "approach" ? "SYNCING" : "HANDOFF") : "ACTIVE"}</span>
            </div>
          </div>

          <div className="tm-hub-cards" ref={hubCardsRef}>
            <div className="tm-hub-grid">
            <button type="button" className="tm-hub-card tm-hub-card--mi" onClick={() => setHubTransition({ target: 0, label: "Loading Market Intelligence…" })}>
              <div className="tm-hub-card-title">Market Intelligence</div>
              <div className="tm-hub-card-desc mono">Quote generation, regime simulation, and market-state visualization.</div>
              <div className="tm-hub-card-preview" aria-hidden="true">
                <div className="tm-prev-line tm-prev-line--cyan" />
                <div className="tm-prev-line tm-prev-line--blue" />
                <div className="tm-prev-bars tm-prev-bars--cyan" />
              </div>
              <div className="tm-hub-card-metrics mono" aria-label="Market Intelligence metrics">
                <div><span className="k">Regime</span><span className="v" style={{ color: regimeColor }}>{regimeName}</span></div>
                <div><span className="k">Quote rate</span><span className="v">{quoteRate ? `${quoteRate.toFixed(2)} /s` : "—"}</span></div>
                <div><span className="k">Symbols</span><span className="v">{meta?.symbols?.length ?? symbols.length ?? "—"}</span></div>
              </div>
            </button>
            <button type="button" className="tm-hub-card tm-hub-card--se" onClick={() => setHubTransition({ target: 1, label: "Loading Strategy Engine…" })}>
              <div className="tm-hub-card-title">Strategy Engine</div>
              <div className="tm-hub-card-desc mono">Feature extraction, buy/sell/hold decisions, and adaptive execution logic.</div>
              <div className="tm-hub-card-preview" aria-hidden="true">
                <div className="tm-prev-line tm-prev-line--violet" />
                <div className="tm-prev-line tm-prev-line--blue" />
                <div className="tm-prev-pulse tm-prev-pulse--violet" />
              </div>
              <div className="tm-hub-card-metrics mono" aria-label="Strategy Engine metrics">
                <div><span className="k">Strategy</span><span className="v">{strat || "—"}</span></div>
                <div><span className="k">Decision</span><span className="v">{normalizeSignal(Array.isArray(latest.signal) ? latest.signal[emaSymbol] : undefined) || "—"}</span></div>
                <div><span className="k">Orders</span><span className="v">{orderRate ? `${orderRate.toFixed(2)} /s` : "—"}</span></div>
              </div>
            </button>
            <button type="button" className="tm-hub-card tm-hub-card--rt" onClick={() => setHubTransition({ target: 2, label: "Loading Risk & Telemetry…" })}>
              <div className="tm-hub-card-title">Risk & Telemetry</div>
              <div className="tm-hub-card-desc mono">Position limits, PnL tracking, latency histograms, and system health.</div>
              <div className="tm-hub-card-preview" aria-hidden="true">
                <div className="tm-prev-line tm-prev-line--teal" />
                <div className="tm-prev-bands tm-prev-bands--teal" />
                <div className="tm-prev-dot tm-prev-dot--teal" />
              </div>
              <div className="tm-hub-card-metrics mono" aria-label="Risk and Telemetry metrics">
                <div><span className="k">PnL</span><span className="v" style={{ color: totalPnl >= 0 ? "#089981" : "#f23645" }}>{Number.isFinite(totalPnl) ? totalPnl.toFixed(2) : "—"}</span></div>
                <div><span className="k">Latency</span><span className="v">{Number.isFinite(latencyNs) ? `${latencyNs.toFixed(0)} ns` : "—"}</span></div>
                <div><span className="k">Fills</span><span className="v">{fillRate ? `${fillRate.toFixed(2)} /s` : "—"}</span></div>
              </div>
            </button>
          </div>
          </div>
          <div className="tm-hub-arch mono" aria-label="System architecture flow">
            MARKET SIMULATOR → QUOTE BOOK → STRATEGY → RISK GATE → ORDER MANAGER → TELEMETRY
          </div>
          <div className="tm-hub-foot mono">Click a system area to explore. Use Previous/Next inside sections.</div>

          {hubTransition && (
            <div className="tm-hub-transition" role="status" aria-live="polite">
              <div className="tm-hub-transition-inner mono">
                <div className="tm-hub-transition-title">{hubTransition.label}</div>
                <div className="tm-hub-transition-bar" aria-hidden="true" />
                <div className="tm-hub-transition-sub">Synchronizing telemetry…</div>
              </div>
            </div>
          )}
        </div>
      ) : (
        <div className="tm-section">
          <div className="tm-section-nav mono">
            <button type="button" className="tm-btn" onClick={goBack}>
              Back to Overview
            </button>
            <div className="tm-section-mid">
              <div className="tm-section-title">
                {activeSection === 0 ? "Market Intelligence" : activeSection === 1 ? "Strategy Engine" : "Risk & Telemetry"}
              </div>
              <div className="tm-section-jump">
                <button type="button" className={`tm-jump ${activeSection === 0 ? "on" : ""}`} onClick={() => goTo(0)}>
                  Market
                </button>
                <button type="button" className={`tm-jump ${activeSection === 1 ? "on" : ""}`} onClick={() => goTo(1)}>
                  Strategy
                </button>
                <button type="button" className={`tm-jump ${activeSection === 2 ? "on" : ""}`} onClick={() => goTo(2)}>
                  Risk
                </button>
              </div>
            </div>
            <div className="tm-section-nav-right">
              <button type="button" className="tm-btn" onClick={goPrev}>
                Previous
              </button>
              <button type="button" className="tm-btn" onClick={goNext}>
                Next
              </button>
            </div>
          </div>

          {activeSection === 0 && (
            <div className="tm-main">
              <aside className="tm-rail">
                <div className="tm-rail-inner">
                  <SymbolMarketDeck symbols={symbols} latest={latest} selectedIdx={emaSymbol} onSelect={setEmaSymbol} />
                </div>
              </aside>
              <main className="tm-center">
                <StatusPills latest={latest} selectedIdx={emaSymbol} />
                <div className="tm-mi-pipeline-live mono" aria-label="Pipeline narrative">
                  <div className="st">
                    <div className="k">QUOTE</div>
                    <div className="v">{quoteRate ? `${quoteRate.toFixed(0)}/s` : "--"}</div>
                  </div>
                  <div className="st">
                    <div className="k">QUOTE BOOK</div>
                    <div className="v">{symbols[emaSymbol] ?? "--"}</div>
                  </div>
                  <div className="st">
                    <div className="k">MID/SPREAD</div>
                    <div className="v">
                      {(() => {
                        const s = symHist.get(emaSymbol);
                        const m = s.mid.length ? s.mid[s.mid.length - 1] : NaN;
                        const sp = s.spread.length ? s.spread[s.spread.length - 1] : NaN;
                        return Number.isFinite(m) && Number.isFinite(sp) ? `${m.toFixed(2)} / ${sp.toFixed(3)}` : "--";
                      })()}
                    </div>
                  </div>
                  <div className="st">
                    <div className="k">EMA FEATURES</div>
                    <div className="v">
                      {(() => {
                        const s = symHist.get(emaSymbol);
                        const d = s.dev.length ? s.dev[s.dev.length - 1] : NaN;
                        return Number.isFinite(d) ? `dev ${d >= 0 ? "+" : ""}${d.toFixed(4)}` : "--";
                      })()}
                    </div>
                  </div>
                  <div className="st">
                    <div className="k">REGIME</div>
                    <div className="v" style={{ color: regimeColor }}>{regimeName || "UNKNOWN"}</div>
                  </div>
                  <div className="st">
                    <div className="k">STRATEGY INPUT</div>
                    <div className="v">{normalizeSignal(Array.isArray(latest.signal) ? latest.signal[emaSymbol] : undefined) || "--"}</div>
                  </div>
                </div>

                <MarketHealthStrip
                  latest={latest}
                  wsOpen={wsState === "open"}
                  ageMs={typeof data?.age_ms === "number" ? data.age_ms : null}
                  parseErrors={typeof data?.parse_errors === "number" ? data.parse_errors : null}
                  qps={quoteRate || null}
                  ops={orderRate || null}
                  fps={fillRate || null}
                  linkUp={linkUp}
                />

                <RegimeTimeline
                  nowSec={typeof data?.ts === "number" && Number.isFinite(data.ts) ? data.ts : Date.now() / 1000}
                  regimeName={regimeName}
                  qps={quoteRate || null}
                  ops={orderRate || null}
                  fps={fillRate || null}
                  rejDelta={Math.max(0, num(latest.rej, 0) - num(miPrevRef.current.rej, 0))}
                />

                <MarketQuoteBook
                  sym={symbols[emaSymbol] ?? "--"}
                  symIdx={emaSymbol}
                  bid={Array.isArray(latest.bid) ? num((latest.bid as unknown[])[emaSymbol], NaN) : null}
                  ask={Array.isArray(latest.ask) ? num((latest.ask as unknown[])[emaSymbol], NaN) : null}
                  mid={Array.isArray(latest.mid) ? num((latest.mid as unknown[])[emaSymbol], NaN) : null}
                  spread={Array.isArray(latest.spread) ? num((latest.spread as unknown[])[emaSymbol], NaN) : null}
                  spreadHist={symHist.get(emaSymbol).spread}
                />

                <div className="tm-chart-stack tm-chart-stack--mi" style={{ gridTemplateRows: "minmax(0, 0.95fr) minmax(0, 1.25fr) minmax(0, 0.65fr)" }}>
                  <div className="tm-plot">
                    <Plot data={thrTraces} layout={plotLayout("Quote / order / fill rates")} config={{ displayModeBar: false, responsive: true }} style={{ width: "100%", height: "100%" }} />
                  </div>
                  <div className="tm-plot">
                    <Plot
                      data={posTrace}
                      layout={{
                        ...plotLayout("Net positions snapshot"),
                        yaxis: { automargin: true, gridcolor: "#2a2e39", color: "#787b86", autorange: "reversed" },
                        xaxis: { gridcolor: "#2a2e39", zeroline: true, zerolinewidth: 1, color: "#787b86" },
                      }}
                      config={{ displayModeBar: false, responsive: true }}
                      style={{ width: "100%", height: "100%" }}
                    />
                  </div>
                  <div className="tm-plot">
                    <Plot
                      data={[
                        {
                          type: "histogram",
                          x: symHist.get(emaSymbol).dev.slice(-220).filter((v) => Number.isFinite(v)),
                          marker: { color: "rgba(90,200,250,0.45)" },
                          nbinsx: 28,
                        },
                      ] as any}
                      layout={{ ...plotLayout("Dev distribution (selected)"), bargap: 0.05 }}
                      config={{ displayModeBar: false, responsive: true }}
                      style={{ width: "100%", height: "100%" }}
                    />
                  </div>
                </div>

                <MarketEventFeed events={miEventsRef.current} />
              </main>
              <aside className="tm-rail tm-rail--right">
                <div className="tm-tools-head">
                  <div className="tm-rail-title">SELECT</div>
                  <select
                    className="mono"
                    value={emaSymbol}
                    onChange={(e) => setEmaSymbol(Number(e.target.value))}
                    style={{ marginTop: 8, width: "100%", padding: 6, borderRadius: 4, background: "#0b0e14", color: "#d1d4dc", border: "1px solid #2a2e39" }}
                  >
                    {symbols.map((sym, i) => (
                      <option key={sym} value={i}>
                        {sym}
                      </option>
                    ))}
                  </select>
                </div>
                <div className="tm-tools-body tm-tools-body--mi">
                  <FeatureVectorPanel
                    sym={symbols[emaSymbol] ?? "--"}
                    latest={latest}
                    selectedIdx={emaSymbol}
                    series={symHist.get(emaSymbol)}
                  />
                  <div className="tm-plot">
                    <Plot data={emaTraces} layout={plotLayout(`Mid vs EMA · ${symbols[emaSymbol] ?? "?"}`)} config={{ displayModeBar: false, responsive: true }} style={{ width: "100%", height: "100%" }} />
                  </div>
                  <div style={{ display: "flex", flexDirection: "column", minHeight: 0, height: "100%" }}>
                    <div className="tm-tabs">
                      <button type="button" className={symMetric === "spread" ? "on" : ""} onClick={() => setSymMetric("spread")}>
                        Spread
                      </button>
                      <button type="button" className={symMetric === "dev" ? "on" : ""} onClick={() => setSymMetric("dev")}>
                        Dev
                      </button>
                      <button type="button" className={symMetric === "pos" ? "on" : ""} onClick={() => setSymMetric("pos")}>
                        Pos
                      </button>
                      <button type="button" className={symMetric === "pnl" ? "on" : ""} onClick={() => setSymMetric("pnl")}>
                        PnL
                      </button>
                    </div>
                    <div className="tm-plot" style={{ flex: "1 1 0", minHeight: 0 }}>
                      {(() => {
                        const s = symHist.get(emaSymbol);
                        const y =
                          symMetric === "pos"
                            ? s.pos
                            : symMetric === "pnl"
                              ? s.pnl
                              : symMetric === "spread"
                                ? s.spread
                                : s.dev;
                        const r = tightRange(y, symMetric === "spread" ? 0.25 : 0.12);
                        return (
                          <Plot
                            data={symMetricTrace}
                            layout={{
                              ...plotLayout(`Feature · ${symMetric.toUpperCase()} · ${symbols[emaSymbol] ?? "?"}`),
                              yaxis: { ...plotBase().yaxis, ...(r ? { range: r } : {}) },
                            }}
                            config={{ displayModeBar: false, responsive: true }}
                            style={{ width: "100%", height: "100%" }}
                          />
                        );
                      })()}
                    </div>
                  </div>
                </div>
              </aside>
            </div>
          )}

          {activeSection === 1 && (
            <div className="tm-main">
              <aside className="tm-rail">
                <div className="tm-rail-inner">
                  <SymbolMarketDeck symbols={symbols} latest={latest} selectedIdx={emaSymbol} onSelect={setEmaSymbol} />
                </div>
              </aside>
              <main className="tm-center">
                <StatusPills latest={latest} selectedIdx={emaSymbol} />
                <div className="tm-flow mono">Features → Strategy Logic → CNN Assist → Buy/Sell/Hold → Risk Check → Order</div>
                <StrategyHealthStrip rates={data?.rates} events={seEventsRef.current} packetAgeMs={typeof data?.age_ms === "number" ? data.age_ms : null} connected={Boolean(data?.connected)} />
                <StrategyDecisionStack d={seDecision} />
                <RiskConsole latest={latest} demoMode={Boolean(meta?.demo_mode)} />
                <RiskGateMatrix latest={latest} selectedIdx={emaSymbol} blockingHint={!seDecision.riskPass ? seDecision.riskReason || seDecision.reason : null} />
                <StrategyExplanationPanel d={seDecision} latest={latest} selectedIdx={emaSymbol} />
                <div className="tm-chart-stack tm-chart-stack--se" style={{ gridTemplateRows: "minmax(0, 1fr) auto minmax(0, 1fr)" }}>
                  <div className="tm-plot">
                    <Plot data={emaTraces} layout={plotLayout(`Mid vs EMA · ${symbols[emaSymbol] ?? "?"}`)} config={{ displayModeBar: false, responsive: true }} style={{ width: "100%", height: "100%" }} />
                  </div>
                  <DecisionTimeline
                    events={seEventsRef.current}
                    onSelectSymbol={(sym) => {
                      const i = symbols.indexOf(sym);
                      if (i >= 0) setEmaSymbol(i);
                    }}
                  />
                  <div className="tm-plot">
                    <Plot
                      data={symMetricTrace}
                      layout={{
                        ...plotLayout(`Decision feature · ${symMetric.toUpperCase()}`),
                        ...(symMetric === "dev" && Number.isFinite(num(latest.threshold, NaN))
                          ? {
                              shapes: [
                                { type: "line", xref: "paper", x0: 0, x1: 1, yref: "y", y0: num(latest.threshold), y1: num(latest.threshold), line: { color: "#f7931a", width: 1, dash: "dot" } },
                                { type: "line", xref: "paper", x0: 0, x1: 1, yref: "y", y0: -num(latest.threshold), y1: -num(latest.threshold), line: { color: "#f7931a", width: 1, dash: "dot" } },
                              ],
                            }
                          : {}),
                      }}
                      config={{ displayModeBar: false, responsive: true }}
                      style={{ width: "100%", height: "100%" }}
                    />
                  </div>
                </div>
              </main>
              <aside className="tm-rail tm-rail--right">
                <div className="tm-tools-head">
                  <div className="tm-rail-title">TOOLS</div>
                  <select
                    className="mono"
                    value={emaSymbol}
                    onChange={(e) => setEmaSymbol(Number(e.target.value))}
                    style={{ marginTop: 8, width: "100%", padding: 6, borderRadius: 4, background: "#0b0e14", color: "#d1d4dc", border: "1px solid #2a2e39" }}
                  >
                    {symbols.map((sym, i) => (
                      <option key={sym} value={i}>
                        {sym}
                      </option>
                    ))}
                  </select>
                </div>
                <div className="tm-tools-body tm-tools-body--se">
                  <CnnAssistPanel latest={latest} />
                  <FeaturePressureBars latest={latest} selectedIdx={emaSymbol} confidence={seDecision.confidence} confidenceSynthetic={seDecision.confidenceSynthetic} />
                  <OrderIntentOutcome d={seDecision} />
                  <LatencyTelemetry latest={latest} histXNs={histXNs} histY={histY} latT={latTrend.t} latLastCy={latTrend.v} />
                </div>
              </aside>
            </div>
          )}

          {activeSection === 2 && (
            <div className="tm-main">
              <aside className="tm-rail">
                <div className="tm-rail-inner">
                  <SymbolMarketDeck symbols={symbols} latest={latest} selectedIdx={emaSymbol} onSelect={setEmaSymbol} />
                </div>
              </aside>
              <main className="tm-center">
                <StatusPills latest={latest} selectedIdx={emaSymbol} />
                <SafetyStateBanner latest={latest} connected={Boolean(data?.connected)} packetAgeMs={typeof data?.age_ms === "number" ? data.age_ms : null} />
                <ExecutionHealthRow latest={latest} rates={data?.rates} events={seEventsRef.current} packetAgeMs={typeof data?.age_ms === "number" ? data.age_ms : null} connected={Boolean(data?.connected)} />
                <RiskConsole latest={latest} demoMode={Boolean(meta?.demo_mode)} />
                <div className="tm-flow mono">Order → Risk Manager → Exchange Link → Fill/Reject → Position/PnL → Telemetry</div>
                <OrderIntentOutcome d={seDecision} />
                <RiskGateMatrix latest={latest} selectedIdx={emaSymbol} blockingHint={!seDecision.riskPass ? seDecision.riskReason || seDecision.reason : null} />
                <div className="tm-metric-deck">
                  <MetricCard label="Initial cash" value={Number.isFinite(costBasis) ? `$${costBasis.toLocaleString(undefined, { minimumFractionDigits: 2 })}` : "—"} tone={costBasis >= 0 ? "good" : "bad"} subtitle="starting balance (≈ port − pnl)" />
                  <MetricCard label="Raw cash" value={Number.isFinite(cash) ? `$${cash.toLocaleString(undefined, { minimumFractionDigits: 2 })}` : "—"} tone={cash >= 0 ? "good" : "bad"} subtitle="cash after fills" spark={series ? { x: series.t_cash, y: series.cash, color: "#089981" } : null} onExpand={() => setExpanded("cash")} />
                  <MetricCard label="Account cash" value={Number.isFinite(cash) ? `$${cash.toLocaleString(undefined, { minimumFractionDigits: 2 })}` : "—"} tone={cash >= 0 ? "good" : "bad"} subtitle="available balance" />
                  <MetricCard label="Portfolio value" value={Number.isFinite(portVal) ? `$${portVal.toLocaleString(undefined, { minimumFractionDigits: 2 })}` : "—"} tone="accent" subtitle="marked-to-market holdings" spark={series ? { x: series.t_cash, y: series.port, color: "#f7931a" } : null} onExpand={() => setExpanded("portfolio")} />
                  <MetricCard label="Total account" value={Number.isFinite(totalAccount) ? `$${totalAccount.toLocaleString(undefined, { minimumFractionDigits: 2 })}` : "—"} tone="accent" subtitle="cash + portfolio" spark={series ? { x: series.t_cash, y: series.port, color: "#2962ff" } : null} onExpand={() => setExpanded("account")} />
                  <MetricCard
                    label="Total PnL"
                    value={Number.isFinite(totalPnl) ? `${totalPnl >= 0 ? "+" : ""}$${totalPnl.toLocaleString(undefined, { minimumFractionDigits: 2 })}` : "—"}
                    tone={totalPnl >= 0 ? "good" : "bad"}
                    subtitle="account − initial"
                    spark={series ? { x: series.t_cash, y: series.pnl, color: totalPnl >= 0 ? "#089981" : "#f23645" } : null}
                    onExpand={() => setExpanded("pnl")}
                  />
                </div>
                <div className="tm-chart-stack tm-chart-stack--rt" style={{ gridTemplateRows: "minmax(0, 1fr) auto minmax(0, 1fr)" }}>
                  <div className="tm-plot">
                    <Plot data={pnlTraces} layout={plotLayout("Profit & portfolio")} config={{ displayModeBar: false, responsive: true }} style={{ width: "100%", height: "100%" }} />
                  </div>
                  <DecisionTimeline
                    events={seEventsRef.current}
                    onSelectSymbol={(sym) => {
                      const i = symbols.indexOf(sym);
                      if (i >= 0) setEmaSymbol(i);
                    }}
                  />
                  <div className="tm-plot">
                    <Plot data={thrTraces} layout={plotLayout("Execution throughput (rates)")} config={{ displayModeBar: false, responsive: true }} style={{ width: "100%", height: "100%" }} />
                  </div>
                </div>
              </main>
              <aside className="tm-rail tm-rail--right">
                <div className="tm-tools-head">
                  <div className="tm-rail-title">TELEMETRY DIAGNOSTICS</div>
                  <select
                    className="mono"
                    value={emaSymbol}
                    onChange={(e) => setEmaSymbol(Number(e.target.value))}
                    style={{ marginTop: 8, width: "100%", padding: 6, borderRadius: 4, background: "#0b0e14", color: "#d1d4dc", border: "1px solid #2a2e39" }}
                  >
                    {symbols.map((sym, i) => (
                      <option key={sym} value={i}>
                        {sym}
                      </option>
                    ))}
                  </select>
                </div>
                <div className="tm-tools-body tm-tools-body--rt">
                  <StreamDiagnosticsBanner latest={latest} connected={Boolean(data?.connected)} packetAgeMs={typeof data?.age_ms === "number" ? data.age_ms : null} hardwareStalled={Boolean(data?.hardware_stalled)} parseErrors={num(data?.parse_errors, 0)} />
                  <LatencyTelemetry latest={latest} histXNs={histXNs} histY={histY} latT={latTrend.t} latLastCy={latTrend.v} />
                  <LastWindowSummary latest={latest} events={seEventsRef.current} />
                  <div style={{ display: "flex", flexDirection: "column", minHeight: 0 }}>
                    <div className="tm-tabs">
                      <button type="button" className={tab === "events" ? "on" : ""} onClick={() => setTab("events")}>
                        Events
                      </button>
                      <button type="button" className={tab === "diag" ? "on" : ""} onClick={() => setTab("diag")}>
                        Diagnostics
                      </button>
                    </div>
                    <div className="tm-tab-body mono">
                      {tab === "events" &&
                        ((data?.events?.length || seEventsRef.current.length) ? (
                          <div className="tm-rt-events mono">
                            {[...(data?.events ?? [])]
                              .slice(-60)
                              .map((ev) => ({
                                ts: typeof ev.ts === "number" ? ev.ts * 1000 : Date.now(),
                                severity: ev.type.toUpperCase().includes("ERROR") ? "ERROR" : ev.type.toUpperCase().includes("WARN") ? "WARN" : "INFO",
                                sym: "ALL",
                                event: ev.type,
                                detail: ev.msg,
                              }))
                              .concat(
                                seEventsRef.current.slice(-30).map((e) => ({
                                  ts: e.ts,
                                  severity: e.outcome === "REJECTED" || e.risk === "BLOCK" ? "WARN" : e.outcome === "FILLED" ? "INFO" : "INFO",
                                  sym: e.symbol,
                                  event: e.risk === "BLOCK" ? "RISK_BLOCKED" : e.outcome,
                                  detail: `${e.action} · ${e.reason}${e.outcomeReason ? ` · ${e.outcomeReason}` : ""}`,
                                }))
                              )
                              .sort((a, b) => b.ts - a.ts)
                              .slice(0, 80)
                              .map((r, i) => (
                                <div key={i} className={`tm-rt-ev sev-${r.severity}`}>
                                  <span className="ts">{new Date(r.ts).toLocaleTimeString()}</span>
                                  <span className="sev">{r.severity}</span>
                                  <span className="sym">{r.sym}</span>
                                  <span className="ev">{String(r.event).toUpperCase()}</span>
                                  <span className="msg">{r.detail}</span>
                                </div>
                              ))}
                          </div>
                        ) : (
                          "No events yet."
                        ))}
                      {tab === "diag" && <pre className="tm-diag">{JSON.stringify(latest, null, 2)}</pre>}
                    </div>
                  </div>
                </div>
              </aside>
            </div>
          )}
        </div>
      )}

      {activeSection !== null && eventBadge && (
        <div className="tm-event-badge mono" style={{ background: eventBadge.color, color: "#0b0e14" }}>
          {eventBadge.text}
        </div>
      )}

      {expanded && (
        <div className="tm-overlay-back" role="presentation" onClick={() => setExpanded(null)}>
          <div className="tm-overlay-panel" role="dialog" onClick={(e) => e.stopPropagation()}>
            <div className="tm-overlay-head">
              <span className="tm-overlay-title mono">{overlayTitle}</span>
              <button type="button" className="tm-overlay-close" aria-label="Close" onClick={() => setExpanded(null)}>
                ×
              </button>
            </div>
            <div className="tm-overlay-plot">
              <Plot
                data={overlayTraces}
                layout={{ ...plotLayout(overlayTitle, 400), legend: { ...plotBase().legend } }}
                config={{ displayModeBar: true, responsive: true }}
                style={{ width: "100%", height: "100%" }}
              />
            </div>
          </div>
        </div>
      )}
    </div>
  );
}
