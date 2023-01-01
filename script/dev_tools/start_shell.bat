@ECHO OFF

CD environment_setup
CALL set_working_directory.bat

IF "%1%"=="" GOTO START_2019
IF "%1%"=="2019" GOTO START_2019
IF "%1%"=="2022" GOTO START_2022

:START_2019
CALL visual_c_2019.bat
GOTO COMPLETE

:START_2022
ALL visual_c_2022.bat
GOTO COMPLETE

:COMPLETE
w: