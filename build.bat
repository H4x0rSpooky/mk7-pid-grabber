@echo off
make re PLGNAME=mk7-pid-grabber
del /f /q .\debug\*
move /y .\build\*.lst .\debug\
move /y *.elf .\debug\
pause