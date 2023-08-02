Write-Host "Installing development environment."

& "$env:DEVENV\tools\devenv\download_libraries.ps1"
& "$env:DEVENV\tools\devenv\configure_compiler.ps1"
