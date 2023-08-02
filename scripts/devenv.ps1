[CmdletBinding()]
param([switch] $force)

Clear-Host; Write-Host "Setting up development environment."

if ($force) {& "$PSScriptRoot\..\tools\devenv.ps1" -install}
else {& "$PSScriptRoot\..\tools\devenv.ps1" -configure}
