SUBST w: %HOMEPATH%\Documents\GitHub\Compiler_Exercises
CALL ^
    "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community"^
"\VC\Auxiliary\Build\vcvarsall.bat" x64
SET PATH=w:%path%
W: