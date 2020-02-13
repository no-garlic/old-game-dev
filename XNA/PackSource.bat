@echo off

if exist PackSrc.rar del PackSrc.rar

Bin\rar.exe a -r PackSrc.rar .\Docs
Bin\rar.exe a -r PackSrc.rar .\Bin
Bin\rar.exe a -r PackSrc.rar .\Common
Bin\rar.exe a -r PackSrc.rar .\Freeworld3D
Bin\rar.exe a -r PackSrc.rar .\Terrain
Bin\rar.exe a -r PackSrc.rar .\Waverace360

@echo Finished
pause
