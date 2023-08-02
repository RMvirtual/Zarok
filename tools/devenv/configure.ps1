Write-Host "Configuring development environment."

if (-Not (Test-Path "$env:DEVENV\devenv")) {
    & "$env:DEVENV\tools\devenv\install.ps1"
}
