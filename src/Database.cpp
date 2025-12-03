#include "../include/Database.hpp"
#include "../include/Utils.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <limits>

// Constructor
Database::Database(const std::string& filename) : filename(filename) {
    loadFromFile();
}

// Generate next available ID
int Database::generateNextId() const {
    if (students.empty()) return 1;
    
    int maxId = 0;
    for (const auto& student : students) {
        if (student.getId() > maxId) {
            maxId = student.getId();
        }
    }
    return maxId + 1;
}

// File I/O - Load from JSON file
void Database::loadFromFile() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // File doesn't exist yet, start with empty database
        return;
    }
    
    students.clear();
    std::string line;
    std::string studentJson;
    bool inStudent = false;
    
    while (std::getline(file, line)) {
        if (line.find("{") != std::string::npos && line.find("\"students\"") == std::string::npos) {
            inStudent = true;
            studentJson = line + "\n";
        } else if (inStudent) {
            studentJson += line + "\n";
            if (line.find("}") != std::string::npos) {
                try {
                    Student student = Student::fromJson(studentJson);
                    if (student.getId() > 0) {
                        students.push_back(student);
                    }
                } catch (const std::exception& e) {
                    Utils::printWarning("Skipped invalid student entry");
                }
                studentJson.clear();
                inStudent = false;
            }
        }
    }
    
    file.close();
}

// File I/O - Save to JSON file
void Database::saveToFile() const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for writing: " + filename);
    }
    
    file << "{\n";
    file << "  \"students\": [\n";
    
    for (size_t i = 0; i < students.size(); ++i) {
        file << students[i].toJson();
        if (i < students.size() - 1) {
            file << ",";
        }
        file << "\n";
    }
    
    file << "  ]\n";
    file << "}\n";
    
    file.close();
}

// Add student with auto-generated ID
void Database::addStudent(const Student& student) {
    students.push_back(student);
    saveToFile();
}

// Add student interactively
void Database::addStudentInteractive() {
    try {
        int id = generateNextId();
        std::string name = Utils::getStringInput("Enter student name: ");
        int age = Utils::getIntInput("Enter age: ");
        std::string major = Utils::getStringInput("Enter major: ");
        double gpa = Utils::getDoubleInput("Enter GPA (0.0 - 4.0): ");
        
        Student student(id, name, age, major, gpa);
        addStudent(student);
        
        Utils::printSuccess("Student added successfully with ID: " + std::to_string(id));
    } catch (const std::exception& e) {
        Utils::printError(e.what());
    }
}

// Edit student by ID
bool Database::editStudent(int id) {
    auto it = std::find_if(students.begin(), students.end(),
                          [id](const Student& s) { return s.getId() == id; });
    
    if (it == students.end()) {
        Utils::printError("Student with ID " + std::to_string(id) + " not found.");
        return false;
    }
    
    std::cout << "\nCurrent information:\n";
    it->displayDetailed();
    
    std::cout << "\n" << Color::YELLOW << "Enter new information (press Enter to keep current value):\n" 
              << Color::RESET;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    try {
        // Name
        std::cout << Color::YELLOW << "New name [" << it->getName() << "]: " << Color::RESET;
        std::string name;
        std::getline(std::cin, name);
        if (!name.empty()) {
            it->setName(Utils::trim(name));
        }
        
        // Age
        std::cout << Color::YELLOW << "New age [" << it->getAge() << "]: " << Color::RESET;
        std::string ageStr;
        std::getline(std::cin, ageStr);
        if (!ageStr.empty()) {
            it->setAge(std::stoi(ageStr));
        }
        
        // Major
        std::cout << Color::YELLOW << "New major [" << it->getMajor() << "]: " << Color::RESET;
        std::string major;
        std::getline(std::cin, major);
        if (!major.empty()) {
            it->setMajor(Utils::trim(major));
        }
        
        // GPA
        std::cout << Color::YELLOW << "New GPA [" << std::fixed << std::setprecision(2) 
                  << it->getGpa() << "]: " << Color::RESET;
        std::string gpaStr;
        std::getline(std::cin, gpaStr);
        if (!gpaStr.empty()) {
            it->setGpa(std::stod(gpaStr));
        }
        
        saveToFile();
        Utils::printSuccess("Student information updated successfully!");
        return true;
        
    } catch (const std::exception& e) {
        Utils::printError(e.what());
        return false;
    }
}

