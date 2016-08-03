ECHO Cleanup Started

cd C:\wamp\www\voxelquestiso
:: SET name=%random%
:: ECHO "%name%"  > .\compiled\main.cpp

del /q .\bin\*.*
xcopy /s /y .\dlls .\bin
xcopy /s /y .\x64\Release .\bin

del /q .\x64\Debug\*.*
del /q .\x64\Release\*.*
del /q .\VoxelQuest\x64\Debug\*.*
del /q .\VoxelQuest\x64\Release\*.*

ECHO running EXE
cd C:\wamp\www\voxelquestiso\bin
VoxelQuest.exe
