cmake_minimum_required(VERSION 3.10)
project(StudentManagementSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/Student.cpp
    src/Course.cpp
    src/Database.cpp
    src/Application.cpp
    src/Utils.cpp
)

# Create executable
add_executable(StudentManagementSystem ${SOURCES})

# Set output directory
set_target_properties(StudentManagementSystem PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)
