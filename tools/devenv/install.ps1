$LIBRARY_SCRIPTS = "$env:DEVENV\tools\libraries"
$TOOLS = "$env:DEVENV\tools\devenv"


& "$LIBRARY_SCRIPTS\gcc.ps1"
& "$LIBRARY_SCRIPTS\googletest.ps1"
& "$TOOLS\configure_libraries.ps1"
