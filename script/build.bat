@echo off
mkdir ..\build
pushd ..\build
: -Zi flag for debug info.
: Return to handmade hero 001 for debugger setup info.
cl -Zi w:\src\main\simple_example.cpp
popd
