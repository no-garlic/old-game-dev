@echo off

@echo Deleting Temp Files...
del /s /q .\Temp\*.*
del /s /q .\Logs\*.*
rmdir /s /q .\Temp

@echo Deleting Compiled Files...
del /s /q /ah *.bak
del /s /q .\Lib\*.*
del /s /q .\Compiled\*.*
del /s /q .\Source\Engine\*.ncb
del /s /q /ah .\Source\Engine\*.suo
del /s /q .\Source\Engine\*.xml
del /s /q .\Source\Engine\*.user
del /s /q .\Source\Engine\*.vspscc
del /s /q .\Source\Projects\*.ncb
del /s /q /ah .\Source\Projects\*.suo
del /s /q .\Source\Projects\*.xml
del /s /q .\Source\Projects\*.user
del /s /q .\Source\Projects\*.vspscc
del /s /q .\Source\Tools\*.ncb
del /s /q /ah .\Source\Tools\*.suo
del /s /q .\Source\Tools\*.xml
del /s /q .\Source\Tools\*.user
del /s /q .\Source\Tools\*.vspscc
del /s /q .\Source\Samples\*.ncb
del /s /q /ah .\Source\Samples\*.suo
del /s /q .\Source\Samples\*.xml
del /s /q .\Source\Samples\*.user
del /s /q .\Source\Samples\*.vspscc
rmdir /s /q .\Compiled
rmdir /s /q .\Lib
del /s /q .\Source\XBOX\*.xml
del /s /q .\Source\XBOX\*.ncb
del /s /q /ah .\Source\XBOX\*.suo

@echo Deleting Binary Files
del /q .\Bin\*.xbe
del /q .\Bin\*.map
del /q .\Bin\*.exe
del /q .\Bin\*.ilk
del /q .\Bin\*.pdb

@echo Deleting Generated Data...
del /q .\Data\Meshes\*.*
del /q .\Data\Textures\*.*
del /q .\Data\Textures\Meshes\*.*
del /q .\Data\Textures\Sky\*.*
del /q .\Data\Textures\UI\*.*
rmdir /s /q .\Data\Textures\Sky
rmdir /s /q .\Data\Textures\UI
rmdir /s /q .\Data\Textures

@echo Finished
