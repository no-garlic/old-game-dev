@echo off

if exist .\Temp\p4 goto Error

mkdir .\Temp\p4

if exist .\Common move /y .\Common .\Temp\p4
if exist .\Freeworld3D move .\Freeworld3D .\Temp\p4
if exist .\Terrain move .\Terrain .\Temp\p4
if exist .\Waverace360 move .\Waverace360 .\Temp\p4
if exist .\Docs move .\Docs .\Temp\p4
if exist .\Bin move .\Bin .\Temp\p4

Temp\p4\Bin\rar.exe x PackSrc.rar .

@echo Finished
pause
exit 0

:Error
@echo Please clean the temp directory first
pause
