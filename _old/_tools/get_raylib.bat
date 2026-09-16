@echo off
chcp 65001 >nul
cd /d "%~dp0.."

echo.
echo   Re-downloading raylib 6.0 source into vendor\raylib ...
echo.

if exist "vendor\raylib" rmdir /s /q "vendor\raylib"
git clone --depth 1 --branch 6.0 https://github.com/raysan5/raylib.git "vendor\raylib"

if errorlevel 1 (
  echo.
  echo [ERROR] Clone failed - no network, or git is missing.
  pause
  exit /b 1
)

if exist "build" rmdir /s /q "build"
echo.
echo   Done. Now double-click build.bat
echo.
pause
