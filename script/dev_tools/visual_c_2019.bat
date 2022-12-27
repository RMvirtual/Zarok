@echo off

CALL set_github_path.bat

: Start MSVC dev environment for compiler command.
CALL ^
    "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community"^
"\VC\Auxiliary\Build\vcvarsall.bat" x64
