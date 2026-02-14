@echo off
setlocal enabledelayedexpansion

:: ============================================================
:: ChineseChess Multi-Config Build ^& Package Script
:: Usage:
::   build.bat          - Build all configs + package
::   build.bat pack     - Package only (skip build)
::   build.bat delete   - Clean all build directories
:: ============================================================

set APP_NAME=ChineseChess
set "ISCC_PATH=C:\Program Files (x86)\Inno Setup 6\ISCC.exe"
set "SEVENZIP=C:\Program Files\7-Zip\7z.exe"
set "VCVARSALL=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"

:: ============================================================
:: Version override: set a value here to skip CMakeLists.txt parsing
::   e.g.  set "VERSION_OVERRIDE=7.3.0"
:: Leave empty to auto-detect from CMakeLists.txt
:: ============================================================
set "VERSION_OVERRIDE=7.4.0"

if defined VERSION_OVERRIDE (
    for /f "tokens=1,2,3 delims=." %%a in ("!VERSION_OVERRIDE!") do (
        set VER_MAJOR=%%a
        set VER_MINOR=%%b
        set VER_PATCH=%%c
    )
) else (
    :: Parse version from CMakeLists.txt
    for /f %%v in ('powershell -NoProfile -Command "(Select-String -Path CMakeLists.txt -Pattern 'set\(project_version_major (\d+)\)').Matches[0].Groups[1].Value"') do set VER_MAJOR=%%v
    for /f %%v in ('powershell -NoProfile -Command "(Select-String -Path CMakeLists.txt -Pattern 'set\(project_version_minor (\d+)\)').Matches[0].Groups[1].Value"') do set VER_MINOR=%%v
    for /f %%v in ('powershell -NoProfile -Command "(Select-String -Path CMakeLists.txt -Pattern 'set\(project_version_patch (\d+)\)').Matches[0].Groups[1].Value"') do set VER_PATCH=%%v
)
set VERSION=!VER_MAJOR!.!VER_MINOR!
set VERSION_FULL=!VER_MAJOR!.!VER_MINOR!.!VER_PATCH!

echo ============================================================
echo  %APP_NAME% v!VERSION_FULL! Multi-Config Build
echo ============================================================

:: Handle "delete" command
if "%1"=="delete" (
    echo [Clean] Removing all build directories...
    for %%d in (build_qt6_msvc_x64 build_qt6_mingw_x64 build_qt5_msvc_x64 build_qt5_msvc_x86) do (
        if exist %%d rd /s /q %%d
    )
    for %%d in (bin_qt6_msvc_x64 bin_qt6_mingw_x64 bin_qt5_msvc_x64 bin_qt5_msvc_x86) do (
        if exist %%d rd /s /q %%d
    )
    echo Done.
    goto _END
)

if not exist release md release

:: Skip build if "pack" command
if "%1"=="pack" goto _PACK_ALL

:: ============================================================
:: Config 1: Qt6 + MSVC2022 + x64
:: ============================================================
echo.
echo [Config 1/4] Qt6 + MSVC2022 + x64
set "QT_PREFIX=C:\Qt\6.8.3\msvc2022_64"
set "BUILD_DIR=build_qt6_msvc_x64"
set "BIN_DIR=bin_qt6_msvc_x64"
set "CMAKE_GEN=Visual Studio 17 2022"
set "CMAKE_ARCH=x64"
set "VCARCH=x64"
call :BUILD_MSVC
if !errorlevel! neq 0 echo WARNING: Config 1 build failed, skipping...

:: ============================================================
:: Config 2: Qt6 + MinGW13 + x64
:: ============================================================
echo.
echo [Config 2/4] Qt6 + MinGW13 + x64
set "QT_PREFIX=C:\Qt\6.8.3\mingw_64"
set "MINGW_PATH=C:\Qt\Tools\mingw1310_64\bin"
set "BUILD_DIR=build_qt6_mingw_x64"
set "BIN_DIR=bin_qt6_mingw_x64"
call :BUILD_MINGW
if !errorlevel! neq 0 echo WARNING: Config 2 build failed, skipping...