// Delete student by ID
bool Database::deleteStudent(int id) {
    auto it = std::find_if(students.begin(), students.end(),
                          [id](const Student& s) { return s.getId() == id; });
    
    if (it == students.end()) {
        Utils::printError("Student with ID " + std::to_string(id) + " not found.");
        return false;
    }
    
    std::cout << "\nStudent to be deleted:\n";
    it->displayDetailed();
    
    std::string confirm = Utils::getStringInput("\nAre you sure you want to delete this student? (yes/no): ");
    if (confirm == "yes" || confirm == "y" || confirm == "Y" || confirm == "YES") {
        students.erase(it);
        saveToFile();
        Utils::printSuccess("Student deleted successfully!");
        return true;
    } else {
        Utils::printWarning("Deletion cancelled.");
        return false;
    }
}

// Search by ID
std::vector<Student> Database::searchById(int id) const {
    std::vector<Student> results;
    auto it = std::find_if(students.begin(), students.end(),
                          [id](const Student& s) { return s.getId() == id; });
    if (it != students.end()) {
        results.push_back(*it);
    }
    return results;
}

// Search by name (partial match, case-insensitive)
std::vector<Student> Database::searchByName(const std::string& name) const {
    std::vector<Student> results;
    std::string lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    
    for (const auto& student : students) {
        std::string studentName = student.getName();
        std::transform(studentName.begin(), studentName.end(), studentName.begin(), ::tolower);
        
        if (studentName.find(lowerName) != std::string::npos) {
            results.push_back(student);
        }
    }
    return results;
}

// Search by major
std::vector<Student> Database::searchByMajor(const std::string& major) const {
    std::vector<Student> results;
    std::string lowerMajor = major;
    std::transform(lowerMajor.begin(), lowerMajor.end(), lowerMajor.begin(), ::tolower);
    
    for (const auto& student : students) {
        std::string studentMajor = student.getMajor();
        std::transform(studentMajor.begin(), studentMajor.end(), studentMajor.begin(), ::tolower);
        
        if (studentMajor.find(lowerMajor) != std::string::npos) {
            results.push_back(student);
        }
    }
    return results;
}

// Search by GPA range
std::vector<Student> Database::searchByGpaRange(double minGpa, double maxGpa) const {
    std::vector<Student> results;
    
    for (const auto& student : students) {
        if (student.getGpa() >= minGpa && student.getGpa() <= maxGpa) {
            results.push_back(student);
        }
    }
    return results;
}

// Display all students
void Database::displayAll() const {
    if (students.empty()) {
        Utils::printWarning("No students in the database.");
        return;
    }
    
    displayStudents(students);
}

// Display a list of students
void Database::displayStudents(const std::vector<Student>& studentList) const {
    if (studentList.empty()) {
        Utils::printWarning("No students found.");
        return;
    }
    
    std::cout << "\n" << Color::BOLD << Color::CYAN 
              << "Total Students: " << studentList.size() << Color::RESET << "\n\n";
    
    std::cout << Color::BOLD << std::setw(8) << "ID" 
              << " │ " << std::setw(25) << std::left << "Name"
              << " │ " << std::setw(4) << "Age"
              << " │ " << std::setw(20) << "Major"
              << " │ " << std::setw(5) << "GPA" << Color::RESET << "\n";
    
    Utils::printSeparator();
    
    for (const auto& student : studentList) {
        student.display();
    }
    
    std::cout << "\n";
}

// Sort by name
void Database::sortByName(bool ascending) {
    if (ascending) {
        std::sort(students.begin(), students.end());
    } else {
        std::sort(students.begin(), students.end(), std::greater<Student>());
    }
}

// Sort by GPA
void Database::sortByGpa(bool ascending) {
    std::sort(students.begin(), students.end(),
             [ascending](const Student& a, const Student& b) {
                 return ascending ? (a.getGpa() < b.getGpa()) : (a.getGpa() > b.getGpa());
             });
}

