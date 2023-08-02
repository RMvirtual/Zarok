Write-Host "Configuring compiler."

$compiler = "$env:DEVENV\devenv\mingw64\bin"
$env:Path += ";$compiler"
