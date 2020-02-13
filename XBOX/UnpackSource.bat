@echo off

if exist .\Temp\p4 rmdir /s /q .\Temp\p4
if not exist .\Temp\p4 mkdir .\Temp\p4

if exist .\Source move /y .\Source .\Temp\p4
if exist .\Data move .\Data .\Temp\p4
if exist .\Art move .\Art .\Temp\p4
if exist .\Docs move .\Docs .\Temp\p4
if exist .\Bin move .\Bin .\Temp\p4

Temp\p4\Bin\Utils\rar.exe x PackSrc.rar .
