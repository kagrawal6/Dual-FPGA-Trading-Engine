import { useEffect, useRef } from "react";
import Globe from "globe.gl";

type ContinentKey = "na" | "sa" | "eu" | "af" | "as" | "me" | "oc";

const HUB_POV_CITIES = [
  { lat: 40.7128, lng: -74.006, continent: "na" as const },
  { lat: -23.5505, lng: -46.6333, continent: "sa" as const },
  { lat: 51.5074, lng: -0.1278, continent: "eu" as const },
  { lat: 50.1109, lng: 8.6821, continent: "eu" as const },
  { lat: -26.2041, lng: 28.0473, continent: "af" as const },
  { lat: 25.2048, lng: 55.2708, continent: "me" as const },
  { lat: 1.3521, lng: 103.8198, continent: "as" as const },
  { lat: 35.6762, lng: 139.6503, continent: "as" as const },
  { lat: 22.3193, lng: 114.1694, continent: "as" as const },
  { lat: -33.8688, lng: 151.2093, continent: "oc" as const },
  { lat: 37.7749, lng: -122.4194, continent: "na" as const },
  { lat: 40.4168, lng: -3.7038, continent: "eu" as const },
] as const;

type HubCity = (typeof HUB_POV_CITIES)[number];

const CONTINENT_BOUNDS: Record<
  ContinentKey,
  { latMin: number; latMax: number; lngMin: number; lngMax: number }
> = {
  na: { latMin: 15, latMax: 72, lngMin: -168, lngMax: -52 },
  sa: { latMin: -55, latMax: 14, lngMin: -82, lngMax: -34 },
  eu: { latMin: 36, latMax: 71, lngMin: -24, lngMax: 42 },
  af: { latMin: -35, latMax: 37, lngMin: -20, lngMax: 52 },
  as: { latMin: -12, latMax: 52, lngMin: 65, lngMax: 155 },
  me: { latMin: 12, latMax: 42, lngMin: 34, lngMax: 63 },
  oc: { latMin: -48, latMax: -5, lngMin: 112, lngMax: 179 },
};

const FX_PAIRS_GLOBAL = [
  "EUR/USD",
  "USD/JPY",
  "GBP/USD",
  "USD/CHF",
  "AUD/USD",
  "USD/CAD",
  "NZD/USD",
  "EUR/GBP",
  "EUR/JPY",
  "GBP/JPY",
  "XAU/USD",
  "BTC/USD",
];

const FX_PAIRS_REGIONAL: Record<ContinentKey, string[]> = {
  na: ["USD/MXN", "USD/CAD", "US10Y/US2Y", "SPX/NDX"],
  sa: ["USD/BRL", "EUR/BRL", "CLP/USD"],
  eu: ["EUR/CHF", "EUR/SEK", "EUR/NOK", "GBP/CHF", "DAX/ESTX50"],
  af: ["USD/ZAR", "EUR/ZAR", "XAU/ZAR", "NGN/USD"],
  as: ["USD/KRW", "USD/SGD", "USD/CNH", "JPY/THB", "IDR/USD"],
  me: ["USD/AED", "USD/SAR", "USD/ILS", "XAU/AED"],
  oc: ["AUD/NZD", "AUD/JPY", "NZD/JPY"],
};

type ArcLayer = "global" | "regional";

type ArcRow = {
  startLat: number;
  startLng: number;
  endLat: number;
  endLng: number;
  color: [string, string];
  layer: ArcLayer;
  dashLen: number;
  dashGap: number;
  dashTime: number;
  dashInitial: number;
  /** Camera-stop generation; global uses 0 */
  focusGen: number;
};

type PopupRow = {
  lat: number;
  lng: number;
  pair: string;
  notional: string;
  profit: string;
  variant?: "ambient";
  /** Matches regional arc generation for gradual UI fade */
  focusGen?: number;
};

type LandPulseRow = {
  kind: "landPulse";
  id: string;
  lat: number;
  lng: number;
};

