$BUILD = "$env:DEVENV\build"
$RELEASE = "$BUILD\release"
$TESTS = "$BUILD\tests"
$SRC = "$env:DEVENV\src"
$TEST_SRC = "$env:DEVENV\tests"
$GOOGLETEST = "$env:DEVENV\devenv\GOOGLETEST"


if (-Not (Test-Path $BUILD)) {New-Item $BUILD -ItemType Directory > $null}

# Release.
if (Test-Path $RELEASE) {Remove-Item $RELEASE -Recurse -Force > $null}
New-Item $RELEASE -ItemType Directory > $null

& $env:COMPILE -o "$RELEASE\main.exe" `
    "$SRC\main.cpp" "$SRC\draw.cpp" `
    -mwindows -luser32 -lgdi32

# Tests.
if (Test-Path $TESTS) {Remove-Item $TESTS -Recurse -Force > $null}
New-Item $TESTS -ItemType Directory > $null

$gtestIncludes = "$GOOGLETEST\googletest\include"
$gtestObject = "$GOOGLETEST\gtest-all.o"
$testExecutable = "$TESTS\all_tests.exe"

g++.exe -o $testExecutable `
    -std=c++17 -isystem $gtestIncludes -pthread `
    "$TEST_SRC\test_example.cpp" $gtestObject 
