@echo off

: Create W: drive path for working git/dev directory.
SUBST w: %HOMEPATH%\Documents\GitHub\Compiler_Exercises
SET PATH=w:%path%
W:

: Start MSVC dev environment for compiler command.
CALL ^
    "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community"^
"\VC\Auxiliary\Build\vcvarsall.bat" x64
