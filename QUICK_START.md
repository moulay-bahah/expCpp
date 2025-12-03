# Quick Start Guide

## Build & Run (Windows)

### Using the build script:
```powershell
.\build.bat
.\StudentManagementSystem.exe
```

### Manual build:
```powershell
# Create build directory if it doesn't exist
mkdir build

# Compile all source files
g++ -std=c++17 -Wall -Wextra -I./include -c src/Utils.cpp -o build/Utils.o
g++ -std=c++17 -Wall -Wextra -I./include -c src/Student.cpp -o build/Student.o
g++ -std=c++17 -Wall -Wextra -I./include -c src/Course.cpp -o build/Course.o
g++ -std=c++17 -Wall -Wextra -I./include -c src/Database.cpp -o build/Database.o
g++ -std=c++17 -Wall -Wextra -I./include -c src/Application.cpp -o build/Application.o
g++ -std=c++17 -Wall -Wextra -I./include -c src/main.cpp -o build/main.o

# Link all object files
g++ build/Utils.o build/Student.o build/Course.o build/Database.o build/Application.o build/main.o -o StudentManagementSystem.exe

# Run the application
.\StudentManagementSystem.exe
```

## Files Created After First Run
- `students.json` - Your student database (auto-created and auto-saved)
- Any exported reports (e.g., `student_report.txt`)

## Features Quick Reference
1. **Add Student** - Auto-generates ID
2. **Edit Student** - Modify any field
3. **Delete Student** - With confirmation
4. **Search** - By ID, name, major, or GPA range
5. **Sort & Display** - By name or GPA
6. **List All** - View all students
7. **Statistics** - Average GPA, highest GPA, students per major
8. **Export Report** - Generate text file report

## Tips
- All data is saved automatically to `students.json`
- Use partial names for searching (case-insensitive)
- GPA must be between 0.0 and 4.0
- Age must be between 1 and 150
- Student IDs are auto-generated and cannot be changed
