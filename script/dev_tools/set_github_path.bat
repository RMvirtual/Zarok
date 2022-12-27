@echo off

: Create W: drive path for working git/dev directory.
SUBST w: %HOMEPATH%\Documents\GitHub\Compiler_Exercises
SET PATH=w:%path%
W:
