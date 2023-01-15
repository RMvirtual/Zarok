@ECHO OFF

PUSHD environment
CALL working_directory.bat
CALL vc_buildtools\install.bat
POPD