// Get average GPA
double Database::getAverageGpa() const {
    if (students.empty()) return 0.0;
    
    double sum = 0.0;
    for (const auto& student : students) {
        sum += student.getGpa();
    }
    return sum / students.size();
}

// Get highest GPA
double Database::getHighestGpa() const {
    if (students.empty()) return 0.0;
    
    double maxGpa = students[0].getGpa();
    for (const auto& student : students) {
        if (student.getGpa() > maxGpa) {
            maxGpa = student.getGpa();
        }
    }
    return maxGpa;
}

// Get students per major
std::map<std::string, int> Database::getStudentsPerMajor() const {
    std::map<std::string, int> majorCount;
    
    for (const auto& student : students) {
        majorCount[student.getMajor()]++;
    }
    
    return majorCount;
}

// Display statistics
void Database::displayStatistics() const {
    if (students.empty()) {
        Utils::printWarning("No students in the database. No statistics available.");
        return;
    }
    
    Utils::printHeader("Student Statistics");
    
    std::cout << Color::BOLD << Color::GREEN << "Overall Statistics:\n" << Color::RESET;
    std::cout << "  Total Students: " << Color::CYAN << students.size() << Color::RESET << "\n";
    std::cout << "  Average GPA:    " << Color::CYAN << std::fixed << std::setprecision(2) 
              << getAverageGpa() << Color::RESET << "\n";
    std::cout << "  Highest GPA:    " << Color::CYAN << std::fixed << std::setprecision(2) 
              << getHighestGpa() << Color::RESET << "\n\n";
    
    std::cout << Color::BOLD << Color::GREEN << "Students per Major:\n" << Color::RESET;
    auto majorStats = getStudentsPerMajor();
    
    for (const auto& pair : majorStats) {
        std::cout << "  " << std::setw(25) << std::left << pair.first << ": " 
                  << Color::CYAN << pair.second << Color::RESET << " student(s)\n";
    }
    std::cout << "\n";
}

// Export report to file
void Database::exportReport(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for writing: " + filename);
    }
    
    file << "====================================================\n";
    file << "         STUDENT MANAGEMENT SYSTEM - REPORT         \n";
    file << "====================================================\n\n";
    
    file << "Generated: " << __DATE__ << " " << __TIME__ << "\n\n";
    
    file << "OVERALL STATISTICS\n";
    file << "--------------------------------------------------\n";
    file << "Total Students: " << students.size() << "\n";
    file << "Average GPA:    " << std::fixed << std::setprecision(2) << getAverageGpa() << "\n";
    file << "Highest GPA:    " << std::fixed << std::setprecision(2) << getHighestGpa() << "\n\n";
    
    file << "STUDENTS PER MAJOR\n";
    file << "--------------------------------------------------\n";
    auto majorStats = getStudentsPerMajor();
    for (const auto& pair : majorStats) {
        file << "  " << std::setw(25) << std::left << pair.first << ": " 
             << pair.second << " student(s)\n";
    }
    file << "\n";
    
    file << "ALL STUDENTS\n";
    file << "--------------------------------------------------\n";
    file << std::setw(8) << "ID" 
         << " | " << std::setw(25) << std::left << "Name"
         << " | " << std::setw(4) << "Age"
         << " | " << std::setw(20) << "Major"
         << " | " << std::setw(5) << "GPA" << "\n";
    file << "--------------------------------------------------\n";
    
    for (const auto& student : students) {
        file << std::setw(8) << student.getId()
             << " | " << std::setw(25) << std::left << student.getName()
             << " | " << std::setw(4) << student.getAge()
             << " | " << std::setw(20) << student.getMajor()
             << " | " << std::fixed << std::setprecision(2) << std::setw(5) 
             << student.getGpa() << "\n";
    }
    
    file << "\n====================================================\n";
    file << "                    END OF REPORT                    \n";
    file << "====================================================\n";
    
    file.close();
    Utils::printSuccess("Report exported to: " + filename);
}