:: ============================================================
:: Config 3: Qt5 + MSVC2019(via VS2022) + x64
:: ============================================================
echo.
echo [Config 3/4] Qt5 + MSVC + x64
set "QT_PREFIX=C:\Qt\5.15.2\msvc2019_64"
set "BUILD_DIR=build_qt5_msvc_x64"
set "BIN_DIR=bin_qt5_msvc_x64"
set "CMAKE_GEN=Visual Studio 17 2022"
set "CMAKE_ARCH=x64"
set "VCARCH=x64"
call :BUILD_MSVC
if !errorlevel! neq 0 echo WARNING: Config 3 build failed, skipping...

:: ============================================================
:: Config 4: Qt5 + MSVC2019(via VS2022) + x86
:: ============================================================
echo.
echo [Config 4/4] Qt5 + MSVC + x86
set "QT_PREFIX=C:\Qt\5.15.2\msvc2019"
set "BUILD_DIR=build_qt5_msvc_x86"
set "BIN_DIR=bin_qt5_msvc_x86"
set "CMAKE_GEN=Visual Studio 17 2022"
set "CMAKE_ARCH=Win32"
set "VCARCH=x86"
call :BUILD_MSVC
if !errorlevel! neq 0 echo WARNING: Config 4 build failed, skipping...

:_PACK_ALL
echo.
echo ============================================================
echo  Packaging all configs...
echo ============================================================

:: Pack Config 1: Qt6 MSVC x64
call :PACK_ONE "bin_qt6_msvc_x64" "qt6.8_msvc2022" "x64" "msvc" "x64"

:: Pack Config 2: Qt6 MinGW x64
call :PACK_ONE "bin_qt6_mingw_x64" "qt6.8_mingw13" "x64" "mingw" "x64"

:: Pack Config 3: Qt5 MSVC x64
call :PACK_ONE "bin_qt5_msvc_x64" "qt5.15_msvc2022" "x64" "msvc" "x64"

:: Pack Config 4: Qt5 MSVC x86
call :PACK_ONE "bin_qt5_msvc_x86" "qt5.15_msvc2022" "x86" "msvc" "x86"

:: --- Cleanup intermediate directories ---
echo.
echo [Cleanup] Removing intermediate build/bin directories...
for %%d in (build_qt6_msvc_x64 build_qt6_mingw_x64 build_qt5_msvc_x64 build_qt5_msvc_x86) do (
    if exist %%d rd /s /q %%d
)
for %%d in (bin_qt6_msvc_x64 bin_qt6_mingw_x64 bin_qt5_msvc_x64 bin_qt5_msvc_x86) do (
    if exist %%d rd /s /q %%d
)
if exist bin rd /s /q bin

:: --- Summary ---
echo.
echo ============================================================
echo  Output files in release/:
echo ============================================================
dir /b release\
echo.
goto _END

:: ============================================================
:: SUBROUTINE: BUILD_MSVC
:: Uses: BUILD_DIR, BIN_DIR, QT_PREFIX, CMAKE_GEN, CMAKE_ARCH, VCARCH
:: ============================================================
:BUILD_MSVC
if not exist "!BUILD_DIR!" md "!BUILD_DIR!"

:: Clean shared bin/ to avoid cross-contamination between configs
if exist bin rd /s /q bin

:: Configure (disable CMakeLists.txt POST_BUILD deploy, we do it ourselves)
echo   [Configure] ...
cmake -G "!CMAKE_GEN!" -A !CMAKE_ARCH! -DCMAKE_PREFIX_PATH="!QT_PREFIX!" -DSKIP_DEPLOY=ON -S . -B "!BUILD_DIR!"
if !errorlevel! neq 0 exit /b 1

:: Build (multi-core)
echo   [Build] ...
cmake --build "!BUILD_DIR!" --config Release --parallel
if !errorlevel! neq 0 exit /b 1

