@echo off

call ..\Bin\vcvars9.bat
cd .\WaveRace360
call devenv WaveRace.sln /build "Debug|x86" 
start .\bin\x86\Debug\WaveRace360.exe

