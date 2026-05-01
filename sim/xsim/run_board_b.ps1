# =============================================================================
# Vivado XSim runner -- Board B testbenches.
#
# Default behaviour (FAST):
#   - skip xvlog if work/ library is up-to-date with sources.prj + RTL/TB
#   - skip xelab if <tb>_snapshot/ is up-to-date
#   - skip the heavyweight tb_nn_inference (huge xelab time on the unrolled
#     NN MACs) unless -IncludeSlow is passed
#
# Flags:
#   -Only <tb>       only run that one TB (still respects caching)
#   -Clean           wipe xsim.dir/ first to force full rebuild
#   -IncludeSlow     also run tb_nn_inference (slow elab; ~5+ min on first run)
#
# Examples (from sim/xsim/):
#   .\run_board_b.ps1                                 # 10 fast Board B TBs
#   .\run_board_b.ps1 -IncludeSlow                    # all 11, incl. NN
#   .\run_board_b.ps1 -Only tb_nn_inference           # just NN
#   .\run_board_b.ps1 -Only tb_msg_demux -Clean       # rebuild + run one TB
# =============================================================================

param(
    [string]$Only        = "",
    [switch]$Clean       = $false,
    [switch]$IncludeSlow = $false
)

$ErrorActionPreference = "Stop"
Set-Location -Path $PSScriptRoot

# ---------------------------------------------------------------------------
# 1. Auto-source Vivado settings (no-op if xvlog is already on PATH).
# ---------------------------------------------------------------------------
. "$PSScriptRoot\_load_vivado_env.ps1"
if (-not (Import-VivadoEnv)) { exit 1 }

# ---------------------------------------------------------------------------
# 2. Test list
# ---------------------------------------------------------------------------
$fastTests = @(
    "tb_msg_demux",
    "tb_quote_book",
    "tb_feature_compute",
    "tb_strategy_engine",
    "tb_risk_manager",
    "tb_order_manager",
    "tb_position_tracker",
    "tb_latency_histogram",
    "tb_board_b_ctrl",
    "tb_board_b_axi_regs"
)
$slowTests = @(
    "tb_nn_inference"        # ~5+ min xelab on first run (NN MAC unroll)
)
$allTests = $fastTests + $slowTests

if ($Only -ne "") {
    if ($allTests -notcontains $Only) {
        Write-Host "ERROR: '$Only' is not in the Board B TB list." -ForegroundColor Red
        Write-Host "Available: $($allTests -join ', ')"
        exit 1
    }
    $tests = @($Only)
} elseif ($IncludeSlow) {
    $tests = $allTests
} else {
    $tests = $fastTests
    Write-Host "(skipping tb_nn_inference -- pass -IncludeSlow to include it)" -ForegroundColor DarkGray
}

# ---------------------------------------------------------------------------
# 3. Workspace setup
# ---------------------------------------------------------------------------
$workDir = Join-Path $PSScriptRoot "xsim.dir"
$logDir  = Join-Path $PSScriptRoot "xsim_logs"

if ($Clean) {
    Write-Host "-Clean: wiping xsim.dir/" -ForegroundColor DarkGray
    if (Test-Path $workDir) { Remove-Item -Recurse -Force $workDir }
    foreach ($f in @("xvlog.log","xvlog.pb","xelab.log","xelab.pb",
                     "xsim.log","xsim.jou","xvlog.jou","xelab.jou",
                     "compile.log","compile.pb")) {
        if (Test-Path $f) { Remove-Item -Force $f }
    }
}
if (-not (Test-Path $logDir)) { New-Item -ItemType Directory -Path $logDir | Out-Null }

# ---------------------------------------------------------------------------
# 4. Source-newer-than-cache check (decides whether xvlog must run again)
# ---------------------------------------------------------------------------
function Get-NewestSourceTime {
    $latest = [DateTime]::MinValue
    foreach ($p in @("sources.prj")) {
        if (Test-Path $p) {
            $t = (Get-Item $p).LastWriteTime
            if ($t -gt $latest) { $latest = $t }
        }
    }
    foreach ($dir in @("..\..\rtl","..\..\tb")) {
        if (Test-Path $dir) {
            $files = Get-ChildItem -Path $dir -Recurse -Include *.sv,*.v -ErrorAction SilentlyContinue
            foreach ($f in $files) {
                if ($f.LastWriteTime -gt $latest) { $latest = $f.LastWriteTime }
            }
        }
    }
    return $latest
}

$sourceTime  = Get-NewestSourceTime
$workTime    = if (Test-Path $workDir) { (Get-Item $workDir).LastWriteTime } else { [DateTime]::MinValue }
$needCompile = (-not (Test-Path $workDir)) -or ($sourceTime -gt $workTime)

