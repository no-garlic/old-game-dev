@echo off

if exist Temp del /s /q Temp\*.*
if exist Temp rmdir /s /q Temp

del /s /q Common\obj\*.*
del /s /q Common\bin\*.*
rmdir /s /q Common\obj
rmdir /s /q Common\bin\x86
rmdir /s /q Common\bin

del /s /q Freeworld3D\obj\*.*
del /s /q Freeworld3D\bin\*.*
rmdir /s /q Freeworld3D\obj
rmdir /s /q Freeworld3D\bin\x86
rmdir /s /q Freeworld3D\bin

del /s /q Terrain\obj\*.*
del /s /q Terrain\bin\*.*
rmdir /s /q Terrain\obj
rmdir /s /q Terrain\bin\x86
rmdir /s /q Terrain\bin

del /s /q WaveRace360\obj\*.*
del /s /q WaveRace360\bin\*.*
rmdir /s /q WaveRace360\obj
rmdir /s /q WaveRace360\bin\x86
rmdir /s /q WaveRace360\bin

del /s /q WaveRace360\Content\obj\*.*
del /s /q WaveRace360\Content\bin\*.*
rmdir /s /q WaveRace360\Content\obj
rmdir /s /q WaveRace360\bin\Content\x86
rmdir /s /q WaveRace360\Content\bin

del /ah WaveRace360\WaveRace360.suo
del /ah WaveRace360\WaveRace360.ncb
del WaveRace360\connectionmap.xml
del WaveRace360\connections.xml
del WaveRace360\settings.xml

@echo Finished
pause