type HtmlEl = PopupRow | LandPulseRow;

function isLandPulse(h: HtmlEl): h is LandPulseRow {
  return (h as LandPulseRow).kind === "landPulse";
}

function isRegionalPopup(h: HtmlEl): h is PopupRow {
  return !isLandPulse(h) && !(h as PopupRow).variant;
}

const CAP_GLOBAL_ARCS = 64;
const CAP_GLOBAL_POPUPS = 18;
const CAP_REGIONAL_ARCS = 140;
const CAP_REGIONAL_HTML = 180;

function rand(min: number, max: number) {
  return min + Math.random() * (max - min);
}

function clamp(x: number, lo: number, hi: number) {
  return Math.min(hi, Math.max(lo, x));
}

function degSep(a: { lat: number; lng: number }, e: { lat: number; lng: number }) {
  const dlat = a.lat - e.lat;
  const dlng = a.lng - e.lng;
  return Math.sqrt(dlat * dlat + dlng * dlng);
}

function hexToRgba(hex: string, alpha: number): string {
  const m = hex.replace("#", "").trim();
  if (m.length !== 6) return hex;
  const r = parseInt(m.slice(0, 2), 16);
  const g = parseInt(m.slice(2, 4), 16);
  const b = parseInt(m.slice(4, 6), 16);
  return `rgba(${r},${g},${b},${clamp(alpha, 0, 1)})`;
}

function dimColorPair(pair: [string, string], alphaMul: number): [string, string] {
  const a = (c: string) => {
    if (c.startsWith("rgba(")) return c;
    if (c.startsWith("#") && c.length === 7) return hexToRgba(c, alphaMul);
    return c;
  };
  return [a(pair[0]), a(pair[1])];
}

function randomGlobalPoint(): { lat: number; lng: number } {
  return {
    lat: (Math.random() - 0.5) * 168,
    lng: (Math.random() - 0.5) * 360,
  };
}

function randomPointInContinent(continent: ContinentKey): { lat: number; lng: number } {
  const b = CONTINENT_BOUNDS[continent];
  return {
    lat: rand(b.latMin, b.latMax),
    lng: rand(b.lngMin, b.lngMax),
  };
}

function pickPair(continent: ContinentKey): string {
  const regional = FX_PAIRS_REGIONAL[continent];
  if (regional.length && Math.random() < 0.55) {
    return regional[Math.floor(Math.random() * regional.length)];
  }
  return FX_PAIRS_GLOBAL[Math.floor(Math.random() * FX_PAIRS_GLOBAL.length)];
}

function pickRegionalColors(): [string, string] {
  const roll = Math.random();
  if (roll < 0.55) return ["#5AC8FA", "#2962FF"];
  if (roll < 0.82) return ["#7DD3FC", "#2962FF"];
  return ["#C4B5FD", "#5AC8FA"];
}

function pickGlobalColors(): [string, string] {
  const a = 0.18 + Math.random() * 0.12;
  const b = 0.14 + Math.random() * 0.1;
  return [`rgba(90,200,250,${a})`, `rgba(41,98,255,${b})`];
}

function buildGlobalArcs(n: number): ArcRow[] {
  const arcs: ArcRow[] = [];
  let guard = 0;
  while (arcs.length < n && guard < 8000) {
    guard += 1;
    const s = randomGlobalPoint();
    const e = randomGlobalPoint();
    const d = degSep(s, e);
    if (d < 16 || d > 128) continue;
    arcs.push({
      startLat: s.lat,
      startLng: s.lng,
      endLat: e.lat,
      endLng: e.lng,
      color: pickGlobalColors(),
      layer: "global",
      dashLen: rand(0.042, 0.11),
      dashGap: rand(0.94, 0.995),
      dashTime: rand(3800, 9200),
      dashInitial: Math.random(),
      focusGen: 0,
    });
  }
  return arcs;
}

