@ECHO OFF
CLS
IF NOT EXIST w:\build MKDIR w:\build
PUSHD w:\build
: -Zi flag for debug info.
: /EHsc added to shut up compiler warnings about not specifying
: exception handling, but need to look up if correct one.
cl -Zi ^
    /I"w:\src\main" ^
    w:\src\main\app\demo\oop_main_menu.cpp ^
    w:\src\main\windows\demo\gui\oop\main_window.cpp ^
    user32.lib gdi32.lib /EHsc
POPD
