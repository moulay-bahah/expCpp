@echo off
echo ============================================
echo Building Student Management System
echo ============================================

if not exist "build" mkdir build

echo.
echo Compiling source files...
g++ -std=c++17 -Wall -Wextra -I./include ^
    -c src/Utils.cpp -o build/Utils.o

g++ -std=c++17 -Wall -Wextra -I./include ^
    -c src/Student.cpp -o build/Student.o

g++ -std=c++17 -Wall -Wextra -I./include ^
    -c src/Course.cpp -o build/Course.o

g++ -std=c++17 -Wall -Wextra -I./include ^
    -c src/Database.cpp -o build/Database.o

g++ -std=c++17 -Wall -Wextra -I./include ^
    -c src/Application.cpp -o build/Application.o

g++ -std=c++17 -Wall -Wextra -I./include ^
    -c src/main.cpp -o build/main.o

echo.
echo Linking...
g++ build/Utils.o build/Student.o build/Course.o ^
    build/Database.o build/Application.o build/main.o ^
    -o StudentManagementSystem.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ============================================
    echo Build successful!
    echo Executable: StudentManagementSystem.exe
    echo ============================================
) else (
    echo.
    echo ============================================
    echo Build failed!
    echo ============================================
)
