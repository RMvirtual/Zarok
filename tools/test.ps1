$TARGET = "$env:DEVENV\build\tests"


Push-Location $TARGET
./my_tests.exe
Pop-Location
