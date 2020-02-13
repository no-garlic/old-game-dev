@echo off
for %%a in (*.asb) do attrib -r %%a
for %%a in (*.ase) do ase2asb.exe %%a

cd SkyBox
for %%a in (*.asb) do attrib -r %%a
for %%a in (*.ase) do ..\ase2asb.exe %%a
cd ..

cd Vessels
for %%a in (*.asb) do attrib -r %%a
for %%a in (*.ase) do ..\ase2asb.exe %%a
cd ..

cd Wave
for %%a in (*.asb) do attrib -r %%a
for %%a in (*.ase) do ..\ase2asb.exe %%a
cd ..

cd Buoys
for %%a in (*.asb) do attrib -r %%a
for %%a in (*.ase) do ..\ase2asb.exe %%a
cd ..

cd Terrain
for %%a in (*.asb) do attrib -r %%a
for %%a in (*.ase) do ..\ase2asb.exe %%a
cd ..

@echo Done!!!
pause