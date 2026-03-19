#!/usr/bin/env python3
"""
Board A PS Script — config_exchange.py
Configures the exchange simulator and starts quote generation.
Run once at boot or when reconfiguring. See §5.1.1 of design spec.
"""

from pynq import Overlay, MMIO

# Register offsets (Board A — Appendix D.1)
CTRL           = 0x00
QUOTE_INTERVAL = 0x04
LFSR_SEED      = 0x08
REGIME         = 0x0C
SYM0_INIT_MID  = 0x10
SYM0_INIT_SPREAD = 0x14
SYM1_INIT_MID  = 0x18
SYM1_INIT_SPREAD = 0x1C
SYM2_INIT_MID  = 0x20
SYM2_INIT_SPREAD = 0x24
SYM3_INIT_MID  = 0x28
SYM3_INIT_SPREAD = 0x2C
STATUS         = 0x40
QUOTES_SENT    = 0x44
ORDERS_RCVD    = 0x48
FILLS_SENT     = 0x4C
REJECTS_SENT   = 0x50
LINK_ERRORS    = 0x54
FIFO_FILL      = 0x58


def q16_16(val):
    """Convert float to unsigned Q16.16."""
    return int(val * 65536) & 0xFFFFFFFF


def main():
    ol = Overlay("overlays/board_a.bit")
    mmio = MMIO(ol.ip_dict['board_a_top_0']['phys_addr'], 256)

    # Configure
    mmio.write(LFSR_SEED,        0xDEADBEEF)
    mmio.write(QUOTE_INTERVAL,   1000)
    mmio.write(REGIME,           0)              # 0=CALM

    mmio.write(SYM0_INIT_MID,    q16_16(150.25))
    mmio.write(SYM0_INIT_SPREAD, q16_16(0.125))
    mmio.write(SYM1_INIT_MID,    q16_16(200.00))
    mmio.write(SYM1_INIT_SPREAD, q16_16(0.25))
    mmio.write(SYM2_INIT_MID,    q16_16(50.00))
    mmio.write(SYM2_INIT_SPREAD, q16_16(0.0625))
    mmio.write(SYM3_INIT_MID,    q16_16(75.00))
    mmio.write(SYM3_INIT_SPREAD, q16_16(0.1875))

    # Start
    mmio.write(CTRL, 0x01)
    print("Board A started. Quotes flowing.")

    # Readback
    status = mmio.read(STATUS)
    print(f"STATUS: 0x{status:08X}  running={status & 1}")


if __name__ == "__main__":
    main()
