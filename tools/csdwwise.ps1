param(
    [Parameter(Mandatory=$true, Position=0)]
    [string] $CsdArg,
    [switch] $LaunchWwise,
    [string] $WwiseExe  # optional, e.g. "C:\Program Files (x86)\Audiokinetic\Wwise 2024.1.5\Authoring\x64\Release\bin\Wwise.exe"
)

$ErrorActionPreference = "Stop"

function Resolve-RepoRoot {
    # repo root assumed to be the parent of this script's folder if script is under <repo>\tools\
    $scriptDir = Split-Path -Parent $PSCommandPath
    $repo = Split-Path -Parent $scriptDir
    if (-not (Test-Path $repo)) { throw "Cannot resolve repo root from script path." }
    return $repo
}

function Resolve-CsdPath([string] $arg) {
    if (Test-Path -LiteralPath $arg) {
        return (Resolve-Path -LiteralPath $arg).Path
    }

    # If only a filename was provided, look in <repo>\csd\<filename>
    if ($arg -notmatch '\.csd$') {
        throw "Input must be a .csd file. Received: $arg"
    }
    $repo = Resolve-RepoRoot
    $defaultDir = Join-Path $repo 'csd'
    $candidate = Join-Path $defaultDir $arg
    if (-not (Test-Path -LiteralPath $candidate)) {
        throw "Could not find '$arg' in default folder: $defaultDir"
    }
    return (Resolve-Path -LiteralPath $candidate).Path
}

function Write-Manifest([string] $absPath) {
    $appDir = Join-Path $env:LOCALAPPDATA 'csdwwise'
    if (-not (Test-Path $appDir)) { New-Item -ItemType Directory -Path $appDir | Out-Null }
    # two tiny files: one json (nice for tools), one txt (fast to read in C++)
    $json = @{ csdPath = $absPath } | ConvertTo-Json -Compress
    Set-Content -Path (Join-Path $appDir 'current.json') -Value $json -Encoding UTF8 -NoNewline
    Set-Content -Path (Join-Path $appDir 'current.txt')  -Value $absPath -Encoding UTF8 -NoNewline
}

function Set-UserEnv([string] $absPath) {
    # Persist user-scoped env var so Wwise can see it on next launch
    [Environment]::SetEnvironmentVariable('CSDWWISE_CSD_PATH', $absPath, 'User')
}

# ---- main
$abs = Resolve-CsdPath $CsdArg
Write-Manifest $abs
Set-UserEnv   $abs

Write-Host "csdwwise: Selected" $abs
Write-Host "Manifest: $env:LOCALAPPDATA\csdwwise\current.{json,txt}"
Write-Host "User env: CSDWWISE_CSD_PATH set (effective on next process launch)."

if ($LaunchWwise) {
    if ([string]::IsNullOrWhiteSpace($WwiseExe)) {
        throw "Please pass -WwiseExe 'C:\path\to\Wwise.exe' or omit -LaunchWwise."
    }
    Start-Process -FilePath $WwiseExe
    Write-Host "Launching Wwise..."
}
