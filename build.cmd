@echo off 

set DEBUG_DIR=build-debug
set RELEASE_DIR=build-release

echo.
echo *******************************
echo *** Building ForcePAD       ***
echo *******************************
echo.

set action=%1

if %action%=="" (
    set action=config
)

echo *** Action: %action%

if %action%==clean (
    echo *** Cleaning build directories
    echo.
    if exist %RELEASE_DIR% rmdir /s /q %RELEASE_DIR%
    if exist %DEBUG_DIR% rmdir /s /q %DEBUG_DIR%    
    exit /b 0
)

if not exist %DEBUG_DIR% mkdir %DEBUG_DIR%  
if not exist %RELEASE_DIR% mkdir %RELEASE_DIR%  

if %action%==config (
    echo *** Configuring debug build
    echo.
    cmake -B %DEBUG_DIR% -DCMAKE_BUILD_TYPE=Debug --preset default
    echo.
    echo *** Building debug build
    echo.
    cmake --build %DEBUG_DIR% --config Debug -- /m
    echo.
    echo *** Configuring release build
    echo.
    cmake -B %RELEASE_DIR% -DCMAKE_BUILD_TYPE=Release --preset default
    echo.
    echo *** Building release build
    echo.
    cmake --build %RELEASE_DIR% --config Release -- /m
    exit /b 0
)