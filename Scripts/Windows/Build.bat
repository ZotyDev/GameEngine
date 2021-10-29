set MSBuildDirectory=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin
cd ..\..
"%MSBuildDirectory%\MSBuild.exe" /p:Platform=x64 /p:Configuration=Release /p:DisableFastUpToDateCheck=1 -m GameEngine.sln
PAUSE