:: Collect output: copy bin/ to BIN_DIR
echo   [Collect] ...
if exist "!BIN_DIR!" rd /s /q "!BIN_DIR!"
xcopy /e /i /q bin "!BIN_DIR!" >nul

:: Deploy Qt runtime
echo   [Deploy] ...
"!QT_PREFIX!\bin\windeployqt.exe" "!BIN_DIR!\%APP_NAME%.exe"
exit /b 0

:: ============================================================
:: SUBROUTINE: BUILD_MINGW
:: Uses: BUILD_DIR, BIN_DIR, QT_PREFIX, MINGW_PATH
:: ============================================================
:BUILD_MINGW
if not exist "!BUILD_DIR!" md "!BUILD_DIR!"

:: Clean shared bin/ to avoid cross-contamination between configs
if exist bin rd /s /q bin

:: Save PATH and add MinGW for this build only
set "SAVED_PATH=!PATH!"
set "PATH=!MINGW_PATH!;!QT_PREFIX!\bin;!PATH!"

:: Configure (disable CMakeLists.txt POST_BUILD deploy, we do it ourselves)
echo   [Configure] ...
cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="!QT_PREFIX!" -DCMAKE_BUILD_TYPE=Release -DSKIP_DEPLOY=ON -S . -B "!BUILD_DIR!"
if !errorlevel! neq 0 exit /b 1

:: Build (multi-core)
echo   [Build] ...
cmake --build "!BUILD_DIR!" --config Release --parallel
if !errorlevel! neq 0 exit /b 1

:: Collect output
echo   [Collect] ...
if exist "!BIN_DIR!" rd /s /q "!BIN_DIR!"
xcopy /e /i /q bin "!BIN_DIR!" >nul

:: Deploy Qt runtime
echo   [Deploy] ...
"!QT_PREFIX!\bin\windeployqt.exe" "!BIN_DIR!\%APP_NAME%.exe"

:: Restore PATH
set "PATH=!SAVED_PATH!"
exit /b 0

:: ============================================================
:: SUBROUTINE: PACK_ONE
:: %~1=BIN_DIR  %~2=qt_compiler_tag  %~3=arch  %~4=compiler_id  %~5=iss_arch
:: ============================================================
:PACK_ONE
set "P_BIN=%~1"
set "P_TAG=%~2"
set "P_ARCH=%~3"
set "P_COMPILER=%~4"
set "P_ISS_ARCH=%~5"

if not exist "!P_BIN!\%APP_NAME%.exe" (
    echo  - SKIP: !P_BIN! not found
    exit /b 0
)

set "PORTABLE_NAME=%APP_NAME%_portable_v!VERSION!_!P_ARCH!_!P_TAG!"
set "SETUP_NAME=%APP_NAME%_setup_v!VERSION!_!P_ARCH!_!P_TAG!"

:: .7z portable
echo  - Creating !PORTABLE_NAME!.7z ...
if exist "release\!PORTABLE_NAME!.7z" del "release\!PORTABLE_NAME!.7z"
"!SEVENZIP!" a -t7z "release\!PORTABLE_NAME!.7z" ".\!P_BIN!\*" >nul
if !errorlevel! neq 0 (
    echo    FAIL
) else (
    echo    OK
)

:: .exe installer via Inno Setup
if exist "!ISCC_PATH!" (
    echo  - Creating !SETUP_NAME!.exe ...
    "!ISCC_PATH!" /DMyAppVersion="!VERSION_FULL!" /DMyArchitecture="!P_ISS_ARCH!" /DMyCOMPILER_ID="!P_COMPILER!" /DMyBinDir="!P_BIN!" /DMyOutputDir="./release" /DOutputBaseFilename="!SETUP_NAME!" setup_package_user.iss >nul
    if !errorlevel! neq 0 (
        echo    FAIL
    ) else (
        echo    OK
    )
) else (
    echo  - SKIP: Inno Setup not found
)
exit /b 0

:_END
endlocal
