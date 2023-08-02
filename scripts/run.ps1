if (-Not $env:DEVENV) {& "$PSScriptRoot\devenv.ps1"}
$tools = "$env:DEVENV\tools"

Clear-Host;
Write-Host "Running application."

& "$tools\run.ps1"
