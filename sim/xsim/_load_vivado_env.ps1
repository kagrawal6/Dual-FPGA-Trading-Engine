# =============================================================================
# Helper: load Vivado tools (xvlog/xelab/xsim) into the current PowerShell
# session. Dot-sourced by run_board_b.ps1 / run_top.ps1.
#
# Strategy:
#   1. If xvlog is already on PATH, do nothing.
#   2. Otherwise, search common install roots for settings64.bat, run it via
#      cmd, and copy the resulting environment back into PowerShell.
#
# Searched roots (in order):
#   $env:VIVADO_ROOT  (override)
#   C:\AMDDesignTools\<ver>\Vivado
#   C:\Xilinx\Vivado\<ver>
#   C:\AMD\Vivado\<ver>
#   D:\AMDDesignTools\<ver>\Vivado
#   D:\Xilinx\Vivado\<ver>
# =============================================================================

function Import-VivadoEnv {
    if (Get-Command "xvlog.bat" -ErrorAction SilentlyContinue) { return $true }
    if (Get-Command "xvlog"     -ErrorAction SilentlyContinue) { return $true }

    $candidates = @()
    if ($env:VIVADO_ROOT -and (Test-Path $env:VIVADO_ROOT)) {
        $candidates += $env:VIVADO_ROOT
    }
    foreach ($root in @("C:\AMDDesignTools","C:\Xilinx\Vivado","C:\AMD\Vivado",
                        "D:\AMDDesignTools","D:\Xilinx\Vivado","D:\AMD\Vivado")) {
        if (-not (Test-Path $root)) { continue }
        $vers = Get-ChildItem $root -Directory -ErrorAction SilentlyContinue |
                Where-Object { $_.Name -match '^\d{4}\.\d+$' } |
                Sort-Object Name -Descending
        foreach ($v in $vers) {
            $vivado = Join-Path $v.FullName "Vivado"
            if (Test-Path (Join-Path $vivado "settings64.bat")) { $candidates += $vivado; continue }
            if (Test-Path (Join-Path $v.FullName "settings64.bat")) { $candidates += $v.FullName }
        }
    }

    if ($candidates.Count -eq 0) {
        Write-Host "ERROR: Could not auto-locate Vivado." -ForegroundColor Red
        Write-Host "  Set `$env:VIVADO_ROOT to the folder containing settings64.bat, e.g.:" -ForegroundColor Yellow
        Write-Host "    `$env:VIVADO_ROOT = 'C:\AMDDesignTools\2025.2\Vivado'" -ForegroundColor Yellow
        return $false
    }

    $vivadoDir   = $candidates[0]
    $settingsBat = Join-Path $vivadoDir "settings64.bat"
    Write-Host "Sourcing Vivado env from: $settingsBat" -ForegroundColor Cyan

    # Run the bat in a cmd.exe subshell, dump the resulting env, and import
    # any Xilinx/Vivado-related vars (and the updated PATH) back into PS.
    $envOutput = cmd /c "`"$settingsBat`" >NUL 2>&1 && set" 2>$null
    foreach ($line in $envOutput) {
        if ($line -match '^([^=]+)=(.*)$') {
            $name = $matches[1]
            $val  = $matches[2]
            # Always update PATH; only forward Xilinx/AMD-specific vars otherwise
            if ($name -eq 'Path' -or $name -eq 'PATH' -or
                $name -match '^(XIL|XILINX|VIVADO|MYVIVADO|RDI_|HDI_|HD_|XILINX_VIVADO|RDIDATADIR)') {
                [Environment]::SetEnvironmentVariable($name, $val, 'Process')
            }
        }
    }

    if (Get-Command "xvlog.bat" -ErrorAction SilentlyContinue) { return $true }
    if (Get-Command "xvlog"     -ErrorAction SilentlyContinue) { return $true }

    Write-Host "ERROR: Sourced settings64.bat but xvlog is still not on PATH." -ForegroundColor Red
    return $false
}
