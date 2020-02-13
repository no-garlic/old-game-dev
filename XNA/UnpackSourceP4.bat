@echo off

call UnpackSource.bat

p4 flush ...

p4 diff -sd Bin\... | p4 -x - delete
p4 diff -sd Art\... | p4 -x - delete
p4 diff -sd Common\... | p4 -x - delete
p4 diff -sd Docs\... | p4 -x - delete
p4 diff -sd Terrain\... | p4 -x - delete
p4 diff -sd Waverace360\... | p4 -x - delete

p4 diff -se Bin\... | p4 -x - edit
p4 diff -se Art\... | p4 -x - edit
p4 diff -se Common\... | p4 -x - edit
p4 diff -se Docs\... | p4 -x - edit
p4 diff -se Terrain\... | p4 -x - edit
p4 diff -se Waverace360\... | p4 -x - edit

dir/s/b/a-d Bin | p4 -x - add
dir/s/b/a-d Art | p4 -x - add
dir/s/b/a-d Common| p4 -x - add
dir/s/b/a-d Docs | p4 -x - add
dir/s/b/a-d Terrain | p4 -x - add
dir/s/b/a-d Waverace360 | p4 -x - add

@echo Finished
pause
