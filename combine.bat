@echo off

echo ...
echo ...
echo ...
echo ...
echo ...
echo ...
echo cleaning files

cd %1

del /q .\compiled\*.*
del /q .\temp\*.*

:: -----------------------------------
echo copying files to source
:: -----------------------------------

xcopy /s /y /i .\src\cpp .\temp
xcopy /y /i .\lzz.exe .\temp
cd temp

:: -----------------------------------
echo running lzz
:: -----------------------------------

set /a totalhpp=0;
for %%f in (*.hpp) do (
	echo %%f
	lzz -hx e -sx h %%f
	set /a totalhpp+=1
)


:: -----------------------------------
echo copying headers to one file
:: -----------------------------------


copy /b .\*.e .\f00270_headers.h
set /a totale=0;
for %%f in (*.e) do (
	set /a totale+=1
	echo. > %%f
)

:: -----------------------------------
echo tothpp
echo %totalhpp%
echo tote
echo %totale%
:: -----------------------------------


if %totale% == %totalhpp% (
    echo .
) else (
	start "" cmd /c "echo.  Error with LZZ check console output.&echo(&pause"
)

for %%f in (*.h) do (
	echo. >> %%f
)
cd ..

:: -----------------------------------
echo copying files to compiled
:: -----------------------------------

xcopy /s /y /i .\temp\*.e .\compiled
copy /b .\temp\*.h .\compiled\main.cpp
