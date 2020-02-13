@echo off

if exist Temp del /s /q Temp\*.*
if exist Temp rmdir /s /q Temp


del /ah /s /q *.suo
del /s /q *.user
del /s /q *.cachefile

del /s /q ContentPipeline\obj\*.*
del /s /q ContentPipeline\bin\*.*
rmdir /s /q ContentPipeline\obj
rmdir /s /q ContentPipeline\bin

del /s /q ContentReader\obj\*.*
del /s /q ContentReader\bin\*.*
rmdir /s /q ContentReader\obj
rmdir /s /q ContentReader\bin


del /s /q WaveRace360\obj\*.*
del /s /q WaveRace360\bin\*.*
rmdir /s /q WaveRace360\obj
rmdir /s /q WaveRace360\bin

del /s /q WaveRace360\Content\obj\*.*
del /s /q WaveRace360\Content\bin\*.*
rmdir /s /q WaveRace360\Content\obj
rmdir /s /q WaveRace360\Content\bin

del /ah WaveRace360\WaveRace360.suo
del /ah WaveRace360\WaveRace360.ncb
del WaveRace360\connectionmap.xml
del WaveRace360\connections.xml
del WaveRace360\settings.xml



del /s /q Samples\JigLibXTest\JigLibGame\obj\*.*
del /s /q Samples\JigLibXTest\JigLibGame\bin\*.*
rmdir /s /q Samples\JigLibXTest\JigLibGame\obj
rmdir /s /q Samples\JigLibXTest\JigLibGame\bin

del /s /q Samples\JigLibXTest\JigLibGame\Content\obj\*.*
del /s /q Samples\JigLibXTest\JigLibGame\Content\bin\*.*
rmdir /s /q Samples\JigLibXTest\JigLibGame\Content\obj
rmdir /s /q Samples\JigLibXTest\JigLibGame\bin\Content\x86
rmdir /s /q Samples\JigLibXTest\JigLibGame\Content\bin


del /s /q Samples\JigLibXTest\HeightmapProcessor\HeightmapProcessor\obj\*.*
del /s /q Samples\JigLibXTest\HeightmapProcessor\HeightmapProcessor\bin\*.*
rmdir /s /q Samples\JigLibXTest\HeightmapProcessor\HeightmapProcessor\obj
rmdir /s /q Samples\JigLibXTest\HeightmapProcessor\HeightmapProcessor\bin


del /s /q Samples\AnimationTest\obj\*.*
del /s /q Samples\AnimationTest\bin\*.*
rmdir /s /q Samples\AnimationTest\obj
rmdir /s /q Samples\AnimationTest\bin

del /s /q Samples\AnimationTest\Content\obj\*.*
del /s /q Samples\AnimationTest\Content\bin\*.*
rmdir /s /q Samples\AnimationTest\Content\obj
rmdir /s /q Samples\AnimationTest\bin\Content\x86
rmdir /s /q Samples\AnimationTest\Content\bin

del /ah Samples\AnimationTest\AnimationTest.suo
del /ah Samples\AnimationTest\AnimationTest.ncb
del Samples\AnimationTest\connectionmap.xml
del Samples\AnimationTest\connections.xml
del Samples\AnimationTest\settings.xml





@echo Finished

pause
