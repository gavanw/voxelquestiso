ECHO Debug Cleanup Started

:: DONT USE THIS, INSTEAD JUST BUILD AND MANUALLY START DEBUGGER

cd C:\wamp\www\voxelquestiso
:: SET name=%random%
:: ECHO "%name%"  > .\compiled\main.cpp

del /q .\bin\*.*
xcopy /s /y .\debugdlls .\bin
xcopy /s /y .\x64\Debug .\bin
del /q .\x64\Debug\*.*
del /q .\x64\Release\*.*
del /q .\VoxelQuest\x64\Debug\*.*
del /q .\VoxelQuest\x64\Release\*.*

ECHO running EXE
cd C:\wamp\www\voxelquestiso\bin
VoxelQuest.exe
