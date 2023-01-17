cd %root_directory%\script\environment\windows\create_working_directory.bat
PUSHD "w:\ide"

"vs_Community.exe" --config "w:\ide\.vsconfig" --passive --wait --force

IF %ERRORLEVEL% NEQ 0 ECHO ("ERROR LEVEL: " %ERRORLEVEL%) ELSE ECHO "OK"
POPD