@echo off
:: ============================================================================
:: CDocx Code Quality Check Script (Windows)
:: ============================================================================
:: Usage:
::   scripts\code-quality.bat format       - Format all code
::   scripts\code-quality.bat format-check - Check formatting without changes
::   scripts\code-quality.bat tidy         - Run static analysis
::   scripts\code-quality.bat tidy-fix     - Run static analysis with auto-fix
::   scripts\code-quality.bat all          - Run all checks
:: ============================================================================

setlocal EnableDelayedExpansion

cd /d "%~dp0\.."

if "%~1"=="" goto :usage

set BUILD_DIR=build
if not exist %BUILD_DIR% (
    echo [ERROR] Build directory not found: %BUILD_DIR%
    echo Please run: mkdir build ^&^& cd build ^&^& cmake ..
    exit /b 1
)

if "%~1"=="format" goto :format
if "%~1"=="format-check" goto :format-check
if "%~1"=="tidy" goto :tidy
if "%~1"=="tidy-fix" goto :tidy-fix
if "%~1"=="all" goto :all

goto :usage

:format
echo [Code Quality] Formatting code with clang-format...
cmake --build %BUILD_DIR% --target format
goto :end

:format-check
echo [Code Quality] Checking code formatting...
cmake --build %BUILD_DIR% --target format-check
goto :end

:tidy
echo [Code Quality] Running clang-tidy analysis...
cmake --build %BUILD_DIR% --target tidy
goto :end

:tidy-fix
echo [Code Quality] Running clang-tidy with auto-fix...
cmake --build %BUILD_DIR% --target tidy-fix
goto :end

:all
echo [Code Quality] Running all checks...
echo.
echo === Format Check ===
cmake --build %BUILD_DIR% --target format-check
echo.
echo === Static Analysis ===
cmake --build %BUILD_DIR% --target tidy
goto :end

:usage
echo.
echo CDocx Code Quality Tools
echo ========================
echo.
echo Usage: %~nx0 [command]
echo.
echo Commands:
echo   format       - Format all code with clang-format
echo   format-check - Check formatting without making changes
echo   tidy         - Run clang-tidy static analysis
echo   tidy-fix     - Run clang-tidy with automatic fixes
echo   all          - Run format-check and tidy
echo.
echo Examples:
echo   %~nx0 format
echo   %~nx0 tidy-fix
echo.

:end
endlocal
