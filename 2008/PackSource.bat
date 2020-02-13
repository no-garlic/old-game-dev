@echo off

if exist PackSrc.rar del PackSrc.rar

Bin\Utils\rar.exe a -r PackSrc.rar .\Data
Bin\Utils\rar.exe a -r PackSrc.rar .\Art
Bin\Utils\rar.exe a -r PackSrc.rar .\Bin
Bin\Utils\rar.exe a -r PackSrc.rar .\Docs
Bin\Utils\rar.exe a -r PackSrc.rar .\Source
