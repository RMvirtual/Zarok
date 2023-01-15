@ECHO OFF
CLS
IF NOT EXIST w:\build MKDIR w:\build
PUSHD w:\build
: -Zi flag for debug info.
: /EHsc added to shut up compiler warnings about not specifying
: exception handling, but need to look up if correct one.
cl -Zi ^
    /I"w:\src\main" ^
    w:\src\main\windows\demo\direct2D\clock\main.cpp ^
    user32.lib gdi32.lib /EHsc
POPD
