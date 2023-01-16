MD "W:\build"
MD "W:\build\MSVC_2"
REM PUSHD "W:\lib\msvc"

CD\

"w:\lib\msvc\vs_BuildTools.exe" --installPath "w:\build\MSVC_2" ^
--add Microsoft.VisualStudio.Workload.VCTools ^
--passive --wait

IF %ERRORLEVEL% NEQ 0 ECHO "ERROR LEVEL: " %ERRORLEVEL%
POPD