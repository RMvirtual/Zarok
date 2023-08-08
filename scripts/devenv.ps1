[CmdletBinding()]
param([switch] $reinstall)


Clear-Host; Write-Host "Setting up development environment."

if ($reinstall) {& "$PSScriptRoot\..\tools\devenv.ps1" -install}
else {& "$PSScriptRoot\..\tools\devenv.ps1" -configure}
