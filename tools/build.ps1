$TARGET = "$env:DEVENV\build"
$RELEASE = "$TARGET\release"
$SRC = "$env:DEVENV\src"
$TESTS = "$TARGET\tests"

Write-Host "Should build here."

if (-Not (Test-Path $TARGET)) {New-Item $TARGET -ItemType Directory > $null}

# Release.
if (Test-Path $RELEASE) {Remove-Item $RELEASE -Recurse -Force > $null}
New-Item $RELEASE -ItemType Directory > $null

& $env:COMPILE -o "$RELEASE\main.exe" `
    "$SRC\main.cpp" "$SRC\draw.cpp" `
    -mwindows -luser32 -lgdi32

# Tests.
if (Test-Path $TESTS) {Remove-Item $TESTS -Recurse -Force > $null}
New-Item $TESTS -ItemType Directory > $null

$googletest = "$env:DEVENV\devenv\googletest"

g++.exe -std=c++17 -isystem "$googletest\googletest\include" -pthread `
    "$env:DEVENV\tests\test_example.cpp" "$googletest\gtest-all.o" `
    -o "$TESTS\my_tests"
