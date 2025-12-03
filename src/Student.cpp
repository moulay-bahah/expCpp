#include "../include/Student.hpp"
#include "../include/Utils.hpp"
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <algorithm>

// Default constructor
Student::Student() : id(0), name(""), age(0), major(""), gpa(0.0) {}

// Parameterized constructor
Student::Student(int id, const std::string& name, int age, const std::string& major, double gpa) {
    setId(id);
    setName(name);
    setAge(age);
    setMajor(major);
    setGpa(gpa);
}

// Setters with validation
void Student::setId(int id) {
    if (id <= 0) {
        throw std::invalid_argument("Student ID must be a positive integer.");
    }
    this->id = id;
}

void Student::setName(const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Student name cannot be empty.");
    }
    this->name = name;
}

void Student::setAge(int age) {
    if (!isValidAge(age)) {
        throw std::invalid_argument("Age must be between 1 and 150.");
    }
    this->age = age;
}

void Student::setMajor(const std::string& major) {
    if (major.empty()) {
        throw std::invalid_argument("Major cannot be empty.");
    }
    this->major = major;
}

void Student::setGpa(double gpa) {
    if (!isValidGpa(gpa)) {
        throw std::invalid_argument("GPA must be between 0.0 and 4.0.");
    }
    this->gpa = gpa;
}

// Display methods
void Student::display() const {
    std::cout << Color::BOLD << std::setw(8) << id << Color::RESET
              << " │ " << Color::CYAN << std::setw(25) << std::left << name << Color::RESET
              << " │ " << std::setw(4) << age
              << " │ " << std::setw(20) << major
              << " │ " << Color::GREEN << std::fixed << std::setprecision(2) 
              << std::setw(5) << gpa << Color::RESET << "\n";
}

void Student::displayDetailed() const {
    std::cout << Color::BOLD << Color::CYAN << "\n┌─ Student Details ─────────────────────────────────┐\n" 
              << Color::RESET;
    std::cout << Color::YELLOW << "  ID:    " << Color::RESET << id << "\n";
    std::cout << Color::YELLOW << "  Name:  " << Color::RESET << name << "\n";
    std::cout << Color::YELLOW << "  Age:   " << Color::RESET << age << "\n";
    std::cout << Color::YELLOW << "  Major: " << Color::RESET << major << "\n";
    std::cout << Color::YELLOW << "  GPA:   " << Color::RESET << std::fixed 
              << std::setprecision(2) << gpa << "\n";
    std::cout << Color::BOLD << Color::CYAN << "└───────────────────────────────────────────────────┘\n" 
              << Color::RESET;
}

// Comparison operators
bool Student::operator<(const Student& other) const {
    return name < other.name;
}

bool Student::operator>(const Student& other) const {
    return name > other.name;
}

// Validation helpers
bool Student::isValidGpa(double gpa) {
    return gpa >= 0.0 && gpa <= 4.0;
}

bool Student::isValidAge(int age) {
    return age > 0 && age <= 150;
}

// JSON serialization
std::string Student::toJson() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "    {\n";
    oss << "      \"id\": " << id << ",\n";
    oss << "      \"name\": \"" << name << "\",\n";
    oss << "      \"age\": " << age << ",\n";
    oss << "      \"major\": \"" << major << "\",\n";
    oss << "      \"gpa\": " << gpa << "\n";
    oss << "    }";
    return oss.str();
}

// Simple JSON parsing (manual implementation)
Student Student::fromJson(const std::string& json) {
    Student student;
    std::istringstream iss(json);
    std::string line;
    
    while (std::getline(iss, line)) {
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) continue;
        
        std::string key = line.substr(0, colonPos);
        std::string value = line.substr(colonPos + 1);
        
        // Remove quotes, spaces, commas
        key.erase(std::remove(key.begin(), key.end(), '\"'), key.end());
        key.erase(std::remove(key.begin(), key.end(), ' '), key.end());
        value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
        value.erase(std::remove(value.begin(), value.end(), ','), value.end());
        value = Utils::trim(value);
        
        try {
            if (key == "id") {
                student.setId(std::stoi(value));
            } else if (key == "name") {
                student.setName(value);
            } else if (key == "age") {
                student.setAge(std::stoi(value));
            } else if (key == "major") {
                student.setMajor(value);
            } else if (key == "gpa") {
                student.setGpa(std::stod(value));
            }
        } catch (const std::exception& e) {
            // Skip invalid fields
        }
    }
    
    return student;
}
