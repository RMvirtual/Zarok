$TARGET = "$env:DEVENV\build"
$RELEASE = "$target\release"
$SRC = "$env:DEVENV\src"


Write-Host "Should build here."

if (-Not (Test-Path $TARGET)) {New-Item $TARGET -ItemType Directory > $null}

if (Test-Path $RELEASE) {Remove-Item $RELEASE -Recurse -Force > $null}
New-Item $RELEASE -ItemType Directory > $null

g++ "$SRC\main.cpp" -o "$RELEASE\main.exe" -mwindows -luser32 -lgdi32
