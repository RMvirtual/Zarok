[CmdletBinding()]
param([switch] $install, [switch] $configure)

& "$PSScriptRoot\devenv\working_directory.ps1"

if ($install) {& "$env:DEVENV\tools\devenv\install.ps1"}
elseif ($configure) {& "$env:DEVENV\tools\devenv\configure.ps1"}