function buildAmbientPopupsForArcs(arcs: ArcRow[], maxPopups: number): PopupRow[] {
  const out: PopupRow[] = [];
  const step = Math.max(1, Math.floor(arcs.length / maxPopups));
  for (let i = 0; i < arcs.length && out.length < maxPopups; i += step) {
    const a = arcs[i];
    const t = 0.22 + Math.random() * 0.42;
    const lat = a.startLat + (a.endLat - a.startLat) * t;
    const lng = a.startLng + (a.endLng - a.startLng) * t;
    const pair = FX_PAIRS_GLOBAL[Math.floor(Math.random() * FX_PAIRS_GLOBAL.length)];
    const notional = `$${rand(0.15, 5.5).toFixed(1)}M`;
    const profit = `+$${Math.round(rand(35, 1100)).toLocaleString("en-US")}`;
    out.push({ lat, lng, pair, notional, profit, variant: "ambient" });
  }
  return out;
}

function travelMsForArc(arc: ArcRow): number {
  const base = arc.layer === "regional" ? arc.dashTime * 0.38 + 420 : arc.dashTime * 0.28 + 800;
  return Math.round(clamp(base, 520, 1600));
}

function buildSingleRegionalTrade(city: HubCity): {
  arc: ArcRow;
  popup: PopupRow;
  travelMs: number;
} | null {
  const cont = city.continent;
  for (let g = 0; g < 400; g += 1) {
    const s = randomPointInContinent(cont);
    const e = randomPointInContinent(cont);
    const d = degSep(s, e);
    if (d < 2.2 || d > 52) continue;
    const pair = pickPair(cont);
    const profit = `+$${Math.round(rand(160, 4800)).toLocaleString("en-US")}`;
    const notional = `$${rand(0.35, 11.5).toFixed(1)}M`;
    const arc: ArcRow = {
      startLat: s.lat,
      startLng: s.lng,
      endLat: e.lat,
      endLng: e.lng,
      color: pickRegionalColors(),
      layer: "regional",
      dashLen: rand(0.11, 0.22),
      dashGap: rand(0.94, 0.992),
      dashTime: rand(880, 2100),
      dashInitial: Math.random() * 0.35,
      focusGen: 0,
    };
    const popup: PopupRow = {
      lat: e.lat,
      lng: e.lng,
      pair,
      notional,
      profit,
    };
    return {
      arc,
      popup,
      travelMs: travelMsForArc(arc),
    };
  }
  return null;
}

function trimRegional(arcs: ArcRow[], html: HtmlEl[], maxArcs: number, maxHtml: number) {
  while (arcs.length > maxArcs) arcs.shift();
  while (html.length > maxHtml) html.shift();
}

