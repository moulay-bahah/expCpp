# Simple Student Management System

A simple, beginner-friendly Student Management System written in C++. This project demonstrates basic programming concepts like arrays, structures, file handling, and functions.

## Features

- **Add Student**: Create new student records with ID, Name, Age, Major, and GPA.
- **View All**: List all students currently in the database.
- **Search**: Find students by name.
- **Edit**: Update existing student information.
- **Delete**: Remove students from the system.
- **Auto-Save**: Data is automatically saved to `students.txt` after every change.

## How to Compile

You have two options to compile the program:

### Option 1: Using the Build Script (Recommended)
Simply double-click the `compile.bat` file included in the project folder. This will automatically compile the code for you.

### Option 2: Manual Compilation
If you prefer to use the command line, open your terminal (Command Prompt or PowerShell) in the project directory and run:

```bash
g++ -o StudentManagement.exe main.cpp
```

## How to Run

After compilation, you can run the program by executing the generated `.exe` file:

```bash
StudentManagement.exe
```

Or by double-clicking `StudentManagement.exe` in your file explorer.

## File Structure

- `main.cpp`: The complete source code for the application.
- `students.txt`: The data file where student records are stored (created automatically).
- `compile.bat`: innovative script to simplify compilation.
- `PRESENTATION.md`: A presentation describing the project.
