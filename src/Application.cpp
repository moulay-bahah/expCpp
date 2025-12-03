#include "../include/Application.hpp"
#include "../include/Utils.hpp"
#include <iostream>
#include <limits>

// Constructor
Application::Application() : database("students.json"), running(true) {}

// Main application loop
void Application::run() {
    Utils::clearScreen();
    
    std::cout << Color::BOLD << Color::MAGENTA;
    std::cout << R"(
    ╔═══════════════════════════════════════════════════════════════╗
    ║                                                               ║
    ║       STUDENT MANAGEMENT SYSTEM                               ║
    ║       Modern C++ Application                                  ║
    ║                                                               ║
    ╚═══════════════════════════════════════════════════════════════╝
    )" << Color::RESET << "\n";
    
    Utils::pause();
    
    while (running) {
        handleMainMenu();
    }
}

// Display main menu
void Application::displayMainMenu() const {
    Utils::clearScreen();
    Utils::printHeader("MAIN MENU");
    
    std::cout << Color::CYAN << "  1. " << Color::RESET << "Add New Student\n";
    std::cout << Color::CYAN << "  2. " << Color::RESET << "Edit Student Information\n";
    std::cout << Color::CYAN << "  3. " << Color::RESET << "Delete Student\n";
    std::cout << Color::CYAN << "  4. " << Color::RESET << "Search Students\n";
    std::cout << Color::CYAN << "  5. " << Color::RESET << "Sort & Display Students\n";
    std::cout << Color::CYAN << "  6. " << Color::RESET << "List All Students\n";
    std::cout << Color::CYAN << "  7. " << Color::RESET << "View Statistics\n";
    std::cout << Color::CYAN << "  8. " << Color::RESET << "Export Report to File\n";
    std::cout << Color::RED << "  0. " << Color::RESET << "Exit\n\n";
    Utils::printSeparator();
}

// Handle main menu
void Application::handleMainMenu() {
    displayMainMenu();
    
    int choice = Utils::getIntInput("\nEnter your choice: ");
    
    switch (choice) {
        case 1:
            handleAddStudent();
            break;
        case 2:
            handleEditStudent();
            break;
        case 3:
            handleDeleteStudent();
            break;
        case 4:
            handleSearch();
            break;
        case 5:
            handleSort();
            break;
        case 6:
            handleListAll();
            break;
        case 7:
            handleStatistics();
            break;
        case 8:
            handleExport();
            break;
        case 0:
            exit();
            break;
        default:
            Utils::printError("Invalid choice. Please try again.");
            Utils::pause();
    }
}

// Add student
void Application::handleAddStudent() {
    Utils::clearScreen();
    Utils::printHeader("ADD NEW STUDENT");
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    database.addStudentInteractive();
    
    Utils::pause();
}

// Edit student
void Application::handleEditStudent() {
    Utils::clearScreen();
    Utils::printHeader("EDIT STUDENT INFORMATION");
    
    if (database.isEmpty()) {
        Utils::printWarning("No students in the database.");
        Utils::pause();
        return;
    }
    
    int id = Utils::getIntInput("\nEnter student ID to edit: ");
    database.editStudent(id);
    
    Utils::pause();
}

// Delete student
void Application::handleDeleteStudent() {
    Utils::clearScreen();
    Utils::printHeader("DELETE STUDENT");
    
    if (database.isEmpty()) {
        Utils::printWarning("No students in the database.");
        Utils::pause();
        return;
    }
    
    int id = Utils::getIntInput("\nEnter student ID to delete: ");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    database.deleteStudent(id);
    
    Utils::pause();
}

// Display search menu
void Application::displaySearchMenu() const {
    Utils::printHeader("SEARCH STUDENTS");
    
    std::cout << Color::CYAN << "  1. " << Color::RESET << "Search by ID\n";
    std::cout << Color::CYAN << "  2. " << Color::RESET << "Search by Name\n";
    std::cout << Color::CYAN << "  3. " << Color::RESET << "Search by Major\n";
    std::cout << Color::CYAN << "  4. " << Color::RESET << "Search by GPA Range\n";
    std::cout << Color::RED << "  0. " << Color::RESET << "Back to Main Menu\n\n";
    Utils::printSeparator();
}

