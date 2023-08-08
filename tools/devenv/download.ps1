$LIBRARY_SCRIPTS = "$env:DEVENV\tools\libraries"
$TOOLS = "$env:DEVENV\tools\devenv"


& "$LIBRARY_SCRIPTS\download\gcc.ps1"
& "$LIBRARY_SCRIPTS\download\googletest.ps1"
& "$TOOLS\configure_libraries.ps1"
