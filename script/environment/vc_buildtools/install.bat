MD "W:\build"
MD "W:\build\MSVC"
CD\

"w:\lib\msvc\vs_BuildTools.exe" --installPath "w:\build\MSVC" ^
--add Microsoft.VisualStudio.Workload.VCTools ^
--passive --wait

IF %ERRORLEVEL% NEQ 0 ECHO "ERROR LEVEL: " %ERRORLEVEL%