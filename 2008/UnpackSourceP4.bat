@echo off

call UnpackSource.bat

p4 flush ...

p4 diff -sd Source\... | p4 -x - delete
p4 diff -sd Data\... | p4 -x - delete
p4 diff -sd Art\... | p4 -x - delete
p4 diff -sd Docs\... | p4 -x - delete
p4 diff -sd Bin\... | p4 -x - delete

p4 diff -se Source\... | p4 -x - edit
p4 diff -se Data\... | p4 -x - edit
p4 diff -se Art\... | p4 -x - edit
p4 diff -se Docs\... | p4 -x - edit
p4 diff -se Bin\... | p4 -x - edit

dir/s/b/a-d Source | p4 -x - add
dir/s/b/a-d Data| p4 -x - add
dir/s/b/a-d Art | p4 -x - add
dir/s/b/a-d Docs | p4 -x - add
dir/s/b/a-d Bin | p4 -x - add
