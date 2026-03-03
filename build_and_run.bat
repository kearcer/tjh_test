@echo off
chcp 65001 >nul
echo ==========================================
echo   TJH Test Project Builder
echo ==========================================
echo.
python "%~dp0build_project.py"
pause
