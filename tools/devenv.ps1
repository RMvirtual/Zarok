[CmdletBinding()]
param([switch] $install, [switch] $configure)

& "$PSScriptRoot\devenv\working_directory.ps1"
$TOOLS = "$env:DEVENV\tools\devenv"


if ($install) {& "$TOOLS\install.ps1"}
elseif ($configure) {& "$TOOLS\configure.ps1"}
