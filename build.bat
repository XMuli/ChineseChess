@echo off

setlocal enabledelayedexpansion

:: Define the new path you want to prepend
set new_path=C:\Qt\5.15.2\msvc2019_64\bin

:: Check if the path already exists in PATH
echo !PATH! | findstr /C:"%new_path%" > nul
if !errorlevel! == 1 (
    :: If the path doesn't exist, prepend it to PATH
    set "PATH=%new_path%;!PATH!"
    echo Updated PATH: !PATH!
) else (
    echo PATH already contains %new_path%
)

::delete build dir
if "%1"=="delete" goto _DEL

if not exist build md build

cd build
cmake -G "Visual Studio 17 2022" -A x64 ..
goto _END

:_DEL
rd build/s/q
goto _END

:_END