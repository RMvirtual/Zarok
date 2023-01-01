@ECHO OFF

: Clear W: drive if in use.
SUBST w: /D

: Create W: drive path for root directory (hardcoded to 3x levels up).
SUBST w: ..\..\..
SET PATH=w:%path%