# Student Management System

A modern, object-oriented C++ application for managing student records with comprehensive CRUD operations, advanced search capabilities, statistical analysis, and file-based persistence.

## Features

### Core Functionality
- ✅ **Add Students**: Create new student records with auto-generated IDs
- ✅ **Edit Students**: Update existing student information
- ✅ **Delete Students**: Remove students with confirmation
- ✅ **List All**: Display all students in a formatted table

### Advanced Search
- 🔍 Search by **ID**
- 🔍 Search by **Name** (partial match, case-insensitive)
- 🔍 Search by **Major**
- 🔍 Search by **GPA Range**

### Sorting Options
- 📊 Sort by **Name** (A-Z or Z-A)
- 📊 Sort by **GPA** (Ascending or Descending)

### Statistics & Reporting
- 📈 **Average GPA** across all students
- 📈 **Highest GPA** in the database
- 📈 **Students per Major** breakdown
- 📄 **Export Report** to text file

### Technical Features
- 🎨 **Colorful Console UI** with ANSI escape codes
- 💾 **JSON File Persistence** (auto-save/load)
- ✔️ **Input Validation** with exception handling
- 🏗️ **Clean OOP Architecture** with separate classes
- 🔧 **CMake Build System** for cross-platform compilation

## Project Structure

```
expCpp/
├── include/
│   ├── Student.hpp          # Student entity class
│   ├── Course.hpp           # Course entity class
│   ├── Database.hpp         # Data management & file I/O
│   ├── Application.hpp      # Menu controller
│   └── Utils.hpp            # Utility functions
├── src/
│   ├── Student.cpp
│   ├── Course.cpp
│   ├── Database.cpp
│   ├── Application.cpp
│   ├── Utils.cpp
│   └── main.cpp             # Entry point
├── CMakeLists.txt           # Build configuration
├── README.md                # This file
└── students.json            # Data file (auto-created)
```

## Building the Project

### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or higher

### Windows (using Visual Studio or MinGW)

```powershell
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build . --config Release

# Run the executable
cd ..
./StudentManagementSystem.exe
```

### Linux / macOS

```bash
# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Run the executable
cd ..
./StudentManagementSystem
```

## Usage Examples

### Adding a Student

```
Enter student name: John Doe
Enter age: 20
Enter major: Computer Science
Enter GPA (0.0 - 4.0): 3.75
```

Output:
```
✓ Student added successfully with ID: 1
```

### Searching by Name

```
Enter student name (partial match): john
```

Output:
```
Total Students: 1

      ID │ Name                      │ Age │ Major                │  GPA
────────────────────────────────────────────────────────────────
       1 │ John Doe                  │  20 │ Computer Science     │ 3.75
```

### Viewing Statistics

```
OVERALL STATISTICS
Total Students: 5
Average GPA:    3.42
Highest GPA:    3.95

STUDENTS PER MAJOR
  Computer Science          : 2 student(s)
  Mathematics              : 1 student(s)
  Physics                  : 2 student(s)
```

## Sample Data

Here's example JSON data that will be automatically created (`students.json`):

```json
{
  "students": [
    {
      "id": 1,
      "name": "John Doe",
      "age": 20,
      "major": "Computer Science",
      "gpa": 3.75
    },
    {
      "id": 2,
      "name": "Jane Smith",
      "age": 21,
      "major": "Mathematics",
      "gpa": 3.95
    }
  ]
}
```

## Class Architecture

### Student
- Encapsulates student data (ID, name, age, major, GPA)
- Provides validation for all fields
- Implements comparison operators for sorting
- Supports JSON serialization/deserialization

### Database
- Manages a collection of Student objects
- Handles file I/O (load/save to JSON)
- Implements CRUD operations
- Provides search and filter capabilities
- Calculates statistics

### Application
- Controls the main menu flow
- Handles user input and validation
- Coordinates between UI and Database
- Manages the application lifecycle

### Utils
- Console manipulation (clear screen, colors)
- Input validation helpers
- Formatted output functions

## Error Handling

The application uses C++ exceptions for error handling:
- **std::invalid_argument**: For invalid input data (e.g., GPA > 4.0)
- **std::runtime_error**: For file I/O errors
- Try-catch blocks throughout for graceful error recovery

## Contributing

This is a university coursework project demonstrating:
- Object-Oriented Programming principles
- STL usage (vector, string, algorithms)
- File I/O operations
- Clean code practices
- Modern C++ features

## License

This project is created for educational purposes.

## Author

Created as a comprehensive C++ programming assignment demonstrating modern software development practices.
