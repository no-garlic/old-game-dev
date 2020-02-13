@echo off

if exist PackAll.rar del PackAll.rar

Bin\Utils\rar.exe a -r PackAll.rar .\Data
Bin\Utils\rar.exe a -r PackAll.rar .\Art
Bin\Utils\rar.exe a -r PackAll.rar .\Bin
Bin\Utils\rar.exe a -r PackAll.rar .\Docs
Bin\Utils\rar.exe a -r PackAll.rar .\Source
Bin\Utils\rar.exe a    PackAll.rar .\*.bat
