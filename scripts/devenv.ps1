[CmdletBinding()]
param([switch] $force)


if ($force) {& "$PSScriptRoot\..\tools\devenv.ps1" -install}
else {& "$PSScriptRoot\..\tools\devenv.ps1" -configure}
