$TARGET = "$env:DEVENV\build"
$RELEASE = "$target\release"
$SRC = "$env:DEVENV\src"


Write-Host "Should build here."

if (-Not (Test-Path $TARGET)) {New-Item $TARGET -ItemType Directory > $null}

if (Test-Path $RELEASE) {Remove-Item $RELEASE -Recurse -Force > $null}
New-Item $RELEASE -ItemType Directory > $null

g++ -o "$RELEASE\main.exe" `
    "$SRC\main.cpp" "$SRC\draw.cpp" `
    -mwindows -luser32 -lgdi32
