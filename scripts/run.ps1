if (-Not $env:DEVENV) {& "$PSScriptRoot\devenv.ps1"}
$TOOLS = "$env:DEVENV\tools"


Clear-Host; Write-Host "Running application."
& "$TOOLS\run.ps1"
