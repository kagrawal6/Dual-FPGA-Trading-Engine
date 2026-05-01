import { useCallback, useEffect, useRef, useState } from "react";

export type TelemetryPacket = {
  ts: number;
  meta?: {
    symbols?: string[];
  };
  latest: Record<string, unknown>;
  rates: Record<string, number>;
  age_ms: number;
  connected: boolean;
  heartbeat: number;
  hardware_stalled: boolean;
  parse_errors: number;
  events: { ts: number; type: string; msg: string }[];
  regime_edge: boolean;
  series: {
    history_sec: number;
    ema_symbol: number;
    t_cash: number[];
    cash: number[];
    pnl: number[];
    port: number[];
    t_act: number[];
    quotes: number[];
    orders: number[];
    fills: number[];
    rejects: number[];
    t_sym: number[];
    mid: number[];
    ema: number[];
  };
};

function wsUrl(): string {
  const p = window.location.protocol === "https:" ? "wss:" : "ws:";
  return `${p}//${window.location.host}/ws/stream`;
}

export function useTelemetry(historySec: number, emaSymbol: number) {
  const [data, setData] = useState<TelemetryPacket | null>(null);
  const [wsState, setWsState] = useState<"connecting" | "open" | "closed">("connecting");
  const wsRef = useRef<WebSocket | null>(null);
  const prefsRef = useRef({ historySec, emaSymbol });
  prefsRef.current = { historySec, emaSymbol };

  const sendPrefs = useCallback(() => {
    const w = wsRef.current;
    if (w && w.readyState === WebSocket.OPEN) {
      w.send(
        JSON.stringify({
          history_sec: prefsRef.current.historySec,
          ema_symbol: prefsRef.current.emaSymbol,
        })
      );
    }
  }, []);

  useEffect(() => {
    sendPrefs();
  }, [historySec, emaSymbol, sendPrefs]);

  useEffect(() => {
    let cancelled = false;
    const connect = () => {
      if (cancelled) return;
      setWsState("connecting");
      const ws = new WebSocket(wsUrl());
      wsRef.current = ws;
      ws.onopen = () => {
        if (cancelled) return;
        setWsState("open");
        ws.send(
          JSON.stringify({
            history_sec: prefsRef.current.historySec,
            ema_symbol: prefsRef.current.emaSymbol,
          })
        );
      };
      ws.onmessage = (ev) => {
        try {
          const pkt = JSON.parse(ev.data) as TelemetryPacket;
          setData(pkt);
        } catch {
          /* ignore */
        }
      };
      ws.onclose = () => {
        if (cancelled) return;
        setWsState("closed");
        wsRef.current = null;
        setTimeout(connect, 1500);
      };
      ws.onerror = () => {
        ws.close();
      };
    };
    connect();
    return () => {
      cancelled = true;
      wsRef.current?.close();
      wsRef.current = null;
    };
  }, []);

  return { data, wsState };
}
