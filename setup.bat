@ECHO OFF
SET root_directory=%CD%
ECHO %root_directory%

PUSHD script\environment
CALL setup.bat
POPD
