[CmdletBinding()]
param([switch] $install)

& "$PSScriptRoot\devenv\working_directory.ps1"
$TOOLS = "$env:DEVENV\tools\devenv"


if ($install) {& "$TOOLS\download.ps1"}
& "$TOOLS\configure.ps1"
