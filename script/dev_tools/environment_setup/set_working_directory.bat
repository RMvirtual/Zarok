@ECHO OFF

: Clear W: drive if in use.
SUBST w: /D 

: Create W: drive path for working git/dev directory.
SUBST w: %HOMEPATH%\Documents\GitHub\Fortesque-Handmade-Edition
SET PATH=w:%path%