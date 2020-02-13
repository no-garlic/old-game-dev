@echo off

@echo.
@echo ===========================================================================
call "C:/Program Files/Microsoft Visual Studio 8/VC/vcvarsall.bat"
@echo ===========================================================================

@echo.
@echo ===========================================================================
@echo Creating Directories
@echo ===========================================================================
if not exist .\Lib mkdir .\Lib
if not exist .\Data\Meshes mkdir .\Data\Meshes
if not exist .\Data\Textures mkdir .\Data\Textures
if not exist .\Data\Textures\Meshes mkdir .\Data\Textures\Meshes
if not exist .\Data\Textures\UI mkdir .\Data\Textures\UI
if not exist .\Data\Textures\Icons mkdir .\Data\Textures\Icons
if not exist .\Data\Textures\Sky mkdir .\Data\Textures\Sky
if not exist .\Logs mkdir .\Logs
if not exist .\Logs\MeshConvert mkdir .\Logs\MeshConvert
if not exist .\Temp mkdir .\Temp

@echo.
@echo ===========================================================================
@echo Building WxWindows (Debug)
@echo ===========================================================================
pushd .\Source\External\wxWidgets-2.6.3\build\msw
call devenv wx.sln /build "Debug|Win32" 
popd

@echo.
@echo ===========================================================================
@echo Building WxPropertyGrid (Debug)
@echo ===========================================================================
pushd .\Source\External\wxPropGrid-1.2.8
call devenv propgrid.sln /build "Debug|Win32" 
popd

@echo.
@echo ===========================================================================
@echo Building Tools (Debug)
@echo ===========================================================================
pushd .\Source\Tools
call devenv Tools.sln /build "Debug|Win32" 
popd

@echo.
@echo ===========================================================================
@echo Building Level Editor (Debug)
@echo ===========================================================================
pushd .\Source\Projects\LevelEditor
call devenv LevelEditor.sln /build "Debug|Win32" 
popd

@echo.
@echo ===========================================================================
@echo Building ActionGame (Debug)
@echo ===========================================================================
pushd .\Source\Projects\ActionGame
call devenv ActionGame.sln /build "Debug|Win32" 
popd

@echo.
@echo ===========================================================================
@echo Converting X files to Meshes
@echo ===========================================================================
del /q .\Logs\MeshConvert\*.*
dir /b .\Art\Meshes\*.x > .\Temp\MeshConvert.txt
for /f %%i in (.\Temp\MeshConvert.txt) do (
  @echo Processing: %%i
  .\Bin\Tools_d.exe MeshConvert %%i > .\Logs\MeshConvert\%%i.log
  .\Bin\Utils\grep.exe -i "ERROR" .\Logs\MeshConvert\%%i.log
)

@echo.
@echo ===========================================================================
@echo Copying Icons
@echo ===========================================================================
copy .\Art\Icons\*.* .\Data\Textures\Icons

@echo.
@echo ===========================================================================
@echo Copying UI Textures
@echo ===========================================================================
copy .\Art\UI\*.* .\Data\Textures\UI

@echo.
@echo ===========================================================================
@echo Copying Sky Textures
@echo ===========================================================================
copy .\Art\Sky\*.* .\Data\Textures\Sky

@echo.
@echo ===========================================================================
@echo Finished
@echo ===========================================================================

pause