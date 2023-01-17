@ECHO OFF
IF NOT EXIST w:\ CALL script\environment\windows\set_working_directory.bat %CD%

START w:\script\environment\vs_community\compiler_shell.bat