export function GlobeGlRandomArcs() {
  const hostRef = useRef<HTMLDivElement | null>(null);

  useEffect(() => {
    const el = hostRef.current;
    if (!el) return;

    let cancelled = false;
    let stopSerial = 0;
    let landPulseSeq = 0;
    const timers: number[] = [];
    const scheduleAny = (fn: () => void, ms: number) => {
      const id = window.setTimeout(() => {
        if (!cancelled) fn();
      }, ms);
      timers.push(id);
      return id;
    };
    const clearTimers = () => {
      timers.forEach((id) => window.clearTimeout(id));
      timers.length = 0;
    };

    let globalArcs: ArcRow[] = [];
    let globalHtml: PopupRow[] = [];
    const regionalArcs: ArcRow[] = [];
    const regionalHtml: HtmlEl[] = [];

    const syncGlobe = () => {
      globe.arcsData([...globalArcs, ...regionalArcs]);
      globe.htmlElementsData([...globalHtml, ...regionalHtml]);
    };

    const appendGlobalBurst = (count: number) => {
      const add = buildGlobalArcs(count);
      globalArcs = [...globalArcs, ...add].slice(-CAP_GLOBAL_ARCS);
      globalHtml = buildAmbientPopupsForArcs(
        globalArcs,
        Math.min(CAP_GLOBAL_POPUPS, 10 + Math.floor(globalArcs.length / 3))
      );
    };

    const globe = new Globe(el)
      .backgroundColor("rgba(11,14,20,0)")
      .showAtmosphere(true)
      .atmosphereColor("rgba(90,200,250,0.12)")
      .enablePointerInteraction(false)
      .globeImageUrl("https://cdn.jsdelivr.net/npm/three-globe/example/img/earth-night.jpg")
      .arcColor((d: ArcRow) => {
        if (d.layer !== "regional") return d.color;
        const lag = stopSerial - d.focusGen;
        if (lag <= 0) return d.color;
        const a = lag === 1 ? 0.48 : lag === 2 ? 0.28 : 0.14;
        return dimColorPair(d.color, a);
      })
      .arcStroke((d: ArcRow) => {
        if (d.layer === "global") return 0.2;
        const lag = stopSerial - d.focusGen;
        if (lag <= 0) return 0.38;
        if (lag === 1) return 0.26;
        return 0.16;
      })
      .arcDashLength((d: ArcRow) => d.dashLen)
      .arcDashGap((d: ArcRow) => d.dashGap)
      .arcDashInitialGap((d: ArcRow) => d.dashInitial)
      .arcDashAnimateTime((d: ArcRow) => d.dashTime)
      .arcsTransitionDuration(480)
      .htmlAltitude(() => 0.02)
      .htmlTransitionDuration(900)
      .htmlElement((d: HtmlEl) => {
        if (isLandPulse(d)) {
          const node = document.createElement("div");
          node.className = "tm-fx-land-pulse";
          node.setAttribute("data-pulse-id", d.id);
          return node;
        }

        const root = document.createElement("div");
        root.className =
          d.variant === "ambient" ? "tm-fx-popup tm-fx-popup--ambient" : "tm-fx-popup";

        const kicker = document.createElement("div");
        kicker.className = "tm-fx-popup-kicker";
        kicker.textContent = d.variant === "ambient" ? "Global · matched" : "Spot FX · filled";

        const pair = document.createElement("div");
        pair.className = "tm-fx-popup-pair mono";
        pair.textContent = d.pair;

        const row = document.createElement("div");
        row.className = "tm-fx-popup-row";
        const rowL = document.createElement("span");
        rowL.textContent = "Notional";
        const rowR = document.createElement("span");
        rowR.className = "mono";
        rowR.textContent = "—";
        row.append(rowL, rowR);

        const profit = document.createElement("div");
        profit.className = "tm-fx-popup-profit mono";
        profit.textContent = "";

        root.append(kicker, pair, row, profit);

        const tNotional = 220 + Math.random() * 420;
        const tProfit = tNotional + 260 + Math.random() * 520;
        scheduleAny(() => {
          if (!rowR.isConnected) return;
          rowR.textContent = d.notional;
        }, tNotional);
        scheduleAny(() => {
          if (!profit.isConnected) return;
          profit.textContent = d.profit;
        }, tProfit);

        return root;
      })
      .htmlElementVisibilityModifier((node: HTMLElement, isVisible: boolean) => {
        node.style.opacity = isVisible ? "1" : "0";
      });

    globe.globeOffset([0, 64]);

    const reduceMotion =
      typeof window !== "undefined" &&
      window.matchMedia("(prefers-reduced-motion: reduce)").matches;

    const controls = globe.controls();
    const baseAuto = 0.38;
    if (!reduceMotion) {
      controls.autoRotate = true;
      controls.autoRotateSpeed = baseAuto;
    } else {
      controls.autoRotate = false;
    }

    const enqueueRegionalArrival = (
      trade: { arc: ArcRow; popup: PopupRow; travelMs: number },
      sid: number,
      schedStop: (fn: () => void, ms: number) => void
    ) => {
      const { travelMs, popup } = trade;
      const pulseId = `lp-${++landPulseSeq}`;
      const taggedArc: ArcRow = { ...trade.arc, focusGen: sid };
      const taggedPopup: PopupRow = { ...popup, focusGen: sid };

      regionalArcs.push(taggedArc);
      trimRegional(regionalArcs, regionalHtml, CAP_REGIONAL_ARCS, CAP_REGIONAL_HTML);
      syncGlobe();

      schedStop(() => {
        regionalHtml.push({
          kind: "landPulse",
          id: pulseId,
          lat: taggedPopup.lat,
          lng: taggedPopup.lng,
        });
        trimRegional(regionalArcs, regionalHtml, CAP_REGIONAL_ARCS, CAP_REGIONAL_HTML);
        syncGlobe();
      }, travelMs);

      schedStop(() => {
        regionalHtml.push(taggedPopup);
        trimRegional(regionalArcs, regionalHtml, CAP_REGIONAL_ARCS, CAP_REGIONAL_HTML);
        syncGlobe();
      }, travelMs + 90 + Math.random() * 220);

      schedStop(() => {
        const next = regionalHtml.filter(
          (h) => !isLandPulse(h) || (h as LandPulseRow).id !== pulseId
        );
        regionalHtml.length = 0;
        regionalHtml.push(...next);
        trimRegional(regionalArcs, regionalHtml, CAP_REGIONAL_ARCS, CAP_REGIONAL_HTML);
        syncGlobe();
      }, travelMs + 920);
    };

    const pruneLegacyForSid = (sid: number, schedStop: (fn: () => void, ms: number) => void) => {
      const tick = () => {
        if (cancelled || stopSerial !== sid) return;
        let removed = 0;
        for (let i = 0; i < regionalArcs.length && removed < 5; ) {
          const a = regionalArcs[i];
          if (a.layer === "regional" && a.focusGen < sid) {
            regionalArcs.splice(i, 1);
            removed += 1;
          } else {
            i += 1;
          }
        }
        let prPop = 0;
        for (let i = 0; i < regionalHtml.length && prPop < 4; ) {
          const h = regionalHtml[i];
          if (isRegionalPopup(h) && h.focusGen != null && h.focusGen < sid) {
            regionalHtml.splice(i, 1);
            prPop += 1;
          } else {
            i += 1;
          }
        }
        trimRegional(regionalArcs, regionalHtml, CAP_REGIONAL_ARCS, CAP_REGIONAL_HTML);
        syncGlobe();

        const more = regionalArcs.some((a) => a.layer === "regional" && a.focusGen < sid);
        if (more) schedStop(tick, 620 + Math.random() * 280);
      };
      schedStop(tick, 3600);
    };

    const runCityStop = (cityIndex: number) => {
      if (cancelled) return;
      stopSerial += 1;
      const sid = stopSerial;
      const phaseEmit = (phase: "handoff" | "approach" | "zoom" | "execute") => {
        try {
          const n = HUB_POV_CITIES.length;
          const idx = ((cityIndex % n) + n) % n;
          const city = HUB_POV_CITIES[idx];
          window.dispatchEvent(
            new CustomEvent("tm:globeFocus", {
              detail: { idx, lat: city.lat, lng: city.lng, continent: city.continent, phase, sid },
            })
          );
        } catch {
          /* ignore */
        }
      };

      phaseEmit("approach");
      globe.arcsData([...globalArcs, ...regionalArcs]);

      const schedStop = (fn: () => void, ms: number) => {
        const id = window.setTimeout(() => {
          if (cancelled || stopSerial !== sid) return;
          fn();
        }, ms);
        timers.push(id);
      };

      const n = HUB_POV_CITIES.length;
      const idx = ((cityIndex % n) + n) % n;
      const city = HUB_POV_CITIES[idx];

      if (reduceMotion) {
        const nTrades = 18;
        for (let i = 0; i < nTrades; i += 1) {
          const t = buildSingleRegionalTrade(city);
          if (t) {
            const arc: ArcRow = {
              ...t.arc,
              focusGen: sid,
              dashLen: 1,
              dashGap: 0,
              dashTime: 0,
              dashInitial: 0,
            };
            regionalArcs.push(arc);
            regionalHtml.push({ ...t.popup, focusGen: sid });
          }
        }
        trimRegional(regionalArcs, regionalHtml, CAP_REGIONAL_ARCS, CAP_REGIONAL_HTML);
        syncGlobe();
        globe.pointOfView({ lat: city.lat, lng: city.lng, altitude: 1.28 }, 0);
        schedStop(() => runCityStop(idx + 1), 9000);
        return;
      }

      controls.autoRotateSpeed = 0.12;

      const wideAlt = 2.05 + Math.random() * 0.1;
      const closeAlt = 1.16 + Math.random() * 0.1;

      /* Soft regional flow during camera move (previous stop arcs stay; new ones accrue) */
      const lightTotal = 6 + Math.floor(Math.random() * 4);
      let lightDone = 0;
      const lightStep = () => {
        if (cancelled || stopSerial !== sid) return;
        if (lightDone >= lightTotal) return;
        const t = buildSingleRegionalTrade(city);
        if (t) enqueueRegionalArrival(t, sid, schedStop);
        lightDone += 1;
        schedStop(lightStep, 820 + Math.random() * 520);
      };
      schedStop(lightStep, 280 + Math.random() * 220);

      /* Extra world activity while shifting focus (still lighter than regional burst) */
      for (let g = 0; g < 4; g += 1) {
        schedStop(() => {
          appendGlobalBurst(3);
          syncGlobe();
        }, 900 + g * 1600);
      }

      globe.pointOfView({ lat: city.lat, lng: city.lng, altitude: wideAlt }, 2600);

      schedStop(() => {
        phaseEmit("zoom");
        controls.autoRotateSpeed = 0.06;
        globe.pointOfView({ lat: city.lat, lng: city.lng, altitude: closeAlt }, 3000);
      }, 2700);

      schedStop(() => {
        phaseEmit("execute");
        controls.autoRotateSpeed = 0.14;

        const nTrades = 15 + Math.floor(Math.random() * 7);
        let done = 0;

        const step = () => {
          if (cancelled || stopSerial !== sid) return;
          if (done >= nTrades) {
            controls.autoRotateSpeed = baseAuto;
            pruneLegacyForSid(sid, schedStop);
            phaseEmit("handoff");
            schedStop(
              () => runCityStop(idx + 1),
              4200 + Math.floor(Math.random() * 1600)
            );
            return;
          }

          const trade = buildSingleRegionalTrade(city);
          if (trade) enqueueRegionalArrival(trade, sid, schedStop);

          done += 1;
          const gap = 380 + Math.random() * 380;
          schedStop(step, gap);
        };

        schedStop(step, 60 + Math.random() * 140);
      }, 2700 + 3200);
    };

    appendGlobalBurst(34);
    syncGlobe();

    const startIdx = Math.floor(Math.random() * HUB_POV_CITIES.length);
    const first = HUB_POV_CITIES[startIdx];
    if (!reduceMotion) {
      globe.pointOfView(
        { lat: first.lat, lng: first.lng, altitude: 2.02 + Math.random() * 0.08 },
        0
      );
    } else {
      globe.pointOfView({ lat: first.lat, lng: first.lng, altitude: 1.3 }, 0);
    }

    scheduleAny(() => runCityStop(startIdx), reduceMotion ? 400 : 700);

    const ro = new ResizeObserver(() => {
      const w = el.clientWidth;
      const h = el.clientHeight;
      if (w > 0 && h > 0) globe.width(w).height(h);
    });
    ro.observe(el);

    const globalRefreshId = window.setInterval(() => {
      if (cancelled) return;
      appendGlobalBurst(11);
      syncGlobe();
    }, 11000);

    return () => {
      cancelled = true;
      clearTimers();
      window.clearInterval(globalRefreshId);
      ro.disconnect();
      try {
        controls.autoRotate = false;
      } catch {
        /* ignore */
      }
      try {
        globe._destructor();
      } catch {
        /* ignore */
      }
    };
  }, []);

  return <div className="tm-globegl" ref={hostRef} aria-hidden="true" />;
}