# ---------------------------------------------------------------------------
# 5. Compile (cached)
# ---------------------------------------------------------------------------
if ($needCompile) {
    Write-Host "==========================================" -ForegroundColor Cyan
    Write-Host " XSim: Compiling all sources..." -ForegroundColor Cyan
    Write-Host "==========================================" -ForegroundColor Cyan
    $compileLog = Join-Path $logDir "_compile.log"
    & xvlog -sv -prj sources.prj 2>&1 | Tee-Object -FilePath $compileLog | Out-Null
    if ($LASTEXITCODE -ne 0) {
        Write-Host "COMPILE FAILED -- see $compileLog" -ForegroundColor Red
        Get-Content $compileLog | Select-String -Pattern "ERROR" | ForEach-Object { Write-Host $_ -ForegroundColor Red }
        exit 1
    }
    Write-Host "Compile OK." -ForegroundColor Green
    # Touch the work dir so next run sees it as fresh
    (Get-Item $workDir).LastWriteTime = Get-Date
} else {
    Write-Host "Compile cache up-to-date (use -Clean to force rebuild)." -ForegroundColor DarkGray
}
Write-Host ""

# ---------------------------------------------------------------------------
# 6. PASS/FAIL detection patterns
# ---------------------------------------------------------------------------
$passPatterns = @(
    'ALL TESTS PASSED', 'TEST PASSED', 'PASS \(', 'PASSED:',
    'Simulation completed successfully', 'All checks passed'
)
$failPatterns = @(
    'FATAL_ERROR', 'TESTBENCH FAILED', 'TEST FAILED', 'FAIL \(',
    'Assertion error', 'Fatal:', '\$fatal'
)

# ---------------------------------------------------------------------------
# 7. Per-TB: elaborate (cached) + run
# ---------------------------------------------------------------------------
$results = [ordered]@{}
foreach ($tb in $tests) {
    Write-Host "------------------------------------------" -ForegroundColor Yellow
    Write-Host " Running $tb" -ForegroundColor Yellow
    Write-Host "------------------------------------------" -ForegroundColor Yellow

    $log      = Join-Path $logDir "$tb.log"
    $snapshot = "${tb}_snapshot"
    $snapDir  = Join-Path $workDir $snapshot

    $needElab = (-not (Test-Path $snapDir)) -or
                ($sourceTime -gt (Get-Item $snapDir).LastWriteTime)

    if ($needElab) {
        Write-Host "  xelab..." -ForegroundColor DarkGray
        & xelab -relax -s $snapshot "work.$tb" -timescale 1ns/1ps 2>&1 | Tee-Object -FilePath $log | Out-Null
        if ($LASTEXITCODE -ne 0) {
            Write-Host "  ELAB FAILED" -ForegroundColor Red
            $results[$tb] = "ELAB_FAIL"
            continue
        }
    } else {
        Write-Host "  (using cached snapshot)" -ForegroundColor DarkGray
        Set-Content -Path $log -Value "(elab skipped -- cached snapshot up-to-date)"
    }

    & xsim $snapshot -R 2>&1 | Tee-Object -FilePath $log -Append | Out-Null
    $simExit = $LASTEXITCODE

    $logText = Get-Content $log -Raw

    $hasPass = $false; foreach ($p in $passPatterns) { if ($logText -match $p) { $hasPass = $true; break } }
    $hasFail = $false; foreach ($p in $failPatterns) { if ($logText -match $p) { $hasFail = $true; break } }

    if     ($hasFail)        { $results[$tb] = "FAIL";    Write-Host "  -> FAIL"    -ForegroundColor Red }
    elseif ($hasPass)        { $results[$tb] = "PASS";    Write-Host "  -> PASS"    -ForegroundColor Green }
    elseif ($simExit -ne 0)  { $results[$tb] = "ERROR";   Write-Host "  -> ERROR (exit=$simExit)" -ForegroundColor Red }
    else                     { $results[$tb] = "UNKNOWN"; Write-Host "  -> UNKNOWN (no PASS/FAIL banner)" -ForegroundColor DarkYellow }
}

# ---------------------------------------------------------------------------
# 8. Summary
# ---------------------------------------------------------------------------
$summaryFile = Join-Path $logDir "SUMMARY.txt"
$summary = @()
$summary += "==============================================="
$summary += " XSim Board B Test Summary"
$summary += "==============================================="
$pass = 0; $fail = 0; $other = 0
foreach ($k in $results.Keys) {
    $v = $results[$k]
    $summary += ("  {0,-30} {1}" -f $k, $v)
    if     ($v -eq "PASS") { $pass++ }
    elseif ($v -eq "FAIL") { $fail++ }
    else                   { $other++ }
}
$summary += "-----------------------------------------------"
$summary += "  PASS: $pass    FAIL: $fail    OTHER: $other"
$summary += "==============================================="

$summary | Tee-Object -FilePath $summaryFile | ForEach-Object {
    if     ($_ -match "PASS") { Write-Host $_ -ForegroundColor Green }
    elseif ($_ -match "FAIL|ERROR|UNKNOWN") { Write-Host $_ -ForegroundColor Red }
    else                       { Write-Host $_ }
}

if ($fail -gt 0 -or $other -gt 0) { exit 1 } else { exit 0 }
