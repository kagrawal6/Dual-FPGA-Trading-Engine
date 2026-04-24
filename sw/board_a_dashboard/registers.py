"""Board A AXI-Lite offsets (must match rtl/board_a/board_a_axi_regs.sv)."""

CTRL = 0x00
QUOTE_INTERVAL = 0x04
LFSR_SEED = 0x08
REGIME = 0x0C
INIT_MID_BASE = 0x10
INIT_SPREAD_BASE = 0x50
SECTOR_ID_BASE = 0x90
TOKEN_BASE = 0xD0
ACTIVE_SYM_COUNT = 0xF0
STATUS = 0xF4
QUOTES_SENT = 0xF8
ORDERS_RCVD = 0xFC

NUM_SYM = 16

REGIME_NAMES = {0: "CALM", 1: "VOLATILE", 2: "BURST", 3: "ADVERSARIAL"}

SECTOR_LABELS = (
    "Technology",
    "Energy",
    "Health Care",
    "Consumer Disc.",
    "Financials",
    "Industrials",
    "Staples / Utilities",
    "Communication",
)
