@echo off
echo ========================================
echo Compiling Simple Student Management System
echo ========================================
echo.

g++ -o StudentManagement.exe main.cpp

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [SUCCESS] Compilation successful!
    echo Executable created: StudentManagement.exe
    echo.
    echo Run the program with: StudentManagement.exe
    echo.
) else (
    echo.
    echo [ERROR] Compilation failed!
    echo.
)

pause
