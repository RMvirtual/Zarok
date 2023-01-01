@ECHO OFF
CLS
MKDIR w:\build
PUSHD w:\build
: -Zi flag for debug info.
: Return to handmade hero 001 for debugger setup info.
: /EHsc added to shut up compiler warnings about not specifying
: exception handling, but need to look up if correct one.
cl -Zi w:\src\main\simple_example.cpp /EHsc 
POPD
