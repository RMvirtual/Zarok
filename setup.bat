CLS
@ECHO OFF

CALL script\environment\windows\set_working_directory.bat %CD%
CD /d w:\
CALL "w:\script\environment\initialise.bat"
