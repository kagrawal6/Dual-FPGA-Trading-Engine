// ============================================================================
// File List: Shared + Link modules and their testbenches
// Usage:  vlog -sv -f filelist_shared.f
// Run from: sim/ directory
// ============================================================================

// ── 1. Package ─────────────────────────────────────────────────────────────
../rtl/shared/hft_pkg.sv

// ── 2. Shared modules ──────────────────────────────────────────────────────
../rtl/shared/debounce.sv
../rtl/shared/sync_fifo.sv
../rtl/shared/lfsr32.sv

// ── 3. Link modules ────────────────────────────────────────────────────────
../rtl/link/link_tx.sv
../rtl/link/link_rx.sv

// ── 4. Testbenches ─────────────────────────────────────────────────────────
../tb/shared/tb_debounce.sv
../tb/shared/tb_sync_fifo.sv
../tb/shared/tb_lfsr32.sv
../tb/link/tb_link_tx.sv
../tb/link/tb_link_rx.sv
../tb/link/tb_link_loopback.sv
