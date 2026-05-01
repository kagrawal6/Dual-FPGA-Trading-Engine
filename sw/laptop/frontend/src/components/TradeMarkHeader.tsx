type Props = {
  regimeName: string;
  regimeColor: string;
  strategy: string;
  linkUp: boolean;
  demoMode: boolean;
};

export function TradeMarkHeader({ regimeName, regimeColor, strategy, linkUp, demoMode }: Props) {
  return (
    <header className="tm-brand">
      <div className="tm-brand-left mono">
        <span className="tm-regime-chip" style={{ borderColor: regimeColor, color: regimeColor }}>
          {regimeName}
        </span>
      </div>
      <div className="tm-brand-center">
        <div className="tm-wordmark" aria-label="TradeMark">
          TradeMark
        </div>
      </div>
      <div className="tm-brand-right mono">
        <span className="tm-meta-pill">{strategy}</span>
        <span className={`tm-meta-pill ${linkUp ? "tm-meta-pill--good" : "tm-meta-pill--bad"}`}>
          link {linkUp ? "UP" : "DOWN"}
        </span>
        {demoMode && <span className="tm-meta-pill tm-meta-pill--demo">demo</span>}
      </div>
    </header>
  );
}