// Handle search
void Application::handleSearch() {
    Utils::clearScreen();
    displaySearchMenu();
    
    int choice = Utils::getIntInput("\nEnter your choice: ");
    std::vector<Student> results;
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    switch (choice) {
        case 1: {
            int id = Utils::getIntInput("Enter student ID: ");
            results = database.searchById(id);
            Utils::clearScreen();
            Utils::printHeader("SEARCH RESULTS (By ID)");
            database.displayStudents(results);
            break;
        }
        case 2: {
            std::string name = Utils::getStringInput("Enter student name (partial match): ");
            results = database.searchByName(name);
            Utils::clearScreen();
            Utils::printHeader("SEARCH RESULTS (By Name)");
            database.displayStudents(results);
            break;
        }
        case 3: {
            std::string major = Utils::getStringInput("Enter major: ");
            results = database.searchByMajor(major);
            Utils::clearScreen();
            Utils::printHeader("SEARCH RESULTS (By Major)");
            database.displayStudents(results);
            break;
        }
        case 4: {
            double minGpa = Utils::getDoubleInput("Enter minimum GPA: ");
            double maxGpa = Utils::getDoubleInput("Enter maximum GPA: ");
            results = database.searchByGpaRange(minGpa, maxGpa);
            Utils::clearScreen();
            Utils::printHeader("SEARCH RESULTS (By GPA Range)");
            database.displayStudents(results);
            break;
        }
        case 0:
            return;
        default:
            Utils::printError("Invalid choice.");
    }
    
    Utils::pause();
}

// Display sort menu
void Application::displaySortMenu() const {
    Utils::printHeader("SORT & DISPLAY STUDENTS");
    
    std::cout << Color::CYAN << "  1. " << Color::RESET << "Sort by Name (A-Z)\n";
    std::cout << Color::CYAN << "  2. " << Color::RESET << "Sort by Name (Z-A)\n";
    std::cout << Color::CYAN << "  3. " << Color::RESET << "Sort by GPA (Ascending)\n";
    std::cout << Color::CYAN << "  4. " << Color::RESET << "Sort by GPA (Descending)\n";
    std::cout << Color::RED << "  0. " << Color::RESET << "Back to Main Menu\n\n";
    Utils::printSeparator();
}

// Handle sort
void Application::handleSort() {
    Utils::clearScreen();
    displaySortMenu();
    
    int choice = Utils::getIntInput("\nEnter your choice: ");
    
    switch (choice) {
        case 1:
            database.sortByName(true);
            Utils::clearScreen();
            Utils::printHeader("STUDENTS SORTED BY NAME (A-Z)");
            database.displayAll();
            break;
        case 2:
            database.sortByName(false);
            Utils::clearScreen();
            Utils::printHeader("STUDENTS SORTED BY NAME (Z-A)");
            database.displayAll();
            break;
        case 3:
            database.sortByGpa(true);
            Utils::clearScreen();
            Utils::printHeader("STUDENTS SORTED BY GPA (ASCENDING)");
            database.displayAll();
            break;
        case 4:
            database.sortByGpa(false);
            Utils::clearScreen();
            Utils::printHeader("STUDENTS SORTED BY GPA (DESCENDING)");
            database.displayAll();
            break;
        case 0:
            return;
        default:
            Utils::printError("Invalid choice.");
    }
    
    Utils::pause();
}

// List all students
void Application::handleListAll() {
    Utils::clearScreen();
    Utils::printHeader("ALL STUDENTS");
    database.displayAll();
    Utils::pause();
}

// View statistics
void Application::handleStatistics() {
    Utils::clearScreen();
    database.displayStatistics();
    Utils::pause();
}

// Export report
void Application::handleExport() {
    Utils::clearScreen();
    Utils::printHeader("EXPORT REPORT");
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string filename = Utils::getStringInput("Enter filename (e.g., report.txt): ");
    
    if (filename.empty()) {
        filename = "student_report.txt";
    }
    
    try {
        database.exportReport(filename);
    } catch (const std::exception& e) {
        Utils::printError(e.what());
    }
    
    Utils::pause();
}

// Exit application
void Application::exit() {
    Utils::clearScreen();
    std::cout << Color::BOLD << Color::GREEN;
    std::cout << R"(
    ╔═══════════════════════════════════════════════════════════════╗
    ║                                                               ║
    ║       Thank you for using Student Management System!          ║
    ║                                                               ║
    ╚═══════════════════════════════════════════════════════════════╝
    )" << Color::RESET << "\n\n";
    
    running = false;
}
