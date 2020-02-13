@echo off

@echo Deleting Temp Files...
del /s /q .\Temp\*.*
del /s /q .\Logs\*.*
rmdir /s /q .\Temp

@echo Deleting Compiled Files...
del /s /q .\*.bak
del /s /q .\Lib\*.*
del /s /q .\Compiled\*.*

del /s /q .\Source\*.ncb
del /s /q /ah .\Source\*.suo
del /s /q .\Source\*.xml
del /s /q .\Source\*.user
del /s /q .\Source\*.bak

del /s /q .\Source\*.vspscc
del /s /q .\Source\*.vssscc
del /s /q .\Source\*.scc

rmdir /s /q .\Source\External\wxPropGrid-1.2.8\vc_msw
rmdir /s /q .\Source\External\wxPropGrid-1.2.8\vc_mswd
rmdir /s /q .\Source\External\wxPropGrid-1.2.8\lib
rmdir /s /q .\Source\External\wxWidgets-2.6.3\build\msw\vc_msw
rmdir /s /q .\Source\External\wxWidgets-2.6.3\build\msw\vc_mswd
rmdir /s /q .\Source\External\wxWidgets-2.6.3\lib

rmdir /s /q .\Compiled
rmdir /s /q .\Lib

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
del /q .\Data\Textures\Icons\*.*
rmdir /s /q .\Data\Textures\Sky
rmdir /s /q .\Data\Textures\UI
rmdir /s /q .\Data\Textures\Icons
rmdir /s /q .\Data\Textures

@echo Finished
