<#
.SYNOPSIS
    Creates a correctly numbered ADR stub from the skill's template.

.DESCRIPTION
    Finds the highest existing NNNN- prefix in docs/adr, increments it, and writes
    a new file seeded from template.md. Bundling this script alongside SKILL.md is
    the point of the demo: skills can carry executable resources, instructions
    cannot.

.EXAMPLE
    pwsh .github/skills/adr-writer/scripts/new-adr.ps1 -Title "Use Postgres for orders"
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$Title
)

$ErrorActionPreference = 'Stop'

$skillRoot = Split-Path -Parent $PSScriptRoot
$repoRoot = Split-Path -Parent (Split-Path -Parent (Split-Path -Parent $skillRoot))
$adrDir = Join-Path $repoRoot 'docs\adr'
$template = Join-Path $skillRoot 'template.md'

if (-not (Test-Path $template)) {
    throw "Template not found at $template"
}

New-Item -ItemType Directory -Path $adrDir -Force | Out-Null

$highest = Get-ChildItem -Path $adrDir -Filter '*.md' -ErrorAction SilentlyContinue |
    ForEach-Object { if ($_.Name -match '^(\d{4})-') { [int]$Matches[1] } } |
    Measure-Object -Maximum |
    Select-Object -ExpandProperty Maximum

$next = if ($null -ne $highest) { [int]$highest + 1 } else { 1 }
$number = '{0:D4}' -f [int]$next

$slug = $Title.ToLowerInvariant() -replace '[^a-z0-9]+', '-' -replace '(^-|-$)', ''
$path = Join-Path $adrDir "$number-$slug.md"

(Get-Content $template -Raw).
    Replace('# NNNN. TITLE', "# $number. $Title").
    Replace('YYYY-MM-DD', (Get-Date -Format 'yyyy-MM-dd')) |
    Set-Content -Path $path -Encoding UTF8

Write-Host "Created $path"
