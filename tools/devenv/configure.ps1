$LIBRARY_SCRIPTS = "$env:DEVENV\tools\libraries"
$TARGET = "$env:DEVENV\devenv"
$TOOLS = "$env:DEVENV\tools\devenv"


if (-Not (Test-Path $TARGET)) {& "$TOOLS\install.ps1"}
& "$LIBRARY_SCRIPTS\configure.ps1"
