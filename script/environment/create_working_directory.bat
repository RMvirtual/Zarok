@ECHO OFF

REM Clear W: drive if in use.
IF EXIST w:\ SUBST w: /d

REM Create W: drive path for root directory (hardcoded to 2x levels up).
SUBST w: ..\..

REM Possible issue here with batch script getting confused about
REM W's root directory location.
: SET PATH=w:%path%