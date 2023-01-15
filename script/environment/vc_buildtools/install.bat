PUSHD w:\lib\msvc

vs_BuildTools.exe --installPath w:\build\msvc ^
 --add --includeOptional Microsoft.VisualStudio.Workload.VCTools  ^
 --norestart --passive --wait

POPD