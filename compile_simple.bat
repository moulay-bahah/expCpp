@echo off
echo ========================================
echo Compiling Simple Student Management System
echo ========================================
echo.

g++ -o StudentManagementSimple.exe simple_main.cpp

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [SUCCESS] Compilation successful!
    echo Executable created: StudentManagementSimple.exe
    echo.
    echo Run the program with: StudentManagementSimple.exe
    echo.
) else (
    echo.
    echo [ERROR] Compilation failed!
    echo.
)

pause
