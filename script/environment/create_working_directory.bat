@ECHO OFF

: Clear W: drive if in use.
IF EXIST w:\ SUBST w: /D

: Create W: drive path for root directory (hardcoded to 2x levels up).
SUBST w: ..\..
SET PATH=w:%path%