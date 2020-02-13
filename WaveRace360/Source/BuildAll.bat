@echo off

@echo.
@echo ===========================================================================
rem call "C:/Program Files/Microsoft Visual Studio 8/VC/vcvarsall.bat"
rem call ""C:\Program Files\Microsoft XNA\XNA Game Studio\v3.0\Tools\XnaGseVars.cmd" "C:\WINDOWS\Microsoft.NET\Framework\v3.5" "C:\WINDOWS\Microsoft.NET\Framework\v2.0.50727""
call ..\Bin\vcvars9.bat
@echo ===========================================================================

@echo.
@echo ===========================================================================
@echo Building Debug WaveRace360
@echo ===========================================================================
pushd .\WaveRace360
call devenv WaveRace.sln /build "Debug|x86" 
rem call vcsexpress WaveRace360.sln /build "Debug|x86" 
popd

@echo.
@echo ===========================================================================
@echo Finished
@echo ===========================================================================

pause