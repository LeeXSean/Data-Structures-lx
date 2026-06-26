@echo off
chcp 65001 >nul
setlocal EnableExtensions

echo ==================================================
echo        Data Structures - CMake Project Setup
echo ==================================================
echo.

set "BUILD_DIR=build"
set "VS_GENERATOR="

where cmake >nul 2>nul
if errorlevel 1 (
    echo [ERROR] CMake was not found in PATH.
    echo.
    echo Install CMake and enable "Add CMake to the system PATH", then run this script again.
    echo https://cmake.org/download/
    echo.
    pause
    exit /b 1
)
echo [OK] CMake found.

echo.
echo [INFO] Looking for a usable Visual Studio C++ generator...
call :try_generator "Visual Studio 18 2026"
if defined VS_GENERATOR goto :generator_found

call :try_generator "Visual Studio 17 2022"
if defined VS_GENERATOR goto :generator_found

call :try_generator "Visual Studio 16 2019"
if defined VS_GENERATOR goto :generator_found

echo.
echo [ERROR] No usable Visual Studio C++ generator was found.
echo.
echo CMake may list Visual Studio generators even when Visual Studio is incomplete.
echo Open Visual Studio Installer, repair or install Visual Studio, and include:
echo   - Desktop development with C++
echo   - MSVC C++ build tools
echo   - Windows SDK
echo.
pause
exit /b 1

:generator_found
echo [OK] Using %VS_GENERATOR%.
echo.
echo [INFO] Regenerating project files in "%BUILD_DIR%"...
echo [INFO] Existing CMake cache will be refreshed, so moved/renamed source folders are handled.

cmake -S "%CD%" -B "%BUILD_DIR%" -G "%VS_GENERATOR%" -A x64 --fresh
if errorlevel 1 (
    echo.
    echo [ERROR] CMake configure failed. Check the error above.
    echo.
    pause
    exit /b 1
)

echo.
echo ==================================================
echo          Project files generated successfully
echo          Run open_in_vs.bat to open Visual Studio
echo ==================================================
echo.
pause
exit /b 0

:try_generator
set "CANDIDATE=%~1"
cmake --help | findstr /C:"%CANDIDATE%" >nul 2>nul
if errorlevel 1 exit /b 1

set "PROBE_DIR=%TEMP%\data-struct-cmake-probe-%RANDOM%-%RANDOM%"
cmake -S "%CD%" -B "%PROBE_DIR%" -G "%CANDIDATE%" -A x64 >nul 2>nul
set "PROBE_RESULT=%ERRORLEVEL%"

if exist "%PROBE_DIR%" rmdir /s /q "%PROBE_DIR%" >nul 2>nul

if "%PROBE_RESULT%"=="0" (
    set "VS_GENERATOR=%CANDIDATE%"
    exit /b 0
)

exit /b 1
