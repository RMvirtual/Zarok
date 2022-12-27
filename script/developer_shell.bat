@echo off
CALL dev_tools\set_working_directory.bat

PUSHD w:\script\dev_tools

if %1%==2019 START visual_c_2019.bat
if %1%==2022 START visual_c_2022_build_tools.bat

POPD