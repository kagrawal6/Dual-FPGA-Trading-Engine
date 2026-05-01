# =============================================================================
# Vivado XSim runner -- top-level / system testbenches.
#
# These TBs all instantiate board_b_top, which now contains nn_inference. The
# first xelab pass on board_b_top will be slow (a few minutes) because the NN
# MAC array gets unrolled. Subsequent runs reuse the cached snapshot and start
# in seconds.
#
# Flags:
#   -Only <tb>   only run that one TB (still respects caching)
#   -Clean       wipe xsim.dir/ first to force full rebuild
#
# TBs:
#   tb_board_a_top, tb_board_b_top, tb_board_b_pipeline, tb_system_top
#
# Examples (from sim/xsim/):
#   .\run_top.ps1                          # all 4 (heavy first time, fast after)
#   .\run_top.ps1 -Only tb_board_a_top     # quick: no NN involved
#   .\run_top.ps1 -Only tb_system_top      # heaviest -- both boards + link
# =============================================================================

param(
    [string]$Only  = "",
    [switch]$Clean = $false
)

$ErrorActionPreference = "Stop"
Set-Location -Path $PSScriptRoot

. "$PSScriptRoot\_load_vivado_env.ps1"
if (-not (Import-VivadoEnv)) { exit 1 }

$tests = @(
    "tb_board_a_top",
    "tb_board_b_top",
    "tb_board_b_pipeline",
    "tb_system_top"
)

if ($Only -ne "") {
    if ($tests -notcontains $Only) {
        Write-Host "ERROR: '$Only' is not in the top-test list." -ForegroundColor Red
        Write-Host "Available: $($tests -join ', ')"
        exit 1
    }
    $tests = @($Only)
}

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

# Cache check -- newest source mtime
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
    (Get-Item $workDir).LastWriteTime = Get-Date
} else {
    Write-Host "Compile cache up-to-date (use -Clean to force rebuild)." -ForegroundColor DarkGray
}
Write-Host ""

$passPatterns = @(
    'ALL TESTS PASSED', 'TEST PASSED', 'PASS \(', 'PASSED:',
    'Simulation completed successfully', 'All checks passed'
)
$failPatterns = @(
    'FATAL_ERROR', 'TESTBENCH FAILED', 'TEST FAILED', 'FAIL \(',
    'Assertion error', 'Fatal:', '\$fatal'
)

$results = [ordered]@{}
foreach ($tb in $tests) {
    Write-Host "------------------------------------------" -ForegroundColor Yellow
    Write-Host " Running $tb (top-level)" -ForegroundColor Yellow
    Write-Host "------------------------------------------" -ForegroundColor Yellow

    $log      = Join-Path $logDir "$tb.log"
    $snapshot = "${tb}_snapshot"
    $snapDir  = Join-Path $workDir $snapshot

    $needElab = (-not (Test-Path $snapDir)) -or
                ($sourceTime -gt (Get-Item $snapDir).LastWriteTime)

    if ($needElab) {
        Write-Host "  xelab... (slow first time -- NN MAC unroll)" -ForegroundColor DarkGray
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

$summaryFile = Join-Path $logDir "SUMMARY_TOP.txt"
$summary = @()
$summary += "==============================================="
$summary += " XSim Top-Level Test Summary"
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
