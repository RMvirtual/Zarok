@echo off

CALL set_working_directory.bat

: Start MSVC dev environment for compiler command.
CALL ^
    "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools"^
"\VC\Auxiliary\Build\vcvarsall.bat" x64
