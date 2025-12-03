#include "../include/Course.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <stdexcept>

// Default constructor
Course::Course() : courseCode(""), courseName(""), credits(0), instructor("") {}

// Parameterized constructor
Course::Course(const std::string& code, const std::string& name, int credits, const std::string& instructor) {
    setCourseCode(code);
    setCourseName(name);
    setCredits(credits);
    setInstructor(instructor);
}

// Setters with validation
void Course::setCourseCode(const std::string& code) {
    if (code.empty()) {
        throw std::invalid_argument("Course code cannot be empty.");
    }
    this->courseCode = code;
}

void Course::setCourseName(const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Course name cannot be empty.");
    }
    this->courseName = name;
}

void Course::setCredits(int credits) {
    if (credits <= 0) {
        throw std::invalid_argument("Credits must be a positive integer.");
    }
    this->credits = credits;
}

void Course::setInstructor(const std::string& instructor) {
    if (instructor.empty()) {
        throw std::invalid_argument("Instructor name cannot be empty.");
    }
    this->instructor = instructor;
}

// Display method
void Course::display() const {
    std::cout << Color::CYAN << courseCode << Color::RESET << " - " 
              << courseName << " (" << credits << " credits) - Prof. " 
              << instructor << "\n";
}
